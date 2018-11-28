#include "DictionarySourceFactory.h"

#include <Columns/ColumnsNumber.h>
#include <Core/Block.h>
#include <Core/ColumnWithTypeAndName.h>
#include <DataTypes/DataTypeNullable.h>
#include <DataTypes/DataTypesNumber.h>
#include <Poco/Logger.h>
#include <common/logger_useful.h>
#include "DictionaryStructure.h"

namespace DB
{
namespace ErrorCodes
{
    extern const int UNKNOWN_ELEMENT_IN_CONFIG;
    extern const int EXCESSIVE_ELEMENT_IN_CONFIG;
    extern const int LOGICAL_ERROR;
    extern const int SUPPORT_IS_DISABLED;
}

namespace
{
    Block createSampleBlock(const DictionaryStructure & dict_struct)
    {
        Block block;

        if (dict_struct.id)
            block.insert(ColumnWithTypeAndName {ColumnUInt64::create(1, 0), std::make_shared<DataTypeUInt64>(), dict_struct.id->name});

        if (dict_struct.key)
        {
            for (const auto & attribute : *dict_struct.key)
            {
                auto column = attribute.type->createColumn();
                column->insertDefault();

                block.insert(ColumnWithTypeAndName {std::move(column), attribute.type, attribute.name});
            }
        }

        if (dict_struct.range_min)
        {
            for (const auto & attribute : {dict_struct.range_min, dict_struct.range_max})
            {
                const auto & type = std::make_shared<DataTypeNullable>(attribute->type);
                auto column = type->createColumn();
                column->insertDefault();

                block.insert(ColumnWithTypeAndName {std::move(column), type, attribute->name});
            }
        }

        for (const auto & attribute : dict_struct.attributes)
        {
            auto column = attribute.type->createColumn();
            column->insert(attribute.null_value);

            block.insert(ColumnWithTypeAndName {std::move(column), attribute.type, attribute.name});
        }

        return block;
    }

}


DictionarySourceFactory::DictionarySourceFactory() : log(&Poco::Logger::get("DictionarySourceFactory"))
{
}

void DictionarySourceFactory::registerSource(const std::string & source_type, Creator create_source)
{
    LOG_DEBUG(log, "Register dictionary source type `" + source_type + "`");
    if (!registered_sources.emplace(source_type, std::move(create_source)).second)
        throw Exception("DictionarySourceFactory: the source name '" + source_type + "' is not unique", ErrorCodes::LOGICAL_ERROR);
}

DictionarySourcePtr DictionarySourceFactory::create(
    const std::string & name,
    const Poco::Util::AbstractConfiguration & config,
    const std::string & config_prefix,
    const DictionaryStructure & dict_struct,
    Context & context) const
{
    Poco::Util::AbstractConfiguration::Keys keys;
    config.keys(config_prefix, keys);
    if (keys.size() != 1)
        throw Exception {name + ": element dictionary.source should have exactly one child element",
                         ErrorCodes::EXCESSIVE_ELEMENT_IN_CONFIG};

    auto sample_block = createSampleBlock(dict_struct);

    const auto & source_type = keys.front();

    {
        const auto found = registered_sources.find(source_type);
        if (found != registered_sources.end())
        {
            const auto & create_source = found->second;
            return create_source(dict_struct, config, config_prefix, sample_block, context);
        }
    }

    throw Exception {name + ": unknown dictionary source type: " + source_type, ErrorCodes::UNKNOWN_ELEMENT_IN_CONFIG};
}

}

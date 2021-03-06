---
machine_translated: true
machine_translated_rev: 72537a2d527c63c07aa5d2361a8829f3895cf2bd
toc_priority: 44
toc_title: "\u0627\u0644\u0632\u0627\u0645\u0627\u062A"
---

# الزامات {#requirements}

## CPU {#cpu}

برای نصب و راه اندازی از بسته های پیش ساخته دب, استفاده از یک پردازنده با معماری ایکس86\_64 و پشتیبانی برای سوس 4.2 دستورالعمل. برای اجرای ClickHouse با پردازنده های که پشتیبانی نمی کند SSE 4.2 یا AArch64 یا PowerPC64LE معماری شما باید ساخت ClickHouse از منابع.

تاتر پیاده سازی پردازش داده های موازی و با استفاده از تمام منابع سخت افزاری در دسترس. در هنگام انتخاب یک پردازنده, را به حساب که فاحشه خانه کار می کند موثر تر در تنظیمات با تعداد زیادی از هسته اما نرخ ساعت پایین تر از در تنظیمات با هسته کمتر و نرخ ساعت بالاتر. مثلا, 16 هسته با 2600 مگاهرتز بهتر از است 8 هسته با 3600 مگاهرتز.

توصیه می شود برای استفاده **افزایش توربو** و **بیش از حد نخ** تکنولوژیها. این به طور قابل توجهی بهبود عملکرد با حجم کار معمولی.

## RAM {#ram}

ما توصیه می کنیم با استفاده از حداقل 4 گیگابایت رم برای انجام نمایش داده شد غیر بدیهی است. سرور کلیک می توانید با مقدار بسیار کوچکتر از رم اجرا, اما نیاز به حافظه برای پردازش نمایش داده شد.

حجم مورد نیاز رم بستگی دارد:

-   پیچیدگی نمایش داده شد.
-   مقدار داده هایی که در نمایش داده شد پردازش شده است.

برای محاسبه حجم مورد نیاز رم, شما باید اندازه داده های موقت برای تخمین [GROUP BY](../sql-reference/statements/select/group-by.md#select-group-by-clause), [DISTINCT](../sql-reference/statements/select/distinct.md#select-distinct), [JOIN](../sql-reference/statements/select/join.md#select-join) و عملیات دیگر استفاده می کنید.

تاتر می توانید حافظه خارجی برای داده های موقت استفاده. ببینید [گروه در حافظه خارجی](../sql-reference/statements/select/group-by.md#select-group-by-in-external-memory) برای اطلاعات بیشتر.

## تعویض پرونده {#swap-file}

غیر فعال کردن فایل مبادله برای محیط های تولید.

## زیرسیستم ذخیره سازی {#storage-subsystem}

شما باید 2 گیگابایت فضای دیسک رایگان برای نصب کلیک کنید.

حجم ذخیره سازی مورد نیاز برای داده های خود را باید به طور جداگانه محاسبه می شود. ارزیابی باید شامل موارد زیر باشد:

-   تخمین حجم داده ها.

    شما می توانید یک نمونه از داده ها و اندازه متوسط یک ردیف از. سپس مقدار ضرب شده توسط تعدادی از ردیف شما برنامه ای برای ذخیره.

-   ضریب فشرده سازی داده ها.

    برای تخمین ضریب فشرده سازی داده ها, بار یک نمونه از داده های خود را به خانه, و مقایسه اندازه واقعی از داده ها با اندازه جدول ذخیره شده. مثلا, داده های کلیک استریم است که معمولا توسط فشرده 6-10 بار.

برای محاسبه حجم نهایی داده ها ذخیره می شود, اعمال ضریب فشرده سازی به حجم داده های تخمین زده شده. اگر شما قصد دارید برای ذخیره داده ها در چند کپی, سپس ضرب حجم تخمین زده شده توسط تعدادی از کپی.

## شبکه {#network}

در صورت امکان از شبکه های 10 گرم یا کلاس بالاتر استفاده کنید.

پهنای باند شبکه برای پردازش نمایش داده شد توزیع با مقدار زیادی از داده های متوسط بسیار مهم است. علاوه بر این, سرعت شبکه را تحت تاثیر قرار فرایندهای تکرار.

## نرم افزار {#software}

کلیک خانه در درجه اول برای خانواده لینوکس از سیستم عامل توسعه یافته است. توزیع لینوکس توصیه شده اوبونتو است. این `tzdata` بسته باید در سیستم نصب شود.

تاتر همچنین می توانید در دیگر خانواده سیستم عامل کار. مشاهده اطلاعات در [شروع کار](../getting-started/index.md) بخش از اسناد و مدارک.

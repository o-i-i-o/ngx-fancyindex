/* Automagically generated from zh_CN.lang, do not edit! */

#include "../template_zh.h"

static const nfi_str_t nfi_zh_CN_short_weekday[] = {
    NFI_S("周一"),
    NFI_S("周二"),
    NFI_S("周三"),
    NFI_S("周四"),
    NFI_S("周五"),
    NFI_S("周六"),
    NFI_S("周日")
};

static const nfi_str_t nfi_zh_CN_long_weekday[] = {
    NFI_S("星期一"),
    NFI_S("星期二"),
    NFI_S("星期三"),
    NFI_S("星期四"),
    NFI_S("星期五"),
    NFI_S("星期六"),
    NFI_S("星期日")
};

static const nfi_str_t nfi_zh_CN_short_month[] = {
    NFI_S("一月"),
    NFI_S("二月"),
    NFI_S("三月"),
    NFI_S("四月"),
    NFI_S("五月"),
    NFI_S("六月"),
    NFI_S("七月"),
    NFI_S("八月"),
    NFI_S("九月"),
    NFI_S("十月"),
    NFI_S("十一月"),
    NFI_S("十二月")
};

static const nfi_str_t nfi_zh_CN_long_month[] = {
    NFI_S("一月"),
    NFI_S("二月"),
    NFI_S("三月"),
    NFI_S("四月"),
    NFI_S("五月"),
    NFI_S("六月"),
    NFI_S("七月"),
    NFI_S("八月"),
    NFI_S("九月"),
    NFI_S("十月"),
    NFI_S("十一月"),
    NFI_S("十二月")
};

static const ngx_fancyindex_template_t nfi_template_zh_CN = {
    NFI_TEMPLATE_FIELDS(zh)
};

static const ngx_fancyindex_lang_t nfi_lang_zh_CN = {
    NFI_S("zh"),
    &nfi_template_zh_CN,
    nfi_zh_CN_short_weekday,
    nfi_zh_CN_long_weekday,
    nfi_zh_CN_short_month,
    nfi_zh_CN_long_month,
    6, 9, 9, 9,
    NFI_S("上午"),
    NFI_S("下午"),
    NFI_S("上午"),
    NFI_S("下午"),
    NFI_S("上级目录")
};

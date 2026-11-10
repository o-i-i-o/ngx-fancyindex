/* Automagically generated from en.lang, do not edit! */

#include "../template_en.h"

static const nfi_str_t nfi_en_short_weekday[] = {
    NFI_S("Mon"),
    NFI_S("Tue"),
    NFI_S("Wed"),
    NFI_S("Thu"),
    NFI_S("Fri"),
    NFI_S("Sat"),
    NFI_S("Sun")
};

static const nfi_str_t nfi_en_long_weekday[] = {
    NFI_S("Monday"),
    NFI_S("Tuesday"),
    NFI_S("Wednesday"),
    NFI_S("Thursday"),
    NFI_S("Friday"),
    NFI_S("Saturday"),
    NFI_S("Sunday")
};

static const nfi_str_t nfi_en_short_month[] = {
    NFI_S("Jan"),
    NFI_S("Feb"),
    NFI_S("Mar"),
    NFI_S("Apr"),
    NFI_S("May"),
    NFI_S("Jun"),
    NFI_S("Jul"),
    NFI_S("Aug"),
    NFI_S("Sep"),
    NFI_S("Oct"),
    NFI_S("Nov"),
    NFI_S("Dec")
};

static const nfi_str_t nfi_en_long_month[] = {
    NFI_S("January"),
    NFI_S("February"),
    NFI_S("March"),
    NFI_S("April"),
    NFI_S("May"),
    NFI_S("June"),
    NFI_S("July"),
    NFI_S("August"),
    NFI_S("September"),
    NFI_S("October"),
    NFI_S("November"),
    NFI_S("December")
};

static const ngx_fancyindex_template_t nfi_template_en = {
    NFI_TEMPLATE_FIELDS(en)
};

static const ngx_fancyindex_lang_t nfi_lang_en = {
    NFI_S("en"),
    &nfi_template_en,
    nfi_en_short_weekday,
    nfi_en_long_weekday,
    nfi_en_short_month,
    nfi_en_long_month,
    3, 9, 3, 9,
    NFI_S("AM"),
    NFI_S("PM"),
    NFI_S("am"),
    NFI_S("pm"),
    NFI_S("Parent directory/")
};

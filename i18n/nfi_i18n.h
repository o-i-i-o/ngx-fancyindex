#ifndef NFI_I18N_H
#define NFI_I18N_H

/*
 * A string literal whose length is known at compile time.
 */
typedef struct {
    const char *data;
    size_t      len;
} nfi_str_t;

#define NFI_S(s) { (s), sizeof(s) - 1 }
#define NFI_MAX(a, b) ((a) > (b) ? (a) : (b))
#define nfi_sizeof_ssz(s) (sizeof(s) - 1)

typedef struct {
    const u_char *t01_head1;
    const u_char *t02_head2;
    const u_char *t03_head3;
    const u_char *t04_body1;
    const u_char *t05_body2;
    const u_char *t06_list1;
    const u_char *t07_list2;
    const u_char *t08_foot1;

    size_t t01_head1_len;
    size_t t02_head2_len;
    size_t t03_head3_len;
    size_t t04_body1_len;
    size_t t05_body2_len;
    size_t t06_list1_len;
    size_t t07_list2_len;
    size_t t08_foot1_len;
} ngx_fancyindex_template_t;

#define NFI_TEMPLATE_FIELDS(p)                                               \
    p##_t01_head1, p##_t02_head2, p##_t03_head3, p##_t04_body1,              \
    p##_t05_body2, p##_t06_list1, p##_t07_list2, p##_t08_foot1,              \
    sizeof(p##_t01_head1) - 1, sizeof(p##_t02_head2) - 1,                    \
    sizeof(p##_t03_head3) - 1, sizeof(p##_t04_body1) - 1,                    \
    sizeof(p##_t05_body2) - 1, sizeof(p##_t06_list1) - 1,                    \
    sizeof(p##_t07_list2) - 1, sizeof(p##_t08_foot1) - 1

typedef struct {
    nfi_str_t code; /**< Language prefix used for Accept-Language matching. */
    const ngx_fancyindex_template_t *tpl;

    const nfi_str_t *short_weekday;
    const nfi_str_t *long_weekday;
    const nfi_str_t *short_month;
    const nfi_str_t *long_month;

    size_t short_weekday_max;
    size_t long_weekday_max;
    size_t short_month_max;
    size_t long_month_max;

    nfi_str_t am;
    nfi_str_t pm;
    nfi_str_t am_lower;
    nfi_str_t pm_lower;

    nfi_str_t parent_dir;
} ngx_fancyindex_lang_t;

/*
 * List of available languages. Adding a language requires a new
 * i18n/<name>.lang file, one line here, and running i18n/gen_i18n.sh.
 */
#define NFI_LANGUAGES(X)     \
    X(en,    EN)             \
    X(zh_CN, ZH_CN)

#endif /* NFI_I18N_H */

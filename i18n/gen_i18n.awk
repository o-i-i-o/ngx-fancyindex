# Generate a C header from a translation source file.
#
# Usage: awk -v src=zh_CN.lang -f gen_i18n.awk zh_CN.lang > zh_CN.h
#
# The input format is a simple "key = value" list. Values that represent
# lists use "|" as separator.

BEGIN {
    FS = "="
}

function trim(s) {
    gsub(/\r/, "", s)
    gsub(/^[ \t]+/, "", s)
    gsub(/[ \t]+$/, "", s)
    return s
}

function isident(s) {
    return s ~ /^[A-Za-z_][A-Za-z0-9_]*$/
}

function cstr(s) {
    gsub(/\\/, "\\\\", s)
    gsub(/"/, "\\\"", s)
    return s
}

function err(msg) {
    printf "%s: %s\n", FILENAME, msg > "/dev/stderr"
    exit 1
}

function need(key) {
    if (v[key] == "") {
        err("missing required key: " key)
    }
    return trim(v[key])
}

function emit_list(key, cname, expected,    n, a, i) {
    n = split(v[key], a, "|")
    if (n != expected) {
        err(key ": expected " expected " items, got " n)
    }
    printf "static const nfi_str_t %s[] = {\n", cname
    for (i = 1; i <= n; i++) {
        printf "    NFI_S(\"%s\")%s\n", cstr(trim(a[i])), (i < n ? "," : "")
    }
    printf "};\n\n"
}

function maxlen(key,    n, a, i, m) {
    n = split(v[key], a, "|")
    m = 0
    for (i = 1; i <= n; i++) {
        if (length(trim(a[i])) > m) {
            m = length(trim(a[i]))
        }
    }
    return m
}

/^[ \t]*#/ || /^[ \t]*$/ {
    next
}

{
    key = trim($1)
    value = trim(substr($0, index($0, "=") + 1))
    v[key] = value
}

END {
    name = need("name")
    code = need("code")
    header = need("template_header")
    prefix = need("template_prefix")
    am = need("am")
    pm = need("pm")
    am_lower = need("am_lower")
    pm_lower = need("pm_lower")
    parent_dir = need("parent_dir")

    if (!isident(name)) {
        err("name is not a valid C identifier: " name)
    }
    if (!isident(prefix)) {
        err("template_prefix is not a valid C identifier: " prefix)
    }

    printf "/* Automagically generated from %s, do not edit! */\n\n", FILENAME
    printf "#include \"%s\"\n\n", header

    emit_list("short_weekday", "nfi_" name "_short_weekday", 7)
    emit_list("long_weekday",  "nfi_" name "_long_weekday",  7)
    emit_list("short_month",   "nfi_" name "_short_month",  12)
    emit_list("long_month",    "nfi_" name "_long_month",   12)

    printf "static const ngx_fancyindex_template_t nfi_template_%s = {\n", name
    printf "    NFI_TEMPLATE_FIELDS(%s)\n", prefix
    printf "};\n\n"

    printf "static const ngx_fancyindex_lang_t nfi_lang_%s = {\n", name
    printf "    NFI_S(\"%s\"),\n", cstr(code)
    printf "    &nfi_template_%s,\n", name
    printf "    nfi_%s_short_weekday,\n", name
    printf "    nfi_%s_long_weekday,\n", name
    printf "    nfi_%s_short_month,\n", name
    printf "    nfi_%s_long_month,\n", name
    printf "    %d, %d, %d, %d,\n", \
           maxlen("short_weekday"), maxlen("long_weekday"), \
           maxlen("short_month"), maxlen("long_month")
    printf "    NFI_S(\"%s\"),\n", cstr(am)
    printf "    NFI_S(\"%s\"),\n", cstr(pm)
    printf "    NFI_S(\"%s\"),\n", cstr(am_lower)
    printf "    NFI_S(\"%s\"),\n", cstr(pm_lower)
    printf "    NFI_S(\"%s\")\n", cstr(parent_dir)
    printf "};\n"
}

# Fancy Index module Hacking HOW-TO

## How to modify the templates

The built-in English template is in the `template.html` file and the Chinese
one in `template_zh.html`. Note that comment markers are used to control how
the `template.awk` Awk script generates the C header which gets ultimately
included in the compiled object code. Comment markers have the
`<!-- var identifier -->` format. Here `identifier` must be a valid C
identifier. All the text following the marker until the next marker will be
flattened into a C string.

If the identifier is `NONE` (capitalized) the text from that marker up to
the next marker will be discarded.


## Regenerating the C headers

Each language has its own template header. The `prefix` given to the script
is used as the prefix of the generated C symbols:

    $ awk -f template.awk -v prefix=en template.html > template_en.h
    $ awk -f template.awk -v prefix=zh template_zh.html > template_zh.h

You will need Awk. I hope any decent implementation will do, but the GNU one
is known to work flawlessly.

If your copy of `awk` is not the GNU implementation, you will need to
install it and use `gawk` instead in the command lines above.

This includes macOS where the current built-in `awk` (currently version
20070501 at time of testing on 10.13.6) doesn't apply correctly and causes
characters to be omitted from the output. `gawk` can be installed with a
package manager such as [Homebrew](https://brew.sh) or
[MacPorts](https://ports.macports.org/port/gawk).


## Translations

The strings used by the built-in templates and the names of weekdays, months
and the AM/PM markers live in the `i18n/*.lang` files. Each file is a simple
`key = value` list, and values that represent lists use `|` as separator. The
C headers (`i18n/*.h`) are generated from them and checked in:

    $ sh i18n/gen_i18n.sh

The `config` script runs the generator when Nginx is configured, but editing
a `.lang` file and running `make` alone does not regenerate the headers: run
`./configure` again or execute the command above. The
`t/i18n-06-generator.test` test fails when the checked-in headers are out of
date.

To add a language `xx`:

1. Copy `i18n/en.lang` to `i18n/xx.lang` and translate the values. `name` and
   `template_prefix` must be valid C identifiers. If the template labels need
   translation, add `template_xx.html`, generate `template_xx.h` as described
   above, and point `template_header` to it.
2. Add `X(xx, XX)` to `NFI_LANGUAGES` in `i18n/nfi_i18n.h`.
3. Include `i18n/xx.h` from `ngx_http_fancyindex_module.c`.
4. Run `sh i18n/gen_i18n.sh` and rebuild.

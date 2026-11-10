#!/bin/sh
# Regenerate the C headers from the *.lang translation sources.

set -e

dir=$(dirname "$0")
cd "$dir"

found=0

for f in *.lang; do
    if [ ! -f "$f" ]; then
        continue
    fi

    out="${f%.lang}.h"
    LC_ALL=C awk -f gen_i18n.awk "$f" > "$out"
    echo "generated ${dir}/${out}"
    found=1
done

if [ "$found" -eq 0 ]; then
    echo "gen_i18n.sh: no .lang files found in $(pwd)" >&2
    exit 1
fi

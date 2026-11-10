#!/bin/sh
# Regenerate the C headers from the *.lang translation sources.

set -e
cd "$(dirname "$0")"

for f in *.lang; do
    out="${f%.lang}.h"
    LC_ALL=C awk -f gen_i18n.awk "$f" > "$out"
    echo "generated i18n/$out"
done

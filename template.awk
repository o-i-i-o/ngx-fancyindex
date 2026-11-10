#! /usr/bin/awk -f
#
# Copyright © Adrian Perez <aperez@igalia.com>
#
# Converts an HTML template into a C header suitable for inclusion.
# Take a look at the HACKING.md file to know how to use it :-)
#
# This code is placed in the public domain.

BEGIN {
	varname = 0;
	print "/* Automagically generated, do not edit! */"
	vars_count = 0;
	if (prefix == "") {
		macro = "NFI_TEMPLATE_SIZE";
	} else {
		macro = "NFI_" toupper(prefix) "_TEMPLATE_SIZE";
	}
}

/^<!--[[:space:]]*var[[:space:]]+[^[:space:]]+[[:space:]]*-->$/ {
	if (varname) print ";";
	if ($3 == "NONE") {
		varname = 0;
		next;
	}
	varname = $3;
	symbol = (prefix == "") ? varname : prefix "_" varname;
	vars[vars_count++] = symbol;
	print "static const u_char " symbol "[] = \"\"";
	next;
}

/^$/ {
	if (!varname) next;
	print "\"\\n\"";
	next;
}

{
	if (!varname) next;
	# Order matters
	gsub(/[\t\v\n\r\f]+/, "");
	gsub(/\\/, "\\\\");
	gsub(/"/, "\\\"");
	print "\"" $0 "\""
}


END {
	if (varname) print ";";
	print "#define " macro " (0 \\";
	for (var in vars) {
		print "\t+ nfi_sizeof_ssz(" vars[var] ") \\";
	}
	print "\t)"
}


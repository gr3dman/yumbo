#!/bin/sh

RESULT=0

function green {
	echo "[32m$*[0m"
}

function red {
	echo "[7;31m$*[0m"
}

for IN in *.in;
do
	[[ -f "$IN" ]] || ( echo "no tests" && continue )

	OUT=$( basename -s.in "$IN" ).out
	[[ -f "$OUT" ]] || continue

	printf "$IN... "
	TMP=$( mktemp -t meml )
	../meml < "$IN" > "$TMP" 2>&1

	if diff -B "$OUT" "$TMP";
	then
		green OK
	else
		red BAD
		RESULT=1
	fi
done

exit $RESULT

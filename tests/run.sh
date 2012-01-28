#!/bin/sh

RESULT=0

green () {
	echo "[32m$*[0m"
}

red () {
	echo "[7;31m$*[0m"
}

for IN in basic-*.in;
do
	[ -f "$IN" ] || ( echo "no tests" && continue )

	OUT=$( basename -s.in "$IN" ).out
	[ -f "$OUT" ] || continue

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

for IN in fail-*.in;
do
	[ -f "$IN" ] || (echo "no tests" && continue )

	printf "$IN... "
	if ../meml < "$IN" > /dev/null 2>&1;
	then
		red BAD
		RESULT=1
	else
		green OK
	fi
done

exit $RESULT

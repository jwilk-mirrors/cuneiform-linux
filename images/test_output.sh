#!/bin/sh

# Does not work on windows.

# Input file paths must be absolute.

infile=$1
truthfile=${infile}.txt
tempfile=`mktemp /tmp/cftest.XXXXXXXX`

export CF_DATADIR=../../datafiles

../cuneiform -o $tempfile "$@"
diff $tempfile $truthfile > /dev/null 2> /dev/null
result=$?
rm $tempfile
exit $result

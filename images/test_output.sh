#!/bin/sh

# Does not work on windows.

infile=$1
truthfile=${infile}.txt
tempfile=`mktemp /tmp/cftest.XXXXXXXX`

#echo `pwd` 
echo "$@" > ~/test.out
export CF_DATADIR=../../datafiles

../cuneiform -o $tempfile "$@"
diff $tempfile $truthfile > /dev/null 2> /dev/null
result=$?
rm $tempfile
exit $result

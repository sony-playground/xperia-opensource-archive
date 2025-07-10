#!/bin/sh

# $1 template manifest (old xfl manifest)
# $2 source manifest (new Android manifest)

head -5 $2
PROJ=$(grep "project name" $1 | cut -d' ' -f4)
for i in ${PROJ[*]}
do
		grep $i $2
done
echo "</manifest>"

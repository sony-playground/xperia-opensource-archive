#!/bin/bash
. ../../core/init.sh

out=`cat $HOST_TMP_DIR/$1`
if [ ${#out} -lt 8 ]; then
		echo "Invalid size" ${#out}", should be 8 or more"
		exit 1
fi
if [ ${out:0:4} != "OKAY" ]; then
		echo "OKAY is missing"
		exit 1
fi
exit 0

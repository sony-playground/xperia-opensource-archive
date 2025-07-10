#!/bin/bash
. ../../core/init.sh

out=`cat $HOST_TMP_DIR/$1`
if [ ${out:0:4} != "OKAY" ]; then
		echo "OKAY is missing"
		exit 1
fi
echo "${out:4}"
exit 0

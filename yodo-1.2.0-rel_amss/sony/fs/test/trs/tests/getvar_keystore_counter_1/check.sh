#!/bin/bash

. ../../core/init.sh

out=`cat $HOST_TMP_DIR/$1`
if [ ${out:0:4} != "OKAY" ]; then
		echo -e "${RED}OKAY is missing${NC}"
		exit 1
fi
echo -e "${GREEN}KEYSTORE COUNTER" ${out:4}"${NC}"
exit 0

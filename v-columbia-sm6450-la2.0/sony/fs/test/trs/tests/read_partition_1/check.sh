#!/bin/bash
. ../common.sh

PART=/dev/block/bootdevice/by-name/frp

exec_remote dd of=$DEV_TMP_DIR/_bin if=$PART
pull_remote $PART $HOST_TMP_DIR/_bin
diff $HOST_TMP_DIR/$1 $HOST_TMP_DIR/_bin
if [ $? -ne 0 ]; then
		echo -e "${RED}READ FAIL! Files differ${NC}"
		exit 1
fi

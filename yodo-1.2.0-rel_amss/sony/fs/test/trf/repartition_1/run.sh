#!/bin/bash

source ../common.sh
source ../authenticate.sh

DBN=/dev/block/bootdevice/by-name
RETVAL=0

stop () {
	adb shell "stop loader-trf"
	exit $RETVAL
}

if ! authenticate; then
	RETVAL=1
	stop
fi

if [ "$STORAGE" == "emmc" ]; then
	echo "EMMC - not supported"
	exit 1
else
	echo "UFS"
	PART=/dev/block/sdf
	BLOCK_SIZE=4096
	GPT_SIZE=6
	backup_1=frp
	backup_2=keystore
	SGPT_OFFSET_5=$((`adb shell cat /sys/block/sdf/size`/8 - 6))

	# send test gpt
	adb push ufs_gpt_5 /ufs_gpt_5
fi

if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# backup original gpt
adb shell dd if=$PART of=/pbak_f bs=$BLOCK_SIZE count=$GPT_SIZE
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi
adb shell dd if=$PART of=/pbak_f2 bs=$BLOCK_SIZE\
		count=$GPT_SIZE skip=$SGPT_OFFSET_5

# flash test gpt
adb shell dd if=/ufs_gpt_5 of=$PART bs=$BLOCK_SIZE count=$GPT_SIZE

# update partitions and wait for the update to take effect before backup
adb shell toybox partprobe $PART
sleep 1s

# backup partitions to be erased
adb pull $DBN/$backup_1 $HOST_TMP_DIR/$backup_1
adb pull $DBN/$backup_2 $HOST_TMP_DIR/$backup_2

# Push command and run loader
adb push fbcmd /fbcmd

# Restart loader, returns when device is ready
if ! restart_loader; then
	RETVAL=1
	stop
fi
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# restore & clean
adb shell rm ufs_gpt_5
adb shell dd if=/pbak_f of=$PART bs=$BLOCK_SIZE count=$GPT_SIZE
adb shell dd if=/pbak_f2 of=$PART bs=$BLOCK_SIZE\
		count=$GPT_SIZE seek=$SGPT_OFFSET_5
adb shell rm pbak_f pbak_f2

# Re-read partition table & restore partitions
adb shell toybox partprobe $PART
adb push $HOST_TMP_DIR/$backup_1 .
adb push $HOST_TMP_DIR/$backup_2 .
adb shell dd if=/$backup_1 of=$DBN/$backup_1
adb shell dd if=/$backup_2 of=$DBN/$backup_2
adb shell rm $backup_1 $backup_2

# analyze and verify output
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -ne 0 ]; then
	RETVAL=1
fi

# stop loader-trf
stop

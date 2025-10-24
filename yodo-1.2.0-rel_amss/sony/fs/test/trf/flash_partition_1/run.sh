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
	echo "EMMC"
	PART=/dev/block/mmcblk0
	BLOCK_SIZE=512
	GPT_SIZE=34
	SGPT_OFFSET=61071326
	backup_1=aboot
	backup_2=abootbak
	fbcmd=fbcmd_emmc
	fbcmd_out_ref=fbcmd_out_ref_emmc
	# send test gpt
	adb push gpt_0 /gpt_0
	adb push gpt_0_alt /gpt_0_alt

else
	echo "UFS"
	PART=/dev/block/sda
	BLOCK_SIZE=4096
	GPT_SIZE=6
	backup_1=frp
	backup_2=keystore
	fbcmd=fbcmd_ufs
	fbcmd_out_ref=fbcmd_out_ref_ufs

	SGPT_OFFSET_0=$((`adb shell cat /sys/block/sda/size`/8 - 6))

	# send test gpt
	adb push ufs_gpt_0 /ufs_gpt_0
	adb push ufs_gpt_0_alt /gpt_0_alt
	adb push ufs_gpt_0_alt_bak /gpt_0_alt_bak
fi

# INIT TEST
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

if [ "$STORAGE" == "emmc" ]; then
	# backup original gpt
	adb shell dd if=$PART of=/part_bak bs=$BLOCK_SIZE count=$GPT_SIZE
	adb shell dd if=$PART of=/part2_bak bs=$BLOCK_SIZE count=$GPT_SIZE\
			skip=$SGPT_OFFSET

	# flash one of the test gpt
	adb shell dd if=/gpt_0_alt of=$PART bs=$BLOCK_SIZE count=$GPT_SIZE

	# update partitions
	adb shell toybox partprobe $PART
else
	# backup original gpt
	adb shell dd if=/dev/block/sda of=/pbak_a bs=$BLOCK_SIZE count=$GPT_SIZE
	adb shell dd if=/dev/block/sda of=/pbak_a2 bs=$BLOCK_SIZE\
			count=$GPT_SIZE skip=$SGPT_OFFSET_0

	# flash all test gpt:s
	adb shell dd if=/gpt_0_alt of=/dev/block/sda bs=$BLOCK_SIZE\
			count=$GPT_SIZE
	adb shell dd if=/gpt_0_alt_bak of=/dev/block/sda bs=$BLOCK_SIZE\
			count=$GPT_SIZE seek=$SGPT_OFFSET_0

	# update partitions with some delay for the changes to take effect
	adb shell toybox partprobe /dev/block/sda
	sleep 2s
fi

# backup partitions to be erased
adb pull $DBN/$backup_1 $HOST_TMP_DIR/$backup_1
adb pull $DBN/$backup_2 $HOST_TMP_DIR/$backup_2

# Push command file
adb push $fbcmd /fbcmd
echo "restart loader"
# Restart loader, returns when device is ready
if ! restart_loader; then
	RETVAL=1
	stop
fi

# VERIFY & RESTORE
# check erase
adb pull $DBN/bboot $HOST_TMP_DIR/bboot
adb pull $DBN/bbootbak $HOST_TMP_DIR/bbootbak

tmp=$(tr -dc '\000' <$HOST_TMP_DIR/bboot | cmp - $HOST_TMP_DIR/bboot)
if [[ $tmp = "-"* ]] || [[ $tmp = "c"* ]]; then
	echo "ERASE bboot FAIL!"
	RETVAL=1
fi

tmp=$(tr -dc '\000' <$HOST_TMP_DIR/bbootbak | cmp - $HOST_TMP_DIR/bbootbak)
if [[ $tmp = "-"* ]] || [[ $tmp = "c"* ]]; then
	echo "ERASE bbootbak FAIL!"
	RETVAL=1
fi

if [ "$STORAGE" == "emmc" ]; then
	# restore & clean
	adb shell rm gpt_0 gpt_0_alt
	adb shell dd if=$PART of=/pres_a bs=$BLOCK_SIZE count=$GPT_SIZE
	adb shell dd if=/part_bak of=$PART bs=$BLOCK_SIZE count=$GPT_SIZE
	adb shell dd if=/part2_bak of=$PART bs=$BLOCK_SIZE count=$GPT_SIZE\
			seek=$SGPT_OFFSET
	adb shell rm part_bak part2_bak

	# Re-read partition table & restore partitions
	adb shell toybox partprobe $PART
	adb push $HOST_TMP_DIR/$backup_1 .
	adb push $HOST_TMP_DIR/$backup_2 .
	adb shell dd if=/$backup_1 of=$DBN/$backup_1
	adb shell dd if=/$backup_2 of=$DBN/$backup_2
	adb shell rm $backup_1 $backup_2
else
	# restore & clean
	adb shell rm gpt_0_alt gpt_0_alt_bak ufs_gpt_0
	adb shell dd if=/dev/block/sda of=/pres_a bs=$BLOCK_SIZE count=$GPT_SIZE
	adb shell dd if=/pbak_a of=/dev/block/sda bs=$BLOCK_SIZE count=$GPT_SIZE
	adb shell dd if=/pbak_a2 of=/dev/block/sda bs=$BLOCK_SIZE\
			count=$GPT_SIZE seek=$SGPT_OFFSET_0
	adb shell rm pbak_a pbak_a2

	# Re-read partition table & restore partitions
	adb shell toybox partprobe /dev/block/sda
	adb push $HOST_TMP_DIR/$backup_1 .
	adb push $HOST_TMP_DIR/$backup_2 .
	adb shell dd if=/$backup_1 of=$DBN/$backup_1
	adb shell dd if=/$backup_2 of=$DBN/$backup_2
	adb shell rm $backup_1 $backup_2
fi

# Check result
adb pull /pres_a $HOST_TMP_DIR/pres_a
adb shell rm pres_a

if [ "$STORAGE" == "emmc" ]; then
	diff $HOST_TMP_DIR/pres_a gpt_0
else
	diff $HOST_TMP_DIR/pres_a ufs_gpt_0
fi
if [ $? -ne 0 ]; then
	echo "return output invalid"
	RETVAL=1
fi

# Extract loader result and analyze
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
OUT=`cat $HOST_TMP_DIR/fbcmd_out`
if [ ${OUT:${#OUT}-4:4} != "OKAY" ]; then
	echo "OKAY is missing: "$OUT
	RETVAL=1
fi

stop

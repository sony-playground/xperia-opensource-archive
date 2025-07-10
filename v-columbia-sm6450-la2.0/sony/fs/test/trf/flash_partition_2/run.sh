#!/bin/bash

source ../common.sh
source ../authenticate.sh

DBN=/dev/block/bootdevice/by-name
RETVAL=0
BLOCK_SIZE=4096
GPT_SIZE=6
backup_1=tz_backup
backup_2=tzbak_backup
SGPT_OFFSET=$((`adb shell cat /sys/block/sde/size`/8 - 6))

stop () {
	adb shell "stop loader-trf"
	exit $RETVAL
}

if ! authenticate; then
	RETVAL=1
	stop
fi

echo "UFS"
# send test gpt
adb push ufs_gpt_4_swap /ufs_gpt_4_swap

# backup original gpt
adb shell dd if=/dev/block/sde of=/pbak_e bs=$BLOCK_SIZE count=$GPT_SIZE
adb shell dd if=/dev/block/sde of=/pbak_e2 bs=$BLOCK_SIZE\
		count=$GPT_SIZE skip=$SGPT_OFFSET

# backup partitions to be swaped
adb pull $DBN/tz $HOST_TMP_DIR/$backup_1
adb pull $DBN/tzbak $HOST_TMP_DIR/$backup_2

# create some random data to make sure both partitions are not empty
adb shell dd if=/dev/urandom of=$DBN/tz bs=$BLOCK_SIZE count=512
adb shell dd if=$DBN/tz of=$DBN/tzbak


# Re-read partition table & restore partitions
adb shell toybox partprobe /dev/block/sde
sleep 2s

# Push command file
adb push fbcmd /fbcmd
echo "restart loader, return when device is ready"
if ! restart_loader; then
	RETVAL=1
	stop
fi

# VERIFY & RESTORE
adb pull $DBN/tz $HOST_TMP_DIR/tz
adb pull $DBN/tzbak $HOST_TMP_DIR/tzbak

# check erase
tmp=$(tr -dc '\000' <$HOST_TMP_DIR/tz | cmp - $HOST_TMP_DIR/tz)
if [[ $tmp = "-"* ]] || [[ $tmp = "c"* ]]; then
	echo "success - tz is not erased"
else
	echo "fail - tz partition has been erased"
	RETVAL=1
fi

tmp=$(tr -dc '\000' <$HOST_TMP_DIR/tzbak | cmp - $HOST_TMP_DIR/tzbak)
if [[ $tmp = "-"* ]] || [[ $tmp = "c"* ]]; then
	echo "success - tzbak is not erased"
else
	echo "fail - tzbak partition has been erased"
	RETVAL=1
fi

# restore & clean
adb shell dd if=/dev/block/sde of=/pres_e bs=$BLOCK_SIZE count=$GPT_SIZE
adb shell dd if=/pbak_e of=/dev/block/sde bs=$BLOCK_SIZE count=$GPT_SIZE
adb shell dd if=/pbak_e2 of=/dev/block/sde bs=$BLOCK_SIZE\
		count=$GPT_SIZE seek=$SGPT_OFFSET
adb shell rm ufs_gpt_4_swap pbak_e pbak_e2

# Re-read partition table & restore partitions
adb shell toybox partprobe /dev/block/sde
adb push $HOST_TMP_DIR/$backup_1 /
adb push $HOST_TMP_DIR/$backup_2 /
adb shell dd if=/$backup_1 of=$DBN/$backup_1
adb shell dd if=/$backup_2 of=$DBN/$backup_2
adb shell rm $backup_1 $backup_2

# Check result
adb pull /pres_e $HOST_TMP_DIR/pres_e
adb shell rm pres_e

diff $HOST_TMP_DIR/pres_e ufs_gpt_4_swap

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

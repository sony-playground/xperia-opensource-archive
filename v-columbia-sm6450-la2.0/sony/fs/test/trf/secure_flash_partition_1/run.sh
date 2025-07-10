#!/bin/bash

source ../common.sh

DBN=/dev/block/bootdevice/by-name

if [ "$STORAGE" == "emmc" ]; then
	echo "EMMC - not supported"
	exit 1

else
	echo "UFS"
	PART=/dev/block/sda
	BLOCK_SIZE=4096
	GPT_SIZE=6
	backup_1=frp
	backup_2=keystore
	fbcmd=fbcmd_ufs
	fbcmd_out_ref=fbcmd_out_ref_ufs

	SGPT_OFFSET_5=$((`adb shell cat /sys/block/sdf/size`/8 - 6))

	# send test gpt
	adb push ufs_gpt_5 /gpt_5
fi

# INIT TEST
if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi


# backup original gpt
adb shell dd if=/dev/block/sdf of=/pbak_f bs=$BLOCK_SIZE count=$GPT_SIZE

adb shell dd if=/dev/block/sdf of=/pbak_f2 bs=$BLOCK_SIZE\
		count=$GPT_SIZE skip=$SGPT_OFFSET_5
# flash all test gpt:s
adb shell dd if=/gpt_5 of=/dev/block/sdf bs=$BLOCK_SIZE count=$GPT_SIZE

# update partitions
adb shell toybox partprobe /dev/block/sdf

# backup partitions to be erased
adb pull $DBN/$backup_1 $HOST_TMP_DIR/$backup_1
adb pull $DBN/$backup_2 $HOST_TMP_DIR/$backup_2

# transfer signature
adb push ufs_gpt_5_X-FLASH-ALL-5ADA.cms /signature1

# RUN LOADER
adb push $fbcmd /fbcmd
adb shell loader -s$STORAGE -g/fbcmd -llog.log
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# restore & clean
adb shell rm gpt_5
adb shell dd if=/pbak_f of=/dev/block/sdf bs=$BLOCK_SIZE count=$GPT_SIZE
adb shell dd if=/pbak_f2 of=/dev/block/sdf bs=$BLOCK_SIZE\
		count=$GPT_SIZE seek=$SGPT_OFFSET_5
adb shell rm pbak_f pbak_f2

# Re-read partition table & restore partitions
adb shell toybox partprobe /dev/block/sdf
adb push $HOST_TMP_DIR/$backup_1 .
adb push $HOST_TMP_DIR/$backup_2 .
adb shell dd if=/$backup_1 of=$DBN/$backup_1
adb shell dd if=/$backup_2 of=$DBN/$backup_2
adb shell rm $backup_1 $backup_2

#cat $HOST_TMP_DIR/fbcmd_out
diff $HOST_TMP_DIR/fbcmd_out $fbcmd_out_ref
if [ $? -eq 0 ]; then
		exit $RETVAL
else
		exit 1
fi

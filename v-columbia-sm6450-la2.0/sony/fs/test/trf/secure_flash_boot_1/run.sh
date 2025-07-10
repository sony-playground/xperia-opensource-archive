#!/bin/bash

source ../common.sh

PART=/dev/block/bootdevice/by-name/boot
RETVAL=0

generate_cms() {
	# detect type of device and set corresponding certificate
	get_plf_type
	set_cert

	echo "Signing the-msg and extracting ..."
	signatory -t CMS -c $CERT \
		-o $HOST_TMP_DIR/cms_gzip \
		--cms-gpt-name boot \
		the-msg.txt

	if [ $? -ne 0 ]; then
		echo "Generating CMS failed"
		exit 1
	fi

	# extact the cms and prepare it to be pushed to the device
	tar -xvf $HOST_TMP_DIR/cms_gzip -C $HOST_TMP_DIR/
	mv $HOST_TMP_DIR/boot.cms $HOST_TMP_DIR/the-signed-msg-cms
}

# back up
adb shell dd if=$PART of=/restore bs=4096 count=1
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# generate cms and push to the device
generate_cms
adb push $HOST_TMP_DIR/the-signed-msg-cms /signature1
adb push the-msg.txt /dump1

# run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# restore
adb shell dd if=$PART of=/dump2 bs=34 count=1
adb shell dd if=/restore of=$PART bs=4096 count=1

# check if flashing succeed
adb pull dump2 $HOST_TMP_DIR/dump2
diff the-msg.txt $HOST_TMP_DIR/dump2
if [ $? -eq 0 ]; then
	echo "FLASH OK!"
	RETVAL=0
else
	echo "FLASH FAIL!"
	RETVAL=1
fi

# clean up
adb shell rm /restore /signature1 /dump1 /dump2

# check result
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ]; then
	exit $RETVAL
else
	exit 1
fi

#!/bin/bash

source ../common.sh
source ../authenticate.sh

RETVAL=0

stop () {
	adb shell "stop loader-trf"
	exit $RETVAL
}

enable_UART_log() {
	echo "Enable serial console logs"
	echo "c download:00000001" > $HOST_TMP_DIR/fbcmd
	echo "b onebyte" >> $HOST_TMP_DIR/fbcmd
	echo "c Write-TA:2:2473" >> $HOST_TMP_DIR/fbcmd
	echo "1" > $HOST_TMP_DIR/onebyte
	adb push $HOST_TMP_DIR/onebyte /
	adb push $HOST_TMP_DIR/fbcmd /
	adb shell loader -s$STORAGE -g/fbcmd
}

reboot_bootloader() {
	adb reboot-bootloader
	echo "Waiting for reboot, this might take some time..."
	adb wait-for-device
}

# Authenticate
if ! authenticate; then
	echo "Authentication failed"
	RETVAL=1
	stop
fi

prepare_ta_ref

# Backup TA
adb shell dd if=/dev/block/bootdevice/by-name/TA of=/TA_bak bs=512
adb pull /TA_bak $HOST_TMP_DIR/TA_bak
# Backup devinfo to be used in restoring the bootloader to locked state
adb shell dd if=/dev/block/bootdevice/by-name/devinfo of=/devinfo_bak
adb pull /devinfo_bak $HOST_TMP_DIR/devinfo_bak
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# Push reference TA to device
adb push $HOST_TMP_DIR/TA_ref /
if [ $? -ne 0 ]; then
	echo "Unable to push TA_ref to device"
	exit 1
fi

# Write reference TA
adb shell dd if=/TA_ref of=/dev/block/bootdevice/by-name/TA bs=512

# Push command file and prepare zerobyte of data to be written to TA66671
adb push fbcmd /
adb shell touch zerobyte

echo "Restart loader, returns when device is ready"
if ! restart_loader; then
	RETVAL=1
fi

# Enable UART log before restarting without it
enable_UART_log

# Reboot to bootloader for oem unlock to take effect
reboot_bootloader

# Unlocking an unlocked bootloader
echo "Trying to unlock the bootloader after it has already been unlocked"
echo "c oem unlock 2A103D267E1808BA" > $HOST_TMP_DIR/fbcmd
adb push $HOST_TMP_DIR/fbcmd /
adb shell loader -s$STORAGE -g/fbcmd

# Extract result for analysis
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_oem_unlock_out

# Restore original TA
adb push $HOST_TMP_DIR/TA_bak /TA_bak
adb shell dd if=/TA_bak of=/dev/block/bootdevice/by-name/TA bs=512

# Restore devinfo with the previous backed up locked state
adb push $HOST_TMP_DIR/devinfo_bak /devinfo_bak
adb shell dd if=/devinfo_bak of=/dev/block/bootdevice/by-name/devinfo

# Reboot to bootloader to lock the bootloader back
echo "Locking back the bootloader"
reboot_bootloader

# Compare oem unlock output with expected output reference
diff $HOST_TMP_DIR/fbcmd_oem_unlock_out fbcmd_out_ref
if [ $? -eq 0 ]; then
	stop
else
	echo "Unexpected response:"
	cat $HOST_TMP_DIR/fbcmd_out
	# Print newline
	echo ""
	RETVAL=1
fi

stop

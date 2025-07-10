#!/system/bin/sh
# Copyright (c) 2021 Sony Corporation

slot_suffix=`getprop ro.boot.slot_suffix`
systemdumper=/system/bin/system_dumper
reboot=/system/bin/reboot

if grep -w 'oembootloader.warmboot=0xc0dedead' /proc/cmdline || \
   grep -w 'oembootloader.warmboot=0xabadbabe' /proc/cmdline; then
	setprop sys.usb.configfs 2
	mkdir -p /persist
	mkdir -p /rdlog
	chmod 0775 /rdlog
	mkdir -p /rdlog/crashdump
	chmod 0770 /rdlog/crashdump
	chown -h root.system /rdlog/crashdump
	ln -s /rdlog/crashdump /data/crashdump
	mkdir -p /sdcard1
	chmod 0775 /sdcard1
	mkdir -p /mnt/tmp

	#set the module parameter,rd_recovery for qcom-reboot-reason
	#to identify the ramdump kernel
	echo 1 > /sys/module/qcom_reboot_reason/parameters/rd_recovery
	mount -t tmpfs tmpfs /mnt/tmp
	mount -t pstore none /sys/fs/pstore
	mount -t debugfs none /sys/kernel/debug
	mkdir -p /mnt/oem
	if [ "$slot_suffix" == "_a" ]; then
		mount -t ext4 -o ro /dev/block/bootdevice/by-name/oem_a /mnt/oem
	elif [ "$slot_suffix" == "_b" ]; then
		mount -t ext4 -o ro /dev/block/bootdevice/by-name/oem_b /mnt/oem
	fi

	$systemdumper
	$reboot "rd_err"
else
	exit 0
fi

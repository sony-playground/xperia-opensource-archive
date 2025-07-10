#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m'
HOST_TMP_DIR=/tmp/fcs_trf
OUT_REF=fbcmd_out_ref
SCRIPTS_DIR=../../../scripts
COMMON_DIR=../../common
YOSHINO_PLF=2005E0E1
TAMA_PLF=0008B0E1
NILE_PLF=000AC0E1
PLATFORM=$YOSHINO_PLF
YOSHINO_CERT=X-FLASH-ALL-5ADA
TAMA_CERT=X-FLASH-ALL-AE08
NILE_CERT=X-FLASH-ALL-9B8D
CERT=$YOSHINO_CERT

contains() {
		string="$1"
		substring="$2"
		if test "${string#*$substring}" != "$string"
		then
			return 0    # $substring is in $string
		else
			return 1    # $substring is not in $string
		fi
}

prepare_ta_ref() {
		# Cleanup
		rm $HOST_TMP_DIR/TA_ref > /dev/null 2>&1
		rm -r $HOST_TMP_DIR/TA > /dev/null 2>&1
		mkdir $HOST_TMP_DIR/TA
		#Unpack ref TA
		$SCRIPTS_DIR/ta_parser\
			-a$HOST_TMP_DIR/TA\
			../../common/TA_ref > /dev/null
		# get devid
		adb push $COMMON_DIR/fbcmd_devid /
		adb shell loader -s$STORAGE -g/fbcmd_devid
		adb pull /fbcmd_devid_out $HOST_TMP_DIR/fbcmd_devid_out
		python $COMMON_DIR/hwc_dev_bind.py\
			$HOST_TMP_DIR/fbcmd_devid_out\
			$HOST_TMP_DIR/TA/2-2003.bin\
			$HOST_TMP_DIR/2-2003-unsigned.bin
		signatory -t SIN -c S1-HWCONF-TEST-B316-0001-HWCONF\
			-o $HOST_TMP_DIR/TA/2-2003.bin\
			$HOST_TMP_DIR/2-2003-unsigned.bin
		#Pack ref TA
		$SCRIPTS_DIR/ta_parser\
			-c$HOST_TMP_DIR/TA/\
			-o$HOST_TMP_DIR/TA_ref > /dev/null
		rm $HOST_TMP_DIR/2-2003-unsigned.bin
		rm -r $HOST_TMP_DIR/TA
}

prepare_replace_hwc_ta_ref() {
		REPLACE_HWC="$1"
		# Cleanup
		rm $HOST_TMP_DIR/TA_ref > /dev/null 2>&1
		rm -r $HOST_TMP_DIR/TA > /dev/null 2>&1
		mkdir $HOST_TMP_DIR/TA
		#Unpack ref TA
		$SCRIPTS_DIR/ta_parser\
			-a$HOST_TMP_DIR/TA\
			../../common/TA_ref > /dev/null
		#Replace HWConfig
		cp $REPLACE_HWC $HOST_TMP_DIR/TA/2-2003.bin
		# get devid
		adb push $COMMON_DIR/fbcmd_devid /
		adb shell loader -s$STORAGE -g/fbcmd_devid
		adb pull /fbcmd_devid_out $HOST_TMP_DIR/fbcmd_devid_out
		python $COMMON_DIR/hwc_dev_bind.py\
			$HOST_TMP_DIR/fbcmd_devid_out\
			$HOST_TMP_DIR/TA/2-2003.bin\
			$HOST_TMP_DIR/2-2003-unsigned.bin
		signatory -t SIN -c S1-HWCONF-TEST-B316-0001-HWCONF\
			-o $HOST_TMP_DIR/TA/2-2003.bin\
			$HOST_TMP_DIR/2-2003-unsigned.bin
		#Pack ref TA
		$SCRIPTS_DIR/ta_parser\
			-c$HOST_TMP_DIR/TA/\
			-o$HOST_TMP_DIR/TA_ref > /dev/null
		rm $HOST_TMP_DIR/2-2003-unsigned.bin
		rm -r $HOST_TMP_DIR/TA
}

set_storage_type() {
		LOCAL_DIR=`pwd`

		#Check whether storage is ufs
		cd ./getvar_ufs-info_1
		./run.sh
		if [ $? -eq 0 ]; then
				STORAGE='ufs'
		else
				STORAGE='emmc'
		fi

		cd $LOCAL_DIR
}

get_plf_type() {
	# get Platform-id from device
	echo "c getvar:Platform-id" > $HOST_TMP_DIR/fbcmd_plf_id
	adb push $HOST_TMP_DIR/fbcmd_plf_id /
	adb shell loader -s$STORAGE -g/fbcmd_plf_id
	adb pull /fbcmd_plf_id_out $HOST_TMP_DIR/fbcmd_plf_id_out
	adb shell rm /fbcmd_plf_id /fbcmd_plf_id_out
	out=`cat $HOST_TMP_DIR/fbcmd_plf_id_out`

	if [[ ${out:0:4} == "OKAY" ]]; then
		PLATFORM=${out:4}
	else
		echo "Getting Platform-id failed: $out"
		exit 1
	fi
}

set_cert() {
	# get the platform type to set the certificate accordingly
	get_plf_type

	# set appropriate certificate
	if [[ $PLATFORM == $YOSHINO_PLF ]]; then
		CERT=$YOSHINO_CERT
		echo "Device: YOSHINO with Platform-id: $PLATFORM"
	elif [[ $PLATFORM == $TAMA_PLF ]]; then
		CERT=$TAMA_CERT
		echo "Device: TAMA with Platform-id: $PLATFORM"
	elif [[ $PLATFORM == $NILE_PLF ]]; then
		CERT=$NILE_CERT
		echo "Device: NILE with Platform-id: $PLATFORM"
	else
		echo "Unknown Platform: $PLATFORM"
		exit 1
	fi
}

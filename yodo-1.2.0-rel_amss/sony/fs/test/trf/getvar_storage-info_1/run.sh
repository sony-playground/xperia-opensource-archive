#!/bin/bash

source ../common.sh

cd ../getvar_ufs-info_1
./run.sh
if [ $? -ne 0 ]; then
		echo "Storage is not UFS. Trying eMMC"
		cd ../getvar_emmc-info_1
		./run.sh
		if [ $? -ne 0 ]; then
				echo "Storage is neither UFS nor eMMC"
				exit 1
		fi
fi


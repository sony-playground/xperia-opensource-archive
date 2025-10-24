#!/bin/bash

#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 05/17/22   tmt     Handle DTBO renaming of DTS files
# 01/13/22   tmt     Update --include parameter to gendtb.py
# 12/20/21   tmt     Update command-line to gendtb.py
# 10/18/21   vk      Initial revision

# Some script constants
DTCPATH="/pkg/qct/software/boottools/"
CPPPATH="/pkg/qct/software/llvm/release/arm/14.0.0/bin/"

# All SoCs in 6.1.1 PW
SOC="Kailua"

usage()
{
	echo "PW Usage: $0 [-t <count of acceptable errors>]" 1>&2;
	echo "Engineer Usage: $0 [-s <SoC> limit check to specified chip]" 1>&2;
	exit 1;
}

echo "------------------------------------------------------------------------------"
echo "Checking for device tree warnings ..."
echo "------------------------------------------------------------------------------"

# Handle command-line arguments first
threshold=0
fail=0
aggregate=0

while getopts ":hs:t:" arg; do
	case $arg in
		h) usage ;;
		s) SOC=$OPTARG ;;
		t) threshold=$OPTARG ;;
	esac
done

# Setup test
rm -rf BuildDT
mkdir BuildDT
cp -rf Settings ./BuildDT
cd BuildDT/Settings
rm -rf dt_build*.log

# Run test on all requested SoCs (default is all SoCs in PW)
for soc in $SOC
do
	Log=dt_build_${soc}.log

	echo --------------------------------------------------------------------------------->>${Log}
	echo ${soc} >${Log}
	echo --------------------------------------------------------------------------------->>${Log}
	mkdir ${soc}_
	lsoc=`echo ${soc} | tr [:upper:] [:lower:]`

	./Tools/gendtb.py -c ${CPPPATH} -d ${DTCPATH} -f ${soc}/soc-${lsoc}-1.0.dts -o ${soc}_ -i "Include ${soc}/Include" 2>&1 | tee ${Log}

	cat ${Log} | grep Warning | wc -l >dt_build_warn_count.log

	echo ${soc}
	value=$(<dt_build_warn_count.log)
	echo "SoC $value"
	aggregate=`expr $aggregate + $value`
	echo "Total $aggregate"

done

	if [ "$aggregate" -gt "$threshold" ]; then
	  echo "----------------------------------------------------------------------------"
	  echo "[FAIL] Invalid device tree warning count $aggregate is more than $threshold for ${SOC}"
	  echo "[FAIL] Invalid device tree $aggregate is more than $threshold " >dt_check_fail.log
	  echo "----------------------------------------------------------------------------"
	  echo "Invalid device tree warnings list  ..."
	  echo "----------------------------------------------------------------------------"
	  fail=1
	else
	  echo "----------------------------------------------------------------------------"
	  echo "[PASS] Current invalid device tree warning value is $aggregate and threshold is $threshold for ${SOC}"
	fi
	echo "----------------------------------------------------------------------------"

# Check for generated .dtb files
for soc in ${SOC}
do
	lsoc=`echo ${soc} | tr [:upper:] [:lower:]`
	if [ ! -f ${soc}_/soc-${lsoc}-1.0.dtb ]; then
		echo "Failed to build ${soc} DTB outside tree !"
		fail=1
	fi
done

if [ $fail != 0 ];then
  echo Exit error
  exit -1
else
  echo Exit OK
  touch dt_check_pass.log
  exit 0
fi

exit 0

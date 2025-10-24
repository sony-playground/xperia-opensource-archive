#!/bin/bash

run_test() {
		echo "-------------------------"
		echo "BEGIN test" $1
		if [ ! -d $1 ]; then
				RETVAL=1
				echo -e "${RED}" $1 "test do not exist.${NC}"
				return
		fi
		cd $1
		./run.sh
		if [ $? -ne 0 ]; then
				echo -e "${RED}TEST" ${d%/} "FAILED!${NC}"
				RETVAL=1
				cd ..
				rm -rf $HOST_TMP_DIR/*
				echo "END test" $1
				failed_tests+=$1" "
				return
		else
				echo -e "${GREEN}TEST" ${d%/} "PASSED${NC}"
		fi
		cd ..
		rm -rf $HOST_TMP_DIR/*
		echo "END test" $1
}

RETVAL=0

# Make sure we source common.sh
source common.sh
if [ $? -ne 0 ]; then
	echo "You must run the test script from the trf folder"
	exit 1
fi
# And double check it was the right common.sh, meaning HOST_TMP_DIR is not empty
if [ -z $HOST_TMP_DIR ]; then
	echo "your HOST_TMP_DIR is not set"
	exit 1
fi

set_storage_type
export STORAGE

export blacklist=`cat blacklist.txt | tr '\n' ' '`

mkdir -p $HOST_TMP_DIR
if [ $# -eq 1 ]; then
		run_test ${1%/}
elif [ $# -eq 0 ]; then
		for d in */; do
				dir=${d%/}
				echo dir=$dir
				if ! contains " $blacklist " " $dir ";
				then
						run_test $dir
				else
						echo "Skipping test $dir"
				fi
		done
else
		echo "INVALID INPUT\n"
		echo "Valid inputs are no arguments or a single argument."
		echo "If no argument is provided, all testcases will be run"
		echo "A single test case can be run by providing the dir name"
		echo " as the only argument."
		RETVAL=1
fi

echo "-------------------------"
if [ $RETVAL -eq 0 ]; then
		echo -e "${GREEN}ALL TESTS OK${NC}"
else
		echo -e "${RED}FOLLOWING TEST(S) FAILED:${NC}"
		for f in ${failed_tests}; do
				echo $f
		done
fi
echo "-------------------------"

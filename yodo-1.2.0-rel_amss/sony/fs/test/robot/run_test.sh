# These variables depend on the environment
export CURRENT_DIR=$(pwd)
export XFL_WS=$HOME/Workspaces/$XFL_BRANCH
export XBOOT_WS=$HOME/Workspaces/$XBOOT_BRANCH
export EXEC_DIR=$HOME/robot-test
export TEST_DATA_DIR=$EXEC_DIR/test_data
export FSCONFIG_XML_FILE=$TEST_DATA_DIR/temp/util/data/fsconfig.xml
export PARTITIONS_DIR=$TEST_DATA_DIR/temp/img/partition

# Set ROBOT_DIR to local directory when developing the robot tests
if [ $DEV_TEST == true ]; then
export ROBOT_DIR=$CURRENT_DIR
else
export ROBOT_DIR=$XFL_WS/vendor/semc/fs/main/test/robot
fi

export XFL_FS_MAIN_DIR=$XFL_WS/vendor/semc/fs/main
export XBOOT_FS_MAIN_DIR=$XBOOT_WS/fcs/main
export TOPIC_BRANCH=test

# Other variables
export BUILD_TARGET=$TARGET-userdebug
if [ $XFL_MANIFEST ];then
export MANIFEST_URL="git://review.sonyericsson.net/platform/"$XFL_MANIFEST
else
export MANIFEST_URL="git://review.sonyericsson.net/platform/manifest"
fi
export XFL_FILE=$XFL_WS/out/target/product/$TARGET/xfl.mbn
export XBOOT_FILE_INTERMEDIATE=intermediate/bootloader_PRIVATE_$USER.tar
export XBOOT_FILE=$XBOOT_WS/out/bootloader/$TARGET/$XBOOT_FILE_INTERMEDIATE
export OUT_ROBOT_DIR=$EXEC_DIR/out
export ANDROID_SW_DIR=$OUT_ROBOT_DIR/android_sw
export LABEL_FILE=$XFL_WS/label.txt
export LD_LIBRARY_PATH=$ROBOT_DIR/../auth
# Timeouts when waiting for ADB and fastboot connections
export ADB_TIMEOUT=300
export FASTBOOT_TIMEOUT=90

function wait_for_adb {
	state=""
	t=0
	while [[ "$state" != "device" && $t != $ADB_TIMEOUT ]]; do
		sleep 3
		let t=$t+3
		state=`adb get-state`
	done
	if [ $t != $ADB_TIMEOUT ]; then
		echo "ADB device is connected!"
	else
		echo "Timeout when waiting for ADB device!"
	fi
}

function wait_for_fastboot_device {
	resp=""
	t=0

	while [[ ${resp:${#resp}-8:8} != "fastboot" && \
			$t != $FASTBOOT_TIMEOUT ]]; do
		sleep 3
		let t=$t+3
		resp=`fastboot devices`
	done
	if [ $t != $FASTBOOT_TIMEOUT ]; then
		echo "Entered Fastboot mode!"
	else
		echo "Timeout when waiting for Fastboot Mode!, response:"$resp
	fi
}

########################################
# Build XFL
########################################

if [ "$BUILD_XFL" == true ]; then

# Remove previous build files
#if [ "$(ls -A $XFL_WS/out)" ]; then
#	rm -r $XFL_WS/out/*
#fi

if [ ! -d "$XFL_WS" ]; then
	mkdir -p $XFL_WS
	cd $XFL_WS
	repo init -u $MANIFEST_URL -b $XFL_BRANCH
	repo sync
else
	cd $XFL_WS
fi

# Delete any previous topic branch
cd $XFL_FS_MAIN_DIR
git cherry-pick --abort
git rebase --abort
git checkout origin/master
git branch -D $TOPIC_BRANCH

repo sync

# Create topic branch and cherry-pick commit
repo start $TOPIC_BRANCH .
# Cherry-pick commit here
cd $XFL_WS

# Touch makefile to ensure XFL is rebuilt
touch $XFL_FS_MAIN_DIR/build/linux/android_main.mk

source build/envsetup.sh
lunch $BUILD_TARGET

export MIN_XFL_VERSION=$(echo $XFL_VERSION.$(date +%Y%m%d.%H%M%S))
make loader -j8 $XFL_BUILD_OPTION
export MAX_XFL_VERSION=$(echo $XFL_VERSION.$(date +%Y%m%d.%H%M%S))

# End of 'if [ $BUILD_XFL ]'
fi

########################################
# Build XBoot
########################################

if [ "$BUILD_XBOOT" == true ]; then

echo "Build XBoot in $XBOOT_WS"

# Remove previous build files
#if [ "$(ls -A $XBOOT_WS/out)" ]; then
#	rm -r $XBOOT_WS/out/*
#fi

if [ ! -d "$XBOOT_WS" ]; then
	mkdir -p $XBOOT_WS
	cd $XBOOT_WS
	repo init -u $MANIFEST_URL -b $XBOOT_BRANCH
else
	cd $XBOOT_WS
fi

# Delete any previous topic branch
cd $XBOOT_FS_MAIN_DIR
git cherry-pick --abort
git rebase --abort
git checkout origin/master
git branch -D $TOPIC_BRANCH

repo sync -j8

# Create topic branch and cherry-pick commit
repo start $TOPIC_BRANCH .
# Cherry-pick commit here
cd $XBOOT_WS

source build/envsetup.sh
lunch common-eng
make sin -j8

# End of 'if [ $BUILD_XBOOT ]'
fi

########################################
# Copy test files to execution directory
########################################
if [ ! -d "$EXEC_DIR" ]; then
	mkdir $EXEC_DIR
	cd $EXEC_DIR
else
	cd $EXEC_DIR
	# Wipe any previous data
	if [ "$(ls -A .)" ]; then
		rm -r *
	fi
fi

if [ ! -d "$OUT_ROBOT_DIR" ]; then
	mkdir $OUT_ROBOT_DIR
fi

cp -r $ROBOT_DIR/* $EXEC_DIR/
cp $ROBOT_DIR/../auth/libsecs.so $EXEC_DIR/
cp $ROBOT_DIR/../auth/secsauth $EXEC_DIR/

########################################
# Enter software service
########################################
echo "Reboot into XFL..."
wait_for_adb
adb reboot oem-53
wait_for_fastboot_device

########################################
# Get software
########################################
# Get latest label on $PLATFORM_BRANCH
LATEST_LABEL=$(repository latestlabel $PLATFORM_BRANCH)
echo "Latest label on" $PLATFORM_BRANCH "is" $LATEST_LABEL

# Get product SW if not already done
if [ -f $LABEL_FILE ]; then
	PREVIOUS_LABEL=$(cat $LABEL_FILE)
else
	PREVIOUS_LABEL=unknown
fi

if [ "$BUILD_XFL" == true ]; then
if [ $LATEST_LABEL != $PREVIOUS_LABEL ]; then
	echo "Get SW" $LATEST_LABEL
	if [ ! -d "$ANDROID_SW_DIR" ]; then
		mkdir $ANDROID_SW_DIR
	fi
	if [ "$(ls -A $ANDROID_SW_DIR)" ]; then
		rm -r $ANDROID_SW_DIR/*
	fi
	semcpkgtoimg $SW_PACKAGE result-flashable variant-userdebug -l $LATEST_LABEL -out $ANDROID_SW_DIR

	# Authenticate to be able to flash
	python $ROBOT_DIR/fastboot.py Authenticate:challenge c.bin
	$ROBOT_DIR/../auth/secsauth c.bin r.bin
	python $ROBOT_DIR/fastboot.py Authenticate:response r.bin

	. flash.sh
	echo $LATEST_LABEL > $LABEL_FILE

	echo "Boot to Android to set SW version in TA (wait for adb)..."
	python fastboot.py continue
	wait_for_adb
	# Wait an additional 5 seconds...
	sleep 5

	echo "Reboot to SW service..."
	adb reboot oem-53
	wait_for_fastboot_device
fi
fi

# Authenticate (again if Android SW was flashed) to be able to flash
python $ROBOT_DIR/fastboot.py Authenticate:challenge c.bin
$ROBOT_DIR/../auth/secsauth c.bin r.bin
python $ROBOT_DIR/fastboot.py Authenticate:response r.bin

# Flash XBoot if built
if [ "$BUILD_XBOOT" == true ]; then
echo Flash XBoot $XBOOT_FILE
python fastboot.py flash $XBOOT_PARTITION $XBOOT_FILE
else
# Get label for boot package in version $LATEST_LABEL
XBOOT_VERSION=$(repository list $LATEST_LABEL | grep -oP $BOOT_PACKAGE' \K.*')
fi

echo "Boot version is" $XBOOT_VERSION

# Flash XFL if built
if [ "$BUILD_XFL" == true ]; then
echo "Flash" $XFL_FILE
python fastboot.py flash $XFL_PARTITION $XFL_FILE
fi

# Create a one-byte file with 0x01
echo -n -e \\x01 > ta_01.bin

# Set TA Enable kernel log
python fastboot.py Write-TA 2 2473 ta_01.bin

# Reboot
# If one-fastboot is implemented (version > 0.39),
# we should do reboot-bootloader
echo "Reboot and enter XFL again..."

# Check protocol version to determine which reboot command to use
version=`python fastboot.py getvar Version-sony`
echo $version

if [ $version \> 'OKAY0.39' ] ; then
python fastboot.py reboot-bootloader
else
python fastboot.py reboot
fi

wait_for_fastboot_device

cd $EXEC_DIR

########################################
# Generate SwVariables.py
########################################
echo "#!/usr/bin/env python3" > SwVariables.py
echo "from Definitions import *" >> SwVariables.py
# Generate SwState variables
echo "inputSwState = SwState()" >> SwVariables.py
echo "inputSwState.xflVersion = "\"$XFL_VERSION\" >> SwVariables.py
echo "inputSwState.minXflVersion = "\"$MIN_XFL_VERSION\" >> SwVariables.py
echo "inputSwState.maxXflVersion = "\"$MAX_XFL_VERSION\" >> SwVariables.py
echo "inputSwState.bootVersion = "\"$XBOOT_VERSION\" >> SwVariables.py
echo "inputSwState.versionBaseband = "\"$SW_SPACE_ID"_"$LATEST_LABEL\" >> SwVariables.py
# Generate DutState variables
echo "inputDutState = DutState()" >> SwVariables.py
echo "inputDutState.model = Model."$MODEL >> SwVariables.py
echo "inputDutState.product = "\"$PRODUCT\" >> SwVariables.py
echo "inputDutState.serial = "\"$SERIAL\" >> SwVariables.py
echo "inputDutState.storageInfo = "\"$STORAGE_INFO\" >> SwVariables.py
echo "inputDutState.secureStorageState.keystoreCounter = "\"$KEYSTORE_COUNTER\" >> SwVariables.py
echo "inputDutState.secureStorageState.locked = LockState."$SECURE_STORAGE_STATE >> SwVariables.py
echo "inputDutState.lockState = LockState."$LOCK_STATE >> SwVariables.py
echo "inputDutState.rootingStatus = RootingStatus."$ROOTING_STATUS >> SwVariables.py
echo "inputDutState.phoneId = "\"$PHONE_ID\" >> SwVariables.py
echo "inputDutState.deviceId = "\"$DEVICE_ID\" >> SwVariables.py

########################################
# Generate Partition Info
########################################
# fetch fsconfig pkg
echo "Fetching fsconfig debian package"
pkg_path=''
while read line
do
  if [[ $line = *"fsconfig"* ]]; then
    pkg_path="$line"
  fi
done <<< "$(semcpkgtoimg $SW_PACKAGE result-flashable variant-userdebug -l $LATEST_LABEL -dru)"

# Create test data directory if it doesn't exist
if [ ! -d "$TEST_DATA_DIR" ]; then
	mkdir -p $TEST_DATA_DIR
fi

semcpkgtoimg $pkg_path variant-userdebug -l $LATEST_LABEL -wdir $TEST_DATA_DIR/temp -keep
# copy fsconfig.xml and prepare partition.zip to generate partition info
cp $FSCONFIG_XML_FILE $TEST_DATA_DIR/

if [ -d "$PARTITIONS_DIR" ]; then
	# Partition directory is provided, zip files
	cd $PARTITIONS_DIR
	zip $TEST_DATA_DIR/partition.zip ./*
	cd -
	echo "Generating PartitionInfo.py for $TARGET"
	python partitionInfoGenerator.py --path=$TEST_DATA_DIR\
		--partitions=$TEST_DATA_DIR/partition.zip\
		--block_size=$BLOCK_SIZE
else
	# Partition directory is not available, use fsconfig.xml
	echo "Generating PartitionInfo.py for $TARGET from fsconfig.xml"
	python partitionInfoGenerator.py --path=$TEST_DATA_DIR\
		--block_size=$BLOCK_SIZE
fi

########################################
# Generate CMS file
########################################
# The file Test.rst is used as payload and bootloader as target
# In TestContent.py it is assumed that bootloader.cms exists in
# current directory.
signatory -c $BOOT_CERT -t CMS --cms-gpt-name bootloader -i Test.rst\
 -o $TEST_DATA_DIR/bootloader.sin
cd $TEST_DATA_DIR
tar -xf $TEST_DATA_DIR/bootloader.sin
cd -

########################################
# Start robot tests
########################################
ROBOT_TAGS="-i $PLATFORM"
if [ "$SELECTED_TEST" == true ]; then
ROBOT_TAGS+="ANDtest"
fi
if [ $PLATFORM_VARIANT ]; then
ROBOT_TAGS+=" -i $PLATFORM_VARIANT"
if [ "$SELECTED_TEST" == true ]; then
ROBOT_TAGS+="ANDtest"
fi
fi

robot -d $EXEC_DIR/report $ROBOT_TAGS Test.rst

cd $CURRENT_DIR

echo "DONE!"

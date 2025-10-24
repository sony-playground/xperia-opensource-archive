# These variables need to be updated for each product

export TARGET=aurora
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=tama
export PLATFORM_BRANCH=p-tama2
#export PLATFORM_VARIANT=softbank
export PRODUCT="H8116"
export SERIAL="BH900043A9"
export PHONE_ID="0000:00440245820420,0000:00440245820920"
export DEVICE_ID="E207C8EF"
export STORAGE_INFO="SKhynix,H28S7Q302BMR,A001"
export KEYSTORE_COUNTER="8"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="ROOTABLE"
export BOOT_PACKAGE=fw-xboot-$TARGET
export SW_PACKAGE=pp-aurora-gdialer-a1-generic
export SW_SPACE_ID=1312-7116

export XFL_BRANCH=tama-lilo
export XFL_PARTITION="xfl_a"
export XFL_VERSION=$USER

export XBOOT_BRANCH=o-tama-xboot
export XBOOT_PARTITION="bootloader_a"
# Version of private boot builds
export XBOOT_VERSION="1310-7079-X-BOOT-SDM845-LA1.0-O-PRIVATE-"$USER

# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true

# Setting BUILD_XBOOT to true will override existing bootloader on the device.
# If set to false, bootloader will not be built and flashed.
export BUILD_XBOOT=true

# Set DEV_TEST to true when developing the robot tests,
# will execute the tests from current directory
export DEV_TEST=false
# If DEV_TEST is false, the tests will execute in $START_DIR
export START_DIR=$HOME/Temp/robot

export CUR_DIR=$CURRENT_DIR

if [ $DEV_TEST == false ]; then
# Start the test from $START_DIR
# Remove previous files
if [ -d "$START_DIR" ]; then
	rm -rf $START_DIR/*
fi

# Download the run script
git clone git://review.sonyericsson.net/platform/vendor/semc/fs/main $START_DIR
# The master branch is default checked out
cd $START_DIR/test/robot
fi

. run_test.sh

cd $CUR_DIR

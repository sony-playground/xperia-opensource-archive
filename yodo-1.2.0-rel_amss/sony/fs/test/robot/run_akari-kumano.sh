# These variables need to be updated for each product

export TARGET=akari
# MODEL should be in upper case
# Add suffix _KUMANO for kumano development on tama devices
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)_KUMANO
# Platform for features
export PLATFORM=kumano
export PLATFORM_VARIANT=softbank
export PLATFORM_BRANCH=p-tama2-softbank
export PRODUCT="702SO"
export SERIAL="BH90003MBJ"
export PHONE_ID="0000:00440245847714"
export DEVICE_ID="5658325B"
export STORAGE_INFO="SAMSUNG,KLUCG2K1EA-B0C1,0100"
export KEYSTORE_COUNTER="4"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="NOT_ROOTABLE"
export BOOT_PACKAGE=fw-xboot-$TARGET
export SW_PACKAGE=pp-akari-softbank-s1-generic
export SW_SPACE_ID=1311-9108

export XFL_BRANCH=feature-tama-lilo-pre-kumano
export XFL_PARTITION="xfl_a"
export XFL_VERSION=$USER

export XBOOT_BRANCH=o-tama-xboot-pre-kumano
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

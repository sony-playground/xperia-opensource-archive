# These variables need to be updated for each product

export TARGET=akari
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=tama
export PLATFORM_BRANCH=o-tama-softbank
export PLATFORM_VARIANT=softbank
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
export XFL_BRANCH=tama-lilo
export XFL_PARTITION="xfl_a"
export XFL_VERSION=$USER
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=false

. run_test.sh


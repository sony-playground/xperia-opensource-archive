# These variables need to be updated for each product

export TARGET=lilac
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=yoshino
export PLATFORM_BRANCH=p-yoshino
export PRODUCT="G8441"
export SERIAL="BH9000J57S"
export PHONE_ID="0000:00440245737737"
export DEVICE_ID="7C3B7E5D"
export STORAGE_INFO="TOSHIBA,THGAF4G8N2LBAIRB,0100"
export KEYSTORE_COUNTER="0"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="ROOTABLE"
export BOOT_PACKAGE=fw-xboot-$TARGET
export BOOT_CERT=X-FLASH-ALL-5ADA
export SW_PACKAGE=pp-lilac-global-lte4a-generic
export SW_SPACE_ID=1306-8499
export XFL_BRANCH=yoshino-lilo
export XFL_PARTITION="xfl"
export XFL_VERSION="eng."${USER:0:6}
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=false

. run_test.sh

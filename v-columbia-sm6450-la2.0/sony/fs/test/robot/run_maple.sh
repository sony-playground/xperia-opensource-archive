# These variables need to be updated for each product

export TARGET=maple
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=yoshino
export PLATFORM_BRANCH=p-yoshino
export PRODUCT="G8141"
export SERIAL="CB512D8MA9"
export PHONE_ID="0000:00440254186241"
export DEVICE_ID="AE972D8D"
export STORAGE_INFO="TOSHIBA,THGAF4G9N4LBAIRB,0100"
export KEYSTORE_COUNTER="0"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="NOT_ROOTABLE"
export BOOT_PACKAGE=fw-xboot-$TARGET
export BOOT_CERT=X-FLASH-ALL-5ADA
export SW_PACKAGE=pp-maple-global-lte4a-generic
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

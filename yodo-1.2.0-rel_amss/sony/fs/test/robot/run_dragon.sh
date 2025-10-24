# These variables need to be updated for each product

export TARGET=dragon
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=huaihe
export PLATFORM_BRANCH=o-huaihe-dragon
export PRODUCT="dragon"
export SERIAL="CB5129YLD6"
export PHONE_ID="0000:00440245123456"
export DEVICE_ID="3CF8E659D0C3C11FC87EE56EFF9786A0"
export STORAGE_INFO="SAMSUNG,KLUCG2K1EA-B0C1,0100"
export KEYSTORE_COUNTER="1"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="ROOTABLE"
export BOOT_PACKAGE=fw-xboot-dragon
export BOOT_CERT=X-FLASH-ALL-0A82
export SW_PACKAGE=pp-dragon-dev-dev
export SW_SPACE_ID=1315-2605
export XFL_BRANCH=odm/hq/android/common-huaihe-xfl
export XFL_MANIFEST=xflmanifest
export XFL_PARTITION="xfl_a"
#export XFL_BUILD_OPTION="ALLOW_MISSING_DEPENDENCIES=true"
export XFL_VERSION=$USER
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=false
# If SELECTED_TEST is true, only tests tagged with 'test' are executed.
export SELECTED_TEST=false

. run_test.sh


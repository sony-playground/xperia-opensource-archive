# These variables need to be updated for each product

export TARGET=apollo
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=tama
export PLATFORM_BRANCH=p-tama2
export PRODUCT="H8314"
export SERIAL="BH9000KAA2"
export PHONE_ID="0000:00440245811857,0000:00440245813077"
export DEVICE_ID="39F488CE"
export STORAGE_INFO="SAMSUNG,KLUCG4J1ED-B0C1,0200"
export KEYSTORE_COUNTER="3"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="ROOTABLE"
export BOOT_PACKAGE=fw-xboot-$TARGET
export BOOT_CERT=X-FLASH-ALL-AE08
export SW_PACKAGE=pp-apollo-global-a1-generic
export SW_SPACE_ID=1311-7916
export XFL_BRANCH=tama-lilo
export XFL_PARTITION="xfl_a"
export XFL_VERSION=$USER
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=false

. run_test.sh


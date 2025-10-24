# These variables need to be updated for each product

export TARGET=griffin
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=kumano
export PLATFORM_BRANCH=p-kumano
export PRODUCT="J8110"
export SERIAL="BH9700QFFR"
export PHONE_ID="0000:00440245939357"
export DEVICE_ID="4A9A3D16"
export STORAGE_INFO="TOSHIBA,THGAF8T0T43BAIRB,0300"
export KEYSTORE_COUNTER="2"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="ROOTABLE"
export BOOT_PACKAGE=fw-xboot-griffin
export BOOT_CERT=X-FLASH-ALL-0A82
export SW_PACKAGE=pp-griffin-gdialer-a1-generic
export SW_SPACE_ID=1317-9335
export XFL_BRANCH=kumano-xfl
export XFL_MANIFEST=xflmanifest
export XFL_PARTITION="xfl_a"
export XFL_BUILD_OPTION="ALLOW_MISSING_DEPENDENCIES=true"
export XFL_VERSION=$USER
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=true
# If SELECTED_TEST is true, only tests tagged with 'test' are executed.
export SELECTED_TEST=false

#while [ true ]; do
  . run_test.sh
#done

# These variables need to be updated for each product

export TARGET=sphinx
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=kumano
export PLATFORM_BRANCH=p-kumano-plus
export PLATFORM_VARIANT=kumano_plus
export PRODUCT="J8010"
export SERIAL="BH9000QPF4"
export PHONE_ID="0000:00440245924908"
export DEVICE_ID="301C3240"
export STORAGE_INFO="SAMSUNG,KLUDG4U1EA-B0C1,0500"
export KEYSTORE_COUNTER="2"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="UNLOCKED"
export ROOTING_STATUS="ROOTED"
export BOOT_PACKAGE=fw-xboot-sphinx
export BOOT_CERT=X-FLASH-ALL-0A82
export SW_PACKAGE=pp-sphinx-global-a1-generic
export SW_SPACE_ID=1318-1463
export XFL_BRANCH=kumano-plus-xfl
export XFL_MANIFEST=xflmanifest
export XFL_PARTITION="xfl_a"
export XFL_BUILD_OPTION="ALLOW_MISSING_DEPENDENCIES=true \
	FCS_PLATFORM=kumano_plus"
export XFL_VERSION=$USER
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=false
# If SELECTED_TEST is true, only tests tagged with 'test' are executed.
export SELECTED_TEST=false

#while [ true ]; do
. run_test.sh
#done


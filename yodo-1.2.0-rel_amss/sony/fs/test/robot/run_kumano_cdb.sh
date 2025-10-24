# These variables need to be updated for each product

export TARGET=kumano_cdb
# MODEL should be in upper case
export MODEL=$(echo $TARGET | tr /a-z/ /A-Z/)
export PLATFORM=kumano
export PLATFORM_BRANCH=p-kumano
export PRODUCT="kumano_cdb"
export SERIAL=""
export PHONE_ID="0000:00000000000777"
export DEVICE_ID="FD6156CE"
export STORAGE_INFO="SAMSUNG,KLUCG2K1EA-B0C1,0100"
export KEYSTORE_COUNTER="13"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="UNLOCKED"
export ROOTING_STATUS="ROOTED"
export BOOT_PACKAGE=fw-xboot-kumano-cdb
export BOOT_CERT=X-FLASH-ALL-0A82
export SW_PACKAGE=pp-kumanocdb-dev-dev
export SW_SPACE_ID=0000-0000
export XFL_BRANCH=kumano-xfl
export XFL_MANIFEST=xflmanifest
export XFL_PARTITION="xfl_a"
export XFL_BUILD_OPTION="ALLOW_MISSING_DEPENDENCIES=true"
export XFL_VERSION=$USER
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=false
# If SELECTED_TEST is true, only tests tagged with 'test' are executed.
export SELECTED_TEST=false

. run_test.sh


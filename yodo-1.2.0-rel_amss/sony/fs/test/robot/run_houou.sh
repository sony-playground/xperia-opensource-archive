# These variables need to be updated for each product

export TARGET=houou
# MODEL should be in upper case
export MODEL=HOUOU
export PLATFORM=ganges
export PLATFORM_VARIANT=ganges-vb1
export PLATFORM_BRANCH=p-ganges-docomo
export PRODUCT="SO-02L"
export SERIAL="BH9200HLDJ"
export PHONE_ID="0000:00440254206573"
export DEVICE_ID="12C67230"
export STORAGE_INFO="SAMSUNG,0x0100,0x0"
export KEYSTORE_COUNTER="3"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="NOT_ROOTABLE"
export BOOT_PACKAGE=fw-xboot-$TARGET
export BOOT_CERT=X-FLASH-ALL-9B8D
export BLOCK_SIZE=512
export SW_PACKAGE=pp-houou-docomo-n1-generic
export SW_SPACE_ID=1316-7200
export XFL_BRANCH=houou-xfl
export XFL_MANIFEST=xflmanifest
export XFL_PARTITION="xfl_a"
export XFL_BUILD_OPTION="ALLOW_MISSING_DEPENDENCIES=true"
export XFL_VERSION=${USER:0:8}
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
# Also required if fs/main git is not on master branch for this product
export DEV_TEST=true

#while [ true ]; do
. run_test.sh
#done

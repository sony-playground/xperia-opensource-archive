# These variables need to be updated for each product

export TARGET=houou_mvno
# MODEL should be in upper case
export MODEL=HOUOU_MVNO
export PLATFORM=ganges
export PLATFORM_VARIANT=ganges-vb2
export PLATFORM_BRANCH=p-ganges-mvno
export PRODUCT="JP1V1"
export SERIAL="BH92001MFX"
export PHONE_ID="0000:00440245945164"
export DEVICE_ID="495AA09D"
export STORAGE_INFO="MICRON,0x014e,0x0"
export KEYSTORE_COUNTER="2"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="NOT_ROOTABLE"
export BOOT_PACKAGE=fw-xboot-houou-v1
export BOOT_CERT=X-FLASH-ALL-9B8D
export BLOCK_SIZE=512
export SW_PACKAGE=pp-houou-mvno-v1-generic
export SW_SPACE_ID=1319-6337
export XFL_BRANCH=ganges-mvno-xfl
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

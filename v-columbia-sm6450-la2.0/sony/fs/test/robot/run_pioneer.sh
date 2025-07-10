# These variables need to be updated for each product

export TARGET=nile
# MODEL should be in upper case
export MODEL=PIONEER
export PLATFORM=nile
export PLATFORM_BRANCH=o-nile-release
export PRODUCT="H3113"
export SERIAL=""
export PHONE_ID="0000:00440245789204"
export DEVICE_ID="1C2212F5"
export STORAGE_INFO="MICRON,0x014e,0x0"
export KEYSTORE_COUNTER="6"
export SECURE_STORAGE_STATE="UNLOCKED"
export LOCK_STATE="LOCKED"
export ROOTING_STATUS="NOT_ROOTABLE"
export BOOT_PACKAGE=fw-xboot-$TARGET
export SW_PACKAGE=pp-pioneer-gdialer-a1-generic
export SW_SPACE_ID=1311-5291
export XFL_BRANCH=odm/cei/android/n-nile-xfl
export XFL_PARTITION="xfl_a"
export XFL_VERSION="eng."${USER:0:6}
# Setting BUILD_XFL to true will override existing XFL on the device.
# If set to false, XFL will not be built and flashed.
export BUILD_XFL=true
# Set DEV_TEST to true when developing the robot tests
export DEV_TEST=true

. run_test.sh

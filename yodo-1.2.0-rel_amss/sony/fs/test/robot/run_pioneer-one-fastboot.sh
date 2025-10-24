# These variables need to be updated for each product

export TARGET=nile
# MODEL should be in upper case
export MODEL=PIONEER
export PLATFORM=kumano
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
export XFL_BRANCH=nile-lilo-one-fastboot
export XFL_PARTITION="xfl_a"
export XFL_VERSION="eng."${USER:0:6}

. run_test.sh


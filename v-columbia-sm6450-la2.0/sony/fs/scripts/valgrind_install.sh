#!/bin/bash -e
# VALGRIND_LIB variable needs to be set on the device:
# export VALGRIND_LIB=/system/bin
# Run valgrind memcheck on the device:
# valgrind --log-file="valgrind.txt" /system/bin/loader -g/dev/fs -llog.log -sufs

if [[ -z "$ANDROID_BUILD_TOP" ]]; then
	echo "ANDROID_BUILD_TOP var is empty please run:"
	echo "source build/envsetup.sh"
	echo "lunch 'target-xxx'"
	exit 1
fi
cd $ANDROID_BUILD_TOP
source build/envsetup.sh
lunch $TARGET_PRODUCT-$TARGET_BUILD_VARIANT
mmma -j6 external/valgrind
make lilo -j6
adb push out/target/product/$TARGET_PRODUCT/obj/EXECUTABLES/valgrind_intermediates/LINKED/valgrind /system/bin/
adb push out/target/product/$TARGET_PRODUCT/obj/SHARED_LIBRARIES/memcheck-arm64-linux_intermediates/LINKED/memcheck-arm64-linux /system/bin/
adb push out/target/product/$TARGET_PRODUCT/obj/SHARED_LIBRARIES/callgrind-arm64-linux_intermediates/LINKED/callgrind-arm64-linux /system/bin/
adb push out/target/product/$TARGET_PRODUCT/obj/EXECUTABLES/lilo_intermediates/LINKED/lilo /system/bin/
adb push out/target/product/$TARGET_PRODUCT/obj/lib/default.supp /system/bin/
adb shell mkdir /data/local/
adb shell mkdir /data/local/tmp




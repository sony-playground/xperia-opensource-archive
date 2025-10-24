#!/bin/bash
#

echo "Generate HW Config for platform $1 with Device Id $2 and IMEI(s) $3 [$4]"
echo "Security is set to OFF"
echo "Output is fs/main/test/boot/build/data_generator/hwconf.hex"
echo "which can be pasted into TA 2003 in FG4"

SECS_PATH=$ANDROID_BUILD_TOP/vendor/semc/fs/flashtools/secs

# Build libsecs.so, check README.md for dependencies.
pushd $SECS_PATH
make client
popd

pushd ../test/boot/build/data_generator
export PYTHONPATH=$SECS_PATH/test/
export LD_LIBRARY_PATH=$SECS_PATH/client/SECS/
python gen_hwconf.py $1 OFF $2 $3 $4

# Back to script dir
popd


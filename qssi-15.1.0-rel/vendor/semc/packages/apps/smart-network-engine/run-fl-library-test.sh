#!/bin/bash -e

## How to run test
# <no-args>                        Run all tests
# -e class <class-name>            Run all the tests in <class-name>
#   (e.g. '-e class com.sony.fl.db.TestDBForPredictManager')

wait_for_boot_completed() {
  while [ "`adb shell getprop sys.boot_completed | tr -d '\r' `" != "1" ] ; do sleep 5; done
}

APP_DIR=$(cd $(dirname $0); pwd)
FLLIB_TEST_DIR=$APP_DIR/app/src/test/

DEFAULT_OPTS="-e notClass com.sony.fl.db.TestSQLite#testSQLite"

#--------------------------------------------------
cd $APP_DIR

# Temporary modify the existing files
sed -i "s/\/\/FLLIBTEST://g" app/build.gradle
find $FLLIB_TEST_DIR -name *.java -o -name *.txt \
    | xargs sed -i "s/src\/test/\/data\/data\/com.sonymobile.smartnetworkengine/g"

# Build & Install SNE and SNE test apps
./gradlew -q clean installDebug installDebugAndroidTest

# Deploy test resources
adb root; adb wait-for-device
adb remount; adb wait-for-device
adb push $FLLIB_TEST_DIR\resources /data/data/com.sonymobile.smartnetworkengine
adb shell chmod -R 777 /data/data/com.sonymobile.smartnetworkengine/resources

# Run tests
_OPTS=$DEFAULT_OPTS
if [ -n "$*" ]; then
    _OPTS=$*
fi
adb shell am instrument -w "$_OPTS" com.sonymobile.smartnetworkengine.test/com.sonymobile.smartnetworkengine.TestRunner

# Uninstall the apps
./gradlew -q uninstallAll

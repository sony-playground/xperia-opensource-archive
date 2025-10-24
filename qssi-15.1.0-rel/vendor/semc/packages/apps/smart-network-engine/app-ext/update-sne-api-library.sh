#!/bin/bash -e

## How to run this script
# ./this-script.sh <sha1>          Generate library from supplied sha1

if [ $# != 1 ]; then
    echo "invalid argument"
    exit 1
fi

APP_DIR=$(cd $(dirname $0); pwd)
WORK_DIR=${APP_DIR}/build/tmp
SHA1=$1
if [ -z "${ANDROID_HOME}" ]; then
    export ANDROID_HOME=~/Android/Sdk
fi

#--------------------------------------------------

rm -rf $WORK_DIR ; mkdir -p $WORK_DIR ; cd $WORK_DIR

# Fetch SNE app repository
git clone ssh://review.ptc.sony.co.jp:29418/platform/vendor/semc/packages/apps/smart-network-engine
cd smart-network-engine
git checkout $SHA1
git log -1 HEAD

# Generate library
./gradlew clean assemble

# Deploy library
cp app-api/build/outputs/aar/app-api-release.aar $APP_DIR/libs/sne-api.aar

#--------------------------------------------------

msg=$(cat << EOD
Update SNE API library

The library has been generated from:

commit $SHA1
(platform/vendor/semc/packages/apps/smart-network-engine)

EOD
)

cd $APP_DIR
git add libs && echo "$msg" | git commit -F -

echo ---
git log -1 HEAD
echo ---

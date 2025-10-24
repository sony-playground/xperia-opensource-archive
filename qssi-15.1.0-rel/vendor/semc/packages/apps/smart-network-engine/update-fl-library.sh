#!/bin/bash -e

## How to run this script
# ./this-script.sh <path-to-lib.tar.gz>          Deploy FLLib (for Nagara1.0)

if [ $# != 1 ]; then
    echo "invalid argument"
    exit 1
fi

function pause() {
    prompt="$1"
    echo -e -n "\033[1;36m$prompt"
    echo -e -n '\033[0m'
    read
    clear
}

APP_DIR=$(cd $(dirname $0); pwd)
WORK_DIR=/tmp/_FLLib_int_tmp
FLLIB=$1

#--------------------------------------------------
cd $APP_DIR

# Clean up work directory
rm -rf $WORK_DIR && mkdir $WORK_DIR

# Extract the library to work directory
tar zxvf $FLLIB -C $WORK_DIR --strip-components 1

# Remove the existing library files
rm -rf app/src/main/java/com/sony/fl
rm -rf app/src/main/jni/fl && mkdir app/src/main/jni/fl
rm -rf app/src/test

# Deploy new version
cp -rp $WORK_DIR/src/main/java app/src/main/
cp -rp $WORK_DIR/src/main/jni/* app/src/main/jni/fl/
cp -rp $WORK_DIR/src/test app/src/
pause "CAUTION: Java/Native build config and proto files may need to be updated(deployed) manually.\nPress enter to continue..."

rm -rf $WORK_DIR
#--------------------------------------------------

msg=$(cat << EOD
Update FLLib to ver-<TBD>

Issue: SNE-<TBD>
EOD
)

git restore app/src/main/java/com/sony/fl/pb/*.proto
git add app/src
echo "$msg" | git commit -e -F -

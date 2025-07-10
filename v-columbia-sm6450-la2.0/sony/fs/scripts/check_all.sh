#!/bin/bash
#
# Run checkpatch on all files in the following directories
# Files in excludeFiles.txt should be excluded
python check_all.py "$ANDROID_BUILD_TOP/vendor/semc/fs/main/scripts/checkpatch.pl --no-tree -f" $ANDROID_BUILD_TOP vendor/semc/fs/main/boot excludeFiles.txt
python check_all.py "$ANDROID_BUILD_TOP/vendor/semc/fs/main/scripts/checkpatch.pl --no-tree -f" $ANDROID_BUILD_TOP vendor/semc/fs/main/build excludeFiles.txt
python check_all.py "$ANDROID_BUILD_TOP/vendor/semc/fs/main/scripts/checkpatch.pl --no-tree -f" $ANDROID_BUILD_TOP vendor/semc/fs/main/core excludeFiles.txt
python check_all.py "$ANDROID_BUILD_TOP/vendor/semc/fs/main/scripts/checkpatch.pl --no-tree -f" $ANDROID_BUILD_TOP vendor/semc/fs/main/integration excludeFiles.txt
python check_all.py "$ANDROID_BUILD_TOP/vendor/semc/fs/main/scripts/checkpatch.pl --no-tree -f" $ANDROID_BUILD_TOP vendor/semc/fs/main/loader excludeFiles.txt
python check_all.py "$ANDROID_BUILD_TOP/vendor/semc/fs/main/scripts/checkpatch.pl --no-tree -f" $ANDROID_BUILD_TOP vendor/semc/fs/main/scripts excludeFiles.txt
python check_all.py "$ANDROID_BUILD_TOP/vendor/semc/fs/main/scripts/checkpatch.pl --no-tree -f" $ANDROID_BUILD_TOP vendor/semc/fs/main/test excludeFiles.txt

#!/bin/bash

source ../authenticate.sh

RETVAL=0


if ! authenticate; then
	RETVAL=1
else
	echo "Authentication succeeded"
fi

adb shell "stop loader-trf"
exit $RETVAL

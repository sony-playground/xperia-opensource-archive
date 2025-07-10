#!/bin/bash
. ../common.sh

export LD_LIBRARY_PATH=`pwd`/../../../auth/
../../../auth/secsauth $HOST_TMP_DIR/$1 $HOST_TMP_DIR/$2

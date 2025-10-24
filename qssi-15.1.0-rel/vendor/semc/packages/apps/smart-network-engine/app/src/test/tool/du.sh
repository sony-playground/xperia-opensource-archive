#!/bin/bash
set -u

if [ $# -eq 0 ]; then
    readonly DIR=./
else
    readonly DIR=$1
fi

if [ ! -d ${DIR} ]; then
    echo "No such directory: ${DIR}"
    exit 1
fi

if [ $# -lt 2 ]; then
    readonly DELAY=1
else
    readonly DELAY=$2
fi

echo "#time,du[$(cd ${DIR} && pwd)]"

while :
do
    USAGE=($(du -b -s $DIR))
    echo -n "$(date "+%Y/%m/%d %H:%M:%S"),"
    echo ${USAGE[0]}
    sleep ${DELAY}
done

exit 0

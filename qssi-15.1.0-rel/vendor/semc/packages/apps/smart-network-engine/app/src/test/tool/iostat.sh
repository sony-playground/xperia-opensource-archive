#!/bin/bash
set -eu

if [ $# -lt 1 ]; then
    readonly DELAY=1
else
    readonly DELAY=$1
fi

readonly TARGET=$(ls /dev/sd? | sed -e 's/\/dev\///')
echo "#device:$(echo ${TARGET} | tr -d '\n'):$(iostat -o JSON | jq -r '.sysstat.hosts[0] | .nodename + ":" + .sysname + ":" + .release + ":" + .machine + ":" + (."number-of-cpus"|tostring)')"
echo "#time,tps,kB_read/s,kB_wrtn/s,kB_read,kB_wrtn"

while :
do
    NOW=$(date +"%Y/%m/%d %H:%M:%S")
    echo -n "${NOW},"
    iostat -dk -o JSON -g summary ${TARGET} | jq -r '.sysstat.hosts[0].statistics[0].disk[] | select(.disk_device == " summary") | [.tps, ."kB_read/s", ."kB_wrtn/s", .kB_read, .kB_wrtn] | @csv'
    sleep ${DELAY}
done

exit 0


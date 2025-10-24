#!/bin/bash

function print {
    echo "${1}" | sed -r 's/\s+/,/g'
}

COUNT=0
vmstat --one-header 1 | while read line; do
    COUNT=$((COUNT+1))
    if [ ${COUNT} -le 2 ]; then
        if [ ${COUNT} -eq 2 ]; then
            echo -n "timestamp,"
            print "${line}"
        fi
        continue
    fi
    echo -n "$(date "+%Y/%m/%d %H:%M:%S"),"
    print "${line}"
done

exit 0

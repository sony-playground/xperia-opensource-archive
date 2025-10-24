#!/bin/bash

echo "#time,NAME,CPU(%),MEM USAGE(MiB),LIMIT,MEM(%),NET INPUT, NET OUTPUT,BLOCK INPUT, BLOCK OUTPUT"
while :
do
    STATS=$(docker stats --no-stream --format "{{.Name}} / {{.CPUPerc}} / {{.MemUsage}} / {{.MemPerc}} / {{.NetIO}} / {{.BlockIO}}" | sed -e "s/\//,/g" | python3 docker_stats.py)
    NOW=$(date +"%Y/%m/%d %H:%M:%S")
    echo "${NOW},${STATS}"
done

exit 0

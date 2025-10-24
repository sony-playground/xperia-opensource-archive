#!/bin/bash
set -eu

readonly HOME_DIR="/var/fl"
readonly SCRIPTS_DIR="${HOME_DIR}/src/test/tool"

if [ $PPID -ne 0 ]; then
    cd $(dirname $0)/../../..
    docker run \
        --tty \
        --rm \
        --volume $(pwd):${HOME_DIR} \
        --volume $(pwd)/src/test/logs:/opt/FLLib/src/test/logs \
        --volume /var/run/docker.sock:/var/run/docker.sock \
        --volume /usr/bin/docker:/usr/bin/docker \
        fllib.runtime \
        bash ${SCRIPTS_DIR}/visualize.sh
    exit 0
fi

run() {
    TARGET=$(
        cd src/test/logs
        ls -tr jstat_* | tail -1 | sed -r 's/^jstat_(.*)\.log$/\1/'
    )
    python3 ${SCRIPTS_DIR}/visualize.py src/test/logs ${TARGET}
}

run

exit 0


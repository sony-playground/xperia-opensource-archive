#!/bin/bash

# ADB based communication

fastboot_command() {
    adb shell "echo $@|tr -d '\n'>$FBIP"
}

fastboot_get() {
    touch "$HOST_TMP_DIR/_out"
    if [ -z "$2" ] || [ $(wc -c <"$HOST_TMP_DIR/_out") -lt $2 ]; then
        adb shell "cat $FBOP>$DEV_TMP_DIR/fb_out"
        adb pull "$DEV_TMP_DIR/fb_out" "$HOST_TMP_DIR/_part" 2> /dev/null
        cat "$HOST_TMP_DIR/_part" >> "$HOST_TMP_DIR/_out"
    fi
    if [ -z "$2" ]; then
        dd if="$HOST_TMP_DIR/_out" of="$HOST_TMP_DIR/$1" 2> /dev/null
    else
        dd if="$HOST_TMP_DIR/_out" of="$HOST_TMP_DIR/$1" \
            bs=$2 count=1 2> /dev/null
        cp "$HOST_TMP_DIR/_out" "$HOST_TMP_DIR/_o"
        dd if="$HOST_TMP_DIR/_o" of="$HOST_TMP_DIR/_out" \
            bs=$2 skip=1 2> /dev/null
        rm "$HOST_TMP_DIR/_o"
    fi
}

fastboot_put() {
    adb push "$HOST_TMP_DIR/$1" "$DEV_TMP_DIR/" 2> /dev/null
    adb shell "dd if=$DEV_TMP_DIR/$1 of=$FBIP 2> /dev/null"
}

side_command() {
    adb shell "echo $@|tr -d '\n'>$SCCP"
}

side_response() {
    adb shell "cat $SCRP>$DEV_TMP_DIR/res_out"
    adb pull "$DEV_TMP_DIR/res_out" "$HOST_TMP_DIR/$1" 2> /dev/null
}

exec_remote() {
    adb shell "$@ 2> /dev/null"
    if [ $? -ne 0 ]; then
        echo "failed to execute $@"
        exit 1
    fi
}

push_remote() {
    adb push "$@" 2> /dev/null
}

pull_remote() {
    adb pull "$@" 2> /dev/null
}

start_loader() {
    adb shell "start loader-dbg"
}

stop_loader() {
    adb shell "stop loader-dbg"
}

get_pid() {
    local tokens=(`adb shell ps|grep "loader"`)
    echo "${tokens[1]}"
}

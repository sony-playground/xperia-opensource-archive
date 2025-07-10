#!/bin/bash

# ADB & android based memory checking

init_memchk() {
		MEMCHK_OPTS="\"backtrace guard free_track leak_track\""
		adb shell "setprop libc.debug.malloc.options" $MEMCHK_OPTS
}

exec_memchk() {
		adb logcat --pid=$1 -d | grep "malloc_debug:"
		adb logcat -c
}

#!/bin/bash
set -eu

export FL_LIBS_DIR="$(pwd)/libs"
export FL_SRC_DIR="$(pwd)/src"
export FL_DEPENDENCY_DIR="$(pwd)/dependency"
export FL_DEPENDENCY_LIBS_DIR="${FL_DEPENDENCY_DIR}/lib"
export FL_DEPENDENCY_INCL_DIR="${FL_DEPENDENCY_DIR}/include"

cd src/test/jni
cmake -S . -B build
cmake --build build

cd build

readonly LASTLOG="$(pwd)/Testing/Temporary/LastTest.log"
readonly FAILLOG="$(pwd)/Testing/Temporary/LastTestsFailed.log"

[ -f ${LASTLOG} ] && rm -f ${LASTLOG}
[ -f ${FAILLOG} ] && rm -f ${FAILLOG}

if [ -f /.dockerenv ]; then
    (
    cd $(pwd)/Testing/Temporary
    sudo rm -f tensor_map.root.jsonl && sudo touch tensor_map.root.jsonl
    sudo rm -f tensor_map.root.index && sudo touch tensor_map.root.index
    sudo rm -fr root.d && sudo mkdir root.d
    )
fi

set +e
ctest --output-junit Testing/Temporary/gtest_results.xml 2>&1
rcd=$?

junit2html Testing/Temporary/gtest_results.xml Testing/Temporary/gtest_results.html
echo "<hr/><p class=\"footer\">$(date)</p>" >> Testing/Temporary/gtest_results.html

if [ -f /.dockerenv ]; then
    (
    cd $(pwd)/Testing/Temporary
    sudo rm -f tensor_map.root.jsonl
    sudo rm -f tensor_map.root.index
    sudo rm -fr root.d
    )
fi

if [ $rcd -ne 0 ]; then
    echo "[31mTest failed. see ${LASTLOG}[37m"
fi

exit $rcd


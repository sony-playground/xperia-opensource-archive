#!/bin/bash

usage() {
    cat <<EOL
Usage: bash capture_coverage_data.sh NAME

  NAME: NAME is used for the tracefile name.
        e.g.    src/test/logs/trace_files/lcovFiltered_{NAME}.info
        valid.  letters, decimal digits and the underscore character ("_")
                must match the regular expression ^[a-zA-Z0-9_]+$

EOL
}

set -eu

if [ $# -ne 1 ]; then
    usage 1>&2
    exit 1
fi

readonly NAME=$1

if [[ ! ${NAME} =~ ^[a-zA-Z0-9_]+$ ]]; then
    usage 1>&2
    exit 1
fi

readonly SCRIPT_DIR=$(cd $(dirname $0); pwd)
cd ${SCRIPT_DIR}

source coverage_for_capture.env ${NAME}

mkdir -p ${OUTPUT_DIR}

lcov -c -d ${GC_FILE_DIR} -t ${NAME} -o ${LCOV_CAPTURE_FILE}
lcov -e ${LCOV_CAPTURE_FILE} */src/main/jni/* -o ${LCOV_TMP_FILTERED_FILE}
# lcov -r ${LCOV_TMP_FILTERED_FILE} */src/main/jni/FLException.h */src/main/jni/com_sony_fl_jni_*.cpp */nlohmann/* */lstm_lcr_binary_nnabla_1.25.0/* -o ${LCOV_FILTERED_FILE}
lcov -r ${LCOV_TMP_FILTERED_FILE} */nlohmann/* */lstm_lcr_binary_nnabla_1.25.0/* -o ${LCOV_FILTERED_FILE}

bash ${SCRIPT_DIR}/reset_coverage_data.sh
rm -f ${LCOV_CAPTURE_FILE} ${LCOV_TMP_FILTERED_FILE}

exit 0


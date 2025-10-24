#!/bin/bash
set -eu

# Usage: bash visualize_coverage.sh

readonly SCRIPT_DIR=$(cd $(dirname $0); pwd)
cd ${SCRIPT_DIR}

source coverage.env

readonly LATEST_GCNO=$(ls -t $(find ${GC_FILE_DIR} -name '*.gcno') | head -1)
echo "Latest: $(ls --full-time ${LATEST_GCNO})"
readonly TRACE_FILES=$(find ${OUTPUT_DIR} -name ${FILTERED_PREFIX}_*.info -newer ${LATEST_GCNO})

rm -rf ${LCOV_HTML_DIR}
genhtml -o ${LCOV_HTML_DIR} -num-spaces 4 -s --legend ${TRACE_FILES}

exit 0


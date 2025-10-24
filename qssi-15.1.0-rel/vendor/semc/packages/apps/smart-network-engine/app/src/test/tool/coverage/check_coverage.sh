#!/bin/bash

usage() {
    cat <<EOL
Usage: bash check_coverage.sh TRACE_FILE COVERAGE_RATE_MIN
       e.g. bash src/test/tool/coverage/check_coverage.sh src/test/logs/trace_files/lcovFiltered_gtest.info 90.0

  TRACE_FILE:           Trace file output by capture_coverage_data.sh
  COVERAGE_RATE_MIN:    Real numbers between 0.0 to 100.0 to one decimal place.
                        Exit with a status of 1 if the total line
                        coverage is less than COVERAGE_RATE_MIN.

EOL
}

set -u

if [ $# -ne 2 ]; then
    usage 1>&2
    exit 1
fi

TRACE_FILE=$1
COVERAGE_RATE=$2

lcov --summary ${TRACE_FILE} --fail-under-lines ${COVERAGE_RATE}
EXIT_CODE=$?
if [ ${EXIT_CODE} -eq 1 ]; then
    echo " fail under lines coverage: ${COVERAGE_RATE}%" 1>&2
    exit $EXIT_CODE
fi

exit 0


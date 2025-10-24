#!/bin/bash

# Usage: bash reset_coverage_data.sh

set -eu

readonly SCRIPT_DIR=$(cd $(dirname $0); pwd)
cd ${SCRIPT_DIR}

source coverage.env

lcov -z -d ${GC_FILE_DIR}

exit 0


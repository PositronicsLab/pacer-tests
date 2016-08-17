#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source ${PACER_BINARY_PATH}/setup.sh
# clean up worksapce
git clean -dfx .
# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh *.in

$@ -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 model.xml


#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source ${PACER_BINARY_PATH}/setup.sh
# clean up worksapce
git clean -dfx .
# re-parse '.in' files
../setup-tests.sh *.in

$@ -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 model.xml > out.log


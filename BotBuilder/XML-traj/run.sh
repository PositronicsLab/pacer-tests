#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source ${PACER_BINARY_PATH}/setup.sh
# clean up worksapce
git clean -dfx .
# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh *.in

 ${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration .4 --stepsize 0.0001 --sample 1 --controlled --display --kinematic


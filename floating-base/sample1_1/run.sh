#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

source ${BUILD_PATH}/Pacer/setup.sh

# clean up worksapce
git clean -dfx .

# re-parse '.in' files
../../setup-tests.sh ./*.in

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --display --no-pipe --stand --duration 1.5 --stepsize 0.00001


popd

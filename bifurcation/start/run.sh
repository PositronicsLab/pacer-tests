#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

source ${BUILD_PATH}/Pacer/setup.sh

# clean up worksapce
git clean -dfx . ../sample*

# re-parse '.in' files
../../setup-tests.sh ../start/*.in ../sample*/*.in

$1 -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 -r model.xml

popd

#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

source ${BUILD_PATH}/Pacer/setup.sh

# clean up worksapce
git clean -dfx ../start ../sample*

# re-parse '.in' files
../../setup-tests.sh ../start/*.in ../sample*/*.in

lldb -- moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 -r avg-model/model.xml

popd

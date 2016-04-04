#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

# clean up worksapce
git clean -dfx ../start ../sample*

# re-parse '.in' files
../../setup-tests.sh ../start/*.in ../sample*/*.in

moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -r -s=0.000000000001 model.xml

popd

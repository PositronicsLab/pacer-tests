#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

# clean up worksapce
git clean -dfx ../start ../sample

# re-parse '.in' files
../../setup-tests.sh ../start/*.in ../sample/*.in

${PACER_INTERFACE_PATH}/pacer-driver --stepsize 0.000000000001 $@

popd

#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .

# set up workspace
cd ${DIR}
  # clean up worksapce
  git clean -dfx .
  # re-parse '.in' files
  ./setup-tests.sh */*.in
popd

${PACER_INTERFACE_PATH}/pacer-driver $@ 


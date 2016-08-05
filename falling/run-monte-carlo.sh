#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

# clean up worksapce
git clean -dfx ..

# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh ../*/*.in

#if [ "$(uname)" == "Darwin" ]; then
  sudo -E nice -n -20 ${PACER_INTERFACE_PATH}/pacer-driver $@
  #nice -n 0 ${PACER_INTERFACE_PATH}/pacer-driver $@
#elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
#  sudo -E nice -n -20 ${PACER_INTERFACE_PATH}/pacer-driver $@
#fi

popd

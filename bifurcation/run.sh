#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
  # clean up worksapce
  git clean -dfx ${DIR}
  # re-parse '.in' files
  ${PACER_SCRIPT_PATH}/setup-tests.sh ${DIR}/*/*.in

moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so $@ model.xml 


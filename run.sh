#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
  # clean up worksapce
  git clean -dfx ${DIR}
  # re-parse '.in' files
  ${DIR}/setup-tests.sh ${DIR}/*/*.in

${PACER_INTERFACE_PATH}/pacer-driver $@ 


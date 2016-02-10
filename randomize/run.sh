#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
  # clean up worksapce
  git clean -dfx .
  # re-parse '.in' files
  ${PACER_SCRIPT_PATH}/setup-tests.sh *.in ../standing/*.in

  moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 -r model.xml


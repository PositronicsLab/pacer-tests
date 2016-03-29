#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
  # clean up worksapce
  git clean -dfx .
  # re-parse '.in' files
  ../setup-tests.sh *.in

  moby-driver -p=${PACER_BINARY_PATH}/Plugin/Component/inverse-dynamics/libTestPlugin.so -s=0.001 -r -mt=3 model.xml




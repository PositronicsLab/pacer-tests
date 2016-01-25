#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

# clean up worksapce
git clean -dfx ..

# re-parse '.in' files
../setup-tests.sh ../*/*.in

#while [1]; do
#  COUNTER=(ps -e | grep "[p]acer-driver" | wc -l)
#  if [ $COUNTER -lt 1 ]
    ${PACER_INTERFACE_PATH}/pacer-driver $@ 
#  fi
#  sleep(10);
#done

popd

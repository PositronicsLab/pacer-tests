#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .

# set up workspace
cd ${DIR}

# clean up worksapce
git clean -dfx .

# re-parse '.in' files
../setup-tests.sh *.in

#combine sim and robot files
../place-robot.sh $1

moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 -r model.xml

popd



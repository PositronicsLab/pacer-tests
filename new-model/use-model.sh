#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .

# set up workspace
cd ${DIR}

# clean up worksapce
git clean -dfx .

# re-parse '.in' files
./setup-tests.sh *.in

#combine sim and robot files
../randomize/place-robot.sh $1

${PACER_INTERFACE_PATH}/pacer-driver --display --stepsize 0.001 --duration 2

popd



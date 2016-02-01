#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

# clean up worksapce
#git clean -dfx ../start $@

# re-parse '.in' files
../../setup-tests.sh ../*/*.in

for i in $@
do
  sed -i.bak "s#>.*</task-directory>#>$i</task-directory>#g" plugins.xml
  screen -d -m ${PACER_INTERFACE_PATH}/pacer-driver --stepsize 0.000000000001
  sleep 10s
done

popd

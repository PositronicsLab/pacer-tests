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
  screen -d -m moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.0005 -r -oi model.xml
  sleep 10s
done

popd

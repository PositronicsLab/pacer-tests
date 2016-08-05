#!/bin/bash
source ${BUILD_PATH}/Pacer/setup.sh
# clean up worksapce
  
git clean -dfx .. 

# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh ./*.in ../sample/*.in

sed -i.bak "s#>.*</task-directory>#>$@</task-directory>#g" plugins.xml
for i in $@
do
  cp -r ../sample ../sample-$i
  sed -i.bak "s#>.*</switch-at-time>#>$i</switch-at-time>#g" ../sample-$i/plugins.xml
done
  screen -d -m -L ../../../BUILD/Moby/moby-driver -r -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 model.xml

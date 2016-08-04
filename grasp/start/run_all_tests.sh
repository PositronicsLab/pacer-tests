#!/bin/bash
source ${BUILD_PATH}/Pacer/setup.sh
# clean up worksapce
  
git clean -dfx . 

# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh ./*.in

for i in $@
do
  git clean -dfx $i
  ${PACER_SCRIPT_PATH}/setup-tests.sh $i/*.in
  sed -i.bak "s#>.*</task-directory>#>$i</task-directory>#g" plugins.xml
  #screen -d -m -L ./run.sh
  screen -d -m -L ../../../BUILD/Moby/moby-driver -r -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 model.xml
  #sleep 10s
done

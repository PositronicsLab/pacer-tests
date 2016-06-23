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
  screen -d -m -L ./run.sh $1  
  sleep 10s
done

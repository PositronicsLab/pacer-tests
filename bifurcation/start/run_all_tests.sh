#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

# clean up worksapce
git clean -dfx ../start

# re-parse '.in' files
${PACER_SCRIPTS_PATH}/setup-tests.sh ../*.in

for i in $@
do
  sed -i.bak "s#>.*</task-directory>#>$i</task-directory>#g" plugins.xml
  ./run.sh $1  
  sleep 10s
done

popd

#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .

# set up workspace
cd ${DIR}
popd

for $i in $@
do
  cp model.xml
done

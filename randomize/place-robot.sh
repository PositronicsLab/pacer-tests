#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# set up workspace
for i in $@
do
  NAME=`basename $i .xml`
  cat ${DIR}/model-sim.xml > $NAME-sim.xml
  cat $i >> $NAME-sim.xml
  sed -i.bak 's#<XML >##g' $NAME-sim.xml
  sed -i.bak 's#<Moby >##g' $NAME-sim.xml
  sed -i.bak 's#</Moby>#</MOBY>#g' $NAME-sim.xml
done

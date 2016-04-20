#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
NAME=`basename $1 .xml`
cat ${DIR}/sim-ground-model.xml > $NAME-sim.xml

sed -i.bak 's#<XML >##g' $1
sed -i.bak 's#<Moby >##g' $1
sed -i.bak 's#</Moby>#</MOBY>#g' $1

cat $1 >> $NAME-sim.xml

cat $NAME-sim.xml > model.xml
mkdir /home/brad/Desktop/$NAME-sim

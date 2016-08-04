#!/bin/bash
cd $BUILDER_CAPT_PATH
NAME=`basename $1 .xml`
cat $BUILDER_CAPT_PATH/sim-ground-model.xml > $NAME-sim.xml

sed -i.bak 's#<XML >##g' $1
sed -i.bak 's#<Moby >##g' $1
sed -i.bak 's#</Moby>#</MOBY>#g' $1

cat $1 >> $NAME-sim.xml

cat $NAME-sim.xml > model.xml
cp model.xml $BUILDER_XML_PATH/model.xml

echo "----------------------------place-robot.sh---------------------------------"  >> /home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt
   echo "modelNo: "$modelNo"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "max_vel: "$max_vel"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "delta_v: "$delta_v"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "curr_vel: "$curr_vel"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "unit_len: "$unit_len"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "unit_den: "$unit_den"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "unit_rad: "$unit_rad"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "test_dur: "$test_dur"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "curr_line: "$curr_line"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "curr_iter: "$curr_iter"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"

   echo "lenF1: "$lenF1"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "lenF2: "$lenF2"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "lenH1: "$lenH1"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "lenH2: "$lenH2"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "base_size_length: "$base_size_length"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "base_size_width: "$base_size_width"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "base_size_height: "$base_size_height"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "density: "$density"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "linkRad: "$linkRad"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "footRad: "$footRad"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "footLen: "$footLen"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"
   echo "KINEMATIC: "$KINEMATIC"" >> "/home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt"

$BUILDER_SCRIPT_PATH/moveOld.sh

if [ "$KINEMATIC"=true ] ; then
	$BUILDER_CAPT_PATH/run.sh
fi
	#. $BUILDER_SCRIPT_PATH/setup-plugins-play.sh *.play


#!/bin/bash
#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off
cd $BUILDER_XML_PATH
${PACER_SCRIPT_PATH}/setup-tests.sh $BUILDER_XML_PATH/*.in

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 0 --stepsize 0.001 --xml --sample 1 \
 --BODY0.density  $density --BODY0.size $base_size_length  $base_size_width  $base_size_height \
 --LF_FOOT.density $density --LF_FOOT.foot.radius $footRad --LF_FOOT.length $footLen --LF_FOOT.radius $linkRad \
 --LF_LEG_1.density  $density --LF_LEG_1.length $lenF1 --LF_LEG_1.radius $linkRad \
 --LF_LEG_2.density $density --LF_LEG_2.length $lenF2 --LF_LEG_2.radius $linkRad \
 --LH_FOOT.density $density --LH_FOOT.foot.radius $footRad --LH_FOOT.length $footLen --LH_FOOT.radius $linkRad \
 --LH_LEG_1.density $density --LH_LEG_1.length $lenH1 --LH_LEG_1.radius $linkRad \
 --LH_LEG_2.density $density --LH_LEG_2.length $lenH2 --LH_LEG_2.radius $linkRad \
 --RF_FOOT.density $density --RF_FOOT.foot.radius $footRad --RF_FOOT.length $footLen --RF_FOOT.radius $linkRad \
 --RF_LEG_1.density $density --RF_LEG_1.length $lenF1 --RF_LEG_1.radius $linkRad \
 --RF_LEG_2.density $density --RF_LEG_2.length $lenF2 --RF_LEG_2.radius $linkRad \
 --RH_FOOT.density $density --RH_FOOT.foot.radius $footRad --RH_FOOT.length $footLen --RH_FOOT.radius $linkRad \
 --RH_LEG_1.density $density --RH_LEG_1.length $lenH1 --RH_LEG_1.radius $linkRad \
 --RH_LEG_2.density $density --RH_LEG_2.length $lenH2 --RH_LEG_2.radius $linkRad \
 --LF_X_1.axis  1 0 0 --LF_Y_2.axis 0  1 0 --LF_Y_3.axis 0  1 0 \
 --RF_X_1.axis -1 0 0 --RF_Y_2.axis 0 -1 0 --RF_Y_3.axis 0 -1 0 \
 --LH_X_1.axis -1 0 0 --LH_Y_2.axis 0  1 0 --LH_Y_3.axis 0  1 0 \
 --RH_X_1.axis 1 0 0 --RH_Y_2.axis 0 -1 0 --RH_Y_3.axis 0 -1 0

echo "----------------------------generate.sh---------------------------------"  >> /home/brad/Desktop/Tests/pacer-tests/BotBuilder/FrontEnd/debug.txt
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

$BUILDER_SCRIPT_PATH/clean-dir.sh
$BUILDER_SCRIPT_PATH/place-robot.sh model-*.xml

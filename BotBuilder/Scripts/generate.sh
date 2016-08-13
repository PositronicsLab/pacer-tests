#!/bin/bash
#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off
cd $BUILDER_XML_PATH

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 0 --moby s=0.001 model-gen.xml --xml --sample 1 \
 --BODY0.density  $density --BODY0.size $base_size_length  $base_size_width  $base_size_height \
 --LF_FOOT.density $density --LF_FOOT.foot.radius $FfootRad --LF_FOOT.length $FfootLen --LF_FOOT.radius $FlinkRad \
 --LF_LEG_1.density  $density --LF_LEG_1.length $lenF1 --LF_LEG_1.radius $FlinkRad \
 --LF_LEG_2.density $density --LF_LEG_2.length $lenF2 --LF_LEG_2.radius $FlinkRad \
 --LH_FOOT.density $density --LH_FOOT.foot.radius $HfootRad --LH_FOOT.length $HfootLen --LH_FOOT.radius $HlinkRad \
 --LH_LEG_1.density $density --LH_LEG_1.length $lenH1 --LH_LEG_1.radius $HlinkRad \
 --LH_LEG_2.density $density --LH_LEG_2.length $lenH2 --LH_LEG_2.radius $HlinkRad \
 --RF_FOOT.density $density --RF_FOOT.foot.radius $FfootRad --RF_FOOT.length $FfootLen --RF_FOOT.radius $FlinkRad \
 --RF_LEG_1.density $density --RF_LEG_1.length $lenF1 --RF_LEG_1.radius $FlinkRad \
 --RF_LEG_2.density $density --RF_LEG_2.length $lenF2 --RF_LEG_2.radius $FlinkRad \
 --RH_FOOT.density $density --RH_FOOT.foot.radius $HfootRad --RH_FOOT.length $HfootLen --RH_FOOT.radius $HlinkRad \
 --RH_LEG_1.density $density --RH_LEG_1.length $lenH1 --RH_LEG_1.radius $HlinkRad \
 --RH_LEG_2.density $density --RH_LEG_2.length $lenH2 --RH_LEG_2.radius $HlinkRad \
 --LF_X_1.axis 1 0 0 --LF_X_1.tare 0 --LF_Y_2.axis 0 1 0 --LF_Y_2.tare 0 --LF_Y_3.axis 0 1 0 --LF_Y_3.tare 0 --LH_X_1.axis -1 0 0 --LH_X_1.tare 0 --LH_Y_2.axis 0 1 0 --LH_Y_2.tare 0 --LH_Y_3.axis 0 1 0 --LH_Y_3.tare 0 --RF_X_1.axis 1 0 0 --RF_X_1.tare 0 --RF_Y_2.axis 0 -1 0 --RF_Y_2.tare 0 --RF_Y_3.axis 0 -1 0 --RF_Y_3.tare 0 --RH_X_1.axis -1 0 0 --RH_X_1.tare 0 --RH_Y_2.axis 0 -1 0 --RH_Y_2.tare 0 --RH_Y_3.axis 0 -1 0 --RH_Y_3.tare 0

cd $BUILDER_CAPT_PATH
$BUILDER_CAPT_PATH/run.sh
echo "----------------------------generate.sh---------------------------------"  >> /tmp/debug.txt
   echo "modelNo: "$modelNo"" >> "/tmp/debug.txt"
   echo "max_vel: "$max_vel"" >> "/tmp/debug.txt"
   echo "delta_v: "$delta_v"" >> "/tmp/debug.txt"
   echo "curr_vel: "$curr_vel"" >> "/tmp/debug.txt"
   echo "unit_len: "$unit_len"" >> "/tmp/debug.txt"
   echo "unit_den: "$unit_den"" >> "/tmp/debug.txt"
   echo "unit_rad: "$unit_rad"" >> "/tmp/debug.txt"
   echo "test_dur: "$test_dur"" >> "/tmp/debug.txt"
   echo "curr_line: "$curr_line"" >> "/tmp/debug.txt"
   echo "curr_iter: "$curr_iter"" >> "/tmp/debug.txt"

   echo "lenF1: "$lenF1"" >> "/tmp/debug.txt"
   echo "lenF2: "$lenF2"" >> "/tmp/debug.txt"
   echo "lenH1: "$lenH1"" >> "/tmp/debug.txt"
   echo "lenH2: "$lenH2"" >> "/tmp/debug.txt"
   echo "base_size_length: "$base_size_length"" >> "/tmp/debug.txt"
   echo "base_size_width: "$base_size_width"" >> "/tmp/debug.txt"
   echo "base_size_height: "$base_size_height"" >> "/tmp/debug.txt"
   echo "density: "$density"" >> "/tmp/debug.txt"
   echo "linkRad: "$linkRad"" >> "/tmp/debug.txt"
   echo "footRad: "$footRad"" >> "/tmp/debug.txt"
   echo "footLen: "$footLen"" >> "/tmp/debug.txt"
   echo "KINEMATIC: "$KINEMATIC"" >> "/tmp/debug.txt"

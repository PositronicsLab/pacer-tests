#!/bin/bash
#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off
#after the model is generated, the proper camera position is inserted into the XML files
#and disabled pairs added for all adjacent links so that the simulation doesn't immediately crash, 
#the next step takes place in the run.sh file in the Kinematics directory
cd $BUILDER_SCRIPT_PATH
./clean-dir.sh
cd $BUILDER_XML_PATH

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 0 --moby s=0.001 model-gen.xml --xml --sample 1 \
 --BODY0.mass  $massBase --BODY0.size $base_size_length  $base_size_width  $base_size_height \
 --LF_FOOT.mass $massF3 --LF_FOOT.foot.radius $FfootRad --LF_FOOT.length $FfootLen --LF_FOOT.radius $FlinkRad \
 --LF_LEG_1.mass  $massF1 --LF_LEG_1.length $lenF1 --LF_LEG_1.radius $FlinkRad \
 --LF_LEG_2.mass $massF2 --LF_LEG_2.length $lenF2 --LF_LEG_2.radius $FlinkRad \
 --LH_FOOT.mass $massH3 --LH_FOOT.foot.radius $HfootRad --LH_FOOT.length $HfootLen --LH_FOOT.radius $HlinkRad \
 --LH_LEG_1.mass $massH1 --LH_LEG_1.length $lenH1 --LH_LEG_1.radius $HlinkRad \
 --LH_LEG_2.mass $massH2 --LH_LEG_2.length $lenH2 --LH_LEG_2.radius $HlinkRad \
 --RF_FOOT.mass $massF3 --RF_FOOT.foot.radius $FfootRad --RF_FOOT.length $FfootLen --RF_FOOT.radius $FlinkRad \
 --RF_LEG_1.mass $massF1 --RF_LEG_1.length $lenF1 --RF_LEG_1.radius $FlinkRad \
 --RF_LEG_2.mass $massF2 --RF_LEG_2.length $lenF2 --RF_LEG_2.radius $FlinkRad \
 --RH_FOOT.mass $massH3 --RH_FOOT.foot.radius $HfootRad --RH_FOOT.length $HfootLen --RH_FOOT.radius $HlinkRad \
 --RH_LEG_1.mass $massH1 --RH_LEG_1.length $lenH1 --RH_LEG_1.radius $HlinkRad \
 --RH_LEG_2.mass $massH2 --RH_LEG_2.length $lenH2 --RH_LEG_2.radius $HlinkRad \
 --LF_X_1.axis 1 0 0 --LF_X_1.tare 0 --LF_Y_2.axis 0 1 0 --LF_Y_2.tare 0 --LF_Y_3.axis 0 1 0 --LF_Y_3.tare 0 --LH_X_1.axis -1 0 0 --LH_X_1.tare 0 --LH_Y_2.axis 0 1 0 --LH_Y_2.tare 0 --LH_Y_3.axis 0 1 0 --LH_Y_3.tare 0 --RF_X_1.axis 1 0 0 --RF_X_1.tare 0 --RF_Y_2.axis 0 -1 0 --RF_Y_2.tare 0 --RF_Y_3.axis 0 -1 0 --RF_Y_3.tare 0 --RH_X_1.axis -1 0 0 --RH_X_1.tare 0 --RH_Y_2.axis 0 -1 0 --RH_Y_2.tare 0 --RH_Y_3.axis 0 -1 0 --RH_Y_3.tare 0

sed -i '2i<DRIVER>\n<camera position="0.35 -0.55 0.5" target="0 0 0" up="0 0 1" />\n<window location="0 0" size="640 480" />\n</DRIVER>' ./model-1.xml

sed -i '143i<DisabledPair object1-id="BODY0_collision" object2-id="LF_1_collision" />' ./model-1.xml
sed -i '144i    <DisabledPair object1-id="LF_3_collision" object2-id="LF_FOOT_collision" />' ./model-1.xml
sed -i '145i   <DisabledPair object1-id="LF_2_collision" object2-id="LF_3_collision" />' ./model-1.xml
sed -i '146i   <DisabledPair object1-id="LF_1_collision" object2-id="LF_2_collision" />' ./model-1.xml
sed -i '147i    <DisabledPair object1-id="BODY0_collision" object2-id="RH_1_collision" />' ./model-1.xml
sed -i '148i    <DisabledPair object1-id="RF_3_collision" object2-id="RF_FOOT_collision" />' ./model-1.xml
sed -i '149i   <DisabledPair object1-id="RF_2_collision" object2-id="RF_3_collision" />' ./model-1.xml
sed -i '150i    <DisabledPair object1-id="RF_1_collision" object2-id="RF_2_collision" />' ./model-1.xml
sed -i '151i    <DisabledPair object1-id="BODY0_collision" object2-id="LH_1_collision" />' ./model-1.xml
sed -i '152i    <DisabledPair object1-id="LH_3_collision" object2-id="LH_FOOT_collision" />' ./model-1.xml
sed -i '153i   <DisabledPair object1-id="LH_2_collision" object2-id="LH_3_collision" />' ./model-1.xml
sed -i '154i    <DisabledPair object1-id="LH_1_collision" object2-id="LH_2_collision" />' ./model-1.xml
sed -i '155i    <DisabledPair object1-id="BODY0_collision" object2-id="RH_1_collision" />' ./model-1.xml
sed -i '156i    <DisabledPair object1-id="RH_3_collision" object2-id="RH_FOOT_collision" />' ./model-1.xml
sed -i '157i   <DisabledPair object1-id="RH_2_collision" object2-id="RH_3_collision" />' ./model-1.xml
sed -i '158i    <DisabledPair object1-id="RH_1_collision" object2-id="RH_2_collision" />' ./model-1.xml


export curr_vel=0


cd $BUILDER_CAPT_PATH
$BUILDER_CAPT_PATH/run.sh


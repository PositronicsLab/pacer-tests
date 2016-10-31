#!/bin/bash
#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off
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
cd $BUILDER_CAPT_PATH
cp -f $BUILDER_XML_PATH/model-1.xml ./
cp -f $BUILDER_XML_PATH/vizdata_*.osg ./

sed -i.bak "/\b\(RecurrentForce\)\b/d" ./model-1.xml
sed -i.bak '/dynamic-body-id="GROUND"/d' ./model-1.xml
#sed -i '8i<ImplicitConstraint joint-id="fixed-base" />' ./model-1.xml
#sed -i '95i<FixedJoint id="fixed-base" inboard-link-id="GROUND" outboard-link-id="BODY0" location="0 0 0" />' ./model-1.xml
shutter -d 0 -a -o $BUILDER_GUI_PATH/model-1.png -e &
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration .1 --sample 1 --moby r s=0.001 p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so model-1.xml
wait

convert $BUILDER_GUI_PATH/model-1.png -resize 200x200 $BUILDER_GUI_PATH/model-1.png

export curr_vel=0


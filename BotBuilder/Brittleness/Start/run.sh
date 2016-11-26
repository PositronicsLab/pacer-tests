#is 100000000 in debug, but set to 1 right now so I can get to the editor
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 1 --moby s=0.001 $BUILDER_XML_PATH/model-gen.xml --xml --sample 1 \
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

$BUILDER_GUI_PATH/editor

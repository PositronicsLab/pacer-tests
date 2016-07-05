#!/bin/bash
#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 0 --stepsize 0.001 --xml --sample 1 \
  --BODY0.density $density --BODY0.size $base_size_length $base_size_width $base_size_height \
  --LF_FOOT.density $density --LF_FOOT.foot.radius 0.01 --LF_FOOT.length 0.1 --LF_FOOT.radius 0.01 \
  --LF_LEG_1.density $density --LF_LEG_1.length $lenF1 --LF_LEG_1.radius 0.01 \
  --LF_LEG_2.density $density --LF_LEG_2.length $lenF2 --LF_LEG_2.radius 0.01 \
  --LH_FOOT.density $density --LH_FOOT.foot.radius 0.01 --LH_FOOT.length 0.1 --LH_FOOT.radius 0.01 \
  --LH_LEG_1.density $density --LH_LEG_1.length $lenH1 --LH_LEG_1.radius 0.01 \
  --LH_LEG_2.density $density --LH_LEG_2.length $lenH2 --LH_LEG_2.radius 0.01 \
  --RF_FOOT.density $density --RF_FOOT.foot.radius 0.01 --RF_FOOT.length 0.1 --RF_FOOT.radius 0.01 \
  --RF_LEG_1.density $density --RF_LEG_1.length $lenF1 --RF_LEG_1.radius 0.01 \
  --RF_LEG_2.density $density --RF_LEG_2.length $lenF2 --RF_LEG_2.radius 0.01 \
  --RH_FOOT.density $density --RH_FOOT.foot.radius 0.01 --RH_FOOT.length 0.1 --RH_FOOT.radius 0.01 \
  --RH_LEG_1.density $density --RH_LEG_1.length $lenH1 --RH_LEG_1.radius 0.01 \
  --RH_LEG_2.density $density --RH_LEG_2.length $lenH2 --RH_LEG_2.radius 0.01 \
  --LF_X_1.axis  1 0 0 --LF_Y_2.axis 0  1 0 --LF_Y_3.axis 0  1 0 \
  --RF_X_1.axis -1 0 0 --RF_Y_2.axis 0 -1 0 --RF_Y_3.axis 0 -1 0 \
  --LH_X_1.axis -1 0 0 --LH_Y_2.axis 0  1 0 --LH_Y_3.axis 0  1 0 \
  --RH_X_1.axis 1 0 0 --RH_Y_2.axis 0 -1 0 --RH_Y_3.axis 0 -1 0

./place-robot.sh model-*.xml

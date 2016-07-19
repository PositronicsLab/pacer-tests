#!/bin/bash
#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off


${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 0 --stepsize 0.001 --xml --sample 1 \
 --BODY0.density  echo $density --BODY0.size  echo $base_size_length  echo $base_size_width  echo $base_size_height \
 --LF_FOOT.density echo $density --LF_FOOT.foot.radius echo $footRad --LF_FOOT.length echo $footLen --LF_FOOT.radius echo $linkRad \
 --LF_LEG_1.density  echo $density --LF_LEG_1.length echo $lenF1 --LF_LEG_1.radius echo $linkRad \
 --LF_LEG_2.density echo $density --LF_LEG_2.length echo $lenF2 --LF_LEG_2.radius echo $linkRad \
 --LH_FOOT.density echo $density --LH_FOOT.foot.radius echo $footRad --LH_FOOT.length echo $footLen --LH_FOOT.radius echo $linkRad \
 --LH_LEG_1.density echo $density --LH_LEG_1.length echo $lenH1 --LH_LEG_1.radius echo $linkRad \
 --LH_LEG_2.density echo $density --LH_LEG_2.length echo $lenH2 --LH_LEG_2.radius echo $linkRad \
 --RF_FOOT.density echo $density --RF_FOOT.foot.radius echo $footRad --RF_FOOT.length echo $footLen --RF_FOOT.radius echo $linkRad \
 --RF_LEG_1.density echo $density --RF_LEG_1.length echo $lenF1 --RF_LEG_1.radius echo $linkRad \
 --RF_LEG_2.density echo $density --RF_LEG_2.length echo $lenF2 --RF_LEG_2.radius echo $linkRad \
 --RH_FOOT.density echo $density --RH_FOOT.foot.radius echo $footRad --RH_FOOT.length echo $footLen --RH_FOOT.radius echo $linkRad \
 --RH_LEG_1.density echo $density --RH_LEG_1.length echo $lenH1 --RH_LEG_1.radius echo $linkRad \
 --RH_LEG_2.density echo $density --RH_LEG_2.length echo $lenH2 --RH_LEG_2.radius echo $linkRad \
 --LF_X_1.axis  1 0 0 --LF_Y_2.axis 0  1 0 --LF_Y_3.axis 0  1 0 \
 --RF_X_1.axis -1 0 0 --RF_Y_2.axis 0 -1 0 --RF_Y_3.axis 0 -1 0 \
 --LH_X_1.axis -1 0 0 --LH_Y_2.axis 0  1 0 --LH_Y_3.axis 0  1 0 \
 --RH_X_1.axis 1 0 0 --RH_Y_2.axis 0 -1 0 --RH_Y_3.axis 0 -1 0

#source clean-dir.sh
#source orderFiles.sh
#source place-robot.sh model-*.xml

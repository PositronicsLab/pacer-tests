#!/bin/bash
# clean up worksapce
git clean -dfx $1

# re-parse '.in' files
${PACER_SCRIPTS_PATH}/setup-tests.sh $1/*.in

screen -d -m -L ${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --display --no-pipe --sample -1 --duration 100 --stepsize 0.001 \
--BODY0.density 1656 --BODY0.size 0.15 0.08 0.05 --LF_FOOT.density 900 --LF_FOOT.foot.radius 0.01 --LF_FOOT.length 0.1 --LF_FOOT.radius 0.011 --LF_LEG_1.density 900 --LF_LEG_1.length 0.025 --LF_LEG_1.radius 0.011 --LF_LEG_2.density 900 --LF_LEG_2.length 0.077 --LF_LEG_2.radius 0.011 --LF_X_1.axis 1 0 0 --LF_Y_2.axis 0 1 0 --LF_Y_3.axis 0 1 0 --LH_FOOT.density 900 --LH_FOOT.foot.radius 0.01 --LH_FOOT.length 0.1 --LH_FOOT.radius 0.011 --LH_LEG_1.density 900 --LH_LEG_1.length 0.025 --LH_LEG_1.radius 0.011 --LH_LEG_2.density 900 --LH_LEG_2.length 0.077 --LH_LEG_2.radius 0.011 --LH_X_1.axis -1 0 0 --LH_Y_2.axis 0 1 0 --LH_Y_3.axis 0 1 0 --RF_FOOT.density 900 --RF_FOOT.foot.radius 0.01 --RF_FOOT.length 0.1 --RF_FOOT.radius 0.011 --RF_LEG_1.density 900 --RF_LEG_1.length 0.025 --RF_LEG_1.radius 0.011 --RF_LEG_2.density 900 --RF_LEG_2.length 0.077 --RF_LEG_2.radius 0.011 --RF_X_1.axis 1 0 0 --RF_Y_2.axis 0 -1 0 --RF_Y_3.axis 0 -1 0 --RH_FOOT.density 900 --RH_FOOT.foot.radius 0.011 --RH_FOOT.length 0.1 --RH_FOOT.radius 0.011 --RH_LEG_1.density 900 --RH_LEG_1.length 0.025 --RH_LEG_1.radius 0.011 --RH_LEG_2.density 900 --RH_LEG_2.length 0.077 --RH_LEG_2.radius 0.011 --RH_X_1.axis -1 0 0 --RH_Y_2.axis 0 -1 0 --RH_Y_3.axis 0 -1 0 


#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

#take in the value provided from master.sh to use as the initial pose
#eval `grep "^export " master.sh`
#poseNum=$i
read poseNum
#open the text file that contains the initial value of the robot's pose row, as well as setting the initial current pose to one row after it as the first position to move to.
INITFILE="initLine.txt"
echo $poseNum > $INITFILE

#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 0 --stepsize 0.001 --xml --sample 1 \
--BODY0.density 1756 --BODY0.size 0.149779 0.0791471 0.0498981  \
--LF_FOOT.density 1100 --LF_FOOT.foot.radius 0.01 --LF_FOOT.length 0.1 --LF_FOOT.radius 0.01 \
--LF_LEG_1.density 1056 --LF_LEG_1.length 0.021 --LF_LEG_1.radius 0.01 --LF_LEG_2.density 1200 --LF_LEG_2.length 0.076 --LF_LEG_2.radius 0.01  \
--LF_X_1.axis 1 0 0 --LF_X_1.x 0.0988703 --LF_X_1.xd 0.00146895  --LF_Y_2.axis 0 1 0 --LF_Y_2.x 0.793081 --LF_Y_2.xd 0.172063 --LF_Y_3.axis 0 1 0 --LF_Y_3.x 1.21112 --LF_Y_3.xd 0.102675 \
--LH_FOOT.density 1543 --LH_FOOT.foot.radius 0.01 --LH_FOOT.length 0.1 --LH_FOOT.radius 0.01 \
--LH_LEG_1.density 1067 --LH_LEG_1.length 0.021 --LH_LEG_1.radius 0.01 \
--LH_LEG_2.density 1021 --LH_LEG_2.length 0.076 --LH_LEG_2.radius 0.01 \
--LH_X_1.axis -1 0 0 --LH_X_1.x -0.0981617 --LH_X_1.xd 0.00515529 \
--LH_Y_2.axis 0 1 0 --LH_Y_2.x -0.795781 --LH_Y_2.xd 0.094515 \
--LH_Y_3.axis 0 1 0 --LH_Y_3.x -1.21137 --LH_Y_3.xd 0.220795 \
--RF_FOOT.density 987 --RF_FOOT.foot.radius 0.01 --RF_FOOT.length 0.1 --RF_FOOT.radius 0.01 \
--RF_LEG_1.density 1345 --RF_LEG_1.length 0.021 --RF_LEG_1.radius 0.01 \
--RF_LEG_2.density 1673 --RF_LEG_2.length 0.076 --RF_LEG_2.radius 0.01 \
--RF_X_1.axis 1 0 0 --RF_X_1.x -0.0997554 --RF_X_1.xd -0.00148376 \
--RF_Y_2.axis 0 -1 0 --RF_Y_2.x -0.789939 --RF_Y_2.xd -0.171485 \
--RF_Y_3.axis 0 -1 0 --RF_Y_3.x -1.21117 --RF_Y_3.xd -0.102463 \
--RH_FOOT.density 1465 --RH_FOOT.foot.radius 0.01 --RH_FOOT.length 0.1 --RH_FOOT.radius 0.01 \
--RH_LEG_1.density 1203 --RH_LEG_1.length 0.021 --RH_LEG_1.radius 0.01 \
--RH_LEG_2.density 1146 --RH_LEG_2.length 0.076 --RH_LEG_2.radius 0.01 \
--RH_X_1.axis -1 0 0 --RH_X_1.x 0.0986269 --RH_X_1.xd -0.00513831 \
--RH_Y_2.axis 0 -1 0 --RH_Y_2.x 0.794019 --RH_Y_2.xd -0.0949643 \
--RH_Y_3.axis 0 -1 0 --RH_Y_3.x 1.21452 --RH_Y_3.xd -0.219797 \


popd

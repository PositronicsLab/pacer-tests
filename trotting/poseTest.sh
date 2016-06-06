#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}




#take in the value provided from master.sh to use as the initial pose
#eval `grep "^export " master.sh`
#poseNum=$i
read poseNum
#open the text file that contains the initial value of the robot's pose row, as well as setting the initial current pose to one row after it as the first position to move to.
INITFILE="/home/brad/Desktop/Poses/initLine.txt"
echo $poseNum > $INITFILE
CURRFILE="/home/brad/Desktop/Poses/currLine.txt"
echo $(expr $poseNum + 1) > $CURRFILE
FILE="/home/brad/Desktop/Poses/PoseSet.txt"

#grab the initial row of values to use for the initial state of the robot
myLine=$(sed -n "${poseNum}"p "${FILE}")
myLineDelim=(${myLine//" ":/ })

#grab each of the values from the row, and put them in their corresponding variables. This order of variables is mantained in all files(LF to RF to LH to RH to Body values)
LF_foot_x_x=${myLineDelim[0]}
LF_foot_x_y=${myLineDelim[1]}
LF_foot_x_z=${myLineDelim[2]}
LF_foot_xd_x=${myLineDelim[3]}
LF_foot_xd_y=${myLineDelim[4]}
LF_foot_xd_z=${myLineDelim[5]}
LF_foot_xdd_x=${myLineDelim[6]}
LF_foot_xdd_y=${myLineDelim[7]}
LF_foot_xdd_z=${myLineDelim[8]}
RF_foot_x_x=${myLineDelim[9]}
RF_foot_x_y=${myLineDelim[10]}
RF_foot_x_z=${myLineDelim[11]}
RF_foot_xd_x=${myLineDelim[12]}
RF_foot_xd_y=${myLineDelim[13]}
RF_foot_xd_z=${myLineDelim[14]}
RF_foot_xdd_x=${myLineDelim[15]}
RF_foot_xdd_y=${myLineDelim[16]}
RF_foot_xdd_z=${myLineDelim[17]}
LH_foot_x_x=${myLineDelim[18]}
LH_foot_x_y=${myLineDelim[19]}
LH_foot_x_z=${myLineDelim[20]}
LH_foot_xd_x=${myLineDelim[21]}
LH_foot_xd_y=${myLineDelim[22]}
LH_foot_xd_z=${myLineDelim[23]}
LH_foot_xdd_x=${myLineDelim[24]}
LH_foot_xdd_y=${myLineDelim[25]}
LH_foot_xdd_z=${myLineDelim[26]}
RH_foot_x_x=${myLineDelim[27]}
RH_foot_x_y=${myLineDelim[28]}
RH_foot_x_z=${myLineDelim[29]}
RH_foot_xd_x=${myLineDelim[30]}
RH_foot_xd_y=${myLineDelim[31]}
RH_foot_xd_z=${myLineDelim[32]}
RH_foot_xdd_x=${myLineDelim[33]}
RH_foot_xdd_y=${myLineDelim[34]}
RH_foot_xdd_z=${myLineDelim[35]}


Base_xd_0=${myLineDelim[36]}
Base_xd_1=${myLineDelim[37]}
Base_xd_2=${myLineDelim[38]}
Base_xd_3=${myLineDelim[39]}
Base_xd_4=${myLineDelim[40]}
Base_xd_5=${myLineDelim[41]}
Base_x_0=${myLineDelim[42]}
Base_x_1=${myLineDelim[43]}
Base_x_2=${myLineDelim[44]}
Base_x_3=${myLineDelim[45]}
Base_x_4=${myLineDelim[46]}
Base_x_5=${myLineDelim[47]}


#generate a model with the Monte-Carlo simulation with the provided initial x/xd/xdd values
#as only the xml file is needed, the duration is set to zero and Moby control is off
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 0 --stepsize 0.001 --xml --sample 1 \
--BODY0.x $Base_x_0 $Base_x_1 $Base_x_2 $Base_x_3 $Base_x_4 $Base_x_5 --BODY0.xd $Base_xd_0 $Base_xd_1 $Base_xd_2 $Base_xd_3 $Base_xd_4 $Base_xd_5 \
--LF_FOOT.x $LF_foot_x_x $LF_foot_x_y $LF_foot_x_z --LF_FOOT.xd $LF_foot_xd_x $LF_foot_xd_y $LF_foot_xd_z --LF_FOOT.xdd $LF_foot_xdd_x $LF_foot_xdd_y $LF_foot_xdd_z \
--RF_FOOT.x $RF_foot_x_x $RF_foot_x_y $RF_foot_x_z --RF_FOOT.xd $RF_foot_xd_x $RF_foot_xd_y $RF_foot_xd_z --RF_FOOT.xdd $RF_foot_xdd_x $RF_foot_xdd_y $RF_foot_xdd_z \
--LH_FOOT.x $LH_foot_x_x $LH_foot_x_y $LH_foot_x_z --LH_FOOT.xd $LH_foot_xd_x $LH_foot_xd_y $LH_foot_xd_z --LH_FOOT.xdd $LH_foot_xdd_x $LH_foot_xdd_y $LH_foot_xdd_z \
--RH_FOOT.x $RH_foot_x_x $RH_foot_x_y $RH_foot_x_z --RH_FOOT.xd $RH_foot_xd_x $RH_foot_xd_y $RH_foot_xd_z --RH_FOOT.xdd $RH_foot_xdd_x $RH_foot_xdd_y $RH_foot_xdd_z \
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

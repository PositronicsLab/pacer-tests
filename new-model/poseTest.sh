#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

source /home/brad/Project/Pacer/debug/setup.sh

# clean up worksapce


# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh ./*.in

poseNum=$LINENUM
FILE="/home/brad/Desktop/Poses/PoseSet.txt"
myLine=$(sed -n "${poseNum}"p "${FILE}")
myLineDelim=(${myLine//" ":/ })
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

Base_x_0=${myLineDelim[36]}
Base_x_1=${myLineDelim[37]}
Base_x_2=${myLineDelim[38]}
Base_x_3=${myLineDelim[39]}
Base_x_4=${myLineDelim[40]}
Base_x_5=${myLineDelim[41]}
Base_xd_0=${myLineDelim[42]}
Base_xd_1=${myLineDelim[43]}
Base_xd_2=${myLineDelim[44]}
Base_xd_3=${myLineDelim[45]}
Base_xd_4=${myLineDelim[46]}
Base_xd_5=${myLineDelim[47]}


${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --display --no-pipe --duration 2 --stepsize 0.0005 --sample 1 \
--BODY0.x $Base_x_0 $Base_x_1 $Base_x_2 $Base_x_3 $Base_x_4 $Base_x_5 --BODY0.xd $Base_xd_0 $Base_xd_1 $Base_xd_2 $Base_xd_3 $Base_xd_4 $Base_xd_5 \
--LF_FOOT.init.x $LF_foot_x_x $LF_foot_x_y $LF_foot_x_z --LF_FOOT.init.xd $LF_foot_xd_x $LF_foot_xd_y $LF_foot_xd_z --LF_FOOT.init.xdd $LF_foot_xdd_x $LF_foot_xdd_y $LF_foot_xdd_z \
--RF_FOOT.init.x $RF_foot_x_x $RF_foot_x_y $RF_foot_x_z --RF_FOOT.init.xd $RF_foot_xd_x $RF_foot_xd_y $RF_foot_xd_z --RF_FOOT.init.xdd $RF_foot_xdd_x $RF_foot_xdd_y $RF_foot_xdd_z \
--LH_FOOT.init.x $LH_foot_x_x $LH_foot_x_y $LH_foot_x_z --LH_FOOT.init.xd $LH_foot_xd_x $LH_foot_xd_y $LH_foot_xd_z --LH_FOOT.init.xdd $LH_foot_xdd_x $LH_foot_xdd_y $LH_foot_xdd_z \
--RH_FOOT.init.x $RH_foot_x_x $RH_foot_x_y $RH_foot_x_z --RH_FOOT.init.xd $RH_foot_xd_x $RH_foot_xd_y $RH_foot_xd_z --RH_FOOT.init.xdd $RH_foot_xdd_x $RH_foot_xdd_y $RH_foot_xdd_z \
--BODY0.density 1720.77 --BODY0.size 0.149779 0.0791471 0.0498981  \
--LF_FOOT.density 638.108 --LF_FOOT.foot.radius 0.01 --LF_FOOT.length 0.0942234 --LF_FOOT.radius 0.0107021 \
--LF_LEG_1.density 1199.49 --LF_LEG_1.length 0.0291514 --LF_LEG_1.radius 0.0115869 --LF_LEG_2.density 869.759 --LF_LEG_2.length 0.0661153 --LF_LEG_2.radius 0.011036  \
--LF_X_1.axis 1 -0.013102 0.013827  --LF_Y_2.axis -0.00330005 1 0.00735038 --LF_Y_2.x 0.793081 --LF_Y_2.xd 0.172063 --LF_Y_3.axis 0.0171256 1 0.00914213 --LF_Y_3.x 1.21112 --LF_Y_3.xd 0.102675 \
--LH_FOOT.density 868.428 --LH_FOOT.foot.radius 0.01 --LH_FOOT.length 0.096718 --LH_FOOT.radius 0.0111776 \
--LH_LEG_1.density 1176.65 --LH_LEG_1.length 0.0248453 --LH_LEG_1.radius 0.010858 \
--LH_LEG_2.density 808.977 --LH_LEG_2.length 0.0754472 --LH_LEG_2.radius 0.0107125 \
--LH_X_1.axis -1 -0.0020049 -0.00742805 --LH_X_1.x -0.0981617 --LH_X_1.xd 0.00515529 \
--LH_Y_2.axis -0.00770934 1 -0.00730208 --LH_Y_2.x -0.795781 --LH_Y_2.xd 0.094515 \
--LH_Y_3.axis -0.00172075 1 -0.010179 --LH_Y_3.x -1.21137 --LH_Y_3.xd 0.220795 \
--RF_FOOT.density 734.373 --RF_FOOT.foot.radius 0.01 --RF_FOOT.length 0.0942827 --RF_FOOT.radius 0.0104688 \
--RF_LEG_1.density 1194.84 --RF_LEG_1.length 0.0292645 --RF_LEG_1.radius 0.0101914 \
--RF_LEG_2.density 835.701 --RF_LEG_2.length 0.071642 --RF_LEG_2.radius 0.0107272 \
--RF_X_1.axis 1 -0.0015683 -0.0232766 --RF_X_1.x -0.0997554 --RF_X_1.xd -0.00148376 \
--RF_Y_2.axis -0.0035855 -1 0.0149623 --RF_Y_2.x -0.789939 --RF_Y_2.xd -0.171485 \
--RF_Y_3.axis 0.0120097 -1 -0.0134498 --RF_Y_3.x -1.21117 --RF_Y_3.xd -0.102463 \
--RH_FOOT.density 925.481 --RH_FOOT.foot.radius 0.0110724 --RH_FOOT.length 0.0965104 --RH_FOOT.radius 0.0104704 \
--RH_LEG_1.density 1118.19 --RH_LEG_1.length 0.0243536 --RH_LEG_1.radius 0.010714 \
--RH_LEG_2.density 1030.22 --RH_LEG_2.length 0.0774137 --RH_LEG_2.radius 0.0104042 \
--RH_X_1.axis -1 -0.00196631 -0.002974 --RH_X_1.x 0.0986269 --RH_X_1.xd -0.00513831 \
 --RH_Y_2.axis -0.0116071 -1 0.0163512 --RH_Y_2.x 0.794019 --RH_Y_2.xd -0.0949643 \
--RH_Y_3.axis 0.00255361 -1 0.00230788 --RH_Y_3.x 1.21452 --RH_Y_3.xd -0.219797 \


popd

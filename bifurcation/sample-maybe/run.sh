#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}

source ${BUILD_PATH}/Pacer/setup.sh

# clean up worksapce
git clean -dfx .

# re-parse '.in' files
../../setup-tests.sh ./*.in

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --display --no-pipe --xml \
 --BODY0.density 1720.77 --BODY0.size 0.149779 0.0791471 0.0498981 --BODY0.x 0.00290244 -1.11723e-06 0.160398 3.87869e-06 0.00335032 2.07803e-06 --BODY0.xd 0.0453753 2.28621e-06 0.00264101 -2.01424e-06 0.0442503 1.34312e-06 --LF_FOOT.density 638.108 --LF_FOOT.foot.radius 0.01 --LF_FOOT.length 0.0942234 --LF_FOOT.radius 0.0107021 --LF_LEG_1.density 1199.49 --LF_LEG_1.length 0.0291514 --LF_LEG_1.radius 0.0115869 --LF_LEG_2.density 869.759 --LF_LEG_2.length 0.0661153 --LF_LEG_2.radius 0.011036 --LF_X_1.axis 1 -0.013102 0.013827 --LF_X_1.x 0.0988703 --LF_X_1.xd 0.00146895 --LF_Y_2.axis -0.00330005 1 0.00735038 --LF_Y_2.x 0.793081 --LF_Y_2.xd 0.172063 --LF_Y_3.axis 0.0171256 1 0.00914213 --LF_Y_3.x 1.21112 --LF_Y_3.xd 0.102675 --LH_FOOT.density 868.428 --LH_FOOT.foot.radius 0.01 --LH_FOOT.length 0.096718 --LH_FOOT.radius 0.0111776 --LH_LEG_1.density 1176.65 --LH_LEG_1.length 0.0248453 --LH_LEG_1.radius 0.010858 --LH_LEG_2.density 808.977 --LH_LEG_2.length 0.0754472 --LH_LEG_2.radius 0.0107125 --LH_X_1.axis -1 -0.0020049 -0.00742805 --LH_X_1.x -0.0981617 --LH_X_1.xd 0.00515529 --LH_Y_2.axis -0.00770934 1 -0.00730208 --LH_Y_2.x -0.795781 --LH_Y_2.xd 0.094515 --LH_Y_3.axis -0.00172075 1 -0.010179 --LH_Y_3.x -1.21137 --LH_Y_3.xd 0.220795 --RF_FOOT.density 734.373 --RF_FOOT.foot.radius 0.01 --RF_FOOT.length 0.0942827 --RF_FOOT.radius 0.0104688 --RF_LEG_1.density 1194.84 --RF_LEG_1.length 0.0292645 --RF_LEG_1.radius 0.0101914 --RF_LEG_2.density 835.701 --RF_LEG_2.length 0.071642 --RF_LEG_2.radius 0.0107272 --RF_X_1.axis 1 -0.0015683 -0.0232766 --RF_X_1.x -0.0997554 --RF_X_1.xd -0.00148376 --RF_Y_2.axis -0.0035855 -1 0.0149623 --RF_Y_2.x -0.789939 --RF_Y_2.xd -0.171485 --RF_Y_3.axis 0.0120097 -1 -0.0134498 --RF_Y_3.x -1.21117 --RF_Y_3.xd -0.102463 --RH_FOOT.density 925.481 --RH_FOOT.foot.radius 0.0110724 --RH_FOOT.length 0.0965104 --RH_FOOT.radius 0.0104704 --RH_LEG_1.density 1118.19 --RH_LEG_1.length 0.0243536 --RH_LEG_1.radius 0.010714 --RH_LEG_2.density 1030.22 --RH_LEG_2.length 0.0774137 --RH_LEG_2.radius 0.0104042 --RH_X_1.axis -1 -0.00196631 -0.002974 --RH_X_1.x 0.0986269 --RH_X_1.xd -0.00513831 --RH_Y_2.axis -0.0116071 -1 0.0163512 --RH_Y_2.x 0.794019 --RH_Y_2.xd -0.0949643 --RH_Y_3.axis 0.00255361 -1 0.00230788 --RH_Y_3.x 1.21452 --RH_Y_3.xd -0.219797 --sample 1 --duration 2 --stepsize 0.0005

popd

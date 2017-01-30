#!/bin/bash
#begins the simulations
#can be ran from anywhere
#the environment variables exported here can be changed except for curr_line and curr_iter
#unit_ values are the values by which each variable can be incremented by
#the velocity values affect the speed of the tests
export POSE_PATH=$2
export max_vel=0.5
export delta_v=0.1
export curr_vel=0
export unit_len=0.001
export unit_den=0.001
export unit_rad=0.001
export test_dur=5     #sliding window length
export curr_line=0
export curr_iter=0


${PACER_SCRIPT_PATH}/setup-tests.sh *.in;

cp $1 ./;

line1=$(awk 'NR==1' $2)
arr=($(echo ${line1}))
echo "${line1}"
echo "${arr}"
echo "${arr[1]}"
sed -i "16s/\(<q type=\"double\">\)\([^<]*\)\(<[^>]*\)/\1"${arr[0]}" "${arr[3]}" "${arr[6]}" "${arr[9]}" "${arr[12]}" "${arr[15]}" "${arr[18]}" "${arr[21]}" "${arr[24]}" "${arr[27]}" "${arr[30]}" "${arr[33]}"\3/" vars.xml
sed -i "17s/\(<qd type=\"double\">\)\([^<]*\)\(<[^>]*\)/\1"${arr[1]}" "${arr[4]}" "${arr[7]}" "${arr[10]}" "${arr[13]}" "${arr[16]}" "${arr[19]}" "${arr[22]}" "${arr[25]}" "${arr[28]}" "${arr[31]}" "${arr[34]}"\3/" vars.xml
sed -i "11s/\(<xd type=\"double\">\)\([^<]*\)\(<[^>]*\)/\1"${arr[36]}" "${arr[37]}" "${arr[38]}" "${arr[39]}" "${arr[40]}" "${arr[41]}"\3/" vars.xml

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 100000000 --moby r s=0.001 p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so model-1.xml --sample 1 --stand


#!/bin/bash
#begins the simulations
#can be ran from anywhere
#the environment variables exported here can be changed except for curr_line and curr_iter
#unit_ values are the values by which each variable can be incremented by
#the velocity values affect the speed of the tests
export name=big_init
export max_vel=0.5
export delta_v=0.1
export curr_vel=0
export unit_len=0.001
export unit_den=0.001
export unit_rad=0.001
export test_dur=5     #sliding window length
export curr_line=0
export curr_iter=0

export POSE_PATH=/home/brad/Desktop/pacer-tests/BotBuilder/PoseSets

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 100000000 --moby r s=0.001 p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so model-1.xml --sample 1 --stand


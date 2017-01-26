#!/bin/bash
#begins the simulations
#can be ran from anywhere
#the environment variables exported here can be changed except for curr_line and curr_iter
#unit_ values are the values by which each variable can be incremented by
#the velocity values affect the speed of the tests
export modelNo=1
export max_vel=0
export delta_v=0
export curr_vel=0
export unit_len=0.001
export unit_den=0.001
export unit_rad=0.001
export test_dur=5      #sliding window length
export curr_line=0
export curr_iter=0
cd $BUILDER_HOME_PATH
> matlabData.txt
$BUILDER_SCRIPT_PATH/init.sh


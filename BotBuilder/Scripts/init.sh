#!/bin/bash
source /home/brad/Project/Pacer/debug/setup.sh
cd $BUILDER_CAPT_PATH
$BUILDER_SCRIPT_PATH/clean-dir.sh

export lenF1=.05
export lenF2=.1

export lenH1=.05
export lenH2=.1

export base_size_length=.15
export base_size_width=.08
export base_size_height=.05

export density=1200

export linkRad=0.01
export footRad=0.01
export footLen=0.1

export KINEMATIC="true"


echo "----------------------------init.sh---------------------------------"  >> "/tmp/debug.txt"
   echo "modelNo: "$modelNo"" >> "/tmp/debug.txt"
   echo "max_vel: "$max_vel"" >> "/tmp/debug.txt"
   echo "delta_v: "$delta_v"" >> "/tmp/debug.txt"
   echo "curr_vel: "$curr_vel"" >> "/tmp/debug.txt"
   echo "unit_len: "$unit_len"" >> "/tmp/debug.txt"
   echo "unit_den: "$unit_den"" >> "/tmp/debug.txt"
   echo "unit_rad: "$unit_rad"" >> "/tmp/debug.txt"
   echo "test_dur: "$test_dur"" >> "/tmp/debug.txt"
   echo "curr_line: "$curr_line"" >> "/tmp/debug.txt"
   echo "curr_iter: "$curr_iter"" >> "/tmp/debug.txt"

   echo "lenF1: "$lenF1"" >> "/tmp/debug.txt"
   echo "lenF2: "$lenF2"" >> "/tmp/debug.txt"
   echo "lenH1: "$lenH1"" >> "/tmp/debug.txt"
   echo "lenH2: "$lenH2"" >> "/tmp/debug.txt"
   echo "base_size_length: "$base_size_length"" >> "/tmp/debug.txt"
   echo "base_size_width: "$base_size_width"" >> "/tmp/debug.txt"
   echo "base_size_height: "$base_size_height"" >> "/tmp/debug.txt"
   echo "density: "$density"" >> "/tmp/debug.txt"
   echo "linkRad: "$linkRad"" >> "/tmp/debug.txt"
   echo "footRad: "$footRad"" >> "/tmp/debug.txt"
   echo "footLen: "$footLen"" >> "/tmp/debug.txt"
   echo "KINEMATIC: "$KINEMATIC"" >> "/tmp/debug.txt"

$BUILDER_SCRIPT_PATH/generate.sh
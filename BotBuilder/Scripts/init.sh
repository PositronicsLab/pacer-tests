#!/bin/bash
source /home/brad/Project/Pacer/debug/setup.sh
${PACER_SCRIPT_PATH}/setup-tests.sh *.in

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

source generate.sh

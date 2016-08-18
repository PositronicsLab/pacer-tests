#!/bin/bash
source ${PACER_BINARY_PATH}/setup.sh
cd $BUILDER_XML_PATH
$BUILDER_SCRIPT_PATH/clean-dir.sh
$PACER_SCRIPT_PATH/setup-tests.sh $BUILDER_CAPT_PATH/*.in
$PACER_SCRIPT_PATH/setup-tests.sh $BUILDER_XML_PATH/*.in

export lenF1=0.019
export lenF2=.02

export lenH1=0.019
export lenH2=0.02

export base_size_length=.15
export base_size_width=.15
export base_size_height=.15

export density=1200

export FlinkRad=0.01
export FfootRad=0.01
export FfootLen=0.02

export HlinkRad=0.01
export HfootRad=0.01
export HfootLen=0.02

export KINEMATIC="true"

export jac_count=0

$BUILDER_SCRIPT_PATH/generate.sh

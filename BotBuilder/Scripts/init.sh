#!/bin/bash
source ${PACER_BINARY_PATH}/setup.sh
cd $BUILDER_XML_PATH
$BUILDER_SCRIPT_PATH/clean-dir.sh
$PACER_SCRIPT_PATH/setup-tests.sh $BUILDER_CAPT_PATH/*.in
$PACER_SCRIPT_PATH/setup-tests.sh $BUILDER_XML_PATH/*.in
$PACER_SCRIPT_PATH/setup-tests.sh $BUILDER_BIF_PATH/sample/*.in
$PACER_SCRIPT_PATH/setup-tests.sh $BUILDER_BIF_PATH/Start/*.in

export lenF1=0.05
export lenF2=0.05
export FfootLen=0.05

export lenH1=0.05
export lenH2=0.05
export HfootLen=0.05

export base_size_length=0.053
export base_size_width=0.05
export base_size_height=0.05

export FlinkRad=0.025
export HlinkRad=0.025

export massF1=0.05
export massF2=0.05
export massF3=0.07

export massH1=0.05
export massH2=0.05
export massH3=0.07

export massBase=0.09

export FfootRad=0.025
export HfootRad=0.025

export KINEMATIC="true"

export jac_count=0

$BUILDER_SCRIPT_PATH/generate.sh

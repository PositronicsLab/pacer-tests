#!/bin/bash
git clean -dxf $BUILDER_HOME_PATH/XML $BUILDER_HOME_PATH/XML-traj $BUILDER_HOME_PATH/PoseSets
cd $BUILDER_XML_PATH
$PACER_SCRIPT_PATH/setup-tests.sh *.in
cd $BUILDER_CAPT_PATH
$PACER_SCRIPT_PATH/setup-tests.sh *.in



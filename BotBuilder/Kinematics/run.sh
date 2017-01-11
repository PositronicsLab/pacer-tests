#!/bin/bash
#runs the kinematic poseSet generation through the plugins goForward and poseListener
#poseListener just records the current positions/velocities/accelerations of the joints and body
#while goForward determines the speed and is responsible for calling the next process
#which is setup-plugins-play.sh
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

cp -f $BUILDER_XML_PATH/model-1.xml ./
cp -f $BUILDER_XML_PATH/vizdata_*.osg ./

sed -i.bak "/\b\(RecurrentForce\)\b/d" ./model-1.xml
sed -i.bak '/dynamic-body-id="GROUND"/d' ./model-1.xml
#sed -i '8i<ImplicitConstraint joint-id="fixed-base" />' ./model-1.xml
#sed -i '95i<FixedJoint id="fixed-base" inboard-link-id="GROUND" outboard-link-id="BODY0" location="0 0 0" />' ./model-1.xml

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --kinematic --duration 100 --sample 1 --moby r s=0.001 p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so model-1.xml


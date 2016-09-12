#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

cp -f $BUILDER_XML_PATH/model-1.xml ./
sed -i.bak "/\b\(RecurrentForce\)\b/d" ./model-1.xml


${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --float --duration 100 --sample 1 --moby s=0.001 p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so model-1.xml


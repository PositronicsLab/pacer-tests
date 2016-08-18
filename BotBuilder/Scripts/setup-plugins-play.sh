#!/bin/bash
cd $BUILDER_XML_PATH
   $BUILDER_SCRIPT_PATH/setInitVals.sh
 
	${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration .4 --moby s=0.001 p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so $BUILDER_XML_PATH/model-1.xml --sample 1 --stand
        





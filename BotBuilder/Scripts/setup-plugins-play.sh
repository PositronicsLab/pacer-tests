#!/bin/bash
#This is the actual limit testing
#there are two important plugins being used here error-check-builder and trajectory-table
#trajectory table just reads the poseSet files and applies the positions/velocities/accelerations from
#the current line to the model while error-check builder searches for limit errors and self-collision errors
#it is error-check-builder that governs what happens at the end of this step, which will either go to the Brittleness/sample/run.sh file
#or to the editor GUI in the FrontEnd directory
cd $BUILDER_XML_PATH
   $BUILDER_SCRIPT_PATH/setInitVals.sh
 
	${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration .4 --moby r s=0.001 p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so $BUILDER_XML_PATH/model-1.xml --sample 1 --stand
        





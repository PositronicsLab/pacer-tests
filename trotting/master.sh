 #!/bin/bash
#source ${PACER_BINARY_PATH}/setup.sh

#${PACER_SCRIPT_PATH}/setup-tests.sh /home/brad/Desktop/Poses/*.in
#${PACER_SCRIPT_PATH}/setup-tests.sh *.in
#./setup-plugins.sh *.play


# generate the model we're using
 for i in `seq 1 402`;
        do
                export i
                 ./poseTest.sh
                  for f in model-*.xml
                  do
	              ./place-robot.sh $f
                  done
                
                moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 -r model.xml
                rm model-*.xml.bak
                rm model-*.xml
                rm *.osg
                rm *.log
        done   
 









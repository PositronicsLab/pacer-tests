./place-robot.sh $1
moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.0005 -r model.xml

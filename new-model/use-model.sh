./place-robot.sh $1
moby-driver -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=.001 -r model.xml
exit $?

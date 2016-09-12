#!/bin/bash
if [[ $# -ne 3 ]] ; then \
  echo "2 arguments are needed, run: ${BASH_SOURCE[0]} <path/to/moby-driver> <path/to/robot/model.xml> <running velocity>"; \
  exit
fi

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
ABS_PATH=$( cd "$( dirname "$2" )" && pwd )
ROBOT_NAME=$( basename "$2" )

echo "Using robot: $ROBOT_NAME at path: $ABS_PATH ($2)"
echo "Running at speed: $3"

source ${PACER_BINARY_PATH}/setup.sh

# clean up worksapce
git clean -dfx .

# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh *.in

sed -i.bak "s#>.*</max-forward-speed>#>$3</max-forward-speed>#g" plugins.xml
sed -i.bak "s#>.*</robot-model>#>$ABS_PATH/$ROBOT_NAME</robot-model>#g" vars.xml
sed -i.bak "s#>.*</xd>#>$3 0 0.1 0 0 0</xd>#g" vars.xml

#$1 -r -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 "$ABS_PATH/$ROBOT_NAME"
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 5 --stand --sample 1 --moby -r p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so s=0.0005 r y=osg v=100 "$ABS_PATH/$ROBOT_NAME"


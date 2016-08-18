#!/bin/bash
if [[ $# -ne 2 ]] ; then \
  echo "2 arguments are needed, run: ${BASH_SOURCE[0]} <path/to/moby-driver> <path/to/robot/model.xml>"; \
  exit
fi

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
ABS_PATH=$( cd "$( dirname "$2" )" && pwd )
ROBOT_NAME=$( basename "$2" )

echo "Using robot: $ROBOT_NAME at path: $ABS_PATH ($2)"

source ${PACER_BINARY_PATH}/setup.sh

# clean up worksapce
git clean -dfx .

# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh *.in

sed -i.bak "s#>.*</robot-model>#>$ABS_PATH/$ROBOT_NAME</robot-model>#g" vars.xml

$1 -r -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 "$ABS_PATH/$ROBOT_NAME"


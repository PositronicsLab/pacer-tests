#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

 ${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --no-pipe --duration 100 --sample 1 --kinematic


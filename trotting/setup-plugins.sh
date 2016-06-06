#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
for var in "$@"
do
# remove .play from name
  newvar=$(echo $var | sed 's#\(.*\)\.play#\1#' )
# create new file
  cp -f $var $newvar
# replace environment vars
  sed -E -i.bak "s#\@\@PACER_MODEL_PATH\@\@#${PACER_MODEL_PATH}#g" $newvar
  sed -E -i.bak "s#\@\@TESTING_ROBOT\@\@#${TESTING_ROBOT}#g" $newvar
done

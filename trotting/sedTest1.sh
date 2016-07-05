#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
value=$(/home/brad/Desktop/Tests/pacer-tests/trotting/model.xml.in)
return=$( echo $value | sed -n 's:.*<SDF filename="\(.*\)"/>.*:\1:g')
echo $return
sed -i "s:$return:model.sdf:p" $value

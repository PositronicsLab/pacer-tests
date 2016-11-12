#!/bin/bash
sed -i.bak "s#>.*</gait-duration>#>$1</gait-duration>#g" ../sample-$1/plugins.xml


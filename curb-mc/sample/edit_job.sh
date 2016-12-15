#!/bin/bash
sed -i.bak "s#>.*</step-height>#>$1</step-height>#g" ../sample-$1/plugins.xml


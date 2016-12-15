#!/bin/bash
sed -i.bak "s#>.*</plan>#>$1</plan>#g" ../sample-$1/plugins.xml


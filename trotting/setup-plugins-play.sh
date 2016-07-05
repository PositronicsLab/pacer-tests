#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
for file in *.play; do
    mv -- "$file" "${file%%.play}"
done

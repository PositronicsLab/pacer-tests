#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
for file in *.capt; do
    mv -- "$file" "${file%%.capt}"
done

#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
currFileNum=1
for i in `ls -v model-*.xml`; do 
        d=$(ls $i | sed -e 's/[^0-9]//g') 
        x=$(cat matlabData.txt | wc -l)
        
	if [ ${d} > ${x} ]; then
             mv "$i" "`echo $i | sed "s/$d/$currFileNum/"`";
        fi
        
	currFileNum=$((currFileNum+1))
done;

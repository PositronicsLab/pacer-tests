#!/bin/bash
for i in `ls -v model-1*.xml`; 
do 
       mv $i $BUILDER_HOME_PATH/Old 
	
done


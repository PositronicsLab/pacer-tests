#!/bin/sh

for i in *-sim.xml 
do
	filename="${i%.*}"
	echo $filename
	mv $i /home/brad/Desktop/$filename/
	mv /home/brad/Desktop/Tests/Testing2.txt /home/brad/Desktop/$filename/
	mv /home/brad/Desktop/Tests/Testing3.txt /home/brad/Desktop/$filename/
	mv /home/brad/Desktop/Tests/Testing4.txt /home/brad/Desktop/$filename/
	mv /home/brad/Desktop/Tests/pacer-tests/new-model/matlabData.txt /home/brad/Desktop/$filename/
	
	touch matlabData.txt;
	touch Testing2.txt;
	touch Testing3.txt;
	touch Testing4.txt;
done


#!/bin/sh

while :
do
./run.sh
			for i in *-sim.xml 
			do
				filename="${i%.*}"
				echo $filename
			done
	if [$? == 0]
		then
		
		var = cat /home/brad/Desktop/Tests/pacer-tests/new-model/Testing2.txt
		
		var2 = cat /home/brad/Desktop/Tests/pacer-tests/new-model/Testing4.txt
		./move-files.sh
		
		else
		./move-files.sh
		mv /home/brad/Desktop/$filename/ /home/brad/Desktop/Error
	fi

		if [var2/var <= 10]
		then	
				
				mv /home/brad/Desktop/$filename/ /home/brad/Desktop/Success
		else
			
				
				mv /home/brad/Desktop/$filename/ /home/brad/Desktop/Failure
		fi

git clean -dxf .;
	
done

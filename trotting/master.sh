 #!/bin/bash
endLength=$(cat /home/brad/Desktop/Poses/PoseSet.txt | wc -l) 
for i in `seq 1 $endLength`;
        do
                export LINENUM=$i
                ./poseTest.sh 
        done    



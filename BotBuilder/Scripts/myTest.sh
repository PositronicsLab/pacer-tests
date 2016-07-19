for i in `ls -v model-*-sim.xml`; 
do 
        if [ ${i//[^0-9]/} -lt $modelNo ] ; then mv $i ./Old 
	fi
done

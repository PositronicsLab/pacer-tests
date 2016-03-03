git clean -dxf . ;
../setup-tests.sh *.in ;

RANGE=0
DECRANGE=100
frontFootRad1=$RANDOM
let "frontFootRad1=$RANGE*$frontFootRad1/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
frontFootRad1=$frontFootRad1.0$decimalVal
frontFootLen=$RANDOM
let "frontFootLen=$RANGE*$frontFootLen/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
frontFootLen=$frontFootLen.0$decimalVal
frontFootRad2=$RANDOM
let "frontFootRad2=$RANGE*$frontFootRad2/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
frontFootRad2=$frontFootRad2.0$decimalVal
frontLink1Rad=$RANDOM
let "frontLink1Rad=$RANGE*$frontLink1Rad/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
frontLink1Rad=$frontLink1Rad.0$decimalVal
frontLink1Len=$RANDOM
let "frontLink1Len=$RANGE*$frontLink1Len/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
frontLink1Len=$frontLink1Len.0$decimalVal
frontLink2Rad=$RANDOM
let "frontLink2Rad=$RANGE*$frontLink2Rad/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
frontLink2Rad=$frontLink2Rad.0$decimalVal
frontLink2Len=$RANDOM
let "frontLink2Len=$RANGE*$frontLink2Len/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
frontLink2Len=$frontLink2Len.0$decimalVal
hindFootRad1=$RANDOM
let "hindFootRad1=$RANGE*$hindFootRad1/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
hindFootRad1=$hindFootRad1.0$decimalVal
hindFootLen=$RANDOM
let "hindFootLen=$RANGE*$hindFootLen/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
hindFootLen=$hindFootLen.0$decimalVal
hindFootRad2=$RANDOM
let "hindFootRad2=$RANGE*$hindFootRad2/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
hindFootRad2=$hindFootRad2.0$decimalVal
hindLink1Rad=$RANDOM
let "hindLink1Rad=$RANGE*$hindLink1Rad/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
hindLink1Rad=$hindLink1Rad.0$decimalVal
hindLink1Len=$RANDOM
let "hindLink1Len=$RANGE*$hindLink1Len/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
hindLink1Len=$hindLink1Len.0$decimalVal
hindLink2Rad=$RANDOM
let "hindLink2Rad=$RANGE*$hindLink2Rad/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
hindLink2Rad=$hindLink2Rad.0$decimalVal
hindLink2Len=$RANDOM
let "hindLink2Len=$RANGE*$hindLink2Len/32768"
decimalVal=$RANDOM
let "decimalVal=$DECRANGE*$decimalVal/32768"
hindLink2Len=$hindLink2Len.0$decimalVal

echo "$frontFootRad1 $frontFootLen $frontFootRad2 $frontLink1Rad $frontLink1Len $frontLink2Rad $frontLink2Len $hindFootRad1 $hindFootLen $hindFootRad2 $hindLink1Rad $hindLink1Len $hindLink2Rad $hindLink2Len"  >> matlabData.txt;
echo " "  >> matlabData.txt;
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --duration 0 --xml --no-pipe --sample 1 \
  --BODY0.density 1956 \
  --LF_FOOT.density 1200 --LF_FOOT.foot.radius $frontFootRad1 --LF_FOOT.length $frontFootLen --LF_FOOT.radius $frontFootRad2 \
  --LF_LEG_1.density 1200 --LF_LEG_1.length $frontLink1Len --LF_LEG_1.radius $frontLink1Rad \
  --LF_LEG_2.density 1200 --LF_LEG_2.length $frontLink2Len --LF_LEG_2.radius $frontLink2Rad \
  --LH_FOOT.density 1200 --LH_FOOT.foot.radius $hindFootRad1 --LH_FOOT.length $hindFootLen --LH_FOOT.radius $hindFootRad2 \
  --LH_LEG_1.density 1200 --LH_LEG_1.length $hindLink1Len --LH_LEG_1.radius $hindLink1Rad \
  --LH_LEG_2.density 1200 --LH_LEG_2.length $hindLink2Len --LH_LEG_2.radius $hindLink2Rad \
  --RF_FOOT.density 1200 --RF_FOOT.foot.radius $frontFootRad1 --RF_FOOT.length $frontFootLen --RF_FOOT.radius $frontFootRad2 \
  --RF_LEG_1.density 1200 --RF_LEG_1.length $frontLink1Len --RF_LEG_1.radius $frontLink1Rad \
  --RF_LEG_2.density 1200 --RF_LEG_2.length $frontLink2Len --RF_LEG_2.radius $frontLink2Rad \
  --RH_FOOT.density 1200 --RH_FOOT.foot.radius $hindFootRad1 --RH_FOOT.length $hindFootLen --RH_FOOT.radius $hindFootRad2 \
  --RH_LEG_1.density 1200 --RH_LEG_1.length $hindLink1Len --RH_LEG_1.radius $hindLink1Rad \
  --RH_LEG_2.density 1200 --RH_LEG_2.length $hindLink2Len --RH_LEG_2.radius $hindLink2Rad --RH_X_1.x 1.5709 

./use-model.sh model-*.xml

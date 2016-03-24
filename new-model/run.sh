git clean -dxf . ;
../setup-tests.sh *.in ;

legMult=$(python -c "import random;print(random.uniform(0.1, .9))")
legMult=$(echo "scale=2;$legMult" | bc)

legFMult=$(python -c "import random;print(random.uniform(0.1, .9))")
legFMult=$(echo "scale=2;$legFMult" | bc)

legHMult=$(python -c "import random;print(random.uniform(0.1, .9))")
legHMult=$(echo "scale=2;$legHMult" | bc)

denseMult=$(python -c "import random;print(random.uniform(1, 6))")
denseMult=$(echo "scale=2;$denseMult" | bc)

lenTotal=.194
lenFTot=$(echo "scale=2;$lenTotal*$legMult" | bc)
lenHTot=$(echo "scale=2;$lenTotal-$lenFTot" | bc)

lenF1=$(echo "scale=2;$lenFTot*$legFMult" | bc)
lenF2=$(echo "scale=2;$lenFTot-$lenF1" | bc)

lenH1=$(echo "scale=2;$lenHTot*$legHMult" | bc)
lenH2=$(echo "scale=2;$lenHTot-$lenH1" | bc)

density=$(echo "scale=2;1000*$denseMult" | bc)


echo "$lenF1 $lenF2 $lenH1 $lenH2 $density"  >> matlabData.txt;
echo " "  >> matlabData.txt;

${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --duration 0 --xml --no-pipe --sample 1 \
   --BODY0.density $density \
  --LF_FOOT.density $density --LF_FOOT.foot.radius 0.01 --LF_FOOT.length 0.1 --LF_FOOT.radius 0.01 \
  --LF_LEG_1.density $density --LF_LEG_1.length $lenF1 --LF_LEG_1.radius 0.01 \
  --LF_LEG_2.density $density --LF_LEG_2.length $lenF2 --LF_LEG_2.radius 0.01 \
  --LH_FOOT.density $density --LH_FOOT.foot.radius 0.01 --LH_FOOT.length 0.1 --LH_FOOT.radius 0.01 \
  --LH_LEG_1.density $density --LH_LEG_1.length $lenH1 --LH_LEG_1.radius 0.01 \
  --LH_LEG_2.density $density --LH_LEG_2.length $lenH2 --LH_LEG_2.radius 0.01 \
  --RF_FOOT.density $density --RF_FOOT.foot.radius 0.01 --RF_FOOT.length 0.1 --RF_FOOT.radius 0.01 \
  --RF_LEG_1.density $density --RF_LEG_1.length $lenF1 --RF_LEG_1.radius 0.01 \
  --RF_LEG_2.density $density --RF_LEG_2.length $lenF2 --RF_LEG_2.radius 0.01 \
  --RH_FOOT.density $density --RH_FOOT.foot.radius 0.01 --RH_FOOT.length 0.1 --RH_FOOT.radius 0.01 \
  --RH_LEG_1.density $density --RH_LEG_1.length $lenH1 --RH_LEG_1.radius 0.01 \
  --RH_LEG_2.density $density --RH_LEG_2.length $lenH2 --RH_LEG_2.radius 0.01 --RH_X_1.x 1.5709 

./use-model.sh model-*.xml

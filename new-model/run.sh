git clean -dxf . ;
../setup-tests.sh *.in ;
${PACER_COMPONENT_PATH}/monte-carlo-simulation/sample.bin --duration 0 --xml --no-pipe --sample 1 \
  --BODY0.density 1956 \
  --LF_FOOT.density 1200 --LF_FOOT.foot.radius 0.01 --LF_FOOT.length 0.1 --LF_FOOT.radius 0.01 \
  --LF_LEG_1.density 1200 --LF_LEG_1.length 0.021 --LF_LEG_1.radius 0.01 \
  --LF_LEG_2.density 1200 --LF_LEG_2.length 0.076 --LF_LEG_2.radius 0.01 \
  --LH_FOOT.density 1200 --LH_FOOT.foot.radius 0.01 --LH_FOOT.length 0.1 --LH_FOOT.radius 0.01 \
  --LH_LEG_1.density 1200 --LH_LEG_1.length 0.021 --LH_LEG_1.radius 0.01 \
  --LH_LEG_2.density 1200 --LH_LEG_2.length 0.076 --LH_LEG_2.radius 0.01 \
  --RF_FOOT.density 1200 --RF_FOOT.foot.radius 0.01 --RF_FOOT.length 0.1 --RF_FOOT.radius 0.01 \
  --RF_LEG_1.density 1200 --RF_LEG_1.length 0.031 --RF_LEG_1.radius 0.01 \
  --RF_LEG_2.density 1200 --RF_LEG_2.length 0.076 --RF_LEG_2.radius 0.01 \
  --RH_FOOT.density 1200 --RH_FOOT.foot.radius 0.01 --RH_FOOT.length 0.1 --RH_FOOT.radius 0.01 \
  --RH_LEG_1.density 1200 --RH_LEG_1.length 0.021 --RH_LEG_1.radius 0.01 \
  --RH_LEG_2.density 1200 --RH_LEG_2.length 0.076 --RH_LEG_2.radius 0.01 --RH_X_1.x 1.5709

./use-model.sh model-*.xml

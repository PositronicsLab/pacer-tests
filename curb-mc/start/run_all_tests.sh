#!/bin/bash
source ${BUILD_PATH}/Pacer/setup.sh
# clean up worksapce
 
if [ "$#" -gt "0" ] 
then
git clean -dfx .. 

${PACER_SCRIPT_PATH}/setup-tests.sh ./*.in

# copy plugin directory for all jobs
ii=0
for i in $@
do
  ii=$((ii + 1))
  # copy generic job
  cp -r ../sample ../sample-$i
  pushd .
  cd ../sample-$i
  # re-parse '.in' files
  ${PACER_SCRIPT_PATH}/setup-tests.sh ./*.in
  sed -i.bak "s#>.*</file>#>monte-carlo-simulation/libmonte-carlo-simulation-${ii}.so</file>#g" ../sample-$i/monte-carlo.xml
  popd
done


# edit all jobs and include them in main controller
for i in $@
do
  # edit job details
  ../sample/edit_job.sh $i

  x=$[RANDOM % 256]
  red=$(bc <<<"scale=2;$x/256.0")
  y=$[RANDOM % 256]
  green=$(bc <<<"scale=2;$y/256.0")
  z=$[RANDOM % 256]
  blue=$(bc <<<"scale=2;$z/256.0")
  
  echo "sample-$i has color [$red $green $blue]"

  printf "\x1b[38;2;${x};${y};${z}mCOLOR\x1b[0m\n"

  sed -i.bak "s#>.*</color>#>$red $green $blue</color>#g" ../sample-$i/monte-carlo.xml
  
  # paste plugin job into plugin.xml
  # make sed tool for this job
  cat append-monte-carlo.xml | sed "s#monte-carlo-name.xml#../sample-$i/monte-carlo.xml#g" > edit-plugin.sh
  chmod +x edit-plugin.sh
  # append to second-to-last line of file
  ./edit-plugin.sh

  rpl -q "<!-- mc-plugins -->" " monte-carlo-sample-$i <!-- mc-plugins -->" plugins.xml
done
rpl -q "<!-- mc-plugins -->" "" plugins.xml
fi

# run pacer
../../../BUILD/Moby/moby-driver -r -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 ../../model/model.xml

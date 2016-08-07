#!/bin/bash
source ${BUILD_PATH}/Pacer/setup.sh
# clean up worksapce
  
git clean -dfx .. 

# copy plugin directory for all jobs
for i in $@
do
  # copy generic job
  cp -r ../sample ../sample-$i
done

# re-parse '.in' files
${PACER_SCRIPT_PATH}/setup-tests.sh ./*.in ../sample/*.in

# edit all jobs and include them in main controller
for i in $@
do
  # edit job details
  sed -i.bak "s#>.*</switch-at-time>#>$i</switch-at-time>#g" ../sample-$i/plugins.xml
  
  # paste plugin job into plugin.xml
  # make sed tool for this job
  cat append-monte-carlo.xml | sed "s#monte-carlo-name.xml#../sample-$i/monte-carlo.xml#g" > edit-plugin.sh
  chmod +x edit-plugin.sh
  # append to second-to-last line of file
  ./edit-plugin.sh
done


# run pacer
screen -d -m -L ../../../BUILD/Moby/moby-driver -r -p=${PACER_SIMULATOR_PATH}/libPacerMobyPlugin.so -s=0.001 model.xml

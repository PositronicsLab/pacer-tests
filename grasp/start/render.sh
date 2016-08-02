#!/bin/bash

# simple script for rendering a movie that takes in static camera positions
# and targets

usage()
{
  echo "render.sh <frame rate> <path to Moby render> <camera position> <path to osg files/output> <camera target> <movie file> <up vector>"
  echo " -- sample camera position: 0 5 10"
  echo " -- sample camera target: 0 0 0"
  echo " -- sample up vector: 0 1 0"
  exit 
}

main ()
{
  # ffmpeg requires particular numbering
a=1
for i in $6/frame*.osg; do
  new=$(printf "img%04d.png" ${a});
  echo $2/moby-render $i -p $3 $4 $5 -t $7 $8 $9  -u ${11} ${12} ${13} $6/${new};
  [ -f $6/$new ] && echo "Already created $new" || screen -d -m $2/moby-render $i -p $3 $4 $5 -t $7 $8 $9  -u ${11} ${12} ${13} $6/${new};
  let a=a+1;
done

# number all images img0001.png, etc...
echo ffmpeg -r $1 -i $6/img%04d.png -f mp4 -q:v 0 -vcodec mpeg4 ${10}
ffmpeg -r $1 -i $6/img%04d.png -f mp4 -q:v 0 -vcodec mpeg4 ${10}
}


# check for proper number of arguments
[ "$#" -ne 13 ] && ( usage && exit) || main $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13}



#!/bin/bash

# All args to this script is sent to the next...
my_args="$@ --fxlog 6"
numargs=$#

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

edl=false
# Check if we provide -l or -p,
# since then we remove the default loader/preloader
for (( arg=1 ; arg <= numargs ; arg++ ))
do
  if [ "$1" == "-l" ]
  then
    echo "Override -l..."
    foundL=true
    shift
    Loader="$1"
  fi

  if [ "$1" == "-r" ]
  then
    echo "Hard service"
    edl=true
  fi
  shift
done

# If loader was not provided, then use the default
if [ ! $foundL ]
then
  my_args="$my_args"
fi

# fxtools needs a dir called logs (or it fails).
if [ ! -d logs ]
then
  echo Create dir logs for fxtool logs
  mkdir logs
fi


# check so the loader exist.
if [ ! -f "$Loader" ] && [ ! $edl ]
then
  echo "Error no loader: "$Loader
  exit 3
fi

echo "About to flash"
echo " Loader         : "$Loader
echo " Args to script : "$my_args
echo ""

python generic_flash.py $my_args

exit $?

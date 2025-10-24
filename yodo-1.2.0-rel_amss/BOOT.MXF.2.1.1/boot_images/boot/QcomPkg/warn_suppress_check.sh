#!/bin/bash
echo "------------------------------------------------------------------------------"
echo "Running warning suppress check ....."
echo "------------------------------------------------------------------------------"

rm -rf warning_suppress.log warning_suppress_pass.log warning_suppress_fail.log warning_suppress_count.log

grep "\-Wno-" * -nr >warning_suppress.log
cat warning_suppress.log | wc -l >warning_suppress_count.log

if [ "$1" = "" ]
then echo no arg
else echo arg is $1
    threshold=$1
fi

value=$(<warning_suppress_count.log)

if [ "$value" -gt "$threshold" ]; then
  echo "Warning suppress count $value is more than $threshold "
  echo "Warning suppress count $value is more than $threshold " >warning_suppress_fail.log
  echo "------------------------------------------------------------------------------"
  echo ".............................. Warnings Disable List ........................."
  echo "------------------------------------------------------------------------------"
  cat  warning_suppress.log
else
  echo "Warning suppress count value is $value and threshold is $threshold"
  echo "Warning suppress count value is $value and threshold is $threshold" >warning_suppress_pass.log
fi
  echo "------------------------------------------------------------------------------"
    

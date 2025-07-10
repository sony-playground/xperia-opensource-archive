#!/bin/bash

# Clean up previous run
rm -rf ./.kwlp
rm -rf ./.kwps
rm -rf ./*.log
rm -rf ./*.out
rm -rf ../../../../Build

#Run KW analysis
./kw.sh

if [ $? -eq 0 ]
then
  echo "+++++++++++++++++++++++++"
  echo "+ KW analysis completed +"
  echo "+++++++++++++++++++++++++"
else
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: KW analysis failed "
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  exit 1
fi
 
grep "(Local)" kw_NetraniPkg_all.log            | wc -l > kw_NetraniPkg_count.log

# Check NetraniPkg
threshold=1500
value=$(<kw_NetraniPkg_count.log)

if [ "$value" -gt "$threshold" ]; then
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: NetraniPkg: KW count $value is more than $threshold "
  echo "ERROR: NetraniPkg: KW count $value is more than $threshold " > kw_NetraniPkg_fail.log
  echo "ERROR: ================================================================================================" >  kw_error_list.log
  echo "ERROR: NetraniPkg: KW count $value is more than $threshold " >> kw_error_list.log 
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  cat kw_NetraniPkg.log >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
else
  echo "OK NetraniPkg value = $value, threshold = $threshold "
  echo "OK NetraniPkg value = $value, threshold = $threshold"  > kw_NetraniPkg_pass.log
fi    


if [ -f kw_error_list.log ]; then
  echo "+++++++++++++++++++++++++++++++++++++++++++++"
  echo "+ Printing KW logs for failed packages .... +"
  echo "+++++++++++++++++++++++++++++++++++++++++++++"

  cat kw_error_list.log | grep -v "Analyzing" | grep -v "Creating knowledge" | grep -v "Compiling"
fi  

exit 0


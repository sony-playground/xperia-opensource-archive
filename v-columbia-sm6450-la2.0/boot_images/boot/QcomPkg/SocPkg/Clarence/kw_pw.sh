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
 
grep "(Local)" kw_ClarencePkg_all.log            | wc -l > kw_ClarencePkg_count.log

# Check ClarencePkg
threshold=1500
value=$(<kw_ClarencePkg_count.log)

if [ "$value" -gt "$threshold" ]; then
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ClarencePkg: KW count $value is more than $threshold "
  echo "ERROR: ClarencePkg: KW count $value is more than $threshold " > kw_ClarencePkg_fail.log
  echo "ERROR: ================================================================================================" >  kw_error_list.log
  echo "ERROR: ClarencePkg: KW count $value is more than $threshold " >> kw_error_list.log 
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  cat kw_ClarencePkg.log >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
else
  echo "OK ClarencePkg value = $value, threshold = $threshold "
  echo "OK ClarencePkg value = $value, threshold = $threshold"  > kw_ClarencePkg_pass.log
fi    


if [ -f kw_error_list.log ]; then
  echo "+++++++++++++++++++++++++++++++++++++++++++++"
  echo "+ Printing KW logs for failed packages .... +"
  echo "+++++++++++++++++++++++++++++++++++++++++++++"

  cat kw_error_list.log | grep -v "Analyzing" | grep -v "Creating knowledge" | grep -v "Compiling"
fi  

exit 0


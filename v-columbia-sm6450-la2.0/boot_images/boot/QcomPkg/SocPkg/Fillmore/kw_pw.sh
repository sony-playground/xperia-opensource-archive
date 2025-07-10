#!/bin/bash

# Clean up previous run
rm -rf ./.kwlp
rm -rf ./.kwps
rm -rf ./*.log
rm -rf ./*.out
rm -rf ../../../Build

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
 
grep "(Local)" kw_SDM855Pkg.log            | wc -l > kw_SDM855Pkg_count.log
grep "(Local)" kw_QcomToolsPkg.log         | wc -l > kw_QcomToolsPkg_count.log
grep "(Local)" kw_QcomTestPkg.log          | wc -l > kw_QcomTestPkg_count.log
grep "(Local)" kw_QcomSocPlatTestPkg.log   | wc -l > kw_QcomSocPlatTestPkg_count.log

# Check SDM855Pkg
threshold=925
value=$(<kw_SDM855Pkg_count.log)

if [ "$value" -gt "$threshold" ]; then
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: SDM855Pkg: KW count $value is more than $threshold "
  echo "ERROR: SDM855Pkg: KW count $value is more than $threshold " > kw_SDM855Pkg_fail.log
  echo "ERROR: ================================================================================================" >  kw_error_list.log
  echo "ERROR: SDM855Pkg: KW count $value is more than $threshold " >> kw_error_list.log 
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  cat kw_SDM855Pkg.log >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
else
  echo "OK SDM855Pkg value = $value, threshold = $threshold "
  echo "OK SDM855Pkg value = $value, threshold = $threshold"  > kw_SDM855Pkg_pass.log
fi    

# Check QcomToolsPkg
threshold=347
value=$(<kw_QcomToolsPkg_count.log)

if [ "$value" -gt "$threshold" ]; then
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: QcomToolsPkg: KW count $value is more than $threshold "
  echo "ERROR: QcomToolsPkg: KW count $value is more than $threshold " > kw_QcomToolsPkg_fail.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: QcomToolsPkg: KW count $value is more than $threshold " >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  cat kw_QcomToolsPkg.log >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
else
  echo "OK QcomToolsPkg value = $value, threshold = $threshold "
  echo "OK QcomToolsPkg value = $value, threshold = $threshold" > kw_QcomToolsPkg_pass.log
fi    

# Check QcomTestPkg
threshold=254
value=$(<kw_QcomTestPkg_count.log)

if [ "$value" -gt "$threshold" ]; then
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: QcomTestPkg: KW count $value is more than $threshold "
  echo "ERROR: QcomtestPkg: KW count $value is more than $threshold " > kw_QcomTestPkg_fail.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: QcomtestPkg: KW count $value is more than $threshold " >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  cat kw_QcomTestPkg.log >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
else
  echo "OK QcomTestPkg value = $value, threshold = $threshold "
  echo "OK QcomTestPkg value = $value, threshold = $threshold" > kw_QcomTestPkg_pass.log
fi    

# Check QcomSocPlatTestPkg
threshold=244
value=$(<kw_QcomSocPlatTestPkg_count.log)

if [ "$value" -gt "$threshold" ]; then
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: QcomSocPlatTestPkg: KW count $value is more than $threshold "
  echo "ERROR: QcomSocPlatTestPkg: KW count $value is more than $threshold " > kw_QcomSocPlatTestPkg_fail.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: QcomSocPlatTestPkg: KW count $value is more than $threshold " >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  cat kw_QcomSocPlatTestPkg.log >> kw_error_list.log
  echo "ERROR: ================================================================================================" >> kw_error_list.log
  echo "ERROR: ------------------------------------------------------------------------------------------------"
  echo "ERROR: ------------------------------------------------------------------------------------------------"
else
  echo "OK QcomSocPlatTestPkg value = $value, threshold = $threshold "
  echo "OK QcomSocPlatTestPkg value = $value, threshold = $threshold" > kw_QcomSocPlatTestPkg_pass.log
fi

if [ -f kw_error_list.log ]; then
  echo "+++++++++++++++++++++++++++++++++++++++++++++"
  echo "+ Printing KW logs for failed packages .... +"
  echo "+++++++++++++++++++++++++++++++++++++++++++++"

  cat kw_error_list.log | grep -v "Analyzing" | grep -v "Creating knowledge" | grep -v "Compiling"
fi  

exit 0


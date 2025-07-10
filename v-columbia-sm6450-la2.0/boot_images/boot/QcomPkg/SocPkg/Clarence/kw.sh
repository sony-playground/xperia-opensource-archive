#!/bin/bash

########### BaseTools ###########################
#Skip BaseTools for Klockwork, so build it before analysis
make -C ../../../../edk2/BaseTools
export PATH=$PATH:/prj/qct/asw/SABin/Linux/Klocwork/User/bin

########### Check for KW binaries ###########################
if [ ! -f /prj/qct/asw/SABin/Linux/Klocwork/User/bin/kwcheck ]; then
    echo "kwcheck file not found !"
    exit 1
fi

if [ ! -f /prj/qct/asw/SABin/Linux/Klocwork/User/bin/kwinject ]; then
    echo "kwinject file not found !"
    exit 1
fi


########### Exit on any error ###########################
set -e

kwcheck create --license-host license-wan-klocwork-01.qualcomm.com --license-port 7322
kwinject -o buildspec_ClarencePkg.out python          ../../../../boot_tools/buildex.py -t Clarence --variant LAA -r DEBUG

########### ClarencePkg ###########################
echo Running KW Analysis on ClarencePkg....
kwcheck import buildspec_ClarencePkg.out

if [ -e kw_ClarencePkg_P1.log ]; then
  echo "Renaming kw_ClarencePkg_P1.log to kw_ClarencePkg_P1_old.log"
  mv -f kw_ClarencePkg_P1.log kw_ClarencePkg_P1_old.log
fi
  
kwcheck run > kw_ClarencePkg_all.log
kwcheck list -F detailed --system --local --severity 1 > kw_ClarencePkg_P1.log


exit 0

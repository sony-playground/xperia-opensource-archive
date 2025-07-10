#!/bin/bash

########### BaseTools ###########################
#Skip BaseTools for Klockwork, so build it before analysis
make -C ../../../BaseTools
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
kwinject -o buildspec_SDM855Pkg.out python          ../../buildex.py -t SDM855Pkg --variant LA -r DEBUG
kwinject -o buildspec_QcomToolsPkg.out python       ../../buildex.py -t QcomToolsPkg           -r DEBUG
kwinject -o buildspec_QcomTestPkg.out python        ../../buildex.py -t QcomTestPkg            -r DEBUG
kwinject -o buildspec_QcomSocPlatTestPkg.out python ../../buildex.py -t QcomSocPlatTestPkg     -r DEBUG

########### SDM855Pkg ###########################
echo Running KW Analysis on SDM855Pkg....
kwcheck import buildspec_SDM855Pkg.out

if [ -e kw_SDM855Pkg.log ]; then
  echo "Renaming kw_SDM855Pkg.log to kw_qcomSDM855Pkg_old.log"
  mv -f kw_SDM855Pkg.log kw_SDM855Pkg_old.log
fi
  
kwcheck run > kw_SDM855Pkg.log

########### QcomToolsPkg ###########################
echo Running KW Analysis on QcomToolsPkg....
kwcheck import buildspec_QcomToolsPkg.out

if [ -e kw_QcomToolsPkg.log ]; then
  echo "Renaming kw_QcomToolsPkg.log to kw_QcomToolsPkg_old.log"
  mv -f kw_QcomToolsPkg.log kw_QcomToolsPkg_old.log
fi  

kwcheck run > kw_QcomToolsPkg.log

########### QcomTestPkg ###########################
echo Running KW Analysis on QcomTestPkg....
kwcheck import buildspec_QcomTestPkg.out

if [ -e kw_QcomTestPkg.log ]; then
  echo "Renaming kw_QcomTestPkg.log to kw_QcomTestPkg_old.log"
  mv -f kw_QcomTestPkg.log kw_QcomTestPkg_old.log
fi
  
kwcheck run > kw_QcomTestPkg.log

########### QcomSocPlatTestPkg ###########################
echo Running KW Analysis on QcomSocPlatTestPkg....
kwcheck import buildspec_QcomSocPlatTestPkg.out

if [ -e kw_QcomSocPlatTestPkg.log ]; then
  echo "Renaming kw_QcomSocPlatTestPkg.log to kw_QcomSocPlatTestPkg_old.log"
  mv -f kw_QcomSocPlatTestPkg.log kw_QcomSocPlatTestPkg_old.log
fi
  
kwcheck run > kw_QcomSocPlatTestPkg.log
exit 0

#!/bin/sh
#
# WARNING!                           WARNING!
#           FOR TEST PURPOSES ONLY 
# WARNING!                           WARNING!
#
#
# Create a private authenticated variable 
# and corresponding db with the cert for it 
#
# Pre-requisite:
#   - OpenSSL 1.0.1f
#   - efitools 1.8.1
#   - xxd 1.10
#

# gEfiImageSecurityDatabaseGuid 
DBGUID=D719B2CB-3D3A-4596-A3BC-DAD00E67656F 

# gEfiGlobalVariableGuid 
GLBGUID=8BE4DF61-93CA-11D2-AA0D-00E098032B8C

# Ensure required packages are installed 
if ! hash openssl 2>/dev/null || \
   ! hash cert-to-efi-sig-list 2>/dev/null || \
   ! hash xxd 2>/dev/null; then
  echo Please ensure following packages are installed:
  echo - OpenSSL 1.0.1f
  echo - efitools 1.8.1
  echo - xxd 1.10
  exit 1
fi

# Generate db Cert
openssl req -new -x509 -newkey rsa:2048 \
 -subj "/CN=dummy db/" -days 3650 -nodes -sha256 \
 -keyout db.key -out db.crt

# Print the cert
#openssl x509 -in db.crt -text -noout

# DER encode the cert
openssl x509 -in db.crt -out db.cer -outform DER

# Generate EFI_SIGNATURE_LIST serialization
cert-to-efi-sig-list -g $DBGUID db.crt db.esl

# Concatenate additional EFI_SIGNATURE_LISTs as required 
#cat db.esl db2.esl ... > db.esl

# Empty signed output directory or create if it doesn't exist
[ -d signed ] && rm -rf ./signed/* || mkdir signed

# Generate db EFI_VARIABLE_AUTHENTICATION_2 serialization
sign-efi-sig-list -g $DBGUID \
  -k db.key -c db.crt db db.esl signed/db

# Create NULL siglist
[ -e nulldb.esl ] && rm nulldb.esl
> nulldb.esl

# Generate NULLdb EFI_VARIABLE_AUTHENTICATION_2 serialization
# with newer timestamp
TIMESTAMP="$(date --date='+1sec' +'%Y-%m-%d %H:%M:%S')"
sign-efi-sig-list -t "$TIMESTAMP" -g $DBGUID \
  -k db.key -c db.crt db nulldb.esl signed/nulldb

# Generate payload EFI_VARIABLE_AUTHENTICATION_2 serialization 
# with global variable GUID and newer timestamp
TIMESTAMP="$(date --date='+2sec' +'%Y-%m-%d %H:%M:%S')"
sign-efi-sig-list -t "$TIMESTAMP" -g $GLBGUID \
  -k db.key -c db.crt payload payload signed/payload

# Erase write-protected header files
[ -e db.h ] && rm -rf ./db.h
[ -e nulldb.h ] && rm -rf ./nulldb.h
[ -e payload.h ] && rm -rf ./payload.h

# Convert serializations to C structs
xxd -i signed/db > db.h
xxd -i signed/nulldb > nulldb.h
xxd -i signed/payload > payload.h


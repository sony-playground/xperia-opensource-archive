#!/bin/sh
#
# Copyright (c) 2019 Qualcomm Technologies Inc. All rights reserved.
#
# WARNING!                           WARNING!
#           FOR TEST PURPOSES ONLY
# WARNING!                           WARNING!
#
# Create PK and null-signed PK
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

# Empty signed output directory or create if it doesn't exist
[ -d signed ] && rm -rf ./signed/* || mkdir signed

# Erase write-protected header files
[ -e PK.h ] && rm -rf ./PK.h
[ -e NullPK.h ] && rm -rf ./NullPK.h

# Create NULL PK
[ -e NullPK.esl ] && rm NullPK.esl
> NullPK.esl

# Generate PK Cert
openssl req -new -x509 -newkey rsa:2048 \
 -subj "/CN=PK/" -days 3650 -nodes -sha256 \
 -keyout PK.key -out PK.crt

# Generate EFI_SIGNATURE_LIST serialization
cert-to-efi-sig-list -g $GLBGUID PK.crt PK.esl

# Generate PK EFI_VARIABLE_AUTHENTICATION_2 serialization
sign-efi-sig-list -g $GLBGUID \
  -k PK.key -c PK.crt PK PK.esl signed/PK

# Generate NullPK EFI_VARIABLE_AUTHENTICATION_2 serialization
# with newer timestamp
TIMESTAMP="$(date --date='+1sec' +'%Y-%m-%d %H:%M:%S')"
sign-efi-sig-list -t "$TIMESTAMP" -g $DBGUID \
  -k PK.key -c PK.crt PK NullPK.esl signed/NullPK

# Convert serializations to C structs
xxd -i signed/PK > PK.h
xxd -i signed/NullPK > NullPK.h


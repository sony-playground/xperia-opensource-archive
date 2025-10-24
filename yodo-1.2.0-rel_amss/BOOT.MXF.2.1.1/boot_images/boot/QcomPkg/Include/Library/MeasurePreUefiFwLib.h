/** @file

  MeasurePreUefiFwLib.h

  Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.

**/

#ifndef _MEASURE_PRE_UEFI_FW_LIB_H_
#define _MEASURE_PRE_UEFI_FW_LIB_H_

#include <Uefi/UefiBaseType.h>

/**
  This sevice does following in a secure environment on Qualcomm platform:
      1. retrieve the pre-uefi fw hash( including uefi image's )
      2. extend the pre-uefi fw hash into PCR0 of TPM
      3. return the pre-eufi fw hash for TCG log purpose 

  Caller of this API needs to allocate two large enough buffers to hold the returned hash values,
  the actual returned buffer sizes are determined by the TPM and register reading, it is recommended 
  to allocate sizeof(TPML_DIGEST_VALUES) for HashBuffer, and 64 bytes for ToBeHashedBuffer. 
  TPML_HASH_VALUES is defined in Tpm20.h

  @param[in/out]  *HashBuffer            The hash buffer holding the returned hash values
                                             in:  allocated buffer ( sizeof(TPML_DIGEST_VALUES) bytes )
                                             out: hash list in TPML_DIGEST_VALUES format

  @param[in]       HashBufferSize        Size of the hash buffer, sizeof(TPML_DIGEST_VALUES) bytes

  @param[in/out]  *ToBeHasedBuffer       The to-be hashed buffer holding hash value read from register
                                             in:  allocated buffer ( 64 bytes )
                                             out: hash read from register

  @param[in/out]  *ToBeHasedBufferSize   Size of the to-be hashed buffer
                                             in:    allocated to-be hashed buffer size ( 64 bytes )
                                             out:  returned hash size 

  @retval EFI_SUCCESS                   The operation is successfully
  @retval EFI_BUFFER_TOO_SMALL          The buffer size is too small
  @retval Other ERRORS                  Other error encountered in this operation            
**/
EFI_STATUS
EFIAPI
MeasurePreUefiFw
(
  IN OUT    UINT8        *HashBuffer,
  IN        UINT32        HashBufferSize,
  IN OUT    UINT8        *ToBeHashedBuffer,
  IN OUT    UINT32       *ToBeHashedBufferSize
);

#endif  // _MEASURE_PRE_UEFI_FW_LIB_H_

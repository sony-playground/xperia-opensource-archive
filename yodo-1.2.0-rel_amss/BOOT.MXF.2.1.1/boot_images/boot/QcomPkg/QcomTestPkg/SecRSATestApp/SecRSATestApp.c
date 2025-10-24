/**
                SecRSATestApp

  Testing SecRSA protocol.

  Copyright (c) 2016, 2019 - 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---     ----------------------------------------------------------
 11/18/20   JP      Ported RSA PSS padding support
 10/01/19   JP      Modified for Padding Type Error handling test case
 08/26/16   SA      Initial version

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/TestInterface.h>
#include <Protocol/EFISecRSA.h>
#include <Protocol/Hash.h>
#include <Protocol/Hash2.h>
#include <Library/QcomBaseLib.h>
#include <string.h>
#include <Protocol/EFICryptoSelect.h>

#include "SecRSA_SIG_verify_test_vectors.h"

#define EFI_FAILURE (80)

#define HASH_LEN_SHA1    20
#define HASH_LEN_SHA224  28
#define HASH_LEN_SHA256  32
#define HASH_LEN_SHA384  48
#define HASH_LEN_SHA512  64

static EFI_STATUS rsa_sign_verify_pkcs1_v15_basic_test(QCOM_SECRSA_PROTOCOL *rsa_protocol, CE_RSA_KEY *key)
{
  EFI_STATUS Status = EFI_FAILURE;
  BigInt modulus_bi;
  BigInt public_exp_bi;
  INT32 hashidx = CE_HASH_IDX_SHA256;
  INT32 hash_len = 32;
  UINT32 padding_type;
  VOID *padding_info = NULL;
  UINT8 public_exponent[] = {0x01, 0x00, 0x01};

  UINT8 modulus[] = {0xe8, 0xeb, 0x78, 0x4d, 0x2f, 0x4d, 0x54, 0x91, 0x7a,
                     0x7b, 0xb3, 0x3b, 0xdb, 0xe7, 0x69, 0x67, 0xe4, 0xd1, 0xe4, 0x33, 0x61,
                     0xa6, 0xf4, 0x82, 0xaa, 0x62, 0xeb, 0x10, 0x33, 0x8b, 0xa7, 0x66, 0x0f,
                     0xeb, 0xa0, 0xa0, 0x42, 0x89, 0x99, 0xb3, 0xe2, 0xb8, 0x4e, 0x43, 0xc1,
                     0xfd, 0xb5, 0x8a, 0xc6, 0x7d, 0xba, 0x15, 0x14, 0xbb, 0x47, 0x50, 0x33,
                     0x8e, 0x9d, 0x2b, 0x8a, 0x1c, 0x2b, 0x13, 0x11, 0xad, 0xc9, 0xe6, 0x1b,
                     0x1c, 0x9d, 0x16, 0x7e, 0xa8, 0x7e, 0xcd, 0xce, 0x0c, 0x93, 0x17, 0x3a,
                     0x4b, 0xf6, 0x80, 0xa5, 0xcb, 0xfc, 0x57, 0x5b, 0x10, 0xf7, 0x43, 0x6f,
                     0x1c, 0xdd, 0xbb, 0xcc, 0xf7, 0xca, 0x4f, 0x96, 0xeb, 0xbb, 0x9d, 0x33,
                     0xf7, 0xd6, 0xed, 0x66, 0xda, 0x43, 0x70, 0xce, 0xd2, 0x49, 0xee, 0xfa,
                     0x2c, 0xca, 0x6a, 0x4f, 0xf7, 0x4f, 0x8d, 0x5c, 0xe6, 0xea, 0x17, 0x99,
                     0x0f, 0x35, 0x50, 0xdb, 0x40, 0xcd, 0x11, 0xb3, 0x19, 0xc8, 0x4d, 0x55,
                     0x73, 0x26, 0x5a, 0xe4, 0xc6, 0x3a, 0x48, 0x3a, 0x53, 0xed, 0x08, 0xd9,
                     0x37, 0x7b, 0x2b, 0xcc, 0xaf, 0x50, 0xc5, 0xa1, 0x01, 0x63, 0xcf, 0xa4,
                     0xa2, 0xed, 0x54, 0x7f, 0x6b, 0x00, 0xbe, 0x53, 0xce, 0x36, 0x0d, 0x47,
                     0xdd, 0xa2, 0xcd, 0xd2, 0x9c, 0xcf, 0x70, 0x23, 0x46, 0xc2, 0x37, 0x09,
                     0x38, 0xed, 0xa6, 0x25, 0x40, 0x04, 0x67, 0x97, 0xd1, 0x37, 0x23, 0x45,
                     0x2b, 0x99, 0x07, 0xb2, 0xbd, 0x10, 0xae, 0x7a, 0x1d, 0x5f, 0x8e, 0x14,
                     0xd4, 0xba, 0x23, 0x53, 0x4f, 0x8d, 0xd0, 0xfb, 0x14, 0x84, 0xa1, 0xc8,
                     0x69, 0x6a, 0xa9, 0x97, 0x54, 0x3a, 0x40, 0x14, 0x65, 0x86, 0xa7, 0x6e,
                     0x98, 0x1e, 0x4f, 0x93, 0x7b, 0x40, 0xbe, 0xae, 0xba, 0xa7, 0x06, 0xa6,
                     0x84, 0xce, 0x91, 0xa9, 0x6e, 0xea, 0x49};

  CONST UINT8 signature[] = {
      0x8f, 0xc2, 0x4d, 0xdd, 0x15, 0xeb, 0x27, 0x57, 0x66, 0xd8, 0x43, 0x63, 0x52, 0xf4, 0xc8, 0x82,
      0x84, 0xd2, 0xc8, 0x8a, 0xa0, 0x7c, 0xe9, 0xcb, 0xb8, 0x4e, 0x6a, 0xe6, 0x21, 0xdb, 0xc9, 0x88,
      0x96, 0x4d, 0xab, 0xfb, 0x10, 0xb0, 0x4a, 0x62, 0x5f, 0xe6, 0x36, 0x4a, 0x5c, 0xe9, 0xd1, 0xad,
      0xcd, 0xf8, 0x15, 0x72, 0x1a, 0x6f, 0x60, 0xe3, 0x57, 0xae, 0xef, 0xa5, 0xe1, 0x2b, 0xb8, 0x8e,
      0x57, 0xe9, 0xfd, 0xf0, 0x37, 0x73, 0x13, 0x4f, 0x45, 0xbc, 0x63, 0x8e, 0x1f, 0x80, 0xd2, 0xfc,
      0x1a, 0xcd, 0x8d, 0x9d, 0x0b, 0x12, 0x1c, 0xff, 0x3e, 0xe5, 0x84, 0xd6, 0x64, 0xe8, 0x7a, 0xb2,
      0xdd, 0x65, 0x8a, 0x55, 0x85, 0xf4, 0x04, 0x91, 0xea, 0xd9, 0xc9, 0x48, 0x8f, 0x9e, 0xa3, 0xb1,
      0xdf, 0xc1, 0x34, 0x75, 0x99, 0xb8, 0xe0, 0x0a, 0x27, 0xc7, 0x37, 0x63, 0x50, 0xdb, 0xcb, 0xe0,
      0xcf, 0x5d, 0x9c, 0xb6, 0x05, 0xe6, 0x90, 0xb2, 0xc7, 0x03, 0x29, 0xfe, 0xa6, 0xd6, 0x50, 0xb6,
      0xdd, 0xa8, 0x17, 0x23, 0x1f, 0xc4, 0xbd, 0x17, 0x7d, 0x03, 0xae, 0xe2, 0x06, 0x61, 0xba, 0x1a,
      0xfa, 0x96, 0x38, 0x42, 0x64, 0xc7, 0x57, 0x06, 0x65, 0x16, 0x9f, 0xd2, 0x4f, 0x91, 0x46, 0x52,
      0x20, 0x6d, 0xe5, 0x36, 0x2c, 0x61, 0xc7, 0x1e, 0xc4, 0x63, 0xb3, 0xf0, 0xb1, 0x17, 0x8e, 0xdb,
      0xa3, 0x2c, 0x3c, 0xb8, 0x9d, 0x86, 0x7f, 0xec, 0xba, 0x9c, 0x6e, 0x3f, 0x49, 0xde, 0x64, 0xaa,
      0xeb, 0x70, 0xa2, 0xe8, 0x20, 0xb1, 0x79, 0xf7, 0xf0, 0x12, 0xf5, 0x5c, 0x7c, 0xff, 0x36, 0x29,
      0xe2, 0x7d, 0x0c, 0x3f, 0x85, 0x11, 0xdf, 0xf1, 0xad, 0xa6, 0x50, 0x91, 0xea, 0x57, 0x6c, 0x80,
      0x8f, 0x12, 0x9d, 0xa7, 0x19, 0x38, 0x63, 0xb9, 0x8e, 0xad, 0xd3, 0x3b, 0xf6, 0x90, 0xdc, 0xb5};

  UINT8 incorrect_hash[32] = {0x0};
  UINT8 correct_hash[] = {
      0xf6, 0x04, 0x08, 0x81, 0x0f, 0xD3, 0xad, 0xB8, 0xa7, 0xb7, 0x9f, 0x8f, 0x9d, 0x98, 0xb6, 0xba,
      0x69, 0xca, 0x7f, 0x84, 0x29, 0xa5, 0x95, 0x30, 0x1a, 0x8a, 0x14, 0x88, 0xa6, 0xee, 0x9d, 0xf5};

  SetMem(key->N, sizeof(S_BIGINT), 0);
  SetMem(key->e, sizeof(S_BIGINT), 0);
  Status = rsa_protocol->SecRSABigIntReadBin(rsa_protocol, modulus, sizeof(modulus), &modulus_bi);
  if (Status != EFI_SUCCESS) {
    AsciiPrint("SecRSATestApp: SecRSABigIntReadBin for modulus failed!, Status = %x\n", Status);
    return EFI_FAILURE;
  }
  Status = rsa_protocol->SecRSABigIntReadBin(rsa_protocol, public_exponent, sizeof(public_exponent), &public_exp_bi);
  if (Status != EFI_SUCCESS) {
    AsciiPrint("SecRSATestApp: SecRSABigIntReadBin for modulus failed!, Status = %x\n", Status);
    return EFI_FAILURE;
  }
  key->N->bi = modulus_bi;
  key->e->bi = public_exp_bi;
  key->e->sign = S_BIGINT_POS;
  key->type = CE_RSA_KEY_PUBLIC;

  UINT8 i = 0;
  UINT32 nonsupport_padding[] = {
    CE_RSA_PAD_PKCS1_V1_5_ENC,
    CE_RSA_PAD_PKCS1_OAEP,
    CE_RSA_NO_PAD,
    CE_RSA_PAD_PKCS1_PSS_AUTORECOVER_SALTLEN
  };

  for (i=0; i<sizeof(nonsupport_padding)/sizeof(UINT32); i++) {
    Status = rsa_protocol->SecRSAVerifySig(rsa_protocol, key, nonsupport_padding[i], padding_info, hashidx,
                                                     correct_hash, hash_len, signature, sizeof(signature));
    if (Status == EFI_SUCCESS) {
      AsciiPrint("SecRSATestApp: Basic Test with Non-support padding index ( %d ) - SUCCESS unexpectedly returned: Test Failed!\n", i);
      return EFI_FAILURE;
    }
    AsciiPrint("SecRSATestApp: Basic Test with Non-support padding index ( %d ) - NON-SUCCESS returned as expected: Test Passed!\n", i);
  }

  padding_type = CE_RSA_PAD_PKCS1_V1_5_SIG;
  Status = rsa_protocol->SecRSAVerifySig(rsa_protocol, key, padding_type, padding_info, hashidx,
                                                   incorrect_hash, hash_len, signature, sizeof(signature));

  if (Status == EFI_SUCCESS) {
    AsciiPrint("SecRSATestApp: Basic Test with incorrect hash - SUCCESS unexpectedly returned: Test Failed!\n");
    return EFI_FAILURE;
  }
  AsciiPrint("SecRSATestApp: Basic Test with incorrect hash - NON-SUCCESS returned as expected: Test Passed!\n");

  Status = rsa_protocol->SecRSAVerifySig(rsa_protocol, key, padding_type, padding_info, hashidx,
                                                   correct_hash, hash_len, signature, sizeof(signature));

  if (Status != EFI_SUCCESS) {
    AsciiPrint("SecRSATestApp: Basic Test with current parameters - NON-SUCCESS returned unexpectedly: Test Failed!\n");
    return EFI_FAILURE;
  }
  AsciiPrint("SecRSATestApp: Basic Test with current parameters: SUCCESS returned as expected: Test Passed!\n");

  return EFI_SUCCESS;
}

static EFI_STATUS Hash2_protocol_hash( EFI_HASH2_PROTOCOL *pEfiHashProtocol, CE_HASH_IDX algo, UINT8 *msg, UINT32 msglen, UINT8 *hash, UINT32 *hashlen)
{
  EFI_STATUS Status = EFI_FAILURE;
  EFI_GUID *AlgoGuid = NULL;
  EFI_HASH2_OUTPUT    Hash_output;
  UINT8               *pHash = NULL;
 
  if ( CE_HASH_IDX_SHA1 == algo ) {
    AlgoGuid = &gEfiHashAlgorithmSha1Guid;
    *hashlen = HASH_LEN_SHA1;
    pHash = (UINT8 *)Hash_output.Sha1Hash;
  } else if ( CE_HASH_IDX_SHA224 == algo ) {
    AlgoGuid = &gEfiHashAlgorithmSha224Guid;
    *hashlen = HASH_LEN_SHA224;
    pHash = (UINT8 *)Hash_output.Sha224Hash;
  } else if ( CE_HASH_IDX_SHA256 == algo ) {
    AlgoGuid = &gEfiHashAlgorithmSha256Guid;
    *hashlen = HASH_LEN_SHA256;
    pHash = (UINT8 *)Hash_output.Sha256Hash;
  } else if ( CE_HASH_IDX_SHA384 == algo ) {
    AlgoGuid = &gEfiHashAlgorithmSha384Guid;
    *hashlen = HASH_LEN_SHA384;
    pHash = (UINT8 *)Hash_output.Sha384Hash;
  } else if ( CE_HASH_IDX_SHA512 == algo ) {
    AlgoGuid = &gEfiHashAlgorithmSha512Guid;
    *hashlen = HASH_LEN_SHA512;
    pHash = (UINT8 *)Hash_output.Sha512Hash;
  } else {
    *hashlen = 0;
    return EFI_UNSUPPORTED;
  }

  Status = pEfiHashProtocol->Hash(pEfiHashProtocol, AlgoGuid, msg, msglen, &Hash_output);
  if ( EFI_ERROR (Status) )
  {
    AsciiPrint("ERROR: Hash failed, Status = (0x%p)\r\n", Status);
    return Status;
  }

  CopyMemS(hash, *hashlen, pHash, *hashlen);
  return EFI_SUCCESS;
}

static UINT32 getSaltLen( CE_HASH_IDX hash_idx)
{
  switch (hash_idx) {
    case CE_HASH_IDX_SHA1:   return HASH_LEN_SHA1;
    case CE_HASH_IDX_SHA224: return HASH_LEN_SHA224;
    case CE_HASH_IDX_SHA256: return HASH_LEN_SHA256;
    case CE_HASH_IDX_SHA384: return HASH_LEN_SHA384;
    case CE_HASH_IDX_SHA512: return HASH_LEN_SHA512;
    default: ;
  }
  return 0;
}

EFI_STATUS
EFIAPI
SecRSATestAppMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status = EFI_FAILURE;
  QCOM_SECRSA_PROTOCOL *pEfiQcomSecRSAProtocol = NULL;
  CE_RSA_KEY key = {0};
  BigInt modulus_bi = {{0}};
  BigInt public_exp_bi = {{0}};

  /* Locate SecRSA Protocol */
  Status = gBS->LocateProtocol(&gEfiQcomSecRSAProtocolGuid, NULL, (VOID **)&pEfiQcomSecRSAProtocol);
  if (Status != EFI_SUCCESS) {
    AsciiPrint("SecRSATestApp: LocateProtocol failed, Status = %x\n", Status);
    goto exit;
  }

  SetMem(&key, sizeof(CE_RSA_KEY), 0);
  key.N = AllocatePool(sizeof(S_BIGINT));
  if (key.N == NULL) {
    AsciiPrint("SecRSATestApp: mem allocation err for key.N\n");
    goto exit;
  }
  key.e = AllocatePool(sizeof(S_BIGINT));
  if (key.e == NULL) {
    AsciiPrint("SecRSATestApp: mem allocation err for key.e\n");
    goto exit;
  }

  /*Run rsa_sign_verify_pkcs1_v15_basic_test */
  AsciiPrint("#### SecRSATestApp: Start Basic Test: rsa_sign_verify_pkcs1_v15_basic_test....#### \n");
  Status = rsa_sign_verify_pkcs1_v15_basic_test(pEfiQcomSecRSAProtocol, &key);
  if (Status != EFI_SUCCESS) {
    AsciiPrint("SecRSATestApp: Basic Test: rsa_sign_verify_pkcs1_v15_basic_test Test Failed!, Status = %x\n", Status);
    goto exit;
  }
  AsciiPrint("#### SecRSATestApp: Basic Test: rsa_sign_verify_pkcs1_v15_basic_test Test -- PASSED! #### \n");

  /* Verify RSA Signature With CAVP Test Vectors  */
  UINT8 i;
  EFI_HASH2_PROTOCOL *HashProtocol = NULL;
  EFI_QCOM_CRYPTO_SELECT_PROTOCOL  *pQcomCryptoSelectProtocol = NULL;
  EFI_CRYPTO_TYPE CryptoType = EFI_HW_CRYPTO;

  /* Located EFI_HASH2_PROTOCOL and EFI_QCOM_CRYPTO_SELECT_PROTOCOL protocols used for Hash input message */
  Status = gBS->LocateProtocol(&gQcomCryptoSelectProtocolGuid, NULL, (VOID **) &pQcomCryptoSelectProtocol);
  if ( EFI_ERROR (Status) )
  {
    AsciiPrint("ERROR: LocateProtocol QcomCryptoSelectProtocol failed, Status = (0x%p)\r\n", Status);
    goto exit;
  }

  Status = pQcomCryptoSelectProtocol->CryptoTypeSet(pQcomCryptoSelectProtocol, CryptoType );
  if ( EFI_ERROR (Status) )
  {
    AsciiPrint("ERROR: CryptoEngineTypeSet failed, Status = (0x%p)\r\n", Status);
    goto exit;
  }

  Status = gBS->LocateProtocol(&gEfiHash2ProtocolGuid, NULL, (VOID **) &HashProtocol);
  if ( EFI_ERROR (Status) )
  {
    AsciiPrint("ERROR: LocateProtocol HashProtocol failed, Status = (0x%p)\r\n", Status);
    goto exit;
  }

  /* Verify RSA Signature with padding PKCS1_V1_5 and CE_RSA_PAD_PKCS1_PSS */
  CE_RSA_PSS_PAD_INFO pss_pad_info;
  void  *padding_info = NULL;
  UINT8 hash[HASH_LEN_SHA512] ={0};
  UINT32 hashlen = 0;

  AsciiPrint("#### SecRSATestApp: Start RSA Signature Verification With CAVP Vectors Tests....#### \n");
  for (i = 0; i<sizeof(RSA_SIG_verify_test)/sizeof(RSA_SIG_verify_test_t); i++) {
    RSA_SIG_verify_test_t *test = &RSA_SIG_verify_test[i];
    SetMem(key.N, sizeof(S_BIGINT), 0);
    SetMem(key.e, sizeof(S_BIGINT), 0);

    Status = pEfiQcomSecRSAProtocol->SecRSABigIntReadBin(pEfiQcomSecRSAProtocol, test->modulus, test->key_len, &modulus_bi);
    if (Status != EFI_SUCCESS) {
      AsciiPrint("SecRSATestApp: SecRSABigIntReadBin for modulus failed!, Status = %x\n", Status);
      goto exit;
    }
    Status = pEfiQcomSecRSAProtocol->SecRSABigIntReadBin(pEfiQcomSecRSAProtocol, test->public_exponent, test->key_len, &public_exp_bi);
    if (Status != EFI_SUCCESS) {
      AsciiPrint("SecRSATestApp: SecRSABigIntReadBin for modulus failed!, Status = %x\n", Status);
      goto exit;
    }
    key.N->bi = modulus_bi;
    key.e->bi = public_exp_bi;
    key.e->sign = S_BIGINT_POS;
    key.type = CE_RSA_KEY_PUBLIC;

    if ( CE_RSA_PAD_PKCS1_PSS == test->pad_type ) {
      pss_pad_info.hashidx = test->hashIdx;
      pss_pad_info.saltlen = getSaltLen(test->hashIdx);
      padding_info = (void *)&pss_pad_info;
    } else {
      padding_info = NULL;
    }

    /* calculate hash from input msg */
    SetMem(hash, sizeof(hash), 0);
    hashlen = 0;
    Status = Hash2_protocol_hash( HashProtocol, test->hashIdx, test->msg, test->msg_len, hash, &hashlen);
    if ( EFI_ERROR (Status) )
    {
      AsciiPrint("ERROR: Hash2_protocol_hash failed, Status = (0x%p)\r\n", Status);
      goto exit;
    }

    Status = pEfiQcomSecRSAProtocol->SecRSAVerifySig(pEfiQcomSecRSAProtocol, 
        &key, 
        test->pad_type,
        padding_info,
        test->hashIdx,
        hash,
        hashlen,
        test->signature,
        test->key_len);

    if (( test->expectedResult && Status != EFI_SUCCESS) || (!test->expectedResult && Status == EFI_SUCCESS))  {
      AsciiPrint("SecRSATestApp: SecRSAVerifySig - Test Vector Num = ( %d ) with Padding Type = ( %d ): Test Failed!\n", i, test->pad_type );
      Status = EFI_DEVICE_ERROR;
      goto exit;
    }
    AsciiPrint("SecRSATestApp: SecRSAVerifySig - Test Vector Num = ( %d ) with Padding Type = ( %d ): Test Passed!\n", i,  test->pad_type );
  }

  AsciiPrint("#### SecRSATestApp: RSA Signature Verification With CAVP Vectors Tests -- PASSED! #### \n");
exit:
  if ( EFI_ERROR (Status) )
    AsciiPrint("#### SecRSATestApp: RSA Signature Verification With CAVP Vectors Tests -- FAILED! #### \n");

  if (key.N != NULL) {
    FreePool(key.N);
  }
  if (key.e != NULL) {
    FreePool(key.e);
  }
  return Status;
}

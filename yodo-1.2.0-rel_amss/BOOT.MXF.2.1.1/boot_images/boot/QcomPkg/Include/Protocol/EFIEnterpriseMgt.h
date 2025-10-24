/**
  @file EFIEnterpriseMgt.h
  @brief EnterpriseMgt data structure definitions.
*/
/*=============================================================================
  Copyright (c) 2020-2021 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/Protocol/EFIEnterpriseMgt.h#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/

#ifndef __EFI_ENTERPRISEMGT_H__
#define __EFI_ENTERPRISEMGT_H__

/* EnterpriseMgt Protocol Version */
#define EFI_QCOM_ENTERPRISEMGT_PROTOCOL_V1 0x0000000000010000 

/** EnterpriseMgt Current Protocol revision. */
#define EFI_QCOM_ENTERPRISEMGT_PROTOCOL_REVISION   EFI_QCOM_ENTERPRISEMGT_PROTOCOL_V1

/* Macro defining EnterpriseMgt driver and lib policy version in use */
#define ENT_MGT_POLICY_VERSION (0x0001)

/* Macros used as cookies for input policy validation */
#define HEAD_COOKIE (0xDEAD)
#define TAIL_COOKIE (0xFEED)

/* Macros to control the EnterpriseMgt debug logs */
#define ENT_MGT_MSGI EFI_D_INFO
#define ENT_MGT_INFO EFI_D_ERROR
#define ENT_MGT_WARN EFI_D_ERROR
#define ENT_MGT_ERRO EFI_D_ERROR

#define MAX_NUM_BITS_IN_ENT_MGT_REG (32)

// #define MAX_FEATURE_BITMAP_SIZE ((ENT_MGT_MAX_FEATURES/MAX_NUM_BITS_IN_ENT_MGT_REG) + 1)
/* Reserve the Max bits to 128. Size of 4 will hold upto 4 * 32 bits = 128 bits. Each bit represents one feature */
/* Reserving the memory to accomodate Max 128 features to cover future feature additions without impacting NV size */
#define MAX_FEATURE_BITMAP_SIZE (4)

#pragma pack(1)
/* Structure to hold policy information for the features to disable */
typedef struct _ENT_MGT_POLICY_STORE {
    UINT16 HeadCookie;
    UINT16 PolicyVersion;
    UINT16 NumFeatures;
    UINT16 CheckSum;
    UINT32 FeatureBitMap[MAX_FEATURE_BITMAP_SIZE];
    UINT16 TailCookie ;
    UINT16 Reserved ;  // For alignment
} ENT_MGT_POLICY_STORE;
#pragma pack()

/*===========================================================================
  DATA TYPE DEFINITIONS
===========================================================================*/
/** @ingroup efi_qcom_enterprisemgt_protocol */
extern EFI_GUID gQcomEnterpriseMgtProtocolGuid;

/* Macros for EnterpriseMgt UEFI NV variable */
#define ENT_MGT_CLIENT_POLICIES_NAME (L"EnterpriseMgtClientPolicies")
#define ENT_MGT_CLIENT_POLICIES_GUID {0xc9249348, 0xed44, 0x4d29, { 0xbf, 0x59, 0xa0, 0xcf, 0xaf, 0x66, 0x63, 0x87 }}
#define ENT_MGT_CLIENT_POLICIES_ATTR (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE)

/* EFI_ENTERPRISE_MGT_LOCK_NOW_VAR */
/** 
  Function to lock Enterprise Management UEFI NV variable.

  @return
    EFI_SUCCESS            EnterpriseMgt UEFI variable locked successfully. 

*/
typedef
EFI_STATUS
(EFIAPI *EFI_ENTERPRISE_MGT_LOCK_NOW_VAR )
(
  VOID
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_qcom_enterprisemgt_protocol
  @par Summary
  Qualcomm Enterprise Management Protocol interface.

  @par Parameters
*/
typedef struct _EFI_QCOM_ENTERPRISEMGT_PROTOCOL {
   UINT64                           Revision;
   EFI_ENTERPRISE_MGT_LOCK_NOW_VAR  EnterpriseMgtLockNowVar;
}EFI_QCOM_ENTERPRISEMGT_PROTOCOL; 

#endif /*__EFI_ENTERPRISEMGT_H__*/

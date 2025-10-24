/** @file
  This library is used by other modules to send TPM2 command.

  Copyright (c) 2020-2022 Copyright Qualcomm Technologies, Inc.  All Rights Reserved.

  Copyright (C) Microsoft Corporation.
  SPDX-License-Identifier: BSD-2-Clause-Patent

  Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved. <BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/
/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---    ----------------------------------------------------------
02/23/22    shl     Added Interfaces to define NV index for SystemGuard
03/30/21    shl     Added return to CopyBufferToDigestList()
10/08/20    shl     Added CopyBufferToDigestList()
07/18/20    shl     Initial version, removed not needed APIs, 
                    added GetDigestListSizeFromHashAlgorithmMask()
=============================================================================*/

#ifndef _TPM2_COMMAND_LIB_H_
#define _TPM2_COMMAND_LIB_H_

#include <IndustryStandard/Tpm20.h>

/**
 *   structue for setting active PCR banks
 */
typedef struct
{
   UINT32   TpmHashAlgoBitmap;
   UINT32   NewPcrBanks;
   UINT32   LastPcrBanks;
   UINT32   ResponseCode;
   CHAR8    Str[32];

} PcrBanksDataType;


/**
  This command removes all TPM context associated with a specific Owner.

  @param[in] AuthHandle        TPM_RH_LOCKOUT or TPM_RH_PLATFORM+{PP}
  @param[in] AuthSession       Auth Session context

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR Unexpected device behavior.
**/
EFI_STATUS
EFIAPI
Tpm2Clear (
  IN TPMI_RH_CLEAR             AuthHandle,
  IN TPMS_AUTH_COMMAND         *AuthSession OPTIONAL
  );


/**
  Disables and enables the execution of TPM2_Clear().

  @param[in] AuthHandle        TPM_RH_LOCKOUT or TPM_RH_PLATFORM+{PP}
  @param[in] AuthSession       Auth Session context
  @param[in] Disable           YES if the disableOwnerClear flag is to be SET,
                               NO if the flag is to be CLEAR.

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR Unexpected device behavior.
**/
EFI_STATUS
EFIAPI
Tpm2ClearControl (
  IN TPMI_RH_CLEAR             AuthHandle,
  IN TPMS_AUTH_COMMAND         *AuthSession, OPTIONAL
  IN TPMI_YES_NO               Disable
  );


/**
  This command enables and disables use of a hierarchy.

  @param[in] AuthHandle        TPM_RH_ENDORSEMENT, TPM_RH_OWNER or TPM_RH_PLATFORM+{PP}
  @param[in] AuthSession       Auth Session context
  @param[in] Hierarchy         Hierarchy of the enable being modified
  @param[in] State             YES if the enable should be SET,
                               NO if the enable should be CLEAR

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR Unexpected device behavior.
**/
EFI_STATUS
EFIAPI
Tpm2HierarchyControl (
  IN TPMI_RH_HIERARCHY         AuthHandle,
  IN TPMS_AUTH_COMMAND         *AuthSession,
  IN TPMI_RH_HIERARCHY         Hierarchy,
  IN TPMI_YES_NO               State
  );


/**
  This command is used to cause an update to the indicated PCR.
  The digests parameter contains one or more tagged digest value identified by an algorithm ID.
  For each digest, the PCR associated with pcrHandle is Extended into the bank identified by the tag (hashAlg).

  @param[in] PcrHandle   Handle of the PCR
  @param[in] Digests     List of tagged digest values to be extended

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR Unexpected device behavior.
**/
EFI_STATUS
EFIAPI
Tpm2PcrExtend (
  IN      TPMI_DH_PCR               PcrHandle,
  IN      TPML_DIGEST_VALUES        *Digests
  );


/**
  This command is used to cause an update to the indicated PCR.
  The data in eventData is hashed using the hash algorithm associated with each bank in which the
  indicated PCR has been allocated. After the data is hashed, the digests list is returned. If the pcrHandle
  references an implemented PCR and not TPM_ALG_NULL, digests list is processed as in
  TPM2_PCR_Extend().
  A TPM shall support an Event.size of zero through 1,024 inclusive.

  @param[in]  PcrHandle   Handle of the PCR
  @param[in]  EventData   Event data in sized buffer
  @param[out] Digests     List of digest

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR Unexpected device behavior.
**/
EFI_STATUS
EFIAPI
Tpm2PcrEvent (
  IN      TPMI_DH_PCR               PcrHandle,
  IN      TPM2B_EVENT               *EventData,
     OUT  TPML_DIGEST_VALUES        *Digests
  );


/**
  This command returns the values of all PCR specified in pcrSelect.

  @param[in]  PcrSelectionIn     The selection of PCR to read.
  @param[out] PcrUpdateCounter   The current value of the PCR update counter.
  @param[out] PcrSelectionOut    The PCR in the returned list.
  @param[out] PcrValues          The contents of the PCR indicated in pcrSelect.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2PcrRead (
  IN      TPML_PCR_SELECTION        *PcrSelectionIn,
     OUT  UINT32                    *PcrUpdateCounter,
     OUT  TPML_PCR_SELECTION        *PcrSelectionOut,
     OUT  TPML_DIGEST               *PcrValues
  );


/**
  This command is used to set the desired PCR allocation of PCR and algorithms.

  @param[in]  AuthHandle         TPM_RH_PLATFORM+{PP}
  @param[in]  AuthSession        Auth Session context
  @param[in]  PcrAllocation      The requested allocation
  @param[out] AllocationSuccess  YES if the allocation succeeded
  @param[out] MaxPCR             maximum number of PCR that may be in a bank
  @param[out] SizeNeeded         number of octets required to satisfy the request
  @param[out] SizeAvailable      Number of octets available. Computed before the allocation

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2PcrAllocate (
  IN  TPMI_RH_PLATFORM          AuthHandle,
  IN  TPMS_AUTH_COMMAND         *AuthSession,
  IN  TPML_PCR_SELECTION        *PcrAllocation,
  OUT TPMI_YES_NO               *AllocationSuccess,
  OUT UINT32                    *MaxPCR,
  OUT UINT32                    *SizeNeeded,
  OUT UINT32                    *SizeAvailable
  );


/**
  Alloc PCR data.

  @param[in]  PlatformAuth      platform auth value. NULL means no platform auth change.
  @param[in]  SupportedPCRBanks Supported PCR banks
  @param[in]  PCRBanks          PCR banks

  @retval EFI_SUCCESS Operation completed successfully.
**/
EFI_STATUS
EFIAPI
Tpm2PcrAllocateBanks (
  IN TPM2B_AUTH                *PlatformAuth,  OPTIONAL
  IN UINT32                    SupportedPCRBanks,
  IN UINT32                    PCRBanks
  );


/**
  This command returns various information regarding the TPM and its current state.

  The capability parameter determines the category of data returned. The property parameter
  selects the first value of the selected category to be returned. If there is no property
  that corresponds to the value of property, the next higher value is returned, if it exists.
  The moreData parameter will have a value of YES if there are more values of the requested
  type that were not returned.
  If no next capability exists, the TPM will return a zero-length list and moreData will have
  a value of NO.

  NOTE:
  To simplify this function, leave returned CapabilityData for caller to unpack since there are
  many capability categories and only few categories will be used in firmware. It means the caller
  need swap the byte order for the fields in CapabilityData.

  @param[in]  Capability         Group selection; determines the format of the response.
  @param[in]  Property           Further definition of information.
  @param[in]  PropertyCount      Number of properties of the indicated type to return.
  @param[out] MoreData           Flag to indicate if there are more values of this type.
  @param[out] CapabilityData     The capability data.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2GetCapability (
  IN      TPM_CAP                   Capability,
  IN      UINT32                    Property,
  IN      UINT32                    PropertyCount,
  OUT     TPMI_YES_NO               *MoreData,
  OUT     TPMS_CAPABILITY_DATA      *CapabilityData
  );


/**
  This command returns the information of TPM manufacture ID.

  This function parse the value got from TPM2_GetCapability and return the TPM manufacture ID.

  @param[out] ManufactureId      The manufacture ID of TPM.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2GetCapabilityManufactureID (
  OUT     UINT32                    *ManufactureId
  );


/**
  This command returns the information of TPM FirmwareVersion.

  This function parse the value got from TPM2_GetCapability and return the TPM FirmwareVersion.

  @param[out] FirmwareVersion1   The FirmwareVersion1.
  @param[out] FirmwareVersion2   The FirmwareVersion2.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2GetCapabilityFirmwareVersion (
  OUT     UINT32                    *FirmwareVersion1,
  OUT     UINT32                    *FirmwareVersion2
  );


/**
  This command returns the information of the maximum value for commandSize and responseSize in a command.

  This function parse the value got from TPM2_GetCapability and return the max command size and response size

  @param[out] MaxCommandSize     The maximum value for commandSize in a command.
  @param[out] MaxResponseSize    The maximum value for responseSize in a command.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2GetCapabilityMaxCommandResponseSize (
  OUT UINT32                    *MaxCommandSize,
  OUT UINT32                    *MaxResponseSize
  );


/**
  This command returns Returns a list of TPMS_ALG_PROPERTIES. Each entry is an
  algorithm ID and a set of properties of the algorithm.

  This function parse the value got from TPM2_GetCapability and return the list.

  @param[out] AlgList      List of algorithm.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2GetCapabilitySupportedAlg (
  OUT TPML_ALG_PROPERTY      *AlgList
  );


/**
  This command returns the information of TPM PCRs.

  This function parse the value got from TPM2_GetCapability and return the PcrSelection.

  @param[out] Pcrs    The Pcr Selection

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2GetCapabilityPcrs (
  OUT TPML_PCR_SELECTION      *Pcrs
  );


/**
  This function will query the TPM to determine which hashing algorithms
  are supported and which PCR banks are currently active.

  @param[out]  TpmHashAlgorithmBitmap A bitmask containing the algorithms supported by the TPM.
  @param[out]  ActivePcrBanks         A bitmask containing the PCRs currently allocated.

  @retval     EFI_SUCCESS   TPM was successfully queried and return values can be trusted.
  @retval     Others        An error occurred, likely in communication with the TPM.

**/
EFI_STATUS
EFIAPI
Tpm2GetCapabilitySupportedAndActivePcrs(
  OUT UINT32                            *TpmHashAlgorithmBitmap,
  OUT UINT32                            *ActivePcrBanks
  );


//
// Help function
//

/**
  Copy AuthSessionIn to TPM2 command buffer.

  @param [in]  AuthSessionIn   Input AuthSession data
  @param [out] AuthSessionOut  Output AuthSession data in TPM2 command buffer

  @return AuthSession size
**/
UINT32
EFIAPI
CopyAuthSessionCommand (
  IN      TPMS_AUTH_COMMAND         *AuthSessionIn, OPTIONAL
  OUT     UINT8                     *AuthSessionOut
  );

/**
  Copy AuthSessionIn from TPM2 response buffer.

  @param [in]  AuthSessionIn   Input AuthSession data in TPM2 response buffer
  @param [out] AuthSessionOut  Output AuthSession data

  @return AuthSession size
**/
UINT32
EFIAPI
CopyAuthSessionResponse (
  IN      UINT8                      *AuthSessionIn,
  OUT     TPMS_AUTH_RESPONSE         *AuthSessionOut OPTIONAL
  );

/**
  Return size of digest.

  @param[in] HashAlgo  Hash algorithm

  @return size of digest
**/
UINT16
EFIAPI
GetHashSizeFromAlgo (
  IN TPMI_ALG_HASH    HashAlgo
  );

/**
  Get hash mask from algorithm.

  @param[in] HashAlgo   Hash algorithm

  @return Hash mask
**/
UINT32
EFIAPI
GetHashMaskFromAlgo (
  IN TPMI_ALG_HASH     HashAlgo
  );


/**
  Return if hash alg is supported in HashAlgorithmMask.

  @param HashAlg            Hash algorithm to be checked.
  @param HashAlgorithmMask  Bitfield of allowed hash algorithms.

  @retval TRUE  Hash algorithm is supported.
  @retval FALSE Hash algorithm is not supported.
**/
BOOLEAN
EFIAPI
IsHashAlgSupportedInHashAlgorithmMask(
  IN TPMI_ALG_HASH  HashAlg,
  IN UINT32         HashAlgorithmMask
  );


/**
  Copy TPML_DIGEST_VALUES into a buffer

  @param[in,out] Buffer             Buffer to hold copied TPML_DIGEST_VALUES compact binary.
  @param[in]     DigestList         TPML_DIGEST_VALUES to be copied.
  @param[in]     HashAlgorithmMask  HASH bits corresponding to the desired digests to copy.

  @return The end of buffer to hold TPML_DIGEST_VALUES.
**/
VOID *
EFIAPI
CopyDigestListToBuffer(
  IN OUT VOID                       *Buffer,
  IN TPML_DIGEST_VALUES             *DigestList,
  IN UINT32                         HashAlgorithmMask
  );


/**
  Copy a buffer into  TPML_DIGEST_VALUES structure

  @param[in,out] Buffer             Buffer to hold TPML_DIGEST_VALUES compact binary.
  @param[in]     DigestList         TPML_DIGEST_VALUES .

  @return The real status
**/
EFI_STATUS
EFIAPI
CopyBufferToDigestList (
  IN     VOID                   *Buffer,
  IN OUT TPML_DIGEST_VALUES     *DigestList
  );


/**
  Get TPML_DIGEST_VALUES data size.

  @param[in]     DigestList    TPML_DIGEST_VALUES data.

  @return TPML_DIGEST_VALUES data size.
**/
UINT32
EFIAPI
GetDigestListSize(
  IN TPML_DIGEST_VALUES             *DigestList
  );


/**
  Get TPML_DIGEST_VALUES data size from HashAlgorithmMask

  @param[in]     DigestList    TPML_DIGEST_VALUES data.

  @return TPML_DIGEST_VALUES data size.
**/
UINT32
EFIAPI
GetDigestListSizeFromHashAlgorithmMask(
  IN UINT32         HashAlgorithmMask
  );


/**
  This function get digest from digest list.

  @param[in]  HashAlg       Digest algorithm
  @param[in]  DigestList    Digest list
  @param[out] Digest        Digest

  @retval EFI_SUCCESS       Digest is found and returned.
  @retval EFI_NOT_FOUND     Digest is not found.
**/
EFI_STATUS
EFIAPI
GetDigestFromDigestList(
  IN TPMI_ALG_HASH      HashAlg,
  IN TPML_DIGEST_VALUES *DigestList,
  OUT VOID              *Digest
  );


/**
  This command is used to read the public area and Name of an NV Index.

  @param[in]  NvIndex            The NV Index.
  @param[out] NvPublic           The public area of the index.
  @param[out] NvName             The Name of the nvIndex.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
Tpm2NvReadPublic (
  IN      TPMI_RH_NV_INDEX          NvIndex,
  OUT     TPM2B_NV_PUBLIC           *NvPublic,
  OUT     TPM2B_NAME                *NvName
  );


/**
  This command defines the attributes of an NV Index and causes the TPM to
  reserve space to hold the data associated with the index.
  If a definition already exists at the index, the TPM will return TPM_RC_NV_DEFINED.

  @param[in]  AuthHandle         TPM_RH_OWNER or TPM_RH_PLATFORM+{PP}.
  @param[in]  AuthSession        Auth Session context
  @param[in]  Auth               The authorization data.
  @param[in]  NvPublic           The public area of the index.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_ALREADY_STARTED    The command was returned successfully, but NvIndex is already defined.
**/
EFI_STATUS
EFIAPI
Tpm2NvDefineSpace (
  IN      TPMI_RH_PROVISION         AuthHandle,
  IN      TPMS_AUTH_COMMAND         *AuthSession, OPTIONAL
  IN      TPM2B_AUTH                *Auth,
  IN      TPM2B_NV_PUBLIC           *NvPublic
  );


/**
  Executes DefineSpace for SystemGuard NV Index used by the OS, with
  requirements in Mircosoft "System Guard Secure Launch and SMM Protection",
  section "System requirements for System Guard", item "TPM NV Index"

  @retval     EFI_SUCCESS         NV Index was defined.
  @retval     EFI_ALREADY_STARTED NV Index has been defined already.
  @retval     EFI_DEVICE_ERROR    Tpm2NvReadPublic() returned an unexpected error.
  @retval     Others              Tpm2NvDefineSpace() returned an error.
**/
EFI_STATUS
EFIAPI
DefineSgTpmNVIndexforOS (
  VOID
  );

#endif

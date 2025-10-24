/**
  @file EFITpmControl.h
  @brief Declaration of Tpm Control Interface 
*/
/*=============================================================================
  Copyright (c) 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---    -----------------------------------------------------------
 03/18/21    shl    Initial version.

=============================================================================*/

#ifndef _EFITPM_CONTROL_H_
#define _EFITPM_CONTROL_H_

#include <Uefi.h>

/* define QCOM_TPM_CONTROL_PROTOCOL */
typedef struct  _QCOM_TPM_CONTROL_PROTOCOL  QCOM_TPM_CONTROL_PROTOCOL;
/** @endcond */

/*  Tpm UEFI GUID */
/** @cond */
extern EFI_GUID gQcomTpmControlProtocolGuid;
/** @endcond */

/** @ingroup efi_tpm_constants
  Protocol version. 
*/
#define QCOM_TPM_CONTROL_REVISION 0x00010000

/* tpm type */
#define dTPM    0x6454504D  //dTPM
#define fTPM    0x6654504D  //fTPM
#define sTPM    0x7354504D  //sTPM
#define None    0x4E6F6E65  //None

/* tpm state */
#define   ENABLED       1
#define   DISABLED      2

/*===========================================================================
  TPM FUNCTION DEFINITIONS
===========================================================================*/

/* QCOM_TPM_CONTROL_GET_TYPE */
/** @ingroup efi_tpm_control_get_type
  @par Summary
  Gets the TPM type, dTPM, fTPM, sTPM or None.

  @param[in]  This   Pointer to the QCOM_TPM_CONTROL_PROTOCOL instance.
  @param[out] Type   Pointer to TPM type

  @return 
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- NULL parameter was passed.

*/
typedef
EFI_STATUS
(EFIAPI *QCOM_TPM_CONTROL_GET_TYPE)( 
  IN  QCOM_TPM_CONTROL_PROTOCOL   *This, 
  OUT UINT32                      *Type
);


/* QCOM_TPM_CONTROL_GET_STATE */
/** @ingroup efi_tpm_control_get_tpm_state
  @par Summary
  Get TPM state, DISABLED or ENABLED or NOT_EXIST. 

  @param[in]  This    Pointer to QCOM_TPM_CONTROL_PROTOCOL instance.
  @param[out] State   Pointer to tpm state. 

  @return 
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- NULL parameter was passed.

*/
typedef
EFI_STATUS
(EFIAPI *QCOM_TPM_CONTROL_GET_STATE)( 
  IN   QCOM_TPM_CONTROL_PROTOCOL   *This,
  OUT  UINT32                      *State
);


/* EFI_TPM_SET_STATE */
/** @ingroup efi_tpm_control_set_tpm_state
  @par Summary
  Set TPM state, must be either DISABLED or ENABLED.  

  @param[in]  This           Pointer to QCOM_TPM_CONTROL_PROTOCOL instance.
  @param[out] State          Value of tpm state to be set. 

  @return 
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Invalid State value.
  EFI_UNSUPPORTED       -- tpm does not exist.

*/
typedef
EFI_STATUS
(EFIAPI *QCOM_TPM_CONTROL_SET_STATE)( 
  IN  QCOM_TPM_CONTROL_PROTOCOL   *This,
  IN  UINT32                       State
);


/* QCOM_TPM_CONTROL_GET_STATE */
/** @ingroup efi_tpm_control_get_tpm_state_and_type
  @par Summary
  Get TPM state and type

  @param[in]  This   Pointer to QCOM_TPM_CONTROL_PROTOCOL instance.
  @param[out] State  Pointer to tpm state. 
  @param[out] Type   Pointer to tpm type.

  @return 
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- NULL parameter was passed.

*/
typedef
EFI_STATUS
(EFIAPI *QCOM_TPM_CONTROL_GET_STATE_AND_TYPE)( 
  IN   QCOM_TPM_CONTROL_PROTOCOL   *This,
  OUT  UINT32                      *State,
  OUT  UINT32                      *Type
);


/* TPM Protocol; structure is documented with Tpm Protocol above */
/** @cond */
struct _QCOM_TPM_CONTROL_PROTOCOL
{ 
  UINT64                               Revision;
  QCOM_TPM_CONTROL_GET_TYPE            GetTpmType;
  QCOM_TPM_CONTROL_GET_STATE           GetTpmState;
  QCOM_TPM_CONTROL_SET_STATE           SetTpmState;
  QCOM_TPM_CONTROL_GET_STATE_AND_TYPE  GetTpmStateAndType;
};
/** @endcond */

#endif /* _EFITPM_CONTROL_H_ */


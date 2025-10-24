/** 
@file  EFIPmicChg.h
@brief PMIC CHG for UEFI.
*/
/*=============================================================================
Copyright (c) 2022 Qualcomm Technologies, Inc.
All rights reserved.
Qualcomm Technologies Inc Confidential and Proprietary.
    
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
06/29/22   dv      Protocol creation for general charger API.

=============================================================================*/

#ifndef __EFIPMICCHG_H__
#define __EFIPMICCHG_H__

/*===========================================================================

                        MACRO DECLARATIONS

===========================================================================*/
/** @addtogroup efi_pmicChg_constants 
@{ */
/**
Protocol version.
*/

#define PMIC_CHG_REVISION           EFI_PMIC_CHG_REVISION_1
#define EFI_PMIC_CHG_REVISION_1     0x0000000000010000 /*EFI_PMIC_CHG_REVISION_<MAJ_REV>*/

/** @} */ /* end_addtogroup efi_pmicChg_constants */

/*  Protocol GUID definition */
/** @ingroup efi_pmicChg_protocol */
#define EFI_PMIC_CHG_PROTOCOL_GUID \
    { 0xc9234855, 0x2e0d, 0x4b3c, {0xb1, 0x13, 0xb6, 0x52, 0x3d, 0xbd, 0x13, 0xc7 } }


/** @cond */
/*===========================================================================

                        EXTERNAL VARIABLES

===========================================================================*/
/**
External reference to the PMIC CHG Protocol GUID.
*/
extern EFI_GUID gQcomPmicChgProtocolGuid;

/*===========================================================================

                        FUNCTION DECLARATIONS

===========================================================================*/


/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

/**
Protocol declaration.
*/
typedef struct _EFI_QCOM_PMIC_CHG_PROTOCOL   EFI_QCOM_PMIC_CHG_PROTOCOL;
/** @endcond */

/** @addtogroup efi_pmicChg_data_types 
@{ */


/*===========================================================================

                        EXTERNAL VARIABLES

===========================================================================*/
/**
External reference to the PMIC CHG CFG DATA.
*/

/*===========================================================================

                        EXTERNAL FUNCTION DECLARATIONS

===========================================================================*/
/* EFI_PM_CHG_GET_PRIMARY_CHGR_PMIC_INDEX */ 
/** @ingroup
  @par Summary
  Returns the Charger PMIC index (Primary)

  @param[out]  PmicDeviceIndex

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS (EFIAPI *EFI_PM_CHG_GET_PRIMARY_CHGR_PMIC_INDEX)
(
  OUT UINT32 *ChargerPmicIndex
);


/*===========================================================================

                        CHG PROTOCOL INTERFACE

===========================================================================*/
/** @ingroup efi_pmicChg_protocol
@par Summary
Qualcomm PMIC CHG Protocol interface.

@par Parameters
@inputprotoparams{pmic_chg_proto_params.tex}
*/

struct _EFI_QCOM_PMIC_CHG_PROTOCOL {
  UINT64                                         Revision;
  EFI_PM_CHG_GET_PRIMARY_CHGR_PMIC_INDEX         GetChgrPmicIndex;
};

#endif  /* __EFIPMICCHG_H__ */

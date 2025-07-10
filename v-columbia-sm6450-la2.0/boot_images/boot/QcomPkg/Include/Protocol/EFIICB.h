/**
  @file  EFIClock.h
  @brief ICB Protocol for UEFI.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/18/20   sds     Created.

=============================================================================*/
#ifndef __EFIICB_H__
#define __EFIICB_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @addtogroup efi_icb_constants
@{ */
/**
  Protocol version.
*/
#define EFI_ICB_PROTOCOL_VERSION 0x0000000000010000

/** @} */ /* end_addtogroup efi_icb_constants */

/** @addtogroup efi_icb_protocol
@{ */
/*  Protocol GUID definition */
#define EFI_ICB_PROTOCOL_GUID \
  { 0x5824F9DE, 0x17D2, 0x4B1F, { 0xA5, 0xFE, 0x5E, 0xB7, 0x7F, 0xA5, 0x30, 0x93 } }


/** @} */ /* end_addtogroup efi_icb_protocol */

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the CLOCK Protocol GUID.
*/
extern EFI_GUID gEfiICBProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
/**
  Protocol declaration.
*/
typedef struct _EFI_ICB_PROTOCOL EFI_ICB_PROTOCOL;

/** @endcond */

/** @addtogroup efi_icb_data_types
@{ */
/** @} */ /* end_addtogroup efi_icb_data_types */

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_ICB_POST_INIT */
/** @ingroup efi_icb_post_init
  @par Summary
  This API is called when UEFI is made all ICB votes required to remain active.
  Allow flush of all zero bandwidth nodes.

  @par Description
    @param  This      [in]  The EFI_ICB_PROTOCOL instance.
 
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_ICB_POST_INIT)(
  IN  EFI_ICB_PROTOCOL *This
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_icb_protocol
  @par Summary
  Clock Protocol interface.

  @par Parameters
  @inputprotoparams{clock_proto_params.tex}
*/
struct _EFI_ICB_PROTOCOL {
   UINT64            Version;
   EFI_ICB_POST_INIT PostInit;
};

#endif  /* __EFIICB_H__ */

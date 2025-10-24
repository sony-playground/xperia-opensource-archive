/**
  @file  EFIRsc.h
  @brief RSC API.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     ----------------------------------------------------------
04/05/20    li      Initial revision.

=============================================================================*/
#ifndef __EFIRSCH_H__
#define __EFIRSCH_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @addtogroup efi_rsc_constants
@{ */
/**
  Protocol version.
*/
#define EFI_RSC_PROTOCOL_REVISION 0x0000000000010000
/** @} */ /* end_addtogroup efi_rsc_constants */

/*  Protocol GUID definition */
/** @ingroup efi_rsc_protocol */
#define EFI_RSC_PROTOCOL_GUID \
  { 0x3806cdf0, 0xc281, 0x4345, { 0x9b, 0x1e, 0x49, 0xdf, 0xb3, 0x12, 0x69, 0x23 } }


/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the RSC API Protocol GUID.
 */
extern EFI_GUID gEfiRscProtocolGuid;
/** @endcond */

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

/* EFI_RSC_INIT */
/** @ingroup efi_rsc_instance_init
  @par Summary
  Initializes the RSC subsystem.

  @return
  EFI_SUCCESS -- Function completed successfully.
 */
typedef EFI_STATUS (EFIAPI* EFI_RSC_INSTANCE_INIT)(const char *name, void **handle);

/* EFI_RSC_PCIE_DISABLE_FORCE_WAKE */
 /** @ingroup efi_rsc_pcie_disable_force_wake
  @par Summary
  Disable force wake after intializing the PLIMs

  @return
  EFI_SUCCESS or error values
 */
typedef void (EFIAPI* EFI_RSC_PCIE_DISABLE_FORCE_WAKE)(void *handle);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_rsc_protocol
  @par Summary
  Rsc Api Protocol interface.

  @par Parameters
*/
typedef struct _EFI_RSC_PROTOCOL {
  UINT64                               Revision;
  EFI_RSC_INSTANCE_INIT                rsc_instance_init;
  EFI_RSC_PCIE_DISABLE_FORCE_WAKE      rsc_pcie_disable_force_wake;
} EFI_RSC_PROTOCOL;

#endif /* __EFIRSC_H__ */

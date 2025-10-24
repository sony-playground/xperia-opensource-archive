/** 
  @file  EFIPasr.h
  @brief PASR EFI protocol interface.
*/
/*=============================================================================
  Copyright (c) 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 04/01/22   daisond   Initial Revision
=============================================================================*/

#ifndef __EIPASR_H__
#define __EIPASR_H__


/** @defgroup efi_pars_protocol EFI_PARS_PROTOCOL
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  efi_pars_protocol_prot PROTOCOL
 *  @ingroup efi_pars_protocol 
 */ 
 /** @defgroup  efi_pars_protocol_apis APIs
 *  @ingroup efi_pars_protocol 
 */ 

/** @defgroup  efi_pars_protocol_data DATA_STRUCTURES
 *  @ingroup efi_pars_protocol 
 */

/** @ingroup efi_pars_protocol_data
 * @cond */
typedef struct _EFI_PASR_PROTOCOL EFI_PASR_PROTOCOL;
/** @endcond */

/** @addtogroup efi_pasr_constants 
@{ */
/** @ingroup efi_pars_protocol_data
  Protocol latest version. 
*/
#define EFI_PASR_PROTOCOL_REVISION EFI_PASR_PROTOCOL_REVISION_V1
#define EFI_PASR_PROTOCOL_REVISION_V1 0x0000000000010000

/** @} */ /* end_addtogroup efi_pasr_constants */

/*  Protocol GUID definition */
/** @ingroup efi_pars_protocol_prot */
#define EFI_PASR_PROTOCOL_GUID \
   { 0x10c0a4a2, 0xfee6, 0x49be, { 0x92, 0xaf, 0xa7, 0xbb, 0x8e, 0xe6, 0x97, 0xc3 } }

  
/** @cond */
/** @ingroup efi_pars_protocol_data
  External reference to the PASR Protocol GUID defined 
  in the .dec file. 
*/
extern EFI_GUID gEfiPasrProtocolGuid;
/** @endcond */
/** @ingroup efi_pars_protocol_data */
typedef struct
{
   UINTN Address;
   UINTN Size;
}PASR_BLOCK;
/** @} */ /* end_addtogroup efi_pasr_data_types */

/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/ 

/* ============================================================================
**  Function : EFI_PASR_CONFIG
** ============================================================================
*/
/** @ingroup efi_pars_protocol_apis
  @par Summary
  Set the PASR start address and size
    
  @param[in]   This                  Pointer to the EFI_PASR_SETSTARTADDR instance.
  @param[in]   NumBlocks             Number of PASR blocks. NumBlocks = 1 is supported currently. 
  @param[in]   Pasr_block            PASR block containing start address and size.
  
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_PASR_CONFIG)(
   IN EFI_PASR_PROTOCOL   *This,
   IN UINT32               NumBlocks,
   IN PASR_BLOCK          *Pasr_Block
   );

/* ============================================================================
**  Function : EFI_PASR_ACTIVATE
** ============================================================================
*/
/** @ingroup efi_pars_protocol_apis
  @par Summary
  PASR enablement 
    
  @param[in]   This                  Pointer to the EFI_PASR_ACTIVATE instance.
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_PASR_ACTIVATE)(
   IN EFI_PASR_PROTOCOL   *This
   );

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_pars_protocol_prot 
  @par Summary
  PASR Protocol interface.

  @par Parameters
*/
struct _EFI_PASR_PROTOCOL {
   UINT64                                Revision;
   EFI_PASR_CONFIG                       PASRConfig;             /* Implemented in protocol revision EFI_PASR_PROTOCOL_REVISION_V1 */
   EFI_PASR_ACTIVATE                     PASRActivate;           /* Implemented in protocol revision EFI_PASR_PROTOCOL_REVISION_V1 */
}; 

#endif /* __EIPASR_H__ */


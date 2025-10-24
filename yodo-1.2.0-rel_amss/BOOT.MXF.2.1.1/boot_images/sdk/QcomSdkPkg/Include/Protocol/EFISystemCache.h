/*===============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         EFISystemCache.h
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  03/11/21   dais        Initial version

================================================================================*/

#ifndef __EFI_SYSTEM_CACHE_H__
#define __EFI_SYSTEM_CACHE_H__

/** @defgroup EFI_SYSTEM_CACHE_PROTOCOL  EFI_SYSTEM_CACHE_PROTOCOL 
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  EFI_SYSTEM_CACHE_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_SYSTEM_CACHE_PROTOCOL 
 */ 
 /** @defgroup  EFI_SYSTEM_CACHE_PROTOCOL_apis APIs
 *  @ingroup EFI_SYSTEM_CACHE_PROTOCOL 
 */ 

/** @defgroup  EFI_SYSTEM_CACHE_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_SYSTEM_CACHE_PROTOCOL 
 */

typedef struct _EFI_SYSTEM_CACHE_PROTOCOL EFI_SYSTEM_CACHE_PROTOCOL;

#define EFI_SYSTEM_CACHE_PROTOCOL_VERSION 0x0000000000010000

#define EFI_SYSTEM_CACHE_PROTOCOL_GUID \
  { 0x92cccff7, 0xb65a, 0x4f59, { 0x86, 0x13, 0x71, 0x19, 0x2d, 0x72, 0xcd, 0x28 } }
  
extern EFI_GUID gEfiSystemCacheProtocolGuid;

/**@ingroup EFI_SYSTEM_CACHE_PROTOCOL_data
**/
typedef struct scid_status_t
{
  UINT8 activated;
  UINT8 deactivated;
  UINT32 scid_maximum_capacity;
  UINT32 capacity_in_use;
}SCID_STATUS;

/**@ingroup EFI_SYSTEM_CACHE_PROTOCOL_apis
  Activate specific SCID

  @param[in]  Scid         Scid which needs to be activated 

  @retval EFI_SUCCESS          success.
  
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SCID_ACTIVATE) (
   IN EFI_SYSTEM_CACHE_PROTOCOL *This,
   IN UINT32            Scid
   ); 
   
/** @ingroup EFI_SYSTEM_CACHE_PROTOCOL_apis
  Deactivate specific SCID

  @param[in]  Scid         Scid which needs to be deactivated

  @retval EFI_SUCCESS          success.
  
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SCID_DEACTIVATE) (
   IN EFI_SYSTEM_CACHE_PROTOCOL *This,
   IN UINT32            Scid
   ); 

/** @ingroup EFI_SYSTEM_CACHE_PROTOCOL_apis
  Get status of specific SCID

  @param[in]  Scid         Scid for which status needs to be read
  @param[in]  Scid_Status  Returns status details of the SCID

  @retval EFI_SUCCESS          success.
  
**/
typedef
EFI_STATUS
(EFIAPI *EFI_GET_SCID_STATUS) (
   IN EFI_SYSTEM_CACHE_PROTOCOL *This,
   IN UINT32            Scid,
   OUT SCID_STATUS      *Scid_Status
   ); 
   
/** @ingroup EFI_SYSTEM_CACHE_PROTOCOL_apis
  Configure settings for island mode

  @retval EFI_SUCCESS          success.
  
**/
typedef
EFI_STATUS
(EFIAPI *EFI_CONFIG_ISLAND_MODE) (
   IN EFI_SYSTEM_CACHE_PROTOCOL *This
   ); 

/** @ingroup EFI_SYSTEM_CACHE_PROTOCOL_prot
**/
struct _EFI_SYSTEM_CACHE_PROTOCOL {
   UINT64                  Revision;
   EFI_SCID_ACTIVATE       Scid_Activate;
   EFI_SCID_DEACTIVATE     Scid_Deactivate;
   EFI_GET_SCID_STATUS     Get_Scid_Status;
   EFI_CONFIG_ISLAND_MODE  Config_Island_Mode;
};


#endif // __EFI_SYSTEM_CACHE_H__
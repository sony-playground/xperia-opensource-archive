/** 
  @file  EFIPlatformInfo.h
  @brief PlatformInfo Protocol for UEFI.
*/
/*=============================================================================
  Copyright (c) 2011-2012 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/18/13   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 05/08/12   vishalo Merge in Techpubs Doxygen change
 05/04/12   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 01/26/12   vishalo Merge in Techpubs Doxygen change
 10/25/11   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 03/07/11   mdt     Created.

=============================================================================*/


#ifndef __EFIPLATFORMINFO_H__
#define __EFIPLATFORMINFO_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

#include "EFIPlatformInfoTypes.h"


/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/

#define EFI_PLATFORMINFO_PROTOCOL_REVISION3 0x0000000000030000

/** @ingroup efi_platform_info_protocol_data
  Protocol version.
*/
#define EFI_PLATFORMINFO_PROTOCOL_VERSION EFI_PLATFORMINFO_PROTOCOL_REVISION3

/** @ingroup efi_platform_info_protocol_data 
 *  Protocol GUID definition
*/
#define EFI_PLATFORMINFO_PROTOCOL_GUID \
  { 0x157a5c45, 0x21b2 , 0x43c5, { 0xba, 0x7c, 0x82, 0x2f, 0xee, 0x5f, 0xe5, 0x99 } }


/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the Platform Info Protocol GUID.
 */
extern EFI_GUID gEfiPlatformInfoProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
/** @ingroup efi_platform_info_protocol_data
  Protocol declaration.
 */
typedef struct _EFI_PLATFORMINFO_PROTOCOL EFI_PLATFORMINFO_PROTOCOL;
/** @endcond */

/** @ingroup efi_platform_info_protocol_data
  Stores the target platform, the platform version, and the subtype of the
  platform.
 */
typedef struct
{
  EFI_PLATFORMINFO_PLATFORM_TYPE    platform;
  /**< Type of the current target; see #EFI_PLATFORMINFO_PLATFORM_TYPE for 
       details. */
  UINT32                            version;
  /**< Version of the platform in use. */
  UINT32                            subtype;
  /**< Subtype of the platform. */
  BOOLEAN                           fusion;
  /**< TRUE if Fusion; FALSE otherwise. */
  
  /*
   * Padding: 3 bytes.
   * TODO: Once this makes it into UEFI, swap the order of
   * fusion and OEMVariantID. That'll potentially save some
   * space if a < 4-byte member is appended to this structure
   * since it'll consume some of the padding.
  */
  UINT32                          OEMVariantID; 
  /**< OEM variant ID. */
} EFI_PLATFORMINFO_PLATFORM_INFO_TYPE;
/** @} */ /* end_addtogroup efi_platformInfo_data_types */


/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_PLATFORMINFO_GET_PLATFORMINFO */ 
/** @ingroup efi_platform_info_protocol_apis
  @par Summary
  Gets information about the current platform. The information is returned 
  in the PlatformInfo parameter.

  @param[in]  This          Pointer to the EFI_PLATFORMINFO_PROTOCOL instance.
  @param[out] PlatformInfo  Pointer to the platform information to be filled 
                            in; see #EFI_PLATFORMINFO_PLATFORM_INFO_TYPE.

  @return
  EFI_SUCCESS        -- Function completed successfully.  \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation. 
*/
typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORMINFO_GET_PLATFORMINFO)(
  IN  EFI_PLATFORMINFO_PROTOCOL           *This,
  OUT EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *PlatformInfo); 


/* EFI_PLATFORMINFO_GET_KEYVALUE */ 
/** @ingroup efi_platform_info_protocol_apis
  @par Summary
  Gets a key value.

  @param[in]  This          Pointer to the EFI_PLATFORMINFO_PROTOCOL instance.
  @param[in]  Key           Key to get the value for; 
                            see #EFI_PLATFORMINFO_KEY_TYPE.
  @param[out] Value         Key value.

  @return
  EFI_SUCCESS        -- Key found.  \n
  EFI_NOT_FOUND      -- Key not found.  \n
  EFI_INVALID_PARAMETER -- Key out of range or Value is NULL.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORMINFO_GET_KEYVALUE)(
  IN  EFI_PLATFORMINFO_PROTOCOL   *This,
  IN  EFI_PLATFORMINFO_KEY_TYPE    Key,
  OUT UINT32                      *Value); 


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_platform_info_protocol_prot
  @par Summary
  Platform Information Protocol interface.

  @par Parameters
  @inputprotoparams{platform_info_proto_params.tex} 
*/
struct _EFI_PLATFORMINFO_PROTOCOL {
  UINT64                            Version;
  EFI_PLATFORMINFO_GET_PLATFORMINFO GetPlatformInfo;  
  EFI_PLATFORMINFO_GET_KEYVALUE     GetKeyValue;
};

#endif  /* __EFIPLATFORMINFO_H__ */

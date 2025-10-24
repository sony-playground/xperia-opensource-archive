#ifndef BOOT_MINIDUMP_H
#define BOOT_MINIDUMP_H
/*=============================================================================

                               Boot minidump
                               Header File
GENERAL DESCRIPTION
  This file provides the APIs for minidump feature

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright (c) 2017, 2020-2022 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
10/06/22   rama    Add boot_md_is_valid_global_mdtoc
04/28/22   rama    Add boot_get_md_region_count
03/10/22   rama    Changes for moving minidump to ECDH encryption
02/18/22   rama    Cleanup phase 2
01/18/22   rama    re-arch updates and cleanup
08/26/21   rama    added md_ss in boot_add_minidump_region
08/09/21   rama    Added md_ss for xbl_sc and boot
06/22/21   rama    Changes to enable minidump
03/30/20   aus     Added new functions for Boot minidump
12/21/17   aus     Removed packed attribute
12/12/17   aus     Updated structures as packed
10/12/17   aus     Updated structures as per design
01/17/17   bd      Initial version

=============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <comdef.h>
#include <boot_encryption.h>
#include <boot_error_if.h>
#include <boot_config_context.h>

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

#define MD_REVISION                       1
#define SBL_MINIDUMP_SMEM_ID              602
#define MD_SHARED_IMEM_BASE               (SHARED_IMEM_BASE + 0xB88)
#define MD_REGION_NAME_LENGTH             16

/* Macro for number of encryption artifacts wrapped_key, iv_buffer and mac_buffer */
#define MD_ENCRYPTION_ARTIFACTS_COUNT     (3)

#define MD_REGION_VALID                   ('V' << 24 | 'A' << 16 | 'L' << 8 | 'I' << 0)
#define MD_REGION_INVALID                 ('I' << 24 | 'N' << 16 | 'V' << 8 | 'A' << 0)
#define MD_REGION_INIT                    ('I' << 24 | 'N' << 16 | 'I' << 8 | 'T' << 0)
#define MD_REGION_NOINIT                  0

#define MD_SS_TOC_MAGIC                   (0 << 24 | 'T' << 16 | 'O' << 8 | 'C' << 0)
#define MD_SS_ENCR_REQ                    (0 << 24 | 'Y' << 16 | 'E' << 8 | 'S' << 0)
#define MD_SS_ENCR_NOTREQ                 (0 << 24 | 0 << 16 | 'N' << 8 | 'R' << 0)
#define MD_SS_ENCR_DONE                   ('D' << 24 | 'O' << 16 | 'N' << 8 | 'E' << 0)
#define MD_SS_ENCR_NOT_DONE               0
#define MD_SS_ENCR_START                  ('S' << 24 | 'T' << 16 | 'R' << 8 | 'T' << 0)
#define MD_SS_ENABLED                     ('E' << 24 | 'N' << 16 | 'B' << 8 | 'L' << 0)
#define MD_SS_DISABLED                    ('D' << 24 | 'S' << 16 | 'B' << 8 | 'L' << 0)

/* Macros defined to match AES-256 CTR mode encryption */
#define MD_AES_KEY_SIZE                   32
#define MD_AES_IV_SIZE                    16
#define MD_AES_MAC_SIZE                   32
#define MD_HMAC_KEY_SIZE                  32
#define MD_RSA_KEY_LEN                    256 // 2048bits

//sizes in bytes
#define MD_VERSION_SIZE 2
#define MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE    (MD_AES_KEY_SIZE + MD_HMAC_KEY_SIZE + MD_VERSION_SIZE)

#define MD_CONTEXT_XBL_SC "XBL_SC_MINI_CTX"
#define MD_CONTEXT_XBL_RD "XBL_RD_MINI_CTX"

static uint8  ALIGN(32)           minidump_version[MD_VERSION_SIZE] = {0x00,0x01};// format is MSB : LSB -> Major Version : Minor Version

typedef  enum
{
  MD_SS_HLOS       = 0,
  MD_SS_QSEE       = 1,
  MD_SS_QHEE       = 2,
  MD_SS_MPSS       = 3,
  MD_SS_CNSS       = 4,
  MD_SS_LPASS      = 5,
  MD_SS_SLPI       = 6,
  MD_SS_CSS        = 7,
  MD_SS_SP         = 8,
  MD_SS_AOP        = 9,
  MD_SS_HLOS_GVM1  = 10,
  MD_SS_HLOS_GVM2  = 11,
  MD_SS_CPUCP      = 12,
  MD_SS_TME        = 13,
  MD_SS_BOOT       = 14,
  MD_SS_XBL_SC     = 15,
  MD_SS_UEFI       = 16,
  MD_SS_SHRM       = 17,
  MD_SS_HYP_VM     = 18,
  MD_SS_MAX        = 19,
  MD_SS_UNKNOWN    = 0x7FFFFFFF,
}md_subsys_type;

/* SMEM region struct */
typedef struct
{
  uint8     region_name[MD_REGION_NAME_LENGTH];
  uint32    seq_num;        /* provision to allow unique naming */
  uint32    md_valid;       /* To dump or not */
  uint64    region_base_address;
  uint64    region_size;
}  md_ss_region;

/* minidump SMEM SubSystem region */
typedef struct  /* SS SMEM ToC struct */
{
   uint32       md_ss_toc_init;
   uint32       md_ss_enable_status;
   uint32       encryption_status;
   uint32       encryption_required;
   uint32       ss_region_count; /*region count */
   uint64       md_ss_smem_regions_baseptr;
}  md_ss_toc;

/* SMEM struct minidump_smem_global region */
typedef struct
 {
   uint32       md_toc_init;
   uint32       md_revision;
   uint32       md_enable_status;
   md_ss_toc    md_ss_toc[MD_SS_MAX];
}  md_global_toc;

typedef struct
{
  uintnt region_base_address;
  uintnt region_size;
  char   region_name[MD_REGION_NAME_LENGTH];
}boot_minidump_region_type;
/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
/*===========================================================================
**  Function :  boot_md_get_global_mdtoc_addr
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the global minidump toc if it is initialized
* 
* @param
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   md_global_toc* Pointer to the global minidump toc
* 
* @par Side Effects
*   None
* 
*/
md_global_toc* boot_md_get_global_mdtoc_addr(void);

/*===========================================================================
**  Function :  boot_md_is_valid_global_mdtoc(void)
** ==========================================================================
*/
/*!
* 
* @brief
*   This function checks global minidump ToC validity
* 
* @param
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   boot_boolean returns TRUE if global minidump ToC is present and valid
* 
* @par Side Effects
*   None
* 
*/
boot_boolean boot_md_is_valid_global_mdtoc(void);

/*===========================================================================
**  Function :  boot_md_get_subsystem_toc
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the subsystem ToC address
* 
* @param
*   md_subsys_type sub-system index
*        
* @par Dependencies
*   None
*   
* @retval
*   md_ss_toc* Pointer to the sub-system minidump toc
* 
* @par Side Effects
*   None
* 
*/
md_ss_toc* boot_md_get_subsystem_toc(md_subsys_type ss_id);

/*===========================================================================
**  Function :  boot_add_minidump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table
* 
* @param
*   char*  Name of the region
*   uint64 Base address
*   uint64 Size
*        
* @par Dependencies
*   None
*   
* @retval
*   boolean TRUE if region added, FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_add_minidump_region(md_subsys_type ss_id, char rg_name[MD_REGION_NAME_LENGTH], uint64 rg_base_addr, uint64 rg_size);

/*===========================================================================
**  Function :  boot_minidump_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes Boot minidump sub-system toc
* 
* @param
*   md_ss                 [in]     subsystem index
*   md_ss_enable_status   [in]     subsystem enable status
*   encryption_required   [in]     encryption required status of subsystem
*   encryption_status     [in]     encryption status of sybsystem
*   ss_baseptr            [in]     address of subsystems region table
*
* @par Dependencies
*   None
*   
* @retval
*   boolean TRUE if init is successful, FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_minidump_init(md_subsys_type ss_id, uint32 md_ss_enable_status, uint32 encryption_required, uint32 encryption_status, uintnt ss_baseptr);


/*===========================================================================
**  Function :  boot_init_encryption_artifacts
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes encryption artifacts required to encrypt regions
* 
* @param
*   config_context_handle [in]    boot handle to get interfaces from config context
*   md_region_count       [in]    region count required to allocate memory for encryption artifacts
* @par Dependencies
*   None
*   
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_init_encryption_artifacts(boot_handle config_context_handle, uint32 md_region_count, uint8 *context);

/*===========================================================================
**  Function :  boot_encrypt_minidump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function encrypts a region and updates IV and MAC in encryption artifacts
* 
* @param
*   md_region_in      [in]     input buffer
*   md_region_in_size [in]     input buffer length
*   md_region_out     [in]     pointer to output buffer
* 
* @par Dependencies
*   None
* 
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_encrypt_minidump_region(uintnt * md_region_in, uintnt md_region_in_size, uintnt * md_region_out);

/*===========================================================================
**  Function :  boot_get_encryption_artifacts
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the encryption 
*   artifacts (Wrapped key & size, IV buffer and size, MAC buffer and size)
* 
* @param
*   wrapped_key        [out] pointer to wrapped key buffer
*   wrapped_key_size   [out] pointer to store wrapped key buffer size
*   iv_buffer          [out] pointer to IV buffer
*   iv_buffer_size     [out] pointer to store IV buffer size
*   mac_buffer         [out] pointer to MAC buffer
*   mac_buffer_size    [out] pointer to store MAC buffer size
*
* @par Dependencies
*   None
*   
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_get_encryption_artifacts(uint8 ** wrapped_key, uint32 * wrapped_key_size, uint8 ** iv_buffer, uint32 * iv_buffer_size, uint8 ** mac_buffer, uint32 * mac_buffer_size);

/*===========================================================================
**  Function :  boot_encrypt_and_get_md_regions
** ==========================================================================
*/
/*!
* 
* @brief
*   This function performs encryption based on auth enabled state and returns minidump region list to caller
* 
* @param
*   config_context_handle     [in]    boot_handle
*   context                   [in]    plaintext context
*   is_auth_enabled           [in]    auth enabled state
*   region_table              [out]   pointer to minidump region table
*   region_count              [out]   pointer to store region table size
*        
* @par Dependencies
*   None
*   
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_encrypt_and_get_md_regions(boot_handle config_context_handle, boot_boolean is_auth_enabled, uint8 *context, boot_minidump_region_type ** region_table, uint32 *region_count);

/*===========================================================================
**  Function :  boot_get_md_region_count
** ==========================================================================
*/
/*!
* 
* @brief
*   This function gets the number of regions in minidump table
* 
* @param
*   md_region_count  [out]  total number of minidump regions
*        
* @par Dependencies
*   minidump table must be initialized in SMEM
*   
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_get_md_region_count(uint32 *md_region_count);

#endif  /* BOOT_MINIDUMP_H */

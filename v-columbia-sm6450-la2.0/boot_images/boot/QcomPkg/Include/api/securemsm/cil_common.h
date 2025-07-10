#ifndef _CIL_COMMON_H
#define _CIL_COMMON_H
/*===========================================================================

                   Common Crypto Interface Library API's

DESCRIPTION
  Contains wrapper definition Crypto Interface Library

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright (c) 2017,2018,2021 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/07/21   rama    change return type to bl_error_boot_type
07/19/21   rama    Unify cil_loader.h and cil_ramdump.h
06/02/21   ds      minidump changes
10/12/17   aus     Updated to support minidump
25/04/17   bd      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_comdef.h>
#include <boot_error_if.h>
#include <xbl_minidump_key_struct.h>
#include <boot_minidump.h>


#define XBL_CIPHER_MAX_MEM  1

/*===========================================================================
**  Function :  boot_encr_aes_key
** ==========================================================================
*/
/**
 * @brief Encrypt aes key
 *
 * @param in [in]      pointer to input aes key
 * @param inlen [in]   length of the input key
 * @param out [in]     pointer to output buffer to store encrypted key 
 * @param out_len [in]  output buffer length
 *
 * @return  bl_error_boot_type
 *
 */
bl_error_boot_type boot_encr_aes_key (uint8 *in, uint32 inlen, uint8 *out, uint32 *outlen);

/*===========================================================================
**  Function :  boot_check_oem_key
** ==========================================================================
*/
/**
 * @brief Check if the OEM key is valid
 * 
 * @param in [in]     pointer to store oem_key status
 * 
 * @return  bl_error_boot_type
 *
 */
bl_error_boot_type boot_check_oem_key(boolean *);

/*===========================================================================
**  Function :  boot_sw_cipher
** ==========================================================================
*/
/**
 * @brief Encrypt the given buffer
 *
 * @param in [in]      pointer to input data
 * @param in_len [in]  pointer to input data length
 * @param out [in]     pointer to output encrypted data
 * @param out_len [in] pointer to output buffer length
 * @param key [in]     AES key
 * @param key_len [in]  AES key length
 * @param nonce [in]     IV key
 * @param nonce_len [in]  IV key length
 * @param tag [out]       TAG output from crypto driver   
 * @param tag_len [in]    TAG buffer length
 * @param dir [in]        dir; false: encrypt, true: decrypt
 *
 * @return  bl_error_boot_type
 *
 */
bl_error_boot_type boot_sw_cipher (
   void   *in, 
   size_t  in_len, 
   void   *out, 
   size_t  out_len,
   void   *key_aes, 
   size_t  key_aes_len,
   void   *key_hmac, 
   size_t  key_hmac_len,
   void   *nonce, 
   size_t  nonce_len,
   void   *tag,
   size_t  tag_len,
   boolean    dir                    //false: encrypt, true: decrypt
);

/*===========================================================================

**  Function :  cil_md_crypto_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Perform encryption initiliazation
*   
*
* @par Dependencies
*   
*   
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type cil_md_crypto_init(void);

/*===========================================================================

**  Function :  cil_md_encrypt_region

** ==========================================================================
*/
/*!
* 
* @brief
*   Perform in-place encryption of the given region
*
* @par Dependencies   
*   
*   
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type cil_md_encrypt_region(uint64 r_base, uint64 r_len, uint32 r_num);

/*===========================================================================

**  Function :  cil_md_add_unencr_regions

** ==========================================================================
*/
/*!
* 
* @brief
*   Adds the encryption key regions to debug table
*
* @par Dependencies
*   This api Must be called AFTER cil_md_encrypt_region has been called for all regions
*   
* @retval
*   None                                                               
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type cil_md_add_unencr_regions(void *handle);

#endif /* _CIL_COMMON_H */

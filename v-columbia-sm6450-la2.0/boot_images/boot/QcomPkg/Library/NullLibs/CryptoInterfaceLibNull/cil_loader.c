/*===========================================================================

                    BOOT EXTERN ENCRYPTION DEFINITIONS

DESCRIPTION
  Crypto Interface Library API's for XBL Loader

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright (c) 2017 - 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/07/21   rama    Changes for error handling
07/19/21   rama    Add cil_common.h
05/29/20   rama    Replace boot_extern_crypto_interface.h with boot_crypto_if.h
03/26/19   jp      Removed aes_share switching to UCLib implementation via CeML API
10/12/17   aus     Updated to support minidump
25/04/17   bd      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include <crypto/secmath.h>
#include <crypto/secrsa.h>

#include <xbl_minidump_oem_public_key.h>
#include "boot_logger.h"
#include <cil_common.h>
#include <boot_crypto_if.h>
  
/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/*===========================================================================
**  Function :  boot_oem_get_pub_key
** ==========================================================================
*/
/**
 * @brief Update the OEM public key
 *
 */
bl_error_boot_type boot_oem_get_pub_key(char** pub_mod_ptr, uint32* pub_mod_len, char** pub_exp_ptr, uint32* pub_exp_len)
{
  return BL_ERR_NONE;
}

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
bl_error_boot_type boot_encr_aes_key (uint8 *in, uint32 inlen, uint8 *out, uint32 *outlen)
{
  return BL_ERR_NONE;
}

/*===========================================================================
**  Function :  boot_check_oem_key
** ==========================================================================
*/
/**
 * @brief Check if the OEM key is valid
 *
 */
bl_error_boot_type boot_check_oem_key(boolean * result)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(result == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  *result = TRUE;

exit:
  return status;
}

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
bl_error_boot_type boot_sw_cipher
(   
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
)
{
  return BL_ERR_NONE;
}


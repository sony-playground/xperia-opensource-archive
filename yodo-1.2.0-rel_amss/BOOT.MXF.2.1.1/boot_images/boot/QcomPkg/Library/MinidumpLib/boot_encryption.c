/*===========================================================================

                    BOOT ENCRYPTION LIB

DESCRIPTION
  Common APIs required to perform encryption

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright (c) 2017-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/10/22   rama    Changes for moving minidump to ECDH encryption
01/06/22   rama    Renamed file to boot_encryption.c and moved to MinidumpLib.
10/07/21   rama    changes for error handling
07/19/21   rama    rename cil_loader.c to cil_common.c
06/02/21   ds      minidump changes
05/29/20   rama    Replace boot_extern_crypto_interface.h with boot_crypto_if.h
03/26/19   jp      Removed aes_share switching to UCLib implementation via CeML API
10/12/17   aus     Updated to support minidump
25/04/17   bd      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include <uclib.h>
#include <boot_encryption.h>
#include <boot_seclib_if.h>

static boolean is_oem_public_key_valid = FALSE;
/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/*===========================================================================
**  Function :  generate_random_value
** ==========================================================================
*/
/*!
*
* @brief
*
* @param
*   buffer   [out]         pointer to store the random number
*   size     [in]    length of random number to be generated in bytes
*
* @par Dependencies
*   BL_ERR_NONE on success
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type generate_random_value(uint8 *buffer, size_t size)
{

  bl_error_boot_type status = BL_ERR_NONE;

  if(buffer == NULL || size == 0)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_NULL_PTR_PASSED);
  }
  else if(uclib_get_prng_data(ucenv_get_env(), buffer, size) != size)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
  }

  return status;
}

/*===========================================================================
**  Function :  boot_check_oem_key
** ==========================================================================
*/
/*!
*
* @brief API to check the OEM key status
*
* @param
*   is_valid  [out]   pointer to store OEM key status
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
bl_error_boot_type boot_check_oem_key(boolean * is_valid)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(is_valid == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  *is_valid = is_oem_public_key_valid;

exit:
  return status;
}


/*===========================================================================
**  Function :  boot_encr_aes_key
** ==========================================================================
*/
/*!
*
* @brief API to perform RSA encryption of AES keys
*
* @param[in]
*   in      [in]   pointer to input aes key
*   inlen   [in]   length of the input key
*   out     [out]   pointer to output buffer to store encrypted key
*   out_len [out]   output buffer length
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
bl_error_boot_type boot_encr_aes_key (boot_handle config_context_handle, 
                                      uint8 *in, 
                                      uint32 inlen, 
                                      uint8 *out, 
                                      uint32 *outlen, 
                                      uint8 *context)
{
  bl_error_boot_type       status = BL_ERR_NONE;
  boot_seclib_if_type *seclib_if = NULL;

  do
  {
    if(config_context_handle == NULL || in == NULL 
       || inlen <= 0 || out == NULL 
       || outlen == NULL || context == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SECLIB_INTERFACE, (void **)&seclib_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }
    if(seclib_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    status = seclib_if->wrap_blob_with_oem_pub_key(in, inlen, out, outlen, context);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    is_oem_public_key_valid = TRUE;
  } while (FALSE);

  return status;
}

/*===========================================================================
**  Function :  boot_sw_cipher
** ==========================================================================
*/
/*!
*
* @brief Encrypt the given buffer
*
* @param
*   in        [in]   pointer to input data
*   in_len    [in]   pointer to input data length
*   out       [in]   pointer to output encrypted data
*   out_len   [in]   pointer to output buffer length
*   key       [in]   AES key
*   key_len   [in]   AES key length
*   nonce     [out]  IV key
*   nonce_len [in]   IV key length
*   tag       [out]  TAG output from crypto driver
*   tag_len   [in]   TAG buffer length
*   dir       [in]   dir; true: encrypt, false: decrypt
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
   boolean    dir                    //true: encrypt, false: decrypt
)
{
  bl_error_boot_type status = BL_ERR_NONE;
  size_t osz_final = 0;
  size_t osz_update=0;
  /* cipher params */
  UCLIB_CIPHER_HANDLE h_cipher = uclib_cipher_new(ucenv_get_env());
  UCLIB_CIPHER_ALG uclib_cipher_alg = UCLIB_AES256;
  UCLIB_CIPHER_MODE mode = UCLIB_CTR;
  
  /* hmac params */
  UCLIB_MAC_HANDLE h_mac = uclib_mac_new(ucenv_get_env());
  UCLIB_HASH_ALG hash_alg = UCLIB_SHA2_256;
  
  /* Crypto engine */
  UCLIB_ENGINE_TYPE engine = UCLIB_CE_ARMV8;
  
  /* Digest Size */
  size_t digest_sz = 0;

  if( !in  || !out  || !key_aes || !key_hmac || !nonce  || !tag || !h_cipher || !h_mac)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  status = generate_random_value(nonce, nonce_len);
  if(status != BL_ERR_NONE)
  {
    goto exit;
  }

  if(uclib_cipher_init(h_cipher, uclib_cipher_alg, mode, engine, dir) != UCLIB_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }

  //Set parameters so we can do the encrypt/decrypt
  if(uclib_cipher_ctrl(h_cipher, UCLIB_CIPHER_SET_KEY, 0, (uint8_t *)key_aes, key_aes_len, NULL) != UCLIB_SUCCESS ||
     uclib_cipher_ctrl(h_cipher, UCLIB_CIPHER_SET_IV, 0, (uint8_t *)nonce, nonce_len, NULL) != UCLIB_SUCCESS
    )
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }
  
  if(uclib_cipher_update(h_cipher, (uint8_t *)in, in_len,(uint8_t *)out, out_len, &osz_update) != UCLIB_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }
  
  if(out_len - osz_update)
  {
    if(uclib_cipher_final(h_cipher, (uint8_t *)(out + osz_update), out_len - osz_update, &osz_final) != UCLIB_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
    }
  }    
  out_len = (uint32)(osz_update + osz_final);
  
  if(uclib_mac_init(h_mac, UCLIB_MAC_HMAC, engine) != UCLIB_SUCCESS ||
  uclib_mac_ctrl(h_mac, UCLIB_MAC_PARAM_SET_HASH_ALG, hash_alg, NULL, 0, NULL) != UCLIB_SUCCESS ||
  uclib_mac_ctrl(h_mac, UCLIB_MAC_PARAM_SET_KEY, 0, (uint8_t *)key_hmac, (size_t)key_hmac_len, NULL) != UCLIB_SUCCESS
  )
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }

  if(uclib_mac_update(h_mac, (uint8_t *)out,(size_t)out_len) != UCLIB_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }  

  if(uclib_mac_ctrl(h_mac, UCLIB_MAC_PARAM_GET_DIGEST_SIZE, 0, (uint8_t *)&digest_sz, sizeof(digest_sz), NULL) != UCLIB_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }
  
  if(tag_len < digest_sz)
  {
    uint8_t digest_temp[16];
    if (uclib_mac_final(h_mac, (uint8_t *)digest_temp, (size_t)sizeof(digest_temp)) != UCLIB_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }
    memscpy(tag, (size_t)(tag_len<16?tag_len:16), (void *)digest_temp, (size_t)sizeof(digest_temp));
  }
  else if(uclib_mac_final(h_mac, (uint8_t *)tag, (size_t)tag_len) != UCLIB_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }
  
  if(h_cipher != NULL)
    if(uclib_cipher_free(h_cipher) != UCLIB_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }
  if(h_mac != NULL)
    if(uclib_mac_free(h_mac) != UCLIB_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }

exit:
  return status;
}


/*===========================================================================

                    BOOT EXTERN ENCRYPTION DEFINITIONS

DESCRIPTION
  Common Crypto Interface Library API's

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
#include <crypto/secmath.h>
#include <crypto/secrsa.h>
#include "boot_logger.h"
#include <cil_common.h>
#include <uclib.h>
#include <boot_config_context.h>
#include <DTBExtnLib.h>

#define BOOT_PUB_KEY_NODE "/sw/oem_pub_key"
#define BOOT_PUB_KEY_BITLEN_PROP "bitLen"
#define BOOT_PUB_KEY_MOD_PROP "n"
#define BOOT_PUB_KEY_EXP_PROP "e"
/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

static raw_key_t raw_key = {0};
static boolean is_oem_public_key_valid = FALSE;

/*===========================================================================
**  Function :  boot_oem_free_key
** ==========================================================================
*/
/**
 * @brief Frees memory allocated for OEM key
 *
 */
static bl_error_boot_type boot_oem_free_pub_key(void)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
  if(status != BL_ERR_NONE)
  {
    goto exit;
  }
  if(raw_key.n != NULL)
  {
    status = mem_if->free(raw_key.n);
    if(status != BL_ERR_NONE)
    {
      goto exit;
    }
  }
  if(raw_key.e != NULL)
  {
    status = mem_if->free(raw_key.e);
    if(status != BL_ERR_NONE)
    {
      goto exit;
    }
  }

exit:
  return status;
}

/*===========================================================================
**  Function :  boot_oem_get_pub_key
** ==========================================================================
*/
/**
 * @brief Update the OEM public key
 *
 */
static bl_error_boot_type boot_oem_get_pub_key(char** pub_mod_ptr, uint32* pub_mod_len, char** pub_exp_ptr, uint32* pub_exp_len)
{
  bl_error_boot_type status = BL_ERR_NONE, temp_status = BL_ERR_NONE;
  void *fdt_handle = NULL;
  fdt_node_handle node;
  int ret_val = 0;
  uint32 mod_len = 0;
  uint32 exp_len = 0;
  boot_memory_mgr_if_type *mem_if = NULL;

  do
  {
    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE || mem_if == NULL)
    {
      goto exit;
    }

    ret_val = fdt_get_blob_handle(&fdt_handle, DEFAULT_BLOB_ID);
    if(ret_val != 0 || fdt_handle == NULL)
    {
      goto exit;
    }

    ret_val = fdt_get_node_handle(&node, fdt_handle, BOOT_PUB_KEY_NODE);
    if(ret_val != 0)
    {
      goto exit;
    }

    ret_val = fdt_get_uint32_prop(&node, BOOT_PUB_KEY_BITLEN_PROP, &(raw_key.bitLength));
    if(ret_val != 0)
    {
      goto exit;
    }

    ret_val = fdt_get_prop_size(&node, BOOT_PUB_KEY_MOD_PROP, &mod_len);
    if(ret_val != 0)
    {
      goto exit;
    }

    status = mem_if->malloc(mod_len, (void *)(&(raw_key.n)));
    if(status != BL_ERR_NONE || raw_key.n == NULL)
    {
      goto exit;
    }

    ret_val = fdt_get_string_prop_list(&node, BOOT_PUB_KEY_MOD_PROP, raw_key.n, mod_len);
    if(ret_val != 0)
    {
      goto exit;
    }

    ret_val = fdt_get_prop_size(&node, BOOT_PUB_KEY_EXP_PROP, &exp_len);
    if(ret_val != 0)
    {
      goto exit;
    }

    status = mem_if->malloc(exp_len, (void *)(&(raw_key.e)));
    if(status != BL_ERR_NONE || raw_key.e == NULL)
    {
      goto exit;
    }

    ret_val = fdt_get_string_prop_list(&node, BOOT_PUB_KEY_EXP_PROP, raw_key.e, exp_len);
    if(ret_val != 0)
    {
      goto exit;
    }

    *pub_mod_ptr = raw_key.n;
    *pub_exp_ptr = raw_key.e;
    *pub_mod_len = (raw_key.bitLength)/8;
    *pub_exp_len = (raw_key.bitLength)/8;

    is_oem_public_key_valid = TRUE;

    return status;
  }while(FALSE);

exit:
  temp_status = boot_oem_free_pub_key();
  if(status == BL_ERR_NONE)
  {
    status = temp_status;
  }

  return status;
}

/*===========================================================================
**  Function :  boot_check_oem_key
** ==========================================================================
*/
/**
 * @brief Check if the OEM key is valid
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
  bl_error_boot_type       status = BL_ERR_NONE;
  CE_RSA_KEY               key;
  CE_RSA_OAEP_PAD_INFO     oaep_pad_info = {0};
  CE_RSA_PADDING_TYPE      padding_type  = CE_RSA_PAD_PKCS1_OAEP;
  void                     *padding_info  = NULL;
  char                     *mod = NULL;
  char                     *exp = NULL;
  uint32                   mod_len = 0;
  uint32                   exp_len = 0;  
  size_t                   keyByteLength;
  uint8                    key_e[sizeof(S_BIGINT)];
  uint8                    key_N[sizeof(S_BIGINT)];
  CeErrorType              ce_result = CE_SUCCESS;


  if(in == NULL || inlen == 0 || out == NULL || outlen == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  status = boot_oem_get_pub_key(&mod,&mod_len,&exp,&exp_len);
  if(status != BL_ERR_NONE)
  {
    goto exit;
  }

  raw_key.n = (char*)mod;
  raw_key.e = (char*)exp;

  //oaep_pad_info.hashidx  = CE_HASH_IDX_SHA1;
  oaep_pad_info.hashidx  = CE_HASH_IDX_SHA256;
  oaep_pad_info.label    = NULL;
  oaep_pad_info.labellen = 0;
  padding_info = (void*)&oaep_pad_info;

  memset(&key, 0, sizeof(CE_RSA_KEY));
  raw_key.bitLength =2048;
  keyByteLength = raw_key.bitLength/8;

  key.e = ( S_BIGINT *)key_e;

  if(secmath_BIGINT_read_radix(&(key.e)->bi, raw_key.e, 16) != 0)
  {
    boot_log_message("No public key provisioned \n");
    memset(out, 0, *outlen);
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }

  (key.e)->bi.n = keyByteLength/sizeof(BLONG);
  (key.e)->sign = S_BIGINT_POS; // Positive

  key.N = ( S_BIGINT *)key_N;

  if(secmath_BIGINT_read_radix(&(key.N)->bi, raw_key.n, 16) != 0)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }

  (key.N)->bi.n = keyByteLength/sizeof(BLONG);
  (key.N)->sign = S_BIGINT_POS; // Positive

  key.type = CE_RSA_KEY_PUBLIC;
  key.bitLength = raw_key.bitLength;

  ce_result = ce_rsa_encrypt(&key, padding_type, padding_info, in, inlen, out, (int*)outlen);
  if(ce_result != CE_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }

  status = boot_oem_free_pub_key();

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
 * @param dir [in]        dir; true: encrypt, false: decrypt
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


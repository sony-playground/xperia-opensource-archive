/*===========================================================================

                    BOOT EXTERN ENCRYPTION DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external crypto drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright (c) 2017,2018,2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/07/21   rama    changes for error handling
07/19/21   rama    update cil_common.h
06/02/21   ds      minidump changes
05/29/20   rama    Removed boot_extern_crypto_interface.h
10/12/17   aus     Updated to support minidump
25/04/17   bd      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include <string.h>
#include <cil_common.h>
#include <boot_target.h>
#include <boot_ramdump_table.h>
#include <boot_ramdump_if.h>
#include <boot_error_if.h>
#include <uclib.h>
#include <boot_crypto_if.h>

static uint8  ALIGN(32)           dload_aes_key[MD_AES_KEY_SIZE];
static uint8  ALIGN(32)           dload_hmac_key[MD_HMAC_KEY_SIZE];
static uint8  ALIGN(32)           dload_aes_and_hmac_key_and_version[MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE];
static uint8  ALIGN(32)           dload_rsa_encr_key[MD_RSA_KEY_LEN];

static uint8  ALIGN(32)           dload_aes_key_iv[MAX_CRASHDUMP_TABLE_ENTRIES][MD_AES_IV_SIZE];
static uint8  ALIGN(32)           dload_aes_key_mac[MAX_CRASHDUMP_TABLE_ENTRIES][MD_AES_MAC_SIZE];



#define MD_UNENCR_MEMORY_REGION2 {(uintnt)dload_rsa_encr_key, MD_RSA_KEY_LEN, "Encrypted AES Key", "md_encr_key_aes.BIN"}
#define MD_UNENCR_MEMORY_REGION3 {(uintnt)dload_aes_key_iv, (MAX_CRASHDUMP_TABLE_ENTRIES*MD_RSA_KEY_LEN), "IV key region", "md_encr_key_iv.BIN"}
#define MD_UNENCR_MEMORY_REGION4 {(uintnt)dload_aes_key_mac, (MAX_CRASHDUMP_TABLE_ENTRIES*MD_RSA_KEY_LEN), "MAC region", "md_encr_key_mac.BIN"}

#define MD_UNENCR_MEMORY_REGION_TABLE MD_UNENCR_MEMORY_REGION2,MD_UNENCR_MEMORY_REGION3,MD_UNENCR_MEMORY_REGION4,MEMORY_REGION_LAST

size_t memscpy( void *dst, size_t dst_size, const void *src, size_t src_size);
 
/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/ 




static bl_error_boot_type generate_aes_iv(int i)
{

  bl_error_boot_type status = BL_ERR_NONE;

  if(uclib_get_prng_data(ucenv_get_env(), dload_aes_key_iv[i], MD_AES_IV_SIZE) != MD_AES_IV_SIZE)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INTERFACE_FAILURE);
  }

  return status;
}


static bl_error_boot_type generate_encr_aeskey(void)
{

  bl_error_boot_type status = BL_ERR_NONE;
  uint32  cipherlen = MD_RSA_KEY_LEN;
  uint32  offset = 0;

  env_t* env = ucenv_get_env();
  if(env == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_UCLIB_GET_ENV);
    goto exit;
  }

  if(uclib_get_prng_data(env, dload_aes_key, MD_AES_KEY_SIZE) != MD_AES_KEY_SIZE)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_UCLIB_GET_PRNG_DATA);
    goto exit;
  }

  if(uclib_get_prng_data(env, dload_hmac_key, MD_HMAC_KEY_SIZE) != MD_HMAC_KEY_SIZE)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_UCLIB_GET_PRNG_DATA);
    goto exit;
  }
  
  offset+=memscpy(dload_aes_and_hmac_key_and_version,MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE,dload_aes_key,(size_t)MD_AES_KEY_SIZE);
  offset+=memscpy(&dload_aes_and_hmac_key_and_version[offset],(MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE-offset),dload_hmac_key,MD_HMAC_KEY_SIZE);
  offset+=memscpy(&dload_aes_and_hmac_key_and_version[offset],(MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE-offset),minidump_version,MD_VERSION_SIZE);
   
  status = boot_encr_aes_key(dload_aes_and_hmac_key_and_version, MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE, dload_rsa_encr_key, &cipherlen);

exit:
  return status;
}

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
bl_error_boot_type cil_md_crypto_init(void)
{
  return generate_encr_aeskey();
}

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
bl_error_boot_type cil_md_encrypt_region(uint64 r_base, uint64 r_len, uint32 r_num)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint8 *iv, *mac;
 
  status = generate_aes_iv(r_num);
  if(status != BL_ERR_NONE)
  {
    goto exit;
  }


  iv = dload_aes_key_iv[r_num];
  mac = dload_aes_key_mac[r_num];

  status = boot_sw_cipher((void*)(r_base), r_len, 
                 (void*)(r_base), r_len, 
                 (void*)(&dload_aes_key[0]), MD_AES_KEY_SIZE,
                 (void*)(&dload_hmac_key[0]), MD_HMAC_KEY_SIZE, 
                 (void*)(iv), MD_AES_IV_SIZE,
                 (void*)(mac), MD_AES_MAC_SIZE,
                 TRUE);

exit:
  return status;
}

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
bl_error_boot_type cil_md_add_unencr_regions(void *handle)
{
    bl_error_boot_type status = BL_ERR_NONE;
    uint32 index;
    ramdump_table_memory_region dump_regions[] = {MD_UNENCR_MEMORY_REGION_TABLE};     
    
    index = 0;
    while ( dump_regions[index].region_base != 0x0 ) 
    {
      status = ramdump_table_add_entry(handle,
                                       RAMDUMP_TABLE_OPTIONAL_DEF_SAVE, 
                                       dump_regions[index].region_base,
                                       dump_regions[index].region_size,
                                       dump_regions[index].desc,
                                       dump_regions[index].filename
                                      );
      if (status != BL_ERR_NONE)
        break;

      index++;
    }

    return status;
}

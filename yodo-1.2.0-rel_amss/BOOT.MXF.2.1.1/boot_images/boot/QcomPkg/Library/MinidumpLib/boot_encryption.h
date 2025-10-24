#ifndef BOOT_ENCRYPTION_H
#define BOOT_ENCRYPTION_H
/*=============================================================================

                               Boot encryption
                               Header File
GENERAL DESCRIPTION
  This file provides the APIs for performing encryption

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
03/10/22   rama    Move wrapping operation to ECDH based encryption
11/18/21   rama    Initial version

=============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include "comdef.h"
#include "boot_config_context.h"
#include "boot_error_if.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/


/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

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
bl_error_boot_type generate_random_value(uint8 *buffer, size_t size);

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
bl_error_boot_type boot_check_oem_key(boolean * is_valid);

/*===========================================================================
**  Function :  boot_encr_aes_key
** ==========================================================================
*/
/*!
*
* @brief API to perform RSA encryption of AES keys
*
* @param[in]
*   config_context_handle [in]    handle required for querying interfaces from config context
*   in                    [in]    pointer to input aes key
*   inlen                 [in]    length of the input key
*   out                   [out]   pointer to output buffer of length SECLIB_WRAPPED_BLOB_AND_ENCR_INFO_LEN
*                                 to store encrypted key 
*   out_len               [out]   output buffer length
*   context               [in]    context string of length SECLIB_HKDF_CONTEXT_LEN
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
                                      uint8 *context);

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
);

#endif /* BOOT_ENCRYPTION_H */

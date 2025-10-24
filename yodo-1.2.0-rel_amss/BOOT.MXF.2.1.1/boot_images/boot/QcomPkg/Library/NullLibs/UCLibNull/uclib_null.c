 /*****************************************************************************
 * uclib_null.c
 *
 * Copyright (c) 2021 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================
                        Edit History


YYYY-MM-DD   who     what, where, why
----------   ---     ----------------------------------------------------------- 
2021-09-28   ck      Initial version

=============================================================================*/

#include "boot_crypto_if.h"


env_t * ucenv_get_env(void)
{
  return NULL;
}


size_t uclib_get_prng_data(env_t *env, uint8_t *buf, size_t buf_sz)
{
  return buf_sz;
}


UCLIB_MD_HANDLE uclib_hash_new(env_t *env)
{
  return NULL;
}


int uclib_hash_init(UCLIB_MD_HANDLE h, UCLIB_HASH_ALG alg, UCLIB_ENGINE_TYPE engine)
{
  return 0;
}


int uclib_hash_free(UCLIB_MD_HANDLE h)
{
  return 0;
}


int uclib_mac_free(UCLIB_MAC_HANDLE h)
{
  return 0;
}


int uclib_hash_update(UCLIB_MD_HANDLE h, const uint8_t *msg, size_t msg_sz)
{
  return 0;
}


int uclib_hash_final(UCLIB_MD_HANDLE h, uint8_t *dgst, size_t dgst_sz)
{
  return 0;
}


int uclib_mac_ctrl(UCLIB_MAC_HANDLE h,
                   UCLIB_MAC_PARAM_TYPE type,
                   int val,
                   uint8_t *buf,
                   size_t isz,
                   size_t *osz)
{
  return 0;
}


int uclib_hash_ctrl(UCLIB_MD_HANDLE h,
                    UCLIB_HASH_PARAM_TYPE type,
                    int val,
                    uint8_t *ibuf,
                    size_t isz,
                    size_t *osz)
{
  return 0;
}


UCLIB_CIPHER_HANDLE uclib_cipher_new(env_t *env)
{
  return NULL;
}


int uclib_cipher_init(UCLIB_CIPHER_HANDLE h,
                      UCLIB_CIPHER_ALG alg,
                      UCLIB_CIPHER_MODE mode,
                      UCLIB_ENGINE_TYPE engine,
                      bool  encrypt)
{
  return 0;
}


int uclib_cipher_ctrl(UCLIB_CIPHER_HANDLE h,
                      UCLIB_CIPHER_PARAM_TYPE type,
                      int val,
                      uint8_t *ibuf,
                      size_t isz,
                      size_t *osz)
{
  return 0;
}


int uclib_cipher_update(UCLIB_CIPHER_HANDLE h,
                        const uint8_t *ibuf, size_t isz,
                        uint8_t *obuf, size_t osz,
                        size_t *vld_osz)
{
  return 0;
}


int uclib_cipher_final(UCLIB_CIPHER_HANDLE h,
                       uint8_t *obuf, size_t osz,
                       size_t *vld_osz)
{
  return 0;
}


int uclib_cipher_free(UCLIB_CIPHER_HANDLE h)
{
  return 0;
}


UCLIB_MAC_HANDLE uclib_mac_new(env_t *env)
{
  return NULL;
}


int uclib_mac_init(UCLIB_MAC_HANDLE h,
                   UCLIB_MAC_ALG alg,
                   UCLIB_ENGINE_TYPE engine)
{
  return 0;
}


int uclib_mac_update(UCLIB_MAC_HANDLE h, const uint8_t *msg, size_t msg_sz)
{
  return 0;
}


int uclib_mac_final(UCLIB_MAC_HANDLE h,
                    uint8_t *dgst,
                    size_t dgst_sz)
{
  return 0;
}

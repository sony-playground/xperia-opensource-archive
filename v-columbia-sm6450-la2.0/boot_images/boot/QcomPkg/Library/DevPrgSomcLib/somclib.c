/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright 2012 Sony Mobile Communications AB.                              *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * Description: Implementation for sake authentication                        *
 *                                                                            *
 *****************************************************************************/
//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
#include "sake_root.h"
#include "somclib.h"
#include "sake_engine.h"
#include "sake_engine_internal.h"
#include "sake_alg.h"
#include "sake_cert.h"
#include "sake_hash.h"
#include "string.h"
#include "uclib.h" // For authentication
#include "secmath.h" // For authentication
#include "devprg_firehose.h"
#include "devprg_sha.h"
#include "devprg_security.h"
#include "fcserr.h"
#include "convert.h"

#include "FirehoseVersion.h"

void* somclib_malloc(size_t sz);
void somclib_free(void* ptr);

#ifdef FEATURE_DEVICEPROGRAMMER_SOMC
#define NONCE_LEN 20
static uint8_t *somc_fh_alloc_buffer_base = NULL;
static bool has_saved_data = false;
static uint8_t saved_rnd[NONCE_LEN];
static uint8_t saved_die_id_buf[sizeof(uint32_t)];
static bool is_authenticated = false;

static char* bin2ascii(const uint8_t* buf, size_t sz)
{
  const char digits[] = "0123456789abcdef";
  char* tmp;
  uint32_t i;
  unsigned char lo, hi;

  if ( (tmp = somclib_malloc(2*sz + 1)) == NULL)
    return NULL;

  for (i = 0; i < (2*sz - 1); i += 2)
  {
    hi = (buf[i>>1]&0xF0) >> 4;
    lo = (buf[i>>1]&0x0F) >> 0;

    tmp[i]   = (uint8_t)digits[hi];
    tmp[i+1] = (uint8_t)digits[lo];
  }

  tmp[i] = '\0';
  return tmp;
}
void somclib_setup()
{
  somc_fh_alloc_buffer_base = NULL;
  has_saved_data = false;
  is_authenticated = false;
}
bool somclib_is_authenticated()
{
    return is_authenticated;
}

typedef struct {
  void* ptr;
  size_t size;
  bool is_free;
} heap_memblock_t;

typedef struct {
  uint8_t* heap_free;
  heap_memblock_t* memblock;
  size_t num_memblocks;
} heap_head_t;
#define SOMC_DH_ALIGN 8
void somclib_setup_allocation(uint8_t *base, uint32_t size)
{
  heap_head_t* head_p = (heap_head_t*)base;
  head_p->heap_free = (uint8_t*)(base + sizeof(heap_head_t));
  head_p->memblock = (heap_memblock_t*)(base + size);
  head_p->num_memblocks = 0;
  somc_fh_alloc_buffer_base = base;
}
void somclib_teardown_allocation(void)
{
  somc_fh_alloc_buffer_base = NULL;
}
size_t get_num_memblocks(uint8_t *base_ptr)
{
  heap_head_t* head_p = (heap_head_t*)base_ptr;
  return head_p->num_memblocks;
}
size_t get_memblock_size(uint8_t *base_ptr, int idx)
{
  heap_head_t* head_p = (heap_head_t*)base_ptr;
  heap_memblock_t* memblock = head_p->memblock;
  return memblock[idx].size;
}
bool get_memblock_is_free(uint8_t *base_ptr, int idx)
{
  heap_head_t* head_p = (heap_head_t*)base_ptr;
  heap_memblock_t* memblock = head_p->memblock;
  return memblock[idx].is_free;
}
void* get_memblock_ptr(uint8_t *base_ptr, int idx)
{
  heap_head_t* head_p = (heap_head_t*)base_ptr;
  heap_memblock_t* memblock = head_p->memblock;
  return memblock[idx].ptr;
}
void set_memblock_free(uint8_t *base_ptr, int idx)
{
  heap_head_t* head_p = (heap_head_t*)base_ptr;
  heap_memblock_t* memblock = head_p->memblock;
  memblock[idx].is_free = true;
}
void unset_memblock_free(uint8_t *base_ptr, int idx)
{
  heap_head_t* head_p = (heap_head_t*)base_ptr;
  heap_memblock_t* memblock = head_p->memblock;
  memblock[idx].is_free = false;
}
void* add_memblock(uint8_t *base_ptr, size_t size)
{
  int align_sz = (size + SOMC_DH_ALIGN-1) & ~(SOMC_DH_ALIGN-1);
  heap_head_t* head_p = (heap_head_t*)base_ptr;
  if ((head_p->heap_free + align_sz + sizeof(heap_memblock_t)) < (uint8_t*)(head_p->memblock))
  {
    head_p->memblock = (heap_memblock_t*)((uint8_t*)(head_p->memblock) - sizeof(heap_memblock_t));
    head_p->memblock[0].ptr = (void*)(head_p->heap_free);
    head_p->heap_free += align_sz;
    head_p->memblock[0].size = size;
    head_p->memblock[0].is_free = false;
    (head_p->num_memblocks)++;
    return head_p->memblock[0].ptr;
  }
  else
  {
    return NULL;
  }
}
void* somclib_malloc(size_t sz)
{
  void* res = NULL;
  int align_sz = (sz + SOMC_DH_ALIGN-1) & ~(SOMC_DH_ALIGN-1);
  if (somc_fh_alloc_buffer_base != NULL)
  {
    int i;
    size_t num_memblocks = get_num_memblocks(somc_fh_alloc_buffer_base);
    int min_i = -1;
    size_t min_size = 0;
    for (i = 0; i < num_memblocks; i++)
    {
      if (get_memblock_is_free(somc_fh_alloc_buffer_base, i))
      {
        size_t cur_size = get_memblock_size(somc_fh_alloc_buffer_base, i);
        if (cur_size == align_sz)
        {
          res = get_memblock_ptr(somc_fh_alloc_buffer_base, i);
          unset_memblock_free(somc_fh_alloc_buffer_base, i);
          break;
        }
        else if ((cur_size > align_sz) &&
                 ((min_i == -1) || (min_size > cur_size)))
        {
          min_size = cur_size;
          min_i = i;
        }
      }
    }
    if (res == NULL)
    {
      if (min_i != -1)
      {
        res = get_memblock_ptr(somc_fh_alloc_buffer_base, min_i);
        unset_memblock_free(somc_fh_alloc_buffer_base, min_i);
      }
      else
      {
        res = add_memblock(somc_fh_alloc_buffer_base, align_sz);
      }
    }
  }
  return res;
}

void somclib_free(void* ptr)
{
  if ((ptr != NULL) && (somc_fh_alloc_buffer_base != NULL))
  {
    int i;
    size_t num_memblocks = get_num_memblocks(somc_fh_alloc_buffer_base);
    for (i = 0; i < num_memblocks; i++)
    {
      if (get_memblock_ptr(somc_fh_alloc_buffer_base, i) == ptr)
      {
        set_memblock_free(somc_fh_alloc_buffer_base, i);
        break;
      }
    }
  }
}

typedef struct
{
  sake_handle_t sake_handle;
  char *imei;
  char *die_id;
  uint8 rand_buf[255];
  size_t rand_buf_len;
  char *rev_str;
  uint16 ssn;
} authenticate_internal_handle_t;

typedef struct
{
  struct __sechsh_ctx_s hash_ctx;
} sechsharm_hash_context_t;


typedef enum{
  ITEM_ARRAY_EXPONENT = 1,
  ITEM_ARRAY_MODULUS
} item_array_type_t;

typedef struct{
  uint32_t length;
  uint8_t* data;
} item_array_t;

/*
 * Parses the length from an ASN.1 blob. For now, only length in the following formats
 * are supported:
 *
 * -------------------------------------------
 *     [ IDX ][idx+1][idx+2]
 * -------------------------------------------
 *     [<H7F ]
 * -------------------------------------------
 *     [ H81 ][ Hxx ]
 * -------------------------------------------
 *     [ H82 ][HMBxx][HLBxx]
 * -------------------------------------------
 */
static int asn1_get_length(uint8_t* asn1, uint32_t* idx, uint32_t* length)
{
  if(asn1[*idx] & 0x80){
    switch(asn1[*idx]){
      case 0x81:
        *length = asn1[*idx+1];
        *idx += 2;
      break;

      case 0x82:
        *length = (asn1[*idx+1] << 8) + asn1[*idx+2];
        *idx += 3;
      break;

      default:
        return -FCSERR_EINVAL;
    }
  }else{
    *length = asn1[*idx];
    (*idx)++;
  }

  return FCSERR_OK;
}

static int extract_public_key_parts(asn_rsa_public_key_t asn1, item_array_t* item, item_array_type_t item_array_type)
{
  uint32_t idx = 0;
  uint32_t length_total, length_modulus, length_exponent;
  uint8_t* modulus = NULL;
  uint8_t* exponent = NULL;
  int status = FCSERR_OK;

  if((!asn1) || (!item))
    return -FCSERR_EINVAL;

  // ASN.1 - START-TAG
  if(asn1[idx] != 0x30)
    return -FCSERR_EINVAL;

  idx++;
  // ASN.1 - TOTAL LENGTH
  status = asn1_get_length(asn1, &idx, &length_total);
  if(status != FCSERR_OK)
    return status;

  // ASN.1 - LENGTH MODULUS
  if(asn1[idx] != 0x02)
    return -FCSERR_EINVAL;

  idx++;
  status = asn1_get_length(asn1, &idx, &length_modulus);
  if(status != FCSERR_OK)
    return status;

  // ASN.1 - KEYDATA - MODULUS
  modulus = &asn1[idx];
  idx += length_modulus;

  // ASN.1 - LENGTH EXPONENT
  if(asn1[idx] != 0x02){
    return -FCSERR_EINVAL;
  }
  idx++;
  status = asn1_get_length(asn1, &idx, &length_exponent);
  if(status != FCSERR_OK)
    return status;

  // ASN.1 - KEYDATA - EXPONENT
  exponent = &asn1[idx];
  idx += length_exponent;

  switch(item_array_type){
    case ITEM_ARRAY_EXPONENT:
      item->data = exponent;
      item->length = length_exponent;
    break;
    case ITEM_ARRAY_MODULUS:
      item->data = modulus;
      item->length = length_modulus;
    break;

    default:
      status = -FCSERR_EINVAL;
    break;
  }

  return status;
}

static int rsa_encrypt_nopad(
   const uint8 *in_buffer_p,
   size_t in_buffer_size,
   uint8 *out_buffer_p,
   size_t out_buffer_size,
   const asn_rsa_public_key_t public_key)
{
    SECMATH_ERRNO_ET secmath_result;
    BigInt *mod, *exp, *sign, *encres;
    int result = FCSERR_OK;

    if (in_buffer_p == NULL || out_buffer_p == NULL || public_key == NULL)
      return -FCSERR_EINVAL;

    mod = (BigInt*)somclib_malloc(sizeof(BigInt));
    exp = (BigInt*)somclib_malloc(sizeof(BigInt));
    sign = (BigInt*)somclib_malloc(sizeof(BigInt));
    encres = (BigInt*)somclib_malloc(sizeof(BigInt));
    if (mod == NULL || exp == NULL || sign == NULL || encres == NULL)
      return -FCSERR_ENOMEM;

    memset((uint8 *)mod,0,sizeof(BigInt));
    memset((uint8 *)exp,0,sizeof(BigInt));
    memset((uint8 *)sign,0,sizeof(BigInt));
    memset((uint8 *)encres,0,sizeof(BigInt));

    item_array_t item_m, item_e;
    result = extract_public_key_parts(public_key, &item_m, ITEM_ARRAY_MODULUS);
    if (result != FCSERR_OK)
      goto error;

    result = extract_public_key_parts(public_key, &item_e, ITEM_ARRAY_EXPONENT);
    if (result != FCSERR_OK)
      goto error;

    secmath_result = secmath_BIGINT_read_unsigned_bin(mod,
                                      (const uint8 *)item_m.data,
                                       item_m.length);
    if (E_SECMATH_SUCCESS != secmath_result)
    {
      result = -FCSERR_ENIMP;
      goto error;
    }

    secmath_result = secmath_BIGINT_read_unsigned_bin(exp,
                                      (const uint8 *)item_e.data,
                                       item_e.length);
    if (E_SECMATH_SUCCESS != secmath_result)
    {
      result = -FCSERR_ENIMP;
      goto error;
    }

    secmath_result = secmath_BIGINT_read_unsigned_bin(sign,
                                       (const uint8 *)in_buffer_p,
                                       in_buffer_size);
    if (E_SECMATH_SUCCESS != secmath_result)
    {
      result = -FCSERR_ENIMP;
      goto error;
    }

    secmath_result = secmath_BIGINT_modexp(encres, sign,
                               exp, mod);
    if (E_SECMATH_SUCCESS != secmath_result)
    {
      result = -FCSERR_ENIMP;
      goto error;
    }

    secmath_result = secmath_BIGINT_to_unsigned_bin(
      encres,
      out_buffer_p,
      out_buffer_size);
    if (E_SECMATH_SUCCESS != secmath_result)
    {
      result = -FCSERR_ENIMP;
      goto error;
    }

error:
  somclib_free(mod);
  somclib_free(exp);
  somclib_free(sign);
  somclib_free(encres);

  return result;
}

static int hash_init(hash_context_t* context,
                     hash_type_t hash_type)
{
  int res = FCSERR_OK;
  sechsharm_hash_context_t *new_context = NULL;

  if (context == NULL)
    return -FCSERR_EINVAL;
  if (hash_type != SHA256_HASH)
    return -FCSERR_ENIMP;


  new_context = somclib_malloc(sizeof(sechsharm_hash_context_t));
  if (new_context == NULL)
    return -FCSERR_ENOMEM;

  sechsharm_sha256_init(&new_context->hash_ctx);
  *context = (hash_context_t)new_context;

  return res;
}

static int hash_update(hash_context_t context,
                       const uint8_t* data,
                       size_t length)
{
  sechsharm_hash_context_t* ctx = (sechsharm_hash_context_t*)context;

  if (ctx == NULL || data == NULL)
    return -FCSERR_EINVAL;

  sechsharm_sha256_update(&ctx->hash_ctx, ctx->hash_ctx.leftover, &ctx->hash_ctx.leftover_size,
                         (uint8_t *)data, length);

  return FCSERR_OK;
}

static int hash_final(hash_context_t context,
                       uint8_t* digest,
                       size_t digest_size)
{
  sechsharm_hash_context_t* ctx = (sechsharm_hash_context_t*)context;

  if (ctx == NULL || digest == NULL || digest_size < HASH_SIZE)
    return -FCSERR_EINVAL;

  sechsharm_sha256_final(&ctx->hash_ctx, ctx->hash_ctx.leftover,
                         &ctx->hash_ctx.leftover_size, digest);
  return FCSERR_OK;
}

static int hash_deinit(hash_context_t context)
{
  somclib_free(context);
  context = NULL;
  return FCSERR_OK;
}

static int hash_get_hash_size(hash_context_t context, size_t* size_p)
{
  *size_p = HASH_SIZE;
  return FCSERR_OK;
}

int somclib_cmd_authenticate(
  uint8_t *buf, uint16_t *state, size_t *buf_len,
  uint16_t *sake_method, uint8_t *level)
{
  uint32_t die_id;
  uint8_t die_id_buf[sizeof(die_id)];
  int res = FCSERR_OK;
  authenticate_internal_handle_t *authenticate_handle = NULL;
  const struct sake_setup *sake_data;

  #ifdef FEATURE_SOMC_TEST_ROOT
  sake_data = &sake_data_test;
  #else
  sake_data = &sake_data_live;
  #endif //FEATURE_SOMC_TEST_ROOT

  if (buf == NULL)
    return -FCSERR_EINVAL;

  authenticate_handle = (authenticate_internal_handle_t*)somclib_malloc(sizeof(authenticate_internal_handle_t));
  if (authenticate_handle == NULL)
    return -FCSERR_ENOMEM;
  memset(authenticate_handle, 0, sizeof(authenticate_internal_handle_t));


  size_t rnd_result = 0;
  size_t hello_msg_len = 0;
  struct sake_ext_functions sake_ext_funcs;

  sake_ext_funcs.hash_functions.hash_init = hash_init;
  sake_ext_funcs.hash_functions.hash_update = hash_update;
  sake_ext_funcs.hash_functions.hash_final = hash_final;
  sake_ext_funcs.hash_functions.hash_deinit = hash_deinit;
  sake_ext_funcs.hash_functions.hash_get_hash_size = hash_get_hash_size;
  sake_ext_funcs.rsa_functions.encrypt_no_pad = rsa_encrypt_nopad;

  authenticate_handle->ssn = 1;
  authenticate_handle->imei = NULL;
  authenticate_handle->rev_str = FIREHOSE_REV_STR;
  authenticate_handle->rand_buf_len = NONCE_LEN;

  switch (*state)
  {
    case 0:
      #define DIE_ID_ADDR 0x221c8610
      die_id = *(uint32_t *)DIE_ID_ADDR;

      die_id_buf[0] = (die_id & 0xFF000000) >> 24;
      die_id_buf[1] = (die_id & 0x00FF0000) >> 16;
      die_id_buf[2] = (die_id & 0x0000FF00) >> 8;
      die_id_buf[3] = (die_id & 0x000000FF);

      authenticate_handle->die_id = bin2ascii(die_id_buf, sizeof(die_id));
      rnd_result = uclib_get_prng_data(ucenv_get_env(),
                       authenticate_handle->rand_buf,
                       authenticate_handle->rand_buf_len
      );
      if (rnd_result != authenticate_handle->rand_buf_len)
      {
        res = -FCSERR_ESTATE;
        goto error;
      }

      res = sake_init(&authenticate_handle->sake_handle,
                (uint8_t *) sake_data->pub_hash,
                (uint8_t *) sake_data->rsa_pub_key,
                (uint8_t *) sake_data->crl,
                sake_ext_funcs
      );
      if (res != FCSERR_OK)
        goto error;

      res = sake_compose_hello_message(authenticate_handle->sake_handle,
                                       &hello_msg_len,
                                       authenticate_handle->rand_buf,
                                       authenticate_handle->rand_buf_len,
                                       authenticate_handle->imei,
                                       authenticate_handle->die_id,
                                       authenticate_handle->rev_str,
                                       authenticate_handle->ssn);
      if(res != FCSERR_OK || hello_msg_len == 0)
        goto error;

      res = sake_get_hello_message(authenticate_handle->sake_handle, buf, hello_msg_len);
      if (res != FCSERR_OK)
        goto error;
      *buf_len = hello_msg_len;
      memcpy(saved_rnd, authenticate_handle->rand_buf, NONCE_LEN);
      memcpy(saved_die_id_buf, die_id_buf, sizeof(uint32_t));
      has_saved_data = true;
    break;
    case 1:
      if (has_saved_data != true)
      {
          res = -FCSERR_ESTATE;
          goto error;
      }

      res = sake_init(&authenticate_handle->sake_handle,
                (uint8_t *) sake_data->pub_hash,
                (uint8_t *) sake_data->rsa_pub_key,
                (uint8_t *) sake_data->crl,
                sake_ext_funcs
      );
      if (res != FCSERR_OK)
        goto error;

      authenticate_handle->die_id = bin2ascii(saved_die_id_buf, sizeof(die_id));
      memcpy(authenticate_handle->rand_buf, saved_rnd, NONCE_LEN);

      res = sake_compose_hello_message(authenticate_handle->sake_handle,
                                       &hello_msg_len,
                                       saved_rnd,
                                       authenticate_handle->rand_buf_len,
                                       authenticate_handle->imei,
                                       authenticate_handle->die_id,
                                       authenticate_handle->rev_str,
                                       authenticate_handle->ssn);
      if(res != FCSERR_OK || hello_msg_len == 0)
        goto error;

      res = sake_check_response_message(authenticate_handle->sake_handle, buf, *buf_len);
      if  (res != FCSERR_OK)
        goto error;

      is_authenticated = true;
      has_saved_data = false;
    break;
  }

error:
  if (authenticate_handle != NULL)
  {
    somclib_free(authenticate_handle->die_id);
    somclib_free(authenticate_handle);
  }
  return res;
}

#define SAKE_PUB_HASH_ID_OFFSET 2
#define SAKE_PUB_HASH_ID_SIZE 2
int somclib_get_sake_root_id(char *buf, size_t buf_len)
{
  int res = FCSERR_OK;

  const struct sake_setup *sake_data;

#ifdef FEATURE_SOMC_TEST_ROOT
  sake_data = &sake_data_test;
#else
  sake_data = &sake_data_live;
#endif //FEATURE_SOMC_TEST_ROOT

  res = bin_to_ascii(buf, buf_len,
                     &sake_data->pub_hash[SAKE_PUB_HASH_ID_OFFSET],
                     SAKE_PUB_HASH_ID_SIZE);

  return res;
}
#endif //FEATURE_DEVICEPROGRAMMER_SOMC

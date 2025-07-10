/* ====================================================================
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * ====================================================================
*/
#include <stdint.h>
#include <stdbool.h>
#include "seclib_err.h"
#include "target_cfg.h"


typedef enum {
  PIMEM_OK             = 0,
  PIMEM_DISABLED       = 1,
  PIMEM_ERROR          = 2,
  PIMEM_NOT_PRESENT    = 3,
  PIMEM_UNKNOWN_ERROR  = 0x7F
} PIMEM_STATUS;


seclib_err_t seclib_get_target_config(const target_cfg_t id, uintptr_t *val)
{
  return SECLIB_SUCCESS;
}


seclib_err_t seclib_pimem_init(void)
{
  return SECLIB_SUCCESS;
}


PIMEM_STATUS seclib_smc_pimem_get_status(void)
{
  return PIMEM_OK;
}


seclib_err_t seclib_get_dump_encryption_artifacts(uint8_t * key,
                                                  size_t key_len,
                                                  uint8_t * mac_key,
                                                  size_t mac_key_len,
                                                  uint8_t * wrapped_key,
                                                  size_t wrapped_key_len)
{
  return SECLIB_SUCCESS;
}


bool seclib_pimem_is_supported(void)
{
  return true;
}
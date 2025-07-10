/* ====================================================================
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * ====================================================================
*/

/**
 *  @file seclib_defs.h
 */
#ifndef _SEC_LIB_DEFS_H
#define _SEC_LIB_DEFS_H

#include <stdint.h>
#include <stddef.h>

/*----------------------------------------------------------------------------
 * Definitions and Type Declarations.
 * -------------------------------------------------------------------------*/

/**
 * The hash commands for hash verification.
 */
typedef enum
{
  SEC_IMG_AUTH_HASH_INIT     = 1,
  SEC_IMG_AUTH_HASH_UPDATE   = 2,
  SEC_IMG_AUTH_HASH_FINALIZE = 3,
  SEC_IMG_AUTH_HASH_DEINIT   = 4,
}sec_img_auth_hash_cmd_et;

/**
 * Different milestones in xBL_SC
 */
typedef enum
{
  SEC_LIB_MILESTONE_TZ_BOOT          = 0,
  SEC_LIB_MILESTONE_COLD_BOOT        = 1,
  SEC_LIB_MILESTONE_COLD_BOOT_DEBUG  = 2, /** Debug milestone corresponds to APDP loaded */
  SEC_LIB_MILESTONE_SDI_PASS2        = 3,
  SEC_LIB_MILESTONE_SDI_PASS2_DEBUG  = 4,
  SEC_LIB_MILESTONE_TEST_MODE        = 5,
  SEC_LIB_MILESTONE_DEVPROG          = 6,
  SEC_LIB_MILESTONE_DDR_INIT         = 7,
}sec_lib_milestone;

/* Enum representing the state of PIMEM HW*/
typedef enum {
  PIMEM_OK             = 0,
  PIMEM_DISABLED       = 1,
  PIMEM_ERROR          = 2,
  PIMEM_NOT_PRESENT    = 3,
  PIMEM_UNKNOWN_ERROR  = 0x7F
} PIMEM_STATUS;

/**
 * Structure to hold the physical memory regions of an image.
 * Filled by xbl_sc.
 */
typedef struct img_range_list
{
  uintptr_t start;     /* Image memory region start address*/
  uintptr_t end;       /* Image memory region end address*/
} img_range_list_t;

#define VERSION_ENCR_INFO_FOR_WRAPPED_BLOB       1
#define SECLIB_HKDF_CONTEXT_LEN                 16
#define SECLIB_WRAPPED_BLOB_AND_ENCR_INFO_LEN  256
typedef struct
{
  /* [out] version of this structure */
  uint32_t ewb_version;
  /* [in]  buffer containing blob that needs to be wrapped e.g., AES key */
  uint8_t* ewb_blob_to_be_wrapped;
  /* [in]  length of `ewb_blob_to_be_wrapped` passed by caller */
  size_t   ewb_blob_to_be_wrapped_len;
  /* [in]  unique per use case string for HKDF operation e.g., "XBL_MINIDUMP" */
  uint8_t  ewb_context[SECLIB_HKDF_CONTEXT_LEN];
  /* [out] buffer containing wrapped input blob and encryption artifacts, encoded
   *       in Qualcomm Binary Encryption (QBEC) format
   */
  uint8_t  ewb_wrapped_blob_and_encr_info[SECLIB_WRAPPED_BLOB_AND_ENCR_INFO_LEN];
  /* [out] length of buffer `ewb_wrapped_blob_and_encr_info` written by seclib */
  size_t   ewb_wrapped_blob_and_encr_info_written_len;
} encr_info_for_wrapped_blob_t;
#endif /* _SEC_LIB_DEFS_H */

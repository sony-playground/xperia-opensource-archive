/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef PLF_NV_H_
#define PLF_NV_H_

#include <stdint.h>

/* Platform Interface to NV (eMMC/UFS)				        */
/* Functions are read/write to platform specific (flash) area           */
/* Keystore needs to be duplicated for fault tolerant updates		*/
/* I.e two independently updateable areas are required			*/
typedef struct plf_nv_t plf_nv_t;

#define KS_NV_ORG		(0)   /* Keystore "partition" #0             */
#define KS_NV_BAK		(1)   /* Keystore "partition" #1             */

/**
 * @brief NV write
 * @param[in] handle    NV Handle
 * @param[in] partition KS_NV_ORG or KS_NV_BAK
 * @param[in] data      The data to write
 * @param[in] data_sz   Size of data
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int plf_nv_write(plf_nv_t * const handle, const uint8_t partition,
			const uint8_t * const data, const uint32_t data_sz);

/**
 * @brief NV read
 * @param[in]  handle    NV Handle
 * @param[in]  partition KS_NV_ORG or KS_NV_BAK
 * @param[out] data      Data read. Allocated by call. Must be free'd by caller.
 * @param[out] data_sz   Size of data
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int plf_nv_read(plf_nv_t * const handle, const uint8_t partition,
		uint8_t **data, uint32_t *data_sz);

/**
 * @brief NV write function pointer prototype
 * @param[in] partition KS_NV_ORG or KS_NV_BAK
 * @param[in] data      The data to write
 * @param[in] data_sz   Size of data
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*plf_nv_write_cb_t)(const uint8_t partition,
					const uint8_t * const data,
					const uint32_t data_sz);

/**
 * @brief NV read function pointer prototype
 *
 * @param[out] data      Data read - must be deallocated by caller
 * @param[out] data_sz   Size of data
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*plf_nv_read_cb_t)(const uint8_t partition,
					uint8_t **data,
					uint32_t *data_sz);

/**
 * @brief Create NV handle
 *
 *
 * @param[out] handle        Opaque handle to keystore
 * @param[in]  write_cb      Function to write to nv
 * @param[in]  read_cb       Function to read from nv
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int plf_nv_create(plf_nv_t **handle,
			plf_nv_write_cb_t write_cb,
			plf_nv_read_cb_t read_cb);

/**
 * @brief Destroy NV handle
 *
 * This function shall be called when NV handle  use is over
 *
 * @param[in] handle   Opaque handle to NV
 */
void plf_nv_destroy(plf_nv_t * const handle);

#endif

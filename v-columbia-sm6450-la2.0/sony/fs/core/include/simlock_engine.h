/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_SIMLOCK_ENGINE_H_
#define FCS_SIMLOCK_ENGINE_H_

/**
 * Find out whether a lock category is locked or unlocked.
 * A lock that has been configured to be inactive will always return unlocked.
 * The validity of the simlock signature is not checked by this function.
 *
 * @param[in]     category       The lock category.
 * @param[in]     simlock_data   Simlock data in binary form as read from
 *                               TA unit TA_SIMLOCK_DATA (2010).
 * @param[in]     data_len       Length (in bytes) of the simlock_data
 *                               buffer size.
 * @param[out]    status         Indicates if the category is locked or not.
 *                               1 means locked. 0 means unlocked
 *                               (or no lock configured for this category).
 *
 * @returns int
 */
int simlock_engine_get_lock_status(int category,
				const unsigned char *simlock_data,
				unsigned int data_len,
				int *status);

/**
 * Attempts to compare the unlocking codes with the hash of the code in TA.
 * If successful the locks will be considered unlocked.
 *
 * @param[in]     iteration_count  Salt iteration count.
 * @param[in]     unlock_code      Code to unlock the simlock.
 * @param[in]     unlock_code_len  Length of unlock code.
 * @param[in]     salt             Salt.
 * @param[in]     salt_len         Salt length.
 * @param[out]    res_buf          Result buffer.
 * @param[out]    res_buf_len      Length of result buffer.
 *
 * @return S1SL_ErrorCode
 */
int simlock_engine_hash_unlock_code(unsigned int iteration_count,
				const unsigned char *unlock_code,
				unsigned int unlock_code_len,
				const unsigned char *salt,
				unsigned int salt_len,
				unsigned char *res_buf,
				unsigned int *res_buf_len);

#endif

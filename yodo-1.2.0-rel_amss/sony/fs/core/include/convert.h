/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef CONVERT_H_
#define CONVERT_H_

#include <stddef.h>
#include <stdint.h>

/*
 * Convert <bin_len> of binary data from buffer <bin_buf> into buffer
 * <ascii_buf> which has size <ascii_buf_size>.
 * The output is null terminated.
 * Returns an FCSERR error code.
 */
int bin_to_ascii(char *ascii_buf, size_t ascii_buf_size,
		const uint8_t *bin_buf, size_t bin_len);

/*
 * Convert <ascii_len> of ascii data from buffer <ascii_buf> into buffer
 * <bin_buf> which has size <bin_buf_size>.
 * Returns an FCSERR error code.
 */
int ascii_to_bin(uint8_t *bin_buf, size_t bin_buf_size,
		const char *ascii_buf, size_t ascii_len);

/**
 * @brief Calculates the size needed based on a given input size.
 *
 * This simply returns ( ((input_size + 2) / 3 ) * 4 )
 *
 * @param[in] input_size The size of unencoded data.
 *
 * @return Returns the size of the buffer needed for the encoded data,
 *         excluding NULL termination.
 */
size_t base64_size_of_result(size_t input_size);

/**
 * @brief Base64 encodes the input array to an output array.
 *
 * @param[in] input The input array to encode.
 * @param[in] input_size The size of the input array.
 * @param[out] result NULL terminated buffer with encoded data.
 *                    The buffer for the result shall be allocated by
 *                    the caller.
 * @param[in] result_size The size of result buffer.
 *
 *  Returns an FCSERR error code
 */

int base64_encode(const uint8_t *input, size_t input_size,
		char *result, size_t result_size);
#endif

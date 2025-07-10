/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "convert.h"
#include "fcslog.h"
#include "fcserr.h"

const char base64_alphabet[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char base64_pad_char = '=';

static int char_to_nibble(char c, int *nibble)
{
	if ((c >= '0') && (c <= '9'))
		*nibble = (int)(c - '0');
	else if ((c >= 'A') && (c <= 'F'))
		*nibble = (int)(c - 'A') + 10;
	else if ((c >= 'a') && (c <= 'f'))
		*nibble = (int)(c - 'a') + 10;
	else
		return -FCSERR_EINFOR;

	return FCSERR_OK;
}

/*
 * Convert <bin_len> of binary data from buffer <bin_buf> into buffer
 * <ascii_buf> which has size <ascii_buf_size>.
 * The output is null terminated.
 * Returns an FCSERR error code.
 */
int bin_to_ascii(char *ascii_buf, size_t ascii_buf_size,
		const uint8_t *bin_buf, size_t bin_len)
{
	const char *hex = "0123456789ABCDEF";
	uint32_t i;

	if (!ascii_buf || !bin_buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (ascii_buf_size < 2 * bin_len + 1) {
		FCS_LOG_ERR("Output buffer too small, %d<%d\n",
			ascii_buf_size, 2 * bin_len + 1);
		return -FCSERR_EINVAL;
	}

	for (i = 0; i < bin_len; i++) {
		ascii_buf[i * 2] = hex[(bin_buf[i] >> 4) & 0xF];
		ascii_buf[i * 2 + 1] = hex[bin_buf[i] & 0xF];
	}

	ascii_buf[i * 2] = '\0';
	return FCSERR_OK;
}

/*
 * Convert <ascii_len> of ascii data from buffer <ascii_buf> into buffer
 * <bin_buf> which has size <bin_buf_size>.
 * Returns an FCSERR error code.
 */
int ascii_to_bin(uint8_t *bin_buf, size_t bin_buf_size,
		const char *ascii_buf, size_t ascii_len)
{
	uint32_t nibble_index, bin_buf_index;
	int nibbles[2];
	int i, res;

	if (!bin_buf || !ascii_buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Required size of the binary buffer is half the size of the ascii
	 * buffer rounded up to handle the case where the size of the ascii
	 * buffer is odd.
	 */
	if (bin_buf_size < (ascii_len + 1) / 2) {
		FCS_LOG_ERR("Output buffer too small, %d<%d\n",
			bin_buf_size, (ascii_len + 1) / 2);
		return -FCSERR_EINVAL;
	}

	/* Convert the ascii buffer to binary beginning from the end.
	 * bin_buf_index is initialized to the last index of the binary buffer.
	 * nibble_index is used to keep track of high (1) and low (0) nibble
	 * of the binary data.
	 */
	nibble_index = 0;
	bin_buf_index = (ascii_len + 1) / 2 - 1;
	for (i = ascii_len - 1; i >= 0; i--) {
		res = char_to_nibble(ascii_buf[i], &nibbles[nibble_index]);
		if (res != FCSERR_OK)
			return res;
		if (nibble_index == 0) {
			nibble_index = 1;
		} else {
			nibble_index = 0;
			bin_buf[bin_buf_index--] =
				(nibbles[1] << 4) | nibbles[0];
		}
	}

	/* If odd number of nibbles, only use low nibble in first byte */
	if (nibble_index == 1)
		bin_buf[0] = nibbles[0];

	return FCSERR_OK;
}


size_t base64_size_of_result(size_t input_size)
{
	return ((input_size + 2) / 3) * 4;
}

int base64_encode(const uint8_t *input,
		size_t input_size,
		char *result,
		size_t result_size)
{
	size_t i;
	size_t j = 0;
	int pad = input_size % 3;
	uint32_t octet_combo;
	uint32_t index[4];
	size_t result_idx = 0;
	size_t needed_result_size = base64_size_of_result(input_size);

	/* Adding 1 char for NULL termination */
	if (result == NULL || result_size < (needed_result_size + 1)
			|| input == NULL) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	for (i = 0; i < input_size; i += 3) {
		/* Combine three bytes 24 bits */
		octet_combo = input[i] << 16;

		if ((i + 1) < input_size)
			octet_combo |= input[i+1] << 8;

		if ((i + 2) < input_size)
			octet_combo |= input[i+2];

		/* Break the 24 bit combo into four 6-bit indexes */
		index[0] = (octet_combo >> 18) & 0x3F;
		index[1] = (octet_combo >> 12) & 0x3F;
		index[2] = (octet_combo >>  6) & 0x3F;
		index[3] = (octet_combo) & 0x3F;

		j = 0;
		while ((needed_result_size > result_idx) && (j < 4))
			result[result_idx++] = base64_alphabet[index[j++]];
	}

	if ((pad != 0) && (j == 4))
		for (; pad < 3; pad++)
			/* Overwrite 'pad' bytes of data with the pad char */
			result[--result_idx] = base64_pad_char;

	result[needed_result_size] = '\0';

	return FCSERR_OK;
}

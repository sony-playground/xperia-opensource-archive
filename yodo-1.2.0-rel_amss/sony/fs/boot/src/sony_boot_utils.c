/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "sony_boot_utils.h"
#include "ta_interface.h"

#include "sony_libc.h"
#include "fcslog.h"

int sony_boot_ta_simple_read(
	uint32_t unit, uint8_t **data, uint32_t *size)
{
	int res = FCSERR_OK;
	uint8_t *buf = NULL;
	int sz;

	if (!data || !size) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*data = NULL;

	if ((get_ta_unit_size(TA_MISC_PART, unit, &sz) == FCSERR_OK)
		&& (sz != 0)) {

		buf = malloc(sz);
		if (!buf) {
			FCS_LOG_ERR("Out of memory for TA unit!\n");
			res = -FCSERR_ENOMEM;
		} else if (read_ta(TA_MISC_PART, unit, buf, sz) != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read TA unit!\n");
			res = -FCSERR_EREAD;
		}
	} else {
		res = -FCSERR_EINDEX;
	}

	if ((res != FCSERR_OK) && buf) {
		free(buf);
		buf = NULL;
	}

	if (buf) {
		*data = buf;
		*size = sz;
	}

	return res;
}

char *sony_alloc_strcat(char *destination, const char *source)
{
	size_t destination_len = 0;
	size_t source_len = 0;
	size_t new_len = 0;

	if (destination != NULL)
		destination_len = strlen(destination);

	if (source)
		source_len = strlen(source);

	if (destination_len || source_len) {
		if (destination) {
			if (destination_len + source_len + 1 >
				MAX_STRING_SIZE) {
				/* Destination buffer is too small */
				FCS_LOG_ERR("Dest buffer is too small\n");
				free(destination);
				destination = NULL;
			}
		} else {
			destination = malloc(MAX_STRING_SIZE);
		}
		new_len = destination_len;

		if (destination && source) {
			strlcpy(destination + new_len, source,
				MAX_STRING_SIZE - new_len);
			new_len += source_len;
			destination[new_len] = 0;
		}
	}
	return destination;
}

char *bin2ascii(const uint8_t *buf, size_t sz)
{
	const char digits[] = "0123456789abcdef";
	char *tmp;
	uint32_t i;
	unsigned char lo, hi;

	if (!buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}

	tmp = malloc(2 * sz + 1);
	if (!tmp)
		return NULL;

	for (i = 0; i < (2 * sz - 1); i += 2) {
		hi = (buf[i >> 1] & 0xF0) >> 4;
		lo = (buf[i >> 1] & 0x0F) >> 0;

		tmp[i]   = (uint8_t)digits[hi];
		tmp[i+1] = (uint8_t)digits[lo];
	}

	tmp[i] = '\0';
	return tmp;
}

char *replace(const char *str, const char *orig, const char *rep)
{
	const char *tmp;
	char *found;
	char *result = NULL;
	size_t res_size;
	size_t len_orig;
	size_t len_rep;
	int count = 0;

	if (!str || !orig || !rep) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}

	len_orig = strlen(orig);
	len_rep = strlen(rep);
	tmp = str;

	/* The number of times the substring appears in the string */
	while ((found = strnstr(tmp, orig, strlen(tmp)))) {
		tmp = found + len_orig;
		count++;
	}

	/* No occurences of the substring were found. */
	if (count == 0)
		return NULL;

	/* Allocate enough memory for the modified string */
	res_size = strlen(str) + count * (len_rep - len_orig) + 1;
	result = malloc(res_size);
	if (!result)
		return NULL;

	result[0] = '\0';

	tmp = str;
	/* Do the substring replacement */
	while (count--) {
		found = strnstr(tmp, orig, strlen(tmp));
		strlcpy(result + strlen(result), tmp, found - tmp + 1);
		strlcat(result, rep, strlen(result) + len_rep + 1);
		tmp = found + len_orig;
	}
	strlcat(result, tmp, res_size);

	return result;
}


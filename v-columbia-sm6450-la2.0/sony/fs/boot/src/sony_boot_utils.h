/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef _SONY_BOOT_UTILS_H_
#define _SONY_BOOT_UTILS_H_

#include <stdint.h>
#include <stdlib.h>

#define LOG_BLOCK(code...) code

#define MAX_STRING_SIZE 4096

/**
 * @brief Allocate a buffer and read specified TA unit
 *
 * The function will identify the size of the unit itself.
 * It is the responsibility of the caller to release the returned data once it
 * is no longer needed.
 *
 * @param[in]  unit The TA unit to read.
 * @param[out] data Buffer to store the allocated data buffer pointer in.
 *                  Buffer is allocated by caller. The allocated data buffer is
 *                  allocated by the function.
 * @param[out] size Buffer to store the size of the unit and the allocated data.
 *                  Buffer is allocated by caller.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int sony_boot_ta_simple_read(uint32_t unit, uint8_t **data, uint32_t *size);

/**
 * @brief strcat implementation with internal memory management
 *
 * Appends source to destination and adds a NULL character.
 * This function will allocate the destination buffer. It will be the
 * responsibility of the caller to release allocated buffers.
 *
 * @param[in] context Sony boot context.
 * @param[in] destination The string to write to (may be NULL)
 * @param[in] source The data to add
 *
 * @returns the concatenated strings. Caller is responsible for deallocating
 */
char *sony_alloc_strcat(char *destination, const char *source);

/**
 * @brief Converter to generate an ascii string with a hexadecimal
 * representation of provided databuffer.
 *
 * Caller must deallocate the returned buffer when done with it.
 * Buffer will be null-terminated and result is unsigned.
 *
 * @param[in] buf Databuffer with binary data to convert.
 * @param[in] sz The number of bytes in the input buffer.
 *
 * @returns NULL-terminated string with HEX representation of input data
 */
char *bin2ascii(const uint8_t *buf, size_t sz);

/**
 * @brief Replace all occurences of a substring in a string, with
 * another substring.
 *
 * Caller must deallocate the returned buffer when done with it.
 *
 * @param[in] str The string on which we operate.
 * @param[in] orig The substring to be replaced.
 * @param[in] rep The substring that replaces the original substring.
 *
 * @returns ASCII string with updated substring, or NULL if the string
 *          does not contain the substring.
 */
char *replace(const char *str, const char *orig, const char *rep);

#endif /* _SONY_BOOT_UTILS_H_ */


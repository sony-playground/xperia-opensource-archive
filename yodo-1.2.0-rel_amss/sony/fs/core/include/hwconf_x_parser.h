/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                         *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * Description                                                                *
 * Parsing the hwconfig X(peria) can be achieved by using this parser API.    *
 *                                                                            *
 * How to use the parser API                                                  *
 * 1. Call hwconf_x_parser_init()                                             *
 * 2. Call the parser API of interest.                                        *
 * 3. Call hwconf_x_parser_deinit() when finished parsing hwconfig.           *
 *                                                                            *
 *****************************************************************************/

#ifndef HWCONF_X_PARSER_H
#define HWCONF_X_PARSER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * Handle used when parsing hwconf.
 */
#define hwconf_x_handle_t void *


/**
 *  This function will initialize the hwconfig parser. A handle pointer
 *  shall be provided to this function by the caller.
 *  This handle is used when the caller is using the parser API
 *  functions to retrieve the data stored in hw config.
 *
 *  @param [out]    phandle      Handle pointer, maps to the parsing of
 *                               the hwconf data.
 *  @param [in]     hwconf       A pointer to the hwconfig binary data.
 *  @param [in]     hwconf_size  Size of the hwconfig binary data in bytes.
 *
 *  Detailed description
 *  This function will use the hwconf_handle_t structure to store all
 *  the parsed data. This hwconf_handle_t structure is passed as a handle
 *  to the caller and will be used in calls to the parser API's.
 *
 *  @returns Success or error indication
 */
int hwconf_x_parser_init(hwconf_x_handle_t *phandle,
		uint8_t *hwconf,
		size_t hwconf_size);

/**
 *  This function will uninitialize and free all the internal structures that
 *  has been used when parsing the hwconfig. After this call the user cannot
 *  parse the hwconfig data that corresponds to the handle parameter.
 *
 *  @param [in]    handle      Handle retrieved when initializing parser.
 *
 *  @returns None
 */
void hwconf_x_parser_deinit(hwconf_x_handle_t handle);


/**
 *  The function is used to retrieve the version of the hardware configuration
 *  handled by the parser. The handle retrieved when initializing the parser
 *  shall be used as a parameter in this function call.
 *
 *  @param [in]        handle    Handle retrieved when initializing parser.
 *  @param [out]       version   The parsed hardware configuration version.
 *
 *  @returns Success or error indication
 */
int hwconf_x_parser_get_version(hwconf_x_handle_t handle, int *version);

/**
 *  The function is used to retrieve the is prototype field of
 *  the hardware configuration handled by the parser.
 *
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]        handle         Handle retrieved when initializing parser.
 *  @param [out]       is_prototype   The is prototype field.
 *
 *  @returns Success or error indication
 */
int hwconf_x_parser_get_isprototype(
		hwconf_x_handle_t handle,
		bool *is_prototype);

/**
 *  This function will get the number of entries in imei list.
 *
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *  @param [out]    count        Entry count.
 *
 *  @returns Success or error indication
 */
int hwconf_x_parser_get_imei_count(hwconf_x_handle_t handle, uint8_t *count);

/**
 *  This function will get a entry in imei list.
 *
 *  The user should NOT deallocate the returned buffer. It is
 *  deallocated with handle.
 *
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *  @param [in]     index        Index of entry (0 - 1).
 *  @param [out]    buffer       IMEI buffer.
 *  @param [out]    buffer_size  Buffer size in bytes.
 *
 *  @returns Success or error indication
 */
int hwconf_x_parser_get_imei(hwconf_x_handle_t handle,
		uint8_t index,
		uint8_t **buffer,
		size_t *buffer_size);

/**
 *  This function will get the HWC device key.
 *
 *  The user should NOT deallocate the returned buffer. It is
 *  deallocated with handle.
 *
 *  The handle retrieved when initializing the parser shall be used as a
 *  parameter in this function call.
 *
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *  @param [out]    buffer       HWC device key buffer.
 *  @param [out]     buffer_size  Buffer size in bytes.
 *
 *  @returns Success or error indication
 */
int hwconf_x_parser_get_hwc_dk(hwconf_x_handle_t handle,
		uint8_t **buffer,
		size_t *buffer_size);

#endif /* HWCONF_X_PARSER_H */

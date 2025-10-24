/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2012-2016 Sony Mobile Communications Inc.                    *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * Description                                                                *
 * Parsing the hwconfig can be achieved by using this parser API.             *
 *                                                                            *
 * How to use the parser API                                                  *
 * 1. Call hwconf_parser_init()                                               *
 * 2. Call the parser API of interest.                                        *
 * 3. Call hwconf_parser_deinit() when finished parsing hwconfig.             *
 *                                                                            *
 *****************************************************************************/

#ifndef HWCONF_PARSER_H
#define HWCONF_PARSER_H

#include <stdint.h>
#include <stddef.h>

/**
 * Supported Phone ID types.
 * Max value 255
 */
enum hwconf_phone_ID_t {
	IMEI = 0,
	MEID = 1,
	MAX_ID_TYPE = 0xFFFF
};


/**
 * Misc data for loader, boot, SW etc
 * Max value 255
 */
enum hwconf_misc_data_type_t {
	LOADER_DATA = 0,
	BOOT_DATA = 1,
	INFO_DATA = 2,
	SW_DATA = 3,
	MAX_MISC_DATA_TYPE = 0xFF
};

/**
 * Flags used in the hwconf_parser_get_sec_conf_global_flags() function.
 */
enum hwconf_sec_conf_global_flags_t {
	/* NoAuthenticationRequired means that the loader runs sensitive
	   commands even if authentication has not been performed.  When
	   the flag is set authentication is still possible, but not
	   required. */
	NO_AUTHENTICATION_REQUIRED = 0x8000,
	/* AllowHighTA means that the loader gives the host read and write
	   access to TA units above ID 65537. */
	ALLOW_HIGH_TA = 0x4000,
	/* Security State exposed to TCB. */
	TCB_SECURITY_STATE_OFF = 0x2000,
	/* Ctrl Root override for Fast Boot. */
	CTRL_ROOT_OVERRIDE = 0x1000,
	/* Commercial device, no JTAG enabled */
	JTAG_FLAGS_NO_JTAG = 0,
	/* R&D device, Modem and Application CPU JTAG enabled */
	JTAG_FLAGS_RnD = 0x01,
	/* Security United R&D device, Modem, Application and
	   TEE JTAG enabled.*/
	JTAG_FLAGS_SEC = 0x02
};


#define hwconf_JTAG_FLAGS_MASK 0xF



/**
 * Handle used when parsing hwconf.
 */
#define hwconf_handle_t void *


/**
 *  This function will initialize the hwconfig parser. A handle pointer
 *  shall be provided to this function by the caller.
 *  This handle is used when the caller is using the parser API
 *  functions to retrieve the data stored in hw config.
 *
 *  @param [in]     hwconf       A pointer to the hwconfig binary data.
 *  @param [in]     hwconf_size  Size of the hwconfig binary data in bytes.
 *  @param [out]    phandle      Handle pointer, maps to the parsing of
 *                               the hwconf data.
 *
 *  Detailed description
 *  This function will use the hwconf_handle_t structure to store all
 *  the parsed data. The structure includes both the stored hwconfig data
 *  as well as members that keeps track of where in the hwconfig we
 *  are currently parsing.
 *  This hwconf_handle_t structure is passed as a handle to the caller
 *  and will be used in calls to the parser API's.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_init(uint8_t *hwconf,
		uint32_t hwconf_size,
		hwconf_handle_t *phandle);

/**
 *  This function will uninitialize and free all the internal structures that
 *  has been used when parsing the hwconfig. After this call the user cannot
 *  parse the hwconfig data that corresponds to the handle parameter.
 *
 *  @param [in]    handle      Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_deinit(hwconf_handle_t handle);




/**
 *  The function is used to retrieve the version of the hardware configuration
 *  handled by the parser. The handle retrieved when initializing the parser
 *  shall be used as a parameter in this function call.
 *
 *  @param [out]       version   The parsed hardware configuration version.
 *  @param [in]        handle    Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint16_t version;
 *  hwconf_parser_get_version(&version, handle);
 */
int hwconf_parser_get_version(uint16_t *version, hwconf_handle_t handle);

/**
 *  hwconf_parser_get_misc_data_tag_length is used to retrieve the length of
 *  a tag in misc data.
 *  @param [in]        index        Index of misc data type.
 *  @param [out]       num_of_bytes The tag size in number of bytes with the
 *                                  null termination character included.
 *
 *  @param [in]        tag          The tag to find
 *  @param [in]        md_type      misc data type
 *  @param [in]        handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_misc_data_tag_length(
		uint8_t index,
		size_t *num_of_bytes,
		char *tag,
		enum hwconf_misc_data_type_t md_type,
		hwconf_handle_t handle);

/**
 *  hwconf_parser_get_misc_data_tag is used to retrieve the contents of a tag
 *  in misc data.
 *
 *  @param [out]       info         The parsed hardware configuration tag data.
 *                                  If info==NULL, the function will not copy
 *                                  the revision string, only return the size of
 *                                  the string. The number of bytes
 *                                  allocated is the calling function's
 *                                  responsibility.
 *  @param [in]        index        Index of misc data type.
 *  @param [out]       num_of_bytes The tag size in number of bytes with the
 *                                  null termination character included.
 *
 *  @param [in]        tag          The tag to find
 *  @param [in]        md_type      misc data type
 *  @param [in]        handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_misc_data_tag(uint8_t *info,
		uint8_t index,
		size_t *num_of_bytes,
		char *tag,
		enum hwconf_misc_data_type_t md_type,
		hwconf_handle_t handle);


/**
 *  hwconf_parser_get_revision_data is used to retrieve the hw_conf revision
 *
 *  @param [out]       revision     The parsed revision array.
 *  @param [out]       num_of_bytes The size of revision in bytes with null
 *                                  termination character included.
 *  @param [in]        handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_revision_data(uint8_t *revision,
		size_t *num_of_bytes,
		hwconf_handle_t handle);

/**
 *  hwconf_parser_get_revision_data is used to retrieve the hw_conf revision
 *
 *  @param [out]       num_of_bytes The size of revision in bytes with null
 *                                  termination character included.
 *  @param [in]        handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_revision_length(size_t *num_of_bytes,
		hwconf_handle_t handle);

/**
 *  The function is used to retrieve the flags of the hardware configuration
 *  handled by the parser.
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [out]       flags   The version will be stored here
 *  @param [in]        handle  Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint16_t flags;
 *  hwconf_parser_get_flags(&flags, handle);
 */
int hwconf_parser_get_flags(uint16_t *flags, hwconf_handle_t handle);



/**
 *  The function is used to retrieve the product ID of the hardware
 *  configuration handled by the parser.
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [out]       id      The product Id will be stored here.
 *  @param [in]        handle  Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint16_t id;
 *  hwconf_parser_get_product_ID(&id, handle);
 */
int hwconf_parser_get_product_ID(uint16_t *id, hwconf_handle_t handle);




/**
 *  This function will retrieve the number of instances that exist for the
 *  specified misc data type from the hardware configuration
 *  handled by the parser. This can be used as a index to the
 *  hwconf_parser_get_misc_type() function. For example if the number of
 *  types are 3 then the index 0 to 2 can be used when calling the
 *  hwconf_parser_get_misc_data().
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]        misc_type   The misc data type.
 *  @param [out]       nr_ins      The number of instances of the type specified
 *  @param [in]        handle      Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint8_t nr_ins;
 *  hwconf_parser_get_misc_type_nr_ins(LOADER_DATA, &nr_ins, handle);
 */
int hwconf_parser_get_misc_type_nr_ins(enum hwconf_misc_data_type_t misc_type,
		uint8_t *nr_ins,
		hwconf_handle_t handle);




/**
 *  This function will retrieve the specified misc data length from
 *  the hardware configuration handled by the parser.
 *  Index is used to get the correct instance if several entries of
 *  the same misc data type exist.
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]     misc_type    The misc data type.
 *  @param [in]     index        Index of misc data type.
 *  @param [out]    length       Misc data length will be stored here.
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint16_t length;
 *  hwconf_parser_get_misc_length(LOADER_DATA, 0, &length, handle);
 */
int hwconf_parser_get_misc_length(enum hwconf_misc_data_type_t misc_type,
		uint8_t index,
		uint16_t *length,
		hwconf_handle_t handle);




/**
 *  This function will get the specified misc data from
 *  the hardware configuration handled by the parser.
 *  The buffer size for the specific misc data type can be retrieved by calling
 *  the hwconf_parser_get_misc_data_length(). Index is used to get
 *  the correct instance if several entries of the same misc data type exist.
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]     misc_type    The misc data type.
 *  @param [in]     index        Index of id.
 *  @param [out]    buffer       Misc data will be stored here.
 *  @param [in]     buffer_size  Buffer size in bytes.
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_misc_data(enum hwconf_misc_data_type_t misc_type,
		uint8_t index,
		uint8_t *buffer,
		uint16_t buffer_size,
		hwconf_handle_t handle);

/**
 *  This function will get the number of instances that exist for the
 *  specified phone id type from the hardware configuration handled by
 *  the parser.
 *  This can be used as a index to the hwconf_parser_get_phone_id() function.
 *  For example if the number of id's are 3 then the index 0 to 2 can be used
 *  when calling the hwconf_parser_get_phone_id().
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]     id_type      The type of phone id.
 *  @param [out]    nr_ins       The number of instances for the type specified.
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint8_t nr_ins;
 *  hwconf_parser_get_phone_id_nr_ins(IMEI, &nr_ins, handle);
 */
int hwconf_parser_get_phone_id_nr_ins(enum hwconf_phone_ID_t id_type,
		uint8_t *nr_ins,
		hwconf_handle_t handle);




/**
 *  This function will get the specified phone id length from the
 *  hardware configuration handled by the parser.
 *  Index is used to get the correct instance if several entries of
 *  the phone id data type exist.
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [in]     id_type      The phone id type.
 *  @param [in]     index        Index of phone id type.
 *  @param [out]    length       Phone id length will be stored here.
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint16_t length;
 *  hwconf_parser_get_phone_id_length(IMEI, 0, &length, handle);
 */
int hwconf_parser_get_phone_id_length(enum hwconf_phone_ID_t id_type,
		uint8_t index,
		uint16_t *length,
		hwconf_handle_t handle);




/**
 *  This function will get the specified phone id from the
 *  hardware configuration handled by the parser.
 *  The user should also add the type of phone id that should be stored in the
 *  buffer as parameter. This can be IMEI, MEID etc. Index is used to get
 *  the correct instance if several id's of the the same type exist.
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 ** @param [in]     id_type      The type of phone id.
 ** @param [in]     index        Index of id.
 *  @param [out]    buffer       Phone id will be stored here.
 *  @param [in]     buffer_size  Buffer size in bytes.
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_phone_id(enum hwconf_phone_ID_t id_type,
		uint8_t index,
		uint8_t *buffer,
		uint8_t buffer_size,
		hwconf_handle_t handle);



/**
 *  This function will get the hw config global security flags from the
 *  hardware configuration handled by the parser.
 *  The handle retrieved when initializing the parser shall be used
 *  as a parameter in this function call.
 *
 *  @param [out]       flags   The version will be stored here
 *  @param [in]        handle  Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 */
int hwconf_parser_get_global_sec_flags(uint16_t *flags,
		hwconf_handle_t handle);



/**
 *  This function will get the number of device id instances that exist in the
 *  hwconfig. The number of instances will be stored in the provided buffer.
 *  This can be used as a index to the hwconf_parser_get_device_id_data
 *  function. For example if the number of instances are 3 then the
 *  index 0 to 2 can be used when calling the hwconf_parser_get_dev_id_data()
 *  function etc. The handle retrieved when initializing the parser shall
 *  be used as a parameter in this function call.
 *
 *  @param [out]        nr_ins   The number of device id instances will
 *                               be stored here.
 *  @param [in]         handle   Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint8_t nr_ins;
 *  hwconf_parser_get_dev_id_nr_ins(&nr_ins, handle);
 */
int hwconf_parser_get_dev_id_nr_ins(uint8_t *nr_ins,
		hwconf_handle_t handle);




/**
 *  The function is used to retrieve the specified device id length from
 *  the hardware configuration handled by the parser. The index is used specify
 *  the device id instance if several exist in the hwconfig.
 *
 *  @param [in]        index   Index of id.
 *  @param [out]       length  The length will be stored here
 *  @param [in]        handle  Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint16_t length;
 *  hwconf_parser_get_dev_id_length(0, &length, handle);
 */
int hwconf_parser_get_dev_id_length(uint8_t index,
		uint16_t *length,
		hwconf_handle_t handle);




/**
 *  This function will get the specified device id. The device id will be
 *  stored in the supplied buffer by the caller.
 *  The buffer size for the specific device id should be according to
 *  hwconf_parser_get_dev_id_length(). Index is used to get the correct
 *  instance if several id's exist. The handle retrieved when initializing
 *  the parser shall be used as a parameter in this function call.
 *
 *  @param [in]     index        Index of id.
 *  @param [out]    buffer       Device id will be stored here.
 *  @param [in]     buffer_size  Buffer size in bytes.
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_dev_id(uint8_t index,
		uint8_t *buffer,
		uint8_t buffer_size,
		hwconf_handle_t handle);




/**
 *  This function will get the hwc device key length. The length will be stored
 *  in a supplied buffer. The handle retrieved when initializing the parser
 *  shall be used as a parameter in this function call.
 *
 *  @param [out]       length   The length will be stored here
 *  @param [in]        handle    Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 *
 *  Example on how to use this function:
 *  uint16_t length;
 *  hwconf_parser_get_hwc_dk_length(&length, handle);
 */
int hwconf_parser_get_hwc_dk_length(uint16_t *length, hwconf_handle_t handle);




/**
 *  This function will get the HWC device key. The key will be stored in the
 *  supplied buffer by the caller. The buffer size for the specific device key
 *  should be according to hwconf_parser_get_hwc_dk_length(). The handle
 *  retrieved when initializing the parser shall be used as a parameter
 *  in this function call.
 *
 *  @param [out]    buffer       The HWC device key will be stored here.
 *  @param [in]     buffer_size  Buffer size in bytes.
 *  @param [in]     handle       Handle retrieved when initializing parser.
 *
 *  @returns Success or error indication
 */
int hwconf_parser_get_hwc_dk(uint8_t *buffer,
		uint8_t buffer_size,
		hwconf_handle_t handle);




#endif /* HWCONF_PARSER_H */

/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SECURITY_PROPERTIES_H_
#define SECURITY_PROPERTIES_H_

#include <stdlib.h>
#include <stdint.h>
#include "fcslist.h"

/**
 * "Set security properties" data type
 */
enum secprop_data_type {
	S1_OTP_DATA = 0,
	DEVICEKEY = 1,
	A2_OTP_DATA = 2,
	DEBUG_EN_KEY = 3,
	SERIAL_NUMBER = 4,
	AV8100_OTP_DATA = 5,
	MDM9x00_OTP_DATA = 7,
	OTP_BURN_EXT_MODEM = 0x11,
	MDM9x00_OTP_DATA_WITH_ADDRESS = 0x87,
	MDM9x00_OTP_DATA_RANDOM_WITH_ADDRESS = 0x8A,
	MDM9x00_OTP_DATA_WITH_ADDRESS_63_56_FEC = 0x8B,
	MDM9x00_OTP_DATA_QCSMK_WITH_ADDRESS = 0x8C,
	OTP_DATA_WITH_ADDRESS = 0x80,
	OTP_DATA_WITH_ADDRESS_NO_FEC = 0x8D,
	RANDOM_DATA = 0x88,
	OTP_DATA_WITH_63_56_FEC = 0x89,
	RANDOM_DATA_NO_FEC = 0x90,
	OTP_DATA_FINAL = 0xF1,
	SEC_PROP_INVALID = 0xFFFF
};

/** security property handler */
typedef int (*secprop_func_ptr)(const uint8_t *data, uint16_t len);

int handle_security_properties(const uint8_t *data, uint32_t length,
		struct list_entry *sec_prop_list);

int set_devicekey(uint8_t *data, uint16_t property_len);

#endif /* SECURITY_PROPERTIES_H_ */

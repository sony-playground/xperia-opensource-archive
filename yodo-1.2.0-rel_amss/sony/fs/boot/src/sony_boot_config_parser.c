/*
 * Copyright 2016, 2022 Sony Corporation
 * All rights, including trade secret rights, reserved.
 */
#include <stdlib.h>
#include <string.h>
#include "sony_boot_config_parser.h"
#include "sony_boot_utils.h"
#include "sony_libc.h"
#include "ta_interface.h"


/* Header files from loader */
#include "fcs_endian.h"
#include "fcslog.h"
#include "fcserr.h"


#define SERVICE_TRIGGER_KEYPAD_EXPECTED_SIZE   (2)
#define SERVICE_TRIGGER_GPIO_EXPECTED_SIZE     (3)
#define SERVICE_TRIGGER_OTG_EXPECTED_SIZE      (1)
#define SERVICE_TRIGGER_POWER_ON_EXPECTED_SIZE (0)
#define SERVICE_TRIGGER_RESET_ON_EXPECTED_SIZE (0)
#define SERVICE_TRIGGER_EXPECTED_LENGTH        (4)
#define KEYBOARD_CFG_EXPECTED_LENGTH           (5)
#define SERVICE_CFG_EXPECTED_LENGTH            (2)
#define RESET_CFG_EXPECTED_LENGTH              (12)
#define FLAFLA_CFG_EXPECTED_LENGTH             (1)
#define LONGPRESS_CFG_EXPECTED_LENGTH          (2)
#define CMDLINE_DATA_EXPECTED_LENGTH           (4)
#define VBUS_DATA_EXPECTED_LENGTH              (3)
#define BACKLIGHT_DATA_EXPECTED_LENGTH         (1)
#define VARIANT_DATA_EXPECTED_LENGTH           (1)

/* Remove use of realloc, always allocate these sizes */
#define MAX_CMD_ENTRY_SIZE 4096
#define MAX_SERVICE_TRIGGERS 340

/**
 *  Config types
 */
enum ConfigTypes_t {
	CONFIG_SERVICE_KEYS = 0x0001,
	CONFIG_BOOT_PARAM_ADD_TA_UNIT = 0x0002,
	CONFIG_SERVICE_CFG = 0x0003,
	CONFIG_LONGPRESS_TIME = 0x0004,
	CONFIG_FLAFLA_OVERRIDE = 0x0005,
	CONFIG_RESET_CFG = 0x0006,
	CONFIG_KEYBOARD_CFG = 0x0007,
	CONFIG_VBUS_VIBRATION = 0x0008,
	CONFIG_BACKLIGHT = 0x0009,
	CONFIG_VARIANT = 0x000A
};

/**
 *  Service mode flags
 */
#define SERVICE_MODE_DISABLE_SRV_PIN 0x0001 /* Disable service pin detection */
#define SERVICE_MODE_USB_SERVICE     0x0002 /* USB interface will be used */
#define SERVICE_MODE_DISABLE_SW_SRV  0x0008 /* Disable soft service */

/**
 *  Supported service types
 */
#define SERVICE_TYPE_SRV_PIN  1 /* Used for service mode (and set FlaFla) */
#define SERVICE_TYPE_SW_SRV   2 /* Used for soft service (and not set FlaFla) */
#define SERVICE_TYPE_FASTBOOT 3 /* Used for fastboot */
#define SERVICE_TYPE_RESET    4 /* Used for reset */
#define SERVICE_TYPE_RECOVERY 5 /* Used for recovery */

/* Local function declarations */

static uint8_t *get_config_data(enum ConfigTypes_t config_type,
	uint32_t *type_sz, const uint8_t *config_data,
	const size_t config_size);
static void store_service_triggers(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static void store_long_press_time(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static void store_service_mode(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static void store_ta_commandline_params(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static void store_fla_fla_override(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static void store_reset_cfg(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static void store_vbus_pulse(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static void store_backlight(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);
static char *ta_to_cmdline(uint32_t unitNbr, uint32_t unitLabel);
static char *ta_to_cmdline_enconsole(uint32_t unitNbr, uint32_t unitLabel);

int bootconfig_parse(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	if (context == NULL || config_data == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	} else if (context->bootconfig != NULL) {
		/* Bootconfig already parsed */
		return FCSERR_OK;
	}

	/* Make a sanity check on the version before committing to
	 * parse the TA data
	 */
	if ((config_data[0] != 0x1A) || (config_data[1] != 0xCE)) {
		/* invalid bootconfig */
		return -FCSERR_EINVAL;
	}

	/* Allocate the configuration structure */
	context->bootconfig = calloc(1,
		sizeof(struct sony_boot_configuration));
	if (context->bootconfig == NULL)
		return -FCSERR_ENOMEM;

	/* Attempt to locate and parse all the configuration types we know
	 * about
	 */

	/* Service Info (0x0001) - Service Key information */
	store_service_triggers(context, config_data, config_size);

	/* Cmdline (0x0002) - TA Parameters appended to cmdline */
	store_ta_commandline_params(context, config_data, config_size);

	/* Configuration (0x0003) - Service configuration (USB etc) */
	store_service_mode(context, config_data, config_size);

	/* Long press (0x0004) - Time the on-key must be pressed to start
	 * phone
	 */
	store_long_press_time(context, config_data, config_size);

	/* FlaFla Override (0x0005) - Permanent service mode, used by
	 * test-people
	 */
	store_fla_fla_override(context, config_data, config_size);

	/* Reset config (0x0006) - Configuration for forced reset sequence */
	store_reset_cfg(context, config_data, config_size);

	/* vbus_pulse_array (0x0008) - Vibration pattern configutration */
	store_vbus_pulse(context, config_data, config_size);

	/* backlight (0x0009) - Backlight configutration */
	store_backlight(context, config_data, config_size);

	return FCSERR_OK;
}


/******************************************************************************/
/**
 *  This function will get the configuration data for a specefic Config type
 */
/******************************************************************************/
static uint8_t *get_config_data(enum ConfigTypes_t config_type,
	uint32_t *type_sz, const uint8_t *config_data,
	const size_t config_size)
{
	uint8_t *cur_config_data = NULL;
	uint32_t config_data_sz = 0;
	uint32_t current_offs = 2; /* Do not include version magic */
	uint16_t current_sz = 0;
	uint16_t current_type = 0;

	if (!type_sz || !config_data || config_size <= 2) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}

	while (current_offs < config_size) {
		/* Sanity check that current location at least have space
		 * for a size
		 */
		if ((current_offs+sizeof(current_sz)) > config_size)
			break;

		/* Get the unit size */
		current_sz = config_data[current_offs] |
			config_data[current_offs + 1] << 8;

		/* Sanity check the unit size */
		if (current_sz == 0)
			break;

		current_offs += sizeof(current_sz);

		/* Sanity check (unit must not exceed the config_size) */
		if ((current_sz + current_offs) > config_size)
			break;

		/* Sanity check that current location at least have space
		 * for a type
		 */
		if ((current_offs + sizeof(current_type)) > config_size)
			break;

		/* Get the Type */
		current_type = config_data[current_offs] |
			config_data[current_offs + 1] << 8;
		current_offs += sizeof(current_type);

		if ((uint16_t)config_type == current_type) {
			/* the unit size we return does not include the size
			 * of the type
			 */
			config_data_sz = current_sz - sizeof(current_type);
			if (config_data_sz > 0) {
				cur_config_data =
					(uint8_t *)&config_data[current_offs];
			} else {
				cur_config_data = NULL;
			}
			break;
		}
		/* move to the next unit */
		current_offs += current_sz - sizeof(current_type);
	}

	*type_sz = config_data_sz;

	return cur_config_data;
}

/******************************************************************************/
/**
 *  Key Info (0x0001)
 *  Extracts all the service keys from the bootconfig buffer and populates
 *  the following members of the configuration structure:
 *  .serviceKeys
 *  .nofServiceKeys
 *  .softservicePins
 *  .nofSoftservicePins
 *  .recoveryKeys
 *  .nofRecoveryKeys
 *  .fastbootKeys
 *  .nofFastbootKeys
 *  .resetKeys
 *  .nofResetKeys
 *
 *  @returns void
 */
/******************************************************************************/
static void store_service_triggers(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_unit_sz;
	uint8_t *config_unit;

	config_unit = get_config_data(CONFIG_SERVICE_KEYS, &config_unit_sz,
		config_data, config_size);

	if (!((config_unit != NULL) && (config_unit_sz >=
		SERVICE_TRIGGER_EXPECTED_LENGTH)))
		return;

	/* Format of input buffer:
	 * +----------+------+-------+-------+---------+-------+-----+
	 * | NOF PINS | SIZE | SVC_T | TRG_T |  DATA   | SIZE2 | ... |
	 * +----------+------+-------+-------+---------+-------+-----+
	 * |    1B    |  2B  |  1B   |  1B   | SIZE-2B |  2B   | ... |
	 * +----------+------+-------+-------+---------+-------+-----+
	 */
	uint8_t const *cur_trigger = &config_unit[1];
	uint16_t cur_trigger_sz = 0;
	unsigned int i;

	FCS_LOG_INF("Parsing %u service triggers\n", config_unit[0]);
	for (i = 0; i < config_unit[0]; i++) {
		/* Ensure that current trigger contains at least
		 * type and policy
		 */
		if (config_unit_sz < (cur_trigger-config_unit + 4)) {
			FCS_LOG_ERR("Trigger lacks type and/or policy!\n");
			goto next;
		}
		enum ServiceTriggerPolicy_t cur_trigger_policy =
			(cur_trigger[3] & SERVICE_TRIGGER_POLICY) ?
			SERVICE_TRIGGER_PART_OF : SERVICE_TRIGGER_STANDALONE;
		enum ServiceTriggerType_t cur_trigger_type =
			(enum ServiceTriggerType_t)(cur_trigger[3] &
			SERVICE_TRIGGER_MASK);
		cur_trigger_sz = cur_trigger[0] | cur_trigger[1] << 8;

		/* sanity check the cur_trigger_sz
		 * - have to contain at least a service and trigger type
		 * - must not exceed the unit size
		 */
		if (cur_trigger_sz < 2 || cur_trigger_sz >
			(config_unit_sz-(cur_trigger+2-config_unit)))
			goto next;

		struct ServiceTrigger **ppKeyVector = NULL;
		uint8_t *nof_keys = NULL;

		switch (cur_trigger[2]) {
		case SERVICE_TYPE_SRV_PIN:
			ppKeyVector = &context->bootconfig->ServiceKeys;
			nof_keys = &context->bootconfig->nofServiceKeys;
			break;
		case SERVICE_TYPE_SW_SRV:
			ppKeyVector = &context->bootconfig->softServicePins;
			nof_keys = &context->bootconfig->nofSoftServicePins;
			break;
		case SERVICE_TYPE_RECOVERY:
			ppKeyVector = &context->bootconfig->recoveryKeys;
			nof_keys = &context->bootconfig->nofRecoveryKeys;
			break;
		case SERVICE_TYPE_FASTBOOT:
			ppKeyVector = &context->bootconfig->fastbootKeys;
			nof_keys = &context->bootconfig->nofFastbootKeys;
			break;
		case SERVICE_TYPE_RESET:
			ppKeyVector = &context->bootconfig->resetKeys;
			nof_keys = &context->bootconfig->nofResetKeys;
			break;
		default:
			ppKeyVector = NULL;
			break;
		}

		if (ppKeyVector == NULL)
			goto next;

		/* Sanity check the key type size */
		switch (cur_trigger_type) {
		case SERVICE_TRIGGER_KEYPAD:
			if (cur_trigger_sz-2 !=
				SERVICE_TRIGGER_KEYPAD_EXPECTED_SIZE) {
				ppKeyVector = NULL;
				FCS_LOG_ERR("Key trigger of invalid size\n");
			}
			break;
		case SERVICE_TRIGGER_GPIO:
		case SERVICE_TRIGGER_GPIO_IN_PMIC:
		case SERVICE_TRIGGER_GPIO_3:
		case SERVICE_TRIGGER_GPIO_IN_PM0:
		case SERVICE_TRIGGER_GPIO_IN_PM1:
		case SERVICE_TRIGGER_GPIO_IN_PM2:
		case SERVICE_TRIGGER_GPIO_IN_PM3:
			if (cur_trigger_sz-2 !=
				SERVICE_TRIGGER_GPIO_EXPECTED_SIZE) {
				ppKeyVector = NULL;
				FCS_LOG_ERR("GPIO trigger of invalid size\n");
			}
			break;
		case SERVICE_TRIGGER_OTG:
			if (cur_trigger_sz-2 !=
				SERVICE_TRIGGER_OTG_EXPECTED_SIZE) {
				ppKeyVector = NULL;
				FCS_LOG_ERR("OTG trigger of invalid size\n");
			}
			break;
		case SERVICE_TRIGGER_POWER_ON:
			if (cur_trigger_sz-2 !=
				SERVICE_TRIGGER_POWER_ON_EXPECTED_SIZE) {
				ppKeyVector = NULL;
				FCS_LOG_ERR("Power trigger of invalid size\n");
			}
			break;
		case SERVICE_TRIGGER_RESET_ON:
			if (cur_trigger_sz-2 !=
				SERVICE_TRIGGER_RESET_ON_EXPECTED_SIZE) {
				ppKeyVector = NULL;
				FCS_LOG_ERR("Reset trigger of invalid size\n");
			}
			break;
		default:
			ppKeyVector = NULL;
			break;
		}

		if (ppKeyVector == NULL)
			goto next;

		/* allocate the vector buffers and assign the trigger
		 * info to them
		 */
		if (*ppKeyVector == NULL) {
			*ppKeyVector = malloc(MAX_SERVICE_TRIGGERS*
					sizeof(struct ServiceTrigger));
			if (*ppKeyVector == NULL)
				goto next;
		} else if (sizeof(struct ServiceTrigger)*(*nof_keys+1) >
					MAX_SERVICE_TRIGGERS*
					sizeof(struct ServiceTrigger)) {

			/* Allocated buffer is too small */
			free(*ppKeyVector);
			goto next;
		}

		(*ppKeyVector)[*nof_keys].svcTriggerType = cur_trigger_type;
		(*ppKeyVector)[*nof_keys].svcTriggerPolicy = cur_trigger_policy;
		memcpy(&(*ppKeyVector)[*nof_keys].svcTriggerData,
			&cur_trigger[4], cur_trigger_sz-2);
		(*nof_keys)++;
next:
		cur_trigger += cur_trigger_sz + 2;
	}
	FCS_LOG_INF("Detected the following number of service triggers:\n"
		"  Service keys: %u\n"
		"  Soft service pins: %u\n"
		"  Reset keys: %u\n"
		"  Recovery keys: %u\n"
		"  Fastboot keys: %u\n",
		context->bootconfig->nofServiceKeys,
		context->bootconfig->nofSoftServicePins,
		context->bootconfig->nofResetKeys,
		context->bootconfig->nofRecoveryKeys,
		context->bootconfig->nofFastbootKeys);
}

/******************************************************************************/
/**
 *  Cmdline type (0x0002)
 *  Extracts the TA units desired on the kernel commandline and populates
 *  the following members of the configuration structure:
 *  .taCommandLineArgs
 *
 *  @returns void
 */
/******************************************************************************/
static void store_ta_commandline_params(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_unit_sz;
	uint8_t *config_unit;
	uint32_t unitNbr, unitLabel;
	uint32_t currentOffset = 0;
	char *cmd_entry = NULL;

	config_unit = get_config_data(CONFIG_BOOT_PARAM_ADD_TA_UNIT,
		&config_unit_sz, config_data, config_size);

	if ((config_unit == NULL) || (config_unit_sz <
		CMDLINE_DATA_EXPECTED_LENGTH)) {

		FCS_LOG_WRN("No TA units to add to commandline\n");
		return;
	}

	/* Must be at least one more complete TA configuration:
	 * <BootTagType, 4 bytes> <UnitNbr, 4 bytes>
	 */
	while (currentOffset <= (config_unit_sz - 2 * sizeof(uint32_t))) {

		/* Get Unit Label */
		memcpy(&unitLabel, &config_unit[currentOffset],
			sizeof(unitLabel));
		currentOffset += sizeof(unitLabel);

		/* Get the UnitNbr */
		memcpy(&unitNbr, &config_unit[currentOffset], sizeof(unitNbr));
		currentOffset += sizeof(unitNbr);

		/* Check that the unit number is within a valid public range */
		if (unitNbr > MISC_TA_MAXIMUM_PUBLIC_UNIT_ID)
			continue;

		/* Add cmdline v2 for Nagara or later if unitNbr is about MISCTA2473 */
		if (unitNbr == TA_ENABLE_CONSOLE) {
			if (context->is_prototype)
				cmd_entry = ta_to_cmdline_enconsole(unitNbr, unitLabel);

			/* add to cmdline v2 */
			if (cmd_entry != NULL) {
				context->sony_cmdline_additions_v2 = sony_alloc_strcat(
				context->sony_cmdline_additions_v2, " ");
				context->sony_cmdline_additions_v2 = sony_alloc_strcat(
				context->sony_cmdline_additions_v2, cmd_entry);
				free(cmd_entry);
			}
		}

		cmd_entry = ta_to_cmdline(unitNbr, unitLabel);

		if (cmd_entry == NULL)
			continue;

		if (context->bootconfig->taCommandLineArgs == NULL) {
			context->bootconfig->taCommandLineArgs =
				malloc(MAX_CMD_ENTRY_SIZE);
			if (context->bootconfig->taCommandLineArgs == NULL) {
				FCS_LOG_ERR("Out of memory\n");
				free(cmd_entry);
				break;
			}
			strlcpy(context->bootconfig->taCommandLineArgs,
				cmd_entry, MAX_CMD_ENTRY_SIZE);
		} else if (strlen(context->bootconfig->taCommandLineArgs) +
			strlen(cmd_entry) + 3 < MAX_CMD_ENTRY_SIZE) {

			strlcat(context->bootconfig->taCommandLineArgs, " ",
				MAX_CMD_ENTRY_SIZE);
			strlcat(context->bootconfig->taCommandLineArgs,
				cmd_entry, MAX_CMD_ENTRY_SIZE);
		} else {
			FCS_LOG_ERR("No room for additional TA units\n");
		}
		free(cmd_entry);
	}
	if (context->bootconfig->taCommandLineArgs) {
		FCS_LOG_INF("Parsed commandline: %s\n",
		context->bootconfig->taCommandLineArgs);
	}
}

/******************************************************************************/
/**
 *  This function will read a TA unit add and create a string with the following
 *  format: "oemandroidboot.XXXXXXXX=<hex dump of TA unit 0xXXXXXXXX"
 *  Caller must free the pointer returned.
 */
/******************************************************************************/
static char *ta_to_cmdline(uint32_t unitNbr, uint32_t unitLabel)
{
	uint32_t str_sz;
	uint32_t unitSize = 0;
	char *str_buf = NULL;
	char *tag_str = NULL;
	char *data_str = NULL;
	uint8_t *ta_buf = NULL;

	if (sony_boot_ta_simple_read(unitNbr, &ta_buf, &unitSize) ==
		FCSERR_OK) {

		/* Allocate a string as
		 * "oemandroidboot.XXXXXXXX=<hex dump of TA unit 0xXXXXXXXX>"
		 */
		str_sz = 2 * unitSize + strlen("oemandroidboot.") + 8 + 1 + 1;
		str_buf = malloc(str_sz);

		write_be_u32(unitLabel, (uint8_t *)&unitLabel);
		tag_str = bin2ascii((uint8_t *)&unitLabel, 4);
		data_str = bin2ascii(ta_buf, (size_t)unitSize);

		if (str_buf && data_str && tag_str) {
			memset(str_buf, 0, str_sz);
			strlcat(str_buf, "oemandroidboot.", str_sz);
			strlcat(str_buf, tag_str, str_sz);
			strlcat(str_buf, "=", str_sz);
			strlcat(str_buf, data_str, str_sz);
		} else if (str_buf) {
			free(str_buf);
			str_buf = NULL;
		}
	} else {
		FCS_LOG_ERR("MiscTA unit %u could not be read!\n", unitNbr);
	}

	/* Cleanup the temporary data_str and tag_str */
	if (data_str)
		free(data_str);
	if (tag_str)
		free(tag_str);
	if (ta_buf)
		free(ta_buf);

	/* Return the result */
	return str_buf;
}

/******************************************************************************/
/**
 *  This function will read a TA unit add and create a string with the following
 *  format: "qcom_geni_serial.con_enabled=<1 or 0>"
         or "msm_geni_serial.XXXXXXXX=<hex dump of TA unit 0xXXXXXXXX"
 *  this function is specialty for TA2473 only.
 *  Caller must free the pointer returned.
 */
/******************************************************************************/
static char *ta_to_cmdline_enconsole(uint32_t unitNbr, uint32_t unitLabel)
{
	uint32_t str_sz;
	uint32_t unitSize = 0;
	char *str_buf = NULL;
#if defined(FEATURE_SM8450)
	char *tag_str = NULL;
#endif /* FEATURE_SM8450 */
	uint8_t *ta_buf = NULL;
#if !defined(FEATURE_SM8450)
#define	COMMANDLINESTR  "qcom_geni_serial.con_enabled"
#else /* FEATURE_SM8450 */
#define	COMMANDLINESTR  "msm_geni_serial."
#endif /* FEATURE_SM8450 */

	if (sony_boot_ta_simple_read(unitNbr, &ta_buf, &unitSize) ==
		FCSERR_OK) {

#if !defined(FEATURE_SM8450)
		/* Allocate a string as
		 * "oemandroidboot.con_enabled=<1 or 0>"
		 */
		str_sz = 2 * unitSize + strlen(COMMANDLINESTR) + 1 + 1;
		str_buf = malloc(str_sz);

		if (str_buf && unitSize) {
			memset(str_buf, 0, str_sz);
			strlcat(str_buf, COMMANDLINESTR, str_sz);
			if (*ta_buf&0x01)
				strlcat(str_buf, "=1", str_sz);
			else
				strlcat(str_buf, "=0", str_sz);
		}
#else /* FEATURE_SM8450 */
		/* Allocate a string as
		 * "oemandroidboot.XXXXXXXX=<hex dump of TA unit 0xXXXXXXXX>"
		 */
		str_sz = 2 * unitSize + strlen(COMMANDLINESTR) + 8 + 1 + 1;
		str_buf = malloc(str_sz);

		write_be_u32(unitLabel, (uint8_t *)&unitLabel);
		tag_str = bin2ascii((uint8_t *)&unitLabel, 4);

		if (str_buf && tag_str) {
			memset(str_buf, 0, str_sz);
			strlcat(str_buf, COMMANDLINESTR, str_sz);
			strlcat(str_buf, tag_str, str_sz);
			if (*ta_buf&0x01)
				strlcat(str_buf, "=1", str_sz);
			else
				strlcat(str_buf, "=0", str_sz);
		} else if (str_buf) {
			free(str_buf);
			str_buf = NULL;
		}
#endif /* FEATURE_SM8450 */
	} else {
		FCS_LOG_ERR("MiscTA unit %u could not be read!\n", unitNbr);
	}

	/* Cleanup the temporary data_str and tag_str */
#if defined(FEATURE_SM8450)
	if (tag_str)
		free(tag_str);
#endif /* FEATURE_SM8450 */
	if (ta_buf)
		free(ta_buf);

	/* Return the result */
	return str_buf;
}
/******************************************************************************/
/**
 *  Service configuration (0x0003)
 *  Extracts the service configuration from the bootconfig buffer and populates
 *  the following members of the configuration structure:
 *  .USB_Is_Enabled
 *  .disable_Service_Pin
 *  .disable_Sw_Svc
 *
 *  @returns void
 */
/******************************************************************************/
static void store_service_mode(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_unit_sz;
	uint8_t *config_unit;
	uint16_t ServiceCfgFlags;

	config_unit = get_config_data(CONFIG_SERVICE_CFG, &config_unit_sz,
		config_data, config_size);

	if ((config_unit != NULL) &&
		(config_unit_sz == SERVICE_CFG_EXPECTED_LENGTH)) {

		ServiceCfgFlags = config_unit[0] | config_unit[1] << 8;

		/* Service key config value */
		if (ServiceCfgFlags & SERVICE_MODE_USB_SERVICE)
			context->bootconfig->USB_Is_Enabled = true;

		if (ServiceCfgFlags & SERVICE_MODE_DISABLE_SRV_PIN)
			context->bootconfig->disable_Service_Pin = true;

		if (ServiceCfgFlags & SERVICE_MODE_DISABLE_SW_SRV)
			context->bootconfig->disable_Sw_Svc = true;

		FCS_LOG_INF("Service mode configuration:\n"
			"  USB enabled: %s\n"
			"  Service pin enabled: %s\n"
			"  Soft service enabled: %s\n",
			context->bootconfig->USB_Is_Enabled ? "True" : "False",
			context->bootconfig->disable_Service_Pin ?
				"False" : "True",
			context->bootconfig->disable_Sw_Svc ? "False" : "True");
	}
}


/******************************************************************************/
/**
 *  Long press (0x0004)
 *  Extracts the long press duration from the bootconfig buffer and populates
 *  the following member of the configuration structure:
 *  .longPressTimeMS
 *
 *  @returns void
 */
/******************************************************************************/
static void store_long_press_time(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_unit_sz;
	uint8_t *config_unit;

	config_unit = get_config_data(CONFIG_LONGPRESS_TIME, &config_unit_sz,
		config_data, config_size);

	if ((config_unit != NULL) &&
		(config_unit_sz == LONGPRESS_CFG_EXPECTED_LENGTH)) {

		context->bootconfig->longPressTimeMS =
			config_unit[0] | config_unit[1]<<8;
		FCS_LOG_INF("Longpress timeout: %u ms\n",
			context->bootconfig->longPressTimeMS);
	}
}

/******************************************************************************/
/**
 *  FlaFla override (0x0005)
 *  Extracts the FlaFla override flag from the bootconfig buffer and populates
 *  the following member of the configuration structure:
 *  .FlaFlaOverride
 *
 *  @returns void
 */
/******************************************************************************/
static void store_fla_fla_override(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_unit_sz;
	uint8_t *config_unit;

	config_unit = get_config_data(CONFIG_FLAFLA_OVERRIDE, &config_unit_sz,
		config_data, config_size);

	if ((config_unit != NULL) &&
		(config_unit_sz == FLAFLA_CFG_EXPECTED_LENGTH)) {

		context->bootconfig->FlaFlaOverride =
			(config_unit[0] == 0 ? false : true);
		FCS_LOG_INF("FlaFla override is %s\n",
			context->bootconfig->FlaFlaOverride ? "True" : "False");
	}
}

/******************************************************************************/
/**
 *  Reset config (0x0006)
 *  Extracts the Reset configuration from the bootconfig buffer and populates
 *  the following members of the configuration structure:
 *  .resetTimeoutMS
 *  .resetNofPulsesStart
 *  .resetStartPulseOnTimeMS
 *  .resetStartPulseOffTimeMS
 *  .resetNofPulsesEnd
 *  .resetEndPulseOnTimeMS
 *  .resetEndPulseOffTimeMS
 *
 *  @returns void
 */
/******************************************************************************/
static void store_reset_cfg(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_unit_sz;
	uint8_t *config_unit;

	config_unit = get_config_data(CONFIG_RESET_CFG, &config_unit_sz,
		config_data, config_size);

	if ((config_unit != NULL) &&
		(config_unit_sz == RESET_CFG_EXPECTED_LENGTH)) {

		context->bootconfig->resetTimeoutMS =
			config_unit[1] << 8 | config_unit[0];
		context->bootconfig->resetNofPulsesStart = config_unit[2];
		context->bootconfig->resetStartPulseOnTimeMS =
			config_unit[4] << 8 | config_unit[3];
		context->bootconfig->resetStartPulseOffTimeMS =
			config_unit[6] << 8 | config_unit[5];
		context->bootconfig->resetNofPulsesEnd = config_unit[7];
		context->bootconfig->resetEndPulseOnTimeMS =
			config_unit[9] << 8 | config_unit[8];
		context->bootconfig->resetEndPulseOffTimeMS =
			config_unit[11] << 8 | config_unit[10];

		FCS_LOG_INF("Reset configuration:\n"
			"  reset timeout: %u ms\n"
			"  nof start reset pulses: %u\n"
			"  start pulse on time: %u ms\n"
			"  start pulse off time: %u ms\n"
			"  nof end reset pulses: %u\n"
			"  end pulse on time: %u ms\n"
			"  end pulse off time: %u ms\n",
			context->bootconfig->resetTimeoutMS,
			context->bootconfig->resetNofPulsesStart,
			context->bootconfig->resetStartPulseOnTimeMS,
			context->bootconfig->resetStartPulseOffTimeMS,
			context->bootconfig->resetNofPulsesEnd,
			context->bootconfig->resetEndPulseOnTimeMS,
			context->bootconfig->resetEndPulseOffTimeMS);
	}
}

/******************************************************************************/
/**
 *  VBUS detection vibration (0x0008)
 *  Extracts the configuration data and applies it to
 *  vbus_pulse_array in the configuration structure.
 *
 *  @returns void
 */
/******************************************************************************/
static void store_vbus_pulse(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_num_of_bytes = 0;
	uint8_t *config_unit;
	uint8_t i = 0, j = 0;

	config_unit = get_config_data(CONFIG_VBUS_VIBRATION,
		&config_num_of_bytes, config_data, config_size);

	if ((!config_unit) || ((config_num_of_bytes % 2) == 0) ||
		(config_num_of_bytes < VBUS_DATA_EXPECTED_LENGTH)) {

		FCS_LOG_ERR("None or incorrect vbus_pulse configuration!\n");
		return;
	}

	config_num_of_bytes += 1;
	context->bootconfig->vbus_pulse_array =
		(uint16_t *)malloc(config_num_of_bytes);
	if (context->bootconfig->vbus_pulse_array == NULL) {
		FCS_LOG_ERR("Failed to allocate VBUS pulse array!\n");
		return;
	}

	context->bootconfig->vbus_pulse_array[i] = 0;

	/* Get number of pulses */
	context->bootconfig->vbus_pulse_array[0] = config_unit[0];

	for (i = 1, j = 1; i < (config_num_of_bytes / 2); i++) {
		context->bootconfig->vbus_pulse_array[i] =
			config_unit[j + 1] << 8 | config_unit[j];
		j += 2;
	}
}

/******************************************************************************/
/**
 *  BACKLIGHT enable/disable (0x0009)
 *  Extracts the configuration data and populate
 *  the backlight member of the configuration structure
 *
 *  @returns void
 */
/******************************************************************************/
static void store_backlight(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	uint32_t config_num_of_bytes = 0;
	uint8_t *config_unit;

	config_unit = get_config_data(CONFIG_BACKLIGHT, &config_num_of_bytes,
		config_data, config_size);

	if (config_unit &&
		(config_num_of_bytes == BACKLIGHT_DATA_EXPECTED_LENGTH)) {
		/* Get backlight configuration */
		context->bootconfig->backlightEnable =
			(config_unit[0] == 0 ? false : true);
	} else {
		FCS_LOG_ERR("No backlight configuration to store!");
	}
}

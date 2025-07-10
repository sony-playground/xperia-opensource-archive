/*
 * Copyright (C) 2012-2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "hwconf_parser.h"
#include "fcslog.h"
#include <stdlib.h>
#include <string.h>
#include "fcserr.h"

enum hwconf_Security_Flags_t {
	hwconf_DEFAULT_SECURITY_OFF = 0,
	hwconf_DEFAULT_SECURITY_ON  = 1,
	hwconf_DEFAULT_SECURITY_MAX = 0xFFFF
};

enum hwconf_hwconfversion_t {
	hwconf_HW_CONF_V1 = 1,
	hwconf_HW_CONF_V2 = 2,
	hwconf_HW_CONF_V3 = 3,
	hwconf_HW_CONF_V4 = 4,
	hwconf_HW_CONF_V5 = 5,
	hwconf_HW_CONF_V6 = 6,
	hwconf_HW_CONF_V7 = 7,
	hwconf_HW_CONF_VERSION_MAX = 0xFFFF
};

/**
 * PartitionID_data.
 */
struct hwconf_part_id {
	uint8_t length;
	uint8_t *data;
	struct hwconf_part_id *next;
};

/**
 * Security Configuration for a certificate type (Cert CN)
 * Minimum serialized size is 10 bytes.
 */
struct hwconf_security_configuration {
	uint16_t version;
	uint16_t certificate_cn_length;
	uint8_t *certificate_cn;
	uint16_t aid;
	uint16_t security_flags;
	uint16_t part_id_array_length;
	struct hwconf_part_id *part_id_array;
	struct hwconf_security_configuration *next;
};

/**
 * Misc data for loader, boot, SW etc
 * Minimum serialized size if 4 bytes empty
 */
struct hwconf_misc_data {
	enum hwconf_misc_data_type_t misc_data_type;
	uint16_t length;
	uint8_t *data;
	struct hwconf_misc_data *next;
};

/**
 * Configuration data common to all devices of a given model.
 * Minimum serialized size is 4 bytes
 */
struct hwconf_model_conf {
	uint16_t product_id;
	uint16_t misc_data_length;
	struct hwconf_misc_data *misc_data_array;
};

/**
 * Device Identifier.
 * minimum serialised size is 2 bytes
 */
struct hwconf_device_id {
	uint16_t length;
	uint8_t *id;
	struct hwconf_device_id *next;
};

/**
 * Phone identifier
 * IMEI, MEID, etc
 * minimum serialised size is 4 bytes
 */
struct hwconf_phone_id {
	enum hwconf_phone_ID_t id_type;
	uint16_t length;
	uint8_t *id;
	struct hwconf_phone_id *next;
};

/**
 * Device unique configuration data.
 * minimum serialized size is 10 bytes
 */
struct hwconf_device_configuration {
	uint16_t phone_id_array_length;
	struct hwconf_phone_id *phone_id_array;
	uint16_t global_security_flags;
	uint16_t security_config_length;
	struct hwconf_security_configuration *security_config_array;
	uint16_t device_id_array_length;
	struct hwconf_device_id *device_id_array;
	uint16_t hwc_dk_length;
	uint8_t *hwc_dk;
};

/**
 * Configuration Data format
 * minimum serialised size is 2+2+4+10 = 16 bytes
 */
struct hwconf_data {
	uint16_t version;
	uint16_t flags;
	struct hwconf_model_conf modelConfig;
	struct hwconf_device_configuration deviceConfig;
};

/**
 * This structure will be used by when parsing the hwconfig.
 * The hwconfig data will be stored in the hwconf_data structure.
 * Rest of the members are used to keep track of the parsing
 * itself. Each time the hwconfig will be read and stored into
 * this structure the hwconf_pos will be increased with the
 * number of bytes read and the hwconf_size decreased.
 * When the hwconf_size is zero means that we have parsed through
 * the whole hwconfig.
 *
 */
struct hwconf_parse {
	/* Pointer to the current parsing position in hwconf */
	uint8_t *hwconf_pos;

	/* Number bytes left to be parsed, zero when finished */
	uint32_t hwconf_size;

	/* Parsed hwconfig data is stored in this structure */
	struct hwconf_data hwconf;

};

/******************************************************************************
 *              Internal utility functions used by init_ functions             *
 ******************************************************************************/
static int deinit_misc_data_array(struct hwconf_model_conf *model_conf);
static int deinit_phone_id_array(
		struct hwconf_device_configuration *device_conf);
static int deinit_sec_conf_part_id_array(
		struct hwconf_security_configuration *sec_conf);
static int deinit_sec_conf_array(
		struct hwconf_device_configuration *device_conf);

static int deinit_dev_id_array(
		struct hwconf_device_configuration *device_conf);

static int hwconf_read(struct hwconf_parse *parse_data,
		uint8_t *data,
		uint32_t length)
{
	if (parse_data->hwconf_size >= length) {
		/* Read the data from hwconfig */
		memcpy(data, parse_data->hwconf_pos, length);

		/* Update the parsing position and bytes left to parse */
		parse_data->hwconf_pos += length;
		parse_data->hwconf_size -= length;

		return FCSERR_OK;
	}
	return -FCSERR_EINVAL;
}


static int hwconf_read_uint16(struct hwconf_parse *parse_data, uint16_t *val)
{
	if (parse_data->hwconf_size >= sizeof(*val)) {
		*val  = *(parse_data->hwconf_pos++) << 8;
		*val |= *(parse_data->hwconf_pos++);

		parse_data->hwconf_size -= sizeof(*val);
		return FCSERR_OK;
	}
	return -FCSERR_EINVAL;
}


static int hwconf_read_uint8(struct hwconf_parse *parse_data, uint8_t *val)
{
	if (parse_data->hwconf_size >= sizeof(*val)) {
		*val = *(parse_data->hwconf_pos++);

		parse_data->hwconf_size -= sizeof(*val);
		return FCSERR_OK;
	}
	return -FCSERR_EINVAL;
}


/******************************************************************************
 *       Internal parser functions used by the hwconf_parser_init()            *
 ******************************************************************************/

static int init_version(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t version = 0;

	struct hwconf_data *hwconf = &parse_data->hwconf;

	/* Read the version from hwconfig */
	res = hwconf_read_uint16(parse_data, &version);
	if (res) {
		FCS_LOG_ERR("Failed to read version\n");
		goto failed;
	}

	/* This parser only support the hwconf version 7 */
	if (version != hwconf_HW_CONF_V7) {
		FCS_LOG_ERR("Only hwconfig version %d supported\n",
				hwconf_HW_CONF_V7);
		res = -FCSERR_EVER;
		goto failed;
	}

	/* Update the hwconfig data structure */
	hwconf->version = version;

	return FCSERR_OK;

failed:
	return res;
}


static int init_flags(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t flags = 0;

	struct hwconf_data *hwconf = &parse_data->hwconf;

	/* Read the flags from hwconfig */
	res = hwconf_read_uint16(parse_data, &flags);
	if (res) {
		FCS_LOG_ERR("Read flags fail\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	hwconf->flags = flags;

	return FCSERR_OK;

failed:
	return res;
}


static int init_product_id(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t product_id = 0;
	struct hwconf_model_conf *model_conf =
		&parse_data->hwconf.modelConfig;

	/* Read the product ID from hwconfig */
	res = hwconf_read_uint16(parse_data, &product_id);
	if (res) {
		FCS_LOG_ERR("Failed to read product id\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	model_conf->product_id = product_id;

	return FCSERR_OK;

failed:
	return res;
}


static int init_misc_data_array_length(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t array_length = 0;
	struct hwconf_model_conf *model_conf =
		&parse_data->hwconf.modelConfig;

	/* Read the misc data array length from hwconfig */
	res = hwconf_read_uint16(parse_data, &array_length);
	if (res) {
		FCS_LOG_ERR("Failed to read misc data array length\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	model_conf->misc_data_length = array_length;

	return FCSERR_OK;

failed:
	return res;
}


static int init_misc_data_type(struct hwconf_parse *parse_data,
		struct hwconf_misc_data *misc_data)
{
	int res;
	uint8_t misc_type = MAX_MISC_DATA_TYPE;

	/* Read the misc data type from hwconfig and update the parse struct */
	res = hwconf_read_uint8(parse_data, &misc_type);
	if (res) {
		FCS_LOG_ERR("Failed to read misc type\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	misc_data->misc_data_type = (enum hwconf_misc_data_type_t)misc_type;

	return FCSERR_OK;

failed:
	return res;
}


static int init_misc_data_length(struct hwconf_parse *parse_data,
		struct hwconf_misc_data *misc_data)
{
	int res;

	/* Read the misc data length from hwconfig */
	res = hwconf_read_uint16(parse_data, &misc_data->length);
	if (res) {
		FCS_LOG_ERR("Failed to read misc data length\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_misc_data(struct hwconf_parse *parse_data,
		struct hwconf_misc_data *misc_data)
{
	int res;
	uint8_t *data = NULL;
	uint32_t length = misc_data->length;

	/* Allocate the misc data buffer */
	data = malloc(sizeof(uint8_t)*length);
	if (data == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto failed;
	}

	/* Reset the misc data buffer */
	memset(data, 0, sizeof(uint8_t)*length);

	/* Read the hwconfig misc data into the buffer */
	res = hwconf_read(parse_data, data, length);
	if (res) {
		FCS_LOG_ERR("Failed to read misc data\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	misc_data->data = data;

	return FCSERR_OK;

failed:
	free(data);
	misc_data->data = NULL;

	return res;
}


static int init_misc_data_array(struct hwconf_parse *parse_data)
{
	int res;
	struct hwconf_model_conf *model_conf =
		&parse_data->hwconf.modelConfig;
	struct hwconf_misc_data *misc_data = NULL;
	struct hwconf_misc_data *prev = NULL;
	uint16_t array_length = 0;
	uint16_t bytes_read = 0;
	uint16_t parse_size = 0;

	/* Sanity check */
	if (model_conf->misc_data_array != NULL) {
		/* Invalid parameters or already initialized array */
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Get the total misc data array length */
	res = init_misc_data_array_length(parse_data);
	if (res) {
		FCS_LOG_ERR("Failed to get misc data array length\n");
		goto failed;
	}

	/* Store the total misc data array length */
	array_length = model_conf->misc_data_length;

	/* Update the parser structure with the misc data array */
	while (bytes_read < array_length) {
		/* Allocate the misc data array */
		misc_data = malloc(sizeof(struct hwconf_misc_data));
		if (misc_data == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto failed;
		}

		/* Reset the misc data structure */
		memset(misc_data, 0, sizeof(struct hwconf_misc_data));

		if (model_conf->misc_data_array == NULL) {
			/* Init the parser structure with the first
			   misc data element.*/
			model_conf->misc_data_array = misc_data;
		} else {
			/* Link the array */
			prev->next = misc_data;
		}

		/* First read the size/bytes currently left to pars */
		parse_size = parse_data->hwconf_size;

		/* Init the type for the entry in the array */
		res = init_misc_data_type(parse_data, misc_data);
		if (res) {
			FCS_LOG_ERR("Init misc data type fail\n");
			goto failed;
		}

		/* Init the length for the entry in the array */
		res = init_misc_data_length(parse_data, misc_data);
		if (res) {
			FCS_LOG_ERR("Init misc data length fail\n");
			goto failed;
		}

		/* Init the misc data for the entry in the array */
		res = init_misc_data(parse_data, misc_data);
		if (res) {
			FCS_LOG_ERR("Init misc data fail\n");
			goto failed;
		}

		/* Calculate the bytes read by looking at how hwconf_size
		   has decreased */
		bytes_read += (parse_size - parse_data->hwconf_size);

		/* Keep the pointer to the last array element */
		prev = misc_data;

	}

	return FCSERR_OK;

failed:
	/* Return original return value */
	if (deinit_misc_data_array(model_conf) != FCSERR_OK)
		FCS_LOG_ERR("Failed to deinit misc_data\n");
	return res;
}


static int init_phone_id_array_length(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t array_length = 0;
	struct hwconf_device_configuration *device_conf =
		&parse_data->hwconf.deviceConfig;

	/* Read the misc data array length from hwconfig */
	res = hwconf_read_uint16(parse_data, &array_length);
	if (res) {
		FCS_LOG_ERR("Failed to read array length\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	device_conf->phone_id_array_length = array_length;

	return FCSERR_OK;

failed:
	return res;
}


static int init_phone_id_type(struct hwconf_parse *parse_data,
		struct hwconf_phone_id *phone_id)
{
	int res;
	uint8_t id_type = 0;

	/* Read the misc data type from hwconfig and update the parse struct */
	res = hwconf_read_uint8(parse_data, &id_type);
	if (res) {
		FCS_LOG_ERR("Failed to read id type\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	phone_id->id_type = (enum hwconf_phone_ID_t)id_type;

	return FCSERR_OK;

failed:
	return res;
}


static int init_phone_id_length(struct hwconf_parse *parse_data,
		struct hwconf_phone_id *phone_id)
{
	int res;

	/* Read the misc data length from hwconfig */
	res = hwconf_read_uint16(parse_data, &phone_id->length);
	if (res) {
		FCS_LOG_ERR("Failed to get phone id length\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_phone_id(struct hwconf_parse *parse_data,
		struct hwconf_phone_id *phone_id)
{
	int res;
	uint8_t *id = NULL;
	uint32_t length = phone_id->length;

	/* Allocate the phone id buffer */
	id = malloc(sizeof(uint8_t)*length);
	if (id == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto failed;
	}

	/* Reset the phone id buffer */
	memset(id, 0, sizeof(uint8_t)*length);

	/* Read the hwconfig phone id into the buffer */
	res = hwconf_read(parse_data, id, length);
	if (res) {
		FCS_LOG_ERR("Failed to read phone id\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	phone_id->id = id;

	return FCSERR_OK;

failed:
	free(id);
	phone_id->id = NULL;

	return res;
}


static int init_phone_id_array(struct hwconf_parse *parse_data)
{
	int res;
	struct hwconf_device_configuration *device_conf =
		&parse_data->hwconf.deviceConfig;
	struct hwconf_phone_id *phone_id = NULL;
	struct hwconf_phone_id *prev = NULL;
	uint16_t array_length = 0;
	uint16_t bytes_read = 0;
	uint16_t parse_size = 0;

	/* Sanity check */
	if (device_conf->phone_id_array != NULL) {
		/* Invalid parameters or already initialized array */
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Get and store the total phone id array length in
	   hwconf_parse struct */
	res = init_phone_id_array_length(parse_data);
	if (res) {
		FCS_LOG_ERR("Failed to get phone id array length\n");
		goto failed;
	}

	/* Store the total phone id data array length */
	array_length = device_conf->phone_id_array_length;

	/* Update the parser structure with the phone id array */
	while (bytes_read < array_length) {
		/* Allocate the phone id array element */
		phone_id = malloc(sizeof(struct hwconf_phone_id));

		/* Check if malloc failed */
		if (phone_id == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto failed;
		}

		/* Reset the phone id data structure */
		memset(phone_id, 0, sizeof(struct hwconf_phone_id));

		if (device_conf->phone_id_array == NULL) {
			/* Init the parser structure with the first
			   phone id element.*/
			device_conf->phone_id_array = phone_id;
		} else {
			/* Link the array element with the previous */
			prev->next = phone_id;
		}

		/* First read the size/bytes currently left to pars */
		parse_size = parse_data->hwconf_size;

		/* Init the type for the entry in the array */
		res = init_phone_id_type(parse_data, phone_id);
		if (res) {
			FCS_LOG_ERR("Failed to init phone id type\n");
			goto failed;
		}

		/* Init the length for the entry in the array */
		res = init_phone_id_length(parse_data, phone_id);
		if (res) {
			FCS_LOG_ERR("Failed to init phone id length\n");
			goto failed;
		}

		/* Init the phone id for the entry in the array */
		res = init_phone_id(parse_data, phone_id);
		if (res) {
			FCS_LOG_ERR("Failed to init phone id\n");
			goto failed;
		}

		/* Calculate the bytes read by looking at how
		   hwconf_size has decreased */
		bytes_read += (parse_size - parse_data->hwconf_size);

		/* Keep the pointer to the last array element */
		prev = phone_id;

	}

	return FCSERR_OK;

failed:

	if (deinit_phone_id_array(device_conf) != FCSERR_OK)
		FCS_LOG_ERR("Failed to deinit phone id array\n");

	return res;
}


static int init_global_sec_flags(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t flags = 0;
	struct hwconf_device_configuration *device_conf = NULL;

	/* Setup structures */
	device_conf =
		&((struct hwconf_parse *)parse_data)->hwconf.deviceConfig;

	/* Read the flags from hwconfig */
	res = hwconf_read_uint16(parse_data, &flags);
	if (res) {
		FCS_LOG_ERR("Failed to get flags\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	device_conf->global_security_flags = flags;

	return FCSERR_OK;

failed:
	return res;
}

static int init_sec_config_length(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t length = 0;
	struct hwconf_device_configuration *device_conf = NULL;

	/* Setup structures */
	device_conf =
		&((struct hwconf_parse *)parse_data)->hwconf.deviceConfig;

	/* Read the sec config from hwconfig */
	res = hwconf_read_uint16(parse_data, &length);
	if (res) {
		FCS_LOG_ERR("Failed to read security config length\n");
		goto failed;
	}

	if (length) {
		FCS_LOG_ERR("Sec configuration in hwconfig not 0.\n");
		res = -FCSERR_EINFOR;
		goto failed;
	}
	/* Update the hwconfig data structure */
	device_conf->security_config_length = length;

	return FCSERR_OK;

failed:
	return res;
}

static int init_sec_version(
		struct hwconf_parse *parse_data,
		struct hwconf_security_configuration *security_conf)
{
	int res;

	/* Read the flags from hwconfig and update parsing structure */
	res = hwconf_read_uint16(parse_data, &security_conf->version);
	if (res) {
		FCS_LOG_ERR("Failed to get security config version\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_sec_cert_cn_length(
		struct hwconf_parse *parse_data,
		struct hwconf_security_configuration *security_conf)
{
	int res;

	/* Read the flags from hwconfig and update parsing structure */
	res = hwconf_read_uint16(parse_data,
			&security_conf->certificate_cn_length);
	if (res) {
		FCS_LOG_ERR("Failed to get certificate cn length\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_sec_cert_cn_data(
		struct hwconf_parse *parse_data,
		struct hwconf_security_configuration *security_conf)
{
	int res;
	uint8_t *cert = NULL;
	uint32_t length = security_conf->certificate_cn_length;

	/* Allocate the certificate cn buffer */
	cert = malloc(sizeof(uint8_t)*length);
	if (cert == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto failed;
	}

	/* Reset the certicate cn data buffer */
	memset(cert, 0, sizeof(uint8_t)*length);

	/* Read the hwconfig certificate cn data into the buffer */
	res = hwconf_read(parse_data, cert, length);
	if (res) {
		FCS_LOG_ERR("Failed to get cn data\n");
		goto failed;
	}

	/* Update the security config structure */
	security_conf->certificate_cn = cert;

	return FCSERR_OK;

failed:
	free(cert);
	security_conf->certificate_cn = NULL;

	return res;
}


static int init_sec_aid(struct hwconf_parse *parse_data,
		struct hwconf_security_configuration *security_conf)
{
	int res;

	/* Read the aid from hwconfig and update parsing structure */
	res = hwconf_read_uint16(parse_data, &security_conf->aid);
	if (res) {
		FCS_LOG_ERR("Failed to read sec config aid\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_sec_flags(struct hwconf_parse *parse_data,
		struct hwconf_security_configuration *security_conf)
{
	int res;

	/* Read the aid from hwconfig and update parsing structure */
	res = hwconf_read_uint16(parse_data, &security_conf->security_flags);
	if (res) {
		FCS_LOG_ERR("Failed to get sec config security flags\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_sec_part_id_array_length(
		struct hwconf_parse *parse_data,
		struct hwconf_security_configuration *security_conf)
{
	int res;

	/* Read the partition id length from hwconfig and update
	   parsing structure.*/
	res = hwconf_read_uint16(parse_data,
			&security_conf->part_id_array_length);
	if (res) {
		FCS_LOG_ERR("Failed to get partition id array length\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_sec_part_id_length(struct hwconf_parse *parse_data,
		struct hwconf_part_id *partition_id)
{
	int res;

	/* Read the partition id length from hwconfig and update
	   parsing structure.*/
	res = hwconf_read_uint8(parse_data, &partition_id->length);
	if (res) {
		FCS_LOG_ERR("Failed to get partition id length\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_sec_part_id_data(struct hwconf_parse *parse_data,
		struct hwconf_part_id *partition_id)
{
	int res;
	uint8_t *part_data = NULL;
	uint32_t length = partition_id->length;

	/* Allocate the certificate cn buffer */
	part_data = malloc(sizeof(uint8_t)*length);
	if (part_data == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto failed;
	}

	/* Reset the certicate cn data buffer */
	memset(part_data, 0, sizeof(uint8_t)*length);

	/* Read the hwconfig certificate cn data into the buffer */
	res = hwconf_read(parse_data, part_data, length);
	if (res) {
		FCS_LOG_ERR("Failed to get partition cn data\n");
		goto failed;
	}

	/* Update the security config structure */
	partition_id->data = part_data;

	return FCSERR_OK;

failed:
	free(part_data);
	partition_id->data = NULL;

	return res;
}


static int init_sec_partition_id_array(
		struct hwconf_parse *parse_data,
		struct hwconf_security_configuration *sec_conf)
{
	int res;
	struct hwconf_part_id *part_id = NULL;
	struct hwconf_part_id *prev = NULL;
	uint16_t array_length = 0;
	uint16_t bytes_read = 0;
	uint16_t parse_size = 0;

	/* Sanity check */
	if (sec_conf->part_id_array != NULL) {
		/* Invalid parameters or already initialized array */
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Get and store the total security config array length in
	   hwconf_parse struct */
	res = init_sec_part_id_array_length(parse_data, sec_conf);
	if (res) {
		FCS_LOG_ERR("failed to get sec config array\n");
		goto failed;
	}

	/* Store the total partition array length */
	array_length = sec_conf->part_id_array_length;

	/* Update the parser structure with the security config array */
	while (bytes_read < array_length) {
		/* Allocate the partition id array element */
		part_id = malloc(sizeof(struct hwconf_part_id));

		/* Check if malloc failed */
		if (part_id == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto failed;
		}

		/* Reset the partition id structure */
		memset(part_id, 0, sizeof(struct hwconf_part_id));

		if (sec_conf->part_id_array == NULL) {
			/* Init the parser structure with the first
			   misc data element.*/
			sec_conf->part_id_array = part_id;
		} else {
			/* Link the current array element with the previous */
			prev->next = part_id;
		}

		/* First read the size/bytes currently left to pars */
		parse_size = parse_data->hwconf_size;

		/* Init the partition id length for the entry in the array */
		res = init_sec_part_id_length(parse_data, part_id);
		if (res) {
			FCS_LOG_ERR("Failed to init sec part id length\n");
			goto failed;
		}

		/* Init the partition id data for the entry in the array */
		res = init_sec_part_id_data(parse_data, part_id);
		if (res) {
			FCS_LOG_ERR("Failed to init partition id\n");
			goto failed;
		}

		/* Calculate the bytes read by looking at how hwconf_size
		   has decreased */
		bytes_read += (parse_size - parse_data->hwconf_size);

		/* Keep the pointer to the last array element */
		prev = part_id;

	}

	return FCSERR_OK;

failed:
	if (deinit_sec_conf_part_id_array(sec_conf) != FCSERR_OK)
		FCS_LOG_ERR("Failed to deinit sec_partition_id_array\n");

	return res;
}

static int init_sec_config_array(struct hwconf_parse *parse_data)
{
	int res;
	struct hwconf_device_configuration *device_conf =
		&parse_data->hwconf.deviceConfig;
	struct hwconf_security_configuration *security_conf = NULL;
	struct hwconf_security_configuration *prev = NULL;
	uint16_t array_length = 0;
	uint16_t bytes_read = 0;
	uint16_t parse_size = 0;

	/* Sanity check */
	if (device_conf->security_config_array != NULL) {
		/* Invalid parameters or already initialized array */
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Store the total phone id data array length */
	array_length = device_conf->security_config_length;

	/* Update the parser structure with the security config array */
	while (bytes_read < array_length) {
		/* Allocate the security config array element */
		security_conf =
			malloc(sizeof(struct hwconf_security_configuration));

		/* Check if malloc failed */
		if (security_conf == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto failed;
		}

		/* Reset the security config structure */
		memset(security_conf, 0,
				sizeof(struct hwconf_security_configuration));

		if (device_conf->security_config_array == NULL) {
			/* Init the parser structure with the first misc
			   data element.*/
			device_conf->security_config_array = security_conf;
		} else {
			/* Link the current array element with the previous */
			prev->next = security_conf;
		}

		/* First read the size/bytes currently left to pars */
		parse_size = parse_data->hwconf_size;

		/* Init the security conf version for the entry in the array */
		res = init_sec_version(parse_data, security_conf);
		if (res) {
			FCS_LOG_ERR("Failed to init security config\n");
			goto failed;
		}

		/* Init the certificate CN length for the entry in the array */
		res = init_sec_cert_cn_length(parse_data, security_conf);
		if (res) {
			FCS_LOG_ERR("Failed to init cert cn length\n");
			goto failed;
		}

		/* Init the certificate CN data for the entry in the array */
		res = init_sec_cert_cn_data(parse_data, security_conf);
		if (res) {
			FCS_LOG_ERR("Failed to init cert cn data\n");
			goto failed;
		}

		/* Init the AID for the entry in the array */
		res = init_sec_aid(parse_data, security_conf);
		if (res) {
			FCS_LOG_ERR("Failed to init security config aid\n");
			goto failed;
		}

		/* Init the security config security flags for the entry
		   in the array */
		res = init_sec_flags(parse_data, security_conf);
		if (res) {
			FCS_LOG_ERR("Failed to init security config flags\n");
			goto failed;
		}

		/* Init the partition id array for the entry in the array */
		res = init_sec_partition_id_array(parse_data, security_conf);
		if (res) {
			FCS_LOG_ERR("Failed to init security config part id\n");
			goto failed;
		}

		/* Calculate the bytes read by looking at how hwconf_size
		   has decreased */
		bytes_read += (parse_size - parse_data->hwconf_size);

		/* Keep the pointer to the last array element */
		prev = security_conf;

	}

	return FCSERR_OK;

failed:
	if (deinit_sec_conf_array(device_conf) != FCSERR_OK)
		FCS_LOG_ERR("Deinit of sec conf array failed\n");

	return res;
}

static int init_dev_id_total_length(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t dev_id_total_length = 0;
	struct hwconf_device_configuration *device_conf =
		&parse_data->hwconf.deviceConfig;

	/* Read the device id total length from hwconfig */
	res = hwconf_read_uint16(parse_data, &dev_id_total_length);
	if (res) {
		FCS_LOG_ERR("Failed to get devide id length\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	device_conf->device_id_array_length = dev_id_total_length;

	return FCSERR_OK;

failed:
	return res;
}



static int init_dev_id_length(struct hwconf_parse *parse_data,
		struct hwconf_device_id *device_id)
{
	int res;

	/* Read the device id length from hwconfig */
	res = hwconf_read_uint16(parse_data, &device_id->length);
	if (res) {
		FCS_LOG_ERR("Failed to read device id length\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int init_dev_id_data(struct hwconf_parse *parse_data,
		struct hwconf_device_id *device_id)
{
	int res;
	uint8_t *id = NULL;
	uint32_t length = device_id->length;

	/* Allocate the phone id buffer */
	id = malloc(sizeof(uint8_t)*length);
	if (id == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto failed;
	}

	/* Reset the device id buffer */
	memset(id, 0, sizeof(uint8_t)*length);

	/* Read the hwconfig phone id into the buffer */
	res = hwconf_read(parse_data, id, length);
	if (res) {
		FCS_LOG_ERR("Failed to read phone id\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	device_id->id = id;

	return FCSERR_OK;

failed:
	free(id);
	device_id->id = NULL;

	return res;
}


static int init_dev_id_array(struct hwconf_parse *parse_data)
{
	int res;
	struct hwconf_device_configuration *device_conf =
		&parse_data->hwconf.deviceConfig;
	struct hwconf_device_id *device_id = NULL;
	struct hwconf_device_id *prev = NULL;
	uint16_t array_length = 0;
	uint16_t bytes_read = 0;
	uint16_t parse_size = 0;

	/* Sanity check */
	if (device_conf->device_id_array != NULL) {
		/* Invalid parameters or already initialized array */
		FCS_LOG_ERR("Invalid parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Store the total device id data array length */
	array_length = device_conf->device_id_array_length;

	/* Update the parser structure with the device id array */
	while (bytes_read < array_length) {
		/* Allocate the device id array element */
		device_id = malloc(sizeof(struct hwconf_device_id));

		/* Check if malloc failed */
		if (device_id == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto failed;
		}

		/* Reset the device id structure */
		memset(device_id, 0, sizeof(struct hwconf_device_id));

		if (device_conf->device_id_array == NULL) {
			/* Init the parser structure with the first
			   device id element.*/
			device_conf->device_id_array = device_id;
		} else {
			/* Link the current array element with the previous */
			prev->next = device_id;
		}

		/* First read the size/bytes currently left to pars */
		parse_size = parse_data->hwconf_size;

		/* Init the device id length for the entry in the array */
		res = init_dev_id_length(parse_data, device_id);
		if (res) {
			FCS_LOG_ERR("Failed to get device id len\n");
			goto failed;
		}

		/* Init the device id data for the entry in the array */
		res = init_dev_id_data(parse_data, device_id);
		if (res) {
			FCS_LOG_ERR("Failed to get device id\n");
			goto failed;
		}

		/* Calculate the bytes read by looking at how hwconf_size
		   has decreased */
		bytes_read += (parse_size - parse_data->hwconf_size);

		/* Keep the pointer to the last array element */
		prev = device_id;

	}

	return FCSERR_OK;

failed:
	if (deinit_dev_id_array(device_conf) != FCSERR_OK)
		FCS_LOG_ERR("Failed to deinit dev id array\n");

	return res;
}


/**
 *  This function reads the hwc device key from the hwconfig and updates
 *  the internal hwconf_parse_data structure with this data.
 *
 *  @param [in]     parse_data    A pointer to the hwconfig parsing structure.
 *
 *  @returns Success or error indication
 */
static int init_hwc_dk_length(struct hwconf_parse *parse_data)
{
	int res;
	uint16_t length = 0;
	struct hwconf_device_configuration *device_conf = NULL;

	/* Setup structures */
	device_conf =
		&((struct hwconf_parse *)parse_data)->hwconf.deviceConfig;

	/* Read the dk-len from hwconfig */
	res = hwconf_read_uint16(parse_data, &length);
	if (res) {
		FCS_LOG_ERR("Faield to get dk length\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	device_conf->hwc_dk_length = length;

	return FCSERR_OK;

failed:
	return res;
}


static int init_hwc_dk_data(struct hwconf_parse *parse_data)
{
	int res;
	uint8_t *hwc_dk = NULL;
	uint32_t length = 0;
	struct hwconf_device_configuration *device_conf = NULL;

	/* Setup structures */
	device_conf =
		&((struct hwconf_parse *)parse_data)->hwconf.deviceConfig;

	/* Get the HWC device key length */
	length = device_conf->hwc_dk_length;

	/* Allocate the hwc device key buffer */
	hwc_dk = malloc(sizeof(uint8_t)*length);
	if (hwc_dk == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto failed;
	}

	/* Reset the hwc device key buffer */
	memset(hwc_dk, 0, sizeof(uint8_t)*length);

	/* Read the hwconfig hwc device key into the buffer */
	res = hwconf_read(parse_data, hwc_dk, length);
	if (res) {
		FCS_LOG_ERR("Failed to get device key\n");
		goto failed;
	}

	/* Update the hwconfig data structure */
	device_conf->hwc_dk = hwc_dk;

	return FCSERR_OK;

failed:
	free(hwc_dk);
	device_conf->hwc_dk = NULL;

	return res;
}

/******************************************************************************
 *       Internal support functions used by the interfaces                     *
 ******************************************************************************/
static int get_misc_data_by_index_type(uint16_t index,
		enum hwconf_misc_data_type_t type,
		struct hwconf_misc_data **ppmisc_data,
		hwconf_handle_t handle)
{
	int res;
	uint8_t i = 0;
	struct hwconf_model_conf *model_conf = NULL;
	struct hwconf_misc_data *misc_data = NULL;

	model_conf = &((struct hwconf_parse *)handle)->hwconf.modelConfig;
	misc_data = model_conf->misc_data_array;


	/* Set the output to NULL */
	*ppmisc_data = NULL;

	/* Find the misc data */
	while (misc_data != NULL) {
		if (misc_data->misc_data_type == type) {
			if (i == index) {
				/* Misc data found */
				*ppmisc_data = misc_data;
				break;
			}

			/*Increase index counter */
			i++;
		}

		/* Proceed to next misc data */
		misc_data = misc_data->next;
	}

	/* Check if data is found for the type and index */
	if (*ppmisc_data == NULL) {
		/* Misc data not found, invalid type or index */
		FCS_LOG_ERR("No misc data found\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	return FCSERR_OK;

failed:
	/* Something went wrong here */
	return res;
}


static int get_phone_id_by_index_type(uint16_t index,
		enum hwconf_phone_ID_t type,
		struct hwconf_phone_id **pp_phone_id,
		hwconf_handle_t handle)
{
	int res;
	uint32_t i = 0;
	struct hwconf_device_configuration *device_conf = NULL;
	struct hwconf_phone_id *phone_id = NULL;

	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;
	phone_id = device_conf->phone_id_array;

	*pp_phone_id = NULL;
	while (phone_id != NULL) {
		if (phone_id->id_type == type) {
			if (i == index) {
				/* phone id found */
				*pp_phone_id = phone_id;
				break;
			}

			/*Increase index counter */
			i++;
		}

		/* Proceed to next phone id */
		phone_id = phone_id->next;
	}

	/* Check if phone id is found for the type and index */
	if (*pp_phone_id == NULL) {
		/* Phone id not found, invalid type or index  */
		FCS_LOG_ERR("No phone id found\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	return FCSERR_OK;

failed:
	/* Something went wrong here */
	return res;
}

static int get_device_id_by_index(uint16_t index,
		struct hwconf_device_id **dev_id,
		hwconf_handle_t handle)
{
	struct hwconf_device_configuration *device_conf = NULL;
	struct hwconf_device_id *device_id = NULL;
	uint8_t ins_count = 0;

	/* Setup structures */
	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;
	device_id = device_conf->device_id_array;

	/* Reset the output */
	*dev_id = NULL;

	/* Find the device id instance */
	while (device_id != NULL) {
		/* Instance found */
		if (ins_count == index) {
			/* Set the output */
			*dev_id = device_id;
			break;
		}

		/* Proceed to next device id in list */
		device_id = device_id->next;
		ins_count++;
	}

	/* Check if device id found */
	if (*dev_id == NULL) {
		FCS_LOG_ERR("Device id not found\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect index or handle.*/
	return -FCSERR_EINVAL;
}


static int deinit_misc_data_array(struct hwconf_model_conf *model_conf)
{
	struct hwconf_misc_data *misc_data = NULL;
	struct hwconf_misc_data *next = NULL;

	/* Sanity checks */
	if (model_conf == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures, pointer to first element i array/list */
	misc_data = model_conf->misc_data_array;

	/* Free all data in array */
	while (misc_data != NULL) {
		/* Temporary save the next element in array */
		next = misc_data->next;

		/* Free all memory used by the current element */
		free(misc_data->data);
		free(misc_data);

		/* Proceed with next element */
		misc_data = next;
	}

	model_conf->misc_data_array = NULL;
	return FCSERR_OK;

failed:
	return -FCSERR_EINVAL;

}

static int deinit_model_conf_arrays(struct hwconf_model_conf *model_conf)
{
	int res;

	/* Sanity checks */
	if (model_conf == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	res = deinit_misc_data_array(model_conf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Deinit misc data array fail\n");
		goto failed;
	}

	return FCSERR_OK;

failed:
	return res;
}


static int deinit_phone_id_array(
		struct hwconf_device_configuration *device_conf)
{
	struct hwconf_phone_id *phone_id = NULL;
	struct hwconf_phone_id *next = NULL;

	/* Sanity checks */
	if (device_conf == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures, pointer to first element i array/list */
	phone_id = device_conf->phone_id_array;

	/* Free all data in array */
	while (phone_id != NULL) {
		/* Temporary save the next element in array */
		next = phone_id->next;

		/* Free all memory used by the current element */
		free(phone_id->id);
		free(phone_id);

		/* Proceed with next element */
		phone_id = next;
	}

	device_conf->phone_id_array = NULL;
	return FCSERR_OK;

failed:
	return -FCSERR_EINVAL;
}


static int deinit_sec_conf_part_id_array(
		struct  hwconf_security_configuration *sec_conf)
{

	struct hwconf_part_id *part_id = NULL;
	struct hwconf_part_id *next = NULL;

	/* Sanity checks */
	if (sec_conf == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures, pointer to first element i array/list */
	part_id = sec_conf->part_id_array;

	/* Free all data in array */
	while (part_id != NULL) {
		/* Temporary save the next element in array */
		next = part_id->next;

		/* Free all memory used by the current element */
		free(part_id->data);
		free(part_id);

		/* Proceed with next element */
		part_id = next;
	}

	sec_conf->part_id_array = NULL;
	return FCSERR_OK;

failed:
	return -FCSERR_EINVAL;
}


static int deinit_sec_conf_array(
		struct hwconf_device_configuration *device_conf)
{
	struct hwconf_security_configuration *sec_conf = NULL;
	struct hwconf_security_configuration *next = NULL;
	int res;

	/* Sanity checks */
	if (device_conf == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Setup structures, pointer to first element i array/list */
	sec_conf = device_conf->security_config_array;

	/* Free all data in array */
	while (sec_conf != NULL) {
		/* Temporary save the next element in array */
		next = sec_conf->next;

		/* Free all memory used by the current element */
		free(sec_conf->certificate_cn);

		if (sec_conf->part_id_array_length > 0) {
			res = deinit_sec_conf_part_id_array(
					sec_conf);
			if (res != FCSERR_OK) {
				FCS_LOG_ERR("Failed to deinit sec config\n");
				goto failed;
			}
		}

		free(sec_conf);

		/* Proceed with next element */
		sec_conf = next;
	}

	device_conf->security_config_array = NULL;
	return FCSERR_OK;

failed:
	return res;
}


static int deinit_dev_id_array(
		struct hwconf_device_configuration *device_conf)
{
	struct hwconf_device_id *device_id = NULL;
	struct hwconf_device_id *next = NULL;

	/* Sanity checks */
	if (device_conf == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures, pointer to first element i array/list */
	device_id = device_conf->device_id_array;

	/* Free all data in array */
	while (device_id != NULL) {
		/* Temporary save the next element in array */
		next = device_id->next;

		/* Free all memory used by the current element */
		free(device_id->id);
		free(device_id);

		/* Proceed with next element */
		device_id = next;
	}

	device_conf->device_id_array = NULL;
	return FCSERR_OK;

failed:
	return -FCSERR_EINVAL;
}

static int deinit_device_conf_arrays(
		struct hwconf_device_configuration *device_conf)
{
	int res;

	/* Sanity checks */
	if (device_conf == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Deinit all arrays*/
	res = deinit_phone_id_array(device_conf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Deinit phone id array fail\n");
		goto failed;
	}

	res = deinit_sec_conf_array(device_conf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Deinit security config array fail\n");
		goto failed;
	}

	res = deinit_dev_id_array(device_conf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Deinit device id array fail\n");
		goto failed;
	}

	/* Deinit hwc device key */
	free(device_conf->hwc_dk);
	device_conf->hwc_dk = NULL;

	return FCSERR_OK;

failed:
	return res;
}

/**
 *  @brief hwconf_copy_tag_contents() is a helper function to
 *  hwconf_get_tag_contents, that find and copy a tag-content and return the
 *  size of the tag content. If tag_contents==NULL, the function will return
 *  only the size. The NULL termination character is included i the resulting
 *  size value.
 *
 *  @param [in]   str           array containing the misc_data without a
 *                              null termination character.
 *  @param [in]   length        The length of str.
 *  @param [out]  tag_contents  The resulting tag content.
 *  @returns                    The length of the tag content, copied or not.
 */
static size_t hwconf_copy_tag_contents(char *str,
		uint8_t *tag_contents, uint16_t length)
{
	char *str_temp = NULL;
	size_t i = 0, j = 0;

	for (; i < length; i++, str++) {
		if (*str == '"') {
			str++;
			str_temp = str;

			for (j = 0; i < length; i++, j++, str_temp++) {
				if (*str_temp == '"') {
					if (NULL != tag_contents) {
						memcpy(tag_contents, str, j);
						tag_contents[j] = 0;
					}
					j++;
					goto exit;
				}
			}
			j = 0;
			goto exit;
		}
	}
exit:
	return j;
}

/**
 *  @brief hwconf_get_tag_contents() is used to locate a tag and retrieve the
 *  contents and/or the size of the tag content. If tag_contents==NULL, the
 *  function will return only the size.
 *
 *  @param [in]   str           array containing the misc_data without a
 *                              null termination character.
 *  @param [in]   tag_to_find   The tag to look for
 *  @param [in]   length        The length of misc_data.
 *  @param [out]  tag_contents  The resulting tag content.
 *  @returns                    The length of the tag content, copied or not.
 */
static size_t hwconf_get_tag_contents(char *str, char *tag_to_find,
		uint16_t length, uint8_t *tag_contents)
{
	char *tag_to_find_temp = tag_to_find, *str_temp = str;
	size_t i = 0, i_test = 0, j = 0;

	while (i < length) {
		if (*str_temp == *tag_to_find_temp) {
			i_test = i;
			while (i_test < length) {
				if (*str_temp == *tag_to_find_temp) {
					i_test++;
					str_temp++;
					tag_to_find_temp++;
				} else if ('\0' == *tag_to_find_temp) {
					j = hwconf_copy_tag_contents(str_temp,
							tag_contents,
							length - i_test);
					goto exit;
				} else {
					str_temp = &str[i];
					break;
				}
			}
		}
		i++;
		str_temp++;
	}
exit:
	return j;
}

/******************************************************************************
 *                Implementation of interface functions                       *
 ******************************************************************************/
int hwconf_parser_init(uint8_t *hwconf,
		uint32_t hwconf_size,
		hwconf_handle_t *phandle)
{
	struct hwconf_parse *parsed_hwconf = NULL;
	int res;

	/* Sanity checks */
	if (phandle == NULL || hwconf == NULL || hwconf_size == 0) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Allocate the hwconf parsing structure */
	parsed_hwconf = malloc(sizeof(struct hwconf_parse));
	if (parsed_hwconf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto failed;
	}

	/* Reset the parsing structure */
	memset(parsed_hwconf, 0, sizeof(struct hwconf_parse));

	/* Initialize the hwconf parsing structure */
	parsed_hwconf->hwconf_pos = hwconf;
	parsed_hwconf->hwconf_size = hwconf_size;

	/* Parse the hwconfig file */
	res = init_version(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init version fail\n");
		goto failed;
	}
	res = init_flags(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init flags fail\n");
		goto failed;
	}
	res = init_product_id(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init product id fail\n");
		goto failed;
	}
	res = init_misc_data_array(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init misc data fail\n");
		goto failed;
	}
	res = init_phone_id_array(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init phone id fail\n");
		goto failed;
	}
	res = init_global_sec_flags(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init global security flags fail\n");
		goto failed;
	}
	res = init_sec_config_length(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init security config length fail\n");
		goto failed;
	}
	res = init_sec_config_array(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init security config array fail\n");
		goto failed;
	}
	res = init_dev_id_total_length(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init device id length fail\n");
		goto failed;
	}
	res = init_dev_id_array(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init device id array fail\n");
		goto failed;
	}
	res = init_hwc_dk_length(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init dk length fail\n");
		goto failed;
	}
	res = init_hwc_dk_data(parsed_hwconf);
	if (res) {
		FCS_LOG_ERR("Init dk fail\n");
		goto failed;
	}
	*phandle = (void *)parsed_hwconf;
	return 0;

failed:
	if (parsed_hwconf)
		hwconf_parser_deinit(parsed_hwconf);

	return res;
}


int hwconf_parser_deinit(hwconf_handle_t handle)
{
	struct hwconf_data *hwconf = NULL;
	int res;

	/* Sanity checks */
	if (handle == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Setup structures */
	hwconf = &((struct hwconf_parse *)handle)->hwconf;

	/* Deinit model and device config arrays*/
	res = deinit_model_conf_arrays(&hwconf->modelConfig);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Deinit model config array fail\n");
		goto failed;
	}

	res = deinit_device_conf_arrays(&hwconf->deviceConfig);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Deinit device config array fail\n");
		goto failed;
	}

	/* Deinit the whole parsing structure */
	free(handle);

	return FCSERR_OK;

failed:
	/* Something went wrong during deinit */
	return res;
}

int hwconf_parser_get_version(uint16_t *version, hwconf_handle_t handle)
{
	struct hwconf_data *hwconf = NULL;

	/* Sanity checks */
	if (handle == NULL || version == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	hwconf = &((struct hwconf_parse *)handle)->hwconf;

	/* Set output to the caller */
	*version = hwconf->version;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect pointer
	   to version or handle. */
	return -FCSERR_EINVAL;
}

int hwconf_parser_get_misc_data_tag_length(
		uint8_t index,
		size_t *num_of_bytes,
		char *tag,
		enum hwconf_misc_data_type_t md_type,
		hwconf_handle_t handle)
{
	return hwconf_parser_get_misc_data_tag(NULL, index,  num_of_bytes, tag,
			md_type, handle);
}

int hwconf_parser_get_misc_data_tag(uint8_t *info,
		uint8_t index,
		size_t *num_of_bytes,
		char *tag,
		enum hwconf_misc_data_type_t md_type,
		hwconf_handle_t handle)
{
	int res = -FCSERR_EINVAL;
	uint16_t length = 0;
	uint8_t *local_info = NULL;

	/* Sanity checks */
	if (NULL == handle || NULL == num_of_bytes) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	res = hwconf_parser_get_misc_length(md_type, index, &length, handle);
	if (res == 0) {
		local_info = malloc(sizeof(uint8_t)*length);
		if (NULL == local_info) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto failed;
		}

		/* Read out the hwconfig misc data */
		res = hwconf_parser_get_misc_data(md_type,
				index,
				local_info,
				length,
				handle);
		if (res == 0) {
			/* Get the content of the tag */
			*num_of_bytes =
				hwconf_get_tag_contents((char *)local_info,
						tag,
						length,
						info);
			if (*num_of_bytes == 0) {
				FCS_LOG_ERR("Empty tag\n");
				res =  -FCSERR_EUNK;
			}
		} else {
			FCS_LOG_ERR("Failed to get misc data\n");
		}
	}
	free(local_info);
failed:
	return res;
}

int hwconf_parser_get_revision_data(uint8_t *revision,
		size_t *num_of_bytes,
		hwconf_handle_t handle)
{
	return hwconf_parser_get_misc_data_tag(revision, 0, num_of_bytes,
			"REV", INFO_DATA, handle);
}

int hwconf_parser_get_revision_length(size_t *num_of_bytes,
		hwconf_handle_t handle)
{
	return hwconf_parser_get_misc_data_tag_length(0, num_of_bytes,
			"REV", INFO_DATA, handle);
}

int hwconf_parser_get_flags(uint16_t *flags, hwconf_handle_t handle)
{
	struct hwconf_data *hwconf = NULL;

	/* Sanity checks */
	if (handle == NULL || flags == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	hwconf = &((struct hwconf_parse *)handle)->hwconf;

	/* Set output to the caller */
	*flags = hwconf->flags;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect pointer
	   to flags or handle. */
	return -FCSERR_EINVAL;
}


int hwconf_parser_get_product_ID(uint16_t *id, hwconf_handle_t handle)
{
	struct hwconf_data *hwconf = NULL;

	/* Sanity checks */
	if (handle == NULL || id == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	hwconf = &((struct hwconf_parse *)handle)->hwconf;

	/* Set output to the caller */
	*id = hwconf->modelConfig.product_id;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect pointer
	   to id or handle. */
	return -FCSERR_EINVAL;
}


int hwconf_parser_get_misc_type_nr_ins(enum hwconf_misc_data_type_t misc_type,
		uint8_t *nr_ins,
		hwconf_handle_t handle)
{
	struct hwconf_model_conf *model_conf = NULL;
	struct hwconf_misc_data *misc_data = NULL;
	uint8_t ins_count = 0;

	/* Sanity checks */
	if (handle == NULL || nr_ins == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	model_conf = &((struct hwconf_parse *)handle)->hwconf.modelConfig;
	misc_data = model_conf->misc_data_array;

	/* Find the number of instances for misc data type */
	while (misc_data != NULL) {
		if (misc_data->misc_data_type == misc_type) {
			/* Instance with the correct type found */
			ins_count++;
		}

		/* Proceed to next miscdata */
		misc_data = misc_data->next;
	}

	/* Set the output to the caller */
	*nr_ins = ins_count;

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect index, misc_type or handle. */
	return -FCSERR_EINVAL;
}


int hwconf_parser_get_misc_length(enum hwconf_misc_data_type_t misc_type,
		uint8_t index,
		uint16_t *length,
		hwconf_handle_t handle)
{
	struct hwconf_misc_data *misc_data = NULL;
	int res;

	/* Sanity checks */
	if (handle == NULL || length == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Get the misc data according to index and type */
	res = get_misc_data_by_index_type(index, misc_type, &misc_data, handle);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get misc data fail\n");
		goto failed;
	}

	/* Set the output */
	*length = misc_data->length;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect index or misc_type. */
	return -FCSERR_EINVAL;
}


int hwconf_parser_get_misc_data(enum hwconf_misc_data_type_t misc_type,
		uint8_t index,
		uint8_t *buffer,
		uint16_t buffer_size,
		hwconf_handle_t handle)
{
	struct hwconf_misc_data *misc_data = NULL;
	int res;

	/* Sanity checks */
	if (buffer == NULL || buffer_size == 0 || handle == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Get the misc data according to index and type */
	res = get_misc_data_by_index_type(index, misc_type, &misc_data, handle);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get misc data by index fail\n");
		goto failed;
	}

	/* Copy the misc data to output */
	memcpy(buffer, misc_data->data, buffer_size);

	return FCSERR_OK;

failed:
	/* Something went wrong here */
	return res;
}


int hwconf_parser_get_phone_id_nr_ins(enum hwconf_phone_ID_t id_type,
		uint8_t *nr_ins,
		hwconf_handle_t handle)
{

	struct hwconf_device_configuration *device_conf = NULL;
	struct hwconf_phone_id *phone_id = NULL;
	uint8_t ins_count = 0;

	/* Sanity checks */
	if (handle == NULL || nr_ins == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;
	phone_id = device_conf->phone_id_array;

	/* Find the number of instances for misc data type */
	while (phone_id != NULL) {
		if (phone_id->id_type == id_type) {
			/* Instance with the correct type found */
			ins_count++;
		}

		/* Proceed to next miscdata */
		phone_id = phone_id->next;
	}

	/* Set the output to the caller */
	*nr_ins = ins_count;

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect index, misc_type or handle. */
	return -FCSERR_EINVAL;
}


int hwconf_parser_get_phone_id_length(enum hwconf_phone_ID_t id_type,
		uint8_t index,
		uint16_t *length,
		hwconf_handle_t handle)
{
	struct hwconf_phone_id *phone_id = NULL;
	int res;

	/* Sanity checks */
	if (handle == NULL || length == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Get the misc data according to index and type */
	res = get_phone_id_by_index_type(index, id_type, &phone_id, handle);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get phone id by index fail\n");
		goto failed;
	}

	/* Set the output */
	*length = phone_id->length;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect index or misc_type. */
	return -FCSERR_EINVAL;
}


int hwconf_parser_get_phone_id(enum hwconf_phone_ID_t id_type,
		uint8_t index,
		uint8_t *buffer,
		uint8_t buffer_size,
		hwconf_handle_t handle)
{
	struct hwconf_device_configuration *device_conf = NULL;
	int res;
	struct hwconf_phone_id *phone_id;

	/* Sanity checks */
	if (buffer == NULL || buffer_size == 0 || handle == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;
	phone_id = device_conf->phone_id_array;

	/* Get the misc data according to index and type */
	res = get_phone_id_by_index_type(index, id_type, &phone_id, handle);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get phone id by index type fail\n");
		goto failed;
	}

	/* Set the output */
	memcpy(buffer, phone_id->id, buffer_size);

	return FCSERR_OK;

failed:
	/* Something went wrong here */
	return res;
}


int hwconf_parser_get_global_sec_flags(uint16_t *flags,
		hwconf_handle_t handle)
{
	struct hwconf_device_configuration *device_conf = NULL;

	/* Sanity checks */
	if (handle == NULL || flags == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;

	/* Set output to the caller */
	*flags = device_conf->global_security_flags;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect pointer
	   to flags or handle. */
	return -FCSERR_EINVAL;
}

int hwconf_parser_get_dev_id_nr_ins(uint8_t *nr_ins,
		hwconf_handle_t handle)
{

	struct hwconf_device_configuration *device_conf = NULL;
	struct hwconf_device_id *device_id = NULL;
	uint8_t ins_count = 0;

	/* Sanity checks */
	if (handle == NULL || nr_ins == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;
	device_id = device_conf->device_id_array;

	/* Find the number of instances for misc data type */
	while (device_id != NULL) {
		/* Instance found */
		ins_count++;

		/* Proceed to next miscdata */
		device_id = device_id->next;
	}

	/* Set the output to the caller */
	*nr_ins = ins_count;

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect index or handle. */
	return -FCSERR_EINVAL;
}

int hwconf_parser_get_dev_id_length(uint8_t index,
		uint16_t *length,
		hwconf_handle_t handle)
{
	struct hwconf_device_id *device_id = 0;
	int res;

	/* Sanity checks */
	if (handle == NULL || length == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Get the device id by index */
	res = get_device_id_by_index(index,
			&device_id,
			handle);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get device id by index fail\n");
		goto failed;
	}

	/* Set the output to the caller */
	*length = device_id->length;

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect index, length or handle. */
	return -FCSERR_EINVAL;
}

int hwconf_parser_get_dev_id(uint8_t index,
		uint8_t *buffer,
		uint8_t buffer_size,
		hwconf_handle_t handle)
{
	struct hwconf_device_id *device_id = 0;
	int res;

	/* Sanity checks */
	if (handle == NULL || buffer == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto failed;
	}

	/* Get the security config partition id by index */
	res = get_device_id_by_index(index,
			&device_id,
			handle);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get device id by index fail\n");
		goto failed;
	}


	/* Set the output */
	memcpy(buffer, device_id->id, buffer_size);

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect index, length or handle. */
	return res;
}


int hwconf_parser_get_hwc_dk_length(uint16_t *length, hwconf_handle_t handle)
{
	struct hwconf_device_configuration *device_conf = NULL;

	/* Sanity checks */
	if (handle == NULL || length == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;

	/* Set the output to the caller */
	*length = device_conf->hwc_dk_length;

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect length or handle. */
	return -FCSERR_EINVAL;
}


int hwconf_parser_get_hwc_dk(uint8_t *buffer,
		uint8_t buffer_size,
		hwconf_handle_t handle)
{
	struct hwconf_device_configuration *device_conf = NULL;

	/* Sanity checks */
	if (handle == NULL || buffer == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Setup structures */
	device_conf = &((struct hwconf_parse *)handle)->hwconf.deviceConfig;

	/* Set the output */
	memcpy(buffer, device_conf->hwc_dk, buffer_size);

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	   incorrect buffer, buffer_size or handle. */
	return -FCSERR_EINVAL;
}


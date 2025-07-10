/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "security_properties.h"
#include "handler_list.h"
#include "ta_interface.h"
#include "fcslist.h"
#include "fcserr.h"
#include "fcslog.h"

#define DEVICE_KEY_LENGTH (16)

/**
 * Declaration of types used internally
 */
typedef int (*secprop_it_worker)(struct list_entry *sec_prop_list,
		enum secprop_data_type prop,
		const uint8_t *data, uint32_t len);

/**
 * The internal structure for the handler_list,
 * do NOT access the variables inside directly please use the wrapper functions.
 */
struct {
	enum secprop_data_type id; /* The secprop id for this callback */
	secprop_func_ptr handler; /* The callback */
	struct list_entry list; /* list data */
} secprop_handler_list;

static uint16_t read_uint16(const uint8_t *data, uint32_t *index)
{
	uint16_t val = data[(*index)++] << 8;

	val |= data[(*index)++];
	return val;
}

static int find_secprop_handler(enum secprop_data_type id,
		struct list_entry *master_list, secprop_func_ptr *handler)
{
	struct handler_list *var_list;

	if (!master_list || !handler) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*handler = NULL;

	LIST_FOR_EACH_DATA(master_list, var_list, list)
	{
		if (var_list->data == (void *)id)
			*handler = (secprop_func_ptr)var_list->handler;
	}

	/* Check if handler is found */
	if (*handler == NULL)
		return -FCSERR_ENOTF;

	return FCSERR_OK;
}

/**
 * This function iterates through the security properties.
 * It means that the worker function will be called for
 * every property/type. The function also indirectly
 * checks that the security property format is ok.
 *
 * Detailed description of params:
 * data   - This is the pointer to the security
 *          property data.
 *          (points to Type in the sec prop file format)
 *
 * len    - The total length of all security properties
 *          (dataEntryList.length in the sec prop file format)
 *
 * worker - Pointer to function that will be invoked
 *          for every sec prop.
 *
 * state  - void pointer that will be passed on to the
 *          worker function.
 */
static int sec_prop_iterate(const uint8_t *data, uint32_t len,
		secprop_it_worker worker,
		struct list_entry *sec_prop_list)
{
	uint32_t i = 0;
	int res = -FCSERR_EINFOR;

	if (!data) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * Check that len - 3 below does not become negative, the calculation
	 * will then fail because len is unsigned.
	 */
	if (len < 3) {
		FCS_LOG_ERR("Invalid length %d\n", len);
		return -FCSERR_EINFOR;
	}

	while (i <= (len - 3)) {
		const enum secprop_data_type prop =
				(enum secprop_data_type) data[i++];
		const uint16_t prop_len = read_uint16(data, &i);

		/* Check that property length is sane */
		if (i + prop_len > len) {
			FCS_LOG_ERR(
				"%s: len %d prop %d, prop_len %d",
				__func__,
				(unsigned int) len,
				(unsigned int) prop,
				prop_len);
			return -FCSERR_EINFOR;
		}

		/* Now invoke the worker function. */
		res = worker(sec_prop_list, prop, data + i, prop_len);

		/*
		 * Fail in case of error that
		 * is not due to Indus rework flow.
		 */
		if ((res != FCSERR_OK) && (res != -FCSERR_EDONE)) {
			FCS_LOG_ERR("Error %d\n", res);
			return res;
		}

		i += prop_len;
	}

	/* Check that the security property format is ok. */
	if (i != len) {
		FCS_LOG_ERR("Invalid length %d %d\n", i, len);
		return -FCSERR_EINFOR;
	}

	return FCSERR_OK;
}

/**
 * This function will check that there is a handler
 * for a specific sec prop/type.
 *
 * Detailed description of params:
 *
 * sec_prop_list - The security property handler list
 *
 * prop          - This is the security type/property.
 *                 (Type in the sec prop file format)
 *
 * data          - This is the actual data for the property.
 *                 (data after the Data.length in the sec prop file format)
 *
 * len           - The length of the data.
 *                 (Data.length in the sec prop file format)
 */
int secprop_checker(struct list_entry *sec_prop_list,
		enum secprop_data_type prop, const uint8_t *data, uint32_t len)
{
	secprop_func_ptr handler;
	int res = -FCSERR_EINVAL;

	(void)(data); /* Unused parameter */
	(void)(len); /* Unused parameter */

	/* Find the appropriate handler for the property/type */
	res = find_secprop_handler(prop, sec_prop_list, &handler);
	if (res != FCSERR_OK)
		FCS_LOG("Handler not found (res %d) for prop:%d\n", res, prop);

	return res;
}

/**
 * This function will invoke the correct handler
 * for a specific sec prop/type.
 *
 * Detailed description of params:
 *
 * sec_prop_list - The security property handler list.
 *
 * prop          - This is the security type/property.
 *                 (Type in the sec prop file format)
 *
 * data          - This is the actual data for the property.
 *                 (data after the Data.length in the sec prop file format)
 *
 * len           - The length of the data.
 *                 (Data.length in the sec prop file format)
 *
 */
static int handler_dispatch(struct list_entry *sec_prop_list,
		enum secprop_data_type prop, const uint8_t *data, uint32_t len)
{
	secprop_func_ptr handler = NULL;
	int res = FCSERR_OK;

	FCS_LOG_INF("dispatching secprop %d", prop);

	/* Find the appropriate handler for the property/type */
	res = find_secprop_handler(prop, sec_prop_list, &handler);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Handler not found for prop: %d", res, prop);
		return res;
	}

	/* Invoke the handler */
	res = handler(data, len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Handler dispatch ERROR for prop: %d", res, prop);
		return res;
	}

	return res;
}

static int check_sec_prop(const uint8_t *data, uint32_t len,
		struct list_entry *sec_prop_list)
{
	return sec_prop_iterate(data, len, secprop_checker, sec_prop_list);
}

static int handle_sec_prop(const uint8_t *data, uint32_t len,
		struct list_entry *sec_prop_list)
{
	secprop_func_ptr handler;
	int res = sec_prop_iterate(data, len, handler_dispatch, sec_prop_list);

	if (res != FCSERR_OK)
		return res;

	/* The complete list is iterated, call final if available */
	if (find_secprop_handler(OTP_DATA_FINAL,
			sec_prop_list, &handler) == FCSERR_OK) {
		/* invoke final */
		res = handler(NULL, 0);
	}

	return res;
}

/**
 * This function handles the security properties.
 * It first checks that every security property/type
 * has a handler. Then this function calls the handler for
 * each security property.
 *
 * Detailed description of params:
 * data          - This is the pointer to the security
 *                 property data.
 *                 (points to EntryList.length in the sec prop file format)
 *
 * length        - The total length of security property
 *                 (dataEntryList.length + 2 in the sec prop file format)
 *
 * sec_prop_list - The security property handler list.
 */
int handle_security_properties(const uint8_t *data, uint32_t length,
		struct list_entry *sec_prop_list)
{
	int res = -FCSERR_EINVAL;
	uint32_t i = 0;
	uint16_t secprop_len = 0;


	if (length < 2) {
		FCS_LOG_ERR("Too few bytes");
		goto error;
	}

	secprop_len = read_uint16(data, &i);

	/* Check that data length of sec prop is correct */
	if (length != ((uint32_t)secprop_len + 2)) {
		FCS_LOG_ERR("handle_security_properties:");
		FCS_LOG_ERR("length: %d secprop_len: %d\n",
				(unsigned int) length, secprop_len);

		res = -FCSERR_EINFOR;
		goto error;
	}

	/* Check the sec prop data format and handlers */
	res = check_sec_prop(data + i, secprop_len, sec_prop_list);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("check_sec_prop() error", res);
		goto error;
	}

	/* Handle each security property */
	res = handle_sec_prop(data + i, secprop_len, sec_prop_list);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("handle_sec_prop() failed", res);
		goto error;
	}

error:
	return res;
}

int set_devicekey(uint8_t *data, uint16_t property_len)
{
	int res = FCSERR_OK;

	if (property_len != DEVICE_KEY_LENGTH)
		return -FCSERR_EINVAL;

	res = write_ta(TA_MISC_PART, TA_DK_NUMBER_UNIT,
			data, DEVICE_KEY_LENGTH);

	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to set device key", res);

	return res;
}

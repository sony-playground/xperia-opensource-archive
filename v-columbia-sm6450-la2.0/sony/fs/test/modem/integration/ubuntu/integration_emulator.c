/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "integration_emulator.h"
#include "integration_main.h"
#include "integration_core.h"
#include "integration_ta_interface.h"
#include "integration_eroot.h"
#include "fcserr.h"
#include "fcstest_defines.h"
#include "ta_interface.h"
#include "rule_types.h"
#include <malloc.h>
#include <string.h>

#define INTEMUL_TIMER_COUNT 4

struct intemul_data {
	struct iterator_info *it;
	bool is_fused;
	unsigned char *dev_id;
	unsigned int dev_id_len;
	unsigned char *hwconfig;
	unsigned int hwconfig_len;
	struct integration_context context;
	struct integration_core_context core_context;
	struct integration_ta_interface_context ta_interface_context;
	struct integration_eroot_context eroot_context;
};

static int set_property(
		unsigned char **property,
		unsigned int *property_len,
		const void *value,
		unsigned int value_len)
{
	free(*property);
	*property = malloc(value_len);
	if (*property == NULL)
		return -FCSERR_ENOMEM;
	memcpy(*property, value, value_len);
	*property_len = value_len;
	return FCSERR_OK;
}

static int intemul_set_property(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	struct intemul_data *data = NULL;

	if ((context == NULL) ||
			(value == NULL) ||
			(value_len == 0)) {
		return -FCSERR_EINVAL;
	}
	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					context);
	switch (id) {
	case INTG_PROP_FUSED:
		if (value_len != 1)
			return -FCSERR_EINVAL;
		if (((char *)value)[0] != 0)
			data->is_fused = true;
		else
			data->is_fused = false;
		break;
	case INTG_PROP_DEV_ID:
		return set_property(&data->dev_id, &data->dev_id_len,
						value, value_len);
	case INTG_PROP_HWCONFIG:
		return set_property(&data->hwconfig, &data->hwconfig_len,
						value, value_len);
	default:
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static int intemul_clear_property(
		struct integration_context *context,
		unsigned int id)
{
	if (context == NULL)
		return -FCSERR_EINVAL;

	return -FCSERR_EINVAL;
}

static int intemul_is_equal_property(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	if ((context == NULL) ||
			((value == NULL) && (value_len > 0)) ||
			((value != NULL) && (value_len == 0)))
		return -FCSERR_EINVAL;

	return -FCSERR_EINVAL;
}

static const struct integration_func intemul_func = {
	.set_property = intemul_set_property,
	.clear_property = intemul_clear_property,
	.is_equal_property = intemul_is_equal_property,
	.prepare_hwstate = NULL
};

static int intemul_is_fused(
		struct integration_core_context *context,
		bool *is_fused)
{
	struct intemul_data *data = NULL;

	if ((context == NULL) || (is_fused == NULL))
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					core_context);

	*is_fused = data->is_fused;
	return FCSERR_OK;
}

static int intemul_get_dieid(
		struct integration_core_context *context,
		unsigned char *buf, unsigned int len)
{
	struct intemul_data *data = NULL;

	if ((context == NULL) || (buf == NULL) || (len == 0))
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					core_context);

	if ((data->dev_id == NULL) || (data->dev_id_len == 0))
		return -FCSERR_ENOTF;

	if (data->dev_id_len != len)
		return -FCSERR_EINVAL;

	memcpy(buf, data->dev_id, data->dev_id_len);
	return FCSERR_OK;
}

static int intemul_get_dieid_len(
		struct integration_core_context *context)
{
	struct intemul_data *data = NULL;

	if (context == NULL)
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					core_context);

	if ((data->dev_id == NULL) || (data->dev_id_len == 0))
		return -FCSERR_ENOTF;

	return data->dev_id_len;
}

static int intemul_is_test_cert_allowed(
		struct integration_core_context *context)
{
	return 1;
}

static const struct integration_core_func intemul_core_func = {
	.is_fused = intemul_is_fused,
	.get_dieid = intemul_get_dieid,
	.get_dieid_len = intemul_get_dieid_len,
	.is_test_cert_allowed = intemul_is_test_cert_allowed,
};

static int intemul_init(
		struct integration_ta_interface_context *context)
{
	return FCSERR_OK;
}

static int intemul_read_unit(struct integration_ta_interface_context *context,
		uint8_t partition,
		uint32_t unit,
		uint8_t *buf,
		int buf_size)

{
	struct intemul_data *data = NULL;

	if (context == NULL || buf == NULL)
		return -FCSERR_EINVAL;

	if (partition != TA_MISC_PART)
		return -FCSERR_ENOTF;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					ta_interface_context);

	switch (unit) {
	case TA_HWCONFIG_UNIT:
		if (data->hwconfig == NULL)
			return -FCSERR_ENOTF;
		if (data->hwconfig_len > buf_size)
			return -FCSERR_EINVAL;
		memcpy(buf, data->hwconfig, data->hwconfig_len);
		break;
	default:
		return -FCSERR_ENOTF;
	}
	return FCSERR_OK;
}

static int intemul_get_unit_size(
		struct integration_ta_interface_context *context,
		uint8_t partition,
		uint32_t unit,
		int *unit_size)
{
	struct intemul_data *data = NULL;

	if (context == NULL || unit_size == NULL)
		return -FCSERR_EINVAL;

	if (partition != TA_MISC_PART)
		return -FCSERR_ENOTF;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					ta_interface_context);

	switch (unit) {
	case TA_HWCONFIG_UNIT:
		if (data->hwconfig == NULL)
			*unit_size = 0;
		else
			*unit_size = data->hwconfig_len;
		break;
	default:
		*unit_size = 0;
	}
	return FCSERR_OK;
}

static const struct integration_ta_interface_func
			intemul_ta_interface_func = {
	.init = intemul_init,
	.get_unit_size = intemul_get_unit_size,
	.read_unit = intemul_read_unit
};

int integration_emulator_setup(
		void (*log)(const char *fmt, ...),
		struct iterator_info *it)
{
	struct intemul_data *data = NULL;

	if (log == NULL || it == NULL)
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)malloc(
			sizeof(struct intemul_data));
	if (data == NULL)
		return -FCSERR_ENOMEM;

	memset(data, 0, sizeof(struct intemul_data));
	data->it = it;
	data->is_fused = true;
	data->dev_id = NULL;
	data->dev_id_len = 0;
	data->hwconfig = NULL;
	data->hwconfig_len = 0;
	data->context.functions = (struct integration_func *)&intemul_func;
	data->context.log = log;

	data->core_context.functions =
		(struct integration_core_func *)&intemul_core_func;
	data->ta_interface_context.functions =
		(struct integration_ta_interface_func *)
		&intemul_ta_interface_func;
	data->eroot_context.functions =
		(struct integration_eroot_func *)&intemul_eroot_func;

	g_integration_context_ptr = &(data->context);
	g_integration_core_context_ptr = &(data->core_context);
	g_integration_ta_interface_context_ptr =
		&(data->ta_interface_context);
	g_integration_eroot_context_ptr = &(data->eroot_context);


	integration_log("Integration is setup\n");

	return FCSERR_OK;
}

void integration_emulator_teardown(void)
{
	struct intemul_data *data = NULL;

	if (g_integration_context_ptr != NULL) {
		data = (struct intemul_data *)
			fcstest_container_of(g_integration_context_ptr,
					struct intemul_data,
					context);

		free(data->dev_id);
		free(data->hwconfig);
		free(data);
	}
	g_integration_context_ptr = NULL;
	g_integration_core_context_ptr = NULL;
	g_integration_ta_interface_context_ptr = NULL;
	g_integration_eroot_context_ptr = NULL;
}


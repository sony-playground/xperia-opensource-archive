/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "security_properties.h"
#include "handler_list.h"
#include "fcserr.h"

static int dummy_handler(const uint8_t *data, uint16_t len)
{
	return FCSERR_OK;
}

static int dummy_handler_err(const uint8_t *data, uint16_t len)
{
	return -FCSERR_EFORMAT;
}

static struct list_entry *setup_handlers(uint8_t cfg)
{
	struct list_entry *handlers;
	void *handler;

	if (cfg & 0x10)
		return NULL;

	handlers = handler_list_init();

	if (cfg & 0x1) {
		handler = (cfg & 0x2) ? dummy_handler : dummy_handler_err;
		handler_list_add_handler(handlers, handler, (void *) 0);
	}

	if (cfg & 0x4) {
		handler = (cfg & 0x8) ? dummy_handler : dummy_handler_err;
		handler_list_add_handler(handlers, handler,
					(void *) OTP_DATA_FINAL);
	}

	return handlers;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	if (Size >= 1) {
		struct list_entry *handlers = setup_handlers(Data[0]);

		handle_security_properties(Data + 1, Size - 1, handlers);

		handler_list_destroy(handlers);
	}

	return 0;
}

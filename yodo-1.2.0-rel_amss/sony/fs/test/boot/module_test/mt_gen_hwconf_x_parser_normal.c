#include "iterator.h"
#include "integration_main.h"
#include "hwconf_x_parser.h"
#include <string.h>

#define CHECKPATCH_FALSE false

/* Test 1:
 * Version: 1
 * IsPrototype: TRUE
 * IMEI 1: 00461234567890
 * DK: Random 16 byte
 */
static const uint8_t hwconf_payload1[44] = {
	0x30, 0x2a, 0x02, 0x01, 0x01, 0x01, 0x01, 0xff,
	0x30, 0x10, 0x0c, 0x0e, 0x30, 0x30, 0x34, 0x36,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x30, 0x04, 0x10, 0xbe, 0x7f, 0x63, 0x0e,
	0xd5, 0xc5, 0x56, 0xb7, 0xb2, 0x9b, 0xff, 0x29,
	0xee, 0x51, 0x62, 0xb4
};
static const int version1 = 1;
static const bool is_prototype1 = true;
static const uint8_t imei1_1[8] = {
	0x00, 0x46, 0x12, 0x34, 0x56, 0x78, 0x90, 0x00
};
static const uint8_t dk1[16] = {
	0xbe, 0x7f, 0x63, 0x0e, 0xd5, 0xc5, 0x56, 0xb7,
	0xb2, 0x9b, 0xff, 0x29, 0xee, 0x51, 0x62, 0xb4
};

/* Test 2:
 * Version: 1
 * IsPrototype: FALSE
 * IMEI 1: 00461234567891
 * IMEI 2: 00461234567892
 * DK: Random 16 byte
 */
static const uint8_t hwconf_payload2[60] = {
	0x30, 0x3A, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00,
	0x30, 0x20, 0x0C, 0x0E, 0x30, 0x30, 0x34, 0x36,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x31, 0x0C, 0x0E, 0x30, 0x30, 0x34, 0x36,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x32, 0x04, 0x10, 0xCE, 0x7F, 0x63, 0x0E,
	0xD5, 0xC5, 0x56, 0xB7, 0xB2, 0x9B, 0xFF, 0x29,
	0xEE, 0x51, 0x62, 0xB8
};
static const int version2 = 1;
static const bool is_prototype2 = CHECKPATCH_FALSE;
static const uint8_t imei2_1[8] = {
	0x00, 0x46, 0x12, 0x34, 0x56, 0x78, 0x91, 0x00
};
static const uint8_t imei2_2[8] = {
	0x00, 0x46, 0x12, 0x34, 0x56, 0x78, 0x92, 0x00
};
static const uint8_t dk2[16] = {
	0xce, 0x7f, 0x63, 0x0e, 0xd5, 0xc5, 0x56, 0xb7,
	0xb2, 0x9b, 0xff, 0x29, 0xee, 0x51, 0x62, 0xb8
};

static int module_verify_valid_payload(
		fcsmt_log_t log,
		const uint8_t *payload,
		size_t payload_size,
		int expected_version,
		bool expected_is_prototype,
		const uint8_t *expected_imei1,
		size_t expected_imei1_len,
		const uint8_t *expected_imei2,
		size_t expected_imei2_len,
		const uint8_t *expected_dk,
		size_t expected_dk_len)
{
	int res = FCSERR_OK;
	hwconf_x_handle_t handle = NULL;

	int version = 0;
	bool is_prototype = false;
	uint8_t *buffer = NULL;
	size_t buffer_size = 0;

	res = hwconf_x_parser_init(&handle,
			(uint8_t *)payload,
			payload_size);
	if (res != FCSERR_OK) {
		log("hwconf_parser_init failed\n");
		goto exit;
	}

	res = hwconf_x_parser_get_version(handle, &version);
	if (res != FCSERR_OK) {
		log("hwconf_parser_get_version failed\n");
		goto exit;
	}
	if (version != expected_version) {
		log("Unexpected version\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = hwconf_x_parser_get_isprototype(handle, &is_prototype);
	if (res != FCSERR_OK) {
		log("hwconf_parser_get_isprototype payloadl1 failed\n");
		goto exit;
	}
	if (is_prototype != expected_is_prototype) {
		log("Unexpected is_prototype\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = hwconf_x_parser_get_imei(handle, 0, &buffer, &buffer_size);
	if (res != FCSERR_OK) {
		log("hwconf_parser_get_imei 1 failed\n");
		goto exit;
	}
	if ((buffer_size != expected_imei1_len) ||
		(memcmp(expected_imei1, buffer, buffer_size) != 0)) {
		log("Unexpected imei 1\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	if (expected_imei2 != NULL && expected_imei2_len > 0) {
		res = hwconf_x_parser_get_imei(
				handle, 1, &buffer, &buffer_size);
		if (res != FCSERR_OK) {
			log("hwconf_parser_get_imei 2 failed\n");
			goto exit;
		}
		if ((buffer_size != expected_imei2_len) ||
			(memcmp(expected_imei2,
				buffer, buffer_size) != 0)) {
			log("Unexpected imei 2\n");
			res = -FCSERR_EINVAL;
			goto exit;
		}
	}
	res = hwconf_x_parser_get_hwc_dk(handle, &buffer, &buffer_size);
	if (res != FCSERR_OK) {
		log("hwconf_parser_get_hwc_dk failed\n");
		goto exit;
	}
	if ((buffer_size != expected_dk_len) ||
		(memcmp(expected_dk, buffer, buffer_size) != 0)) {
		log("Unexpected dk\n");
		res = -FCSERR_EINVAL;
	}

exit:
	hwconf_x_parser_deinit(handle);
	return res;
}

int execute_module_gen_hwconf_x_parser_normal(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match)
{
	int res = FCSERR_OK;

	switch (it->cur_module_item) {
	case 0:
		/* If unexpected shutdown goto 2 */
		set_next_module_item(it, 1);
		export_tcstate(it);


		/* Test 1:
		 * Version: 1
		 * IsPrototype: TRUE
		 * IMEI 1: 00461234567890
		 * DK: Random 16 byte
		 */
		res = module_verify_valid_payload(
			log,
			hwconf_payload1, sizeof(hwconf_payload1),
			version1,
			is_prototype1,
			imei1_1, sizeof(imei1_1),
			NULL, 0,
			dk1, sizeof(dk1));
		if (res != FCSERR_OK) {
			log("Verify 1 failed\n");
			goto test_failure;
		}

		/* Test 2:
		 * Version: 1
		 * IsPrototype: FALSE
		 * IMEI 1: 00461234567891
		 * IMEI 2: 00461234567892
		 * DK: Random 16 byte
		 */
		res = module_verify_valid_payload(
			log,
			hwconf_payload2, sizeof(hwconf_payload2),
			version2,
			is_prototype2,
			imei2_1, sizeof(imei2_1),
			imei2_2, sizeof(imei2_2),
			dk2, sizeof(dk2));
		if (res != FCSERR_OK) {
			log("Verify 2 failed\n");
			goto test_failure;
		}

		/* We got through the test, goto next test */
		inc_n_executed(it);
		set_next_module_item(it, -1);
		break;
	default:
		/* Unexpected shutdown/restart */
		goto test_failure;
	}

	return FCSERR_OK;

test_failure:
	set_next_module_item(it, -1);
	inc_n_failed(it);
	inc_n_executed(it);
	return FCSERR_OK;
}



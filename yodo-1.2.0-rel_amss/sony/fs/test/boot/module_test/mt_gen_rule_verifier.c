#include "iterator.h"
#include "integration_main.h"
#include "rule_verifier.h"
#include "rule_verifier_intern.h"
#include <string.h>

/* Object identifier for SOMC Attribute
 * id-signatureUsage in doc/requirements/keyusage.asn
 */
static const uint8_t attribute_oid[] = {
	0x06, 0x0B, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82,
	0xFB, 0x15, 0x01, 0x02, 0x03
};

/* Object identifier for SOMC Extension
 * id-ce-keyUsage in doc/requirements/keyusage.asn
 */
static const uint8_t extension_oid_keyusage[] = {
	0x06, 0x0B, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82,
	0xFB, 0x15, 0x01, 0x01, 0x01
};

/* Object identifier for SOMC Extension
 * id-ce-deviceBinding in doc/requirements/keyusage.asn
 */
static const uint8_t extension_oid_binding[] = {
	0x06, 0x0B, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82,
	0xFB, 0x15, 0x01, 0x01, 0x02
};

/* Test 1:
 * Bind to correct DevID (Device: 0xFCABADF6)
 * Attr: Purpose:HwConfig, Binding:DevID=0xFCABADF6
 * Cert: Purpose:HwConfig
 */
static const uint8_t devid_test1[] = {
	0xFC, 0xAB, 0xAD, 0xF6
};
static const uint32_t usage_test1 = RULE_USAGE_HWCONFIG;
static const uint8_t attribute_test1[] = {
	0x30, 0x0B, 0xA1, 0x03, 0x0A, 0x01, 0x01, 0x04,
	0x04, 0xFC, 0xAB, 0xAD, 0xF6
};
static const uint8_t extension_keyusage_test1[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x01
};
static const int ref_res_test1 = FCSERR_OK;

/* Test 2:
 * Bind to wrong DevID (Device: 0xFCABADF7)
 * Attr: Purpose:HwConfig, Wrong Binding:DevID=0xFCABADF6
 * Cert: Purpose:HwConfig
 */
static const uint8_t devid_test2[] = {
	0xFC, 0xAB, 0xAD, 0xF7
};
static const uint32_t usage_test2 = RULE_USAGE_HWCONFIG;
static const uint8_t attribute_test2[] = {
	0x30, 0x0B, 0xA1, 0x03, 0x0A, 0x01, 0x01, 0x04,
	0x04, 0xFC, 0xAB, 0xAD, 0xF6
};
static const uint8_t extension_keyusage_test2[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x01
};
static const int ref_res_test2 = -FCSERR_EBINDER;

/* Test 3:
 * Bind to first DevID (Device: 0xFCABADF6)
 * Attr: Purpose:HwConfig, Binding:DevID=0xFCABADF6,0x7CABADF6
 * Cert: Purpose:HwConfig
 */
static const uint8_t devid_test3[] = {
	0xFC, 0xAB, 0xAD, 0xF6
};
static const uint32_t usage_test3 = RULE_USAGE_HWCONFIG;
static const uint8_t attribute_test3[] = {
	0x30, 0x13, 0xA1, 0x03, 0x0A, 0x01, 0x01, 0x30,
	0x0C, 0x04, 0x04, 0xFC, 0xAB, 0xAD, 0xF6, 0x04,
	0x04, 0x7C, 0xAB, 0xAD, 0xF6
};
static const uint8_t extension_keyusage_test3[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x01
};
static const int ref_res_test3 = FCSERR_OK;

/* Test 4:
 * Bind to second DevID (Device: 0x7CABADF6)
 * Attr: Purpose:HwConfig, Binding:DevID=0xFCABADF6,0x7CABADF6
 * Cert: Purpose:HwConfig
 */
static const uint8_t devid_test4[] = {
	0x7C, 0xAB, 0xAD, 0xF6
};
static const uint32_t usage_test4 = RULE_USAGE_HWCONFIG;
static const uint8_t attribute_test4[] = {
	0x30, 0x13, 0xA1, 0x03, 0x0A, 0x01, 0x01, 0x30,
	0x0C, 0x04, 0x04, 0xFC, 0xAB, 0xAD, 0xF6, 0x04,
	0x04, 0x7C, 0xAB, 0xAD, 0xF6
};
static const uint8_t extension_keyusage_test4[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x01
};
static const int ref_res_test4 = FCSERR_OK;

/* Test 5:
 * Bind to no DevID in list (Device: 0xFCABADF7)
 * Attr: Purpose:HwConfig, Binding:DevID=0xFCABADF6,0x7CABADF6
 * Cert: Purpose:HwConfig
 */
static const uint8_t devid_test5[] = {
	0xFC, 0xAB, 0xAD, 0xF7
};
static const uint32_t usage_test5 = RULE_USAGE_HWCONFIG;
static const uint8_t attribute_test5[] = {
	0x30, 0x13, 0xA1, 0x03, 0x0A, 0x01, 0x01, 0x30,
	0x0C, 0x04, 0x04, 0xFC, 0xAB, 0xAD, 0xF6, 0x04,
	0x04, 0x7C, 0xAB, 0xAD, 0xF6
};
static const uint8_t extension_keyusage_test5[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x01
};
static const int ref_res_test5 = -FCSERR_EBINDER;

/* Test 6:
 * Bind to IMEI (Device: 00440245851024)
 * Attr: Purpose:Simlock, Binding:IMEI=00440245851024
 * Cert: Purpose:Simlock
 */
static const uint8_t imei_test6[] = {
	0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34, 0x35,
	0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint32_t usage_test6 = RULE_USAGE_SIMLOCK;
static const uint8_t attribute_test6[] = {
	0x30, 0x15, 0xA1, 0x03, 0x0A, 0x01, 0x00, 0x0C,
	0x0E, 0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34,
	0x35, 0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint8_t extension_keyusage_test6[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x00
};
static const int ref_res_test6 = FCSERR_OK;

/* Test 7:
 * Bind to wrong IMEI (Device: 00440245851024)
 * Attr: Purpose:Simlock, Binding:IMEI=00440245851025
 * Cert: Purpose:Simlock
 */
static const uint8_t imei_test7[] = {
	0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34, 0x35,
	0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint32_t usage_test7 = RULE_USAGE_SIMLOCK;
static const uint8_t attribute_test7[] = {
	0x30, 0x15, 0xA1, 0x03, 0x0A, 0x01, 0x00, 0x0C,
	0x0E, 0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34,
	0x35, 0x38, 0x35, 0x31, 0x30, 0x32, 0x35
};
static const uint8_t extension_keyusage_test7[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x00
};
static const int ref_res_test7 = -FCSERR_EBINDER;

/* Test 8:
 * Bind to IMEI (Device: 00440245851024)
 * Expected OPID=264
 * Attr: Purpose:Simlock, Binding:IMEI=00440245851024
 * Cert: Purpose:Simlock, OPID=0x0108
 */
static const uint8_t imei_test8[] = {
	0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34, 0x35,
	0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint32_t usage_test8 = RULE_USAGE_SIMLOCK;
static const uint32_t opid_test8 = 264;
static const uint8_t attribute_test8[] = {
	0x30, 0x15, 0xA1, 0x03, 0x0A, 0x01, 0x00, 0x0C,
	0x0E, 0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34,
	0x35, 0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint8_t extension_keyusage_test8[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x00
};
static const uint8_t orgunit_test8[] = {
	0x32, 0x31, 0x20, 0x30, 0x31, 0x30, 0x38, 0x20,
	0x4F, 0x50, 0x49, 0x44
};
static const int ref_res_test8 = FCSERR_OK;

/* Test 9:
 * Bind to IMEI (Device: 00440245851024)
 * Unexpected OPID=None
 * Attr: Purpose:Simlock, Binding:IMEI=00440245851024
 * Cert: Purpose:Simlock, OPID=0x0108
 */
static const uint8_t imei_test9[] = {
	0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34, 0x35,
	0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint32_t usage_test9 = RULE_USAGE_SIMLOCK;
static const uint8_t attribute_test9[] = {
	0x30, 0x15, 0xA1, 0x03, 0x0A, 0x01, 0x00, 0x0C,
	0x0E, 0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34,
	0x35, 0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint8_t extension_keyusage_test9[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x00
};
static const uint8_t orgunit_test9[] = {
	0x32, 0x31, 0x20, 0x30, 0x31, 0x30, 0x38, 0x20,
	0x4F, 0x50, 0x49, 0x44
};
static const int ref_res_test9 = -FCSERR_EOPID;

/* Test 10:
 * Bind to IMEI (Device: 00440245851024)
 * Unexpected OPID=263
 * Attr: Purpose:Simlock, Binding:IMEI=00440245851024
 * Cert: Purpose:Simlock, OPID=0x0108
 */
static const uint8_t imei_test10[] = {
	0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34, 0x35,
	0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint32_t usage_test10 = RULE_USAGE_SIMLOCK;
static const uint32_t opid_test10 = 263;
static const uint8_t attribute_test10[] = {
	0x30, 0x15, 0xA1, 0x03, 0x0A, 0x01, 0x00, 0x0C,
	0x0E, 0x30, 0x30, 0x34, 0x34, 0x30, 0x32, 0x34,
	0x35, 0x38, 0x35, 0x31, 0x30, 0x32, 0x34
};
static const uint8_t extension_keyusage_test10[] = {
	0x30, 0x05, 0xA1, 0x03, 0x0A, 0x01, 0x00
};
static const uint8_t orgunit_test10[] = {
	0x32, 0x31, 0x20, 0x30, 0x31, 0x30, 0x38, 0x20,
	0x4F, 0x50, 0x49, 0x44
};
static const int ref_res_test10 = -FCSERR_EOPID;

/* Test 11:
 * Cert bind to wrong DevID (Device: 0xFCABADF7)
 * Attr: Purpose:Flash oem_b
 * Cert: Purpose:None, Binding:DevID=0x00000000000000000000000000000000
 */
static const uint8_t devid_test11[] = {
	0xFC, 0xAB, 0xAD, 0xF7
};
static const uint32_t usage_test11 = RULE_USAGE_FLASH;
static const uint8_t attribute_test11[] = {
	0x30, 0x07, 0x0C, 0x05, 0x6F, 0x65, 0x6D, 0x5F, 0x62
};
static const uint8_t extension_binding_test11[] = {
	0x30, 0x12, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};
static const int ref_res_test11 = -FCSERR_EBINDER;

/* Test 12:
 * Cert bind to correct DevID (Device: 0xFCABADF7)
 * Attr: Purpose:Flash oem_b
 * Cert: Purpose:None, Binding:DevID=0xFCABADF7
 */
static const uint8_t devid_test12[] = {
	0xFC, 0xAB, 0xAD, 0xF7
};
static const uint32_t usage_test12 = RULE_USAGE_FLASH;
static const uint8_t attribute_test12[] = {
	0x30, 0x07, 0x0C, 0x05, 0x6F, 0x65, 0x6D, 0x5F, 0x62
};
static const uint8_t extension_binding_test12[] = {
	0x30, 0x06, 0x04, 0x04, 0xFC, 0xAB, 0xAD, 0xF7
};
static const int ref_res_test12 = FCSERR_OK;


static int test_rule_verifier(
		fcsmt_log_t log,
		const uint8_t *devid, size_t devid_len,
		const uint8_t *imei, size_t imei_len,
		const uint8_t *devid_hmac, size_t devid_hmac_len,
		const uint8_t *imei_hmac, size_t imei_hmac_len,
		uint32_t init_usage,
		uint32_t *opid,
		const uint8_t *attribute, size_t attribute_len,
		const uint8_t *extension_keyusage,
		size_t extension_keyusage_len,
		const uint8_t *extension_binding,
		size_t extension_binding_len,
		const uint8_t *orgunit, size_t orgunit_len,
		uint32_t ref_actual_usage,
		char *ref_param,
		uint32_t *ref_sequence,
		uint32_t *ref_verified_with_hmac,
		int *ref_sl_range_start,
		int *ref_sl_range_len,
		int ref_res)
{
	int res = FCSERR_OK;
	int test_res = 0;
	struct rule_verifier *rule_handle = NULL;
	struct dev_binding binding = {};
	uint32_t actual_usage = 0;
	char *actual_param = NULL;
	uint32_t sequence = 0;
	uint32_t verified_with_hmac = 0;
	int sl_range_start = 0;
	int sl_range_len = 0;
	struct rule_attribute attribute_rec = {
		.oid = attribute_oid,
		.oid_len = sizeof(attribute_oid),
		.asn1_buffer = attribute,
		.asn1_buffer_len = attribute_len
	};
	struct rule_extension extension_keyusage_rec = {
		.cert_level = 0,
		.oid = extension_oid_keyusage,
		.oid_len = sizeof(extension_oid_keyusage),
		.asn1_buffer = extension_keyusage,
		.asn1_buffer_len = extension_keyusage_len
	};
	struct rule_extension extension_binding_rec = {
		.cert_level = 0,
		.oid = extension_oid_binding,
		.oid_len = sizeof(extension_oid_binding),
		.asn1_buffer = extension_binding,
		.asn1_buffer_len = extension_binding_len
	};
	struct rule_ou orgunit_rec = {
		.cert_level = 0,
		.ou = orgunit,
		.ou_len = orgunit_len
	};

	if (devid != NULL) {
		binding.die_id = (uint8_t *)devid;
		binding.die_id_sz = devid_len;
	}
	if (imei != NULL) {
		binding.imei = (uint8_t *)imei;
		binding.imei_sz = imei_len;
	}
	if (devid_hmac != NULL) {
		binding.die_id_hmac = (uint8_t *)devid_hmac;
		binding.die_id_hmac_sz = devid_hmac_len;
	}
	if (imei_hmac != NULL) {
		binding.imei_hmac = (uint8_t *)imei_hmac;
		binding.imei_hmac_sz = imei_hmac_len;
	}

	res = rule_init(&rule_handle, &binding, init_usage);
	if (res != FCSERR_OK) {
		log("Failed to init rule session\n");
		goto endfunction;
	}

	if (opid != NULL) {
		res = rule_set_opid(rule_handle, *opid);
		if (res != FCSERR_OK) {
			log("Failed to set opid\n");
			goto endfunction;
		}
	}

	if (attribute != NULL) {
		res = rule_update_unhandled_attributes(
			rule_handle, &attribute_rec);
		if (res != FCSERR_OK) {
			log("Failed to handle attribute\n");
			goto endfunction;
		}
	}

	if (extension_keyusage != NULL) {
		res = rule_update_unhandled_extensions(
			rule_handle, &extension_keyusage_rec);
		if (res != FCSERR_OK) {
			log("Failed to handle extension keyusage\n");
			goto endfunction;
		}
	}

	if (extension_binding != NULL) {
		res = rule_update_unhandled_extensions(
			rule_handle, &extension_binding_rec);
		if (res != FCSERR_OK) {
			log("Failed to handle extension binding\n");
			goto endfunction;
		}
	}

	if (orgunit != NULL) {
		res = rule_update_subject_ou(
			rule_handle, &orgunit_rec);
		if (res != FCSERR_OK) {
			log("Failed to handle ou\n");
			goto endfunction;
		}
	}

	res = rule_final(rule_handle);
	if (res != FCSERR_OK) {
		log("Failed to finalize rule session\n");
		goto endfunction;
	}

	res = rule_get_actual_usage(rule_handle,
			&actual_usage,
			&actual_param);
	if (res != FCSERR_OK) {
		log("Failed to get actual usage\n");
		goto endfunction;
	}

	if (actual_usage != ref_actual_usage) {
		log("Unexpected actual usage\n");
		test_res = 1;
		goto endfunction;
	}

	if (ref_param != NULL) {
		if (actual_param == NULL ||
			strncmp(ref_param, actual_param, strlen(ref_param))) {
			log("Unexpected actual usage\n");
			test_res = 1;
			goto endfunction;
		}
	}

	if (ref_sequence != NULL) {
		res = rule_get_sequence(rule_handle, &sequence);
		if (res != FCSERR_OK) {
			log("Failed to get sequence\n");
			goto endfunction;
		}
		if (*ref_sequence != sequence) {
			log("Unexpected sequence\n");
			test_res = 1;
			goto endfunction;
		}
	}

	if (ref_verified_with_hmac != NULL) {
		res = rule_verified_with_hmac(rule_handle, &verified_with_hmac);
		if (res != FCSERR_OK) {
			log("rule_verified_with_hmac failed\n");
			goto endfunction;
		}
		if (*ref_verified_with_hmac != verified_with_hmac) {
			log("Unexpected verified_with_hmac\n");
			test_res = 1;
			goto endfunction;
		}
	}

	if (ref_sl_range_start != NULL && ref_sl_range_len != NULL) {
		res = rule_get_simlock_range(rule_handle,
					&sl_range_start,
					&sl_range_len);
		if (res != FCSERR_OK) {
			log("rule_get_simlock_range failed\n");
			goto endfunction;
		}
		if (*ref_sl_range_start != sl_range_start ||
				*ref_sl_range_len != sl_range_len) {
			log("Unexpected simlock range\n");
			test_res = 1;
			goto endfunction;
		}
	}

endfunction:
	rule_deinit(rule_handle);
	if (!test_res && (res != ref_res)) {
		log("Unexpected ret code %d\n", res);
		test_res = 1;
	}
	return test_res;
}

int execute_module_gen_rule_verifier(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match)
{
	switch (it->cur_module_item) {
	case 0:
		/* If unexpected shutdown goto 2 */
		set_next_module_item(it, 1);
		export_tcstate(it);


		/*
		 * Test 1:
		 */
		if (test_rule_verifier(
				log,
				devid_test1, sizeof(devid_test1),
				NULL, 0,
				NULL, 0,
				NULL, 0,
				usage_test1,
				NULL,
				attribute_test1, sizeof(attribute_test1),
				extension_keyusage_test1,
				sizeof(extension_keyusage_test1),
				NULL, 0,
				NULL, 0,
				usage_test1,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test1)) {
			log("Test 1 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 2:
		 */
		if (test_rule_verifier(
				log,
				devid_test2, sizeof(devid_test2),
				NULL, 0,
				NULL, 0,
				NULL, 0,
				usage_test2,
				NULL,
				attribute_test2, sizeof(attribute_test2),
				extension_keyusage_test2,
				sizeof(extension_keyusage_test2),
				NULL, 0,
				NULL, 0,
				usage_test2,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test2)) {
			log("Test 2 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 3:
		 */
		if (test_rule_verifier(
				log,
				devid_test3, sizeof(devid_test3),
				NULL, 0,
				NULL, 0,
				NULL, 0,
				usage_test3,
				NULL,
				attribute_test3, sizeof(attribute_test3),
				extension_keyusage_test3,
				sizeof(extension_keyusage_test3),
				NULL, 0,
				NULL, 0,
				usage_test3,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test3)) {
			log("Test 3 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 4:
		 */
		if (test_rule_verifier(
				log,
				devid_test4, sizeof(devid_test4),
				NULL, 0,
				NULL, 0,
				NULL, 0,
				usage_test4,
				NULL,
				attribute_test4, sizeof(attribute_test4),
				extension_keyusage_test4,
				sizeof(extension_keyusage_test4),
				NULL, 0,
				NULL, 0,
				usage_test4,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test4)) {
			log("Test 4 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 5:
		 */
		if (test_rule_verifier(
				log,
				devid_test5, sizeof(devid_test5),
				NULL, 0,
				NULL, 0,
				NULL, 0,
				usage_test5,
				NULL,
				attribute_test5, sizeof(attribute_test5),
				extension_keyusage_test5,
				sizeof(extension_keyusage_test5),
				NULL, 0,
				NULL, 0,
				usage_test5,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test5)) {
			log("Test 5 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 6:
		 */
		if (test_rule_verifier(
				log,
				NULL, 0,
				imei_test6, sizeof(imei_test6),
				NULL, 0,
				NULL, 0,
				usage_test6,
				NULL,
				attribute_test6, sizeof(attribute_test6),
				extension_keyusage_test6,
				sizeof(extension_keyusage_test6),
				NULL, 0,
				NULL, 0,
				usage_test6,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test6)) {
			log("Test 6 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 7:
		 */
		if (test_rule_verifier(
				log,
				NULL, 0,
				imei_test7, sizeof(imei_test7),
				NULL, 0,
				NULL, 0,
				usage_test7,
				NULL,
				attribute_test7, sizeof(attribute_test7),
				extension_keyusage_test7,
				sizeof(extension_keyusage_test7),
				NULL, 0,
				NULL, 0,
				usage_test7,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test7)) {
			log("Test 7 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 8:
		 */
		if (test_rule_verifier(
				log,
				NULL, 0,
				imei_test8, sizeof(imei_test8),
				NULL, 0,
				NULL, 0,
				usage_test8,
				(uint32_t *)&opid_test8,
				attribute_test8, sizeof(attribute_test8),
				extension_keyusage_test8,
				sizeof(extension_keyusage_test8),
				NULL, 0,
				orgunit_test8, sizeof(orgunit_test8),
				usage_test8,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test8)) {
			log("Test 8 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 9:
		 */
		if (test_rule_verifier(
				log,
				NULL, 0,
				imei_test9, sizeof(imei_test9),
				NULL, 0,
				NULL, 0,
				usage_test9,
				NULL,
				attribute_test9, sizeof(attribute_test9),
				extension_keyusage_test9,
				sizeof(extension_keyusage_test9),
				NULL, 0,
				orgunit_test9, sizeof(orgunit_test9),
				usage_test9,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test9)) {
			log("Test 9 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 10:
		 */
		if (test_rule_verifier(
				log,
				NULL, 0,
				imei_test10, sizeof(imei_test10),
				NULL, 0,
				NULL, 0,
				usage_test10,
				(uint32_t *)&opid_test10,
				attribute_test10, sizeof(attribute_test10),
				extension_keyusage_test10,
				sizeof(extension_keyusage_test10),
				NULL, 0,
				orgunit_test10, sizeof(orgunit_test10),
				usage_test10,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test10)) {
			log("Test 10 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 11:
		 */
		if (test_rule_verifier(
				log,
				devid_test11, sizeof(devid_test11),
				NULL, 0,
				NULL, 0,
				NULL, 0,
				usage_test11,
				NULL,
				attribute_test11, sizeof(attribute_test11),
				NULL, 0,
				extension_binding_test11,
				sizeof(extension_binding_test11),
				NULL, 0,
				usage_test11,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test11)) {
			log("Test 11 failed!\n");
			goto test_failure;
		}

		/*
		 * Test 12:
		 */
		if (test_rule_verifier(
				log,
				devid_test12, sizeof(devid_test12),
				NULL, 0,
				NULL, 0,
				NULL, 0,
				usage_test12,
				NULL,
				attribute_test12, sizeof(attribute_test12),
				NULL, 0,
				extension_binding_test12,
				sizeof(extension_binding_test12),
				NULL, 0,
				usage_test12,
				NULL,
				NULL,
				NULL,
				NULL, NULL,
				ref_res_test12)) {
			log("Test 12 failed!\n");
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



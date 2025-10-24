/*
 * Copyright 2016, 2021, 2022 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

#include "rule_verifier.h"
#include "rule_verifier_intern.h"
#include "der_parser.h"
#include "asn1pdu_rule.h"
#include "fcserr.h"
#include "fcslog.h"
#include "convert.h"
#include <string.h>

/* 1.3.6.1.4.1.48533.1.2.3 */
const uint8_t rule_somc_oid_attribute[] = {
	0x06, 0x0B, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82,
	0xFB, 0x15, 0x01, 0x02, 0x03
};
/* 1.3.6.1.4.1.48533.1.2.5 */
const uint8_t rule_somc_oid_attr_simlock[] = {
	0x06, 0x0B, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82,
	0xFB, 0x15, 0x01, 0x02, 0x05
};
/* 1.3.6.1.4.1.48533.1.1.1 */
const uint8_t rule_somc_oid_ext_usage[] = {
	0x06, 0x0B, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82,
	0xFB, 0x15, 0x01, 0x01, 0x01
};
/* 1.3.6.1.4.1.48533.1.1.2 */
const uint8_t rule_somc_oid_ext_binding[] = {
	0x06, 0x0B, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82,
	0xFB, 0x15, 0x01, 0x01, 0x02
};

const char *rule_s1root_prefix = "S1_Root";
const char *rule_s1hwconf = "S1_HWConf";
const char *rule_s1simlock = "S1_SL";
const char *rule_s1rlock = "S1_RLock";
const char *rule_s1fota = "S1_FOTA";


struct rule_verifier {
	struct dev_binding *binding;
	uint32_t verified_with_hmac;
	uint32_t allowed_usage;
	bool valid_opid;
	uint32_t opid;
	const char **match;
	uint8_t *extusage_buffer;
	size_t extusage_buffer_len;
	uint8_t *extbind_buffer;
	size_t extbind_buffer_len;
	uint8_t *attribute_buffer;
	size_t attribute_buffer_len;
	uint8_t *attrsimlock_buffer;
	size_t attrsimlock_buffer_len;
	int root_level;
	uint8_t *root_cn_buffer;
	size_t root_cn_buffer_len;
	uint8_t *leaf_cn_buffer;
	size_t leaf_cn_buffer_len;
	uint8_t *leaf_ou_buffer;
	size_t leaf_ou_buffer_len;
	struct derparser_object *parameter;
	struct derparser_object *sequence;
};

static char *rule_memchr(const char *block, char c, size_t size)
{
	char *ptr = NULL;
	char *hlimit = NULL;

	if (!block || size == 0)
		return NULL;

	ptr = (char *)block;
	hlimit = ptr + size;

	while (ptr < hlimit) {
		if (*ptr == c)
			return ptr;
		ptr++;
	}
	return NULL;
}

char *rule_memmem(char *haystack, size_t hlen,
		char *needle, size_t nlen) {

	char *hlimit = NULL;
	char *ptr = NULL;
	char ch = '\0';

	if (!haystack || !needle)
		return NULL;
	if (nlen == 0)
		return haystack;
	if (hlen < nlen)
		return NULL;

	ptr = haystack;
	ch = needle[0];
	hlimit = ptr + hlen - nlen + 1;

	ptr = rule_memchr(ptr, ch, hlimit-ptr);
	while (ptr) {
		if (!memcmp(ptr, needle, nlen))
			return ptr;
		ptr++;
		ptr = rule_memchr(ptr, ch, hlimit-ptr);
	}
	return NULL;
}

static int rule_check_extusage_with_param(
		struct rule_verifier *session,
		uint8_t *asn1_buffer,
		size_t asn1_buffer_len,
		const char *param) {
	int res = -FCSERR_EINVAL;
	struct iterator_info *iterator = NULL;
	struct derparser_object *str_value = NULL;

	if (!session) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * Setup interator for matching usage.
	 */
	res = derparser_create_iterator(
			&iterator,
			asn1pdu_keyusage,
			asn1_buffer_len,
			asn1_buffer,
			(const char **)session->match);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto rule_check_extusage_with_param;
	}

	/*
	 * Extract partition if RULE_USAGE_FLASH.
	 */
	if (session->allowed_usage == RULE_USAGE_FLASH) {
		str_value = derparser_create_string();
		if (str_value == NULL) {
			FCS_LOG_ERR("Failed to create string\n");
			res = -FCSERR_ENOMEM;
			goto rule_check_extusage_with_param;
		}
	}

	/*
	 * Loop through matching usages.
	 */
	while (true) {
		res = derparser_next(iterator, str_value);
		if (res == 0) {
			FCS_LOG_ERR("Failed to find expected usage\n");
			res = -FCSERR_ENOTF;
			goto rule_check_extusage_with_param;
		} else if (res < 0) {
			FCS_LOG_ERR("Failed to extract usage\n");
			goto rule_check_extusage_with_param;
		}
		/*
		 * Matching usage.
		 * Check param constraint.
		 */
		if (param != NULL) {
			if (str_value != NULL &&
				derparser_get_string(str_value) != NULL) {

				if (strncmp(
					derparser_get_string(str_value),
					param, strlen(param)) == 0) {

					/*
					 * Matching param constraint.
					 * We are done.
					 */
					res = FCSERR_OK;
					goto rule_check_extusage_with_param;
				}
			} else {
				FCS_LOG_ERR("No string object found\n");
				return -FCSERR_EINVAL;
			}
		} else {
			/* No param constraint. We are done. */
			res = FCSERR_OK;
			goto rule_check_extusage_with_param;
		}
	}

rule_check_extusage_with_param:
	derparser_delete_object(str_value);
	derparser_delete_iterator(iterator);
	return res;
}

static int rule_check_match(
		uint8_t *binding,
		size_t binding_len,
		uint8_t *binding_hmac,
		size_t binding_hmac_len,
		const struct asn1_item *format,
		uint8_t *asn1_buffer,
		size_t asn1_buffer_len,
		const char **match,
		bool *has_match,
		uint32_t *verified_with_hmac) {
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	struct derparser_object *buf_value = NULL;
	uint8_t *p_buf = NULL;
	size_t buf_len = 0;
	uint32_t binding_count = 0;
	char ui_buf[64];
	int res2 = FCSERR_OK;

	if (has_match == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	*has_match = false;
	if (verified_with_hmac != NULL)
		*verified_with_hmac = 0;
	res = derparser_create_iterator(
			&iterator,
			format,
			asn1_buffer_len,
			asn1_buffer,
			match);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto rule_check_match_end;
	}

	buf_value = derparser_create_buffer();
	if (NULL == buf_value) {
		FCS_LOG_ERR("Failed to create buffer\n");
		res = -FCSERR_ENOMEM;
		goto rule_check_match_end;
	}

	while (true) {
		res = derparser_next(iterator, buf_value);
		if (res < 0) {
			FCS_LOG_ERR("Failed to parse asn1 buffer\n");
			goto rule_check_match_end;
		} else if (res == 0) {
			/* No more bindings */
			if (binding_count > 0) {
				FCS_LOG_ERR("Bindings found, but no match\n");
				res = -FCSERR_EBINDER;
			}
			goto rule_check_match_end;
		}

		binding_count++;
		if (binding_count > 2) {
			FCS_LOG_ERR("More than 2 binding items\n");
			res = -FCSERR_EBINDER;
			goto rule_check_match_end;
		}

		buf_len = derparser_get_buffer(buf_value, &p_buf);

		if (binding != NULL) {
			*has_match = true;

			//dev_id len
			FCS_LOG_INF("binding_len:%d\n", binding_len);
			FCS_LOG_INF("buf_len:%d\n", buf_len);

			//dut_normal.c dut_dev_id
			res2 = bin_to_ascii(ui_buf, sizeof(ui_buf), binding, binding_len);
			if (res2 == FCSERR_OK) {
				FCS_LOG_INF("binding:%s\n", ui_buf);
			}

			res2 = bin_to_ascii(ui_buf, sizeof(ui_buf), p_buf, buf_len);
			if (res2 == FCSERR_OK) {
				FCS_LOG_INF("p_buf:%s\n", ui_buf);
			}

			if ((binding_len == buf_len) &&
				(memcmp(binding, p_buf, buf_len) == 0)) {
				res = FCSERR_OK;
				goto rule_check_match_end;
			}
		}

		if (binding_hmac != NULL) {
			*has_match = true;
			if ((binding_hmac_len == buf_len) &&
				(memcmp(binding_hmac, p_buf, buf_len)) == 0) {
				if (verified_with_hmac != NULL)
					*verified_with_hmac = 1;
				res = FCSERR_OK;
				goto rule_check_match_end;
			}
		}

	}

rule_check_match_end:
	derparser_delete_object(buf_value);
	derparser_delete_iterator(iterator);
	return res;
}

static int rule_check_binding(
		struct rule_verifier *session,
		const struct asn1_item *format,
		uint8_t *asn1_buffer,
		size_t asn1_buffer_len,
		uint32_t *verified_with_hmac)
{
	int res = FCSERR_OK;
	bool has_match = false;

	if (session == NULL || session->binding == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

#ifndef CFG_IGNORE_BINDING_DEVID
	res = rule_check_match(session->binding->die_id,
			session->binding->die_id_sz,
			session->binding->die_id_hmac,
			session->binding->die_id_hmac_sz,
			format, asn1_buffer, asn1_buffer_len,
			(const char **)(ASN1PDU_MATCH_BINDING_DEV_ID),
			&has_match, verified_with_hmac);

	if (res == FCSERR_OK && !has_match) {
		/* No binding on one device ID.
		 * Check for device ID list.
		 */
		res = rule_check_match(session->binding->die_id,
			session->binding->die_id_sz,
			session->binding->die_id_hmac,
			session->binding->die_id_hmac_sz,
			format, asn1_buffer, asn1_buffer_len,
			(const char **)
				(ASN1PDU_MATCH_BINDING_DEV_ID_LIST),
			&has_match, verified_with_hmac);
	}
#endif

	if (res == FCSERR_OK && !has_match) {
		/* No binding on device ID. Check binding for IMEI */
		res = rule_check_match(session->binding->imei,
				session->binding->imei_sz,
				session->binding->imei_hmac,
				session->binding->imei_hmac_sz,
				format, asn1_buffer, asn1_buffer_len,
				(const char **)(ASN1PDU_MATCH_BINDING_IMEI),
				&has_match, verified_with_hmac);
	}

	return res;
}

static int rule_validate_attribute(struct rule_verifier *session)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	struct derparser_object *str_value = NULL;
	struct derparser_object *int_value = NULL;

	if (!session) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	if ((NULL == session->attribute_buffer) ||
			(0 == session->attribute_buffer_len)) {
		FCS_LOG_ERR("No attribute found\n");
		res = -FCSERR_EINVAL;
		goto rule_validate_attribute_end;
	}

	/* Validate usage and extract parameter if available */
	res = derparser_create_iterator(
			&iterator,
			asn1pdu_signatureusage,
			session->attribute_buffer_len,
			(uint8_t *)(session->attribute_buffer),
			(const char **)(session->match));
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto rule_validate_attribute_end;
	}

	if (RULE_USAGE_FLASH == session->allowed_usage) {
		str_value = derparser_create_string();
		if (NULL == str_value) {
			FCS_LOG_ERR("Failed to create string\n");
			res = -FCSERR_ENOMEM;
			goto rule_validate_attribute_end;
		}
	}

	res = derparser_next(iterator, str_value);
	if (0 > res) {
		FCS_LOG_ERR("Failed to parse attribute\n");
		goto rule_validate_attribute_end;
	} else if (0 == res) {
		FCS_LOG_ERR("Unexpected attribute usage\n");
		res = -FCSERR_EINVAL;
		goto rule_validate_attribute_end;
	}
	session->parameter = str_value;
	str_value = NULL;

	/* Validate and extract sequence */
	if (RULE_USAGE_KEYSTORE == session->allowed_usage) {
		int_value = derparser_create_integer();
		if (NULL == int_value) {
			FCS_LOG_ERR("Failed to create integer\n");
			res = -FCSERR_ENOMEM;
			goto rule_validate_attribute_end;
		}

		derparser_delete_iterator(iterator);
		iterator = NULL;

		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				session->attribute_buffer_len,
				(uint8_t *)(session->attribute_buffer),
				ASN1PDU_MATCH_SEQUENCE);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto rule_validate_attribute_end;
		}

		res = derparser_next(iterator, int_value);
		if (0 > res) {
			FCS_LOG_ERR("Failed to parse attribute\n");
			goto rule_validate_attribute_end;
		} else if (0 == res) {
			FCS_LOG_ERR("Did not find sequence\n");
			res = -FCSERR_EINVAL;
			goto rule_validate_attribute_end;
		}
		session->sequence = int_value;
		int_value = NULL;
	}

	/* Validate binding */
	res = rule_check_binding(
		session,
		asn1pdu_signatureusage,
		session->attribute_buffer,
		session->attribute_buffer_len,
		&session->verified_with_hmac);
	if (FCSERR_OK != res)
		FCS_LOG_ERR("Failed to verify binding\n");

rule_validate_attribute_end:
	derparser_delete_object(str_value);
	derparser_delete_object(int_value);
	derparser_delete_iterator(iterator);
	return res;
}

static int rule_get_value(const uint8_t *buffer,
		uint32_t *offset,
		size_t len,
		uint32_t *value)
{
	int res = FCSERR_OK;
	char ch = '\0';
	bool empty = true;
	uint32_t val_out = 0;
	int factor = 16;

	if (!buffer || !offset || !value) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	while (*offset < len) {
		ch = buffer[*offset];
		(*offset)++;
		if (ch == ' ')
			break;
		if (ch >= '0' && ch <= '9') {
			empty = false;
			val_out *= factor;
			val_out += ch - '0';
			continue;
		}
		if (ch >= 'a' && ch <= 'f') {
			empty = false;
			val_out *= factor;
			val_out += ch - 'a' + 10;
			continue;
		}
		if (ch >= 'A' && ch <= 'F') {
			empty = false;
			val_out *= factor;
			val_out += ch - 'A' + 10;
			continue;
		}
		res = -FCSERR_EFORMAT;
		break;
	}
	if (empty)
		res = -FCSERR_EFORMAT;
	if (res == FCSERR_OK)
		*value = val_out;
	return res;
}

static int rule_extract_opid(const uint8_t *buffer,
		size_t buffer_len,
		uint32_t *opid)
{
	int res = FCSERR_OK;
	uint32_t idx_buf = 0;
	uint32_t op_index = 0;
	uint32_t op_id = 0;

	if (!buffer || !opid) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	res = rule_get_value(buffer, &idx_buf, buffer_len, &op_index);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR(
			"Parse opidx failed: %d\n",
			res);
		goto rule_extract_opid_end;
	}
	res = rule_get_value(buffer, &idx_buf, buffer_len, &op_id);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR(
			"Parse opidx failed: %d\n",
			res);
		goto rule_extract_opid_end;
	}
	if (((buffer_len - idx_buf) != 4) ||
			memcmp(&buffer[idx_buf], "OPID", 4)) {
		res = -FCSERR_EFORMAT;
		FCS_LOG_ERR(
			"Parse string failed\n");
		goto rule_extract_opid_end;
	}
	*opid = op_id;

rule_extract_opid_end:
	return res;
}

static int rule_validate_s1(struct rule_verifier *handle)
{
	int res = FCSERR_OK;

	if (!handle) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	if ((handle->root_cn_buffer_len >= strlen(rule_s1root_prefix)) &&
			(NULL != handle->root_cn_buffer) &&
			(0 == memcmp(handle->root_cn_buffer,
					rule_s1root_prefix,
					strlen(rule_s1root_prefix)))) {
		if (NULL != handle->leaf_cn_buffer)  {
			if ((handle->allowed_usage == RULE_USAGE_HWCONFIG) &&
					(handle->leaf_cn_buffer_len ==
					strlen(rule_s1hwconf)) &&
					(0 == memcmp(handle->leaf_cn_buffer,
						rule_s1hwconf,
						strlen(rule_s1hwconf))))
				goto rule_validate_s1_end;
			else if ((handle->allowed_usage ==
						RULE_USAGE_SIMLOCK) &&
					(handle->leaf_cn_buffer_len ==
					strlen(rule_s1simlock)) &&
					(0 == memcmp(handle->leaf_cn_buffer,
						rule_s1simlock,
						strlen(rule_s1simlock))))
				goto rule_validate_s1_end;
			else if ((handle->allowed_usage ==
						RULE_USAGE_RLOCK) &&
					(handle->leaf_cn_buffer_len ==
					strlen(rule_s1rlock)) &&
					(0 == memcmp(handle->leaf_cn_buffer,
						rule_s1rlock,
						strlen(rule_s1rlock))))
				goto rule_validate_s1_end;
			else if ((handle->allowed_usage == RULE_USAGE_FOTA) &&
					(handle->leaf_cn_buffer_len ==
					strlen(rule_s1fota)) &&
					(0 == memcmp(handle->leaf_cn_buffer,
						rule_s1fota,
						strlen(rule_s1fota))))
				goto rule_validate_s1_end;
			else {
				FCS_LOG_ERR(
					"S1 CN doesn't match usage\n");
				res = -FCSERR_EVCC;
				goto rule_validate_s1_end;
			}
		} else {
			FCS_LOG_ERR("No S1 leaf cert is defined\n");
			res = -FCSERR_EVCC;
			goto rule_validate_s1_end;
		}
	} else {
		/* Certificate chain is not S1 PKI */
		res = 1;
	}
rule_validate_s1_end:
	return res;
}

static int rule_validate_extensions(struct rule_verifier *session)
{
	int res = FCSERR_OK;
	char *param = NULL;

	if (!session) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	if ((session->extusage_buffer == NULL) ||
			(session->extusage_buffer_len == 0))
		goto rule_validate_rule_validate_extensions_bind;

	if (session->parameter != NULL)
		param = derparser_get_string(session->parameter);

	res = rule_check_extusage_with_param(
			session,
			session->extusage_buffer,
			session->extusage_buffer_len,
			param);
	if (res != FCSERR_OK)
		goto rule_validate_rule_validate_extensions_end;

rule_validate_rule_validate_extensions_bind:
	if ((session->extbind_buffer == NULL) ||
			(session->extbind_buffer_len == 0))
		goto rule_validate_rule_validate_extensions_end;
	/*
	 * Param verified_with_hmac is only for attribute binding.
	 * Send NULL to function.
	 */
	res = rule_check_binding(
		session,
		asn1pdu_devicebinding,
		session->extbind_buffer,
		session->extbind_buffer_len,
		NULL);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to verify extension binding\n");

rule_validate_rule_validate_extensions_end:
	return res;
}

int rule_init(struct rule_verifier **handle,
	struct dev_binding *binding,
	uint32_t usage)
{
	int res = -FCSERR_EINVAL;
	int i;
	uint32_t ref_usage = 0;
	const char **match = NULL;
	struct rule_verifier *session = NULL;

	if ((!handle) || (!binding) ||
			(0 == usage) ||
			((binding->die_id != NULL) &&
			 (binding->die_id_sz == 0)) ||
			((binding->die_id_hmac != NULL) &&
			 (binding->die_id_hmac_sz == 0)) ||
			((binding->imei != NULL) &&
			 (binding->imei_sz == 0)) ||
			((binding->imei_hmac != NULL) &&
			 (binding->imei_hmac_sz == 0)) ||
			((binding->die_id == NULL) &&
			 (binding->die_id_sz > 0)) ||
			((binding->die_id_hmac == NULL) &&
			 (binding->die_id_hmac_sz > 0)) ||
			((binding->imei == NULL) &&
			 (binding->imei_sz > 0)) ||
			((binding->imei_hmac == NULL) &&
			 (binding->imei_hmac_sz > 0))) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto rule_init_end;
	}

	for (i = 0; i < 32; i++) {
		ref_usage = 1U << i;
		if (usage == (usage & ref_usage)) {
			break;
		} else if (0 != (usage & ref_usage)) {
			FCS_LOG_ERR("Combination of usages not allowed\n");
			goto rule_init_end;
		}
	}

	if (usage == RULE_USAGE_HWCONFIG)
		match = (const char **)ASN1PDU_MATCH_HWC;
	else if (usage == RULE_USAGE_SIMLOCK)
		match = (const char **)ASN1PDU_MATCH_SL;
	else if (usage == RULE_USAGE_LOADER_KERNEL)
		match = (const char **)ASN1PDU_MATCH_LOADER;
	else if (usage == RULE_USAGE_NORMAL_KERNEL)
		match = (const char **)ASN1PDU_MATCH_NORMAL;
	else if (usage == RULE_USAGE_FOTA_KERNEL)
		match = (const char **)ASN1PDU_MATCH_FOTA;
	else if (usage == RULE_USAGE_RAMDUMP_KERNEL)
		match = (const char **)ASN1PDU_MATCH_RAMDUMP;
	else if (usage == RULE_USAGE_FLASH)
		match = (const char **)ASN1PDU_MATCH_FLASH;
	else if (usage == RULE_USAGE_PARTTBL)
		match = (const char **)ASN1PDU_MATCH_FLASH;
	else if (usage == RULE_USAGE_KEYSTORE)
		match = (const char **)ASN1PDU_MATCH_KEYSTORE;
	else if (usage == RULE_USAGE_FOTA)
		match = (const char **)ASN1PDU_MATCH_FOTA;
	else if (usage == RULE_USAGE_RLOCK)
		match = (const char **)ASN1PDU_MATCH_RLOCK;
	else {
		FCS_LOG_ERR("Usages not allowed\n");
		goto rule_init_end;
	}
	session = (struct rule_verifier *)malloc(
		sizeof(struct rule_verifier));
	if (NULL == session) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto rule_init_end;
	}
	session->binding = binding;
	session->verified_with_hmac = 0;
	session->allowed_usage = usage;
	session->valid_opid = false;
	session->opid = 0;
	session->match = match;
	session->extusage_buffer = NULL;
	session->extusage_buffer_len = 0;
	session->extbind_buffer = NULL;
	session->extbind_buffer_len = 0;
	session->attribute_buffer = NULL;
	session->attribute_buffer_len = 0;
	session->attrsimlock_buffer = NULL;
	session->attrsimlock_buffer_len = 0;
	session->root_level = 0;
	session->root_cn_buffer = NULL;
	session->root_cn_buffer_len = 0;
	session->leaf_cn_buffer = NULL;
	session->leaf_cn_buffer_len = 0;
	session->leaf_ou_buffer = NULL;
	session->leaf_ou_buffer_len = 0;
	session->parameter = NULL;
	session->sequence = NULL;

	*handle = session;
	session = NULL;
	res = FCSERR_OK;

rule_init_end:
	rule_deinit(session);
	return res;
}

void rule_deinit(struct rule_verifier *handle)
{
	struct rule_verifier *session = handle;

	if (NULL != session) {
		derparser_delete_object(session->sequence);
		derparser_delete_object(session->parameter);
		free(session->leaf_cn_buffer);
		free(session->root_cn_buffer);
		free(session->attribute_buffer);
		free(session->attrsimlock_buffer);
		free(session->extbind_buffer);
		free(session->extusage_buffer);
		free(session);
	}
}

int rule_set_opid(struct rule_verifier *handle,
	uint32_t opid)
{
	int res = -FCSERR_EINVAL;
	struct rule_verifier *session = handle;

	if (!session) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto rule_set_opid_end;
	}

	if (handle->allowed_usage != RULE_USAGE_SIMLOCK) {
		FCS_LOG_ERR("OPID only valid in SIMLOCK usage.\n");
		goto rule_set_opid_end;
	}

	session->valid_opid = true;
	session->opid = opid;
	res = FCSERR_OK;

rule_set_opid_end:
	return res;
}

int rule_get_actual_usage(struct rule_verifier *handle,
	uint32_t *usage,
	char **param)
{
	int res = -FCSERR_EINVAL;
	struct rule_verifier *session = handle;

	if ((!session) ||
			(NULL == usage) ||
			(NULL == param)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto rule_get_actual_usage_end;
	}

	*usage = session->allowed_usage;
	*param = NULL;
	if (NULL != session->parameter)
		*param = derparser_get_string(session->parameter);
	else
		*param = NULL;
	res = FCSERR_OK;

rule_get_actual_usage_end:
	return res;
}

int rule_get_sequence(struct rule_verifier *handle,
	uint32_t *sequence)
{
	int res = -FCSERR_EINVAL;
	struct rule_verifier *session = handle;

	if ((!session) ||
			(NULL == sequence)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto rule_get_sequence_end;
	}

	if (NULL == session->sequence) {
		FCS_LOG_ERR("No sequence was found\n");
		res = -FCSERR_ENOTF;
		goto rule_get_sequence_end;
	}

	*sequence = derparser_get_integer(session->sequence);
	res = FCSERR_OK;

rule_get_sequence_end:
	return res;
}

static int rule_validate_opid(struct rule_verifier *handle)
{
	int res;
	uint32_t opid_in_cert;

	if (handle->leaf_ou_buffer == NULL && handle->valid_opid) {
		FCS_LOG_ERR("OPID is required\n");
		return -FCSERR_EOPID;
	} else if (handle->leaf_ou_buffer == NULL) {
		return FCSERR_OK;
	}

	res = rule_extract_opid(handle->leaf_ou_buffer,
				handle->leaf_ou_buffer_len, &opid_in_cert);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Extract_opid failed: %d\n", res);
		return res;
	}

	if (!handle->valid_opid || handle->opid != opid_in_cert) {
		FCS_LOG_ERR("OPID unmatched\n");
		return -FCSERR_EOPID;
	}

	return FCSERR_OK;
}

int rule_final(struct rule_verifier *handle)
{
	int res = -FCSERR_EINVAL;
	struct rule_verifier *session = handle;

	if (!session) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto rule_final_end;
	}

	if (handle->allowed_usage == RULE_USAGE_SIMLOCK) {
		res = rule_validate_opid(handle);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Validate opid failed\n");
			goto rule_final_end;
		}
	}

	if ((handle->allowed_usage == RULE_USAGE_HWCONFIG) ||
			(handle->allowed_usage == RULE_USAGE_SIMLOCK) ||
			(handle->allowed_usage == RULE_USAGE_RLOCK) ||
			(handle->allowed_usage == RULE_USAGE_FOTA)) {
		/* S1_ROOT or SOMC CMS */
		res = rule_validate_s1(handle);
		if (res < 0) {
			FCS_LOG_ERR("Verify of S1PKI failed\n");
			goto rule_final_end;
		}
		if (res == FCSERR_OK)
			goto rule_final_end;

		/* Not S1_ROOT we assume SOMC CMS */

	} else if ((handle->allowed_usage != RULE_USAGE_FLASH) &&
			(handle->allowed_usage != RULE_USAGE_KEYSTORE) &&
			(handle->allowed_usage != RULE_USAGE_LOADER_KERNEL) &&
			(handle->allowed_usage != RULE_USAGE_NORMAL_KERNEL)) {
		/* Unexpected usage */
		FCS_LOG_ERR("Unexpected usage\n");
		goto rule_final_end;
	}

	/* SOMC CMS Attribute*/
	res = rule_validate_attribute(handle);
	if (res < 0)
		goto rule_final_end;

	/* SOMC Extensions*/
	res = rule_validate_extensions(handle);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Verify of Extensions failed\n");

rule_final_end:
	return res;
}

static int rule_check_and_save(
	const struct asn1_item *format,
	const uint8_t *const ibuf,
	const size_t isz,
	uint8_t **obuf,
	size_t *const osz)
{
	int res;
	struct iterator_info *iterator = NULL;

	if (*obuf != NULL) {
		FCS_LOG_ERR("Multiple extensions/attributes not supported\n");
		return -FCSERR_EINVAL;
	}

	/* Do sanity check on extension */
	res = derparser_create_iterator(
		&iterator, format, isz,
		(uint8_t *)(ibuf), (const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		return res;
	}

	res = derparser_next(iterator, NULL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse extension\n");
		goto exit;
	}

	/* Save extension to be processed later */
	*obuf = malloc(isz);
	if (*obuf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}
	memcpy(*obuf, ibuf, isz);
	*osz = isz;

	res = FCSERR_OK;
exit:
	derparser_delete_iterator(iterator);
	return res;
}

static bool rule_match_ex_oid(
	const struct rule_extension *ext, const uint8_t *oid, size_t oid_sz)
{
	return ((ext->oid_len == oid_sz)) &&
		(memcmp(ext->oid, oid, oid_sz) == 0);
}

int rule_update_unhandled_extensions(struct rule_verifier *handle,
		const struct rule_extension *extension)
{
	if ((!handle) || (!extension)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	if (rule_match_ex_oid(extension, rule_somc_oid_ext_usage,
			      sizeof(rule_somc_oid_ext_usage)))
		return rule_check_and_save(
			asn1pdu_keyusage, extension->asn1_buffer,
			extension->asn1_buffer_len, &handle->extusage_buffer,
			&handle->extusage_buffer_len);
	else if (rule_match_ex_oid(extension, rule_somc_oid_ext_binding,
				   sizeof(rule_somc_oid_ext_binding)))
		return rule_check_and_save(
			asn1pdu_devicebinding, extension->asn1_buffer,
			extension->asn1_buffer_len, &handle->extbind_buffer,
			&handle->extbind_buffer_len);

	return FCSERR_OK;
}

static bool rule_match_attr_oid(
	const struct rule_attribute *attr, const uint8_t *oid, size_t oid_sz)
{
	return ((attr->oid_len == oid_sz)) &&
		(memcmp(attr->oid, oid, oid_sz) == 0);
}

int rule_update_unhandled_attributes(struct rule_verifier *handle,
		const struct rule_attribute *attribute)
{
	if ((!handle) || (!attribute)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	if (rule_match_attr_oid(attribute, rule_somc_oid_attribute,
				sizeof(rule_somc_oid_attribute)))
		return rule_check_and_save(
			asn1pdu_signatureusage, attribute->asn1_buffer,
			attribute->asn1_buffer_len, &handle->attribute_buffer,
			&handle->attribute_buffer_len);
	if (rule_match_attr_oid(attribute, rule_somc_oid_attr_simlock,
				sizeof(rule_somc_oid_attr_simlock)))
		return rule_check_and_save(
			asn1pdu_simlockprotection, attribute->asn1_buffer,
			attribute->asn1_buffer_len, &handle->attrsimlock_buffer,
			&handle->attrsimlock_buffer_len);

	return FCSERR_OK;

}

int rule_update_subject_cn(struct rule_verifier *handle,
		const struct rule_cn *cn)
{
	int res = -FCSERR_EINVAL;
	struct rule_verifier *session = handle;

	if ((!session) || (!cn)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto rule_update_subject_cn_end;
	}

	if (0 == cn->cert_level) {
		if (NULL != handle->leaf_cn_buffer) {
			FCS_LOG_ERR("Multiple leaf certs???\n");
			res = -FCSERR_EVCC;
			goto rule_update_subject_cn_end;
		}
		session->leaf_cn_buffer = malloc(cn->cn_len);
		if (NULL == session->leaf_cn_buffer) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto rule_update_subject_cn_end;
		}
		memcpy(session->leaf_cn_buffer, cn->cn, cn->cn_len);
		session->leaf_cn_buffer_len = cn->cn_len;
	} else {
		if (session->root_level < cn->cert_level) {
			if (NULL != session->root_cn_buffer) {
				/* Previous cert wasn't the root */
				free(session->root_cn_buffer);
				session->root_cn_buffer = NULL;
			}
			session->root_cn_buffer = malloc(cn->cn_len);
			if (NULL == session->root_cn_buffer) {
				FCS_LOG_ERR("Out of memory\n");
				res = -FCSERR_ENOMEM;
				goto rule_update_subject_cn_end;
			}
			memcpy(session->root_cn_buffer, cn->cn, cn->cn_len);
			session->root_cn_buffer_len = cn->cn_len;
			session->root_level = cn->cert_level;
		}
	}

	res = FCSERR_OK;

rule_update_subject_cn_end:
	return res;
}

int rule_update_subject_ou(struct rule_verifier *handle,
		const struct rule_ou *ou)
{
	int res = -FCSERR_EINVAL;
	struct rule_verifier *session = handle;

	if ((!session) || (!ou)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto rule_update_subject_ou_end;
	}

	if (0 == ou->cert_level) {
		if (rule_memmem((char *)ou->ou, ou->ou_len,
				(char *)"OPID", 4)) {
			if (NULL != handle->leaf_ou_buffer) {
				FCS_LOG_ERR("Multiple ou with OPID???\n");
				res = -FCSERR_EVCC;
				goto rule_update_subject_ou_end;
			}
			session->leaf_ou_buffer = malloc(ou->ou_len);
			if (NULL == session->leaf_ou_buffer) {
				FCS_LOG_ERR("Out of memory\n");
				res = -FCSERR_ENOMEM;
				goto rule_update_subject_ou_end;
			}
			memcpy(session->leaf_ou_buffer, ou->ou, ou->ou_len);
			session->leaf_ou_buffer_len = ou->ou_len;
		} else {
			FCS_LOG_ERR("Don't allow OU without OPID\n");
			res = -FCSERR_EVCC;
			goto rule_update_subject_ou_end;
		}
	}

	res = FCSERR_OK;

rule_update_subject_ou_end:
	return res;
}

int rule_verified_with_hmac(struct rule_verifier *handle,
		uint32_t *verified_with_hmac)
{
	if ((!handle) || (!verified_with_hmac)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	*verified_with_hmac = handle->verified_with_hmac;

	return FCSERR_OK;
}

int rule_get_simlock_range(struct rule_verifier *handle, int *start, int *len)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	struct derparser_object *int_value = NULL;

	if (!handle || !start || !len) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	if ((handle->attrsimlock_buffer == NULL) ||
	    (handle->attrsimlock_buffer_len == 0)) {
		FCS_LOG_ERR("No attributes found\n");
		return -FCSERR_EINVAL;
	}

	/* Validate usage and extract parameter if available */
	res = derparser_create_iterator(
		&iterator, asn1pdu_simlockprotection,
		handle->attrsimlock_buffer_len,
		(uint8_t *)(handle->attrsimlock_buffer),
		ASN1PDU_MATCH_START);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto exit;
	}

	int_value = derparser_create_integer();
	if (int_value == NULL) {
		FCS_LOG_ERR("Failed to create int value\n");
		goto exit;
	}

	res = derparser_next(iterator, int_value);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse attribute\n");
		goto exit;
	}
	*start = derparser_get_integer(int_value);

	derparser_delete_iterator(iterator);
	iterator = NULL;

	res = derparser_create_iterator(
		&iterator, asn1pdu_simlockprotection,
		handle->attrsimlock_buffer_len,
		(uint8_t *)(handle->attrsimlock_buffer),
		ASN1PDU_MATCH_LENGTH);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto exit;
	}

	res = derparser_next(iterator, int_value);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse attribute\n");
		goto exit;
	}
	*len = derparser_get_integer(int_value);
	res = FCSERR_OK;

exit:
	derparser_delete_iterator(iterator);
	derparser_delete_object(int_value);
	return res;
}

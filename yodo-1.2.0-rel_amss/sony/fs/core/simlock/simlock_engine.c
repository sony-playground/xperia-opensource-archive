/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "simlock_engine.h"
#include <string.h>
#include "fcserr.h"
#include "fcslog.h"
#include "fcs_crypto.h"
#include "digest.h"


#define NOF_LOCK_CATEGORIES	4
#define MAX_HASH_LEN		32
#define MAX_UNLOCK_KEY_LEN	20
#define SALT_LEN		20
#define BOMB_LEN		20
#define VER_OFFS		(BOMB_LEN)

struct simlock_data_offsets {
	int bomb_code;
	int fresh_code;
	int test_sims;
	int custom;
	int static_lock[NOF_LOCK_CATEGORIES];
	int codes[NOF_LOCK_CATEGORIES];
	int cks[NOF_LOCK_CATEGORIES];
	int al[NOF_LOCK_CATEGORIES];
	int fresh_seal;  /* dynamic signature */
	int kirin;      /* dynamic signature */
	int total_size;  /* total size excluding kirin */
};

static unsigned int get_big_uint(const unsigned char *adr,
				const unsigned char *end_adr)
{
	unsigned int a;

	if (adr + 4 > end_adr)
		return 0;

	a = adr[0] << 24;
	a |= adr[1] << 16;
	a |= adr[2] << 8;
	a |= adr[3];

	return a;
}

static int get_big_ushort(const unsigned char *adr,
			const unsigned char *end_adr)
{
	int a;

	if (adr + 2 > end_adr)
		return 0;

	a = adr[0] << 8;
	a |= adr[1];

	return a;
}

static int get_uchar(const unsigned char *adr, const unsigned char *end_adr)
{
	if (adr + 1 > end_adr)
		return 0;

	return adr[0];
}

static int parse_auto_locked(const unsigned char *buf, unsigned int buf_len,
			int start_offs, struct simlock_data_offsets *sd_offs)
{
	const unsigned char *bufend;
	int offs;
	int cat_offs;
	int a;
	int lock_cat_len;

	bufend = buf + buf_len;
	offs = start_offs;

	for (a = 0; a < NOF_LOCK_CATEGORIES; a++) {
		sd_offs->al[a] = offs;
		lock_cat_len = get_big_ushort(&buf[offs], bufend);
		offs += 2;
		cat_offs = 0;
		while (cat_offs < lock_cat_len) {
			cat_offs += 2 + get_big_ushort(&buf[offs + cat_offs],
							bufend);
			cat_offs += 1 + get_uchar(&buf[offs + cat_offs],
							bufend);
			cat_offs += 1 + get_uchar(&buf[offs + cat_offs],
							bufend);
			if (offs + cat_offs > (int)buf_len)
				break;
		}
		if (cat_offs != lock_cat_len) {
			FCS_LOG_ERR("Bad SimLock data\n");
			return -FCSERR_EDATA;
		}
		offs += lock_cat_len;
	}
	if (offs > (int)buf_len) {
		FCS_LOG_ERR("Bad SimLock data\n");
		return -FCSERR_EDATA;
	}

	offs -= start_offs;

	return offs;
}

static int parse_cks(const unsigned char *buf, unsigned int buf_len,
		int start_offs,	struct simlock_data_offsets *sd_offs)
{
	const unsigned char *bufend;

	int a;
	int offs;
	int code_len;

	bufend = buf + buf_len;
	offs = start_offs;

	for (a = 0; a < NOF_LOCK_CATEGORIES; a++) {
		sd_offs->cks[a] = offs;
		offs += 1;
		code_len = get_uchar(&buf[offs], bufend);
		offs += 1 + code_len;
	}
	if (offs > (int)buf_len) {
		FCS_LOG_ERR("Bad SimLock data\n");
		return -FCSERR_EDATA;
	}

	offs -= start_offs;

	return offs;
}

static int parse_codes(const unsigned char *buf, unsigned int buf_len,
		int start_offs,	struct simlock_data_offsets *sd_offs)
{
	const unsigned char *bufend;
	int offs;
	int a;
	int code_hash_len;

	bufend = buf + buf_len;
	offs = start_offs;

	for (a = 0; a < NOF_LOCK_CATEGORIES; a++) {
		sd_offs->codes[a] = offs;
		offs += SALT_LEN + 5;
		code_hash_len = get_uchar(&buf[offs], bufend);
		offs += 1 + code_hash_len;
	}
	if (offs > (int)buf_len) {
		FCS_LOG_ERR("Bad SimLock data\n");
		return -FCSERR_EDATA;
	}

	offs -= start_offs;

	return offs;
}


static int parse_one_customization(const unsigned char *buf,
			unsigned int buf_len, int start_offs)
{
	const unsigned char *bufend;
	int offs;
	int lock_cat_len;
	int imsi_len;
	int gid_len;
	int a;

	bufend = buf + buf_len;
	offs = start_offs;

	lock_cat_len = get_big_ushort(&buf[offs], bufend);
	offs += 2;

	while ((offs - start_offs) - 2 < lock_cat_len) {
		imsi_len = get_big_ushort(&buf[offs], bufend);
		offs += 2 + imsi_len;

		for (a = 0; a < 2; a++) {
			gid_len = get_uchar(&buf[offs], bufend);
			offs += 1 + gid_len;
		}
	}

	if (offs > (int)buf_len) {
		FCS_LOG_ERR("Bad SimLock data\n");
		return -FCSERR_EDATA;
	}
	if (start_offs + lock_cat_len + 2 != offs) {
		FCS_LOG_ERR("Bad SimLock data\n");
		return -FCSERR_EDATA;
	}

	offs -= start_offs;

	return offs;
}


static int parse_custom(const unsigned char *buf, unsigned int buf_len,
			int start_offs, struct simlock_data_offsets *sd_offs)
{
	int a;
	int len;
	int lensum = 4;

	sd_offs->custom = start_offs;
	for (a = 0; a < NOF_LOCK_CATEGORIES; a++) {
		sd_offs->static_lock[a] = start_offs + lensum;
		len = parse_one_customization(buf, buf_len,
					sd_offs->static_lock[a]);
		if (len < 0) {
			lensum = len;
			break;
		}
		lensum += len;
	}

	return lensum;
}


static int parse_config(const unsigned char *buf, unsigned int buf_len,
		int start_offs,	struct simlock_data_offsets *sd_offs)
{
	const unsigned char *bufend;
	int offs;
	int ver;
	int test_sims_len;
	int operator_name_len;
	int server_marker_len;
	int code_hash_len;

	bufend = buf + buf_len;
	offs = start_offs;

	ver = buf[offs++];
	if (ver != 2) {
		FCS_LOG_ERR("Invalid simlock version\n");
		return -FCSERR_EVER;
	}

	offs += 3;

	sd_offs->bomb_code = offs;
	offs += SALT_LEN + 5;
	code_hash_len = get_uchar(&buf[offs], bufend);
	offs += 1 + code_hash_len;

	sd_offs->fresh_code = offs;
	offs += SALT_LEN + 5;
	code_hash_len = get_uchar(&buf[offs], bufend);
	offs += 1 + code_hash_len;

	operator_name_len = get_big_ushort(&buf[offs], bufend);
	offs += 2 + operator_name_len;

	server_marker_len = get_big_ushort(&buf[offs], bufend);
	offs += 2 + server_marker_len;

	sd_offs->test_sims = offs;
	test_sims_len = get_big_ushort(&buf[offs], bufend);

	offs += 2 + test_sims_len;

	if (offs > (int)buf_len) {
		FCS_LOG_ERR("Bad SimLock data\n");
		return -FCSERR_EDATA;
	}

	offs -= start_offs;

	return offs;
}

static int parse_dynamic_signature(const unsigned char *simlock_data,
			unsigned int simlock_data_len, int start_offs,
			struct simlock_data_offsets *sd_offs)
{
	int offs;
	int ver;
	int seal_len;
	const unsigned char *bufend;

	bufend = simlock_data + simlock_data_len;
	offs = start_offs;

	sd_offs->fresh_seal = -1;
	sd_offs->kirin = -1;
	ver = simlock_data[VER_OFFS];
	if (ver <= 1)
		return 0;

	sd_offs->fresh_seal = offs;
	seal_len = get_uchar(&simlock_data[offs++], bufend);
	offs += seal_len;
	if (offs > (int)simlock_data_len) {
		FCS_LOG_ERR("Bad SimLock data\n");
		return -FCSERR_EDATA;
	}

	sd_offs->kirin = offs;
	offs -= start_offs;

	return offs;
}

static int parse_simlock_data(const unsigned char *simlock_data,
				unsigned int simlock_data_len,
				struct simlock_data_offsets *sd_offs)
{
	int offs = 0;
	int config_len;
	int custom_len;
	int codes_len;
	int cks_len;
	int auto_locked_len;
	int dyn_sig_len;

	if (!simlock_data || simlock_data_len < BOMB_LEN + 1)
		return -FCSERR_EINVAL;
	offs += BOMB_LEN;

	config_len = parse_config(simlock_data, simlock_data_len,
				offs, sd_offs);
	if (config_len < 0)
		return config_len;

	offs += config_len;

	custom_len = parse_custom(simlock_data, simlock_data_len,
				offs, sd_offs);
	if (custom_len < 0)
		return custom_len;

	offs += custom_len;

	codes_len = parse_codes(simlock_data, simlock_data_len, offs, sd_offs);
	if (codes_len < 0)
		return codes_len;

	offs += codes_len;

	cks_len = parse_cks(simlock_data, simlock_data_len, offs, sd_offs);
	if (cks_len < 0)
		return cks_len;

	offs += cks_len;

	auto_locked_len = parse_auto_locked(simlock_data, simlock_data_len,
				offs, sd_offs);
	if (auto_locked_len < 0)
		return auto_locked_len;

	offs += auto_locked_len;

	dyn_sig_len = parse_dynamic_signature(simlock_data, simlock_data_len,
				offs, sd_offs);
	if (dyn_sig_len < 0)
		return dyn_sig_len;

	offs += dyn_sig_len;

	sd_offs->total_size = offs;

	return FCSERR_OK;
}


static int verify_unlock(const unsigned char *simlock_data,
			unsigned int data_len,
			int code_offs,
			int unlock_code_offs,
			unsigned int unlock_code_len)
{
	/* Return  0: unlocked; 1: locked */

	int code_type;
	const unsigned char *bufend;
	unsigned int iteration_count;
	int salt_offs;
	unsigned int code_hash_length;
	unsigned char unlock_code_hash[MAX_HASH_LEN];
	int status = FCSERR_OK;
	unsigned int buf_len;
	unsigned int b;

	bufend = simlock_data + data_len;

	code_type = simlock_data[code_offs++];
	if (code_type != 2) {
		FCS_LOG_ERR("Only SHA256 is supported\n");
		return 1;
	}

	iteration_count = get_big_uint(&simlock_data[code_offs], bufend);
	code_offs += 4;
	salt_offs = code_offs;
	code_offs += SALT_LEN;
	code_hash_length = simlock_data[code_offs++];
	if (code_hash_length == 0)
		return 0;

	buf_len = sizeof(unlock_code_hash);
	status = simlock_engine_hash_unlock_code(iteration_count,
					&simlock_data[unlock_code_offs],
					unlock_code_len,
					&simlock_data[salt_offs],
					SALT_LEN,
					unlock_code_hash,
					&buf_len);
	if (status != FCSERR_OK) {
		FCS_LOG_ERR("simlock_engine_hash_unlock_code error %d\n",
				status);
		return 1;
	}

	if (buf_len != code_hash_length) {
		FCS_LOG_WRN("Mismatch in unlock code length\n");
		return 1;
	}

	for (b = 0; b < buf_len; b++) {
		if (unlock_code_hash[b] != simlock_data[code_offs + b])
			return 1;
	}

	return 0;
}

static int static_lock_is_empty(const unsigned char *simlock_data,
				unsigned int data_len,
				const struct simlock_data_offsets *sd_offs,
				int category)
{
	/* Return  0 = static lock of this category is empty
	 *         1 = static lock of this category is not empty */
	int lock_cat_len;
	int offs;
	const unsigned char *end_adr;

	end_adr = simlock_data + data_len;
	offs = sd_offs->static_lock[category];
	lock_cat_len = get_big_ushort(&simlock_data[offs], end_adr);
	if (lock_cat_len <= 4)
		return 0;

	return 1;
}


static int auto_lock_is_empty(const unsigned char *simlock_data,
			unsigned int data_len,
			const struct simlock_data_offsets *sd_offs,
			int category)
{
	/* Return  0 = auto lock of this category is empty or inactive
	 *         1 = auto lock of this category is not empty */
	int lock_cat_len;
	int offs;
	const unsigned char *end_adr;

	end_adr = simlock_data + data_len;
	/* Is autolock inactive? */
	offs = sd_offs->custom;
	if (simlock_data[offs + category] == 0)
		return 0;

	/* Is autolock empty? */
	offs = sd_offs->al[category];
	lock_cat_len = get_big_ushort(&simlock_data[offs], end_adr);
	if (lock_cat_len <= 4)
		return 0;

	return 1;
}

/**
 * Hashes the unlock clear text key and checks if it matches the static
 * key hash. If it does unlock_state is set to 1 indicating that the
 * lock category in question has been unlocked.
 */
static int calculate_one_unlock_state(const unsigned char *simlock_data,
				unsigned int data_len,
				const struct simlock_data_offsets *sd_offs,
				int category,
				unsigned char *unlock_state)
{
	int b;
	int offs;
	unsigned int unlock_code_length;

	offs = sd_offs->cks[category];
	offs += 1;
	unlock_code_length = simlock_data[offs++];

	b = verify_unlock(simlock_data, data_len, sd_offs->codes[category],
			offs, unlock_code_length);

	*unlock_state = 0;
	if (b == 0)
		*unlock_state = 1;

	return FCSERR_OK;
}

int simlock_engine_get_lock_status(int category,
				const unsigned char *simlock_data,
				unsigned int data_len,
				int *lock_status)
{
	int status;
	unsigned char unlocked;
	struct simlock_data_offsets sd_offs;

	if (!lock_status || category < 1 || category > NOF_LOCK_CATEGORIES)
		return -FCSERR_EINVAL;

	*lock_status = 1;

	status = parse_simlock_data(simlock_data, data_len, &sd_offs);
	if (status != FCSERR_OK) {
		FCS_LOG_ERR("parse_simlock_data returned error: %d\n", status);
		return status;
	}

	/* Return unlocked if we have a correct unlock code */
	status = calculate_one_unlock_state(simlock_data, data_len,
					&sd_offs, category - 1 , &unlocked);
	if (status != FCSERR_OK) {
		FCS_LOG_ERR("calculate_one_unlock_state returned error: %d\n",
				status);
		return status;
	}

	if (unlocked != 0) {
		*lock_status = 0;
		return FCSERR_OK;
	}

	/* Return unlocked if static lock and autolock are empty */
	if (static_lock_is_empty(simlock_data, data_len, &sd_offs, category - 1)
	== 0 &&
	auto_lock_is_empty(simlock_data, data_len, &sd_offs, category - 1) == 0)
		*lock_status = 0;

	return status;
}

int simlock_engine_hash_unlock_code(unsigned int iteration_count,
			const unsigned char *unlock_code,
			unsigned int unlock_code_len,
			const unsigned char *salt, unsigned int salt_len,
			unsigned char *res_buf, unsigned int *res_buf_len)
{
	unsigned char hash_buf[MAX_UNLOCK_KEY_LEN + SALT_LEN];
	unsigned int hash_len;
	int status;
	unsigned int a;
	struct digest *dgst = NULL;
	unsigned int calc_hash_length = 0;
	unsigned char *local_res_buf;

	if (!unlock_code ||
		unlock_code_len > MAX_UNLOCK_KEY_LEN ||
		iteration_count == 0) {
		return -FCSERR_EINVAL;
	}

	/* The SHA-256 hash algorithm */
	if (*res_buf_len < MAX_HASH_LEN) {
		FCS_LOG_ERR("Buffer too small\n");
		return -FCSERR_EINVAL;
	}

	if (unlock_code_len + salt_len > sizeof(hash_buf)) {
		FCS_LOG_ERR("hash_buf too small\n");
		return -FCSERR_EINVAL;
	}

	memcpy(hash_buf, unlock_code, unlock_code_len);
	memcpy(hash_buf + unlock_code_len, salt, salt_len);
	hash_len = unlock_code_len + salt_len;


	for (a = 0; a < iteration_count; a++) {
		if (a > 0) {
			memcpy(hash_buf, local_res_buf, MAX_HASH_LEN);
			hash_len = MAX_HASH_LEN;
		}
		if (dgst != NULL)
			digest_sha256_deinit(dgst);
		status = digest_sha256_init(&dgst);
		if (status != FCSERR_OK) {
			FCS_LOG_ERR("Failed to init digest calculation: (%d)\n",
					status);

			goto exit;
		}
		status = digest_sha256_update(dgst, hash_buf, hash_len);
		if (status != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update digest: (%d)\n",
					status);
			goto exit;
		}

		status = digest_sha256_final(dgst, &local_res_buf,
				&calc_hash_length);
		if (status != FCSERR_OK) {
			FCS_LOG_ERR("Failed to finalize digest: (%d)\n",
					status);
			goto exit;
		}
	}
	*res_buf_len = MAX_HASH_LEN;
	memcpy(res_buf, local_res_buf, *res_buf_len);

exit:
	if (dgst != NULL)
		digest_sha256_deinit(dgst);
	return status;
}

/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kstypes.h"
#include "kspk.h"
#include "rpmbio.h"
#include "nvio.h"
#include "fcserr.h"
#include "fcs_defines.h"

static uint32_t die_id_mock = 0x4673;
static uint8_t  imei_mock[IMEI_ASCII_SIZE] = "12345678901234";
static uint32_t rpmb_counter_mock = 1;
static uint8_t  rot_mock[]    = {0x1, 0x2, 0x3, 0x4};

extern unsigned char	test_ks_bin[];
extern int		test_ks_bin_len;

/* Define Implementation provided callbacks */
crypto_cms_cb_t		plf_cms_cb;
ks_io_read_cb_t		plf_nv_read_cb;
ks_io_write_cb_t	plf_nv_write_cb;
ks_io_read_cb_t		plf_rpmb_read_cb;
ks_io_write_cb_t	plf_rpmb_write_cb;

void hexdump(uint8_t* buf, uint32_t sz)
{
	int i;

	for (i = 0; i < sz; i++) {
		if ((i % 16) == 0)
			printf("\n");
		printf("%X,", buf[i]);
	}
	printf("\n");
}

int plf_rpmb_write_mock(ks_io_state_t *state, uint8_t *data, uint32_t data_sz)
{
	printf("Writing to RPMB\n");
	return FCSERR_OK;
}

int plf_rpmb_read_mock(ks_io_state_t *state, uint8_t *data, uint32_t *data_sz)
{
	printf("Reading from RPMB\n");
	if (*data_sz < sizeof(rpmb_counter_mock))
		return -FCSERR_EINVAL;

	memcpy(data, &rpmb_counter_mock, sizeof(rpmb_counter_mock));
	*data_sz = sizeof(rpmb_counter_mock);
	return FCSERR_OK;
}

int plf_nv_write_mock(ks_io_state_t *state,
			uint8_t *data,
			const uint32_t data_sz)
{
	nvio_state_t *the_nv_state;

	the_nv_state = (nvio_state_t *)state;
	printf("Writing to NV partition:%d\n", the_nv_state->partition);
	return FCSERR_OK;
}

int plf_nv_read_mock(ks_io_state_t *state,
			uint8_t *data,
			uint32_t *data_sz)
{
	nvio_state_t *the_nv_state;

	the_nv_state = (nvio_state_t *)state;
	printf("Reading from NV partition:%d\n", the_nv_state->partition);
	*data_sz = test_ks_bin_len;
	if (data)
		memcpy(data, &test_ks_bin[0], test_ks_bin_len);

	return FCSERR_OK;
}

int plf_cms_mock(const uint8_t *const rot, const uint32_t rot_sz,
			const uint8_t *const msg, const uint32_t msg_sz,
			const uint8_t *const die_id, const uint32_t die_sz,
			const uint8_t *const imei, const uint32_t imei_sz,
			uint32_t *counter,
			uint8_t **payload,
			uint32_t *payload_len)
{
	*payload = (uint8_t *)msg + 0x40;
	*payload_len = 0x1241;
	*counter = 1;

	return FCSERR_OK;
}

int  main(void)
{
	ks_context_t *the_keystore;
	struct ks_io_handle *rpmb_handle;
	struct ks_io_handle *nv_org_handle;
	struct ks_io_handle *nv_bak_handle;
	int ret;
	uint32_t nof_keys;
	struct ksstore_blob the_data;

	/* Initialize Implementation defined callbacks */
	plf_cms_cb = plf_cms_mock;
	plf_nv_read_cb = plf_nv_read_mock;
	plf_nv_write_cb = plf_nv_write_mock;
	plf_rpmb_read_cb = plf_rpmb_read_mock;
	plf_rpmb_write_cb = plf_rpmb_write_mock;

	ret = rpmb_open(&rpmb_handle);
	if (ret != FCSERR_OK) {
		printf("Failed to create RPMB handle\n");
		exit(1);
	}

	ret = nv_open(&nv_org_handle, KS_NV_ORG);
	if (ret != FCSERR_OK) {
		printf("Failed to create NV handle\n");
		exit(1);
	}

	ret = nv_open(&nv_bak_handle, KS_NV_BAK);
	if (ret != FCSERR_OK) {
		printf("Failed to create NV handle\n");
		exit(1);
	}

	ret = ks_create_static(&the_keystore,
			(uint8_t*) &die_id_mock,
			sizeof(die_id_mock),
			imei_mock,
			sizeof(imei_mock),
			nv_org_handle,
			nv_bak_handle,
			rpmb_handle,
			rot_mock,
			sizeof(rot_mock));
	if (ret != FCSERR_OK) {
		printf("Failed to create KEYSTORE handle\n");
		exit(1);
	}

	ret = ks_load_keystore(the_keystore, XFLKEYSTORE_PRIM);
	if (ret != FCSERR_OK) {
		printf("Failed to load the keystore\n");
		exit(1);
	}

	ret = ks_get_nof_keys(the_keystore, 0, &nof_keys);
	if (ret != FCSERR_OK) {
		printf("Failed to get number of keys\n");
		exit(1);
	}
	printf("The keystore domain 0 has %d keys\n", nof_keys);

	ret = ks_get_key_by_index(the_keystore, 0, 0, &the_data);
	if (ret != FCSERR_OK) {
		printf("Failed to get key %d\n", 0);
		exit(1);
	}
	hexdump(the_data.blob, the_data.size);

	ret = ks_get_key_by_index(the_keystore, 0, 1, &the_data);
	if (ret != FCSERR_OK) {
		printf("Failed to get key %d\n", 1);
		exit(1);
	}
	hexdump(the_data.blob, the_data.size);

	ret = ks_get_nof_keys(the_keystore, 1, &nof_keys);
	if (ret != FCSERR_OK) {
		printf("Failed to get number of keys\n");
		exit(1);
	}
	printf("The keystore domain 1 has %d keys\n", nof_keys);

	ret = ks_get_key_by_index(the_keystore, 1, 0, &the_data);
	if (ret != FCSERR_OK) {
		printf("Failed to get key %d\n", 0);
		exit(1);
	}
	hexdump(the_data.blob, the_data.size);

	ret = ks_get_key_by_index(the_keystore, 1, 1, &the_data);
	if (ret != FCSERR_OK) {
		printf("Failed to get key %d\n", 1);
		exit(1);
	}
	hexdump(the_data.blob, the_data.size);

	ks_destroy(the_keystore);
	return 0;
}

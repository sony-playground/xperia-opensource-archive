/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "transport_verifier.h"
#include "fcserr.h"
#include "fcslog.h"
#include <string.h>

#define HASH_ITEM_SIZE 0x20

struct transport_verifier {
	uint8_t *hashlist_cur;
	uint8_t *hashlist_end;
};

int transport_init(struct transport_verifier **handle,
	uint8_t *payload,
	size_t payload_len)
{
	int res = -FCSERR_EINVAL;
	struct transport_verifier *session = NULL;

	if ((!handle) ||
			(NULL == payload) ||
			(0 == payload_len)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto transport_init_end;
	}

	if (0 != (payload_len % HASH_ITEM_SIZE)) {
		FCS_LOG_ERR("Payload size is not multiple of SHA256\n");
		goto transport_init_end;
	}

	session = malloc(sizeof(struct transport_verifier) + payload_len);
	if (NULL == session) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto transport_init_end;
	}
	session->hashlist_cur =
		&((uint8_t *)session)[sizeof(struct transport_verifier)];
	session->hashlist_end = session->hashlist_cur + payload_len;
	memcpy(session->hashlist_cur, payload, payload_len);

	*handle = session;
	session = NULL;
	res = FCSERR_OK;

transport_init_end:
	transport_deinit(session);
	return res;
}

void transport_deinit(struct transport_verifier *handle)
{
	free(handle);
}

bool transport_has_more(struct transport_verifier *handle)
{
	struct transport_verifier *session = handle;

	if ((NULL != session) &&
			((session->hashlist_cur + HASH_ITEM_SIZE) <=
				session->hashlist_end))
		return true;
	return false;
}

int transport_verify_hash(struct transport_verifier *handle,
	uint8_t *hash,
	size_t hash_len)
{
	int res = -FCSERR_EINVAL;
	struct transport_verifier *session = handle;
	uint8_t *p_buf = NULL;
	size_t buf_len = 0;

	if ((!session) ||
			(NULL == hash) ||
			(0 == hash_len)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		goto transport_verify_hash_end;
	}

	if ((session->hashlist_cur + HASH_ITEM_SIZE) >
			session->hashlist_end) {
		FCS_LOG_ERR("No more hash entries\n");
		res = -FCSERR_ESTATE;
		goto transport_verify_hash_end;
	}

	/* Check towards current hash value */
	buf_len = HASH_ITEM_SIZE;
	p_buf = session->hashlist_cur;
	if ((hash_len != buf_len) ||
			(0 != memcmp(hash, p_buf, buf_len))) {
		FCS_LOG_ERR("Did not match hash\n");
		res = -FCSERR_EVHSH;
		goto transport_verify_hash_end;
	}

	/* Iterate to next hash value */
	session->hashlist_cur += HASH_ITEM_SIZE;

	res = FCSERR_OK;

transport_verify_hash_end:
	return res;
}


/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SAKE_ENGINE_INTERNAL_H_
#define SAKE_ENGINE_INTERNAL_H_

#include "sake_engine.h"

/*
 * Defines needed in the firehose environment
 */
#ifdef FEATURE_DEVICEPROGRAMMER_SOMC
extern void *somc_malloc(size_t sz);
extern void somc_free(void *ptr);

#define free somclib_free
#define malloc somclib_malloc
#endif

#ifdef SAKE_DEBUG
static void SAKE_DBGDUMP(unsigned char *adr, unsigned int len)
{
	unsigned int a;

	for (a = 0; a < len; a++) {
		printf("%02x ", adr[a]);
		if ((a&0xf) == 15)
			printf("\n");
	}
	printf("\n");
}
#else
#define SAKE_DBGDUMP(adr, len)
#endif

/* Firehose patch */
#define CONFIG_SAKE_SHA256_HASH
/* End Firehose patch */
#define CRL_ENTRY_SIZE 4
/*
 * perhaps it is safer to always use the same size to make it less
 * transparent
 */
/* which sha is used? */
#define PUB_HASH_LEN 2
#define PUB_EXP_LEN 3
#ifdef CONFIG_SAKE_SHA256_HASH
#define HASH_TYPE_INTERNAL SHA256_HASH
#define HASH_SIZE 32
#define HASH_ALG 4
#define SAKE_OID_SIZE 19
#define SAKE_OID  {0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01,\
		   0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20}
#else
#ifdef CONFIG_SAKE_SHA1_HASH
#define HASH_TYPE_INTERNAL SHA1_HASH
#define HASH_SIZE 20
#define HASH_ALG 1
#define SAKE_OID_SIZE 15
#define SAKE_OID {0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02,\
		  0x1a, 0x05, 0x00, 0x04, 0x14 }
#else
#error "We must define which hash algorithm to use"
#endif
#endif

#define DEFAULT_SSN 0xffffffff

struct R_ITEM {
	uint32_t len;
	uint8_t *data;
};

struct PublicKey {
	struct R_ITEM item_m;   /* Public Modulus */
	struct R_ITEM item_e;   /* Public Exponent */
	struct R_ITEM item_h;   /* Public Hash */
};



/* internal representation of sake related info */
struct sake_internal_handle {
	hash_type_t hash_type; /* hash type */
	uint32_t hash_digest_size; /* hash digest size */
	uint32_t savedHelloLen;/* length of saved hello message */
	uint8_t *savedHelloMsg;/*
				* saved hello message kept after a successful
				* call to compose helloi
				*/
	uint32_t savedSsn;/*ssn from secs server in h*/
	struct PublicKey public_key;
	int32_t cert_revocation_list_version;
	/*
	 * The CRL contains the last 4 bytes of the
	 * cert signature = 4 last bytes of a x509 file.
	 */
	struct sake_ext_functions funcs; /* Ext functions required by SAKE */
	int32_t cert_revocation_list_len;
	uint8_t (*cert_revocation_list)[CRL_ENTRY_SIZE];
};

/* utility functions */
void deinit_public_key(struct PublicKey *public_key);

#endif /* SAKE_ENGINE_INTERNAL_H_ */

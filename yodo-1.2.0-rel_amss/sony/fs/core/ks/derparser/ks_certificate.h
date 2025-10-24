/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KS_CERTIFICATE_H_
#define _KS_CERTIFICATE_H_

#include <stdint.h>

/* KeyStoreCertificate */
struct ks_certificate {
	uint32_t size;
	uint8_t *buf;
};

#endif /* _KS_CERTIFICATE_H_ */


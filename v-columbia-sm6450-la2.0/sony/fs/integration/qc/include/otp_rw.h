/*
 * Copyright (C) 2013 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef OTP_RW_H_
#define OTP_RW_H_

#include <stdint.h>
/*
 * This file defines the hw specific fuse interface
 * The interface is not thread safe
 */

/* defines for otp_rw_entry.flags */
#define OTP_RW_READ             0
#define OTP_RW_BURN_FEC         1
#define OTP_RW_BURN_NO_FEC      2
#define OTP_RW_BURN_RAND_FEC    3
#define OTP_RW_BURN_RAND_NO_FEC 4

struct otp_rw_entry {
	uint32_t flags;
	uint32_t addr;
	uint32_t data[2];
};

int otp_rw_init(void);
void otp_rw_final(void);

/*
 * otp_data must be 8 bytes
 */
int otp_read_row(uint32_t otp_addr, uint32_t *otp_data);
/*
 * Write a complete config
 */
int otp_write_cfg(const void *buf, const int len);

#endif

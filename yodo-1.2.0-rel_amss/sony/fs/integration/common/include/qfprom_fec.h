/******************************************************
 *              ____                                  *
 *             / ___|  ___  _ __  _   _               *
 *             \___ \ / _ \| '_ \| | | |              *
 *              ___) | (_) | | | | |_| |              *
 *             |____/ \___/|_| |_|\__, |              *
 *                                |___/               *
 *                                                    *
 ******************************************************
 * Copyright (C) 2012 Sony Mobile Communications Inc. *
 * All rights, including trade secret rights, reserved*
 ******************************************************
 */

#ifndef QFPROM_FEC_H_
#define QFPROM_FEC_H_

#include <stdint.h>
#include <stdbool.h>

uint64_t add_fec_63_56(uint64_t data);

bool otp_flip_bit_check(uint32_t *otp_read, uint32_t *otp_target);

#endif /* QFPROM_FEC_H_ */

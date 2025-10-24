/******************************************************
 *               ____                                  *
 *              / ___|  ___  _ __  _   _               *
 *              \___ \ / _ \| '_ \| | | |              *
 *               ___) | (_) | | | | |_| |              *
 *              |____/ \___/|_| |_|\__, |              *
 *                                 |___/               *
 *                                                     *
 *******************************************************
 *  Copyright (C) 2012 Sony Mobile Communications Inc. *
 * All rights, including trade secret rights, reserved *
 ******************************************************/

#include <stdbool.h>
#include "qfprom_fec.h"

/*
 * Local functions
 */
static uint_fast8_t fec_parity_63_56(uint64_t data);
static bool bitsum_mod2_64(uint64_t data);

uint64_t add_fec_63_56(uint64_t data)
{
	uint64_t fec = 0;
	const uint64_t fec_mask = 0x00FFFFFFFFFFFFFF;

	/* Clear fec if it is there (shouldn't be) */
	data &= fec_mask;

	fec = fec_parity_63_56(data);

	fec <<= 56;
	data |= fec;

	return data;
}

static uint_fast8_t fec_parity_63_56(uint64_t data)
{
#define parity_width_63_56 7
	/*
	 * 80-N2003-1_C_QFPROM_programming.pdf
	 * Table 2.1 "63/56 Hammingcode Code Parity"
	 * transposed F matrix
	 */
	const uint64_t Ft[parity_width_63_56] = {
		0xFBCEB0B8DA44CA,
		0x7DE7585C6D2265,
		0xC53D1C96ECD5F8,
		0x629E8E4B766AFC,
		0x314F4725BB357E,
		0x18A7A392DD9ABF,
		0xF79D6171B48995};
	unsigned int i;
	uint64_t row = 0;
	uint_fast8_t code = 0;

	for (i = 0; i < parity_width_63_56; i++) {
		code <<= 1;
		row = Ft[i] & data;
		if (bitsum_mod2_64(row))
			code |= 1;
	}

	return code;
}

static bool bitsum_mod2_64(uint64_t data)
{
	data ^= (data >> 32);
	data ^= (data >> 16);
	data ^= (data >> 8);
	data ^= (data >> 4);
	data ^= (data >> 2);
	data ^= (data >> 1);

	return (data & 1);
}

bool otp_flip_bit_check(uint32_t *otp_read, uint32_t *otp_target)
{
	unsigned int loop = 0;
	uint32_t tmp = 0;

	for (loop = 0 ; loop <= 1 ; loop++) {
		tmp = ~otp_target[loop];
		tmp = tmp & otp_read[loop];

		if (tmp)
			return false;
	}

	return true;
}

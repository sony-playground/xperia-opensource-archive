#ifndef SAKE_ROOT_H
#define SAKE_ROOT_H
/*
 * Copyright (C) 2015 Sony Mobile Communications AB.
 * All rights, including trade secret rights, reserved.
 */
struct  sake_setup {
	uint8_t pub_hash[4];
	uint8_t rsa_pub_key[270];
	uint8_t crl[14];
};

/* TODO: Replace with real data */
const struct sake_setup sake_data_test = /* test */ {
	{ 0x00 },
	{ 0x00 },
	{ 0x00 }
};

/* TODO: Replace with real data */
const struct sake_setup sake_data_live = {
	{ 0x00 },
	{ 0x00 },
	{ 0x00 }
};
#endif /* SAKE_ROOT_H */

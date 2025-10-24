/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KeyStore_H_
#define _KeyStore_H_

#include <decoder.h>
#include <string.h>
#include <stdint.h>

#include "ks_main.h"

extern asn_TYPE_descriptor_t asn_DEF_KeyStore;

/* KeyStore typedefs for keystore.c */
typedef struct ks_main KeyStore_t;
typedef struct ks_entry KeyStoreEntry_t;

#endif /* _KeyStore_H_ */


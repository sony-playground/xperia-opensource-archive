/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_TRANSPORT_H_
#define FCS_TRANSPORT_H_

#include <stdint.h>

struct transport;

/*
 * Open connection. It is assumed that the implementation of this interface can
 * retrieve parameters needed.
 */
struct transport *tr_open(void);

/*
 * Close connection and free up resources.
 */
void tr_close(struct transport *handle);

/*
 * Read data from transport interface.
 * The input handle is implementation defined.
 */
int tr_read(struct transport *handle, uint8_t *data_p, size_t size);

/*
 * Write data from USB interface. The input handle is implementation defined.
 */
int tr_write(struct transport *handle, uint8_t *data_p, size_t size);

/*
 * Returns how large reads you can make from tr_read
 */
size_t tr_get_max_read_size(void);

#endif

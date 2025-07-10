/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdbool.h>

#ifndef FCS_UEVENT_HANDLER_H_
#define FCS_UEVENT_HANDLER_H_

struct uevent_par {
	uint8_t battery_capacity;
};

/**
 * Set the purge on usb removal boolean.
 *
 * @param [in]  purge         If set to true, purge will be done before
 *                            powerdown on USB removal.
 */
void purge_usb_removal(bool purge);

/**
 * This will create a new thread (if not already created)
 * for handling the kernel uevents. The update_par will
 * be send as an input to the thread. If the thread is
 * created the uevent_par will be updated in the thread.
 *
 * @param [in]  update_par       Input to the uevent thread
 *
 * @returns int
 */
int uevent_handle_update(struct uevent_par update_par);

/**
 * Wait for the uevent handle thread to terminate.
 */
void uevent_thread_join(void);

#endif /* FCS_UEVENT_HANDLER_H_ */

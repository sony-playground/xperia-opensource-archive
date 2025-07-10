/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef AB_INT_H_
#define AB_INT_H_

#include <stdbool.h>

/* Interface for vendor specific A/B implementation */
int ab_set_active(char new_active_slot);
int ab_get_active(char *slot);
int ab_get_retry_count(char slot, int *count);
int ab_get_unbootable(char slot, bool *unbootable);
int ab_get_successful(char slot, bool *successful);
/* Clear successful, clear unbootable and reset retry counter */
int ab_reset_slot(char *slot);

#endif

/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright 2012 Sony Mobile Communications AB.                              *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * Description: Sake crypto algorithms                                        *
 *                                                                            *
 *****************************************************************************/

#ifndef SOMCLIB_H
#define SOMCLIB_H

#include <stdbool.h>
#include <stdint.h>

void somclib_setup();
void somclib_setup_allocation(uint8_t *base, uint32_t size);
void somclib_teardown_allocation(void);
int somclib_cmd_authenticate(
  uint8_t *buf, uint16_t *state, size_t *buf_len,
  uint16_t *sake_method, uint8_t *level);
bool somclib_is_authenticated();
int somclib_get_sake_root_id(char *buf, size_t buf_len);

#endif //SOMCLIB_H


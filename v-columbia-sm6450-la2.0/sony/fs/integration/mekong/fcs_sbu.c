/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdio.h>
#include "partman.h"
#include "fcsenv_def.h"
#include "fcs_sbu.h"

#define ADD_PART(X) {.key = X, .key_length = sizeof(X)}

/* Partitions that are affected by safe boot upgrade */

/* TODO: Specify SM33 boot partitions and add them to list */

/* Number of partitions affected by safe boot upgrade */
int num_boot_partitions;

struct sbu_list boot_partitions[] = {
};

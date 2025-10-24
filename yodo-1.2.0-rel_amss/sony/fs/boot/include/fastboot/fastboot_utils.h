/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */


/* cpoied from fcs/main/loader/protocol/fastboot.c */
#define FB_PART_LIST_SIZE (64 * 1024L)

/* copied from edk2/abl/QcomModulePkg/Library/FastbootLib/FastbootCmds.c */
#define FASTBOOT_BUFFER_SIZE (64)

/* copied from edk2/abl/QcomModulePkg/Library/FastbootLib/FastbootCmds.c */
#define GETVAR_VALUE_SIZE (FASTBOOT_BUFFER_SIZE - 4 + 1)

/* copied from edk2/abl/QcomModulePkg/Library/FastbootLib/FastbootCmds.h */
#define MAX_GET_VAR_NAME_SIZE 32


#define FB_VERSION "0.4"
#define FB_SONY_VERSION "0.54"

/* Fastboot Variable list */
typedef struct _X_FASTBOOT_VAR {
  struct _X_FASTBOOT_VAR *next;
  char name[MAX_GET_VAR_NAME_SIZE];
  char value[GETVAR_VALUE_SIZE];
} X_FASTBOOT_VAR;

int fastboot_add_func(const char *name, int (*func)(char *val));

int fastboot_get_variable(const char *getvar_var_name, char *value);

int fastboot_get_x_variable_list(X_FASTBOOT_VAR **x_fastboot_var);

void fastboot_x_variable_list_free(X_FASTBOOT_VAR *x_fastboot_var);

int extract_partition_and_unit(const uint8_t *arg,
                                uint8_t *partition,
                                uint32_t *unit);

void fastboot_init_getvar(void);

int fastboot_get_loaderversion(char *val);

bool fastboot_get_secure(void);


/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_STORAGE_RAM_H_
#define FCS_STORAGE_RAM_H_

struct storage_ctx *storage_ram_open(const char *dev, const char *name);

int storage_ram_unlink(const char *dev, const char *name);

struct storage_dir *storage_ram_opendir(const char *dev);

#endif

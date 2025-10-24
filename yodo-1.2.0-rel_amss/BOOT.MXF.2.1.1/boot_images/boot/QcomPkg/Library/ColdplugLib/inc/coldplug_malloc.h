/***********************************************************************
 * Coldplug Malloc Module.
 *
 * Coldplug
 * Copyright (C) 2020 QUALCOMM Technologies, Inc.
 *
 * Coldplug Malloc functions.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2020-11-16   rp    Create

 ===========================================================================*/

#ifndef __COLDPLUG_MALLOC_H__
#define __COLDPLUG_MALLOC_H__

#include "coldplug_config.h"
#include "coldplug_comdef.h"

void coldplug_malloc_init(void);
void* coldplug_malloc(uint32 size);
void coldplug_free(void *ptr);

#endif


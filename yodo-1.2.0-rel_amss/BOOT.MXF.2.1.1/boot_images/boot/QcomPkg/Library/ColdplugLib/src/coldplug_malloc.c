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

#include "coldplug_malloc.h"
#include "coldplug_assert.h"
#include "DALSys.h"

#include <string.h>

struct coldplug_malloc_stats_type {
	uint32 malloc_calls_count;
	uint32 free_calls_count;
	uint32 malloc_calls_fail_count;
	uint32 malloc_size_total;
	uint32 malloc_size_fail_total;
};
static struct coldplug_malloc_stats_type coldplug_malloc_stats;


void coldplug_malloc_init(void)
{
	memset(&coldplug_malloc_stats, 0, sizeof(coldplug_malloc_stats));
}

void* coldplug_malloc(uint32 size)
{
	DALResult result;
	void *ptr = NULL;

	result = DALSYS_Malloc(size, &ptr);
	if (result != DAL_SUCCESS) {
		++coldplug_malloc_stats.malloc_calls_fail_count;
		coldplug_malloc_stats.malloc_size_fail_total += size;
		return NULL;
	}

	++coldplug_malloc_stats.malloc_calls_count;
	coldplug_malloc_stats.malloc_size_total += size;
	return ptr;
}

void coldplug_free(void *ptr)
{
	DALResult result;

	COLDPLUG_ASSERT(ptr != NULL);

	result = DALSYS_Free(ptr);
	COLDPLUG_ASSERT(result == DAL_SUCCESS);
	(void) result;

	COLDPLUG_ASSERT(coldplug_malloc_stats.free_calls_count <
			coldplug_malloc_stats.malloc_calls_count);
	++coldplug_malloc_stats.free_calls_count;
}



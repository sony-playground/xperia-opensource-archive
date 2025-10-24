// Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.

#ifndef __HEAP_H
#define __HEAP_H

#include <Library/MemoryAllocationLib.h>

#define HEAP_ZALLOC_TYPE(ty)      ((ty *) AllocateZeroPool(sizeof(ty)))

#define HEAP_ZALLOC_ARRAY(ty, k)  ((ty *) AllocateZeroPool(sizeof(ty)*(k)))

#define HEAP_FREE_PTR(var)        ((void) (FreePool(var), (var) = 0))

#endif // __HEAP_MEM_H

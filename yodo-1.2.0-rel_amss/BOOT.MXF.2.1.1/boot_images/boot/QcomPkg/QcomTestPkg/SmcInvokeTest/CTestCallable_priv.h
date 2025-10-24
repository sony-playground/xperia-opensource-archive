// Copyright (c) 2017, 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.

#ifndef CTESTCALLABLE_PRIV_H
#define CTESTCALLABLE_PRIV_H

#include <stdint.h>
#include <stddef.h>
#include "object.h"

typedef struct {
  int refs;
  size_t counter;
  int32_t op;
  int32_t retValue;
  int32_t retValueError;
  Object oArg;
  Object oOOArg;
  Object oOOArg0;
  Object oOOArg1;
  Object oOOArg2;
  void *bArg_ptr;
  size_t bArg_len;
} TestCallable;

#endif //CTESTCALLABLE_PRIV_H

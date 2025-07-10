/*===========================================================================

  Copyright (c) 2014, Qualcomm Technologies, Inc.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#ifndef KVP_H
#define KVP_H

#include <bytearray_common.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define       MAX_KVP_LENGTH    100

struct kvp_s
{
    bytearray_t *buffer;
    unsigned     read_idx;
};

typedef struct kvp_s kvp_t;

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // KVP_H


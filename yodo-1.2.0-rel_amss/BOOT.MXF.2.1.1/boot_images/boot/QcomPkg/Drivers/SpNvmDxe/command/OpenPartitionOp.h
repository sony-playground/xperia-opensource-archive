/*========================================================================
OpenPartitionOp.h
This file describes the Open partition operation class.

Copyright (c) 2020 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================*/
/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/09/20   ll      initial release
=============================================================================*/
#ifndef OPENPARTITIONOP_H_
#define OPENPARTITIONOP_H_

#include "Operation.h"
/**
 * This struct defines the open partition operation
 */
void *   OpenPartitionOp_new(va_list ap);
void     OpenPartitionOp_delete(void * _self);
int32_t  OpenPartitionOp_getRspSize();
int      OpenPartitionOp_execute(void * _self, void* rspBuffer, uint32_t rspSize, void * _mng);
int      OpenPartitionOp_get_is_skp(void * _self);
int      OpenPartitionOp_get_is_ari(void * _self);
uint8_t* OpenPartitionOp_get_marker(void * _self);
void     OpenPartitionOp_set_marker(void * _self, uint8_t* marker);

/**
 * This struct defines the is commit done operation
 */
struct OpenPartitionOp {
    const void * Operation;

    boolean     m_is_skp;
    boolean     m_is_ari;
    uint8_t*    m_marker;

    open_partition_req_t* m_req;
    open_partition_rsp_t* m_rsp;
    uint32_t m_segSizes[MAX_SEGS];
};
#endif /* OPENPARTITIONOP_H_ */





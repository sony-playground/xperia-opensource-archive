/*========================================================================
CreatePartitionOp.h
This file describes the create partition operation class.

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
#ifndef CREATEPARTITIONOP_H_
#define CREATEPARTITIONOP_H_

#include "Operation.h"


void *   CreatePartitionOp_new(va_list ap);
void     CreatePartitionOp_delete(void * _self);
int32_t  CreatePartitionOp_getRspSize();
int      CreatePartitionOp_execute(void * _self, void* rspBuffer, uint32_t rspSize, void * _mng);
int      CreatePartitionOp_get_is_skp(void * _self);
int      CreatePartitionOp_get_is_ari(void * _self);
uint8_t* CreatePartitionOp_get_marker(void * _self);
void     CreatePartitionOp_set_marker(void * _self,  uint8_t* marker);

/**
 * This struct defines the create partition operation
 */
struct CreatePartitionOp {
    const void * Operation;

    boolean     m_is_skp;
    boolean     m_is_ari;
    uint8_t*    m_marker;

    create_partition_req_t* m_req;
    create_partition_rsp_t* m_rsp;
    uint32_t m_segSizes[MAX_SEGS];
};

#endif /* CREATEPARTITIONOP_H_ */





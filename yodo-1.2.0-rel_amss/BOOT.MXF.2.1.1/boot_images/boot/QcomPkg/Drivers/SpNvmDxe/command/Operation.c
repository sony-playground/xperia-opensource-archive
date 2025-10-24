/*========================================================================
Operation.c
This file describe the implementation of the IsCommitOp class.

Copyright (c) 2021 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================*/
/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/29/21   vp      Logging improvements
 03/09/20   ll      initial release
=============================================================================*/
#include "Operation.h"
#include <assert.h>

void DefaultOp_ctor(struct Operation * self, void* req)
{
    (void)self;
    (void)req;
    LOGI("DefaultOp--Command from SPU not supported");
}


int32_t DefaultOp_getRspSize()
{
    LOGI("DefaultOp--Command from SPU not supported");
    return -1;
}


int DefaultOp_execute(void * _self, void*  rspBuffer, uint32_t rspSize, void* _mng)
{
    LOGI("DefaultOp--Command from SPU not supported");
    (void)_self;
    (void)rspBuffer;
    (void)rspSize;
    (void)_mng;
    return -1;
}


int DefaultOp_get_is_skp(void * _self)
{
    (void)_self;
    LOGI("DefaultOp--get_is_skp");
    return -1;
}


int DefaultOp_get_is_ari(void * _self)
{
    (void)_self;
    LOGI("DefaultOp--get_is_ari");
    return -1;
}


uint8_t* DefaultOp_get_marker(void * _self)
{
    (void)_self;
    LOGI("DefaultOp--get_marker");
    return NULL;
}


void DefaultOp_set_marker(void * _self,  uint8_t* marker)
{
    (void)_self;
    (void)marker;
    LOGI("DefaultOp--set_marker");
}


void DefaultOp_delete(void * _self){
     (void)_self;
     //do nothing
     LOGI("DefaultOp--Command from SPU not supported");
}


void * DefaultOp_new(va_list ap){

    LOGI("DefaultOp--Command from SPU not supported");
    return NULL;
}

//New Operation
void * newOperation (const void * operation, ...)
{ 
    const struct Operation * op = operation;
    LOGI("newOperation, op[0x%x], opgetRspSize[0x%x]\n", op, op->getRspSize);
    va_list ap;
    void * result;

    ASSERT(operation && op->new);
    va_start(ap, operation);
    result =  op->new(ap);
    * (const struct Operation **) result = operation;
    va_end(ap);

    return result;
}

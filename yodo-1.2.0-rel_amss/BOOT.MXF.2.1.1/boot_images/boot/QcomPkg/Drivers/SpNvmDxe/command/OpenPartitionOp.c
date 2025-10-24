/*========================================================================
OpenPartitionOp.c
This file describe the implementation of the OpenPartitionOp class.

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
#include "OpenPartitionOp.h"
#include "SecNvmManager.h"

//pass in size?
void OpenPartitionOp_ctor(struct OpenPartitionOp * self, void* req)
{
   self->m_req = (open_partition_req_t*)req;

   memset(self->m_segSizes, 0, MAX_SEGS);
   switch (self->m_req->reqId) {
        case OPEN_PARTITION_REQUEST:
        case EXT_OPEN_PARTITION_REQUEST:
            self->m_is_ari=true;
            break;
        case OPEN_PARTITION_ARI_SKP_REQUEST:
        case EXT_OPEN_PARTITION_ARI_SKP_REQUEST:
            self->m_is_skp = true;
            self->m_is_ari=true;
            self->m_marker = self->m_req->arc;
            break;

        default:
            LOGE("invalid request id: %d", self->m_req->reqId);
            break;
   }

   for(uint8_t i=0; (i < self->m_req->numSegs) && (i < MAX_SEGS); i++) {
       if((OPEN_PARTITION_REQUEST == self->m_req->reqId) ||
               (OPEN_PARTITION_ARI_SKP_REQUEST == self->m_req->reqId)) {
           self->m_segSizes[i] = MAX_BLOCKS_IN_SEGMENT;
       } else if((EXT_OPEN_PARTITION_REQUEST == self->m_req->reqId) ||
               (EXT_OPEN_PARTITION_ARI_SKP_REQUEST == self->m_req->reqId)) {
           self->m_segSizes[i] = ((extended_open_partition_req_t*)(self->m_req))->segSizes[i];
       }
   }

    LOGE("reqId=%d, %d segments, isAri=%d, isSkp=%d",
            self->m_req->reqId, self->m_req->numSegs, self->m_is_ari, self->m_is_skp);
}


int32_t OpenPartitionOp_getRspSize()
{
    LOGI("@@@OpenPartitionOp_getRspSize: size: %d\n", sizeof(open_partition_rsp_t));
    return sizeof(open_partition_rsp_t);
}


int OpenPartitionOp_execute(void * _self, void*  rspBuffer, uint32_t rspSize, void * _mng)
{
    LOGD("OpenPartitionOp");
    struct OpenPartitionOp * self = (struct OpenPartitionOp *)_self;
    struct SecNvmManager* mng = (struct SecNvmManager*)_mng;

    if (!rspBuffer ||(rspSize != sizeof(open_partition_rsp_t))) {
        LOGE("invalid input parameters");
        return -EINVAL;
    }

    // prepare response buffer
    self->m_rsp = (open_partition_rsp_t*)rspBuffer;
    self->m_rsp->rspId = OPEN_PARTITION_RESPONSE;
    memscpy(self->m_rsp->uuid, UUID_SIZE, self->m_req->uuid, UUID_SIZE);
    self->m_rsp->ret = NVM_SUCCESS;

    if (!self->m_req) {
        LOGE("invalid request parameters");
        self->m_rsp->ret = INVALID_MSG_PARAM;
        return 0;
    }


    if (self->m_is_ari) {
        self->m_rsp->numSegs = self->m_is_skp ? 1 : self->m_req->numSegs;
    } else {
        self->m_rsp->numSegs = (uint8_t)mng->getSegsNum(self->m_req->uuid);
        self->m_req->numSegs = self->m_rsp->numSegs; // will be used as input from SP
    }

    if (self->m_req->numSegs > MAX_SEGS) {
        LOGE("found too many segment files (%d)", self->m_req->numSegs);
        self->m_rsp->ret = CRITICAL_ERROR;
        return 0;
    }
    
    //Not checking mng lock and asym cmd ongoing for UEFI

    // allocate DDR segments, and upload segments files to the DDR
    int ret = mng->openPartition(mng, self->m_req, &(self->m_rsp->baseAddr), self->m_rsp->offsets, _self, self->m_segSizes);
    if (ret) {
        LOGE("Fail to open the partition (%d)", ret);
        switch (ret) {
           case -EEXIST:
               self->m_rsp->ret = PARTITION_ALREADY_EXIST;
               break;
           case -ENOBUFS:
               self->m_rsp->ret = NO_PARTITION_AVAILABLE;
               break;
           case -EBUSY:
               self->m_rsp->ret = SERVER_IS_BUSY;
               break;
           case -ENOENT:
               self->m_rsp->ret = PARTITION_DOESNT_EXIST;
               break;
           case -EINVAL:
               self->m_rsp->ret = INVALID_MSG_PARAM;
               break;
           case -EBADMSG:
               self->m_rsp->ret = VERIFICATION_FAIL;
               break;
           default:
               self->m_rsp->ret = CRITICAL_ERROR;
        }
    }
    return 0;
}


int OpenPartitionOp_get_is_skp(void * _self)
{
    LOGI("OpenPartitionOp--get_is_skp");
    struct OpenPartitionOp * self = (struct OpenPartitionOp *)_self;
    return self->m_is_skp;
}


int OpenPartitionOp_get_is_ari(void * _self)
{
    LOGI("OpenPartitionOp--get_is_ari");
    struct OpenPartitionOp * self = (struct OpenPartitionOp *)_self;
    return self->m_is_ari;
}


uint8_t* OpenPartitionOp_get_marker(void * _self)
{
    LOGI("OpenPartitionOp--get_marker");
    struct OpenPartitionOp * self = (struct OpenPartitionOp *)_self;
    return self->m_marker;
}


void OpenPartitionOp_set_marker(void * _self,  uint8_t* marker)
{
    LOGI("OpenPartitionOp--set_marker");
    struct OpenPartitionOp * self = (struct OpenPartitionOp *)_self;
    self->m_marker = marker;
}


void OpenPartitionOp_delete(void * _self){
     (void)_self;
     //do nothing
}


void * OpenPartitionOp_new(va_list ap){

    void *req = va_arg(ap, void *);
    uint32_t reqSize = va_arg(ap, uint32_t);

    if (!req || (sizeof(open_partition_req_t) > reqSize)) {
        LOGE("Invalid request buffer");
        return NULL;
    }

    open_partition_req_t* open_req =  (open_partition_req_t*)req;
    if((EXT_OPEN_PARTITION_REQUEST == open_req->reqId) ||
                   (EXT_OPEN_PARTITION_ARI_SKP_REQUEST == open_req->reqId)) {
        if(reqSize < sizeof(extended_open_partition_req_t)) {
            LOGE("invalid request buffer");
            return NULL;
        }
    }
    //Allocate the IsCommitOp object
    struct OpenPartitionOp * openPartitionOp = (struct OpenPartitionOp *)nvm_os_malloc(sizeof(struct OpenPartitionOp));
    ASSERT(openPartitionOp);

    //Call constructor
    OpenPartitionOp_ctor(openPartitionOp, req);
    return openPartitionOp;
}



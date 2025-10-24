/*========================================================================
SecNvmManager.cpp
This file describe the implementation of the SecNvmManager class.

Copyright (c) 2021 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================*/
/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/29/21   vp      Logging improvements
 05/19/21   vp      Minimize Log Prints for Open Partition failure
 02/16/21   vp      Track secnvmmanager state for app partition too.
 02/08/21   vp      Fix for bug in setting marker_length of app partition
 03/09/20   ll      initial release
=============================================================================*/
#include "SecNvmManager.h"
#include "Commands.h"
#include "CreatePartitionOp.h"
#include "OpenPartitionOp.h"
#include "CommitOp.h"
#include "IsCommitOp.h"

#include "osCommon.h"
#include "stringl/stringl.h"  // strnlen()

#include <Uefi.h>
#include <PrintShLib.h>
#include <stdio.h>  // printf(); MIN()
#include <stdint.h>		// size_t
#include <stdarg.h>		// va_arg()
#include <stdbool.h>	// bool , true , false
#include <string.h>		// memset()
#include <Library/MemoryAllocationLib.h>
#include "QcomLib.h"
#include <Library/UefiBootServicesTableLib.h>

/**
 Protocol Dependencies
 */
#include <Protocol/EFISpcom.h>

EFI_SPCOM_PROTOCOL * spcom_protocol;

//class descriptor for NvmSegment
static const struct Class _NvmSegment = {
      sizeof(struct NvmSegment),
      NvmSegment_ctor, 
      NULL
};

void SecNvmManager_receiveRequests_cb(struct spcom_server*, const void* reqBuffer, size_t reqSize, void** rspBuffer_pptr, size_t *const rspSize_ptr, void * server_param);

/* Internal functions */
inline static void resetNvmManagerState(struct SecNvmManager * self) {
      LOGI("reset m_state to SEC_NVM_INIT_STATE");
      self->m_state = SEC_NVM_INIT_STATE;
}

inline static int setNvmManagerState(struct SecNvmManager * self, sec_nvm_request_id_t reqId, bool is_skp)
{
      if (self == NULL){
         LOGD("%s: Invalid SecNvmManager reference", __func__);
         return -EINVAL;
      }

      if (self->m_state == SEC_NVM_INIT_DONE_STATE) {
         LOGD("%s: is_skp:%d, reqId:%d, m_state=%d",
              __func__, is_skp, reqId, self->m_state);
         return 0;
      }
      LOGI("%s: is_skp:%d, reqId:%d, m_state=%d\n",
              __func__, is_skp, reqId, self->m_state);
      // move to the next state
      switch (reqId) {
      case CREATE_PARTITION_REQUEST :
      case EXT_CREATE_PARTITION_REQUEST:
      case CREATE_PARTITION_ARI_SKP_REQUEST:
      case EXT_CREATE_PARTITION_ARI_SKP_REQUEST:
         if (self->m_state != SEC_NVM_INIT_STATE)
            LOGI("wrong state (reqId:%d, m_state=%d)", reqId, self->m_state);
         self->m_state = SEC_NVM_CREATE_STATE;
         break;

      case OPEN_PARTITION_REQUEST:
      case EXT_OPEN_PARTITION_REQUEST:
      case OPEN_PARTITION_ARI_SKP_REQUEST:
      case EXT_OPEN_PARTITION_ARI_SKP_REQUEST:
         if (self->m_state != SEC_NVM_INIT_STATE)
            LOGI("wrong state (reqId:%d, m_state=%d)", reqId, self->m_state);
         self->m_state = SEC_NVM_OPEN_STATE;
         break;

      case COMMIT_REQUEST:
      case COMMIT_ARI_SKP_REQUEST:
         if ((self->m_state != SEC_NVM_OPEN_STATE) &&
             (self->m_state != SEC_NVM_CREATE_STATE))
            LOGI("wrong state (reqId:%d, m_state=%d)", reqId, self->m_state);
         if (self->m_state == SEC_NVM_OPEN_STATE)
            self->m_state = SEC_NVM_INIT_DONE_STATE;
         else if (self->m_state == SEC_NVM_CREATE_STATE) //first commit
            self->m_state = SEC_NVM_CREATE_DONE_STATE;
         else if (self->m_state == SEC_NVM_CREATE_DONE_STATE) //second commit
            self->m_state = SEC_NVM_INIT_DONE_STATE;
         break;

      case IS_COMMIT_REQUEST:
         break;

      default:
         LOGE("wrong request id:%d, m_state=%d", reqId, self->m_state);
         return -EINVAL;
      }
      return 0;
}

inline static int32_t getSegmentsCount(struct SecNvmManager * self) {
      return self->m_segmentsCount;
}


inline static bool isSegmentsEmpty(struct SecNvmManager * self) {
      return self->m_segmentsCount == 0;
}


inline static int32_t addSegment(struct SecNvmManager * self, struct NvmSegment* seg) {
      LOGI("SecNvmManager in addSegment\n");
      if (self->m_segmentsCount < MAX_SEGS && NULL != seg) {
         self->m_segments[self->m_segmentsCount] = seg;
         self->m_segmentsCount++;
         LOGI("self->m_segmentsCount= 0x%d\n", self->m_segmentsCount);
         return self->m_segmentsCount-1;
      }
      return -1;
}


static char* uuidToStr(uint8_t uuid[], char* uuidStr, size_t uuidStrSize)
{
    size_t written;

    if (!uuidStr || uuidStrSize < 1) {
        LOGE("incorrect UUID string paremeters");
        return NULL;
    }

    for (uint32_t i = 0; i < UUID_SIZE; i++) {
        written = snprintf(uuidStr, uuidStrSize, "%u", uuid[i]);
        if (written > 0 && written < uuidStrSize){
           uuidStrSize -= written;
           uuidStr += written;
        }else {
           LOGE("Insufficient Buffer size");
           return NULL;
        }
    }
    return uuidStr;
}


static int setUuid(struct SecNvmManager * self, uint8_t uuid[])
{
    // uuid must not change after first call
    if (self->m_uuid) {
        if (0 == memcmp(self->m_uuid, uuid, UUID_SIZE)) {
            return 0;
        }
        LOGE("UUID redefinition");
        return -EINVAL;
    } else  {
        self->m_uuid = (uint8_t*)nvm_os_malloc(UUID_SIZE);
        if (!self->m_uuid) {
            LOGE("UUID allocation failed");
            return -ENOMEM;
        }
        memcpy(self->m_uuid, uuid, UUID_SIZE);
    }

    if (!uuidToStr(uuid, self->m_uuidStr, UUID_STR_SIZE)) {
        LOGE("unable to convert UUID to a string");
        return -ENOMEM;
    }

    return 0;
}


static void clearUuid(struct SecNvmManager * self)
{
    if (self->m_uuid) {
        nvm_os_free(self->m_uuid);
        self->m_uuid = NULL;
    }
    self->m_uuidStr[0] = 0;
}


static void resetSegments(struct SecNvmManager * self, void * ionPtr, uint32_t ionSize)
{
    for (int32_t i = 0; i < getSegmentsCount(self); i++) {
        if (self->m_segments[i]) {
           //call destructor for segment delete self->m_segments[i].delete();
           nvm_os_free(self->m_segments[i]);
           self->m_segments[i] = NULL;
        }
    }
    self->m_segmentsCount = 0;
    if (ionPtr != NULL && ionSize != 0) {
        //spcom_protocol->SpcomFree(self->m_channelName, ionPtr, (size_t)ionSize);
    }

}

uint8_t* getOpMarker(void * cmd, uint8_t* cmac, uint8_t* counter)
{
    struct Operation* op = NULL; 

    if (cmd == NULL) {
        LOGE("!!! cmd ptr NULL !!!");
        return NULL;
    }
    op = *(struct Operation **)cmd;

    if (!op) {
        LOGE("!!! op ptr NULL !!!");
        return NULL;
    }

    if (op->get_is_ari((void *)cmd)) {
        if (!op->get_is_skp((void *)cmd)) {
            LOGI("ari, no-skp: marker points to req CMAC");
            return cmac;
        }
        else {
            // marker for ari+skp combination is defined in the Operation constructor
            LOGI("ari, skp: marker points to req ARC");
        }
    }
    else {
        LOGE("no-ari: marker points to a counter: %d", *counter);
        return counter;
    }
    return op->get_marker((void *)cmd);
}

static const struct Operation _CreatePartitionOp = {
    CreatePartitionOp_new, 
    CreatePartitionOp_delete,
    CreatePartitionOp_getRspSize,
    CreatePartitionOp_execute,
    CreatePartitionOp_get_is_skp,
    CreatePartitionOp_get_is_ari,
    CreatePartitionOp_get_marker,
    CreatePartitionOp_set_marker
};

static const struct Operation _OpenPartitionOp = {
    OpenPartitionOp_new, 
    OpenPartitionOp_delete,
    OpenPartitionOp_getRspSize,
    OpenPartitionOp_execute,
    OpenPartitionOp_get_is_skp,
    OpenPartitionOp_get_is_ari,
    OpenPartitionOp_get_marker,
    OpenPartitionOp_set_marker
};

static const struct Operation _CommitOp = {
    CommitOp_new, 
    CommitOp_delete,
    CommitOp_getRspSize,
    CommitOp_execute,
    CommitOp_get_is_skp,
    CommitOp_get_is_ari,
    CommitOp_get_marker,
    CommitOp_set_marker
};

static const struct Operation _IsCommitOp = {
    IsCommitOp_new, 
    IsCommitOp_delete,
    IsCommitOp_getRspSize,
    IsCommitOp_execute,
    IsCommitOp_get_is_skp,
    IsCommitOp_get_is_ari,
    IsCommitOp_get_marker,
    IsCommitOp_set_marker
};

static const struct Operation _DefaultOp = {
    DefaultOp_new, 
    DefaultOp_delete,
    DefaultOp_getRspSize,
    DefaultOp_execute,
    DefaultOp_get_is_skp,
    DefaultOp_get_is_ari,
    DefaultOp_get_marker,
    DefaultOp_set_marker
};


struct Operation* createOp(int8_t* req, uint32_t reqSize)
{
   struct Operation* op;
   const struct Operation* factoryTable[] = {
        &_CreatePartitionOp,
        &_OpenPartitionOp,
        &_CommitOp,
        &_DefaultOp, //AbortOp not supported
        &_DefaultOp, //AsyncCommitOp not supported
        &_IsCommitOp,

        // SKP sequences handled by apps operations objects
        &_CreatePartitionOp,
        &_OpenPartitionOp,
        &_CommitOp,

        //extended request
        &_CreatePartitionOp,
        &_OpenPartitionOp,

        //extended request - SKP
        &_CreatePartitionOp,
        &_OpenPartitionOp,

        // GET_SBDB_ADDR_REQUEST and LOOKUP_SBAPP_REQUEST
        &_DefaultOp, //ScratchBufferOp for GET_SBDB_ADDR_REQUEST not supported
        &_DefaultOp  //ScratchBufferOp for LOOKUP_SBAPP_REQUEST not supported
   };

   if (!req) {
      LOGE("undefined operation request");
      return NULL;
   }

   if (req[0] >= REQUEST_MAX_SIZE) {
      LOGE("invalid operation request reqId=%d", req[0]);
      return NULL;
   }

   sec_nvm_request_id_t reqId = (sec_nvm_request_id_t)req[0];

   op = newOperation(factoryTable[reqId], req, reqSize);
   return op;
}


int SecNvmManager_startSpcomServer(struct SecNvmManager * self) {
    EFI_STATUS ret = EFI_SUCCESS;
    struct spcom_service_info serviceInfo;
    
    if (spcom_protocol == NULL)
    {
        EFI_STATUS status;

        status = gBS->LocateProtocol (&gEfiSpcomProtocolGuid, NULL,
                                    (void**) &(spcom_protocol));
        if (status != EFI_SUCCESS)
        {
           LOGE("LocateProtocol, gEfiSpcomProtocolGuid %r", status);
           return -ENODEV;
        }
    }
	
    ret = spcom_protocol->IsSpssLinkUp();
	 if (ret != EFI_SUCCESS) {
		 LOGE("SPSS is not up, received timeout");
		 return -ENODEV;
	 }

    memset(&serviceInfo, 0, sizeof(struct spcom_service_info));
    serviceInfo.ch_name = self->m_channelName;
    serviceInfo.notify_server_request_cb = SecNvmManager_receiveRequests_cb;
    serviceInfo.server_param = self; //Passing in the SecNvmManager object
	
    LOGI("register spcom service, channel:%a",serviceInfo.ch_name);
    ret = spcom_protocol->RegisterService(&serviceInfo, &(self->m_spcomServer));
    if (ret != EFI_SUCCESS) {
        LOGE("can't register spcom service [%a]", serviceInfo.ch_name);
        return -ENODEV;
    }
    return 0;
}

EFI_STATUS SecNvmManager_receiveRequests(struct SecNvmManager * self)
{
    EFI_STATUS ret = EFI_SUCCESS;

    if (!self || !(self->m_spcomServer)) {
        LOGE("invalid input");
        return -EINVAL;
    }

    // listen to SP NVM requests
    ret = spcom_protocol->ServerGetNextRequest(self->m_spcomServer);

    return ret;
}


void SecNvmManager_receiveRequests_cb(struct spcom_server * server_handle, const void* reqBuffer, size_t reqSize, void** rspBuffer_pptr, size_t * rspSize_ptr, void * server_param) {

    int8_t* rspBuffer = NULL;
    struct Operation* op = NULL;
    void * cmd = NULL;
    int ret = 0;
    int rspSize = 0;
    int8_t* reqBuffer_int8 = (int8_t*)reqBuffer;
    struct SecNvmManager * mng = NULL;

    if (!server_handle || !reqBuffer || !rspBuffer_pptr || !rspSize_ptr) {
        LOGE("Invalid input param \n");
        return;
    }
    mng = (struct SecNvmManager *)server_param;
    cmd = createOp((int8_t*)reqBuffer, reqSize);
    if (!cmd) {
        LOGE("fail to create operation cmd \n" );
        return;
    }
    op = *(struct Operation **)cmd;
    if (!op) {
        LOGE("operation ptr is NULL\n" );
        return;
    }

    rspSize = op->getRspSize();

    rspBuffer = (int8_t*)nvm_os_malloc(rspSize);
    if (!rspBuffer) {
        LOGE("fail to allocate response buffer (%d bytes)\n", rspSize);
        return;
    }

    memset(rspBuffer, 0, rspSize);

    ret = op->exec(cmd, rspBuffer, rspSize, mng);
    if (ret < 0) {
        LOGE("fail to execute operation (%d)\n", ret);
        goto clean_after_error;
    }
    *rspBuffer_pptr = rspBuffer;
    *rspSize_ptr    = rspSize;

    ret = setNvmManagerState(mng,(sec_nvm_request_id_t)reqBuffer_int8[0], op->get_is_skp((void *)cmd));
    if (ret < 0) {
       LOGE("fail to update service state (%d)", ret);
       goto clean_after_error;
    }

    LOGI("receiveRequests_cb Done reqid: %d\n", reqBuffer_int8[0]);

    return;
clean_after_error:
  
    LOGI("exit ret=%d spcom loop\n", ret);
    if (rspBuffer) {
        nvm_os_free(rspBuffer);
        rspBuffer = NULL;
    }
    if (op) {
        nvm_os_free(op);
        op = NULL;
    }
}

//testCode
int SecNvmManager_loadNvmAppTest(struct SecNvmManager * self) {
     EFI_STATUS ret = EFI_SUCCESS;
     size_t load_app_resp;

     //load nvmTestApp via spcom then App will send create partion. who will trigger the read?
     EFI_GUID enterpriseFvGuid = { 0xB7524B2D, 0x0A91, 0x49A2, { 0xAA, 0x5E, 0xBD, 0xA2, 0x66, 0x69, 0x9D, 0x49 } };  

     /*
     * Size of "\\sundae\secproc_sw_dropbox\vparth\spcomdxe_boot_changes_493\asymw2t.sig" is 20624 bytes
     */
     ret = spcom_protocol->LoadSpApp("nvm_noheap", &enterpriseFvGuid, 20976, 64 * 1024, &load_app_resp);
     if(ret != EFI_SUCCESS)
     {
        LOGE("Failed to load echoapp: %d, spu returned %d\n", ret, load_app_resp);
     }

     for (uint32_t i = 0; i < 6; i++) {
       ret = SecNvmManager_receiveRequests(self);
       LOGI("GetRequest: %d\n", ret);
     }

     return 0;
}


// getSegsNum() function counts existing files and returns
// file name from uuid: ROOT_PATH/uuid_string_X_0
// iif exist count as valid segment
uint32_t SecNvmManager_getSegsNum(uint8_t uuid[])
{
    uint32_t    numSegs = 0;
    char        filename[FILE_NAME_SIZE];
    char        uuidStr[UUID_STR_SIZE];
    size_t      left_size = FILE_NAME_SIZE;
    uint32_t    written = 0;
    char*       pname;

    if (!uuidToStr(uuid, uuidStr, UUID_STR_SIZE)) {
        LOGE("unable to convert UUID to a string");
        return 0;
    }

    while (numSegs < MAX_SEGS) {
        left_size = FILE_NAME_SIZE;
        pname = filename;
        //pname += snprintf(pname, left_size, "%s", ROOT_PATH);
        written = snprintf(pname, left_size, "%s", ROOT_PATH);
        if (written > 0 && written < left_size){
          left_size -= sizeof(ROOT_PATH);
          pname += written;
        }else {
          LOGE("Insufficient Buffer size");
          return 0;
        }

        written = snprintf(pname, left_size, "%s_%u_0",
                uuidStr, numSegs);

        if (written > 0 && written < left_size){
          LOGI("checking file:%a", filename);
        }else {
          LOGE("Insufficient Buffer size");
          return 0;
        }

        // check that file exist
        osfd_t fd = os_open_segment_file((const char*)filename, OS_O_RDONLY);
        if (OS_IS_FD_INVALID(fd)) {
            LOGE("found %d segments, file %a doesn't exist", numSegs, filename);
            break;
        }
        numSegs++;
    }

    LOGI("found %d segments", numSegs);

    return numSegs;
}


int SecNvmManager_allocatePartition(
    struct SecNvmManager * self,
    create_partition_req_t *req,
    create_partition_rsp_t *rsp,
    uint64_t * baseAddr_ptr,
    uint32_t out_offsets[],
    void * cmd,
    uint32_t segsSize[])
{
    int ret = 0;
    uint32_t totalSize = 0;
    struct Operation* op = NULL; 
    void * baseAddr_32b;
    //only allow 1 SegDb segment and 1 sTPM-lite Data segment
    //Is there usecase for more segment for Data for UEFI?
    //If so, we can expand.
    if (!cmd || !req || !rsp || !out_offsets || req->numSegs > MAX_SEGS) {
        LOGE("NULL input parameters or request too many segments");
        return -EINVAL;
    }

    op = * (struct Operation **)cmd;

    if (op == NULL) {
        LOGE("!!! op ptr NULL !!!");
        return -EINVAL;
    }
    // uuid must not change after first call
    ret = setUuid(self, req->uuid);
    if (ret) {
        LOGE("Invalid UUID");
        return -EINVAL;
    }

    // clear the old partition data segments
    if(!isSegmentsEmpty(self)) {
        LOGI("clear old allocated segments");
        //The ion should be deleted
        //spcom_unlock_ion_buffer(m_channelName, m_ionHandle.fd);
        resetSegments(self, NULL, 0);
    }

    struct NvmSegment* seg = NULL;
    // create the NvmSegment objects vector. UEFI should only have 1 NvmSegment Obj. 
    for (uint8_t i=0 ; i < req->numSegs; i++) {
        LOGI("allocate segment#%d out of %d", i, req->numSegs);

        seg = new((const void *)&_NvmSegment, i, self->m_uuidStr, segsSize[i],
              op->get_is_ari((void *)cmd), op->get_is_skp((void *)cmd));
        if (!seg) {
            LOGE("failed to allocate segment#%d", i);
            ret = -ENOMEM;
            break;
        }

        op->set_marker(cmd, getOpMarker(cmd, req->cmacs[i].cmac, seg->getCounterPtr(seg)));
        ret = seg->createSegment(seg, op->get_marker(cmd));
        if (ret) {
            LOGE("failed to create segment#%d (%d)", i, ret);
            nvm_os_free(seg);
            break;
        }

        out_offsets[i] = totalSize;

        totalSize += seg->getSegmentSize(seg);

        if (-1 == addSegment(self, seg)) {
            LOGE("failed to store segment#%d (%d)", i, ret);
            nvm_os_free(seg);
            ret = -ENOBUFS;
            break;
        }
    }

    //Check if we had error during the segment vector initiation
    if (ret) {
        resetSegments(self, NULL, 0);
        clearUuid(self);
        return ret;
    }

    LOGI("Done creating NvmSegments\n");
    //allocate DDR in PIL region memory
    if(EFI_SUCCESS != spcom_protocol->SpcomAlloc(self->m_channelName, (void *)&baseAddr_32b, (size_t)totalSize)){
        LOGE("DDR allocation failure, size=%d", totalSize);
        resetSegments(self, NULL, 0);
        clearUuid(self);
        return -ENOBUFS;
    }
    LOGI("DDR allocation , size=0x%x, baseAddr = 0x%x", totalSize, (uint32_t)baseAddr_32b);

    *baseAddr_ptr = 0x00000000FFFFFFFF & (uint32_t)baseAddr_32b;

    //Update the DDR address of each segment
    for (uint8_t i=0 ; i < req->numSegs; i++) {
        self->m_segments[i]->setSegmentAddr(self->m_segments[i], (uint64_t)(*baseAddr_ptr + out_offsets[i]));
    }

    // remove files with no pointers (can be due to resize of partition)
    //Shouldn't have any effect for UEFI case. 
    //NvmSegment_removeInvalidSegmentsFiles(m_uuidStr, req->numSegs);

    return ret;
}

int SecNvmManager_openPartition(
    struct SecNvmManager * self,
    open_partition_req_t *req,
    uint64_t * baseAddr_ptr,
    uint32_t out_offsets[],
    void* cmd,
    uint32_t segsSize[])
{
    int ret = 0;
    uint32_t totalSize = 0;
    struct Operation* op = NULL; 
    void * baseAddr_32b;

    if (!cmd || !req || !out_offsets) {
        LOGE("NULL input parameters");
        return -EINVAL;
    }
    op = *(struct Operation **)cmd;

    if (op == NULL) {
        LOGE("!!! op ptr NULL !!!");
        return -EINVAL;
    }

    // check if the partition has already been opened/created -
    // reset the partition and upload it again for SSR support
    // The SP should block reopen from his side
    if (!isSegmentsEmpty(self)) {
        LOGI("clear old allocated segments");
        resetSegments(self, NULL, 0);
    }

    // uuid must not change after first call
    ret = setUuid(self, req->uuid);
    if (ret) {
        LOGE("Invalid UUID");
        return -EINVAL;
    }

    struct NvmSegment* seg = NULL;
    // create the NvmSegment objects vector. UEFI should only have 1 NvmSegment Obj. 
    for (uint8_t i=0 ; i < req->numSegs; i++) {
        LOGI("allocate segment#%d out of %d\n", i, req->numSegs);

        seg = new((const void *)&_NvmSegment, i, self->m_uuidStr, segsSize[i],
              op->get_is_ari((void *)cmd),op->get_is_skp((void *)cmd));
        if (!seg) {
            LOGE("failed to allocate segment#%d\n", i);
            ret = -ENOMEM;
            break;
        }

        out_offsets[i] = totalSize;
        LOGI("out_offsets[%d] = 0x%x\n", i, out_offsets[i]);
        totalSize += seg->getSegmentSize(seg);
        LOGI("totalSize = 0x%x\n", totalSize);
        if (-1 == addSegment(self, seg)) {
            LOGE("failed to store segment#%d (%d)\n", i, ret);
            nvm_os_free(seg);
            ret = -ENOBUFS;
            break;
        }
    }

    //Check if we had error during the segment vector initiation
    if (ret) {
        LOGE("resetSegments & clearUuid\n");
        resetSegments(self, NULL, 0);
        clearUuid(self);
        return ret;
    }

    LOGI("DDR allocation , m_channelName = %a, &baseAddr: 0x%x", self->m_channelName, &baseAddr_32b);
    //alocate DDR in PIL region memory
    if(EFI_SUCCESS != spcom_protocol->SpcomAlloc(self->m_channelName, (void *)&baseAddr_32b, (size_t)totalSize)){
        LOGE("DDR allocation failure, size=%d", totalSize);
        resetSegments(self, NULL, 0);
        clearUuid(self);
        return -ENOBUFS;
    }

    LOGI("DDR allocation , size=0x%x, baseAddr = 0x%x", totalSize, (uint32_t)baseAddr_32b);

    *baseAddr_ptr = 0x00000000FFFFFFFF & (uint32_t)baseAddr_32b;
    //Set DDR addr, and upload the segemnt to the DDR
    for (uint8_t i=0 ; i < req->numSegs; i++) {
        self->m_segments[i]->setSegmentAddr(self->m_segments[i], (uint64_t)(*baseAddr_ptr + out_offsets[i]));
        op->set_marker((void *)cmd, getOpMarker(cmd, req->cmacs[i].cmac, self->m_segments[i]->getCounterPtr(self->m_segments[i])));

        ret = self->m_segments[i]->openSegment(self->m_segments[i], op->get_marker(cmd));
        if (ret) {
        	LOGI("failed to open segment#%d (%d)", i, ret);
            resetSegments(self, baseAddr_32b, totalSize);
            clearUuid(self);
            //Should we free the PIL allocation here?
            return ret;
        }
    }

    // remove files with no pointers (can be due to resize of partition)
    //NvmSegment::removeInvalidSegmentsFiles(m_uuidStr, req->numSegs);

    return ret;
}

int SecNvmManager_updateSegmentsData(
    struct SecNvmManager * self,
    commit_req_t *req,
    void* cmd)
{
    int ret = 0;
    struct Operation* op = NULL; 

    if (!cmd ||!req) {
        LOGE("NULL input parameters");
        return -EINVAL;
    }

    op = * (struct Operation **)cmd;

    if (op == NULL) {
        LOGE("!!! op ptr NULL !!!");
        return -EINVAL;
    }

    if (!self->m_uuid || isSegmentsEmpty(self)) {
        LOGE("partition doesn't exist");
        return -EINVAL;
    }

    if (memcmp(self->m_uuid, req->uuid, UUID_SIZE) != 0) {
        LOGE("invalid uuid");
        return -EINVAL;
    }

    if (req->numSegs > getSegmentsCount(self)) {
        LOGE("invalid number of segments");
        return -EINVAL;
    }

    // go over the application requested segments - and update the persist data
    // of each segment
    struct NvmSegment *seg = NULL;
    for (uint8_t i = 0; i < req->numSegs; i++) {
        LOGI("update segment#%d out of %d", i, req->numSegs);
        if (req->segs[i].segNum >= getSegmentsCount(self)) {
            LOGE("invalid segment number segs[%d].segNum=%d", i,
                    req->segs[i].segNum);
            ret =  -EINVAL;
            break;
        }

        seg = self->m_segments[req->segs[i].segNum];
        op->set_marker((void *)cmd, getOpMarker(cmd, req->segs[i].cmac.cmac, seg->getCounterPtr(seg)));
        ret = seg->updateSegment(seg, op->get_marker(cmd));
        if (ret) {
            LOGE("failed to update segment[%d] data, SP should issue ABORT (%d)",
                    req->segs[i].segNum, ret);
            break;
        }
    }

    return ret;
}


void * SecNvmManager_ctor(void * _self, va_list * app){

    struct SecNvmManager * self = _self;
    const char * appName = va_arg(* app, const char*);


    self->m_uuid = NULL;
    self->m_spcomServer = NULL;
    self->m_segmentsCount = 0; 
    self->m_state = SEC_NVM_INIT_STATE;
    LOGI("SecNvmManager_ctor--appName: %a\n", appName);
    snprintf(self->m_channelName, SPCOM_CHANNEL_NAME_SIZE, "%s%s",
            NVM_CHANNEL_NAME_PREFIX, appName);
    LOGI("SecNvmManager_ctor--m_channelName: %a\n", self->m_channelName);
    //Populate function pointers
    self->receiveRequests             = SecNvmManager_receiveRequests;
    self->startSpcomServer            = SecNvmManager_startSpcomServer;
    self->allocatePartition           = SecNvmManager_allocatePartition;
    self->openPartition               = SecNvmManager_openPartition;
    self->updateSegmentsData          = SecNvmManager_updateSegmentsData;
    self->getSegsNum                  = SecNvmManager_getSegsNum;
    self->loadNvmAppTest              = SecNvmManager_loadNvmAppTest;

    return _self;
}


void SecNvmManager_dtor(void * _self)
{
    struct SecNvmManager * self = _self;
    int ret = spcom_protocol->UnregisterService(self->m_spcomServer);
    if (!ret) {
        LOGE("can't unregister spcom service (%d)", ret);
    }

    //should we keep a ion buffer in global?
    resetSegments(self, NULL, 0);
    clearUuid(self);

}

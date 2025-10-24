/*========================================================================
SecNvmManager.h
This file describes the SecNvmManager class.

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
#ifndef SECNVMMANAGER_H_
#define SECNVMMANAGER_H_

#include "osCommon.h"
#include "SecNvmDefs.h"
#include "Commands.h"
#include "NvmSegment.h"
#include "Operation.h"

typedef struct thread_param_t {
    char name[NVM_APP_NAME_SIZE];
} thread_param_t;

typedef enum {
    SEC_NVM_INIT_STATE,
    SEC_NVM_CREATE_STATE,
    SEC_NVM_OPEN_STATE,
    SEC_NVM_CREATE_DONE_STATE,
    SEC_NVM_INIT_DONE_STATE,
    SEC_NVM_ILLEGAL_STATE,
} nvm_service_state_t;

struct Operation;
/*
typedef struct {
   uint8_t   uuid[UUID_SIZE];
   int32     ion_fd;
   uint32_t  size;
   cmac_t    rh;
} app_sb_data_t;;

const int SCRATCH_DB_ION_BUFFER_SIZE = 0x1000;
typedef struct {
   app_sb_data_t apps[MAX_SB_SEGS];
   uint8_t sb_count;
   cmac_t rh;
} scratch_db_t;
*/
/*-------------------------------------------------------------------------
 * Class Definitions
 * ----------------------------------------------------------------------*/
/**
 * This struct defines the main module of each
 * SP application thread.
 * The class is responsible for receiving the SP application
 * requests(sending from the SP NVM library) and manage the
 * the partition memory of the SP application.
 * There is an option to execute asynchronous commit message that
 * is running on separated asyncCmdThread.
 * The thread execute asyncCommitFunc function that updates
 * the asyncRspMsg member of the class, the isCommit operation is
 * responsible for getting the asyncRspMsg buffer when the executing
 * of the asyncCmdThread thread is done, till the function is done
 * all the other requests return error.
 */
struct SecNvmManager
{
   const void * class;
    /**
    * The main function of the manager.
    *
    * The function gets SPCOM request message, executes the request
    * and sends the response
    *
    * @return void.
    */
   EFI_STATUS (*receiveRequests)(struct SecNvmManager * self);

   /**
    * The function registers SPCOM service, that is:
    * - waits for SP link up
    * - do register SCOM service
    *
    * @return errno standard errors
    */
   int (*startSpcomServer)(struct SecNvmManager * self);

      /**
    * depending on current operation *op constructed so it contains valid and
    * consistent values of:
    * m_is_skp true iif request is coming from SKP
    * m_is_ari true iif ARI is supported by SP
    * marker points to:
    *  NULL - m_is_ari == false
    *  arc  - m_is_ari && m_is_skp == true
    *  cmac - m_is_ari && !m_is_skp == true
    * marker_length - ARC_SIZE/CMAC_SIZE/TRANCATION_COUNTER_SIZE
    * marker_offset - offset related to segment/file start
    */


   /**
    * The function allocates DDR partition(in segments unit)
    * in case partition exist reallocate new one.
    *
    * @param out_ionFd -   The ion fd of the DDR partition
    * @param out_offsets - The offset of the segments in the ION buffer
    *
    * @return error code.
    */
   int (*allocatePartition)(struct SecNvmManager * self, create_partition_req_t *req, create_partition_rsp_t *rsp, uint64_t* baseAddr_ptr,
                            uint32_t out_offsets[], void * cmd, uint32_t segsSize[]);

   /**
    * The function allocates DDR partition and upload all
    * the existed application data from the storage.
    *
    * @param out_ionFd -   The ion fd of the DDR partition
    * @param out_offsets - The offset of the segments in the ION buffer
    *
    * @return error code.
    */
   int (*openPartition)(struct SecNvmManager * self, open_partition_req_t *req, uint64_t * baseAddr_ptr,
                        uint32_t out_offsets[], void * cmd, uint32_t segsSize[]);

   /**
    * The function updates persist data of the requested segments
    *
    * @return error code.
    */
   int (*updateSegmentsData)(struct SecNvmManager * self, commit_req_t *req, void * cmd);

   uint32_t (*getSegsNum)(uint8_t uuid[]);
   //Not called anywhere
   //bool (*spcomIsValid)() { return m_spcomServer != NULL; };
   //Used for scratch buffer Op
   //const char * (*getChannelName)();
   //Not Used anywhere
   //static void (*skp_open_done)();

   /**
    * The function updates load test app nvm_noheap
    *
    * @return error code.
    */
   int (*loadNvmAppTest)(struct SecNvmManager * self);


   uint8_t*             m_uuid;
   char                 m_uuidStr[UUID_STR_SIZE];
   struct spcom_server* m_spcomServer;
   char                 m_channelName[SPCOM_CHANNEL_NAME_SIZE];
   //os_thread_t          m_asyncCmdThread;
   //os_thread_mutex_t    m_mutex;
   //bool                 m_isAsyncThreadBusy;
   //bool                 m_isLockState;
   //int8_t*              m_asyncRsp;
   //uint32_t             m_asyncRspSize;

   struct NvmSegment*  m_segments[MAX_SEGS];
   uint32_t            m_segmentsCount;
   // Scratch Buffer support
   //ionInfo              m_ionHandle;
   //static ionInfo       m_ionScratchHandle;

   nvm_service_state_t m_state;
};


void * SecNvmManager_ctor(void * _self, va_list * app);
void SecNvmManager_dtor(void * _self);

#endif /* SECNVMMANAGER_H_ */

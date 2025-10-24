/*========================================================================
NvmSegment.h
This file describes the NvmSegment class.

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
#ifndef NVMSEGMENT_H_
#define NVMSEGMENT_H_

#include "osCommon.h"
#include "SecNvmDefs.h"

typedef uint32_t counter_t;

#define  NVM_CHANNEL_NAME_PREFIX       "sec_nvm_"
#define  NVM_CHANNEL_NAME_PREFIX_SIZE  sizeof(NVM_CHANNEL_NAME_PREFIX)
#define  NVM_APP_NAME_SIZE             (SPCOM_CHANNEL_NAME_SIZE - NVM_CHANNEL_NAME_PREFIX_SIZE)


#define  TRANSACTION_COUNTER_SIZE sizeof(counter_t)

#define  CHAR_MAX_DIGIT_NUM       3
#define  UUID_STR_SIZE            (CHAR_MAX_DIGIT_NUM * UUID_SIZE) + 1
#define  FILE_NAME_SIZE           sizeof(ROOT_PATH) + (CHAR_MAX_DIGIT_NUM * UUID_SIZE) + CHAR_MAX_DIGIT_NUM + 3

/**
 *  The NvmSegment class is responsible for managing NVM segment memory.
 *
 *  Each NVM segment data is stored in the DDR and persistently in the storage.
 *  Using two copies in the storage, power failure recovery is supported.
 *
 *  That is 2 copies of the memory segment keep in two separated files. Only
 *  one file is valid, to define this used 'marker':
 *      - SKP segment marker is arc[ARC_SIZE] 32 byte value
 *      - Application segment marker is cmac[CMAC_SIZE] 16 byte value
 *  `marker` stored in both DDR and files. SP communicates marker value along
 *  with rest request data.
 *
 *  In order to update a segment data, we need to check the bytemap at the end
 *  of the segment (known offset), if byte from the data bytemap is set the
 *  corresponding data block in the segment should be updated and the
 *  corresponding 32B of hash should be changed accordingly
 *
 *  Memory layout of segment (note that file layout is different, no bytemap, control, pad64)
 *   struct SegmentLayout {
 *      // Data
 *      data_block_t data[BLOCKS_IN_SEGMENT];      // 1Mb actual 1024 data blocks
 *      // L2
 *      l2_slice_t   l2_data[BLOCKS_IN_SEGMENT];   // 48 * 1024 = 48Kb
 *      // L1
 *      l1_block_t   l1_data[L1_BLOCKS_IN_SLICE];  // 48 * 32 blocks in slice = 1Kb
 *      uint8_t      seg_num[SEG_NUM_SIZE];        // 1 byte
 *      uint8_t      reserved[RESERVED_META_DATA]; // 15 bytes
 *      uint8_t      arc[ARC_SIZE];                // anti rollback counter
 *      uint8_t      cmac[CMAC_SIZE];              // 16 bytes
 *      //  next fields are not saved in the file
 *      uint8_t      version[VER_SIZE];            // 2 bytes
 *      uint8_t      bytemap[BYTEMAP_SIZE];        // 1 * 1024 = 1Kb
 *      uint8_t      control[COMMIT_CONTROL_SIZE];  // 1 byte used to ack SP
 *                                                 // about nvm segment synced with flash
 *      uint8_t      pad64[PADDING_64BIT];
 *  } ;
 */
struct NvmSegment
{
   const void * class;

   /* "Public" */
   uint32_t (*getSegmentSize)(struct NvmSegment* self);

   void (*setSegmentAddr)(struct NvmSegment* self, uint64_t addr);

   /**
    * The function create 2 segments files:
    * - first file contains marker value on marker_offset from position 0
    * - second file is empty, only created
    */
   int (*createSegment)(struct NvmSegment* self, uint8_t *marker);

   /** The function uploads the pointed segment file into the DDR mirror */
   int (*openSegment)(struct NvmSegment* self, uint8_t *marker);

   /**
    * The function updates the pointed segment file in the storage by coping the
    * dirty data and hash blocks from the DDR.
    */
   int (*updateSegment)(struct NvmSegment* self, uint8_t *marker);

   /**
    * The function aborts the write changes in the DDR segment by uploading all
    * changed content from the file with matched marker
    */
   int (*abortSegment)(struct NvmSegment* self, uint8_t *marker);

   /**
    * The function sets in the segment control block that the asynchronous
    * commit command is done
    */
   void (*setUpdateSegmentDone)(struct NvmSegment* self);

   /**
    * The function removes invalid application files - Invalid files can be due
    * to resize of partition in recreate partition call.
    */
   void (*removeInvalidSegmentsFiles)(struct NvmSegment* self, const char* uuidStr, uint32_t startingFrom);

   uint8_t * (*getCounterPtr)(struct NvmSegment* self);


   uint32_t        M_BLOCKS_IN_SEGMENT;
   uint32_t        M_DATA_SIZE;
   uint32_t        M_SLICES_IN_SEGMENT;
   uint32_t        M_L1_HASH_SIZE;
   uint32_t        M_L1_SIZE;
   uint32_t        M_L2_SIZE;
   uint32_t        M_BYTEMAP_SIZE;
   uint32_t        M_SEGMENT_DATA_SIZE;
   uint32_t        M_PADDING_64BIT;
   uint32_t        M_SEGMENT_SIZE;
   uint32_t        M_ALIGNED_SEGMENT_SIZE;
   uint32_t        M_SEGMENT_FILE_SIZE;
   uint32_t        M_BYTEMAP_OFFSET;
   uint32_t        M_TRANSACTION_COUNTER_OFFSET;

   uint64_t              m_addr;
   uint32_t              m_size;
   char                  m_uuidStr[UUID_STR_SIZE];
   char                  m_file0[FILE_NAME_SIZE];
   char                  m_file1[FILE_NAME_SIZE];
   uint8_t               m_segNum;

   // last valid commit bytemap, updated in the end of commit operation, before response to SP
   uint8_t               m_bytemap[MAX_BYTEMAP_SIZE];
   counter_t             m_counter; // used as marker for ari bypass and as a transaction marker
   boolean               m_is_ari;
   boolean               m_is_ari_bypass;
   ssize_t               m_marker_length;
   off_t                 m_marker_offset;
};

void * NvmSegment_ctor(void * _self, va_list * app);

#endif /* NVMSEGMENT_H_ */

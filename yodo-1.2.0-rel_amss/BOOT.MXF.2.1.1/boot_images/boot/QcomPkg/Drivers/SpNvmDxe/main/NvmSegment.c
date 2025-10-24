/*========================================================================
NvmSegment.cpp
This file describe the implementation of the NvmSegment class.

Copyright (c) 2021 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================*/
/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/19/21   vp      Minimize Error Log Prints for Open Partition failure
 04/19/21   av      Fix segment market length assignment
 02/16/21   vp      Fix incorrect return values
 02/11/21   nc      SCM calls optimization
 02/08/21   vp      Fix for bug in setting marker_length of app partition
 03/09/20   ll      initial release
=============================================================================*/
#include "osCommon.h"
#include "stringl/stringl.h"  // strnlen()

#include <Uefi.h>
#include <PrintShLib.h>
#include <stdio.h>  // printf(); MIN()
#include <stdint.h>     // size_t
#include <stdarg.h>     // va_arg()
#include <stdbool.h>    // bool , true , false
#include <string.h>     // memset()
#include <stdlib.h>
#include <Library/MemoryAllocationLib.h>
#include "QcomLib.h"
#include "stringl/stringl.h"  // strnlen()

#include "NvmSegment.h"
#include "Operation.h"

#define BUFFER_SIZE 4096

boolean is_skp = false;

/* -----LOCAL FUNCTIONS----- */
char *marker_to_str(uint8_t *marker, ssize_t marker_length)
{
    static char marker_str[BUFFER_SIZE];
    char *cur = marker_str;
    size_t left_size = BUFFER_SIZE;
    size_t written;

    // each byte of marker converted into 3 chars of string representation
    // marker_length could be 16/32/sizeof(uint32_t) bytes
    ssize_t size = (marker_length * 3) >= BUFFER_SIZE ? (BUFFER_SIZE / 3) - 1: marker_length;

    for (ssize_t i = 0; i < size; i++) {
        written = snprintf(cur, left_size, "%02x ", marker[i]);
        if (written > 0 && written < left_size){
           left_size -= 3;
           cur += written;
        }else {
           LOGE("Insufficient Buffer size");
           return 0;
        }
    }
    *cur = 0;
    return marker_str;
}

/*
 * returns true iff 'marker_length' bytes readed from offset 'marker_offset'
 * are equal to 'marker' byte array
 *
 * fd - open file descriptor
 * marker - points to valid array of 'marker_length' bytes
 */
bool match_marker(struct NvmSegment * self, osfd_t fd, uint8_t *marker)
{
    uint8_t file_marker[BUFFER_SIZE] = {0};
    uint8_t *buf = file_marker;
    bool found = false;
    size_t left_to_read = self->m_marker_length;
    ssize_t bytesread = 0;

    if (!marker) {
        LOGE("%a:marker is NULL", __func__);
        return false;
    }
    // positional read from 'fd' file_arc value
    while (left_to_read > 0 &&
            (bytesread = os_pread(fd, (void *)buf, left_to_read, self->m_marker_offset)) > 0) {
        left_to_read -= bytesread;
        buf += bytesread;
    }
    if (bytesread <= 0) {
        LOGE("pread() error, left_to_read=%ld", left_to_read);
    }

    if (left_to_read == 0) {
        if (!memcmp(file_marker, marker, self->m_marker_length)) {
            found = true;
            LOGD("found marker for file");
        } else {
            LOGD("file_marker=%a", marker_to_str(file_marker, self->m_marker_length));
            LOGD("marker=%a", marker_to_str(marker, self->m_marker_length));
        }
    }
    return found;
}

/**
 * The function calculate the size of the set continuous bytes in the bytemap.
 *
 * @param bytemap -        The pointer to a set byte in the
 *                         bytemap
 * @param bytemapSize -    The remain bytemap size.
 *
 */
uint32_t find_set_size(uint8_t* bytemap, uint32_t bytemapSize)
{
    uint32_t cnt = 0;

    for (uint32_t i = 0; i < bytemapSize; i++) {
        if (!bytemap[i]) break;
        cnt++;
    }
    return cnt;
}

/* Read counter from file fd
 * fd must be valid descriptor of open file
 * returns zero in case of error
 */
counter_t get_file_counter(struct NvmSegment* self, osfd_t fd)
{
    counter_t counter = 0;

    ssize_t u32ReadLen = os_pread(fd, (void *)&counter,
            TRANSACTION_COUNTER_SIZE, self->M_TRANSACTION_COUNTER_OFFSET);
    if (u32ReadLen != TRANSACTION_COUNTER_SIZE) {
        LOGE("failed to read transaction counter");
        return 0;
    }
    return counter;
}

/* Write counter to file fd
 * fd must be valid descriptor of open file
 * returns -EINVAL in case of error
 */
int set_file_counter(struct NvmSegment* self, osfd_t fd, counter_t counter)
{
    int ret = 0;

    ssize_t u32WritenLen = os_pwrite(fd, (void *)&counter,
            TRANSACTION_COUNTER_SIZE, self->M_TRANSACTION_COUNTER_OFFSET);
    if (u32WritenLen != TRANSACTION_COUNTER_SIZE) {
        LOGE("failed to write transaction counter: %u",counter);
        return -EINVAL;
    }
    return ret;
}

/*
 * Opens m_file0 and m_file1, depending on 'marker' value
 * returns open file descriptor into 'fd' and second open
 * file descriptor as 'fd_backup'
 *
 * on error close both files
 */
int open_files(struct NvmSegment* self, uint8_t *marker, osfd_t *fd, osfd_t *fd_backup)
{
    osfd_t      fd0, fd1;
    uint32_t    cnt0, cnt1;
    bool        fd0_matched = false;
    bool        fd1_matched = false;

    *fd = OS_FD_INVALID;
    *fd_backup = OS_FD_INVALID;

    fd0 = os_open_segment_file(self->m_file0, OS_O_RDWR);
    if (OS_IS_FD_INVALID(fd0)) {
        LOGI("can't open %a file for seg#%d", self->m_file0, self->m_segNum);
        return -ENOENT;
    }

    fd1 = os_open_segment_file(self->m_file1, OS_O_RDWR);
    if (OS_IS_FD_INVALID(fd1)) {
        LOGI("can't open %a file for seg#%d", self->m_file1, self->m_segNum);
        return -ENOENT;
    }

    if (self->m_is_ari) {
        // In case of "NO ARI" ignore markers and go straight to counters
        fd0_matched = match_marker(self, fd0, marker);
        fd1_matched = match_marker(self, fd1, marker);
    }
    self->m_is_ari_bypass = fd0_matched && fd1_matched;
    LOGD("m_is_ari: %d, m_is_ari_bypass: %d", self->m_is_ari, self->m_is_ari_bypass);

    if (self->m_is_ari && !self->m_is_ari_bypass) {
        // define which file is actual, second file is backup
        if (fd0_matched) {
            *fd = fd0;
            *fd_backup = fd1;
            LOGD("match marker of %a", self->m_file0);
        } else if (fd1_matched) {
            *fd = fd1;
            *fd_backup = fd0;
            LOGD("match marker of %a", self->m_file1);
        } else {
            LOGD("can't find marker value");
            return -EBADMSG;
        }
    } else {
        LOGD("ari bypass: check counters");
        cnt0 = get_file_counter(self, fd0);
        cnt1 = get_file_counter(self, fd1);

        LOGD("counters: cnt0: %u, cnt1: %u", cnt0, cnt1);
        if (cnt0 > 0 || cnt1 > 0) {
            if (cnt0 >= cnt1) {
                *fd = fd0;
                *fd_backup = fd1;
                LOGD("match counter %d of %a", cnt0, self->m_file0);
            } else {
                *fd = fd1;
                *fd_backup = fd0;
                LOGD("match counter %d of %a", cnt1, self->m_file1);
            }
        } else {
            // both cnt0 & cnt1 not valid
            return -EBADMSG;
        }
    }
    return SUCCESS;
}

int commit_seg_to_file(struct NvmSegment* self, osfd_t fd, uint8_t* bytemap)
{
    int         ret = 0;
    ssize_t     u32WritenLen = 0;
    void        *buff = NULL;
    uint8_t     total_size = 0;

    // Zero transaction counter
    ret = set_file_counter(self, fd, 0);
    if (ret) {
        LOGE("failed to zero transaction counter");
        return ret;
    }

    for (uint32_t i = 0; i < self->M_BYTEMAP_SIZE;) {
        if (bytemap[i]) {
            // find how many data blocks are dirty starting from block i
            uint32_t setSize = find_set_size(&bytemap[i], self->M_BYTEMAP_SIZE - i);
            if (!setSize) {
                LOGE("bytemap has changed - corruption error");
                return -EILSEQ;
            }

            //Write the data into the file
            LOGD("commit %d blocks starting from %d, self->m_addr = 0x%x, setSize = 0x%x, i = %d",
                    setSize, (i * DATA_BLOCK_SIZE), self->m_addr, setSize, i);
            u32WritenLen = os_pwrite(fd, (void *)(self->m_addr + (i * DATA_BLOCK_SIZE)),
                    (setSize * DATA_BLOCK_SIZE), (i * DATA_BLOCK_SIZE));
            if (u32WritenLen != (setSize * DATA_BLOCK_SIZE)) {
                LOGE("failed to write data block");
                return -EINVAL;
            }

            //Write the updated L2 hash block into the file
            LOGD("commit %d hash blocks starting from %d",
                    setSize, self->M_DATA_SIZE + (i * L2_BLOCK_SIZE));
            u32WritenLen = os_pwrite(fd, (void *)(self->m_addr + self->M_DATA_SIZE + (i * L2_BLOCK_SIZE)),
                    (setSize * L2_BLOCK_SIZE), self->M_DATA_SIZE + (i * L2_BLOCK_SIZE));
            if (u32WritenLen != (setSize * L2_BLOCK_SIZE)) {
                LOGE("failed to write hash block");
                return -EINVAL;
            }
            i += setSize;
        } else { // bytemap[i] != 0
            i++;
        }
    } // for

    /* Write L1 + root hash + bytemap + transaction counter in one SCM call */
    total_size = self->M_L1_SIZE + ROOT_HASH_SIZE + self->M_BYTEMAP_SIZE + TRANSACTION_COUNTER_SIZE;
    buff = nvm_os_malloc(total_size);
    if(!buff) {
        LOGE("Failed to alloc buffer");
        return -ret;
    }

    memscpy(buff,
            (self->M_L1_SIZE + ROOT_HASH_SIZE + self->M_BYTEMAP_SIZE + TRANSACTION_COUNTER_SIZE),
            (void *)(self->m_addr + self->M_DATA_SIZE + self->M_L2_SIZE),
            self->M_L1_SIZE + ROOT_HASH_SIZE);

    memscpy((buff + self->M_L1_SIZE + ROOT_HASH_SIZE),
            (self->M_BYTEMAP_SIZE + TRANSACTION_COUNTER_SIZE),
            (void*)(self->m_addr + self->M_BYTEMAP_OFFSET),
            self->M_BYTEMAP_SIZE);

    self->m_counter++;
    memscpy((buff + self->M_L1_SIZE + ROOT_HASH_SIZE + self->M_BYTEMAP_SIZE),
            TRANSACTION_COUNTER_SIZE,
            (void*) &self->m_counter,
            TRANSACTION_COUNTER_SIZE);

    u32WritenLen = os_pwrite(fd, buff,
                            (self->M_L1_SIZE + ROOT_HASH_SIZE + self->M_BYTEMAP_SIZE + TRANSACTION_COUNTER_SIZE),
                            (self->M_DATA_SIZE + self->M_L2_SIZE));
    nvm_os_free(buff);
    if(u32WritenLen < total_size) {
        LOGE("Failed to read L1+root hash, bytemap, counter");
        return -EINVAL;
    }

    if (!self->m_is_ari || self->m_is_ari_bypass) {
        LOGD("updated active file with transaction counter: %u, m_is_ari_bypass: %d",
                self->m_counter, self->m_is_ari_bypass);
    }

    LOGD("successfully updated DDR->flash (transaction counter: %u)", self->m_counter);
    return 0;
}

/* Go over the set byte in the bytemap and update the blocks data in the DDR
 * segment by the data blocks in the file.
 */
int load_seg_from_file(struct NvmSegment* self, osfd_t fd, uint8_t* bytemap)
{
    int         ret = 0;
    ssize_t     u32ReadLen;
    void        *buff = NULL;
    uint8_t      total_size  = 0;

    for(uint32_t i = 0; i < self->M_BYTEMAP_SIZE;) {
        if (bytemap[i]) {
            // find how many data blocks are dirty starting from block i
            uint32_t setSize = find_set_size(&bytemap[i], self->M_BYTEMAP_SIZE - i);
            if (!setSize) {
                LOGE("bytemap has changed - corruption error");
                return -EILSEQ;
            }
            // Load block from file
            LOGD("load %d blocks starting from %d, my_addr 0x%x",
                    setSize, (i * DATA_BLOCK_SIZE), self->m_addr);
            u32ReadLen = os_pread(fd, (void *)self->m_addr + (i * DATA_BLOCK_SIZE),
                    (setSize * DATA_BLOCK_SIZE), (i * DATA_BLOCK_SIZE));
            if (u32ReadLen != (setSize * DATA_BLOCK_SIZE)) {
                LOGE("failed to read data block");
                return -EINVAL;
            }

            // Load hash block from file
            LOGD("load %d hash blocks starting from %d",
                    setSize, self->M_DATA_SIZE + (i * L2_BLOCK_SIZE));
            u32ReadLen = os_pread(fd, (void *)self->m_addr + self->M_DATA_SIZE + (i * L2_BLOCK_SIZE),
                    (setSize * L2_BLOCK_SIZE), self->M_DATA_SIZE + (i * L2_BLOCK_SIZE));
            if (u32ReadLen != (setSize * L2_BLOCK_SIZE)) {
                LOGE("failed to read hash block");
                return -EINVAL;
            }
            memset(&bytemap[i], 0, setSize);
            i += setSize;
        } else {
            bytemap[i] = 0;
            i++;
        }
    }

    /* Read the L1+root hash, bytemap and transaction counter */
    total_size = self->M_L1_SIZE + ROOT_HASH_SIZE + self->M_BYTEMAP_SIZE + TRANSACTION_COUNTER_SIZE;
    
    buff = nvm_os_malloc(total_size);
    if(!buff) {
        return -ret;
    }

    u32ReadLen = os_pread(fd, buff,
                          total_size, self->M_DATA_SIZE + self->M_L2_SIZE);
    if(u32ReadLen != total_size) {
        LOGE("Failed to read L1+root hash, bytemap and transaction counter");
        nvm_os_free(buff);
        return -EINVAL;
    }

    memscpy((void*)(self->m_addr + self->M_DATA_SIZE + self->M_L2_SIZE),
            self->M_L1_SIZE + ROOT_HASH_SIZE,
            buff, total_size);

    memscpy((void *)self->m_bytemap,
            self->M_BYTEMAP_SIZE,
            buff + self->M_L1_SIZE + ROOT_HASH_SIZE,
            total_size - (self->M_L1_SIZE + ROOT_HASH_SIZE));

    memscpy(&self->m_counter,
            TRANSACTION_COUNTER_SIZE,
            buff + (total_size - TRANSACTION_COUNTER_SIZE),
            TRANSACTION_COUNTER_SIZE);
    if (!self->m_counter) {
        LOGI("file counter is undefined");
    }
    
    nvm_os_free(buff);

    return 0;
}


off_t getMarkerOffset(struct NvmSegment* self, bool is_ari, bool is_skp) {
    off_t offset = self->M_DATA_SIZE + self->M_L2_SIZE + self->M_L1_SIZE + SEG_NUM_SIZE + RESERVED_META_DATA;

    if(!is_ari) {
        return self->M_TRANSACTION_COUNTER_OFFSET;
    }
    if(is_skp) {
        return offset;
    }

    return offset + ARC_SIZE;

}


uint32_t getMarkerSize(bool is_ari, bool is_skp) {

    if(is_ari) {
        if(is_skp) {
            return ARC_SIZE;
        } else {
            return CMAC_SIZE;
        }
    }

    return TRANSACTION_COUNTER_SIZE;
}


int createSegmentFile(struct NvmSegment* self, char *file, counter_t counter,
        uint8_t *marker, boolean is_backup)
{
    int     ret = 0;
    ssize_t done_bytes;
    osfd_t  fd;

    if (!marker){
        LOGE("no valid marker parameters");
        return -EINVAL;
    }

    fd = os_create_segment_file(file, is_skp, is_backup);
    if (OS_IS_FD_INVALID(fd)) {
        LOGE("failed to create %a file", file);
        return -ENOBUFS;
    }

    // In case of "NO ARI", marker points to the transaction counter - skip
    // marker writing, counter will be saved later on
    if (self->m_is_ari) {
        // write marker to the file
        LOGD("update marker: [%a], file: %a, pos: %lu",
                marker_to_str(marker, self->m_marker_length), file, self->m_marker_offset);
        done_bytes = os_pwrite(fd, marker, self->m_marker_length, self->m_marker_offset);
        if (done_bytes != self->m_marker_length) {
            LOGE("write marker to %a failed, written:%ld",
                    self->m_file0, done_bytes);
            return -ENOBUFS;
        }
    }

    // write transaction counter value to the file
    ret = set_file_counter(self, fd, counter);
    if (ret) {
        LOGE("failed to write transaction counter: %u", counter);
        return ret;
    }
    LOGD("update transaction counter: %u, file: %a, pos: %lu",
            counter, file, (ssize_t)self->M_TRANSACTION_COUNTER_OFFSET);

    return 0;
}


/* -----PUBLIC FUNCTIONS----- */
uint32_t NvmSegment_getSegmentSize(struct NvmSegment* self) {
    return self->m_size;
}


void NvmSegment_setSegmentAddr(struct NvmSegment* self, uint64_t addr) {
    self->m_addr = addr;
}


/*
 * Creates 2 files to save DDR content using double buffer scheme.
 * There are 3 cases for marker:
 * 1. No-ari case: marker value is m_counter, stored after DDR content
 * 2. Application segment: cmac value used at OFFSET_OF(nvm_segment_t, cmac)
 * 3. SKP segment: arc value used at OFFSET_OF(nvm_segment_t, arc)
 */
int NvmSegment_createSegment(struct NvmSegment* self, uint8_t *marker)

{
    int     ret = 0;


    if (!marker) {
        LOGE("no marker parameters");
        return -EINVAL;
    }

    //No need to create dir for UEFI: os_mkdir(ROOT_PATH)

    // sec_nvm daemon stores SP partition files in /mnt/vendor/persist/secnvm
    // at first boot, there is no such folder, it is created by init.qcom.rc
    // There is race between attampt of sec_nvm to create seg_db partition file
    // stored in not existing folder and init.qcom.rc
    // This change gives more time for init.qcom.rc to create the folder.
    //No need to wait for UEFI raw partition: usleep(100000);

    // Create first (main) file
    counter_t next_counter = self->m_counter + 1;
    LOGI("NvmSegment_createSegment: sizeof(self->m_file0): %d", strlen(self->m_file0));
    ret = createSegmentFile(self, self->m_file0, next_counter,
            marker, false);
    if (ret) {
        LOGE("failed to create main file %a", self->m_file0);
        return ret;
    }

    // Create second (backup) file
    ret = createSegmentFile(self, self->m_file1, self->m_counter,
            marker, true);
    if (ret) {
        LOGE("failed to create main file %a", self->m_file1);
        return ret;
    }

    // Increment transaction marker
    self->m_counter++;
    LOGI("NvmSegment_createSegment:Successfully created 2 files self->m_counter: %d", self->m_counter);
    return 0;
}


int NvmSegment_openSegment(struct NvmSegment* self, uint8_t *marker)
{
    osfd_t fd, fd_backup;

    if (!marker) {
        LOGE("no marker parameters");
        return -EINVAL;
    }

    int ret = open_files(self, marker, &fd, &fd_backup);
    if (ret != SUCCESS) {
        LOGI("failed to open files (%d)", ret);
        return ret;
    }

    // Mark entire bytemap as "dirty" to force the load_seg_from_file() to
    // read entire DDR from a file.
    memset(self->m_bytemap, 1, self->M_BYTEMAP_SIZE);
    ret = load_seg_from_file(self, fd, self->m_bytemap);
    if (ret != 0) {
        LOGE("failed to load segment from file (%d)", ret);
        goto err_out;
    }

    LOGI("successfully uploaded segment to DDR");

err_out:
    //No real "close" for UEFI raw partition
    return ret;
}


int NvmSegment_updateSegment(struct NvmSegment* self, uint8_t *marker)
{
    osfd_t fd, fd_backup;
    int ret = 0;
    uint8_t* bytemap;


    // find correct segment and backup file
    ret = open_files(self, marker, &fd, &fd_backup);
    if (ret != 0) {
        LOGE("can't open files (%d)", ret);
        return ret;
    }

    // Check the backup file integrity, correctness of the main file is assured by SPU
    // Correct backup file must include non-zero transaction counter value and
    // transaction counter must be smaller than active m_counter
    counter_t counter = get_file_counter(self, fd_backup);
    if (!counter || counter >= self->m_counter) {
        // Mark entire bytemap as "dirty" to force next commit_seg_to_file() to
        // write entire DDR to file.
        LOGD("dirty backup file");
        memset(self->m_bytemap, 1, self->M_BYTEMAP_SIZE);
    }
    else {
        // Merge current bytemap with previous
        bytemap = (uint8_t*)self->m_addr +  self->M_BYTEMAP_OFFSET;
        for (uint32_t i = 0; i< self->M_BYTEMAP_SIZE; i++) {
            self->m_bytemap[i] |= bytemap[i];
        }
    }

    // Keep "fd" as a backup and use the "fd_backup" to write current DDR content
    ret = commit_seg_to_file(self, fd_backup, self->m_bytemap);
    if (ret != 0) {
        LOGD("failed to update backup file (%d)", ret);
    } else {
        LOGD("successfully commited to the backup file, save bytemap for the next time");
        memscpy(self->m_bytemap, self->M_BYTEMAP_SIZE, (uint8_t*)self->m_addr +  self->M_BYTEMAP_OFFSET, self->M_BYTEMAP_SIZE);
    }

    //No real "close" for UEFI raw partition
    return ret;
}


void NvmSegment_setUpdateSegmentDone(struct NvmSegment* self)
{
   uint8_t* controlBlock = (uint8_t*)(self->m_addr + self->M_SEGMENT_DATA_SIZE - COMMIT_CONTROL_SIZE);
   memset(controlBlock, 1, COMMIT_CONTROL_SIZE);
}


int NvmSegment_abortSegment(struct NvmSegment* self, uint8_t *marker)
{
    osfd_t fd, fd_backup;
    int ret;

    if (!marker && self->m_is_ari) {
        LOGE("no marker parameters: m_is_ari=%d, marker=%p",
                self->m_is_ari, marker);
        return -EINVAL;
    }

    //Open file
    ret = open_files(self, marker, &fd, &fd_backup);
    if (ret != SUCCESS) {
        LOGE("fail to open files (%d)", ret);
        return ret;
    }

    uint8_t* bytemap = (uint8_t*)self->m_addr +  self->M_BYTEMAP_OFFSET;
    ret = load_seg_from_file(self, fd, bytemap);
    if (ret != 0) {
        LOGE("failed to load segment from file (%d)", ret);
    }
    return ret;
}


void NvmSegment_removeInvalidSegmentsFiles(struct NvmSegment* self, const char* uuidStr, uint32_t startingFrom)
{
    char file0[FILE_NAME_SIZE];
    char file1[FILE_NAME_SIZE];

    for (uint32_t i = startingFrom; i < MAX_SEGS; i++) {
        //Change the segment number
        snprintf(file0, FILE_NAME_SIZE, "%s%s_%d_0",
                ROOT_PATH, uuidStr, i);
        snprintf(file1, FILE_NAME_SIZE, "%s%s_%d_1",
                ROOT_PATH, uuidStr, i);

        //Check if the file exist
        osfd_t fd0 = os_open_segment_file(file0, OS_O_RDONLY);
        osfd_t fd1 = os_open_segment_file(file1, OS_O_RDONLY);

        //If both of the files not exist
        if (OS_IS_FD_INVALID(fd0) && OS_IS_FD_INVALID(fd1)) {
            //This should never happen for UEFI case
            break;
        }
        if (OS_IS_FD_VALID(fd1)) {
            LOGD("remove deprecated file %a", file1);
            os_remove(file1);
        }
        if (OS_IS_FD_VALID(fd0)) {
            LOGD("remove deprecated file %a", file0);
            os_remove(file0);
        }
    }
}


uint8_t * NvmSegment_getCounterPtr(struct NvmSegment* self){ 
     return (uint8_t *)&(self->m_counter); 
}


/*-----CONTRUCTOR-----*/
void * NvmSegment_ctor(void * _self, va_list * app){

    struct NvmSegment*  self = _self;
    uint8_t segNum = va_arg(* app, uint32_t) & 0xFF;
    const char* uuidStr = va_arg(* app, const char*);
    uint32_t size = va_arg(* app, uint32_t);
    self->m_is_ari = va_arg(* app, int);
    is_skp = va_arg(* app, int);

    self->M_BLOCKS_IN_SEGMENT = size;
    self->M_DATA_SIZE = self->M_BLOCKS_IN_SEGMENT * DATA_BLOCK_SIZE;
    self->M_SLICES_IN_SEGMENT = self->M_BLOCKS_IN_SEGMENT / BLOCKS_IN_SLICE;
    self->M_L1_HASH_SIZE = HASH_BLOCK_SIZE * self->M_SLICES_IN_SEGMENT;
    self->M_L1_SIZE = self->M_L1_HASH_SIZE + SEG_NUM_SIZE + RESERVED_META_DATA + ARC_SIZE;
    self->M_L2_SIZE = SLICE_SIZE * self->M_SLICES_IN_SEGMENT;
    self->M_BYTEMAP_SIZE = self->M_BLOCKS_IN_SEGMENT;
    self->M_SEGMENT_DATA_SIZE = self->M_DATA_SIZE + self->M_L2_SIZE + self->M_L1_SIZE + ROOT_HASH_SIZE + VER_SIZE + self->M_BYTEMAP_SIZE + COMMIT_CONTROL_SIZE;
    self->M_PADDING_64BIT = (8 - (self->M_SEGMENT_DATA_SIZE & 7)) & 7;
    self->M_SEGMENT_SIZE = self->M_SEGMENT_DATA_SIZE + self->M_PADDING_64BIT;
    self->M_ALIGNED_SEGMENT_SIZE = (ROUND_UP(self->M_SEGMENT_SIZE, SIZE_4K));
    self->M_SEGMENT_FILE_SIZE = self->M_SEGMENT_SIZE - (COMMIT_CONTROL_SIZE + self->M_PADDING_64BIT + VER_SIZE);
    self->M_BYTEMAP_OFFSET = self->M_SEGMENT_DATA_SIZE - self->M_BYTEMAP_SIZE - COMMIT_CONTROL_SIZE;
    self->M_TRANSACTION_COUNTER_OFFSET = self->M_SEGMENT_FILE_SIZE;

    LOGI("NvmSegment:M_BLOCKS_IN_SEGMENT: %d\n", self->M_BLOCKS_IN_SEGMENT);
    
    strlcpy(self->m_uuidStr, uuidStr, UUID_STR_SIZE);

    // create file0, file1 names
    snprintf(self->m_file0, FILE_NAME_SIZE, "%s%s_%u_0\0",
            ROOT_PATH, self->m_uuidStr, segNum);
    LOGI("NvmSegment:file0: %a, strlen file name: %d, name addr of file0:0x%x\n", self->m_file0, strlen(self->m_file0), &(self->m_file0[0]));
    snprintf(self->m_file1, FILE_NAME_SIZE, "%s%s_%u_1\0",
            ROOT_PATH, self->m_uuidStr, segNum);
    LOGI("NvmSegment:file1: %a\n", self->m_file1);

    //Update segment DDR data
    self->m_addr = 0;;
    self->m_size = self->M_ALIGNED_SEGMENT_SIZE;
    self->m_segNum = segNum;
    memset(self->m_bytemap, 0, MAX_BYTEMAP_SIZE);

    self->m_counter = 1;
    self->m_is_ari_bypass = false;
    self->m_marker_offset = self->M_DATA_SIZE + self->M_L2_SIZE + self->M_L1_HASH_SIZE + SEG_NUM_SIZE + RESERVED_META_DATA;
    LOGI("NvmSegment:m_marker_offset:0x%x\n", self->m_marker_offset);
    if(self->m_is_ari) {
        if(is_skp) {
            self->m_marker_length =  ARC_SIZE;

        } else {
            self->m_marker_length = CMAC_SIZE;
            self->m_marker_offset  += ARC_SIZE;

        }
    } else {
        self->m_marker_length = TRANSACTION_COUNTER_SIZE;
        self->m_marker_offset = self->M_TRANSACTION_COUNTER_OFFSET;
    }

    LOGI("NvmSegment:m_marker_length:%d\n", self->m_marker_length);

    //Populate function pointers
    self->getSegmentSize             = NvmSegment_getSegmentSize;
    self->setSegmentAddr             = NvmSegment_setSegmentAddr;
    self->createSegment              = NvmSegment_createSegment;
    self->openSegment                = NvmSegment_openSegment;
    self->updateSegment              = NvmSegment_updateSegment;
    self->abortSegment               = NvmSegment_abortSegment;
    self->setUpdateSegmentDone       = NvmSegment_setUpdateSegmentDone;
    self->removeInvalidSegmentsFiles = NvmSegment_removeInvalidSegmentsFiles;
    self->getCounterPtr              = NvmSegment_getCounterPtr;

    LOGI("NvmSegment:created segment#%u, m_counter=%d, m_is_ari=%d, UUID=%a\n",
            segNum, self->m_counter, self->m_is_ari, self->m_uuidStr);
    return self;
}


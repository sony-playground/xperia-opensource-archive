/*========================================================================
osCommon_UEFI.c
This file describe the implementation of the osGlue for UEFI, including: 
1. file: 
  a. macro define
  b. file operations (raw_xxx)
  c. file generic operations def (os_xxx)
2. new/delete in c format.
 
3. define class 
struct Class {
  size_t size;
  void * (* ctor) (void * self, va_list * app);
  void * (* dtor) (void * self); 
} 
 
Copyright (c) 2021 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================*/
/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/18/21   vp      KW error - add a null pointer check in kmdf_pWrite
 07/29/21   vp      Logging improvements
 06/21/21   ts      MISRA issues
 05/19/21   vp      Fix Buffer overflow while read/write of FLASH
 02/17/21   vp      Fix for bug in length of 2_TO_8_SECTORS for backup file
 02/08/21   vp      Fix for bug in setting marker_length of app partition
 03/09/20   ll      initial release
=============================================================================*/
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
#include <assert.h>

#include <Library/UefiBootServicesTableLib.h>


osf_t g_spNVMPartition_fileHandles[MAX_NUM_OF_FILES];


/** Return the nearest multiple of y at or above x */
#define ROUND_UP(x,y)  ((((x) + (y) - 1) / (y)) * (y))

static EFI_GUID SpNvmPartitionGuid = { 0xE42E2B4C, 0x33B0, 0x429B, { 0xB1, 0xEF, 0xD3, 0x41, 0xC5, 0x47, 0x02, 0x2C }};


void*
nvm_os_malloc (size_t size)
{
   void *pMem = NULL;

   pMem = AllocateZeroPool (size);
   if (!pMem)
   {
      LOGE("AllocateZeroPool, size=0x%x", size);
   }
   return pMem;
}

void
nvm_os_free (void *pMem)
{
   FreePool (pMem);
}


/**

 *Read data from the SPU_NVM partition 
 *  
    
	@param[in]        *buf 		           Data to be read
 *@param[in]        nbyte              num of bytes to be read.
 *@param[in]        offset             offset to read from 


 * @retval        Status                

**/
EFI_STATUS kmdf_pRead(uint8_t *buf, uint64_t nbyte, uint64_t offset)
{

  HandleInfo HandleInfoList[4] = {};
  uint32_t MaxHandles = 0;
  PartiSelectFilter HandleFilter = {0};
  uint32_t Attribs = 0;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_BLOCK_IO_PROTOCOL *BlkIo = NULL;
  uint64_t imgSize = 0;
  uint8_t *data_ptr = NULL;
  uint64_t roundUpNbyte = 0;
  uint32_t offset_block = offset/0x1000;
  uint32_t block_align_pre = offset%0x1000;

  if (nbyte == 0 || buf == NULL) {

    LOGE("read_partition: Invalid input arguments!\n");
    Status = EFI_INVALID_PARAMETER;
    goto exit;
  }

  /* Select the BlkIo handle that represents the partition by the
   * GUID on Non removable media */
  Attribs |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
  Attribs |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;

  MaxHandles = sizeof(HandleInfoList) / sizeof(*HandleInfoList);
  HandleFilter.VolumeName = 0;
  HandleFilter.RootDeviceType = 0;
  HandleFilter.PartitionType = 0;
  HandleFilter.PartitionType = &SpNvmPartitionGuid;//&enterpriseFvGuid;

  Status = GetBlkIOHandles(Attribs, &HandleFilter, HandleInfoList, &MaxHandles);

  if (EFI_ERROR(Status)) {
    LOGE("read_partition: Failed to get handle\n");
    goto exit;
  }

  /* Having more than one partition is considered ambiguity, so return
   * invalid param */
  if (MaxHandles > 1) {
    LOGE("read_partition: Ambiguity in Image partition\n");
    Status = EFI_INVALID_PARAMETER;
    goto exit;
  }

  if (MaxHandles == 0) {
    LOGE("read_partition: Image partition not found\n");
    Status = EFI_NOT_FOUND;
    goto exit;
  }

  /* Get the Block IO protocol instance from the handle */
  BlkIo = HandleInfoList[0].BlkIo;

  /* Get the partition size and round it up to EFI_PAGE_SIZE */
  imgSize = (BlkIo->Media->LastBlock + 1) * BlkIo->Media->BlockSize;
  LOGI("read_partition: imgSize = 0x%x\n", imgSize);
  if (imgSize < (offset + nbyte)) {

    LOGE("read_partition: read out of range!\n"); // should never happen
    Status = EFI_OUT_OF_RESOURCES;
    goto exit;
  }

  /* Get the to be write size and round it up to EFI_PAGE_SIZE */
  roundUpNbyte = ROUND_UP((nbyte + block_align_pre), BlkIo->Media->BlockSize);
  data_ptr = nvm_os_malloc(roundUpNbyte);

  if (data_ptr == NULL) {
    LOGE("read_partition: cannot allocate memory pool!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto exit;
  }

  Status = BlkIo->ReadBlocks(BlkIo, BlkIo->Media->MediaId, offset_block, roundUpNbyte, data_ptr);
  if (EFI_ERROR(Status)) {

    LOGE("read_partition: readblocks was unsuccessful\n");
    goto exit;
  }

  if (block_align_pre + nbyte > roundUpNbyte){
	  LOGE("read_partition: Buffer over read\n");
	  LOGE(" block_align_pre + nbyte:0x%x, nbyte:0x%x, roundUpNbyte: 0x%x\n", block_align_pre + nbyte,nbyte,roundUpNbyte);
	  Status = EFI_OUT_OF_RESOURCES;
	  goto exit;
  }
  memscpy(buf, nbyte, data_ptr+block_align_pre, nbyte);
  Status = EFI_SUCCESS;
exit:
  if (data_ptr) {
    nvm_os_free(data_ptr);
  }
  return Status;
}



/**

 *Write data from the SPU_NVM partition 
 *  
    
	@param[in]        *buf 		           Data to write
 *@param[in]        nbyte              num of bytes to be write.
 *@param[in]        offset             offset to be write  


 * @retval        Status                

**/
EFI_STATUS kmdf_pWrite(uint8_t *buff, uint64_t nbyte, uint64_t offset)
{

  HandleInfo HandleInfoList[1] = {};
  uint32_t MaxHandles = 0;
  PartiSelectFilter HandleFilter = {0};
  uint32_t Attribs = 0;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_BLOCK_IO_PROTOCOL *BlkIo = NULL;
  uint64_t imgSize = 0;
  uint8_t *data_ptr = NULL;
  uint64_t roundUpNbyte = 0;
  uint32_t offset_block = offset/0x1000;
  uint32_t block_align_pre = offset%0x1000;

  if ( buff == NULL || nbyte == 0 ) {

    LOGE("write_partition: Invalid input!\n");
    Status = EFI_INVALID_PARAMETER;
    goto exit;
  }

  /* Select the BlkIo handle that represents the partition by the
   * GUID on Non removable media */
  Attribs |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
  Attribs |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;

  MaxHandles = sizeof(HandleInfoList) / sizeof(*HandleInfoList);
  HandleFilter.VolumeName = 0;
  HandleFilter.RootDeviceType = 0;
  HandleFilter.PartitionType = 0;
  HandleFilter.PartitionType = &SpNvmPartitionGuid;//&enterpriseFvGuid;

  Status = GetBlkIOHandles(Attribs, &HandleFilter, HandleInfoList, &MaxHandles);

  if (EFI_ERROR(Status)) {
    LOGE("write_partition: Failed to get handle\n");
    goto exit;
  }

  /* Having more than one partition is considered ambiguity, so return
   * invalid param */
  if (MaxHandles > 1) {
    LOGE("write_partition: Ambiguity in Image partition\n");
    Status = EFI_INVALID_PARAMETER;
    goto exit;
  }

  if (MaxHandles == 0) {
    LOGE("write_partition: Image partition not found\n");
    Status = EFI_NOT_FOUND;
    goto exit;
  }

  /* Get the Block IO protocol instance from the handle */
  BlkIo = HandleInfoList[0].BlkIo;

  /* Get the partition size and round it up to EFI_PAGE_SIZE */
  imgSize = (BlkIo->Media->LastBlock + 1) * BlkIo->Media->BlockSize;
  LOGI("write_partition: imgSize = 0x%x\n", imgSize);
  /* Get the to be write size and round it up to EFI_PAGE_SIZE */
  roundUpNbyte = ROUND_UP((nbyte + block_align_pre), BlkIo->Media->BlockSize);

  if (imgSize < (offset + nbyte)) {

    LOGE("write_partition: write out of range but  continue!, offset: 0x%x, nbyte: 0x%x\n", offset, nbyte); // should never happen
    Status = EFI_OUT_OF_RESOURCES;
    goto exit;
  }

  data_ptr = nvm_os_malloc(roundUpNbyte);

  if (data_ptr == NULL) {
    LOGE("write_partition: cannot allocate memory pool!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto exit;
  }

  memset(data_ptr, 0, roundUpNbyte);

  LOGI(" imgSize: 0x%x!, blockSize:0x%x, rod: 0x%x, block_align_pre: 0x%x\n", imgSize, BlkIo->Media->BlockSize, roundUpNbyte, block_align_pre);

  LOGI(" offset:0x%x, nbyte:0x%x, offset_block:0x%x\n", offset,nbyte, offset_block);
  Status = BlkIo->ReadBlocks(BlkIo, BlkIo->Media->MediaId, offset_block, roundUpNbyte, data_ptr);
  if (EFI_ERROR(Status)) {
    LOGE("write_partition: readblocks was unsuccessful, status: 0x%x\n", Status);
    goto exit;
  }

  if (block_align_pre + nbyte > roundUpNbyte){
	  LOGE("write_partition: Buffer overflow\n");
	  LOGE(" block_align_pre + nbyte:0x%x, nbyte:0x%x, roundUpNbyte: 0x%x\n", block_align_pre + nbyte,nbyte,roundUpNbyte);
	  Status = EFI_OUT_OF_RESOURCES;
	  goto exit;
  }

  memscpy(data_ptr+block_align_pre, nbyte, buff, nbyte);

  Status = BlkIo->WriteBlocks(BlkIo, BlkIo->Media->MediaId, offset_block, roundUpNbyte, data_ptr);
  if (EFI_ERROR(Status)) {

    LOGE("write_partition: writeblocks was unsuccessful\n");
    goto exit;
  }
  Status = EFI_SUCCESS;
exit:
  if (data_ptr) {
    nvm_os_free(data_ptr);
  }
  return Status;
}


void kmdf_doNothing(osfd_t fileHandle){
}


osfd_t kmdf_openFile(const char *pathname, int access)
{
    (void)access;
    int i = 0;
    size_t mem_size = 0;

    for (i = 0; i < MAX_NUM_OF_FILES; i ++) {
        if((mem_size = strlen(pathname)) == 0){         /* get pathname size and check it is not zero */
           LOGE("Open file -- file pathname 0\n");
           return 0;
        }
        if(FILE_PATH_SIZE < mem_size){            /* Assign the minimum b/w pathname and FILE_PATH_SIZE */
           mem_size = FILE_PATH_SIZE;
        }
        if(g_spNVMPartition_fileHandles[i].is_created == true && 
           0 == memcmp(g_spNVMPartition_fileHandles[i].file_name, pathname, mem_size)){
            //return file handle
            return (osfd_t)&g_spNVMPartition_fileHandles[i]; 
        }
        LOGI("Open file -- fileHandles[i].file_name: %a,is_created:%d, pathname: %a\n", g_spNVMPartition_fileHandles[i].file_name, g_spNVMPartition_fileHandles[i].is_created,pathname);
    }

    LOGE("Open file -- no file found\n");
    return 0;
}


/*
 return new file handle is avaliable
*/
osfd_t kmdf_createFile(const char *pathname, boolean is_skp, boolean is_backup, int access)
{
    EFI_STATUS          Status;
    //raw file system not access info.
    (void)access;
    (void)is_skp;
    int i = 0;

    LOGI("createFile-pathname: %a, strlen(pathname):%d\n", pathname, strlen(pathname));

    if(is_skp == true && is_backup == false){
       i = 0;
    }else if(is_skp == true && is_backup == true){
       i = 1;
    }else if(is_skp == false && is_backup == false){
       i = 2;
    }else if(is_skp == false && is_backup == true){
       i = 3;
    }else{
       LOGE("create file -- unable to determine partition index\n");
       return 0;
    }

    if(g_spNVMPartition_fileHandles[i].is_created == false){
       g_spNVMPartition_fileHandles[i].is_created = true;
       g_spNVMPartition_fileHandles[i].size = (i==1 ? NVM_SECTOR_SIZE*2 : NVM_MAX_FILE_SIZE);//NVM_MAX_FILE_SIZE;//
       memscpy(g_spNVMPartition_fileHandles[i].file_name, MIN(FILE_PATH_SIZE, strlen(pathname)), pathname, MIN(FILE_PATH_SIZE, strlen(pathname)));
       LOGI("create file -- MIN(FILE_PATH_SIZE, strlen(pathname)):%d, strlen(pathname): %d, &pathname[0]: 0x%x\n", MIN(FILE_PATH_SIZE, strlen(pathname)), strlen(pathname), &pathname[0]);
       //write back file meta data
       Status = kmdf_pWrite((uint8_t *)g_spNVMPartition_fileHandles, sizeof(osf_t)*MAX_NUM_OF_FILES, NVMFILEMETA_OFFSITE);
       if (EFI_ERROR(Status)) {
         //unable to update the file system meta data revert back.
         g_spNVMPartition_fileHandles[i].is_created = false;
         g_spNVMPartition_fileHandles[i].size = 0;
         memset(g_spNVMPartition_fileHandles[i].file_name, 0, sizeof(g_spNVMPartition_fileHandles[i].file_name));
         LOGE("create file -- unable to update the file system meta data\n");
         return 0;
       }
       LOGI("createFile success i = %d; vAddr=0x%x\n", i, g_spNVMPartition_fileHandles[i].vAddr);
    }

    return (osfd_t)&g_spNVMPartition_fileHandles[i];
}
/*
 reset nvm file status to free
 and clean the memory of file size
*/
int32_t kmdf_removeFile(const char *pathname)
{
    EFI_STATUS          Status;
    osf_t               spNVMPartition_fileHandles;
    int i = 0;
    size_t mem_size = 0;

    LOGI("removeFile-pathname: %a\n", pathname);

    for (i = 0; i < MAX_NUM_OF_FILES; i ++) {
        if((mem_size = strlen(pathname)) == 0){         /* get pathname size and check it is not zero */
           LOGE("Open file -- file pathname 0\n");
           return 0;
        }
        if(FILE_PATH_SIZE < mem_size){            /* Assign the minimum b/w pathname and FILE_PATH_SIZE */
           mem_size = FILE_PATH_SIZE;
        }
        if(g_spNVMPartition_fileHandles[i].is_created == true && 
           0 == memcmp(g_spNVMPartition_fileHandles[i].file_name, pathname, mem_size)){

            //found the file to be removed.
            //make a local copy of the meta data
            //
            memscpy((void *)&spNVMPartition_fileHandles, sizeof(osf_t), (void *)&g_spNVMPartition_fileHandles[i], sizeof(osf_t));
            //Set the file to free
            g_spNVMPartition_fileHandles[i].is_created = false;
            g_spNVMPartition_fileHandles[i].size = 0;
            memset(g_spNVMPartition_fileHandles[i].file_name, 0, sizeof(g_spNVMPartition_fileHandles[i].file_name));
            //write back file meta data
            Status = kmdf_pWrite((uint8_t *)g_spNVMPartition_fileHandles, sizeof(osf_t)*MAX_NUM_OF_FILES, NVMFILEMETA_OFFSITE);
            //Clean the data??? too slow?
            if (EFI_ERROR(Status)) {
                //unable to update the file system meta data revert back.
                memscpy((void *)&g_spNVMPartition_fileHandles[i], sizeof(osf_t), (void *)&spNVMPartition_fileHandles, sizeof(osf_t));
                LOGE("removeFile -- unable to update the file system meta data\n");
                return -1;
            }
        }
    }

    if (i == MAX_NUM_OF_FILES) {
        LOGE("removeFile -- Didn't find the file to remove\n"); 
    }
    return 0;
}


/**

 *Read file data from the SPU_NVM partition and returns the  
 *start address and total size.  
 *  
	@param[in]        fileHandle		     file to be read    
	@param[out]      *buf 		           Data read
 *@param[in]        nbyte              bytes to be read.
 *@param[in]        offset             offset to be read  


 * @retval        ssize_t                

**/
ssize_t kmdf_pReadFile(osfd_t _fileHandle_ptr,  void * buf, uint64_t nbyte, uint64_t offset)
{
    EFI_STATUS          Status = EFI_SUCCESS;
    osf_t*              fileHandle_ptr = (osf_t*)_fileHandle_ptr;
    uint64_t            remaining_nbyte = nbyte;
    uint64_t            remapped_nbyte  = nbyte;
    uint64_t            remapped_offset = 0;
    uint32_t            buf_offset      = 0;
    boolean             is_remapped     = false; 

    if (!fileHandle_ptr->is_created) {
      LOGE("File is not created\n");
      return EFI_INVALID_PARAMETER;
    }

    LOGI(" kmdf_pRead vAddr: 0x%x, offset: 0x%x, nbyte:0x%x\n", fileHandle_ptr->vAddr, offset, nbyte);
    if (fileHandle_ptr->vAddr == NVM_MAX_FILE_SIZE &&                           //it's segDb_1
        offset + nbyte > NVM_2ND_SECTOR_START_OFFSET) { //last byte to read should cross the duplicate data start address
      LOGI(" Need Remap");
      is_remapped = true;
    }
    //is_remapped = false;  //temp
    if (is_remapped == true) {
       if ((fileHandle_ptr->size + NVM_2_TO_8_SECTORS_SIZE) < (offset + nbyte)) {
        LOGE("File Out of range read Remap, file->vAddr:0x%x, offset:0x%x, nbyte: 0x%x\n",fileHandle_ptr->vAddr, offset, nbyte);
        return EFI_INVALID_PARAMETER;
      }
      //Read the 1st non-duplicated sector if any
      remapped_nbyte  =  (offset < NVM_SECTOR_SIZE) ? (NVM_SECTOR_SIZE - offset) : 0; //do we have anything to read for the 1st sector? Yes : No
      if (remapped_nbyte != 0) {
          remapped_offset =  offset;
          LOGI(" remapped kmdf_pRead1 remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x\n", remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset);
          Status = kmdf_pRead((uint8_t *)buf, remapped_nbyte, fileHandle_ptr->vAddr + remapped_offset);
          if (EFI_ERROR(Status)) {
            LOGE(" remapped kmdf_pRead1 failed");
            return -1;
          }
          buf_offset += remapped_nbyte;
      }

      //Read the 2st to 8 duplicated sector if any (either remaining bytes or full)
      remaining_nbyte  = nbyte - remapped_nbyte;
      if (remaining_nbyte !=0 && offset <= NVM_8TH_SECTOR_END_OFFSET) {
        //Update the new offset
        if(offset > NVM_2ND_SECTOR_START_OFFSET) {
          remapped_offset = offset; //only duplicated sectors
        }
        else {
          remapped_offset = NVM_SECTOR_SIZE;  //crossing from 1st sector
        }

        //Update the new number of byte to read
        if(offset + nbyte > NVM_8TH_SECTOR_END_OFFSET) {  //the last byte to read crosses the duplicate data end address.
          remapped_nbyte = NVM_8TH_SECTOR_END_OFFSET - remapped_offset + 1;
        }
        else {   //the last byte to read crossing the duplicated data end address, read the rest to the duplicated session
          remapped_nbyte = remaining_nbyte;
        }

        LOGI(" remapped kmdf_pRead2 buf_offset:0x%x, remapped_nbyte: 0x%x, remapped_offset: 0x%x\n", buf_offset, remapped_nbyte, remapped_offset);
        Status = kmdf_pRead((uint8_t *)(buf + buf_offset), remapped_nbyte, remapped_offset);  //Here there is no vAddr due to the assumption that duplicate data is in segDb_0
        if (EFI_ERROR(Status)) {
         LOGE(" remapped kmdf_pRead2 failed");
         return -1;
        }
        buf_offset      += remapped_nbyte;
      }

      //Read the 9th non-duplicated sector to the updated location if any
      remaining_nbyte -= remapped_nbyte;
      if (remaining_nbyte != 0) { //the last byte to read crosses the duplicate data end address. 
        //Update the new offset
        if(offset > NVM_8TH_SECTOR_END_OFFSET) {
          remapped_offset = offset - NVM_2_TO_8_SECTORS_SIZE; //only duplicated sectors
        }
        else {
          remapped_offset = NVM_SECTOR_SIZE;  //crossing from 1st sector
        }
        LOGI(" remapped kmdf_pRead3  buf_offset:0x%x, remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x\n", buf_offset, remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset);
        Status = kmdf_pRead((uint8_t *)(buf + buf_offset), remaining_nbyte, fileHandle_ptr->vAddr + remapped_offset);
      }
    }
    else {
      if (fileHandle_ptr->size < (offset + nbyte)) {
        LOGE("File Out of range write, file->vAddr:0x%x, offset:0x%x, nbyte: 0x%x\n",fileHandle_ptr->vAddr, offset, nbyte);
        return EFI_INVALID_PARAMETER;
      }
      LOGI(" remapped kmdf_pRead Regular buf_offset:0x%x, remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x\n", buf_offset, remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset);
      Status = kmdf_pRead(buf, nbyte, fileHandle_ptr->vAddr + offset);
    }
    if (EFI_ERROR(Status)) {
      LOGE(" kmdf_pRead failed");
      return -1;
    }
    else{
      return nbyte;
    }
}


/**

 *Write file data from the SPU_NVM partition 
 *  
	@param[in]        fileHandle		     file to be written   
	@param[in]        *buf 		           Data to write
 *@param[in]        nbyte              num of bytes to be write.
 *@param[in]        offset             offset to be write  


 * @retval        ssize_t                

**/
ssize_t kmdf_pWriteFile(osfd_t _fileHandle_ptr, const void * buf, uint64_t nbyte, uint64_t offset)
{
    EFI_STATUS          Status = EFI_SUCCESS;
    osf_t*              fileHandle_ptr  = (osf_t*)_fileHandle_ptr;
    uint64_t            remaining_nbyte = nbyte;
    uint64_t            remapped_nbyte  = nbyte;
    uint64_t            remapped_offset = 0;
    uint32_t            buf_offset      = 0;
    boolean             is_remapped     = false; 

    if (!fileHandle_ptr->is_created) {
      LOGE("File is not created\n");
      return EFI_INVALID_PARAMETER;
    }

    LOGI(" kmdf_pWrite vAddr: 0x%x, offset: 0x%x, nbyte:0x%x\n", fileHandle_ptr->vAddr, offset, nbyte);
    if (fileHandle_ptr->vAddr == NVM_MAX_FILE_SIZE &&                           //it's segDb_1
        offset + nbyte > NVM_2ND_SECTOR_START_OFFSET) { //last byte to write should cross the duplicate data start address
      LOGI(" Need Remap");
      is_remapped = true;
    }
    //is_remapped = false;  //temp
    if (is_remapped == true) {
      if ((fileHandle_ptr->size + NVM_2_TO_8_SECTORS_SIZE) < (offset + nbyte)) {
        LOGE("File Out of range write Remap, file->vAddr:0x%x, offset:0x%x, nbyte: 0x%x\n",fileHandle_ptr->vAddr, offset, nbyte);
        return EFI_INVALID_PARAMETER;
      }
      //Write the 1st non-duplicated sector if any
      remapped_nbyte  =  (offset < NVM_SECTOR_SIZE) ? (NVM_SECTOR_SIZE - offset) : 0;  //do we have anything to write for the 1st sector? Yes : No
      LOGI(" remapped kmdf_pWrite0 remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x, remaining_nbyte: 0x%x\n", remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset, remaining_nbyte);

      if (remapped_nbyte != 0) {
          remapped_offset =  offset;
          LOGI(" remapped kmdf_pWrite1 remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x\n", remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset);
          Status = kmdf_pWrite((uint8_t *)buf, remapped_nbyte, fileHandle_ptr->vAddr + remapped_offset);
          if (EFI_ERROR(Status)) {
            LOGE(" remapped kmdf_pWrite1 failed");
            return -1;
          }

          buf_offset += remapped_nbyte;
      }

      //Write the 2st to 8 duplicated sector if any (either remaining bytes or full)
      remaining_nbyte  = nbyte - remapped_nbyte;
      LOGI(" remapped2 kmdf_pWrite remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x, remaining_nbyte: 0x%x\n", remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset, remaining_nbyte);

      if (remaining_nbyte !=0 && offset <= NVM_8TH_SECTOR_END_OFFSET) {
    	LOGI(" remapped Write the 2st to 8 duplicated sector if any, remaining_nbyte:0x%x", remaining_nbyte);
        //Update the new offset
        if(offset >= NVM_2ND_SECTOR_START_OFFSET) {
          remapped_offset = offset; //only duplicated sectors
        }
        else {
          remapped_offset = NVM_SECTOR_SIZE;  //crossing from 1st sector
        }

        //Update the new number of byte to write
        if(offset + nbyte > NVM_8TH_SECTOR_END_OFFSET) {  //the last byte to write crosses the duplicate data end address.
          remapped_nbyte = NVM_8TH_SECTOR_END_OFFSET - remapped_offset;
        }
        else {   //the last byte to write not crossing the duplicated data end address, write the rest to the duplicated session
          remapped_nbyte = remaining_nbyte;
        }
        LOGI(" remapped kmdf_pWrite2 buf_offset:0x%x, remapped_nbyte: 0x%x, remapped_offset: 0x%x\n", buf_offset, remapped_nbyte, remapped_offset);
        Status = kmdf_pWrite((uint8_t *)(buf + buf_offset), remapped_nbyte, remapped_offset);  //Here there is no vAddr due to the assumption that duplicate data is in segDb_0;

        if (EFI_ERROR(Status)) {
         LOGE(" remapped kmdf_pWrite2 failed");
         return -1;
        }
        buf_offset      += remapped_nbyte;
      }

      //Write the 9th non-duplicated sector if any
      remaining_nbyte -= remapped_nbyte;
      LOGI(" remapped3 kmdf_pWrite remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x, remaining_nbyte: 0x%x\n", remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset, remaining_nbyte);

      if (remaining_nbyte != 0) { //the last byte to write crosses the duplicate data end address. 
    	LOGI(" remapped Write the 9th sector if any, remaining_nbyte:0x%x", remaining_nbyte);
        //Update the new offset
        if(offset > NVM_8TH_SECTOR_END_OFFSET) {
          remapped_offset = offset - NVM_2_TO_8_SECTORS_SIZE; //only duplicated sectors
          LOGI(" offset > NVM_8TH_SECTOR_END_OFFSET, remapped_offset:0x%x", remapped_offset);
        }
        else {
          remapped_offset = NVM_SECTOR_SIZE;  //crossing from 1st sector
          LOGI(" offset <- NVM_8TH_SECTOR_END_OFFSET, remapped_offset:0x%x", remapped_offset);
        }
        LOGI(" remapped kmdf_pWrite3  buf_offset:0x%x, remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x\n", buf_offset, remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset);

        Status = kmdf_pWrite((uint8_t *)(buf + buf_offset), remaining_nbyte, fileHandle_ptr->vAddr + remapped_offset);
      }
    }
    else {
          if (fileHandle_ptr->size < (offset + nbyte)) {
            LOGE("File Out of range write, file->vAddr:0x%x, offset:0x%x, nbyte: 0x%x\n",fileHandle_ptr->vAddr, offset, nbyte);
            return EFI_INVALID_PARAMETER;
          }
          Status = kmdf_pWrite((uint8_t *)buf, nbyte, fileHandle_ptr->vAddr + offset);
          LOGI(" remapped kmdf_pWrite Regular buf_offset:0x%x, remapped_nbyte: 0x%x, vAddr: 0x%x, remapped_offset: 0x%x\n", buf_offset, remapped_nbyte, fileHandle_ptr->vAddr, remapped_offset);
    }
    if (EFI_ERROR(Status)) {
      LOGE(" kmdf_pWrite failed");
      return -1;
    }
    else{
      return nbyte;
    }
}


/*
  called upon SpNvmDxe start. Initialize/read fileSystemMeta data
*/
void fileSystemInit()
{
    EFI_STATUS            Status;

    //Read metadata from partition
    Status = kmdf_pRead((uint8_t *)g_spNVMPartition_fileHandles, sizeof(osf_t)*MAX_NUM_OF_FILES, NVMFILEMETA_OFFSITE);
	//check whether meta data is initialized by checking Magic
    if (g_spNVMPartition_fileHandles[0].magic == NVMFILEMETA_MAGIC_ID) {
      /* file system is already initialized */
      LOGI("File system present from previous power cycle\n");
      return;
    }
  
    //if initialized populate the globle file handles with the values
    for (int i = 0; i < MAX_NUM_OF_FILES; i ++) {
      g_spNVMPartition_fileHandles[i].magic = NVMFILEMETA_MAGIC_ID;
      g_spNVMPartition_fileHandles[i].is_created = false;
      g_spNVMPartition_fileHandles[i].size = 0;
      //g_spNVMPartition_fileHandles[i].vAddr = NVM_MAX_FILE_SIZE * i;
      memset (g_spNVMPartition_fileHandles[i].file_name, 0, sizeof(g_spNVMPartition_fileHandles[i].file_name));
    }

    g_spNVMPartition_fileHandles[0].vAddr = SEGDB_0_VADDR;
    g_spNVMPartition_fileHandles[1].vAddr = SEGDB_1_VADDR;
    g_spNVMPartition_fileHandles[2].vAddr = DATA_0_VADDR;
    g_spNVMPartition_fileHandles[3].vAddr = DATA_1_VADDR;

    LOGI(" Do kmdf_pWrite for filesys meta data!\n");
    //if not initialize the globle handles and write back to the partition
    Status = kmdf_pWrite((uint8_t *)g_spNVMPartition_fileHandles, sizeof(osf_t)*MAX_NUM_OF_FILES, NVMFILEMETA_OFFSITE);
    LOGI("status:0x%x", Status);
}


void * new (const void * _class, ...)
{ 
    const struct Class * class = _class;
    void * p = nvm_os_malloc(class->size);
     ASSERT(p);
    * (const struct Class **) p = class;
    if (class->ctor) {   
        va_list ap;
        va_start(ap, _class);
        p = class->ctor(p, & ap);
        va_end(ap);
    }
    return p;
}


void delete (void * self)
{ 
    const struct Class ** cp = self;
    if (self && * cp && (* cp)->dtor) {
        (* cp)->dtor(self);
    }
    nvm_os_free(self);
}

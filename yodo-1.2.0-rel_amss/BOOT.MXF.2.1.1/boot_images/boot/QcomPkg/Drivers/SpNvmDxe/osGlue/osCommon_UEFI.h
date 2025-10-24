/*========================================================================
osCommon_UEFI.h
This file describe the implementation of the CreatePartitionOp class.
1. [mutex] (WIP: for multi-thread UEFI config) 
2. [assert] (WIP: not used) 
3. [common type define] (according the UEFI coding protocol?)
4. [thread operations] (WIP: for multi-thread UEFI config) 
5. file: 
  a. macro define
  b. file operations (raw_xxx)
  c. file generic operations def (os_xxx)
6. new/delete in c format.
 
7. define class 
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
 07/29/21   vp      Logging improvements
 03/09/20   ll      initial release
=============================================================================*/
#ifndef _OS_COMMON_UEFI_
#define _OS_COMMON_UEFI_

#include <comdef.h>
#include <stdarg.h>

#undef SPNVMDXE_DEBUG  //define this flag to increase verbosity

#ifdef SPNVMDXE_DEBUG
#define LOGI(fmt, x...) DEBUG ((EFI_D_INFO, fmt"\n", ##x))
#define LOGD(fmt, x...) DEBUG ((EFI_D_VERBOSE, fmt"\n", ##x))
#else
#define LOGI(fmt, x...)
#define LOGD(fmt, x...)
#endif

#define LOGE(fmt, x...) DEBUG ((EFI_D_ERROR, fmt"\n", ##x))

#define OS_O_RDONLY 0x0000
#define OS_O_WRONLY 0x0001
#define OS_O_RDWR   0x0002


#define NVM_HANA_HEADER_VERSION 3
#define NVM_KONA_HEADER_VERSION 4

//File meta data
#define MAX_NUM_OF_FILES 4
#define NVMFILEMETA_OFFSITE 0x22000
/* NVM File magic */
#define NVMFILEMETA_MAGIC_ID ((size_t)(0x11223344))
/* NVM max file size */
#define NVM_MAX_FILE_SIZE 0x9000
#define FILE_PATH_SIZE    512

#define NVM_SECTOR_SIZE 0x1000

#define NVM_2ND_SECTOR_START_OFFSET 0x1000

#define NVM_8TH_SECTOR_END_OFFSET 0x7FFF

#define NVM_9TH_SECTOR_FILE1_START_OFFSET 0x1000

#define NVM_2_TO_8_SECTORS_SIZE 7*NVM_SECTOR_SIZE //0x8000

#define SEGDB_0_VADDR 0
#define SEGDB_1_VADDR 0x9000
#define DATA_0_VADDR  0xB000
#define DATA_1_VADDR  0x14000

void fileSystemInit();
typedef struct osf_t {
    size_t magic;
    boolean is_created;
    size_t size;
    uint32_t vAddr;   //this is the offset from secnvm partition. this is determined by which file info are you
    char file_name[FILE_PATH_SIZE];  //use file path as file name
} osf_t;

typedef uintptr_t osfd_t;

#define OS_FD_INVALID      0
#define OS_IS_FD_VALID(fd_ptr) (fd_ptr != 0)
#define OS_IS_FD_INVALID(fd_ptr) (fd_ptr == 0)

#define ROOT_PATH  ""

EFI_STATUS kmdf_pRead(uint8_t *buf, uint64_t nbyte, uint64_t offset);
EFI_STATUS kmdf_pWrite(uint8_t *buff, uint64_t buff_len, uint64_t offset);
osfd_t kmdf_openFile(const char *pathname, int access);
osfd_t kmdf_createFile(const char *pathname, boolean is_skp, boolean is_backup, int access);
int32_t kmdf_removeFile(const char *pathname);
ssize_t kmdf_pReadFile(osfd_t _fileHandle, void * buf, uint64_t nbyte, uint64_t offset);
ssize_t kmdf_pWriteFile(osfd_t _fileHandle, const void * buf, uint64_t nbyte, uint64_t offset);

#define os_snprintf snprintf
#define os_strncpy strlcpy

//osfd_t os_open(const char *pathname, int access)
#define os_open_segment_file(pathname, access) kmdf_openFile(pathname, access)
//osfd_t os_create(const char *pathname, int access)
#define os_create_segment_file(pathname, is_skp, is_backup) kmdf_createFile(pathname, is_skp, is_backup, OS_O_WRONLY)
//int os_remove(const char* filename)
#define os_remove(pathname) kmdf_removeFile(pathname)


//ssize_t os_pread(osfd_t fd, void* buf, size_t nbytes, off_t offset)
#define os_pread(fd, buf, nbyte, offset) kmdf_pReadFile(fd, buf, nbyte, offset)
//ssize_t os_pwrite (osfd_t fd, const void* buf, size_t n, off_t offset)
#define os_pwrite(fd, buf, nbyte, offset) kmdf_pWriteFile(fd, buf, nbyte, offset)


struct Class {
  size_t size;
  void * (* ctor) (void * self, va_list * app);
  void (* dtor) (void * self); 
};

void * new (const void * _class, ...);
void delete (void * self);

#define ENOENT 2
#define ENOMEM   12 /* 12 Out of Memory */
#define EBUSY    16 /* 16 Device or resource busy */
#define EEXIST   17 /* 17 File exists */
#define ENODEV   19 /* 19 No such device */ 
#define EINVAL   22 /* 22   Invalid argument */
#define ENOBUFS	 55	/* 55 No buffer space available */
#define EILSEQ   85/* 85   Illegal byte sequence */
#define EBADMSG  88 /* 88   Bad message */ 
#define SUCCESS EFI_SUCCESS

void* nvm_os_malloc (size_t size);
void nvm_os_free (void *pMem);
#endif /* _OS_COMMON_UEFI_ */

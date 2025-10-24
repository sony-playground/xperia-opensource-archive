
/**
@file  EfiFV.h
@brief FV UEFI Protocol definitions.
*/
/*=============================================================================
Copyright (c) 2019-2020 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
03/04/20   cm      added API LoadFileFromFv
08/16/19   md      Initial revision

=============================================================================*/
#ifndef __EFI_FV_UTILS_H_
#define __EFI_FV_UTILS_H_

/*===========================================================================
INCLUDE FILES
===========================================================================*/

/*===========================================================================
MACRO DECLARATIONS
===========================================================================*/
/* Protocol version. */
/*
 *   Document the version changes here
 *   V 1.0
 *      Initial version
 *   V 1.1
 *       added API LoadFileFromFv
 */

/** @defgroup efi_fv_utils_protocol EFI_FV_UTILS_PROTOCOL
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  efi_fv_utils_protocol_prot PROTOCOL
 *  @ingroup efi_fv_utils_protocol 
 */ 
 /** @defgroup  efi_fv_utils_protocol_apis APIs
 *  @ingroup efi_fv_utils_protocol 
 */ 

/** @defgroup  efi_fv_utils_protocol_data DATA_STRUCTURES
 *  @ingroup efi_fv_utils_protocol 
 */ 

/** @ingroup efi_fv_utils_protocol_data
@{ */
#define EFI_FV_UTILS_PROTOCOL_VER_INIT_VER       0x00010000
#define EFI_FV_UTILS_PROTOCOL_LOAD_FILE_VER      0x00010001

#define EFI_FV_UTILS_PROTOCOL_VERSION   EFI_FV_UTILS_PROTOCOL_LOAD_FILE_VER

/* Protocol GUID definition */
#define EFI_FV_UTILS_PROTOCOL_GUID \
        { 0xbc9b4091, 0x6f29, 0x48b6,{ 0xbf, 0x34, 0x3e, 0xdd, 0x20, 0x8f, 0xa0, 0x0a } };
/** @} */ /* end_ingroup efi_fv_utils_protocol_data */
/*===========================================================================
EXTERNAL VARIABLES
===========================================================================*/
/* External reference to the FV Protocol GUID. */
extern EFI_GUID gEfiFVUtilsProtocolGuid;

/*===========================================================================
TYPE DEFINITIONS
===========================================================================*/
/** @ingroup efi_fv_utils_protocol_prot 
 * Protocol declaration */
typedef struct _EFI_FV_UTILS_PROTOCOL EFI_FV_PROTOCOL;



/*===========================================================================
FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_Launch_App_From_Guided_Fv */
/** @ingroup efi_fv_utils_protocol_apis
 * Launches an app from a guided FV. Depends on FV being
   accessible as a simple file system

   FvGuid     Guid of FV to launch app from
   AppName    Ascii name of app to launch
   Args       Ascii command line args to pass to app *
*/
typedef
EFI_STATUS
(EFIAPI *EFI_LAUNCH_APP_FROM_GUIDED_FV)(IN EFI_FV_PROTOCOL     *This,
                                        EFI_GUID *FvGuid, 
                                        CHAR8    *AppName, 
                                        CHAR8    *Args);


/* EFI_Load_File_From_Guided_Fv */
/** @ingroup efi_fv_utils_protocol_apis
 * Reads a file into buffer from a specified guided FV. 
   Buffer is allocated within function and FileSize contains
   size read in bytes. If FvGuid is NULL, it searches in all
   loaded FVs.
   
   It is the caller's responsibility to free the buffer

   FvGuid     Guid of FV to launch app from
   FileName   File to be read 
   FileBuffer Buffer to to be read into
   FileSize   Size in bytes of file read
*/
typedef
EFI_STATUS
(EFIAPI *EFI_LOAD_FILE_FROM_GUIDED_FV)(IN EFI_FV_PROTOCOL	*This,
                                       EFI_GUID	  *FvGuid, 
                                       CHAR8      *FileName,
									   OUT UINT8  **FileBuffer,
									   OUT UINTN  *FileSize);


/** @ingroup efi_fv_utils_protocol_apis
 EFI_Guided_Fv_Is_Mounted */
/* Checks if the FV matching "FvGuid" has been mounted */
typedef
BOOLEAN
(EFIAPI *EFI_GUIDED_FV_IS_MOUNTED)(IN EFI_FV_PROTOCOL     *This,
                                   IN EFI_GUID *FvGuid);

/* EFI_Mount_Desired_FvF_rom_Partition */
/** @ingroup efi_fv_utils_protocol_apis
  This function mounts a desired FV (firmware volume) passed as an argument from Partition.
  The Partition might contain recursive FV as well which in that case the buffer will have Filesystem 
  data loaded. If needed it is decompresses and then mounted.

  @param[in]  FvPartitionName     String name of the FV to be mounted
  @param[in]  PartitionGuid       Partition GUID of the FV to be mounted
  @param[in]  DesiredFvGuid       GUID of desired FV to be mounted
  @param[in]  DesiredFVFileGUID   Optional FVFile Guid (FFS Name) to mount if recursive (stops further recursion on finding this file)

  @retval  EFI_SUCCESS           The Firmware volume is found and successfully mounted.
  @ret_val EFI_INVALID_PARAMETER Input parameter missing. 
**/
typedef
EFI_STATUS
(EFIAPI *EFI_MOUNT_DESIRED_FV_FROM_PARTITION)(IN EFI_FV_PROTOCOL     *This,
                                              IN  CONST CHAR8   *FvPartitionName, 
                                              IN  EFI_GUID      *PartitionGuid, 
                                              IN  EFI_GUID      *DesiredFvGuid,
                                              IN  EFI_GUID      *DesiredFVFileGUID);


/*===========================================================================
PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_fv_utils_protocol_prot
EFI_FV_UTILS_PROTOCOL Protocol interface.
*/
struct _EFI_FV_UTILS_PROTOCOL {
    UINT64                               Version;
    EFI_MOUNT_DESIRED_FV_FROM_PARTITION  MountFVFromPartition;
    EFI_GUIDED_FV_IS_MOUNTED             CheckIfFvMounted;
    EFI_LAUNCH_APP_FROM_GUIDED_FV        LaunchAppFromFv;
	EFI_LOAD_FILE_FROM_GUIDED_FV		 LoadFileFromFv;
};

#endif  /* __EFI_FV_H_ */


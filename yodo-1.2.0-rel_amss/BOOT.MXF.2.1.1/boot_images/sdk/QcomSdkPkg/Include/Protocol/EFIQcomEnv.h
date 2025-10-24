/**
  @file  EFIQcomEnv.h
  @brief Qualcomm Environment EFI protocol interface.
*/
/*=============================================================================
  Copyright (c) 2018, 2020-2021 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/


/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/23/21   pb       Added IsUefiEnhanced() API
 03/30/21   yw       Added method GetSimpleMemRegionInfoByName().
 06/18/20   yw       Added GetCmdLineArgs(), LoadFileFromPartition(), GetBlkIOHandles(),
                     GetUUID(), GetProcessorName(), DeleteFile(), ReadFile(), WriteFil()
                     from QcomLib
 03/03/20   cm       Added GetTimerCountu/ms() APIs
 10/03/18   kpa      Initial Draft

=============================================================================*/

#ifndef __EFIQCOMENV_H__
#define __EFIQCOMENV_H__

#include <QcomEnvType.h>

/** @defgroup EFI_QCOMENV_PROTOCOL 
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  EFI_QCOMENV_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_QCOMENV_PROTOCOL 
 */ 
 /** @defgroup  EFI_QCOMENV_PROTOCOL_apis APIs
 *  @ingroup EFI_QCOMENV_PROTOCOL 
 */ 

/** @defgroup  EFI_QCOMENV_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_QCOMENV_PROTOCOL 
 */ 
 
/** @cond */
typedef struct _EFI_QCOMENV_PROTOCOL EFI_QCOMENV_PROTOCOL;
/** @endcond */

/** @addtogroup EFI_QCOMENV_PROTOCOL_data
@{ */
/**
  Protocol version.
  Document the version changes here
 *   V 1.1
 *      Initial version
 *   V 1.2
 *       added API GetTimerCountus
 *         added API GetTimerCountms
 *   V 1.3
 *       added API GetSimpleMemRegionInfoByName
 *   V 1.4
 *       added API IsUefiEnhanced 
*/
#define EFI_QCOMENV_PROTOCOL_INIT_VER               0x00010001
#define EFI_QCOMENV_PROTOCOL_GET_TIMER_VER          0x00010002
#define EFI_QCOMENV_PROTOCOL_GET_MEMINFO_VER        0x00010003
#define EFI_QCOMENV_PROTOCOL_IS_UEFI_ENHANCED_VER   0x00010004

#define EFI_QCOMENV_PROTOCOL_REVISION   EFI_QCOMENV_PROTOCOL_IS_UEFI_ENHANCED_VER
/** @} */ /* end_addtogroup efi_qcomenv_constants */

/*  Protocol GUID definition */
/** @ingroup efi_qcomenv_protocol */
#define EFI_QCOMENV_PROTOCOL_GUID \
  { 0xDC241E53, 0x498B, 0x3B59, { 0xAD, 0x17, 0xC8, 0xB2, 0x9E, 0x6B, 0x36, 0xA8 } }  

 
/** @cond */
/**
  External reference to the Qualcomm Environment Protocol GUID defined
  in the .dec file.
*/
extern EFI_GUID gEfiQcomEnvProtocolGuid;
/** @endcond */


/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/
/* ============================================================================
**  Function : EFI_QcomEnv_SetDdrThroughputLow
** ============================================================================
*/
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  @par Summary
  Sets DDR CPU busbandwith npa vote for low freq

  @param[in]      This               Pointer to the EFI_QCOMENV_PROTOCOL instance.


  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_NOT_READY         -- Protocol Dependencies not satisfied. \n
  EFI_BUFFER_TOO_SMALL  -- Input ResetReasonString buffer is not long enough,
                           Length will be returned in ResetReasonStrLen
*/
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_SETDDRTHROUGHPUTLOW)(
   IN EFI_QCOMENV_PROTOCOL       *This
   );
   
/* =========================================​===================================
**  Function : EFI_QcomEnv_GetTimerCountus
** =========================================​===================================
*/
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  @par Summary
  Get Running time in uS based on the Arch Timer Counter.
  This could get wrapped around based on the resolution and Speed. So
  use with caution.
  If the Timer is 32 bit running at 19.2 MHz, it would wrap around, to 0
  after 223 Sec
  @return
  Integer of 32 bit type
*/
typedef
UINTN
(EFIAPI *EFI_QCOMENV_GETTIMERCOUNTUS)(
    IN EFI_QCOMENV_PROTOCOL *This
);

/* =========================================​===================================
**  Function : EFI_QcomEnv_GetTimerCountms
** =========================================​===================================
*/
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  @par Summary
  Get Running time in mS based on the Arch Timer Counter.
  This could get wrapped around based on the resolution and Speed. So
  use with caution.
  If the Timer is 32 bit running at 19.2 MHz, it would wrap around, to 0
  after 223 Sec
  @return
  Integer of 32 bit type
*/

typedef
UINTN
(EFIAPI *EFI_QCOMENV_GETTIMERCOUNTMS)(
    IN EFI_QCOMENV_PROTOCOL *This
);


/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Extract the Command line arguments from the Image handle, process them and return
  in Argc, Argv format.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image to extract Cmd line
  @param[in] ArgcPtr        Pointer to Argc count variable.
  @param[in] ArgvArrayPtr   Pointer to Argv variable. If Argc>0 then Argv need to be freed using
                             FreePool call
  
  @retval EFI_SUCCESS           Successfully processed
  @retval EFI_OUT_OF_RESOURCES  Failed to allocate memory for the buffers
**/
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_GETCMDLINEARGS)(
    IN EFI_QCOMENV_PROTOCOL* This,
    IN  EFI_HANDLE           ImageHandle,
    OUT UINTN*               ArgcPtr,
    OUT CHAR8***             ArgvArrayPtr
    );
            

/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Loads a  file from a partition specified by Root Device type GUID
  Partition Type GUID and Block IO attributes

  @param  Path            Path to Smbios file
  @param  RootDeviceType  Root Device Type GUID
  @param  Partition Type  GUID eg: gEfiPartTypeSystemPartGuid
  @param  PartitionLabel  eg: L"logfs"
  @param  BlkIOAttrib     Attributes to be used for fetching Block IO handle
  @param  ReadFileSize    Ptr that can hold read file size

  @return EFI_SUCCESS if successful
**/
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_LOADFILEFROMPARTITION)(
   IN EFI_QCOMENV_PROTOCOL* This,
   UINT32                    BlkIOAttrib,
   CHAR16                    *Path,
   EFI_GUID                  *RootDeviceType,
   EFI_GUID                  *PartitionType,
   CHAR16                    *PartitionLabel,
   UINT8                     **CfgBuffPtr,
   UINTN                     *ReadFileSize
   );
            
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Returns a list of BlkIo handles based on required criteria
  SelectionAttrib : Bitmask representing the conditions that need
                    to be met for the handles returned. Based on the
                    selections filter members should have valid values.
  FilterData      : Instance of Partition Select Filter structure that
                    needs extended data for certain type flags. For example
                    Partition type and/or Volume name can be specified.
  HandleInfoPtr   : Pointer to array of HandleInfo structures in which the
                    output is returned.
  MaxBlkIopCnt    : On input, max number of handle structures the buffer can hold,
                    On output, the number of handle structures returned.

  @retval EFI_SUCCESS if the operation was successful
 */
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_GETBLKIOHANDLES) (
   IN EFI_QCOMENV_PROTOCOL   *This,
   IN  UINT32                SelectionAttrib,
   IN  PartiSelectFilter     *FilterData,
   OUT HandleInfo            *HandleInfoPtr,
   IN OUT  UINT32*           MaxBlkIopCnt
   );
  
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
**/  
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_GETUUID)(
   IN EFI_QCOMENV_PROTOCOL* This,
   OUT VOID                 *Buffer,
   IN UINT32                BufferSize
);
   
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
 * Get processor name string
 *
 * @param  ProcNameStr   Pointer to buffer where result can be expected
 * @param  StrSize       Size of the buffer
 *
 * @return EFI_SUCCESS if successful
 
 * **/
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_GETPROCESSORNAME) (
    IN EFI_QCOMENV_PROTOCOL* This,
    IN OUT  CHAR8*           ProcNameStr,
    IN      UINTN            StrSize
    );
                  
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Delete a  file from specified partition
  @param  Path            Path to Smbios file
  @param  RootDeviceType  Root Device Type GUID
  @param  Partition Type  GUID eg: gEfiPartTypeSystemPartGuid
  @param  PartitionLabel      eg: L"logfs"
  @param  SelectNonRemovable  TRUE for Non-removable / FALSE for Removable
  @param  Volumename          VolumeName to match
  @return EFI_SUCCESS if successful
**/

typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_DELETEFILE) (
  IN EFI_QCOMENV_PROTOCOL* This,
  IN  CHAR16               *Path,
  IN  EFI_GUID             *RootDeviceType,
  IN  EFI_GUID             *PartitionType,
  IN  CHAR16               *PartitionLabel,
  IN  BOOLEAN              SelectNonRemovable,
  IN  CHAR8                *VolumeName
  );
  
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Read a file to a buffer

  @param  Path                File path
  @param  RootDeviceTypeGuid  eg: gEfiEmmcGppPartition1Guid
  @param  PartitionType       eg: gEfiPlatPartitionTypeGuid
  @param  PartitionLabel      eg: L"logfs"
  @param  SelectNonRemovable  TRUE for Non-removable / FALSE for Removable
  @param  Volumename          VolumeName to match
  @param  BytesToRead         # of bytes to read from file
  @param  ReadOffset          Read-offset in file in bytes
  @param  FileBuffer          Data read from file is copied to FileBuffer
  @param  FileBufferSize      Size of the file
  @return EFI_SUCCESS         If file was read successfully

**/
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_READFILE)(
  IN EFI_QCOMENV_PROTOCOL*  This,
  IN     CHAR16             *Path,
  IN     EFI_GUID           *RootDeviceType,
  IN     EFI_GUID           *PartitionType,
  IN     CHAR16             *PartitionLabel,
  IN     BOOLEAN            SelectNonRemovable,
  IN     CHAR8              *VolumeName,
  IN OUT UINTN              *BytesToRead,
  IN     UINT64             ReadOffset,
  OUT    UINT8              *FileBuffer,
  IN     UINT32             FileBufferSize
  );
  
  

/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Write a buffer to a file

  @param  Path                File path
  @param  RootDeviceTypeGuid  eg: gEfiEmmcGppPartition1Guid
  @param  PartitionType       eg: gEfiPlatPartitionTypeGuid
  @param  PartitionLabel      eg: L"logfs"
  @param  SelectNonRemovable  TRUE for Non-removable / FALSE for Removable
  @param  Volumename          VolumeName to match
  @param  BytesToRead         # of bytes to write to file
  @param  WriteOffset         Write-offset in file in bytes
  @param  FileBuffer          Data written to a file is copied from FileBuffer
  @param  FileBufferSize      Size of the file
  @return EFI_SUCCESS         If file was written successfully

**/
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_WRITEFILE)(
  IN EFI_QCOMENV_PROTOCOL* This,
  IN     CHAR16           *Path,
  IN     EFI_GUID         *RootDeviceType,
  IN     EFI_GUID         *PartitionType,
  IN     CHAR16           *PartitionLabel,
  IN     BOOLEAN          SelectNonRemovable,
  IN     CHAR8            *VolumeName,
  IN     UINTN            *BytesToWrite,
  IN     UINT64           WriteOffset,
  IN     UINT8            *FileBuffer,
  IN     UINT32           FileBufferSize
  );

/** @ingroup EFI_QCOMENV_PROTOCOL_data
**/
#define MAX_MEM_LABEL_NAME2 32
typedef struct
{
  CHAR8                        Name[MAX_MEM_LABEL_NAME2];   // Region Name in ASCII
  UINT64                       MemBase;                    // Offset to DDR memory base
  UINT64                       MemSize;                    // Size (in bytes) of the memory region
} SimpleMemRegionInfo;
  
/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Get Memory Region information structure created by parsing the
  platform config file

  @param  RegionName             Pointer to ASCII region name in configuration file
  @param  MemRegionInfo          Pointer to MemRegionInfo, allocated by caller,
                                 returns copy in same struct, cannot be NULL

  @retval EFI_SUCCESS            Successfully retrieved the entry
  @retval EFI_NOT_FOUND          Unable to find specified entry in table
  @retval EFI_NOT_READY          Error: Config SharedLib is not initialized
  @retval EFI_INVALID_PARAMETER  RegionName or MemoryRegion is NULL
**/
  
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_GET_SIMPLE_MEMREGION_INFO_BY_NAME) (
  IN EFI_QCOMENV_PROTOCOL*      This,
  IN     CHAR8                  *RegionName, 
  OUT    SimpleMemRegionInfo    *SimpleMemoryRegion
  );

/** @ingroup EFI_QCOMENV_PROTOCOL_apis
  Finding Uefi is Monetized or not

  Level      : On Input, Enhanced level value the buffer can hold
               On Output, Enhanced level can be returned 
                           
  @return EFI_SUCCESS           If Success
**/
typedef
EFI_STATUS
(EFIAPI *EFI_QCOMENV_ISUEFIENHANCED)(
  IN EFI_QCOMENV_PROTOCOL*      This,
  IN OUT UINT32*                Level
  );
  
/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup EFI_QCOMENV_PROTOCOL_prot
  @par Summary
  Qualcomm Environment Protocol interface.

  @par Parameters
*/
struct _EFI_QCOMENV_PROTOCOL {
   UINT64                                                  Revision;
   EFI_QCOMENV_SETDDRTHROUGHPUTLOW                         SetDdrThroughputLow;// this is deprecated
   EFI_QCOMENV_GETTIMERCOUNTUS                             GetTimerCountus;
   EFI_QCOMENV_GETTIMERCOUNTMS                             GetTimerCountms;
   EFI_QCOMENV_GETCMDLINEARGS                              GetCmdLineArgs;
   EFI_QCOMENV_LOADFILEFROMPARTITION                       LoadFileFromPartition;
   EFI_QCOMENV_GETBLKIOHANDLES                             GetBlkIOHandles;
   EFI_QCOMENV_GETUUID                                     GetUUID;
   EFI_QCOMENV_GETPROCESSORNAME                            GetProcessorName;
   EFI_QCOMENV_DELETEFILE                                  DeleteFile;
   EFI_QCOMENV_READFILE                                    ReadFile;
   EFI_QCOMENV_WRITEFILE                                   WriteFile;
   /* only available in EFI_QCOMENV_PROTOCOL_GET_MEMINFO_VER/V1.3 support */
   EFI_QCOMENV_GET_SIMPLE_MEMREGION_INFO_BY_NAME           GetSimpleMemRegionInfoByName;   
   /* only available in EFI_QCOMENV_PROTOCOL_IS_UEFI_ENHANCED_VER/V1.4support */
   EFI_QCOMENV_ISUEFIENHANCED                              IsUefiEnhanced;   
};

#endif /* __EFIQCOMENV_H__ */


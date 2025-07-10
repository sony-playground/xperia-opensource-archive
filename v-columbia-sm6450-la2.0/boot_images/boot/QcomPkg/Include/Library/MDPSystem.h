#ifndef __MDPSYSTEM_H__
#define __MDPSYSTEM_H__
/*=============================================================================

  File: MDPTypes.h

  Header file for common driver types


  Copyright (c) 2011-2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <Protocol/EFIChipInfoTypes.h>
#include "MDPTypes.h"

/*===========================================================================

                                 Defines

===========================================================================*/


/* Enumeration of the available log levels in the system
 */
typedef enum
{
  MDP_LOGLEVEL_ERROR,
  MDP_LOGLEVEL_WARN,
  MDP_LOGLEVEL_INFO,
} MDP_LogLevel;

/* Maximum size of a single environment variable (in bytes)
 */
#define MDP_OSAL_MAX_ENVVAR_SIZE                      64

/* Define Display Configuration related information in IMEM
*/
#define DISPLAY_BOOT_IMEM_SIZE                        32   /* bytes */
#define DISPLAY_BOOT_HEADER_ID                        0xA
#define DISPLAY_BOOT_HEADER_ID_MASKT                  0xF
#define DISPLAY_BOOT_HEADER_ID_SHIFT                  28
#define DISPLAY_BOOT_HEADER_ADDRTYPE_MASK             0x1
#define DISPLAY_BOOT_HEADER_ADDRTYPE_SHIFT            27
#define DISPLAY_BOOT_HEADER_FRAMEBUFFER1SIZE_MASK     0x7F
#define DISPLAY_BOOT_HEADER_FRAMEBUFFER1SIZE_SHIFT    20
#define DISPLAY_BOOT_HEADER_FRAMEBUFFER2SIZE_MASK     0x7F
#define DISPLAY_BOOT_HEADER_FRAMEBUFFER2SIZE_SHIFT    12
#define DISPLAY_BOOT_HEADER_PLATFORMID_MASK           0x7
#define DISPLAY_BOOT_HEADER_PLATFORMID_SHIFT          8
#define DISPLAY_BOOT_HEADER_CHECKSUM_MASK             0xFF
#define DISPLAY_BOOT_HEADER_CHECKSUM_SHIFT            0

#ifdef RAMDUMP_MODE
	#define MDP_Log_Message(level, fmt, ...) 
#else
	#define MDP_Log_Message(level, fmt, ...)          MDP_Log_MessageEx(level, fmt, ##__VA_ARGS__);
#endif

/* This is the Display Configuration in IMEM */
#define IMEM_DISPLAY_CONFIG_OFFSET                    0x0002ABA4
#define IMEM_DISPLAY_BOOT_CONFIG_ADDR                 (SYSTEM_IMEM_BASE + IMEM_DISPLAY_CONFIG_OFFSET)

/*===========================================================================

                                Helper Macros

===========================================================================*/
#define MDP_MIN(_a_, _b_) \
    (((_a_)<(_b_))?(_a_):(_b_))

#define MDP_MAX(_a_, _b_) \
    (((_a_)>(_b_))?(_a_):(_b_))



/*===========================================================================

                                Enumeration

===========================================================================*/



/* PCD values for the PCD entry  gQcomTokenSpaceGuid.PcdExtDisplayType
 */
typedef enum
{
  PCD_EXTERNAL_DISPLAY_NONE    = 0,
  PCD_EXTERNAL_DISPLAY_DP      = 1,
  PCD_EXTERNAL_DISPLAY_HDMI    = 2,
  PCD_EXTERNAL_DISPLAY_MAX,
  PCD_EXTERNAL_DISPLAY_FORCE_32BIT = 0x7FFFFFFF
} ExternalDisplayPCDType;

/* MDP Variable Flag Type
 */
typedef enum
{
  MDP_VARIABLE_FLAG_NONE          = 0,
  MDP_VARIABLE_FLAG_NON_VOLATILE  = 1,
  MDP_VARIABLE_FLAG_MAX,
} MDPVariableFlagType;

/* MDP Boot Platform ID Type
 */
typedef enum
{
  MDP_BOOT_PLATFORMID_NONE        = 0,
  MDP_BOOT_PLATFORMID_DUAL_PANEL  = 1,  /* Dual panel platform */
  MDP_BOOT_PLATFORMID_CPHY_MODE   = 2,  /* Cphy mode platform */
  MDP_BOOT_PLATFORMID_MAX,
} MDPBootPlatformIDType;

/* MDPDisplayPeripheralType
 */
typedef enum
{
  MDP_DISPLAY_PERIPHERAL_NONE      = 0x0,  /* No peripheral type specified */
  MDP_DISPLAY_PERIPHERAL_DSI0      = 0x1,  /* Display peripheral type DSI0 */
  MDP_DISPLAY_PERIPHERAL_DSI1      = 0x2,  /* Display peripheral type DS1  */
  MDP_DISPLAY_PERIPHERAL_DP0       = 0x4,  /* Display peripheral type DP0  */
  MDP_DISPLAY_PERIPHERAL_DP1       = 0x8,  /* Display peripheral type DP1  */
  MDP_DISPLAY_PERIPHERAL_EDP0      = 0x10, /* Display peripheral type EDP0 */
  MDP_DISPLAY_PERIPHERAL_EDP1      = 0x20, /* Display peripheral type EDP1 */
} MDPDisplayPeripheralType;

/*===========================================================================

                        Structures

===========================================================================*/
#pragma pack(push,1)

/*
 * Structure that defines how display information organized in iMEM
 * 32 bytes of IMEM reserved for Display
 */
typedef struct
{

  UINT32 uHeader;      /* Format of the header
                        * MagicID          : Bits 31-28 // Should be 0101b
                        * AddressType      : Bit  27    // 0 for 32bit address, 1 for 64bit address
                                                        // If 64bit then uFBAddress1 is lower 32 bits and uFBAddress2 is the upper 32bits.
                        * Framebuffer1Size : Bits 20-26 // Frame buffer 1 size in megabytes (up to 127MB is supported), 0 means not allocated
                        * Reserved         : Bit  19
                        * Framebuffer2Size : Bits 12-18 // Frame buffer 2 size in megabytes (up to 127MB is supported), 0 means not allocated
                        * Reserved         : Bits 11
                        * PlatformID       : Bits 8-10  // The platform identifier for display.
                        * Checksum         : Bits 0-7
                        */
  UINT32 uFBAddress1;  /* Lower 32 bits of Frame Buffer Address  */
  UINT32 uFBAddress2;  /* Higher 32 bits of Frame Buffer Address */
  UINT32 uReserved;    /* Reserved */
} DISPLAY_BOOT_CONFIG;
#pragma pack(pop)

/*
 * Structure that maps a display interface to a bitmask for fuse register
 */
typedef struct
{
  MDPDisplayPeripheralType eInterface; /* Display Interface */
  uint32                   uBitMask;   /* Bitmask for fuse register */
} MDPDisplayFuseMapType;

/*
 * Structure that maps a chipset to a fuse regisetr offset
 */
typedef struct
{
  EFIChipInfoFamilyType eChipsetFamily; /* Chipset family */
  uint32                uFuseOffset;    /* Fuse regisetr offset */
} MDPDisplayFuseAddressType;


/*===========================================================================

                        Public Functions

===========================================================================*/

/****************************************************************************
*
** FUNCTION: MDP_Log_MessageEx()
*/
/*!
* \brief
*   This function will perform the logging of Debug messages
*
* \param [in] uLogType   - Log level
*        [in] pLogString -  Log String
*
* \retval void
*
****************************************************************************/
void MDP_Log_MessageEx(MDP_LogLevel uLogType, char *pLogString, ...);

/****************************************************************************
*
** FUNCTION: MDP_ReadUnaligned_U32()
*/
/*!
* \brief
* This function reads the uint16 values from aligned boundary and packs them into uint32
*
* if pSrc is at offset of 1 or 3 from the uint32 aligned address
*            reads uint16 from aligned (pSrc -1) address and extracts the LSB
*            reads next uint16 addresses and
*            reads the next +1 uint16 address and extracts the MSB
*            Packs these into uint32 pDest address
*
*if pSrc is at offset 2 from the the uint32 aligned address
*            reads uint16 from aligned (pSrc -1) address
*            reads next uint16 addresses
*            Packs these into uint32 pDest addr
*
* Otherwise pSrc is on aligned address boundary

*
* \param [in] pDest   - pointer to Uint32
*        [in]  pSrc   - pointer to Uint8
*
* \retval void
*
****************************************************************************/
void MDP_ReadUnaligned_U32(uint32 *pDest, uint8 * pSrc);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_MB()
*/
/*!
* \brief
*   This function creates a hardware memory barrier (fence) that prevents the CPU from
*  re-ordering read and write operations.
*
* \param void
*
*
* \retval void
*
****************************************************************************/
void MDP_OSAL_MB(void);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_MB_Ex()
*/
/*!
* \brief
*   This function creates a memory barrier and flushes the data cache
*   for a specific region of memory.
*
* \param [in]  pBuffer     - Memory to be flushed
* \param [in]  pBufferSize - Memory size to be flushed
*
*
* \retval void
*
****************************************************************************/
void MDP_OSAL_MB_Ex(void* pBuffer, uint32 uBufferSize);

/****************************************************************************
*
** FUNCTION: MDP_GetEnvironmentVariable()
*/
/*!
* \brief
*   Helper to retrieve a system environment variable.
*
* \param [in]  pVariableName - Environment variable name
*        [out] pValue        - Variable storage
*        [in]  uSize         - Size of the environment variable
*
* \retval MDP_STATUS_OK on success
*
****************************************************************************/
MDP_Status MDP_GetEnvironmentVariable(CHAR16 *pVariableName, void *pValue, UINT32 uSize);

/****************************************************************************
*
** FUNCTION: MDP_SetFirmwareEnvironmentVariable()
*/
/*!
* \brief
*   Program the platform environment variable
*
* \param [in] pValue - Environment variable data
* \param [in] uSize  - Environment variable size
*
* \retval MDP_STATUS_OK on success
*
****************************************************************************/
MDP_Status MDP_SetFirmwareEnvironmentVariable(void *pValue, UINT32 uSize);


/****************************************************************************
*
** FUNCTION: MDP_GetBootServiceVariable()
*/
/*!
* \brief
*   Helper to retrieve a system environment variable from QcomTokenSpace.
*
* \param [in]  pVariableName - Environment variable name
*        [out] pValue        - Variable storage
*        [out] puSize        - Size of the environment variable
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS MDP_GetBootServiceVariable(CHAR16 *pVariableName, void *pValue, UINTN *puSize);


/****************************************************************************
*
** FUNCTION: MDP_GetBootServiceVariableSize()
*/
/*!
* \brief
*   Helper to retrieve data size for system variable from QcomTokenSpace.
*
* \param [in]  pVariableName - Environment variable name
*        [out] puSize        - Size of the environment variable
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS MDP_GetBootServiceVariableSize(CHAR16 *pVariableName, UINTN *puSize);

/****************************************************************************
*
** FUNCTION: MDP_SetBootServiceVariable()
*/
/*!
* \brief
*   Helper to set a system environment variable using QcomTokenSpace.
*
* \param [in]  pVariableName - Environment variable name
*        [in]  pValue        - Variable storage
*        [in]  uSize         - Size of the environment variable
*        [in]  uFlags        - the MDP variable flags
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS MDP_SetBootServiceVariable(CHAR16 *pVariableName, void *pValue, UINTN uSize, UINT32 uFlags);

/****************************************************************************
*
** FUNCTION: MDP_GetDDRType()
*/
/*!
* \brief
*   retrieve DDR details info from system
*
* \retval UINT32
*
****************************************************************************/
UINT32 MDP_GetDDRType(void);


/****************************************************************************
*
** FUNCTION: MDP_SetupMMUSIDs()
*/
/*!
* \brief
*   Helper to program Display MMU SID to bypass
*
* \param   sEFIChipSetFamily  - Platform family
*          uMMUSidMask        - Platform MMU Sid Mask
*
* \retval MDP_STATUS_OK on success
*
****************************************************************************/
MDP_Status MDP_SetupMMUSIDs(EFIChipInfoFamilyType  sEFIChipSetFamily, uint32 uMMUSidMask);


/****************************************************************************
*
** FUNCTION: MDP_MDSS_HWIOBaseAddr()
*/
/*!
* \brief
*   Retrieve MDSS base Address
*
* \retval MDSS HWIO base address
*
****************************************************************************/
uintPtr MDP_MDSS_HWIOBaseAddr(EFIChipInfoFamilyType  sEFIChipSetFamily);

/****************************************************************************
*
** FUNCTION: MDP_GetDDRType()
*/
/*!
* \brief
*   retrieve DDR details info from system
*
* \retval uint32
*
****************************************************************************/
uint32 MDP_GetDDRType(void);


/****************************************************************************
*
** FUNCTION: MDP_OSAL_MEMZERO()
*/
/*!
* \brief
*   Fills a target buffer with 0 value
*
* \param [in] pBuffer   - The memory to set
*        [in] uLength   - The number of bytes to set
*
* \retval void
*
****************************************************************************/
void MDP_OSAL_MEMZERO(void *pBuffer, UINTN uLength);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_MEMCPY()
*/
/*!
* \brief
*   Copies a source buffer to a destination buffer
*
* \param [in] pDest   - The pointer to the destination buffer of the memory copy
*        [in] pSrc    - The pointer to the source buffer of the memory copy.
*        [in] uLength - The number of bytes to copy from SourceBuffer to DestinationBuffer.

*
* \retval void
*
****************************************************************************/
void MDP_OSAL_MEMCPY( void *pDest, void * pSrc, UINTN uLength);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_MEMSET()
*/
/*!
* \brief
*   Fills a target buffer with a byte value
*
* \param [in] pBuffer - The memory to set
*        [in] uLength - The number of bytes to set
*        [in] uValue  - The value with which to fill Length bytes of Buffer
*
* \retval void
*
****************************************************************************/
void MDP_OSAL_MEMSET( void *pBuffer, UINT8  uValue, UINTN  uLength);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_CALLOC()
*/
/*!
* \brief
*   Allocate memory from local heap
*
* \param [in] uLength   - Requested size of memory to be allocated
*
* \retval point to the block of allocated memory
*
****************************************************************************/
void* MDP_OSAL_CALLOC(UINTN uLength);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_FREE()
*/
/*!
* \brief
*   Free allocated memory from local heap
*
* \param [in] pBuffer   - Pointer to block of memory allocated
*
* \retval void
*
****************************************************************************/
void MDP_OSAL_FREE(void* pBuffer);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_DELAYMS()
*/
/*!
* \brief
*   This function will sleep for a given time in milliseconds
*
* \param [in] uDelayMs   - Sleep time in milliseconds
*
* \retval void
*
****************************************************************************/
void MDP_OSAL_DELAYMS(UINTN uDelayMs);

/****************************************************************************
*
** FUNCTION: MDP_OSAL_DELAYUS()
*/
/*!
* \brief
*   This function will sleep for a given time in microsecond
*
* \param [in] uDelayUs   - Sleep time in microsecond
*
* \retval void
*
****************************************************************************/
void MDP_OSAL_DELAYUS(UINTN uDelayUs);

/****************************************************************************
*
** FUNCTION: MDP_SaveFirmwareEnvironmentVariable()
*/
/*!
* \brief
*   This function will save display info into UEFI environment variable
*
* \param [in] eDisplayId        - Display ID
*
* \retval void
*
****************************************************************************/
MDP_Status MDP_SaveFirmwareEnvironmentVariable(MDP_Display_IDType eDisplayId);

/****************************************************************************
*
** FUNCTION: MDP_GetConfigValue()
*/
/*!
* \brief
*   Get config value created by parsing the platform config file
*
* \param [in] Key         - Pointer to ASCII parameter to search for in config file
*        [in] Value       - On input pointer to buffer used to return value
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_GetConfigValue(IN CHAR8* Key, IN OUT UINT32* Value);

/****************************************************************************
*
** FUNCTION: MDP_GetTimerCountMS()
*/
/*!
* \brief
*    Running time in mS based on the Arch Timer Counter.
*    This could get wrapped around based on the resolution and Speed.So
*    use with caution.
*    If the Timer is 32 bit running at 19.2 MHz, it would wrap around, to 0
*    after 223 Sec
*
* \param NONE  - Log level
*
* \retval Timer count
*
****************************************************************************/
UINT32     MDP_GetTimerCountMS(void);

/****************************************************************************
*
** FUNCTION: MDP_GetTimerCountUS()
*/
/*!
* \brief
*    Running time in uS based on the Arch Timer Counter.
*    This could get wrapped around based on the resolution and Speed.So
*    use with caution.
*    If the Timer is 32 bit running at 19.2 MHz, it would wrap around, to 0
*    after 223 Sec
*
* \param NONE  - Log level
*
* \retval Timer count
*
****************************************************************************/
UINT32     MDP_GetTimerCountUS(void);

/****************************************************************************
*
** FUNCTION: MDP_SetMultiThreadState()
*/
/*!
* \brief
*   This function will set multithreadded state to be enabled or not.
*
* \param [in]  bEnable            - Multithreadded state.
*
* \retval None
*
****************************************************************************/
MDP_Status MDP_SetMultiThreadState(bool32 bEnable);

/****************************************************************************
*
** FUNCTION: MDP_Display_SetVariable()
*/
/*!
* \brief
*   Function to set the display variable.
*
  @param[in]  pVariableName              The variable name that need to set.
  @param[in]  pVariableValue             The variable value.
  @param[in]  uDataLength                The length of the variable value.
  @param[in]  uFlags                     The flag to set variable.
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_Display_SetVariable(CHAR16 *pVariableName, UINT8 *pVariableValue, UINTN uDataLength, UINTN uFlags);

/****************************************************************************
*
** FUNCTION: MDP_Display_GetVariable()
*/
/*!
* \brief
*   Function to get the display variable.
*
  @param[in]   pVariableName              The variable name that need to get.
  @param[out]  pVariableValue             The variable value.
  @param[out]  pDataLength                The length of the variable value.
  @param[in]   uFlags                     The flag to get variable.
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_Display_GetVariable(CHAR16 *pVariableName, UINT8 *pVariableValue, UINTN *pDataLength, UINTN uFlags);

/****************************************************************************
*
** FUNCTION: MDP_Display_ReadConfigFile()
*/
/*!
* \brief
*   Function to read panel config file from specific partition
*
  @param[in]      pPartName     The partition that stores the file
  @param[in]      pFileName     The file name that need to get
  @param[out]     pFileBuf      Buffer that used to store the file content reads back
  @param[in]      pFileBufLen   The length of the file buffer
  @param[in]      uFlags        The flag to get file.
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_Display_ReadConfigFile(CHAR16 *pPartName, CHAR16 *pFileName, UINT8 **pFileBuf, UINTN *pFileBufLen, UINTN uFlags);

/****************************************************************************
*
** FUNCTION: MDP_Display_WriteTextFile()
*/
/*!
* \brief
*   Function to write text file to specific partition
*
  @param[in]      pPartName     The partition that stores the file
  @param[in]      pFileName     The file that written to
  @param[in]      pBuf          Buffer that written to the file
  @param[in]      uBufLen       Buffer length
  @param[in]      uFlags        Flag to set
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_Display_WriteTextFile(CHAR16 *pPartName, CHAR16 *pFileName, UINT8 *pBuf, UINTN uBufLen, UINTN uFlags);


/****************************************************************************
*
** FUNCTION: MDP_Display_SetVariable_Integer()
*/
/*!
* \brief
*   Function to set the display variable.
*
  @param[in]  pVariableName              The variable name that need to set.
  @param[in]  uVariableValue             The variable value.
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_Display_SetVariable_Integer(CHAR16 *pVariableName, UINT32 uVariableValue);

/****************************************************************************
*
** FUNCTION: MDP_Display_GetVariable_Integer()
*/
/*!
* \brief
*   Function to get the display variable.
*
  @param[in]   pVariableName              The variable name that need to get.
  @param[out]  pVariableValue             The variable value.
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_Display_GetVariable_Integer(CHAR16 *pVariableName, UINT32 *pVariableValue);

/****************************************************************************
*
** FUNCTION: MDP_GetDisplayBootConfig()
*/
/*!
* \brief
*   This function will get display boot config from IMEM
*
* \param [out] pFrameBufferAddr  : Pointer to the buffer that store framebuffer address
*        [out] pFrameBuffersSize : pointer to the buffer that store framebuffer size
*        [out] pPlatformID       : pointer to the Platform ID
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_GetDisplayBootConfig(UINTN *pFrameBufferAddr, UINT32 *pFrameBuffersSize, uint8 *pPlatformID);


/****************************************************************************
*
** FUNCTION: MDP_SetDisplayBootConfig()
*/
/*!
* \brief
*   This function will set display boot config to IMEM, only 32 bit address supported
*
* \param [in] uFrameBuffer1Addr: framebuffer address
         [in] uFrameBuffers1Size: framebuffer size in bytes
*s
* \retval None
*
****************************************************************************/
MDP_Status MDP_SetDisplayBootConfig(UINT32 uFrameBuffer1Addr, UINT32 uFrameBuffers1Size);

/****************************************************************************
*
** FUNCTION:  MDP_MountFv()
*/
/*!
* \brief
*   Mount fv for display.
*
* \param [in]  gFvNameGuid        - The fv name guid
*        [in]  pFvName            - The fv name
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS MDP_MountFv(EFI_GUID gFvNameGuid, CHAR16 *pFvName);


/****************************************************************************
*
** FUNCTION: MDPCRC8Calculation()
*/
/*!
* \brief
*   This function will calculation checksum
*
* \param [in] pBuf : pointer to the start of buffer
*        [in] uSize: bytes to be calculated
*
* \retval UINT8
*
****************************************************************************/
UINT8 MDPCRC8Calculation(UINT8 *pBuf, UINT32 uSize);


/****************************************************************************
*
** FUNCTION: MDP_Display_LoadFile()
*/
/*!
* \brief
*   This function will load file from FV system
*
* \param [in]  pFileName   : name of the file need to be loaded
*        [out] pFileBuffer : pointer to the start of buffer
*        [out] pBufferSize : size of callers buffer in bytes
*        [out] pRetSize    : bytes to be calculated
*        [in]  uFlags      : flags to load the file
*                            DISP_LOAD_FILE_FLAG_IMAGEFV  - load file from imagefv
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS MDP_Display_LoadFile(CHAR8 *pFileName, UINT8 **pFileBuffer, UINT32 *pBufferSize, UINT32 *pRetSize, UINT32 uFlags);


/****************************************************************************
*
** FUNCTION: MDP_CheckInterfaceAvailable()
*/
/*!
* \brief
*   Function to parse the fuse register value and check for whether a display interface is available or not
*
* \param [in] sEFIChipSetFamily      : Platform family
*        [in] eDisplayPeripheralType : display interface
*
* \retval bool32 
*
****************************************************************************/
bool32 MDP_CheckInterfaceAvailable(EFIChipInfoFamilyType sEFIChipSetFamily, MDPDisplayPeripheralType eDisplayPeripheralType);

/****************************************************************************
*
** FUNCTION: MDP_Display_LoadFileEx()
*/
/*!
* \brief
*   This function will load file from FAT FV system
*
* \param [in]     pPatitionName : name of the partition where the file is stored
         [in]     pFileName     : name of the file need to be loaded
*        [in/out] pFileBuffer   : pointer to the start of buffer, if it is null, caller is expecting this function to allocate memory.
*        [in/out] pBufferSize   : size of callers buffer in bytes to read, if it is 0, this function needs to find file size, and allocate memory, and read the whole file.
*        [in]     uReadOffset   : Read offset
*        [out]    pRetSize      : bytes read
*        [in]     uFlags        : flags to load the file
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_Display_LoadFileEx(CHAR16* pPatitionName, CHAR8* pFileName, UINT8** pFileBuffer, UINT32* pBufferSize, uint64 uReadOffset, UINT32* pRetSize, UINT32 uFlags);

/****************************************************************************
*
** FUNCTION: MDP_IsRamDumpMode()
*/
/*!
* \brief
*   This function will return if device is executing in ram dump mode
*
* \param none
*
* \retval TRUE if in ramdump mode
*
****************************************************************************/
bool32 MDP_IsRamDumpMode();

/****************************************************************************
*
** FUNCTION: MDP_GetMemoryRegionInfo()
*/
/*!
* \brief
*   This function will return memory region base address and size of given memory label
*
* \param [in]     pMemLabel     : Memory region label
*        [out]    pMemAddress   : Base address of memory region
*        [out]    pMemSize      : size of memory region
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDP_GetMemoryRegionInfo(uint8* pMemLabel, uint8** pMemAddress, uint32* pMemSize);

#endif // __MDPSYSTEM_H__


/** @file Sec.c
  C Entry point for the SEC. First C code after the reset vector.
  
  Copyright (c) 2010-2021 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/28/21   cm      Minor corrections in Print statements
 07/16/21   cm      Adding extra parameter to StartFvDecompression
 07/09/21   md      Added function call to detect overlap memory regions in the
                    Ram partition table defined hole
 05/20/21   cm      Adding checks to decide on Decompression
 05/05/21   kpa     Updates to add SEC performance logs
 03/05/21   cm      Adding ENABLE_DEP_32 flag check					
 02/01/21   tmt     Add DTBExtnLib support
 12/21/20   cm      Support for 32 bit PrintUefiStartInfo
 11/12/20   cm      Support for NoMap
 11/07/20   kpa     Include ImageOffsets.h for target specific offsets 
 10/16/20   cm      Support to print TimerDelta for 32 bit
 10/07/20   cm      Support to print Correct Ram info for 32 bit
 09/14/20   cm      Support to print Preloaded ram partition Info
 07/17/20   cm      Fix Assert in BuildMemoryHob
 06/24/20   cm      Updated Asserts in UartInit
 06/02/20   cm      Removed log statement after calling PrePiDecompressFvLibInit
 03/18/20   am      Added Total installed SDRAM memory print
 01/24/20   md      Added binning support check for early cores initialization.
 01/03/20   md      Added binning support check before decompressing FV.
 08/22/19   kpa     Added support to optimize fv decompression
 07/15/19   kpa     Added EbsPerfInfoHobInit
 02/04/19   md      Support to display in the log if using constant for ASLR. 
 12/12/18   md      Add support for configurable UART log buffer size. 
 11/01/18   kpa     Stub SetUefiTargetReset api.
 09/19/17   mt      Added prints for ASLR and DEP flags
 05/05/17   sj      Added performance hob for pei performance data
 02/21/17   vk      Cleanup, remove InitStackCanary call
 01/27/17   ai      Fix use of retail
 12/09/16   bh      Implement ASLR for stack and SEC/DXE heaps
 11/01/16   bh      Buffered logging in early stages before shared lib init
 09/26/16   vk      Add DBI dump support
 09/02/16   ai      Correct UEFI start time 
 07/26/16   vk      Reinitialize the allocate page buffer
 06/08/16   vk      Add early exception handling
 05/05/16   vk      Add FD DEP support
 03/03/16   bh      Enable shared print lib
 02/18/16   bh      Clean up SEC and memory map handling
 11/15/15   vk      Add UefiPrePiHeapMemBase
 10/20/15   vk      Print RAM partition entries
 09/30/15   bh      Update firmware versioning
 09/01/15   vk      Zero our stack for 32 bit
 08/13/15   vk      Add presil flag enabled warning
 07/24/15   vk      Make error message as INFO
 07/28/15   bh      Use Pcd value for HaltOnRetail feature
 07/15/15   bh      Get config value after initializing shared libraries
 07/13/15   sk      Added Prodmode HOB
 07/13/15   ao      move crash dump related code to CrashDumpDxe driver
 06/24/15   bh      Add placeholder for HaltBootOnFuseBlown logic in cfg file
 05/19/15   vk      Support STI 32 bit
 05/18/15   jb      Check SPI as a valid boot device.
 05/15/15   jb      Move adding FV mem regions to after late init
 04/17/15   jb      Change output to occur even in release builds
 04/17/15   vk      Move to start initially from RAM partition entry with FD
 03/02/15   jb      Add option to skip DBI setup
 02/12.15   dg      Build Mem Alloc Hob for regions marked EfiRuntimeServicesData
 02/12/15   vk      Enable crashdump handling
 02/11/15   vk      Disable crashdump handling
 01/22.15   jb      Add UefiDebugModeEntry loop
 11/13/14   jb      Add ability to skip early cache init
 10/30/14   vk      Add RAM parition table lib
 10/18/14   jb      Update values to 64bits, Single resource memory allocation
 10/30/14   vk      New cfg file, support for 4GB DDR
 09/04/14   na      Add AU and Version info to DisplayEarlyInfo
 07/09/14   vk      Do not handle crashdump in PRE_SIL
 06/06/14   yg      Limit memory to 2GB
 06/03/14   vk      Support for 4GB DDR
 05/22/14   vk      Remove limiting DDR size to be 2GB
 05/15/14   shireesh removed support for SDI dump version 0 and Added support for SDI dump ver 1
 05/08/14   vk      Move to updated InfoBlock
 04/22/14   aus     Fixed to use ImemCookieBase instead of DloadCookieBase
 04/10/14   niting  Fixed warnings
 04/09/14   vk      Update InitFBPT signature
 04/01/14   cpaulo  Removed call to TimerInit since it's not required
 03/18/14   vk      Fix gcc warnings
 02/28/14   vk      Print warning for RAM partition table v0
 02/07/14   vk      Add stack canary init
 01/21/14   vk      Update adding memory region hob for absolute address
 11/26/13   vk      Remove stack zero out
 11/15/13   vk      Remove carve out support
 10/22/13   vk      Update to use MAX_ADDRESS
 08/29/13   niting  Limit DDR size to be 2GB
 07/26/13   vk      Support for RAM partition v1
 07/24/13   yg      Reduce logging
 06/25/13   niting  Always setup HOB for legacy UEFI dump
 05/17/13   vk      Initialize cache early
 04/03/13   niting  Added offline crash dump support
 03/19/13   vk      Add hob for InfoBlock
 03/14/13   yg      Print UEFI Start Time
 03/12/13   vk      Add support for SmemNullLib
 02/29/13   vk      Add carve out mode to InfoBlk
 02/15/13   vk      Print AU info
 02/11/13   niting  Use UefiCfgLib to initialize mass storage cookie address
 02/06/13   vk      Print cfg file, handle incase ASSERT is disabled
 01/29/13   vk      Branch from 8974 for target independent version

=============================================================================*/

/*---------------------------------------------------------------------------*/
/*  NOTE: SEC is common for all targets, changes must be target independent  */
/*---------------------------------------------------------------------------*/

#include <PiPei.h>

#include <Pi/PiHob.h>
#include <PiDxe.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PrePiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/ArmLib.h>
#include <Library/PeCoffGetEntryPointLib.h>
#include <Library/DebugAgentLib.h>
#include <Ppi/GuidedSectionExtraction.h>
#include <Guid/LzmaDecompress.h>
#include <Library/ZlibDecompress.h>
#include <Library/SerialPortLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/CpuExceptionHandlerLib.h>
#include <Library/PrintLib.h>
#include <Library/CacheMaintenanceLib.h>

#include <Library/PrintShLib.h>
#include <Library/CookieLib.h>
#include <Library/RamPartitionTableLib.h>
#include <Include/UefiInfoBlk.h>
#include <Library/QcomTargetLib.h>
#include <Library/QcomTimerLib.h>
#include <Library/QcomLib.h>
#include <Library/TimerLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/ProcAsmLib.h>
#include <Library/PerformanceLib.h>
#include <Library/TargetInitLib.h>
#include <Library/AslrLib.h>
#include <Library/TargetResetLib.h>
#include <Library/PmicShutdown.h>
#include <ChipInfo.h>

#include "LzmaDecompress.h"
#include "UefiPlatCfg.h"
#include "ShLibInstall.h"
#include "SerialPortShLibInstall.h"
#include "UefiCfgLibInstall.h"
#include "FwVersion.h"

#include "Library/SplitBootLib.h"
#include <Library/ImagePathUtilsLib.h>
#include <Library/FvDecompressLib.h>

#include "ImageOffsets.h"

//
// Define the maximum debug and assert message length that this library supports
//
#define MAX_DEBUG_MESSAGE_LENGTH  0x100

#define HWIO_IN(x) (*((volatile UINT32*)(x)))

/* Per SWI, timer will overflow after 2^31-1 = 2147483647 */
#define LOG_MAX_COUNT_VAL  2147483647
#define COUNTER_OVERFLOW   0xFFFFFFFF
#define RETRY_COUNT        1000


extern EFI_GUID gQcomFwVersionStringGuid;
extern UINTN SerialBufferedWrite (UINT8* Buffer, UINTN Bytes);
extern EFI_STATUS DtbInit (VOID);
extern VOID DtbExtnIntfInit (VOID);

EFI_STATUS EFIAPI UEFISerialOperations(VOID);
BOOLEAN EFIAPI AddUEFIMinidumpRegion(CHAR8* RegionName, UINTN* RegionBaseAddr, UINTN RegionSize);
EFI_STATUS EFIAPI ExtractGuidedSectionLibConstructor (VOID);
EFI_STATUS EFIAPI LzmaDecompressLibConstructor (VOID);
EFI_STATUS EFIAPI ZlibDecompressLibConstructor (VOID);
EFI_STATUS EarlyCacheInit (UINTN MemBase, UINTN MemSize);
UefiInfoBlkType* InitInfoBlock (UINTN Address, UINTN Size);
UefiInfoBlkType* GetInfoBlock (VOID);
VOID* AddInfoBlkHob (VOID);
VOID SetFdDep (VOID);
VOID InitDbiDump(VOID);
EFI_STATUS ReInitPagePoolBuffer (UINTN PoolPageCount);
void UefiBootContinue (void* arg);
BOOLEAN EFIAPI JTAGDebugDisableFusesBlown(VOID);
VOID SetUefiTargetReset(VOID);
INT32 GetTargetBootCore (VOID);
// Variables for SEC performance logging 
UINT32 EarlyCacheInitSt =0, EarlyCacheInitEnd =0, LoadParsePlatCfgSt =0, LoadParsePlatCfgEnd =0,
       InitCacheWithMemRegSt =0, InitCacheWithMemRegEnd =0, UpdtSysMemSt =0, UpdtSysMemEnd =0,
       logVarSt =0, logVarEnd =0, UefiBootContinueSt =0, UefiBootContinueMid =0;

#ifdef ENABLE_SEC_PERF
#define SEC_PERF EFI_D_WARN
#else
#define SEC_PERF EFI_D_INFO
#endif

extern EFI_GUID gQcomProdmodeInfoGuid;
extern EFI_GUID gEfiStartTimeHobGuid;
extern UINT64   gUEFIStartCounter;
STATIC VOID*    gStackBase;
STATIC UINT64   gReset = 0; 
BOOLEAN         gProdmodeInfo = FALSE;

extern EFI_GUID gEbsPerfInfoHobGuid;

BootContinueParameterBlkType BootContinueParameterBlkPtr;

/* SEC_RETAIL */
#if defined (PRODMODE)
#define SEC_PRODMODE_ENABLED TRUE
#else
#define SEC_PRODMODE_ENABLED FALSE
#endif

#define SEC_RETAIL (SEC_PRODMODE_ENABLED || gProdmodeInfo)


// Added a performance hob for resetEnd data
STATIC EFI_STATUS AddPerformanceHob(UINT64 Reset )
{
   typedef struct {
       UINT64         ResetEnd; 
   } FIRMWARE_SEC_PERFORMANCE;
 
   FIRMWARE_SEC_PERFORMANCE *Performance;
   Performance =  (FIRMWARE_SEC_PERFORMANCE*)AllocateZeroPool(sizeof(FIRMWARE_SEC_PERFORMANCE));
   if(Performance !=NULL)
   {       
     Performance->ResetEnd = Reset;
        
     BuildGuidDataHob (
      &gEfiFirmwarePerformanceGuid,
      Performance,
      sizeof (FIRMWARE_SEC_PERFORMANCE)
          );           
    } 
    return EFI_SUCCESS;
}

/**
  Get number of cycles from power on

  @return Number of cycles
          0xFFFFFFFF if overflow detected
**/
STATIC UINT32
BootGetCounter(VOID)
{
  volatile UINT32 curr_count;
  volatile UINT32 last_count;
  volatile UINT32 retry_count;

  retry_count = RETRY_COUNT;

  /*Grab current time count*/
  curr_count = HWIO_IN((UINTN)PcdGet32(PcdTimeTickClkAddress));

  /*Keep grabbing the time until a stable count is given*/
  do
  {
    last_count = curr_count;
    curr_count = HWIO_IN((UINTN)PcdGet32(PcdTimeTickClkAddress));

    retry_count--;
    if (retry_count == 0)
      return curr_count;

  } while (curr_count != last_count);

  if(curr_count < LOG_MAX_COUNT_VAL)
  {
    return curr_count;
  }
  else
    return COUNTER_OVERFLOW;
}

/**
  Get Time from power on

  @return Time in nanoseconds
          0 if overflow detected
**/
STATIC UINT32
BootGetTimeNanoSec(VOID)
{
  UINT32 TimeTickCount;
  TimeTickCount = BootGetCounter();

  if(TimeTickCount == COUNTER_OVERFLOW)
    return 0;

  /*
  Clock frequency is 32.768 KHz
  1 / (32.768 KHz) = 30517.5781 nanoseconds ~= 30518 ns
  */
  return (TimeTickCount * 30518);
}


STATIC VOID
UefiDebugModeEntry(VOID)
{
  UINT32 UefiDebugCookie;
  UINTN UefiDebugCookieAddr;
  volatile UINT32  *UefiDebugCookiePtr;
  UefiDebugCookie = PcdGet32(PcdUefiDebugCookie);

  UefiDebugCookieAddr = (UINTN)(PcdGet32(PcdIMemCookiesBase) + PcdGet64(PcdUefiDebugCookieOffset));
  UefiDebugCookiePtr = (UINT32 *)UefiDebugCookieAddr;

  /* Loop here to wait for jtag attach if cookie value matches*/
  while( *UefiDebugCookiePtr == UefiDebugCookie );
}

VOID
BuildMemoryTypeInformationHob (VOID);

STATIC VOID 
SerialPrint (IN  CONST CHAR8  *Format, ...)
{
  CHAR8    AsciiBuffer[MAX_DEBUG_MESSAGE_LENGTH];
  UINTN    CharCount;
  VA_LIST  Marker;

  ASSERT (Format != NULL);

  /* Convert the DEBUG() message to a Unicode String */
  VA_START (Marker, Format);
  CharCount = AsciiVSPrint (AsciiBuffer, sizeof (AsciiBuffer), Format, Marker);
  VA_END (Marker);

  SerialBufferedWrite ((UINT8 *) AsciiBuffer, CharCount);
}

STATIC VOID
UartInit ()
{
  EFI_STATUS Status;
  UINT64 SerialLogBuffer;

  SerialLogBuffer = FixedPcdGet64(PcdEmbeddedFdBaseAddress) + SERIAL_BUFFER_OFFSET;

  SerialPortInitialize ();
  Status = SerialBufferInit((UINT8*) SerialLogBuffer, SERIAL_BUFFER_SIZE);
  ASSERT((Status == EFI_SUCCESS) || (Status == EFI_BAD_BUFFER_SIZE));
  if (Status == EFI_BAD_BUFFER_SIZE)
   SerialPrint ("WARNING: Bad SBL Pointer!!\n");
}

STATIC VOID
PrintUefiStartInfo ()
{
  SerialPrint ("\n\nUEFI Start     [%5d]\n", 
      ConvertTimerCountms(gUEFIStartCounter));
	  
  /* Needed for script that can decode the stack frame */
  SerialPrint (" - 0x%09X [%5d] Sec.efi\n", (UINTN)FixedPcdGet64(PcdEmbeddedFdBaseAddress) + EFI_PAGE_SIZE, GetTimerCountms());

#ifdef ENABLE_ASLR
  if (IsStaticRNGUsed()) 
     SerialPrint ("ASLR          : ON [WARNING Using constant]\n");
  else
     SerialPrint ("ASLR          : ON\n");  
#else
  SerialPrint ("ASLR          : OFF [WARNING]\n");
#endif

#if (defined (ENABLE_DEP_64) || defined(ENABLE_DEP_32))  && defined (ENABLE_XN) && !defined(ENABLE_EXEC_CODE_READY_TO_BOOT )
  SerialPrint ("DEP           : ON\n");
#elif (defined (ENABLE_DEP_64) || defined(ENABLE_DEP_32)) && defined (ENABLE_XN) && defined(ENABLE_EXEC_CODE_READY_TO_BOOT )
  SerialPrint ("DEP           : ON (RTB)\n");
#else
  SerialPrint ("DEP           : OFF [WARNING]\n");
#endif

#ifdef PRE_SIL
  SerialPrint ("PRE_SIL       : ON [WARNING]\n");
#endif
}

/**
  Build HOB for the memory region

  @param  MemRegion       pointer to the memory region

  @retval EFI_SUCCESS     Successfully retrieves memory base and size
  @retval EFI_INVALID_PARAMETER  The RAM partition table is invalid
**/
STATIC EFI_STATUS
BuildMemoryHob (IN MemRegionInfo    *pMemRegion)
{
  /* Make sure the region's end address doesn't exceed the MAX_ADDRESS) */
  ASSERT (pMemRegion->MemBase < MAX_ADDRESS);
  ASSERT ((pMemRegion->MemBase + pMemRegion->MemSize - 1) <= MAX_ADDRESS);

  /* Build ResourceHob */
  if (pMemRegion->BuildHobOption != AllocOnly) {
    BuildResourceDescriptorHob (pMemRegion->ResourceType,
                                pMemRegion->ResourceAttribute,
                                pMemRegion->MemBase,
                                pMemRegion->MemSize);
  }

  if (pMemRegion->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY || pMemRegion->MemoryType == EfiRuntimeServicesData)
  {
    /* Build MemoryAllocationHob */
    BuildMemoryAllocationHob (pMemRegion->MemBase,
                              pMemRegion->MemSize,
                              pMemRegion->MemoryType);
  }

  return EFI_SUCCESS;
}

/* Build HOB for the FV type specified */
/* Currently only EFI_HOB_TYPE_FV2 is handled */
STATIC VOID
BuildMemHobForFv (IN UINT16 Type)
{
  EFI_PEI_HOB_POINTERS      HobPtr;
  EFI_HOB_FIRMWARE_VOLUME2  *Hob = NULL;

  HobPtr.Raw = GetHobList ();
  while ((HobPtr.Raw = GetNextHob (Type, HobPtr.Raw)) != NULL)
  {
    if (Type == EFI_HOB_TYPE_FV2)
    {
      Hob = HobPtr.FirmwareVolume2;
      /* Build memory allocation HOB to mark it as BootServicesData */
      BuildMemoryAllocationHob(Hob->BaseAddress, EFI_SIZE_TO_PAGES(Hob->Length) * EFI_PAGE_SIZE, EfiBootServicesData);
    }
    HobPtr.Raw = GET_NEXT_HOB (HobPtr);
  }
}

STATIC EFI_STATUS
InitSharedLibs (VOID)
{
  EFI_STATUS Status;
  MemRegionInfo* MemRegions = NULL;
  UINTN MemRegionsCnt = 0;
  ConfigPair* ConfigTablePtr;
  UINTN ConfigCnt;
  UefiInfoBlkType* UefiInfoBlkPtr;
  UINT64 SerialLogBuffer;

  SerialLogBuffer = FixedPcdGet64(PcdEmbeddedFdBaseAddress) + SERIAL_BUFFER_OFFSET;

  /* Get info block */
  UefiInfoBlkPtr = GetInfoBlock();

  if (UefiInfoBlkPtr == NULL)
    return EFI_OUT_OF_RESOURCES;

  ShLibMgrInit ();

  /* Get Memory map from parsed cfg file */
  GetMemRegionCfgInfo(&MemRegions, &MemRegionsCnt);
  UefiInfoBlkPtr->MemTablePtr = (UINTN*) MemRegions;
  UefiInfoBlkPtr->MemTableCount = MemRegionsCnt;

  /* Get config table from parsed config file */
  GetConfigTable(&ConfigTablePtr, &ConfigCnt);
  UefiInfoBlkPtr->ConfigTablePtr = (UINTN*) ConfigTablePtr;
  UefiInfoBlkPtr->ConfigTableCount = ConfigCnt;

  /* Initialize cfg shared lib */
  Status = UefiCfgShLibInit (MemRegions, MemRegionsCnt, ConfigTablePtr, ConfigCnt);
  if (Status != EFI_SUCCESS)
    return EFI_OUT_OF_RESOURCES;

  UefiInfoBlkPtr->UartLogBufferPtr = (UINTN*)SerialLogBuffer;
  UefiInfoBlkPtr->UartLogBufferLen = SERIAL_BUFFER_SIZE;

  
  Status = SerialPortShLibInit ();
  if (Status != EFI_SUCCESS)
    return EFI_OUT_OF_RESOURCES;
  
  Status = InitPrintLibHost();
  if (Status != EFI_SUCCESS)
    return EFI_OUT_OF_RESOURCES;
  
  return Status;
}

STATIC VOID
AddMemRegionHobs (VOID)
{
  UINTN           Index;
  MemRegionInfo*  MemRegions = NULL;
  UINTN           MemRegionsCnt = 0;

  GetMemRegionCfgInfo(&MemRegions, &MemRegionsCnt);
  if ((MemRegions == NULL) || (MemRegionsCnt == 0))
  {
    DEBUG((EFI_D_ERROR, "UEFI Memory Map configuration not found\r\n"));
    ASSERT (MemRegions != NULL);
    ASSERT (MemRegionsCnt != 0);
    CpuDeadLoop();
    return; /* For KW */
  }

  for (Index = 0; Index < MemRegionsCnt; Index++)
  {
    switch (MemRegions[Index].BuildHobOption)
    {
      case AllocOnly:
        BuildMemoryHob(&MemRegions[Index]);
        break;

      case AddMem:
        BuildMemoryHob(&MemRegions[Index]);
        break;

      case AddPeripheral:
        BuildMemoryHob(&MemRegions[Index]);
        break;

      case HobOnlyNoCacheSetting:
        BuildMemoryHob(&MemRegions[Index]);
        break;

      case NoBuildHob:
        /* Don't do anything, only cache is initialized */
        break;

      case NoMap:
        /* Don't do anything */
        break;

      case AddDynamicMem:
      /* Don't do anything */
        break;

      case ErrorBuildHob:
      default:
        DEBUG ((EFI_D_ERROR, "Invalid BuildHob Option\n"));
        ASSERT(FALSE);
        CpuDeadLoop();
        break;
    } /* end of switch */
  } /* end of for */
}

STATIC VOID
InitPerf (VOID)
{
  UINT64 Tick = 1;
  if (PerformanceMeasurementEnabled ())
    Tick = gUEFIStartCounter; 

  PERF_START (NULL, "SEC", NULL, Tick);
}

STATIC VOID
SetFwVersionStringInInfoBlk(VOID)
{
  EFI_HOB_GUID_TYPE *GuidHob       = NULL;
  CHAR8*            FwVerStr       = NULL;
  VOID*             Destination    = NULL;
  UefiInfoBlkType*  UefiInfoBlkPtr = NULL;

  GuidHob = GetFirstGuidHob(&gQcomFwVersionStringGuid);
  if (GuidHob == NULL)
  {
    DEBUG((EFI_D_WARN, "FW version string HOB not found!\n"));
    return;
  }

  FwVerStr = GET_GUID_HOB_DATA(GuidHob);
  if (FwVerStr == NULL)
  {
    DEBUG((EFI_D_WARN, "FW version string not found in HOB!\n"));
    return;
  }

  UefiInfoBlkPtr = GetInfoBlock();
  if (UefiInfoBlkPtr == NULL)
  {
    DEBUG((EFI_D_WARN, "Could not locate UefiInfoBlkPtr\r\n"));
    return;
  }

  Destination = (VOID*)((UINTN)UefiInfoBlkPtr + sizeof(UefiInfoBlkType));
  AsciiStrCpyS(Destination, AsciiStrLen(FwVerStr) + 1, FwVerStr);
  UefiInfoBlkPtr->RelInfo = Destination;
}

STATIC EFI_STATUS
PrintInstalledSDRAMPartitionSize (VOID)
{
  EFI_STATUS       Status;
  UINT64            TotalRamSize = 0;
  
  Status = GetInstalledSDRAMMemory ((UINTN *)&TotalRamSize);
  if (EFI_ERROR (Status))
  {
    return Status;
  }

  SerialPrint("RAM Installed : %ld MB (0x%010lx)\n", TotalRamSize / BYTES_TO_MB, TotalRamSize);

  return Status;
}

STATIC EFI_STATUS
PrintAvailableRamPartitions (VOID)
{
  EFI_STATUS    Status;
  MemRegionInfo *pRamPartTable = NULL;
  UINTN         AvailNumParts = 0;
  UINTN         i             = 0;
  UINT64         TotalRamSize = 0;


  Status = GetRamPartitions(&AvailNumParts, NULL);
  if (Status == EFI_BUFFER_TOO_SMALL)
  {
    pRamPartTable = AllocatePool((sizeof(MemRegionInfo) * AvailNumParts));
    if (pRamPartTable == NULL)
      return EFI_OUT_OF_RESOURCES;

    Status = GetRamPartitions(&AvailNumParts, pRamPartTable);
    if (Status != EFI_SUCCESS)
      return EFI_UNSUPPORTED;

    if (pRamPartTable == NULL)
      return EFI_UNSUPPORTED;

    for (i = 0; i < AvailNumParts; i++)
    {
      SerialPrint("RAM Entry %d   : Base 0x%010lx  Size 0x%010lx\n", i, pRamPartTable[i].MemBase, pRamPartTable[i].MemSize);
      TotalRamSize += pRamPartTable[i].MemSize;
    }
    
    AvailNumParts = 0;
    Status = GetPreLoadedRamPartitions(&AvailNumParts, NULL);
    if (Status == EFI_BUFFER_TOO_SMALL)
    {
      pRamPartTable = AllocatePool((sizeof(MemRegionInfo) * AvailNumParts));
      if (pRamPartTable == NULL)
        return EFI_OUT_OF_RESOURCES;   
      Status = GetPreLoadedRamPartitions(&AvailNumParts, pRamPartTable);
      if (Status != EFI_SUCCESS)
        return EFI_UNSUPPORTED;
    }
    for (i = 0; i < AvailNumParts; i++)
    {
      SerialPrint("Preloaded %d : Base 0x%010lx  Size 0x%010lx\n", i, pRamPartTable[i].MemBase, pRamPartTable[i].MemSize); 
    }

    SerialPrint("RAM Available : %ld MB (0x%010lx)\n", TotalRamSize / BYTES_TO_MB, TotalRamSize);
  }

  return EFI_SUCCESS;
}

/**
  HOB list initialization

  @param  StackBase       pointer to the stack base
  @param  StackSize       stack size

**/
STATIC
VOID
InitHobList (UINTN MemoryBase, UINTN MemorySize, UefiInfoBlkType* UefiInfoBlkPtr)
{
  /* Create HOB list for SEC Heap */
  SetHobList (HobConstructor ((VOID *)MemoryBase, MemorySize, (VOID*)MemoryBase, (VOID *)(MemoryBase + MemorySize)));

  /* Add resource HOB for SEC Heap */
  BuildResourceDescriptorHob (EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_SETTINGS_CAPABILITIES, MemoryBase, MemorySize);

  if (FeaturePcdGet (PcdPrePiProduceMemoryTypeInformationHob)) {
    /* Optional feature that helps prevent EFI memory map fragmentation. */
    BuildMemoryTypeInformationHob ();
  }

  if (UefiInfoBlkPtr != NULL)
    UefiInfoBlkPtr->HobBase = GetHobList();
}

STATIC
VOID
ReInitHobList (UINTN MemoryBase, UINTN MemorySize, UefiInfoBlkType* UefiInfoBlkPtr)
{
  EFI_PEI_HOB_POINTERS HobPtr;
  EFI_HOB_MEMORY_ALLOCATION_HEADER MemDesc;
  EFI_HOB_FIRMWARE_VOLUME *FvHeader;
  EFI_HOB_GUID_TYPE *GuidHob;
  EFI_HOB_HANDOFF_INFO_TABLE *HobInfo;
  
  HobPtr.Raw = GetHobList();

  InitHobList(MemoryBase, MemorySize, UefiInfoBlkPtr);
  while ((HobPtr.Raw != NULL) && (!END_OF_HOB_LIST(HobPtr)))
  {
    switch(HobPtr.Header->HobType)
    {
      case EFI_HOB_TYPE_HANDOFF:
        HobInfo = HobPtr.HandoffInformationTable;
        break;
      case EFI_HOB_TYPE_MEMORY_ALLOCATION:
        MemDesc = HobPtr.MemoryAllocation->AllocDescriptor;
        BuildMemoryAllocationHob(MemDesc.MemoryBaseAddress,
                                 MemDesc.MemoryLength,
                                 MemDesc.MemoryType);           
        break;
      case EFI_HOB_TYPE_GUID_EXTENSION:
        GuidHob = HobPtr.Guid;
        BuildGuidDataHob(&(GuidHob->Name), GET_GUID_HOB_DATA(HobPtr), GuidHob->Header.HobLength);
        break;    
      case EFI_HOB_TYPE_FV:
        FvHeader = HobPtr.FirmwareVolume;
        BuildFvHob(FvHeader->BaseAddress, FvHeader->Length);
        break;    
      default:
        break;
    }
    HobPtr.Raw = GET_NEXT_HOB(HobPtr);
  }
}

STATIC VOID
ValidateFdRegion(UINT64 FdBase)
{
  MemRegionInfo FdRegion;
  EFI_STATUS    Status;

  Status = GetPartitionEntryByAddr (FdBase, &FdRegion);
  if (EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_ERROR, "Invalid memory configuration, check memory partition table\n"));
    ASSERT (Status == EFI_SUCCESS);
    CpuDeadLoop();
    return; /* For KW */
  }
}

VOID PrintTimerDelta (VOID)
{
  UINT64 QtimerVal = 0, MpmCounter = 0;
  UINT64 Delta = 0;

  QtimerVal = GetTimerCountms();
  
  MpmCounter = BootGetTimeNanoSec() / 1000000;

  if (MpmCounter >= QtimerVal)
  {
   Delta = MpmCounter - QtimerVal;
   SerialPrint("Timer Delta   : +%ld mS\n", Delta);
  }
  else
  {
   Delta = QtimerVal - MpmCounter ;
   SerialPrint("Timer Delta   : -%ld mS\n", Delta);
  }
}

VOID
Main (IN  VOID  *StackBase, IN  UINTN StackSize)
{
  EFI_STATUS       Status = EFI_NOT_READY;
  UefiInfoBlkType* UefiInfoBlkPtr = NULL;
  UINT64           UefiFdBase = 0, SecHeapMemBase = 0; 
  UINTN            SecHeapAslrVal = 0;
  UINTN            HobStackSize;
  MemRegionInfo    DxeHeapMemInfo;
  UINTN            DxeHeapAslrVal = 0;
  UINT32 MaxCoreCnt = 0, EnableMultiThreading = 0, EarlyInitCoreCnt = 0;
  DALResult        DalStatus = DAL_ERROR;
  
  gReset = GetTimeInNanoSecond(GetPerformanceCounter());
  UefiFdBase = FixedPcdGet64(PcdEmbeddedFdBaseAddress);
  SecHeapMemBase = UefiFdBase + SEC_HEAP_MEM_OFFSET;
  HobStackSize = StackSize;

  gStackBase = StackBase;

  logVarSt = GetTimerCountms();
  /* Start UART debug output */
  UartInit();
  logVarEnd = GetTimerCountms();

  PrintUefiStartInfo();

  /* Get nibble from random value to adjust SEC heap */
  SecHeapAslrVal = GetRNumOfBits(ASLR_HEAP_RNG_BITS);

  InitHobList(SecHeapMemBase,
              SEC_HEAP_MEM_SIZE - (SecHeapAslrVal*ASLR_HEAP_ALIGN),
              UefiInfoBlkPtr);
  
  // Need memory allocation working
  InitializeCpuExceptionHandlers (NULL);

  PrintTimerDelta();

  /* Enable program flow prediction, if supported */
//  ArmEnableBranchPrediction ();

  /* Initialize Info Block */
  UefiInfoBlkPtr = InitInfoBlock (UefiFdBase + UEFI_INFO_BLK_OFFSET, UEFI_INFO_BLK_SIZE);
  ASSERT(UefiInfoBlkPtr != NULL);
  UefiInfoBlkPtr->StackBase = StackBase;
  UefiInfoBlkPtr->StackSize = StackSize;
  UefiInfoBlkPtr->BootCore  = GetTargetBootCore();
  /* Add hob for sharing InfoBlock with Dxe */
  if(AddInfoBlkHob() == NULL)
    DEBUG((EFI_D_ERROR, "WARNING: Unable to add InfoBlk HOB\r\n"));

  InitRamPartitionTableLib ();

  ValidateFdRegion(UefiFdBase);
 
  /* Add the FVs to the hob list */
  BuildFvHob (PcdGet64(PcdFlashFvMainBase), PcdGet64(PcdFlashFvMainSize));

  /* Should be done after we have setup HOB for memory allocation  */
  PrintAvailableRamPartitions ();

  PrintInstalledSDRAMPartitionSize ();
  
  EarlyCacheInitSt = GetTimerCountms();
  
  #ifndef ENABLE_STANDALONE
  Status = EarlyCacheInit (UefiFdBase, UEFI_FD_SIZE);       
  if (EFI_ERROR(Status))         
  {
    DEBUG((EFI_D_ERROR, "EarlyCacheInit Failed\r\n"));
    ASSERT(Status == EFI_SUCCESS);
    CpuDeadLoop();
  }
  
  #endif 
  EarlyCacheInitEnd = GetTimerCountms();
    
  LoadParsePlatCfgSt = GetTimerCountms();  
  /* Load and Parse platform cfg file, cache re-initialized per cfg file */
  Status = LoadAndParsePlatformCfg();
  LoadParsePlatCfgEnd = GetTimerCountms();

  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "Error parsing configuration file\r\n"));
    ASSERT(Status == EFI_SUCCESS);
    CpuDeadLoop();
    return; /* For KW */
  }

  /* Validate memory regions dont overlap with the hole defined in rampartition table */
  Status = ValidateParsedMemoryRegions();
  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR,"Error: Overlap detected!!! Memory region carved out in a hole defined by RAM partition table !\n"));
    CpuDeadLoop();
  }

  UpdtSysMemSt = GetTimerCountms();
  /* Add information from all other memory banks */
  Status = UpdateSystemMemoryRegions();
  UpdtSysMemEnd = GetTimerCountms();
  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "Error updating info for all banks\r\n"));
    ASSERT(Status == EFI_SUCCESS);
    CpuDeadLoop();
    return; /* For KW */
  }

  InitCacheWithMemRegSt = GetTimerCountms();
  /* Initialize cache for all memory regions */
  Status = InitCacheWithMemoryRegions();
  InitCacheWithMemRegEnd = GetTimerCountms();

  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "Error initializing cache with memory regions\r\n"));
    ASSERT(Status == EFI_SUCCESS);
    CpuDeadLoop();
    return; /* For KW */
  }

  /* All shared lib related initialization */
  Status = InitSharedLibs();
  if (Status != EFI_SUCCESS)
  {
     DEBUG((EFI_D_ERROR, "InitSharedLibs failed\r\n"));
     ASSERT(Status == EFI_SUCCESS);
     CpuDeadLoop();
  }

#if defined (ENABLE_DEP_64) || defined (ENABLE_DEP_32) 
  /* Enable DEP for FD region */ 
  SetFdDep();
#endif  

  /* Look for "DXE Heap" memory region in config file */
  Status = GetMemRegionInfoByName("DXE Heap", &DxeHeapMemInfo);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "Could not locate \"DXE Heap\" in CFG\r\n"));
    ASSERT(Status == EFI_SUCCESS);
    CpuDeadLoop(); 
  }

  /* Get nibble from random value to adjust DXE heap */
  DxeHeapAslrVal = GetRNumOfBits(ASLR_HEAP_RNG_BITS);

  /* Re-initialize HOB to point to the DXE Heap in CFG */
  ReInitHobList(DxeHeapMemInfo.MemBase,
                DxeHeapMemInfo.MemSize - (DxeHeapAslrVal*ASLR_HEAP_ALIGN),
                UefiInfoBlkPtr);

  /* Re allocate UEFI log buffer */
  UEFISerialOperations();

  /* add log buffer region into minidump */
  Status = AddUEFIMinidumpRegion("UEFI_LOG", (UINTN*) UefiInfoBlkPtr->UartLogBufferPtr, (UINTN) UefiInfoBlkPtr->UartLogBufferLen);
  if (Status == EFI_SUCCESS)
     DEBUG ((EFI_D_ERROR, "Minidump      : ON\n")); 
  else
     DEBUG ((EFI_D_ERROR, "Minidump      : OFF (No UEFI Log)\n"));

  UINT32 PagePoolCount = 0;
  Status = GetConfigValue ("SecPagePoolCount", &PagePoolCount);
  if ((Status != EFI_SUCCESS) || (PagePoolCount < 0x40))
  {
    DEBUG((EFI_D_ERROR, "Need valid SecPagePoolCount cfg, using default value of 0x400\r\n"));
    PagePoolCount = 0x400;
  }

  /* Now we have access to bigger pool, move pre-pi memory allocation pool to it */
  ReInitPagePoolBuffer (PagePoolCount);
  

  Status = GetConfigValue ("EnableMultiThreading", &EnableMultiThreading);
  if ((Status != EFI_SUCCESS) || (EnableMultiThreading == 0))
      UefiBootContinue (0);  // Just continue booting explicitly if returns or on failure

  #define MAX_CORES_COUNT   4
  #define MAX_CORE_MASK     0xFF

  /* Max cores to keep functional in the system including the boot core */
  Status = GetConfigValue ("MaxCoreCnt", &MaxCoreCnt);
  if ((Status != EFI_SUCCESS) || (MaxCoreCnt > 8))
    MaxCoreCnt = MAX_CORES_COUNT;

  Status = GetConfigValue ("EarlyInitCoreCnt", &EarlyInitCoreCnt);
  if ((Status != EFI_SUCCESS) || (EarlyInitCoreCnt > MaxCoreCnt))
    EarlyInitCoreCnt = 0x2;

  if (!SEC_RETAIL)
  {
    DalStatus = ChipInfo_Init();
    if (DalStatus != DAL_SUCCESS)
       EarlyInitCoreCnt = 0x1;
    else
    {
      UINT32 CoreMask;
      DalStatus = ChipInfo_GetDefectiveCPUs(0, &CoreMask);
      if ((DalStatus != DAL_SUCCESS) || ((CoreMask & 0x2) != 0))
        EarlyInitCoreCnt = 0x1;
      if ((DalStatus == DAL_SUCCESS))
        BootContinueParameterBlkPtr.AvailMaxCoreMask = (CoreMask ^ MAX_CORE_MASK);
    }
  }
  
  BootContinueParameterBlkPtr.Version = Boot_Continue_Parameter_Blk_Version;
  BootContinueParameterBlkPtr.MaxCoreCnt = MaxCoreCnt;
  BootContinueParameterBlkPtr.EarlyInitCoreCnt = EarlyInitCoreCnt;

  InitSplitBoot (&UefiBootContinue, &BootContinueParameterBlkPtr);  // Doesn't return if succeeds

  UefiBootContinue (0);  // Just continue booting explicitly if returns or on failure
}

void DecompressFV(IN UINT32 DecompressionRqd)
{
  EFI_STATUS       Status = EFI_NOT_READY;
  UINT64           UefiFdBase = 0;
  UINT64           UefiFdSize = 0;
  DECOMPRESSION_MODE LaunchMode = BACKGROUND;
  UINT32           BeforeCount, AfterCount;
  UINT32           EnableMultiCoreFvDecompression = 0;

  UefiFdBase = FixedPcdGet64 (PcdEmbeddedFdBaseAddress);
  UefiFdSize = FixedPcdGet64 (PcdEmbeddedFdSize);

  /*Initialize FV Decompression Lib */ 
  PrePiDecompressFvLibInit ();
  if (!DecompressionRqd)
    return;

  BeforeCount = GetTimerCountms ();  
  /* Assume the FV that contains the SEC (our code) also contains a compressed FV 
     Perform Blocking Decompression first, so as to freeup and reuse temp buffer 
  */
  Status = StartFvDecompression ((void *)UefiFdBase, UefiFdSize, 
                                  &gCompressedDxeCoreContainerFvGuid, SYNCHRONOUS, NOMOUNT);
  if (Status != EFI_SUCCESS)
  {
    DEBUG ((EFI_D_ERROR, "Dxe Core  FV decompression failed, Status: %d\r\n", Status));
    ASSERT(FALSE);
  }   
  
  Status = PropagateProcessingFvInfo (&gCompressedDxeCoreContainerFvGuid);
  AfterCount = GetTimerCountms ();
  DEBUG((EFI_D_INFO, "Dxe Core FV Decompress time %d ms\r\n", (AfterCount - BeforeCount)));  
  if (Status != EFI_SUCCESS)
    DEBUG ((EFI_D_ERROR, "AddDecompressdFvForDxe failed, Status: %d\r\n", Status));

  Status = GetConfigValue ("EnableMultiCoreFvDecompression", &EnableMultiCoreFvDecompression);
  if ((Status != EFI_SUCCESS) || (EnableMultiCoreFvDecompression == 0))
    LaunchMode = SYNCHRONOUS;
  else
  {
    if (!SEC_RETAIL)
    {
      if (BootContinueParameterBlkPtr.EarlyInitCoreCnt < 0x2)
      {
        DEBUG ((EFI_D_ERROR, "Core 1 is non operational"));
        LaunchMode = SYNCHRONOUS;
      }
    }
  }
  
  BeforeCount = GetTimerCountms (); 
  Status = StartFvDecompression ((void *)UefiFdBase, UefiFdSize, 
                                 &gCompressedAuxFvGuid, LaunchMode, STAGE1);
  if ((Status != EFI_SUCCESS) && (Status != EFI_NOT_FOUND))
  {
    /*Secondary/Auxillary Fv is optional, If not found, continue boot */
    DEBUG ((EFI_D_ERROR, "UEFI Aux FV decompression failed, Status: %d\r\n", Status));
  }   

  AfterCount = GetTimerCountms ();
  DEBUG((EFI_D_INFO, "Auxillary FV Decompress time %d ms (Decompress Thread)\r\n", (AfterCount - BeforeCount)));  

}

void UefiBootContinue (void* arg)
{
  UINT32           UefiStartTime = 0;
  UefiInfoBlkType* UefiInfoBlkPtr = NULL; 
  UINTN            HobStackSize = 0;
  UINT32           DecompressionRqd = 1;
  EFI_STATUS       Status = EFI_DEVICE_ERROR;

  UefiBootContinueSt = GetTimerCountms();
  InitDbiDump();
  /* Get info block */
  UefiInfoBlkPtr = GetInfoBlock();
  if (UefiInfoBlkPtr == NULL)
  {
    DEBUG((EFI_D_ERROR, "Could not locate UefiInfoBlkPtr\r\n"));
    ASSERT(FALSE);
    CpuDeadLoop(); 
  }

#ifdef ENABLE_ASLR
  /* Round Adjusted Stack size to page boundary for stack HOB to be created */
  HobStackSize =  (UefiInfoBlkPtr->StackSize + EFI_PAGE_SIZE) & (~(EFI_PAGE_SIZE-1));
#endif

  BuildStackHob ((EFI_PHYSICAL_ADDRESS)gStackBase, HobStackSize);
  BuildCpuHob (PcdGet8 (PcdPrePiCpuMemorySize), PcdGet8 (PcdPrePiCpuIoSize));
  
  /* Build HOB to pass up prodmode info for security applications */
  gProdmodeInfo = JTAGDebugDisableFusesBlown();
  BuildGuidDataHob (&gQcomProdmodeInfoGuid, &gProdmodeInfo, sizeof(BOOLEAN));

  DisplayEarlyInfo();

  SetFwVersionStringInInfoBlk();

  AddMemRegionHobs ();
  
  /* Initialize the DTB loaded by previous boot stage */
  Status = DtbInit();
  if (Status == EFI_SUCCESS)
    DtbExtnIntfInit();
  
  /* TODO: Confirm DTB addr matches its own location in DTB memory map */

  /* Start perf here, after timer init, start at current tick value */
  InitPerf();
  
  /*Add hob for ExitBootServices performance data*/
  EbsPerfInfoHobInit();
  
  /*Add performance hob for pei performance data*/
  AddPerformanceHob(gReset);

  /* SEC phase needs to run library constructors by hand */
  ExtractGuidedSectionLibConstructor ();
  
  Status = GetConfigValue ("DecompressionRequired", &DecompressionRqd);
  if (Status == EFI_NOT_FOUND)
    DecompressionRqd = 1;

  if (DecompressionRqd)
  {
    LzmaDecompressLibConstructor ();
    ZlibDecompressLibConstructor ();
  }	

  /* Build HOBs to pass up our Version of stuff the DXE Core needs to save space */
  BuildPeCoffLoaderHob ();
  BuildExtractSectionHob (
    &gLzmaCustomDecompressGuid,
    LzmaGuidedSectionGetInfo,
    LzmaGuidedSectionExtraction
    );

  BuildExtractSectionHob (
    &gZlibDecompressGuid,
    ZlibGuidedSectionGetInfo,
    ZlibGuidedSectionDecompress
    );

  /* Build HOB to pass up start time */
  UefiStartTime = ConvertTimerCountms(gUEFIStartCounter);
  BuildGuidDataHob (&gEfiStartTimeHobGuid, &UefiStartTime, sizeof(UINT32));

  UefiBootContinueMid = GetTimerCountms();
  DecompressFV(DecompressionRqd);

  /* Any non-critical initialization */
  TargetLateInit();

  /* Build memory allocation HOB for FV2 type
     Need to remove for decompressed image */
  BuildMemHobForFv(EFI_HOB_TYPE_FV2);

  SetUefiCrashCookie();

  SetUefiTargetReset();

  DEBUG ((SEC_PERF ," UartInit                   [%5d] ms\n", (logVarEnd - logVarSt))); 
  DEBUG ((SEC_PERF ," EarlyCacheInit             [%5d] ms\n", (EarlyCacheInitEnd - EarlyCacheInitSt)));
  DEBUG ((SEC_PERF ," LoadAndParsePlatformCfg    [%5d] ms\n", (LoadParsePlatCfgEnd - LoadParsePlatCfgSt)));
  DEBUG ((SEC_PERF ," UpdateSystemMemoryRegions  [%5d] ms\n", (UpdtSysMemEnd - UpdtSysMemSt)));
  DEBUG ((SEC_PERF ," InitCacheWithMemoryRegions [%5d] ms\n", (InitCacheWithMemRegEnd - InitCacheWithMemRegSt)));
  DEBUG ((SEC_PERF ," UefiBootContinue Start      %5d ms\n", UefiBootContinueSt));
  DEBUG ((SEC_PERF ," UefiBootContinue Mid        %5d ms\n", UefiBootContinueMid)); 

  /* Load the DXE Core and transfer control to it */
  LoadDxeCoreFromFv (NULL, 0);

  /* DXE Core should always load and never return */
  ASSERT (FALSE);
  CpuDeadLoop();
}

/* PcdTargetPanic */
#define TARGET_PANIC_SHUTDOWN         0x0
#define TARGET_PANIC_HARD_RESET       0x1

/**
  Set UEFI Target reset behavior - Do Hard Reset or Shutdown based on PCD
  Default Panic action - Shutdown
**/
VOID
SetUefiTargetReset (VOID)
{
  // XBL Loader will configure target for hard reset.
  // If SDI is enabled, TZ will configure the target for warm reset
  // for collecting crash dumps
}

/**
  Override scheduler platform_halt logic
*/
VOID
platform_halt(UINT32 action, UINT32 reason)
{
  if (SEC_RETAIL) {
    TargetPanic();
  }

  CpuDeadLoop();
}

/**
  Entry point

  @param  StackBase       pointer to the stack base
  @param  StackSize       stack size
**/
VOID
CEntryPoint (
  IN  VOID  *StackBase,
  IN  UINTN StackSize
  )
{
	
  #ifndef ENABLE_STANDALONE	
  UefiDebugModeEntry();
  #endif
  TargetEarlyInit();

  Main (StackBase, StackSize);
}


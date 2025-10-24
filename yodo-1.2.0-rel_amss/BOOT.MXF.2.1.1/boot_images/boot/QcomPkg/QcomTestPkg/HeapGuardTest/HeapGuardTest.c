/** @file HeapGuardTest
   
  Tests for HeapGuard on Page and Pool (AARCH64)
  
  The target will have the following(or similar) 
  enabled for Page/Pool and Bsdata memory Type
  #gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPropertyMask | 0x3
  #gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPoolType | 0x10
  #gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPageType | 0x10
  
  # Test command           Description                                       Expected Results(Heapguard        Expected Results(Heapguard enabled)
                                                                                              not enabled)      
===========================================================================================================================================================================
  1. HeapGuardTest          Checks heap guard for Page allocation by          Test should Fail                  Data abort/Permission fault
                            trying to update write to a page above         
  2. HeapGuardTest --page   Same as above                                     Same as above                     Same as above
  3. HeapGuardTest --pool   Checks heap guard for Pool allocation by          Test should Fail                  Data abort/Permission fault
                            trying to update write to a page above 
  
  Copyright (c) 2022 Qualcomm Technologies Inc. All rights reserved.

**/

#include <string.h>
#include <Library/TestInterface.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/QcomLib.h>

#define POOL_SIZE_IN_BYTES 5
#define PAGE_COUNT 1
#define TESTCASE_NAME_MAX                   40
#define TESTCASE_DESCRIPTION_MAX           120

CHAR8 characterQ = 'Q';
CHAR8 characterA = 'A';

 /* Test case
 */
typedef struct {
  CHAR8     mTestName[TESTCASE_NAME_MAX];               /* Test name */
  CHAR8     pMemoryBlockType[TESTCASE_NAME_MAX];        /* Type of memory block - Page/Pool */
  VOID*    (*pAllocateFn)(UINTN);                       /*AllocatePages or AllocatePool*/
  UINTN     AllocationSize;                             /*Allocation size for each memory block(bytes for Pool and page count for Pages)*/
  UINTN     SizeInBytes;                                /*The offset(from address) at which the test will try writing a value*/
} TestCase;
 
TestCase PoolGuardTest = 
{
  "PoolGuard Test",
  "Pool",
  &AllocatePool,
  POOL_SIZE_IN_BYTES,
  ALIGN_VARIABLE(POOL_SIZE_IN_BYTES)
};

TestCase PageGuardTest = 
{
  "PageGuard Test",
  "Page",
  &AllocatePages,
  PAGE_COUNT,
  EFI_PAGES_TO_SIZE(PAGE_COUNT)
};

EFI_STATUS GuardTest(TestCase *Test)
{
  EFI_STATUS Status =  EFI_SUCCESS;
  AsciiPrint("Running %a\n", Test->mTestName);
  VOID *Buffer = NULL;
  CHAR8 tempVal = 0;
  UINTN SizeInBytes = Test->SizeInBytes;

  Buffer = Test->pAllocateFn(Test->AllocationSize);
  AsciiPrint("The following step should pass\n");
  AsciiPrint("Setting %d bytes from address starting at 0x%010lx to character %c\n", SizeInBytes, Buffer, characterQ);
  SetMem(Buffer, SizeInBytes, (UINT8)characterQ);
  
  AsciiPrint("Now Expect a (Data abort/Permission fault) if HeapGuard for %a is enabled\n",Test->pMemoryBlockType);
  AsciiPrint("Trying to write a character %c at 0x%010lx(this address is start of Guarding)\n", characterA, Buffer+SizeInBytes);
  //SetMem(Buffer+Size, Size, (UINT8)characterA);
  
  tempVal = *(CHAR8*)(Buffer+SizeInBytes); //backing up the existing value
  *(CHAR8*)(Buffer+SizeInBytes) = characterA;
  
  /*if heapguard was enabled and fails to set RO
  or
  if heap gaurd is not enabled,
  setting back to the character that was before
  */
  *(CHAR8*)(Buffer+SizeInBytes) = tempVal;
  
  //FreePages(Buffer, PAGE_COUNT);
  Status = EFI_UNSUPPORTED;
  return Status;
}

EFI_STATUS
ProcessCommandAndTest (UINTN Argc, CHAR8** Argv)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  if (Argc > 1)
    return EFI_INVALID_PARAMETER;

  //running PageGuardTest by default if no argument is given
  if (Argc == 0)
    Status = GuardTest(&PageGuardTest);

  else if (AsciiStriCmp ((CHAR8*)Argv[0], "--page") == 0)
    Status = GuardTest(&PageGuardTest);
  
  else if (AsciiStriCmp ((CHAR8*)Argv[0], "--pool") == 0)
    Status = GuardTest(&PoolGuardTest);

  return Status;
}

EFI_STATUS
EFIAPI
HeapGuardTestMain(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
    )
{
  UINTN      Argc = 0;
  CHAR8      **Argv;
  EFI_STATUS Status = EFI_SUCCESS;

  TEST_START("HeapGuardTest");
  
  if(EFI_ERROR(GetCmdLineArgs (ImageHandle, &Argc, &Argv)))
      return EFI_INVALID_PARAMETER;

  Status = ProcessCommandAndTest (Argc, Argv);

  TestStatus("HeapGuardTest", Status);
  TEST_STOP("HeapGuardTest");

  return Status;
}

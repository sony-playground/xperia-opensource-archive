/**@file

    Copyright (c) 2015 - 2020,2022 Qualcomm Technologies Inc. All rights reserved.<BR>

**/

#include <PiDxe.h>
#include <Library/PeCoffLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomBaseLib.h>

/* SYMPATH_ANCHOR_STR must be present in the Symbol path
   Everything before SYMPATH_ANCHOR_STR is stripped from Symbol path */
#define SYMPATH_ANCHOR_STR    "Build"

/* UEFICORE_ANCHOR_STR is used to differentiate QC UEFI code */
#define UEFICORE_ANCHOR_STR   "boot_images"

/* Maximum size for T32 practice script */
#define ALLOC_PAGES           16

/* Maximum size of string being added to T32 practice script */
#define TEMP_STR_SZ                   1024
#define TEMP_WORK_BUFFERS_PAGE_CNT    1
#define TEMP_PKG_NAME_MEM_SIZE            256

#define DRIVER_DELIMITER_CHAR ','
#define BKPT_DRVR_MAX_NUM     3
#define BKPT_DRVR_MAX_LEN     32

/* Format string should contain "0x" this is used for faster searching */
#define ADDRESS_FORMAT_STRING     "0x%09lx"

STATIC UefiInfoBlkType *InfoBlkPtr      = NULL;
STATIC CHAR8           *TempCmdString   = NULL;
STATIC CHAR8           *TempPathString   = NULL;
STATIC CHAR8           *TempPkgNameMem   = NULL;
CHAR8  DrvrList[BKPT_DRVR_MAX_NUM][BKPT_DRVR_MAX_LEN];
UINTN  DrvrNum                          = 0;
UINT8  DrvrListBuilt                    = 0;

UINTN  SpaceCeilingHit                  = 0;

UINT32 *LocalMemBase, *LocalMemEnd, *LocalMemFree;

/*
 *  Design for multiple pkg symbols loading and source translation
 *
 *
 *
 * */

#define PKG_PATH_LEN       32

static CHAR8* TranslationInsertPtr;

typedef struct __PkgPathInfoType
{
   CHAR8* PkgName;
   CHAR8* TranslatePath;
   CHAR8* ObjPath;
   struct __PkgPathInfoType * Next;
}PkgPathInfoType;

PkgPathInfoType *SymloadPkgsList = NULL;


VOID* LocalMemAlloc (UINTN Bytes)
{
   VOID* MemPtr;
   
   if (LocalMemFree >= LocalMemEnd)
      return NULL;

   Bytes += (sizeof(*LocalMemFree) - 1);
   Bytes &= (~(sizeof(*LocalMemFree) - 1));

   if ((LocalMemFree + Bytes) >= LocalMemEnd)
      return NULL;  // Out of memory, increase the size of pre_allocation

   MemPtr = LocalMemFree;
   LocalMemFree += (Bytes / sizeof(*LocalMemFree));

   return MemPtr;
}

CHAR8* ConvertToUpper (CHAR8* Str)
{
  CHAR8 *TempStr = Str;

  while (Str && *Str)
  {
    if ((*Str >= 'a') && (*Str <= 'z'))
      *Str = *Str - 0x20;
    ++Str;
  }

  return TempStr;
}

VOID
BuildDriverList(
  IN CONST CHAR8 *Drivers
  )
{
  CONST CHAR8 *Start, *End;

  if (Drivers == NULL)
    return;

  if (*Drivers == 0)
    return;

  Start = End = Drivers;
  //check for multiple drivers
  while (Start != NULL)
  {
    if ((*End == DRIVER_DELIMITER_CHAR) || (*End == '\0'))
    {
      CopyMem(DrvrList[DrvrNum], Start, ((UINTN)End - (UINTN)Start));
      Start = ++End;
      DrvrNum++;

      if (*End == '\0')
        break;
    }
    else
    {
      End++;
    }
  }

  DrvrListBuilt = 1;
}

CHAR8 *
EFIAPI
MatchDriverName(
  IN CONST CHAR8  *Command
  )
{
  CHAR8       *Rest = NULL;
  UINTN        Index =0;

  //Go up till DrvrNum so we don't compare empty string
  for (Index=0; Index < DrvrNum; Index++)
  {
    Rest = AsciiStrStr(Command, DrvrList[Index]);

    if (Rest)
      break;
  }

  return Rest;

}

/* Note that this function jumps backwards, ie we search from end of the
 * script backwards towards the beginning
 *
 * If input pointer is NULL, then take the pointer from InfoBlk ie a fresh
 * search, otherwise moves backwards from provided location, ie continue search
 * Returns the location of string 0x */
CHAR8* JumpToNextAddr (CHAR8* CurrentPtr)
{
  CHAR8 *ScriptStart;

  ScriptStart = (CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr;

  if (CurrentPtr)
    CurrentPtr--;

  while (CurrentPtr && (CurrentPtr > ScriptStart))
  {
    if ((CurrentPtr[0] == '0') && (CurrentPtr[1] == 'x'))
      return CurrentPtr;
    --CurrentPtr;
  }
  return NULL;
}

/* Search backwards for ".dll" and when found, go till either '/' or '\' */
CHAR8* GetModuleNameForAddr (CHAR8* AddrPtr, UINTN* LenPtr)
{
  CHAR8* ModulePtr = AddrPtr;
  UINTN  Len;
  CHAR8 *ScriptStart;

  if (AddrPtr == NULL)
    return NULL;

  ScriptStart = (CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr;

  while (ModulePtr && (ModulePtr > ScriptStart))
  {
    if ((ModulePtr[0] == '.') &&
        (ModulePtr[1] == 'd') &&
        (ModulePtr[2] == 'l') &&
        (ModulePtr[3] == 'l'))
      break;

    --ModulePtr;
  }

  if (ModulePtr == ScriptStart)
    return NULL;

  Len = 0;

  while (ModulePtr && (ModulePtr > ScriptStart))
  {
    if ((*ModulePtr == '/') ||
        (*ModulePtr == '\\'))
    {
      if (LenPtr)
        *LenPtr = Len;
      return ModulePtr + 1;
    }

    ++Len;
    --ModulePtr;
  }

  return NULL;
}

/* Logic is to search backwards till we find "&Sf=" and then
 * search forward till we find the same string. Then, move
 * everything after till the start of it and update the fields */
VOID RemoveCmdForModule (CHAR8* ModuleNameLocation)
{
  CHAR8 *CmdStart, *CmdEnd, *ScriptStart, *ScriptEnd, *Cptr;
  UINTN CmdShrinkSize;

  if (ModuleNameLocation == NULL)
    return;

  CmdStart = CmdEnd = ModuleNameLocation;
  ScriptStart = (CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr;
  ScriptEnd = (CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr + InfoBlkPtr->TotalCmdSize;

  while (CmdStart > ScriptStart)
  {
    if ((CmdStart[0] == '&') &&
        (CmdStart[1] == 'S') &&
        (CmdStart[2] == 'f') &&
        (CmdStart[3] == '='))
      break;

    --CmdStart;
  }

  while (CmdEnd < ScriptEnd)
  {
    if ((CmdEnd[0] == '&') &&
        (CmdEnd[1] == 'S') &&
        (CmdEnd[2] == 'f') &&
        (CmdEnd[3] == '='))
      break;

    ++CmdEnd;
  }

  /* Now we found the bounds, remove it. Keep it simple now, optimize later.
   * Removal algorith is,
   * Move the text from end of cmd till the end of script to start of cmd range
   * fill the end portion of script with nul for the length of
   * cmd removed */
  CmdShrinkSize = CmdEnd - CmdStart;

  CopyMem (TempCmdString, CmdStart, CmdShrinkSize);
  TempCmdString[CmdShrinkSize] = 0;

  Cptr = CmdStart;
  while (CmdEnd < ScriptEnd)
  {
    *Cptr = *CmdEnd;
    ++Cptr;
    ++CmdEnd;
  }

  while (Cptr < ScriptEnd)
  {
    *Cptr = 0;
    ++Cptr;
  }

  InfoBlkPtr->TotalCmdSize -= CmdShrinkSize;
}

int InsertTranslationEntry(CHAR8* PkgName, CHAR8* PkgRootPath, CHAR8* BuildOutPath)
{
   UINTN AdditionSize;
   CHAR8* SrcPtr, *SrcEnd, *DstPtr;
   
   //changing line 307 to global &%aObj\n to support multidrivers debug
   AsciiSPrint (TempCmdString,
                TEMP_STR_SZ,
                "\nglobal &%aPkg\n"
                "global &%aBinToSrcRelPath\n"
                "if (\"&%aBinToSrcRelPath\"==\"\")\n(\n  &%aBinToSrcRelPath=\".\"\n)\n"
                "y.spath.translate \"%a\" \"&%aPkg\"\n"
                "global &%aObj\n"
                "&%aObj=\"&%aPkg/&%aBinToSrcRelPath/%a\"\n",
                PkgName, PkgName, PkgName, PkgName, PkgRootPath, PkgName, PkgName, PkgName, PkgName, PkgName, BuildOutPath);

   AdditionSize = AsciiStrLen (TempCmdString);

   if (InfoBlkPtr->TotalCmdSize + AdditionSize > InfoBlkPtr->SymbolLoadCmdStrSize)
      return -1; // ignore silently

   SrcEnd = TranslationInsertPtr;
   SrcPtr = (CHAR8*)(InfoBlkPtr->SymbolLoadCmdStrPtr + InfoBlkPtr->TotalCmdSize);
   DstPtr = SrcPtr + AdditionSize;

   while (SrcPtr >= SrcEnd)
   {
      *DstPtr = *SrcPtr;
      --DstPtr;
      --SrcPtr;
   }

   AsciiStrnCpyS ( TranslationInsertPtr , AsciiStrLen(TranslationInsertPtr) + AsciiStrLen(TempCmdString), TempCmdString, AdditionSize);
   //AsciiStrnCpyS is adding a NULL value at the end of the Destination string 
   // according to this definition If no null char is copied from
   // Source, then Destination[Length] is always set to null.
   // which was not there previously with the AsciiStrnCpy Function
   // so we are facing Practice Block Nesting Error during Symbol load 
   // So assigning the last value of the Destination to \n 
   TranslationInsertPtr[AdditionSize] = '\n';
   if (InfoBlkPtr->LastCmdSize)
   {
      // TODO: Check if this needs to take care of the situation where
      // we don't need to adjust this, or need to adjust by a different
      // size
      InfoBlkPtr->LastCmdSize += AdditionSize;
   }
   InfoBlkPtr->TotalCmdSize += (UINT32)AdditionSize;
   TranslationInsertPtr += AdditionSize;

   return 0;
}

/* Check if a Pkg translation exists, if not, add it to tracking list
 * and generate the translation statement in the script (this operation
 * will change the size of script and any pointers within the script, like
 * incremental load pointer)
 */
int CheckAndAddTranslateEntry(CHAR8* PkgName, CHAR8* PkgRootPath, CHAR8* BuildOutPath)
{
   PkgPathInfoType *PkgEntry, *NewEntry;
   UINTN Sz;

   if ((PkgName == NULL) || (PkgRootPath == NULL) || (BuildOutPath == NULL))
      return -1;

   /* Check if the entry exists, just return if it does */
   PkgEntry = SymloadPkgsList;
   while (PkgEntry)
   {
      if (AsciiStrCmp(PkgEntry->PkgName, PkgName) == 0)
      {
         /* Found, just sanity check and exit */
         return 0;
      }
      PkgEntry = PkgEntry->Next;
   }

   /* If not, add */
   NewEntry = LocalMemAlloc (sizeof(*NewEntry));
   if (NewEntry == NULL)
      return -2;

   Sz = AsciiStrLen(PkgName) + 1;
   NewEntry->PkgName = LocalMemAlloc (Sz);
   if (NewEntry->PkgName == NULL)
      return -2;
   AsciiStrCpyS (NewEntry->PkgName, Sz, PkgName);

   Sz = AsciiStrLen(PkgRootPath) + 1;
   NewEntry->TranslatePath = LocalMemAlloc (Sz);
   if (NewEntry->TranslatePath == NULL)
      return -2;
   AsciiStrCpyS (NewEntry->TranslatePath, Sz, PkgRootPath);

   Sz = AsciiStrLen(BuildOutPath) + 1;
   NewEntry->ObjPath = LocalMemAlloc (Sz);
   if (NewEntry->ObjPath == NULL)
      return -2;
   AsciiStrCpyS (NewEntry->ObjPath, Sz, BuildOutPath);

   /* Fastest to find the recently added one */
   NewEntry->Next = SymloadPkgsList;
   SymloadPkgsList = NewEntry;

   InsertTranslationEntry (PkgName, PkgRootPath, BuildOutPath);

   return 0;
}

CHAR8 GetPathSeperator (CHAR8* ImageSymbolFilePath)
{
   CHAR8* TempPtr = ImageSymbolFilePath;
   CHAR8* EndPtr;
   UINTN  SLen;

   if (TempPtr == NULL)
      return 0;

   SLen = AsciiStrLen (ImageSymbolFilePath);
   EndPtr = TempPtr + SLen;

   if ((EndPtr < TempPtr) || (SLen >= EFI_PAGE_SIZE))
      return 0;

   while (TempPtr < EndPtr)
   {
      if ((*TempPtr == '/') || (*TempPtr == '\\'))
         return *TempPtr;
      ++TempPtr;
   }
   return 0;
}

static CHAR8* AsciiToLower (CHAR8* SrcStr, UINTN Size)
{
   CHAR8 ch;
   CHAR8 *TempPtr = SrcStr;

   while (Size)
   {
      ch = *TempPtr;
      if ((ch >= 'A') && (ch <= 'Z'))
      {
         ch += ('a' - 'A');
         *TempPtr = ch;
      }
      ++TempPtr;
      --Size;
   }

   return SrcStr;
}

/* if Path = "/local/mnt/workspace/abcdef/abl/adev/obj/ABL_OBJ/Build/DEBUG_CLANG35/" 
 *                                                            ^
 *                                                            |
 *
 *  FolderPtr would be pointing to the Path Seperator Before Build folder as above
 * Returned pointer would be pointing to path seperator before the resulting parent
 * folder on the same path buffer to make it easy to compare the pointers
 * Here the search will continue until the folder name does NOT have obj in it
 * */
CHAR8* GetNoObjParentFolder (CHAR8* FullPathPtr, CHAR8* FolderPtr, UINTN* FolderNameSizePtr)
{
   CHAR8 TempFolderName[64];
   CHAR8* TempPtr, *CopyTillPtr;

   if (FolderPtr <= FullPathPtr)
      return NULL;

   TempPtr = FolderPtr - 1;
   CopyTillPtr = FolderPtr;     // This pointer should be pointing to path seperator

   while (TempPtr > FullPathPtr)
   {
      if ((*TempPtr == '/') || (*TempPtr == '\\'))
      {
         UINTN Sz = (CopyTillPtr - TempPtr) - 1;
         AsciiStrnCpyS (TempFolderName, sizeof(TempFolderName), TempPtr + 1, Sz);
         AsciiToLower (TempFolderName, Sz);
         if (AsciiStrStr (TempFolderName, "obj") == NULL)
         {
            if (FolderNameSizePtr)
               *FolderNameSizePtr = Sz;
            return TempPtr + 1;
         }

         CopyTillPtr = TempPtr;
      }
      --TempPtr;
   }
   return NULL;
}

/* Copy the full path into global TempPathString for processing and returning the
 * pointer Symbol File Path.
 * Pkg Name is copied to TempPkgNameMem buffer and PkgName pointer is returned to 
 * that buffer location. Because of this, those global buffers shouldn't be altered */
CHAR8* GetPkgNameAndSymbolPath (CHAR8* ImageSymbolFilePath, CHAR8** SymFilePathPtr)
{
   /*  Pkg name is found between Build and DEBUG_* / RELEASE_* folders
    *    - Replace path seperator with _
    *    - If there is not folder between those, then its ABL path
    *    - Then jump to parent folders until a folder without obj is found
    *      since that would be the root where both Sources and Obj output
    *      are found
    * */
   CHAR8 *BuildFolderPtr;
   CHAR8 *DbgRelFolderPtr;
   CHAR8 *ArchImgFolderPtr;
   CHAR8 *SymbolFilePath;
   CHAR8  PathSepChar, *PathSepStr;
   CHAR8  TempWorkStr[32];
   UINTN  FolderJumpLen = 0;
   UINTN  PkgNameLen = 0;
   CHAR8* PkgNamePtr;
   int i;

   if (ImageSymbolFilePath == NULL)
      return NULL;

   if (ImageSymbolFilePath[0] == 0)  // Zero len for images that don't have any path...!!?
      return NULL;

   PathSepChar = GetPathSeperator (ImageSymbolFilePath);

   if (PathSepChar == 0)
      return NULL;
   else if (PathSepChar == '/')
      PathSepStr = "/";
   else if (PathSepChar == '\\')
      PathSepStr = "\\";
   else
      return NULL;

   AsciiSPrint (TempWorkStr, sizeof(TempWorkStr), "%aBuild%a", PathSepStr, PathSepStr);

   AsciiStrCpyS (TempPathString, TEMP_STR_SZ, ImageSymbolFilePath);

   BuildFolderPtr = AsciiStrStr (TempPathString, TempWorkStr);
   if (BuildFolderPtr == NULL)
      return NULL;

   AsciiSPrint (TempWorkStr, sizeof(TempWorkStr), "%aDEBUG_", PathSepStr);

   DbgRelFolderPtr = AsciiStrStr (TempPathString, TempWorkStr);
   if (DbgRelFolderPtr == NULL)
   {
      AsciiSPrint (TempWorkStr, sizeof(TempWorkStr), "%aRELEASE_", PathSepStr);

      DbgRelFolderPtr = AsciiStrStr (TempPathString, TempWorkStr);
      if (DbgRelFolderPtr == NULL)
         return NULL;
   }

   AsciiSPrint (TempWorkStr, sizeof(TempWorkStr), "%aAARCH64%a", PathSepStr, PathSepStr);

   FolderJumpLen = 9;  // Add length of /AARCH64/ to get to next folder
   ArchImgFolderPtr = AsciiStrStr (TempPathString, TempWorkStr);
   if (ArchImgFolderPtr == NULL)
   {
      AsciiSPrint (TempWorkStr, sizeof(TempWorkStr), "%aARM%a", PathSepStr, PathSepStr);
      FolderJumpLen = 5;  // Add length of /ARM/ to get to next folder

      ArchImgFolderPtr = AsciiStrStr (TempPathString, TempWorkStr);
      if (ArchImgFolderPtr == NULL)
         return NULL;
   }

   SymbolFilePath = ArchImgFolderPtr + FolderJumpLen;

   PkgNamePtr = BuildFolderPtr + 6; // Jump over past "/Build" for Pkg Name start TODO: Compare to end ptr

   PkgNameLen = DbgRelFolderPtr - PkgNamePtr;

   /* Now see how much does the folder names span between Build and DbgRel folders */
   if (PkgNameLen == 0)
   {
      UINTN NameSize = 0;
      CHAR8 *ParentPtr;
      /* ABL case */
      ParentPtr = GetNoObjParentFolder (TempPathString, BuildFolderPtr, &NameSize);
      if ((ParentPtr == NULL) || (NameSize == 0))
         return NULL;

      PkgNameLen = NameSize;
      PkgNamePtr = ParentPtr;
      *(PkgNamePtr + NameSize) = 0; // Include the pkg name folder which is common to both sources and objects
   }
   else
   {
      PkgNamePtr++;    // go past "Build/"
      --PkgNameLen;
   }

   AsciiStrnCpyS (TempPkgNameMem, TEMP_PKG_NAME_MEM_SIZE, PkgNamePtr, PkgNameLen);

   for (i=0; i<PkgNameLen; ++i)
   {
      if ((TempPkgNameMem[i] == '/') || (TempPkgNameMem[i] == '\\'))
         TempPkgNameMem[i] = '_';
   }

   // Null terminate for translation path ends at Build Folder start
   *BuildFolderPtr = 0;
   ++BuildFolderPtr;

   // Null terminate for Obj path ends just before symbol file path start
   *(SymbolFilePath - 1) = 0;

   /* Now we have Pkg name for both Cases */
//   DEBUG((EFI_D_ERROR, "Pkg Name : %a\n", TempPkgNameMem));
//   DEBUG((EFI_D_ERROR, "Translation path : %a\n", TempPathString));
//   DEBUG((EFI_D_ERROR, "Build out folder : %a\n", BuildFolderPtr));
//   DEBUG((EFI_D_ERROR, "dll path : %a\n", SymbolFilePath));

   CheckAndAddTranslateEntry (TempPkgNameMem, TempPathString, BuildFolderPtr);

   if (SymFilePathPtr)
      *SymFilePathPtr = SymbolFilePath;

   return TempPkgNameMem;
}

/*******************************************************************************
 *            PUBLIC functions
*******************************************************************************/
/**
  Process image loading event and update the symbol loading debug script

  If ImageContext is NULL, then return

  @param  ImageContext  Pointer to the image context structure that describes the
                        PE/COFF image that has already been loaded and relocated.

**/
VOID
ProcessImageLoad (IN PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext)
{
  CHAR8 *ImgPathPtr;
  CHAR8 *TempCmdPtr;
  UINTN  StripParts;
  CHAR8* CmdPtr = NULL;
  UINTN  CmdLen;
  UINT64 LoadAddr;
  CHAR8* SymFilePath = NULL;
  CHAR8* PkgName;

  if (ImageContext == NULL || ImageContext->PdbPointer == NULL)
    return;

  if (InfoBlkPtr == NULL)
  {
    InfoBlkPtr = (UefiInfoBlkType*)GetInfoBlkPtr();
    if (InfoBlkPtr == NULL)
      return;
  }

  if (TempCmdString == NULL)
  {
     CHAR8* EndPtr;

    TempCmdString = AllocatePages(TEMP_WORK_BUFFERS_PAGE_CNT);
    if (TempCmdString == NULL)
      return;

    EndPtr = TempCmdString + (TEMP_WORK_BUFFERS_PAGE_CNT * EFI_PAGE_SIZE);

    TempPathString = TempCmdString + TEMP_STR_SZ;
    if ((TempPathString + TEMP_STR_SZ) > EndPtr)
       while (1); // wrong configuration, increase alloc page count

    TempPkgNameMem = TempPathString + TEMP_PKG_NAME_MEM_SIZE;
    if ((TempPkgNameMem + TEMP_PKG_NAME_MEM_SIZE) > EndPtr)
       while (1); // wrong configuration, increase alloc page count
  }

  if (InfoBlkPtr->SymbolLoadCmdStrPtr == 0)
  {
    InfoBlkPtr->LoaderBreakPoint = (UINT64)BreakPointFunction;
    InfoBlkPtr->SymbolLoadCmdStrPtr = (UINT64)AllocatePages(ALLOC_PAGES);

    if (InfoBlkPtr->SymbolLoadCmdStrPtr == 0)
      return;

    InfoBlkPtr->SymbolLoadCmdStrSize = ALLOC_PAGES * EFI_PAGE_SIZE;

    SetMem ((VOID*)InfoBlkPtr->SymbolLoadCmdStrPtr, InfoBlkPtr->SymbolLoadCmdStrSize, 0);

    LocalMemBase = AllocatePages(1);
    LocalMemFree = LocalMemBase;
    LocalMemEnd = LocalMemBase + (EFI_PAGE_SIZE / sizeof(*LocalMemBase));
	
    /* AsciiSprint used later forces to \r\n for any combo of CR/LF, so if we keep
     * CR/LF combo same across the script then it would showup clean in all editors
     * and Practice script will not complain about the last parenthesis */
    /* DeclarationPointer will be pointing to the end of string here before the
     * last newline, so if the formatting is changed, it needs to be updated */
    AsciiStrCatS ((CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr, InfoBlkPtr->SymbolLoadCmdStrSize,
        "local &Sf\r\n\r\n");
    CmdPtr = (CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr;
    CmdLen = AsciiStrLen (CmdPtr);
    InfoBlkPtr->TotalCmdSize += (UINT32)CmdLen;
    TranslationInsertPtr = (CHAR8*)(InfoBlkPtr->SymbolLoadCmdStrPtr + InfoBlkPtr->TotalCmdSize - 2);
  }

  CmdPtr = (CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr;
  LoadAddr = (ImageContext->ImageAddress + ImageContext->SizeOfHeaders);

  ImgPathPtr = ImageContext->PdbPointer;

  PkgName = GetPkgNameAndSymbolPath (ImgPathPtr, &SymFilePath);

  if ((ImgPathPtr == NULL) || (PkgName == NULL) || (SymFilePath == NULL))
     return;

  /*
  * For each core module, add the following to the cmm script:
  * &Sf="<path_to_dll>"
  * if (os.file("&Sf"))
  * (
  *   data.load.elf "&Sf" <addr> /nocode /noclear
  * )
  */
  AsciiSPrint (TempCmdString, TEMP_STR_SZ,
               "&Sf=\"&%aObj/%a\"\nif (os.file(\"&Sf\"))\n(\n  data.load.elf \"&Sf\" "
               ADDRESS_FORMAT_STRING " /nocode /noclear\n)\n",
               PkgName, SymFilePath, LoadAddr);

  CmdLen = AsciiStrLen (TempCmdString);

  /* Silently skip loading symbols if there is no more space */
  if (InfoBlkPtr->TotalCmdSize + CmdLen > InfoBlkPtr->SymbolLoadCmdStrSize)
  {
    ++SpaceCeilingHit;
    return;
  }

  TempCmdPtr = CmdPtr + InfoBlkPtr->TotalCmdSize;

  /* Write T32 practice script changes to memory */
  InfoBlkPtr->TotalCmdSize += (UINT32)CmdLen;
  CopyMem(TempCmdPtr, TempCmdString, CmdLen);

  if (!DrvrListBuilt)
    BuildDriverList(InfoBlkPtr->DebugStopDriverStr);

  /* Check if current module matches string passed by host and enter breakpoint */
  AsciiSPrint(TempCmdString, TEMP_STR_SZ, "%a", ImgPathPtr);
  if (MatchDriverName(ConvertToUpper(TempCmdString)))
  {
    ExtractModuleName (ImgPathPtr, InfoBlkPtr->BkptModuleName);
    BreakPointFunction();
  }
}

VOID
ProcessImageUnload (IN PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext)
{
  CHAR8 *TempCmdPtr;
  CHAR8 *UnloadingModule;
  CHAR8 *AddrLocation;
  UINTN  CmdLen;
  CHAR8  AddressString[20];
  UINT64 LoadAddr;
  CHAR8 *ModuleNameLocation, *ScriptStart;
  UINTN  ModNameLen;
  CHAR8 *EndOfModulePtr, *StartOfModulePtr;

  if (ImageContext == NULL || ImageContext->PdbPointer == NULL)
    return;

  if (InfoBlkPtr == NULL)
  {
    InfoBlkPtr = (UefiInfoBlkType*)GetInfoBlkPtr();
    if (InfoBlkPtr == NULL)
      return;
  }

  if (InfoBlkPtr->TotalCmdSize == 0)
    return;

  ScriptStart = (CHAR8*)InfoBlkPtr->SymbolLoadCmdStrPtr;

  LoadAddr = (ImageContext->ImageAddress + ImageContext->SizeOfHeaders);

  AsciiSPrint (AddressString, sizeof(AddressString), ADDRESS_FORMAT_STRING, LoadAddr);

  UnloadingModule = ExtractModuleName(ImageContext->PdbPointer, TempCmdString);
  if (UnloadingModule == NULL)
    return;

  AddrLocation = TempCmdPtr = ScriptStart + InfoBlkPtr->TotalCmdSize;
  while (AddrLocation)
  {
    AddrLocation = JumpToNextAddr (AddrLocation);

    if (AddrLocation == NULL)
      break;

    if (CompareMem (AddressString, AddrLocation, AsciiStrLen(AddressString) - 1) == 0)
      break;
  }

  if (AddrLocation)
  {
    ModuleNameLocation = GetModuleNameForAddr (AddrLocation, &ModNameLen);

    if (ModuleNameLocation == NULL)
      return;

    if (CompareMem (ModuleNameLocation, UnloadingModule, ModNameLen - 1) == 0)
    {
      RemoveCmdForModule (ModuleNameLocation);
      return;
    }
  }
}


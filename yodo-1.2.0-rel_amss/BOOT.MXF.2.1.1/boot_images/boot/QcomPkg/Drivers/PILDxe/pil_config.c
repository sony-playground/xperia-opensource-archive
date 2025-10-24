/*===============================================================================
  Copyright (c) 2017-2018, 2021, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         pil_config.c
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  08/08/22   cm         Added change to detemernine PilConfigIndex 
                        and also added Mediatype as Config key
						Porting Support for loading images from backup partition
  12/08/21   cm         Added PreImage and PostImage
  06/14/17   yw         initial version

================================================================================*/
#include <pil_config.h>
#include <pil_loader.h>
#include<Library/BaseMemoryLib.h>
#include<Library/UefiLib.h>
#include<Library/QcomLib.h>
#include<Library/ParserLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Library/TimerLib.h>
#include <Library/QcomBaseLib.h>

/* cfg arrary used to save all subsys cfgs, PilSubsysCfgNum is 
the number of valid items in the array */
STATIC UINT32                    PilSubsysCfgNum = 0;
STATIC PIL_SUBSYS_CFG_TYPE        PilSubsysCfgList[PIL_SUBSYS_MAX_NUM] = { {0} };

STATIC PIL_SUBSYS_CFG_TYPE TempCfg;
STATIC BOOLEAN CfgFound = FALSE; 

/* base address of image load info region in IMEM */
UINTN ImageLoadInfoBase = 0;
/* size of image load info region in IMEM*/
UINT32 ImageLoadInfoSize = 0;

STATIC UINT8* CfgBuffer = NULL;
STATIC UINTN CfgFileSize = 0;

/*
    RetailList[] contains the list of SubsysID which is allowed 
    to be processed/loaded by PIL in retail product
*/
UINT32     RetailImageNum = 0; 
PIL_SUBSYS_CFG_TYPE*    RetailList[PIL_SUBSYS_MAX_NUM] = { 0 };

/*
    AutoStartList[] contains the list of SubsysID which is processed/loaded
    at PIL loading
*/
UINT32     AutoStartImageNum = 0;
PIL_SUBSYS_CFG_TYPE*  AutoStartList[PIL_SUBSYS_MAX_NUM] = { 0 };


/* Index of uefipil cfg file to be chosen */
UINT8 PilConfigIndex;

/* Array of all uefipil cfg files */
CHAR16 PIL_CONFIG_FILES[PIL_CONFIG_MAX][PIL_CONFIG_STR_MAX_LEN] = {L"uefipil.cfg", L"uefipil_network.cfg"};


#define SWAP_BYTES(x,y)  do {           \
                           UINT8 t;     \
                           t = (x);     \
                           (x) = (y);   \
                           (y) = t;     \
                         }while(0)


VOID SetPilConfigIndex(UINT8 index)
{
  PilConfigIndex = index;
  return;
}

/* Convert Byte Stream data to GUID format. The parser would have returned the
 * GUID in byte stream format, the cfg will have in guid format, this routine
 * makes sure to put the data into correct format
 * For example:
 * if Cfg has data in below format:
 *    DEA0BA2C CBDD 4805 B4F9 F428251C3E98
 *
 * Parser will return data as follows in stream format
 *    DE A0 BA 2C CB DD 48 05 B4 F9 F4 28 25 1C 3E 98
 *
 * Need to be converted into GUID format (Considering integer and endianness)
 *    DEA0BA2C CBDD 4805 B4F9 F428251C3E98 is equal to stream as follows
 *    2C BA A0 DE DD CB 05 48 B4 F9 F4 28 25 1C 3E 98
 * */
STATIC VOID AdjustGUID (UINT8* Buffer)
{
  /* DWord */
  SWAP_BYTES(Buffer[0], Buffer[3]);
  SWAP_BYTES(Buffer[1], Buffer[2]);

  /* Word */
  SWAP_BYTES(Buffer[4], Buffer[5]);

  /* Word */
  SWAP_BYTES(Buffer[6], Buffer[7]);
}


/**
  callback function to fill PIL configure structure for each subsys 

  @param[in] section        section name of PIL subsys configuration, i.e. ADSP, SLPI etc
  @garam[in] key            name string of the configuration structure field
  @param[in] value          value string of the configuration structure field
  
  @retval                     none

**/
STATIC VOID ConfigKeyValCb (UINT8* Section, UINT8* Key, UINT8* Value)
{
    CfgFound = TRUE;
    
    if (AsciiStriCmp ((CHAR8*)Key, "Type") == 0)
    {
        if (AsciiStriCmp((CHAR8*)Value, "elf_fv") == 0)
          TempCfg.Type = ELF_FV;
        else if (AsciiStriCmp((CHAR8*)Value, "elf_single") == 0)
          TempCfg.Type = ELF_SINGLE;
        else if (AsciiStriCmp((CHAR8*)Value, "elf_split") == 0)
          TempCfg.Type = ELF_SPLIT;
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "FwName") == 0)
    {
        AsciiStrToUnicodeStrS((CHAR8*)Value, TempCfg.FwName, NAME_MAX_LENGTH);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "PreImage") == 0)
    {
        AsciiStrToUnicodeStrS((CHAR8*)Value, TempCfg.PreImage, NAME_MAX_LENGTH);
    }

    else if (AsciiStriCmp ((CHAR8*)Key, "SubsysID") == 0)
    {
        TempCfg.SubsysID = AsciiStrDecimalToUintn((CHAR8*)Value);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "PartiLabel") == 0)
    {
        AsciiStrToUnicodeStrS((CHAR8*)Value, TempCfg.PartiLabel, NAME_MAX_LENGTH);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "PartiRootGuid") == 0)
    {
        HexStrToBin (Value, AsciiStrLen((CHAR8*)Value), 
                      (UINT32*)&TempCfg.PartiRootGuid, sizeof(EFI_GUID));
        AdjustGUID((UINT8*)&TempCfg.PartiRootGuid);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "PartiGuid") == 0)
    {
        HexStrToBin (Value, AsciiStrLen((CHAR8*)Value), 
                      (UINT32*)&TempCfg.PartiGuid, sizeof(EFI_GUID));
        AdjustGUID((UINT8*)&TempCfg.PartiGuid);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "ImagePath") == 0)
    {
        AsciiStrToUnicodeStrS((CHAR8*)Value, TempCfg.ImagePath, NAME_MAX_LENGTH);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "ResvMemoryStart") == 0)
    {
        TempCfg.ResvRegionStart = AsciiStrHexToUint64((CHAR8*)Value);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "ResvMemorySize") == 0)
    {
        TempCfg.ResvRegionSize = AsciiStrHexToUint64((CHAR8*)Value);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "ImageLoadInfo") == 0)
    {
        if (AsciiStriCmp((CHAR8*)Value, "Yes") == 0)
            TempCfg.ImageLoadInfo = TRUE;
        else if (AsciiStriCmp((CHAR8*)Value, "No") == 0)
            TempCfg.ImageLoadInfo = FALSE;
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "Unlock") == 0)
    {
        if (AsciiStriCmp((CHAR8*)Value, "Yes") == 0)
            TempCfg.Unlock = TRUE;
        else if (AsciiStriCmp((CHAR8*)Value, "No") == 0)
            TempCfg.Unlock = FALSE;
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "OverrideElfAddr") == 0)
    {
        if (AsciiStriCmp((CHAR8*)Value, "Yes") == 0)
            TempCfg.OverrideElfAddr = TRUE;
        else if (AsciiStriCmp((CHAR8*)Value, "No") == 0)
            TempCfg.OverrideElfAddr = FALSE;
    }

    else if (AsciiStriCmp ((CHAR8*)Key, "ProxyGuid") == 0)
    {
        HexStrToBin (Value, AsciiStrLen((CHAR8*)Value),
                      (UINT32*)&TempCfg.ProxyGuid, sizeof(EFI_GUID));
        AdjustGUID((UINT8*)&TempCfg.ProxyGuid);
    }
	
	else if (AsciiStriCmp ((CHAR8*)Key, "BackupPartiLabel") == 0)
    {
        AsciiStrToUnicodeStr((CHAR8*)Value, TempCfg.BackupPartiLabel);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "BackupPartiRootGuid") == 0)
    {
        HexStrToBin (Value, AsciiStrLen((CHAR8*)Value), 
                      (UINT32*)&TempCfg.BackupPartiRootGuid, sizeof(EFI_GUID));
        AdjustGUID((UINT8*)&TempCfg.BackupPartiRootGuid);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "BackupPartiGuid") == 0)
    {
        HexStrToBin (Value, AsciiStrLen((CHAR8*)Value), 
                      (UINT32*)&TempCfg.BackupPartiGuid, sizeof(EFI_GUID));
        AdjustGUID((UINT8*)&TempCfg.BackupPartiGuid);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "PostImage") == 0)
    {
        AsciiStrToUnicodeStrS((CHAR8*)Value, TempCfg.PostImage, NAME_MAX_LENGTH);
    }
    
    else if (AsciiStriCmp ((CHAR8*)Key, "Mediatype") == 0)
    {
        AsciiStrToUnicodeStrS((CHAR8*)Value, TempCfg.MediaType, NAME_MAX_LENGTH);
    }

}


/**
  Convert string to Lowercase if lowercase alphabets found.

  @param  Str      Null Terminated string of characters.
          StrSize Max size of buffer, to prevent against
                   strings that are not NULL terminated.

  @retval  VOID

**/
STATIC VOID UnicodeStrToLower (CHAR16* Str, UINT32 StrSize)
{
    UINT32 i;
    if(Str == NULL)
      return;
    for (i=0;i<StrSize;i++)
    {
        if (Str[i]==0)
            break;
        if(Str[i] >= 'A' && Str[i] <= 'Z')
        {
           Str[i] += ('a'-'A');
        }
    }        
}

/**
  Convert string to uppercase if uppercase alphabets found.

  @param  Str      Null Terminated string of characters.
          StrSize Max size of buffer, to prevent against
                   strings that are not NULL terminated.

  @retval  VOID

**/
STATIC VOID AsciiStrToUpper (CHAR8* Str, UINT32 StrSize)
{
  do
  {
    if(Str == NULL)
      break;
    while( (*Str!=0) && StrSize )
    {
      if(*Str >= 'a' && *Str <= 'z')
      {
         *Str = *Str - ('a'-'A');
      }
      StrSize--;
      Str++;
    }
  }while(0);
}

/**
  retrieve PIL configure information from configure file 

  @param[in] Section        section name of PIL configuration, e.g. ADSP, SLPI etc 
                            must be uppercase CHAR8
  
  @retval PIL_SUCCESS       success
  @retval other             failurel

**/
STATIC PIL_STATUS PilGetSubsysCfg(CHAR8* Section)
{
  EFI_STATUS Status;
  INTN CfgPd;
  
  if (!Section)
    return PIL_INVALID_PARAM;
    
  if (CfgBuffer == NULL)
  {
    Status = ReadFromFV(PIL_CONFIG_FILES[PilConfigIndex], (VOID **) &CfgBuffer, &CfgFileSize);
    if (EFI_SUCCESS != Status)
      return PIL_GENERIC_ERR;
  }
    
  CfgPd = OpenParser (CfgBuffer, (UINT32)CfgFileSize, NULL);
  if (CfgPd < 0)
    return PIL_GENERIC_ERR;
    
    ZeroMem((VOID*)&TempCfg, sizeof(PIL_SUBSYS_CFG_TYPE));
    CfgFound = FALSE;
    
    EnumKeyValues (CfgPd, (UINT8*)Section, ConfigKeyValCb);
    CloseParser(CfgPd); 

    if (!CfgFound)
        return PIL_INVALID_CFG;
    return PIL_SUCCESS;
}


/**
  look up if subsys cfg with given subsys name already exits

  @param[in] Name            FwName of the subsys to be found, case insensitive 
  
  @retval non-NULL           Ptr to the cfg of the subsys with the given subsys name 
  @retval NULL              subsys with the given name is not found

**/

STATIC PIL_SUBSYS_CFG_TYPE* LookUpCfgByName(CHAR16* Name)
{
    PIL_SUBSYS_CFG_TYPE* RetCfg = NULL;
    UINT32 Idx;
    
    for (Idx = 0; Idx<=PilSubsysCfgNum; Idx++)
    {
        /* version is no-zero means it's valide cfg, go through the cfg list 
        searching for cfg item with same Fwname, case insensitive */
        if (PilSubsysCfgList[Idx].Version != 0 && \
             0 == StriCmp(Name, PilSubsysCfgList[Idx].FwName))
        {
            RetCfg = &PilSubsysCfgList[Idx];
            break;
        }
    }
    return RetCfg;
}


/**
  duplicate the given Cfg into PilSubsysCfgList

  @param[in] Cfg                Cfg to be added 
  @param[in] Overwrite            if find existing cfg with the same Id, overwrite it with given cfg 
  
  @retval non-NULL           Ptr to the added cfg
  @retval NULL              fail to add the cfg

**/

PIL_SUBSYS_CFG_TYPE* PilDuplicateCfg(PIL_SUBSYS_CFG_TYPE* Cfg)
{
    PIL_SUBSYS_CFG_TYPE* Ret;
    
    // if no cfg found, add the cfg to PilSubsysCfgList, return the Ptr
    Ret = &PilSubsysCfgList[PilSubsysCfgNum++];

    if (PilSubsysCfgNum >= PIL_SUBSYS_MAX_NUM) {
        ASSERT_EFI_ERROR(EFI_BUFFER_TOO_SMALL);
        ASSERT_FAIL_PIL_RETURN(0, NULL, PIL_INVALID_CFG);
    }
    
    CopyMem((VOID*)Ret, (VOID*)Cfg, sizeof(PIL_SUBSYS_CFG_TYPE));
    if (Ret->Version == 0)
      Ret->Version = PIL_SUBSYS_CFG_LATEST_VERSION;
    return Ret;
}

/*
   given a FwName, check if the subsys is alreasy in PilSubsysCfgList
   if found return the ptr, otherwise find the cfg in cfg file, add
   to PilSubsysCfgList and return the ptr
   
   @param[in] Name                unique FwName of the subsys
  
   @retval non-NULL            Ptr to the added cfg
   @retval NULL              fail to add the cfg

*/
PIL_SUBSYS_CFG_TYPE* PilInitCfgByUnicodeName(CHAR16* Name)
{
    PIL_SUBSYS_CFG_TYPE* RetCfg;
    INTN  PilRet;
    CHAR8 Section[NAME_MAX_LENGTH];
    CHAR16 TempFwName[NAME_MAX_LENGTH];
    
    if (!Name)
        return NULL;

    if ( NULL!= (RetCfg = LookUpCfgByName(Name)))
        return RetCfg;
    
    // convert to CHAR8 uppercase
    UnicodeStrToAsciiStrS(Name, Section, NAME_MAX_LENGTH);
    AsciiStrToUpper(Section, NAME_MAX_LENGTH);
    
    // get Cfg from uefipil.cfg or from Variable, save in TempCfg
    PilRet = PilGetSubsysCfg(Section);
    if (PilRet != PIL_SUCCESS) {
        PIL_ERROR("Failed to get cfg for %s\n", Name);
        return NULL;
    }
    
    // update FwName as unicode string with lower case if it's missing
    if (TempCfg.FwName[0] == 0)  {
        StrnCpyS(TempFwName, NAME_MAX_LENGTH-1, Name, NAME_MAX_LENGTH-1);
        UnicodeStrToLower(TempFwName, NAME_MAX_LENGTH);
        StrnCpyS(TempCfg.FwName, NAME_MAX_LENGTH-1, TempFwName, NAME_MAX_LENGTH-1);
    }

  return PilDuplicateCfg(&TempCfg);
}

#if 0
/**
  if find Cfg with given FwName(Section) in cfg list, return the ptr
  otherwise retrieve PIL configure information from configure file

  @param[in] section        section name of PIL configuration, e.g. ADSP, SLPI etc
                            case insensitive, could be FwName  
  
  @retval non-NULL           ptr to the cfg
  @retval NLL                fail

**/

PIL_SUBSYS_CFG_TYPE* PilInitCfgByAsciiName(CHAR8* Section)
{
    EFI_STATUS Status; 
    PIL_SUBSYS_CFG_TYPE* RetCfg;
    INTN CfgPd;
    CHAR16 TempFwName[NAME_MAX_LENGTH];
    
    if (!Section)
        return NULL;
    
    // convert to CHAR16 lowercase
    ZeroMem((VOID*)TempFwName, sizeof(CHAR16)*NAME_MAX_LENGTH);
    AsciiStrToUnicodeStrS(Section, TempFwName, NAME_MAX_LENGTH);
    UnicodeStrToLower(TempFwName, NAME_MAX_LENGTH);
    
    if ( NULL!= (RetCfg = LookUpCfgByName(TempFwName)))
        return RetCfg;
    
    if (CfgBuffer == NULL)
    {
      Status = ReadFromFV(PIL_CONFIG_FILES[PilConfigIndex], (VOID **) &CfgBuffer, &CfgFileSize);
      if (EFI_SUCCESS != Status)
        return PIL_GENERIC_ERR;
    }
    
    CfgPd = OpenParser (CfgBuffer, (UINT32)CfgFileSize, NULL);
    if (CfgPd < 0)
      return PIL_GENERIC_ERR;
    
    ZeroMem((VOID*)&TempCfg, sizeof(PIL_SUBSYS_CFG_TYPE));
    CfgFound = FALSE;
    
    EnumKeyValues (CfgPd, (UINT8*)Section, ConfigKeyValCb);
    CloseParser(CfgPd); 
    
    if (FALSE == CfgFound)
        return NULL;
    
    // update FwName if it's missing
    if (TempCfg.FwName[0] == 0) 
        StrnCpyS(TempCfg.FwName, NAME_MAX_LENGTH-1, TempFwName, NAME_MAX_LENGTH-1);
    
    return PilDuplicateCfg(&TempCfg);
}
#endif

#if 0
/**
  look up if given cfg already exits by the subsys ID

  @param[in] Id                Id of the subsys to be searched for 
  
  @retval non-NULL           Ptr to the cfg of the subsys with the given Id 
  @retval NULL              subsys with the given Id is not found

**/

PIL_SUBSYS_CFG_TYPE* LookUpCfgById(UINT32 Id)
{
    UINT32 Idx;
    PIL_SUBSYS_CFG_TYPE* Ret = NULL;
    
    for (Idx = 0; i<=PilSubsysCfgNum; i++)
    {
        if (PilSubsysCfgList[Idx].Version != 0 && \
            Id == PilSubsysCfgList[Idx].SubsysID) 
        {
            Ret = &PilSubsysCfgList[Idx];
            break;
        }
    }
    return Ret;
}
#endif


/**
  callback function to get info of image load region 

  @param[in] Section        name of PIL config section, i.e. IMEM_LOAD_INFO
  @garam[in] key            name of the structure field of PIL_IMAGE_INFO_TYPE
  @param[in] Value          value string of the configuration structure field
  
  @retval                     none

**/
STATIC VOID InitImageLoadInfoCb(UINT8* Section, UINT8* Key, UINT8* Value)
{
    if (AsciiStriCmp ((CHAR8*)Key, "ImageLoadInfoBase") == 0)
    {
        ImageLoadInfoBase = AsciiStrHexToUintn((CHAR8*)Value);
    }
    
    if (AsciiStriCmp ((CHAR8*)Key, "ImageLoadInfoSize") == 0)
    {
        ImageLoadInfoSize = AsciiStrDecimalToUintn((CHAR8*)Value);
    }
}


/**
  callback function to initilize RetailList[] The list constains the subsys 
  which are allowed to be processed/loaded by PIL in retail product

  @param[in] Section    name of PIL retail section, i.e. RETAIL
  @param[in] key        name of PIL configuration section, i.e. ADSP, SLPI etc
  @param[in] Value        no value used in retail section

  @return none
**/
STATIC VOID InitRetailListCb(UINT8* Section, UINT8* Key, UINT8* Value)
{
    PIL_SUBSYS_CFG_TYPE* NewCfg;
    CHAR16 TempFwName[NAME_MAX_LENGTH];

    // convert to CHAR16 lowercase
    ZeroMem((VOID*)TempFwName, sizeof(CHAR16)*NAME_MAX_LENGTH);
    AsciiStrToUnicodeStrS((const CHAR8*)Key, TempFwName, NAME_MAX_LENGTH);
    UnicodeStrToLower(TempFwName, NAME_MAX_LENGTH);
    
    /* check cfg list, if found cfg just add to retail list
       otherwise find the cfg from cfg file, add to cfg list and 
       return the ptr
    */   
    NewCfg = PilInitCfgByUnicodeName(TempFwName);
    if (NewCfg != NULL) {
        RetailList[RetailImageNum++] = NewCfg;
    }
    else {
        PIL_ERROR("No %s cfg found in uefipil cfg file\n", Key);
        gLastPilError = PIL_INVALID_CFG;
        ASSERT(0);
    }
}


/**
  callback function to initilize AutoStartList[] The list constains the subsys 
  which are are processed/loaded by PIL by default

  @param[in] Section    name of PIL auto start section, i.e. AUTO
  @param[in] key        name of PIL configuration section, i.e. ADSP, SLPI etc
  @param[in] Value        no value used in AUTO section

  @return none
**/
STATIC VOID InitAutoListCb(UINT8* Section, UINT8* Key, UINT8* Value)
{
    PIL_SUBSYS_CFG_TYPE* NewCfg;
    CHAR16 TempFwName[NAME_MAX_LENGTH];
    
    // convert to CHAR16 lowercase
    ZeroMem((VOID*)TempFwName, sizeof(CHAR16)*NAME_MAX_LENGTH);
    AsciiStrToUnicodeStrS((const CHAR8*)Key, TempFwName, NAME_MAX_LENGTH);
    UnicodeStrToLower(TempFwName, NAME_MAX_LENGTH);
    
    /* check cfg list, if found cfg just add to auto list
       otherwise find the cfg from cfg file, add to cfg list and 
       return the ptr
    */
    NewCfg = PilInitCfgByUnicodeName(TempFwName);
    if (NewCfg != NULL) {
        AutoStartList[AutoStartImageNum++] = NewCfg;
    }
    else {
        PIL_ERROR("No %s cfg found in uefipil cfg file\n", Key);
        gLastPilError = PIL_INVALID_CFG;
        ASSERT(0);
    }
}

/**
  Initilize image list from given section. 
  The list could be
  Retail List - contains subsys which are allowed to be processed/loaded by PIL
  in retail product, or
  Auto List - contains subsys which are processed/loaded by PIL by default  
  or 
  read ImageLoadInfoBase & ImageLoadInfoSize from cfg file

  @param[in] Section            section name of the list, only support:
                                1) AUTO 2) RETAIL 3) IMAGE_LOAD_INFO_REGION

  @return EFI_SUCCESS           The function completed successfully.
  @return other                    Some error occurred.
**/
EFI_STATUS InitImageList(CHAR8* Section)
{
    EFI_STATUS Status; 
    INTN CfgPd;
    KeyValueCallBackFuncType InitListCb = NULL;
    CHAR8 SectionBuf[NAME_MAX_LENGTH] = { 0 };
    UINT32 SecLen = AsciiStrLen(Section);

    if (CfgBuffer == NULL)
    {
        Status = ReadFromFV(PIL_CONFIG_FILES[PilConfigIndex], (VOID **) &CfgBuffer, &CfgFileSize);
        if (EFI_SUCCESS != Status)
            return Status;
    }

    CfgPd = OpenParser (CfgBuffer, (UINT32)CfgFileSize, NULL);
    if (CfgPd < 0)
        return EFI_INVALID_PARAMETER;

    CopyMem(SectionBuf, Section, AsciiStrSize(Section));
    if ( SecLen == 4 && 0 == AsciiStrnCmp(SectionBuf, "AUTO", 4))
        InitListCb = InitAutoListCb;
    else if ( SecLen == 6 && 0 == AsciiStrnCmp(SectionBuf, "RETAIL", 5))
        InitListCb = InitRetailListCb;
    else if ( SecLen == 22 && 0 == AsciiStrnCmp(SectionBuf, "IMAGE_LOAD_INFO_REGION", 22))
        InitListCb = InitImageLoadInfoCb;
    else {
        ASSERT_EFI_ERROR(EFI_INVALID_PARAMETER);
        ASSERT_FAIL_EFI_RETURN(0, EFI_INVALID_PARAMETER, EFI_INVALID_PARAMETER);
    }

    EnumKeyValues (CfgPd, (UINT8*)Section, InitListCb);
    CloseParser(CfgPd);
    
    if (0 == AsciiStrnCmp("IMAGE_LOAD_INFO_REGION", SectionBuf, 22) &&
        (ImageLoadInfoBase == 0 || ImageLoadInfoSize == 0))
        return EFI_INVALID_PARAMETER;

    return EFI_SUCCESS;
}



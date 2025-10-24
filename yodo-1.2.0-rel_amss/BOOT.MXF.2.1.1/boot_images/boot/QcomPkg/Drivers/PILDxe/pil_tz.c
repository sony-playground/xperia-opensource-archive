/*===============================================================================
  Copyright (c) 2017-2021 Qualcomm Technologies, Inc.  All Rights Reserved.

  FILE:         pil_tz.c
  DESCRIPTION:

  REVISION HISTORY

  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  08/08/22   cm          Ported changes to support to load from backup partition
  12/08/21   cm          Adding support to load PreImage and PostImage
  09/10/20   yw          add PilShutdownImage() and optional ssr support
  07/07/20   kpa         Skip attempt to mount FAT partition if ImagePath is null
  03/22/19   md          Add function to Authenticate ELF-FV image
  10/08/18   yg          Add lock to make thread safe
  06/14/17   yw          initial version

================================================================================*/
#include<pil_tz.h>
#include<pil_log.h>
#include<pil_loader.h>
#include<pil_config.h>
#include<Library/BaseLib.h>
#include<Library/UefiLib.h>
#include<Protocol/EFIClock.h>
#include<Library/QcomLib.h>
#include<Library/PrintLib.h>
#include<Library/TimerLib.h>
#include<Library/QcomBaseLib.h>
#include<Library/EfiFileLib.h>
#include<Library/BaseMemoryLib.h>
#include<Library/QcomTargetLib.h>
#include<Library/MemoryAllocationLib.h>
#include<Library/UefiBootServicesTableLib.h>
#include<Library/UncachedMemoryAllocationLib.h>
#include <Library/KernelLib.h>
#include <boot_recovery_partition.h>

#define IS_ALPHABET(c)  (((c)>='a'&&(c)<='z')||((c)>='A'&&(c)<='Z')||((c)=='_'))

/*
    RetailList[] contains the list of SubsysID which is allowed
    to be processed/loaded by PIL in retail product
*/
extern UINT32     RetailImageNum;
extern PIL_SUBSYS_CFG_TYPE*   RetailList[];

UINT64 StorageSpentCnt, AuthSpentUs, FvProcSpentCnt;

const PIL_METHODS_TYPE PilSplitElf =
{
    .LoadMetaData = PilLoadMdtFile,
    .ValidateMetaData = PilValidateMetadata,
    .SetupMemoryRange = PilSetupMemoryRange,
    .LoadSegments = PilLoadSegments,
    .AuthAndReset = PilAuthAndReset,
    .PostLoad = PilPostLoad,
	.Shutdown = PilShutdown,
};

const PIL_METHODS_TYPE PilSingleElf =
{
    .LoadEntireImage = PilLoadElfFile,
    .LoadMetaData = CopyMetaDataFromLoadedElf,
    .ValidateMetaData = PilValidateMetadata,
    .SetupMemoryRange = PilSetupMemoryRange,
    .LoadSegments = PilLoadSegments,
    .AuthAndReset = PilAuthAndReset,
    .PostLoad = PilPostLoad,
	.Shutdown = PilShutdown,
};

const PIL_METHODS_TYPE PilFv =
{
    .LoadEntireImage = PilLoadElfFile,
    .LoadMetaData = CopyMetaDataFromLoadedElf,
    .ValidateMetaData = PilValidateMetadata,
    .SetupMemoryRange = PilSetupMemoryRange,
    .AuthAndReset = PilAuthAndReset,
    .PostLoad = PilPostLoad,
};

/**
  load and boot image by giving the subsys configure

  @param[in] cfg            configure of subsys to process/load

  @retval PIL_SUCCESS       success
  @retval other             failurel

**/
PIL_STATUS PilProcessImageInternal(PIL_SUBSYS_CFG_TYPE* CfgIn)
{
    EFI_STATUS  Status   = EFI_DEVICE_ERROR;
    PIL_SUBSYS_CTX_TYPE* Ctx;
    PIL_SUBSYS_CFG_TYPE* Cfg;
    PIL_SUBSYS_PRIV_TYPE* Priv;
    UINT64 LoadStart, LoadEnd;
    PIL_STATUS PilRet = PIL_SUCCESS;
    UINT32    Idx;
    const PIL_METHODS_TYPE*  PilMethod;

    StorageSpentCnt = AuthSpentUs = FvProcSpentCnt = 0;

    /* we need unique FwName to identify subsys, consider different
       subsys could have same ImagePath. */
    if (0 == CfgIn->FwName[0]) {
        PIL_ERROR("Need unique FwName\n");
        return PIL_INVALID_PARAM;
    }

    LoadStart = GetPerformanceCounter();

    /* look for cfg with the given name in cfg list, cfg file, and variables */
    Cfg = PilInitCfgByUnicodeName(CfgIn->FwName);
    if (Cfg != NULL) {
        if (Cfg != CfgIn) {
            /* Allow protocol users to override the cfg */
            DEBUG((EFI_D_ERROR, "Overriding PIL cfg by caller\n"));
            CopyMem(Cfg, CfgIn, sizeof(PIL_SUBSYS_CFG_TYPE));
        }
    }
    else {
        /* did not find cfg with given name, this subsys is not in cfg file or variables,
           need to duplicate the cfg in cfg list */
        Cfg = PilDuplicateCfg(CfgIn);
    }
    if(Cfg == NULL)
    {
        PIL_ERROR_CFG(Cfg, "Cfg is NULL Pointer\n");
        PilRet = PIL_INVALID_CFG;
        goto LoadErr;
    }
    if (RETAIL) {
        for (Idx = 0; Idx<RetailImageNum; Idx++) {
            if (RetailList[Idx] == Cfg)
                break;
        }
        if (Idx == RetailImageNum) {
            PIL_ERROR_CFG(Cfg, "not supported in retail\n");
            return PIL_SUBSYS_NOT_SUPPORTED;
        }
    }

    

    StorageSpentCnt = AuthSpentUs = FvProcSpentCnt = 0;
    LoadStart = GetPerformanceCounter();

    PilRet = PilInitSubsys(Cfg, &Ctx);
    if (PilRet != PIL_SUCCESS)
    {
        if (PilRet == PIL_SUBSYS_RUNNING) {
            PIL_WARN_CFG(Cfg, "subsys is in running\n");
            return PIL_SUBSYS_RUNNING;
        }
        else if (PilRet == PIL_SUBSYS_EXIST) {
            PIL_WARN_CFG(Cfg, "Found ctx exists, continue to load\n");
        }
        else  {
            PIL_ERROR_CFG(Cfg, "Failed to create ctx\n");
            goto LoadErr;
        }
    }

    Cfg = Ctx->Cfg;
    if(Cfg == NULL)
    {
        PIL_ERROR_CFG(Cfg, "Cfg is NULL Pointer\n");
        PilRet = PIL_INVALID_CFG;
        goto LoadErr;
    }
    Priv = Ctx->Priv;

    switch(Cfg->Type)
    {
        case ELF_FV:
            PilMethod = &PilFv;
            break;
        case ELF_SINGLE:
            PilMethod = &PilSingleElf;
            break;
        case ELF_SPLIT:
            PilMethod = &PilSplitElf;
            break;
        default:
            PIL_ERROR_CFG(Cfg, "%r is not supported\n", Cfg->Type);
            return PIL_SUBSYS_NOT_SUPPORTED;
    }

    if (Cfg->Type == ELF_FV) {
        PIL_INFO_CFG(Cfg, "Skip to mount FV partition\n");
    }
    else if (Cfg->Type == ELF_SPLIT || Cfg->Type == ELF_SINGLE) {
        EFI_GUID* RootGuid = IsZeroGuid((CONST GUID*)&Cfg->PartiRootGuid)?NULL:&Cfg->PartiRootGuid;
        EFI_GUID* PartiGuid = IsZeroGuid((CONST GUID*)&Cfg->PartiGuid)?NULL:&Cfg->PartiGuid;
        CHAR16*   PartiLabel = (PartiGuid == NULL)?Cfg->PartiLabel:NULL;
        
        if((Cfg->ImagePath[0] != 0) )
        {
            Status = MountFatPartitionExt(RootGuid, PartiGuid, PartiLabel);
            if (EFI_ERROR(Status)) {
                PIL_ERROR_CFG(Cfg, "Mount partition return %r\n", Status);
                //return PIL_LOAD_ERR;
            } else {
                PIL_INFO_CFG(Cfg, "Mount partition return %r\n", Status);
            }
        }
    }
    else {
        PIL_ERROR_CFG(Cfg, "No support type %r\n", Cfg->Type);
        return PIL_SUBSYS_NOT_SUPPORTED;
    }



    // load ELF file into memory for non-split image
    if (PilMethod->LoadEntireImage)
    {
        PilRet = PilMethod->LoadEntireImage(Ctx);
        if (PilRet != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to load ELF file\n");
            goto LoadErr;
        }
    }

    // load metadata into memory
    if (PilMethod->LoadMetaData)
    {
        PilRet = PilMethod->LoadMetaData(Ctx);
        if (PilRet != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to load metadata\n");
            goto LoadErr;
        }
    }
    else {
        PIL_ERROR_CFG(Cfg, "LoadMetaData cannot be NULL\n");
        PilRet = PIL_GENERIC_ERR;
        goto LoadErr;
    }

    // validate metadata including ELF and prgram headers, and hash segment
    if (PilMethod->ValidateMetaData)
    {
        PilRet = PilMethod->ValidateMetaData(Ctx);
        if (PilRet != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to validate metadata\n");
            goto LoadErr;
        }
    }
    else {
        PIL_ERROR_CFG(Cfg, "ValidateMetaData cannot be NULL\n");
        PilRet = PIL_GENERIC_ERR;
        goto LoadErr;
    }

    // setup memory range and notify hyp&tz PIL service
    if (PilMethod->SetupMemoryRange)
    {
        PilRet = PilMethod->SetupMemoryRange(Ctx);
        if (PilRet != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to setup memory range\n");
            goto LoadErr;
        }
    }
    else {
        PIL_ERROR_CFG(Cfg, "SetupMemoryRange cannot be NULL\n");
        PilRet = PIL_GENERIC_ERR;
        goto LoadErr;
    }

    // load segments, not required for FV image
    if (PilMethod->LoadSegments)
    {
        PilRet = PilMethod->LoadSegments(Ctx);
        if (PilRet != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to load segments\n");
            goto LoadErr;
        }
    }

    // bring subsys out of reset
    if (PilMethod->AuthAndReset)
    {
        PilRet = PilMethod->AuthAndReset(Ctx);
        if (PilRet != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to bring proc out of reset\n");
            goto LoadErr;
        }
    }
    else {
        PIL_ERROR_CFG(Cfg, "AuthAndReset cannot be NULL\n");
        PilRet = PIL_GENERIC_ERR;
        goto LoadErr;
    }

    /* post load operations, including write loading info in IMEM,
       unlcok is required, and process FV image
    */
    if (PilMethod->PostLoad)
    {
        PilRet = PilMethod->PostLoad(Ctx);
        if (PilRet != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to do post-load operations\n");
            goto LoadErr;
        }
    }

    /* update subsys status */
    Priv->ProcStatus = PIL_PROC_RUNNING;

    LoadEnd = GetPerformanceCounter();
    for (Idx=0; Idx<Priv->SmcCnt; Idx++)
        AuthSpentUs += Priv->SmcBenchMarkus[Idx].Timeus;

    PIL_WARN_CFG(Cfg, "Done t=%dms s=%dms a=%dms f=%dms\n", ConvertTimerCountms(LoadEnd - LoadStart),
                 ConvertTimerCountms(StorageSpentCnt), DivU64x32(AuthSpentUs, 1000),
                 ConvertTimerCountms(FvProcSpentCnt));

    PilCleanUp(Ctx);
    
    


    return PIL_SUCCESS;
LoadErr:
    return PilRet;
}

/**
  Wrapper Api to load and boot image by giving the subsys name

  @param[in] cfg            configuration of subsys to process/load

  @retval PIL_SUCCESS       success
  @retval other             failure

**/
PIL_STATUS PilProcessImageExt(PIL_SUBSYS_CFG_TYPE* CfgIn)
{
    PIL_STATUS  PStatus;
    PIL_SUBSYS_CFG_TYPE* NewCfg;
    PIL_STATUS ImageStatus = PIL_SUCCESS;
	PIL_SUBSYS_CFG_TYPE  CfgBckup;
	boot_recovery_status RecoveryStatus = BOOT_RECOVERY_SMEM_UNINITIALIZED_VARIABLE;
    
    if (CfgIn == NULL)
        return PIL_INVALID_PARAM;
    
    if(AsciiStriCmp((CHAR8*) CfgIn->PreImage, "") != 0)
    {
      PIL_WARN_CFG(CfgIn, "PreImage: %s\n", CfgIn->PreImage);
      NewCfg = PilInitCfgByUnicodeName(CfgIn->PreImage);
      if(NewCfg == NULL)
      {
        PIL_ERROR_CFG(CfgIn, "PreImage %s not found\n", CfgIn->PreImage);
        return PIL_INVALID_CFG;
      }	
      
      ImageStatus = PilProcessImageExt (NewCfg);

      //Pil status greater than 0 are Error codes
      if(ImageStatus)
      {
        PIL_ERROR_CFG(NewCfg, "PIL status: %d\n\n", ImageStatus);
        return ImageStatus;
      }
    }

    PStatus = PilProcessImageInternal (CfgIn);   
	if (PStatus != PIL_SUCCESS)
    { 
      if(CfgIn->Version < PIL_SUBSYS_CFG_VERSION_V2)
        return PIL_INVALID_CFG;
      
      /*Attempt to load from backup partition if feasible */
      if ((CfgIn->BackupPartiLabel[0] != 0x0) || 
          (!IsZeroGuid (&CfgIn->BackupPartiRootGuid)) ||
          (!IsZeroGuid (&CfgIn->BackupPartiGuid)))
      {
        PIL_WARN_CFG (CfgIn, "Attempting Backup partition Image load \n");

        /* backup config temporarily */
        CopyMem (&CfgBckup, CfgIn, sizeof (CfgBckup));
        
        /* Override current bad partition info with supposed good partition info */
        if (CfgIn->BackupPartiLabel[0] != 0x0)
          CopyMem (&CfgIn->PartiLabel, &CfgIn->BackupPartiLabel,  sizeof(CfgIn->PartiLabel));
        
        if (!IsZeroGuid (&CfgIn->BackupPartiRootGuid))
          CopyGuid (&CfgIn->PartiRootGuid, &CfgIn->BackupPartiRootGuid);
        
        if (!IsZeroGuid (&CfgIn->BackupPartiGuid))
          CopyGuid (&CfgIn->PartiGuid, &CfgIn->BackupPartiGuid);
        
        PStatus = PilProcessImageInternal (CfgIn);
        if (PStatus == PIL_SUCCESS)
        {
          /*call boot recovery partition lib api to report good bad guids. */
          /*bad: CfgBckup->PartiGuid    Good: CfgIn->PartiGuid*/
           PIL_WARN_CFG (CfgIn, "Image loaded from %g Partition instead of %g \n"
                        ,&CfgIn->PartiGuid, &(CfgBckup.PartiGuid));

           RecoveryStatus = boot_recovery_add_good_and_corrupted_partition_id
                              ((UINT8 *)(&(CfgBckup.PartiGuid )), /*Original Bad partition */
                              (UINT8 *) &CfgIn->PartiGuid );      /*Backup, Good partition*/
           if (RecoveryStatus != BOOT_RECOVERY_ERROR_NONE )
           {
             PIL_WARN_CFG(CfgIn, "Good & Corrupted partition update to SMEM failed\n");
             PStatus = PIL_GENERIC_ERR;
           }
        }
        else
        {
          PIL_ERROR_CFG(CfgIn, "Backup partition Image load Failed PStatus: %x \n", PStatus);
        }
      }
    }
   
    if(AsciiStriCmp((CHAR8*) CfgIn->PostImage, "") != 0)
    {
      PIL_WARN_CFG(CfgIn, "PostImage: %s\n", CfgIn->PostImage);
      NewCfg = PilInitCfgByUnicodeName(CfgIn->PostImage);
      if(NewCfg == NULL)
      {
        PIL_ERROR_CFG(CfgIn, "PostImage %s not found\n", CfgIn->PostImage);
        return PIL_INVALID_CFG;
      }	
      
      ImageStatus = PilProcessImageExt(NewCfg);

      //Pil status greater than 0 are Error codes
      if(ImageStatus)
      {
        PIL_ERROR_CFG(NewCfg, "PIL status: %d\n\n", ImageStatus);
        return ImageStatus;
      }
    }
        
    return PStatus;
}


/**
  load and boot image by giving the subsys name

  @param[in] Subsys            name of subsys to process/load

  @retval PIL_SUCCESS       success
  @retval other             failurel

**/
PIL_STATUS PilProcessImage(CHAR16* Subsys)
{
    PIL_STATUS  PStatus;
    PIL_SUBSYS_CFG_TYPE* Cfg;
    LockHandle* PilLock = NULL;
    
    if (!Subsys)
        return PIL_INVALID_PARAM;
    
    InitLock ("PIL_Lock", &PilLock);

    AcquireLock (PilLock);
    
    Cfg = PilInitCfgByUnicodeName(Subsys);
    if (Cfg == NULL) {
        PIL_WARN("No configuration found for %s\n", Subsys);
        PStatus = PIL_SUBSYS_NOT_SUPPORTED;
    }
    else
      PStatus = PilProcessImageExt(Cfg);
        
    ReleaseLock (PilLock);
    return PStatus;
}

/**
  shutdown the subsystem, keep the subsystem ctx in list

  @param[in] SubsysId       subsystem ID to be shutdown

  @retval PIL_SUCCESS       success
  @retval other             failurel

**/
PIL_STATUS PilShutdownImage(UINT32 SubsysId)
{
    PIL_SUBSYS_CTX_TYPE *Ctx=NULL;
    PIL_SUBSYS_PRIV_TYPE* Priv;
    const PIL_METHODS_TYPE*  PilMethod;
    PIL_SUBSYS_CFG_TYPE* Cfg;
    PIL_SUBSYS_CFG_TYPE* NewCfg;
    LockHandle* PilLock = NULL;
    PIL_STATUS  PStatus;
    
    InitRecursiveLock ("PIL_Lock", &PilLock);

    AcquireLock (PilLock);
    
    /* assume the subsys ctx is already initialized, 
    so just search in subsys ctx list */
    PStatus = GetLoadedSubsysCfgById(SubsysId, &Cfg);
    ASSERT(PStatus==PIL_SUCCESS);
    
    switch(Cfg->Type)
    {
        case ELF_SINGLE:
            PilMethod = &PilSingleElf;
            break;
        case ELF_SPLIT:
            PilMethod = &PilSplitElf;
            break;
        default:
            PIL_ERROR_CFG(Cfg, "%r is not supported\n", Cfg->Type);
            return PIL_SUBSYS_NOT_SUPPORTED;
    }
    
    PStatus = PilInitSubsys(Cfg, &Ctx);
    if (PStatus != PIL_SUBSYS_RUNNING||Ctx==NULL)
    {
        PIL_ERROR_CFG(Cfg, "Not in running state\n");
        return PIL_SUBSYS_NOT_SUPPORTED;
    }

    if (PilMethod->Shutdown)
    {
      //The Post Image loaded should be shutdown before
      //shutting down the intended image
	  if(AsciiStriCmp((CHAR8*) Cfg->PostImage, "") != 0)
      {
        PIL_WARN_CFG(Cfg, "PostImage to Shutdown: %s\n", Cfg->PostImage);
        NewCfg = PilInitCfgByUnicodeName(Cfg->PostImage);
        if(NewCfg == NULL)
        {
          PIL_ERROR_CFG(Cfg, "PostImage: %s to shutdown not found\n", Cfg->PostImage);
          return PIL_INVALID_CFG;
        }	
        PStatus = PilShutdownImage(NewCfg->SubsysID);
        if(PStatus != EFI_SUCCESS)
          return PStatus;
        }
        
        PStatus = PilMethod->Shutdown(Ctx);
        if (PStatus == PIL_SUCCESS)    {
            /* update status */
            ASSERT(Ctx->Priv != NULL);
            Priv = Ctx->Priv;
            Priv->ProcStatus = PIL_PROC_DOWN;
            PIL_WARN_CFG(Cfg, "shutdown completed\n");
            /*The Pre image loaded should be shutdown after
            shutting down the intended image*/
            if(AsciiStriCmp((CHAR8*) Cfg->PreImage, "") != 0)
            {
              PIL_WARN_CFG(Cfg, "PreImage to Shutdown: %s\n", Cfg->PreImage);
              NewCfg = PilInitCfgByUnicodeName(Cfg->PreImage);
              if(NewCfg == NULL)
              {
                PIL_ERROR_CFG(Cfg, "PreImage: %s to shutdown not found\n", Cfg->PreImage);
                return PIL_INVALID_CFG;
              }

              PStatus = PilShutdownImage(NewCfg->SubsysID);
            }
        }
        else {
            PIL_ERROR_CFG(Cfg, "Failed to shutdown\n");
        }
    }
    else {
        PIL_ERROR_CFG(Cfg, "shutdown is not supported\n");
        PStatus = PIL_SUBSYS_NOT_SUPPORTED;
    }
    
    ReleaseLock (PilLock);
    return PStatus;
}

PIL_STATUS PilLoadAndAuthELFFVImagefromBuffer(VOID *Buffer, VOID** FvImageBase)
{
   PIL_SUBSYS_CFG_TYPE *Cfg;
   PIL_SUBSYS_CTX_TYPE *Ctx;
   PIL_STATUS  PStatus;
   const PIL_METHODS_TYPE*  PilMethod;
   PIL_SUBSYS_PRIV_TYPE* Priv;

   Ctx = AllocateZeroPool(sizeof(PIL_SUBSYS_CTX_TYPE));
   if (Ctx == NULL)
      return PIL_OUT_OF_MEMORY;

   Cfg = AllocateZeroPool(sizeof(PIL_SUBSYS_CFG_TYPE));
   if (Cfg == NULL)
      return PIL_OUT_OF_MEMORY;

       // allocate buffer for private data
   Priv = AllocateZeroPool(sizeof(PIL_SUBSYS_PRIV_TYPE));
   if (Priv == NULL)
      return PIL_OUT_OF_MEMORY;


   Ctx->Cfg = Cfg;
   Ctx->Priv = Priv;
   Cfg->Type = ELF_FV;
   Cfg->SubsysID = 20;
   Priv->ElfLoadInfo.ElfBase = Buffer;
   PilMethod = &PilFv;

   PStatus = PilMethod->LoadMetaData(Ctx);
   if (PStatus != PIL_SUCCESS)
   {
      PIL_ERROR_CFG(Cfg, "Failed to load metadata\n");
      goto LoadErr;
    }

    // validate metadata including ELF and prgram headers, and hash segment
   PStatus = PilMethod->ValidateMetaData(Ctx);
   if (PStatus != PIL_SUCCESS)
   {
     PIL_ERROR_CFG(Cfg, "Failed to validate metadata\n");
     goto LoadErr;
   }

    // setup memory range and notify hyp&tz PIL service
    if (PilMethod->SetupMemoryRange)
    {
        PStatus = PilMethod->SetupMemoryRange(Ctx);
        if (PStatus != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to setup memory range\n");
            goto LoadErr;
        }
    }
    else {
        PIL_ERROR_CFG(Cfg, "SetupMemoryRange cannot be NULL\n");
        PStatus = PIL_GENERIC_ERR;
        goto LoadErr;
    }

    // load segments, not required for FV image
    if (PilMethod->LoadSegments)
    {
        PStatus = PilMethod->LoadSegments(Ctx);
        if (PStatus != PIL_SUCCESS) {
            PIL_ERROR_CFG(Cfg, "Failed to load segments\n");
            goto LoadErr;
        }
    }

   /* Not sure if we need this */
   PStatus = PilMethod->AuthAndReset(Ctx);
   if (PStatus != PIL_SUCCESS)
   {
      PIL_ERROR_CFG(Cfg, "Failed to bring proc out of reset\n");
      goto LoadErr;
    }

   *FvImageBase = (VOID *)Priv->RegionStart;

    return PIL_SUCCESS;
LoadErr:
    return PStatus;
}

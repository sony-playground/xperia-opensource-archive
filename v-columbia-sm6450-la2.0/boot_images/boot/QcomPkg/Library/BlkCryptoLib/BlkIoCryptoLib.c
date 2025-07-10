/**
 * @file    BlkIoCryptoLib.c
 * @brief   Inline Cryptographic Interface Library
 *
 *  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
 */

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h> 
#include <Protocol/EFIHWIO.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/BlockIoCrypto.h>
#include <HALhwio.h>

#include "BlkIoCryptoLib.h"
#include "BlkIoCryptoHWIO.h"
#include <Protocol/EFIScm.h>
#include <Include/scm_sip_interface.h>
#include <Protocol/EFIShmBridge.h>

BOOLEAN ICE_SETUP_DONE = FALSE;
#define ICE_CORE_CURRENT_MAJOR_VERSION 0x03
#define ICE_MAX_BIST_CHECK_COUNT 100
#define ICE_CIPHER_MODE_XTS_256 3
#define UFS_CE 10

EFI_GUID gEfiBlockIoCryptoAlgoAesXtsGuid = EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_XTS;

static INT64 ICECheckVersion(void)
{
    UINT32 Major, Minor, Step;

    Major = HWIO_UFS_MEM_ICE_VERSION_INM(HWIO_UFS_MEM_ICE_VERSION_MAJOR_VERSION_BMSK) >>
            HWIO_UFS_MEM_ICE_VERSION_MAJOR_VERSION_SHFT;
    Minor = HWIO_UFS_MEM_ICE_VERSION_INM(HWIO_UFS_MEM_ICE_VERSION_MINOR_VERSION_BMSK) >>
            HWIO_UFS_MEM_ICE_VERSION_MINOR_VERSION_SHFT;
    Step = HWIO_UFS_MEM_ICE_VERSION_INM(HWIO_UFS_MEM_ICE_VERSION_STEP_VERSION_BMSK) >>
            HWIO_UFS_MEM_ICE_VERSION_STEP_VERSION_SHFT;
    
    if (Major < ICE_CORE_CURRENT_MAJOR_VERSION) {
        DEBUG ((EFI_D_ERROR, "Unknown ICE device at %lu, rev %d.%d.%d",
                UFS_MEM_ICE_REGS_REG_BASE, Major, Minor, Step));
        return -1;
    }

    return 0;
    
}

static VOID ICELowPowerOptimizationEnable(void)
{
    UINT32 Regval;

    Regval = HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_IN;
    Regval |= 0x7000;
    /* Optimization enable sequence */
    Regval |= 0xD807100;

    HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_OUT(Regval);
}

static INT64 ICEWaitBistStatus(void)
{
    INT64 Count;
    INT64 Loop;

    for (Count = 0; Count < ICE_MAX_BIST_CHECK_COUNT; Count++) {
        if (!(HWIO_UFS_MEM_ICE_BIST_STATUS_IN & HWIO_UFS_MEM_ICE_BIST_STATUS_RMSK))
            break;
        for (Loop = 0; Loop < 50; Loop++);
        //Delay(50);
    }

    if (HWIO_UFS_MEM_ICE_BIST_STATUS_IN) {
        DEBUG ((EFI_D_ERROR, "Wait bist status failed, reg 0x%x\n",
                HWIO_UFS_MEM_ICE_BIST_STATUS_IN));
        return -1;
    }

    return 0;
}

static EFI_STATUS ICEInit (void)
{
    if (0 != ICECheckVersion()) {
        return EFI_DEVICE_ERROR;
    }

    ICELowPowerOptimizationEnable();
    if (0 != ICEWaitBistStatus()) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

static BOOLEAN IsPowerOf2 (unsigned long N)
{
    return (N != 0 && ((N & (N - 1)) == 0));
}

static UINT8 GetDataUnitSizeMask (UINT64 DataUnitSize)
{
    if (DataUnitSize < 512 || DataUnitSize > 65536 ||
        !IsPowerOf2(DataUnitSize))
	    return 0;

	return DataUnitSize / 512;
}

static UINT8 GetCryptoCapId (EFI_GUID Algorithm)
{
	if (!CompareMem(&Algorithm, &gEfiBlockIoCryptoAlgoAesXtsGuid, sizeof(EFI_GUID)))
        return 0x03;

    return -1;
}

static EFI_STATUS ICEProgramKey (IN UINT64 Index,
    IN VOID  *CryptoKey, IN UINT64 KeySize,
	IN UINT8 DuSize, IN UINT8 CapId)
{
    EFI_STATUS                     Status = EFI_SUCCESS;  
    QCOM_SCM_PROTOCOL             *pQcomScmProtocol = NULL;
    EFI_SHMBRIDGE_PROTOCOL        *pShmBridgeProtocol = NULL;
    UINT64                         Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64                         Results[SCM_MAX_NUM_RESULTS] = {0};
    VOID                           *ShmBuf = NULL;
    VOID                           *KeyBuf = NULL;

    // Locate QCOM_SCM_PROTOCOL. 
    Status = gBS->LocateProtocol ( &gQcomScmProtocolGuid, 
                                 NULL, 
                                 (VOID **)&pQcomScmProtocol
                               );
    if( EFI_ERROR(Status)) 
    {
        DEBUG(( EFI_D_INFO, " Locate SCM Protocol failed, Status =  (0x%p)\r\n", Status));
        return Status;
    }

    // Locate SHM BRIDGE PROTOCOL. 
    Status = gBS->LocateProtocol ( &gEfiShmBridgeProtocolGuid, 
                                 NULL, 
                                 (VOID **)&pShmBridgeProtocol
                               );
    if( EFI_ERROR(Status)) 
    {
        DEBUG(( EFI_D_INFO, " Locate SHM Bridge Protocol failed, Status =  (0x%p)\r\n", Status));
        return Status;
    }

    ShmBuf = pShmBridgeProtocol->ShmBridgeAllocate(pShmBridgeProtocol, &KeySize, ShmBridgeBootSvcData);
    if (ShmBuf == NULL)
    {
        Status =  EFI_OUT_OF_RESOURCES;
        DEBUG ((EFI_D_ERROR, "Failed to allocate memory:(size=%d) from SHMBridge\n", KeySize));
        return Status;
    }

    KeyBuf = ShmBuf;
    CopyMem (KeyBuf, CryptoKey, KeySize);

    Parameters[0] = Index;
    Parameters[1] = (UINTN)KeyBuf;
    Parameters[2] = KeySize;
    Parameters[3] = ICE_CIPHER_MODE_XTS_256;
    Parameters[4] = DuSize;
    Parameters[5] = UFS_CE;

    /* Make a SCM Sys call */
    Status = pQcomScmProtocol->ScmSipSysCall (pQcomScmProtocol,
                                            TZ_ES_SET_CONFIG_ICE_KEY_CE_TYPE_ID,
                                            TZ_ES_SET_CONFIG_ICE_KEY_CE_TYPE_PARAM_ID,
                                            Parameters,
                                            Results
                                            );
    if (EFI_ERROR (Status)) 
    {
        DEBUG(( EFI_D_ERROR, "ScmSipSysCall() failed, Status = (0x%x)\r\n", Status));
    }

    if (ShmBuf != NULL)
    {
        pShmBridgeProtocol->ShmBridgeFree(pShmBridgeProtocol, ShmBuf);
        ShmBuf = NULL;
    }

    return Status;
}

EFI_STATUS EFIAPI SetICEConfiguration (			
    IN CHAR8                                              *Id,
    IN UINT64                                             ConfigurationCount, 
    IN EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY      *ConfigurationTable, 
    OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY  *ResultingTable)
{
    EFI_STATUS EfiStatus = EFI_UNSUPPORTED;
    UINT8 DataUnitMask = 0;
    UINT8 CryptoAlgId = 0;
    if (!ICE_SETUP_DONE) {
        EfiStatus = ICEInit();
        if (EfiStatus) {
            DEBUG ((EFI_D_ERROR, "Failed to initialize ICE 0x%08x\n", EfiStatus));
            return EfiStatus;
        }

        ICE_SETUP_DONE = TRUE;
    }
    
    DataUnitMask = GetDataUnitSizeMask(ConfigurationTable->Capability.CryptoBlockSizeBitMask);
    CryptoAlgId = GetCryptoCapId(ConfigurationTable->Capability.Algorithm);

    if (CryptoAlgId == -1) {
        DEBUG ((EFI_D_ERROR, "Incorrect Algorithm GUID\n"));
        return EFI_INVALID_PARAMETER;
    }

    EfiStatus = ICEProgramKey(ConfigurationTable->Index,
                               ConfigurationTable->CryptoKey,
                               ConfigurationTable->Capability.KeySize,
                               DataUnitMask,
                               CryptoAlgId);
    if (EfiStatus) {
        DEBUG ((EFI_D_ERROR, "Error programming key to slot %d, error 0x%08x\n",
                ConfigurationTable->Index, EfiStatus));
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}
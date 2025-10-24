/**
* @file     UFS.c
* @brief   Universal Flash Storage (UFS) Dxe Driver
*
*  Copyright (c) 2013 - 2022 Qualcomm Technologies, Inc. All rights reserved.
*/


/*=============================================================================
                              EDIT HISTORY


when            who   what, where, why
----------      ---   ----------------------------------------------------------- 
2022/10/18      pz    Register for UEFI exit callback to trigger UFS Device Power_down
2022-07-06      jt    Start BlockIo2 requests in timer callback
2022-07-01      ak    Updated ACPI support changes
2022-06-10      jt    Implement UFSFlushBlocksEx
2022-05-20      sa    Added BlockIo2 for multiple doorbells.
2022-05-10      sa    Added SharedIce Protocol. 
2022-05-02      jt    Correct RPMB partition size
2022-04-06      pz    Report RPMB partition region 0 size
2022-04-01      pz    Add SSU configuration API
2022-04-01      jt    Add check before conversion of unicode to ASCII 
2022-03-21      cm    Add API to return turbo mode support info
2022-02-18      ssb   Initialized structures info and ufs_info
2021-10-25      jt    Add sync cache support 
2021-04-28      jt    Add ICE support 
2020-12-23      vm    Release lock before setting PurgeTimer to avoid deadlock 
2020-06-28      am    Register for sleep callback with SystemSleepLib instead of PSleepLib 
2020-06-02      jt    Use bBootLunEn to get the boot LUN
2020-03-31      jt    Add power management functions
2019-07-22      jt    Move SMMU configuration to BSP 
2018-08-16      wek   Map the UFS controller register space on Init.
2018-08-16      jt    Register for Sleep callback to trigger UFS LPM  
2018-06-26      jt    Allow UFS SMMU config even for other boot devices
2018-06-21      jt    Support IOC enablement
2018-06-04      jt    Turn off clocks if UFS is not the boot device
2018-05-29      jt    Use recursive lock
2018-04-24      jt    Changes to RegisterListener
2018-02-16      jt    Add HAL IOMMU configuration
2017-02-01      jt    Use wrapper functions for BlkIo
2016-11-30      jt    Return all entries in UFSGetLUWriteProtectInfo
2016-09-21      jt    Secure write protect changes
2016-09-20      jt    Correct serial number length
2016-06-28      jt    Add get/set boot LUN APIs
2016-01-26      jt    Card info changes
2016-01-21      rh    Adding BlockIO2
2015-10-19      jt    Pass MediaId as argument for GPTListenerInit
2015-05-13      jb    Change device path type name to not conflict with standard one
2015-04-03      rm    Add check for boot device
2015-03-26      rm    Add RPMB protocols
10-09-2014      rh    Adding RPMB APIs
09-23-2014      rh    Use unique GUID for LUs, different from eMMC
05-05-2013      ai    Initial version

=============================================================================*/

#include <Uefi.h>
#include <Guid/EventGroup.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/ArmLib.h>
#include <Library/SerialPortShLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/StorSecApp.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/BlockIo2.h>
#include <Protocol/BlockIoCrypto.h>
#include <Protocol/DevicePath.h>
#include <Protocol/EFICardInfo.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFIHWIO.h>
#include <Protocol/EFIStorageDeviceMgmt.h>

#include <Library/GPTListener.h>
#include <Library/RpmbListener.h>
#include <Library/RpmbLib.h>
#include <Protocol/EFIRpmb.h>
#include <Protocol/EFIEraseBlock.h>
#include <Protocol/EFIStorageWriteProtect.h>
#include <Protocol/EFIHALIOMMUProtocol.h>
#include <Protocol/EFIAcpiPlatform.h>

#include "UfsBlockIO2.h"
#include "UFS.h"
#include "Library/KernelLib.h"
#include <api/storage/ufs_api.h>

#include <BootConfig.h>
#include <Library/HobLib.h>
#include "BlkIoCryptoLib.h"

#define UFS_TPL TPL_CALLBACK

/* RPMB transfer limit */
#define RPMB_MAX_BLOCK_TRANSFER_SIZE 0xffff

LockHandle* UfsLockPtr;


/* UFS Device Path */
typedef struct {
   VENDOR_DEVICE_PATH  Ufs;
   EFI_DEVICE_PATH     End;
} QCUFS_DEVICE_PATH;

static QCUFS_DEVICE_PATH gUfsDevicePath [UFS_UEFI_MAX_LUN_ACCESS];

static VENDOR_DEVICE_PATH UfsPath =
{
   HARDWARE_DEVICE_PATH,
   HW_VENDOR_DP,
   (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
   (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
   0
};

static EFI_DEVICE_PATH UfsEndPath =
{
   END_DEVICE_PATH_TYPE,
   END_ENTIRE_DEVICE_PATH_SUBTYPE,
   sizeof (EFI_DEVICE_PATH_PROTOCOL),
   0
};

#define _UFS_DEV_PROTOTYPE    { UFS_DEV_SIGNATURE, NULL, NULL, 0, 0, 0, 0, 0, 0, 0 }

static UFS_DEV gUfsDevice[UFS_UEFI_MAX_LUN_ACCESS] = {
   _UFS_DEV_PROTOTYPE,
   _UFS_DEV_PROTOTYPE,
   _UFS_DEV_PROTOTYPE,
   _UFS_DEV_PROTOTYPE,
   _UFS_DEV_PROTOTYPE,
   _UFS_DEV_PROTOTYPE,
   _UFS_DEV_PROTOTYPE,
   _UFS_DEV_PROTOTYPE
};

/* UFS Block IO's Media */
static EFI_BLOCK_IO_MEDIA UFSMedia = {
   SIGNATURE_32('u','f','s',' '),            /* MediaId */
   FALSE,                                    /* RemovableMedia */
   FALSE,                                    /* MediaPresent */
   FALSE,                                    /* LogicalPartition */
   FALSE,                                    /* ReadOnly */
   FALSE,                                    /* WriteCaching */
   4096,                                     /* BlockSize */
   4,                                        /* IoAlign */
   0,                                        /* LastBlock */
   0,                                        /* LowestAlignedLba */
   0,                                        /* LogicalBlocksPerPhysicalBlock */
   0                                         /* OptimalTransferLengthGranularity */
};

static EFI_BLOCK_IO_MEDIA gMediaUfs[UFS_UEFI_MAX_LUN_ACCESS];

/* UFS Block IO Protocol */
EFI_BLOCK_IO_PROTOCOL gBlockIoUfs = {
   EFI_BLOCK_IO_PROTOCOL_REVISION3,          /* Revision */
   0,                                        /* Media */
   UFSReset,                                 /* Reset */
   UFSReadBlocksWrapper,                     /* ReadBlocks */
   UFSWriteBlocksWrapper,                    /* WriteBlocks */
   UFSFlushBlocks                            /* FlushBlocks */
};

/* UFS Block IO2 Protocol */
EFI_BLOCK_IO2_PROTOCOL gBlockIo2Ufs = {
   0,                                        /* Media */
   UFSResetEx,                               /* Reset */
   UFSReadBlocksEx,                          /* ReadBlocksEx */
   UFSWriteBlocksEx,                         /* WriteBlocksEx */
   UFSFlushBlocksEx                          /* FlushBlocksEx */
};

/* UFS Block IO Crypto Protocol */
EFI_BLOCK_IO_CRYPTO_PROTOCOL gBlockIoCryptoUfs = {
   0,                         /* Media */
   UFSCryptoReset,            /* Reset */
   UFSCryptoGetCapabilities,  /* GetCapabilities */     
   UFSCryptoSetConfiguration, /* SetConfiguration */
   UFSCryptoGetConfiguration, /* GetConfiguration */
   UFSCryptoReadEx,           /* ReadExtended */
   UFSCryptoWriteEx,          /* WriteExtended */ 		   
   UFSCryptoFlushBlocks	      /* Flushblocks */ 
};	

/* Device Paths for all the UFS LUNs */
static EFI_GUID UfsDevicePathGuids[UFS_UEFI_MAX_LUN_ACCESS] = {
   EFI_UFS_LUN_0_GUID,
   EFI_UFS_LUN_1_GUID,
   EFI_UFS_LUN_2_GUID,
   EFI_UFS_LUN_3_GUID,
   EFI_UFS_LUN_4_GUID,
   EFI_UFS_LUN_5_GUID,
   EFI_UFS_LUN_6_GUID,
   EFI_UFS_LUN_7_GUID
};

/* RPMB Protocol */
static const EFI_SDCC_RPMB_PROTOCOL gUfsRpmbProtocol = {
   EFI_RPMB_PROTOCOL_REVISION,               /* Revision */
   0,                                        /* Reliable Write Count */
   0,                                        /* RPMB Partition Size */
   RPMBReadCounterPkt,                       /* Read Counter*/
   RPMBProgProvisionKey,                     /* Program Provision Key */
   RPMBReadBlocks,                           /* Read Sectors */
   RPMBWriteBlocks,                          /* Write Sectors */
   0                                         /* Max RMPB Read/Write Transfer Size */
};

/* UFS Card Info Protocol */
static EFI_MEM_CARDINFO_PROTOCOL gUfsCardInfoProtocol = {
   EFI_MEM_CARD_INFO_PROTOCOL_REVISION,      /* Revision */
   UFSGetCardInfo,                           /* GetCardInfo */
   UFSGetActiveBootLU,                       /* GetBootLU */
   UFSSetActiveBootLU                        /* SetBootLU */
#ifdef FEATURE_XBOOT
  ,UfsGetDeviceDescriptor,                   /* GetDeviceDescriptor */
   UfsGetUnitDescriptor                      /* GetUnitDescriptor */
#endif /* FEATURE_XBOOT */
};

/* Storage Write Protect Protocol */
static EFI_STORAGE_WP_PROTOCOL gUfsWriteProtectProtocol = {
   EFI_STORAGE_WP_PROTOCOL_REVISION,      /* Revision */
   UFSGetSupportedLbaWriteProtectTypes,   /* GetSupportedLbaWriteProtectTypes */
   UFSSetLUWriteProtect,                  /* SetLUWriteProtect */
   UFSSetLbaWriteProtect,                 /* SetLbaWriteProtect */
   UFSClearWriteProtect,                  /* ClearWriteProtect */
   UFSGetLUWriteProtectInfo               /* GetLUWriteProtectInfo */
};

/* Erase Blocks Protocol */
static const EFI_ERASE_BLOCK_PROTOCOL gUfsEraseBlkProtocol = {
   EFI_ERASE_BLOCK_PROTOCOL_REVISION,        /* Revision */
   4096,                                     /* Erase Granularity */
   UFSEraseBlocks                            /* Erase Blocks */
#ifdef FEATURE_XBOOT
   ,UfsNonSecureEraseBlocks                  /* Normal Erase Blocks */
   ,UfsPurgeBlocks                           /* Purge Blocks */
#endif /* FEATURE_XBOOT */
};

/* Storage device management protocol */
static const EFI_STORAGE_DEV_MGMT_PROTOCOL gUfsDeviceMgmtProtocol = {
   EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION4,   /* Revision */
   UFSFillDeviceInfo,                        /* GetDeviceInfo */
   UFSGetErrorStats,                         /* GetErrorStats */
   {                                         /* PowerMgmt */
      UFSGetOpModeCaps,                      /* GetOpModeCaps */
      UFSGetCurrentOpMode,                   /* GetCurrentOpMode */
      UFSSetGear,                            /* SetSpeedLevel */
      UFSSetVoltageCorner,                   /* SetVoltageCorner */
      UFSSetOperationalMode,                 /* SetOperationalMode */
      UFSConfigLinkParams,                   /* ConfigLink */
      UFSSetLinkState,                       /* SetLinkState */
      UFSSetDeviceMode                       /* SetDeviceMode */
   },
   {                                         /* HwConfig */
      UFSGetLevelShifterInfo,                /* GetLevelShifterInfo */ 
      UFSGetTurboModeInfo,		             /* GetTurboModeInfo */
      {
        UFSGetSharedIceAlgo,                 /* Get Shared Ice Info */   
        UFSSetSharedIceAlgo                  /* Set Shared Ice Info */   
      }
   }
};

static UFS_DEV gUfsRpmbDevice = _UFS_DEV_PROTOTYPE;
static UFS_DEV gUfsWlunDevice = _UFS_DEV_PROTOTYPE; 

static QCUFS_DEVICE_PATH gUfsWlunDevicePath;
static QCUFS_DEVICE_PATH gUfsRpmbDevicePath;

/* SCM registration event */
static EFI_EVENT ScmInitialized = NULL;
static VOID *ScmInitializedToken = NULL;
extern EFI_GUID gQcomScmProtocolGuid;

extern EFI_GUID gEfiHalIommuProtocolGuid;
HAL_IOMMU_fptable_t *fp_table = NULL;

/* Exit boot services event */
static EFI_EVENT ExitBootServicesEvent = NULL;
static EFI_QCOM_ACPIPLATFORM_PROTOCOL *AcpiPlatProtocol = NULL;
static EFI_EVENT Ufs40Init = NULL;
static VOID *Ufs40InitToken = NULL;

#define REVERSE_WORD(x) ((x & 0xff) << 8) | ((x >> 8) & 0xff)

/** Connection to blockIO2 **/
EFI_EVENT         gUfsBlkIo2TimerEvent;
BLKIO2_REQ_LIST   gUfsReqList;
DRIVER_INFO       gUfsTransferInfo;
EFI_EVENT         gUfsPurgeTimerEvent;
EFI_BLOCK_IO_PROTOCOL *gUfsCurrentErase;

VOID PurgeTimerEventNotify (
            IN  EFI_EVENT  Event,
            IN  VOID      *Context);

EFI_STATUS UFSIoWrapper (
            IN VOID                     *pThis,
            IN UINT32                    MediaId,
            IN UINT32                    TransferType,
            IN EFI_LBA                   Lba,
            IN OUT VOID                 *Token,
            IN UINT64                   BufferSize,
            IN OUT VOID                 *Buffer, 
            IN UINT64                   *CryptoIndex, 
            IN VOID                     *CryptoIvInput);

/**
   Reset the Block Device.
**/
EFI_STATUS EFIAPI UFSReset (
            IN EFI_BLOCK_IO_PROTOCOL   *This,
            IN BOOLEAN                 ExtendedVerification)
{
   return EFI_SUCCESS;
}

/**
   Return supported write protect types
**/
EFI_STATUS EFIAPI UFSGetSupportedLbaWriteProtectTypes(
   IN EFI_STORAGE_WP_PROTOCOL *This,
   OUT UINT32 *LbaWpTypes
)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_info_type info = {0};
   if ((NULL == This) || (NULL == LbaWpTypes))
   {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_WRITE_PROTECT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   *LbaWpTypes = WP_NOT_PROTECTED;

   AcquireLock (UfsLockPtr);
   /* Get device info to determine bLUWriteProtect value */
   rc = ufs_get_device_info (hUFS, &info);
   ReleaseLock (UfsLockPtr);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "GetSupportedLbaWriteProtectTypes: Get device "
                           "info failed, status 0x%x\n", rc));
      return EFI_DEVICE_ERROR;
   }

   /* Set options based on bLUWriteProtect */
   if (2 == info.bLUWriteProtect)
   {
      *LbaWpTypes |= WP_PERMANENT;
   }
   else if (1 == info.bLUWriteProtect)
   {
      *LbaWpTypes |= WP_POWERON;
   }
   else if (0 == info.bLUWriteProtect)
   {
      *LbaWpTypes |= (WP_SECURE_NV | WP_SECURE_P | WP_SECURE_P_EN);
   }
   else
   {
      DEBUG ((EFI_D_ERROR, "GetSupportedLbaWriteProtectTypes: Invalid value "
                           "for bLUWriteProtect\n"));
      return EFI_INVALID_PARAMETER;
   }

   return EFI_SUCCESS;
}

/**
   Set write protection for the entire LU
**/
EFI_STATUS EFIAPI UFSSetLUWriteProtect(
   IN EFI_STORAGE_WP_PROTOCOL *This
)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   /* Validate passed-in pointers are not NULL */
   if (NULL == This)
   {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_WRITE_PROTECT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* Set fPowerOnWPEn field in the flags */
   AcquireLock (UfsLockPtr);
   rc = ufs_set_pon_write_protect(hUFS);
   ReleaseLock (UfsLockPtr);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "ufs_set_pon_write_protect with return value of %d\n", rc));
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}

/**
   Get write protection information for the LU specified
**/
EFI_STATUS EFIAPI UFSGetLUWriteProtectInfoInternal(
   IN EFI_STORAGE_WP_PROTOCOL *This,
   OUT EFI_WP_CONFIG *ProtectInfo
)
{
   EFI_STATUS Status;
   INT32 rc;
   SdMgrSecureWpInfo WpInfo;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_info_type info = {0};
   UINT8 i = 0, index = 0;

   if ((NULL == This) || (NULL == ProtectInfo))
   {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_WRITE_PROTECT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* Get device info to determine bLUWriteProtect value */
   rc = ufs_get_device_info (hUFS, &info);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "GetLbaWriteProtectType: Get device info failed, status 0x%x\n", rc));
      return EFI_DEVICE_ERROR;
   }

   /* If fPermanentWPEn = 1, then permanent write protection will be enabled for
      those LUNs where bLUWriteProtect = 2, regardless of LBA */
   if (2 == info.bLUWriteProtect)
   {
      if (info.fPermanentWPEn)
      {
         ProtectInfo->NumEntries = 1;
         ProtectInfo->WpEntries[0].WpType = WP_PERMANENT;
         ProtectInfo->WpEntries[0].Lba = 0;
         ProtectInfo->WpEntries[0].NumBlocks = info.dLuTotalBlocks;
         return EFI_SUCCESS;
      }
   }
   /* If fPowerOnWPEn = 1, then power on write protection will be enabled for
      those LUNs where bLUWriteProtect = 1, regardless of LBA */
   else if (1 == info.bLUWriteProtect)
   {
      if (info.fPowerOnWPEn)
      {
         ProtectInfo->NumEntries = 1;
         ProtectInfo->WpEntries[0].WpType = WP_POWERON;
         ProtectInfo->WpEntries[0].Lba = 0;
         ProtectInfo->WpEntries[0].NumBlocks = info.dLuTotalBlocks;
         return EFI_SUCCESS;
      }
   }
   /* If bLUWriteProtect = 0, then check to see if the LBA is part of a secure
      write protect configuration block */
   else if (0 == info.bLUWriteProtect)
   {
      for (i = 0; i < UFS_UEFI_MAX_LUN_ACCESS; i++)
      {
         if (UfsDevice == &gUfsDevice[i])
         {
            WpInfo.LunNumber = i;
         }
      }

      ProtectInfo->NumEntries = 0;

      /* Get Secure Write Protect Configuration Block */
      Status = UFSGetSecureWpConfigBlock(&WpInfo);
      if (EFI_SUCCESS != Status)
      {
         DEBUG ((EFI_D_ERROR, "GetLbaWriteProtect: UFSGetSecureWpConfigBlockt failed "
                              "with return value of 0x%x\n", Status));
         return Status;
      }

      for (i = 0; i < WpInfo.NumEntries; i++)
      {
         ProtectInfo->NumEntries++;
         ProtectInfo->WpEntries[index].Lba = WpInfo.WpEntries[i].Addr;
         ProtectInfo->WpEntries[index].NumBlocks = WpInfo.WpEntries[i].NumBlocks;

         /* NV-type when WPT = 0 */
         if (0 == WpInfo.WpEntries[i].WpTypeMask)
         {
            ProtectInfo->WpEntries[index].WpType = WP_SECURE_NV;
         }
         /* P-type when WPT = 1 */
         else if (1 == WpInfo.WpEntries[i].WpTypeMask)
         {
            ProtectInfo->WpEntries[index].WpType = WP_SECURE_P;
         }
         /* NV-AWP-type when WPT = 2 */
         else if (2 == WpInfo.WpEntries[i].WpTypeMask)
         {
            ProtectInfo->WpEntries[index].WpType = WP_SECURE_P_EN;
         }

         index++;
      }
   }
   else
   {
      DEBUG ((EFI_D_ERROR, "GetLbaWriteProtect: Invalid bLUWriteProtect "
                           "value 0x%x\n", info.bLUWriteProtect));
      return EFI_INVALID_PARAMETER;
   }

   return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UFSGetLUWriteProtectInfo(
   IN EFI_STORAGE_WP_PROTOCOL *This,
   OUT EFI_WP_CONFIG *ProtectInfo
)
{
  EFI_STATUS Status;

  AcquireLock (UfsLockPtr);
  Status = UFSGetLUWriteProtectInfoInternal (This, ProtectInfo);
  ReleaseLock (UfsLockPtr);

  return Status;
}
/**
   Set write protection for the LBA ranges
**/
EFI_STATUS EFIAPI UFSSetLbaWriteProtect(
   IN EFI_STORAGE_WP_PROTOCOL *This,
   IN EFI_WP_CONFIG *WpConfig
)
{
   EFI_STATUS Status;
   INT32 rc;
   SdMgrSecureWpInfo WpInfo;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_info_type info = {0};
   UINT8 i;

   if ((NULL == This) || (NULL == WpConfig))
   {
      return EFI_DEVICE_ERROR;
   }

   UfsDevice = UFS_DEV_FROM_WRITE_PROTECT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* Get device info to determine bLUWriteProtect value */
   AcquireLock (UfsLockPtr);
   rc = ufs_get_device_info (hUFS, &info);
   ReleaseLock (UfsLockPtr);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "SetLbaWriteProtect: Get device info failed, status 0x%x\n", rc));
      return EFI_DEVICE_ERROR;
   }

   if (0 != info.bLUWriteProtect)
   {
      DEBUG ((EFI_D_ERROR, "LBA write protect only allowed for bLUWriteProtect = 0\n", rc));
      return EFI_INVALID_PARAMETER;
   }

   for (i = 0; i < UFS_UEFI_MAX_LUN_ACCESS; i++)
   {
      if (UfsDevice == &gUfsDevice[i])
      {
         WpInfo.LunNumber = i;
      }
   }

   Status = UFSGetSecureWpConfigBlock(&WpInfo);
   if (EFI_SUCCESS != Status)
   {
      DEBUG ((EFI_D_ERROR, "UFSSetLbaWriteProtect: UFSGetSecureWpConfigBlock failed "
                           "with return value of 0x%x\n", Status));
      return Status;
   }

   /* Once the configuration block is updated, we won't have NumEntries = 0.
      If we see that NumEntries = 1 and the first entry disabled, then
      we know that the ClearWriteProtect has happened and so we essentially
      have NumEntries = 0 */
   if ((WpInfo.NumEntries == 1) && (WpInfo.WpEntries[0].WpEnable == 0))
   {
      WpInfo.NumEntries = 0;
   }

   if ((MAX_SECURE_WP_ENTRIES - WpInfo.NumEntries) < WpConfig->NumEntries)
   {
      DEBUG ((EFI_D_ERROR, "Number of configuration entries too large\n"));
      return EFI_INVALID_PARAMETER;
   }

   /* Set up the configuration structure */
   for (i = WpInfo.NumEntries; i < (WpInfo.NumEntries + WpConfig->NumEntries); i++)
   {
      WpInfo.WpEntries[i].WpEnable = 1;

      if (WP_SECURE_NV == WpConfig->WpEntries[i-WpInfo.NumEntries].WpType)
      {
         WpInfo.WpEntries[i].WpTypeMask = 0;
      }
      else if (WP_SECURE_P == WpConfig->WpEntries[i-WpInfo.NumEntries].WpType)
      {
         WpInfo.WpEntries[i].WpTypeMask = 1;
      }
      else if (WP_SECURE_P_EN == WpConfig->WpEntries[i-WpInfo.NumEntries].WpType)
      {
         WpInfo.WpEntries[i].WpTypeMask = 2;
      }
      else
      {
         DEBUG ((EFI_D_ERROR, "UFSSetLbaWriteProtect: Invalid WpType"));
         return EFI_INVALID_PARAMETER;
      }

      WpInfo.WpEntries[i].Addr = WpConfig->WpEntries[i-WpInfo.NumEntries].Lba;
      WpInfo.WpEntries[i].NumBlocks = WpConfig->WpEntries[i-WpInfo.NumEntries].NumBlocks;

   }

   WpInfo.NumEntries += WpConfig->NumEntries;

   /* Send request to secure app */
   Status = UFSSetSecureWpConfigBlock(&WpInfo);
   if (EFI_SUCCESS != Status)
   {
      DEBUG ((EFI_D_ERROR, "UFSSetLbaWriteProtect: UFSSetSecureWpConfigBlock failed "
                           "with return value of 0x%x\n", Status));
      return Status;
   }

   return EFI_SUCCESS;
}

/**
   Clear secure write protection entries for the LU specified
**/
EFI_STATUS EFIAPI UFSClearWriteProtectInternal(
   IN EFI_STORAGE_WP_PROTOCOL *This
)
{
   EFI_STATUS Status;
   INT32 rc;
   SdMgrSecureWpInfo WpInfo;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_info_type info = {0};
   UINT8 i = 0;

   if (NULL == This)
   {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_WRITE_PROTECT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* Get device info to determine bLUWriteProtect value */
   rc = ufs_get_device_info (hUFS, &info);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "ClearWriteProtect: Get device info failed, status 0x%x\n", rc));
      return EFI_DEVICE_ERROR;
   }

   if (0 != info.bLUWriteProtect)
   {
      DEBUG ((EFI_D_ERROR, "Clear write protect only allowed for bLUWriteProtect = 0\n"));
      return EFI_INVALID_PARAMETER;
   }

   for (i = 0; i < UFS_UEFI_MAX_LUN_ACCESS; i++)
   {
      if (UfsDevice == &gUfsDevice[i])
      {
         WpInfo.LunNumber = i;
      }
   }

   /* Get Secure Write Protect Configuration Block */
   Status = UFSGetSecureWpConfigBlock(&WpInfo);
   if (EFI_SUCCESS != Status)
   {
      DEBUG ((EFI_D_ERROR, "ClearWriteProtect: UFSGetSecureWpConfigBlock failed "
                           "with return value of 0x%x\n", Status));
      return Status;
   }

   /* NumEntries > 0, so we clear the entries, but set NumEntries = 1 */
   SetMem(WpInfo.WpEntries, MAX_SECURE_WP_ENTRIES * sizeof(SdMgrSecureWpInfoEntry), 0x00);
   WpInfo.NumEntries = 0x1;

   /* Update the Secure Write Protect Configuration Block */
   Status = UFSSetSecureWpConfigBlock(&WpInfo);
   if (EFI_SUCCESS != Status)
   {
      DEBUG ((EFI_D_ERROR, "ClearWriteProtect: UFSSetSecureWpConfigBlock failed "
                           "with return value of 0x%x\n", Status));
      return Status;
   }

   return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UFSClearWriteProtect(
   IN EFI_STORAGE_WP_PROTOCOL *This
)
{
  EFI_STATUS Status;

  AcquireLock (UfsLockPtr);
  Status = UFSClearWriteProtectInternal (This);
  ReleaseLock (UfsLockPtr);

  return Status;
}

/**
  Gets information about the UFS part
**/
EFI_STATUS EFIAPI UFSFillDeviceInfoInternal (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_DEV_INFO *DevInfo)
{
   CHAR8 StrDescriptor[256] = {0}; // Largest string descriptor has 126 unicode chars + length + IDN 
   EFI_STATUS Status = EFI_SUCCESS; 
   INT32 rc = 0; 
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_info_type Info; 
   UINT32 DescriptorLen = 0, i = 0; 

   if ((NULL == This) || (NULL == DevInfo)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *)UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   /* Get Card Info */
   rc = ufs_get_device_info (hUFS, &Info);
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "ufs_get_device_info failed %x\n", rc));
      return EFI_DEVICE_ERROR;
   }

   /* Get UFS spec version */
   DevInfo->SpecVersion = Info.wSpecVersion; 

   /* Get Vendor Id- 1st 8 bytes in Inquiry Str */
   DevInfo->VendorId = AllocateZeroPool (8 + 1);
   if (NULL == DevInfo->VendorId) {
      return EFI_OUT_OF_RESOURCES;
   }
   CopyMem (DevInfo->VendorId, Info.inquiry_str, 8); 
   DevInfo->VendorId[8] = '\0';

   /* Get Product Id - Next 16 bytes in Inquiry Str */
   DevInfo->ProductId = AllocateZeroPool (16 + 1); 
   if (NULL == DevInfo->ProductId) {
      return EFI_OUT_OF_RESOURCES; 
   }
   CopyMem (DevInfo->ProductId, Info.inquiry_str + 8, 16); 
   DevInfo->ProductId[16] = '\0';

   /* Get Firmware Revision - Last 4 bytes in Inquiry Str */
   DevInfo->FirmwareRevision = AllocateZeroPool(4 + 1);
   if (NULL == DevInfo->FirmwareRevision) {
      return EFI_OUT_OF_RESOURCES;
   }
   CopyMem (DevInfo->FirmwareRevision, Info.inquiry_str + 24, 4);
   DevInfo->FirmwareRevision[4] = '\0';

   /* Get Serial Number string descriptor and convert from Unicode to ASCII */
   rc = ufs_get_device_info_str (hUFS, Info.iSerialNumber, StrDescriptor, 
                                 sizeof(StrDescriptor));  
   if ((UFS_EOK != rc) || (StrDescriptor[1] != 0x05)) {
      DEBUG ((EFI_D_ERROR, "ufs_get_device_info_str Serial Number FAILED. %x\n\n\n", rc));
      return EFI_DEVICE_ERROR;
   }

   DescriptorLen = StrDescriptor[0] - 2;  

   DevInfo->SerialNumber = AllocateZeroPool (DescriptorLen); 
   if (NULL == DevInfo->SerialNumber) {
      return EFI_OUT_OF_RESOURCES; 
   }
   
   /* Check whether string might actually be Ascii by checking the lower 8 bits of
      the first Unicode character (expected to be 0) */
   if ((*((CHAR16 *)(StrDescriptor + 2)) & 0xff) != 0) {
      Status = StrCpyS ((CHAR16 *)DevInfo->SerialNumber, DescriptorLen, (const CHAR16 *)StrDescriptor + 2);
      if (EFI_SUCCESS != Status) {
         DEBUG ((EFI_D_ERROR, "UFSFillDeviceInfo Ascii StrCpy failed %x\n", Status));
         return Status;
      }
   }
   else {
      /* Reverse each unicode character to get correct endianness for UnicodeStrToAsciiStrS */
      for (i = 0; i < 126; i++) {
         *((CHAR16 *)(&StrDescriptor[2] + (2 * i))) = REVERSE_WORD (*((CHAR16 *)(&StrDescriptor[2] + (2 * i))));  
      }

      Status = UnicodeStrToAsciiStrS ((CHAR16 *)(StrDescriptor + 2), DevInfo->SerialNumber, DescriptorLen);  
      if (EFI_SUCCESS != Status) {
         DEBUG((EFI_D_ERROR, "UFSFillDeviceInfo unicode to Ascii conversion failed %x\n", Status));
         return Status; 
      }
   }

   return EFI_SUCCESS; 
}

EFI_STATUS EFIAPI UFSFillDeviceInfo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_DEV_INFO *DevInfo)
{
   EFI_STATUS Status;

   AcquireLock (UfsLockPtr);
   Status = UFSFillDeviceInfoInternal (This, DevInfo);
   ReleaseLock (UfsLockPtr);

   return Status;
}

/**
  Provides the storage error statistics
**/
EFI_STATUS EFIAPI UFSGetErrorStats (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_ERR_STATS *ErrInfo)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_error_stats ErrStats; 

   if ((NULL == This) || (NULL == ErrInfo)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *)UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr);
   rc = ufs_get_error_statistics (hUFS, &ErrStats);  
   ReleaseLock (UfsLockPtr); 
   if (UFS_EOK != rc) 
   {
      DEBUG ((EFI_D_ERROR, "ufs_get_error_statistics failed with return value %d\n", rc)); 
      return EFI_DEVICE_ERROR;
   }

   ErrInfo->UFSErrorStats.TotalFailureCnt = ErrStats.total_error_cnt; 
   CopyMem (&ErrInfo->UFSErrorStats.PAIndErrCnt, &ErrStats.pa_ind_err_cnt, sizeof (ErrInfo->UFSErrorStats.PAIndErrCnt));
   ErrInfo->UFSErrorStats.PATotalErrCnt = ErrStats.pa_total_err_cnt; 
   CopyMem (&ErrInfo->UFSErrorStats.DLIndErrCnt, &ErrStats.dl_ind_err_cnt, sizeof (ErrInfo->UFSErrorStats.DLIndErrCnt));
   ErrInfo->UFSErrorStats.DLTotalErrCnt = ErrStats.dl_total_err_cnt; 
   ErrInfo->UFSErrorStats.DMETotalErrCnt = ErrStats.dme_total_err_cnt; 

   return EFI_SUCCESS; 
}

/**
   Get the information about speed levels and voltage corners 
**/
EFI_STATUS EFIAPI UFSGetOpModeCaps (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    OUT EFI_STORAGE_OP_MODE_CAPABILITIES *Caps)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   
   if ((NULL == This) || (NULL == Caps)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   rc = ufs_get_operational_mode_capabilities (hUFS, (void *)Caps);
   ReleaseLock (UfsLockPtr); 
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "ufs_get_operational_mode_capabilities failed with return value %d\n", rc)); 
      return EFI_DEVICE_ERROR;
   }
   
   return EFI_SUCCESS;
}

/**
  Gets the current UFS operational mode 
**/
EFI_STATUS EFIAPI UFSGetCurrentOpMode (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_OP_MODE_INFO *OpModeInfo)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_current_operational_mode_info CurrInfo; 
   
   if ((NULL == This) || (NULL == OpModeInfo)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   /* Set the voltage corner and speed to the one requested */
   rc = ufs_get_current_operational_mode_info (hUFS, &CurrInfo); 
   ReleaseLock (UfsLockPtr); 
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "ufs_get_current_operational_mode_info failed with return value %d\n", rc)); 
      return EFI_DEVICE_ERROR;
   }

   OpModeInfo->CurrentSpeedLevel = CurrInfo.speed_level; 
   OpModeInfo->CurrentVoltCorner = CurrInfo.volt_corner; 
   OpModeInfo->LinkState = CurrInfo.link_state; 
   
   return EFI_SUCCESS;
}

/**
   Sets the UFS speed (gear)
**/
EFI_STATUS EFIAPI UFSSetGear (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN UINT8 SpeedLevel)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   
   if ((NULL == This) || (0 == SpeedLevel)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *)UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   /* Set the speed (gear) to the requested one */
   rc = ufs_set_speed (hUFS, SpeedLevel);
   ReleaseLock (UfsLockPtr); 
   if (UFS_EOK != rc) 
   {
      DEBUG ((EFI_D_ERROR, "ufs_set_speed failed with return value %d\n", rc)); 
      if (-UFS_EINVAL == rc) {
         return EFI_UNSUPPORTED; 
      }
      else {
         return EFI_DEVICE_ERROR;
      }
   }
   
   return EFI_SUCCESS;
}

/** 
   Sets the voltage corner 
**/
EFI_STATUS EFIAPI UFSSetVoltageCorner (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_VOLT_CORNER VoltCorner)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   
   if ((NULL == This) || (0 == VoltCorner)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *)UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   /* Set the voltage corner to the one requested */
   rc = ufs_configure_volt_corner (hUFS, VoltCorner);
   ReleaseLock (UfsLockPtr); 
   if (UFS_EOK != rc) 
   {
      DEBUG ((EFI_D_ERROR, "ufs_configure_volt_corner failed with return value %d\n", rc)); 
      if (-UFS_EINVAL == rc) {
         return EFI_UNSUPPORTED; 
      }
      else {
         return EFI_DEVICE_ERROR;
      }
   }
   
   return EFI_SUCCESS;
}

/** 
   Sets the operational mode (speed + voltage corner)  
**/
EFI_STATUS EFIAPI UFSSetOperationalMode (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_VOLT_CORNER VoltCorner,
    IN UINT8 SpeedLevel)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   
   if ((NULL == This) || (0 == SpeedLevel) || (0 == VoltCorner)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   /* Set the voltage corner and speed to the one requested */
   rc = ufs_set_operational_mode (hUFS, VoltCorner, SpeedLevel);
   ReleaseLock (UfsLockPtr); 
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "ufs_set_operational_mode failed with return value %d\n", rc)); 
      if (-UFS_EINVAL == rc) {
         return EFI_UNSUPPORTED;
      }
      else {
         return EFI_DEVICE_ERROR;
      }
   }
   
   return EFI_SUCCESS;
}

/**
   Configures any link parameters 
**/
EFI_STATUS EFIAPI UFSConfigLinkParams (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_LINK_PARAMS *Params)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   if ((NULL == This) || (NULL == Params)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   rc = ufs_autoH8 (hUFS, Params->IdleTimeMs); 
   ReleaseLock (UfsLockPtr); 
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "ufs_autoH8 failed with return value %d\n", rc)); 
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS; 
} 

/**
   Changes the UFS link state (hibernate enter/exit)
**/
EFI_STATUS EFIAPI UFSSetLinkState (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_LINK_STATE LinkState)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   UINT8 H8_Enter = 1; 
   
   if (NULL == This) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   /* Link active = disable hibernate and vice versa */
   if (LINK_ACTIVE == LinkState) {
      H8_Enter = 0; 
   } 
   else if (LINK_SLEEP == LinkState) {
      H8_Enter = 1; 
   }
   else {
      return EFI_INVALID_PARAMETER; 
   }

   AcquireLock (UfsLockPtr); 
   rc = ufs_h8 (hUFS, H8_Enter); 
   ReleaseLock (UfsLockPtr); 

   if (rc != UFS_EOK) {
      DEBUG ((EFI_D_ERROR, "ufs_h8 failed with return value %d\n", rc)); 
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}

/**
   Sets the UFS device mode.
**/
EFI_STATUS EFIAPI UFSSetDeviceMode (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_DEV_MODE DevMode)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   ufs_device_mode Device_Mode;

   if (NULL == This) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   /* Device_Mode: 1 - Active, 2 - UFS_sleep, 3 - PowerDown  */
   switch (DevMode)
   {
      case DEVICE_ON:
         Device_Mode = UFS_ACTIVE;
         break;
      case DEVICE_SLEEP:
         Device_Mode = UFS_SLEEP;
         break;
      case DEVICE_OFF:
         Device_Mode = UFS_POWERDOWN;
         break;
      default:
         return EFI_INVALID_PARAMETER;
   }
   
   AcquireLock (UfsLockPtr); 
   rc = ufs_set_device_mode (hUFS, Device_Mode); 
   ReleaseLock (UfsLockPtr); 

   if (rc != UFS_EOK) {
      DEBUG ((EFI_D_ERROR, "UFSSetDeviceMode failed with return value %d\n", rc)); 
      return EFI_DEVICE_ERROR;
   }

    return EFI_SUCCESS;
}

/**
   Read BufferSize bytes from Lba into Buffer.
**/
EFI_STATUS EFIAPI UFSReadBlocks (
            IN VOID                   *This,
            IN UINT32                  MediaId,
            IN EFI_LBA                 Lba,
            IN UINT64                  BufferSize,
            OUT VOID                   *Buffer, 
            IN UINT64                  *CryptoIndex, 
            IN VOID                    *CryptoIvInput)
{
   INT32  rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   UINT32 transfer_size = 0, block_count = 0, block_size = 0;
   UINT8 *temp_buffer;
   EFI_BLOCK_IO_MEDIA *Media; 
   struct ufs_crypto_context crypto; 

   /* Validate passed-in pointers are not NULL */
   if ((NULL == Buffer) || (NULL == This)) {
      return EFI_INVALID_PARAMETER;
   }
   
   if ((NULL != CryptoIndex) && (NULL != CryptoIvInput)) {
      Media = ((EFI_BLOCK_IO_CRYPTO_PROTOCOL *)This)->Media;
      UfsDevice = UFS_DEV_FROM_BLOCKIO_CRYPTO (This);
   }
   else {
      Media = ((EFI_BLOCK_IO_PROTOCOL *)This)->Media; 
      UfsDevice = UFS_DEV_FROM_BLOCKIO (This);
   }
   
   if (NULL == Media) {
      return EFI_INVALID_PARAMETER;
   }   

   /* Validate if buffer is multiple of block size */
   if ((BufferSize%(Media->BlockSize)) != 0 ) {
      return EFI_BAD_BUFFER_SIZE;
   }

   /* Validate block size and access range */
   if ((Lba > Media->LastBlock) || (Media->BlockSize == 0)) {
      return EFI_INVALID_PARAMETER;
   }

   if (Media->MediaId != MediaId) {
      return EFI_MEDIA_CHANGED;
   }

   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* If BufferSize is zero, the host is pinging the card for its presence */
   if (0 == BufferSize)
   {
      if (!hUFS)
      {
         (void) ufs_close(hUFS);
         UfsDevice->DeviceHandle = NULL;
         UfsDevice->BlkIo.Media->MediaPresent = FALSE;
         UfsDevice->BlkIoCrypto.Media->MediaPresent = FALSE;
         return EFI_NO_MEDIA;
      }
      else
      {
         return EFI_SUCCESS;
      }
   }

   block_size = Media->BlockSize;
   block_count = (BufferSize/block_size);

   /* Check if LBA plus the total sectors trying to access would exceed the */
   /* total size of the partition */
   if ((Lba + (BufferSize/block_size)) > (Media->LastBlock + 1)) {
      return EFI_INVALID_PARAMETER;
   }

   /* Break transfer into smaller transfers to UFS_MAX_BLOCK_TRANSFER_SIZE transfer size */
   temp_buffer = (UINT8 *)Buffer;

   while (block_count > 0)
   {
      transfer_size = (block_count > UFS_MAX_BLOCK_TRANSFERS) ?
         UFS_MAX_BLOCK_TRANSFERS : block_count;
		 
      if ((NULL != CryptoIndex) && (NULL != CryptoIvInput)) {
         crypto.cfg_index = *(CryptoIndex) & 0xff; 
         crypto.dun = *((UINT64 *)CryptoIvInput); 
         rc = ufs_read_ex( hUFS, temp_buffer, Lba, transfer_size, NULL, &crypto);
      }
      else {
      rc = ufs_read( hUFS, temp_buffer, Lba, transfer_size);
      }		 

      Lba = Lba + transfer_size;
      block_count = block_count - transfer_size;
      temp_buffer = temp_buffer + (transfer_size * block_size);

      if (UFS_EOK != rc) 
      {
        DEBUG ((EFI_D_ERROR, "UFS READ with return value of %d\n", rc));
        // If all the doorbell slots are occupied and an asyn request comes in.
        if (UFS_EBUSY == rc)
        {
          return EFI_OUT_OF_RESOURCES; 
        }
        else 
        {
          return EFI_DEVICE_ERROR;
        }
      }
   }

   return EFI_SUCCESS;
}

/**
   Write BufferSize bytes from Lba into Buffer.
**/
EFI_STATUS EFIAPI UFSWriteBlocks (
            IN VOID                    *This,
            IN UINT32                  MediaId,
            IN EFI_LBA                 Lba,
            IN UINT64                  BufferSize,
            IN VOID                    *Buffer,
            IN UINT64                  *CryptoIndex, 
            IN VOID                    *CryptoIvInput)
{
   INT32  rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   UINT32 transfer_size = 0, block_count = 0, block_size = 0;
   UINT8 *temp_buffer;
   EFI_BLOCK_IO_MEDIA *Media;
   struct ufs_crypto_context crypto;

   /* Validate passed-in pointers are not NULL */
   if ((NULL == Buffer) || (NULL == This)) {
      return EFI_INVALID_PARAMETER;
   }

   if ((NULL != CryptoIndex) && (NULL != CryptoIvInput)) {
      Media = ((EFI_BLOCK_IO_CRYPTO_PROTOCOL *)This)->Media;
      UfsDevice = UFS_DEV_FROM_BLOCKIO_CRYPTO (This);
   }
   else {
      Media = ((EFI_BLOCK_IO_PROTOCOL *)This)->Media; 
      UfsDevice = UFS_DEV_FROM_BLOCKIO (This);
   }

   if (NULL == Media) {
      return EFI_INVALID_PARAMETER;
   }   

   /* Validate if buffer is multiple of block size */
   if (((BufferSize%(Media->BlockSize)) != 0)) {
      return EFI_BAD_BUFFER_SIZE;
   }

   /* Validate block size and access range */
   if ((Lba > Media->LastBlock) || (Media->BlockSize == 0)) {
      return EFI_INVALID_PARAMETER;
   }

   /* Validate if LBA plus the total sectors trying to access would exceed the */
   /* total size of the partition */
   if ((Lba + (BufferSize/Media->BlockSize)) > (Media->LastBlock + 1)) {
      return EFI_INVALID_PARAMETER;
   }

   if (Media->MediaId != MediaId) {
      return EFI_MEDIA_CHANGED;
   }

   hUFS = UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   /* Break transfer into smaller transfers to UFS_MAX_BLOCK_TRANSFER_SIZE transfer size */
   temp_buffer = (UINT8 *)Buffer;
   block_size = UfsDevice->BlkIo.Media->BlockSize;
   block_count = (BufferSize/block_size);

   while (block_count > 0)
   {
     transfer_size = (block_count > UFS_MAX_BLOCK_TRANSFERS) ?
                         UFS_MAX_BLOCK_TRANSFERS : block_count;

     if ((NULL != CryptoIndex) && (NULL != CryptoIvInput)) {
        crypto.cfg_index = *(CryptoIndex) & 0xff; 
        crypto.dun = *((UINT64 *)CryptoIvInput); 
        rc = ufs_write_ex( hUFS, temp_buffer, Lba, transfer_size, NULL, &crypto);
     }
     else {
     rc = ufs_write( hUFS, temp_buffer, Lba, transfer_size);
     }		 

     Lba = Lba + transfer_size;
     block_count = block_count - transfer_size;
     temp_buffer = temp_buffer + (transfer_size * block_size);

     // If all the doorbell slots are occupied and an asyn request comes in.
     if (UFS_EOK != rc) 
     {
        DEBUG ((EFI_D_ERROR, "UFS WRITE with return value of %d\n", rc));
        if (UFS_EBUSY == rc) 
        {
          return EFI_OUT_OF_RESOURCES; 
        }
        else 
        {
          return EFI_DEVICE_ERROR;
        }
      }
   }
   return EFI_SUCCESS;
}


/**
   Flush the Block Device.
**/
EFI_STATUS EFIAPI UFSFlushBlocks (
            IN EFI_BLOCK_IO_PROTOCOL  *This)
{
   INT32  rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;

   /* Validate passed-in pointers are not NULL */
   if (NULL == This) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_BLOCKIO (This);
   hUFS = UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   /* Use LBA = 0 and Blocks = 0 to sync the entire LUN */
   rc = ufs_sync_cache (hUFS, 0, 0); 
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "UFSFlushBlocks with return value of %d\n", rc));
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS; 
}

/**
   Reset the Block Device.
**/
EFI_STATUS EFIAPI UFSCryptoReset (
            IN EFI_BLOCK_IO_CRYPTO_PROTOCOL   *This,
            IN BOOLEAN                        ExtendedVerification)
{
   return EFI_SUCCESS;
}


EFI_STATUS GetICECapabilities (
            IN CHAR8                             *Id, 
            OUT EFI_BLOCK_IO_CRYPTO_CAPABILITIES *Capabilities)
{
   (void) Id; 
   (void) Capabilities; 
   return EFI_SUCCESS; 
}

EFI_STATUS GetICEConfiguration (			
            IN CHAR8                                             *Id,
            IN UINT64                                            StartIndex,
            IN UINT64 										              ConfigurationCount,
            IN EFI_GUID 										           *KeyOwnerGuid, 
            OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ConfigurationTable)
{
   (void)Id;
   (void)StartIndex;
   (void)ConfigurationCount; 
   (void)KeyOwnerGuid;
   (void)ConfigurationTable;
   return EFI_SUCCESS;		
}

/**
   Get CRYPTO capabilities.
**/
EFI_STATUS EFIAPI UFSCryptoGetCapabilities (
            IN EFI_BLOCK_IO_CRYPTO_PROTOCOL      *This,
            OUT EFI_BLOCK_IO_CRYPTO_CAPABILITIES *Capabilities)
{
   if ((NULL == This) || (NULL == Capabilities)) {
      return EFI_INVALID_PARAMETER;
   }
	
   if (0 != GetICECapabilities ("ufs", Capabilities)) {
      return EFI_DEVICE_ERROR; 
   }

   return EFI_SUCCESS;
}

/**
   Set CRYPTO configuration.
**/
EFI_STATUS EFIAPI UFSCryptoSetConfiguration (			
            IN EFI_BLOCK_IO_CRYPTO_PROTOCOL                      *This,
            IN UINT64                                            ConfigurationCount, 
            IN EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY     *ConfigurationTable, 
            OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ResultingTable)
{
   if ((NULL == This) || (NULL == ConfigurationTable)) {
      return EFI_INVALID_PARAMETER;
   }

   if (0 != SetICEConfiguration ("ufs", ConfigurationCount, ConfigurationTable, ResultingTable)) {
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}

/**
   Get CRYPTO configuration.
**/
EFI_STATUS EFIAPI UFSCryptoGetConfiguration (			
            IN EFI_BLOCK_IO_CRYPTO_PROTOCOL                      *This,
            IN UINT64                                            StartIndex,
            IN UINT64                                            ConfigurationCount,
            IN EFI_GUID                                          *KeyOwnerGuid, 
            OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ConfigurationTable)
{
   if ((NULL == This) || (NULL == ConfigurationTable)) {
      return EFI_INVALID_PARAMETER;
   }

   if (0 != GetICEConfiguration ("ufs", StartIndex, ConfigurationCount, KeyOwnerGuid, ConfigurationTable)) {
      return EFI_DEVICE_ERROR; 
   }

   return EFI_SUCCESS;		
}

/**
   Flush the Block Device.
**/
EFI_STATUS EFIAPI UFSCryptoFlushBlocks (
            IN EFI_BLOCK_IO_CRYPTO_PROTOCOL  *This, 
            IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token)
{
   return EFI_SUCCESS;
}

/**
   Function: UFSGetLevelShifterInfo
  
 Get information about Level Shifter
  
   @param  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
   @param  LsInfo              Level Shifter Information
  
   @return EFI_SUCCESS             Operation completed successfully.
   @return EFI_INVALID_PARAMETER   Parameter is invalid.
   @return EFI_DEVICE_ERROR        Device reported an error.  
 **/
EFI_STATUS EFIAPI UFSGetLevelShifterInfo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    OUT EFI_STORAGE_LS_INFO *LsInfo)
{
  /* This Function is not supported for UFS. */ 
  return EFI_UNSUPPORTED;
}

/** 
  Function: UFSGetTurboModeInfo 

  Get information about Turbo Mode enablement

  @param  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance 
  @param  TurboModeEn         Turbo Mode enable Information

  @return EFI_SUCCESS             Operation completed successfully.
  @return EFI_INVALID_PARAMETER   Parameter is invalid. 
  @return EFI_DEVICE_ERROR        Device reported an error.  
**/
EFI_STATUS EFIAPI UFSGetTurboModeInfo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_TURBOMODE_INFO *TurboModeInfo)
{
   INT32 rc = UFS_EOK;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS; 
   uint8_t tm_info;

   if ((This == NULL) || (TurboModeInfo == NULL)) 
   {
      return EFI_INVALID_PARAMETER; 
   }
   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   rc = ufs_get_turbofreq_diff_info (hUFS, &tm_info); 
   ReleaseLock (UfsLockPtr); 
   
   if (rc != UFS_EOK) {
   DEBUG ((EFI_D_ERROR, "ufs_get_turbofreq_diff_info failed with return value %d\n", rc)); 
   return EFI_DEVICE_ERROR;
   }
   TurboModeInfo->DiffTurboFreq = tm_info;
   return EFI_SUCCESS; 
}
/**
   Get Shared ICE info
**/
EFI_STATUS EFIAPI UFSGetSharedIceAlgo (
            IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
            OUT EFI_STORAGE_SHARED_ICE_INFO *buffer)
{
   INT32  rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   if ((NULL == This) || (NULL == buffer)) 
   { return EFI_INVALID_PARAMETER; }

   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   
   rc = ufs_get_shared_ice_algo (hUFS, (void *)buffer);

   ReleaseLock (UfsLockPtr);
   
   if (UFS_EOK != rc) 
   {
     if (-UFS_EPERM == rc) {
       DEBUG ((EFI_D_ERROR, "SharedIce Algorithm Not Supported\n"));
       return EFI_UNSUPPORTED; 
     }
     else
     {
       DEBUG ((EFI_D_ERROR, "UFSGetSharedIceAlgo failed with error = %d\n",rc));
       return EFI_DEVICE_ERROR;
     }
   }  
   return EFI_SUCCESS;
}

/**
   Set Shared ICE info
**/
EFI_STATUS EFIAPI UFSSetSharedIceAlgo (
            IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
            IN EFI_STORAGE_SHARED_ICE_INFO *buffer)
{
   INT32  rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   if ((NULL == This) || (NULL == buffer)) 
   { return EFI_INVALID_PARAMETER;}
   
   UfsDevice = UFS_DEV_FROM_DEV_MGMT (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr); 
   
   rc = ufs_set_shared_ice_algo (hUFS, (void *)buffer);

   ReleaseLock (UfsLockPtr);

   if (UFS_EOK != rc) 
   {
     if (-UFS_EPERM == rc) {
        DEBUG ((EFI_D_ERROR, "SharedIce Algorithm Not Supported\n"));
        return EFI_UNSUPPORTED; 
     }
     else
     {
	DEBUG ((EFI_D_ERROR, "UFSSetSharedIceAlgo failed with error = %d\n",rc));
	return EFI_DEVICE_ERROR;
     }
   }   
   
   return EFI_SUCCESS;
}

VOID EFIAPI RegisterListener (
            IN EFI_EVENT        Event,
            IN VOID             *Context)
{
   EFI_STATUS EfiStatus = EFI_UNSUPPORTED;
   EFI_BLOCK_IO_PROTOCOL *BlkIo = (EFI_BLOCK_IO_PROTOCOL *)Context;

   if ((NULL == BlkIo) || (NULL == BlkIo->Media))
   {
      return;
   }

   EfiStatus = RPMBListenerInit(BlkIo->Media->MediaId);
   if (EFI_SUCCESS != EfiStatus)
   {
      DEBUG ((EFI_D_ERROR, "Failed to initialize RPMB Listener, Status 0x%08x\n", EfiStatus));
   }

   EfiStatus = GPTListenerInit(BlkIo);
   if (EFI_SUCCESS != EfiStatus)
   {
      DEBUG ((EFI_D_ERROR, "Failed to initialize GPT Listener, Status 0x%08x\n", EfiStatus));
   }

   EfiStatus = InitPartitionConfig();
   if (EFI_SUCCESS != EfiStatus)
   {
      DEBUG ((EFI_D_ERROR, "Failed to initialize Partition config, Status 0x%08x\n", EfiStatus));
   }
}

VOID
EFIAPI
UfsDxeExitBSCallback (
   IN EFI_EVENT        Event,
   IN VOID             *Context)
{
   INT32 rc = 0; 
   UINT32 lun = 0; 
   CHAR8 OsTypeString[MAX_OS_TYPE_LEN] = {0};
   UINTN OsTypeStringLen = MAX_OS_TYPE_LEN;

   for (lun = 0; lun < UFS_UEFI_MAX_LUN_ACCESS; lun++) {
      if (gUfsDevice[lun].DeviceHandle) {
         rc = ufs_sync_cache ((struct ufs_handle *)gUfsDevice[lun].DeviceHandle, 0, (gUfsDevice[lun].BlkIo.Media->LastBlock + 1));
         if (UFS_EOK != rc) {
            DEBUG ((EFI_D_ERROR, "ufs_sync_cache for LUN %d with return value of %d\n", lun, rc));
         }
      }
   }

   GetConfigString ("OsTypeString", OsTypeString, &OsTypeStringLen);
   OsTypeString[MAX_OS_TYPE_LEN-1] = '\0';

   if (0 != AsciiStrCmp("WP", OsTypeString)){
      rc = ufs_set_device_mode((struct ufs_handle *)gUfsWlunDevice.DeviceHandle, UFS_POWERDOWN);
      if (UFS_EOK != rc) {
         DEBUG ((EFI_D_ERROR, "ufs_set_device_mode with return value of %d\n", rc));
      }
   }
}

static void UFSSleepCb (enum PwrTxnType SleepMode, struct ufs_handle *hUFS)
{
   INT32 rc = 0; 

   switch(SleepMode)
   {
      case DevicePwrOFF:
         rc = ufs_clock_gate (hUFS); 
         if (UFS_EOK != rc) {
            DEBUG ((EFI_D_ERROR, "ufs_clock_gate with return value of %d\n", rc));
         }
         break;
      case DevicePwrON:
         rc = ufs_clock_ungate (hUFS); 
         if (UFS_EOK != rc) {
            DEBUG ((EFI_D_ERROR, "ufs_clock_ungate with return value of %d\n", rc));
         }
         break;
      default:
         break;
   }
}

/**
   Update ACPI AML variable to enable update UFS features
**/
EFI_STATUS EFIAPI AmlUpdateUFSFeatures (
   IN OUT VOID **AmlVariableBuffer, 
   IN OUT UINTN  AmlVariableBufferSize
   )
{
   if ((NULL == AmlVariableBuffer) || (NULL == *AmlVariableBuffer))
   {
      DEBUG ((EFI_D_WARN, "AmlUpdateUFSFeatures: Could not find the AML variable in DSDT\r\n"));
      return EFI_SUCCESS; 
   }

   *((UINTN*) ((CHAR8 *)(*AmlVariableBuffer) + AML_NAMESPACE_HEADER_SIZE)) = 0x1; 

   return EFI_SUCCESS; 
}

VOID EFIAPI RegisterAmlVariable (
   IN EFI_EVENT        Event,
   IN VOID             *Context)
{ 
   CHAR8 AmlVariableUFS40[AML_NAMESTRING_LENGTH] = {'P','U','S','4'}; 
   CHAR8 *AmlVariable = NULL; 
   EFI_STATUS Status = EFI_UNSUPPORTED; 

   if (NULL == AcpiPlatProtocol)
   {
      Status = gBS->LocateProtocol(&gQcomAcpiPlatformProtocolGuid, NULL, 
                                (VOID **)&AcpiPlatProtocol); 
      ASSERT_EFI_ERROR(Status); 
   }

   else if (Event == Ufs40Init)
   {
      AmlVariable = AmlVariableUFS40;
   }

   Status = AcpiPlatProtocol->AmlVariableRegister(AcpiPlatProtocol, AmlVariable, GETMODE_PREFIX, 
                                                  NULL, AmlUpdateUFSFeatures); 
   ASSERT_EFI_ERROR(Status); 
}

/**
   Driver initializatoin entry point.
**/
EFI_STATUS EFIAPI UFSDxeInitialize (
            IN EFI_HANDLE         ImageHandle,
            IN EFI_SYSTEM_TABLE   *SystemTable)
{
   EFI_STATUS Status;
   UINT32 lun = 0;
   UINT32 lun_enabled_mask = 0;
   UINT8  total_luns_enabled = 0;
   VOID *ScmProtocol = NULL;
   INT32 rc = 0;
   struct ufs_info_type ufs_info = {0};

   UINT32 AlwaysDoSmmuConfig = 0;
   CHAR8 OsTypeString[MAX_OS_TYPE_LEN] = {0};
   UINTN OsTypeStringLen = MAX_OS_TYPE_LEN;

   InitRecursiveLock ("UFS_DRVR", &UfsLockPtr);

   /* Don't do anything if it doesn't boot from UFS */
   if (!boot_from_ufs ()) {
      /* Turn off the UFS clocks */
      ufs_clk_ctrl (0, UFS_CLK_OFF);

      /* Configure SMMU if HLOS needs it to detect UFS */
      Status = GetConfigValue ("UfsSmmuConfigForOtherBootDev", &AlwaysDoSmmuConfig);
      if (EFI_SUCCESS != Status)
      {
         AlwaysDoSmmuConfig = 0;
      }

      if (AlwaysDoSmmuConfig)
      {
         rc = ufs_configure_smmu(); 
         if (UFS_EOK != rc) 
         {
            DEBUG ((EFI_D_ERROR, "UFSSmmuConfig failed\n"));
            return EFI_DEVICE_ERROR; 
         }
      }

      return EFI_SUCCESS;
   }

// TODO: Remove Timer Profiling Code
#if 0
   {
      Timetick_timer_Type Timer;
      UINT32 call_count = 0;
      UINT64 starting_tick = 0, ending_tick = 0, total_ticks = 0;
      UINT32 TimetickFreq = 0;
      UINT64 uSeconds = 0;

      if(PcdGet32(PcdQTimerEnabled))
      {
        Timer = TIMETICK_QTIMER;
      }
      else
      {
        Timer = TIMETICK_TIMER_ADGT;
      }

      /* Enable TimeTick for collecting performance data */
      Timetick_Init();
      Timetick_Enable(Timer, TRUE);

      Timetick_GetCount(Timer, &starting_tick);
      //Delay of 5s
      for (call_count=0; call_count<5000; call_count++)
      {
        ufs_osal_stall_us(1);
      }
      Timetick_GetCount(Timer, &ending_tick);
      total_ticks = ending_tick - starting_tick;

      /* Convert ticks to micro seconds */
      Timetick_GetFreq(Timer, &TimetickFreq);
      uSeconds = MultU64x32(total_ticks, 1000000);
      uSeconds = DivU64x32(uSeconds, TimetickFreq);
      DEBUG ((EFI_D_ERROR, "uSeconds = %ld\n", uSeconds));
   }
#endif

   /* When UEFI is RAM Loaded UFS register space is not map. Map it always. */
   {
     EFI_HWIO_PROTOCOL *HWIOProtocol = NULL;
     UINT64 Addr, ICEAddr; 
     Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&HWIOProtocol);
     if ((EFI_SUCCESS != Status) || (HWIOProtocol == NULL))
     {
       DEBUG ((EFI_D_ERROR, "ERROR: Failed to locate HWIO Protocol: 0x%08x\n", Status));
       return Status;
     }

     Status = HWIOProtocol->MapRegion(HWIOProtocol, "+UFS_MEM_UFS", (UINT8**) &Addr);
     if (EFI_SUCCESS != Status)
     {
       DEBUG ((EFI_D_ERROR, "ERROR: 0x%08x Failed to map UFS_MEM_UFS base address: 0x%08x\n", Status, Addr));
       return Status;
     }

     Status = HWIOProtocol->MapRegion(HWIOProtocol, "+UFS_MEM_ICE", (UINT8**) &ICEAddr);
     if (EFI_SUCCESS != Status)
     {
       DEBUG ((EFI_D_ERROR, "ERROR: 0x%08x Failed to map UFS_MEM_ICE base address: 0x%08x\n", Status, ICEAddr));
       return Status;
     }
   }

   rc = ufs_configure_smmu(); 
   if (UFS_EOK != rc) 
   {
      DEBUG ((EFI_D_ERROR, "UFSSmmuConfig failed\n"));
      return EFI_DEVICE_ERROR; 
   }

   /* Initialize UFS */
   gUfsWlunDevice.DeviceHandle = ufs_open (0, UFS_WLUN_DEVICE);
   if (!gUfsWlunDevice.DeviceHandle)
      ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);

   /* Get valid LUNs */
   rc = ufs_get_device_info ((struct ufs_handle *)gUfsWlunDevice.DeviceHandle, &ufs_info); 
   if (UFS_EOK != rc)
      ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);
   lun_enabled_mask = ufs_info.dLunEnabled;
   total_luns_enabled = ufs_info.bNumberLu;

   /* Install DevMgmt, DevicePath protocol on Device WLUN */
   gUfsWlunDevicePath.Ufs = UfsPath;
   gUfsWlunDevicePath.Ufs.Guid = (EFI_GUID)EFI_UFS_DEVICE_WLUN_GUID;
   gUfsWlunDevicePath.End = UfsEndPath;

   gUfsWlunDevice.DeviceMgmt = gUfsDeviceMgmtProtocol;
   Status = gBS->InstallMultipleProtocolInterfaces (
       &gUfsWlunDevice.ClientHandle,
       &gEfiDevicePathProtocolGuid, &gUfsWlunDevicePath,
       &gEfiStorageDevMgmtProtocolGuid, &gUfsWlunDevice.DeviceMgmt,
       NULL
   );

   for (lun = 0; lun < total_luns_enabled; lun++)
   {
      // Check if LUN is enabled
      if (!(lun_enabled_mask & ((UINT32) 1) << lun))
         continue;

      gUfsDevicePath[lun].Ufs = UfsPath;
      gUfsDevicePath[lun].Ufs.Guid = UfsDevicePathGuids[lun];
      gUfsDevicePath[lun].End = UfsEndPath;

      gUfsDevice[lun].Signature    = UFS_DEV_SIGNATURE;
      gUfsDevice[lun].BlkIo        = gBlockIoUfs;
      gUfsDevice[lun].BlkIo.Media  = &gMediaUfs[lun];
      gUfsDevice[lun].BlkIoCrypto  = gBlockIoCryptoUfs;
      gUfsDevice[lun].BlkIoCrypto.Media = &gMediaUfs[lun];
      gUfsDevice[lun].BlkIo2        = gBlockIo2Ufs;
      gUfsDevice[lun].BlkIo2.Media  = &gMediaUfs[lun];
      gUfsDevice[lun].CardInfo     = gUfsCardInfoProtocol;
      gUfsDevice[lun].EraseBlk     = gUfsEraseBlkProtocol;
      CopyMem(gUfsDevice[lun].BlkIo.Media,
                 &UFSMedia, sizeof(EFI_BLOCK_IO_MEDIA));
      CopyMem(gUfsDevice[lun].BlkIoCrypto.Media, 
                 &UFSMedia, sizeof(EFI_BLOCK_IO_MEDIA));
      gUfsDevice[lun].WriteProtect = gUfsWriteProtectProtocol;

      /* Initialize LUN */
      gUfsDevice[lun].DeviceHandle = ufs_open (0, lun);
      if (!gUfsDevice[lun].DeviceHandle) {
         gUfsDevice[lun].BlkIo.Media->MediaPresent = FALSE;
         continue;
      }
      gUfsDevice[lun].BlkIo.Media->MediaPresent = TRUE;
      gUfsDevice[lun].BlkIoCrypto.Media->MediaPresent = TRUE; 
      rc = ufs_get_device_info ((struct ufs_handle *)gUfsDevice[lun].DeviceHandle, &ufs_info);
      if (UFS_EOK != rc)
         ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);
      gUfsDevice[lun].BlkIo.Media->LastBlock = ufs_info.dLuTotalBlocks - 1;
      gUfsDevice[lun].BlkIoCrypto.Media->LastBlock = ufs_info.dLuTotalBlocks - 1; 

      /* Assume LUN0 and install the following protocols: */
      /* BlkIO */
      Status = gBS->InstallMultipleProtocolInterfaces (
         &gUfsDevice[lun].ClientHandle,
         &gEfiBlockIoProtocolGuid, &gUfsDevice[lun].BlkIo,
         &gEfiDevicePathProtocolGuid, &gUfsDevicePath[lun],
         &gEfiMemCardInfoProtocolGuid, &gUfsDevice[lun].CardInfo,
         &gEfiBlockIo2ProtocolGuid, &gUfsDevice[lun].BlkIo2,
         &gEfiEraseBlockProtocolGuid, &gUfsDevice[lun].EraseBlk,
         &gEfiStorageWpProtocolGuid, &gUfsDevice[lun].WriteProtect,
         &gEfiBlockIoCryptoProtocolGuid, &gUfsDevice[lun].BlkIoCrypto, 
         NULL
      );
      ASSERT_EFI_ERROR(Status);
   }
   
   GetConfigString ("OsTypeString", OsTypeString, &OsTypeStringLen);
   OsTypeString[MAX_OS_TYPE_LEN-1] = '\0';
   
   if (ufs_info.wSpecVersion >= 0x400 && (0 == AsciiStrCmp("WP", OsTypeString))) {
      /* Create the RegisterAmlVariable callback */
      Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                RegisterAmlVariable,
                                NULL, 
                                &Ufs40Init);
      ASSERT_EFI_ERROR (Status); 
   
      Status = gBS->RegisterProtocolNotify(&gQcomAcpiPlatformProtocolGuid,
                                           Ufs40Init, 
                                           (VOID *)&Ufs40InitToken); 
      ASSERT_EFI_ERROR(Status);
   }
	
   gUfsRpmbDevicePath.Ufs = UfsPath;
   gUfsRpmbDevicePath.Ufs.Guid = (EFI_GUID)EFI_UFS_RPMB_LUN_GUID;
   gUfsRpmbDevicePath.End = UfsEndPath;

   gUfsRpmbDevice.RPMB = gUfsRpmbProtocol;
   gUfsRpmbDevice.CardInfo = gUfsCardInfoProtocol;

   gUfsRpmbDevice.DeviceHandle = ufs_open (0, UFS_WLUN_RPMB);
   if (!gUfsRpmbDevice.DeviceHandle) {
      DEBUG ((EFI_D_ERROR, "Cannot open UFS RPMB!\n"));
   }
   rc = ufs_get_device_info ((struct ufs_handle *)gUfsRpmbDevice.DeviceHandle, &ufs_info);
   if (UFS_EOK != rc)  ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);

   gUfsRpmbDevice.RPMB.RPMBMaxTransferSize = ufs_info.RPMBPartitionSizeInBytes;
   gUfsRpmbDevice.RPMB.RPMBPartitionSizeInBytes = ufs_info.RPMBPartitionSizeInBytes;
   gUfsRpmbDevice.RPMB.ReliableWriteCount = ufs_info.bRPMB_ReadWriteSize;

   Status = gBS->InstallMultipleProtocolInterfaces (
      &gUfsRpmbDevice.ClientHandle,
      &gEfiSdccRpmbProtocolGuid, &gUfsRpmbDevice.RPMB,
      &gEfiDevicePathProtocolGuid, &gUfsRpmbDevicePath,
      &gEfiMemCardInfoProtocolGuid, &gUfsRpmbDevice.CardInfo,
      NULL
   );

   /* Allocate memory for RPMB listener */
   Status = RPMBListenerAllocMem();
   if(Status != EFI_SUCCESS)
   {
      DEBUG ((EFI_D_ERROR, "Failed to allocate memory for RPMB listener\n"));
      return Status;
   }

   /* Allocate memory for GPT listener */
   Status = GPTListenerAllocMem();
   if(Status != EFI_SUCCESS)
   {
      DEBUG ((EFI_D_ERROR, "Failed to allocate memory for GPT listener\n"));
      return Status;
   }

   Status = gBS->LocateProtocol(&gQcomScmProtocolGuid, NULL,
                                (VOID **)&ScmProtocol);
   if (Status == EFI_SUCCESS)
   {
      RegisterListener(ScmInitialized, (VOID *)&gUfsDevice[0].BlkIo);
   }
   else
   {
      /* Create the RegisterListener callback */
      Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                RegisterListener,
                                (VOID *)&gUfsDevice[0].BlkIo,
                                &ScmInitialized
                             );
      ASSERT_EFI_ERROR (Status);

      Status = gBS->RegisterProtocolNotify(&gQcomScmProtocolGuid,
                                           ScmInitialized,
                                           (VOID *)&ScmInitializedToken);

      ASSERT_EFI_ERROR(Status);
   }

   /* Initialize request list for Block IO 2 */
   gUfsTransferInfo.BlkIO2Initialized = TRUE;
   Status = BlkIo2ReqListInit(&gUfsReqList, REQ_LIST_SIZE);

   if(Status == EFI_SUCCESS)
   {
      /* Create Internal Event for Block IO 2 */
      Status = gBS->CreateEvent (
                       EVT_TIMER | EVT_NOTIFY_SIGNAL,
                       UFS_TPL,
                       BlkIo2TimerEventNotify,
                       NULL,
                       &gUfsBlkIo2TimerEvent
                       );

      if(EFI_ERROR (Status))
      {
         gUfsTransferInfo.BlkIO2Initialized = FALSE;
         DEBUG ((EFI_D_WARN, "Block IO 2 timer creation failed, cannot use Block IO 2.\n"));
      }
   }
   else
   {
      gUfsTransferInfo.BlkIO2Initialized = FALSE;
      DEBUG ((EFI_D_WARN, "Initialization failed, cannot use Block IO 2.\n"));
   }

   /* Create an event for Erase, Purge */
   gUfsTransferInfo.PurgeEventInitialized = TRUE;
   Status = gBS->CreateEvent (
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
                    UFS_TPL,
                    PurgeTimerEventNotify,
                    NULL,
                    &gUfsPurgeTimerEvent
                    );

   if(EFI_ERROR (Status))
   {
      gUfsTransferInfo.PurgeEventInitialized = FALSE;
      DEBUG ((EFI_D_WARN, "Purge event timer creation failed, cannot use non-blocking block erase.\n"));
   }

   /* Register for Exit Boot Services callback to do sync cache */
   Status = gBS->CreateEventEx (EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                UfsDxeExitBSCallback,
                                NULL,
                                &gEfiEventExitBootServicesGuid,
                                &ExitBootServicesEvent);
   ASSERT_EFI_ERROR (Status);

   /* Register for Sleep callback for UFS LPM with SystemSleepLib */
   Status = RegisterDevicePowerTransitionCallback ((PwrTxnNotifyFn)UFSSleepCb, (struct ufs_handle *)gUfsWlunDevice.DeviceHandle);
   if (EFI_ERROR (Status))
   {
     DEBUG ((EFI_D_ERROR, "UFS Sleep callback registration failed, Status = 0x%lx\n", Status));
   }

   return EFI_SUCCESS;
}


/**
   Get the active UFS Boot LU
**/
EFI_STATUS EFIAPI UFSGetActiveBootLUInternal (
   EFI_MEM_CARDINFO_PROTOCOL  *This,
   UINT32                     *ActiveBootLU)
{
   INT32 rc;
   struct ufs_info_type info = {0};

   if ((NULL == This) || (NULL == ActiveBootLU))
   {
      return EFI_INVALID_PARAMETER;
   }

   rc = ufs_get_device_info ((struct ufs_handle *)gUfsWlunDevice.DeviceHandle, &info);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "Get Card Info FAILED %x\n\n\n", rc));
      return EFI_DEVICE_ERROR;
   }

   /* bBootLunEn tells us which BOOT LUN is current */
   *ActiveBootLU = info.bBootLunEn;

   return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UFSGetActiveBootLU (
   EFI_MEM_CARDINFO_PROTOCOL  *This,
   UINT32                     *ActiveBootLU)
{
  EFI_STATUS Status;

  AcquireLock (UfsLockPtr);
  Status = UFSGetActiveBootLUInternal (This, ActiveBootLU);
  ReleaseLock (UfsLockPtr);

  return Status;
}
/**
   Set the active UFS Boot LU
**/
EFI_STATUS EFIAPI UFSSetActiveBootLU (
   EFI_MEM_CARDINFO_PROTOCOL *This,
   UINT32                    BootLU)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   if ((NULL == This) || (BootLU > UFS_LUN_BOOT_B))
   {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_CARD_INFO (This);
   hUFS = UfsDevice->DeviceHandle;

   if (NULL == hUFS)
   {
      return EFI_INVALID_PARAMETER;
   }

   AcquireLock (UfsLockPtr);
   rc =  ufs_set_bootable (hUFS, BootLU);
   ReleaseLock (UfsLockPtr);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "Set Active Boot LU FAILED. %x\n\n\n", rc));
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}

/**
   Get the card information
**/
EFI_STATUS EFIAPI UFSGetCardInfoInternal (
            EFI_MEM_CARDINFO_PROTOCOL   *This,
            MEM_CARD_INFO               *card_info)
{
   char serial_num_str[254] = {0}; // 126 unicode chars + length + IDN
   INT32 rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   struct ufs_info_type info = {0};
   int i;

   if ((NULL == card_info) || (NULL == This)) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_CARD_INFO (This);
   hUFS = UfsDevice->DeviceHandle;
   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   /* Get Card Info */
   rc = ufs_get_device_info (hUFS, &info);
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "Get Card Info FAILED. %x\n\n\n", rc));
      return EFI_DEVICE_ERROR;
   }

   /* Copy the information out */
   card_info->card_type[0] = 'U';
   card_info->card_type[1] = 'F';
   card_info->card_type[2] = 'S';
   card_info->card_type[3] = ' ';

   card_info->mfr_id = info.wManufacturerID;
   rc = ufs_get_device_info_str (hUFS, info.iSerialNumber,
                                 serial_num_str, sizeof(serial_num_str));
   if (UFS_EOK != rc || serial_num_str[1] != 0x05)
   {
      DEBUG ((EFI_D_ERROR, "Get Card Serial Number FAILED. %x\n\n\n", rc));
      return EFI_DEVICE_ERROR;
   }

   card_info->serial_num_len = serial_num_str[0] - 2;  // Get length and reduce by 2 bytes (length, IDN)

   CopyMem(card_info->product_serial_num, &serial_num_str[2], card_info->serial_num_len);

   for (i = 0; i < 29; i++)
   {
      card_info->inquiry_str[i] = info.inquiry_str[i];
   }

   rc = ufs_get_device_info ((struct ufs_handle *)gUfsRpmbDevice.DeviceHandle, &info);
   if (UFS_EOK != rc)
   {
      DEBUG ((EFI_D_ERROR, "Get Card Info FAILED. %x\n\n\n", rc));
      return EFI_DEVICE_ERROR;
   }
   card_info->rpmb_size_in_byte = info.qLogicalBlockCount * 256;
   card_info->reliable_write_count = info.bRPMB_ReadWriteSize;

   return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UFSGetCardInfo (
            EFI_MEM_CARDINFO_PROTOCOL   *This,
            MEM_CARD_INFO               *card_info)
{
  EFI_STATUS Status;

  AcquireLock (UfsLockPtr);
  Status = UFSGetCardInfoInternal (This, card_info);
  ReleaseLock (UfsLockPtr);

  return Status;
}


/**
   This function retrieves Read Counter Response packet from flash device.
   The Response packet includes the Write Counter as well as the MAC which
   is used later to validate the Response packet

   @param  RespPktBuffer [OUT]    Pointer to the response from the Read
                                  Counter command

   @retval  RPMB_NO_ERROR           Successfully read the Counter packet.
   @retval  RPMB_ERR_INVALID_PARAM  NULL pointer is passed in to the function.
   @retval  RPMB_ERR_READ           Failed to read the Counter packet.
**/
INT32 EFIAPI RPMBReadCounterPkt (
            EFI_SDCC_RPMB_PROTOCOL       *This,
            UINT32                       *RespPktBuffer)
{
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   INT32  rc = 0;

   if ((NULL == This) || (NULL == RespPktBuffer)) {
      return RPMB_ERR_INVALID_PARAM;
   }

   UfsDevice = UFS_DEV_FROM_RPMB (This);
   hUFS = UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return RPMB_ERR_INVALID_PARAM;
   }

   AcquireLock (UfsLockPtr);
   rc = ufs_rpmb_read_cnt_pkt(hUFS, (UINT8 *)RespPktBuffer);
   ReleaseLock (UfsLockPtr);

   if (UFS_EOK != rc) {
      return RPMB_ERR_READ;
   }
   return RPMB_NO_ERROR;
}

/**
 This function programs the RPMB's key using the provided packet
 formatted as ProvisionKey command.

 @param CmdPktBuffer  [IN] : Pointer to a ProvisionKey command packet
                             to be sent to RPMB to program its key
 @param RespPktBuffer [OUT]: Pointer to the response packet for the
                             ProvisionKey command

 @retval  RPMB_NO_ERROR            Successfully provision the RPMB's Key.
 @retval  RPMB_ERR_INVALID_PARAM   NULL pointer is passed in to the function.
 @retval  RPMB_ERR_GENERAL         Failed to provision the key (Key has been
                                   provisioned).
**/
INT32 EFIAPI RPMBProgProvisionKey (
            EFI_SDCC_RPMB_PROTOCOL       *This,
            UINT32                       *CmdPktBuffer,
            UINT32                       *RespPktBuffer )
{
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS = NULL;
   INT32  rc = UFS_EOK;

   if ((NULL == CmdPktBuffer) || (NULL == RespPktBuffer) || (NULL == This)) {
      return RPMB_ERR_INVALID_PARAM;
   }

   UfsDevice = UFS_DEV_FROM_RPMB (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return RPMB_ERR_INVALID_PARAM;
   }

   AcquireLock (UfsLockPtr);
   rc = ufs_rpmb_write_blocks(hUFS, (UINT8 *)CmdPktBuffer,
                              1, (UINT8 *)RespPktBuffer);
   ReleaseLock (UfsLockPtr);

   if (UFS_EOK != rc) {
      return RPMB_ERR_GENERAL;
   }

   return RPMB_NO_ERROR;
}

/**
  This function reads the sectors from RPMB partition using the
  cmd packet buffers provided.

  @param   CmdPktBuffer  [IN] : Pointer to a formatted packet for Read Request
  @param   PktCount      [IN] : How many half sectors to read
  @param   DataBuffer    [OUT]: Pointer to data read from PRMB

  @retval  RPMB_NO_ERROR            Successfully read the Counter packet
  @retval  RPMB_ERR_INVALID_PARAM   NULL pointer is passed in to the function
  @retval  RPMB_ERR_READ            Failed to read the sectors

**/
INT32 EFIAPI RPMBReadBlocks (
            EFI_SDCC_RPMB_PROTOCOL       *This,
            UINT32                       *CmdPktBuffer,
            UINT32                       PktCount,
            UINT32                       *DataBuffer)
{
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   INT32 rc = UFS_EOK;

   if ((NULL == CmdPktBuffer) || (NULL == DataBuffer) ||
       (NULL == This) || (PktCount == 0))
   {
      return RPMB_ERR_INVALID_PARAM;
   }

   if (PktCount > RPMB_MAX_BLOCK_TRANSFER_SIZE) {
      return RPMB_ERR_INVALID_PARAM;
   }

   UfsDevice = UFS_DEV_FROM_RPMB (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return RPMB_ERR_INVALID_PARAM;
   }

   AcquireLock (UfsLockPtr);
   rc = ufs_rpmb_read_blocks(hUFS, (UINT8 *)CmdPktBuffer,
                             PktCount, (UINT8 *)DataBuffer);
   ReleaseLock (UfsLockPtr);
   if (UFS_EOK != rc) {
      return RPMB_ERR_READ;
   }

   return RPMB_NO_ERROR;

}

/**
  This function writes the sectors to the RPMB partition using
  the provided cmd packet buffers

  @param  CmdPktBuffer  [IN] :  Pointer to a formatted packets to be sent
                                to PRMB to write to RPMB partition
  @param  PktCount      [IN] :  Number of half sectors to write
  @param  RespPktBuffer [OUT]:  Pointer to the response packet from PRMB

  @retval  RPMB_NO_ERROR            Successfully Write the RPMB sectors.
                                    Caller should authenticate the Response
                                    packet and validate the Write Counter
  @retval  RPMB_ERR_INVALID_PARAM   NULL pointer is passed in to the function
  @retval  RPMB_ERR_WRITE           Failed to write the sectors
**/
INT32 EFIAPI RPMBWriteBlocks (
            EFI_SDCC_RPMB_PROTOCOL       *This,
            UINT32                       *CmdPktBuffer,
            UINT32                       PktCount,
            UINT32                       *RespPktBuffer )
{
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS = NULL;
   INT32  rc = UFS_EOK;

   if ((NULL == CmdPktBuffer) || (NULL == RespPktBuffer) ||
      (NULL == This) || (PktCount == 0))
   {
      return RPMB_ERR_INVALID_PARAM;
   }

   if (PktCount > RPMB_MAX_BLOCK_TRANSFER_SIZE) {
      return RPMB_ERR_INVALID_PARAM;
   }

   UfsDevice = UFS_DEV_FROM_RPMB (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return RPMB_ERR_INVALID_PARAM;
   }

   AcquireLock (UfsLockPtr);
   rc = ufs_rpmb_write_blocks(hUFS, (UINT8 *)CmdPktBuffer,
                              PktCount, (UINT8 *)RespPktBuffer);
   ReleaseLock (UfsLockPtr);

   if (UFS_EOK != rc) {
      return RPMB_ERR_WRITE;
   }

   return RPMB_NO_ERROR;
}

/* Block IO2 supporting functions */

/**
   A wrapper for Block IO and Block IO 2. whether Block IO or Block IO 2 protocol
   will be used depending on caller and device status.

   @param  This       Indicates a pointer to the calling context.
   @param  MediaId    Id of the media, changes every time the media is replaced.
   @param  Lba        The starting Logical Block Address to read from
   @param  Token    A pointer to the token associated with the transaction.
   @param  BufferSize Size of Buffer, must be a multiple of device block size.
   @param  Buffer     A pointer to the destination buffer for the data.
                      The caller is responsible for either having implicit or
                      explicit ownership of the buffer.
   @param  CryptoIndex   A pointer to the configuration table index. 
   @param  CryptoIvInput A pointer to a buffer that contains 
                         additional cryptographic parameters as
                         required.

   @retval EFI_SUCCESS           The data was read correctly from the device.
   @retval EFI_DEVICE_ERROR      The device reported an error while
                                 performing the read.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHANGED     The MediaId does not matched the
                                 current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block
                                 size of the device.
   @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not
                                 valid,or the buffer is not on proper alignment.
**/
EFI_STATUS UFSIoWrapper (
            IN VOID                     *pThis,
            IN UINT32                    MediaId,
            IN UINT32                    TransferType,
            IN EFI_LBA                   Lba,
            IN OUT VOID                 *Token,
            IN UINT64                    BufferSize,
            IN OUT VOID                 *Buffer, 
            IN UINT64                   *CryptoIndex, 
            IN VOID                     *CryptoIvInput)
{
   EFI_STATUS        Status = EFI_SUCCESS;
   UFS_DEV           *UfsDevice;
   UINT32            block_size = 0;
   BLKIO2_REQ_LIST  *pReqList = &gUfsReqList;
   UINT32            i = 0; 
   REQ_ENTRY        *pReq; 

   if ((TransferType == BLOCKIO_READ) || (TransferType == BLOCKIO_WRITE))
   {
      // Cancel timer for Block IO
      if (gUfsTransferInfo.TimerSet == TRUE) {
         gBS->SetTimer (gUfsBlkIo2TimerEvent, TimerCancel, 0);
      }

      // If there are still unfilled entries in the request list, 
      // we can go ahead with the BlkIo transfer. Otherwise, we need to 
      // wait until an entry gets completed
      if (pReqList->FilledEntries != REQ_LIST_SIZE)
      {
         if (TransferType == BLOCKIO_READ) 
         {
           Status = UFSReadBlocks(pThis, MediaId, Lba, BufferSize, Buffer, CryptoIndex, CryptoIvInput);
         }
         else
         {
           Status = UFSWriteBlocks(pThis, MediaId, Lba, BufferSize, Buffer, CryptoIndex, CryptoIvInput);
         }
      }
      else
      {
         Status = BlkIoSlotFullHandler(pThis, TransferType, Lba, BufferSize, Buffer, CryptoIndex, CryptoIvInput); 
      }

      // Set the timer again if necessary
      if (TRUE  == gUfsTransferInfo.TimerSet) {
         gBS->SetTimer (gUfsBlkIo2TimerEvent, TimerPeriodic, BLKIO2_POLL_PERIOD);
      }
   }
   // If caller calls Block IO 2
   else
   {
      EFI_EVENT TokenEvent; 
      EFI_BLOCK_IO_MEDIA *Media; 
      EFI_BLOCK_IO2_PROTOCOL *This = pThis;
      EFI_BLOCK_IO2_TOKEN *BlkIo2Token = Token; 

      // Validate passed-in pointers are not NULL
      if ((NULL == Buffer) || (NULL == This) || (NULL == This->Media) ||
          (NULL == BlkIo2Token) || (NULL == BlkIo2Token->Event))  {
         Status = EFI_INVALID_PARAMETER;
         goto WrapperExit;
      }

      if ((NULL != CryptoIndex) && (NULL != CryptoIvInput)) {
         TokenEvent = ((EFI_BLOCK_IO_CRYPTO_TOKEN *)Token)->Event; 
         Media = ((EFI_BLOCK_IO_CRYPTO_PROTOCOL *)pThis)->Media;
         UfsDevice = UFS_DEV_FROM_BLOCKIO_CRYPTO (pThis); 
      }
      else {
         TokenEvent = ((EFI_BLOCK_IO2_TOKEN *)Token)->Event; 
         Media = ((EFI_BLOCK_IO2_PROTOCOL *)pThis)->Media;
         UfsDevice = UFS_DEV_FROM_BLOCKIO2 (pThis);
      }

      if ((NULL == Media) || (NULL == TokenEvent)) {
         Status = EFI_INVALID_PARAMETER;
         goto WrapperExit;
      }

      // Validate if buffer is multiple of block size
      if ((BufferSize%(Media->BlockSize) != 0) || (BufferSize == 0)) {
         Status = EFI_BAD_BUFFER_SIZE;
         goto WrapperExit;
      }

      // Validate block size and access range
      if ((Lba > Media->LastBlock) || (Media->BlockSize == 0)) {
         Status = EFI_INVALID_PARAMETER;
         goto WrapperExit;
      }

      if (Media->MediaId != MediaId) {
         Status = EFI_MEDIA_CHANGED;
         goto WrapperExit;
      }

      block_size = Media->BlockSize;

      if ((Lba + (BufferSize/block_size)) > (Media->LastBlock + 1)) {
         Status = EFI_INVALID_PARAMETER;
         goto WrapperExit;
      }

      // Add request to the queue, if space is available
      EfiAcquireLock (&pReqList->ReqListLock);

      if (pReqList->FilledEntries == REQ_LIST_SIZE) {
         Status = EFI_OUT_OF_RESOURCES;
         EfiReleaseLock (&pReqList->ReqListLock);
         goto WrapperExit;
      }

      for (i = 0; i < REQ_LIST_SIZE; i++) {
         pReq = pReqList->Entries + i; 
         if (pReq->This == NULL) {
            SetMem(pReq, sizeof(REQ_ENTRY), 0);
            pReq->This = pThis; 
            pReq->Token = Token; 
            pReq->Lba = Lba; 
            pReq->BufferSize = BufferSize; 
            pReq->Buffer = Buffer; 
            pReq->Type = TransferType;
            pReq->Index = CryptoIndex; 
            pReq->CryptoIvInput = CryptoIvInput;
            pReqList->FilledEntries++; 
            break;
         }
      }

      EfiReleaseLock (&pReqList->ReqListLock);

      // Set timer if not set
      if (gUfsTransferInfo.TimerSet == FALSE)
      {
         gUfsTransferInfo.TimerSet = TRUE;
         gBS->SetTimer (gUfsBlkIo2TimerEvent, TimerPeriodic, BLKIO2_POLL_PERIOD);
      }
   }

WrapperExit:
   return Status;
}

/**
   Read BufferSize bytes from Lba into Buffer.

   @param  This       Indicates a pointer to the calling context.
   @param  MediaId    Id of the media, changes every time the media is replaced.
   @param  Lba        The starting Logical Block Address to read from
   @param  BufferSize Size of Buffer, must be a multiple of device block size.
   @param  Buffer     A pointer to the destination buffer for the data.
                      The caller is responsible for either having implicit or
                      explicit ownership of the buffer.

   @retval EFI_SUCCESS           The data was read correctly from the device.
   @retval EFI_DEVICE_ERROR      The device reported an error while
                                 performing the read.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHANGED     The MediaId does not matched the
                                 current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block
                                 size of the device.
   @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not
                                 valid,or the buffer is not on proper alignment.
**/
EFI_STATUS UFSReadBlocksWrapper (
            IN EFI_BLOCK_IO_PROTOCOL  *This,
            IN UINT32                  MediaId,
            IN EFI_LBA                 Lba,
            IN UINTN                   BufferSize,
            OUT VOID                  *Buffer)
{
   EFI_STATUS Status = EFI_UNSUPPORTED;

   // UFS accesses has NOTIFY priority
   EFI_TPL PrevTPL;
   PrevTPL = gBS->RaiseTPL (UFS_TPL);

   AcquireLock (UfsLockPtr);
   Status = UFSIoWrapper (This, MediaId, BLOCKIO_READ, Lba, NULL, BufferSize, Buffer, NULL, NULL);
   ReleaseLock (UfsLockPtr);

   gBS->RestoreTPL (PrevTPL);

   return Status;
}

/**
   Write BufferSize bytes from Buffer to Lba.

   @param  This       Indicates a pointer to the calling context.
   @param  MediaId    The media ID that the write request is for.
   @param  Lba        The starting logical block address to be
                      written. The   caller is responsible for
                      writing to only legitimate locations.
   @param  BufferSize Size of Buffer, must be a multiple of device block size.
   @param  Buffer     A pointer to the source buffer for the data.

   @retval EFI_SUCCESS           The data was written correctly to the device.
   @retval EFI_WRITE_PROTECTED   The device can not be written to.
   @retval EFI_DEVICE_ERROR      The device reported an error
                                 while performing the write.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHNAGED     The MediaId does not matched
                                 the current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple
                                 of the block size of the device.
   @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not
                                 valid or the buffer is not on proper
                                 alignment.
**/
EFI_STATUS UFSWriteBlocksWrapper (
            IN EFI_BLOCK_IO_PROTOCOL   *This,
            IN UINT32                  MediaId,
            IN EFI_LBA                 Lba,
            IN UINTN                   BufferSize,
            IN VOID                    *Buffer)
{
   EFI_STATUS Status = EFI_UNSUPPORTED;

   // UFS accesses has NOTIFY priority
   EFI_TPL PrevTPL;
   PrevTPL = gBS->RaiseTPL (UFS_TPL);

   AcquireLock (UfsLockPtr);
   Status = UFSIoWrapper(This, MediaId, BLOCKIO_WRITE,Lba, NULL, BufferSize, Buffer, NULL, NULL);
   ReleaseLock (UfsLockPtr);

   gBS->RestoreTPL (PrevTPL);

   return Status;
}

/**
   Read BufferSize bytes from Lba into Buffer and optionally decrypts them inline. 

   @param  This          Indicates a pointer to the calling context.
   @param  MediaId       Id of the media, changes every time the media is replaced.
   @param  Lba           The starting Logical Block Address to read from
   @param  Token         A pointer to the token associated with the transaction.
   @param  BufferSize    Size of Buffer, must be a multiple of device block size.
   @param  Buffer        A pointer to the destination buffer for the data.
                         The caller is responsible for either having implicit or
                         explicit ownership of the buffer.
   @param  Index         A pointer to the configuration table index. 
   @param  CryptoIvInput A pointer to a buffer that contains additional cryptographic    
                         parameters as required. 

   @retval EFI_SUCCESS           The data was read correctly from the device.
   @retval EFI_DEVICE_ERROR      The device reported an error while
                                 performing the read.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHANGED     The MediaId does not matched the
                                 current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block
                                 size of the device.
   @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not
                                 valid,or the buffer is not on proper alignment.
**/
EFI_STATUS UFSCryptoReadEx (
            IN EFI_BLOCK_IO_CRYPTO_PROTOCOL  *This,
            IN UINT32                        MediaId,
            IN EFI_LBA                       Lba,
            IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token, 
            IN UINT64                        BufferSize,
            OUT VOID                         *Buffer, 
            IN UINT64                        *Index, 
            IN VOID                          *CryptoIvInput)
{
   EFI_STATUS Status = EFI_UNSUPPORTED;

   // UFS accesses has NOTIFY priority
   EFI_TPL PrevTPL;
   PrevTPL = gBS->RaiseTPL (UFS_TPL);

   AcquireLock (UfsLockPtr);
   if ((Token != NULL) && (Token->Event != NULL))
   {
     Status = UFSIoWrapper (This, MediaId, BLOCKIO2_READ, Lba, Token, BufferSize, Buffer, Index, CryptoIvInput);
   }
   else
   {
     Status = UFSIoWrapper (This, MediaId, BLOCKIO_READ, Lba, Token, BufferSize, Buffer, Index, CryptoIvInput);
   }
   
   ReleaseLock (UfsLockPtr);

   gBS->RestoreTPL (PrevTPL);

   return Status;
}

/**
   Write BufferSize bytes from Buffer to Lba and optionally 
   encrypts the data inline

   @param  This          Indicates a pointer to the calling context.
   @param  MediaId       The media ID that the write request is for.
   @param  Lba           The starting logical block address to be
                         written. The caller is responsible for
                         writing to only legitimate locations.
   @param  Token         A pointer to the token associated with the transaction. 						 
   @param  BufferSize    Size of Buffer, must be a multiple of device block size.
   @param  Buffer        A pointer to the source buffer for the data.
   @param  Index         A pointer to the configuration table index. 
   @param  CryptoIvInput A pointer to a buffer that contains additional cryptographic
                         parameters as required. 

   @retval EFI_SUCCESS           The data was written correctly to the device.
   @retval EFI_WRITE_PROTECTED   The device can not be written to.
   @retval EFI_DEVICE_ERROR      The device reported an error
                                 while performing the write.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHNAGED     The MediaId does not matched
                                 the current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple
                                 of the block size of the device.
   @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not
                                 valid or the buffer is not on proper
                                 alignment.
**/
EFI_STATUS UFSCryptoWriteEx (
            IN EFI_BLOCK_IO_CRYPTO_PROTOCOL  *This,
            IN UINT32                        MediaId,
            IN EFI_LBA                       Lba,
            IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token, 
            IN UINT64                        BufferSize,
            IN VOID                          *Buffer, 
            IN UINT64                        *Index,
            IN VOID                          *CryptoIvInput)
{
   EFI_STATUS Status = EFI_UNSUPPORTED;

   // UFS accesses has NOTIFY priority
   EFI_TPL PrevTPL;
   PrevTPL = gBS->RaiseTPL (UFS_TPL);

   AcquireLock (UfsLockPtr);
   if ((Token != NULL) && (Token->Event != NULL))
   {
     Status = UFSIoWrapper(This, MediaId, BLOCKIO2_WRITE, Lba, Token, BufferSize, Buffer, Index, CryptoIvInput);
   }
   else
   {
     Status = UFSIoWrapper(This, MediaId, BLOCKIO_WRITE, Lba, Token, BufferSize, Buffer, Index, CryptoIvInput);
   }
   
   ReleaseLock (UfsLockPtr);

   gBS->RestoreTPL (PrevTPL);

   return Status;
}

/**
  Read BufferSize bytes from Lba into Buffer.

  This function reads the requested number of blocks from the device. All the
  blocks are read, or an error is returned.
  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_or EFI_MEDIA_CHANGED is returned and
  non-blocking I/O is being used, the Event associated with this request will
  not be signaled.

  @param[in]       This       Indicates a pointer to the calling context.
  @param[in]       MediaId    Id of the media, changes every time the media is
                              replaced.
  @param[in]       Lba        The starting Logical Block Address to read from.
  @param[in, out]  Token       A pointer to the token associated with the transaction.
  @param[in]       BufferSize Size of Buffer, must be a multiple of device block size.
  @param[out]      Buffer     A pointer to the destination buffer for the data. The
                              caller is responsible for either having implicit or
                              explicit ownership of the buffer.

  @retval EFI_SUCCESS           The read request was queued if Token->Event is
                                not NULL.The data was read correctly from the
                                device if the Token->Event is NULL.
  @retval EFI_DEVICE_ERROR      The device reported an error while performing
                                the read.
  @retval EFI_NO_MEDIA          There is no media in the device.
  @retval EFI_MEDIA_CHANGED     The MediaId is not for the current media.
  @retval EFI_BAD_BUFFER_SIZE   The BufferSize parameter is not a multiple of the
                                intrinsic block size of the device.
  @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not valid,
                                or the buffer is not on proper alignment.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed due to a lack
                                of resources.
**/
EFI_STATUS UFSReadBlocksEx (
            IN     EFI_BLOCK_IO2_PROTOCOL *This,
            IN     UINT32                 MediaId,
            IN     EFI_LBA                Lba,
            IN OUT EFI_BLOCK_IO2_TOKEN    *Token,
            IN     UINTN                  BufferSize,
            OUT VOID                      *Buffer)
{
   EFI_STATUS Status = EFI_UNSUPPORTED;

   /* UFS accesses has NOTIFY priority */
   EFI_TPL PrevTPL;
   PrevTPL = gBS->RaiseTPL(UFS_TPL);
   AcquireLock (UfsLockPtr);

   /* Do not use Block IO 2 if not initialized succesfully */
   if (gUfsTransferInfo.BlkIO2Initialized == FALSE)
   {
      Status = EFI_OUT_OF_RESOURCES;
      goto ReadBlocksExExit;
   }

   Status = UFSIoWrapper(This, MediaId, BLOCKIO2_READ, Lba, Token, BufferSize, Buffer, NULL, NULL);

ReadBlocksExExit:
   ReleaseLock (UfsLockPtr);
   gBS->RestoreTPL (PrevTPL);

   return Status;
}

/**
  Write BufferSize bytes from Buffer to Lba.

  This function writes the requested number of blocks to the device. All blocks
  are written, or an error is returned.If EFI_DEVICE_ERROR, EFI_NO_MEDIA,
  EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED is returned and non-blocking I/O is
  being used, the Event associated with this request will not be signaled.

  @param[in]       This       Indicates a pointer to the calling context.
  @param[in]       MediaId    The media ID that the write request is for.
  @param[in]       Lba        The starting logical block address to be written. The
                              caller is responsible for writing to only legitimate
                              locations.
  @param[in, out]  Token      A pointer to the token associated with the transaction.
  @param[in]       BufferSize Size of Buffer, must be a multiple of device block size.
  @param[in]       Buffer     A pointer to the source buffer for the data.

  @retval EFI_SUCCESS           The write request was queued if Event is not NULL.
                                The data was written correctly to the device if
                                the Event is NULL.
  @retval EFI_WRITE_PROTECTED   The device can not be written to.
  @retval EFI_NO_MEDIA          There is no media in the device.
  @retval EFI_MEDIA_CHNAGED     The MediaId does not matched the current device.
  @retval EFI_DEVICE_ERROR      The device reported an error while performing the write.
  @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block size of the device.
  @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not valid,
                                or the buffer is not on proper alignment.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed due to a lack
                                of resources.

**/
EFI_STATUS UFSWriteBlocksEx (
            IN     EFI_BLOCK_IO2_PROTOCOL *This,
            IN     UINT32                 MediaId,
            IN     EFI_LBA                Lba,
            IN OUT EFI_BLOCK_IO2_TOKEN    *Token,
            IN     UINTN                  BufferSize,
            OUT VOID                      *Buffer)
{
   EFI_STATUS Status = EFI_UNSUPPORTED;

   EFI_TPL PrevTPL;
   PrevTPL = gBS->RaiseTPL(UFS_TPL);
   AcquireLock (UfsLockPtr);

   /* Do not use Block IO 2 if not initialized succesfully */
   if (gUfsTransferInfo.BlkIO2Initialized == FALSE)
   {
      Status = EFI_OUT_OF_RESOURCES;
      goto WriteBlocksExExit;
   }
   Status = UFSIoWrapper(This, MediaId, BLOCKIO2_WRITE, Lba, Token, BufferSize, Buffer, NULL, NULL);

WriteBlocksExExit:
   ReleaseLock (UfsLockPtr);
   gBS->RestoreTPL (PrevTPL);

   return Status;
}

/**
  Reset the block device hardware.

  @param[in]  This                 Indicates a pointer to the calling context.
  @param[in]  ExtendedVerification Indicates that the driver may perform a more
                                   exhausive verfication operation of the device
                                   during reset.

  @retval EFI_SUCCESS          The device was reset.
  @retval EFI_DEVICE_ERROR     The device is not functioning properly and could
                               not be reset.
**/
EFI_STATUS EFIAPI UFSResetEx (
            IN EFI_BLOCK_IO2_PROTOCOL  *This,
            IN BOOLEAN                 ExtendedVerification)
{
   return EFI_SUCCESS;
}

/**
  Flush the Block Device.

  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned and non-blocking I/O is being used, the Event associated with
  this request will not be signaled.

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UFSFlushBlocksEx (
            IN     EFI_BLOCK_IO2_PROTOCOL   *This,
            IN OUT EFI_BLOCK_IO2_TOKEN      *Token)
{
   EFI_STATUS Status = EFI_SUCCESS;
   INT32  rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;

   /* Validate passed-in pointers are not NULL */
   if (NULL == This) {
      return EFI_INVALID_PARAMETER;
   }

   UfsDevice = UFS_DEV_FROM_BLOCKIO2 (This);
   hUFS = UfsDevice->DeviceHandle;

   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   /* Use LBA = 0 and Blocks = 0 to sync the entire LUN */
   rc = ufs_sync_cache (hUFS, 0, 0); 
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "UFSFlushBlocksEx with return value of %d\n", rc));
      Status = EFI_DEVICE_ERROR;
   }

   if (Token != NULL) {
      Token->TransactionStatus = Status; 
      gBS->SignalEvent(Token->Event); 
   }

   return Status; 
}


/**
  Erase blocks in the Block Device

  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned and non-blocking I/O is being used, the Event associated with
  this request will not be signaled.

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UFSEraseBlocks (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN     UINT32 MediaId,
   IN     EFI_LBA LBA,
   IN OUT EFI_ERASE_BLOCK_TOKEN *Token,
   IN     UINTN Size
   )
{
   INT32  rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   UINT32 blocks;
   EFI_STATUS Status = EFI_SUCCESS;

   /* Validate passed-in size are not zero */
   if (0 == Size) {
      return EFI_INVALID_PARAMETER;
   }

   /* Validate if size is multiple of block size */
   if ((Size%(This->Media->BlockSize)) != 0 ) {
      return EFI_INVALID_PARAMETER;
   }

   /* Validate block size and access range */
   if ((LBA > This->Media->LastBlock) || (This->Media->BlockSize == 0)) {
      return EFI_INVALID_PARAMETER;
   }

   if (This->Media->MediaId != MediaId) {
      return EFI_MEDIA_CHANGED;
   }

   gUfsCurrentErase = This;
   UfsDevice = UFS_DEV_FROM_BLOCKIO (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* Check if LBA plus the total sectors trying to erase would exceed the */
   /* total size of the partition */
   if ((LBA + (Size/This->Media->BlockSize)) > (UfsDevice->BlkIo.Media->LastBlock + 1)) {
      return EFI_INVALID_PARAMETER;
   }

   blocks = Size/(This->Media->BlockSize);


   AcquireLock (UfsLockPtr);

   rc = ufs_unmap (hUFS, LBA, blocks);
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "UFS UNMAP with return value of %d\n", rc));
      Status = EFI_DEVICE_ERROR;
      goto ReleaseLockExit ;
   }

   /* Setup non-block purge sequence if purge event is initialized */
   if (gUfsTransferInfo.PurgeEventInitialized && Token != NULL) {
      rc = ufs_purge_nonblock_setup (hUFS);
      if (rc == -UFS_EBUSY) {
         // Device in busy, continue the non-blocking wait
      }
      else if (rc == UFS_EOK) {
         // Device is out of busy already, no need to wait
         if (Token != NULL) {
            gUfsTransferInfo.EraseToken = NULL;
            Token->TransactionStatus = EFI_SUCCESS;
         }
         Status = EFI_SUCCESS;
         goto ReleaseLockExit ;
      }
      else {
         DEBUG ((EFI_D_WARN, "UFS non-blocking purge setup failed with value of %d\n", rc));
      }
   }

   rc = ufs_purge_and_wait (hUFS);
   if (rc == -UFS_EBUSY) {
      /* Pending transfer is taking place, setting up a timer */
      ReleaseLock (UfsLockPtr);
      gBS->SetTimer (gUfsPurgeTimerEvent, TimerPeriodic, BLKIO2_POLL_PERIOD);
      if (Token != NULL) {
         gUfsTransferInfo.EraseToken = Token;
         Status = gBS->CreateEvent (EVT_TIMER,
                                    TPL_APPLICATION,
                                    NULL,
                                    NULL,
                                    &Token->Event );
         ASSERT_EFI_ERROR (Status);
         Token->TransactionStatus = EFI_SUCCESS;
      }
      return EFI_SUCCESS;
   }
   else if (rc != UFS_EOK) {
      DEBUG ((EFI_D_ERROR, "UFS purge with return value of %d\n", rc));
      if (Token != NULL) {
         Token->Event = NULL;
         Token->TransactionStatus = EFI_DEVICE_ERROR;
      }
      Status = EFI_DEVICE_ERROR;
      goto ReleaseLockExit ;
   }

   /* Purge completed, set the token to NULL */
   if (Token != NULL) {
      Token->Event = NULL;
      Token->TransactionStatus = EFI_SUCCESS;
   }

ReleaseLockExit:
  ReleaseLock (UfsLockPtr);

  return Status;
}

#ifdef FEATURE_XBOOT
/**
  Erase blocks in the Block Device

  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned, the Event associated with
  this request will not be signaled.

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UfsNonSecureEraseBlocksInternal (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN     UINT32 MediaId,
   IN     EFI_LBA LBA,
   IN     UINTN Size
   )
{
   INT32  rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   UINT32 blocks;

   /* Validate passed-in size are not zero */
   if (0 == Size) {
      return EFI_INVALID_PARAMETER;
   }

   /* Validate if size is multiple of block size */
   if ((Size%(This->Media->BlockSize)) != 0 ) {
      return EFI_INVALID_PARAMETER;
   }

   /* Validate block size and access range */
   if ((LBA > This->Media->LastBlock) || (This->Media->BlockSize == 0)) {
      return EFI_INVALID_PARAMETER;
   }

   if (This->Media->MediaId != MediaId) {
      return EFI_MEDIA_CHANGED;
   }

   gUfsCurrentErase = This;
   UfsDevice = UFS_DEV_FROM_BLOCKIO (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* Check if LBA plus the total sectors trying to erase would exceed the */
   /* total size of the partition */
   if ((LBA + (Size/This->Media->BlockSize)) > (UfsDevice->BlkIo.Media->LastBlock + 1)) {
      return EFI_INVALID_PARAMETER;
   }

   blocks = Size/(This->Media->BlockSize);

   rc = ufs_unmap (hUFS, LBA, blocks);
   if (UFS_EOK != rc) {
      DEBUG ((EFI_D_ERROR, "UFS UNMAP with return value of %d\n", rc));
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UfsNonSecureEraseBlocks (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN     UINT32 MediaId,
   IN     EFI_LBA LBA,
   IN     UINTN Size
   )
{
   EFI_STATUS Status;

   AcquireLock (UfsLockPtr);
   Status = UfsNonSecureEraseBlocksInternal (This, MediaId, LBA, Size);
   ReleaseLock (UfsLockPtr);

   return Status;
}

/**
  Purge blocks in the Block Device

  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned and non-blocking I/O is being used, the Event associated with
  this request will not be signaled.

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UfsPurgeBlocksInternal (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN OUT EFI_ERASE_BLOCK_TOKEN *Token
   )
{
   INT32  rc;
   UFS_DEV    *UfsDevice;
   struct ufs_handle *hUFS;
   EFI_STATUS Status;

   gUfsCurrentErase = This;
   UfsDevice = UFS_DEV_FROM_BLOCKIO (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   /* Setup non-block purge sequence if purge event is initialized */
   if (gUfsTransferInfo.PurgeEventInitialized && Token != NULL) {
      rc = ufs_purge_nonblock_setup (hUFS);
      if (rc == -UFS_EBUSY) {
         // Device in busy, continue the non-blocking wait
      }
      else if (rc == UFS_EOK) {
         // Device is out of busy already, no need to wait
         if (Token != NULL) {
            gUfsTransferInfo.EraseToken = NULL;
            Token->TransactionStatus = EFI_SUCCESS;
         }
         return EFI_SUCCESS;
      }
      else {
         DEBUG ((EFI_D_WARN, "UFS non-blocking purge setup failed with value of %d\n", rc));
      }
   }

   rc = ufs_purge_and_wait (hUFS);
   if (rc == -UFS_EBUSY) {
      /* Pending transfer is taking place, setting up a timer */
      gBS->SetTimer (gUfsPurgeTimerEvent, TimerPeriodic, BLKIO2_POLL_PERIOD);
      if (Token != NULL) {
         gUfsTransferInfo.EraseToken = Token;
         Status = gBS->CreateEvent (EVT_TIMER,
                                    TPL_APPLICATION,
                                    NULL,
                                    NULL,
                                    &Token->Event );
         ASSERT_EFI_ERROR (Status);
         Token->TransactionStatus = EFI_SUCCESS;
      }
      return EFI_SUCCESS;
   }
   else if (rc != UFS_EOK) {
      DEBUG ((EFI_D_ERROR, "UFS purge with return value of %d\n", rc));
      if (Token != NULL) {
         Token->Event = NULL;
         Token->TransactionStatus = EFI_DEVICE_ERROR;
      }
      return EFI_DEVICE_ERROR;
   }

   /* Purge completed, set the token to NULL */
   if (Token != NULL) {
      Token->Event = NULL;
      Token->TransactionStatus = EFI_SUCCESS;
   }

   return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UfsPurgeBlocks (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN OUT EFI_ERASE_BLOCK_TOKEN *Token
   )
{
   EFI_STATUS Status;

   AcquireLock (UfsLockPtr);
   Status = UfsPurgeBlocksInternal (This, Token);
   ReleaseLock (UfsLockPtr);

   return Status;
}
#endif /* FEATURE_XBOOT */

/******************************************************************************
*  Handle the timer event for purge
*
* Arguments:
*    Event              [IN] : UEFI event method, not used
*    Context            [IN] : Can be any forms of input parameter, not used
******************************************************************************/
VOID PurgeTimerEventNotify (
                     IN  EFI_EVENT  Event,
                     IN  VOID      *Context)
{
   INT32 rc = -UFS_ENOENT;
   EFI_ERASE_BLOCK_TOKEN  *temp_token;
   UFS_DEV                *UfsDevice;
   struct ufs_handle      *hUFS;

   UfsDevice = UFS_DEV_FROM_BLOCKIO (gUfsCurrentErase);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;
   AcquireLock (UfsLockPtr);
   rc = ufs_purge_and_wait (hUFS);
   ReleaseLock (UfsLockPtr);

   if (rc == UFS_EOK) {
      gBS->SetTimer (gUfsPurgeTimerEvent, TimerCancel, 0);
      temp_token = gUfsTransferInfo.EraseToken;
      gBS->SignalEvent(temp_token->Event);
      return;
   }
   if (rc == -UFS_EBUSY) {
      /* Still busy, wait more */
      return;
   }
   else {
      DEBUG ((EFI_D_ERROR, "UFS purge with return value of %d\n", rc));
      return;
   }

   return;
}

#ifdef FEATURE_XBOOT
EFI_STATUS EFIAPI UfsGetDeviceDescriptor (
            IN EFI_MEM_CARDINFO_PROTOCOL   *This,
            OUT UINT8 *DeviceDescriptor,
            IN UINT32 Size)
{
   INT32 rc = -UFS_ENOENT;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   AcquireLock(UfsLockPtr);
   UfsDevice = UFS_DEV_FROM_CARD_INFO(This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;
   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   rc = ufs_get_descriptor_device_raw_data(
     hUFS, (char *)DeviceDescriptor, Size);
   ReleaseLock(UfsLockPtr);

   if (UFS_EOK != rc) {
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UfsGetUnitDescriptor (
            IN EFI_MEM_CARDINFO_PROTOCOL   *This,
            IN UINT32 Lun,
            OUT UINT8 *UnitDescriptor,
            IN UINT32 Size)
{
   INT32 rc = -UFS_ENOENT;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   AcquireLock(UfsLockPtr);
   UfsDevice = UFS_DEV_FROM_CARD_INFO(This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;
   if (NULL == hUFS) {
      return EFI_INVALID_PARAMETER;
   }

   rc = ufs_get_descriptor_unit_raw_data(
     hUFS, Lun, (char *)UnitDescriptor, Size);
   ReleaseLock(UfsLockPtr);

   if (UFS_EOK != rc) {
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}
#endif /* FEATURE_XBOOT */

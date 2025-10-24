/** @file SPSSDxe.c

  Implements the Qualcomm's driver that loads SPSS

  Copyright (c) 2019 - 2022,  Qualcomm Technologies Inc. All 
  rights reserved. 

**/

/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     -----------------------------------------------------------
 07/31/22     nl      Fix: Init pEfiChipInfoProtocol before using it
 07/07/22     me      Update SPSS PIL loading address for Halliday per ipcat and 
                      Update chipFamily check to check for Halliday
 05/27/22     bxr     Change file coded format to be UTF-8
 04/07/22     ll      Update SPSS PIL loading address for Kailua per ipcat
 02/14/22     nl      Remove the WA, set SP_CNOC_SP_SCSR_RMB_GPm
 02/07/22     vp      Temporary WA, to avoid setting SP_CNOC_SP_SCSR_RMB_GPm
 02/05/22     nl      Fix a bug in reading SPSS configuration
 09/30/21     nl      Updates for Kailua support removing Waipio support
 06/29/21     av      Add support for 1.5MB image size
 06/29/21     sg      Add WA to consider SPSS config_mode b'11 as PROD type
 01/20/20     ll      Updates for Waipio support removing Lahaina support
 10/29/20     mm      Updated Lahaina power alarm GPIO as b7
 06/17/20     av      Write to a GP register if SPSS load attempt fails
 06/05/20     av      Replace chipID check with chipFamily,load 1t/p images on R2
 05/20/20     av      Update chipID check to include all Lahaina variants
 01/23/20     kv      Updates for Lahaina support
 06/21/19     as      Add IAR support
 06/18/19     av      Read SECURITY CONTROL CORE register for image type
 06/05/19     av      Initial revision - introduce driver that loads SPSS
 
=============================================================================*/
#include <Uefi.h>

/**
  EFI interfaces
 */
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomUtilsLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/QcomBaseLib.h>
#include <npa.h>

#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIChipInfoTypes.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIHWIO.h>

#include <Library/BaseMemoryLib.h>
#include <PrintShLib.h>
#include <HALhwio.h>
#include "HALbootHWIO.h"

/**
  EFI interfaces
 */

#include <Protocol/LoadedImage.h>
#include <Protocol/EFIPIL.h>
#include <Protocol/EFIHWIO.h>

/**
File Logging Dependencies
*/
#include "ULogFront.h"
#include "ULogUEFI.h"

extern EFI_STATUS spss_iar_main(PIL_SUBSYS_CFG_TYPE* spss_cfg);

/*===========================================================================*/
/*                  DEFINES                                                  */
/*===========================================================================*/
#define SPSS_MAX_CHIP_VER       3
#define SWAP_BYTES(x,y)  do {           \
                           UINT8 t;     \
                           t = (x);     \
                           (x) = (y);   \
                           (y) = t;     \
                         }while(0)
#define SPSS_CONFIG_PROD_VAL   0x0
#define SPSS_CONFIG_TEST_VAL   0x1
#define SPSS_CONFIG_MODE_FIELD  7
#define SPSS_CONFIG_MASK        0x00000003
#define MAX_PATH_LEN            128
#define SP_CNOC_SP_SCSR_BASE_ADDR        0x01880000
/* Register to write to incase SPSS load fails */
#define SP_CNOC_SP_SCSR_RMB_GPm(m)       (0x01881100 + (0x4*m))
/* Bit mask to be used to indicate SPSS load failure */
#define SP_SCSR_RMB_GP_LOAD_FAILURE_MASK 0x00000001
#define SP_SCSR_REGISTER_ACCESS_ERROR    0xDEADBEEF

#define SP_TME_FUSE_CONTROLLER_SW_RANGE5_OFFSET_ADDR 0x021C8214
#define SP_TME_FUSE_ACCESS_ERROR                     0xDEADBEEF
/*===========================================================================*/
/*                  GLOBAL VARIABLES                                         */
/*===========================================================================*/
STATIC UINT32* gpSPRegister = NULL;
STATIC UINT32*             gpFuse        = NULL; 


STATIC EFI_HWIO_PROTOCOL*  pHWIOProtocol = NULL;
/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/
STATIC EFI_STATUS SPSSDxe_PreLoadChecks( BOOLEAN *pIsChipVersionRelevant );
STATIC EFI_STATUS SPSSDxe_BuildLoadCfg( PIL_SUBSYS_CFG_TYPE* spss_cfg,
                                        BOOLEAN IsChipVersionRelevant );
STATIC EFI_STATUS SPSSDxe_LoadSPSS( PIL_SUBSYS_CFG_TYPE* spss_cfg );
STATIC VOID SPSSDxe_VotePMICResources ( VOID );
STATIC EFI_STATUS SPSSDxe_MapSPRegisters( VOID );
STATIC UINT32 SPSSDxe_ReadSPRegister( UINT32 addr );
STATIC UINT32 SPSSDxe_WriteSPRegister( UINT32 addr, UINT32 val );
STATIC EFI_STATUS SPSSDxe_MapFuse( VOID );
STATIC UINT32 SPSSDxe_ReadFuse( UINT32 addr );

/*===========================================================================*/
/*                  FUNCTIONS DEFINITIONS                                    */
/*===========================================================================*/
/**
  SPSSDxe_Entry ()

  @brief
  Initialize SPSS App
 */
EFI_STATUS SPSSDxe_Entry
(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
  EFI_STATUS                     Status   = EFI_LOAD_ERROR;
  PIL_SUBSYS_CFG_TYPE            spss_cfg = {};
  BOOLEAN                        IsChipVersionRelevant = TRUE;

  /* Ensure loading of SPSS in UEFI is supported */
  Status = SPSSDxe_PreLoadChecks(&IsChipVersionRelevant);
  if (Status != EFI_SUCCESS)
  {
    return Status;
  }

  /* Build the load configuration for SPSS based on the chip version
     and device type (test or production) */
  Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&pHWIOProtocol);

  if ((EFI_ERROR(Status)) || (pHWIOProtocol == NULL))
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a failed to get HWIO protocol, status [0x%x] \r\n", __FUNCTION__, Status ));
    return EFI_DEVICE_ERROR;
  }

  Status = SPSSDxe_BuildLoadCfg(&spss_cfg, IsChipVersionRelevant);
  if (EFI_SUCCESS == Status)
  {
    /* Now trigger PilDXE protocol to load SP subsystem */
    Status = SPSSDxe_LoadSPSS(&spss_cfg);
  }

  return Status;
}


/**
  SPSSDxe_ReadFuse ()

  @brief
  Reads a TME fuse where addr is the offset
 */
STATIC UINT32 SPSSDxe_ReadFuse(UINT32 addr)
{
  /* Set to default value */
  UINT32 val = SP_TME_FUSE_ACCESS_ERROR;

  if (gpFuse != NULL)
  {
    addr = addr + (UINT32)(uintptr_t) gpFuse;
    val = in_dword(addr);
  }

  return val;
}


/**
  SPSSDxe_MapFuse ()

  @brief
  Initializes maps TME region
 */
STATIC EFI_STATUS SPSSDxe_MapFuse(VOID)
{
  EFI_STATUS         Status = 0;

  if (pHWIOProtocol == NULL)
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a HWIO protocol is NULL \r\n", __FUNCTION__ ));
    return EFI_DEVICE_ERROR;
  }

  /* Map TME base address to read fuse */
  Status = pHWIOProtocol->MapRegion(pHWIOProtocol, "TMESS",
                                   (UINT8**)&(gpFuse));
  if ((Status != EFI_SUCCESS) || (gpFuse == NULL)) 
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a MapRegion() failed = %r \r\n", __FUNCTION__, Status ));
    return EFI_DEVICE_ERROR;
  }

  return Status;
}


/**
  SPSSDxe_ReadSPRegister ()

  @brief
  Reads a SP shared register
 */
STATIC UINT32 SPSSDxe_ReadSPRegister(UINT32 addr)
{
  UINT32 val = SP_SCSR_REGISTER_ACCESS_ERROR;

  if (gpSPRegister != NULL)
  {
    addr = ((addr - SP_CNOC_SP_SCSR_BASE_ADDR) + (UINT32)(uintptr_t) gpSPRegister);
    val = in_dword(addr);
  }

  return val;
}

/**
  SPSSDxe_WriteSPRegister ()

  @brief
  Writes to a SP shared register
 */
STATIC UINT32 SPSSDxe_WriteSPRegister(UINT32 addr, UINT32 val)
{
  UINT32 val_out = SP_SCSR_REGISTER_ACCESS_ERROR;

  if (gpSPRegister != NULL)
  {
    addr = ((addr - SP_CNOC_SP_SCSR_BASE_ADDR) + (UINT32)(uintptr_t) gpSPRegister);
    val_out = out_dword(addr, val);
  }

  return val_out;
}

/**
  SPSSDxe_MapSPRegisters ()

  @brief
  Initializes HWIOProtocol variable and maps SP region
 */
STATIC EFI_STATUS SPSSDxe_MapSPRegisters(VOID)
{
  EFI_STATUS         status = 0;

  /* Map SP shared registers */
  status = pHWIOProtocol->MapRegionByAddress(pHWIOProtocol, 
                                             (UINT8*) SP_CNOC_SP_SCSR_BASE_ADDR,
                                             (UINT8**) &gpSPRegister);
  if ((status != EFI_SUCCESS) || (gpSPRegister == NULL)) 
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a MapRegionByAddress() failed = %r \r\n", __FUNCTION__, status ));
    return EFI_DEVICE_ERROR;
  }

  return status;
}

/**
  SPSSDxe_PreLoadChecks ()

  @brief
  Perform pre loading checks in order to decide whether to
  move forward with SPSS loading
 */
STATIC EFI_STATUS SPSSDxe_PreLoadChecks( BOOLEAN *pIsChipVersionRelevant )
{
  EFI_STATUS             Status               = EFI_LOAD_ERROR;
  EFI_CHIPINFO_PROTOCOL *pEfiChipInfoProtocol = NULL;
  EFIChipInfoFamilyType  chipFamily           = EFICHIPINFO_NUM_FAMILIES;
  EFIChipInfoPartType    ePart                = EFICHIPINFO_PART_SPSS;
  UINT32                 defectiveMask        = 0;
  BOOLEAN                isChipInWhiteList    = FALSE;

  if (pIsChipVersionRelevant != NULL)
  {
	*pIsChipVersionRelevant = TRUE;
  }

  /* Make sure we load SPSS in UEFI for Kailua/Halliday */
  Status = gBS->LocateProtocol(&gEfiChipInfoProtocolGuid,NULL, (VOID**) &pEfiChipInfoProtocol);
  if (EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a gEfiChipInfoProtocolGuid protocol failed = %r \r\n", __FUNCTION__, Status ));
    return Status;
  }

  Status = pEfiChipInfoProtocol->GetChipFamily(pEfiChipInfoProtocol,&chipFamily);
  if ((EFI_SUCCESS != Status) || (chipFamily >= EFICHIPINFO_NUM_FAMILIES))
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a GetChipFamily failed = %r \r\n", __FUNCTION__, Status));
    return EFI_INVALID_PARAMETER;
  }

  if ((chipFamily == EFICHIPINFO_FAMILY_KAILUA) ||
      (chipFamily == EFICHIPINFO_FAMILY_HALLIDAY))
  {
    isChipInWhiteList = TRUE;
	/* For Kailua/Halliday, same SPSS image version (1t/1p) works for both V1 and V2/R2
	   SoC versions. MAKE SURE to revisit the chip version relevance for each
	   chipset. */
	if (pIsChipVersionRelevant != NULL)
	{
	  *pIsChipVersionRelevant = FALSE;
	}
  }

  if (!isChipInWhiteList)
  {
    /* SPSS shall not be loaded on this chipset */
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a SPSS loading in UEFI not supported for chipFamily = 0x%x \r\n", __FUNCTION__, chipFamily));
    return EFI_INVALID_PARAMETER;
  }

  Status = pEfiChipInfoProtocol->GetDefectivePart(pEfiChipInfoProtocol,ePart,&defectiveMask);
  if ((defectiveMask != 0) || (EFI_SUCCESS != Status))
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a Defective part detected - SPU image load failed-%r \r\n", __FUNCTION__, Status));
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

/* Convert Byte Stream data to GUID format.
 * For example:
 * if Cfg has data in below format:
 *    DEA0BA2C CBDD 4805 B4F9 F428251C3E98
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
  SPSSDxe_BuildLoadCfg ()

  @brief
  Build the load configuration for SPSS based on the chip
  version and device type (test or production)
 */
STATIC EFI_STATUS SPSSDxe_BuildLoadCfg( PIL_SUBSYS_CFG_TYPE* spss_cfg,
                                        BOOLEAN IsChipVersionRelevant )
{
  EFI_STATUS             Status               = EFI_SUCCESS;
  CHAR8                 *PartGuidStr          = "EBD0A0A2 B9E5 4433 87C0 68B6B72699C7";
  CHAR8                 *ImagePathPrefix      = "\\image\\spss";
  CHAR8                 *ImagePath            = NULL;
  UINT32                 ImagePathLength      = AsciiStrLen(ImagePathPrefix) + 2;
  EFI_CHIPINFO_PROTOCOL *pEfiChipInfoProtocol = NULL;
  EFIChipInfoFamilyType  chipFamily           = EFICHIPINFO_NUM_FAMILIES;
  EFIChipInfoVersionType ChipVer              = (EFIChipInfoVersionType) 0;
  UINT32                 ChipVerMajor         = 1; /* so that by default SPSS
                                                      1t/1p images get loaded
                                                      on devices where same
                                                      SPSS image is applicable
                                                      to all versions of the
                                                      SoC */                                                      
  UINT32                 SPSS_Config          = 0; /* So that incase the fuse
                                                      reading fails, we load
                                                      prod images by default */

    Status = gBS->LocateProtocol(&gEfiChipInfoProtocolGuid,NULL, (VOID**) &pEfiChipInfoProtocol);
    if (EFI_SUCCESS != Status)
    {
      DEBUG((EFI_D_ERROR,"SPSSDxe:: %a gEfiChipInfoProtocolGuid protocol failed = %r \r\n", __FUNCTION__, Status ));
      return Status;
    }

  /* In order to figure out the SPSS image to be loaded, we need to know:
     1. The Chip Version - For Kailua/Halliday, single SPSS image version works 
                           for all Chip versions. So, we will not perform
						   a chip version check and always use spss1x image.
     2. Test vs Production device.
     So, lets get that information */
  if (IsChipVersionRelevant)
  {
    Status = pEfiChipInfoProtocol->GetChipVersion(pEfiChipInfoProtocol, &ChipVer);
    if (EFI_SUCCESS != Status)
    {
      DEBUG((EFI_D_ERROR,"SPSSDxe:: %a GetChipVersion failed = %r \r\n", __FUNCTION__, Status));
      return Status;
    }

    /* First 2 bytes of ChipVer contain the major Version number... thats all
       we need */
    ChipVerMajor = (0x0000FFFF & (ChipVer >> 16));

    if (ChipVerMajor == 0 || ChipVerMajor > SPSS_MAX_CHIP_VER)
    {
      DEBUG((EFI_D_ERROR,"SPSSDxe:: %a GetChipVersion returned invalid chip ver = %d \r\n", __FUNCTION__, ChipVerMajor));
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pEfiChipInfoProtocol->GetChipFamily(pEfiChipInfoProtocol,&chipFamily);
  if ((EFI_SUCCESS != Status) || (chipFamily >= EFICHIPINFO_NUM_FAMILIES))
  {
    DEBUG((EFI_D_ERROR,"SPSSDxe:: %a GetChipFamily failed = %r \r\n", __FUNCTION__, Status));
    return EFI_INVALID_PARAMETER;
  }

  /* Read SECURITY QC_CONFIG5 register(sensed register of QFPROM_CORR_QC_CONFIG_ROW2_MSB) 
     to find out SPSS CONFIG MODE,
     which is then used to determine whether to
     load test or prod SPSS images to the device:
     SPSS_CONFIG_MODE bits 00: prod
     SPSS_CONFIG_MODE bits 01: test */
  if (EFI_SUCCESS == SPSSDxe_MapFuse())
  {
     SPSS_Config = SPSSDxe_ReadFuse(SP_TME_FUSE_CONTROLLER_SW_RANGE5_OFFSET_ADDR);
     SPSS_Config >>= SPSS_CONFIG_MODE_FIELD;
     SPSS_Config &= SPSS_CONFIG_MASK;
  }
  DEBUG((EFI_D_INFO, "SPSSDxe:: %a SPSS_Config = 0x%x. \r\n", __FUNCTION__, SPSS_Config));
  /* We retrieved all the info needed. Now lets create a string representing
     the correct SPSS image path */
  ImagePath = AllocateZeroPool(ImagePathLength);
  if (ImagePath == NULL)
  {
    DEBUG((EFI_D_ERROR, "SPSSDxe:: %a MALLOC error. \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  ImagePathLength = AsciiStrLen(ImagePathPrefix);
  AsciiStrCpyS(ImagePath, MAX_PATH_LEN, ImagePathPrefix);
  if (AsciiStrLen(ImagePath) < ImagePathLength)
  {
    DEBUG((EFI_D_ERROR, "SPSSDxe:: %a Couldn't copy ImagePathPrefix string. \r\n", __FUNCTION__));
    FreePool(ImagePath);
    return EFI_DEVICE_ERROR;
  }
  ImagePathLength += 1;
  switch (ChipVerMajor)
  {
    case 2:
      AsciiStrCatS(ImagePath, MAX_PATH_LEN, "2");
      break;
    case 3:
      AsciiStrCatS(ImagePath, MAX_PATH_LEN, "3");
      break;
    case 1:
    default:
      AsciiStrCatS(ImagePath, MAX_PATH_LEN, "1");
      break;
  }
  if (AsciiStrLen(ImagePath) < ImagePathLength)
  {
    DEBUG((EFI_D_ERROR, "SPSSDxe:: %a Couldn't copy ImagePath version. \r\n", __FUNCTION__));
    FreePool(ImagePath);
    return EFI_DEVICE_ERROR;
  }

  ImagePathLength += 1;

  if (SPSS_Config == SPSS_CONFIG_PROD_VAL)
  {
    AsciiStrCatS(ImagePath, MAX_PATH_LEN, "p");
  }
  else if (SPSS_Config == SPSS_CONFIG_TEST_VAL)
  {
    AsciiStrCatS(ImagePath, MAX_PATH_LEN, "t");
  }

  if (AsciiStrLen(ImagePath) < ImagePathLength)
  {
    DEBUG((EFI_D_ERROR, "SPSSDxe:: %a Couldn't copy ImagePath string. \r\n", __FUNCTION__));
    FreePool(ImagePath);
    return EFI_DEVICE_ERROR;
  }

  /* Now we have everything needed to create the config. Lets create
     the config */
  spss_cfg->Version = 1;
  spss_cfg->Type = ELF_SPLIT;
  HexStrToBin ((UINT8*)PartGuidStr, AsciiStrLen(PartGuidStr),
               (UINT32*)&(spss_cfg->PartiGuid), sizeof(EFI_GUID));
  AdjustGUID((UINT8*)&(spss_cfg->PartiGuid));
  AsciiStrToUnicodeStrS(ImagePath, spss_cfg->ImagePath, NAME_MAX_LENGTH);
  AsciiStrToUnicodeStrS("SPSS", spss_cfg->FwName, NAME_MAX_LENGTH);
  spss_cfg->SubsysID = 14;
  /* Refer IPCAT memory map SPSS region info to update this */
  if (chipFamily == EFICHIPINFO_FAMILY_KAILUA)
  {
    spss_cfg->ResvRegionStart = 0x9B100000;
  }
  else if (chipFamily == EFICHIPINFO_FAMILY_HALLIDAY)
  {
    spss_cfg->ResvRegionStart = 0x8D600000; /* Halliday */
  }

  spss_cfg->ResvRegionSize = 0x180000;
  spss_cfg->ImageLoadInfo = TRUE;
  spss_cfg->OverrideElfAddr = TRUE;

  FreePool(ImagePath);
  return Status;
}

/**
  SPSSDxe_VotePMICResources ()

  @brief
  Vote ON the PMIC resources before loading the SPSS image:
  1. Turn ON ARI LDO
  2. Configure ARI power alarm GPIO
 */
STATIC VOID SPSSDxe_VotePMICResources ( VOID )
{
  npa_client_handle vreg_sp = NULL; /* for PX13 */
  npa_client_handle gpio_b7 = NULL; /* for GPIO7B */

  vreg_sp =  npa_create_sync_client("/pm/vreg.sp/en", "vreg_sp", NPA_CLIENT_REQUIRED);
  gpio_b7 =  npa_create_sync_client("/pm/gpiob7/en", "gpio_b7", NPA_CLIENT_REQUIRED);
  if (vreg_sp != NULL)
  {
    npa_issue_required_request(vreg_sp, 1); /* enable vote */
  }

  if (gpio_b7 != NULL)
  {
    npa_issue_required_request(gpio_b7, 1); /* enable vote */
  }
}

/**
  SPSSDxe_LoadSPSS ()

  @brief
  Trigger loading of SPSS image using PILProtocol
 */
STATIC EFI_STATUS SPSSDxe_LoadSPSS( PIL_SUBSYS_CFG_TYPE* spss_cfg )
{
  EFI_PIL_PROTOCOL  *PILProtocol = NULL;
  EFI_STATUS         Status      = EFI_LOAD_ERROR;
  UINT32             RegisterVal = 0;

  if (spss_cfg == NULL)
  {
    DEBUG((EFI_D_ERROR, "SPSSDxe:: %a invalid argument. \r\n", __FUNCTION__));
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateProtocol (&gEfiPilProtocolGuid,NULL, (VOID **) &PILProtocol);
  if ((EFI_SUCCESS != Status) && (NULL == PILProtocol))
  {
    DEBUG(( EFI_D_ERROR, "SPSSDxe:: %a LocateProtocol = %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  /* setup for IAR */
  Status = spss_iar_main(spss_cfg);
  
  /* Now load the SPSS with the cfg created above */
  Status = PILProtocol->ProcessPilImageExt(spss_cfg);

  if (EFI_SUCCESS == Status)
  {
    /* Vote ON the PMIC resources before loading SPSS */
    SPSSDxe_VotePMICResources();
  }
  else
  {
    DEBUG(( EFI_D_ERROR, "SPSSDxe:: %a ProcessPilImageExt = %r \r\n", __FUNCTION__, Status));
    if (EFI_SUCCESS == SPSSDxe_MapSPRegisters())
    {
      // Set only the least significant bit
      RegisterVal = SPSSDxe_ReadSPRegister(SP_CNOC_SP_SCSR_RMB_GPm(0));
      if(RegisterVal != SP_SCSR_REGISTER_ACCESS_ERROR)
      {
        RegisterVal |= SP_SCSR_RMB_GP_LOAD_FAILURE_MASK;
        (VOID) SPSSDxe_WriteSPRegister(SP_CNOC_SP_SCSR_RMB_GPm(0), RegisterVal);
      }
    }
  }

  return Status;
}


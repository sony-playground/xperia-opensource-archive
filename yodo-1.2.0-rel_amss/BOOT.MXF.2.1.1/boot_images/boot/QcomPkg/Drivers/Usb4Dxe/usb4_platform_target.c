/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_platform_target.c
 *
 *
 *  @brief :  usb4 platform implementation
 *
 *   Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include <Uefi.h>
// #include <Library/IoLib.h>
// #include <Library/DebugLib.h>
// #include <Library/MemoryAllocationLib.h>
// #include <Library/UefiBootServicesTableLib.h>
// #include <Library/UefiRuntimeServicesTableLib.h>
// #include <Protocol/EFIUsb4Config.h>
// #include <Protocol/EFIClock.h>
#include <Protocol/EFIHWIO.h>               //MapRegionByAddress()

// #include <string.h>
#include <stdlib.h>
#include <Usb4Utils.h>
#include "msmhwio_usb4.h"
#include "Usb4Log.h"
#include "usb4_platform_target.h"
#include "usb4_mem.h"      // DMA API declaration, and structs
#include "usb4_gcc.h"


// #include "VVHAL_usb4_logger.h"   // Logging utilities
// #include "VVHAL_usb4_gcc_platform.h"
// #include "VVHAL_usb4_utils.h"
// #include "VVHAL_usb4_platform_ahb_access_target.h"
// #include <new>
// #include <cstring>
// #include "VVHAL_usb4_mem.h"
// #include "VVHAL_usb4_platform_defs.h"
// 
// #include "VVHAL_usb4_hwio.h"
// #include "VVHAL_usb4_hwioreg_core.h"

#ifdef ASIC
// #include "usb4_platform_cio_phy_target.h"
#else
#include "usb4_platform_cio_phy_emulation.h"
#endif

#if defined(USB4_COMPILING_GEN_EMU)
    #include "usb4_platform_copss.h"
    #include "deo_mutex.h"
#endif /* USB4_COMPILING_GEN_EMU */
    
extern EFI_GUID gEfiClockProtocolGuid;


/*----------------------------------------------------------------------------
* Global variables
*--------------------------------------------------------------------------*/
const CHAR8 Usb4Hr0PowerDomain[] = "gcc_usb4_gdsc";
const CHAR8 Usb4Hr1PowerDomain[] = "gcc_usb4_1_gdsc";


#if defined(USB4_COMPILING_GEN_EMU)
    DEO_MUTEX_DECLARE(static s_usb4_cm_platform_mutex0); // one instance for each core
    DEO_MUTEX_DECLARE(static s_usb4_cm_platform_mutex1); // one instance for each core

    deo_mutex_t* g_pUsb4CmMutex[USB4_NUM_OF_CORES] = {&s_usb4_cm_platform_mutex0, 
                                                      &s_usb4_cm_platform_mutex1};
#endif /* USB4_COMPILING_GEN_EMU */

// UEFI OS specific mapping done in Usb4MapRegion()
static UINT8* s_usb4CoreBases[] = 
{
  (UINT8*)(USB4_HOST_ROUTER_0USB4_WRAPPER_BASE),
  (UINT8*)(USB4_HOST_ROUTER_1USB4_WRAPPER_BASE),
};


/*----------------------------------------------------------------------------
 * Static local functions
 *--------------------------------------------------------------------------*/



/*====================== VVHAL_usb4_platform_target ===================*/

/*----------------------------------------------------------------------------
 * Functions implementation
 *--------------------------------------------------------------------------*/
EFI_STATUS
Usb4UcInitTlmm (
  IN usb4_platform_ctx_t* usb4_platform_ctx
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = gBS->LocateProtocol(&gEfiTLMMProtocolGuid,
                                 NULL, (VOID **)&usb4_platform_ctx->TLMMProtocol);
  if (Status != EFI_SUCCESS)
  {
    // DEBUG(( EFI_D_WARN, "%a: TLMM Locate Protocol failed\r\n", __func__));
    return Status;
  }
  return Status;
}


EFI_STATUS
EFIAPI
Usb4MapRegion(usb4_platform_ctx_t* usb4_platform_ctx)
{
  EFI_STATUS Status;
	UINT8* BaseAddr = 0;

	if (usb4_platform_ctx->HWIOProtocol == NULL)
	{
		Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&usb4_platform_ctx->HWIOProtocol);
		if ((EFI_SUCCESS != Status) || (usb4_platform_ctx->HWIOProtocol == NULL))
		{
			DEBUG ((EFI_D_ERROR, "ERROR: Failed to locate HWIO Protocol: 0x%08x\n", Status));
			return Status;
        }
    }

    switch (usb4_platform_ctx->m_coreIndex)
    {
        case 0: 
            BaseAddr = (UINT8*) USB4_HOST_ROUTER_0USB4_WRAPPER_BASE;
            Status = usb4_platform_ctx->HWIOProtocol->MapRegionByAddress(usb4_platform_ctx->HWIOProtocol, BaseAddr, (UINT8**) &usb4_platform_ctx->UsbHrAddr[usb4_platform_ctx->m_coreIndex]);
            break;
        case 1:
            BaseAddr = (UINT8*) USB4_HOST_ROUTER_1USB4_WRAPPER_BASE;
            Status = usb4_platform_ctx->HWIOProtocol->MapRegionByAddress(usb4_platform_ctx->HWIOProtocol, BaseAddr, (UINT8**) &usb4_platform_ctx->UsbHrAddr[usb4_platform_ctx->m_coreIndex]);
            break;
        default: 
            return EFI_INVALID_PARAMETER;
    }

    if (EFI_SUCCESS != Status)
    {
        DEBUG ((EFI_D_ERROR, "ERROR: 0x%08x Failed to map instant %d base address: 0x%08x\n", Status, usb4_platform_ctx->m_coreIndex, BaseAddr));
    }

    return Status;
}

EFI_STATUS
EFIAPI
Usb4UnmapRegion(usb4_platform_ctx_t* usb4_platform_ctx)
{
    EFI_STATUS Status = EFI_SUCCESS;
    if (usb4_platform_ctx->HWIOProtocol == NULL)
    {
        Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&usb4_platform_ctx->HWIOProtocol);
        if ((EFI_SUCCESS != Status) || (usb4_platform_ctx->HWIOProtocol == NULL))
        {
            DEBUG ((EFI_D_ERROR, "ERROR: Failed to locate HWIO Protocol: 0x%08x\n", Status));
            return Status;
        }
    }
    switch (usb4_platform_ctx->m_coreIndex)
    {
        case 0:
        case 1:
            if (usb4_platform_ctx->UsbHrAddr[usb4_platform_ctx->m_coreIndex])
            {
                Status = usb4_platform_ctx->HWIOProtocol->UnMapRegion(usb4_platform_ctx->HWIOProtocol, usb4_platform_ctx->UsbHrAddr[usb4_platform_ctx->m_coreIndex]);
            }
            break;
        default: 
            return EFI_INVALID_PARAMETER;
    }
    if (EFI_SUCCESS != Status)
    {
        DEBUG ((EFI_D_ERROR, "ERROR: 0x%08x Failed to map instant %d\n", Status, usb4_platform_ctx->m_coreIndex));
    }
    return Status;
}


usb4_platform_ctx_t* Usb4PlatformCreate(UINT32 coreIndex)
{
    usb4_platform_ctx_t* usb4_platform_ctx = NULL;
    switch(coreIndex)
    {
        case 0:
        case 1:
            usb4_platform_ctx = usb4_mem_alloc(sizeof(usb4_platform_ctx_t), 0);
            Usb4PlatformInit(usb4_platform_ctx, coreIndex);
            return usb4_platform_ctx;
            break;
        default:
            break;
    }
    return NULL;
}



int Usb4PlatformInit(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 coreIndex)
{
    EFI_STATUS Status = EFI_SUCCESS;
    HAL_IOMMUResult_t SmmuStatus = HAL_IOMMU_ERR_OK;
    

    Usb4Log1(USB4_LOG_CFG, Usb4PlatformInit__Param__CreatingPlatformForCoreIndex, 0, coreIndex);
    // USB4_LOG_INFO("Creating platform for core %d\n", coreIndex);
    // ++++ Base Class
    usb4_platform_ctx->m_interrupts = NULL;
    usb4_platform_ctx->m_ahbAccess = NULL;
#if 0
    usb4_platform_ctx->m_GCC = NULL;
#endif
    usb4_platform_ctx->m_PHY = NULL;
    usb4_platform_ctx->m_uC = NULL;
#if 0 // TODO: AC port PD
    usb4_platform_ctx->m_PD = NULL;
#endif
    usb4_platform_ctx->m_pDpAux = NULL;
    usb4_platform_ctx->m_bSkipLoadingFirmware = FALSE;
    usb4_platform_ctx->m_bDoSidebandOverride = TRUE;
    usb4_platform_ctx->m_sidebandOverrideValue = USB4_platform_sb_ctrl_sw_pulldown;
    usb4_platform_ctx->m_bSleepUnplugged = FALSE;
    // ---- Base Class

    usb4_platform_ctx->m_coreIndex = coreIndex;
    usb4_platform_ctx->m_coreBaseAddress = NULL;
    // usb4_platform_ctx->m_pMutex = NULL;
    usb4_platform_ctx->m_USBAP_RXTERM_BACKDOOR_STS = 0;

#if defined(USB4_COMPILING_GEN_EMU)
    if (NULL == usb4_platform_ctx->m_pMutex)
    {
        usb4_platform_ctx->m_pMutex = g_pUsb4CmMutex[usb4_platform_ctx->m_coreIndex];
        USB4_ASSERT(NULL != usb4_platform_ctx->m_pMutex);
        if (NULL == usb4_platform_ctx->m_pMutex->lock)
        {
            USB4_ASSERT(DEO_SUCCESS == VVDRV_deo_mutex_create(usb4_platform_ctx->m_pMutex, DEO_MUTEX_ATTR_CRITICAL_SECTION));
        }
        USB4_ASSERT(NULL != usb4_platform_ctx->m_pMutex->lock);
    }
#else /* USB4_COMPILING_GEN_EMU */
    // TODO: AC need to define mutex
    // USB4_LOG_WARNING("Need to define MUTEX...\n");
#endif /* USB4_COMPILING_GEN_EMU */

    if (NULL == usb4_platform_ctx->m_interrupts)
    {
        // m_interrupts = new (std::nothrow) VVHAL_usb4_platform_interrupts();
        usb4_platform_ctx->m_interrupts = usb4_mem_alloc(sizeof(usb4_platform_interrupts_ctx_t), 0);
        if (NULL == usb4_platform_ctx->m_interrupts)
        {
            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
            goto ErrorHandling;
        }
    }
#if 0 // TODO: AC port interrupt mode
    switch(usb4_platform_ctx->m_coreIndex)
    {
        case 0:
            usb4_platform_ctx->m_interrupts->m_interrupt_vectors = g_usb4_platform_interrupts_core0;
            usb4_platform_ctx->m_interrupts->m_interrupt_vectors_size = g_usb4_platform_interrupts_core0_size;
            break;
        case 1:
            usb4_platform_ctx->m_interrupts->m_interrupt_vectors = g_usb4_platform_interrupts_core1;
            usb4_platform_ctx->m_interrupts->m_interrupt_vectors_size = g_usb4_platform_interrupts_core1_size;
            break;
        default:
            USB4_ERROR_STACK_MSG(-1, "Core number out of range\n");
            goto ErrorHandling;
    }
#endif

    // ++++ UEFI specific
  	Status = Usb4MapRegion(usb4_platform_ctx);
  	if (Status)
  	{
  		DEBUG ((EFI_D_ERROR, "Usb4Entry: Failed to map usb4 region, status \n", Status));
  		return Status;
  	}

    Status = gBS->LocateProtocol(&gEfiHalIommuProtocolGuid, NULL, (void **)&usb4_platform_ctx->IommuProtocol);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Usb4PlatformInit: Failed to locate iommu protocol\n"));
      return -1;
    }

    usb4_platform_ctx->IommuProtocol->_HAL_IOMMU_protocol_init((HAL_IOMMU_fptable_t **)&usb4_platform_ctx->SmmuTable);
    SmmuStatus = usb4_platform_ctx->SmmuTable->domain_create_func(&usb4_platform_ctx->Usb4SmmuDomain);  
    if (SmmuStatus != HAL_IOMMU_ERR_OK) {
      DEBUG ((EFI_D_ERROR, "Usb4PlatformInit: Failed SMMU:domain_create_func\n"));
      return -1;
    }

    // SMMU
    SmmuStatus = usb4_platform_ctx->SmmuTable->config_bypass_domain_func(usb4_platform_ctx->Usb4SmmuDomain, HAL_IOMMU_AARCH64_NON_CCA_DOMAIN_TYPE);
    if (SmmuStatus != HAL_IOMMU_ERR_OK) {
      DEBUG ((EFI_D_ERROR, "Usb4PlatformInit: Failed SMMU:config_bypass_domain_func\n"));
      return -1;
    }

    if (usb4_platform_ctx->m_coreIndex == 0) {
      SmmuStatus = usb4_platform_ctx->SmmuTable->domain_attach_func(usb4_platform_ctx->Usb4SmmuDomain, (VOID*)"USB4", 0x0, 0x0);
    }
    else if (usb4_platform_ctx->m_coreIndex == 1) {
      SmmuStatus = usb4_platform_ctx->SmmuTable->domain_attach_func(usb4_platform_ctx->Usb4SmmuDomain, (VOID*)"USB4", 0x1, 0x0);
    }
    else {
      return -1;
    }
    if (SmmuStatus != HAL_IOMMU_ERR_OK) {
      DEBUG ((EFI_D_ERROR, "Usb4PlatformInit: Failed SMMU:domain_attach_func\n"));
      return -1;
    }

    Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID**)&usb4_platform_ctx->ClockProtocol);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Usb4PlatformInit: Failed to locate clock protocol\n"));
      goto ErrorHandling;
      return -1;
    }

// Placeholder, moved PowerDomain code

    // Usb4GccInit and Usb4GccEnableClocks further down
    // ---- UEFI specific


#ifdef USB4_COMPILING_GEN_EMU
    if (0 != VVHAL_usb4_copss_getDutBase(usb4_platform_ctx->m_coreIndex, 
                                         &usb4_platform_ctx->m_coreBaseAddress, 
                                         NULL))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
#else /* USB4_COMPILING_GEN_EMU */
    usb4_platform_ctx->m_coreBaseAddress = s_usb4CoreBases[usb4_platform_ctx->m_coreIndex];
#endif /* USB4_COMPILING_GEN_EMU */
    USB4_ASSERT(NULL != usb4_platform_ctx->m_coreBaseAddress);

    if (NULL == usb4_platform_ctx->m_ahbAccess)
    {
        // usb4_platform_ctx->m_ahbAccess = new (std::nothrow) VVHAL_usb4_platform_ahb_access_target(usb4_platform_ctx->m_coreBaseAddress);
        usb4_platform_ctx->m_ahbAccess = usb4_mem_alloc(sizeof(usb4_platform_ahb_access_ctx_t), 0);
        if (NULL == usb4_platform_ctx->m_ahbAccess)
        {
            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
            goto ErrorHandling;
        }
        Usb4PlatformAhbAccessInit(usb4_platform_ctx->m_ahbAccess, usb4_platform_ctx->m_coreBaseAddress, 0); // Added initialization
    }


// +++ UEFI Power Domain Code
#if 0 // TODO: AC Not in power domain list in UEFI, need to investigate
        if (EFI_SUCCESS != Usb4PlatformConfigPowerDomain(usb4_platform_ctx, TRUE, "gcc_usb_tbu_gdsc"))
        {
           USB4_ERROR_STACK(-1);
           goto ErrorHandling;
        }
#endif

        if (0 == usb4_platform_ctx->m_coreIndex)
        {
          if (EFI_SUCCESS != Usb4PlatformConfigPowerDomain(usb4_platform_ctx, TRUE, Usb4Hr0PowerDomain))
          {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
          }
        }
        else if (1 == usb4_platform_ctx->m_coreIndex)
        {
          if (EFI_SUCCESS != Usb4PlatformConfigPowerDomain(usb4_platform_ctx, TRUE, Usb4Hr1PowerDomain))
          {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
          }
        }
        else
        {
          USB4_ERR_FATAL("Invalid Core Index", 0, 0, 0);
          goto ErrorHandling;
        }
// --- UEFI Power Domain Code  


//    if (NULL == usb4_platform_ctx->m_GCC)
    {
#ifndef USB4_USE_ENABLE_ALL_CLKS_CMM
        UINT32 mask = USB4_GCC_RESET_ALL;
#endif // ~USB4_USE_ENABLE_ALL_CLKS_CMM
        // usb4_platform_ctx->m_GCC = new (std::nothrow) VVHAL_usb4_gcc_platform();
//        usb4_platform_ctx->m_GCC = usb4_mem_alloc(sizeof(usb4_gcc_ctx_t), 0); // Absorbed into usb4_platform_ctx
//        if (NULL == usb4_platform_ctx->m_GCC)
//        {
//            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
//            goto ErrorHandling;
//        }
    
        if (0 != Usb4GccInit(usb4_platform_ctx, usb4_platform_ctx->m_coreIndex, usb4_platform_ctx->m_coreBaseAddress))
        {
            USB4_ERROR_STACK_MSG(-1, "m_GCC.Init failed\n");
            goto ErrorHandling;
        }

#ifndef USB4_USE_ENABLE_ALL_CLKS_CMM       
        if (0 != Usb4GccEnableClocks(usb4_platform_ctx, mask, TRUE))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
#endif // ~USB4_USE_ENABLE_ALL_CLKS_CMM

        if (0 != Usb4GccCoreCollapse(usb4_platform_ctx, FALSE))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

// TODO: AC PMIC

    Usb4PlatformInitTlmm(usb4_platform_ctx);

    if (NULL == usb4_platform_ctx->m_PHY)
    {
        if (0 != Usb4PlatformSideBandRxControl(usb4_platform_ctx, USB4_platform_sb_ctrl_hw_ctrl))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
        if (0 != Usb4PlatformSideBandTxControl(usb4_platform_ctx, USB4_platform_sb_ctrl_sw_nopull))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

#ifdef ASIC
        // usb4_platform_ctx->m_PHY = new (std::nothrow) VVHAL_usb4_platform_cio_phy_target();
        usb4_platform_ctx->m_PHY = usb4_mem_alloc(sizeof(usb4_platform_cio_phy_ctx_t), 0);
        if (NULL == usb4_platform_ctx->m_PHY)
        {
            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
            goto ErrorHandling;
        }

        // m_phyBaseAddress are initialized internally
        Usb4PlatformCioPhyInit(usb4_platform_ctx->m_PHY, usb4_platform_ctx->m_coreIndex, usb4_platform_ctx->m_coreBaseAddress);
#else
        // usb4_platform_ctx->m_PHY = new (std::nothrow) VVHAL_usb4_platform_cio_phy_emulation();
        usb4_platform_ctx->m_PHY = usb4_mem_alloc(sizeof(usb4_platform_cio_phy_ctx_t), 0);
        if (NULL == usb4_platform_ctx->m_PHY)
        {
            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
            goto ErrorHandling;
        }

        // if (0 != usb4_platform_ctx->m_PHY->Init(usb4_platform_ctx->m_coreIndex, usb4_platform_ctx->m_coreBaseAddress))
        if (0 != Usb4PlatformCioEmulationPhyInit(usb4_platform_ctx->m_PHY, usb4_platform_ctx->m_coreIndex, usb4_platform_ctx->m_coreBaseAddress))
        {
            USB4_ERROR_STACK_MSG(-1, "Instance initialization failed\n");
            goto ErrorHandling;
        }
#endif
    }

    if (NULL == usb4_platform_ctx->m_uC)
    {
        // usb4_platform_ctx->m_uC = new (std::nothrow) VVHAL_usb4_platform_uC_target(usb4_platform_ctx->m_coreBaseAddress, usb4_platform_ctx->m_coreIndex);
        usb4_platform_ctx->m_uC = usb4_mem_alloc(sizeof(usb4_platform_uC_ctx_t), 0);
        if (NULL == usb4_platform_ctx->m_uC)
        {
            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
            goto ErrorHandling;
        }
        Usb4PlatformUcInit(usb4_platform_ctx->m_uC, usb4_platform_ctx->m_coreBaseAddress, usb4_platform_ctx->m_coreIndex);
    }

    #if 0 // PD does not have data structure, pass the CoreIdx each time, the API names are VVDRV_pd_api_*
    if (NULL == usb4_platform_ctx->m_PD)
    {
        usb4_platform_ctx->m_PD = new (std::nothrow) VVDRV_usb4_pd();
        if (NULL == usb4_platform_ctx->m_PD)
        {
            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
            goto ErrorHandling;
        }
    }
    if (0 != usb4_platform_ctx->m_PD->Init(usb4_platform_ctx->m_coreIndex))
    {
        USB4_ERROR_STACK_MSG(-1, "m_PD.Init failed\n");
        goto ErrorHandling;
    }
    #endif
    
    if (NULL == usb4_platform_ctx->m_pDpAux)
    {
        // usb4_platform_ctx->m_pDpAux = new (std::nothrow) VVDRV_usb4_dp_aux();
        usb4_platform_ctx->m_pDpAux = usb4_mem_alloc(sizeof(usb4_dp_aux_ctx_t), 0);
        if (NULL == usb4_platform_ctx->m_pDpAux)
        {
            USB4_ERROR_STACK_MSG(-1, "Instance creation failed\n");
            goto ErrorHandling;
        }
    }

    if (0 != Usb4DpAuxInit(usb4_platform_ctx->m_pDpAux, usb4_platform_ctx->m_coreBaseAddress, usb4_platform_ctx->m_coreIndex))
    {
        USB4_ERROR_STACK_MSG(-1, "m_pDpAux.Init failed");
        goto ErrorHandling;
    }
    
    return 0;
ErrorHandling:
    return -1;
}


UINT32 Usb4PlatformGetCoreIndex(usb4_platform_ctx_t* usb4_platform_ctx)
{
  return usb4_platform_ctx->m_coreIndex;
};


int Usb4PlatformGetHIA_Base(usb4_platform_ctx_t* usb4_platform_ctx, UINT8** ppBase)
{
    USB4_ASSERT(NULL != ppBase);

    *ppBase = usb4_platform_ctx->m_coreBaseAddress + HOST_INTERFACE_REG_BASE_OFFS;

    return 0;
}

int Usb4PlatformGetCore_Base(usb4_platform_ctx_t* usb4_platform_ctx, UINT8** ppBase)
{
    USB4_ASSERT(NULL != ppBase);

    *ppBase = usb4_platform_ctx->m_coreBaseAddress;
    return 0;
}

int Usb4PlatformStorePersistentData(usb4_platform_ctx_t* usb4_platform_ctx)
{
    USB4_ASSERT(NULL != usb4_platform_ctx->m_coreBaseAddress);
    usb4_platform_ctx->m_USBAP_RXTERM_BACKDOOR_STS = HWIO_INX(usb4_platform_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS, USB4_USBAP_CFG_RXTERM_BACKDOOR_STS);
    return 0;
}

int Usb4PlatformWriteBackPersistentData(usb4_platform_ctx_t* usb4_platform_ctx)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    USB4_ASSERT(NULL != usb4_platform_ctx->m_coreBaseAddress);
    HWIO_OUTX(usb4_platform_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS, USB4_USBAP_CFG_RXTERM_BACKDOOR_CTRL, usb4_platform_ctx->m_USBAP_RXTERM_BACKDOOR_STS);
    usb4_timer_Sleep_ms(&timer, 1);

#if defined(HWIO_USB4_USBAP_CFG_PHYSTATUS_EN_ADDR)
    
    HWIO_OUTXF(usb4_platform_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS, USB4_USBAP_CFG_PHYSTATUS_EN, PHYSTATUS_EN, 0x1);  /* USB4_USBAP_CFG_PHYSTATUS_EN.PHYSTATUS_EN=1 */
#if !defined(RUMI)
    // TODO: AC is GE register write still applicable for ASIC???  Double check
#define GE_DUT_USER_REGS_REG_BASE_OFFS                                                         0x01f80000
#define HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x)                                                     ((x) + 0x0000018c)
#define HWIO_GE_DUT_USB31_CTRL_REG_PHYS(x)                                                     ((x) + 0x0000018c)
#define HWIO_GE_DUT_USB31_CTRL_REG_OFFS                                                        (0x0000018c)
#define HWIO_GE_DUT_USB31_CTRL_REG_RMSK                                                              0x11
#define HWIO_GE_DUT_USB31_CTRL_REG_POR                                                         0x00000011
#define HWIO_GE_DUT_USB31_CTRL_REG_POR_RMSK                                                    0xffffffff
#define HWIO_GE_DUT_USB31_CTRL_REG_ATTR                                                               0x3
#define HWIO_GE_DUT_USB31_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_USB31_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_USB31_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_USB31_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_USB31_CTRL_REG_IN(x))
#define HWIO_GE_DUT_USB31_CTRL_REG_PIPE_CLK_EN_BMSK                                                  0x10
#define HWIO_GE_DUT_USB31_CTRL_REG_PIPE_CLK_EN_SHFT                                                   0x4
#define HWIO_GE_DUT_USB31_CTRL_REG_SLEEP_CLK_EN_BMSK                                                  0x1
#define HWIO_GE_DUT_USB31_CTRL_REG_SLEEP_CLK_EN_SHFT                                                  0x0
    HWIO_OUTX(usb4_platform_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB31_CTRL_REG, 0x11);  // Ungate pipe + sleep_clk
#endif /* RUMI */  
#else /* !HWIO_USB4_USBAP_CFG_PHYSTATUS_EN_ADDR */
    USB4_ERROR_STACK_MSG(-1, "Skip USB4_USBAP_CFG_PHYSTATUS_EN.PHYSTATUS_EN=1");
    USB4_ERROR_STACK_MSG(-1, "Skip GE_DUT_USB31_CTRL_REG=0x11");
#endif /* HWIO_USB4_USBAP_CFG_PHYSTATUS_EN_ADDR */

    return 0;
}

int Usb4PlatformPutPlatformToSleep(usb4_platform_ctx_t* usb4_platform_ctx)
{
    usb4_platform_ctx->m_bSkipLoadingFirmware = TRUE;

    //HWIO_OUTF(GCC_USB4_PHY_RX0_MUXR,MUX_SEL,0x2);
    //HWIO_OUTF(GCC_USB4_PHY_RX1_MUXR,MUX_SEL,0x2);

    //Set Bit 5 of USB4_PCS_WAKEUP_CLK_CONFIG1:
    //5~CLAMP_EN~Clamps the PHY's USB4 data inputs. Active high.~
    //(QCTDD06753137)
    return 0;
}

int Usb4PlatformGetCablePluggedStatus(usb4_platform_ctx_t* usb4_platform_ctx)
{
    /* If platform is disconnected, need to do the override */
    UINT32 plugged = 0;
    USB4_ASSERT(NULL != usb4_platform_ctx->m_coreBaseAddress);
    plugged = HWIO_INXF(usb4_platform_ctx->m_coreBaseAddress + LANE_0_NULL_REG_BASE_OFFS,USB4_L0_ADP_CS_4_STANDARD,  PLUGGED);
    if (0 == plugged) /* If the port is unplugged, need to do the override */
    {
        usb4_platform_ctx->m_bDoSidebandOverride = TRUE;
        usb4_platform_ctx->m_sidebandOverrideValue = USB4_platform_sb_ctrl_sw_pulldown;
        usb4_platform_ctx->m_bSleepUnplugged = TRUE;
    }
    else
    {
        usb4_platform_ctx->m_bDoSidebandOverride = FALSE; /* If pull-up is sufficient, avoid override. Is USB3 resume fails, then there was a disconnect instead of resume.
        Then enable override */
        usb4_platform_ctx->m_sidebandOverrideValue = USB4_platform_sb_ctrl_sw_pullup;
        usb4_platform_ctx->m_bSleepUnplugged = FALSE;
    }
    return 0;
}

//TODO: Validate registration for sleep done interrupt
int Usb4PlatformWakePlatformFromSleep(usb4_platform_ctx_t* usb4_platform_ctx)
{
    //Clear Bit 5 of USB4_PCS_WAKEUP_CLK_CONFIG1:
    //5~CLAMP_EN~Clamps the PHY's USB4 data inputs. Active high.~
    //(QCTDD06753137)

    //HWIO_OUTF(GCC_USB4_PHY_RX0_MUXR,MUX_SEL,0x0);
    //HWIO_OUTF(GCC_USB4_PHY_RX1_MUXR,MUX_SEL,0x0);
    return 0;
//ErrorHandling:
//    return -1;
}

/**
* @brief Lock mutex; This is not try lock. Failure means mutex is not valid/
* @return 0 on success, other on failure
*/
int Usb4PlatformLockMutex(usb4_platform_ctx_t* usb4_platform_ctx)
{
#if defined(USB4_COMPILING_GEN_EMU)
    if ((NULL == usb4_platform_ctx->m_pMutex) || (NULL == usb4_platform_ctx->m_pMutex->lock))
    {
        USB4_ERROR_STACK_MSG(-1, "No Mutex");
        return -1;
    }

    USB4_ASSERT(DEO_SUCCESS == VVDRV_deo_mutex_lock(usb4_platform_ctx->m_pMutex));
    return 0;
#else /* USB4_COMPILING_GEN_EMU */
    return 0;
#endif /* USB4_COMPILING_GEN_EMU */
};

/**
* @brief UnLock mutex; This is not try lock. Failure means mutex is not valid/
* @return 0 on success, other on failure
*/
int Usb4PlatformUnlockMutex(usb4_platform_ctx_t* usb4_platform_ctx)
{
#if defined(USB4_COMPILING_GEN_EMU)
    if ((NULL == usb4_platform_ctx->m_pMutex) || (NULL == usb4_platform_ctx->m_pMutex->lock))
    {
        USB4_ERROR_STACK_MSG(-1, "No Mutex");
        return -1;
    }

    USB4_ASSERT(DEO_SUCCESS == VVDRV_deo_mutex_unlock(usb4_platform_ctx->m_pMutex));
    return 0;

#else /* USB4_COMPILING_GEN_EMU */
    return 0;
#endif /* USB4_COMPILING_GEN_EMU */
};

int Usb4PlatformPlatformPreReset(usb4_platform_ctx_t* usb4_platform_ctx)
{
    if (usb4_platform_ctx->m_bDoSidebandOverride)
    {
        USB4_ASSERT(0 == Usb4PlatformSideBandRxControl(usb4_platform_ctx, usb4_platform_ctx->m_sidebandOverrideValue));
        USB4_ASSERT(0 == Usb4PlatformSideBandTxControl(usb4_platform_ctx, usb4_platform_ctx->m_sidebandOverrideValue));
    }
    return 0;
};

int Usb4PlatformPlatformPostReset(usb4_platform_ctx_t* usb4_platform_ctx)
{
    if (usb4_platform_ctx->m_bDoSidebandOverride)
    {
        UINT32 txEnable = 0;
        usb4_utils_timer timer;
        timer.m_source = USB4_TIMER_SOURCE_QTIMER;
        /* TODO: Check connected and disconnected sleep - may need to move SbTxEnable outside of If */
        txEnable = (USB4_platform_sb_ctrl_sw_pulldown != usb4_platform_ctx->m_sidebandOverrideValue)? 1: 0;
        USB4_ASSERT(0 == Usb4PlatformOverrideSbTxEnable(usb4_platform_ctx, txEnable));
        USB4_ASSERT(0 == Usb4PlatformSideBandRxControl(usb4_platform_ctx, USB4_platform_sb_ctrl_hw_ctrl));
        USB4_ASSERT(0 == Usb4PlatformSideBandTxControl(usb4_platform_ctx, USB4_platform_sb_ctrl_hw_ctrl));
        USB4_ASSERT(0 == usb4_timer_Sleep_ms(&timer, 10));
    }
    return 0;
};

int Usb4PlatformOverrideSbTxEnable(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 overrideValue)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT8 *pSbBase;
    USB4_ASSERT(NULL != usb4_platform_ctx->m_coreBaseAddress);

    pSbBase = usb4_platform_ctx->m_coreBaseAddress + SIDEBAND_REGS_REG_BASE_OFFS;
    while (overrideValue != HWIO_INXF(pSbBase, USB4_SB_TX_CTRL, TX_ENABLE))
    {
        HWIO_OUTXF(pSbBase, USB4_SB_TX_CTRL, TX_ENABLE, overrideValue);
        USB4_ASSERT(0 == usb4_timer_Sleep_ms(&timer, 1)); /* Needed for pull down to work */
    }
    return 0;
}

int Usb4PlatformOverrideSbTDisconnectRx(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 overrideValue, UINT32* pPrevValue)
{
    UINT8 *pSbBase;
    USB4_ASSERT(NULL != usb4_platform_ctx->m_coreBaseAddress);

    pSbBase = usb4_platform_ctx->m_coreBaseAddress + SIDEBAND_REGS_REG_BASE_OFFS;
    if (NULL != pPrevValue)
    {
        *pPrevValue = HWIO_INXF(pSbBase, USB4_SB_RX_COUNTERS, TDISCONNECTRX_VAL);
    }
    HWIO_OUTXF(pSbBase, USB4_SB_RX_COUNTERS, TDISCONNECTRX_VAL, overrideValue);
    return 0;
};


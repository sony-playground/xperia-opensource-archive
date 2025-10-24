/**
  @file pcie_osal_uefi.c
  @brief Internal interface include file for the PCIe target specific
  configuration layer.

  This file contains definitions of constants, data structures, and
  interfaces that provide target specific configuration data.

===============================================================================
                   Copyright (c) 2018 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/
#include "com_dtypes.h"
#include <Base.h>
#include <PiDxe.h>
#include <Library/ArmLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomBaseLib.h>
#include "pcie_osal.h"
#include "pcie_host_log.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>

#include "pcie_cfg_types.h"
#include <Protocol/EFIHALIOMMUProtocol.h>
#include <Library/TzRuntimeLib.h>
#include <Library/pmapp_npa.h>
#include <Library/Clock.h>
#include <Protocol/EFIRsc.h>
//#include <Protocol/EFIUsb4Protocol.h>

void pcie_osal_init (void)
{
}

void pcie_osal_deinit (void)
{
}

char log_buff[128];

void pcie_osal_log_msg(const char *fmt, ...)
{
   VA_LIST  Marker;
   VA_START (Marker, fmt);

   AsciiVSPrint (log_buff, sizeof(log_buff), fmt, Marker);
   DEBUG ((EFI_D_ERROR, log_buff));

   VA_END (Marker);
}

uint64 pcie_osal_get_time_ms (void)
{
   return GetTimerCountms ();
}

void* pcie_osal_malloc (size_t size)
{
   return AllocatePool (size);
}

void pcie_osal_free (void *ptr)
{
   FreePool (ptr);
}

void* pcie_osal_malloc_aligned (size_t size, uint8 align)
{
   return AllocatePages (EFI_SIZE_TO_PAGES (size)); // Keep it simple for now
}

void pcie_osal_free_aligned (void *ptr)
{
//   FreePages (ptr, number of pages);
}

void pcie_osal_busywait_us (uint32 time_us)
{
   gBS->Stall (time_us);
}

pcie_status_t pcie_osal_mem_region_map (pcie_osal_pa_t pa, size_t size, pcie_osal_mem_props_t mem_props,
                             pcie_osal_mem_info_t *mem_info)
{
  EFI_STATUS status = 0;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR Descriptor;

  /* Both memprop options can by satisfied by UC MMIO space type */

  status = gDS->GetMemorySpaceDescriptor (pa, &Descriptor);

  if (EFI_ERROR (status))
  {
     PCIE_HOST_LOG_ERROR ("Cannot get memory descriptor\n");
     return PCIE_ERROR;
  }

  if (Descriptor.Length < size)
     PCIE_HOST_LOG_ERROR ("Currently mapped size is smaller 0x%lx, 0x%x\n", Descriptor.Length, size);

  if ((Descriptor.GcdMemoryType != EfiGcdMemoryTypeMemoryMappedIo) ||
      (Descriptor.Length < size))
  {
     if (Descriptor.GcdMemoryType != EfiGcdMemoryTypeNonExistent)
     {
        status = gDS->RemoveMemorySpace (pa, size);
        DEBUG ((EFI_D_WARN, "Region is being remapped to correct type and size\n"));
     }

     status = gDS->AddMemorySpace (EfiGcdMemoryTypeMemoryMappedIo,
                                   pa, size, EFI_MEMORY_UC);
     if (EFI_ERROR (status))
     {
        PCIE_HOST_LOG_ERROR ("Unable to add memory space: addr=0x%lx, size=0x%lx\n", pa, size);
        return PCIE_ERROR;
     }

     status = gDS->SetMemorySpaceAttributes (pa, size, EFI_MEMORY_UC);
     if (EFI_ERROR (status))
     {
         PCIE_HOST_LOG_ERROR ("Fail to set memory attibute: addr=0x%lx, size=0x%lx\n", pa, size);
         return PCIE_ERROR;
     }
  }

  // TODO: Make sure to loop through the whole range

  if (mem_info)
  {
     mem_info->va = mem_info->pa = pa;
     mem_info->size = size;
  }

  return PCIE_SUCCESS;
}

void pcie_osal_memory_barrier (void)
{
 //  ArmDataMemoryBarrier ();
   ArmDataSynchronizationBarrier ();
}

pcie_status_t pcie_get_target_platform_info (uint32* chip_id_ptr, uint32* chip_ver_ptr, uint32* chip_family_ptr, uint32* plat_type_ptr)
{
  EFI_STATUS                  Status;
  EFI_CHIPINFO_PROTOCOL      *pChipInfo;
  EFI_PLATFORMINFO_PROTOCOL  *pPlatformInfo;
  EFIChipInfoIdType           ChipId;
  EFIChipInfoVersionType      Version;
  EFIChipInfoFamilyType       ChipFamily;
  EFI_PLATFORMINFO_PLATFORM_INFO_TYPE PlatformInfo;

  if (plat_type_ptr)
  {
     Status = gBS->LocateProtocol (&gEfiPlatformInfoProtocolGuid, NULL,
                                   (VOID **) &pPlatformInfo);
     if (EFI_ERROR (Status))
       return PCIE_ERROR;

     Status = pPlatformInfo->GetPlatformInfo (pPlatformInfo, &PlatformInfo);
     if (EFI_ERROR (Status))
       return PCIE_ERROR;

     *plat_type_ptr = PlatformInfo.platform;
  }

  Status = gBS->LocateProtocol (&gEfiChipInfoProtocolGuid, NULL,
                               (VOID **) &pChipInfo);
  if (EFI_ERROR (Status))
    return PCIE_ERROR;

  if (chip_id_ptr)
  {
     Status = pChipInfo->GetChipId (pChipInfo, &ChipId);
     if (Status != EFI_SUCCESS)
       return PCIE_ERROR;

     *chip_id_ptr = ChipId;
  }

  if (chip_ver_ptr)
  {
     Status = pChipInfo->GetChipVersion (pChipInfo, &Version);
     if (Status != EFI_SUCCESS)
       return PCIE_ERROR;

     *chip_ver_ptr = Version;
  }

  if (chip_family_ptr)
  {
     Status = pChipInfo->GetChipFamily (pChipInfo, &ChipFamily);
     if (Status != EFI_SUCCESS)
       return PCIE_ERROR;

     *chip_family_ptr = ChipFamily;
  }

   return PCIE_SUCCESS;
}

pcie_status_t write_secure_tcsr_reg_val (UINT32* addr, UINT32 val)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT64 TcsrRegInfo[2];

  TcsrRegInfo[0] = (UINT64)addr;
  TcsrRegInfo[1] = val;

  Status = TzFastcall (TZ_IO_ACCESS_WRITE_ID, TZ_IO_ACCESS_WRITE_ID_PARAM_ID, TcsrRegInfo, 2);
  
  if (Status != EFI_SUCCESS)
  {
     PCIE_HOST_LOG_ERROR ("Secure reg write failed\n");
     return PCIE_ERROR;
  }
  
  return PCIE_SUCCESS;
}

#if 0
uint32 pcie_init_ldos (pcie_pmic_config_t* pmic_config, int enable)
{
   // handle for the client.
   npa_query_type    query_result;
   npa_query_status  query_status = NPA_QUERY_NO_VALUE;

   if (pmic_config == NULL)
      return PCIE_ERROR;

   if (pmic_config->pmic_handle == NULL)
   {
      pmic_config->pmic_handle = npa_create_sync_client (PMIC_NPA_GROUP_ID_PCIE, pmic_config->pmic_npa_groupid, pmic_config->type);

      if (pmic_config->pmic_handle == NULL)
         return PCIE_ERROR;
   }

   query_status = npa_query_by_name (PMIC_NPA_GROUP_ID_PCIE, NPA_QUERY_CURRENT_STATE, &query_result);
   if (query_status == NPA_QUERY_SUCCESS)
   {
      if (enable)
         npa_issue_required_request (pmic_config->pmic_handle, pmic_config->on_level);
      else
         npa_issue_required_request (pmic_config->pmic_handle, pmic_config->off_level);
   }

   return PCIE_SUCCESS;
}
#endif

pcie_status_t pcie_configure_smmu (pcie_resources_ctxt_t *resources_ctxt, const char *Io_mmu_cfg)
{
   EFI_HAL_IOMMU_PROTOCOL * pHALIOMMUProtocol;
   HAL_IOMMU_fptable_t * fp_table = NULL;
   VOID                * p_pcie_domain_hdl;
   EFI_STATUS           Status = EFI_SUCCESS;
   HAL_IOMMUResult_t    IoMMUStatus;

   if (Io_mmu_cfg == NULL)
   {
      //PCIE_HOST_LOG_ERROR ("Assuming SMMUv3 is enabled\n");
      return PCIE_SUCCESS;  // Assume SMMUv3 is enabled
   }

   if (resources_ctxt == NULL)
      return PCIE_ERROR;

   if (resources_ctxt->smmu_initialized)
      return PCIE_SUCCESS;

   Status = gBS->LocateProtocol(&gEfiHalIommuProtocolGuid, NULL,
                                (VOID **)&pHALIOMMUProtocol);
   if (EFI_ERROR(Status))
   {
      PCIE_HOST_LOG_ERROR ("HalIOMMU protocol not found\n");
      return PCIE_ERROR;
   }

   pHALIOMMUProtocol->_HAL_IOMMU_protocol_init(&fp_table);
   if (HAL_IOMMU_ERR_OK != fp_table->domain_create_func (&p_pcie_domain_hdl))
   {
      PCIE_HOST_LOG_ERROR ("Unable to get HalIoMMU handle\n");
      return PCIE_ERROR;
   }

   IoMMUStatus = fp_table->config_bypass_domain_func (p_pcie_domain_hdl,
                                                      HAL_IOMMU_AARCH64_CCA_DOMAIN_TYPE);
   if (IoMMUStatus != HAL_IOMMU_ERR_OK)
   {
      PCIE_HOST_LOG_ERROR ("Unable to enable IoMMU bypass\n");
      return PCIE_ERROR;
   }

   IoMMUStatus = fp_table->domain_attach_func (p_pcie_domain_hdl,
                                               (void *)Io_mmu_cfg, 0x0, 0x0);
   if (IoMMUStatus != HAL_IOMMU_ERR_OK)
   {
      PCIE_HOST_LOG_ERROR ("Unable to attach IoMMU bypass\n");
      return PCIE_ERROR;
   }

   ++resources_ctxt->smmu_initialized;

   return PCIE_SUCCESS;
}

pcie_status_t pcie_ldo_op (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_pmic_config_t *pmic_config, int enable)
{
   STATIC npa_client_handle PcieReqClient = NULL;

   /* TODO: Revisit this routine. We need both Node and clients specific to
    *  per port, so both config need to come from config. For now since the
	*  NPA module doesn't keep reference count, instead it just ignores the
	*  second enable request and first disable will actually turn it off. So,
	*  for now just turn it ON once system wide and just use gdsc to control
	*  power. */

   if (enable == ENABLE)
   {
      if (PcieReqClient == NULL)
      {
         PcieReqClient = npa_create_sync_client(pmic_config->node_id, "pcie",
                                          NPA_CLIENT_REQUIRED);
         if (PcieReqClient == NULL)
         {
            PCIE_HOST_LOG_ERROR ("Unable to get ldo handle\n");
            return PCIE_ERROR;
         }
      }
      npa_issue_required_request(PcieReqClient, PMIC_NPA_MODE_ID_GENERIC_ACTIVE); // Enable
      return PCIE_SUCCESS;
   }

   else
   {
      npa_issue_required_request(PcieReqClient, PMIC_NPA_MODE_ID_GENERIC_OFF); // off calls
      PcieReqClient = NULL;
      return PCIE_SUCCESS;
   }    
}


/* Shouldn't be port specific? Confirm from Clk team */
ClockHandle    pcie_clock_handle = 0;

ClockHandle get_clock_handle(void)
{
   ClockResult res;

   if (pcie_clock_handle == 0)
   {
      res = Clock_Attach (&pcie_clock_handle, "PCIeRC");
      if (res != CLOCK_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to get Clk API handle\n");
         return 0;
      }
   }

   return pcie_clock_handle;
}

pcie_status_t pcie_clock_op (const char *clk_name, int enable)
{
   ClockResult   res;
   ClockIdType   clk_id;
   ClockHandle   clk_handle;

   if (clk_name == NULL)
      return PCIE_ERROR;

   clk_handle = get_clock_handle ();
   if (clk_handle == 0)
      return PCIE_ERROR;

   res = Clock_GetId (clk_handle, clk_name, &clk_id);
   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clk get ID failed %a\n", clk_name);
      return PCIE_ERROR;
   }

   if (enable)
      res = Clock_Enable (clk_handle, clk_id);
   else
      res = Clock_Disable (clk_handle, clk_id);

   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clk En/Dis failed %a\n", clk_name);
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_clks_set_freq (const clk_freq_cfg_t  *clk_freq)
{
   ClockResult   res;
   ClockIdType   clk_id;
   ClockHandle   clk_handle;

   clk_handle = get_clock_handle ();
   if (clk_handle == 0)
      return PCIE_ERROR;

   while (clk_freq->name != NULL)
   {
      uint32 freq_out = 0;

      res = Clock_GetId (clk_handle, clk_freq->name, &clk_id);
      if (res != CLOCK_SUCCESS)
         return PCIE_ERROR;

      res = Clock_SetFrequency (clk_handle, clk_id, clk_freq->freq, CLOCK_FREQUENCY_HZ_CLOSEST, &freq_out);
      if (res != CLOCK_SUCCESS)
         PCIE_HOST_LOG_ERROR ("Set frequency failed for %a\n", clk_freq->name);

      clk_freq++;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_clock_mux_op (const pcie_clk_mux_cfg_t  *clk_mux_cfg, int enable)
{
   ClockResult res;
   ClockIdType   clk_id;
   ClockHandle    clk_handle;
   UINT32 mux_val;

   if ((clk_mux_cfg == NULL) || (clk_mux_cfg->clk_name == NULL))
      return PCIE_ERROR;

   clk_handle = get_clock_handle ();
   if (clk_handle == 0)
      return PCIE_ERROR;

   res = Clock_GetId (clk_handle, clk_mux_cfg->clk_name, &clk_id);
   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Get mux ID failed for %a\n", clk_mux_cfg->clk_name);
      return PCIE_ERROR;
   }

   if (enable)
      mux_val = clk_mux_cfg->en_mux_val;
   else
      mux_val = clk_mux_cfg->dis_mux_val;

   res = Clock_SelectExternalSource (clk_handle, clk_id, 0, mux_val, 0, 0, 0, 0);
   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Set mux failed for %a\n", clk_mux_cfg->clk_name);
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_clocks_reset (const char ** clk_reset)
{
   ClockResult   res;
   ClockIdType   clk_id;
   ClockHandle   clk_handle;
   const char**  clk_names;

   if (clk_reset == NULL)
      return PCIE_ERROR;

   clk_handle = get_clock_handle ();
   if (clk_handle == 0)
      return PCIE_ERROR;

   clk_names = clk_reset;
   while (*clk_names != NULL)
   {
      res = Clock_GetId (clk_handle, *clk_names, &clk_id);
      if (res != CLOCK_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Clk get ID failed %a\n", *clk_names);
         return PCIE_ERROR;
      }

      if (Clock_ResetBlock (clk_handle, clk_id, CLOCK_RESET_ASSERT) != CLOCK_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to Assert BCR\n");
         return PCIE_ERROR;
      }

      pcie_osal_memory_barrier ();

      pcie_osal_busywait_us (100);

      if (Clock_ResetBlock (clk_handle, clk_id, CLOCK_RESET_DEASSERT) != CLOCK_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to Deassert BCR\n");
         return PCIE_ERROR;
      }
      ++clk_names;
   }

   pcie_osal_memory_barrier ();

   return PCIE_SUCCESS;
}

pcie_status_t pcie_vote_icb_clk_bw (npa_client_handle* handles, const pcieIcbClkBW_t* icb_bw, int enable)
{
   npa_client_handle npa_hndl;

   /* For now this routine assumes there is just 1 BW vote entry per port */
   if ((icb_bw == NULL) || (handles == NULL))
       return PCIE_ERROR;
 
   if (enable)
   {
      npa_hndl = *handles;
      if (npa_hndl == NULL)
      {
        npa_hndl = npa_create_sync_client_ex ("/icb/arbiter", icb_bw->npa_client_name,
                                              NPA_CLIENT_VECTOR, icb_bw->ms_size,
                                              (void *)icb_bw->ms_list);
 
        if (npa_hndl == NULL)
        {
           PCIE_HOST_LOG_ERROR ("Unable to create ICB BW npa handle\n");
           return PCIE_ERROR;
        }
      }
 
      npa_issue_vector_request (npa_hndl,
                                icb_bw->req_size/sizeof(npa_resource_state),
                                (npa_resource_state *)icb_bw->req_list );
 
      *handles = npa_hndl;
   }
   else  // Remove votes
   {
      npa_hndl = *handles;
 
      npa_complete_request (npa_hndl);
      npa_destroy_client (npa_hndl);
      *handles = NULL;
   }

   return PCIE_SUCCESS;
}

#if 0
pcie_status_t pcie_drive_ext_clocks (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_clocks_cfg_t *clock_config, uint32 enable)
{
   const char **clks;

   if (clock_config == NULL)
      return PCIE_INVALID_PARAM;

   if (clock_config->ext_clks == NULL)
      return PCIE_SUCCESS;

//   PCIE_HOST_LOG_ERROR ("%8ld : Ext clks\n", GetTimerCountus ()));
   clks = clock_config->ext_clks;
   while (*clks != NULL)
   {
      if (pcie_clock_op (*clks, enable) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to drive ext clk %a\n", *clks);
         return PCIE_ERROR;
      }
      ++clks;
   }

   return PCIE_SUCCESS;
}
#endif

pcie_status_t pcie_disable_clocks (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_clocks_cfg_t *clock_config)
{
   const char **clks;

   if ((clock_config == NULL) || (clock_config->core_clks == NULL) ||
       (clock_config->clk_reset == NULL) || (clock_config->clk_pwr == NULL) ||
       (clock_config->phy_pwr == NULL) || (clock_config->clk_freq == NULL))
      return PCIE_INVALID_PARAM;

   pcie_vote_icb_clk_bw (&rsrc_ctxt->icb_handles[0], clock_config->icb_bw, DISABLE);

   if (clock_config->clk_mux)  // Mux is optional in some targets
   {
      if (pcie_clock_mux_op (clock_config->clk_mux, DISABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to switch mux en\n");
         return PCIE_ERROR;
      }
   }

   clks = clock_config->core_clks;
   while (*clks != NULL)
   {
      if (pcie_clock_op (*clks, DISABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to turn OFF clk %a\n", *clks);
         return PCIE_ERROR;
      }
      ++clks;
   }

   /* GDSC Domain power off */
   if (pcie_clock_op (clock_config->clk_pwr, DISABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn OFF GDSC\n");
      return PCIE_ERROR;
   }

   if (pcie_clock_op (clock_config->phy_pwr, DISABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn OFF GDSC\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_enable_clocks (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_clocks_cfg_t *clock_config)
{
   const char **clks;

   if ((clock_config == NULL) || (clock_config->core_clks == NULL) ||
       (clock_config->clk_reset == NULL) || (clock_config->clk_pwr == NULL) ||
       (clock_config->phy_pwr == NULL) || (clock_config->clk_freq == NULL))
      return PCIE_INVALID_PARAM;

   /* GDSC Domain power up */
   if (pcie_clock_op (clock_config->clk_pwr, ENABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn ON GDSC\n");
      return PCIE_ERROR;
   }

   if (pcie_clock_op (clock_config->phy_pwr, ENABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn ON PHY GDSC\n");
      return PCIE_ERROR;
   }

   if (pcie_clocks_reset (clock_config->clk_reset) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("BCR reset failed\n");
      return PCIE_ERROR;
   }

   clks = clock_config->core_clks;
   while (*clks != NULL)
   {
      if (pcie_clock_op (*clks, ENABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to turn ON clk %a\n", *clks);
         return PCIE_ERROR;
      }
      ++clks;
   }

   if (pcie_clks_set_freq (clock_config->clk_freq) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Set freq failed\n");
      return PCIE_ERROR;
   }

   if (clock_config->clk_mux)  // Mux is optional in some targets
   {
      if (pcie_clock_mux_op (clock_config->clk_mux, ENABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to switch mux en\n");
         return PCIE_ERROR;
      }
   }

   pcie_vote_icb_clk_bw (&rsrc_ctxt->icb_handles[0], clock_config->icb_bw, ENABLE);

   return PCIE_SUCCESS;
}

/*******************************************************************************
 * GPIO related
********************************************************************************/
// TODO: Streamline these API's in this file

EFI_STATUS PcieSetGPIO (UINT32 GpioPin, UINT32 Level)
{
   EFI_TLMM_PROTOCOL       *TLMMProtocol = NULL;
   EFI_STATUS              Status;

   Status = gBS->LocateProtocol (&gEfiTLMMProtocolGuid, NULL,
                                (VOID **)&TLMMProtocol);
   if (EFI_ERROR (Status))
   {
    DEBUG ((EFI_D_WARN, "TLMM Protocol not found\r\n"));
    return Status;
   }

   Status = TLMMProtocol->GpioOut (EFI_GPIO_CFG (GpioPin, 0, 0, 0, 0), Level);
   if (EFI_ERROR (Status))
   {
    DEBUG ((EFI_D_WARN, "GpioOut failed\r\n"));
    return Status;
   }

   return Status;
}

STATIC EFI_STATUS PcieConfigureTLMMGPIO (CONST tlmm_gpio_cfg_t* tlmm_cfg)
{
   EFI_TLMM_PROTOCOL       *TLMMProtocol = NULL;
   EFI_STATUS              Status;

   if (tlmm_cfg == NULL)
      return EFI_INVALID_PARAMETER;

   Status = gBS->LocateProtocol (&gEfiTLMMProtocolGuid, NULL,
                                (VOID **)&TLMMProtocol);
   if (EFI_ERROR (Status))
   {
      DEBUG ((EFI_D_WARN, "TLMM Protocol not found\r\n"));
      return Status;
   }

   Status = TLMMProtocol->ConfigGpio (EFI_GPIO_CFG (
                                       tlmm_cfg->gpio_num,
                                       tlmm_cfg->func_sel,
                                       tlmm_cfg->direction,
                                       tlmm_cfg->pull,
                                       tlmm_cfg->drive_strength),
                                     TLMM_GPIO_ENABLE);
   if (EFI_ERROR (Status))
   {
      DEBUG ((EFI_D_WARN, "ConfigGpio failed\r\n"));
      return Status;
   }

   if (tlmm_cfg->direction == GPIO_OUTPUT)
   {
      Status = TLMMProtocol->GpioOut (EFI_GPIO_CFG (
                                         tlmm_cfg->gpio_num,
                                         tlmm_cfg->func_sel,
                                         tlmm_cfg->direction,
                                         tlmm_cfg->pull,
                                         tlmm_cfg->drive_strength),
                                      tlmm_cfg->value);
      if (EFI_ERROR (Status))
      {
        DEBUG ((EFI_D_WARN, "GpioOut failed\r\n"));
        return Status;
      }
   }

   return Status;
}

STATIC EFI_STATUS PcieConfigurePMICGPIO (CONST pmic_gpio_cfg_t* pmic_cfg)
{
   EFI_QCOM_PMIC_GPIO_PROTOCOL  *PmicGpioProtocol = NULL;
   EFI_PM_GPIO_PERIPH_INDEX      gpio_num;
   UINT32                        pmic_index;
   EFI_STATUS                    Status;

   if (pmic_cfg == NULL)
      return EFI_INVALID_PARAMETER;

   pmic_index = pmic_cfg->pmic_index;
   gpio_num = pmic_cfg->gpio_num;

   Status = gBS->LocateProtocol (&gQcomPmicGpioProtocolGuid, NULL,
                                 (VOID **)&PmicGpioProtocol);
   if (EFI_ERROR (Status))
   {
      DEBUG ((EFI_D_WARN, "PMIC Protocol not found\r\n"));
      return Status;
   }

   Status = PmicGpioProtocol->CfgMode (pmic_index, gpio_num, EFI_PM_GPIO_DIG_OUT);

   Status |= PmicGpioProtocol->SetVoltageSource (pmic_index, gpio_num,
                                                 pmic_cfg->vsrc);

   Status |= PmicGpioProtocol->SetOutBufCfg (pmic_index, gpio_num,
                                             pmic_cfg->buff_cfg);

   Status |= PmicGpioProtocol->SetOutSrcCfg (pmic_index, gpio_num,
                                             pmic_cfg->src_cfg);

   Status |= PmicGpioProtocol->SetOutDrvStr (pmic_index, gpio_num,
                                             pmic_cfg->drv_str);

   Status |= PmicGpioProtocol->SetOutputLevel (pmic_index, gpio_num,
                                               pmic_cfg->gpio_level);

   Status |= PmicGpioProtocol->Enable (pmic_index, gpio_num, TRUE);

   if (EFI_ERROR (Status))
      DEBUG ((EFI_D_WARN, "PMIC GPIO Config Failed\r\n"));

   return Status;
}

EFI_STATUS PcieConfigureGPIOs (CONST pcie_gpio_cfg_t * pcie_gpio_cfg)
{
   EFI_STATUS  Status = EFI_SUCCESS;

   if (pcie_gpio_cfg == NULL)
      return EFI_INVALID_PARAMETER;

   switch (pcie_gpio_cfg->cfg_type)
   {
      case MSM_GPIO:
        Status = PcieConfigureTLMMGPIO (&pcie_gpio_cfg->pcie_pin.tlmm);
        break;
    
      case PMIC_GPIO:
        Status = PcieConfigurePMICGPIO (&pcie_gpio_cfg->pcie_pin.pmic);
        break;
    
      case DELAY:
        pcie_osal_busywait_us (pcie_gpio_cfg->pcie_pin.delay_us);
        break;
    
      case NONE:
      case PMIC_MPP:
      default:
        break;
   }

   return Status;
}



EFI_STATUS PcieConfigureGPIOs (CONST pcie_gpio_cfg_t * pcie_gpio_cfg);
EFI_STATUS PcieSetGPIO (UINT32 GpioPin, UINT32 Level);

pcie_status_t pcie_osal_gpio_set (uint32 pin, boolean level)
{
   if (PcieSetGPIO (pin, level) != EFI_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Set GPIO failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_initialize_gpios (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_gpio_cfg_t *gpio_cfg)
{
   EFI_STATUS Status = EFI_DEVICE_ERROR;
   int i;

   if ((gpio_cfg == NULL) || (rsrc_ctxt == NULL))
      return PCIE_ERROR;

   if (rsrc_ctxt->gpio_initialized == TRUE)
      return PCIE_SUCCESS;

   for (i = 0; gpio_cfg[i].cfg_type != NONE; ++i)
   {
      Status = PcieConfigureGPIOs (&gpio_cfg[i]);

      if (Status != EFI_SUCCESS)
         break;
   }

   if (Status == EFI_SUCCESS)
      rsrc_ctxt->gpio_initialized = TRUE;

   return PCIE_SUCCESS;
}

pcie_status_t enable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg)
{
   pcie_status_t res;

   if ((port_cfg == NULL) || (resources_ctxt == NULL))
      return PCIE_ERROR;

   if (port_cfg->driver_config == NULL)
      return PCIE_SUCCESS;

   if (pcie_ldo_op (resources_ctxt, port_cfg->driver_config->pmic_cfg, ENABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn ON ldos\n");
      return PCIE_ERROR;
   }

   res = pcie_enable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg);
   if (res != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clock init failed\n");
      return PCIE_ERROR;
   }

   if (pcie_configure_smmu (resources_ctxt, port_cfg->driver_config->iommu_cfg) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("SMMU init failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t disable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg)
{
   pcie_status_t res;

   if ((port_cfg == NULL) || (resources_ctxt == NULL))
      return PCIE_ERROR;

   if (port_cfg->driver_config == NULL)
      return PCIE_SUCCESS;

   res = pcie_disable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg);
   if (res != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clock deinit failed\n");
      return PCIE_ERROR;
   }

   if (pcie_ldo_op (resources_ctxt, port_cfg->driver_config->pmic_cfg, DISABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn OFF ldos\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

/* Need to be called after atleast one port is up and before L1ss is enabled
 * Need to be called only once, so status is tracked locally */
pcie_status_t enable_rsc_module(void)
{
  VOID                       *RscHandle = NULL;
  EFI_RSC_PROTOCOL           *PcieRscProtocolIntf = NULL;
  EFI_STATUS                 Status = EFI_SUCCESS;
  static UINT32              rsc_init_complete = 0;

  if (rsc_init_complete)
     return PCIE_SUCCESS;

  Status = gBS->LocateProtocol (&gEfiRscProtocolGuid, NULL,
                               (VOID **)&PcieRscProtocolIntf);
  if (EFI_ERROR (Status))
  {
     PCIE_HOST_LOG_ERROR ("Unable to find Rsc protocol, ignoring to continue..!!\n");
     ++rsc_init_complete;
     return PCIE_SUCCESS; // On this platform RSC init is not required if PLIM not present
  }

// TODO: Needs Clean Up
//   pcie_ldo_op (NULL, NULL, 1);

  pcie_osal_busywait_us (1000);

  Status = PcieRscProtocolIntf->rsc_instance_init("pcie", &RscHandle);
  if (EFI_ERROR (Status))
  {
    PCIE_HOST_LOG_ERROR ("PCIe PLIM RscInit Failed\r\n");
    return PCIE_ERROR;
  }

  ++rsc_init_complete;

  return PCIE_SUCCESS;
}

//USB4_PROTOCOL   *PcieUsb4Intf = NULL;

pcie_status_t init_pcie_tunneled_port (pcie_port_config_t* port_config_ptr)
{
#if 0
   EFI_STATUS  Status = EFI_SUCCESS;
   UINT32   port_idx;
   BOOLEAN  usb4_result;

   if (port_config_ptr == NULL)
     return PCIE_ERROR;

   if (PcieUsb4Intf == NULL)
   {
      Status = gBS->LocateProtocol (&gQcomUsb4ProtocolGuid, NULL,
                                    (VOID **)&PcieUsb4Intf);
      if (EFI_ERROR (Status))
      {
        PCIE_HOST_LOG_ERROR ("Unable to find USB4 protocol\n");
        return PCIE_ERROR;
      }
   }

   port_idx = port_config_ptr->hw_rp_index;
   usb4_result = PcieUsb4Intf->QueryPathEnable (PcieUsb4Intf, USB4_CLIENT_PCIE, port_idx);

   if (usb4_result == FALSE)
   {
     PCIE_HOST_LOG_ERROR ("Unable to enable PCIe %d path over USB4\n", port_idx);
     return PCIE_ERROR;
   }
#endif
   return PCIE_SUCCESS;
}

#include "Protocol/EFISmmuMapSid.h"
EFI_SMMU_MAP_SID_PROTOCOL* SmmuMapSidIntf;

pcie_status_t map_mem_smmu_sid (uint32 smmu_config, uint32 rbdf, void* base_addr, uint64 size_bytes, void** map_handle_ptr)
{
   EFI_STATUS  Status = EFI_SUCCESS;

   if (SmmuMapSidIntf == NULL)
   {
      Status = gBS->LocateProtocol (&gEfiSmmuMapSidProtocolGuid, NULL,
                                    (VOID **)&SmmuMapSidIntf);
      if (EFI_ERROR (Status))
      {
        PCIE_HOST_LOG_ERROR ("Unable to find SMMU Sid mapping protocol\n");
        return PCIE_ERROR;
      }
   }

   Status = SmmuMapSidIntf->MapPcieSid (rbdf, base_addr, size_bytes, map_handle_ptr);
   if (EFI_ERROR (Status))
      PCIE_HOST_LOG_ERROR ("Failed to map Address to SID 0x%lX to %X\n", base_addr, rbdf);
   
   return Status;
}

pcie_status_t unmap_smmu_sid (void* map_handle)
{
   EFI_STATUS  Status = EFI_SUCCESS;

   if (SmmuMapSidIntf == NULL)
   {
      Status = gBS->LocateProtocol (&gEfiSmmuMapSidProtocolGuid, NULL,
                                    (VOID **)&SmmuMapSidIntf);
      if (EFI_ERROR (Status))
      {
        PCIE_HOST_LOG_ERROR ("Unable to find SMMU Sid mapping protocol\n");
        return PCIE_ERROR;
      }
   }

   Status = SmmuMapSidIntf->UnmapSid (map_handle);
   if (EFI_ERROR (Status))
      PCIE_HOST_LOG_ERROR ("Failed to un-map address for SID\n");
   
   return Status;
}

/*******************************************************************************
 *                         Unused functions
 ******************************************************************************/
#ifdef UNUSED_APIS_ADD_IMPLEMENTATION_AND_MOVE_OUT
uint64 pcie_osal_get_elapsed_time (uint64 t1, uint64 t2, pcie_osal_time_unit_t unit)
{
}

int pcie_osal_mem_region_unmap (pcie_osal_mem_info_t *mem_info)
{
}

pcie_osal_pa_t pcie_osal_va_to_pa (pcie_osal_va_t va)
{
}

void pcie_osal_cache_ctrl (pcie_osal_cache_op_t op, pcie_osal_va_t va, size_t size)
{
}

int pcie_osal_sync_init (pcie_osal_sync_t *sync, uint32 flags)
{
}

int pcie_osal_sync_deinit (pcie_osal_sync_t *sync)
{
}

void pcie_osal_sync_enter (pcie_osal_sync_t *sync)
{
}

void pcie_osal_sync_leave (pcie_osal_sync_t *sync)
{
}

int pcie_osal_event_init (pcie_osal_event_t *event)
{
}

int pcie_osal_event_deinit (pcie_osal_event_t *event)
{
}

void pcie_osal_event_reset (pcie_osal_event_t *event)
{
}

void pcie_osal_event_wait (pcie_osal_event_t *event)
{
}

void pcie_osal_event_signal (pcie_osal_event_t *event)
{
}

void pcie_osal_sleep (uint32 time_ms, boolean non_deferrable)
{
   gBS->Stall (time_us);
}

int pcie_osal_thread_spawn (pcie_osal_thread_t *thread, const char *name,
                           pcie_osal_cb_t fcn, void *ctxt, uint32 priority)
{
}

void* pcie_osal_memset (void *ptr, uint8 val, size_t size)
{
}

size_t pcie_osal_memscpy (void *dst, size_t dst_size, const void *src, size_t src_size)
{
}

size_t pcie_osal_strlcpy (char *dst, const char *src, size_t dst_size)
{
}

uint32 pcie_osal_atomic_set (uint32 *ptr, uint32 value)
{
}

uint32 pcie_osal_atomic_read (uint32 *ptr)
{
}

void pcie_osal_atomic_set_bit (uint32 *ptr, uint32 bit)
{
}

void pcie_osal_atomic_clear_bit (uint32 *ptr, uint32 bit)
{
}

uint32 pcie_osal_atomic_inc (uint32 *ptr)
{
}

uint32 pcie_osal_atomic_dec (uint32 *ptr)
{
}

int pcie_osal_isr_unregister (pcie_osal_irq_t *irq)
{
}

int pcie_osal_irq_disable (pcie_osal_irq_t *irq)
{
}

boolean pcie_osal_irq_is_set (pcie_osal_irq_t *irq)
{
}

int pcie_osal_isq_mask (pcie_osal_irq_t *irq)
{
}

int pcie_osal_isq_unmask (pcie_osal_irq_t *irq)
{
}

int pcie_osal_irq_ack (pcie_osal_irq_t *irq)
{
}

#endif


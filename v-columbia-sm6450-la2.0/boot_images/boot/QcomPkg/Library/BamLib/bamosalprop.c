/**
  @file bamosalprop.c
  @brief
  This file contains implementation of interfaces for BAM device config.

*/
/*
===============================================================================
    Copyright (c) 2016, 2019, 2021 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================
*/
#include "com_dtypes.h"
#include "bamosal.h"
#include "bam.h"
#include "bamtgtcfg.h"
#include "DTBExtnLib.h"
#include "DALSys.h"
#include <Library/DebugLib.h>

#define BAM_NODE_NAME   "/soc/bam_config"

#define BAM_DT_CHECK_ERROR(x)                                         \
{                                                                     \
  if (ret_value) {                                                    \
    DEBUG((EFI_D_ERROR,"%s, ret Value = %d\n", u##x, ret_value));     \
    goto __EXIT;                                                      \
  }                                                                   \
}

extern bam_target_config_type* bam_tgt_config_ptr;

/* ============================================================================
**  Function : bam_osal_init
** ============================================================================
*/
/**
  Initializes BAM device config .

  Initializes OSAL Interfaces. Performs any initialization pertaining to the
  BAM device config.

  @param  None

  @return
  None.

*/
void bam_osal_init(void)
{
  bam_target_config_type *dcfg = NULL;
  void* blob = NULL; 
  fdt_node_handle hNode;
  int ret_value = -1;
  uint32 prop_size = 0;

  bam_tgt_config_ptr = NULL;

  ret_value = fdt_get_blob_handle(&blob, DEFAULT_BLOB_ID);
  BAM_DT_CHECK_ERROR("Unable to get blob handle");
  
  ret_value = fdt_get_node_handle(&hNode, blob, BAM_NODE_NAME);
  BAM_DT_CHECK_ERROR("Unable to get BAM node handle");
  
  dcfg = bam_osal_malloc(sizeof(bam_target_config_type));
  if(!dcfg) {
    ret_value = -1;
    BAM_DT_CHECK_ERROR("Failed malloc BAM config");
  }

  DALSYS_memset((void *)dcfg, 0, sizeof(bam_target_config_type));
	
  ret_value = fdt_get_uint64_prop(&hNode, "bam_pa", (uint64 *)&dcfg->bam_pa);
  BAM_DT_CHECK_ERROR("Unable to get bam_pa");

  ret_value = fdt_get_uint32_prop(&hNode, "options", (uint32 *)&dcfg->options);
  BAM_DT_CHECK_ERROR("Unable to get BAM options");

  ret_value = fdt_get_uint32_prop(&hNode, "cfg_bits", (uint32 *)&dcfg->cfg_bits);
  BAM_DT_CHECK_ERROR("Unable to get BAM cfg_bits");

  ret_value = fdt_get_uint8_prop(&hNode, "ee", (uint8 *)&dcfg->ee);
  BAM_DT_CHECK_ERROR("Unable to get BAM ee");

  ret_value = fdt_get_prop_size(&hNode, "sec_config", &prop_size);
  BAM_DT_CHECK_ERROR("Unable to get BAM sec_config prop size");

  if (64 == (8 * prop_size)) {
    ret_value = fdt_get_uint64_prop(&hNode, "sec_config", (uint64 *)&dcfg->sec_config);
  } else {
    ret_value = fdt_get_uint32_prop(&hNode, "sec_config", (uint32 *)&dcfg->sec_config);
  }
  BAM_DT_CHECK_ERROR("Unable to get BAM sec_config");

  ret_value = fdt_get_uint32_prop(&hNode, "size", (uint32 *)&dcfg->size);
  BAM_DT_CHECK_ERROR("Unable to get BAM size"); 

__EXIT:
  if (ret_value) {
    if(dcfg)
    {
      bam_osal_free(dcfg);
      dcfg = NULL;
    }
  }

  bam_tgt_config_ptr = dcfg;
}

/* ============================================================================
**  Function : bam_osal_deinit
** ============================================================================
*/
/**
  DeInitializes OSAL Interfaces.

  Deinitializes OSAL Interfaces. Performs any deinitialization pertaining to the
  OS specific APIs.

  @param  None

  @return
  None.

*/
void bam_osal_deinit(void)
{
  if(bam_tgt_config_ptr) {
    bam_osal_free(bam_tgt_config_ptr);
    bam_tgt_config_ptr = NULL;
  }
}


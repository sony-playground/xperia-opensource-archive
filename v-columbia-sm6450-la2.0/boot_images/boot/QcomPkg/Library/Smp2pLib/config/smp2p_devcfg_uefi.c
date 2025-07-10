/*===========================================================================

                     SMP2P DEVICE CONFIGURATION

        This file provides the device configuration for SMP2P

  ---------------------------------------------------------------------------
  Copyright (c) 2018, 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header:

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/26/17   jlg     Established settings interface
===========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/

#include "IPCC.h"
#include "smem_type.h"
#include "smp2p_settings.h"

/*===========================================================================
                    CONSTANT / MACRO DECLARATIONS
===========================================================================*/

/*===========================================================================
                      GLOBAL DATA DEFINATION
===========================================================================*/
/** Local processor info */
const smp2p_proc_info_type smp2p_devcfg_proc_info = 
{ 
  /** This host name */
  "apps",
  
  /** This host SMEM ID */
  SMEM_APPS,
  
  /** Feature flags supported */
  SMP2P_FFLAGS_SSR_HANDSHAKE,
  
  /** Max number of entries */
  16
};

/** Interrupt info for connected subsystems */
const smp2p_interrupt_info_type smp2p_devcfg_interrupt_info[] = 
{
	
  /** SLPI */
  {
    /* destination */
    SMEM_SSC,
    
    /* destination host type */
    EFI_IPCC_C_SLPI,
    
    /* interrupt register */
    SMP2P_IRQ,
  },
  /** WPSS */
  {
    /* destination */
    SMEM_WPSS,
    
    /* destination host type */
    EFI_IPCC_C_WPSS,
    
    /* interrupt register */
    SMP2P_IRQ,
  },
  
  /** ADSP */
  {
    /* destination */
    SMEM_ADSP,
    
    /* destination host type */
    EFI_IPCC_C_LPASS,
    
    /* interrupt register */
    SMP2P_IRQ,
  },
  
  /** CDSP */
  {
  /* destination */
    SMEM_CDSP,

  /* destination host type */
    EFI_IPCC_C_CDSP,

  /* interrupt register */
   SMP2P_IRQ,
  },
  
  /** MPSS */
  {
    /* destination */
    SMEM_MODEM,
    
    /* destination host type */
    EFI_IPCC_C_MPSS,
    
    /* interrupt register */
    SMP2P_IRQ,
  },
 
  
  
  /** END */
  {
    /* destination */
    SMEM_INVALID_HOST,

    /* destination host type */
    SMP2P_NULL_CLIENT,

    /* interrupt register */
    SMP2P_NULL_SIGNAL,
  },
};

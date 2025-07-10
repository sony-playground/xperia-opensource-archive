/*------------------------------------------------------------------------------
   SMP2P_SETTINGS.H  - SMP2P Settings Interface
------------------------------------------------------------------------------*/
/*!
  @file
    smp2p_settings.h

  @brief
    This file contains the SMP2P settings interface structure definitions.
*/

/*------------------------------------------------------------------------------
     Copyright  2017, 2020 Qualcomm Technologies Incorporated.
     All rights reserved.
------------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.0/QcomPkg/Library/Smp2pLib/interface/smp2p_settings.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/26/17   jlg     Initial version; created settings interface for SMP2P
===========================================================================*/
#ifndef SMP2P_SETTINGS_H_
#define SMP2P_SETTINGS_H_

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "smem_type.h"
#include "comdef.h"
#include <Protocol/EFIIPCC.h>

/*===========================================================================
                        DEFINITIONS
===========================================================================*/
/* Feature flags (smp2p_header_version_type.flags, 24 bits) */
#define SMP2P_FFLAGS_SSR_HANDSHAKE      0x000001

#define SMP2P_FFLAGS_SUPPORTED  (SMP2P_FFLAGS_SSR_HANDSHAKE)
#define SMP2P_FFLAGS_REQUESTED  (smp2p_proc_info.fflags)

#define SMP2P_NULL_SIGNAL ((EFIIPCC_Signal)-1)
#define SMP2P_NULL_CLIENT EFI_IPCC_C_TOTAL

/* Defined by MPROC Arch */
#define SMP2P_IRQ 2

/*===========================================================================
                        TYPE DEFINITIONS
===========================================================================*/
/** Defines the structure with information about this host */
typedef struct {
  /** This host name */
  const char     *name;
  /** This host SMEM ID */
  smem_host_type host;
  /** Feature flags supported */
  uint32         fflags;
  /** Max number of entries */
  uint16         max_entries;
} smp2p_proc_info_type;

/** Defines the structure with information on how to map, send and receive
 *  interrupts. */
typedef struct
{
  smem_host_type          dest;
  /** destination host type */
  EFIIPCC_Client             processor;
  /** outgoing interrupt register */
  EFIIPCC_Signal             irq;
} smp2p_interrupt_info_type;

#endif /* SMP2P_SETTINGS_H_ */

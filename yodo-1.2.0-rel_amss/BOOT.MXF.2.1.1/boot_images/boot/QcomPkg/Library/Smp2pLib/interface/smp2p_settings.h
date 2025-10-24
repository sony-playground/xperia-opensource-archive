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
     Copyright  2017, 2020, 2022 Qualcomm Technologies Incorporated.
     All rights reserved.
------------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/Smp2pLib/interface/smp2p_settings.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/15/22   mad     Carved out constants for soc-specific settings in DeviceTree
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
#include "smp2p_defines.h"

/*===========================================================================
                        DEFINITIONS
===========================================================================*/

#define SMP2P_FFLAGS_SUPPORTED  (SMP2P_FFLAGS_SSR_HANDSHAKE)
#define SMP2P_FFLAGS_REQUESTED  (smp2p_proc_info.fflags)

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
  UINT32         fflags;
  /** Max number of entries */
  UINT32         max_entries;
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

int smp2p_dt_parse(void);
#endif /* SMP2P_SETTINGS_H_ */

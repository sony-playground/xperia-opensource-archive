/** 
 * Utils
 *  
 * Copyright (c) 2021 - 2022 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/26/21   yg      Initial version

=============================================================================*/
#ifndef __PCIE_TEST_UTILS_H___
#define __PCIE_TEST_UTILS_H___

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>
#include "Library/pcie_dtypes.h"
#include "pcie_host_r.h"

#define LOCAL_ANALOG_TEST     1
#define LOCAL_DIGITAL_TEST    2
#define REMOTE_DIGITAL_TEST   3
#define L0_TEST               4
#define MEMIO_TEST            5
#define EPCFG_TEST            6


#define MAX_PCIE_CORES  8

typedef struct {
   pcie_dev_t *ep_handle;
   pcie_dev_t *rc_handle;
   pcie_dev_probe_cb_payload_t ep_info;
   uint32 RcIdx;
}dev_handle_info_type;

static inline uint32 READ_CFG_REG(volatile uint32* CfgSpcAddr, uint32 RegOffset)
{
   uint32 val;
   val = (*((CfgSpcAddr) + ((RegOffset)/4)));
//   AsciiPrint ("RD :  0x%09X => 0x%08X\n", ((CfgSpcAddr) + ((RegOffset)/4)), val);
   return val;
}


static inline void WRITE_CFG_REG(volatile uint32* CfgSpcAddr, uint32 RegOffset, uint32 val)
{
//   AsciiPrint ("WR :  0x%09X <= 0x%08X\n", ((CfgSpcAddr) + ((RegOffset)/4)), val);
   ((*((CfgSpcAddr) + ((RegOffset)/4))) = (val));
}

static inline uint32 read_mmio_reg32 (volatile uint32* base_addr, uint32 offset)
{
   return *(base_addr + (offset / 4));
}

static inline void write_mmio_reg32 (volatile uint32* base_addr, uint32 offset, uint32 val)
{
   *(base_addr + (offset / 4)) = val;
}

EFI_STATUS SetSocGpio (UINTN Pin, UINTN Level);


EFI_STATUS GetTargetPlatformInfo (EFIChipInfoIdType        *ChipIdPtr, 
                                  EFIChipInfoVersionType   *ChipVerPtr, 
                                  EFIChipInfoFamilyType    *ChipFamilyPtr, 
                                  UINT32                   *PlatTypePtr);

// TODO: keep the API's names and args consistent or move to different interface/implementation file
pcie_status_t enumerate_pcie_port (uint32 port_idx);

pcie_status_t get_enumerated_dev_handle (uint32 port_idx, dev_handle_info_type* dev_handle_info_ptr);

pcie_status_t poweroff_pcie_port (uint32 port_idx);

pcie_status_t get_link_status (UINTN CoreIdx, pcie_link_status_t *link_status_info_ptr);

#define ASPM_TYPE_L0s                   0
#define ASPM_TYPE_L11ss                 11
#define ASPM_TYPE_L12ss                 12

EFI_STATUS RunASPMTest (UINTN CoreIdx, uint32 aspm_type);

EFI_STATUS RunCfgSpaceTest (UINTN CoreIdx);

EFI_STATUS RunMemIOTest (UINTN CoreIdx);

#endif


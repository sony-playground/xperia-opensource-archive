#ifndef ___EFI_PCIE_PLAT_POLICY_H__
#define ___EFI_PCIE_PLAT_POLICY_H__

/** @file
 *
 * UEFI Protocol interface for PCIe platform policy for Qcom platforms
 *  
 * Copyright (c) 2020 - 2021 Qualcomm Technologies, Inc. All rights reserved.
 *
**/
/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/09/21   yg      Changed notion of API to disable
 10/08/20   yg      Draft version

=============================================================================*/

#include <Uefi.h>

/* External global reference to the Qcom PCIe platform policy Protocol GUID */
extern EFI_GUID gEfiPciePlatPolicyProtocolGuid;

/* Protocol GUID definition. { 9847B2BD-1CB6-4DA0-B970-EDE4A558E588 } */
#define EFI_PCIE_PLAT_POLICY_PROTOCOL_GUID \
                        {0x9847B2BD, 0x1CB6, 0x4DA0, {0xB9, 0x70, 0xED, 0xE4, \
                                                      0xA5, 0x58, 0xE5, 0x88}}

/*
 *   Document the version changes here
 *   V 1.0
 *      Initial version
 * */
#define PCIE_PLAT_POLICY_VER_INITIAL        0x00010000

/* Current protocol version */
#define PCIE_PLAT_POLICY_VERSION         PCIE_PLAT_POLICY_VER_INITIAL

/*******************************************************************************
 *
 *   Interface type definitions
 *
 ******************************************************************************/

typedef enum
{
   PcieHwConfigNone = 0,

  /* This setting is SOC specific setting. Setting will be applied on the SOC/
   * platform where this is applicable.
   * Default value for HW PHY Mux config is all ports 2 lanes, when we need
   * different option call the API. This option affects at the hardware level,
   * and should be reflective of what the board layout has been set. Note that
   * this is different from lane/link width changes that we can request using
   * the capability registers.
   * Port : Required, Ports mask
   * Arg  : Required, indicates the Lane count setting need to be applied to
   *        all port specified in the Port mask  */
   PcieHwPhyLanesConfig = 1,

   PcieLaneConfigMaxEntries,
}PcieHwConfigType;

/* Any mask bit set to 1 will disable that port, others remain unchanged */
typedef
EFI_STATUS
(EFIAPI *DISABLE_PCIE_ROOT_PORTS) (IN UINT32 PortsMask);

/* Set or change a HW configuration. Port/Arg arguments are optional based on
 * the config in question. Refer to specific config for more info.
 *
 * Returns:
 * EFI_SUCCESS     : Successfully applied the config change requested
 * EFI_NO_MAPPING  : Config is not applicable for the SOC/platform, should
 *                   not be treated as an error condition.
 * EFI_UNSUPPORTED : Unsupported config option.
 * EFI_NOT_READY   : If config requires port/device being ready and is not
 * EFI_DEVICE_ERROR : Encountered error while applying the config change
 * EFI_INVALID_PARAMETER : Parameter invalid for the config requested.
 *
 * */
typedef
EFI_STATUS
(EFIAPI *SET_PCIE_HW_CONFIG) (IN PcieHwConfigType  HwCfg,
                              IN UINT32            Port    OPTIONAL,
                              IN UINTN             Arg     OPTIONAL);

/*===========================================================================
                    PROTOCOL INTERFACE
===========================================================================*/

/* Each SOC platform comes with its own default settings. If the default
 * settings work and same as desired settings these API's don't need to be
 * called. Only use this inteface to change from default settings.
 *
 * These settings affect only during initial port linkup/enumeration. So these
 * should be set on Protocol installed notification, immediately after the
 * notification enumeration would start. So any updates after enumeration will
 * NOT take effect until subsequent linkdown/linkup and enumeration */
typedef struct {
  UINT64                      Version;

  DISABLE_PCIE_ROOT_PORTS     DisablePcieRootPorts;
  SET_PCIE_HW_CONFIG          SetPcieHwConfig;

} EFI_PCIE_PLAT_POLICY_PROTOCOL;

#endif  /* ___EFI_PCIE_PLAT_POLICY_H__ */


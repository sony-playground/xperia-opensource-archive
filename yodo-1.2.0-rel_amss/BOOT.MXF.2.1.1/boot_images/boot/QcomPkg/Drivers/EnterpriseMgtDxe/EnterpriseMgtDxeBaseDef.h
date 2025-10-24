/**
  @file EnterpriseMgtDxeBaseDef.h
  @brief EnterpriseMgt driver base data structure definitions.
*/
/*=============================================================================
  Copyright (c) 2020,2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtDxeBaseDef.h#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#ifndef __ENTERPRISEMGTBASEDEF_H__
#define __ENTERPRISEMGTBASEDEF_H__

#include <Protocol/EFIAcpiPlatform.h>
#include <Library/IoLib.h>

/* Macros defining MAX values */
#define MAX_ENT_MGT_REGISTERS (32)
#define MAX_HLOS_MANAGED_DEVICES (ACPI_MAX_DSDT_DEVICES)
#define MAX_DEVICE_NAME_SIZE (ACPI_MAX_DEVICE_NAME_SIZE)

/* Macros for EnterpriseMgt0 LOCK bit and values */
#define ENT_MGT_LOCK_BIT_POSITION (1)
#define ENT_MGT_LOCK_BIT_VALUE (1)

#define MAX_ENT_MGT_BIT_POSITION (31)

// Helper macros to map functions for reading/writing to EnterpriseMgt HW registers.
#define ENT_MGT_REG_READ(x) MmioRead32(x)
#define ENT_MGT_REG_WRITE(x, y) MmioWrite32(x, y)

#pragma pack(1)

/* Structure defining the Register bit-values*/
typedef struct _ENT_MGT_REG_POLICY {
    UINT32 RegisterAddress;
    UINT32 BitMask;
    UINT32 Value;
} ENT_MGT_REG_POLICY;

/* Structure defining the ACPI device node STA method name */
typedef struct _HLOS_MNG_DEVICE {
    UINT8 DeviceName[MAX_DEVICE_NAME_SIZE];
}HLOS_MNG_DEVICE;

/* Structure to hold processed client policy information */
typedef struct _ENT_MGT_PROCESSED_POLICY {
    UINT32             NumMgtXRegs;
    UINT32             NumberOfHlosDevices;
    ENT_MGT_REG_POLICY MgtXRegList[MAX_ENT_MGT_REGISTERS];
    HLOS_MNG_DEVICE    HlosDeviceList[MAX_HLOS_MANAGED_DEVICES];
} ENT_MGT_PROCESSED_POLICY;

/* Structure defining the Interface register bit details*/
typedef struct _INTERFACE_ID_REGISTER {
    UINT32 RegisterAddress;
    UINT8  BitPosition;
    UINT8  BitValue;
}INTERFACE_ID_REGISTER;

/* Structure defining the interface node */
typedef struct _INTERFACE_NODE {
    UINT32 Size;
    UINT32 NumberOfInterfaceIDs;
    UINT32 NumberOfHlosManagedDevices;
    UINT32 InterfaceIDOffset;
    UINT32 HlosManagedDeviceOffset;
    INTERFACE_ID_REGISTER *reg;
    HLOS_MNG_DEVICE *pDeviceList;
} INTERFACE_NODE;

/* Structure defining the feature node */
typedef struct _FEATURE_NODE {
    UINT32 SizeofFeatureNode;
    UINT32 FeatureType;
    UINT32 NumInterfaces;
    UINT32 InterfaceOffset;
    INTERFACE_NODE *InterfaceList;
} FEATURE_NODE;

/* Structure defining the overall platform configurations */
typedef struct _ENT_MGT_CONFIG {
    UINT32 Size;
    UINT16 Revision;
    UINT16 Reserved;
    UINT32 VendorId;
    UINT32 NumberOfFeatures;
    UINT32 FeatureNodeOffset;
    FEATURE_NODE *FeatureNodeList;
} ENT_MGT_CONFIG;

#pragma pack()

#endif /*__ENTERPRISEMGTBASEDEF_H__*/
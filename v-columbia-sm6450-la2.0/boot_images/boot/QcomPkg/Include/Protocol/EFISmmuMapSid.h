/** 
 *
 * UEFI Protocol interface to map memory for a particular SID
 *  
 * Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/25/21           Initial version

=============================================================================*/

#include <Uefi.h>

#ifndef ___EFI_SMMU_MAP_SID_PROTOCOL_H__
#define ___EFI_SMMU_MAP_SID_PROTOCOL_H__

/* External global reference to the SMMU_MAP_SID Protocol GUID */
extern EFI_GUID gEfiSmmuMapSidProtocolGuid;


/* Protocol GUID definition. { 969445C5-94A0-41A4-8DE7-3F233349E1DD } */
#define EFI_SMMU_MAP_SID_PROTOCOL_GUID \
   { 0x969445C5, 0x94A0, 0x41A4, {0x8D, 0xE7, 0x3F, 0x23, 0x33, 0x49, 0xE1, 0xDD }}

/*
 *   Document the version changes here
 *   V 1.0
 *      Initial version
 * */
#define SMMU_MAP_SID_VER_INITIAL        0x00010000

/* Current protocol version */
#define EFI_SMMU_MAP_SID_PROTOCOL_VER   SMMU_MAP_SID_VER_INITIAL

/*******************************************************************************
 *
 *   Interface type definitions
 *
 ******************************************************************************/

typedef EFI_STATUS  (*MAP_PCIE_SID) (IN  UINT32 RBdf, IN VOID* HostAddr,
                                     IN  UINTN ByteCnt, OUT VOID** MapHandlePtr);

typedef EFI_STATUS  (*UNMAP_SID) (IN  VOID* MapHandle);


/*===========================================================================
                    PROTOCOL INTERFACE
===========================================================================*/

typedef struct {
  UINT64                          Version;
  MAP_PCIE_SID                    MapPcieSid;
  UNMAP_SID                       UnmapSid;
}EFI_SMMU_MAP_SID_PROTOCOL;

extern EFI_SMMU_MAP_SID_PROTOCOL* gSmmuMapSid;

#endif  /* ___EFI_SMMU_MAP_SID_PROTOCOL_H__ */


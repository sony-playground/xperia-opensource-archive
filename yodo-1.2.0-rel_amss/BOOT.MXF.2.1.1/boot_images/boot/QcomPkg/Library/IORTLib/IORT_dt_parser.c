/**
 *
 * @file IORT.c
 *
 * @brief Implementation of IORT API on top of ACPI stored in Device
 *        Configuration
 *
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */
 
 /*Includes*/
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include "IORT.h"
#include "DALSys.h"
#include "DALStdErr.h"
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DTBDefs.h>
#include <Protocol/EFIDtbExtn.h>

 /*Macro Definitions*/
#pragma pack(1)

#define IORT_WORLD_ID_NON_SECURE 0x0
#define IORT_WORLD_ID_SECURE 0x1
#define IORT_WORLD_ID_SHIFT 31

#define IORT_DYNAMIC_MAPPING_NO 0x0
#define IORT_DYNAMIC_MAPPING_YES_DEFAULT 0x0
#define IORT_DYNAMIC_MAPPING_YES 0x1
#define IORT_DYNAMIC_MAPPING_SHIFT 30

#define IORT_TRANSLATION_TYPE_S2_ONLY 0x0
#define IORT_TRANSLATION_TYPE_S2CR_BYPASS 0x1
#define IORT_TRANSLATION_TYPE_SINGLE_STAGE 0x1
#define IORT_TRANSLATION_TYPE_NESTED 0x3
#define IORT_TRANSLATION_TYPE_SHIFT 24

#define IORT_MAX_SID_MAPPING_NUM 128
#define IORT_MAX_SMMUv2_SID_MAPPING_NUM 1
#define IORT_MAX_DEV_OBJECT_NAME_SIZE 32
#define IORT_MAX_ABSOLUTE_NODE_NAME_SIZE 64
#define IORT_MAX_OEM_ID_SIZE 6
#define IORT_MAX_INSTANCE_NODE_NUM 2
#define IORT_MAX_CLIENT_NODE_NUM 32
#define IORT_MAX_NODE_NUM (IORT_MAX_INSTANCE_NODE_NUM + IORT_MAX_CLIENT_NODE_NUM)
#define IORT_MAX_CONTEXT_INTERRUPT_NUM 128
#define IORT_MAX_PMU_INTERRUPT_NUM 16

#define IORT_DTB_LINE_BUF_SIZE 0x100

#define IORT_VMID_SHIFT 16

#define IORT_OEM_ID_SIZE 6

#define IORT_TYPE_SMMUV2NODE 3
#define IORT_TYPE_CLIENT 1

//#define IORT_DT_ENABLE_DEBUG_LOG
#define IORT_DT_PROPS_FORMAT_INSTANCE_NODE "WWWWWWWWWWWWWW"
#define IORT_DT_PROPS_FORMAT_CLIENT_NODE "WWWWWWWWWW"
#define IORT_DT_PROPS_FORMAT_SIDMAPPING_NODE "WWWWW"

#define IORT_FDT_GET_NODE_HANDLE(x, y) DTBExtnProtocol->FdtGetNodeHandle(x, y)
#define IORT_FDT_GET_COUNT_OF_SUBNODES(x, y)                                   \
  DTBExtnProtocol->FdtGetCountOfSubnodes(x, y)
#define IORT_FDT_GET_SIZE_OF_SUBNODE_NAMES(x, y, z)                            \
  DTBExtnProtocol->FdtGetSizeOfSubnodeNames(x, y, z)
#define IORT_FDT_GET_SUBNODE_NAMES(x, y, z)                                    \
  DTBExtnProtocol->FdtGetSubnodeNames(x, y, z)
#define IORT_FDT_GET_UINT32_PROP(x, y, z)                                      \
  DTBExtnProtocol->FdtGetUint32Prop(x, y, z)
#define IORT_FDT_GET_UINT32_PROP_LIST(w, x, y, z)                              \
  DTBExtnProtocol->FdtGetUint32PropList(w, x, y, z)
#define IORT_FDT_GET_UINT64_PROP(x, y, z)                                      \
  DTBExtnProtocol->FdtGetUint64Prop(x, y, z)
#define IORT_FDT_GET_STRING_PROP_LIST(w, x, y, z)                              \
  DTBExtnProtocol->FdtGetStringPropList(w, x, y, z)
#define IORT_FDT_GET_PROP_VALUES_OF_NODE(w, x, y, z)                              \
  DTBExtnProtocol->FdtGetPropValuesOfNode(w ,x ,y ,z )

#define IORT_DT_CHECK_NODE_PROPERTY(x)                                         \
  {                                                                            \
    if (ret_value) {                                                           \
      DEBUG((EFI_D_ERROR, "%a: Error in getting %s with return = %d\n",        \
             __FUNCTION__, u##x, ret_value));                                  \
      return ret_value;                                                        \
    }                                                                          \
  }

#define IORT_DT_CHECK_GENERIC_ERROR(x)                                         \
  {                                                                            \
    if (ret_value) {                                                           \
      DEBUG((EFI_D_ERROR, "%a: %s, return = %d\n", __FUNCTION__, u##x,         \
             ret_value));                                                      \
      return ret_value;                                                        \
    }                                                                          \
  }

#define IORT_DT_CHECK_NULL_POINTER(x)                                          \
  {                                                                            \
    if (x == NULL) {                                                                  \
      DEBUG((EFI_D_ERROR, "%a: %s is a Null pointer \n", __FUNCTION__, #x)); \
      return -1;                                                               \
    }                                                                          \
  }

#define IORT_DT_CHECK_UPPER_BOUND(x,y)                                          \
  {                                                                            \
    if (x > y) {                                                                  \
      DEBUG((EFI_D_ERROR, "%a: %s is greater than %s \n", __FUNCTION__, #x, #y)); \
      return -1;                                                               \
    }                                                                          \
  }

#ifdef IORT_DT_ENABLE_DEBUG_LOG
#define IORT_DT_DEBUG(...) DEBUG((EFI_D_ERROR, __VA_ARGS__))
#else
#define IORT_DT_DEBUG(...)
#endif

 /*Type Definitions*/
 
typedef struct _INTERRUPT {
  uint32_t InterruptFlags;
  uint32_t GSIV;
} INTERRUPT;

/*Required for getting list of property values. For any change 
IORT_DT_PROPS_FORMAT_SIDMAPPING_NODE needs to be reviewed*/

typedef struct _SIDMAPPING {
  uint32_t InputBase;
  uint32_t NumIDs;
  uint32_t OutputBase;
  uint32_t Flags;
  uint32_t OutputReference;
} SIDMAPPING;

typedef struct _SMMUV2NODE {
  uint8_t Type;
  uint16_t Length;
  uint8_t Revision;
  uint32_t Reserved;
  uint32_t NumberofMappings;
  uint32_t MappingsOffset;
  uint64_t BaseAddress;
  uint64_t Span;
  uint32_t Flags;
  uint32_t Model;
  uint32_t GlobalIntOffset;
  uint32_t NumContextInterrupts;
  uint32_t ContextIntOffset;
  uint32_t NumPMUInterrupts;
  uint32_t PMUIntOffset;
  uint32_t NSGIRPT_GSIV;
  uint32_t NSGIRPT_FLAGS;
  uint32_t NSGCFGIRPT_GSIV;
  uint32_t NSGCFGIRPT_FLAGS;
  INTERRUPT ContextInterrupts[IORT_MAX_CONTEXT_INTERRUPT_NUM];
  INTERRUPT PMUInterrupts[IORT_MAX_PMU_INTERRUPT_NUM];
  SIDMAPPING SIDMappings[IORT_MAX_SMMUv2_SID_MAPPING_NUM];
} SMMUV2NODE;

typedef struct _NAMEDNODE {
  uint8_t Type;
  uint16_t Length;
  uint8_t Revision;
  uint32_t Reserved;
  uint32_t NumberofMappings;
  uint32_t MappingsOffset;
  uint32_t NodeFlags;
  uint32_t CacheCoherency;
  uint8_t AllocationHints;
  uint16_t Reserved1;
  uint8_t MemAccessFlags;
  uint8_t DeviceMemAddressSize;
  uint8_t DevObjectName[IORT_MAX_DEV_OBJECT_NAME_SIZE];
  SIDMAPPING SIDMappings[IORT_MAX_SID_MAPPING_NUM];
} NAMEDNODE;

/*Required for getting list of property values. For any change 
IORT_DT_PROPS_FORMAT_CLIENT_NODE needs to be reviewed*/

typedef struct _IORT_CLIENT_HEADER {
  uint32_t Type;
  uint32_t Revision;
  uint32_t Reserved;
  uint32_t NumberofMappings;
  uint32_t NodeFlags;
  uint32_t CacheCoherency;
  uint32_t AllocationHints;
  uint32_t Reserved1;
  uint32_t MemAccessFlags;
  uint32_t DeviceMemAddressSize;
}IORT_CLIENT_HEADER_t;

/*Required for getting list of property values. For any change 
IORT_DT_PROPS_FORMAT_INSTANCE_NODE needs to be reviewed*/

typedef struct _IORT_INSTANCE_HEADER {
  uint32_t Type;
  uint32_t Revision;
  uint32_t Reserved;
  uint32_t NumberofMappings;
  uint32_t BaseAddress;
  uint32_t Span;
  uint32_t Flags;
  uint32_t Model;
  uint32_t NumContextInterrupts;
  uint32_t NumPMUInterrupts;
  uint32_t NSGIRPT_GSIV;
  uint32_t NSGIRPT_FLAGS;
  uint32_t NSGCFGIRPT_GSIV;
  uint32_t NSGCFGIRPT_FLAGS;
}IORT_INSTANCE_HEADER_t;

typedef struct _IORT {
  uint32_t Signature;
  uint32_t Length;
  uint8_t Revision;
  uint8_t Checksum;
  uint8_t OEMID[IORT_MAX_OEM_ID_SIZE];
  uint64_t OEMTableID;
  uint32_t OEMRevision;
  uint32_t CreatorID;
  uint32_t CreatorRevision;
  uint32_t NumberofIORTNodes;
  uint32_t IORTNodesOffset;
  uint32_t Reserved;
  SMMUV2NODE InstanceNode[IORT_MAX_INSTANCE_NODE_NUM];
  NAMEDNODE ClientNode[IORT_MAX_CLIENT_NODE_NUM];
} IORT;

typedef struct _iort_subnode_name {
  char subnode_name[IORT_MAX_ABSOLUTE_NODE_NAME_SIZE];
  uint32_t size;
} iort_subnode_name_type;

 /*Global/Static Variable Declarations*/

IORT g_iort_info;
static char iort_node_string[] = "/soc/iort";
static fdt_node_handle iort_node;
static SIDMAPPING sidmapping_info;
static IORT_CLIENT_HEADER_t iort_client_header_info;
static IORT_INSTANCE_HEADER_t iort_instance_header_info;
static uint32_t iort_instance_handles[IORT_MAX_INSTANCE_NODE_NUM];

EFI_DTB_EXTN_PROTOCOL *DTBExtnProtocol = NULL;
EFI_STATUS Status = EFI_DEVICE_ERROR;

 /*Function Definitions*/
 
static int iort_strcat(char *dest, int max_dest_strlen, char *s1, char *s2) {
  IORT_DT_CHECK_NULL_POINTER(s1);
  IORT_DT_CHECK_NULL_POINTER(s2);
  IORT_DT_CHECK_NULL_POINTER(dest);
  
  uint32_t req_dest_strlen = strlen(s1) + strlen(s2) + 1;
  
  IORT_DT_CHECK_UPPER_BOUND(req_dest_strlen,max_dest_strlen);

  char *dest_internal =
      AllocatePool((req_dest_strlen) * sizeof(char));
      
  IORT_DT_CHECK_NULL_POINTER(dest_internal);
  
  strlcpy(dest_internal, s1, strlen(s1) + 1);

  char *ptr = dest_internal + strlen(s1);

  while (*s2 != '\0'){
    *ptr = *s2;
    ptr = ptr + 1;
    s2  = s2 + 1;
  }

  *ptr = '\0';

  strlcpy(dest, dest_internal, strlen(dest_internal) + 1);
  FreePool(dest_internal);
  dest_internal = NULL;

  return 0;
}

static int iort_get_subnode_name_list(char *node, iort_subnode_name_type *subnode_list,
                               uint32_t *num_subnodes) {
  uint32_t count = 0;
  uint32_t size = 0;
  char *walk = NULL;
  int ret_value = -1;
  fdt_node_handle hNode;

  IORT_DT_CHECK_NULL_POINTER(subnode_list);
  IORT_DT_CHECK_NULL_POINTER(num_subnodes);

  ret_value = IORT_FDT_GET_NODE_HANDLE(&hNode, node);
  IORT_DT_CHECK_GENERIC_ERROR("Unable to find Subnodes");
  IORT_DT_CHECK_NULL_POINTER(&hNode);

  ret_value = IORT_FDT_GET_COUNT_OF_SUBNODES(&hNode, &count);
  IORT_DT_CHECK_NODE_PROPERTY("count of sub nodes");

  uint32_t *intptr = (uint32_t *)AllocatePool(count * sizeof(uint32_t));
  IORT_DT_CHECK_NULL_POINTER(intptr);

  ret_value = IORT_FDT_GET_SIZE_OF_SUBNODE_NAMES(&hNode, intptr, count);
  IORT_DT_CHECK_NODE_PROPERTY("size of subnode names");
  
  for (uint32_t i = 0; i < count; i++) {
    size = size + intptr[i];
  }

  FreePool(intptr);
  intptr = NULL;

  char *ptr = (char *)AllocatePool(size * sizeof(char));
  IORT_DT_CHECK_NULL_POINTER(ptr);

  walk = (char *)ptr;

  ret_value = IORT_FDT_GET_SUBNODE_NAMES(&hNode, ptr, size * sizeof(char));
  IORT_DT_CHECK_NODE_PROPERTY("Subnode Names");

  for (uint32_t i = 0; i < count; i++) {
    uint32_t walk_len = strlen(walk);

    char *name_buff = (char *)AllocatePool((walk_len + 1) * sizeof(char));
    IORT_DT_CHECK_NULL_POINTER(name_buff);

    strlcpy(name_buff, walk, (walk_len + 1));

    // Get absolute node name
    uint32_t node_abs_path_len =
        strlen(node) + strlen("/") + strlen(name_buff) + 1;
    char *node_abs_path =
        (char *)AllocatePool(node_abs_path_len * sizeof(char));

    IORT_DT_CHECK_NULL_POINTER(node_abs_path);
    ret_value = iort_strcat(node_abs_path,IORT_MAX_ABSOLUTE_NODE_NAME_SIZE, node, "/");
    IORT_DT_CHECK_GENERIC_ERROR("iort_strcat failed");
    ret_value = iort_strcat(node_abs_path,IORT_MAX_ABSOLUTE_NODE_NAME_SIZE, node_abs_path, name_buff);
    IORT_DT_CHECK_GENERIC_ERROR("iort_strcat failed");

    strlcpy(subnode_list[i].subnode_name, node_abs_path,
            strlen(node_abs_path) + 1);

    FreePool(name_buff);
    name_buff = NULL;
    FreePool(node_abs_path);
    node_abs_path = NULL;

    walk = walk + strlen(walk) + 1;
  }

  *num_subnodes = count;

  FreePool(ptr);
  ptr = NULL;

  return 0;
}

static int iort_configure_instance_nodes(fdt_node_handle hNode, char *node) {
  int ret_value = -1;
  static uint32_t instance_count = 0;
  uint32_t *irpt_list = NULL;

  IORT_DT_CHECK_UPPER_BOUND(instance_count,IORT_MAX_INSTANCE_NODE_NUM-1);

  ret_value = IORT_FDT_GET_PROP_VALUES_OF_NODE(&hNode, IORT_DT_PROPS_FORMAT_INSTANCE_NODE , &iort_instance_header_info, sizeof(iort_instance_header_info));
  
  if(ret_value != -FDT_ERR_QC_TRUNCATED){
    IORT_DT_CHECK_GENERIC_ERROR("iort_get_prop_values_of_node failed to get iort_instance_header_info");
  }
  else{
    ret_value = 0;
  }

  // Type
  g_iort_info.InstanceNode[instance_count].Type = iort_instance_header_info.Type;

  // Revision
  g_iort_info.InstanceNode[instance_count].Revision = iort_instance_header_info.Revision;

  // Reserved
  g_iort_info.InstanceNode[instance_count].Reserved = iort_instance_header_info.Reserved;

  // NumberofMappings
  g_iort_info.InstanceNode[instance_count].NumberofMappings = iort_instance_header_info.NumberofMappings;

  // BaseAddress
  g_iort_info.InstanceNode[instance_count].BaseAddress = iort_instance_header_info.BaseAddress;

  // Span
  g_iort_info.InstanceNode[instance_count].Span = iort_instance_header_info.Span;

  // Flags
  g_iort_info.InstanceNode[instance_count].Flags = iort_instance_header_info.Flags;

  // Model
  g_iort_info.InstanceNode[instance_count].Model = iort_instance_header_info.Model;

  // NumContextInterrupts
  g_iort_info.InstanceNode[instance_count].NumContextInterrupts = iort_instance_header_info.NumContextInterrupts;

  // NumPMUInterrupts
  g_iort_info.InstanceNode[instance_count].NumPMUInterrupts = iort_instance_header_info.NumPMUInterrupts;

  // NSGIRPT_GSIV
  g_iort_info.InstanceNode[instance_count].NSGIRPT_GSIV = iort_instance_header_info.NSGIRPT_GSIV;

  // NSGIRPT_FLAGS
  g_iort_info.InstanceNode[instance_count].NSGIRPT_FLAGS = iort_instance_header_info.NSGIRPT_FLAGS;

  // NSGCFGIRPT_GSIV
  g_iort_info.InstanceNode[instance_count].NSGCFGIRPT_GSIV = iort_instance_header_info.NSGCFGIRPT_GSIV;

  // NSGCFGIRPT_FLAGS
  g_iort_info.InstanceNode[instance_count].NSGCFGIRPT_FLAGS = iort_instance_header_info.NSGCFGIRPT_FLAGS;

  // ContextInterrupts
  if (g_iort_info.InstanceNode[instance_count].NumContextInterrupts > 0) {
    irpt_list = (uint32_t *)AllocatePool(
        g_iort_info.InstanceNode[instance_count].NumContextInterrupts *
        sizeof(uint32_t));
    IORT_DT_CHECK_NULL_POINTER(irpt_list);

    ret_value = IORT_FDT_GET_UINT32_PROP_LIST(
        &hNode, "ContextInterrupts", irpt_list,
        g_iort_info.InstanceNode[instance_count].NumContextInterrupts *
            sizeof(uint32_t));
    IORT_DT_CHECK_NODE_PROPERTY("ContextInterrupts");

    for (uint32_t i = 0;
         i < g_iort_info.InstanceNode[instance_count].NumContextInterrupts;
         i++) {
      g_iort_info.InstanceNode[instance_count].ContextInterrupts[i].GSIV =
          irpt_list[i];
    }
    FreePool(irpt_list);
    irpt_list = NULL;
  }

  // ContextInterruptFlags
  if (g_iort_info.InstanceNode[instance_count].NumContextInterrupts > 0) {
    irpt_list = (uint32_t *)AllocatePool(
        g_iort_info.InstanceNode[instance_count].NumContextInterrupts *
        sizeof(uint32_t));
    IORT_DT_CHECK_NULL_POINTER(irpt_list);

    ret_value = IORT_FDT_GET_UINT32_PROP_LIST(
        &hNode, "ContextInterruptFlags", irpt_list,
        g_iort_info.InstanceNode[instance_count].NumContextInterrupts *
            sizeof(uint32_t));
    IORT_DT_CHECK_NODE_PROPERTY("ContextInterruptFlags");

    for (uint32_t i = 0;
         i < g_iort_info.InstanceNode[instance_count].NumContextInterrupts;
         i++) {
      g_iort_info.InstanceNode[instance_count]
          .ContextInterrupts[i]
          .InterruptFlags = irpt_list[i];
    }
    FreePool(irpt_list);
    irpt_list = NULL;
  }

  // PMUInterrupts
  if (g_iort_info.InstanceNode[instance_count].NumPMUInterrupts > 0) {
    irpt_list = (uint32_t *)AllocatePool(
        g_iort_info.InstanceNode[instance_count].NumPMUInterrupts *
        sizeof(uint32_t));
    IORT_DT_CHECK_NULL_POINTER(irpt_list);

    ret_value = IORT_FDT_GET_UINT32_PROP_LIST(
        &hNode, "PMUInterrupts", irpt_list,
        g_iort_info.InstanceNode[instance_count].NumPMUInterrupts *
            sizeof(uint32_t));
    IORT_DT_CHECK_NODE_PROPERTY("PMUInterrupts");

    for (uint32_t i = 0;
         i < g_iort_info.InstanceNode[instance_count].NumPMUInterrupts; i++) {
      g_iort_info.InstanceNode[instance_count].PMUInterrupts[i].GSIV =
          irpt_list[i];
    }
    FreePool(irpt_list);
    irpt_list = NULL;
  }

  // PMUInterruptFlags
  if (g_iort_info.InstanceNode[instance_count].NumPMUInterrupts > 0) {
    irpt_list = (uint32_t *)AllocatePool(
        g_iort_info.InstanceNode[instance_count].NumPMUInterrupts *
        sizeof(uint32_t));
    IORT_DT_CHECK_NULL_POINTER(irpt_list);

    ret_value = IORT_FDT_GET_UINT32_PROP_LIST(
        &hNode, "PMUInterruptFlags", irpt_list,
        g_iort_info.InstanceNode[instance_count].NumPMUInterrupts *
            sizeof(uint32_t));
    IORT_DT_CHECK_NODE_PROPERTY("PMUInterruptFlags");

    for (uint32_t i = 0;
         i < g_iort_info.InstanceNode[instance_count].NumPMUInterrupts; i++) {
      g_iort_info.InstanceNode[instance_count].PMUInterrupts[i].InterruptFlags =
          irpt_list[i];
    }
    FreePool(irpt_list);
    irpt_list = NULL;
  }

  // Derived configuration

  // Length
  g_iort_info.InstanceNode[instance_count].Length = sizeof(SMMUV2NODE);

  // MappingsOffset
  g_iort_info.InstanceNode[instance_count].MappingsOffset = (uint32_t)(
      (uint64_t)&g_iort_info.InstanceNode[instance_count].SIDMappings -
      (uint64_t)&g_iort_info.InstanceNode[instance_count]);

  // GlobalIntOffset
  g_iort_info.InstanceNode[instance_count].GlobalIntOffset = (uint32_t)(
      (uint64_t)&g_iort_info.InstanceNode[instance_count].NSGIRPT_GSIV -
      (uint64_t)&g_iort_info.InstanceNode[instance_count]);

  // ContextIntOffset
  g_iort_info.InstanceNode[instance_count].ContextIntOffset = (uint32_t)(
      (uint64_t)&g_iort_info.InstanceNode[instance_count].ContextInterrupts -
      (uint64_t)&g_iort_info.InstanceNode[instance_count]);

  // PMUIntIntOffset
  g_iort_info.InstanceNode[instance_count].PMUIntOffset = (uint32_t)(
      (uint64_t)&g_iort_info.InstanceNode[instance_count].PMUInterrupts -
      (uint64_t)&g_iort_info.InstanceNode[instance_count]);

  instance_count = instance_count + 1;

  return 0;
}

static int iort_get_instance_index(uint32_t phandle, uint32_t* index){
  uint32_t ret_val = -1;
  for(uint32_t i=0; i<IORT_MAX_INSTANCE_NODE_NUM; i++){
    if(phandle == iort_instance_handles[i]){
      *index = i;
      ret_val = 0;
      break;
    }
  }  
  return ret_val;  
}

static int iort_configure_client_nodes(fdt_node_handle hNode, char *node) {
  int ret_value = -1;
  uint32_t value_32 = 0;
  static uint32_t client_count = 0;

  IORT_DT_CHECK_UPPER_BOUND(client_count,IORT_MAX_CLIENT_NODE_NUM-1);

  ret_value = IORT_FDT_GET_PROP_VALUES_OF_NODE(&hNode, IORT_DT_PROPS_FORMAT_CLIENT_NODE, &iort_client_header_info, sizeof(iort_client_header_info));
  
  if(ret_value != -FDT_ERR_QC_TRUNCATED){
    IORT_DT_CHECK_GENERIC_ERROR("iort_get_prop_values_of_node failed to get iort_client_header_info");
  }
  else{
    ret_value = 0;
  }
  
  // Type
  g_iort_info.ClientNode[client_count].Type = iort_client_header_info.Type;

  // Revision
  g_iort_info.ClientNode[client_count].Revision = iort_client_header_info.Revision;

  // Reserved
  g_iort_info.ClientNode[client_count].Reserved = iort_client_header_info.Reserved;

  // NumberofMappings
  g_iort_info.ClientNode[client_count].NumberofMappings = iort_client_header_info.NumberofMappings;

  // NodeFlags
  g_iort_info.ClientNode[client_count].NodeFlags = iort_client_header_info.NodeFlags;

  // CacheCoherency
  g_iort_info.ClientNode[client_count].CacheCoherency = iort_client_header_info.CacheCoherency;

  // AllocationHints
  g_iort_info.ClientNode[client_count].AllocationHints = iort_client_header_info.AllocationHints;

  // Reserved1
  g_iort_info.ClientNode[client_count].Reserved1 = iort_client_header_info.Reserved1;

  // MemAccessFlags
  g_iort_info.ClientNode[client_count].MemAccessFlags = iort_client_header_info.MemAccessFlags;

  // DeviceMemAddressSize
  g_iort_info.ClientNode[client_count].DeviceMemAddressSize = iort_client_header_info.DeviceMemAddressSize;

  // DevObjectName
  ret_value = IORT_FDT_GET_STRING_PROP_LIST(
      &hNode, "DevObjectName",
      (char *)g_iort_info.ClientNode[client_count].DevObjectName,
      IORT_MAX_DEV_OBJECT_NAME_SIZE * sizeof(char));
  IORT_DT_CHECK_NODE_PROPERTY("DevObjectName");

  // Derived configuration

  // Length
  g_iort_info.ClientNode[client_count].Length = sizeof(NAMEDNODE);

  // MappingsOffset
  g_iort_info.ClientNode[client_count].MappingsOffset =
      (uint32_t)((uint64_t)&g_iort_info.ClientNode[client_count].SIDMappings -
                 (uint64_t)&g_iort_info.ClientNode[client_count]);

  char *abs_SIDMappings_node =
      (char *)AllocatePool(IORT_MAX_ABSOLUTE_NODE_NAME_SIZE * sizeof(char));
  IORT_DT_CHECK_NULL_POINTER(abs_SIDMappings_node);

  ret_value = iort_strcat(abs_SIDMappings_node,IORT_MAX_ABSOLUTE_NODE_NAME_SIZE, node, "/");
  IORT_DT_CHECK_GENERIC_ERROR("iort_strcat failed");
  ret_value = 
      iort_strcat(abs_SIDMappings_node,IORT_MAX_ABSOLUTE_NODE_NAME_SIZE, abs_SIDMappings_node, "SIDMappings");
  IORT_DT_CHECK_GENERIC_ERROR("iort_strcat failed");

  iort_subnode_name_type *sidmapping = (iort_subnode_name_type *)AllocatePool(
      IORT_MAX_SID_MAPPING_NUM * sizeof(iort_subnode_name_type));
      
  IORT_DT_CHECK_NULL_POINTER(sidmapping);
  uint32_t num_sidmapping = 0;

  ret_value = iort_get_subnode_name_list(abs_SIDMappings_node, sidmapping,
                                         &num_sidmapping);
  IORT_DT_CHECK_GENERIC_ERROR("iort_get_subnode_name_list failed");

  FreePool(abs_SIDMappings_node);
  abs_SIDMappings_node = NULL;

  IORT_DT_CHECK_UPPER_BOUND(num_sidmapping,IORT_MAX_SID_MAPPING_NUM);

  for (uint32_t i = 0; i < num_sidmapping; i++) {
    ret_value = IORT_FDT_GET_NODE_HANDLE(&hNode, sidmapping[i].subnode_name);
    IORT_DT_CHECK_GENERIC_ERROR("Unable to find Sidmappings");
    IORT_DT_CHECK_NULL_POINTER(&hNode);

    ret_value = IORT_FDT_GET_PROP_VALUES_OF_NODE(&hNode, IORT_DT_PROPS_FORMAT_SIDMAPPING_NODE, &sidmapping_info, sizeof(SIDMAPPING));
    IORT_DT_CHECK_GENERIC_ERROR("iort_get_prop_values_of_node failed to get sidmapping_info");

    //InputBase
    g_iort_info.ClientNode[client_count].SIDMappings[i].InputBase = sidmapping_info.InputBase;
    
    //NumIDs
    g_iort_info.ClientNode[client_count].SIDMappings[i].NumIDs = sidmapping_info.NumIDs;
    
    //OutputBase
    g_iort_info.ClientNode[client_count].SIDMappings[i].OutputBase = sidmapping_info.OutputBase;
    
    //Flags
    g_iort_info.ClientNode[client_count].SIDMappings[i].Flags = sidmapping_info.Flags;
    
    value_32 = sidmapping_info.OutputReference;
    
    uint32_t instance_index = 0;
    ret_value = iort_get_instance_index(value_32,&instance_index);
    IORT_DT_CHECK_GENERIC_ERROR("Unable to find instance index");

    g_iort_info.ClientNode[client_count].SIDMappings[i].OutputReference = (uint32_t)((uint64_t)&g_iort_info.InstanceNode[instance_index] - (uint64_t)&g_iort_info);
  }
  FreePool(sidmapping);
  sidmapping = NULL;

  client_count = client_count + 1;

  return 0;
}

static int iort_configure_nodes(char *node) {
  int ret_value = -1;
  uint32_t value_32 = 0;
  fdt_node_handle hNode;

  ret_value = IORT_FDT_GET_NODE_HANDLE(&hNode, node);
  IORT_DT_CHECK_NODE_PROPERTY("SMMU Node");
  IORT_DT_CHECK_NULL_POINTER(&hNode);

  // Get Type of node to decide SMMUv2 instance or Client Node
  ret_value = IORT_FDT_GET_UINT32_PROP(&hNode, "Type", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("Type");

  if (value_32 == IORT_TYPE_SMMUV2NODE) // This is SMMUv2 Node
  {
    ret_value = iort_configure_instance_nodes(hNode, node);
    IORT_DT_CHECK_GENERIC_ERROR("iort_configure_instance_nodes failed");
  } else if (value_32 == IORT_TYPE_CLIENT) // SMMU Client Node
  {
    ret_value = iort_configure_client_nodes(hNode, node);
    IORT_DT_CHECK_GENERIC_ERROR("iort_configure_client_nodes_nodes failed");
  } else {
    ret_value = -1;
    IORT_DT_CHECK_GENERIC_ERROR("Invalid iort Node type");
  }
  return 0;
}

static int iort_data_init(void) {
  for (uint32_t i = 0; i < IORT_MAX_INSTANCE_NODE_NUM; i++) {
    g_iort_info.InstanceNode[i].Length = sizeof(SMMUV2NODE);
  }

  for (uint32_t i = 0; i < IORT_MAX_CLIENT_NODE_NUM; i++) {
    g_iort_info.ClientNode[i].Length = sizeof(NAMEDNODE);
  }

  return 0;
}

int parseIORTDT() {
  int ret_value;
  uint32_t value_32;
  uint64_t value_64;
  char *ptr = NULL;

  Status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL,
                               (VOID **)&DTBExtnProtocol);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: Locate DTBExtnProtocol failed with error %r \n",
           __FUNCTION__, Status));
    return -1;
  }
  /* find specific node */
  // iort
  ret_value = IORT_FDT_GET_NODE_HANDLE(&iort_node, iort_node_string);
  IORT_DT_CHECK_NODE_PROPERTY("iort_node_string");
  IORT_DT_CHECK_NULL_POINTER(&iort_node);

  /* extract properties from node */

  // Signature
  ret_value = IORT_FDT_GET_UINT32_PROP(&iort_node, "Signature", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("Signature");

  g_iort_info.Signature = value_32;

  // Revision
  ret_value = IORT_FDT_GET_UINT32_PROP(&iort_node, "Revision", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("Revision");

  g_iort_info.Revision = value_32;

  // Checksum
  ret_value = IORT_FDT_GET_UINT32_PROP(&iort_node, "Checksum", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("Checksum");

  g_iort_info.Checksum = value_32;

  // OEMID
  ptr = (char *)AllocatePool(IORT_OEM_ID_SIZE * sizeof(char));
  IORT_DT_CHECK_NULL_POINTER(ptr);

  ret_value =
      IORT_FDT_GET_STRING_PROP_LIST(&iort_node, "OEMID", ptr, sizeof(ptr));
  IORT_DT_CHECK_NODE_PROPERTY("OEMID");

  for (uint32_t i = 0; i < IORT_OEM_ID_SIZE; i++) {
    g_iort_info.OEMID[i] = ptr[i];
  }

  FreePool(ptr);
  ptr = NULL;

  ret_value = IORT_FDT_GET_UINT64_PROP(&iort_node, "OEMTableID", &value_64);
  IORT_DT_CHECK_NODE_PROPERTY("OEMTableID");

  g_iort_info.OEMTableID = value_64;

  // OEMRevision
  ret_value = IORT_FDT_GET_UINT32_PROP(&iort_node, "OEMRevision", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("OEMRevision");

  g_iort_info.OEMRevision = value_32;

  // CreatorID
  ret_value = IORT_FDT_GET_UINT32_PROP(&iort_node, "CreatorID", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("CreatorID");

  g_iort_info.CreatorID = value_32;

  // CreatorRevision
  ret_value =
      IORT_FDT_GET_UINT32_PROP(&iort_node, "CreatorRevision", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("CreatorRevision");

  g_iort_info.CreatorRevision = value_32;

  // NumberofIORTNodes
  ret_value =
      IORT_FDT_GET_UINT32_PROP(&iort_node, "NumberofIORTNodes", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("NumberofIORTNodes");

  g_iort_info.NumberofIORTNodes = value_32;

  // Reserved
  ret_value = IORT_FDT_GET_UINT32_PROP(&iort_node, "Reserved", &value_32);
  IORT_DT_CHECK_NODE_PROPERTY("Reserved");

  g_iort_info.Reserved = value_32;

  //instance_handles
  ret_value = IORT_FDT_GET_UINT32_PROP_LIST(&iort_node, "instance_handles", iort_instance_handles,sizeof(iort_instance_handles));
  IORT_DT_CHECK_NODE_PROPERTY("instance_handles");
  
  // Derived properties
  // Length
  g_iort_info.Length = sizeof(g_iort_info);

  // IORTNodesOffset
  g_iort_info.IORTNodesOffset =
      (uint32_t)((uint64_t)&g_iort_info.Reserved - (uint64_t)&g_iort_info + 4);

  // Subnode specific configuration
  uint32_t iort_subnode_count = 0;
  iort_subnode_name_type *iort_subnode_name_list =
      (iort_subnode_name_type *)AllocatePool(
          (IORT_MAX_NODE_NUM) *
          IORT_MAX_ABSOLUTE_NODE_NAME_SIZE * sizeof(char));
  IORT_DT_CHECK_NULL_POINTER(iort_subnode_name_list);

  ret_value = iort_get_subnode_name_list(
      iort_node_string, iort_subnode_name_list, &iort_subnode_count);
  IORT_DT_CHECK_GENERIC_ERROR("iort_get_subnode_name_list failed");

  IORT_DT_CHECK_UPPER_BOUND(iort_subnode_count,IORT_MAX_NODE_NUM);

  for (uint32_t i = 0; i < iort_subnode_count; i++) {

    ret_value = iort_configure_nodes(
        iort_subnode_name_list[i]
            .subnode_name); // This function needs to be written
    IORT_DT_CHECK_GENERIC_ERROR("iort_configure_nodes failed");
  }

  FreePool(iort_subnode_name_list);
  iort_subnode_name_list = NULL;

  ret_value = iort_data_init();
  IORT_DT_CHECK_GENERIC_ERROR("iort_data_init failed");

  return 0;

}

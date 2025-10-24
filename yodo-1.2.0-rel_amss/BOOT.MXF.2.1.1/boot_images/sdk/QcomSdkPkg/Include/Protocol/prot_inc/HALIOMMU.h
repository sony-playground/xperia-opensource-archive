#ifndef __HAL_IOMMU_H__
#define __HAL_IOMMU_H__
/*==============================================================================
@file HALIOMMU.h


        Copyright (c) 2020 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

==============================================================================*/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/24/20   dai     Created

=============================================================================*/
/*------------------------------------------------------------------------------
* Include Files
*-----------------------------------------------------------------------------*/
#include "Uefi.h"
#include "prot_dtypes.h"

/** @defgroup efi_hal_io_mmu_protocol EFI_HAL_IO_MMU_PROTOCOL
 *  @ingroup tech_core
 */
 /** @defgroup  efi_hal_io_mmu_protocol_prot PROTOCOL
 *  @ingroup efi_hal_io_mmu_protocol 
 */ 
 /** @defgroup  efi_hal_io_mmu_protocol_apis APIs
 *  @ingroup efi_hal_io_mmu_protocol 
 */ 

/** @defgroup  efi_hal_io_mmu_protocol_data DATA_STRUCTURES
 *  @ingroup efi_hal_io_mmu_protocol 
 */
/** @ingroup efi_hal_io_mmu_protocol_data
  @par Summary
  HAL_IOMMUResult_t enum.

  @par Parameters
*/
typedef enum {
  HAL_IOMMU_ERR_OK = 0,
  HAL_IOMMU_ERR_HAL_SUCCESS = 0,
  HAL_IOMMU_ERR_GENERIC_ERROR, //1
  HAL_IOMMU_ERR_INVALID_PARAM, //2
  HAL_IOMMU_ERR_NULL_POINTER, //3
  HAL_IOMMU_ERR_OUT_OF_RANGE, //4 
  HAL_IOMMU_ERR_REDUNDANT_CONFIGURATION, //5
  HAL_IOMMU_ERR_VMID_NOT_FOUND, //6
  HAL_IOMMU_ERR_VMID_NOT_INIT, //7
  HAL_IOMMU_ERR_INIT_PT_FAILED, //8
  HAL_IOMMU_ERR_REGISTER_MMU_FAILED, //9
  HAL_IOMMU_ERR_DEREGISTER_MMU_FAILED, //10
  HAL_IOMMU_ERR_GET_PT_ATTR_FAILED, //11
  HAL_IOMMU_ERR_INVALID_CACHE_ATTR, //12
  HAL_IOMMU_ERR_MAP_FAILED, //13
  HAL_IOMMU_ERR_UNMAP_FAILED, //14
  HAL_IOMMU_ERR_INIT_CLOCK_FAILED, //15
  HAL_IOMMU_ERR_ENABLE_CLOCK_FAILED, //16
  HAL_IOMMU_ERR_DISABLE_CLOCK_FAILED, //17
  HAL_IOMMU_ERR_PAGETABLE_NOT_INIT, //18
  HAL_IOMMU_ERR_MALLOC_FAILED, //19
  HAL_IOMMU_ERR_GET_IORT_INFO_FAILED, //20
  HAL_IOMMU_ERR_UNSUPPORTED_INSTANCE_FOR_TARGET, //21
  HAL_IOMMU_ERR_DOMAIN_IN_USE, //22
  HAL_IOMMU_ERR_SID_NOT_FOUND, //23
  HAL_IOMMU_ERR_DEVICE_INCOMPATIBLE_WITH_DOMAIN, //24
  HAL_IOMMU_ERR_SOC_CFG_FAILED, //25
  HAL_IOMMU_ERR_QUEUE_FULL, // 26
  HAL_IOMMU_ERR_QUEUE_EMPTY, // 27
  HAL_IOMMU_ERR_V2_INIT_FAILED, // 28
  HAL_IOMMU_ERR_V3_INIT_FAILED, // 29
  HAL_IOMMU_ERR_BAD_ADDRESS, // 30
  HAL_IOMMU_ERR_PTE_NOT_FOUND, // 31
  HAL_IOMMU_ERR_RESULT_SIZE = 0x7FFFFFFF, // force to 32-bit enum
} HAL_IOMMUResult_t;

/** @ingroup efi_hal_io_mmu_protocol_data
  @par Summary
  hal_iommu_fault_info struct.

  @par Parameters
*/
struct hal_iommu_fault_info {
    void *p_domain;
    void *FAR;
    void *device_handle;
    struct {
        unsigned WNR:1;
        unsigned IND:1;
        unsigned PRV:1;
        unsigned MULTI:1;
        unsigned ASYNC:1;
        unsigned PTWF:1;
        unsigned RESERVED:26;
    } flags;
    enum {
        UNSUPPORTED_UPSTREAM_TRANS,
        ADDRESS_SIZE_FAULT,
        TLB_MATCH_CONFLICT,
        EXTERNAL_FAULT,
        PERMISSION_FAULT,
        ACCESS_FLAG_FAULT,
        TRANSLATION_FAULT,
    } type;
};
/** @ingroup efi_hal_io_mmu_protocol_data
  @par Summary
  hal_iommu_domain_aarch64 struct.

  @par Parameters
*/
struct hal_iommu_domain_aarch64 {
    UINT64 TTBR0;
    UINT64 TTBR1;
    UINT32 MAIR0;
    UINT32 MAIR1;
    UINT32 SCTLR;
    UINT32 TCR;
    UINT32 TCR2;
};
/** @ingroup efi_hal_io_mmu_protocol_data
  @par Summary
  hal_iommu_vmsa enum.

  @par Parameters
*/
enum hal_iommu_vmsa {
    HAL_IOMMU_ARM_ARCH_AARCH64,
    HAL_IOMMU_ARM_ARCH_INVALID,
};
/** @ingroup efi_hal_io_mmu_protocol_data
  @par Summary
  hal_iommu_domain_config struct.

  @par Parameters
*/
struct hal_iommu_domain_config {
    enum hal_iommu_vmsa vmsa;
    union {
        struct hal_iommu_domain_aarch64 domain_cfg64;
    } config;
};
/** @ingroup efi_hal_io_mmu_protocol_data
  @par Summary
  hal_iommu_bypass_domain_type enum.

  @par Parameters
*/
enum hal_iommu_bypass_domain_type {
    HAL_IOMMU_AARCH64_NON_CCA_DOMAIN_TYPE,
    HAL_IOMMU_AARCH64_CCA_DOMAIN_TYPE,
    HAL_IOMMU_DOMAIN_TYPE_INVALID
};

typedef void (*fp_hal_iommu_fault_handler_t)(void *p_context, struct hal_iommu_fault_info *p_fault_info);

typedef HAL_IOMMUResult_t (*fp_hal_iommu_domain_create_t)(void **pp_domain);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_domain_delete_t)(void *p_domain);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_domain_attach_device_t)(void *p_domain, void *client_handle, UINT32 arid, UINT32 mask);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_domain_detach_device_t)(void *p_domain, void *client_handle, UINT32 arid, UINT32 mask);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_domain_configure_t)(void *p_domain, struct hal_iommu_domain_config *p_domain_cfg);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_flush_domain_t)(void *p_domain);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_flush_domain_va_list_t)(void *p_domain, BOOLEAN last_level, UINT32 number, UINT64 *va_list);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_register_fault_handler_t)(void *p_domain, fp_hal_iommu_fault_handler_t handler, void *p_context);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_configure_bypass_domain_t)(void *p_domain, enum hal_iommu_bypass_domain_type type);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_idiom_detach_t)(void *client_handle, UINT32 arid, UINT32 mask);
typedef HAL_IOMMUResult_t (*fp_arch_mmu_init_aspace_t)(void **p_aspace, UINT64 base, size_t size);
typedef HAL_IOMMUResult_t (*fp_arch_mmu_destroy_aspace_t)(void *p_aspace);
typedef HAL_IOMMUResult_t (*fp_arch_mmu_map_t)(void *p_aspace, UINT64 vaddr, UINT64 paddr, UINT32 count, UINT32 flags);
typedef HAL_IOMMUResult_t (*fp_arch_mmu_unmap_t)(void *p_aspace, UINT64 vaddr, UINT32 count);
typedef HAL_IOMMUResult_t (*fp_hal_iommu_domain_update_aspace_t)(struct hal_iommu_domain_config *p_domain_cfg, void *p_aspace);
/** @ingroup efi_hal_io_mmu_protocol_data
  @par Summary
  HAL_IOMMU_fptable_t struct.

  @par Parameters
*/
typedef struct HAL_IOMMU_fptable_s {
    fp_hal_iommu_domain_create_t                    domain_create_func;
    fp_hal_iommu_domain_delete_t                    domain_delete_func;
    fp_hal_iommu_domain_attach_device_t             domain_attach_func;
    fp_hal_iommu_domain_detach_device_t             domain_detach_func;
    fp_hal_iommu_domain_configure_t                 domain_configure_func;
    fp_hal_iommu_flush_domain_t                     flush_domain_func;
    fp_hal_iommu_flush_domain_va_list_t             flush_domain_va_list_func;
    fp_hal_iommu_register_fault_handler_t           register_fault_handler_func;    
    fp_hal_iommu_configure_bypass_domain_t          config_bypass_domain_func;
    fp_hal_iommu_idiom_detach_t                     idiom_detach_func; 
    fp_arch_mmu_init_aspace_t                       mmu_aspace_init_func;
    fp_arch_mmu_destroy_aspace_t                    mmu_aspace_destroy_func;
    fp_arch_mmu_map_t                               mmu_map_addr_func;
    fp_arch_mmu_unmap_t                             mmu_unmap_addr_func;
    fp_hal_iommu_domain_update_aspace_t             domain_update_aspace_func;
} HAL_IOMMU_fptable_t;

#endif /* __HAL_IOMMU_H__ */

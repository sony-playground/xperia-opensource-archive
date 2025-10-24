/** @file EFIHALIOMMUProtocol.h

  HAL IOMMU Protocol for UEFI

  Copyright (c) 2010-2011,2014 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/19/17   amo     Created

=============================================================================*/

#ifndef __HAL_IOMMU_PROTOCOL_H__
#define __HAL_IOMMU_PROTOCOL_H__

#include "HALIOMMU.h"

#define HAL_IOMMU_REVISION 0x0000000000010002


/** @ingroup efi_hal_io_mmu_protocol_data
@{ */
#define HAL_IOMMU_FLAG_CACHED            (0<<0)
#define HAL_IOMMU_FLAG_UNCACHED          (1<<0)
#define HAL_IOMMU_FLAG_UNCACHED_DEVICE   (2<<0) /** only exists on some arches, otherwise UNCACHED */
#define HAL_IOMMU_FLAG_CACHE_MASK        (3<<0)

#define HAL_IOMMU_FLAG_PERM_USER         (1<<2)
#define HAL_IOMMU_FLAG_PERM_RO           (1<<3)
#define HAL_IOMMU_FLAG_PERM_NO_EXECUTE   (1<<4)
#define HAL_IOMMU_FLAG_NS                (1<<5) /** NON-SECURE */
#define HAL_IOMMU_FLAG_INVALID           (1<<7) /** indicates that flags are not specified */
/** @} */ /* end_ingroup efi_hal_io_mmu_protocol_data */

/** @ingroup efi_hal_io_mmu_protocol_apis */
typedef 
void
(EFIAPI *EFI_HAL_IOMMU_PROTOCOL_INIT)(
   OUT   HAL_IOMMU_fptable_t            **p_fp_table
   );

/** @ingroup efi_hal_io_mmu_protocol_apis */
typedef 
void
(EFIAPI *EFI_HAL_IOMMU_PROTOCOL_DEINIT)(
   VOID
   );

/** @ingroup efi_hal_io_mmu_protocol_prot */
typedef struct _EFI_HAL_IOMMU_PROTOCOL {
   UINT64                            revision;
   EFI_HAL_IOMMU_PROTOCOL_INIT       _HAL_IOMMU_protocol_init;
   EFI_HAL_IOMMU_PROTOCOL_DEINIT     _HAL_IOMMU_protocol_deinit;
} 
EFI_HAL_IOMMU_PROTOCOL; 

extern EFI_GUID gEfiHalIommuProtocolGuid;

#endif /*__HAL_IOMMU_PROTOCOL_H__*/

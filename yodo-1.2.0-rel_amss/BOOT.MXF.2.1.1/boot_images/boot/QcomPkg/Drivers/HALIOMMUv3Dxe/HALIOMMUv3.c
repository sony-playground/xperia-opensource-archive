/**
 *
 * @file HALIOMMUv3.c
 * 
 * @brief Implementation of SMMUv3 IORT APIs
 *
 * Copyright (c) 2017,2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */
#include <string.h>
#include <Protocol/IoMmu.h>
#include <Protocol/EFIScm.h>
#include <Protocol/PciIo.h>
#include <Include/scm_sip_interface.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include "HALIOMMUv3.h"
#include "HALIOMMUv3Reg.h"
#include "mmu.h"

/*MACRO Declaration*/
// TODO, Target Specific Macros?
#define UEFI_BASE_ADDR 0x80000000
#define UEFI_DDR_SIZE  0x4000000000 // 256GB temporarily, until dynamic sizing is necessary

#define ROUND_UP_4KB(x)  (((x) + 0xFFF) & ~0xFFF)

#define SMMU_PARAVIRT_OP_ATTACH         0
#define SMMU_PARAVIRT_OP_DETATCH        1
#define SMMU_PARAVIRT_OP_INVAL_ASID     2
#define SMMU_PARAVIRT_OP_INVAL_VA       3
#define SMMU_PARAVIRT_OP_ALL_S1_BYPASS  4

#define ASID_MAX 0xFFFF
#define INVALID_ASID -1

/*Type definitions*/
struct mapping_handle {
    UINT64 va;
    UINT64 pa;
    UINT32 pages;
    UINT32 perm;
    UINT32 asid;
    UINT32 sid;
    void *aspace;
};

struct global_asid_node {
    UINT32 asid;
    UINT32 sid;
    void *aspace;
    hal_iommuv3_cd_t *p_cd;
    hal_iommuv3_ste_t *p_ste;
    boolean attached;
    struct global_asid_node *next;
};

/*Variable declaration*/
struct global_asid_node *g_asid_list_head = NULL;
static int g_next_unique_asid = 0;
static hal_iommuv3_ste_t g_default_ste = {0};
static hal_iommuv3_cd_t g_default_cd = {0};


// SCM Protocol
QCOM_SCM_PROTOCOL             *pQcomScmProtocol = NULL;

/*Function Declaration*/
static UINT32 alloc_asid(void);
static struct global_asid_node *get_asid_node(UINT32 sid);

/*Function implimentation*/
/* Helper Functions */
static UINT32 alloc_asid(void)
{
    if(g_next_unique_asid > ASID_MAX)
        return INVALID_ASID;
    return g_next_unique_asid++;
}

static struct global_asid_node *get_asid_node(UINT32 sid)
{
    struct global_asid_node *new = NULL;
    struct global_asid_node *curr = g_asid_list_head;
    
    while(curr) {
        if(curr->sid == sid) {
            return curr;
        }

        curr = curr->next;
    }
    
    // No node present, create one and add to front
    new = (struct global_asid_node *)AllocatePool(sizeof(struct global_asid_node));
    if(new) {
        new->asid = alloc_asid();
        new->sid = sid;
        // Create new aspace
        if(HAL_IOMMU_ERR_OK != arch_mmu_init_aspace(&new->aspace, UEFI_BASE_ADDR, UEFI_DDR_SIZE)) {
            FreePool(new);
            return NULL;
        }
        new->attached = FALSE;
        new->next = g_asid_list_head;
        g_asid_list_head = new;
    }
    
    return new;
}

/**
  Get Stream ID from DeviceHandle.

  This function is invoked during SetAttribute phase of buffer mapping in UEFI
  with SMMUV3

  When a device driver requests its bus driver to map a DMA buffer, the bus
  driver is expected to invoke SetAttributes call passing the UEFI EFI Handle
  pointing to the device of origin, from which it is possible to identify what
  type of device it is and use approproate protocol APIs to extract Stream ID

  NOTE: This same function can be extended to use the DeviceHandle to identify
        other bus masters if matching it with PciIo protocol failed.

  @param[in]   DeviceHandle      The device who initiates the DMA access request.
  @param[out]  Sid               Stream ID output from this function.

  @retval EFI_SUCCESS            SID is extracted from the DeviceHandle.
  @retval EFI_INVALID_PARAMETER  DeviceHandle is an invalid handle.
  @retval EFI_UNSUPPORTED        There are not enough resources available to query the Device ID.
  @retval EFI_DEVICE_ERROR       The bus master protocol driver reported an error.

**/
EFI_STATUS GetStreamIdFromDeviceHandle(IN EFI_HANDLE DeviceHandle, UINT32 *Sid)
{
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINTN               Seg;
    UINTN               Bus;
    UINTN               Dev;
    UINTN               Func;
    UINT32              StreamID = 0;
    EFI_STATUS          Status;

    if (DeviceHandle == NULL || Sid == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    Status = gBS->HandleProtocol (DeviceHandle, &gEfiPciIoProtocolGuid, (VOID **)&PciIo);
    if (Status == EFI_SUCCESS)
    {
        Status = PciIo->GetLocation (PciIo, &Seg, &Bus, &Dev, &Func);
        if (EFI_ERROR(Status))
        {
            return EFI_DEVICE_ERROR;
        }

        /* Stream ID composition for PCIe devices:
         *
         * ---------------------------------
         * | 31:16 | 15:08 | 07:03 | 02:00 |
         * ---------------------------------
         * |  Seg  |  Bus  |  Dev  |  Func |
         * ---------------------------------
         */
        StreamID |= ((UINT16)Seg << 16);
        StreamID |= ((UINT8)Bus << 8);
        StreamID |= ((UINT8)Dev << 3);
        StreamID |= ((UINT8)Func);

        *Sid = StreamID;

        return EFI_SUCCESS;
    }
    else
    {
       size_t RBDF = (size_t)DeviceHandle;
       // We didn't find the protocol on the handle means the handle
       // was not from PciIo protocol implementation. If when an error return
       // from Handle protocol is not desired, this condition can be run first isntead.
       // One failure from HandleProtocol means the argument might be RBDF
       // value instead of a UEFI Handle, so sanity check the value for RBdf
       // For now we can limit the Rootport count to 16
       // and generally we will not have more than 2 buses
       // and generally never more than a device and function
       if (((RBDF & 0xFF) == 0) &&         // Dev,Func == 0
           (((RBDF >> 8) & 0xFF) < 2) &&   // Bus == 0 or 1
           (((RBDF >> 16) & 0xFFFF) < 16)) // Rootport < 16
       {
          *Sid = (UINT32)RBDF;
          return EFI_SUCCESS;
       }
    }

    return EFI_UNSUPPORTED;
}

/**
  Set IOMMU attribute for a system memory.

  If the IOMMU protocol exists, the system memory cannot be used
  for DMA by default.

  When a device requests a DMA access for a system memory,
  the device driver need use SetAttribute() to update the IOMMU
  attribute to request DMA access (read and/or write).

  The DeviceHandle is used to identify which device submits the request.
  The IOMMU implementation need translate the device path to an IOMMU device ID,
  and set IOMMU hardware register accordingly.
  1) DeviceHandle can be a standard PCI device.
     The memory for BusMasterRead need set EDKII_IOMMU_ACCESS_READ.
     The memory for BusMasterWrite need set EDKII_IOMMU_ACCESS_WRITE.
     The memory for BusMasterCommonBuffer need set EDKII_IOMMU_ACCESS_READ|EDKII_IOMMU_ACCESS_WRITE.
     After the memory is used, the memory need set 0 to keep it being protected.
  2) DeviceHandle can be an ACPI device (ISA, I2C, SPI, etc).
     The memory for DMA access need set EDKII_IOMMU_ACCESS_READ and/or EDKII_IOMMU_ACCESS_WRITE.

  @param[in]  This              The protocol instance pointer.
  @param[in]  DeviceHandle      The device who initiates the DMA access request.
  @param[in]  Mapping           The mapping value returned from Map().
  @param[in]  IoMmuAccess       The IOMMU access.

  @retval EFI_SUCCESS            The IoMmuAccess is set for the memory range specified by DeviceAddress and Length.
  @retval EFI_INVALID_PARAMETER  DeviceHandle is an invalid handle.
  @retval EFI_INVALID_PARAMETER  Mapping is not a value that was returned by Map().
  @retval EFI_INVALID_PARAMETER  IoMmuAccess specified an illegal combination of access.
  @retval EFI_UNSUPPORTED        DeviceHandle is unknown by the IOMMU.
  @retval EFI_UNSUPPORTED        The bit mask of IoMmuAccess is not supported by the IOMMU.
  @retval EFI_UNSUPPORTED        The IOMMU does not support the memory range specified by Mapping.
  @retval EFI_OUT_OF_RESOURCES   There are not enough resources available to modify the IOMMU access.
  @retval EFI_DEVICE_ERROR       The IOMMU device reported an error while attempting the operation.

**/
EFI_STATUS
HAL_IOMMUv3_Set_Attribute(
  IN EDKII_IOMMU_PROTOCOL  *This,
  IN EFI_HANDLE            DeviceHandle,
  IN VOID                  *Mapping,
  IN UINT64                IoMmuAccess
)
{
    UINT32 sid = 0;
    struct global_asid_node *asid_node = NULL;
    struct arch_aspace *p_aspace_local = NULL;
    struct mapping_handle *map_handle = (struct mapping_handle *)Mapping;
    UINT64 Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 Results[SCM_MAX_NUM_RESULTS] = {0};
    EFI_STATUS Status;
    
    if(!pQcomScmProtocol)
        return EFI_UNSUPPORTED;
    
    if(!map_handle)
        return EFI_INVALID_PARAMETER;
    
    // Get SID from DeviceHandle
    Status = GetStreamIdFromDeviceHandle(DeviceHandle, &sid);
    if (EFI_ERROR(Status))
    {
        DEBUG(( EFI_D_ERROR, "Get SID Failed, Status:(0x%x)\r\n", Status));
        return EFI_DEVICE_ERROR;
    }

    // Get ASID node from SID
    asid_node = get_asid_node(sid);
    if(!asid_node)
        return EFI_OUT_OF_RESOURCES;
    
    // Install aspace/asid into mapping handle, to be used in Unmap
    map_handle->aspace = asid_node->aspace;
    map_handle->asid = asid_node->asid;
    map_handle->sid = sid;
    
    switch(IoMmuAccess & (EDKII_IOMMU_ACCESS_READ | EDKII_IOMMU_ACCESS_WRITE)) {
        case (EDKII_IOMMU_ACCESS_READ | EDKII_IOMMU_ACCESS_WRITE):
        case EDKII_IOMMU_ACCESS_WRITE:
            map_handle->perm = ARCH_MMU_FLAG_PERM_USER;
            break;
        case EDKII_IOMMU_ACCESS_READ:
            map_handle->perm = ARCH_MMU_FLAG_PERM_USER | ARCH_MMU_FLAG_PERM_RO;
            break;
        case 0:
            return EFI_SUCCESS;
            break;
        default:
            return EFI_INVALID_PARAMETER;
            break;
    }
    
    // Add the mapping
    if(HAL_IOMMU_ERR_OK != arch_mmu_map(map_handle->aspace, map_handle->va, map_handle->pa, map_handle->pages, map_handle->perm | ARCH_MMU_FLAG_CACHED)) {
        return EFI_DEVICE_ERROR;
    }
    
    if(!asid_node->attached) {
        char *temp_buff;
        
        // If not attached, setup CD/STE and SMC to Hypervisor to attach
        asid_node->p_ste = (hal_iommuv3_ste_t *)AllocatePool(sizeof(hal_iommuv3_ste_t)); // Alignment not needed, since HYP will copy into its own aligned STE
        temp_buff = (char *)AllocatePool(sizeof(hal_iommuv3_cd_t)*2); // Unaligned buffer, CD must be 64-byte aligned
        if(!asid_node->p_ste || !temp_buff)
            return EFI_OUT_OF_RESOURCES;
        // Get 64 byte alignment
        for(; (UINT64)temp_buff & 0x3F; temp_buff++);
        asid_node->p_cd = (hal_iommuv3_cd_t *)temp_buff; // Note, freeing this is now impossible but likely never needed (even through FreePool is currently unimplemented)        
        
        // Install default values
        memscpy(asid_node->p_ste, sizeof(hal_iommuv3_ste_t), &g_default_ste, sizeof(hal_iommuv3_ste_t));
        memscpy(asid_node->p_cd, sizeof(hal_iommuv3_cd_t), &g_default_cd, sizeof(hal_iommuv3_cd_t));
        
        // Install TTBR0 and ASID into CD
        p_aspace_local = (struct arch_aspace *)map_handle->aspace;
        HAL_IOMMUv3_ProgramCDField(CD_TTB0, asid_node->p_cd, (UINT64)p_aspace_local->tt_virt >> 4);
        HAL_IOMMUv3_ProgramCDField(CD_ASID, asid_node->p_cd, map_handle->asid);
        
        // Install CD into STE
        HAL_IOMMUv3_ProgramSTEField(STE_S1ContextPtr, asid_node->p_ste, (UINT64)asid_node->p_cd >> 6);
        
        // Invoke Paravirtualization SMC to Attach to IOMMUv3
        Parameters[0] = SMMU_PARAVIRT_OP_ATTACH;    // Operation
        Parameters[1] = sid;                        // Stream Id
        Parameters[4] = (UINT64)asid_node->p_ste;   // STE
        Parameters[5] = sizeof(hal_iommuv3_ste_t);  // size of ste
        Parameters[6] = (UINT64)asid_node->p_cd;    // CD
        Parameters[7] = sizeof(hal_iommuv3_cd_t);   // size of cd
        /* Make a SCM Sys call */
        Status = pQcomScmProtocol->ScmSipSysCall(pQcomScmProtocol,
                                                 TZ_MEM_PROTECT_SMMUV3_PARAVIRT,
                                                 TZ_MEM_PROTECT_SMMUV3_PARAVIRT_PARAM_ID,
                                                 Parameters,
                                                 Results
                                                );
        if(EFI_SUCCESS != Status) {
            DEBUG(( EFI_D_ERROR, "HAL_IOMMUv3_Set_Attribute: ScmSipSysCall(ATTACH) failed, Status = (0x%x), ECODE= (0x%x), Handle = (0x%x)\r\n", Status, Results[0], map_handle));
            return EFI_DEVICE_ERROR;
        }
        
        asid_node->attached = TRUE;
    }
        
    
    // TLBI
    // Invoke Paravirtualization SMC to Attach to IOMMUv3
    Parameters[0] = SMMU_PARAVIRT_OP_INVAL_ASID; // Operation
    Parameters[1] = sid;                         // Stream Id
    Parameters[2] = map_handle->asid;            // ASID
    Parameters[3] = 0;                           // Unused
    Parameters[4] = 0;                           // Unused
    Parameters[5] = 0;                           // Unused
    Parameters[6] = 0;                           // Unused
    Parameters[7] = 0;                           // Unused
    /* Make a SCM Sys call */
    Status = pQcomScmProtocol->ScmSipSysCall(pQcomScmProtocol,
                                             TZ_MEM_PROTECT_SMMUV3_PARAVIRT,
                                             TZ_MEM_PROTECT_SMMUV3_PARAVIRT_PARAM_ID,
                                             Parameters,
                                             Results
                                            );
    if(EFI_SUCCESS != Status) {
        DEBUG(( EFI_D_ERROR, "HAL_IOMMUv3_Set_Attribute ScmSipSysCall(INVAL_ASID) failed, Status = (0x%x), ECODE= (0x%x), Handle = (0x%x)\r\n", Status, Results[0], map_handle));
        return EFI_DEVICE_ERROR;
    }
    
    return EFI_SUCCESS;
}

/**
  Provides the controller-specific addresses required to access system memory from a
  DMA bus master.

  @param  This                  The protocol instance pointer.
  @param  Operation             Indicates if the bus master is going to read or write to system memory.
  @param  HostAddress           The system memory address to map to the PCI controller.
  @param  NumberOfBytes         On input the number of bytes to map. On output the number of bytes
                                that were mapped.
  @param  DeviceAddress         The resulting map address for the bus master PCI controller to use to
                                access the hosts HostAddress.
  @param  Mapping               A resulting value to pass to Unmap().

  @retval EFI_SUCCESS           The range was mapped for the returned NumberOfBytes.
  @retval EFI_UNSUPPORTED       The HostAddress cannot be mapped as a common buffer.
  @retval EFI_INVALID_PARAMETER One or more parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed due to a lack of resources.
  @retval EFI_DEVICE_ERROR      The system hardware could not map the requested address.

**/
EFI_STATUS
HAL_IOMMUv3_Map(
  IN     EDKII_IOMMU_PROTOCOL                       *This,
  IN     EDKII_IOMMU_OPERATION                      Operation,
  IN     VOID                                       *HostAddress,
  IN OUT UINTN                                      *NumberOfBytes,
  OUT    EFI_PHYSICAL_ADDRESS                       *DeviceAddress,
  OUT    VOID                                       **Mapping
)
{
    if(!pQcomScmProtocol)
        return EFI_UNSUPPORTED;
    // Allocate Mapping Object
    struct mapping_handle *map_handle = AllocatePool(sizeof(struct mapping_handle));
    if(!map_handle) {
        *NumberOfBytes = 0x0;
        *DeviceAddress = 0x0;
        *Mapping = NULL;
        return EFI_OUT_OF_RESOURCES;
    }
    
    // Populate Fields (And align buffer to page granule)
    map_handle->va = (UINT64)HostAddress & ~0xFFF;
    map_handle->pa = map_handle->va;
    map_handle->pages = ROUND_UP_4KB(((UINT64)HostAddress + *NumberOfBytes) - map_handle->va) / PAGE_SIZE;
    map_handle->perm = 0;
    map_handle->asid = INVALID_ASID;
    map_handle->aspace = NULL;
    
    *Mapping = (void *)map_handle;
    *DeviceAddress = (EFI_PHYSICAL_ADDRESS)HostAddress;
    
    return EFI_SUCCESS;
}

/**
  Completes the Map() operation and releases any corresponding resources.

  @param  This                  The protocol instance pointer.
  @param  Mapping               The mapping value returned from Map().

  @retval EFI_SUCCESS           The range was unmapped.
  @retval EFI_INVALID_PARAMETER Mapping is not a value that was returned by Map().
  @retval EFI_DEVICE_ERROR      The data was not committed to the target system memory.
**/
EFI_STATUS
HAL_IOMMUv3_Unmap(
  IN  EDKII_IOMMU_PROTOCOL                     *This,
  IN  VOID                                     *Mapping
)
{
    struct mapping_handle *map_handle = (struct mapping_handle *)Mapping;
    UINT64 Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 Results[SCM_MAX_NUM_RESULTS] = {0};
    EFI_STATUS Status;
    
    if(!pQcomScmProtocol)
        return EFI_UNSUPPORTED;
    
    if(!map_handle)
        return EFI_INVALID_PARAMETER;
    
    // Unmap
    if(HAL_IOMMU_ERR_OK != arch_mmu_unmap(map_handle->aspace, map_handle->va, map_handle->pages))
        return EFI_DEVICE_ERROR;
    
    // TLBI
    // Invoke Paravirtualization SMC to Attach to IOMMUv3
    Parameters[0] = SMMU_PARAVIRT_OP_INVAL_ASID; // Operation
    Parameters[1] = map_handle->sid;             // Stream Id
    Parameters[2] = map_handle->asid;            // ASID
    Parameters[3] = 0;                           // Unused
    /* Make a SCM Sys call */
    Status = pQcomScmProtocol->ScmSipSysCall(pQcomScmProtocol,
                                             TZ_MEM_PROTECT_SMMUV3_PARAVIRT,
                                             TZ_MEM_PROTECT_SMMUV3_PARAVIRT_PARAM_ID,
                                             Parameters,
                                             Results
                                            );
    if(EFI_SUCCESS != Status) {
        DEBUG(( EFI_D_ERROR, "HAL_IOMMUv3_Unmap: ScmSipSysCall(INVAL_ASID) failed, Status = (0x%x), ECODE= (0x%x), Handle = (0x%x)\r\n", Status, Results[0], map_handle));
        return EFI_DEVICE_ERROR;
    }
    
    // Free the handle
    FreePool(map_handle);
    
    return EFI_SUCCESS;
}

/**
  Allocates pages that are suitable for an OperationBusMasterCommonBuffer or
  OperationBusMasterCommonBuffer64 mapping.

  @param  This                  The protocol instance pointer.
  @param  Type                  This parameter is not used and must be ignored.
  @param  MemoryType            The type of memory to allocate, EfiBootServicesData or
                                EfiRuntimeServicesData.
  @param  Pages                 The number of pages to allocate.
  @param  HostAddress           A pointer to store the base system memory address of the
                                allocated range.
  @param  Attributes            The requested bit mask of attributes for the allocated range.

  @retval EFI_SUCCESS           The requested memory pages were allocated.
  @retval EFI_UNSUPPORTED       Attributes is unsupported. The only legal attribute bits are
                                MEMORY_WRITE_COMBINE, MEMORY_CACHED and DUAL_ADDRESS_CYCLE.
  @retval EFI_INVALID_PARAMETER One or more parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES  The memory pages could not be allocated.

**/
EFI_STATUS
HAL_IOMMUv3_Allocate_Buffer(
  IN     EDKII_IOMMU_PROTOCOL                     *This,
  IN     EFI_ALLOCATE_TYPE                        Type,
  IN     EFI_MEMORY_TYPE                          MemoryType,
  IN     UINTN                                    Pages,
  IN OUT VOID                                     **HostAddress,
  IN     UINT64                                   Attributes
)
{
    return EFI_UNSUPPORTED;
}

/**
  Frees memory that was allocated with AllocateBuffer().

  @param  This                  The protocol instance pointer.
  @param  Pages                 The number of pages to free.
  @param  HostAddress           The base system memory address of the allocated range.

  @retval EFI_SUCCESS           The requested memory pages were freed.
  @retval EFI_INVALID_PARAMETER The memory range specified by HostAddress and Pages
                                was not allocated with AllocateBuffer().

**/
EFI_STATUS
HAL_IOMMUv3_Free_Buffer(
  IN  EDKII_IOMMU_PROTOCOL                     *This,
  IN  UINTN                                    Pages,
  IN  VOID                                     *HostAddress
)
{
    return EFI_INVALID_PARAMETER;
}



VOID EFIAPI HAL_IOMMUv3_EBS_Callback(IN EFI_EVENT Event, IN VOID *Context)
{
    UINT64 Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 Results[SCM_MAX_NUM_RESULTS] = {0};
    EFI_STATUS Status;
    
    // Make SMC to Setup S1 in Bypass
    Parameters[0] = SMMU_PARAVIRT_OP_ALL_S1_BYPASS; // Operation
    Parameters[1] = 0x14F80000;             // SMMU Base Address
    /* Make a SCM Sys call */
    Status = pQcomScmProtocol->ScmSipSysCall(pQcomScmProtocol,
                                             TZ_MEM_PROTECT_SMMUV3_PARAVIRT,
                                             TZ_MEM_PROTECT_SMMUV3_PARAVIRT_PARAM_ID,
                                             Parameters,
                                             Results
                                            );
    if(EFI_SUCCESS != Status) {
        DEBUG(( EFI_D_ERROR, "HAL_IOMMUv3_EBS_Callback: ScmSipSysCall(ALL_S1_BYPASS) failed, Status = (0x%x), ECODE= (0x%x)\r\n", Status, Results[0]));
    }
}



EFI_STATUS
HAL_IOMMUv3_Init(VOID)
{
    EFI_STATUS Status;
    // Lookup Needed Protocols
    // Locate QCOM_SCM_PROTOCOL.
    Status = gBS->LocateProtocol ( &gQcomScmProtocolGuid,
                                   NULL,
                                   (VOID **)&pQcomScmProtocol
                                 );
    if(EFI_SUCCESS != Status) {
        DEBUG(( EFI_D_INFO, " Locate SCM Protocol failed, Status =  (0x%p)\r\n", Status));
        return Status;
    }
    
    // Default Context Descriptor Settings
    HAL_IOMMUv3_ProgramCDField(CD_T0SZ, (void *)&g_default_cd, 0x10); // 48-bit VA
    HAL_IOMMUv3_ProgramCDField(CD_TG0, (void *)&g_default_cd, 0x0); // 4KB page granule
    HAL_IOMMUv3_ProgramCDField(CD_IR0, (void *)&g_default_cd, 0x1); // Inner WB RA/WA Cached
    HAL_IOMMUv3_ProgramCDField(CD_OR0, (void *)&g_default_cd, 0x1); // Outer WB RA/WA Cached
    HAL_IOMMUv3_ProgramCDField(CD_SH0, (void *)&g_default_cd, 0x2); // Outer Shareable
    HAL_IOMMUv3_ProgramCDField(CD_EPD0, (void *)&g_default_cd, 0x0); // Enable TT0
    HAL_IOMMUv3_ProgramCDField(CD_ENDI, (void *)&g_default_cd, 0x0); // Little Endian
    HAL_IOMMUv3_ProgramCDField(CD_EPD1, (void *)&g_default_cd, 0x1); // Disable TT1
    HAL_IOMMUv3_ProgramCDField(CD_V, (void *)&g_default_cd, 0x1); // CD is Valid
    HAL_IOMMUv3_ProgramCDField(CD_IPS, (void *)&g_default_cd, 0x1); // 36-bit IPA
    HAL_IOMMUv3_ProgramCDField(CD_AFFD, (void *)&g_default_cd, 0x1); // Disable Access Flag Faults
    HAL_IOMMUv3_ProgramCDField(CD_WXN, (void *)&g_default_cd, 0x1); // DEP on Priviledged Pages
    HAL_IOMMUv3_ProgramCDField(CD_UWXN, (void *)&g_default_cd, 0x1); // DEP on Unprivileged Pages
    HAL_IOMMUv3_ProgramCDField(CD_AA64, (void *)&g_default_cd, 0x1); // AARCH64 PTs
    HAL_IOMMUv3_ProgramCDField(CD_S, (void *)&g_default_cd, 0x0); // DO NOT Stall Upon Faults
    HAL_IOMMUv3_ProgramCDField(CD_R, (void *)&g_default_cd, 0x1); // Record fault in Event Log
    HAL_IOMMUv3_ProgramCDField(CD_A, (void *)&g_default_cd, 0x1); // Return Abort Upstream
    HAL_IOMMUv3_ProgramCDField(CD_ASET, (void *)&g_default_cd, 0x1); // ASIDs not shared with CPU for DVM
    HAL_IOMMUv3_ProgramCDField(CD_MAIR, (void *)&g_default_cd, MMU_MAIR_VAL); // MAIR
    
    // Default Stream Table Entry Settings
    HAL_IOMMUv3_ProgramSTEField(STE_V, (void *)&g_default_ste, 0x1); // STE Valid
    HAL_IOMMUv3_ProgramSTEField(STE_Config, (void *)&g_default_ste, STE_CONFIG_S1T_S2B); // S1 Translate S2 Bypass
    HAL_IOMMUv3_ProgramSTEField(STE_S1CDMax, (void *)&g_default_ste, 0x0); // Single Context Descriptor
    HAL_IOMMUv3_ProgramSTEField(STE_S1_CIR, (void *)&g_default_ste, 0x1); // CD is Inner WB RA Cached
    HAL_IOMMUv3_ProgramSTEField(STE_S1_COR, (void *)&g_default_ste, 0x1); // CD is Outer WB RA Cached
    HAL_IOMMUv3_ProgramSTEField(STE_S1_CSH, (void *)&g_default_ste, 0x2); // CD is Outer Shareable
    HAL_IOMMUv3_ProgramSTEField(STE_S1_STALLD, (void *)&g_default_ste, 0x1); // Disable Stall
    
    return EFI_SUCCESS;
}


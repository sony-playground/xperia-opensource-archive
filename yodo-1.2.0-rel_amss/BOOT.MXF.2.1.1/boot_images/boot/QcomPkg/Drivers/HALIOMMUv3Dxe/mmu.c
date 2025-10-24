/*
 * Copyright (c) 2014 Google Inc. All rights reserved
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <mmu.h>
 

#include <stdlib.h>
#include <string.h>

#include "DebugLib.h"
#include <Library/MemoryAllocationLib.h>


#define LOCAL_TRACE 0
#define TRACE_CONTEXT_SWITCH 0

#define IS_ALIGNED(a, b) (!(((uintptr_t)(a)) & (((uintptr_t)(b))-1)))
#define IS_PAGE_ALIGNED(x) IS_ALIGNED(x, PAGE_SIZE)

#define PT_PA2VA(paddr) (uint64_t)((uint64_t)(paddr) - pt_mem_phys_offset)
#define PT_VA2PA(vaddr) (uint64_t)((uint64_t)(vaddr) + pt_mem_phys_offset)

static uint64_t pt_mem_phys_offset = 0;
extern VOID * HAL_IOMMU_InternalAllocatePages ( uint32_t Pages );

static inline boolean is_valid_vaddr(arch_aspace_t *aspace, vaddr_t vaddr)
{
    return (vaddr >= aspace->base && vaddr <= aspace->base + aspace->size - 1);
}

HAL_IOMMUResult_t arch_mmu_get_aspace_ttbr(void *p_aspace, uint64_t **pt_ttbaseaddr)
{
    HAL_IOMMUResult_t ret = HAL_IOMMU_ERR_OK;
    struct arch_aspace *p_aspace_local = (struct arch_aspace *)p_aspace;

      /* Input Validation */
    if (!p_aspace || !pt_ttbaseaddr)
        return HAL_IOMMU_ERR_NULL_POINTER;

    //DEBUG ((EFI_D_ERROR,"aspace %p, base 0x%lx, size 0x%zx \n", p_aspace_local, p_aspace_local->base, p_aspace_local->size));
  
    *pt_ttbaseaddr = p_aspace_local->tt_virt;

    return ret;
}
/* convert user level mmu flags to flags that go in L1 descriptors */
static pte_t mmu_flags_to_pte_attr(uint flags)
{
    pte_t attr = MMU_PTE_ATTR_AF;

    switch (flags & ARCH_MMU_FLAG_CACHE_MASK) {
        case ARCH_MMU_FLAG_CACHED:
            attr |= MMU_PTE_ATTR_NORMAL_MEMORY | MMU_PTE_ATTR_SH_INNER_SHAREABLE;
            break;
        case ARCH_MMU_FLAG_UNCACHED:
            attr |= MMU_PTE_ATTR_STRONGLY_ORDERED;
            break;
        case ARCH_MMU_FLAG_UNCACHED_DEVICE:
            attr |= MMU_PTE_ATTR_DEVICE;
            break;
        default:
            /* invalid user-supplied flag */
            DebugAssert(__FILE__,__LINE__, "Invalid user-supplied flag");
            return HAL_IOMMU_ERR_INVALID_PARAM;
    }

    switch (flags & (ARCH_MMU_FLAG_PERM_USER | ARCH_MMU_FLAG_PERM_RO)) {
        case 0:
            attr |= MMU_PTE_ATTR_AP_P_RW_U_NA;
            break;
        case ARCH_MMU_FLAG_PERM_RO:
            attr |= MMU_PTE_ATTR_AP_P_RO_U_NA;
            break;
        case ARCH_MMU_FLAG_PERM_USER:
            attr |= MMU_PTE_ATTR_AP_P_RW_U_RW;
            break;
        case ARCH_MMU_FLAG_PERM_USER | ARCH_MMU_FLAG_PERM_RO:
            attr |= MMU_PTE_ATTR_AP_P_RO_U_RO;
            break;
    }

    if (flags & ARCH_MMU_FLAG_PERM_NO_EXECUTE) {
        attr |= MMU_PTE_ATTR_UXN | MMU_PTE_ATTR_PXN;
    }

    if (flags & ARCH_MMU_FLAG_NS) {
        attr |= MMU_PTE_ATTR_NON_SECURE;
    }

    return attr;
}


HAL_IOMMUResult_t arch_mmu_query(arch_aspace_t *p_aspace, vaddr_t vaddr, paddr_t *paddr, uint *flags)
{
    uint index;
    uint index_shift;
    uint page_size_shift;
    pte_t pte;
    pte_t pte_addr;
    uint descriptor_type;
    pte_t *page_table;
    vaddr_t vaddr_rem;

    //DEBUG ((EFI_D_ERROR,"aspace %p, vaddr 0x%lx\n", p_aspace, vaddr));

    if (!is_valid_vaddr(p_aspace, vaddr))
        return HAL_IOMMU_ERR_OUT_OF_RANGE;


    index_shift = MMU_USER_TOP_SHIFT;
    page_size_shift = MMU_USER_PAGE_SIZE_SHIFT;

    vaddr_rem = vaddr;
    index = vaddr_rem >> index_shift;
    ASSERT(index < MMU_USER_PAGE_TABLE_ENTRIES_TOP);


    page_table = p_aspace->tt_virt;

    while (1) {
        index = vaddr_rem >> index_shift;
        vaddr_rem -= (vaddr_t)index << index_shift;
        pte = page_table[index];
        descriptor_type = pte & MMU_PTE_DESCRIPTOR_MASK;
        pte_addr = pte & MMU_PTE_OUTPUT_ADDR_MASK;

        /*DEBUG ((EFI_D_ERROR,"va 0x%lx, index %d, index_shift %d, rem 0x%lx, pte 0x%llx\n",
                vaddr, index, index_shift, vaddr_rem, pte));
        */
        if (descriptor_type == MMU_PTE_DESCRIPTOR_INVALID)
            return HAL_IOMMU_ERR_PTE_NOT_FOUND;

        if (descriptor_type == ((index_shift > page_size_shift) ?
                                MMU_PTE_L012_DESCRIPTOR_BLOCK :
                                MMU_PTE_L3_DESCRIPTOR_PAGE)) {
            break;
        }

        if (index_shift <= page_size_shift ||
                descriptor_type != MMU_PTE_L012_DESCRIPTOR_TABLE) {
            return HAL_IOMMU_ERR_GENERIC_ERROR;
        }

        page_table = (pte_t *)pte_addr;
        index_shift -= page_size_shift - 3;
    }

    if (paddr)
        *paddr = pte_addr + vaddr_rem;
    if (flags) {
        *flags = 0;
        if (pte & MMU_PTE_ATTR_NON_SECURE)
            *flags |= ARCH_MMU_FLAG_NS;
        switch (pte & MMU_PTE_ATTR_ATTR_INDEX_MASK) {
            case MMU_PTE_ATTR_STRONGLY_ORDERED:
                *flags |= ARCH_MMU_FLAG_UNCACHED;
                break;
            case MMU_PTE_ATTR_DEVICE:
                *flags |= ARCH_MMU_FLAG_UNCACHED_DEVICE;
                break;
            case MMU_PTE_ATTR_NORMAL_MEMORY:
                break;
            default:
                DebugAssert(__FILE__,__LINE__, "Not Implemented");;
        }
        switch (pte & MMU_PTE_ATTR_AP_MASK) {
            case MMU_PTE_ATTR_AP_P_RW_U_NA:
                break;
            case MMU_PTE_ATTR_AP_P_RW_U_RW:
                *flags |= ARCH_MMU_FLAG_PERM_USER;
                break;
            case MMU_PTE_ATTR_AP_P_RO_U_NA:
                *flags |= ARCH_MMU_FLAG_PERM_RO;
                break;
            case MMU_PTE_ATTR_AP_P_RO_U_RO:
                *flags |= ARCH_MMU_FLAG_PERM_USER | ARCH_MMU_FLAG_PERM_RO;
                break;
        }
        if ((pte & MMU_PTE_ATTR_UXN) && (pte & MMU_PTE_ATTR_PXN)) {
            *flags |= ARCH_MMU_FLAG_PERM_NO_EXECUTE;
        }
    }
    /*DEBUG ((EFI_D_ERROR,"va 0x%lx, paddr 0x%lx, flags 0x%x\n",
            vaddr, paddr ? *paddr : ~0UL, flags ? *flags : ~0U));
    */
    return HAL_IOMMU_ERR_OK;
}

/*
static HAL_IOMMUResult_t alloc_page_table(paddr_t *paddrp, uint page_size_shift)
{
    size_t size = 1U << page_size_shift;

    DEBUG ((EFI_D_ERROR,"page_size_shift %u\n", page_size_shift));

    if (size >= PAGE_SIZE) {
        size_t count = size / PAGE_SIZE;
        size_t ret = pmm_alloc_contiguous(count, page_size_shift, paddrp, NULL);
        if (ret != count)
            return HAL_IOMMU_ERR_MALLOC_FAILED;
    } else {
        void *vaddr = memalign(size, size);
        if (!vaddr)
            return HAL_IOMMU_ERR_MALLOC_FAILED;
        *paddrp = vaddr_to_paddr(vaddr);
        if (*paddrp == 0) {
            free(vaddr);
            return HAL_IOMMU_ERR_MALLOC_FAILED;
        }
    }

    DEBUG ((EFI_D_ERROR,"allocated 0x%lx\n", *paddrp));
    return HAL_IOMMU_ERR_OK;
}*/

static void free_page_table(void *vaddr, paddr_t paddr, uint page_size_shift)
{
    //DEBUG ((EFI_D_ERROR,"vaddr %p paddr 0x%lx page_size_shift %u\n", vaddr, paddr, page_size_shift));

    size_t size = 1U << page_size_shift;

    if (size >= PAGE_SIZE) {
        FreePages(vaddr, 1);
    }  
}

static pte_t *arm64_mmu_get_page_table(vaddr_t index, uint page_size_shift, pte_t *page_table)
{
    pte_t pte;
    void *vaddr;	
    paddr_t paddr;

    pte = page_table[index];
    switch (pte & MMU_PTE_DESCRIPTOR_MASK) {
        case MMU_PTE_DESCRIPTOR_INVALID:
			vaddr = HAL_IOMMU_InternalAllocatePages(1);//ToDo rrahul
			if (!vaddr)
                return NULL;

            //DEBUG ((EFI_D_ERROR,"allocated page table, vaddr 0x%lx\n", vaddr));
            memset(vaddr, MMU_PTE_DESCRIPTOR_INVALID, 1U << page_size_shift);

            __asm__ volatile("dmb ishst" ::: "memory");

            pte = PT_VA2PA(vaddr) | MMU_PTE_L012_DESCRIPTOR_TABLE;
            page_table[index] = pte;
            //DEBUG ((EFI_D_ERROR,"pte %p[0x%lx] = 0x%llx\n", page_table, index, pte));
            return vaddr;

        case MMU_PTE_L012_DESCRIPTOR_TABLE:
            paddr = pte & MMU_PTE_OUTPUT_ADDR_MASK;
            //DEBUG ((EFI_D_ERROR,"found page table 0x%lx\n", paddr));
            return (pte_t *)paddr;

        case MMU_PTE_L012_DESCRIPTOR_BLOCK:
            return NULL;

        default:
            DebugAssert(__FILE__,__LINE__, "Not Implemented");;
    }

    return NULL;
}

static boolean page_table_is_clear(pte_t *page_table, uint page_size_shift)
{
    int i;
    int count = 1U << (page_size_shift - 3);
    pte_t pte;

    for (i = 0; i < count; i++) {
        pte = page_table[i];
        if (pte != MMU_PTE_DESCRIPTOR_INVALID) {
            /*DEBUG ((EFI_D_ERROR,"page_table at %p still in use, index %d is 0x%llx\n",
                    page_table, i, pte));
            */
            return FALSE;
        }
    }

    //DEBUG ((EFI_D_ERROR,"page table at %p is clear\n", page_table));
    return TRUE;
}

static void arm64_mmu_unmap_pt(vaddr_t vaddr, vaddr_t vaddr_rel,
                               size_t size,
                               uint index_shift, uint page_size_shift,
                               pte_t *page_table, uint asid)
{
    pte_t *next_page_table;
    vaddr_t index;
    size_t chunk_size;
    vaddr_t vaddr_rem;
    vaddr_t block_size;
    vaddr_t block_mask;
    pte_t pte;
    paddr_t page_table_paddr;

    /*DEBUG ((EFI_D_ERROR,"vaddr 0x%lx, vaddr_rel 0x%lx, size 0x%lx, index shift %d, page_size_shift %d, page_table %p\n",
            vaddr, vaddr_rel, size, index_shift, page_size_shift, page_table));
    */
    while (size) {
        block_size = 1UL << index_shift;
        block_mask = block_size - 1;
        vaddr_rem = vaddr_rel & block_mask;
        chunk_size = MIN(size, block_size - vaddr_rem);
        index = vaddr_rel >> index_shift;

        pte = page_table[index];

        if (index_shift > page_size_shift &&
                (pte & MMU_PTE_DESCRIPTOR_MASK) == MMU_PTE_L012_DESCRIPTOR_TABLE) {
            page_table_paddr = pte & MMU_PTE_OUTPUT_ADDR_MASK;
            next_page_table = (pte_t *)page_table_paddr;
            arm64_mmu_unmap_pt(vaddr, vaddr_rem, chunk_size,
                               index_shift - (page_size_shift - 3),
                               page_size_shift,
                               next_page_table, asid);
            if (chunk_size == block_size ||
                    page_table_is_clear(next_page_table, page_size_shift)) {
                //DEBUG ((EFI_D_ERROR,"pte %p[0x%lx] = 0 (was page table)\n", page_table, index));
                page_table[index] = MMU_PTE_DESCRIPTOR_INVALID;
                __asm__ volatile("dmb ishst" ::: "memory");
                free_page_table(next_page_table, page_table_paddr, page_size_shift);
            }
        } else if (pte) {
            //DEBUG ((EFI_D_ERROR,"pte %p[0x%lx] = 0\n", page_table, index));
            page_table[index] = MMU_PTE_DESCRIPTOR_INVALID;
            CF;
            if (asid == MMU_ARM64_GLOBAL_ASID)
                ARM64_TLBI(vaae1is, vaddr >> 12);
            else
                ARM64_TLBI(vae1is, vaddr >> 12 | (vaddr_t)asid << 48);
        } else {
            DEBUG ((EFI_D_ERROR,"pte %p[0x%lx] already clear\n", page_table, index));
        }
        vaddr += chunk_size;
        vaddr_rel += chunk_size;
        size -= chunk_size;
    }
}

static HAL_IOMMUResult_t arm64_mmu_map_pt(vaddr_t vaddr_in, vaddr_t vaddr_rel_in,
                            paddr_t paddr_in,
                            size_t size_in, pte_t attrs,
                            uint index_shift, uint page_size_shift,
                            pte_t *page_table, uint asid)
{
    HAL_IOMMUResult_t ret;
    pte_t *next_page_table;
    vaddr_t index;
    vaddr_t vaddr = vaddr_in;
    vaddr_t vaddr_rel = vaddr_rel_in;
    paddr_t paddr = paddr_in;
    size_t size = size_in;
    size_t chunk_size;
    vaddr_t vaddr_rem;
    vaddr_t block_size;
    vaddr_t block_mask;
    pte_t pte;

    /*DEBUG ((EFI_D_ERROR,"vaddr 0x%lx, vaddr_rel 0x%lx, paddr 0x%lx, size 0x%lx, attrs 0x%llx, index shift %d, page_size_shift %d, page_table %p\n",
            vaddr, vaddr_rel, paddr, size, attrs,
            index_shift, page_size_shift, page_table));
    */
    if ((vaddr_rel | paddr | size) & ((1UL << page_size_shift) - 1)) {
        //DEBUG ((EFI_D_ERROR,"not page aligned\n"));
        return HAL_IOMMU_ERR_INVALID_PARAM;
    }

    while (size) {
        block_size = 1UL << index_shift;
        block_mask = block_size - 1;
        vaddr_rem = vaddr_rel & block_mask;
        chunk_size = MIN(size, block_size - vaddr_rem);
        index = vaddr_rel >> index_shift;

        if (((vaddr_rel | paddr) & block_mask) ||
                (chunk_size != block_size) ||
                (index_shift > MMU_PTE_DESCRIPTOR_BLOCK_MAX_SHIFT)) {
            next_page_table = arm64_mmu_get_page_table(index, page_size_shift,
                              page_table);
            if (!next_page_table)
                goto err;

            ret = arm64_mmu_map_pt(vaddr, vaddr_rem, paddr, chunk_size, attrs,
                                   index_shift - (page_size_shift - 3),
                                   page_size_shift, next_page_table, asid);
            if (ret)
                goto err;
        } else {
            pte = page_table[index];
            if (pte) {
                /*DEBUG ((EFI_D_ERROR,"page table entry already in use, index 0x%lx, 0x%llx\n",
                       index, pte));
                */
                goto err;
            }

            pte = paddr | attrs;
            if (index_shift > page_size_shift)
                pte |= MMU_PTE_L012_DESCRIPTOR_BLOCK;
            else
                pte |= MMU_PTE_L3_DESCRIPTOR_PAGE;

            //DEBUG ((EFI_D_ERROR,"pte %p[0x%lx] = 0x%llx\n", page_table, index, pte));
            page_table[index] = pte;
        }
        vaddr += chunk_size;
        vaddr_rel += chunk_size;
        paddr += chunk_size;
        size -= chunk_size;
    }

    return 0;

err:
    arm64_mmu_unmap_pt(vaddr_in, vaddr_rel_in, size_in - size,
                       index_shift, page_size_shift, page_table, asid);
    __asm("DSB sy");
    return HAL_IOMMU_ERR_GENERIC_ERROR;
}

HAL_IOMMUResult_t arm64_mmu_map(vaddr_t vaddr, paddr_t paddr, size_t size, pte_t attrs,
                  vaddr_t vaddr_base, uint top_size_shift,
                  uint top_index_shift, uint page_size_shift,
                  pte_t *top_page_table, uint asid)
{
    HAL_IOMMUResult_t ret;
    vaddr_t vaddr_rel = vaddr - vaddr_base;
    vaddr_t vaddr_rel_max = 1UL << top_size_shift;

    /*DEBUG ((EFI_D_ERROR,"vaddr 0x%lx, paddr 0x%lx, size 0x%lx, attrs 0x%llx, asid 0x%x\n",
            vaddr, paddr, size, attrs, asid));
    */
    /* Input Validation */
    if (vaddr_rel > vaddr_rel_max - size || size > vaddr_rel_max) {
        /*DEBUG ((EFI_D_ERROR,"vaddr 0x%lx, size 0x%lx out of range vaddr 0x%lx, size 0x%lx\n",
               vaddr, size, vaddr_base, vaddr_rel_max));
        */
        return HAL_IOMMU_ERR_INVALID_PARAM;
    }

    if (!top_page_table) {
        //DEBUG ((EFI_D_ERROR,"page table is NULL\n"));
        return HAL_IOMMU_ERR_INVALID_PARAM;
    }

    ret = arm64_mmu_map_pt(vaddr, vaddr_rel, paddr, size, attrs,
                           top_index_shift, page_size_shift, top_page_table, asid);
    __asm("DSB sy");
    return ret;
}

HAL_IOMMUResult_t arm64_mmu_unmap(vaddr_t vaddr, size_t size,
                    vaddr_t vaddr_base, uint top_size_shift,
                    uint top_index_shift, uint page_size_shift,
                    pte_t *top_page_table, uint asid)
{
    vaddr_t vaddr_rel = vaddr - vaddr_base;
    vaddr_t vaddr_rel_max = 1UL << top_size_shift;

    //DEBUG ((EFI_D_ERROR,"vaddr 0x%lx, size 0x%lx, asid 0x%x\n", vaddr, size, asid));

    if (vaddr_rel > vaddr_rel_max - size || size > vaddr_rel_max) {
        DEBUG ((EFI_D_ERROR,"vaddr 0x%lx, size 0x%lx out of range vaddr 0x%lx, size 0x%lx\n",
               vaddr, size, vaddr_base, vaddr_rel_max));
        return HAL_IOMMU_ERR_INVALID_PARAM;
    }

    if (!top_page_table) {
        //DEBUG ((EFI_D_ERROR,"page table is NULL\n"));
        return HAL_IOMMU_ERR_INVALID_PARAM;
    }

    arm64_mmu_unmap_pt(vaddr, vaddr_rel, size,
                       top_index_shift, page_size_shift, top_page_table, asid);
    __asm("DSB sy");
    return HAL_IOMMU_ERR_OK;
}

HAL_IOMMUResult_t arch_mmu_map(void *p_aspace, vaddr_t vaddr, paddr_t paddr, uint count, uint flags)
{
    HAL_IOMMUResult_t ret;
    struct arch_aspace *p_aspace_local = (struct arch_aspace *)p_aspace;
    pte_t attrs;

    //DEBUG ((EFI_D_ERROR,"vaddr 0x%lx paddr 0x%lx count %u flags 0x%x\n", vaddr, paddr, count, flags));

    /* Input Validation */
    if (!is_valid_vaddr(p_aspace_local, vaddr))
        return HAL_IOMMU_ERR_OUT_OF_RANGE;

    if (!IS_PAGE_ALIGNED(vaddr) || !IS_PAGE_ALIGNED(paddr))
        return HAL_IOMMU_ERR_BAD_ADDRESS;

    if (count == 0)
        return HAL_IOMMU_ERR_OK;

    attrs = mmu_flags_to_pte_attr(flags);
    if (attrs == HAL_IOMMU_ERR_INVALID_PARAM )
        return HAL_IOMMU_ERR_INVALID_PARAM;

	ret = arm64_mmu_map(vaddr, paddr, count * PAGE_SIZE, attrs,
                         0, MMU_USER_SIZE_SHIFT,
                         MMU_USER_TOP_SHIFT, MMU_USER_PAGE_SIZE_SHIFT,
					     p_aspace_local->tt_virt, MMU_ARM64_USER_ASID);    

    return ret;
}

HAL_IOMMUResult_t arch_mmu_unmap(void *p_aspace, vaddr_t vaddr, uint count)
{
    HAL_IOMMUResult_t ret;
    struct arch_aspace *p_aspace_local = (struct arch_aspace *)p_aspace;

    //DEBUG ((EFI_D_ERROR,"vaddr 0x%lx count %u\n", vaddr, count));

    /* Input Validation */
    if (p_aspace == NULL) 
        return HAL_IOMMU_ERR_NULL_POINTER;

    if (!is_valid_vaddr(p_aspace_local, vaddr))
        return HAL_IOMMU_ERR_OUT_OF_RANGE;

    //DEBUG_ASSERT(IS_PAGE_ALIGNED(vaddr));

    if (!IS_PAGE_ALIGNED(vaddr))
        return HAL_IOMMU_ERR_INVALID_PARAM;

    ret = arm64_mmu_unmap(vaddr, count * PAGE_SIZE,
                           0, MMU_USER_SIZE_SHIFT,
                           MMU_USER_TOP_SHIFT, MMU_USER_PAGE_SIZE_SHIFT,
					       p_aspace_local->tt_virt,
                           MMU_ARM64_USER_ASID);
  

    return ret;
}

HAL_IOMMUResult_t arch_mmu_init_aspace(void **p_aspace, vaddr_t base, size_t size )
{
    struct arch_aspace *p_new_aspace = NULL;
    pte_t *base_address = NULL;
    //DEBUG ((EFI_D_ERROR,"aspace %p, base 0x%lx, size 0x%lx, flags 0x%x\n", p_aspace, base, size));

    /* Input Validation */
    if (p_aspace == NULL) 
        return HAL_IOMMU_ERR_NULL_POINTER;

    if(size == 0 )
        return HAL_IOMMU_ERR_INVALID_PARAM;

    if (!IS_PAGE_ALIGNED(base) || !IS_PAGE_ALIGNED(size))
        return HAL_IOMMU_ERR_INVALID_PARAM;

    /* Allocate AddressSpace [aspace] Object */
    p_new_aspace = (struct arch_aspace *)AllocatePool(sizeof(struct arch_aspace));
    if(!p_new_aspace) 
        return HAL_IOMMU_ERR_MALLOC_FAILED;


    /* Initialize Members */
    memset((void*)p_new_aspace, 0x0, sizeof(struct arch_aspace));

    p_new_aspace->base = base;
    p_new_aspace->size = size;

    base_address = HAL_IOMMU_InternalAllocatePages(1); 
    if (!base_address)
        return HAL_IOMMU_ERR_MALLOC_FAILED;

    p_new_aspace->tt_virt = base_address;
    memset(p_new_aspace->tt_virt, 0, PAGE_SIZE); 

    //DEBUG ((EFI_D_ERROR,"tt_virt %p\n",  p_new_aspace->tt_virt));

    /* Return opaque domain handle to caller */
    *p_aspace = (void*)p_new_aspace;

    return HAL_IOMMU_ERR_OK;
}

HAL_IOMMUResult_t arch_mmu_destroy_aspace(void *p_aspace)
{
    //DEBUG ((EFI_D_ERROR,"aspace %p\n", p_aspace));

    //struct arch_aspace *p_aspace_local = (struct arch_aspace *)p_aspace;

    /* Input Validation */
    if(!p_aspace) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }

    // Unmap and Free all level of page table 
    //ToDo rrahul
    // write a recursive free function to find table entries in 512 entries table
    //Do we even need to write this as UEFI will reclaom all memoeyr
    //FreePages(p_aspace_local->tt_virt, 1);

    // Free Handle
    FreePool(p_aspace);

    return HAL_IOMMU_ERR_OK;

}



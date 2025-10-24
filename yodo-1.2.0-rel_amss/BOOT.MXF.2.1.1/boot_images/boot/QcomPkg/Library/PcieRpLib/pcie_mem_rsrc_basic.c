/**
  @file pcie_mem_rsrc_basic.c
  Memory resource managing routine.

  This module does a linear memory allocation for PCIe host controller without
  taking fragmentation into account. This is a simple allocator for memory
  restricted environments.

*/
/*
 ==============================================================================

          Edit History


  when       who     what, where, why
  --------   ---     ---------------------------------------------------------
  01/15/20   Yg      created new

 ==============================================================================
     Copyright (c) 2020 QUALCOMM Technologies Incorporated
     All Rights Reserved.  Qualcomm Confidential and Proprietary.
 ==============================================================================
*/

#include "pcie_mem_rsrc.h"
#include "pcie_host_log.h"
#include "string.h"

/* 
 * Context representing single fragmented memory region
 *
 * +----------------------+------------------+
 * |                      |                  |
 * |    mem_inuse         |  free_mem        |
 * |                      |                  |
 * +----------------------+------------------+
 * ^                      ^
 * |                      |
 * |                      |
 * |                      |
 * resource_base        free_base
 *
 *
 * In above situation any new allocations will happen adjacent
 * to the current allocation. Either lower side or upper side
 * is determined by which side is best suited based on alignment
 * requirement and size to keep largest free chunk still
 * available for later use.
 *
 * */
struct _pcie_mem_rsrc_ctx{
   uint64_t resource_base;
   uint64_t free_base;
   uint64_t resource_size;
};

pcie_mem_ctxt mem_ctxt_pool[MAX_MEM_CONTEXTS];
uint8_t mem_ctxt_pool_in_use[MAX_MEM_CONTEXTS];

/* Alignment of size/addr based on the value in question */
#define ALIGNMENT_OF(x)        (((x) & ((x) - 1)) ^ (x))

/* Macro to align a number to the next higher boundary */
#define UPALIGN(val,align)     (((val)|((align)-1)) + 1)


/*******************************************************************************
 *            Public functions
 ******************************************************************************/

pcie_mem_ctxt* open_mem_resource (uint64_t mem_base, uint64_t mem_size)
{
   int i;

   if ((mem_base == 0) || (mem_size == 0))
      return NULL;

   for (i=0; i < MAX_MEM_CONTEXTS; ++i)
   {
      if (mem_ctxt_pool_in_use[i] == 0)
      {
         mem_ctxt_pool_in_use[i] = 1;
         mem_ctxt_pool[i].resource_base = mem_base;
         mem_ctxt_pool[i].free_base = mem_base;
         mem_ctxt_pool[i].resource_size = mem_size;
         return &mem_ctxt_pool[i];
      }
   }

   return NULL;
}

mem_rsrc_status_t
close_mem_resource (pcie_mem_ctxt* ctxt)
{
   int i;

   if (ctxt == NULL)
      return MEM_RSRC_INVALID_ARGS;

   for (i=0; i < MAX_MEM_CONTEXTS; ++i)
   {
      if (ctxt == &mem_ctxt_pool[i])
      {
         mem_ctxt_pool_in_use[i] = 0;
         return MEM_RSRC_SUCCESS;
      }
   }
   return MEM_RSRC_NOT_FOUND;
}

mem_rsrc_status_t
get_resource_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr)
{
   if (ctxt == NULL)
      return MEM_RSRC_INVALID_ARGS;

   if ((mem_base_ptr == NULL) || (mem_size_ptr == NULL))
      return MEM_RSRC_INVALID_ARGS;

   *mem_base_ptr = ctxt->resource_base;
   *mem_size_ptr = ctxt->resource_size;

   return MEM_RSRC_SUCCESS;
}

mem_rsrc_status_t
get_allocated_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr)
{
   if (ctxt == NULL)
      return MEM_RSRC_INVALID_ARGS;

   if ((mem_base_ptr == NULL) || (mem_size_ptr == NULL))
      return MEM_RSRC_INVALID_ARGS;

   *mem_base_ptr = ctxt->resource_base;
   *mem_size_ptr = ctxt->free_base - ctxt->resource_base;

   return MEM_RSRC_SUCCESS;
}

mem_rsrc_status_t
allocate_mem (pcie_mem_ctxt* ctxt, uint64_t req_size, uint64_t* mem_ptr)
{
   uint64_t allocated_pa_base, bar_align_size, available_free_size, end_ptr;

   if (ctxt == NULL)
      return MEM_RSRC_INVALID_ARGS;

   if ((req_size == 0) || (mem_ptr == NULL))
      return MEM_RSRC_INVALID_ARGS;

   *mem_ptr = 0;

   /* Find the least position bit set and align to that position */
   bar_align_size = ALIGNMENT_OF (req_size);

   end_ptr = ctxt->resource_base + ctxt->resource_size;

   available_free_size = end_ptr - ctxt->free_base;

   allocated_pa_base = UPALIGN(ctxt->free_base,bar_align_size);

   if ((allocated_pa_base + req_size) > end_ptr)
      return MEM_RSRC_OUT_OF_MEMORY;

   ctxt->free_base = allocated_pa_base + req_size;

   *mem_ptr = allocated_pa_base;

   return MEM_RSRC_SUCCESS;
}



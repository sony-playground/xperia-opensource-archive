/**
  @file pcie_mem_rsrc.c
  Memory resource managing routine.

  This module manages the memory allocation for PCIe host controller
  for a given alignment and consequently keep all allocations together
  so that the memory doesn't get fragmented and make it easier to configure
  type 1 header range.

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

typedef struct {
   uint64_t base;
   uint64_t size;
}mem_pool_t;

/* 
 * Context representing single fragmented memory region
 *
 * +--------------+-----------------+------------------+
 * |              |                 |                  |
 * | lower_free   |   mem_inuse     |  upper_free      |
 * |              |                 |                  |
 * +--------------+-----------------+------------------+
 *
 * In above situation any new allocations will happen adjacent
 * to the current allocation. Either lower side or upper side
 * is determined by which side is best suited based on alignment
 * requirement and size to keep largest free chunk still
 * available for later use.
 *
 * */
struct _pcie_mem_rsrc_ctx{
   uint64_t signature;
   uint64_t resource_base;
   uint64_t resource_size;
   mem_pool_t lower_free;
   mem_pool_t mem_inuse;
   mem_pool_t upper_free;
};

pcie_mem_ctxt mem_ctxt_pool[MAX_MEM_CONTEXTS];
uint8_t mem_ctxt_pool_in_use[MAX_MEM_CONTEXTS];

/* Alignment of size/addr based on the value in question */
#define ALIGNMENT_OF(x)        (((x) & ((x) - 1)) ^ (x))

/* Macro to align a number to the next higher boundary */
#define UPALIGN(val,align)     (((val)|((align)-1)) + 1)

#define MEM_CTXT_SIGNATURE     0x123456789abcdef
//#define MEM_CTXT_SIGNATURE     (('P' << 56) || ('C' << 48) || ('I' << 40) || ('E' << 32) ||   \
  //                              ('M' << 24) || ('C' << 16) || ('X' << 8) || 'T')

typedef enum {
   ALLOC_ERROR = 0,
   ALLOC_FROM_START = 1,
   ALLOC_ADJ_LOWER  = 2,   // Adjacent preceeding the already allocated space
   ALLOC_ADJ_UPPER  = 3,   // Adjacent succeeding the allocated space
}alloc_source_t;

static void resolve_conflicts (pcie_mem_ctxt* ctxt)
{
   uint64_t allocated_end, region_end;
   if (ctxt->mem_inuse.base < (ctxt->lower_free.base + ctxt->lower_free.size))
      ctxt->lower_free.size = ctxt->mem_inuse.base - ctxt->lower_free.base;

   allocated_end = ctxt->mem_inuse.base + ctxt->mem_inuse.size;
   region_end = ctxt->upper_free.base + ctxt->upper_free.size;
   if (ctxt->upper_free.base < allocated_end)
   {
      ctxt->upper_free.base = allocated_end;
      ctxt->upper_free.size = region_end - allocated_end;
   }
}

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
         memset (&mem_ctxt_pool[i], 0, sizeof(mem_ctxt_pool[i]));
         mem_ctxt_pool[i].signature = MEM_CTXT_SIGNATURE;

         mem_ctxt_pool[i].resource_base = mem_base;
         mem_ctxt_pool[i].resource_size = mem_size;

         mem_ctxt_pool[i].lower_free.base = mem_base;
         mem_ctxt_pool[i].lower_free.size = mem_size;
         return &mem_ctxt_pool[i];
      }
   }

   return NULL;
}

mem_rsrc_status_t
close_mem_resource (pcie_mem_ctxt* ctxt)
{
   int i;

   if ((ctxt == NULL) || (ctxt->signature != MEM_CTXT_SIGNATURE))
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
   if ((ctxt == NULL) || (ctxt->signature != MEM_CTXT_SIGNATURE))
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
   if ((ctxt == NULL) || (ctxt->signature != MEM_CTXT_SIGNATURE))
      return MEM_RSRC_INVALID_ARGS;

   if ((mem_base_ptr == NULL) || (mem_size_ptr == NULL))
      return MEM_RSRC_INVALID_ARGS;

   *mem_base_ptr = ctxt->mem_inuse.base;
   *mem_size_ptr = ctxt->mem_inuse.size;

   return MEM_RSRC_SUCCESS;
}

mem_rsrc_status_t
get_upper_free_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr)
{
   if ((ctxt == NULL) || (ctxt->signature != MEM_CTXT_SIGNATURE))
      return MEM_RSRC_INVALID_ARGS;

   if ((mem_base_ptr == NULL) || (mem_size_ptr == NULL))
      return MEM_RSRC_INVALID_ARGS;

   *mem_base_ptr = ctxt->upper_free.base;
   *mem_size_ptr = ctxt->upper_free.size;

   return MEM_RSRC_SUCCESS;
}

mem_rsrc_status_t
get_lower_free_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr)
{
   if ((ctxt == NULL) || (ctxt->signature != MEM_CTXT_SIGNATURE))
      return MEM_RSRC_INVALID_ARGS;

   if ((mem_base_ptr == NULL) || (mem_size_ptr == NULL))
      return MEM_RSRC_INVALID_ARGS;

   *mem_base_ptr = ctxt->lower_free.base;
   *mem_size_ptr = ctxt->lower_free.size;

   return MEM_RSRC_SUCCESS;
}

/* Desired algorithm that can handle all fragmentation and coalescing:
 *  Have available memory structures (as many fragments to handle) and
 *  current allocation resources. Size argument also indicates what's
 *  the alignment required. If the current allocation already happened,
 *  then pick the memory adjacent to current allocation, on the side
 *  with least alignment or can fit on the least remaining side. Each
 *  Type 1 should pick just 1 contiguous range */
mem_rsrc_status_t
allocate_mem (pcie_mem_ctxt* ctxt, uint64_t req_size, uint64_t* mem_ptr)
{
   uint64_t allocated_pa_base, bar_align_size;
   alloc_source_t alloc_option = ALLOC_ERROR;

   if ((ctxt == NULL) || (ctxt->signature != MEM_CTXT_SIGNATURE))
      return MEM_RSRC_INVALID_ARGS;

   if ((req_size == 0) || (mem_ptr == NULL))
      return MEM_RSRC_INVALID_ARGS;

   *mem_ptr = 0;

   /* Find the least position bit set and align to that position */
   bar_align_size = ALIGNMENT_OF (req_size);

   /* Check if we have already allocated memory, if yes, then keep this
    * allocation adjacent, otherwise start with base */
   if (ctxt->mem_inuse.base == 0)
   {
      if ((ctxt->lower_free.base != 0) && (ctxt->lower_free.size >= bar_align_size))
      {
         alloc_option = ALLOC_FROM_START;
      }
      else
      {
         PCIE_HOST_LOG_ERROR (" Insufficient memory : Base 0x%X, Free sz 0x%X, Req 0x%X, Align : 0x%X\n",
            ctxt->lower_free.base, ctxt->lower_free.size, req_size, bar_align_size);
         return MEM_RSRC_OUT_OF_MEMORY;
      }
   }
   else
   {
      uint8_t lower_available = 0, upper_available = 0;
      uint64_t addr, align_compensation;

      /* Check size availability */
      align_compensation = 0;
      if (ALIGNMENT_OF(ctxt->upper_free.base) < bar_align_size)
        align_compensation = bar_align_size - ALIGNMENT_OF(ctxt->upper_free.base);

      if (ctxt->upper_free.size >= (bar_align_size + align_compensation))
         upper_available++;

      align_compensation = 0;
      addr = ctxt->mem_inuse.base - bar_align_size;
      if (ALIGNMENT_OF(addr) < bar_align_size)
        align_compensation = bar_align_size - ALIGNMENT_OF(addr);

      if (ctxt->lower_free.size >= (bar_align_size + align_compensation))
         lower_available++;

      if ((lower_available == 0) && (upper_available == 0))
      {
         PCIE_HOST_LOG_ERROR (" Out of memory : Req 0x%X, Align : 0x%X\n", req_size, bar_align_size);
         PCIE_HOST_LOG_ERROR ("    Free Base 0x%X, Sz 0x%X, In use Base 0x%X, Sz : 0x%X\n",
            ctxt->lower_free.base, ctxt->lower_free.size, ctxt->mem_inuse.base, ctxt->mem_inuse.size);
         PCIE_HOST_LOG_ERROR ("    Upper Free Base 0x%X, sz 0x%X, Req 0x%X, Align : 0x%X\n",
            ctxt->upper_free.base, ctxt->upper_free.size);
         return MEM_RSRC_OUT_OF_MEMORY;
      }

      if (lower_available != upper_available)
      {
         /* Easy choice, only 1 available */
         if (lower_available)
            alloc_option = ALLOC_ADJ_LOWER;

         if (upper_available)
            alloc_option = ALLOC_ADJ_UPPER;
      }
      else
      {
         if (bar_align_size == ctxt->lower_free.size)
            alloc_option = ALLOC_ADJ_LOWER;
         else if (bar_align_size == ctxt->upper_free.size)
            alloc_option = ALLOC_ADJ_UPPER;
         else
         {
            uint64_t align_lower, align_upper;
            align_lower = ALIGNMENT_OF(ctxt->mem_inuse.base);
            align_upper = ALIGNMENT_OF(ctxt->mem_inuse.base + ctxt->mem_inuse.size);

            if (align_lower == align_upper)
            {
               /* If both sizes are same then lets pick before */
               alloc_option = ALLOC_ADJ_LOWER;

               /* Otherwise pick smaller of the two */
               if (ctxt->upper_free.size < ctxt->lower_free.size)
                  alloc_option = ALLOC_ADJ_UPPER;
               else if (ctxt->upper_free.size > ctxt->lower_free.size)
                  alloc_option = ALLOC_ADJ_LOWER;
            }
            else if (align_lower < align_upper)
               alloc_option = ALLOC_ADJ_LOWER;
            else if (align_lower > align_upper)
               alloc_option = ALLOC_ADJ_UPPER;
         }
      }
   }

   /* If we are here, we have our pick, allocate now, here we just
    * include the required memory to be allocated into the in use
    * memory and later resolve the conflicts with free mem range */
   switch (alloc_option)
   {
      case ALLOC_FROM_START:
            allocated_pa_base = UPALIGN (ctxt->lower_free.base, bar_align_size);

            ctxt->mem_inuse.base = allocated_pa_base;
            ctxt->mem_inuse.size = req_size;

            if (ctxt->upper_free.base == 0)
            {
               /* Just assign to cover full range till end, later we adjust */
               ctxt->upper_free.base = ctxt->lower_free.base;
               ctxt->upper_free.size = ctxt->lower_free.size;
            }
            break;

      case ALLOC_ADJ_LOWER:
            allocated_pa_base = ctxt->mem_inuse.base - req_size;
            req_size += (allocated_pa_base & (bar_align_size - 1));

            /* Move to lower address to align */
            allocated_pa_base = (allocated_pa_base & (~(bar_align_size - 1)));

            ctxt->mem_inuse.base = allocated_pa_base;
            ctxt->mem_inuse.size += req_size;
            break;

      case ALLOC_ADJ_UPPER:
            {
               uint64_t val_to_adjust, allocated_alignment;

               allocated_pa_base = ctxt->mem_inuse.base + ctxt->mem_inuse.size;

               allocated_alignment = allocated_pa_base & (bar_align_size - 1);

               val_to_adjust = 0;
               if (allocated_alignment)
                  val_to_adjust = bar_align_size - allocated_alignment;

               req_size += val_to_adjust;
               allocated_pa_base += val_to_adjust;
               ctxt->mem_inuse.size += req_size;
            }
            break;


      default:
         return MEM_RSRC_ERROR_UNKNOWN;
   }

   /* Now adjust all the conflicts */
   resolve_conflicts(ctxt);

   *mem_ptr = allocated_pa_base;

   return MEM_RSRC_SUCCESS;
}

mem_rsrc_status_t mark_mem_allocated (pcie_mem_ctxt* ctxt, uint64_t alloc_base, uint64_t alloc_size)
{
   uint64_t allocated_end, added_size;

   if ((ctxt == NULL) || (ctxt->signature != MEM_CTXT_SIGNATURE))
      return MEM_RSRC_INVALID_ARGS;

   if ((alloc_base < ctxt->resource_base) ||
       ((alloc_base + alloc_size) > (ctxt->resource_base + ctxt->resource_size)))
      return MEM_RSRC_INVALID_ARGS;

   if (alloc_base < (ctxt->lower_free.base + ctxt->lower_free.size))
   {
      added_size = (ctxt->lower_free.base + ctxt->lower_free.size) - alloc_base;
      ctxt->mem_inuse.base = alloc_base;
      ctxt->mem_inuse.size += added_size;
   }

   allocated_end = ctxt->mem_inuse.base + ctxt->mem_inuse.size;
   if ((alloc_base + alloc_size) > allocated_end)
      ctxt->mem_inuse.size = (alloc_base + alloc_size) - ctxt->mem_inuse.base;

   resolve_conflicts(ctxt);

   return MEM_RSRC_SUCCESS;
}


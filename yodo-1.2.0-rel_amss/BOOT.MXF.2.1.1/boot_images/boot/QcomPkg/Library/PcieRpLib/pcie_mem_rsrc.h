#ifndef __PCIE_RC_MEM_RSRC_H__
#define __PCIE_RC_MEM_RSRC_H__

/**
  @file pcie_mem_rsrc.h
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

#include "com_dtypes.h"
#include "pcie_osal.h"

struct _pcie_mem_rsrc_ctx;
typedef struct _pcie_mem_rsrc_ctx pcie_mem_ctxt;

typedef enum
{
   MEM_RSRC_SUCCESS       = 0,
   MEM_RSRC_INVALID_ARGS  = 1,
   MEM_RSRC_NOT_FOUND     = 2,
   MEM_RSRC_OUT_OF_MEMORY = 3,
   MEM_RSRC_ERROR_UNKNOWN = 4,
}mem_rsrc_status_t;

pcie_mem_ctxt* open_mem_resource (uint64_t mem_base, uint64_t mem_size);

mem_rsrc_status_t close_mem_resource (pcie_mem_ctxt* ctxt);

mem_rsrc_status_t get_resource_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr);

mem_rsrc_status_t get_allocated_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr);

mem_rsrc_status_t get_free_upper_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr);

mem_rsrc_status_t get_free_lower_range (pcie_mem_ctxt* ctxt, uint64_t* mem_base_ptr, uint64_t* mem_size_ptr);

mem_rsrc_status_t allocate_mem (pcie_mem_ctxt* ctxt, uint64_t size, uint64_t* mem_ptr);

mem_rsrc_status_t mark_mem_allocated (pcie_mem_ctxt* ctxt, uint64_t mem_base, uint64_t mem_size);


#endif //__PCIE_RC_MEM_RSRC_H__


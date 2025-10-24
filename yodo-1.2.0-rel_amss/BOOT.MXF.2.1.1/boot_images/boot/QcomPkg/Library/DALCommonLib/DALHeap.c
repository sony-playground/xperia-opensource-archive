/** @file DALHeap.c

  DAL Heap

  Copyright (c) 2015-2020,2022 Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/13/22   ds      heap init with reserved align carveout
 02/05/22   ds      skip allocation from uncached heap for DALHEAP_ANY request
 02/11/21   ak      Add check if memType is out of range.
 04/07/20   ak      Added ability to allocate with type
 01/30/17   ak      Ported memheap_lite 
 03/27/15   unr     64 bit fixes
 08/11/14   sho     Creation

=============================================================================*/
#include "DALStdDef.h"
#include "DALHeap.h"
#include "DALSys.h" 
#include "memheap_lite.h"

#define MAX_NUM_DALHEAPS 9

typedef struct 
{
    mem_heap_type heap_struct;
    uint8_t initialized;
    void* pHeapBase;
}DALSYSMemState;

static DALSYSMemState memState[MAX_NUM_DALHEAPS] = {{{0}, FALSE},
                                                   {{0}, FALSE},
                                                   {{0}, FALSE},
                                                   {{0}, FALSE},
                                                   {{0}, FALSE},
                                                   {{0}, FALSE}, 
                                                   {{0}, FALSE}, 
                                                   {{0}, FALSE}, 
                                                   {{0}, FALSE}  
                                                   }; 
  

DALResult DALSYS_HeapInit(VOID *pHeapBase, 
                           unsigned int dwHeapSz, 
                           DALHEAP_MEM_TYPE memType,
                           unsigned int alignment,
	                         unsigned int number_of_chunks){
    int idx =0;

    //check if memType is out of bounds
    if (memType >= MAX_NUM_DALHEAPS)
      return DAL_ERROR;

    //User does not want specifc type of memory, find an empty slot
    if(DALHEAP_ANY == memType){
        for(idx = DALHEAP_FREE_SLOTS; idx < MAX_NUM_DALHEAPS; idx++){
            if(memState[idx].initialized == FALSE) 
                break;
        }
        if(idx == MAX_NUM_DALHEAPS)
            return DAL_ERROR; //All slots taken
    }
    //User passed a specific memType
    else {  
        if(memState[memType].initialized != FALSE)
            return DAL_ERROR; //already initialized this type
        idx = memType;
    }
	
    //check if memType is out of bounds
    if (idx >= MAX_NUM_DALHEAPS || idx < 0)
      return DAL_ERROR;
    // Set flag to indicate that we have initialized this heap
    memState[idx].initialized = 0x1;
    // Initialize heap structure with all zeros
    memset(&memState[idx].heap_struct, 0, sizeof(mem_heap_type));
    // Initialize the heap
    mem_init_heap_with_resrv_alignd_mem(&memState[idx].heap_struct, pHeapBase, dwHeapSz, alignment, number_of_chunks);
    // keep track of heap base ptr
    memState[idx].pHeapBase = pHeapBase;
    return DAL_SUCCESS;

}

DALResult DALSYS_HeapDeInit(VOID *pHeapBase){ 
	//Find which heap is being freed
    int idx =0;
    for(idx =0; idx < MAX_NUM_DALHEAPS; idx++){
    	if(memState[idx].pHeapBase == pHeapBase){
    		mem_deinit_heap(&(memState[idx].heap_struct));
    		memState[idx].initialized = FALSE;
    		memset(&memState[idx].heap_struct, 0, sizeof(mem_heap_type));
    		memState[idx].pHeapBase = NULL;
    		return DAL_SUCCESS;
    	}
    }
    return DAL_ERROR;
}


DALResult DALSYS_HeapForceDeInit(VOID *pHeapBase){
    //Find which heap is being freed
    int idx =0;
    for(idx =0; idx < MAX_NUM_DALHEAPS; idx++){
        if(memState[idx].pHeapBase == pHeapBase){
            mem_force_deinit_heap(&(memState[idx].heap_struct));
            memState[idx].initialized = FALSE;
            memset(&memState[idx].heap_struct, 0, sizeof(mem_heap_type));
            memState[idx].pHeapBase = NULL;
            return DAL_SUCCESS;
        }
    }
    return DAL_ERROR;
}



DALResult
DALSYS_Memalign(UINT32 dwSize, UINT32 alignment, VOID **ppMem)
{
  int idx=0;
   for(idx =0; idx < MAX_NUM_DALHEAPS; idx++)
   {
     if(idx == DALHEAP_UNCACHED)
        continue;
     // If the pointer to the pointer is null, skip it
     if(ppMem != NULL)
     {
         // Call into mem_malloc
         *ppMem = mem_memalign(&memState[idx].heap_struct, alignment, dwSize);
         if(*ppMem != NULL)
         {
             return DAL_SUCCESS;
         }
     }
   }

   return DAL_ERROR;
}



DALResult
DALSYS_MallocType(unsigned int dwSize, VOID **ppMem, DALHEAP_MEM_TYPE memType){
    
    int idx =0;
    
    //check if memType if out of bounds
    if (memType >= MAX_NUM_DALHEAPS || NULL == ppMem)
      return DAL_ERROR;

    if(memType != DALHEAP_ANY){
        *ppMem = mem_malloc(&memState[memType].heap_struct, dwSize);
        if(*ppMem != NULL){
           return DAL_SUCCESS;
        }
        return DAL_ERROR;
    }

    //DALHEAP_ANY is asked
    for(idx =0; idx < MAX_NUM_DALHEAPS; idx++){
      if(idx == DALHEAP_UNCACHED)
        continue;
       *ppMem = mem_malloc(&memState[idx].heap_struct, dwSize);
       if(*ppMem != NULL){
           return DAL_SUCCESS;
       } 
    } 

   return DAL_ERROR;
}

/*Gives an address from first available heap region*/
DALResult
DALSYS_Malloc(unsigned int dwSize, VOID **ppMem){
    return DALSYS_MallocType(dwSize, ppMem, DALHEAP_ANY);
}


DALResult
DALSYS_Free(VOID *pmem)
{
   int  idx =0;
   // Check to see which heap this pointer came from (and if that heap was initialized)
   for(idx =0; idx < MAX_NUM_DALHEAPS; idx++){
   		if(memState[idx].initialized && \
      	((pmem >= (void*) memState[idx].heap_struct.first_block) && \
       	(pmem < (((void*) memState[idx].heap_struct.first_block) + memState[idx].heap_struct.total_bytes))))
   		{
   			mem_free(&memState[idx].heap_struct, pmem);
   			return DAL_SUCCESS;
   		}
   }
   if(idx == MAX_NUM_DALHEAPS) return DAL_ERROR; //pointer passed didn't come from any existing heaps
   return DAL_SUCCESS;
}

DALResult
DALSYS_HeapGetStatus(DALHEAP_MEM_TYPE memType, void** pHeapBase){

  /*check if memType is out of bounds*/
  if (memType >= MAX_NUM_DALHEAPS)
    return DAL_ERROR;

  /*Set the current value of pHeapBase at the index*/
  /*If heap is un-initialzed, this should be set to NULL by default*/
  *pHeapBase = memState[memType].pHeapBase;

  return DAL_SUCCESS;
}

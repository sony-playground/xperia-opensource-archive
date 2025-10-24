#ifndef _DAL_HEAP
#define _DAL_HEAP
/*==============================================================================
@file DALHeap.h


        Copyright (c) 2020 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary


==============================================================================*/

// Supported memory types for heap
typedef enum 
{
   DALHEAP_ANY = -1,  
   DALHEAP_IMEM = 0,
   DALHEAP_DDR = 1,
   DALHEAP_UNCACHED =2,
   DALHEAP_FREE_SLOTS =3,
}
DALHEAP_MEM_TYPE;

/*=============================================================================
                           PROTOTYPE DECLARATIONS
=============================================================================*/
/**
  @brief Initialize internal and external heap

  Invoke to provide heap memory to heap manager
  to heap manager.

  @param pHeapBase  : Base address of the heap
  @param dwHeapSz   : Size of the heap
  @param memType    : Type of heap

  @return Dal - Success/Failure
*/
DALResult DALSYS_HeapInit(VOID *pHeapBase, unsigned int dwHeapSz, 
      DALHEAP_MEM_TYPE memType,
      unsigned int alignment,
	    unsigned int number_of_chunks);

/**
  @brief De-Initialize a heap given its base address

  Invoke to remove a heap memory region from the list of heaps
  currently managed by heap manager.

  @param pHeapBase  : Base address of the heap

  @return Dal - Success/Failure
*/
DALResult DALSYS_HeapDeInit(VOID *pHeapBase); 


/**
  @brief Force De-Initialize a heap given its base address

  Invoke to remove a heap memory region from the list of heaps
  currently managed by heap manager even if the heap is under use 
  and not in reset state.

  The API client is responsible for any side effect of the 
  heap force deinit such as :
   - the user who had the memory still allocated , if later calls free() for that memory ptr.
   - the user who had the memory still allocated, may still be actively using the memory so 
     if after the force_deinit heap the heap memory relinquished for some other purpose
   then the active user may corrupt it since it still holds the heap memory address
  
  @param pHeapBase  : Base address of the heap

  @return Dal - Success/Failure
*/
DALResult DALSYS_HeapForceDeInit(VOID *pHeapBase); 

/**
  @brief Allocate memory from available heap regions.

  Invoke to allocate memory from the list of heaps currently managed by heap manager.

  If specified DALHEAP_MEM_TYPE is DALHEAP_ANY, a random heap memory region will be
  chosen to allocate from.
  
  @param dwSize  : Allocation size
  @param ppMem   : Address of allocated memory range
                   will be stored in this pointer.
  @param memType : Type of memory to be allocated

  @return Dal - Success/Failure
*/
DALResult DALSYS_MallocType(unsigned int dwSize, VOID **ppMem, DALHEAP_MEM_TYPE memType);

/**
  @brief Return current status of a given heap.

  For the provided DALHEAP_MEM_TYPE, if the heap is initialized and is actively managed by heap manager,
  API returns the pointer to heap structure.

  @param memType : Type of heap  
  @param pHeapBase  : NULL if heap is not initialized
                    : non-NULL pointer to heap structure 
                    
  @return Dal - Success/Failure
*/
DALResult DALSYS_HeapGetStatus(DALHEAP_MEM_TYPE memType, void** pHeapBase);
#endif //_DAL_HEAP


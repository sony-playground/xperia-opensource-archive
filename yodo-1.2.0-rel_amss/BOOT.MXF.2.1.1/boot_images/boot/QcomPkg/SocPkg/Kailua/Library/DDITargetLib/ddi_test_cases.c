/**
 * @file ddi_test_cases.c
 * @brief
 * DDI test cases.
 */
/*=============================================================================

                                DDI Test cases
                                Source File
GENERAL DESCRIPTION
This file defines the DDI test cases

  Copyright (c) 2016-2017,2020-2022 QUALCOMM Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
===============================================================================

===============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

===============================================================================
when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/19/17   na      Initial version
==============================================================================*/

/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <string.h>
#include "stdint.h"
#include "ddr_params.h"
#include "ddi_flash_params.h"
#include "ddi_testing.h"
#include "ddi_test_cases.h"
#include "DALSys.h"
#include <Library/ArmMmuLib.h>
#include <ArmMmuLibEfiAttributesMap.h>


/*==============================================================================
                                  DATA
==============================================================================*/

#define MAX_TEST_PATTERN_SIZE 32
#define MEMREAD_SIZE 0x10000  //alined to row address


#if DDI_PRINT_ENABLE
extern char ddi_log_string[100];
#endif

uint32 swsys_mul_wid = 0xFCA01979;
uint32 swsys_mul_zid = 0xBA031903;

struct ddr_test_region_t ddr_test_region[MAX_DDR_REGIONS] = {{0}};
uint32 num_ddr_test_region;

peg_frequency ddi_setparam_pegfreq_func_ptr = NULL;

uint64 mem_pattern[MAX_TEST_PATTERN_SIZE*2];

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/


/* ============================================================================
**  Function : ddi_malloc
** ============================================================================
*/
void* ddi_malloc(size_t size)
{
  DALResult ret;
  void* mem_p;

  if(size> UINT32_MAX) {return NULL;}
  
  ret = DALSYS_Malloc( (uint32)size,(void**)&mem_p);
  if (ret != DAL_SUCCESS)
  {
    // DALSYS_Malloc doesn't guarantee NULL pOut like normal malloc
    mem_p = NULL;
  }
  return mem_p;
}
/* ============================================================================
**  Function : ddi_free
** ============================================================================
*/
void ddi_free(void* buffer_p)
{
  DALSYS_Free(buffer_p);
}


/* ============================================================================
**  Function : ddi_get_frequency_plan_index
** ============================================================================
*/
int8 ddi_get_frequency_plan_index(uint32 freq_khz)
{
  int8 i;
  int8 freq_plan_index=-1;

  if (freq_khz == 0)
  {
    return -1;
  }

  for (i=0;i<(sizeof(ddr_driver_struct->aop_params->mc_states)/sizeof(ddr_driver_struct->aop_params->mc_states[0]));i++)
  {
    if (freq_khz == ddr_driver_struct->aop_params->mc_states[i].freq_khz)
    {
      freq_plan_index = i;
      break;
    }
  }

    return freq_plan_index;
}

/* ============================================================================
**  Function : ddi_get_rank
** ============================================================================
*/
/*!
*   @brief
*   Based on address, get rank
*
*   @param addr        -   [IN] address to translate
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval uint64
*
*   @sa None
*/
uint64 ddi_get_rank (uint64* addr)
{
  uint8 i;
  uint64 rank=0;

  for (i=0;i<num_ddr_test_region;i++)
  {
    if (((uint64)addr >= ddr_test_region[i].start)  && ((uint64)addr < ddr_test_region[i].end))
    {
    rank=ddr_test_region[i].rank;
    break;
  }
  }

  return rank;
}

/* ============================================================================
**  Function : ddi_get_channel
** ============================================================================
*/
/*!
*   @brief
*   Based on address, get channel
*
*   @param addr        -   [IN] address to translate
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval uint64
*
*   @sa None
*/
uint64 ddi_get_channel (uint64* addr) {
  return (uint64)addr >> 8 & 0x3;
}

/* ============================================================================
**  Function : ddi_get_row
** ============================================================================
*/
/*!
*   @brief
*   Based on address, get row
*
*   @param addr        -   [IN] address to translate
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval uint64
*
*   @sa None
*/
uint64 ddi_get_row (uint64* addr)
{
  return (uint64)addr >> 16 & 0xFFFF;
}


/* ============================================================================
**  Function : swsys_srand_uefi
** ============================================================================
*/
/*!
*   @brief
*   set seed for random data generation
*
*   @details
*   set seed for random data generation
*   if seen value is 0, then a predefined seed value will be used
*
*   @param seed        -   [IN] seed value to set
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void swsys_srand_uefi (uint32 seed)
{
  if (seed != 0 && seed != 0x464FFFFF) {
    swsys_mul_wid = seed;
  }
  else {
    swsys_mul_wid = 0xFCA01979;
  }
  swsys_mul_zid = 0xBA031903;
}

/* ============================================================================
**  Function : swsys_srand_uefi_32
** ============================================================================
*/
/*!
*   @brief
*   get random int32
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval int32
*
*   @sa None
*/
int32 swsys_rand_uefi_32 ()
{
  swsys_mul_zid = 36969 * (swsys_mul_zid & 65535) + (swsys_mul_zid >> 16);
  swsys_mul_wid = 18000 * (swsys_mul_wid & 65535) + (swsys_mul_wid >> 16);
  return ((swsys_mul_zid << 16) + swsys_mul_wid);
}

/* ============================================================================
**  Function : swsys_srand_uefi_64
** ============================================================================
*/
/*!
*   @brief
*   get random int64
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval int64
*
*   @sa None
*/
int64 swsys_rand_uefi_64 ()
{
  return ((int64)swsys_rand_uefi_32() << 32) + swsys_rand_uefi_32();
}

/* ============================================================================
**  Function : address_printer_w
** ============================================================================
*/
/*!
*   @brief
*   Print DDR address under test
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval void
*
*   @sa None
*/
static void address_printer_w(uint64 ptr)
{
  if((ptr&(MEMREAD_SIZE-1))==0)
  {
    snprintf(ddi_log_string, sizeof(ddi_log_string), " write:addr=0x%016lx", ptr);
    boot_log_message(ddi_log_string);
  }
}


/* ============================================================================
**  Function : address_printer_r
** ============================================================================
*/
/*!
*   @brief
*   Print DDR address under test
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval void
*
*   @sa None
*/
static void address_printer_r(uint64 ptr)
{
  if((ptr&(MEMREAD_SIZE-1))==0)
  {
    snprintf(ddi_log_string, sizeof(ddi_log_string), " read:addr=0x%016lx", ptr);
    boot_log_message(ddi_log_string);
  }
}

/* ============================================================================
**  Function : ddi_cmp_set_failure
** ============================================================================
*/
/*!
*   @brief
*   entry point for logging a data comparison failure
*
*   @details
*   run when a data comparison mismatch is seen when validating a test case
*
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param addr        -   [IN] failing address
*   @param expected_val-   [IN] expected data
*   @param read_val    -   [IN] read data
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval boolean
*
*   @sa None
*/
boolean ddi_cmp_set_failure(ddi_cmp_params* cmp_params, uint64* addr, uint64 expected_val, uint64 read_val)
{
  return cmp_params->handle_fail(cmp_params->handle_fail_params, addr, expected_val, read_val, cmp_params->output_iter);
}

/* ============================================================================
**  Function : ddr_setpattern
** ============================================================================
*/
/*!
*   @brief
*   sets a user defined pattern to a data region
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_setpattern(uint64* start, uint64* end, uint64* pattern, uint64 pattern_size, uint8 log)
{
  uint64 *ptr = start;
  uint64 i;
  uint64 size;


  if(pattern_size <= MAX_TEST_PATTERN_SIZE)
  {
    for (i = 0; i < MAX_TEST_PATTERN_SIZE*2; i++)
	{
      mem_pattern[i] = *(pattern + i %pattern_size);
    }

    while (ptr < end)
    {
      size = ptr -start;
      ddi_memcpy256(ptr, &mem_pattern[size%pattern_size], MAX_TEST_PATTERN_SIZE);
#if DDI_PRINT_ENABLE
      if(log==1)
	    address_printer_w((uint64)ptr);
#endif	  
      ptr += MAX_TEST_PATTERN_SIZE;
    }
  }
  else
  {
    for (i = 0; i < pattern_size; i++)
    {
      //move to imem
      mem_pattern[i] = *(pattern + i);
    }

    while (ptr < end)
    {
      size = ((end - ptr) > pattern_size)?pattern_size:(end - ptr);
      ddi_memcpy(ptr, &mem_pattern[0], size);
#if DDI_PRINT_ENABLE
      if(log==1)
        address_printer_w((uint64)ptr);
#endif	  
      ptr += size;
    }
  }

  return DDI_CMD_COMPLETE;
}

/* ============================================================================
**  Function : ddr_cmppattern
** ============================================================================
*/
/*!
*   @brief
*   compare data region against a user defined pattern
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_cmppattern(uint64* start, uint64* end, uint64* pattern, uint64 pattern_size, ddi_cmp_params* cmp_params, uint8 log)
{
  ddi_error ret = DDI_CMD_NOT_COMPLETE;
  uint64 *ptr = start;
  uint64 read_value;
  uint64 result_code;
  uint64 size;
  uint64 i;
    // TODO: validate that expected_val is not a read failure
  if(pattern_size <= MAX_TEST_PATTERN_SIZE)
  {
    for (i = 0; i < MAX_TEST_PATTERN_SIZE*2; i++)
    {
      mem_pattern[i] = *(pattern + i %pattern_size);
    }

    while (ptr < end)
    {
      size=(ptr-start);
      result_code=ddi_memcmp(ptr, &mem_pattern[size%pattern_size], MAX_TEST_PATTERN_SIZE);
      if(result_code !=0)
      {
        ret |= DDI_CMD_FAIL;
        read_value = *(uint64 *)result_code;
        if (ddi_cmp_set_failure(cmp_params, (uint64 *)result_code, *(pattern +((uint64)(ptr-start)%pattern_size) +((uint64 *)result_code-ptr)), read_value))
        {
          return ret;
        }
      }
#if DDI_PRINT_ENABLE
    if(log==1)
        address_printer_r((uint64)ptr);
#endif	  
    ptr += MAX_TEST_PATTERN_SIZE;
    }
  }
  else
  {
    //size = pattern_size;
    for (i = 0; i < pattern_size; i++)
    {
      //move to imem
      mem_pattern[i] = *(pattern + i);
    }
    while (ptr < end)
    {
      size = ((end - ptr) > pattern_size)?pattern_size:(end - ptr);
      result_code=ddi_memcmp(ptr, &mem_pattern[0], size);
      if(result_code !=0)
      {
        ret |= DDI_CMD_FAIL;
        read_value = *(uint64 *)result_code;
        if (ddi_cmp_set_failure(cmp_params, (uint64 *)result_code, *(pattern +((uint64 *)result_code-ptr)), read_value))
        {
          return ret;
        }
      }
#if DDI_PRINT_ENABLE
      if(log==1)
        address_printer_r((uint64)ptr);
#endif		  
      ptr += size;
    }
  }

  return ret;
}

/* ============================================================================
**  Function : ddr_setrand
** ============================================================================
*/
/*!
*   @brief
*   set data region with random data
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_setrand(uint64* start, uint64* end, uint8 log)
{
  uint64 *ptr = start;
  uint64 i;

  while (ptr < end)
  {

    for (i = 0; i < MAX_TEST_PATTERN_SIZE; i++) 
    {
      mem_pattern[i] = swsys_rand_uefi_64();
    }

    ddi_memcpy256(ptr, mem_pattern,MAX_TEST_PATTERN_SIZE);
#if DDI_PRINT_ENABLE
    if(log==1)
      address_printer_w((uint64)ptr);
#endif		
    ptr += MAX_TEST_PATTERN_SIZE;
  }

  return DDI_CMD_COMPLETE;
}

/* ============================================================================
**  Function : ddr_setrandstride
** ============================================================================
*/
/*!
*   @brief
*   set data region with random data
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param rand_stride -   [IN] random data stride length
*   @param rand_seed   -   [IN] random data seed
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_setrandstride(uint64* start, uint64* end, uint64 rand_stride, uint64 random_seed, uint8 log)
{
  uint64 *ptr = start;
  uint64 i, rand_idx=0;
    // set the first rand_stride bytes to random data,
  while (ptr < end)
  {
    // then use it as a pattern for the rest of the buffer
    for (i = 0; i < MAX_TEST_PATTERN_SIZE; i++,rand_idx++)
    {
      mem_pattern[i] = swsys_rand_uefi_64();
      if(rand_idx >=rand_stride)
      {
        swsys_srand_uefi(random_seed);
        rand_idx=0;
      }
    }

    ddi_memcpy256(ptr, mem_pattern, MAX_TEST_PATTERN_SIZE);
#if DDI_PRINT_ENABLE
    if(log==1)
      address_printer_w((uint64)ptr);
#endif	
    ptr += MAX_TEST_PATTERN_SIZE;
  }

  return DDI_CMD_COMPLETE;
}


/* ============================================================================
**  Function : ddr_cmprand
** ============================================================================
*/
/*!
*   @brief
*   set data region with random data
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*   random seed must be set to original as when setrand was first called
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_cmprand(uint64* start, uint64* end, ddi_cmp_params* cmp_params, uint8 log)
{
  ddi_error ret = DDI_CMD_NOT_COMPLETE;
  uint64 *ptr = start;
  uint64 i;
  uint64 read_value;
  uint64 result_code;
    // in this case, we should regenerate the random data for
  while (ptr < end)
  {
    // the first stride, then do a standard pattern compare
    for (i = 0; i < MAX_TEST_PATTERN_SIZE; i++)
    {
      mem_pattern[i] = swsys_rand_uefi_64();
    }
    // against it. This should avoid subsequent strides from
    result_code=ddi_memcmp(ptr, mem_pattern, MAX_TEST_PATTERN_SIZE);
    if(result_code !=0)
    {
      ret |= DDI_CMD_FAIL;
      read_value = *(uint64 *)result_code;
      if (ddi_cmp_set_failure(cmp_params, (uint64 *)result_code, mem_pattern[(uint64 *)result_code-ptr], read_value))
      {
        return ret;
      }
    }
#if DDI_PRINT_ENABLE
    if(log==1)
      address_printer_r((uint64)ptr);
#endif	
    ptr += MAX_TEST_PATTERN_SIZE;
  }

  return ret;
}

    // reporting corruptions if the first stride has a corruption.
/* ============================================================================
**  Function : ddr_cmprandstride
** ============================================================================
*/
/*!
*   @brief
*   set data region with random data
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param rand_stride -   [IN] random data stride length
*   @param rand_seed   -   [IN] random data seed
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*   random seed must be set to original as when setrand was first called
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_cmprandstride(uint64* start, uint64* end, uint64 rand_stride, uint64 random_seed, ddi_cmp_params* cmp_params, uint8 log)
{
  ddi_error ret = DDI_CMD_NOT_COMPLETE;
  uint64 *ptr = start;
  uint64 i,rand_idx=0;
  uint64 read_value;
  uint64 result_code;

  while (ptr < end)
  {

    for (i = 0; i < MAX_TEST_PATTERN_SIZE; i++,rand_idx++)
    {
      mem_pattern[i] = swsys_rand_uefi_64();
      if(rand_idx >=rand_stride)
      {
        swsys_srand_uefi(random_seed);
        rand_idx=0;
      }
    }

    result_code=ddi_memcmp(ptr, mem_pattern, MAX_TEST_PATTERN_SIZE);
    if(result_code !=0)
    {
      ret |= DDI_CMD_FAIL;
      read_value = *(uint64 *)result_code;
      if (ddi_cmp_set_failure(cmp_params, (uint64 *)result_code, mem_pattern[(uint64 *)result_code-ptr], read_value))
      {
        return ret;
      }
    }
#if DDI_PRINT_ENABLE
    if(log==1)
      address_printer_r((uint64)ptr);
#endif
    ptr += MAX_TEST_PATTERN_SIZE;
  }

  return ret;
}

/* ============================================================================
**  Function : ddr_setvalue
** ============================================================================
*/
/*!
*   @brief
*   sets a value to a data region
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param value       -   [IN] value to set
*   @param invert_row  -   [IN] option to invert the data on every DRAM row
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_setvalue(uint64* start, uint64* end, uint64 value, boolean invert_row, uint8 log)
{

  uint64 *ptr = start;
  uint64 size;
  uint64 flip=0;

  size = ((uint64)start & (MEMREAD_SIZE-1))/sizeof(uint64);
  ddi_memset512(ptr, value, size);
  ptr -= size;

  while (ptr < end)
  {
    size = ((end - ptr) > MEMREAD_SIZE/sizeof(uint64))?(MEMREAD_SIZE/sizeof(uint64)):(end - ptr);

    if(invert_row && flip)
    {
      ddi_memset512(ptr, ~value, size);
    }
    else
    {
      ddi_memset512(ptr, value, size);
    }
#if DDI_PRINT_ENABLE
    if(log==1)
      address_printer_w((uint64)ptr);
#endif		
    flip=1-flip;
    ptr += size;
  }

  return DDI_CMD_COMPLETE;
}

/* ============================================================================
**  Function : ddr_cmpvalue
** ============================================================================
*/
/*!
*   @brief
*   compares a value with a data region
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param value       -   [IN] value to set
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param invert_row  -   [IN] option to invert the data on every DRAM row
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_cmpvalue(uint64* start, uint64* end, uint64 value, ddi_cmp_params* cmp_params, boolean invert_row, uint8 log)
{
  ddi_error ret = DDI_CMD_NOT_COMPLETE;
  uint64 *ptr = start;
  uint64 size;
  uint64 cmp_value,read_value;
  uint64 flip=0;
  uint64 result_code;

  while (ptr < end)
  {
    size = ((end - ptr) > MEMREAD_SIZE/sizeof(uint64))?(MEMREAD_SIZE/sizeof(uint64)):(end - ptr);

    if(invert_row && flip)
    {
      cmp_value= ~value;
    }
    else
    {
      cmp_value= value;
    }

    result_code=ddi_memcmptoval(ptr, cmp_value, size);
    if(result_code !=0)
    {
      ret |= DDI_CMD_FAIL;
      read_value = *(uint64 *)result_code;
      if (ddi_cmp_set_failure(cmp_params, (uint64 *)result_code, cmp_value, read_value))
      {
        return ret;
      }
      ptr=(uint64 *)(result_code+sizeof(uint64));
    }
    else
    {
#if DDI_PRINT_ENABLE
      if(log==1)
        address_printer_r((uint64)ptr);
#endif	
      ptr += size;
    }
    flip=1-flip;
  }

  return ret;
}

/* ============================================================================
**  Function : ddr_op_value
** ============================================================================
*/
/*!
*   @brief
*   data operations when setting or comparing a value
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param value       -   [IN] value to set
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param invert_row  -   [IN] option to invert the data on every DRAM row
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_op_value(uint64* start, uint64* end, uint64 value, ddi_cmp_params* cmp_params, boolean invert_row, uint8 log)
{
  if (cmp_params) {
    return ddr_cmpvalue(start, end, value, cmp_params, invert_row, log);
  }
  else {
    return ddr_setvalue(start, end, value, invert_row, log);
  }
}

/* ============================================================================
**  Function : ddr_op_pattern
** ============================================================================
*/
/*!
*   @brief
*   data operations when setting or comparing a user defined pattern
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_op_pattern(uint64* start, uint64* end, uint64* pattern, uint64 pattern_size, ddi_cmp_params* cmp_params, uint8 log)
{
  if (cmp_params) {
    return ddr_cmppattern(start, end, pattern, pattern_size, cmp_params, log);
  }
  else {
    return ddr_setpattern(start, end, pattern, pattern_size, log);
  }
}

/* ============================================================================
**  Function : ddr_op_rand
** ============================================================================
*/
/*!
*   @brief
*   data operations when setting or comparing random data
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param rand_stride -   [IN] random data stride length
*   @param rand_seed   -   [IN] random data seed
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_op_rand(uint64* start, uint64* end, uint64 rand_stride, uint64 random_seed, ddi_cmp_params* cmp_params, uint8 log)
{
  if (cmp_params)
{
    if (rand_stride && (rand_stride < (end - start)))
    {
      return ddr_cmprandstride(start, end, rand_stride, random_seed, cmp_params, log);
    }
    else
    {
      return ddr_cmprand(start, end, cmp_params, log);
    }
  }
  else
  {
    if (rand_stride && (rand_stride < (end - start)))
    {
      return ddr_setrandstride(start, end, rand_stride, random_seed, log);
    }
    else
    {
      return ddr_setrand(start, end, log);
  }
  }
}

/* ============================================================================
**  Function : ddr_op_read
** ============================================================================
*/
/*!
*   @brief
*   data operations when generating read traffic
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/

ddi_error ddr_op_read(uint64* start, uint64* end, uint8 log)
{
  uint64 val = 0;
  uint64 size = end - start;
  uint64 *ptr = start;

  size = (uint64)start & (MEMREAD_SIZE-1);
  ddi_memread256(&val, (uint64 *)ptr, size);
  ptr -= size;

  while (ptr < end)
  {
    size = ((end - ptr) > MEMREAD_SIZE/sizeof(uint64))?(MEMREAD_SIZE):((end - ptr)*sizeof(uint64));
    ddi_memread256(&val, ptr, size);

    #if DDI_PRINT_ENABLE
    if(log==1)
      address_printer_r((uint64)ptr);
    #endif
    ptr+=size/sizeof(uint64);
  }
  return DDI_CMD_COMPLETE;
}

/* ============================================================================
**  Function : ddr_mem_op
** ============================================================================
*/
/*!
*   @brief
*   entry point for data operations
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*   @param invert_row  -   [IN] flag to invert row or not
*   @param rand        -   [IN] flag to use random data or not
*   @param rand_stride -   [IN] random data stride length
*   @param rand_seed   -   [IN] random data seed
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param op_type     -   [IN] data operation type
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddr_mem_op(uint64* start, uint64* end, boolean invert_row, boolean rand, uint64 rand_stride, uint64 random_seed, uint64* pattern, uint64 pattern_size, ddi_mem_op_type op_type, ddi_cmp_params* cmp_params, uint8 log)
{

  //WatchDog_Pet();

  if (!rand && !pattern_size) {
    rand = TRUE;
  }
  if (op_type == DDI_MEM_OP_RD) {
    return ddr_op_read(start, end, log);
  }
  else if (rand) {
    return ddr_op_rand(start, end, rand_stride, random_seed, cmp_params, log);
  }
  else if (pattern_size == 1) {
    return ddr_op_value(start, end, *pattern, cmp_params, invert_row, log);
  }
  else {
    return ddr_op_pattern(start, end, pattern, pattern_size, cmp_params, log);
  }
}

/* ============================================================================
**  Function : ddr_mem_op
** ============================================================================
*/
/*!
*   @brief
*   entry point for data operations where blocked memory regions are avoided
*
*   @param invert_row  -   [IN] flag to invert row or not
*   @param rand        -   [IN] flag to use random data or not
*   @param rand_stride -   [IN] random data stride length
*   @param rand_seed   -   [IN] random data seed
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param op_type     -   [IN] data operation type
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_mem_op(boolean invert_row, boolean random, uint64 random_stride, uint64 random_seed, uint64* pattern, uint64 pattern_size, ddi_mem_op_type op_type, ddi_cmp_params* cmp_params, uint8 log)
{
  uint8 i;
  ddi_error err = DDI_CMD_NOT_COMPLETE;
  for (i = 0; i < num_ddr_test_region; i++)
  {
    err |= ddr_mem_op((uint64*)ddr_test_region[i].start, (uint64*)ddr_test_region[i].end, invert_row, random, random_stride, random_seed, pattern, pattern_size, op_type, cmp_params, log);
  }
  return err;
}

/* ============================================================================
**  Function : get_start_end
** ============================================================================
*/
/*!
*   @brief
*   filter the user input to set start and end based on mapped data region
*
*   @param start       -   [IN] starting address of data region
*   @param end         -   [IN] ending address of data region
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
#define RANK_IDX(r) ((r)==1?0:(((r)==2)?1:(((r)==4)?2:3)))
ddi_error get_start_end(uint64* start, uint64* end)
{
  uint64 reg_start,reg_end,next_reg_start;
  uint32 no_reg = ddr_driver_struct->ddr_regions_info.no_of_ddr_regions;
  uint8 idx_t=no_reg-1;
  uint8 idx_h=idx_t;
  uint8 i;

  if (*start > *end)
  {
    return DDI_CMD_INVALID_INPUT;
  }

  // set the boundaries to the ddr region
  if ((*start == 0)
    || (*start < ddr_driver_struct->ddr_regions_info.ddr_region[0].start_address))
  {
    *start = ddr_driver_struct->ddr_regions_info.ddr_region[0].start_address;
  }

  if ((*end == 0)
    ||(*end > ddr_driver_struct->ddr_regions_info.ddr_region[no_reg-1].start_address + ddr_driver_struct->ddr_regions_info.ddr_region[no_reg-1].size))
  {
    *end = ddr_driver_struct->ddr_regions_info.ddr_region[no_reg-1].start_address + ddr_driver_struct->ddr_regions_info.ddr_region[no_reg-1].size;
  }

  //Minimum Granularity of memtest 256bytes = 32 x 8 bytes
  *start = *start & ~(uint64)0xFF;
  *end = *end & ~(uint64)0xFF;

  //Fill in the memTest region
  for (i=0; i<no_reg-1; i++)
  {
    reg_start = ddr_driver_struct->ddr_regions_info.ddr_region[i].start_address;
    reg_end = ddr_driver_struct->ddr_regions_info.ddr_region[i].start_address + ddr_driver_struct->ddr_regions_info.ddr_region[i].size;
    next_reg_start = ddr_driver_struct->ddr_regions_info.ddr_region[i+1].start_address;

    if((*start >= reg_start) && (*start < reg_end))
    {
      idx_h=i;
    }

    if((*start < next_reg_start) && (*start >= reg_end))
    {
      *start = next_reg_start;
      idx_h=i+1;
    }

    if((*end > reg_start) && (*end <= reg_end))
    {
      idx_t=i;
    }

    if((*end <= next_reg_start) && (*end > reg_end))
    {
      *end = reg_end;
      idx_t=i;
    }
  }

  memset(ddr_test_region, 0, sizeof(struct ddr_test_region_t) * MAX_DDR_REGIONS);
//  boot_log_message(ddi_log_string);
  ddr_test_region[0].start = *start;
  num_ddr_test_region=idx_t-idx_h+1;

  for (i=0; i<num_ddr_test_region; i++)
  {
    ddr_test_region[i].end = ddr_driver_struct->ddr_regions_info.ddr_region[idx_h+i].start_address + ddr_driver_struct->ddr_regions_info.ddr_region[idx_h+i].size;
    ddr_test_region[i].rank= RANK_IDX(ddr_driver_struct->ddr_regions_info.ddr_region[idx_h+i].ddr_rank);
    ddr_test_region[i+1].start = ddr_driver_struct->ddr_regions_info.ddr_region[idx_h+i+1].start_address;
  }
//  #endif
  ddr_test_region[num_ddr_test_region-1].rank = RANK_IDX(ddr_driver_struct->ddr_regions_info.ddr_region[idx_t].ddr_rank);
  ddr_test_region[num_ddr_test_region-1].end = *end;

  return DDI_CMD_COMPLETE;
}

/* ============================================================================
**  Function : ddr_mem_set
** ============================================================================
*/
/*!
*   @brief
*   entry point for memory set data operations
*
*   @param invert_row  -   [IN] flag to invert row or not
*   @param rand        -   [IN] flag to use random data or not
*   @param rand_stride -   [IN] random data stride length
*   @param rand_seed   -   [IN] random data seed
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param op_type     -   [IN] data operation type
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_mem_set(boolean invert_row, boolean random, uint64 random_stride, uint64 random_seed, uint64* pattern, uint64 pattern_size, uint8 log)
{
  return ddi_mem_op(invert_row, random, random_stride, random_seed, pattern, pattern_size, DDI_MEM_OP_WR_CMP, NULL, log);
}

/* ============================================================================
**  Function : ddr_mem_cmp
** ============================================================================
*/
/*!
*   @brief
*   entry point for memory comp data operations
*
*   @param invert_row  -   [IN] flag to invert row or not
*   @param rand        -   [IN] flag to use random data or not
*   @param rand_stride -   [IN] random data stride length
*   @param rand_seed   -   [IN] random data seed
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param op_type     -   [IN] data operation type
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_mem_cmp(boolean invert_row, boolean random, uint64 random_stride, uint64 random_seed, uint64* pattern, uint64 pattern_size, ddi_cmp_params* cmp_params, uint8 log)
{
  return ddi_mem_op(invert_row, random, random_stride, random_seed, pattern, pattern_size, DDI_MEM_OP_WR_CMP, cmp_params, log);
}

/* ============================================================================
**  Function : ddr_mem_read
** ============================================================================
*/
/*!
*   @brief
*   entry point for memory read data operations
*
*   @param invert_row  -   [IN] flag to invert row or not
*   @param rand        -   [IN] flag to use random data or not
*   @param rand_stride -   [IN] random data stride length
*   @param pattern     -   [IN] pointer to pattern array
*   @param pattern_size-   [IN] size of pattern array
*   @param op_type     -   [IN] data operation type
*   @param cmp_params  -   [IN] pointer to data comparison parameters
*   @param log         -   [IN] log mask
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_mem_read(boolean random, uint64 random_stride, uint64* pattern, uint64 pattern_size, uint8 log)
{
  return ddi_mem_op(FALSE, random, random_stride, 0, pattern, pattern_size, DDI_MEM_OP_RD, NULL, log);
}


/* ============================================================================
**  Function : ddi_add_fail_summary
** ============================================================================
*/
/*!
*   @brief
*   This function is called to log a failure to the test case fail summary
*
*   @param fail_summary-   [IN] pointer to test case failure summary
*   @param addr        -   [IN] failing address
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void ddi_add_fail_summary (ddi_fail_summary* fail_summary, uint64* addr)
{
  uint32 instance;
  fail_summary->total_fail_count++;
  instance = ddi_get_rank(addr);
  if (instance < fail_summary->num_ranks) {
    fail_summary->rank[instance]++;
  }
  instance = ddi_get_channel(addr);
  if (instance < fail_summary->num_channels) {
    fail_summary->channel[instance]++;
  }
}

/* ============================================================================
**  Function : ddi_handle_fail_rdwr
** ============================================================================
*/
/*!
*   @brief
*   This function is called to log a read/write failure to the flash
*
*   @details
*   This will log a DRAM retention test case failure to the flash
*
*   @param fail_params -   [IN] pointer to test case failure summary
*   @param addr        -   [IN] failing address
*   @param expected    -   [IN] expected data
*   @param read        -   [IN] read data
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval boolean
*
*   @sa None
*/
boolean ddi_handle_fail_rdwr(ddi_handle_fail_params* fail_params, uint64* addr, uint64 expected, uint64 read, uint64* output_iter)
{
  ddi_fail_summary* fail_summary = fail_params->fail_summary;
  uint32 max_fails = fail_params->max_fails;
  ddi_add_fail_summary(fail_summary, addr);
  uint64 fail_count = fail_summary->total_fail_count;
  boolean status;

  #if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), " !error:addr=0x%010lx ref=0x%016lx data=0x%016lx xor=0x%016lx",
     (uint64)addr, (uint64)expected, (uint64)read, (uint64)(expected^read));
  boot_log_message(ddi_log_string);
  #endif

  if (fail_count > max_fails)
  {
    return TRUE;
  }
  
  fail_summary->num_fail_records++;
  ddi_fail_addr fail_addr;
  fail_addr.fail_addr = (uint64)addr;
  fail_addr.expected_data = expected;
  fail_addr.read_data = read;
  status=save_ddi_data2ddr_partition((uint8 *)&fail_addr, sizeof(ddi_fail_addr), *output_iter);
  if(status)
    *output_iter += sizeof(ddi_fail_addr);

  return FALSE;
}


/* ============================================================================
**  Function : ddi_delay
** ============================================================================
*/
/*!
*   @brief
*   API for setting delay values small or large values
*
*   @param delay_us    -   [IN] delay time
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
void ddi_delay(uint64 delay_us)
{
  uint64 i;
  uint64 timer_loop_us = 1000000;
  uint64 timer_loop_max = delay_us / timer_loop_us;
  for (i = 0; i < timer_loop_max; i++) {
    seq_wait(timer_loop_us, US);
  }
  seq_wait(delay_us % timer_loop_us, US);
}


/* ============================================================================
**  Function : ddi_fill_device_info
** ============================================================================
*/
/*!
*   @brief
*   API for filling in device information from ddr shared structure
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_device_info
*
*   @sa None
*/

void ddi_fill_device_info(  ddi_device_info* dev_info)
{
  uint8 i;

  dev_info->chip_id = ddr_shared_data->platform_id;
  dev_info->chip_sn = ddr_shared_data->serial_num;
  dev_info->dsf_version = ddr_shared_data->dsf_code_version;
  dev_info->shrm_dsf_version = ddr_shared_data->shrm_code_version;
  dev_info->dram_manufacturer_id = ddr_shared_data->device_params.manufacturer_id;
  dev_info->dram_device_type = ddr_shared_data->device_params.device_type;

  dev_info->dram_rank0_MB = 0;
  dev_info->dram_rank1_MB = 0;
  for (i = 0; i < ddr_shared_data->num_channel; i++)
  {
    dev_info->dram_rank0_MB+= ddr_shared_data->ddr_size_info.ddr_cs0_mb[i];
    dev_info->dram_rank1_MB+= ddr_shared_data->ddr_size_info.ddr_cs1_mb[i];
  }
}

/* ============================================================================
**  Function : ddi_fill_mrinfo
** ============================================================================
*/
/*!
*   @brief
*   This function is helper to read MR data and return
*
*   @param record           -   [IN] buffer for MR data
*   @param channel          -   [IN] channel
*   @param rank             -   [IN] rank
*   @param address          -   [IN] MR address
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddi_read_mrinfo(ddi_mr_record* record, uint8 channel, uint8 rank, uint32 address)
{
  record->channel=channel;
  record->rank=rank;
  record->mraddr=address;	
  record->mrval= HAL_DDR_FW_MC_MR_Read(channel, rank, address);
}


boolean ddi_fill_mrinfo(ddi_mr_info* dev_mr_info)
{
	int i,j;
	int idx=0;
	uint32 mr_array[17]={5,6,7,8,12,14,15,47,48,49,50,51,52,53,54,55,56};

	for (j = 0; j < ddr_shared_data->num_channel; j++)
	{
	  for (i = 0; i < sizeof(mr_array)/sizeof(uint32); i++)
	  {
		ddi_read_mrinfo(&dev_mr_info->mr_data[idx++],j,0,mr_array[i]);
		if((ddr_shared_data->device_params.populated_chipselect&0x2) !=0)
		  ddi_read_mrinfo(&dev_mr_info->mr_data[idx++],j,1,mr_array[i]);
	  }
	}
	  
	dev_mr_info->no_record=idx;

	return save_mr_data2ddr_partition((uint8*)dev_mr_info, sizeof(ddi_mr_info), 0);
}


/* ============================================================================
**  Function : ddi_run_command_delay
** ============================================================================
*/
/*!
*   @brief
*   This function is called to run the delay DDI test case
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_run_command_delay(uint64 cmd_id, void* params, uint64* output_iter)
{
  ddi_delay_params* cparams = (ddi_delay_params*)params;
  uint64 header_offset = *output_iter;
  boolean status;

  boot_log_message("DDI: add delay");

  #if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), "delay_ms: %d", cparams->delay_ms);
  boot_log_message(ddi_log_string);
  #endif

  ddi_delay(cparams->delay_ms * 1000);

  ddi_output_header output_header;
  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type=  ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
  output_header.test_status = DDI_CMD_NOT_COMPLETE;

  return output_header.test_status;
}

/* ============================================================================
**  Function : ddi_run_command_rd
** ============================================================================
*/
/*!
*   @brief
*   This function is called to run the read DDI test case
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_run_command_rd(uint64 cmd_id, void* params, uint64* output_iter)
{
  ddi_output_header output_header;
  ddi_rd_params* cparams = (ddi_rd_params*)params;
  uint64* start = (uint64*)cparams->start_addr;
  uint64* end = (uint64*)cparams->end_addr;
  uint64 repeat_count = cparams->repeat_count;
  uint8 log_level= cparams->log_level;
  uint64 header_offset = *output_iter;
  boolean status;
  ddi_error ret=DDI_CMD_NOT_COMPLETE;

  boot_log_message("DDI: memory read command");

  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_NOT_COMPLETE;
  output_header.dram_type  = ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  do
  {

    if(repeat_count < 1)
      repeat_count =1;

    if(( get_start_end((uint64*)&start, (uint64*)&end) & DDI_CMD_COMPLETE) ==0)
    {
      output_header.test_status = DDI_CMD_INVALID_INPUT;
      break;
    }

    #if DDI_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "  test range: 0x%lx ~ 0x%lx", start, end);
    boot_log_message(ddi_log_string);
    snprintf(ddi_log_string, sizeof(ddi_log_string), "repeat_count: %lld", repeat_count);
    boot_log_message(ddi_log_string);
    #endif

    for (uint64 i = 0; i < repeat_count; i++)
    {
      #if DDI_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), " Start Read Test #%d", i+1);
      boot_log_message(ddi_log_string);
      #endif
      ret |= ddi_mem_read(FALSE, 0, NULL, 0, log_level);
    }
	
    if(ret ==DDI_CMD_COMPLETE)
      output_header.test_status = DDI_CMD_COMPLETE;
    else
      output_header.test_status = DDI_CMD_FAIL;
	  
  }while(0);

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(!status)
    output_header.test_status = DDI_CMD_NOT_COMPLETE;

#if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), "** %s **", TEST_REPORT_STRING(output_header.test_status ));
  boot_log_message(ddi_log_string);
#endif

  return output_header.test_status;
}

/* ============================================================================
**  Function : ddi_run_command_wr
** ============================================================================
*/
/*!
*   @brief
*   This function is called to run the write DDI test case
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_run_command_wr(uint64 cmd_id, void* params, uint64* output_iter)
{
  ddi_output_header output_header;
  ddi_wr_params* cparams = (ddi_wr_params*)params;
  uint64 header_offset = *output_iter;
  uint64* start = (uint64*)cparams->start_addr;
  uint64* end = (uint64*)cparams->end_addr;
  uint64 repeat_count = cparams->repeat_count;
  uint32 random_seed = cparams->random_seed;
  uint64 random_stride = cparams->random_stride;
  uint64 pattern_size = cparams->pattern_size;
  uint64* pattern = NULL;
  uint8 invert_row = (cparams->flags & DDI_WR_FLAGS_MASK_INVERT_ROW) > DDI_WR_FLAGS_SHIFT_INVERT_ROW;
  uint8 random = (cparams->flags & DDI_WR_FLAGS_MASK_RANDOM) > DDI_WR_FLAGS_SHIFT_RANDOM;
  uint8 log_level= cparams->log_level;
  boolean status;
  ddi_error ret=DDI_CMD_NOT_COMPLETE;

  boot_log_message("DDI: ddr write command");

  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_NOT_COMPLETE;
  output_header.dram_type =  ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  do
  {
    pattern = (uint64*)((uint8*)cparams + sizeof(ddi_wr_params));

    // Set minimum repeat count as 1
    if(repeat_count < 1)
      repeat_count =1;

    if(( get_start_end((uint64*)&start, (uint64*)&end) & DDI_CMD_COMPLETE) ==0)
    {
      output_header.test_status = DDI_CMD_INVALID_INPUT;
      break;
    }

    if(pattern_size>(MAX_TEST_PATTERN_SIZE*2))
    {
      output_header.test_status = DDI_CMD_INVALID_INPUT;
      break;
    }

    #if DDI_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "  test range: 0x%lx ~ 0x%lx", start, end);
    boot_log_message(ddi_log_string);
    #endif

    if (random)
    {
      invert_row = FALSE;
      if (!random_seed)
      {
      // TODO: get a dynamic random seed, using timestamp?
        random_seed = swsys_rand_uefi_64();
      }
      swsys_srand_uefi(random_seed);

      #if DDI_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "  random_stride: %d, random_seed: 0x%08x", random_stride,random_seed);
      boot_log_message(ddi_log_string);
      #endif
    }
    else
    {
      #if DDI_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "  pattern_size: %d", pattern_size);
      boot_log_message(ddi_log_string);

      for (uint64 i=0;i<pattern_size;i++)
      {
        snprintf(ddi_log_string, sizeof(ddi_log_string), "  pattern: 0x%016llx", (uint64)pattern[i]);
        boot_log_message(ddi_log_string);
      }
      #endif

    if (pattern_size != 1)
      invert_row = FALSE;
    }

    #if DDI_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "  repeat: %lld  invert: %d", repeat_count, invert_row);
    boot_log_message(ddi_log_string);
    #endif

    for (uint64 i = 0; i < repeat_count; i++)
	{
      #if DDI_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), " Start Write Test #%d", i+1);
      boot_log_message(ddi_log_string);
      #endif
      ret |= ddi_mem_set(invert_row, random, random_stride, random_seed, pattern, pattern_size,log_level);
    }

    if(ret ==DDI_CMD_COMPLETE)
      output_header.test_status = DDI_CMD_COMPLETE;
    else
      output_header.test_status = DDI_CMD_FAIL;

  }while(0);

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(!status)
    output_header.test_status = DDI_CMD_NOT_COMPLETE;

  #if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), "** %s **", TEST_REPORT_STRING(output_header.test_status ));
  boot_log_message(ddi_log_string);
  #endif

  return output_header.test_status;
}


/* ============================================================================
**  Function : ddi_run_command_rdwr
** ============================================================================
*/
/*!
*   @brief
*   This function is called to run the read/write DDI test case
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_run_command_rdwr(uint64 cmd_id, void* params, uint64* output_iter)
{
  ddi_output_header output_header;
  ddi_rdwr_params* cparams = (ddi_rdwr_params*)params;
  ddi_rdwr_output rdwr_output;
  uint64 header_offset = *output_iter;
  uint64* start = (uint64*)cparams->start_addr;
  uint64* end = (uint64*)cparams->end_addr;
  uint64 repeat_count = cparams->repeat_count;
  uint32 random_seed = cparams->random_seed;
  uint64 random_stride = cparams->random_stride;
  uint64 pattern_size = cparams->pattern_size;
  uint64* pattern = NULL;
  uint8 random = (cparams->flags & DDI_RDWR_FLAGS_MASK_RANDOM) >> DDI_RDWR_FLAGS_SHIFT_RANDOM;
  uint8 verify = (cparams->flags & DDI_RDWR_FLAGS_MASK_VERIFY) >> DDI_RDWR_FLAGS_SHIFT_VERIFY;
  uint8 invert_row = (cparams->flags & DDI_RDWR_FLAGS_MASK_INVERT_ROW) >> DDI_RDWR_FLAGS_SHIFT_INVERT_ROW;
  uint8 cache = (cparams->flags & DDI_RDWR_FLAGS_MASK_CACHEABLE) >> DDI_RDWR_FLAGS_SHIFT_CACHEABLE;
  uint8 log_level= cparams->log_level;

  boolean status;
  ddi_error ret=DDI_CMD_NOT_COMPLETE;

  boot_log_message("DDI: Memory Test command");

  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_NOT_COMPLETE;
  output_header.dram_type =  ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header)+ sizeof(ddi_rdwr_output);

  ddi_mr_info dev_mr_info;
  ddi_fill_mrinfo(&dev_mr_info);

  memset(&rdwr_output, 0, sizeof(ddi_rdwr_output));

  do
  {
     //blocking Memory test at higher than 3.2GHz DDR clockTest for data corruption issue
    if(ddr_external_get_clk_speed()>3200000)
    {
      output_header.test_status = DDI_CMD_INVALID_INPUT;
      break;
    }

    pattern = (uint64*)((uint8*)cparams + sizeof(ddi_rdwr_params));

    // Set minimum repeat count as 1
    if(repeat_count < 1)
      repeat_count =1;

    if(( get_start_end((uint64*)&start, (uint64*)&end) & DDI_CMD_COMPLETE) ==0)
    {
      output_header.test_status = DDI_CMD_INVALID_INPUT;
      break;
    }

    if(pattern_size>(MAX_TEST_PATTERN_SIZE*2))
    {
      output_header.test_status = DDI_CMD_INVALID_INPUT;
      break;
    }

    #if DDI_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "  test range: 0x%lx ~ 0x%lx", start, end);
    boot_log_message(ddi_log_string);
    #endif

    if (random)
    {
      invert_row = FALSE;
      if (!random_seed)
      {
        // TODO: get a dynamic random seed, using timestamp?
        random_seed = swsys_rand_uefi_64();
      }
      #if DDI_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "  random_stride: %d  random_seed: 0x%08x", random_stride, random_seed);
      boot_log_message(ddi_log_string);
      #endif
    }
    else
    {
      #if DDI_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "  pattern_size: %d", pattern_size);
      boot_log_message(ddi_log_string);
      for (uint64 i=0;i<pattern_size;i++)
      {
        snprintf(ddi_log_string, sizeof(ddi_log_string), "  pattern: 0x%016llx", (uint64)pattern[i]);
        boot_log_message(ddi_log_string);
      }
  #endif

      if (pattern_size != 1)
        invert_row = FALSE;
    }

    #if DDI_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "  repeat: %lld  verify: %d  invert: %d  cache: %d", repeat_count, verify, invert_row, cache);
    boot_log_message(ddi_log_string);
    #endif

      // TODO: get a dynamic random seed, using timestamp?
    rdwr_output.fail_summary.num_ranks = (ddr_shared_data->enabled_chipselects&0x1) + ((ddr_shared_data->enabled_chipselects>>1)&0x1);
    rdwr_output.fail_summary.num_channels = ddr_shared_data->num_channel;

    if(cache==1)
    {
      for (uint64 i=0; i<ddr_driver_struct->ddr_regions_info.no_of_ddr_regions; i++)
      {
        ArmSetMemoryAttributes(ddr_driver_struct->ddr_regions_info.ddr_region[i].start_address, ddr_driver_struct->ddr_regions_info.ddr_region[i].size,EFI_ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK);
      }
    }

    for (uint64 i = 0; i < repeat_count; i++)
    {
      #if DDI_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), " Start Write test #%d",i+1);
      boot_log_message(ddi_log_string);
      #endif

      swsys_srand_uefi(random_seed);
      ret |= ddi_mem_set(invert_row, random, random_stride, random_seed, pattern, pattern_size,log_level);
      if(cache==1)
      {
        if (ArmDataCacheEnabled())
          ArmCleanInvalidateDataCache ();
        else
          ArmInvalidateDataCache ();
        ArmInstructionSynchronizationBarrier();
      }

      if (verify)
      {
        #if DDI_PRINT_ENABLE
        snprintf(ddi_log_string, sizeof(ddi_log_string), " Start Verify #%d",i+1);
        boot_log_message(ddi_log_string);
        #endif

        // set the rdwr_output header
        ddi_handle_fail_params fail_params;
        fail_params.fail_summary = &rdwr_output.fail_summary;
        fail_params.max_fails = (ddi_get_DDIpartition_size()-(*output_iter))/sizeof(ddi_fail_addr);

        ddi_cmp_params cmp_params;
        cmp_params.handle_fail = ddi_handle_fail_rdwr;
        cmp_params.handle_fail_params = &fail_params;
        cmp_params.output_iter = output_iter;

        swsys_srand_uefi(random_seed);
        ret |= ddi_mem_cmp(invert_row, random, random_stride, random_seed, pattern, pattern_size, &cmp_params,log_level);
      }
      else
      {
        ret |= ddi_mem_read(random, random_stride, pattern, pattern_size,log_level);
      }

      random_seed = swsys_rand_uefi_64();
    }

    if(ret ==DDI_CMD_COMPLETE)
      output_header.test_status = DDI_CMD_COMPLETE;
    else
      output_header.test_status = DDI_CMD_FAIL;
  }while(0);

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status)
  {
    status=save_ddi_data2ddr_partition((uint8*)&rdwr_output, sizeof(ddi_rdwr_output), header_offset + sizeof(ddi_output_header));
  }

  if(!status)
    output_header.test_status = DDI_CMD_NOT_COMPLETE;

  #if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), "total_fail_count: %d", rdwr_output.fail_summary.total_fail_count);
  boot_log_message(ddi_log_string);
  snprintf(ddi_log_string, sizeof(ddi_log_string), "** %s **", TEST_REPORT_STRING(output_header.test_status));
  boot_log_message(ddi_log_string);
  #endif

  return output_header.test_status;
}

/* ============================================================================
**  Function : ddi_run_command_freq
** ============================================================================
*/
/*!
*   @brief
*   This function is called to run the frequency switch DDI test case
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_run_command_freq(uint64 cmd_id, void* params, uint64* output_iter)
{
  ddi_freq_params* cparams = (ddi_freq_params*)params;
  uint64 header_offset = *output_iter;
  int8 freq_plan_index;
  boolean status;

  boot_log_message("DDI: DDR frequency switch");

  ddi_output_header output_header;
  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type=  ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  #if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), "freq: %d", cparams->freq_khz);
  boot_log_message(ddi_log_string);
  #endif

  do
  {

    freq_plan_index = ddi_get_frequency_plan_index(cparams->freq_khz);

    if(freq_plan_index ==-1)
    {
      output_header.test_status = DDI_CMD_FAIL;
      break;
    }
    ddr_external_set_clk_speed((uint8)freq_plan_index);

  }while(0);

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
    output_header.test_status = DDI_CMD_NOT_COMPLETE;

  return output_header.test_status;
}

/* ============================================================================
**  Function : ddi_run_command_plot
** ============================================================================
*/
/*!
*   @brief
*   This function is called to run the Eye Plot DDI test case
*
*   @details
*   This will call into DSF to plot the CDC vs Vref data eyes.
*   A data eye will be generated for every bit per enabled rank/channel/byte
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_run_command_plot(uint64 cmd_id, void* params, uint64* output_iter)
{
  int8 freq_plan_index;
  ddi_device_info dev_info;
  ddi_plot_params* cparams = (ddi_plot_params*)params;
  boolean status=TRUE;
  uint64 header_offset = *output_iter;

  boot_log_message("DDI: running plot command");

  #if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), "type: %s, freq: %d", cparams->type?"WRITE":"READ", cparams->freq_khz);
  boot_log_message(ddi_log_string);
  snprintf(ddi_log_string, sizeof(ddi_log_string), "x_step: %d, y_step: %d", cparams->x_step, cparams->y_step);
  boot_log_message(ddi_log_string);
  #endif

  ddi_output_header output_header;
  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type = ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header) +sizeof(ddi_device_info);

  do
  {

    freq_plan_index = ddi_get_frequency_plan_index(cparams->freq_khz);
    if ((freq_plan_index < 0) || (ddr_driver_struct->aop_params->mc_states[freq_plan_index].freq_enable != 1))
    {
      #if DDI_PRINT_ENABLE
      boot_log_message("DDI: invalid frequency option\r\n");
      #endif
      output_header.test_status = DDI_CMD_INVALID_INPUT;
      break;
    }

    if (cparams->type == DDI_PLOT_WR)
      status = HAL_DDR_FW_XY_Plot_WR(freq_plan_index, (uint32*)output_iter, cparams->x_step, cparams->y_step);
    else if (cparams->type == DDI_PLOT_RD)
      status = HAL_DDR_FW_XY_Plot_RD(freq_plan_index, (uint32*)output_iter, cparams->x_step, cparams->y_step);
    else if (cparams->type == DDI_PLOT_CA)
      status = HAL_DDR_FW_XY_Plot_CA(freq_plan_index, (uint32*)output_iter, cparams->x_step, cparams->y_step);
    else
      output_header.test_status = DDI_CMD_INVALID_INPUT;

    if (status != TRUE)
      output_header.test_status = DDI_CMD_FAIL;

  } while(0);

  status = save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
     output_header.test_status = DDI_CMD_NOT_COMPLETE;

  ddi_fill_device_info(&dev_info);
  status = save_ddi_data2ddr_partition((uint8*)&dev_info, sizeof(ddi_device_info), header_offset+sizeof(ddi_output_header));
  if(status != TRUE)
    output_header.test_status = DDI_CMD_NOT_COMPLETE;

  #if DDI_PRINT_ENABLE
  snprintf(ddi_log_string, sizeof(ddi_log_string), "** %s **", TEST_REPORT_STRING(output_header.test_status));
  boot_log_message(ddi_log_string);
  #endif

  return output_header.test_status;
}


#define ECDT_VOLTAGE_RAIL_LIMIT 8
uint8 ddi_voltage_lvl_to_idx(uint32 rail)
{
  uint8 i =0;
  // Voltage Plan Parameter Rail Index Content see eCDT User Guide 2.1 pg 18
  uint32 voltage_rail[ECDT_VOLTAGE_RAIL_LIMIT]={MIN_SVS,
                                           LOW_SVS,
                                           SVS,
                                           SVS_L1,
                                           NOMINAL,
                                           TURBO,
                                           TURBO_L1,
                                           LOW_SVS_P1,
                                           };
  for(i=0;i<ECDT_VOLTAGE_RAIL_LIMIT;i++)
  {
    if(rail == voltage_rail[i])
    {
      return i;
    }
  }
  return 0;
}


/* ============================================================================
**  Function : ddi_read_eCDT_parameters
** ============================================================================
*/
/*!
*   @brief
*   This function is called to read eCDT settingd from device
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_read_ecdt_parameters(uint64 cmd_id, void* params, uint64* output_iter)
{
  void* buffer = NULL;
  size_t buffer_size = 1024;
  ddi_out_interface_settings * ecdt_output;
  uint64 header_offset = *output_iter;
  int param_cnt;
  int8 freq_plan_index;
  uint8 number_of_freq;
  boolean status;
  uint32  voltage_over[20];

  ddi_output_header output_header;

  boot_log_message("DDI: read eCDT");

  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type = ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  do
  {

    buffer = ddi_malloc(buffer_size);
    if (buffer == NULL)
    {
      //failed to malloc
      output_header.test_status = DDI_CMD_NOT_COMPLETE;
      break;
    }

    ecdt_output = (ddi_out_interface_settings *)buffer;
    #ifdef DDI_DEBUG_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "buf 0x%X , &data 0x%X, data 0x%X, nfreq %d",
                          buffer, &(ecdt_output->settings_buf), ecdt_output->settings_buf,number_of_freq);
    boot_log_message(ddi_log_string);
     #endif //DDI_DEBUG_PRINT_ENABLE

    number_of_freq=0;
    *output_iter += sizeof(number_of_freq);

    for (freq_plan_index = 1;freq_plan_index < (sizeof(ddr_driver_struct->aop_params->mc_states)/sizeof(ddr_driver_struct->aop_params->mc_states[0])); freq_plan_index++)
    {
      if(ddr_driver_struct->aop_params->mc_states[freq_plan_index].freq_enable != 1)
      continue;

      ecdt_output->freq_khz = ddr_driver_struct->aop_params->mc_states[freq_plan_index].freq_khz;

      ecdt_output->vddcx = ddi_voltage_lvl_to_idx(ddr_driver_struct->aop_params->mc_states[freq_plan_index].vddcx);
      ecdt_output->vddmx = ddi_voltage_lvl_to_idx(ddr_driver_struct->aop_params->mc_states[freq_plan_index].vddmx);
      ecdt_output->vdda =  ddi_voltage_lvl_to_idx(ddr_driver_struct->aop_params->mc_states[freq_plan_index].vdda);
      ecdt_output->enable = ddr_driver_struct->aop_params->mc_states[freq_plan_index].freq_enable;

      #ifdef DDI_DEBUG_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "freq_idx %d, freq_khz %d", freq_plan_index, ecdt_output->freq_khz);
      boot_log_message(ddi_log_string);

      snprintf(ddi_log_string, sizeof(ddi_log_string), "en %d, vddcx %d, vddmx %d, vdda %d",
                                      ecdt_output->enable, ecdt_output->vddcx, ecdt_output->vddmx, ecdt_output->vdda);
      boot_log_message(ddi_log_string);
      #endif //DDI_DEBUG_PRINT_ENABLE


      param_cnt = DDR_FW_eCDT_Get_Voltage_Override_Values(freq_plan_index, (void*)&voltage_over[0], sizeof(voltage_over));

#ifdef DDI_DEBUG_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "read vol level %d bytes", param_cnt);
      boot_log_message(ddi_log_string);
#endif //DDI_DEBUG_PRINT_ENABLE

      if ( param_cnt< 0x20)
	  {
        output_header.test_status = DDI_CMD_NOT_COMPLETE;
        break;
      }
      for(int i=0;i<(uint8)param_cnt/sizeof(uint32);i+=2)
      {
        if(voltage_over[i]==0)
          ecdt_output->vddq_lvl =  voltage_over[i+1];
        else if(voltage_over[i]==1)
          ecdt_output->vdd2h_lvl =  voltage_over[i+1];
        else if(voltage_over[i]==2)
          ecdt_output->vdd2l_lvl =  voltage_over[i+1];
      }
      param_cnt = HAL_DDR_FW_eCDT_Get_Interface_Parameter_Values(freq_plan_index, (void*)&(ecdt_output->settings_buf), buffer_size-sizeof(ddi_out_interface_settings));

      #ifdef DDI_DEBUG_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "read setting %d bytes", param_cnt);
      boot_log_message(ddi_log_string);
      #endif //DDI_DEBUG_PRINT_ENABLE

      if ( (param_cnt< 0) || (param_cnt > buffer_size) )
	  {
        output_header.test_status = DDI_CMD_NOT_COMPLETE;
        break;
      }
      ecdt_output->number_settings = (uint8)param_cnt/(2*sizeof(uint32));
      #ifdef DDI_DEBUG_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "n settings %d ", ecdt_output->number_settings);
      boot_log_message(ddi_log_string);

      int i;
      uint32* temp = (uint32*)&(ecdt_output->settings_buf);
      for (i=0;i<(param_cnt/4);i+=2)
      {
        snprintf(ddi_log_string, sizeof(ddi_log_string), "setting %d = 0x%X ", *(temp+i), *(temp+i+1));
        boot_log_message(ddi_log_string);
      }
      #endif //DDI_DEBUG_PRINT_ENABLE
      number_of_freq++;

      status=save_ddi_data2ddr_partition((uint8*)buffer, sizeof(ddi_out_interface_settings)- sizeof(ecdt_output->settings_buf) + param_cnt, *output_iter);
      if(status)
        *output_iter += sizeof(ddi_out_interface_settings)- sizeof(ecdt_output->settings_buf) + param_cnt;
      else
      {
        output_header.test_status = DDI_CMD_NOT_COMPLETE;
        break;
      }
    }

  }while(0);

  if (buffer != NULL)
  {
    ddi_free(buffer);
    buffer = NULL;
  }

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  status=save_ddi_data2ddr_partition((uint8*)&number_of_freq, sizeof(number_of_freq), header_offset+ sizeof(ddi_output_header));
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  return output_header.test_status;
}


/* ============================================================================
**  Function : ddi_get_ac_timing
** ============================================================================
*/
/*!
*   @brief
*   This function is called to do get AC timing
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/

ddi_error ddi_get_ac_timing(uint64 cmd_id, void* params, uint64* output_iter)
{
  void* buffer = NULL;
  size_t buffer_size = 2048;
  ddi_out_ac_timing_w_clk * ac_w_clk_out;
  int param_cnt;
  int8 freq_plan_index;
  uint8 number_of_freq;
  boolean status;

  uint64 header_offset = *output_iter;
  ddi_output_header output_header;

  boot_log_message("DDI: read AC timing");

  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type = ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  do
  {
    buffer = ddi_malloc(buffer_size);
    if (buffer == NULL)
    {
      //failed to malloc
      output_header.test_status = DDI_CMD_NOT_COMPLETE;
      break;
    }

    ac_w_clk_out = (ddi_out_ac_timing_w_clk *)buffer;
    #ifdef DDI_DEBUG_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "buf 0x%X , &data 0x%X, data 0x%X, nfreq %d",
                          buffer, &(ac_w_clk_out->settings_buf), ac_w_clk_out->settings_buf,number_of_freq);
    boot_log_message(ddi_log_string);
    #endif //DDI_DEBUG_PRINT_ENABLE

    number_of_freq=0;
    *output_iter += sizeof(number_of_freq);

    for (freq_plan_index = 1;freq_plan_index < (sizeof(ddr_driver_struct->aop_params->mc_states)/sizeof(ddr_driver_struct->aop_params->mc_states[0])); freq_plan_index++)
    {
      if(ddr_driver_struct->aop_params->mc_states[freq_plan_index].freq_enable != 1)
        continue;

      ac_w_clk_out->freq_khz = ddr_driver_struct->aop_params->mc_states[freq_plan_index].freq_khz;
      ac_w_clk_out->enable = ddr_driver_struct->aop_params->mc_states[freq_plan_index].freq_enable;

      #ifdef DDI_DEBUG_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "freq_idx %d, freq_khz %d", freq_plan_index, ac_w_clk_out->freq_khz);
      boot_log_message(ddi_log_string);

      #endif //DDI_DEBUG_PRINT_ENABLE

      param_cnt = HAL_DDR_FW_eCDT_Get_AC_Timing_Values((void*)&(ac_w_clk_out->settings_buf), buffer_size-sizeof(ddi_out_ac_timing_w_clk));

      #ifdef DDI_DEBUG_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "read %d bytes", param_cnt);
      boot_log_message(ddi_log_string);
      #endif //DDI_DEBUG_PRINT_ENABLE

      if ( (param_cnt< 0) || (param_cnt > buffer_size) )
      {
        output_header.test_status = DDI_CMD_NOT_COMPLETE;
        break;
      }
      ac_w_clk_out->number_settings = (uint8)param_cnt/(2*sizeof(uint32));

      #ifdef DDI_DEBUG_PRINT_ENABLE
      snprintf(ddi_log_string, sizeof(ddi_log_string), "n settings %d ", ac_w_clk_out->number_settings);
      boot_log_message(ddi_log_string);

      int i;
      uint32* temp = (uint32*)&(ac_w_clk_out->settings_buf);
      for (i=0;i<(param_cnt/4);i+=2)
      {
        snprintf(ddi_log_string, sizeof(ddi_log_string), "setting %d = 0x%X ", *(temp+i), *(temp+i+1));
        boot_log_message(ddi_log_string);
      }
      #endif //DDI_DEBUG_PRINT_ENABLE
      number_of_freq++;

      status=save_ddi_data2ddr_partition((uint8*)buffer, sizeof(ddi_out_ac_timing_w_clk)- sizeof(ac_w_clk_out->settings_buf) + param_cnt, *output_iter);
      if(status)
        *output_iter += sizeof(ddi_out_ac_timing_w_clk)- sizeof(ac_w_clk_out->settings_buf) + param_cnt;
      else
      {
        output_header.test_status = DDI_CMD_NOT_COMPLETE;
        break;
      }
    }
  }while(0);

  if (buffer != NULL)
  {
    ddi_free(buffer);
    buffer = NULL;
  }

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  status=save_ddi_data2ddr_partition((uint8*)&number_of_freq, sizeof(number_of_freq), header_offset+ sizeof(ddi_output_header));
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  return output_header.test_status;
}


/* ============================================================================
**  Function : ddi_get_safe_mode_info
** ============================================================================
*/
/*!
*   @brief
*   This function is called to get safe mode enable setting
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_get_safe_mode_info(uint64 cmd_id, void* params, uint64* output_iter)
{

  void* buffer = NULL;
  size_t buffer_size = 1024;
  ddi_out_safe_mode* safe_mode_out = NULL;
  uint64 header_offset = *output_iter;
  int param_cnt = 0;
  boolean status;

  ddi_output_header output_header;

  boot_log_message("DDI: get safe mode setting");

  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type = ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  do{
    buffer = ddi_malloc(buffer_size);
    if (buffer == NULL)
    {
      //failed to malloc
      output_header.test_status = DDI_CMD_NOT_COMPLETE;
      break;
    }

    safe_mode_out = (ddi_out_safe_mode *)buffer;

    param_cnt = HAL_DDR_FW_eCDT_Get_Safe_Mode_Values((void*)&(safe_mode_out->settings_buf), buffer_size-sizeof(ddi_out_safe_mode));

    #ifdef DDI_DEBUG_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "read %d bytes", param_cnt);
    boot_log_message(ddi_log_string);
    #endif //DDI_DEBUG_PRINT_ENABLE

    if ( (param_cnt< 0) || (param_cnt > buffer_size) )
	{
      output_header.test_status = DDI_CMD_NOT_COMPLETE;
      break;
    }

    safe_mode_out->number_settings = (uint8)param_cnt/(2*sizeof(uint32));

    #ifdef DDI_DEBUG_PRINT_ENABLE
    snprintf(ddi_log_string, sizeof(ddi_log_string), "n settings %d ", safe_mode_out->number_settings);
    boot_log_message(ddi_log_string);

    int i;
    uint32* temp = (uint32*)&(ac_w_clk_out->settings_buf);
    for (i=0;i<(param_cnt/4);i+=2)
    {
      snprintf(ddi_log_string, sizeof(ddi_log_string), "setting %d = 0x%X ", *(temp+i), *(temp+i+1));
      boot_log_message(ddi_log_string);
    }
    #endif //DDI_DEBUG_PRINT_ENABLE

    status=save_ddi_data2ddr_partition((uint8*)safe_mode_out, sizeof(ddi_out_safe_mode)-sizeof((safe_mode_out->settings_buf))+param_cnt, *output_iter);
    if(status)
      *output_iter += sizeof(ddi_out_safe_mode)-sizeof(safe_mode_out->settings_buf)+param_cnt;
    else
    {
      output_header.test_status = DDI_CMD_NOT_COMPLETE;
      break;
    }
  }while(0);

  if (buffer != NULL)
  {
    ddi_free(buffer);
    buffer = NULL;
  }

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  return output_header.test_status;
}


/* ============================================================================
**  Function : ddi_get_device_info
** ============================================================================
*/
/*!
*   @brief
*   This function is called to get device information
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/
ddi_error ddi_get_device_info(uint64 cmd_id, void* params, uint64* output_iter)
{
  ddi_output_header output_header;
  uint64 header_offset = *output_iter;
  ddi_device_info dev_info;
  boolean status;

  boot_log_message("DDI: get device info");

  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type = ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);

  ddi_fill_device_info(&dev_info);
  status=save_ddi_data2ddr_partition((uint8*)&dev_info, sizeof(ddi_device_info), *output_iter);
  if(status)
    *output_iter += sizeof(ddi_device_info);
  else
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  return output_header.test_status;
}


/* ============================================================================
**  Function : ddi_run_dump_mr
** ============================================================================
*/
/*!
*   @brief
*   This function is called to store MR data to device
*   This will overwrite existing MR data on reserved DDR partition area
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_error
*
*   @sa None
*/

ddi_error ddi_read_mr(uint64 cmd_id, void* params, uint64* output_iter)
{
  ddi_output_header output_header;
  uint64 header_offset = *output_iter;
  boolean status;
  
  output_header.cmd_id = cmd_id;
  output_header.test_status = DDI_CMD_COMPLETE;
  output_header.dram_type = ddr_shared_data->device_params.device_type;
  *output_iter += sizeof(ddi_output_header);
  
  boot_log_message("DDI: dump and store MR data");

  ddi_mr_info dev_mr_info;
  status=ddi_fill_mrinfo(&dev_mr_info);
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  status=save_ddi_data2ddr_partition((uint8*)&output_header, sizeof(ddi_output_header), header_offset);
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  ddi_mr_offset ddi_mr_offset_v;
  ddi_mr_offset_v.mr_offset = ddi_get_MRpartition_offset();

  status=save_ddi_data2ddr_partition((uint8*)&ddi_mr_offset_v, sizeof(ddi_mr_offset), header_offset+sizeof(ddi_output_header));
  if(status != TRUE)
  {
    output_header.test_status = DDI_CMD_NOT_COMPLETE;
  }

  return output_header.test_status;  
}

/* ============================================================================
**  Function : ddi_run_command_empty
** ============================================================================
*/
/*!
*   @brief
*   This function is called to do nothing
*
*   @param cmd_id      -   [IN] ID of the command. Used for logging to flash.
*   @param params      -   [IN] pointer to test case parameters
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

ddi_error ddi_run_command_empty(uint64 cmd_id, void* params, uint64* output_iter)
{
  return DDI_CMD_INVALID_INPUT;
}


/* ============================================================================
**  Function : ddi_run_command_setparam
** ============================================================================
*/
/*!
*   @brief
*   This function is for set DDI parameter after DDR initialization
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddi_run_command_setparam(void)
{
  boot_log_message("DDI: Set parameter");

  if (ddi_setparam_pegfreq_func_ptr != NULL)
  {
    ddi_setparam_pegfreq_func_ptr();
  }
}


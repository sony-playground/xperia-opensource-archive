/*===========================================================================

JtagProgrammer_eeprom.c

 This is the Jtag programmer tool for EEPROM implementation.

 Copyright (c) 2020 Qualcomm Technologies, Incorporated.
 All Rights Reserved.
 Qualcomm Confidential and Proprietary

============================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



when         who     what, where, why
----------   ---     ----------------------------------------------------------
07/13/22     ds      heap init with reserved align carveout
2020-09-10   eo      Initial Release

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/ 

#include "JtagProgrammer.h"
#include "JtagProgrammerParam.h"

#ifdef JTAGPROGRAMMER_EEPROM_ENABLE

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "eeprom_api.h"
#include <Library/BaseMemoryLib.h>
#include "JtagProgrammerBsp.h"
#include "ClockBoot.h"
#include "DALSys.h"
#include "DALHeap.h"


/*===========================================================================

                           DEFINITIONS

===========================================================================*/
#define SIZE_64K 65536
#define SIZE_32K 32768
#define SIZE_16K 16384
#define SIZE_4K  4096
#define SIZE_Page 32 

#define EEPROM_JTAG_UNCACHED_HEAP_SIZE   (32 * 1024)

/* enum to indicate status of probe */
//static probe_code_type probe_status = MEM_DEVICE_NOT_PROBED;

/* EEPROM device structure */
eeprom_handle_t handle_eeprom;
eeprom_handle_t unit_test_handle;

struct eeprom_info dev_info;

/* NOR device parameters */
UINT32 page_size_bytes;    /* number of bytes in a page         */
UINT32 total_pages;        /* number of pages in the device     */
char device_name[32];
static uint32 dev_is_initialized = 0;

typedef struct
{
   UINT32 page_size_bytes;	  /* number of bytes in a page		   */
   UINT32 total_pages;		  /* number of pages in the EEPROM	   */
   char device_name[32];
} EEPROM_DEVICE_INFO;

static EEPROM_DEVICE_INFO eeprom_device_info;

#define SIZE_IN_PAGES(x) ( ((x % eeprom_device_info.page_size_bytes) == 0) ? x/eeprom_device_info.page_size_bytes : x/eeprom_device_info.page_size_bytes+1 )

UINT32 EEPROM_PAGE_SIZE __attribute__((used)) = SIZE_Page; 
UINT8 eeprom_jtag_uncached_heap[EEPROM_JTAG_UNCACHED_HEAP_SIZE];

 /*===========================================================================

                     MACRO DEFINITIONS FOR MODULE

===========================================================================*/


/*===========================================================================

                      FUNCTION PROTOTYPES

===========================================================================*/
UINT32 jsdcc_mem_read_eeprom(void);
UINT32 jsdcc_mem_write_eeprom(void);
UINT32 jsdcc_mem_erase_eeprom(void);
UINT32 jsdcc_mem_compute_crc_eeprom(void);
UINT32 jsdcc_mem_print_info_eeprom(void);
UINT32 jsdcc_mem_program_eeprom(void);
UINT32 jsdcc_mem_chip_erase_eeprom(void);
UINT32 jsdcc_mem_erase_bulk_eeprom(void);
UINT32 jsdcc_mem_unit_test_eeprom(void);

void eeprom_utils_strcpy(char* dest, const char *src, UINT32 len)
{
  if ((strlcat(dest,src,len))>= len)
  {
   outputMessage ("Device ID too long\n ");
  }
  dest[len-1] ='\0';
}

void eeprom_utils_deinit(void)
{
  if (dev_is_initialized )
  {
    eeprom_close(handle_eeprom);
    dev_is_initialized = FALSE;
  }
}

UINT32 eeprom_utils_init(void)
{
  INT32 result = EEPROM_DEVICE_DONE;

  if (dev_is_initialized)
  {
    return EEPROM_DEVICE_DONE;
  }
 
  /* Use equivalent function of DALSYS_HeapInit  */
  
  DALSYS_HeapInit(eeprom_jtag_uncached_heap, EEPROM_JTAG_UNCACHED_HEAP_SIZE, DALHEAP_ANY, 0 ,0);
  /* DALSYS_InitMod API needs heap to be setup before called */
  //DALSYS_InitMod(NULL);
 
  if(EEPROM_DEVICE_DONE != eeprom_open(EEPROM_DEVICE_ID_CDT, &handle_eeprom))                 
  {
    outputMessage("Error Opening EEPROM Device\n");
    return EEPROM_DEVICE_FAIL;
  }
  

  result = eeprom_get_info(handle_eeprom, &dev_info);
  if(EEPROM_DEVICE_DONE != result)
  {
    outputMessage("Get Info Error\n");
    result = EEPROM_DEVICE_FAIL;
    goto close_and_detach;
  }

  /* Get some information about the device */
  page_size_bytes = dev_info.page_size_bytes;

  eeprom_utils_strcpy(device_name, (const char *)dev_info.device_name, 
                      sizeof(device_name));

  eeprom_utils_strcpy(eeprom_device_info.device_name, (const char *)dev_info.device_name, 
                      sizeof(device_name));

  total_pages = dev_info.total_pages_in_device;

  eeprom_device_info.page_size_bytes = page_size_bytes;
  eeprom_device_info.total_pages = total_pages;

  dev_is_initialized = TRUE;

  return result;

close_and_detach:
   eeprom_close(handle_eeprom);
   return result;
}

UINT32 do_probe_eeprom(void)
{
  UINT32 ret_code;
  
  eeprom_init_dtb();

  ret_code = eeprom_utils_init();
  
  
  return ret_code;
}  /* do_probe */

/*===========================================================================

DESCRIPTION
  This function is a wrapper for the real memory read routine. It extracts
  the required parameters from TRACE32 and passes it onto the real thing.

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_read_eeprom(void)
{
  UINT32 page, data_length,byte_offset, byte_count;
  INT32 result = EEPROM_DEVICE_DONE;
  byte *pdata;

  pdata = jtag_prog_param.data;
  page = jtag_prog_param.addr;
  data_length = jtag_prog_param.data_length;

  /*convert pages to bytes */
  byte_offset = page * EEPROM_PAGE_SIZE;
  byte_count = data_length *EEPROM_PAGE_SIZE;
  
  outputMessage("Reading Sector 0x%x \n", jtag_prog_param.addr);
     
  result = eeprom_read(handle_eeprom,byte_offset, byte_count,pdata);
  
  if (EEPROM_DEVICE_DONE != result)
  {
    outputMessage("Failed with status %d\n", result);
    eeprom_utils_deinit();
    return STATUS_FAIL;
  }
  else
  {
      outputMessage("Success\n");
  }

  return STATUS_SUCCESS;
}  // jsdcc_mem_read


/*===========================================================================

DESCRIPTION
  This function is a wrapper for the real memory write routine. It extracts
  the required parameters from TRACE32 and passes it onto the real thing.

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_write_eeprom(void)
{
  UINT32 page, data_length,byte_offset, byte_count;
  byte *pdata;
  INT32 result = EEPROM_DEVICE_DONE;

  page = jtag_prog_param.addr;
  data_length = jtag_prog_param.data_length;

  /*convert pages to bytes */
  byte_offset = page * EEPROM_PAGE_SIZE;
  byte_count = data_length * EEPROM_PAGE_SIZE;
  
  outputMessage("Writing to sector 0x%x\n", jtag_prog_param.addr);
  
  pdata = jtag_prog_param.data;
  result = eeprom_write(handle_eeprom, byte_offset, byte_count,pdata);
  
  if (EEPROM_DEVICE_DONE != result)
  {
      outputMessage("Failed with status %d\n", result);
      eeprom_utils_deinit();
	  return STATUS_FAIL;
  }
  else
  {
    outputMessage("Success\n");
  }

  return STATUS_SUCCESS;
}  // jsdcc_mem_write



/*===========================================================================

DESCRIPTION
  This function erases specified number of sectors from the card

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/

UINT32 jsdcc_mem_erase_partition_eeprom(void)
{
   return STATUS_SUCCESS;
}


/*===========================================================================

DESCRIPTION
  This function is a wrapper for the real memory program routine. It extracts
  the required parameters from TRACE32 and passes it onto the real thing.  
  Program is very similar to write, except the length of the data is divided
  by BLOCK_SIZE.

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_program_eeprom(void)
{
  byte *pdata;
  INT32 result = EEPROM_DEVICE_DONE;
	UINT32 byte_offset,data_length;

  if(sector_writing) 
  {
    jtag_prog_param.addr = redirect_offset + SIZE_IN_PAGES(jtag_prog_param.addr);
    jtag_prog_param.data_length = jtag_prog_param.data_length < redirect_partition ? jtag_prog_param.data_length : redirect_partition;
    if (jtag_prog_param.data_length == 0) 
    {
      return STATUS_SUCCESS;
    }
    redirect_partition -= jtag_prog_param.data_length;
  }
  pdata = jtag_prog_param.data;
  byte_offset = jtag_prog_param.addr * EEPROM_PAGE_SIZE;
  data_length = jtag_prog_param.data_length;
	  
  result = eeprom_write(handle_eeprom,byte_offset,data_length,pdata);
   
  if (EEPROM_DEVICE_DONE != result)
  {
	  outputMessage("Mem Program Failed with status %d\n", result);
	  eeprom_utils_deinit();
	  return STATUS_FAIL;
  }

  return STATUS_SUCCESS;
}  // jsdcc_mem_program


/*===========================================================================

DESCRIPTION
  This function calls the mem_get_device_info API to get the information of 
  the memory device attached.

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_print_info_eeprom(void)
{
   
   outputMessage("Device Name = %s\n", eeprom_device_info.device_name);
   outputMessage("Page size  is %d \n", eeprom_device_info.page_size_bytes);
   outputMessage("Total Pages Avail is %d \n", eeprom_device_info.total_pages);
   
   return STATUS_SUCCESS;
}  /* jsdcc_mem_print_info */

/*===========================================================================

DESCRIPTION
  This function erases a specified sector from the card

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_erase_eeprom()
{
 return STATUS_SUCCESS;
}

/*===========================================================================

DESCRIPTION
  This function erases a specified sector from the card

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_erase_bulk_eeprom()
{
  return STATUS_SUCCESS;
}
/*===========================================================================

DESCRIPTION
  This function is for unit test of eeprom driver apis.

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/

UINT32 jsdcc_mem_unit_test_eeprom()
{
  INT32 result = EEPROM_DEVICE_DONE;
  UINT32 page, data_length;
  char Test_Write_Buffer[4096];
  char Test_Read_Buffer[4096];
  UINT16 i, j, k, flag;
  char  WriteTestChar = 0xAA;
  UINT32 rw_page, Block_count;
  
  flag =0;
  page = jtag_prog_param.addr * EEPROM_PAGE_SIZE;
  data_length = jtag_prog_param.data_length * EEPROM_PAGE_SIZE;

  result = eeprom_open(EEPROM_DEVICE_ID_CDT, &handle_eeprom);
  if(EEPROM_DEVICE_DONE != result)                 
  {
    outputMessage("Error Opening The Device For TestClient-1\n");
    flag =2;
    goto jsdcc_mem_unit_test_eeprom_end;
  }

  result = eeprom_open(EEPROM_DEVICE_ID_RF, &unit_test_handle);
  if(EEPROM_DEVICE_DONE != result)                 
  {
    outputMessage("Error Opening The Device For TestClient-1\n");
    flag = 3;
    goto jsdcc_mem_unit_test_eeprom_end;
  }

  outputMessage("Done with Flash open\n");

  for(i=0; i<data_length; i++)
  {
    Test_Write_Buffer[i]= WriteTestChar;
  }
  outputMessage("Buffer initialized 1\n");

  rw_page = page;
  Block_count = 1;

  for (i= 0; i < Block_count; i++)
  {
    result = eeprom_write(handle_eeprom, rw_page, data_length, &Test_Write_Buffer);
    if (EEPROM_DEVICE_DONE != result)
    {
      outputMessage("Write Flash Failed with status %d\n", result);
      flag = 7;
      goto jsdcc_mem_unit_test_eeprom_end;
    }
    else
    {
      //outputMessage("Write Successful for block %d\n",block_no+i);
    }
    memset(&Test_Read_Buffer, 0, sizeof(Test_Read_Buffer));

    result = eeprom_read(handle_eeprom, rw_page, data_length, &Test_Read_Buffer);
    if (EEPROM_DEVICE_DONE != result)
    {
      outputMessage("Read Flash Failed with status %d\n", result);
      flag = 8;
      goto jsdcc_mem_unit_test_eeprom_end;
    }
    else
    {
      //outputMessage("Read Successful for block %d\n",block_no+i);
    }

    for(j=0; j<data_length; j++)
    {
      if (WriteTestChar != Test_Read_Buffer[j] )
      {
        outputMessage("Failed!!Read Write mismatch at %d\n", j);
        flag = 9;
        goto jsdcc_mem_unit_test_eeprom_end;
      }
    }

    outputMessage("Data comparison between Read and Write operations Successful! \n");
    rw_page = rw_page + EEPROM_PAGE_SIZE;

  }
  
  WriteTestChar = 0x55;  
  for(i=0; i<data_length; i++)
  {
    Test_Write_Buffer[i]= WriteTestChar;
  }
  outputMessage("Buffer initialized 2\n");

  rw_page = page;
  Block_count = jtag_prog_param.data_length;
  memset(&Test_Read_Buffer, 0, sizeof(Test_Read_Buffer));
	
  for (i= 0; i < Block_count; i++)
  {
    k = i * EEPROM_PAGE_SIZE;
	
    result = eeprom_write(handle_eeprom, rw_page, EEPROM_PAGE_SIZE, &Test_Write_Buffer[k]);
    if (EEPROM_DEVICE_DONE != result)
    {
      outputMessage("Write Flash Failed with status %d\n", result);
      flag = 10;
      goto jsdcc_mem_unit_test_eeprom_end;
    }
    else
    {
      //outputMessage("Write Successful for block %d\n",block_no+i);
    }

    result = eeprom_read(handle_eeprom, rw_page, EEPROM_PAGE_SIZE, &Test_Read_Buffer[k]);
    if (EEPROM_DEVICE_DONE != result)
    {
      outputMessage("Read Flash Iteration 2 Failed with status %d\n", result);
      flag = 12;
      goto jsdcc_mem_unit_test_eeprom_end;
    }
    else
    {
      //outputMessage("Read Flash Iteration 2 Successful for block %d\n",block_no+i);
    }

    for(j=k; j < EEPROM_PAGE_SIZE; j++)
    {
      if (WriteTestChar != Test_Read_Buffer[j] )
      {
        outputMessage("Failed!!Read Write mismatch at %d for iteration %d\n", j, i);
        flag = 13;
        goto jsdcc_mem_unit_test_eeprom_end;
      }
    }

    outputMessage("Data comparison between Read and Write operations Successful for Iteration! %d \n", i);
    rw_page = rw_page + EEPROM_PAGE_SIZE;

  }
	
  result = eeprom_close(handle_eeprom);
  if(EEPROM_DEVICE_DONE != result)                 
  {
    outputMessage("Error Closing The Device For TestClient-1: status %d\n", result);
    flag = 14;
    //goto jsdcc_mem_unit_test_eeprom_end;
  } 

  result = eeprom_close(unit_test_handle);
  if(EEPROM_DEVICE_DONE != result)                 
  {
    outputMessage("Error Closing The Device For TestClient-2\n");
    flag = 15;
    goto jsdcc_mem_unit_test_eeprom_end;
  }
  jsdcc_mem_unit_test_eeprom_end:
  if (flag ==0)
  {
    outputMessage("Unit Test succesful!!\n");
    return STATUS_SUCCESS;
  }
  else 
  {
    outputMessage ("Failed with flag status %d",flag);
    eeprom_utils_deinit();
    return EEPROM_DEVICE_FAIL;	 
  }
}


/*===========================================================================

DESCRIPTION
  This function computes the CRC32 over a buffer

DEPENDENCIES
  Assumes jtag_prog_param (global variable) has valid parameters.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_compute_crc_eeprom(void)
{ 
   UINT32 page, data_length, byte_offset, byte_count;
   INT32 result = EEPROM_DEVICE_DONE;
   byte *pdata;

   pdata = jtag_prog_param.data;
   page = jtag_prog_param.addr * 16;
   data_length = SIZE_IN_PAGES(jtag_prog_param.data_length);

   byte_offset = page * EEPROM_PAGE_SIZE;
   byte_count = data_length * EEPROM_PAGE_SIZE;
   
   outputMessage("Reading Sector 0x%x \n", jtag_prog_param.addr);
	  
   result = eeprom_read(handle_eeprom, byte_offset, byte_count,pdata);
   
   if (EEPROM_DEVICE_DONE != result) 
   {
     outputMessage("Failed with status %d\n", result);
     eeprom_utils_deinit();
     return STATUS_FAIL;
   }
   else
   {
	   outputMessage("Success\n");
   }

   jtag_prog_param.data_length = calc_crc32((UINT8 *)pdata, jtag_prog_param.data_length);
   
   outputMessage("CRC Compute: Success! \n");

   return STATUS_SUCCESS;
}

/*===========================================================================

DESCRIPTION
  This function is a wrapper for the real memory erase routine.  
  The step to erase the entire memory device is to check the size
  of each physical partition and erase the partition by issue the 
  block erase command.

RETURN VALUE
  If success, return STATUS_SUCCESS else STATUS_FAIL

SIDE EFFECTS

===========================================================================*/

UINT32 jsdcc_mem_chip_erase_eeprom(void)
{  
  return STATUS_SUCCESS;
}  

/*===========================================================================

DESCRIPTION
  This function call the API to set the active boot partition

DEPENDENCIES

RETURN VALUE
  If success, return the starting sector of the givin partition, if
  failed, return 0

SIDE EFFECTS

===========================================================================*/
UINT32 jsdcc_mem_set_active_boot_eeprom(void)
{
   return STATUS_SUCCESS;
}
#else

UINT32 do_probe_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_read_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_write_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_erase_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_compute_crc_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_print_info_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_program_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_chip_erase_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_erase_partition_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_set_active_boot_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_erase_bulk_eeprom(void)
{
   return STATUS_SUCCESS;
}
UINT32 jsdcc_mem_unit_test_eeprom()
{
   return STATUS_SUCCESS;
}

#endif /* JTAGPROGRAMMER_EEPROM_ENABLE */

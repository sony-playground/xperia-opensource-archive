/*=======================================================================
* FILE:        flash_log.c
*
* SERVICES:    Routines to support flash logging
*
* DESCRIPTION :
*
* Copyright (c) 2010,2015, 2020-2021 QUALCOMM Technologies Incorporated.
* All Rights Reserved.
* QUALCOMM Confidential and Proprietary
*=======================================================================*/

/*===================================================================
*
*                       EDIT HISTORY FOR FILE
*
*   This section contains comments describing changes made to the
*   module. Notice that changes are listed in reverse chronological
*   order.
*
*   $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandJtagToolsLib/flash_log.c#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
*
* when         who     what, where, why
* ----------   ---     ----------------------------------------------
* 06/25/21     sa      Initialise va_list argument.
* 06/20/20     sa      Removed Unused code.
* 06/11/20     sa      Ported to Olympic.
* 01/28/15     sb      Fix Klocwork errors
* 07/12/10     nr      Initial version
*==================================================================*/

/*===================================================================
*
*                     Include Files
*
====================================================================*/

#include "comdef.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "flash_log.h"

/* Buffer to store the print output */
#define BUFFER_SIZE 0x4000
uintnt output_buffer_length = 0;
byte  output_buffer[BUFFER_SIZE];


/*
 * Printing the message to output_buffer.
 */
int outputMessage(const char* string, ...)
{
  int retval = 0;
  uintnt buffer_space = 0;
  byte *buffer = &output_buffer[output_buffer_length];
  va_list arguments = {0};
  va_start(arguments, string);

  buffer_space = sizeof(output_buffer) - output_buffer_length;

  retval = vsnprintf((char *)buffer,
                      buffer_space,
                      string,
                      arguments);
  output_buffer_length += MIN(buffer_space, retval);

  return retval;
  //va_end(arguments);
}

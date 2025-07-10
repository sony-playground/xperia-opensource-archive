/** @file DTBHexDump.c
  Low-level hex dump utility for debug/trace messages

  Copyright (c) 2020-2021 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/28/21   tmt     Add INSTRUMENTATION on/off support
 12/16/20   tmt     Prep for multi-thread support, remove global buffer
 11/23/20   tmt     Support port to Q6
 07/16/20   tmt     Initial creation of Library

=============================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <libfdt_env.h>
#include <fdt.h>
#include <libfdt.h>

#include "DTBExtnLib.h"
#include "DTBInternals.h"
#include "DTBExtnLib_env.h"

/*=========================================================================
     Default Defines
==========================================================================*/
#define HEX_PARAGRAPH 0x10
#define FBUF_SIZE 68		/* hold single line of output */

/*=========================================================================
     Local Static Variables
==========================================================================*/

/**
 * dtb_hex_dump - hex dump on console log
 * @title: character string describing what is being dumped
 * @addr: address of buffer to dump
 * @length: number of bytes in buffer to dump
 *
 * returns: void, no return value
 */
void dtb_hex_dump(char *title, void *addr, int length) 
{
#ifdef INSTRUMENTATION
    int i, j;
	unsigned char abuf[HEX_PARAGRAPH+1];		/* ascii buffer (or dots) */
	unsigned char *aptr = (unsigned char *)addr;
    int count = 0;				/* track length of format string as it builds up */
    char fbuf[FBUF_SIZE];

    fbuf[0] = '\0';

    /* title goes first, if provided */
    if (NULL != title)
		PUTS(title);

    /* Handle each byte in addr buffer */
    for (i=0,j=0; i<length; i++) {

        /* Store hex value of byte in data stream */
        snprintf(&fbuf[count], FBUF_SIZE, " %02x", aptr[i]);
        count+=3;

        /* Store Ascii value (or dot) for end of line */
        abuf[j++] = isprint(aptr[i]) ? aptr[i] : '.';

		/* are we at end of hex paragraph? */
		if ( (HEX_PARAGRAPH == j) || (i == length-1) ) {
			if ( (count + 3 + j) < FBUF_SIZE ) {
				while (j<HEX_PARAGRAPH) {
					abuf[j] = 0;
					strlcat(fbuf, "   ", 3);
					count += 3;
					j++;
				}
				strlcat(fbuf, "  ", 2);
				strlcat(fbuf, (const char *)abuf, j);
				PUTS(fbuf);
				fbuf[0] = '\0';
				count = j = 0;
			} else
				break;
		}
    }
#endif
}

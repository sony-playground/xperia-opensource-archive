#ifndef NAND_DUMP_H
#define NAND_DUMP_H

/*=======================================================================
 * FILE:        nand_dump.h
 *
 * SERVICES:    Flash Programming Plug-In for Lauterbach FLASH_PROG/ICD TRACE32
 *
 * DESCRIPTION
 *   This file has the Nand device dump structure
 *
 *       Copyright (c) 2009, 2012, 2020 Qualcomm Technologies Inc.
 *	   All Rights Reserved.
 *	   Qualcomm Confidential and Proprietary
 *=======================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *   
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/11/20     sa      Ported to Olympic.
 * 04/20/20     sa      Removed unused code, nand_sim.h
 * 09/11/12     eo      Remove miboot.h
 * 11/03/09     wt      Initial version
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_prog.h"
#include "nand_tools.h"
#include "flash_miparti.h"
#include "nand_api.h"


/* Nand device dump structure */
/* Holds the device structure, the partition info */
struct dump_device_info
{
  /* NAND device structure */
  nand_handle_t flash_handle;
  struct flash_info flash_info;

  uint32 read_bsize_per_blk; /* Number of bytes to be read per block */

  /* Partition to be read */
  char parti_name[FLASH_PART_NAME_LENGTH];

  uint32 current_block;

  /* Number of blocks in Partition */
  uint32 num_bad_blks_in_partition;

  /* Actual size of data read/page */
  uint32 read_stride;

};

extern struct dump_device_info dump_dev_info_param;

extern struct dump_device_info *dump_dev ;

#endif /* NAND_DUMP_H */

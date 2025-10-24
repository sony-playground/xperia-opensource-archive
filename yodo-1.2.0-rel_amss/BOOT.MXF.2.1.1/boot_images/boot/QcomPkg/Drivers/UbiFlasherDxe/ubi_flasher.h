/***********************************************************************
 * ubi_flasher.h
 *
 * UBI Flasher module.
 * Copyright (C) 2017,2020 QUALCOMM Technologies, Inc.
 *
 * Flashes an UBI or an UBIFS images onto nand flash.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2020-06-09   eo    Porting ubi flasher support to XBL Core
2017-09-08   rp    Create

===========================================================================*/
#ifndef __UBI_FLASHER_H__
#define __UBI_FLASHER_H__

#include "comdef.h"

#ifndef UBI_FLASHER_SYSTEM_PARTITION_NAME
#define UBI_FLASHER_SYSTEM_PARTITION_NAME "system"
#endif

typedef void* ubi_flasher_handle;

int ubi_flasher_open(const char *partition_name, ubi_flasher_handle *hdl,
	uint32 *page_size_arg, uint32 *block_size_arg);
int ubi_flasher_write(ubi_flasher_handle hdl_arg, uint32 frame_no,
  uint8 *buf, uint32 buf_size);
int ubi_flasher_close(ubi_flasher_handle hdl_arg);

#endif /* __UBI_FLASHER_H__ */

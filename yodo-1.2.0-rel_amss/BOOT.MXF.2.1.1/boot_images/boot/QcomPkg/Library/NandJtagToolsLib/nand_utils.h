#ifndef __NAND_UTILS_H__
#define __NAND_UTILS_H__

/*=======================================================================
 * FILE:        nand_utils.h
 *
 * SERVICES:    Various utility functions used in NAND.
 *
 * GENERAL DESCRIPTION
 *    Various utility functions used in NAND.
 *
 *        Copyright © 2008-2010, 2020 QUALCOMM Technologies Inc.
 *               All Rights Reserved.
 *            QUALCOMM Proprietary/GTDR
 *=======================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *   $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandJtagToolsLib/nand_utils.h#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/11/20     sa      Ported to Olympic.
 * 01/08/10     op      Support WM7 boot config read/write
 * 02/27/09     jz      Renamed functions to be prefixed with flash_utils_
 * 10/29/08     mm      Initial version
 *==================================================================*/

uint32 flash_utils_list_bad_blocks(void);
uint32 flash_utils_erase_block(uint32 dwBlock);
uint32 flash_utils_invalidate_block(uint32 dwBlock);
uint32 flash_utils_make_block_good(uint32 dwBlock);
uint32 flash_utils_read_page(void);
uint32 flash_utils_fill_page(void);
uint32 flash_utils_read_id (void);
uint32 flash_utils_otp_page(void);
uint32 flash_utils_read_uuid(void);
uint32 flash_utils_validate_boot_block (void);
uint32 flash_utils_bldr_read_boot_config(void);
uint32 flash_utils_bldr_write_boot_Config(void);


#endif /* __NAND_UTILS_H__ */

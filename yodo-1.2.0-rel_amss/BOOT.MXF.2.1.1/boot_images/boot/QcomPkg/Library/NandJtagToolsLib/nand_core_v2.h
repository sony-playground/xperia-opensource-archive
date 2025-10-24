#ifndef NAND_CORE_V2_H
#define NAND_CORE_V2_H

/*=======================================================================
 * FILE:        nand_core_v2.h
 *
 * SERVICES:    Flash Programming Plug-In support for SB2.0 configuration
 *
 * DESCRIPTION
 *   This file has the definitions specific for SecureBoot 2.0 architecture
 *
 *        Copyright © 2009, 2020 QUALCOMM Technologies Incorporated.
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
 *   $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandJtagToolsLib/nand_core_v2.h#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/11/20     sa      Ported to Olympic.
 * 02/27/09     jz      Initial version
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/
 

/* ------------------------------------------------------------------------
** Structure definition for boot Multi-Image Block Storage
** ------------------------------------------------------------------------ */
struct boot_block_ctl;
typedef struct boot_block_ctl *boot_block_ctl_t;

struct boot_block_ctl {
  int    dbl_block;      /* Block number for DBL                */
  int    bbtb_block;     /* Block number for Bad Block Table    */
  int    mibib_block;    /* Block number for MIBIB              */
};

#endif /* NAND_CORE_V2_H */

#ifndef __FLASH_LOG_H__
#define __FLASH_LOG_H__

/*=======================================================================
* FILE:        flash_log.h
*
* SERVICES:    Routines to support flash logging
*
* DESCRIPTION :
*
* Copyright (c) 2010, 2020 QUALCOMM Technologies Incorporated.
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
*   $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandJtagToolsLib/flash_log.h#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
*
* when         who     what, where, why
* ----------   ---     ----------------------------------------------
* 06/20/20     sa      Removed unused feature.
* 06/11/20     sa      Ported to Olympic.
* 04/20/20     sa      Removed old unused code.
* 07/12/10     nr      Initial version
*==================================================================*/


int outputMessage(const char*, ...);

/* -----------------------------------------------------------------------
** Macros for debug print output
** ----------------------------------------------------------------------- */
  #ifdef TNOISY
    #define FLASHLOG(l, x) if (TNOISY >= l) {outputMessage x;}
  #else
    #define FLASHLOG(l, x) /**/
  #endif /* NOISY */

#endif /* __FLASH_LOG_H__ */

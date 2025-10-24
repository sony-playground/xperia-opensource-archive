#ifndef __PM_PBUS_H__
#define __PM_PBUS_H__

/*! \file
 *  \n
 *  \brief  pm_pbus.h
 *  \n  Function and data structure declarations for PBUS driver interface.
 *  \n
 *  \n
 *  \n &copy; Copyright 2015-2017, 2021 QUALCOMM Technologies Incorporated, All Rights Reserved.
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/pmic/pm/pm_pbus.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/17/16   akm     Created.
=============================================================================*/


#include "comdef.h"
#include "pm_err_flags.h"


/*===========================================================================
                Definitions
===========================================================================*/

#define PM_LOGGER_MAX_BUFFER_SIZE 1024

typedef struct __attribute__((packed))
{
  uint8 val;
  uint16 regoffs;
  uint8 opr;
}pm_pbus_logger_data_type;

typedef struct
{
  uint8  data[2048];        /* Data (256*8*8 bits) */
} pm_pbus_data_type;

/*===========================================================================
Definitions
===========================================================================*/

/**
 * @brief This function configures and captures the PBUS logger.
 *
 * @details
 *
 * @param[in/out] a pointer to a buffer that contains data from
 *        the PBUS logger.
 * @return
 * PM_ERR_FLAG_SUCCESS -- on success otherwise PMIC error code.
 */
pm_err_flag_type pm_pbus_logger(uint8 device_index, pm_pbus_data_type *pbus_log_data);


#endif /* __PM_PBUS_H__ */

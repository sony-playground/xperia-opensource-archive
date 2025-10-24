#ifndef PM_CLK_DRIVER__H
#define PM_CLK_DRIVER__H

/*! \file pm_clk_driver.h
 *  \n
 *  \brief This file contains CLOCK peripheral driver related function prototypes,
 *         enums and driver data structure type.   
 *  \n  
 *  \n &copy; Copyright 2013-2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/clk/src/pm_clk_driver.h#2 $

when        who     what, where, why
--------    ---     ----------------------------------------------------------
04/12/13    aks      Created as part of Code refactoring.
========================================================================== */
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_err_flags.h"
#include "hw_module_type.h"
#include "CoreVerify.h"
#include "pm_comm.h"
#include "pm_utils.h"

/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/

#define PM_CLK_INVALID_DATA   99

/* Please make sure to change the clk_info and clk_dep info arrays in
   config folder when the below macro is changed */
#define PM_MAX_NUM_CLKS       17

/*! \enum pm_clk_type
 *  \brief This enum contains definitions of Clock types
 */
typedef enum
{
  PM_CLK_SLEEP,
  PM_CLK_XO,
  PM_CLK_1,  
  PM_CLK_2,  
  PM_CLK_3,  
  PM_CLK_4,  
  PM_CLK_5,  
  PM_CLK_6,  
  PM_CLK_7,  
  PM_CLK_8,  
  PM_CLK_9,  
  PM_CLK_10, 
  PM_CLK_11, 
  PM_CLK_12,
  PM_CLK_13,
  PM_CLK_DIST,
  PM_CLK_MAX_INDEX,
  PM_CLK_TYPE_INVALID = PM_CLK_MAX_INDEX,

  /* Legacy PMIC Clock Buffer numbers */
  PM_RFCLK_1 = PM_CLK_1,
  PM_RFCLK_2,    
  PM_RFCLK_3,    
  PM_RFCLK_4,    
  PM_RFCLK_5,    
  PM_CLK_LN_BB = PM_CLK_6,
  PM_CLK_BB_1 = PM_CLK_6,
  PM_CLK_BB_2,    
  PM_CLK_BB_3,    
  PM_CLK_BB_4,
  PM_CLK_BB_5,
  PM_CLK_DIV_1 = PM_CLK_11,
  PM_CLK_DIV_2,   
  PM_CLK_DIV_3,   
  PM_ALL_CLKS = PM_CLK_MAX_INDEX,
}pm_clk_type;


typedef struct 
{ 
    pm_register_address_type    peripheral_offset;
    pm_register_address_type    STATUS1;            //0x8
    pm_register_address_type    EN_CTL;             //0x46
    pm_register_address_type    TIMER;              //0x4C
    pm_register_address_type    INT_EN_SET;         //0x15
    pm_register_address_type    INT_EN_CLR;         //0x16    
}pm_clk_register_info_type;

typedef struct 
{
    pm_comm_info_type               *comm_ptr;
    uint32                          num_of_peripherals;
    uint8                           periph_subtype[PM_MAX_NUM_CLKS];
    uint8                           dig_maj_min[PM_MAX_NUM_CLKS];
    //array of clk peripheral index  to get to right offset from base
    uint8                           clk_perph_index[PM_CLK_MAX_INDEX];
    pm_clk_type                     clk_common[PM_MAX_NUM_CLKS];
    pm_register_address_type        base_address;
    pm_clk_register_info_type       *clk_reg_table;
    boolean                         xo_always_on;
}pm_clk_data_type;

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
void pm_clk_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_clk_data_type* pm_clk_get_data(uint8 pmic_index);

uint8 pm_clk_get_num_peripherals(uint8 pmic_index);

/*===========================================================================

                        API

===========================================================================*/

/**
* Force enables or allows disable of the clock.
*
* @param[in] pmic_chip Selects the PMIC chip in which the buffers being
*                      controlled are located. The device index starts with
*                      zero.
* @param[in] periph Selects the clock peripheral to turn on.
*               See #pm_clk_type.
* @param[in] on_off Turns a clock on or off (enable or disable).
*                   See #pm_on_off_type.
* 
* @return
* SUCCESS or Error -- See #pm_err_flag_type.
*/
pm_err_flag_type pm_clk_sw_enable(uint8 pmic_chip, pm_clk_type periph, pm_on_off_type on_off);

/**
* Returns the clock software enable status.
*
* @param[in] pmic_chip Selects the PMIC chip in which the buffers being
*                      controlled are located. The device index starts with
*                      zero.
* @param[in] periph Selects the clock peripheral to turn on.
*               See #pm_clk_type.
* @param[out] on_off Returns clock on or off status (enable or disable).
*                   See #pm_on_off_type.
* 
* @return
* SUCCESS or Error -- See #pm_err_flag_type.
*/
pm_err_flag_type pm_clk_sw_enable_status(uint8 pmic_chip, pm_clk_type periph, pm_on_off_type* on_off);

/**
* Returns the currently configured clock warmup time delay in 
* micro seconds. 
*
* @param[in] pmic_chip Selects the PMIC chip in which the buffers being
*                      controlled are located. The device index starts with
*                      zero.
* @param[in] periph Selects the clock peripheral to turn on.
*                   See #pm_clk_type.
* @param[out] warmup_time_usec Pointer to return the configured 
*                              warmup time delay value in uS.
* 
* @return
* SUCCESS or Error -- See #pm_err_flag_type.
*/
pm_err_flag_type pm_clk_get_warmup_time(uint8 pmic_chip, pm_clk_type periph, uint32 *warmup_time_usec);

/**
* Setting interrupt rising edge and enablign the interrupt
*
* @param[in] pmic_chip Selects the PMIC chip in which the buffers being
*                      controlled are located. The device index starts with
*                      zero.
* @param[in] periph Selects the clock peripheral to turn on.
*               See #pm_clk_type.
* @param[in] on_off Turns interrupt on or off (enable or disable).
*                   See #pm_on_off_type.
* 
* @return
* SUCCESS or Error -- See #pm_err_flag_type.
*/
pm_err_flag_type pm_clk_irq_enable(uint8 pmic_chip, pm_clk_type periph, pm_on_off_type on_off);

/**
* Returns the clock software enable status.
*
* @param[in] pmic_chip Selects the PMIC chip in which the buffers being
*                      controlled are located. The device index starts with
*                      zero.
* @param[in] periph Selects the clock peripheral to turn on.
*               See #pm_clk_type.
* @param[out] clk_ready return the CLK_OK status
* 
* @return
* SUCCESS or Error -- See #pm_err_flag_type.
*/
pm_err_flag_type pm_clk_ready_status(uint8 pmic_chip, pm_clk_type periph, boolean *clk_ready);

#endif /* PM_CLK_DRIVER_H */


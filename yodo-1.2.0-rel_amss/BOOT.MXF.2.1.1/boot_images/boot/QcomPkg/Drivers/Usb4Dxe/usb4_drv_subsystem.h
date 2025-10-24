/**---------------------------------------------------------------------------
 * @file usb4_drv_subsystem.h
 * 
 * @brief   Header file for a Connection Manager
 * 
 * Copyright (c) 2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/


#ifndef __USB4_DRV_SUBSYSTEM_H__
#define __USB4_DRV_SUBSYSTEM_H__


/*----------------------------------------------------------------------------
 * Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Definitions
 *--------------------------------------------------------------------------*/

typedef enum
{
    USB4_DRV_SUBSYSTEM_USB4,
    USB4_DRV_SUBSYSTEM_USB3,
    USB4_DRV_SUBSYSTEM_PCIE,
    USB4_DRV_SUBSYSTEM_DP,
    USB4_DRV_SUBSYSTEM_CNT,
} USB4_DRV_SUBSYSTEM;

/*----------------------------------------------------------------------------
 * Function Declarations
 *--------------------------------------------------------------------------*/

#endif /* __USB4_DRV_SUBSYSTEM_H__ */

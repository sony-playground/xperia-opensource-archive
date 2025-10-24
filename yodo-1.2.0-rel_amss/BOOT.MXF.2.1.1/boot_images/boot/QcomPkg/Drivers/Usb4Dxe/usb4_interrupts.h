/**---------------------------------------------------------------------------
 *   @file        usb4_interrupts.h
 *
 *   @brief   Header file for a full USB4 API
 *
 *   Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef __USB4_INTERRUPTS_H__
#define __USB4_INTERRUPTS_H__

// #include "VVHAL_usb4_platform.h"

/*----------------------------------------------------------------------------
 * Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Enumerations Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations
 *--------------------------------------------------------------------------*/
// /**
//  * @brief This function handles hot plug interrupt from QGIC
//  * @params[in] Interrupt source and a pointer to user data
//  */
// void VVDRV_usb4_generic_isr_CONTROL_PACKET(uint32 int_source, void *user_data);
// 
// /**
//  * @brief This function handles cable connect interrupt from QGIC
//  * @params[in] Interrupt source and a pointer to user data
//  */
// void VVDRV_usb4_generic_isr_CABLE_CONNECT(uint32 int_source, void *user_data);

/**
 * @brief This function handles cable connect interrupt from PMIC
 * @params[in] Interrupt source and a pointer to user data
 */
void VVDRV_usb4_interrupts_isr_pd_connect(UINT32 int_source, void *user_data);

/**
* @brief This function handles events that comes from the UC
* @params[in] Interrupt source and a pointer to user data
*/
void VVDRV_usb4_interrupts_isr_uc(UINT32 int_source, void *user_data);

/*-------------------------------------------------------------------*/
/**
 * @brief handle interrupts caused by control packet transmition
 * @param int_source - the interrupt source that triggered the interrupt
 * @param user_data - user context passed as interrupt argument 
 */
void VVDRV_usb4_interrupts_isr_hia_rings(UINT32 int_source, void *user_data);

/*-------------------------------------------------------------------*/
/**
 * @brief handle interrupts caused by device wake signalling
 * @param int_source - the interrupt source that triggered the interrupt
 * @param user_data - user context passed as interrupt argument
 */
void VVDRV_usb4_interrupts_isr_wake(UINT32 int_source, void *user_data);

/*-------------------------------------------------------------------*/
/**
 * @brief handle interrupts caused by display's adpater auxilery channel
 * @param int_source - the interrupt source that triggered the interrupt
 * @param user_data - user context passed as interrupt argument 
 */
void VVDRV_usb4_interrupts_isr_dp_aux(UINT32 int_source, void *user_data);

/*-------------------------------------------------------------------*/


#endif //__USB4_INTERRUPTS_H__

#ifndef MI_PMU_H
#define MI_PMU_H
/*
===========================================================================

FILE:         mi_pmu.h 

DESCRIPTION:  Header file for the MI_PMU library.

===========================================================================

                             Edit History

$Header: //components/rel/aop.ho/5.0/aop_proc/core/api/systemdrivers/mi_pmu.h#1 $

when         who     what, where, why
----------   ---     ------------------------------------------------------
2019/08/14   sds     Initial revision.

===========================================================================
        Copyright (c) 2019 QUALCOMM Technologies, Incorporated.
                         All Rights Reserved.
                 QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include <stdbool.h>
#include <stdint.h>

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** External interface
** ----------------------------------------------------------------------- */
/**
@brief This function initializes the MI_PMU library.
*/
void mi_pmu_init( void );

/* -----------------------------------------------------------------------
** AOP services interface
** ----------------------------------------------------------------------- */
/**
@brief Interface for AOP services to notify PMU of any pending services

@param[in] irq - The IRQ to handle

@returns true if abort is desired, false otherwise
*/
bool mi_pmu_handle_aop_service_req( int irq );

#endif /* MI_PMU_H */


/*******************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2014,2021 Qualcomm Technologies Incorporated.
 All rights reserved.
 ******************************************************************************/
/*==============================================================================
$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/DSFTargetLib/interface/header/itf_ds/HALhwio.h#1 $
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $
================================================================================*/
#ifndef HAL_HWIO_H
#define HAL_HWIO_H
/*
===========================================================================
*/
/**
  @file HALhwio.h 
  
  Public interface include file for accessing the HWIO HAL definitions.
  
  The HALhwio.h file is the public API interface to the HW I/O (HWIO)
  register access definitions.
*/



/*=========================================================================
      Include Files
==========================================================================*/


/*
 * Common types.
 */
#include "HALcomdef.h"
#include "stddef.h"
#include "msmhwio.h"


#define HWIO_OUTXF2(base, io, field2, field1, val2, val1)               HWIO_OUTXM(base, io, (HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                                                                        ( (val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))) )
#define HWIO_OUTXF3(base, io, field3, field2, field1, val3, val2, val1) HWIO_OUTXM(base, io, (HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                                                                        ( (val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))) )
#define HWIO_OUTXF4(base, io, field4, field3, field2, field1, val4, val3, val2, val1)               HWIO_OUTXM(base, io, (HWIO_FMSK(io, field4) |HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                                                                                                    ( (val4<<HWIO_SHFT(io, field4))|(val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))) )

#define HWIO_OUTXF5(base, io, field5, field4, field3, field2, field1, val5, val4, val3, val2, val1) HWIO_OUTXM(base, io, (HWIO_FMSK(io, field5)|HWIO_FMSK(io, field4)|HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                                                                                                    ( (val5<<HWIO_SHFT(io, field5))|(val4<<HWIO_SHFT(io, field4))|(val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))) )
#define HWIO_OUTXF6(base, io, field6, field5, field4, field3, field2, field1, val6, val5, val4, val3, val2, val1) HWIO_OUTXM(base, io, (HWIO_FMSK(io, field6)|HWIO_FMSK(io, field5)|HWIO_FMSK(io, field4)|HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                                                                                                                  ( (val6<<HWIO_SHFT(io, field6))|(val5<<HWIO_SHFT(io, field5))|(val4<<HWIO_SHFT(io, field4))|(val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))) )

#endif /* HAL_HWIO_H */


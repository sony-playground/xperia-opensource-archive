#ifndef __SPMIBUSDEBUG_H__
#define __SPMIBUSDEBUG_H__

/*! \file  SpmiBusDebug.h
 *
 *  \brief  Contains SPMI bus debug driver interface declaration
 *
 *  &copy; Copyright 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
 */


#include "SpmiBus.h"

Spmi_Result SpmiBusDebug_Init();

Spmi_Result SpmiBus_ReadLongDebug(uint32 busId,
                                  uint32 vSlaveId,
                                  Spmi_AccessPriority priority,
                                  uint32 address,
                                  uint8* data,
                                  uint32 len,
                                  uint32* bytesRead);

Spmi_Result SpmiBus_WriteLongDebug(uint32 busId,
                                   uint32 vSlaveId,
                                   Spmi_AccessPriority priority,
                                   uint32 address,
                                   uint8* data,
                                   uint32 len);

Spmi_Result SpmiBus_ReadModifyWriteLongByteDebug(uint32 busId,
                                                 uint32 vSlaveId,
                                                 Spmi_AccessPriority priority,
                                                 uint32 address,
                                                 uint8 data,
                                                 uint8 mask,
                                                 uint8 *byteWritten);

Spmi_Result SpmiBus_VerifyDebugMode();


#endif

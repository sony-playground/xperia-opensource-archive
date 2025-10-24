#ifndef BOOT_FRAMEWORK_H
#define BOOT_FRAMEWORK_H

/*===========================================================================

                      Boot Config Context Header File

GENERAL DESCRIPTION
  This file contains the interfaces for Config Context module. 

Copyright 2019 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/boot_framework.h#1 $ 
$DateTime: 2022/08/18 10:15:46 $ 
$Author: pwbldsvc $

when        who      what, where, why
----------  ---      ----------------------------------------------------------
04/03/19    ep       Initial version

===========================================================================*/


/*===========================================================================
                           INCLUDE FILES
===========================================================================*/
#include "boot_comdef.h"


/*==========================================================================
                          PUBLIC DATA DECLARATIONS
===========================================================================*/
#define CLOSED_OBJECT_ID	-1


typedef void* boot_handle;

typedef struct boot_handle_common_type
{
	uint32 id;
	boot_handle config_context_handle;
} boot_handle_common_type;

#endif // BOOT_FRAMEWORK_H

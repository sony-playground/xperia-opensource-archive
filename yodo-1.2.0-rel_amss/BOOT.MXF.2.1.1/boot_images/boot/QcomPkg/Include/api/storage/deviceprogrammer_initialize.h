/*==================================================================
 *
 * FILE:        deviceprogrammer_firehose.h
 *
 * DESCRIPTION:
 *   
 *
 *        Copyright © 2008-2014,2020 Qualcomm Technologies Incorporated.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 * YYYY-MM-DD   who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 2020-07-23   rama    Changed pbl_shared to void*
 * 2014-10-02   ah      Major code clean up
 * 2014-08-14   wek     Indicate that deviceprogrammer functions don't return.
 * 2013-06-03   ah      Added legal header
 * 2013-05-31   ab      Initial checkin
 */

#ifndef DEVICEPROGRAMMER_INITIALIZE_H
#define DEVICEPROGRAMMER_INITIALIZE_H

#include <pbl_sbl_shared.h>
#include "boot_sbl_if.h"

void deviceprogrammer_entry(void *pbl_shared);

#endif


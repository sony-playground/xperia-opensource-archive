#ifndef __UFS_ERRNO_H
#define __UFS_ERRNO_H
/**********************************************************************
 *
 *   UFS private definition header file
 *
 * Copyright (c) 2012-2013, 2020-2021 Qualcomm Technologies, Inc.  
*  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *
 **********************************************************************/

/*======================================================================

                        EDIT HISTORY FOR MODULE


when         who     what, where, why
----------   ---     --------------------------------------------------- 
2021-10-25   jt      Add EPERM 
2020-03-31   jt      Add ENOSYS
2012-12-18   rh      Initial creation
=======================================================================*/

#include "ufs_api.h"

#define EOK                         (UFS_EOK)
#define EPERM                       (UFS_EPERM)
#define ENOENT                      (UFS_ENOENT)
#define EIO                         (UFS_EIO)
#define ENOMEM                      (UFS_ENOMEM)
#define EBUSY                       (UFS_EBUSY)
#define ENODEV                      (UFS_ENODEV)
#define EINVAL                      (UFS_EINVAL)
#define ENOSYS                      (UFS_ENOSYS)
#define EPROTO                      (UFS_EPROTO)
#define ETIME                       (UFS_ETIME)

// Custom internal meessages
#define ECHKCND                     1000

#endif /* __UFS_ERRNO_H */

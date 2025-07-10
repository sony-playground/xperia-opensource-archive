/*===========================================================================
                              DALSys.h

DESCRIPTION:

Copyright (c) 2019 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/
#ifndef _DAL_SYS
#define _DAL_SYS

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef uintptr_t
typedef unsigned int uintptr_t;
#endif

#define DALSYS_SYNC_OBJ_SIZE_BYTES 4

typedef void * DALSYSSyncHandle;

#define DALSYS_SyncEnter(x) INTLOCK()
#define DALSYS_SyncLeave(x) INTFREE()
#define DALSYS_SyncCreate(x, y, z) DAL_SUCCESS

#define DAL_SUCCESS 0
#define DAL_ERROR 1

#endif /* _DAL_SYS */

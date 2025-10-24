/*===============================================================================================
 * FILE:        timesafe.h
 *
 * DESCRIPTION: Declaration of timesafe APIs
 *
 *              Copyright (c) 2013, 2021 Qualcomm Technologies Incorporated
 *              All Rights Reserved. Qualcomm Confidential and Proprietary.
 *===============================================================================================*/

#ifndef	_TIMESAFE_H
#define	_TIMESAFE_H

#ifdef __cplusplus
extern "C" {
#endif

int timesafe_memcmp(const void *, const void *, size_t);
int timesafe_strncmp(const char *, const char *, size_t);

#ifdef __cplusplus
}
#endif

#endif

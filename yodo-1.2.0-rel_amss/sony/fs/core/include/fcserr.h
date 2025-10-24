/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_ERROR_H_
#define FCS_ERROR_H_

#define FCSERR_OK       (0)

/*
 * error codes based on linux errno
 */

#define FCSERR_PERM      (1) /* Operation not permitted */
#define FCSERR_ENOENT    (2) /* No such file or directory */
#define FCSERR_ESRCH     (3) /* No such process */
#define FCSERR_EINTR     (4) /* Interrupted system call */
#define FCSERR_EIO       (5) /* I/O error */
#define FCSERR_ENXIO     (6) /* No such device or address */
#define FCSERR_E2BIG     (7) /* Argument list too long */
#define FCSERR_ENOEXEC   (8) /* Exec format error */
#define FCSERR_EBADF     (9) /* Bad file number */
#define FCSERR_ECHILD   (10) /* No child processes */
#define FCSERR_EAGAIN   (11) /* Try again */
#define FCSERR_ENOMEM   (12) /* Out of memory */
#define FCSERR_EACCES   (13) /* Permission denied */
#define FCSERR_EFAULT   (14) /* Bad address */
#define FCSERR_ENOTBLK  (15) /* Block device required */
#define FCSERR_EBUSY    (16) /* Device or resource busy */
#define FCSERR_EEXIST   (17) /* File exists */
#define FCSERR_EXDEV    (18) /* Cross-device link */
#define FCSERR_ENODEV   (19) /* No such device */
#define FCSERR_ENOTDIR  (20) /* Not a directory */
#define FCSERR_EISDIR   (21) /* Is a directory */
#define FCSERR_EINVAL   (22) /* Invalid argument */

#define FCSERR_EBADRQC  (54)  /* Invalid request code */
#define FCSERR_ENODATA  (61)  /* No data */
#define FCSERR_ENOBUFS  (105) /* No buffer space available */

/* Custom error codes */
#define FCSERR_EPART    (1000) /* Partition size error */
#define FCSERR_EHDR     (1001) /* Broken sparse header(s) */
#define FCSERR_EUNK     (1002) /* Unknown option */
#define FCSERR_EOOB     (1003) /* Out of bounds */
#define FCSERR_ENIMP    (1004) /* Not implemented */
#define FCSERR_ELZ4     (1005) /* LZ4 decompress error */
#define FCSERR_ERRPART  (1006) /* Reread partition error */
#define FCSERR_ESTATE   (1007) /* Bad state */
#define FCSERR_EOPEN    (1008) /* Open failed */
#define FCSERR_EFORMAT  (1009) /* Format failed */
#define FCSERR_ENOHWC   (1010) /* No hardware config */
#define FCSERR_EVER     (1011) /* Unsupported version */
#define FCSERR_EMAGIC   (1012) /* Wrong magic */
#define FCSERR_ESIZE    (1013) /* Wrong size */
#define FCSERR_EHASH    (1014) /* Wrong hash */
#define FCSERR_EINDEX   (1015) /* Wrong index */
#define FCSERR_EINFOR   (1016) /* Wrong format */
#define FCSERR_ENOTF    (1017) /* Not found */
#define FCSERR_EVCC     (1018) /* Verify certchain error */
#define FCSERR_EHCLC    (1019) /* Hash calculation error */
#define FCSERR_EVS      (1020) /* Verify signature error */
#define FCSERR_EDEVID   (1021) /* Unmatched devid */
#define FCSERR_ETIME    (1022) /* Get time error */
#define FCSERR_EDONE    (1023) /* Operation already done error */
#define FCSERR_EBURN	(1024) /* Failed to burn fuse */
#define FCSERR_EVHSH    (1025) /* Hash verify error */
#define FCSERR_EDATA	(1026) /* Bad data */
#define FCSERR_AUTH     (1027) /* SAKE authentication required */
#define FCSERR_EWRITE   (1028) /* Write error */
#define FCSERR_EREAD    (1029) /* Read error */
#define FCSERR_EOPFAIL  (1030) /* Operation failed */
#define FCSERR_EOPID    (1031) /* Wrong opid */
#define FCSERR_ETBL	(1032) /* Bad partition table */
#define FCSERR_EBINDER	(1033) /* Unmatched binder */
#define FCSERR_EUSAGE	(1034) /* Wrong usage */
#define FCSERR_ESLOT	(1035) /* No active slot */
#define FCSERR_ENONCE	(1036) /* Nonce error */
#define FCSERR_ERFUSE	(1037) /* Error reading fuse */
#define FCSERR_EBADVER  (1038) /* Bad version */
#define FCSERR_SUPPORT	(1039) /* Not support */

#endif

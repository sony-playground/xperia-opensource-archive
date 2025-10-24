/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef OTP_DEF_H_
#define OTP_DEF_H_

/*
 * Note that the actual fuse definitions are used from the
 * header in MTK's sec trustlet git directly
 */

/* LOCK bits */
#define LOCK_CTRL_LOCK		(1 << 2)
#define LOCK_PID_VID_LOCK	(1 << 1)

/* SEC_CTRL bits */
#define SEC_CTRL_DAA_EN	(1 << 2)
#define SEC_CTRL_SBC_EN	(1 << 1)

/* SEC_LOCK bits */
#define SEC_LOCK_SEC_MSC_LOCK		(1 << 3)
#define SEC_LOCK_SEC_CTRL_LOCK		(1 << 2)
#define SEC_LOCK_AC_KEY_LOCK		(1 << 1)
#define SEC_LOCK_SBC_PUBK_HASH_LOCK	(1 << 0)

/* SEC_MSC bits */
#define SEC_MSC_MD1_SBC_EN	(1 << 1)

/* State flags for determining fuse status */
#define LOCK_FLAGS	(LOCK_CTRL_LOCK)
#define SEC_LOCK_FLAGS	(SEC_LOCK_SEC_CTRL_LOCK | \
			SEC_LOCK_AC_KEY_LOCK | \
			SEC_LOCK_SBC_PUBK_HASH_LOCK | \
			SEC_LOCK_SEC_MSC_LOCK)
#define SEC_CTRL_FLAGS	(SEC_CTRL_DAA_EN | SEC_CTRL_SBC_EN)
#define SEC_MSC_FLAGS	(SEC_MSC_MD1_SBC_EN)

#endif

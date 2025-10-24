/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef XFLATTEST_H_
#define XFLATTEST_H_

#define XFLATTEST_CMD_SET_SEC_DATA	0
#define XFLATTEST_CMD_GET_SEC_DATA	1
#define XFLATTEST_CMD_GET_RPMB_SECTOR	2
#define XFLATTEST_CMD_SET_RPMB_SECTOR	3
#define XFLATTEST_CMD_CLR_RPMB_SECTOR	4
#define XFLATTEST_CMD_LOCK_RPMB		5
/*Set and get raw sec data is used for xfl and no SW fuse is checked or blown */
#define XFLATTEST_CMD_SET_XFL_SEC_DATA	6
#define XFLATTEST_CMD_GET_RAW_SEC_DATA	7
#define XFLATTEST_CMD_READ_FUSE_DATA	8
#define XFLATTEST_CMD_READ_SUID		9

#define RAW_SECDATA_INDEX		0
#define RAW_XFL_SECDATA_INDEX		1

#define PROTOCOL_VERSION_SEC_DATA 0x01000000
/*Added keystore_hash to sec_data in version 2 */
#define PROTOCOL_VERSION_2_SEC_DATA 0x01100000
/*Added avb_version and rollback_counter to sec_data in version 3 */
#define PROTOCOL_VERSION_3_SEC_DATA 0x01110000
/* Added keystore_hash_sha256 and has_been_unlocked to sec_data in version 4 */
#define PROTOCOL_VERSION_4_SEC_DATA 0xDADA0004

#define PROTOCOL_VERSION_XFL_SEC_DATA 0xBABE0001
/* Added has_been_unlocked to xfl_sec_data in version 2 */
#define PROTOCOL_VERSION_2_XFL_SEC_DATA 0xBABE0002

#define MAX_PHONE_ID_LENGTH 8
#define MAX_DEVICE_KEY 16
#define MAX_HWCONF_REV_LENGTH 32
#define KEYSTORE_HASH_LENGTH 20
#define KEYSTORE_SHA256_LENGTH 32

#define SW_DEV_SECURITY_ON  0
#define SW_DEV_SECURITY_OFF 0x2000

#define XFLATTEST_NONCE_LEN 20

#define XFLATTEST_INVALID_RPMB_COUNTER 0xffffffff

#define XFLATTEST_MAX_NUM_OF_RB_INDEX 32
#define VERIFIED_BOOT_V1 1
#define VERIFIED_BOOT_V2 2

// specific define for struct ipc_sec_data
#define IPC_SEC_VERSION_V1 1
#define HUK_LENGTH 80

#define HAS_BEEN_UNLOCKED_MAGIC 0x6B636F6C

struct xflattest_cmd {
	uint32_t cmd_id;
	uint32_t payload_len;
} __attribute__ ((packed));

struct xflattest_rsp {
	int32_t result;
	uint32_t payload_len;
} __attribute__ ((packed));

/*Index specifies which raw data to get, secdata or xflsecdata*/
struct get_raw_data_cmd {
	uint32_t index;
} __attribute__ ((packed));

int get_xflattest_data(uint8_t *data);

/*
 * protocol_version		The protocol version.
 *
 * os_version			OS version extracted from Android boot image
 *				header.
 *
 * xcs_root			TRUE if XCS_ROT, FALSE if SONY_ROT.
 *
 * sw_dev_security_state	Software development security state.
 *				SW_DEV_SECURITY_ON if security is ON.
 *				SW_DEV_SECURITY_OFF if security is OFF.
 *
 * phoneid			First IMEI, 14 BCD digits, last byte not used.
 *
 * dk				Device key, combined (xor) from HW Config and
 *				TA unit.
 *
 * bl_unlock_status		Bootloader unlock status. Can be one of the
 *				following:
 *				BOOT_NOT_UNLOCKABLE
 *				BOOT_UNLOCKABLE
 *				BOOT_UNLOCKED
 *				BOOT_UNLOCKABLE_SIMLOCK_LOCKED
 *				BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED
 *
 * keystore_hash		SHA1 over the keystore payload in case there is
 *				a valid keystore in the device.
 *
 * avb_version			Android verified boot version
 *
 * rollback_counter		Verified boot v2 rollback counters. The data is
 *				valid only if avb_version = VERIFIED_BOOT_V2
 *
 * keystore_hash_sha256		SHA256 over the keystore payload in case there
 *				is a valid keystore in the device.
 *
 * has_been_unlocked		HAS_BEEN_UNLOCKED_MAGIC if bootloader has ever
 *				been unlocked.
 */
struct sec_data {
	uint32_t protocol_version;
	uint32_t os_version;
	uint32_t xcs_rot;
	uint32_t sw_dev_security_state;
	uint8_t  phoneid[MAX_PHONE_ID_LENGTH];
	uint8_t  dk[MAX_DEVICE_KEY];
	uint8_t  bl_unlock_status;
	uint8_t  hwconf_rev[MAX_HWCONF_REV_LENGTH];
	uint8_t  hwconf_rev_length;
	uint8_t  keystore_hash[KEYSTORE_HASH_LENGTH];
	uint32_t avb_version;
	uint64_t rollback_counter[XFLATTEST_MAX_NUM_OF_RB_INDEX];
	uint8_t  keystore_hash_sha256[KEYSTORE_SHA256_LENGTH];
	uint32_t has_been_unlocked;
} __attribute__ ((packed));

/*
 * version		version of the structure.
 *
 * xfl_data		security data "as is". user should check protocol_version
 *				before parse and extract the data.
 *
 * shared_huk	hardware unique key that could be shared between tz apps.
 */
struct ipc_sec_data {
	uint8_t version;
	struct sec_data xfl_data;
	uint8_t shared_huk[HUK_LENGTH];
} __attribute__ ((packed));

/*Used internally by xfl loader*/
struct xfl_sec_data {
	uint32_t version;
	uint8_t  bl_unlock_status;
	uint32_t rpmb_ks_counter;
	uint32_t xcs_rot;
	uint8_t  sake_nonce[XFLATTEST_NONCE_LEN];
	uint8_t  keystore_hash_sha256[KEYSTORE_SHA256_LENGTH];
	uint64_t rollback_counter[XFLATTEST_MAX_NUM_OF_RB_INDEX];
	uint32_t has_been_unlocked;
} __attribute__ ((packed));

struct rpmb_msg {
	uint32_t sector;
} __attribute__ ((packed));
#endif

/*
 * Copyright 2016,2021,2022 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
/**
 * @defgroup xboot_glue Sony XBoot support functions
 * @{
 * @brief Interface to set up and take generic xperia decisions for the boot
 *
 * During intialization the security settings and keystore is loaded and
 * verified.
 *
 * This interface defines the API for making Xperia related decisions for the
 * boot.
 * Example of such decisions are whether fastboot operations are allowed, or
 * if the boot should enter service mode.
 *
 * It also provides the API to iterate through both embedded root certificates
 * and certificates stored in keystore.
 *
 * The functionality relies on the following support from integration:
 * - Implementation of PAL interface
 * - MiscTA library
 * - Crypto functionality
 * - Fuse config (is_fused/die_id)
 * - Heap
 *
 * Detailed information on the integration is found in doc/integration/boot.txt.
 *
 * @file xboot_glue.h
 */
#ifndef XBOOT_GLUE_H_
#define XBOOT_GLUE_H_

#include "rule_types.h"

struct xboot_ctx;

/**
 * @brief List of the different possible boot images.
 *
 * Boot modes handled by xboot interface
 */
/* Normal image (usually a kernel) */
#define XBOOT_BOOT_DEFAULT_MODE				0
/* Sony service (usually customized bootstage) */
#define XBOOT_BOOT_SONY_SERVICE_MODE			3
/* Fastboot (usually customized bootstage) */
#define XBOOT_BOOT_FASTBOOT_MODE			4
/* Recovery image (usually a kernel) */
#define XBOOT_BOOT_RECOVERY_MODE			5
/* Ramdumper */
#define XBOOT_BOOT_DUMPER_MODE				6
/* FOTA */
#define XBOOT_BOOT_FOTA_MODE				7
/* Initial value */
#define XBOOT_BOOT_INVALID_MODE				100

/**
 * @brief Init Xperia Boot context.
 *
 * This function will create and populate the boot context by reading
 * and verifying HW Config and KeyStore. The KeyStore state will be
 * updated if a new KeyStore is present.
 *
 * @param[out] ctx            Created XBoot context.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_init(struct xboot_ctx **ctx);

/**
 * @brief Get RPMB keystore counter.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 *
 * @param[in]  ctx         XBoot context.
 * @param[out] counter     Counter value.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_ks_counter(struct xboot_ctx *ctx, unsigned int *counter);

/**
 * @brief Check if keystore is XCS rooted.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 *
 * @param[in]  ctx         XBoot context.
 * @param[out] is_xcs_rot  0 => not XCS, else is XCS.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_ks_is_xcs_rot(struct xboot_ctx *ctx, unsigned int *is_xcs_rot);

/**
 * @brief Check if XCS flag in secure storage is set.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 *
 * @param[in]  ctx         XBoot context.
 * @param[out] is_xcs_set  0 => XCS not set, else XCS is set.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_sec_stor_xcs_rot(struct xboot_ctx *ctx, uint32_t *is_xcs_set);

/**
 * @brief Get Die ID.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[out] id       Pointer to Die ID buffer.
 * @param[out] len      Length of Die ID.
 *
 * @returns Die ID buffer for success, else NULL.
 */
int xboot_get_die_id(unsigned char **id, unsigned int *len);

/**
 * @brief Fetch rooting status from SimLock.
 *
 * Unlock Status values are defined in fcs_defines.h
 * RCK (Rooting Control Key) is read from simlock and converted to binary.
 * The size of rck_h buffer must at least be 32 bytes and allocated by caller.
 *
 *
 * @param [out] unlock_status             Ptr to variable with rooting status.
 * @param [out] rck_h                     Ptr to buffer with the rck hash.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_simlock_unlock_data(unsigned char *unlock_status,
				unsigned char *rck_h);

/**
 * @brief Verify rck.
 *
 * Calculate the hash of a given rck (Rooting Control Key), and compare
 * it to a precalculated hash value.
 * The size of rck_h_sl should be 32 bytes.
 *
 *
 * @param [in] rck_h_sl      Precalculated rck hash value.
 * @param [in] rck_fb        rck in ascii format.
 * @param [in] rck_fb_len    Length of rck_ascii.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_compare_rck(unsigned char *rck_h_sl,
		const unsigned char *rck_fb,
		unsigned int rck_fb_len);

/**
 * @brief Google unlock allowed.
 *
 *
 * @param[out] allow_unlock 1 if bootloader unlock is allowed,
 *                          0 if bootloader unlock is not allowed.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_google_allow_unlock(unsigned char *allow_unlock);

/**
 * @brief Delete DK in MiscTA.
 *
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_delete_dk(void);


/** @brief Get number of public keys for usage
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * @param[in]  ctx   XBoot context.
 * @param[in]  usage Usage of public key.
 * @param[out] count Number of public keys.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_pub_key_count(struct xboot_ctx *ctx,
		unsigned int usage, unsigned int *count);

/**
 * @brief Get number of root certs for usage.
 *
 * It is required that the #xboot_init has executed successfully.
 * The caller should provide the expected usage of the root cert.
 * Available usages are defined in file "rule_types.h".
 *
 *
 * @param[in]  ctx     XBoot context.
 * @param[in]  usage   Usage of root cert.
 * @param[out] count   Number of certs.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_signer_cert_count(struct xboot_ctx *ctx,
		unsigned int usage, unsigned int *count);


/**
 * @brief Get public key for usage at index.
 *
 * It is required that the #xboot_init and #xboot_get_pub_key_count
 * have executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer.
 *
 * @param[in]  ctx     XBoot context.
 * @param[in]  usage   Usage of public key.
 * @param[in]  index   Index of public key.
 * @param[out] pub_key Returned public key.
 * @param[out] len     Length of public key.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_pub_key(struct xboot_ctx *ctx,
		unsigned int usage,
		unsigned int index,
		const unsigned char **pub_key,
		unsigned int *len);

/**
 * @brief Get root cert for usage at index.
 *
 * It is required that the #xboot_init and #xboot_get_signer_cert_count
 * has executed successfully.
 * The caller should provide the expected usage of the root cert.
 * Available usages are defined in file "rule_types.h".
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  ctx     XBoot context.
 * @param[in]  usage   Usage of root cert.
 * @param[in]  index   Index of root cert.
 * @param[out] cert    Returned cert buffer.
 * @param[out] len     Length of cert buffer.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_signer_cert(struct xboot_ctx *ctx,
		unsigned int usage, unsigned int index,
		const unsigned char **cert, unsigned int *len);

/**
 * @brief Check OEM Unlock flag request.
 *
 * Check if the bootloader OEM Unlock flag request is present
 * and if it is a valid CMS signed message set the OEM Unlock flag.
 * It is required that the #xboot_init has executed successfully.
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns #FCSERR_OK for valid OEM unlock flag request.
 */
int xboot_check_auto_set_oem_unlock(struct xboot_ctx *ctx);

/**
 * @brief Check auth command requests.
 *
 * Check whether the xfl has any commands to be executed by the boot and if
 * so execute such.
 * It is required that the #xboot_init has executed successfully.
 *
 * @param[in] ctx	XBoot context.
 *
 * @returns #FCSERR_OK if execution of cmd is ok.
 */
int xboot_check_auth_cmd(struct xboot_ctx *ctx);

/** @brief Generate auth channel nonce.
 *
 * Generate the authentication channel nonce.
 * It is required that the #xboot_init and #xboot_make_decisions have executed
 * successfully.
 *
 * @param[in] ctx	XBoot context.
 *
 * @returns #FCSERR_OK for success.
 */
int xboot_gen_auth_ch_nonce(struct xboot_ctx *ctx);

/**
 * @brief Get auth command nonce.
 *
 * Get the authenticated channel nonce. It is required that
 * #xboot_check_auth_cmd has executed successfully and the device boot mode is
 * set to SW service to get a valid nonce.
 *
 * @param[out] nonce	20 byte nonce
 *
 * @returns #FCSERR_OK if execution of cmd is ok.
 */
int xboot_get_auth_ch_nonce(uint8_t *nonce);

/**
 * @brief Return first Phone ID.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  ctx      XBoot context.
 * @param[out] len      Length of Phone ID.
 *
 * @returns Phone ID buffer for success, else NULL.
 */
unsigned char *xboot_get_phoneid(struct xboot_ctx *ctx, unsigned int *len);

/**
 * @brief Return second Phone ID.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  ctx      XBoot context.
 * @param[out] len      Length of Phone ID.
 *
 * @returns Phone ID buffer for success, else NULL.
 */
unsigned char *xboot_get_second_phoneid(struct xboot_ctx *ctx,
		unsigned int *len);

/**
 * @brief Return Phone ID counter.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * NOTE: Max Phone ID counter is MAX_PHONEID_COUNT,
 * which defined in file 'sony_boot_context.h'
 *
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns Phone ID counter for success, else 0.
 */
uint8_t xboot_get_phoneid_count(struct xboot_ctx *ctx);

/**
 * @brief Return device key (DK).
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  ctx      XBoot context.
 * @param[out] len      Length of device key.
 *
 * @returns DK buffer for success, else NULL.
 */
unsigned char *xboot_get_devicekey(struct xboot_ctx *ctx, unsigned int *len);

/**
 * @brief Is is_prototype in HWConfig set.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns true if prototype, else false.
 */
int xboot_is_prototype(struct xboot_ctx *ctx);

/**
 * @brief Return hwconf revision field.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  ctx      XBoot context.
 * @param[out] len      Length of revision field.
 *
 * @returns revision buffer for success, else NULL.
 */
unsigned char *xboot_get_hwconf_rev(struct xboot_ctx *ctx,
	unsigned int *len);

/**
 * @brief Take XBoot related decisions and return them.
 *
 * It is required that the #xboot_init has executed successfully.
 *
 * Reset detection, service mode detection and XBoot specific startup
 * indications are all managed by this function.
 *
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_make_decisions(struct xboot_ctx *ctx);

/**
 * @brief Return xboot additions to kernel commandline.
 *
 * It is required that the #xboot_init and #xboot_make_decisions
 * has executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns null terminated string for success, else NULL.
 */
char *xboot_get_cmdline_additions(struct xboot_ctx *ctx);

/**
 * @brief Return xboot additions to kernel commandline v2.
 *
 * It is required that the #xboot_init and #xboot_make_decisions
 * has executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns null terminated string for success, else NULL.
 */
char *xboot_get_cmdline_additions_v2(struct xboot_ctx *ctx);

/**
 * @brief Return the xboot configuration for backlight.
 *
 * It is required that the #xboot_init and #xboot_make_decisions
 * has executed successfully.
 *
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns 0 if backlight is configured OFF. A non zero value is returned
 * if backlight is configured to be ON.
 */
int xboot_is_backlight_enable(struct xboot_ctx *ctx);

/**
 * @brief Return the boot mode.
 *
 * It is required that the #xboot_init and #xboot_make_decisions
 * has executed successfully.
 *
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns boot mode for success, else #XBOOT_BOOT_INVALID_MODE.
 */
unsigned int xboot_get_boot_mode(struct xboot_ctx *ctx);

/**
 * @brief Return when long press management is finalised or shuts down.
 *
 * This function should be called before the boot leaves the current runtime
 * environment in order to ensure that all startup indications have finished
 * processing.
 *
 *
 * @param[in] ctx      XBoot context.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_finalize_longpress(struct xboot_ctx *ctx);

/**
 * @brief Read anti-rollback counters
 *
 * This function should be called to read anti-rollback counters from
 * VB-meta.
 *
 *
 * @param[out] cnt_buf  Buffer containing anti-rollback counters.
 * @param[in] vector_size   Number of counter elements in the buffer.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_rollback_counters(uint64_t *cnt_buf, uint32_t vector_size);

/**
 * @brief Reset rollback counters in secure storage.
 *
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_reset_rollback_counters(void);

/**
 * @brief Get Android verified boot version.
 *
 *
 * @returns AVB version.
 */
int xboot_get_avb_version(void);

/**
 * @brief Unlock the bootloader. Prior to unlocking the bootloader, all other
 * necessary operations, like erasing userdata, clearing rollback counters etc,
 * are executed.
 *
 * @param[in] rck_hash   Buffer containing the RCK hash.
 * @param[in] rck        Buffer containing the RCK to be checked.
 * @param[in] rck_len    Size of the rck buffer.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_unlock_bootloader(uint8_t *rck_hash, uint8_t *rck, uint8_t rck_len);

/**
 * @brief Lock the bootloader. Prior to locking the bootloader, all other
 * necessary operations, like erasing userdata, clearing rollback counters etc,
 * are executed.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_lock_bootloader(void);

/**
 * @brief Returns random generated number.
 *
 * There is no entropy source used in this function, so the additional buffer
 * is a requirement.
 *
 * @param[out] buf Buffer to be filled with the rng.
 * @param[in]  additional Additional data to be updated by mbedtls drbg
 *             functions. This should be some platform generated random number.
 * @param[in]  len The length of the output buffer.
 *
 * @returns #FCSERR_OK on success, otherwise an error has occurred.
 */
int xboot_rng(uint8_t *buf, char *additional, uint16_t len);

/**
 * @brief Returns pointer of taCommandLineArgs
 *
 * This function returns pointer of taCommandLineArgs that member of xboot_ctx
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns pointer of taCommandLineArgs
 */
char *xboot_bootconfig_get_taCommandLine(struct xboot_ctx *ctx);

/**
 * @brief Returns pointer of taCustomerId
 *
 * This function returns pointer of taCustomerId that member of xboot_ctx
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns pointer of taCommandLineArgs
 */
char *xboot_bootconfig_get_taCustomerId(struct xboot_ctx *ctx);

/**
 * @brief clear taCustomerId
 *
 * Clear and Free taCustomerId that member of xboot_ctx
 *
 * @param[in]  ctx      XBoot context.
 */
void xboot_bootconfig_clear_taCustomerId(struct xboot_ctx *ctx);

/**
 * @brief Returns pointer of taColorId
 *
 * This function returns pointer of taColorId that member of xboot_ctx
 *
 * @param[in]  ctx      XBoot context.
 *
 * @returns pointer of taCommandLineArgs
 */
char *xboot_bootconfig_get_taColorId(struct xboot_ctx *ctx);

/**
 * @brief clear taColorId
 *
 * Clear and Free taColorId that member of xboot_ctx
 *
 * @param[in]  ctx      XBoot context.
 */
void xboot_bootconfig_clear_taColorId(struct xboot_ctx *ctx);
#endif
/** @}*/

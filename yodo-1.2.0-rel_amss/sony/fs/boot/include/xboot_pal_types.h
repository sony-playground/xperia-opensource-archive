/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
/**
 * @ingroup xboot_lib
 * @{
 * @file xboot_pal_types.h
 * @}
 */
#ifndef INCLUSION_GUARD_XBOOT_PAL_TYPES
#define INCLUSION_GUARD_XBOOT_PAL_TYPES

#include <stdbool.h>
#include <stdint.h>
#include "fcserr.h"


/**
 * @defgroup xboot_pal_misc Miscellaneous PAL types
 * @ingroup xboot_lib
 * @brief Miscellaneous platform specific functionality
 *
 * Here are placed the platform specific functionality that does not clearly
 * fall into any of the defined groups.
 * @{
 */
/**
 * @brief RGB LED control options
 *
 * White light should be emitted if all three colors are turned on.
 * Because of this, it is needed to first call the function to turn off all
 * colors when enabling a single color to avoid mixing colors unintentionally.
 */
enum xbpal_rgb_led_cfg_t {
	/* Red light, used for USB cable indication */
	XBPAL_LED_TURN_ON_RED = 0,

	/* Green light, used for Sony service */
	XBPAL_LED_TURN_ON_GREEN = 1,

	/* Blue light,  used for fastboot service */
	XBPAL_LED_TURN_ON_BLUE = 2,

	/* Turn off RGB LED */
	XBPAL_LED_TURN_OFF = 3,

	XBPAL_LED_TURN_INVALID = 0xFFFFFFFF
};

/**
 * @brief JTAG control options
 */
enum xbpal_jtag_cfg_t {
	/* No JTAG access should be enabled */
	XBPAL_JTAG_OFF = 0,

	/* Enable JTAG access for public-domain subsystems */
	XBPAL_JTAG_ON = 1,

	/* Enable JTAG access for all accessible subsystems */
	XBPAL_JTAG_ON_SECURE = 2,

	XBPAL_JTAG_INVALID = 0xFFFFFFFF
};

/**
 * @brief List of different shutdown reasons
 *
 * If bootlib call shutdown it will provide a reason to why it did.
 */

enum xbpal_shutdown_reason_t {
	/* Unspecified reason */
	XBPAL_SHUTDOWN_REASON_OTHER = 0,

	/* Verification failure */
	XBPAL_SHUTDOWN_REASON_VERIFICATION = 1,

	XBPAL_SHUTDOWN_REASON_INVALID = 0xFFFFFFFF
};

/** @} */

/**
 * @defgroup xboot_pal_gpio GPIO related PAL types
 * @ingroup xboot_lib
 * @brief GPIO related platform specific functionality
 *
 * The @c chip argument specifiy which ASIC to configure.
 * Chip 0 is always the main digital baseband.
 * Chip 1 is always the main analog baseband.
 * Chip 2 may be a secondary baseband or GPIO extender, and so on.
 * The primary user inside the xboot library for the secondary ASICS is the
 * boot config parser, so the definition of additional chip IDs must map to the
 * boot configuration.
 * @{
 */

/**
 * @brief GPIO direction
 *
 * Specifies which direction the selected GPIO should be configured to use.
 */
enum xbpal_gpio_dir_t {
	/* GPIO is output */
	XBPAL_GPIO_OUT = 0,

	/* GPIO is input */
	XBPAL_GPIO_IN = 1,

	/* GPIO is both input and output */
	XBPAL_GPIO_BOTH = 2,

	/* GPIO is disabled */

	XBPAL_GPIO_OFF = 3,
	XBPAL_GPIO_DIR_INVALID = 0xFFFFFFFF
};

/**
 * @brief GPIO function
 *
 * Specifies which function the selected GPIO should be configured to use.
 */
enum xbpal_gpio_func_t {
	/* GPIO uses default function */
	XBPAL_GPIO_PRIMARY = 0,

	/* GPIO uses alternative function 2 */
	XBPAL_GPIO_ALTERNATE_SECOND = 1,

	/* GPIO uses alternative function 3 */
	XBPAL_GPIO_ALTERNATE_THIRD = 2,

	/* GPIO uses alternative function 4 */
	XBPAL_GPIO_ALTERNATE_FOURTH = 3,

	XBPAL_GPIO_FUNC_INVALID = 0xFFFFFFFF
};

/**
 * @brief GPIO pull configuration
 *
 * Specifies which type of pull the selected GPIO should be configured to use.
 */
enum xbpal_gpio_pull_t {
	/* GPIO is configured with pull-down */
	XBPAL_GPIO_PULLDOWN = 0,

	/* GPIO is configured with pull-up */
	XBPAL_GPIO_PULLUP = 1,

	/* GPIO is configured with pulls disabled */
	XBPAL_GPIO_PULLDISABLE = 2,

	/* GPIO is configured as a three-state pin */
	XBPAL_GPIO_OPENDRAIN = 3,

	XBPAL_GPIO_PULL_INVALID = 0xFFFFFFFF
};

/**
 * @brief GPIO special function pull configuration
 *
 * Specifies which type of pull the selected GPIO should be configured to use
 * when the GPIO is not configured for primary/default function.
 */
enum xbpal_gpio_alt_pull_t {
	/* Pulls are enabled */
	XBPAL_GPIO_ALTPULL_ENABLE = 0,

	/* Pulls are disabled */
	XBPAL_GPIO_ALTPULL_DISABLE = 1,

	XBPAL_GPIO_ALTPULL_INVALID = 0xFFFFFFFF
};

/**
 * @brief GPIO drive strength configuration
 *
 * Specifies the strength of the drive-capabilities of the selected GPIO.
 * The exact strength of the drive is specific to the platform.
 */
enum xbpal_gpio_drive_t {
	/* GPIO uses high drive strength */
	XBPAL_GPIO_DRIVE_HIGH = 0,

	/* GPIO uses medium drive strength */
	XBPAL_GPIO_DRIVE_MEDIUM = 1,

	/* GPIO uses low drive strength */
	XBPAL_GPIO_DRIVE_LOW = 2,

	XBPAL_GPIO_DRIVE_INVALID = 0xFFFFFFFF
};

/**
 * @brief GPIO configurations
 *
 * Collects all the different configuration parameters of a GPIO pin in a
 * single structure.
 */
struct xbpal_gpio_cfg {
	/* GPIO direction */
	enum xbpal_gpio_dir_t      direction;

	/* GPIO function */
	enum xbpal_gpio_func_t     function;

	/* GPIO pull configuration */
	enum xbpal_gpio_pull_t     pullUpOrDown;

	/* GPIO alternate function pull mode */
	enum xbpal_gpio_alt_pull_t altFuncPullMode;

	/* GPIO drive strength */
	enum xbpal_gpio_drive_t    driveStrength;
};

/** @} */

/**
 * @defgroup xboot_pal_warmboot Warmboot related PAL types
 * @ingroup xboot_lib
 * @brief Warmboot related platform specific functionality
 *
 * The warmboot functions provide support for manipulating warmboot reasons
 * and magics as well as rebooting the platform into different modes.
 * The effect the warmboot reason has on the bootflow is described below:
 * @dotfile warmboot.dot "Warmboot detection flow"
 * @{
 */

/* Platform independent flags (all platforms should support these) */
/* Power on key */
#define XBPAL_STARTUP_MASK_ONKEY    0x00000001

/* Main watchdog (considered crash) */
#define XBPAL_STARTUP_MASK_WATCHDOG 0x00000002

/* USB cable insertion */
#define XBPAL_STARTUP_MASK_VBUS     0x00000004

/*
 * Platform specific flags (some platforms may support these,
 * the onse who don't should leave them cleared)
 */
/* Sudden moment power loss (QC) */
#define XBPAL_STARTUP_MASK_SMPL        0x00001000

/* Real time clock alarm (QC+MTK) */
#define XBPAL_STARTUP_MASK_RTC         0x00002000

/* Wall charger attached (QC+MTK) */
#define XBPAL_STARTUP_MASK_WALLCHARGER 0x00004000

/* Hard reset asserted (QC) */
#define XBPAL_STARTUP_MASK_HARD_RESET  0x00008000

/* Power lock (QC) */
#define XBPAL_STARTUP_MASK_POWERLOCK   0x00010000

/* Startup by wdt (MTK) */
#define XBPAL_STARTUP_MASK_WATCHDOG_BYPASS_PWK 0x00020000

/* Startup by tool (MTK) */
#define XBPAL_STARTUP_MASK_TOOL_BYPASS_PWK     0x00040000

/* Platform specific flags that trigger crashdumper */
/* Platform specific wdog 1 */
#define XBPAL_STARTUP_MASK_PLF_WATCHDOG_1 0x01000000

/* Platform specific wdog 2 */
#define XBPAL_STARTUP_MASK_PLF_WATCHDOG_2 0x02000000

/* Platform specific wdog 3 */
#define XBPAL_STARTUP_MASK_PLF_WATCHDOG_3 0x04000000

/* Mask to identify all bits that trigger crashdumper */
/* All bits that trigger dumper */
#define XBPAL_STARTUP_MASK_PLF_CRASHES 0xFF000002

/**
 * @brief Warmboot reasons we care about
 */
enum xbpal_warmboot_t {
	/* Cleared reason (uncontrolled restart) */
	XBPAL_WB_CLEAR = 0,

	/* Indicate cold boot */
	XBPAL_WB_NONE = 1,

	/* Sony service */
	XBPAL_WB_SONY_SVC = 2,

	/* Fastboot service */
	XBPAL_WB_FB_SVC = 3,

	/* FOTA boot */
	XBPAL_WB_FOTA = 4,

	/* FOTA PIN cache boot, used during override */
	XBPAL_WB_FOTA_CACHE = 5,

	/* Normal boot */
	XBPAL_WB_NORMAL = 6,

	/* System crash */
	XBPAL_WB_CRASH = 7,

	/* System crash without dumper */
	XBPAL_WB_CRASH_ND = 8,

	/* Recovery service */
	XBPAL_WB_RECOVERY = 9,

	/* Unknown warmbot reason */
	XBPAL_WB_OTHER = 10,

	/* Service mode override reason */
	XBPAL_WB_SYSTEM = 11,

	/* Crash during FOTA update */
	XBPAL_WB_FOTA_CRASH = 12,

	/* Verified boot EIO mode */
	XBPAL_WB_DMV_EIO = 13,

	/* Verified boot Enforce mode */
	XBPAL_WB_DMV_ENFORCE = 14,

	/* Verified boot EIO mode */
	XBPAL_WB_DMV_KEYCLEAR = 15,

	/* Ramdumper successfully done */
	XBPAL_WB_RD_OK = 16,

	/* Ramdumper decryption failure 1 */
	XBPAL_WB_RD_DECFAIL_NO_TL = 17,

	/* Ramdumper decryption failure 2 */
	XBPAL_WB_RD_DECFAIL_PART_TL = 18,

	/* Ramdumper too early HWWD */
	XBPAL_WB_RD_CRASH_EARLY_HWWD = 19,

	/* Ramdumper HWWD */
	XBPAL_WB_RD_CRASH_LATE_HWWD = 20,

	/* Ramdumper NO free space to store tlcore */
	XBPAL_WB_RD_NO_SPACE = 21,

	/* Ramdumper kernel panic */
	XBPAL_WB_REBOOT_RD_CRASH = 22,

	/* Ramdumper application failure */
	XBPAL_WB_REBOOT_RD_APPERR = 23,

	/* HWWD during FOTA update */
	XBPAL_WB_FOTA_HWWD = 24,

	XBPAL_WB_INVALID = 0xFFFFFFFF
};

/**
 *  @brief USB OTG RID state
 */
enum xbpal_ServiceOtgRid_t {
	/* OTG ACA RID state A */
	XBPAL_SERVICE_OTG_TYPE_RID_A = 0,

	/* OTG ACA RID state B */
	XBPAL_SERVICE_OTG_TYPE_RID_B = 1,

	/* OTG ACA RID state C */
	XBPAL_SERVICE_OTG_TYPE_RID_C = 2
};

/**
 * Platform Abstract Layer Functions
 *
 * These functions must be defined in the platform
 */

/**
 * @brief Return pin value
 *
 * @param[in] chip The subsystem for the pin (DBB/PMIC/etc).
 * @param[in] pin The pin to read.
 * @param[out] state Buffer to store the state of the pin in
 *                   (@c '1' or @c '0').
 *                   Buffer supplied by caller.
 *
 * @returns FCSERR_OK if pin was successfully read.
 *
 * @par Consequence if not implemented:
 * Parts of the bootconfig that uses GPIO pin triggers (service mode,
 * reset, etc) will not work as expected.
 */
int xbpal_gpio_get_pin(uint8_t chip, uint32_t pin, uint8_t *state);

/**
 * @brief Perform a complete configuration for given pin
 *
 * @param[in] chip The subsystem for the pin (DBB/PMIC/etc).
 * @param[in] pin The pin to configure.
 * @param[in] cfg Buffer with the configuration to apply.
 *
 * @returns FCSERR_OK if configuration was successfully
 * set.
 *
 * @par Consequence if not implemented:
 * Parts of the bootconfig that uses GPIO pin triggers will not work as
 * expected.
 */
int xbpal_gpio_set_config(
		uint8_t chip, uint32_t pin, struct xbpal_gpio_cfg *cfg);

/**
 * @brief Return elapsed time in ms since power on/reset
 *
 * @returns the amount of ms spent since boot entry.
 *
 * @par Consequence if not implemented:
 * The library might not get reasonable precision when processing the
 * longpress timeout as defined by the boot configuration (MiscTA unit
 * #TA_SONY_BOOT_CONFIGURATION_UNIT).
 */
uint32_t xbpal_get_boot_time(void);

/**
 * @brief Register timer callback and start timer
 *
 * Start a timer and call the provided function once the supplied
 * timeout expires.
 * If the timeout expires, the callback will be called and then
 * de-registered.
 *
 * @param[in] ctx Timer context.
 * @param[in] sony_timer_cb The function to call once the timeout has
 * expired.
 * @param[in] timeout The timeout in milliseconds.
 * @param[in] arg Argument pointer for callback.
 *
 * @returns FCSERR_OK if registration was successful.
 *
 * @par Consequence if not implemented:
 * The library will not be able to handle the timings for forced
 * reset/shutdown behavior.
 */
int xbpal_timer_register_cb(
	void **ctx, void (*xbpal_timer_cb)(void *arg), uint32_t timeout,
	void *arg);

/**
 * @brief Stop registered timer
 *
 * Stop the timer associated with the provided callback and de-register
 * the callback. This should not be necessary if the timer has expired.
 *
 * @param[in] ctx Timer context.
 *
 * @returns FCSERR_OK if de-registration was successful.
 *
 * @par Consequence if not implemented:
 * The library will not be able to handle the timings for forced
 * reset/shutdown behavior.
 */
int xbpal_timer_deregister_cb(void *timer_context);

/**
 * @brief Halt execution for the specified number of microseconds
 *
 * @param[in] time_us The time to halt in microseconds.
 *
 * @par Consequence if not implemented:
 * The library will not be able to inject delays to securely handle HW
 * interfaces such as GPIOs which on some target might cause incorrect
 * readings.
 */
void xbpal_delay_us(uint32_t time_us);

/**
 * @brief Read the platform startup reason bit field
 *
 * @returns The startup reason bits packed in a manner that complies to
 * the masks defined above.
 *
 * @par Consequence if not implemented:
 * The library will not be able to handle LED indication for USB cable,
 * ramdumper will only be booted using warmboot and longpress
 * management will not be activated since library will not be able to
 * determine that handset was started using onkey.
 */
uint32_t xbpal_get_startup_bits(void);

/**
 * @brief Read the stored warmboot reason
 *
 * The value will be cached so that this function will always return the
 * original warmboot reason even if the value is cleared using
 *
 * @returns The stored warmboot reason.
 *
 * @par Consequence if not implemented:
 * The library will not be able to determine warmboot reasons. This
 * will affect the ability to handle FOTA, ramdumper and the
 * possibility to schedule service modes from the phone software or
 * console (i.e. 'adb reboot bootloader').
 */
uint32_t xbpal_get_wb_reason(void);

/**
 * @brief Translate the provided warmboot reason
 *
 * @param[in] warmboot_raw The raw warmboot value.
 *
 * @returns The corresponding value for the supplied reason.
 *
 * @par Consequence if not implemented:
 * The library will not be able to determine warmboot reasons. This
 * will affect the ability to handle FOTA, ramdumper and the
 * possibility to schedule service modes from the phone software or
 * console (i.e. 'adb reboot bootloader').
 */
enum xbpal_warmboot_t xbpal_translate_wb_reason(uint32_t raw_reason);

/**
 * @brief Write a platform specific cleared reason
 *
 * @par Consequence if not implemented:
 * This is usually used to set the prepared wb reason to HWWD when
 * leaving the boot, to be able to launch crash dumper.
 */
void xbpal_clear_wb_reason(void);

/**
 * @brief Return VBUS state of USB block
 *
 * Only VBUS origniating from a computer host should be identified.
 * E.g. no charger-only cables should indicate VBUS valid.
 *
 * @returns @c true if VBUS is active.
 *
 * @par Consequence if not implemented:
 * The library will not be able to determine USB cable connectivity.
 * Cases where the library will issue a warmoot to enter service mode,
 * it will then instead shut down. All service detections that require
 * USB cable connected will be ignored.
 */
bool xbpal_usb_vbus_detect(void);

/**
 * @brief Return detected OTG RID state
 *
 * Returns the detected OTG RID state if the state is valid.
 *
 * @param[out] otg_state Buffer for the RID state of the USB tranciever.
 *                       Buffer supplied by caller.
 *
 * @returns @c true if a valid state is detected.
 *
 * @par Consequence if not implemented:
 * The library will not be able to determine service triggers from OTG ACA RID
 * state. Other trigger types remain unaffected if this function is not
 * implemented.
 */
bool xbpal_usb_otg_detect(enum xbpal_ServiceOtgRid_t *otg_state);

/**
 * @brief Return press state of power button
 *
 * @returns @c true if button is pressed.
 *
 * @par Consequence if not implemented:
 * The library will not be able to determine the state of the power
 * button. Service triggers that use the power button and longpress
 * management will not work.
 */
bool xbpal_pwr_button_pressed(void);

/**
 * @brief Return press state of reset button
 *
 * @returns @c true if button is pressed.
 *
 * @par Consequence if not implemented:
 * The library will not be able to determine the state of the reset
 * button. Service triggers that use the reset button and longpress
 * management will not work.
 */
bool xbpal_rst_button_pressed(void);

/**
 * @brief Return press state of keyboard button
 *
 * @param[in] row Row in the matrix of the key to scan.
 * @param[in] col Column in the matrix of the key to scan.
 *
 * @returns @c true if button is pressed.
 *
 * @par Consequence if not implemented:
 * The library will not be able to determine the status of keys
 * connected to a keyboard matrix. Other trigger types (including GPIO
 * based keys) remain unaffected if this function is not implemented.
 */
bool xbpal_kbd_button_pressed(uint8_t row, uint8_t col);

/**
 * @brief Do platform specific erase of user sensitive partitions
 *
 * @returns @c bool true if filesystems are successfully erased.
 * <b>Consequence if not implemented:</b> userdata & cache
 * will not be erased when bootloader is being locked/unlocked or when
 * a new xcs keystore is being applied.
 */
bool xbpal_erase_user_sensitive(void);

/**
 * @brief Get the size of the factory reset protection data.
 * @param[in/out] data_sz
 * @returns FCSERR_OK on success.
 * <b>Consequence if not implemented:</b> Auto set OEM Unlock flag
 * will not work.
 */
int xbpal_get_frp_data_size(uint32_t *data_sz);

/**
 * @brief Do platform specific read of partition used for Google
 * factory reset protection.
 * @param[in/out] data     Buffer for the frp data.
 *                         Buffer supplied by caller.
 * @param[in/out] data_sz  Size of the data buffer
 * @returns FCSERR_OK if read was successful.
 * <b>Consequence if not implemented:</b> Auto set OEM Unlock flag
 * will not work.
 */
int xbpal_read_frp_data(uint8_t *data, uint32_t data_sz);

/**
 * @brief Do platform specific reset detection
 *
 * @returns @c true if reset is detected.
 *
 * @par Consequence if not implemented:
 * Library will not be able to detect and enter its reset-flow that
 * provides user feedback for forced-reset.
 */
bool xbpal_reset_detect(void);

/**
 * @brief Control vibrator
 *
 * Implementor can decide how to handle a delayed actuation
 * (when_us > 0) in order to provide optimum bootup perfomance.
 * A synchronous implementation could potentially degrade bootup time
 * significantly.
 * An asynchronous implementation need to ensure thread safety to avoid
 * conflicts with other parts of the environment.
 *
 * @attention If when_us is greater than 0, vibration should only start
 * if power key is pressed.
 *
 * @param[in] when_us Delay in microseconds to wait before staring
 * vibration.
 * @param[in] duration_us Duration in microseconds of the vibration.
 *
 * @par Consequence if not implemented:
 * Library will not be able to provide tactile feedback to indicate
 * power on or reset behaviour.
 */
void xbpal_vibrate(uint32_t when_us, uint32_t duration_us);

/**
 * @brief Control RGB LED
 *
 * @param[in] cfg Configuration of RGB LED
 *
 * @returns @c true if operation succeeded.
 *
 * @par Consequence if not implemented:
 * Library will not be able to provide visible feedback to indicate
 * charging or service modes.
 */
bool xbpal_rgb_led_ctl(enum xbpal_rgb_led_cfg_t cfg);

/**
 * @brief Shut down the device
 *
 * @param[in] The reason for it being called.
 *
 * @returns will only return if unsuccessful.
 *
 * @par Consequence if not implemented:
 * Library will not be able to shutdown the device. If this function
 * returns or is not implemented, library will hang, and unless a
 * forced shutdown mechanism is used, will drain the device power
 * source.
 */
void xbpal_shutdown(enum xbpal_shutdown_reason_t reason);

/**
 * @brief Return version string
 *
 * @param[out] version_string NULL terminated string with version
 * information.
 *
 * @returns FCSERR_OK for success, else an error occurred.
 *
 * @par Consequence if not implemented:
 * No version information will be available.
 */
int xbpal_get_version_string(char **version_string);

/**
 * @brief Unlock the bootloader.
 *
 * @returns FCSERR_OK for success, else an error occurred.
 */
int xbpal_unlock_bootloader(void);

/**
 * @brief Lock the bootloader.
 *
 * @returns FCSERR_OK for success, else an error occurred.
 */
int xbpal_lock_bootloader(void);

/**
 * @brief Reset the VB meta anti-rollback counters
 *
 * @returns FCSERR_OK for success, else an error occurred.
 */
int xbpal_reset_vbmeta_counters(void);

/**
 * @brief Read the VB meta anti-rollback  counters
 *
 * @param[out] cnt_buf  Buffer containing anti-rollback counters.
 * @param[in] vector_size   Number of counter elements in the buffer.
 *
 * @returns FCSERR_OK for success, else an error occurred.
 */
int xbpal_read_vbmeta_counters(uint64_t *cnt_buf, uint32_t vector_size);

/**
 * @brief Get Android verified boot version.
 *
 * @returns AVB version.
 */
int xbpal_get_avb_version(void);

/**
 * @brief Read recovery message from misc partition.
 *
 * @returns true if there is a "boot-recovery" message in misc partition.
 */
bool xbpal_boot_into_recovery(void);





int xbpal_get_partition_size(uint64_t *size, uint16_t *pname);
int xbpal_get_block_size(uint32_t *BlockSize, uint16_t *pname);
int xbpal_reead_partition_chunk(void *ImageBuffer, uint32_t *ImageSize, uint16_t *pname, uint64_t offset);
int xbpal_get_battery_capacity(uint32_t *soc);
int xbpal_get_ufs_info(uint8_t* buf, uint16_t len);


void* xbpal_sha256_init(void);
void xbpal_sha256_update(void* ctx, const uint8_t* data, uint32_t len);
uint8_t* xbpal_sha256_final(void* ctx, uint32_t* len);
void xbpal_sha256_deinit(void* ctx);
void lock_ta_open();
void unlock_ta_open();
#endif /* INCLUSION_GUARD_XBOOT_PAL_TYPES */

/*
 * Copyright 2016,2021,2022 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#ifndef INCLUSION_GUARD_SONY_BOOT_CONTEXT
#define INCLUSION_GUARD_SONY_BOOT_CONTEXT

#include <stdint.h>
#include <stdbool.h>

#define PBA_SPACE_NR_MAX_SZ 13
#define PBA_SPACE_REV_MAX_SZ 7

#define MAX_PHONEID_COUNT 2

/**
 *  Service modes
 */
enum ServiceModeDetect_t {
	SERVICE_MODE_DETECT_NONE = 0,
	SERVICE_MODE_DETECT_USB_SONY = 2,
	SERVICE_MODE_DETECT_USB_FASTBOOT = 3,
	SERVICE_MODE_DETECT_RECOVERY = 4
};

/**
 *  Supported service triggers
 */
enum ServiceTriggerType_t {
	SERVICE_TRIGGER_KEYPAD = 1,
	SERVICE_TRIGGER_GPIO = 2,
	SERVICE_TRIGGER_GPIO_IN_PMIC = 3,
	SERVICE_TRIGGER_OTG = 4,
	SERVICE_TRIGGER_POWER_ON = 5,
	SERVICE_TRIGGER_GPIO_3 = 6,
	SERVICE_TRIGGER_RESET_ON = 7,
	SERVICE_TRIGGER_GPIO_IN_PM0 = 0x10,
	SERVICE_TRIGGER_GPIO_IN_PM1 = 0x11,
	SERVICE_TRIGGER_GPIO_IN_PM2 = 0x12,
	SERVICE_TRIGGER_GPIO_IN_PM3 = 0x13,
	SERVICE_TRIGGER_UNSUPPORTED = 0xFF
};

/**
 *  Supported service trigger policies
 */
enum ServiceTriggerPolicy_t {
	SERVICE_TRIGGER_STANDALONE = 0,
	SERVICE_TRIGGER_PART_OF = 1
};

#define SERVICE_TRIGGER_MASK   (0x7F)
#define SERVICE_TRIGGER_POLICY (0x80)

/**
 *  Service key data
 */
union ServiceTriggerData_t {
	struct {
		uint8_t row;
		uint8_t col;
	} keypad_data;

	struct {
		uint8_t pin_lsb;
		uint8_t pin_msb;
		uint8_t config;
	} gpio_data;

	struct {
		uint8_t pin_lsb;
		uint8_t pin_msb;
		uint8_t config;
	} pmic_gpio_data;

	struct {
		uint8_t pin_lsb;
		uint8_t pin_msb;
		uint8_t config;
	} gpio_3_data;

	struct {
		uint8_t rid_class;
	} usb_data;
};

/**
 *  Service key structure
 */
struct ServiceTrigger {
	enum ServiceTriggerType_t   svcTriggerType;
	enum ServiceTriggerPolicy_t svcTriggerPolicy;
	union ServiceTriggerData_t  svcTriggerData;
};

/**
 * @brief List of the different longpress states.
 *
 * Depending on the state of the longpress detection mechanism boot should, or
 * should not continue booting.
 */
enum longpress_state_t {
	LONG_PRESS_RUNNING = 0,	/* Timer has not expired yet */
	LONG_PRESS_FAILED = 1,	/* Timer exipired, longpress not OK */
	LONG_PRESS_OK = 2	/* Timer exipired, longpress OK */
};

/* Structure that hold information about configuration values that could be
 * overwritten by MiscTA unit TA_S1_BOOT_CONFIGURATION_UNIT.
 */
struct sony_boot_configuration {
	struct ServiceTrigger *ServiceKeys;
	uint8_t                 nofServiceKeys;
	struct ServiceTrigger *softServicePins;
	uint8_t                 nofSoftServicePins;
	struct ServiceTrigger *resetKeys;
	uint8_t                 nofResetKeys;
	struct ServiceTrigger *recoveryKeys;
	uint8_t                 nofRecoveryKeys;
	struct ServiceTrigger *fastbootKeys;
	uint8_t                 nofFastbootKeys;
	bool                    USB_Is_Enabled;
	bool                    disable_Service_Pin;
	bool                    disable_Sw_Svc;
	uint16_t                longPressTimeMS;
	bool                    FlaFlaOverride;
	uint16_t                resetTimeoutMS;
	uint8_t                 resetNofPulsesStart;
	uint16_t                resetStartPulseOnTimeMS;
	uint16_t                resetStartPulseOffTimeMS;
	uint8_t                 resetNofPulsesEnd;
	uint16_t                resetEndPulseOnTimeMS;
	uint16_t                resetEndPulseOffTimeMS;
	char                    *taCommandLineArgs; /* NULL terminated string */
	uint16_t                *vbus_pulse_array;
	bool                    backlightEnable;
	char                    *taCustomerId; /* NULL terminated string */
	char                    *taColorId; /* NULL terminated string */
};

/* Structure that hold information about override information */
struct sony_boot_override {
	uint32_t *startupBits;
	uint32_t *warmbootReason;
};

struct xboot_ctx {
	unsigned char *imei;
	unsigned int imei_len;
	unsigned char *imei2;
	unsigned int imei2_len;
	uint8_t imei_count;
	unsigned char *device_key;
	unsigned int device_key_len;
	int is_prototype;
	struct ks_ctx *ks;
	char *version_string;
	enum ServiceModeDetect_t curr_service_mode;
	bool shutdowntimer_tripped;
	enum longpress_state_t longpress_state;
	uint32_t warmboot_reason;
	uint32_t startup_flags;
	struct sony_boot_configuration *bootconfig;
	struct sony_boot_override override_data;
	void *timer_context;
	int boot_mode;
	/* Sony additions to kernel commandline */
	char *sony_cmdline_additions;
	char *sony_cmdline_additions_v2;
	/* backlight_enable makes it possible to turn on or off the backlight
	 * based on settings in bootconfig.
	 */
	bool backlight_enable;
};

#endif

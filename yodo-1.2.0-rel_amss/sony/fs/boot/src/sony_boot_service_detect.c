/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "sony_boot_service_detect.h"
#include "ta_interface.h"
#include "fcslog.h"

/**
 *  GPIO config bits in the bootconfig
 */
#define GPIO_CFG_ASSERT_STATE_MASK 0x01

#define GPIO_CFG_MUX_MASK          0x0E
#define GPIO_CFG_MUX_PRIMARY       0x00
#define GPIO_CFG_MUX_SECONDARY     0x02
#define GPIO_CFG_MUX_THIRD         0x04
#define GPIO_CFG_MUX_FOURTH        0x06

#define GPIO_CFG_PULL_MASK         0x30
#define GPIO_CFG_PULLDOWN          0x00
#define GPIO_CFG_PULLUP            0x10
#define GPIO_CFG_PULLOFF           0x20
#define GPIO_CFG_PULLOPENDRAIN     0x30

static bool trigger_detect(struct xboot_ctx *context,
	struct ServiceTrigger *triggerData, uint8_t nofTriggers);
static bool is_gpio_asserted(struct xboot_ctx *context, uint8_t chip,
	uint32_t pin, uint8_t cfg);
static bool reset_trigger_detect(struct xboot_ctx *context,
	struct ServiceTrigger *triggerData, uint8_t nofTriggers);
static void shutdowntimer_cb(void *arg);

int sony_boot_service_detect(
	struct xboot_ctx *context,
	const enum xbpal_warmboot_t warmboot_reason)
{
	if (!context || !context->bootconfig) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (warmboot_reason == XBPAL_WB_SYSTEM) {
		/* System warmboot reason overrides service mode in any case */
		context->curr_service_mode = SERVICE_MODE_DETECT_NONE;
		return FCSERR_OK;
	} else if (context->curr_service_mode != SERVICE_MODE_DETECT_NONE) {
		/* Service mode has already been determined */
		return FCSERR_OK;
	}

	context->curr_service_mode = SERVICE_MODE_DETECT_NONE;

	/* Sony service has the highest priority */

	/* Check triggers that will set SERVICE_MODE */
	if (!(context->bootconfig->disable_Service_Pin)) {
		if (trigger_detect(context, context->bootconfig->ServiceKeys,
			context->bootconfig->nofServiceKeys)) {
			FCS_LOG("SW service triggering key detected\n");
			/* A SW_SERVICE triggering key was pressed, also check
			 * if VBUS is valid, set SERVICE_MODE
			 */
			if (xbpal_usb_vbus_detect()) {
				context->curr_service_mode =
					SERVICE_MODE_DETECT_USB_SONY;
			} else {
				FCS_LOG("VBUS not detected\n");
			}
		}
	}

	/* If still no service mode detected,
	 * check other triggers
	 */
	if (context->curr_service_mode == SERVICE_MODE_DETECT_NONE &&
		!(context->bootconfig->disable_Sw_Svc)) {

		if (trigger_detect(context,
			context->bootconfig->softServicePins,
			context->bootconfig->nofSoftServicePins)) {

			FCS_LOG("SW service triggering pin detected\n");
			if (xbpal_usb_vbus_detect()) {
				context->curr_service_mode =
						SERVICE_MODE_DETECT_USB_SONY;
			} else {
				FCS_LOG("VBUS not detected\n");
			}
		}
	}

	/* Recovery service has lower priority */
	if (context->curr_service_mode == SERVICE_MODE_DETECT_NONE) {
		if (trigger_detect(context, context->bootconfig->recoveryKeys,
			context->bootconfig->nofRecoveryKeys)) {

			FCS_LOG("Recovery service trigger detected\n");
			context->curr_service_mode =
				SERVICE_MODE_DETECT_RECOVERY;
		}
	}

	/* Fastboot service has lower priority */
	if (context->curr_service_mode == SERVICE_MODE_DETECT_NONE) {
		if (trigger_detect(context, context->bootconfig->fastbootKeys,
			context->bootconfig->nofFastbootKeys)) {

			FCS_LOG("Fastboot service trigger detected\n");
			if (xbpal_usb_vbus_detect()) {
				context->curr_service_mode =
					SERVICE_MODE_DETECT_USB_FASTBOOT;
			} else {
				FCS_LOG("VBUS not detected\n");
			}
		}
	}

	/* If no service mode is triggered at all and we are coldbooting,
	 * check Factory Mode flag and override
	 */
	if (context->curr_service_mode == SERVICE_MODE_DETECT_NONE &&
		warmboot_reason == XBPAL_WB_NONE) {
		uint8_t FactoryMode = 0x00;
		/* Check if the Factory Mode flag is set */
		if (read_ta(TA_MISC_PART, TA_FACTORY_MODE_UNIT,
			&FactoryMode, sizeof(uint8_t)) != FCSERR_OK) {
			return -FCSERR_EINDEX;
		}

		if (FactoryMode != 0x01)
			return FCSERR_OK;

		FCS_LOG("FactoryMode is set\n");

		/* Pick service mode if VBUS detected */
		if (xbpal_usb_vbus_detect()) {
			context->curr_service_mode =
				SERVICE_MODE_DETECT_USB_SONY;
		} else {
			FCS_LOG("VBUS not detected\n");
		}
	}
	return FCSERR_OK;
}


/******************************************************************************/
/**
 * Parses the supplied list of triggers, probes and determines if any one is
 * asserted (or all if they use the "part_of" policy).
 *
 * @param[in] triggerData A list of triggers to evaluate.
 * @param[in] nofTriggers The number of triggers to evaluate.
 *
 * @returns true as soon as an active trigger is found, else false
 */
/******************************************************************************/
static bool trigger_detect(struct xboot_ctx *context,
	struct ServiceTrigger *triggerData, uint8_t nofTriggers)
{
	unsigned int i;
	bool result = false;
	unsigned int nof_part_of_triggers = 0;
	unsigned int nof_asserted_part_of_triggers = 0;
	bool part_of_trigger_trigged[32] = {false};
	enum xbpal_ServiceOtgRid_t plf_rid;
	enum xbpal_ServiceOtgRid_t trigger_rid;

	if (!context || !triggerData) {
		FCS_LOG_ERR("Invalid argument\n");
		return false;
	}

	if (nofTriggers > 32) {
		/* More than 32 triggers does not seem sane */
		FCS_LOG_ERR("Cannot handle more than 32 triggers!\n");
		return false;
	}

	for (i = 0; i < nofTriggers; i++) {
		switch (triggerData[i].svcTriggerType) {
		case SERVICE_TRIGGER_KEYPAD:
			if (!xbpal_kbd_button_pressed(
				triggerData[i].svcTriggerData.keypad_data.row,
				triggerData[i].svcTriggerData.keypad_data.col))
				break;

			FCS_LOG_INF("Keypad trigged on row %u col %u\n",
				triggerData[i].svcTriggerData.keypad_data.row,
				triggerData[i].svcTriggerData.keypad_data.col);

			if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_STANDALONE)
				return true;

			else if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_PART_OF)

				part_of_trigger_trigged[i] = true;
			break;

		case SERVICE_TRIGGER_GPIO:
			if (!is_gpio_asserted(context, 0,
			  triggerData[i].svcTriggerData.gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_data.pin_msb << 8,
			  triggerData[i].svcTriggerData.gpio_data.config))
				break;

			FCS_LOG_INF("GPIO trigged on pin %u\n",
			  triggerData[i].svcTriggerData.gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_data.pin_msb << 8);

			if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_STANDALONE)
				return true;

			else if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_PART_OF)

				part_of_trigger_trigged[i] = true;
			break;

		case SERVICE_TRIGGER_GPIO_IN_PMIC:
			if (!is_gpio_asserted(context, 1,
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
				<< 8,
			  triggerData[i].svcTriggerData.pmic_gpio_data.config))
				break;

			FCS_LOG_INF("PMIC GPIO trigged on pin %u\n",
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
			  << 8);

			if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_STANDALONE)
				return true;

			else if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_PART_OF)

				part_of_trigger_trigged[i] = true;
			break;

		case SERVICE_TRIGGER_GPIO_IN_PM0:
		case SERVICE_TRIGGER_GPIO_IN_PM1:
		case SERVICE_TRIGGER_GPIO_IN_PM2:
		case SERVICE_TRIGGER_GPIO_IN_PM3:
			if (!is_gpio_asserted(context,
			  triggerData[i].svcTriggerType,
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
				<< 8,
			  triggerData[i].svcTriggerData.pmic_gpio_data.config))
				break;

			FCS_LOG_INF("PMIC GPIO trigged on pin %d\n",
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
			  << 8);

			if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_STANDALONE)
				return true;

			else if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_PART_OF)

				part_of_trigger_trigged[i] = true;
			break;

		case SERVICE_TRIGGER_GPIO_3:
			if (!is_gpio_asserted(context, 2,
			  triggerData[i].svcTriggerData.gpio_3_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_3_data.pin_msb
				<< 8,
			  triggerData[i].svcTriggerData.gpio_3_data.config))
				break;

			FCS_LOG_INF("GPIO 3 trigged on pin %u\n",
			  triggerData[i].svcTriggerData.gpio_3_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_3_data.pin_msb
			  << 8);

			if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_STANDALONE)
				return true;

			else if (triggerData[i].svcTriggerPolicy ==
				SERVICE_TRIGGER_PART_OF)

				part_of_trigger_trigged[i] = true;
			break;

		case SERVICE_TRIGGER_OTG:
			trigger_rid =
			  triggerData[i].svcTriggerData.usb_data.rid_class;

			if ((xbpal_usb_otg_detect(&plf_rid) == FCSERR_OK) &&
				plf_rid == trigger_rid) {

				FCS_LOG_INF("OTG trigged\n");

				if (triggerData[i].svcTriggerPolicy ==
					SERVICE_TRIGGER_STANDALONE)
					return true;

				else if (triggerData[i].svcTriggerPolicy ==
					SERVICE_TRIGGER_PART_OF)

					part_of_trigger_trigged[i] = true;
			}
			break;

		case SERVICE_TRIGGER_POWER_ON:
			if (xbpal_pwr_button_pressed()) {
				FCS_LOG_INF("Power button trigged\n");

				if (triggerData[i].svcTriggerPolicy ==
					SERVICE_TRIGGER_STANDALONE)
					return true;

				else if (triggerData[i].svcTriggerPolicy ==
					SERVICE_TRIGGER_PART_OF)

					part_of_trigger_trigged[i] = true;
			}
			break;

		case SERVICE_TRIGGER_RESET_ON:
			if (xbpal_rst_button_pressed()) {
				FCS_LOG_INF("Reset button trigged\n");

				if (triggerData[i].svcTriggerPolicy ==
					SERVICE_TRIGGER_STANDALONE)
					return true;

				else if (triggerData[i].svcTriggerPolicy ==
					SERVICE_TRIGGER_PART_OF)

					part_of_trigger_trigged[i] = true;
			}
			break;

		default:
			FCS_LOG_ERR("No support for trigger type 0x%02X\n",
				triggerData[i].svcTriggerType);
			break;
		} /* switch.. */
	} /* for.. */

	/* Check if all part-of triggers are trigged
	 * Calculate total number of part-of triggers
	 */
	for (i = 0; i < nofTriggers; i++) {
		if (triggerData[i].svcTriggerPolicy ==
			SERVICE_TRIGGER_PART_OF) {

			nof_part_of_triggers++;

			/* Calculate the number of asserted part-of triggers */
			if (part_of_trigger_trigged[i])
				nof_asserted_part_of_triggers++;
		}
	}

	/* If we have part-of triggers and they are all asserted,
	 * then we have a valid trigger
	 */
	if (nof_part_of_triggers > 0 &&
		nof_part_of_triggers == nof_asserted_part_of_triggers)

		result = true;

	return result;
}

/******************************************************************************/
/**
 * Parses the supplied list of triggers, probes and determines if any one is
 * asserted. The difference between this and trigger_detect is that this
 * function returns true only if ALL supplied triggers are asserted.
 *
 * @param[in] triggerData A list of triggers to evaluate.
 * @param[in] nofTriggers The number of triggers to evaluate.
 *
 * @returns true if all triggers are active, else false. False if no
 *          triggers exists.
 */
/******************************************************************************/
static bool reset_trigger_detect(struct xboot_ctx *context,
	struct ServiceTrigger *triggerData, uint8_t nofTriggers)
{
	unsigned int i;
	bool result = false;
	enum xbpal_ServiceOtgRid_t plf_rid;
	enum xbpal_ServiceOtgRid_t trigger_rid;

	if (!context || !triggerData || nofTriggers == 0) {
		FCS_LOG_ERR("Invalid argument\n");
		return false;
	}

	for (i = 0; i < nofTriggers; i++) {
		if (i > 0 && false == result)
			break;
		result = false;
		switch (triggerData[i].svcTriggerType) {
		case SERVICE_TRIGGER_KEYPAD:
			if (!xbpal_kbd_button_pressed(
				triggerData[i].svcTriggerData.keypad_data.row,
				triggerData[i].svcTriggerData.keypad_data.col))
				break;

			FCS_LOG_INF("Keypad trigged on row %u col %u\n",
			  triggerData[i].svcTriggerData.keypad_data.row,
			  triggerData[i].svcTriggerData.keypad_data.col);
			result = true;
			break;

		case SERVICE_TRIGGER_GPIO:
			if (!is_gpio_asserted(context, 0,
			  triggerData[i].svcTriggerData.gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_data.pin_msb << 8,
			  triggerData[i].svcTriggerData.gpio_data.config))
				break;

			FCS_LOG_INF("GPIO trigged on pin %u\n",
			  triggerData[i].svcTriggerData.gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_data.pin_msb << 8);
			result = true;
			break;

		case SERVICE_TRIGGER_GPIO_IN_PMIC:
			if (!is_gpio_asserted(context, 1,
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
			  << 8,
			  triggerData[i].svcTriggerData.pmic_gpio_data.config))
				break;

			FCS_LOG_INF("PMIC GPIO trigged on pin %u\n",
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
			  << 8);
			result = true;
			break;

		case SERVICE_TRIGGER_GPIO_IN_PM0:
		case SERVICE_TRIGGER_GPIO_IN_PM1:
		case SERVICE_TRIGGER_GPIO_IN_PM2:
		case SERVICE_TRIGGER_GPIO_IN_PM3:
			if (!is_gpio_asserted(context,
			  triggerData[i].svcTriggerType,
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
			  << 8,
			  triggerData[i].svcTriggerData.pmic_gpio_data.config))
				break;

			FCS_LOG_INF("PMIC GPIO trigged on pin %d\n",
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_lsb |
			  triggerData[i].svcTriggerData.pmic_gpio_data.pin_msb
			  << 8);
			result = true;
			break;


		case SERVICE_TRIGGER_GPIO_3:
			if (!is_gpio_asserted(context, 2,
			  triggerData[i].svcTriggerData.gpio_3_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_3_data.pin_msb
			  << 8,
			  triggerData[i].svcTriggerData.gpio_3_data.config))
				break;

			FCS_LOG_INF("GPIO 3 trigged on pin %u\n",
			  triggerData[i].svcTriggerData.gpio_3_data.pin_lsb |
			  triggerData[i].svcTriggerData.gpio_3_data.pin_msb
			  << 8);
			result = true;
			break;

		case SERVICE_TRIGGER_OTG:
			trigger_rid =
			  triggerData[i].svcTriggerData.usb_data.rid_class;

			if ((xbpal_usb_otg_detect(&plf_rid) != FCSERR_OK) &&
				plf_rid == trigger_rid)
				break;

			FCS_LOG_INF("OTG trigged\n");
			result = true;
			break;

		case SERVICE_TRIGGER_POWER_ON:
			if (!xbpal_pwr_button_pressed())
				break;

			FCS_LOG_INF("Power button trigged\n");
			result = true;
			break;

		case SERVICE_TRIGGER_RESET_ON:
			if (!xbpal_rst_button_pressed())
				break;

			FCS_LOG_INF("Reset button trigged\n");
			result = true;
			break;

		default:
			FCS_LOG_ERR("No support for trigger type 0x%02X\n",
				triggerData[i].svcTriggerType);
			break;
		}
	}
	return result;
}

int sony_boot_service_reset_detect(
	struct xboot_ctx *context,
	enum reset_state_t *reset_state)
{
	int result = FCSERR_OK;
	unsigned int i;
	void *timer_context;

	if (!context || !context->bootconfig || !reset_state) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*reset_state = NO_RESET_DET;

	/* Determine if the reset triggers are active */
	if (reset_trigger_detect(context, context->bootconfig->resetKeys,
		context->bootconfig->nofResetKeys) ||
		xbpal_reset_detect()) {

		FCS_LOG_INF("Reset detected\n");
		*reset_state = RESET_DET_VIBRATION_NOT_DONE;
		if (context->bootconfig->resetTimeoutMS > 0) {
			/* Indicate reset to user */
			for (i = 0;
				i < context->bootconfig->resetNofPulsesStart;
				i++) {

				xbpal_vibrate(0, 1000 *
				  context->bootconfig->resetStartPulseOnTimeMS
				  );
				xbpal_delay_us(1000 *
				  context->bootconfig->resetStartPulseOffTimeMS
				  );
			}
			*reset_state = RESET_DET_VIBRATION_DONE;

			/* Start a timeout and determine if user presses the
			 * keys long enough to force a shutdown
			 */
			result = xbpal_timer_register_cb(&timer_context,
				shutdowntimer_cb,
				(uint32_t)context->bootconfig->resetTimeoutMS,
				context);
			if (result != FCSERR_OK) {
				FCS_LOG_ERR(
					"Failed to register timer for reset flow, timeout was %u ms!\n",
					context->bootconfig->resetTimeoutMS);
				return result;
			}

			/* Wait for the timer to expire or a trigger
			 * to be released
			 */
			while (!context->shutdowntimer_tripped &&
				reset_trigger_detect(context,
				context->bootconfig->resetKeys,
				context->bootconfig->nofResetKeys))
				;

			(void)xbpal_timer_deregister_cb(timer_context);

			if (!context->shutdowntimer_tripped) {
				FCS_LOG(
					"Reset keys pressed but released before shutdown timer expired. Booting normally.\n");
				return result;
			}

			context->shutdowntimer_tripped = false;
			/* Keys have been pressed long enough
			 * for shutdown, indicate this
			 */
			for (i = 0;
				i < context->bootconfig->resetNofPulsesEnd;
				i++) {

				xbpal_vibrate(0, 1000 *
				  context->bootconfig->resetEndPulseOnTimeMS);
				xbpal_delay_us(1000 *
				  context->bootconfig->resetEndPulseOffTimeMS);
			}
			FCS_LOG(
				"Reset keys pressed long enough. Shutting down now.\n");
#if defined(FEATURE_SM8350) || defined(FEATURE_SM8450) || defined(FEATURE_SM8550)
			while (xbpal_pwr_button_pressed()) {
				xbpal_delay_us(1000 * 10); /* 1ms x 10 = 10ms */
			}
#endif /* FEATURE_SM8350 || FEATURE_SM8450 || FEATURE_SM8550 */
			xbpal_shutdown(XBPAL_SHUTDOWN_REASON_OTHER);
			FCS_LOG_ERR("Shutdown has failed!\n");
			return -FCSERR_EOPFAIL;
		}
		context->curr_service_mode = SERVICE_MODE_DETECT_RECOVERY;
		FCS_LOG(
			"Reset key pressed but resetTimeoutMS is set to zero. Booting Recovery\n");
	} else {
		FCS_LOG_INF("No reset key(s) pressed\n");
	}

	return result;
}


/******************************************************************************/
/**
 * Wrapper to use generic GPIO interface to determine if provided GPIO is
 * asserted.
 *
 * @param[in] chip The ASIC to probe on.
 * @param[in] pin The pin to probe.
 * @param[in] cfg The bootconfig specific configuration for the pin.
 *
 * @returns true if pin is asserted
 */
/******************************************************************************/
static bool is_gpio_asserted(struct xboot_ctx *context, uint8_t chip,
	uint32_t pin, uint8_t cfg)
{
	static struct xbpal_gpio_cfg GpioCfg;
	bool isAsserted = false;

	GpioCfg.direction = XBPAL_GPIO_IN;
	GpioCfg.driveStrength = XBPAL_GPIO_DRIVE_MEDIUM;
	switch (cfg&GPIO_CFG_MUX_MASK) {
	case GPIO_CFG_MUX_SECONDARY:
		GpioCfg.function = XBPAL_GPIO_ALTERNATE_SECOND;
		break;
	case GPIO_CFG_MUX_THIRD:
		GpioCfg.function = XBPAL_GPIO_ALTERNATE_THIRD;
		break;
	case GPIO_CFG_MUX_FOURTH:
		GpioCfg.function = XBPAL_GPIO_ALTERNATE_FOURTH;
		break;
	default:
		GpioCfg.function = XBPAL_GPIO_PRIMARY;
		break;
	}

	switch (cfg&GPIO_CFG_PULL_MASK) {
	case GPIO_CFG_PULLDOWN:
		GpioCfg.pullUpOrDown = XBPAL_GPIO_PULLDOWN;
		break;
	case GPIO_CFG_PULLUP:
		GpioCfg.pullUpOrDown = XBPAL_GPIO_PULLUP;
		break;
	case GPIO_CFG_PULLOPENDRAIN:
		GpioCfg.pullUpOrDown = XBPAL_GPIO_OPENDRAIN;
		break;
	default:
		GpioCfg.pullUpOrDown = XBPAL_GPIO_PULLDISABLE;
		break;
	}

	if (GpioCfg.function != XBPAL_GPIO_PRIMARY &&
		GpioCfg.pullUpOrDown != XBPAL_GPIO_PULLDISABLE)

		GpioCfg.altFuncPullMode = XBPAL_GPIO_ALTPULL_ENABLE;
	else
		GpioCfg.altFuncPullMode = XBPAL_GPIO_ALTPULL_DISABLE;

	/* apply the configuration to the pin before reading it */
	if (xbpal_gpio_set_config(chip, pin, &GpioCfg) == FCSERR_OK) {
		uint8_t pin_value;

		 /* Let GPIO config settle before sampling */
		xbpal_delay_us(10);

		if (xbpal_gpio_get_pin(chip, pin, &pin_value) == FCSERR_OK) {
			if ((cfg&GPIO_CFG_ASSERT_STATE_MASK) &&
				 pin_value != 0)

				isAsserted = true;

			else if (!(cfg&GPIO_CFG_ASSERT_STATE_MASK) &&
				pin_value == 0)

				isAsserted = true;
		}
	}

	return isAsserted;
}

static void shutdowntimer_cb(void *arg)
{
	/* User pressed magic combo long enough, indicate this */
	((struct xboot_ctx *)arg)->shutdowntimer_tripped = true;
}



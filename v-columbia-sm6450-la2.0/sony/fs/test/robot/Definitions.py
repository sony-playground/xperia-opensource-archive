#!/usr/bin/env python3

class ContentId:
	# TC_ is Test Content
	DO_NOT_CARE = "Do not care"
	TC_TA_SIMLOCK_UNIT = "TA_SIMLOCK_UNIT"
	TC_TA_SIMLOCK_SIGNATURE_UNIT = "TA_SIMLOCK_SIGNATURE_UNIT"
	TC_TA_SW_UNIT = "TA_SW_UNIT"
	TC_TA_S1_BOOT_VERSION_UNIT = "TA_S1_BOOT_VERSION_UNIT"
	TC_TA_PHONE_NAME = "TA_PHONE_NAME"
	TC_TA_RCK = "TA_RCK"
	TC_TA_RESET_LOCK_STATUS = "TA_RESET_LOCK_STATUS"
	TC_TA_AUTH_CH = "TA_AUTH_CH"
	TC_TA_MSN_UNIT = "TA_MSN_UNIT"
	TC_TA_DK_NUMBER_UNIT = "TA_DK_NUMBER_UNIT"
	TC_TA_KEYSTORE_HMAC_KEY_APPLY = "TA_KEYSTORE_HMAC_KEY_APPLY"
	TC_TA_HWCONFIG_UNIT = "TA_HWCONFIG_UNIT"
	TC_TA_GOOGLE_LOCK_STATE = "TA_GOOGLE_LOCK_STATE"
	TC_CMS = "CMS"
	TC_PARTITION_TABLE = "PARTITION_TABLE"
	TC_RCK = "RCK"
	TC_KEYSTORE_PARTITION = "KEYSTORE_PARTITION"
	TC_SAKE_RESPONSE = "SAKE_RESPONSE"
	TC_FLASH_IMAGE = "FLASH_IMAGE"
	TC_SIGNATURE_FILE = "TC_SIGNATURE_FILE"
	TC_GETVAR_VERSION = "GETVAR_VERSION"
	TC_GETVAR_USB_VERSION = "GETVAR_USB_VERSION"
	TC_GETVAR_MAX_DOWNLOAD_SIZE = "TC_GETVAR_MAX_DOWNLOAD_SIZE"
	TC_GETVAR_VERSION_SONY = "TC_GETVAR_VERSION_SONY"
	TC_GETVAR_XFL_VERSION = "TC_GETVAR_XFL_VERSION"
	TC_GETVAR_MIN_XFL_VERSION = "TC_GETVAR_MIN_XFL_VERSION"
	TC_GETVAR_MAX_XFL_VERSION = "TC_GETVAR_MAX_XFL_VERSION"
	TC_GETVAR_SERIAL = "TC_GETVAR_SERIAL"
	TC_GETVAR_VERSION_BOOTLOADER = "TC_GETVAR_VERSION_BOOTLOADER"
	TC_GETVAR_VERSION_BASEBAND = "TC_GETVAR_VERSION_BASEBAND"
	TC_GETVAR_PRODUCT = "TC_GETVAR_PRODUCT"
	TC_GETVAR_PHONE_ID = "TC_GETVAR_PHONE_ID"
	TC_GETVAR_ROOTING_STATUS = "TC_GETVAR_ROOTING_STATUS"
	TC_GETVAR_DEVICE_ID = "TC_GETVAR_DEVICE_ID"
	TC_GETVAR_PLATFORM_ID = "TC_GETVAR_PLATFORM_ID"
	TC_GETVAR_FRP_PARTITION = "TC_GETVAR_FRP_PARTITION"
	TC_GETVAR_SECURE = "TC_GETVAR_SECURE"
	TC_GETVAR_SECTOR_SIZE = "TC_GETVAR_SECTOR_SIZE"
	TC_GETVAR_UFS_INFO = "TC_GETVAR_UFS_INFO"
	TC_GETVAR_EMMC_INFO = "TC_GETVAR_EMMC_INFO"
	TC_GETVAR_KEYSTORE_COUNTER = "TC_GETVAR_KEYSTORE_COUNTER"
	TC_GETVAR_KEYSTORE_XCS = "TC_GETVAR_KEYSTORE_XCS"
	TC_GETVAR_SAKE_ROOT = "TC_GETVAR_SAKE_ROOT"
	TC_GETVAR_DEFAULT_SECURITY = "TC_GETVAR_DEFAULT_SECURITY"
	TC_GETVAR_S1_ROOT = "TC_GETVAR_S1_ROOT"
	TC_GETVAR_SECURITY_STATE = "TC_GETVAR_SECURITY_STATE"
	TC_GETVAR_STORED_SECURITY_STATE = "TC_GETVAR_STORED_SECURITY_STATE"
	TC_GETVAR_BATTERY = "TC_GETVAR_BATTERY"
	TC_GETVAR_ROLLBACK_INDEX_COUNT = "TC_GETVAR_ROLLBACK_INDEX_COUNT"
	TC_GETVAR_ROLLBACK_INDEX = "TC_GETVAR_ROLLBACK_INDEX"
	TC_GETVAR_SLOT_COUNT = "TC_GETVAR_SLOT_COUNT"
	TC_GETVAR_CURRENT_SLOT = "TC_GETVAR_CURRENT_SLOT"
	TC_GETVAR_HAS_SLOT = "TC_GETVAR_HAS_SLOT"
	TC_GETVAR_SLOT_UNBOOTABLE = "TC_GETVAR_SLOT_UNBOOTABLE"
	TC_GETVAR_SLOT_SUCCESSFUL = "TC_GETVAR_SLOT_SUCCESSFUL"
	TC_GETVAR_PARTITION_TYPE = "TC_GETVAR_PARTITION_TYPE"
	TC_GETVAR_PARTITION_SIZE = "TC_GETVAR_PARTITION_SIZE"
	TC_GETVAR_X_CONF = "TC_GETVAR_X_CONF"
	TC_GETVAR_HAS_BEEN_UNLOCKED = "TC_GETVAR_HAS_BEEN_UNLOCKED"

class VariantId:
	# TCV_ is Test Content Variant
	TCV_VALID = "VALID"
	TCV_INVALID = "INVALID"

class FuseState:
	UNFUSED = "UNFUSED"
	LIVE = "LIVE"
	TEST = "TEST"

class LockState:
	UNLOCKED = "UNLOCKED"
	LOCKED = "LOCKED"

class RootingStatus:
	ROOTED = "ROOTED"
	ROOTABLE = "ROOTABLE"
	NOT_ROOTABLE = "NOT_ROOTABLE"

class Model:
	# This is the key of the DUT.
	INVALID = "invalido"
	APOLLO = "apollo"
	AKARI = "akari"
	AURORA = "aurora"
	PIONEER = "pioneer"
	MAPLE = "maple"
	LILAC = "lilac"
	APOLLO_KUMANO = "apollo-kumano"
	AKARI_KUMANO = "akari-kumano"
	KUMANO_CDB = "kumano-cdb"
	HOUOU = "houou"
	HOUOU_MVNO = "houou-mvno"
	DRAGON = "dragon"
	SPHINX = "sphinx"
	GRIFFIN = "griffin"

	def __init__(self, model):
		self.model = model

class SecureStorageState:
	def __init__(self):
		self.locked = LockState.LOCKED
		self.keystoreCounter = 0

# These variables depend on the HW of the DUT
class DutState:
	def __init__(self):
		# model is the key of the DUT, see class Model above
		self.model = "model"
		# product is the product id for the device, like 'H1234'
		self.product = "product"
		# phoneId is the IMEI(s)
		self.phoneId = "phoneId"
		# device id is the unique id of the DUT
		self.deviceId = "deviceId"
		self.fuseState = FuseState.UNFUSED
		self.lockState = LockState.LOCKED
		# Rooting status of the device
		self.rootingStatus = RootingStatus.ROOTED
		self.secureStorageState = SecureStorageState()
		# serial is the serial number, like 'BH90003MBJ'
		self.serial = "serial"
		# storageInfo shows into about the memory, like 'SAMSUNG,KLUCG4J1ED-B0C1,0200'
		# It is used both for UFS and EMMC
		self.storageInfo = "storageInfo"

# These variables depend on the SW of the DUT
class SwState:
	def __init__(self):
		self.xflVersion = "xflVersion"
		self.minXflVersion = "minXflVersion"
		self.maxXflVersion = "maxXflVersion"
		self.bootVersion = "bootVersion"
		self.versionBaseband = "versionBaseband"

# These variables are set based on DutState and SwState
class TCVar:
	rollbackIndex = []

	def __init__(self):
		# Getvar variables
		self.protocolVersion = "0.4"
		self.maxDownloadSize = "104857600"
		self.protocolVersionSony = "0.38"
		self.usbVersion = "usbVersion"
		self.product = "product"
		self.platformId = "platform"
		self.frpPartition = "FRP Partition"
		self.secure = "no"
		self.sectorSize = "4096"
		self.keystoreXcs = "keystoreXcs"
		self.sakeRoot = "sakeRoot"
		self.defaultSecurity = "defaultSecurity"
		self.s1Root = "s1root"
		self.securityState = "securityState"
		self.storedSecurityState = "storedSecurityState"
		self.rollbackIndexCount = "rollbackIndexCount"
		for i in range(32):
			self.rollbackIndex.append("0")
		self.slotCount = "slotCount"
		self.currentSlot = "currentSlot"
		self.hasSlotSystem = "hasSlotSystem"
		self.hasSlotUserdata = "hasSlotUserdata"
		self.slotUnbootableA = "slotUnbootableA"
		self.slotUnbootableB = "slotUnbootableB"
		self.slotSuccessfulA = "slotSuccessfulA"
		self.slotSuccessfulB = "slotSuccessfulB"

		self.partitionTable = {"partition1","partition2"}
		self.signatureFile = "signatureFile"
		self.invalidSignatureFile = "invalidSignatureFile"
		self.xConf = "xConf"
		self.partitionInfo = {}
		self.hasBeenUnlocked = "no"

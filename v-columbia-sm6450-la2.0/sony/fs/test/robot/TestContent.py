#!/usr/bin/env python3

from Definitions import *
import sys
sys.path.insert(0, './test_data')
from PartitionInfo import *

### Global variables ###
gTCVar = TCVar()
gDutState = DutState()
gSwState = SwState()

class TestContent:
	def setup_test_content(self, dutState, swState):
		print("TC: Setting up test content for DUT model {}".format(dutState.model))
		# Save setup data
		gSwState.xflVersion = swState.xflVersion
		gSwState.minXflVersion = swState.minXflVersion
		gSwState.maxXflVersion = swState.maxXflVersion
		gSwState.bootVersion = swState.bootVersion
		gSwState.versionBaseband = swState.versionBaseband

		gDutState.model = dutState.model
		gTCVar.product = dutState.product
		gDutState.serial = dutState.serial
		gDutState.phoneId = dutState.phoneId
		gDutState.deviceId = dutState.deviceId
		gDutState.storageInfo = dutState.storageInfo
		gDutState.secureStorageState.keystoreCounter = dutState.secureStorageState.keystoreCounter
		if dutState.secureStorageState.locked == LockState.LOCKED:
			gTCVar.keystoreXcs = "yes"
		else:
			gTCVar.keystoreXcs = "no"
		if dutState.lockState == LockState.UNLOCKED:
			gTCVar.secure = "no"
		else:
			gTCVar.secure = "yes"
		gTCVar.frpPartition = "frp"
		if dutState.fuseState == FuseState.UNFUSED:
			gTCVar.defaultSecurity = "OFF"
		else:
			gTCVar.defaultSecurity = "ON"
		gDutState.rootingStatus = dutState.rootingStatus

		gTCVar.slotCount = "2"
		gTCVar.currentSlot = "a"
		gTCVar.hasSlotSystem = "yes"
		gTCVar.hasSlotUserdata = "no"
		gTCVar.slotUnbootableA = "no"
		gTCVar.slotUnbootableB = "no"
		gTCVar.slotSuccessfulA = "yes"
		gTCVar.slotSuccessfulB = "no"
		gTCVar.usbVersion = "0x0310"
		gTCVar.rollbackIndexCount = "0"
		gTCVar.hasBeenUnlocked = "yes"

		gTCVar.signatureFile = "test_data/bootloader.cms"
		gTCVar.invalidSignatureFile = "Test.rst"

		if (dutState.model == Model.GRIFFIN):
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.53"
			gTCVar.partitionTable = {"p1","p2"}
			gTCVar.platformId = "300A50E1"
			gTCVar.sakeRoot = "D686"
			gTCVar.s1Root = "S1_Root_c0f0,S1_Root_Test_b316"
			gTCVar.securityState = "27ThDX1WjB+9xCxfO7+AxuVEleM9TYWCy/mcptzbHOM="
			gTCVar.storedSecurityState = "27ThDX1WjB+9xCxfO7+AxuVEleM9TYWCy/mcptzbHOM="
			gTCVar.rollbackIndexCount = "32"
			gTCVar.xConf = "b98a,b94e"
			# For Kumano and onwards, the successful bit is cleared
			# when flashing or erasing any partition.
			gTCVar.slotSuccessfulA = "no"
			gTCVar.partitionInfo = PartitionInfo()
			gTCVar.usbVersion = "0x0320"
			gTCVar.hasBeenUnlocked = "no"

		if (dutState.model == Model.DRAGON):
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.50"
			gTCVar.partitionTable = {"p1","p2"}
			gTCVar.platformId = "000A50E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.s1Root = "S1_Root_c0f0,S1_Root_Test_b316"
			gTCVar.securityState = "2uzVxykO2cfRTyjrfkuX5BHn9sgO77mWvV+/vzUIZFM="
			gTCVar.storedSecurityState = "2uzVxykO2cfRTyjrfkuX5BHn9sgO77mWvV+/vzUIZFM="
			gTCVar.rollbackIndexCount = "0"
			gTCVar.xConf = "9261,2da1"
			# For Kumano and onwards, the successful bit is cleared
			# when flashing or erasing any partition.
			gTCVar.slotSuccessfulA = "no"
			gTCVar.partitionInfo = PartitionInfo()
			gTCVar.sectorSize = "512"

		if (dutState.model == Model.KUMANO_CDB):
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.53"
			gTCVar.partitionTable = {"p1","p2"}
			gTCVar.platformId = "000A50E1"
			gTCVar.sakeRoot = "D686"
			gTCVar.s1Root = "S1_Root_c0f0,S1_Root_Test_b316"
			gTCVar.securityState = "27ThDX1WjB+9xCxfO7+AxuVEleM9TYWCy/mcptzbHOM="
			gTCVar.storedSecurityState = "27ThDX1WjB+9xCxfO7+AxuVEleM9TYWCy/mcptzbHOM="
			gTCVar.rollbackIndexCount = "32"
			gTCVar.xConf = "b98a,b94e"
			# For Kumano and onwards, the successful bit is cleared
			# when flashing or erasing any partition.
			gTCVar.slotSuccessfulA = "no"
			gTCVar.partitionInfo = PartitionInfo()

		if (dutState.model == Model.SPHINX):
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.53"
			gTCVar.partitionTable = {"p1","p2"}
			gTCVar.platformId = "200A50E1"
			gTCVar.sakeRoot = "D686"
			gTCVar.s1Root = "S1_Root_c0f0,S1_Root_Test_b316"
			gTCVar.securityState = "27ThDX1WjB+9xCxfO7+AxuVEleM9TYWCy/mcptzbHOM="
			gTCVar.storedSecurityState = "27ThDX1WjB+9xCxfO7+AxuVEleM9TYWCy/mcptzbHOM="
			gTCVar.rollbackIndexCount = "32"
			gTCVar.xConf = "b98a,b94e"
			# For Kumano and onwards, the successful bit is cleared
			# when flashing or erasing any partition.
			gTCVar.slotSuccessfulA = "no"
			gTCVar.partitionInfo = PartitionInfo()

		if (dutState.model == Model.APOLLO_KUMANO) or \
		   (dutState.model == Model.AKARI_KUMANO):
			# Used for pre development of kumano on tama devices
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.44"
			gTCVar.platformId = "1008B0E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.s1Root = "S1_Root_e090,S1_Root_Test_b316"
			gTCVar.securityState = "wSaq4guKAposHQYWumdHOVvrDFlLAbDib7JISLENTVc="
			gTCVar.storedSecurityState = "wSaq4guKAposHQYWumdHOVvrDFlLAbDib7JISLENTVc="
			gTCVar.rollbackIndexCount = "32"
			gTCVar.xConf = "b98a,b94e"
			# For Kumano and onwards, the successful bit is cleared
			# when flashing or erasing any partition.
			gTCVar.slotSuccessfulA = "no"
			gTCVar.partitionInfo = PartitionInfo()

		if (dutState.model == Model.APOLLO) or \
		   (dutState.model == Model.AURORA) or \
		   (dutState.model == Model.AKARI):
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.38"
			gTCVar.platformId = "1008B0E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.s1Root = "S1_Root_e090,S1_Root_Test_b316"
			gTCVar.securityState = "wSaq4guKAposHQYWumdHOVvrDFlLAbDib7JISLENTVc="
			gTCVar.storedSecurityState = "wSaq4guKAposHQYWumdHOVvrDFlLAbDib7JISLENTVc="
			gTCVar.rollbackIndexCount = "32"
			gTCVar.partitionInfo = PartitionInfo()

		if (dutState.model == Model.MAPLE):
			gTCVar.protocolVersion = "0.4-SONY-0.31"
			gTCVar.protocolVersionSony = "0.31"
			gTCVar.platformId = "2005E0E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.s1Root = "S1_Root_e69c,S1_Root_Test_b316"
			gTCVar.securityState = "8B466AE1D9E6E41DDCA94DA6230863C7B1AF3F98"
			gTCVar.storedSecurityState = "8B466AE1D9E6E41DDCA94DA6230863C7B1AF3F98"
			gTCVar.slotCount = "0"
			gTCVar.partitionInfo = PartitionInfo()

		if (dutState.model == Model.LILAC):
			gTCVar.protocolVersion = "0.4-SONY-0.31"
			gTCVar.protocolVersionSony = "0.31"
			gTCVar.platformId = "2005E0E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.usbVersion = "0x0200"
			gTCVar.s1Root = "S1_Root_e69c,S1_Root_Test_b316"
			gTCVar.securityState = "F9E333216BD5DDEF30B81943FF4B3D7C3D73682B"
			gTCVar.storedSecurityState = "F9E333216BD5DDEF30B81943FF4B3D7C3D73682B"
			gTCVar.slotCount = "0"
			gTCVar.partitionInfo = PartitionInfo()

		if dutState.model == Model.PIONEER:
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.38"
			gTCVar.platformId = "000AC0E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.s1Root = "S1_Root_70f0,S1_Root_Test_b316"
			gTCVar.securityState = "smYw/EZOLvA5yi+PiiqO4AVCl8E/aEKH34clWNosGkM="
			gTCVar.storedSecurityState = "smYw/EZOLvA5yi+PiiqO4AVCl8E/aEKH34clWNosGkM="
			gTCVar.sectorSize = "512"
			gTCVar.usbVersion = "0x0200"
			gTCVar.partitionInfo = PartitionInfo()

		if dutState.model == Model.HOUOU:
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.38"
			gTCVar.platformId = "000AC0E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.s1Root = "S1_Root_70f0,S1_Root_Test_b316"
			gTCVar.securityState = "3UMUXdndrHWQIoJWJYJwzV53oTTgoiquqMp4ImZzq+A="
			gTCVar.storedSecurityState = "3UMUXdndrHWQIoJWJYJwzV53oTTgoiquqMp4ImZzq+A="
			gTCVar.sectorSize = "512"
			gTCVar.usbVersion = "0x0200"
			gTCVar.partitionInfo = PartitionInfo()

		if dutState.model == Model.HOUOU_MVNO:
			gTCVar.protocolVersion = "0.4"
			gTCVar.protocolVersionSony = "0.38"
			gTCVar.platformId = "000AC0E1"
			gTCVar.sakeRoot = "D8D2"
			gTCVar.s1Root = "S1_Root_70f0,S1_Root_Test_b316"
			gTCVar.securityState = "xMITHBUbKa6S8m87wfHysLPWxs7eTLdoXNPXq4PbB+c="
			gTCVar.storedSecurityState = "xMITHBUbKa6S8m87wfHysLPWxs7eTLdoXNPXq4PbB+c="
			gTCVar.sectorSize = "512"
			gTCVar.usbVersion = "0x0200"
			gTCVar.rollbackIndexCount = "32"
			gTCVar.partitionInfo = PartitionInfo()

	def get_test_content(self, content_id, variant = VariantId.TCV_VALID):
		# Get test content for <content_id> with variant <variant>
		# Default variant is a valid content. Other variants
		# may be valid or invalid and specified for each <content_id>
		print("Get test content for id {}, variant {}".format(content_id, variant))

		if content_id == ContentId.TC_TA_PHONE_NAME:
			if variant == VariantId.TCV_VALID:
				return gDutState.model
			else:
				return Model.INVALID

		if content_id == ContentId.TC_GETVAR_USB_VERSION:
			return gTCVar.usbVersion

		if content_id == ContentId.TC_GETVAR_VERSION:
			return gTCVar.protocolVersion

		if content_id == ContentId.TC_GETVAR_MAX_DOWNLOAD_SIZE:
			return gTCVar.maxDownloadSize

		if content_id == ContentId.TC_GETVAR_VERSION_SONY:
			return gTCVar.protocolVersionSony

		if content_id == ContentId.TC_GETVAR_XFL_VERSION:
			return gSwState.xflVersion

		if content_id == ContentId.TC_GETVAR_MIN_XFL_VERSION:
			return gSwState.minXflVersion

		if content_id == ContentId.TC_GETVAR_MAX_XFL_VERSION:
			return gSwState.maxXflVersion

		if content_id == ContentId.TC_GETVAR_VERSION_BOOTLOADER:
			return gSwState.bootVersion

		if content_id == ContentId.TC_GETVAR_VERSION_BASEBAND:
			return gSwState.versionBaseband

		if content_id == ContentId.TC_GETVAR_SERIAL:
			return gDutState.serial

		if content_id == ContentId.TC_GETVAR_PRODUCT:
			return gTCVar.product

		if content_id == ContentId.TC_GETVAR_PHONE_ID:
			return gDutState.phoneId

		if content_id == ContentId.TC_GETVAR_ROOTING_STATUS:
			return gDutState.rootingStatus

		if content_id == ContentId.TC_GETVAR_DEVICE_ID:
			return gDutState.deviceId

		if content_id == ContentId.TC_GETVAR_PLATFORM_ID:
			return gTCVar.platformId

		if content_id == ContentId.TC_GETVAR_FRP_PARTITION:
			return gTCVar.frpPartition

		if content_id == ContentId.TC_GETVAR_SECURE:
			return gTCVar.secure

		if content_id == ContentId.TC_GETVAR_SECTOR_SIZE:
			return gTCVar.sectorSize

		if content_id == ContentId.TC_GETVAR_UFS_INFO:
			return gDutState.storageInfo

		if content_id == ContentId.TC_GETVAR_EMMC_INFO:
			return gDutState.storageInfo

		if content_id == ContentId.TC_GETVAR_KEYSTORE_COUNTER:
			return gDutState.secureStorageState.keystoreCounter

		if content_id == ContentId.TC_GETVAR_KEYSTORE_XCS:
			return gTCVar.keystoreXcs

		if content_id == ContentId.TC_GETVAR_SAKE_ROOT:
			return gTCVar.sakeRoot

		if content_id == ContentId.TC_GETVAR_DEFAULT_SECURITY:
			return gTCVar.defaultSecurity

		if content_id == ContentId.TC_GETVAR_S1_ROOT:
			return gTCVar.s1Root

		if content_id == ContentId.TC_GETVAR_X_CONF:
			return gTCVar.xConf

		if content_id == ContentId.TC_GETVAR_SECURITY_STATE:
			return gTCVar.securityState

		if content_id == ContentId.TC_GETVAR_STORED_SECURITY_STATE:
			return gTCVar.securityState

		if content_id == ContentId.TC_GETVAR_ROLLBACK_INDEX_COUNT:
			return gTCVar.rollbackIndexCount

		if content_id == ContentId.TC_GETVAR_ROLLBACK_INDEX:
			return gTCVar.rollbackIndex[int(variant)]

		if content_id == ContentId.TC_GETVAR_SLOT_COUNT:
			return gTCVar.slotCount

		if content_id == ContentId.TC_GETVAR_CURRENT_SLOT:
			return gTCVar.currentSlot

		if content_id == ContentId.TC_GETVAR_HAS_SLOT:
			if variant == "system":
				return gTCVar.hasSlotSystem
			elif variant == "userdata":
				return gTCVar.hasSlotUserdata

		if content_id == ContentId.TC_GETVAR_SLOT_UNBOOTABLE:
			if variant == "a":
				return gTCVar.slotUnbootableA
			elif variant == "b":
				return gTCVar.slotUnbootableB

		if content_id == ContentId.TC_GETVAR_SLOT_SUCCESSFUL:
			if variant == "a":
				return gTCVar.slotSuccessfulA
			elif variant == "b":
				return gTCVar.slotSuccessfulB

		if content_id == ContentId.TC_GETVAR_PARTITION_TYPE:
			return gTCVar.partitionInfo.partitions[variant]['fs_type']

		if content_id == ContentId.TC_GETVAR_PARTITION_SIZE:
			return gTCVar.partitionInfo.partitions[variant]['size']

		if content_id == ContentId.TC_GETVAR_HAS_BEEN_UNLOCKED:
			return gTCVar.hasBeenUnlocked

		if content_id == ContentId.TC_PARTITION_TABLE:
			if variant == VariantId.TCV_VALID:
				partition_table_list = []
				for key in gTCVar.partitionInfo.partitions:
					partition_table_list.append(key)
				return partition_table_list
			if variant == VariantId.TCV_INVALID:
				return ["invalid","partitions"]

		if content_id == ContentId.TC_SIGNATURE_FILE:
			if variant == VariantId.TCV_VALID:
				return gTCVar.signatureFile
			if variant == VariantId.TCV_INVALID:
				return gTCVar.invalidSignatureFile

		return "No content available for {}".format(content_id)

if __name__ == '__main__':
	# This is just test code for the interface
	ss_state = SecureStorageState()
	ss_state.locked = LockState.LOCKED
	ss_state.keystoreCounter = 7

	dut_state = DutState()
	dut_state.model = Model.APOLLO
	dut_state.fuseState = FuseState.LIVE
	dut_state.rootingStatus = RootingStatus.ROOTED

	dut_state.secureStorageState = ss_state

	sw_state = SwState()

	tc = TestContent()
	tc.setup_test_content(dut_state, sw_state)
	phone_name = tc.get_test_content(ContentId.TC_TA_PHONE_NAME, VariantId.TCV_VALID)
	print("Phone name is {}".format(phone_name))

	partition_table_list = tc.get_test_content(ContentId.TC_PARTITION_TABLE, VariantId.TCV_VALID)
	print("Partition table is {}".format(partition_table_list))

	rooting_status = tc.get_test_content(ContentId.TC_GETVAR_ROOTING_STATUS, VariantId.TCV_VALID)
	print("Rooting status is {}".format(rooting_status))

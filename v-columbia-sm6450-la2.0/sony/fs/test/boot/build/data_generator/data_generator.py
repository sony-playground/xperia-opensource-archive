#!/usr/bin/env python
from ctypes import *
import struct
import os
import time
import sys
import secs
import hashlib
import binascii
import hmac
from random import *

# Parser support Begin
class LenStateObject:
	def __init__(self):
		self.result = False
		self.state = 'Idle'
		self.firstLen = None
		self.curLen = None

	def __str__(self):
		l = []
		l.append('\nLenStateObject:\n')
		l.append(' result: ' + str(self.result) + '\n')
		l.append(' state: ' + str(self.state) + '\n')
		l.append(' firstLen: ' + str(self.firstLen) + '\n')
		l.append(' curLen: ' + str(self.curLen) + '\n')
		return ''.join(l)

	def addValue(self, value):
		self.result = False
		if self.state == 'Idle':
			if value < 0x80:
				self.curLen = value
				self.state = 'Idle'
				self.result = True
			elif value == 0x81:
				self.curLen = 0
				self.state = '12go'
				self.result = True
			elif value == 0x82:
				self.curLen = 0
				self.state = '22go'
				self.result = True
		elif self.state == '12go':
			self.curLen = self.curLen * 256 + value;
			self.state = 'Idle'
			self.result = True
		elif self.state == '22go':
			self.curLen = self.curLen * 256 + value;
			self.state = '12go'
			self.result = True
		if (self.result and self.state == 'Idle' and self.firstLen == None):
			self.firstLen = self.curLen

	def getResult(self):
		return self.result

	def getState(self):
		return self.state

	def getFirst(self):
		return self.firstLen

	def getCurrent(self):
		return self.curLen

class ValueStateObject:
	def __init__(self):
		self.result = False
		self.state = 'Idle'
		self.value = None
		self.length = 0

	def __str__(self):
		l = []
		l.append('\nLenStateObject:\n')
		l.append(' result: ' + str(self.result) + '\n')
		l.append(' state: ' + str(self.state) + '\n')
		l.append(' value: ' + str(self.value) + '\n')
		l.append(' length left: ' + str(self.length) + '\n')
		return ''.join(l)

	def addValue(self, value):
		self.result = True
		if self.length > 0:
			if self.state == 'Idle':
				if self.value == None:
					self.value = [[value]]
				else:
					self.value.append([value])
			else:
				self.value[len(self.value)-1].extend([value])
			self.state = 'Extend'
			self.length = self.length - 1
			if self.length <= 0:
				self.state = 'Idle'
		else:
			self.state = 'Idle'

	def setLength(self, value_len):
		self.length = value_len

	def getResult(self):
		return self.result

	def getState(self):
		return self.state

	def getValueAt(self, index):
		if ((index >= 0) and (index < len(self.value))):
			return self.value[index]
		else:
			return None
# Parser support End

boot_version = [
	0x58, 0x5F, 0x42, 0x6F, 0x6F, 0x74, 0x5F, 0x54,
	0x61, 0x72, 0x67, 0x65, 0x77, 0x5F, 0x54, 0x46,
	0x57
]

boot_config = [
	0x1a, 0xce, 0x33, 0x00, 0x01, 0x00, 0x08, 0x03,
	0x00, 0x02, 0x04, 0x02, 0x05, 0x00, 0x02, 0x02,
	0x51, 0x00, 0x10, 0x05, 0x00, 0x01, 0x03, 0x05,
	0x00, 0x10, 0x05, 0x00, 0x04, 0x83, 0x06, 0x00,
	0x10, 0x02, 0x00, 0x04, 0x85, 0x05, 0x00, 0x03,
	0x03, 0x06, 0x00, 0x10, 0x05, 0x00, 0x05, 0x83,
	0x05, 0x00, 0x10, 0x02, 0x00, 0x05, 0x85, 0x1a,
	0x00, 0x02, 0x00, 0xa9, 0x09, 0xbe, 0xba, 0xa9,
	0x09, 0x00, 0x00, 0xb3, 0x08, 0xbe, 0xba, 0xb3,
	0x08, 0x00, 0x00, 0x7e, 0x13, 0xbe, 0xba, 0x7e,
	0x13, 0x00, 0x00, 0x04, 0x00, 0x03, 0x00, 0x02,
	0x00, 0x04, 0x00, 0x04, 0x00, 0xb0, 0x04, 0x0e,
	0x00, 0x06, 0x00, 0xb8, 0x0b, 0x01, 0x4b, 0x00,
	0x00, 0x00, 0x03, 0x96, 0x00, 0x2c, 0x01, 0x03,
	0x00, 0x09, 0x00, 0x00
]

class PlatformInfo:
	def __init__(self, key,
			s1_roots,
			count_live_embcert_xfl,
			count_test_embcert_xfl,
			hwconf_live_rev, hwconf_live_cert,
			hwconf_test_rev, hwconf_test_cert,
			sake_live_certid, sake_live_crl_version, sake_live_crl,
			sake_test_certid, sake_test_crl_version, sake_test_crl,
			authch_live_rev,
			authch_test_rev,
			ks_live_rev, ks_live_cert,
			ks_test_rev, ks_test_cert,
			boot_version, boot_config,
			simlock_live_cert,
			simlock_test_cert,
			transport_live_cert,
			transport_test_cert,
			secdata_version):
		self.s1_roots = s1_roots
		self.count_live_embcert_xfl = count_live_embcert_xfl
		self.count_test_embcert_xfl = count_test_embcert_xfl
		self.sake_test_crl = sake_test_crl
		self.key = key
		self.hwconf_live_rev = hwconf_live_rev
		self.hwconf_live_cert = hwconf_live_cert
		self.hwconf_test_rev = hwconf_test_rev
		self.hwconf_test_cert = hwconf_test_cert
		self.sake_live_certid = sake_live_certid
		self.sake_live_crl_version = sake_live_crl_version
		self.sake_live_crl = sake_live_crl
		self.sake_test_certid = sake_test_certid
		self.sake_test_crl_version = sake_test_crl_version
		self.sake_test_crl = sake_test_crl
		self.authch_live_rev = authch_live_rev
		self.authch_test_rev = authch_test_rev
		self.ks_live_rev = ks_live_rev
		self.ks_live_cert = ks_live_cert
		self.ks_test_rev = ks_test_rev
		self.ks_test_cert = ks_test_cert
		self.boot_version = boot_version
		self.boot_config = boot_config
		self.simlock_live_cert = simlock_live_cert
		self.simlock_test_cert = simlock_test_cert
		self.transport_live_cert = transport_live_cert
		self.transport_test_cert = transport_test_cert
		self.secdata_version = secdata_version

	def __str__(self):
		return (' Key: ' + key
			+ '\n S1 Roots: ' + s1_roots
			+ '\n Live Count Embedded XFL certs: ' + str(count_live_embcert_xfl)
			+ '\n Test Count Embedded XFL certs: ' + str(count_test_embcert_xfl)
			+ '\n HWConfig Live Revision: ' + hwconf_live_rev
			+ '\n HwConfig Live Certificate Name: ' + hwconf_live_cert
			+ '\n HWConfig Test Revision: ' + hwconf_test_rev
			+ '\n HwConfig Test Certificate Name: ' + hwconf_test_cert,
			+ '\n SAKE Live Cert Id: ' + sake_live_certid
			+ '\n SAKE Live CRL Version: ' + sake_live_crl_version
			+ '\n SAKE Live CRL: ' + sake_live_crl
			+ '\n SAKE Live Cert Id: ' + sake_test_certid
			+ '\n SAKE Live CRL Version: ' + sake_test_crl_version
			+ '\n SAKE Live CRL: ' + sake_test_crl,
			+ '\n Athenticate Channel Live Revision: ' + authch_live_rev,
			+ '\n Athenticate Channel Test Revision: ' + authch_test_rev,
			+ '\n KeyStore Live Revision: ' + ks_live_rev
			+ '\n KeyStore Live Certificate Name: ' + ks_live_cert
			+ '\n KeyStore Test Revision: ' + ks_test_rev
			+ '\n KeyStore Test Certificate Name: ' + ks_test_cert
			+ '\n Boot Version: ' + boot_version
			+ '\n Boot Config: ' + boot_config
			+ '\n Simlock Live Certificate Name: ' + simlock_live_cert
			+ '\n Simlock Test Certificate Name: ' + simlock_test_cert
			+ '\n Transport Live Certificate Name: ' + transport_live_cert
			+ '\n Transport Test Certificate Name: ' + transport_test_cert
			+ '\n SecData Version: ' + secdata_version )

class PlatformNotFoundError(Exception):
	def __init__(self, platform):
		self.platform = platform

	def __str__(self):
		l = []
		l.append('\nUnknown platform\n')
		l.append(' platform: ' + self.platform + '\n')
		return ''.join(l)

class ParameterError(Exception):
	def __init__(self, parameter, value):
		self.parameter = parameter
		self.value = value

	def __str__(self):
		l = []
		l.append('\nWrong parameter value\n')
		l.append(' parameter: ' + self.parameter + '=' + self.value + '\n')
		return ''.join(l)

class DataGenerator(object):

	# obnoxious/seldsecs31/safesemla.extranet.sonyericsson.com
	def __init__(self, quiet = None, lib_path=None, url_secs='http://safesemla.extranet.sonyericsson.com/dispatch'):
		self.platforms = [
			PlatformInfo(
				'Yoshino_R1-Ubuntu',
				'S1_Root_e69c,S1_Root_Test_b316',
				1,
				1, # No of embedded roots, Ubuntu has only 1 test root
				'HWC_Yoshino_Com_001', 'S1_HWConf_e69c_0004',
				'HWC_Yoshino_Dev_001', 'S1_HWConf_Test_b316_0001',
				[ 0xd1, 0x59 ], 0, [],
				[ 0xd8, 0xd2 ], 0, [],
				'XFL-??????-?-??',
				'XFL-??????-?-??',
				'DKS_Yoshino_Com_002', 'x_keystore_6099',
				'DKS_Yoshino_Dev_003', 'x_keystore_e28f',
				boot_version, boot_config,
				'S1_SL_e69c_0004',
				'S1_SL_Test_b316_0001',
				'x_flash_all_XXXX',
				'x_flash_all_5ada',
				0xBABE0001),
			PlatformInfo(
				'Tama-Ubuntu',
				'S1_Root_e090,S1_Root_Test_b316',
				1,
				1, # No of embedded roots, Ubuntu has only 1 test root
				'HWC_Tama_Com_001', 'S1_HWConf_e090_0004',
				'HWC_Tama_Dev_001', 'S1_HWConf_Test_b316_0001',
				[ 0xb7, 0xdf ], 0, [],
				[ 0xd8, 0xd2 ], 0, [],
				'XFL-SDM845-O-15',
				'XFL-SDM845-O-15',
				'DKS_Tama_XXX_NNN', 'x_keystore_6099', # Don't know live keystore for Tama
				'DKS_Tama_Dev_005', 'x_keystore_68e8',
				boot_version, boot_config,
				'S1_SL_e090_0004',
				'S1_SL_Test_b316_0001',
				'x_flash_all_XXXX',
				'x_flash_all_ae08',
				0xBABE0001),
			PlatformInfo(
				'Nile-Ubuntu',
				'S1_Root_e090,S1_Root_Test_b316',
				1,
				1, # No of embedded roots, Ubuntu has only 1 test root
				'HWC_Nile_Com_001', 'S1_HWConf_70f0_0004',
				'HWC_Nile_Dev_001', 'S1_HWConf_Test_b316_0001',
				[ 0xb7, 0xdf ], 0, [],
				[ 0xd8, 0xd2 ], 0, [],
				'XFL-SDM845-O-15',
				'XFL-SDM845-O-15',
				'DKS_Nile_Com_001', 'x_keystore_2397', # Sony Keystore Live
				'DKS_Nile_Dev_001', 'x_keystore_7dd7', # Sony Keystore Test
				boot_version, boot_config,
				'S1_SL_70f0_0004',
				'S1_SL_Test_b316_0001',
				'x_flash_all_XXXX',
				'x_flash_all_9b8d',
				0xBABE0001),
			PlatformInfo(
				'Kumano-Ubuntu',
				'S1_Root_e090,S1_Root_Test_b316',
				1,
				1, # No of embedded roots, Ubuntu has only 1 test root
				'HWC_Kumano_001', 'x_conf_hwconfig_b94e',
				'HWC_Kumano_001', 'x_conf_hwconfig_b98a',
				[ 0x2f, 0x14 ], 0, [],
				[ 0xd6, 0x86 ], 0, [],
				'XFL-SDM845-O-15',
				'XFL-SDM845-O-15',
				'DKS_Kumano_Com_00x', 'x_conf_keystore_b94e',
				'DKS_Kumano_Dev_001', 'x_conf_keystore_b98a',
				boot_version, boot_config,
				'S1_SL_70f0_0004',
				'S1_SL_Test_b316_0001',
				'x_flash_all_XXXX',
				'x_flash_all_9b8d',
				0xBABE0001),
			PlatformInfo(
				'Huaihe-Ubuntu',
				'S1_Root_e090,S1_Root_Test_b316',
				1,
				1, # No of embedded roots, Ubuntu has only 1 test root
				'HWC_SM33_002', 'x_conf_hwconfig_2da1',
				'HWC_SM33_002', 'x_conf_hwconfig_9261',
				[ 0x90, 0x93 ], 0, [],
				[ 0xd8, 0xd2 ], 0, [],
				'XFL-??????-?-??',
				'XFL-??????-?-??',
				'DKS_SM33_Com_00x', 'x_conf_keystore_2da1',
				'DKS_SM33_Dev_002', 'x_conf_keystore_9261',
				boot_version, boot_config,
				'x_conf_simlock_2da1',
				'x_conf_simlock_9261',
				'x_flash_all_XXXX',
				'x_flash_all_9b8d',
				0xBABE0001)
		]

		if not lib_path:
			lib_path = 'secs.dll' if sys.platform == 'win32' else 'libsecs.so'
		DataGenerator.module = cdll.LoadLibrary(lib_path)
		if not quiet:
			print 'SECS lib: {} loaded.'.format(lib_path)
		self.handle = secs.Secs()
		self.handle.connect(url_secs)
		self.handle.checkTiming()
		if not quiet:
			print 'handle:', self.handle
		if self.handle == 0:
			raise FxToolError(self.getLastError(), 'No handle')

	def __del__(self, quiet = None):
		if self.handle:
			if not quiet:
				print 'Terminating SECS, handle:', self.handle
			self.handle.releaseHandle()

	def appendHeaderToFile(self, fobj, platform, devInfo, quiet = None):
		fobj.write('/*\n')
		fobj.write(' * Copyright (C) 2018 Sony Mobile Communications Inc.\n')
		fobj.write(' * All rights, including trade secret rights, reserved.\n')
		fobj.write(' */\n')
		fobj.write('\n')
		fobj.write('/*******************************************************************\n')
		fobj.write(' * This file is autogenerated for xboot test framework.\n')
		fobj.write(' *\n')
		fobj.write(' * Platform:  %s\n' % platform)
		fobj.write(' * DefSec:    %s\n' % devInfo["defsec"])
		fobj.write(' * DevID:     %s\n' % devInfo["devid"])
		fobj.write(' * PhoneID1:  %s\n' % devInfo["phoneid1"])
		if "phoneid2" in devInfo.keys():
			fobj.write(' * PhoneID2:  %s\n' % devInfo["phoneid2"])
		fobj.write(' * KSCounter: %s\n' % devInfo["kscounter"])
		fobj.write(' *******************************************************************/\n')

	def appendResultXToFileAsCArray(self, src, fobj, name, quiet = None):
		length = self.handle.cbuflen.value
		if (src > 0):
		    length = self.handle.cbuf2len.value
		fobj.write('\n')
		fobj.write('const unsigned char ')
		fobj.write(name)
		fobj.write('[')
		fobj.write(str(length))
		fobj.write('] = {\n')
		fobj.write('\t')
		col = 0
		for n in range(0, length):
			if (col >= 8):
				fobj.write(',\n')
				fobj.write('\t')
				col = 0
			elif (n > 0):
				fobj.write(', ')
			if (src > 0):
				fobj.write("0x%02X" % self.handle.cbuf2[n])
			else:
				fobj.write("0x%02X" % self.handle.cbuf[n])
			col = col + 1
		fobj.write('\n};\n')
		fobj.write('const unsigned int ')
		fobj.write(name)
		if (len(name) <= 22):
			fobj.write('_len = sizeof(')
		else:
			fobj.write('_len =\n\tsizeof(')
		fobj.write(name)
		fobj.write(');\n')

	def saveResult2File(self, fobj):
		length = self.handle.cbuflen.value
		for n in range(0, length):
			fobj.write("%02X" % self.handle.cbuf[n])

	def appendResultToFileAsCArray(self, fobj, name, quiet = None):
		self.appendResultXToFileAsCArray(0, fobj, name, quiet)

	def appendResult2ToFileAsCArray(self, fobj, name, quiet = None):
		self.appendResultXToFileAsCArray(1, fobj, name, quiet)

	def appendUCListToFileAsCArray(self, fobj, buf, name, quiet = None):
		length = len(buf)
		fobj.write('\n')
		fobj.write('const unsigned char ')
		fobj.write(name)
		fobj.write('[')
		fobj.write(str(length))
		fobj.write('] = {\n')
		fobj.write('\t')
		col = 0
		for n in range(0, length):
			if (col >= 8):
				fobj.write(',\n')
				fobj.write('\t')
				col = 0
			elif (n > 0):
				fobj.write(', ')
			fobj.write("0x%02X" % buf[n])
			col = col + 1
		fobj.write('\n};\n')
		fobj.write('const unsigned int ')
		fobj.write(name)
		if (len(name) <= 22):
			fobj.write('_len = sizeof(')
		else:
			fobj.write('_len =\n\tsizeof(')
		fobj.write(name)
		fobj.write(');\n')

	def appendLongListToFileAsULArray(self, fobj, buf, name, quiet = None):
		length = len(buf)
		fobj.write('\n')
		fobj.write('const unsigned long ')
		fobj.write(name)
		fobj.write('[')
		fobj.write(str(length))
		fobj.write('] = {\n')
		fobj.write('\t')
		col = 0
		for n in range(0, length):
			if (col >= 8):
				fobj.write(',\n')
				fobj.write('\t')
				col = 0
			elif (n > 0):
				fobj.write(', ')
			fobj.write(str(buf[n]))
			col = col + 1
		fobj.write('\n};\n')
		fobj.write('const unsigned int ')
		fobj.write(name)
		fobj.write('_len = ')
		fobj.write(str(length))
		fobj.write(';\n')

	def appendIntToFileAsCUInt(self, fobj, value, name, quiet = None):
		fobj.write('const unsigned int ')
		fobj.write(name)
		fobj.write(' = ')
		if (value > 0):
			fobj.write(str(value))
		else:
			# Check Patch!
			fobj.write('{ 0x00 }')
		fobj.write(';\n')

	def appendNewLineToFile(self, fobj, quiet = None):
		fobj.write('\n')

	def getPlatform(self, platform, quiet = None):
		for i in range(len(self.platforms)):
			if self.platforms[i].key == platform:
				return self.platforms[i]
		raise PlatformNotFoundError(platform)

	def printPlatforms(self, quiet = None):
		print "Available platforms are:"
		for i in range(len(self.platforms)):
			print " - " + self.platforms[i].key

	def authenticate(self, devInfo, platform, quiet = None):
		sakeresp_max_len = 8192
		hello = [
			'\x02', '\x00',							# Sake Version
			'\x01', '\x04',							# HASH ALG
			'\x00', '\x14',							# NONCE LENGTH
			'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',	# NONCE
			'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',	# NONCE
			'\x00', '\x00', '\x00', '\x00',					# NONCE
			'\x00', '\x1A',							# CERT ID LIST LENGTH
			'\x00', '\x18',							# CERT ID LENGTH
			'\xFE',								# IDENTIFIER
			'\x04',								# PUB HASH LENGTH +
											# 2 (CRL VER)
			'\x00', '\x00',							# PUB HASH
			'\x00', '\x00',							# CRL VERSION
			'\x00', '\x1B',							# Length No
											# IMEI/DEV_ID/REV
			'D', 'E', 'V', 'I', 'D', '=', '\"',
			'0', '0', '0', '0', '0', '0', '0', '0', '\"', ';',		# DEV_ID
			'R', 'E', 'V', '=', '\"', 'D', 'G', 'E', 'N', '\"',		# REV
			'\x00', '\x01' ]						# SSN
		platformObj = self.getPlatform(platform, quiet)
		for i in range(0, 20):
			hello[6 + i] = chr(randint(0, 255))
		if devInfo["defsec"] == 'OFF':
			hello[32] = chr(platformObj.sake_test_certid[0])
			hello[33] = chr(platformObj.sake_test_certid[1])
		else:
			hello[32] = chr(platformObj.sake_live_certid[0])
			hello[33] = chr(platformObj.sake_live_certid[1])

		if len(devInfo["devid"]) != 8:
			raise PlatformNotFoundError('DevId', devInfo["devid"])

		hello[45] = devInfo["devid"][0]
		hello[46] = devInfo["devid"][1]
		hello[47] = devInfo["devid"][2]
		hello[48] = devInfo["devid"][3]
		hello[49] = devInfo["devid"][4]
		hello[50] = devInfo["devid"][5]
		hello[51] = devInfo["devid"][6]
		hello[52] = devInfo["devid"][7]
		#print '========='
		#print [hex(ord(a)) for a in hello]
		#print '========='
		self.handle.sakeAuthenticateWithLen(hello, len(hello), sakeresp_max_len)
		#length = self.handle.cbuflen.value
		#for n in range(0, length):
		#    print hex(self.handle.cbuf[n]),
		#print

	def getFused(self, devInfo, quiet = None):
		self.handle.resetBuffer(10)
		self.handle.cbuflen.value = 1
		if devInfo["defsec"] == 'OFF':
			self.handle.cbuf[0] = 0
		else:
			self.handle.cbuf[0] = 1

	def getDevID(self, devInfo, quiet = None):
		self.handle.resetBuffer(10)
		self.handle.cbuflen.value = len(devInfo["devid"])/2
		for n in range(0, len(devInfo["devid"]), 2):
			self.handle.cbuf[n/2] = int(devInfo["devid"][n], 16) * 16 + int(devInfo["devid"][n + 1], 16)

	def getSignedHWConfigNormal(self, devInfo, platform, quiet = None):
		hwconfig_max_len = 8192
		smk = None
		platformObj = self.getPlatform(platform, quiet)
		if "phoneid2" in devInfo.keys():
			phoneId = [devInfo["phoneid1"], devInfo["phoneid2"]]
		else:
			phoneId = [devInfo["phoneid1"]]
		if devInfo["defsec"] == 'OFF':
			self.handle.getSignedHwConfigWithIdList(
				hwconfig_max_len,
				platformObj.hwconf_test_rev,
				[devInfo["devid"]],
				platformObj.hwconf_test_cert,
				phoneId,
				smk,
				1)
		else:
			self.handle.getSignedHwConfigWithIdList(
				hwconfig_max_len,
				platformObj.hwconf_live_rev,
				[devInfo["devid"]],
				platformObj.hwconf_live_cert,
				phoneId,
				smk,
				0)

	def getDKNormal(self, devInfo, quiet = None):
		dk_max_len = 64
		self.handle.generateDeviceKey(devInfo["phoneid1"], dk_max_len)
		#length = self.handle.cbuflen.value
		#for n in range(0, length):
		#    print hex(self.handle.cbuf[n]),
		#print

	def getSignedSLSignatureNormal(self, devInfo, platform, quiet = None):
		#buf_max_len = 65536
		buf_max_len = 4096
		data_max_len = 4096
		keycodeslen=1024
		infile ="s1_simlock_blank_v2_root_allowed.ta"
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			cert = platformObj.simlock_test_cert
		else:
			cert = platformObj.simlock_live_cert
		self.handle.getS1SimlockSignatureWithCert(cert, infile, devInfo["phoneid1"], buf_max_len, data_max_len, keycodeslen)
		length = self.handle.cbuflen.value

	def getSignedSLNotRootableSignatureNormal(self, devInfo, platform, quiet = None):
		buf_max_len = 4096
		data_max_len = 4096
		keycodeslen=1024
		infile ="s1_simlock_without_rooting_allowed_tag.ta"
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			cert = platformObj.simlock_test_cert
		else:
			cert = platformObj.simlock_live_cert
		self.handle.getS1SimlockSignatureWithCert(cert, infile, devInfo["phoneid1"], buf_max_len, data_max_len, keycodeslen)
		length = self.handle.cbuflen.value

	def getSignedKeyStoreNormalDevId(self, devInfo, platform, quiet = None):
		keystore_max_len = 65536
		next_count = int(devInfo["kscounter"]) + 1
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			self.handle.getSignedDeviceKeystore(
				platformObj.ks_test_rev,
				[devInfo["devid"]],
				next_count,
				platformObj.ks_test_cert,
				keystore_max_len)
		else:
			self.handle.getSignedDeviceKeystore(
				platformObj.ks_live_rev,
				[devInfo["devid"]],
				next_count,
				platformObj.ks_live_cert,
				keystore_max_len)
		return [ 0x00, next_count ]

	def getSignedKeyStoreNormalImei(self, devInfo, platform, quiet = None):
		keystore_max_len = 65536
		next_count = int(devInfo["kscounter"]) + 1
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			self.handle.getSignedDeviceKeystoreImeiBinding(
				platformObj.ks_test_rev,
				devInfo["phoneid1"],
				next_count,
				platformObj.ks_test_cert,
				keystore_max_len)
		else:
			self.handle.getSignedDeviceKeystoreImeiBinding(
				platformObj.ks_live_rev,
				devInfo["phoneid1"],
				next_count,
				platformObj.ks_live_cert,
				keystore_max_len)
		return [ 0x00, next_count ]

	def getSignedKeyStoreXcsDevId(self, devInfo, platform, quiet = None):
		keystore_max_len = 65536
		transport_max_len = 4096
		next_count = int(devInfo["kscounter"]) + 2
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			self.handle.getTwiceSignedDeviceKeystore(
				platformObj.ks_test_rev,
				[devInfo["devid"]],
				next_count,
				True,
				None,
				platformObj.ks_test_cert,
				platformObj.transport_test_cert,
				keystore_max_len,
				transport_max_len)
		else:
			self.handle.getTwiceSignedDeviceKeystore(
				platformObj.ks_live_rev,
				[devInfo["devid"]],
				next_count,
				True,
				None,
				platformObj.ks_live_cert,
				platformObj.transport_live_cert,
				keystore_max_len,
				transport_max_len)
		return [ 0xFF, next_count ]

	def getSignedKeyStoreXcsImei(self, devInfo, platform, quiet = None):
		keystore_max_len = 65536
		transport_max_len = 4096
		next_count = int(devInfo["kscounter"]) + 2
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			self.handle.getTwiceSignedDeviceKeystoreWithVBImeiBinding(
				platformObj.ks_test_rev,
				devInfo["phoneid1"],
				next_count,
				True,
				None,
				None,
				platformObj.ks_test_cert,
				platformObj.transport_test_cert,
				keystore_max_len,
				transport_max_len)
		else:
			self.handle.getTwiceSignedDeviceKeystoreWithVBImeiBinding(
				platformObj.ks_live_rev,
				devInfo["phoneid1"],
				next_count,
				True,
				None,
				None,
				platformObj.ks_live_cert,
				platformObj.transport_live_cert,
				keystore_max_len,
				transport_max_len)
		return [ 0xFF, next_count ]

	def getTotalNumberOfCerts(self, devInfo, platform, quiet = None):
		platformObj = self.getPlatform(platform, quiet)
		domains = self.parseKeyStoreResult(quit)
		if devInfo["defsec"] == 'OFF':
			if (3 in domains):
				domains[3] = domains[3] + platformObj.count_test_embcert_xfl
			else:
				domains[3] = platformObj.count_test_embcert_xfl
		else:
			if (3 in domains):
				domains[3] = domains[3] + platformObj.count_live_embcert_xfl
			else:
				domains[3] = platformObj.count_live_embcert_xfl
		return domains

	def getSha256OfCMSEmbPL(self, quiet = None):
		payload = self.parseCMSEmbPLResult(quit)
		print "PayLoad Len:", len(payload)

		d = hashlib.sha256()
		d.update(bytearray(payload))
		value = d.digest()

		dout = [0] * len(value)
		for n in range(len(value)):
			dout[n] = ord(value[n])

		return dout

	def getNumberOfEmbeddedCerts(self, devInfo, platform, quiet = None):
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			return platformObj.count_test_embcert_xfl
		else:
			return platformObj.count_live_embcert_xfl

	def getSignedResetFrpRequest(self, devInfo, platform, quiet = None):
		rlock_max_len = 65536
		xid = None
		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			self.handle.getSignedRemoteLockWithState(
				0,
				1,
				devInfo["phoneid1"],
				'S1_ROOT=\"' + platformObj.s1_roots + '\"',
				xid,
				rlock_max_len)
		else:
			self.handle.getSignedRemoteLockWithState(
				1,
				1,
				devInfo["phoneid1"],
				'S1_ROOT=\"' + platformObj.s1_roots + '\"',
				xid,
				rlock_max_len)

	def getBootVersion(self, platform, quiet = None):
		platformObj = self.getPlatform(platform, quiet)
		return platformObj.boot_version

	def getBootConfig(self, platform, quiet = None):
		platformObj = self.getPlatform(platform, quiet)
		return platformObj.boot_config

	def getSecDataVersion(self, platform, quiet = None):
		platformObj = self.getPlatform(platform, quiet)
		return platformObj.secdata_version

	def getSecDataLocked(self):
		return 0

	def getSecDataNoNonce(self):
		return [0]*20

	def getSecDataNoRB(self):
		return [0]*0x20

	def generateHMACKeyAndMaskBinding(self, devid, imei):
		hmac_key = os.urandom(32)
		bin_devid = binascii.unhexlify(devid)
		mask_devid = hmac.new(hmac_key, bin_devid, hashlib.sha256)
		mask_imei = hmac.new(hmac_key, imei, hashlib.sha256)
		return bytearray(hmac_key), mask_devid.hexdigest(), mask_imei.hexdigest()

	def modifyLastByte(self, buffer_with_bytes = None):
		if buffer_with_bytes:
			last_byte = len(buffer_with_bytes) - 1
			buffer_with_bytes[last_byte] = (buffer_with_bytes[last_byte] + 1) % 256
		else:
			last_byte = self.handle.cbuflen.value - 1
			self.handle.cbuf[last_byte] = (self.handle.cbuf[last_byte] + 1) % 256

	def modifyPayloadInKeystore(self):
		class FindError(Exception):
			def __init__(self, values):
				self.values = values
			def __str__(self):
				return 'Did not find in keystore: %s' % ', '.join(map(hex, self.values))

		class EatError(Exception):
			def __init__(self, index, expected, actual):
				self.i, self.e, self.a = index, expected, actual
			def __str__(self):
				return 'Keystore index: %d; Expected: 0x%X; Actual: 0x%X' % (self.i, self.e, self.a)

		def findAndEat(index, *values):
			for i in range(index, self.handle.cbuflen.value):
				if i + len(values) > self.handle.cbuflen.value:
					raise FindError(values)
				j = 0
				for v in values:
					if v != self.handle.cbuf[i+j]:
						break
					j += 1
				if j == len(values):
					return i+j
			raise FindError(values)

		def eat(index, *values):
			for v in values:
				if v != self.handle.cbuf[index]:
					raise EatError(index, v, self.handle.cbuf[index])
				index += 1;
			return index

		index = findAndEat(0, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x01)	# Find Object Identifier 'id-data'
		index = eat(index, 0xA0, 0x82)								# Eat 'eContent[0]' and length byte
		index += 2										# Skip length
		index = eat(index, 0x04, 0x82)								# Eat Octet String tag and length byte
		index += 2										# Skip length
		index = eat(index, 0x30, 0x82)								# Eat Constructed Sequence tag and length byte
		index += 2										# Skip length

		self.handle.cbuf[index+0] = 0xCA
		self.handle.cbuf[index+1] = 0xFE
		self.handle.cbuf[index+2] = 0xFA
		self.handle.cbuf[index+3] = 0xCE

	# Parser support Begin
	def processLenFieldInResult(self, stateLen, offset):
		if stateLen == None:
			stateLen = LenStateObject()
		value = self.handle.cbuf[offset]
		stateLen.addValue(value)
		return stateLen

	def setValFieldLen(self, stateVal, length):
		if stateVal == None:
			stateVal = ValueStateObject()
		stateVal.setLength(length)
		return stateVal;

	def processValFieldInResult(self, stateVal, offset):
		if stateVal == None:
			stateVal = ValueStateObject()
		value = self.handle.cbuf[offset]
		stateVal.addValue(value)
		return stateVal

	def matchPatternInResult(self,  matchHeaderPattern, offset, search):
		length = self.handle.cbuflen.value
		stateLen = None
		stateVal = None
		foundpattern = False
		for n in range(offset, length):
			stateLen = None
			stateVal = None
			foundpattern = True
			m = 0
			o = 0
			while m < len(matchHeaderPattern):
				if ((n + o) >= length):
					foundpattern = False
					break
				if not (matchHeaderPattern[m][0] == '?'):
					if (self.handle.cbuf[n + o] != int(matchHeaderPattern[m], 16)):
						foundpattern = False
						break
					m = m + 1;
				elif (matchHeaderPattern[m] == '?len'):
					stateLen = self.processLenFieldInResult(stateLen, n + o)
					if not stateLen.getResult():
						foundpattern = False
						break
					if stateLen.getState() == 'Idle':
						stateVal = self.setValFieldLen(stateVal, stateLen.getCurrent())
						m = m + 1
				elif (matchHeaderPattern[m] == '?val'):
					stateVal = self.processValFieldInResult(stateVal, n + o)
					if not stateVal.getResult():
						foundpattern = False
						break
					if stateVal.getState() == 'Idle':
						m = m + 1;
				o = o + 1;

			if (foundpattern):
				break
			if not search:
				foundpattern = False
				break

		return [foundpattern,
			n,
			n + o,
			stateLen.getFirst() if stateLen != None else None,
			stateLen.getCurrent() if stateLen != None else None,
			stateVal]

	def parseKeyStoreResult(self, quiet = None):
		matchHeaderPattern = [
			'0x30', '?len', '0x06', '0x09', '0x2a', '0x86',
			'0x48', '0x86', '0xf7', '0x0d', '0x01', '0x07', '0x01', '0xa0',
			'?len', '0x04', '?len', '0x30',
			'?len', '0x02', '0x01', '0x01', '0x01', '?len',
			'?val', '0x30', '?len' ]
		matchEntryPattern = [
			'0x30', '?len', '0x02', '?len', '?val' ]
		domains = {}

		match = self.matchPatternInResult(matchHeaderPattern, 0, True)
		if match[0]:
			end_list = match[2] + match[4] # EndPos + CurLen
			pos_list = match[2] # EndPos
			while (match[0] and pos_list < end_list):
				match = self.matchPatternInResult(matchEntryPattern, pos_list, False)
				if (match[0]):
					domain = match[5].getValueAt(0)[0]
					if (domain in domains):
						domains[domain] = domains[domain] + 1
					else:
						domains[domain] = 1
					pos_list = match[1] + 4 + match[3] # StartPos + <Header> + FirstLen

		return domains

	def parseCMSEmbPLResult(self, quiet = None):
		matchEmbPayloadPattern = [
			'0x30', '?len', '0x06', '0x09', '0x2a', '0x86',
			'0x48', '0x86', '0xf7', '0x0d', '0x01', '0x07', '0x01', '0xa0',
			'?len', '0x04', '?len' ]

		end_payload = 0
		begin_payload = 0
		match = self.matchPatternInResult(matchEmbPayloadPattern, 0, True)
		if match[0]:
			end_payload = match[2] + match[4] # EndPos + CurLen
			begin_payload = match[2] # EndPos

		return self.handle.cbuf[begin_payload:end_payload]
	# Parser support End

	def authenticate_channel_nonce(self, quiet = None):
		nonce = [
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00
		]
		for i in range(0, 20):
			nonce[i] = randint(0, 255)
		return nonce

	def authenticate_channel(self, devInfo, platform, nonce, rev, ssn, quiet = None):
		sakeresp_max_len = 8192
		hello = bytearray([
			0x02, 0x00,						# Sake Version
			0x01, 0x04,						# HASH ALG
			0x00, 0x14,						# NONCE LENGTH
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		# NONCE
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		# NONCE
			0x00, 0x00, 0x00, 0x00,					# NONCE
			0x00, 0x1A,						# CERT ID LIST LENGTH
			0x00, 0x18,						# CERT ID LENGTH
			0xFE,							# IDENTIFIER
			0x04,							# PUB HASH LENGTH +
										# 2 (CRL VER)
			0x00, 0x00,						# PUB HASH
			0x00, 0x00,						# CRL VERSION
			0x00, 0x26						# Length No
										# IMEI/DEV_ID/REV
		])
		platformObj = self.getPlatform(platform, quiet)
		for i in range(0, 20):
			hello[6 + i] = nonce[i]
		if devInfo["defsec"] == 'OFF':
			hello[32] = platformObj.sake_test_certid[0]
			hello[33] = platformObj.sake_test_certid[1]
		else:
			hello[32] = platformObj.sake_live_certid[0]
			hello[33] = platformObj.sake_live_certid[1]

		# Length No
		data_len = 13 + len(devInfo["devid"]) + len(rev) + 2
		hello[36] = (data_len >> 8) & 0xff
		hello[37] = data_len & 0xff

		# DEV_ID
		hello.append('D')
		hello.append('E')
		hello.append('V')
		hello.append('I')
		hello.append('D')
		hello.append('=')
		hello.append('\"')
		# Add DevId Make lower case
		for i in range(0, len(devInfo["devid"])):
			hello.append((devInfo["devid"][i]).lower())
		hello.append('\"')
		hello.append(';')
		# REV
		hello.append('R');
		hello.append('E');
		hello.append('V');
		hello.append('=');
		hello.append('\"');
		for i in range(0, len(rev)):
			hello.append(rev[i])
		hello.append('\"')

		# SSN
		hello.append((ssn >> 8) & 0xff)
		hello.append(ssn & 0xff)

		self.handle.sakeAuthenticateWithLen(hello, len(hello), sakeresp_max_len)

	def authch_ARB(self, devInfo, platform, nonce, quiet = None):
		sakeresp_max_len = 8192
		auth_cmd_header = bytearray([
			0x12, 0x01, 0x77, 0x11, 0x01, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00
		])
		arb_cmd = bytearray([
			0x12, 0x01, 0x77, 0x11, 0x01, 0x00, 0x00, 0x00,
			0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		])

		platformObj = self.getPlatform(platform, quiet)
		if devInfo["defsec"] == 'OFF':
			rev = platformObj.authch_test_rev.encode("utf8")
			rev_len = len(rev) + 1
			for ch in rev:
				auth_cmd_header.append(ch)
			auth_cmd_header.append('\x00')
		else:
			rev = platformObj.authch_live_rev.encode("utf8")
			rev_len = len(rev) + 1
			for ch in rev:
				auth_cmd_header.append(ch)
			auth_cmd_header.append('\x00')

		# Update command buffer len
		length = 28 + rev_len
		auth_cmd_header[12] = length & 0xFF
		auth_cmd_header[13] = (length >> 8) & 0xFF
		auth_cmd_header[14] = (length >> 16) & 0xFF
		auth_cmd_header[15] = (length >> 24) & 0xFF
		# Update rev len
		auth_cmd_header[20] = rev_len & 0xFF
		auth_cmd_header[21] = (rev_len >> 8) & 0xFF
		auth_cmd_header[22] = (rev_len >> 16) & 0xFF
		auth_cmd_header[23] = (rev_len >> 24) & 0xFF

		rev = auth_cmd_header[28:length-1]
		ssn = auth_cmd_header[16] + auth_cmd_header[17] * 256

		# Get Authentication Response
		self.authenticate_channel(devInfo, platform, nonce, rev, ssn, quiet)
		# Make room for Auth Channel Command/Header
		resp_len = self.handle.cbuflen.value
		header_len = len(auth_cmd_header)
		for n in range(resp_len-1, -1, -1):
			self.handle.cbuf[header_len + n] = self.handle.cbuf[n]
		self.handle.cbuflen.value = self.handle.cbuflen.value + header_len
		# Add auth cmd header
		for n in range(0, len(auth_cmd_header)):
			self.handle.cbuf[n] = auth_cmd_header[n]
		# Update command buffer len
		length = 28 + resp_len
		self.handle.cbuf[12] = length & 0xFF
		self.handle.cbuf[13] = (length >> 8) & 0xFF
		self.handle.cbuf[14] = (length >> 16) & 0xFF
		self.handle.cbuf[15] = (length >> 24) & 0xFF
		# Update response len
		self.handle.cbuf[24] = resp_len & 0xFF
		self.handle.cbuf[25] = (resp_len >> 8) & 0xFF
		self.handle.cbuf[26] = (resp_len >> 16) & 0xFF
		self.handle.cbuf[27] = (resp_len >> 24) & 0xFF

		# Add arb cmd
		for n in range(0, len(arb_cmd)):
			self.handle.cbuf[self.handle.cbuflen.value + n] = arb_cmd[n]
		self.handle.cbuflen.value = self.handle.cbuflen.value + len(arb_cmd)

		#length = self.handle.cbuflen.value
		#for n in range(0, length):
		#    if ((n % 16) == 0):
		#        print
		#    print '0x{:02X}'.format(self.handle.cbuf[n]),
		#print

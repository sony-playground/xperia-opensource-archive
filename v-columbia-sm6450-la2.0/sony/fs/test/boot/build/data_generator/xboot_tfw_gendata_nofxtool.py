#!/usr/bin/env python

import sys
import time
from optparse import OptionParser, OptionGroup
from sys import stdout
from ctypes import *
from copy import copy

from data_generator import DataGenerator

def main():
	quiet = True

	dg = DataGenerator()

	if (len(sys.argv) != 6):
		print "Please provide platform name, defsec, devid, phoneid, kscounter!"
		dg.printPlatforms()
		assert(0)

	platform = sys.argv[1]
	imeis = sys.argv[4].split()

	if (len(imeis) < 1) or (len(imeis) > 2):
		print "Must be one or two phoneid(s)!"
		assert(0)

	dev_info = { "defsec":sys.argv[2], "devid":sys.argv[3], "phoneid1":imeis[0], "kscounter":sys.argv[5] }
	if len(imeis) == 2:
		dev_info["phoneid2"] = imeis[1]

	dg.getPlatform(platform)

	print "Generating test data for platform " + sys.argv[1]
	print "DefSec ", dev_info["defsec"]
	print "DevID ", dev_info["devid"]
	print "PhoneID1 ", dev_info["phoneid1"]
	if "phoneid2" in dev_info.keys():
		print "PhoneID2 ", dev_info["phoneid2"]
	print "KSCounter ", dev_info["kscounter"]

	##############################################################
	# dut_normal.c
	##############################################################

	f = open('dut_normal.c', 'w')
	dg.appendHeaderToFile(f, platform, dev_info, quiet)

	dg.getFused(dev_info, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_fuse', quiet)

	dg.getDevID(dev_info, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_dev_id', quiet)

	#dg.authenticate(dev_info, 'Yoshino_R1', quiet)
	dg.getSignedHWConfigNormal(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_hwconfig', quiet)

	dg.getDKNormal(dev_info, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_miscta_dk', quiet)

	ks_parms = dg.getSignedKeyStoreNormalDevId(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_ks_valid_devid', quiet)

	ks_parms = dg.getSignedKeyStoreNormalImei(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_ks_valid_imei', quiet)

	dg.appendNewLineToFile(f)
	domains = dg.getTotalNumberOfCerts(dev_info, platform, quiet)
	print 'domain: ' + str(domains)
	# Domain normal (1)
	if 1 in domains:
		dg.appendIntToFileAsCUInt(f, domains[1], 'const_dut_ks_valid_n_normal_cert', quiet)
	else:
		dg.appendIntToFileAsCUInt(f, 0, 'const_dut_ks_valid_n_normal_cert', quiet)
	# Domain xfl (3)
	if 3 in domains:
		dg.appendIntToFileAsCUInt(f, domains[3], 'const_dut_ks_valid_n_xfl_cert', quiet)
	else:
		dg.appendIntToFileAsCUInt(f, 0, 'const_dut_ks_valid_n_xfl_cert', quiet)
	n = dg.getNumberOfEmbeddedCerts(dev_info, platform, quiet)
	dg.appendIntToFileAsCUInt(f, n, 'const_dut_emb_valid_n_xfl_cert', quiet)

	dg.appendNewLineToFile(f)
	dg.appendIntToFileAsCUInt(f, dg.getSecDataVersion(platform, quiet), 'const_dut_sec_data_version', quiet)
	dg.appendIntToFileAsCUInt(f, dg.getSecDataLocked(), 'const_dut_sec_data_unlock', quiet)
	dg.appendLongListToFileAsULArray(f, dg.getSecDataNoRB(), 'const_dut_sec_data_rollback_counter', quit)
	dg.appendUCListToFileAsCArray(f, dg.getSecDataNoNonce(), 'const_dut_sec_data_sake_nonce', quit)

	dg.appendNewLineToFile(f)
	dg.appendIntToFileAsCUInt(f, ks_parms[1], 'const_dut_sec_data_ks_counter', quiet)
	dg.appendIntToFileAsCUInt(f, ks_parms[0], 'const_dut_sec_data_ks_xcs_rot', quiet)
	dg.appendUCListToFileAsCArray(f, dg.getSha256OfCMSEmbPL(quiet), 'const_dut_sec_data_ks_hash', quit)

	dev_info["kscounter"] = (int)(dev_info["kscounter"]) - 1
	ks_parms = dg.getSignedKeyStoreXcsImei(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_ks_valid_imei_diff_payload', quiet)
	dev_info["kscounter"] = (int)(dev_info["kscounter"]) + 1

	ks_parms = dg.getSignedKeyStoreXcsImei(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_ks_xcs_valid', quiet)

	dg.appendNewLineToFile(f)
	domains = dg.getTotalNumberOfCerts(dev_info, platform, quiet)
	print 'domain: ' + str(domains)
	# Domain normal (1)
	if 1 in domains:
		dg.appendIntToFileAsCUInt(f, domains[1], 'const_dut_ks_xcs_valid_n_normal_cert', quiet)
	else:
		dg.appendIntToFileAsCUInt(f, 0, 'const_dut_ks_xcs_valid_n_normal_cert', quiet)
	# Domain xfl (3)
	if 3 in domains:
		dg.appendIntToFileAsCUInt(f, domains[3], 'const_dut_ks_xcs_valid_n_xfl_cert', quiet)
	else:
		dg.appendIntToFileAsCUInt(f, 0, 'const_dut_ks_xcs_valid_n_xfl_cert', quiet)

	dg.appendNewLineToFile(f)
	dg.appendIntToFileAsCUInt(f, ks_parms[1], 'const_dut_sec_data_ks_xcs_counter', quiet)
	dg.appendIntToFileAsCUInt(f, ks_parms[0], 'const_dut_sec_data_ks_xcs_xcs_rot', quiet)
	dg.appendUCListToFileAsCArray(f, dg.getSha256OfCMSEmbPL(quiet), 'const_dut_sec_data_ks_xcs_hash', quit)

	dg.getSignedResetFrpRequest(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_reset_frp', quiet)

	dg.appendUCListToFileAsCArray(f, dg.getBootVersion(platform, quiet), 'const_dut_boot_version', quit)

	dg.appendUCListToFileAsCArray(f, dg.getBootConfig(platform, quiet), 'const_dut_boot_config', quit)

	dg.getSignedSLSignatureNormal(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_sl_signature', quiet)
	dg.appendResult2ToFileAsCArray(f, 'const_dut_sl_data', quiet)

	dg.getSignedSLNotRootableSignatureNormal(dev_info, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_sl_not_rootable_signature', quiet)
	dg.appendResult2ToFileAsCArray(f, 'const_dut_sl_not_rootable_data', quiet)

	authch_nonce = dg.authenticate_channel_nonce(quiet)
	dg.appendUCListToFileAsCArray(f, authch_nonce, 'const_dut_authch_sake_nonce', quit)

	dg.authch_ARB(dev_info, platform, authch_nonce, quiet)
	dg.appendResultToFileAsCArray(f, 'const_dut_auth_channel', quiet)

	f.close()

	##############################################################
	# dut_valid.c
	##############################################################

	f = open('dut_valid.c', 'w')
	dg.appendHeaderToFile(f, platform, dev_info, quiet)

	dg.appendNewLineToFile(f)
	f.write('/*\n')
	f.write(' * Keystore with KS counter 5. It has the same hash as\n')
	f.write(' * the normal keystore const_dut_ks_valid_imei.\n')
	f.write(' */')
	temp = copy(dev_info)
	temp["kscounter"] = 4
	ks_parms = dg.getSignedKeyStoreNormalImei(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'keystore_counter5', quiet)

	dg.appendNewLineToFile(f)
	dg.appendIntToFileAsCUInt(f, ks_parms[1], 'sec_data_keystore_counter5', quiet)

	hmac_key, devid_hmac, imei_hmac = dg.generateHMACKeyAndMaskBinding(dev_info["devid"], dev_info["phoneid1"])
	print "devid_hmac =", devid_hmac
	print "imei_hmac =", imei_hmac

	dg.appendNewLineToFile(f)
	f.write('/* XCS keystore bound to HMAC of DevID. */')
	temp = copy(dev_info)
	temp["devid"] = devid_hmac
	dg.getSignedKeyStoreXcsDevId(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'xcs_keystore_bound_to_hmac_devid', quiet)

	dg.appendNewLineToFile(f)
	f.write('/* XCS keystore bound to HMAC of IMEI. */')
	temp = copy(dev_info)
	temp["phoneid1"] = imei_hmac
	dg.getSignedKeyStoreXcsImei(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'xcs_keystore_bound_to_hmac_imei', quiet)

	dg.appendNewLineToFile(f)
	f.write('/* Non XCS keystore bound to HMAC of IMEI. */')
	dg.getSignedKeyStoreNormalImei(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'sony_keystore_bound_to_hmac_imei', quiet)

	hmac_key_new, devid_hmac, imei_hmac = dg.generateHMACKeyAndMaskBinding(dev_info["devid"], dev_info["phoneid1"])
	print "devid_hmac =", devid_hmac
	print "imei_hmac =", imei_hmac

	dg.appendNewLineToFile(f)
	f.write('/* Non XCS keystore bound to HMAC of IMEI with new HMAC key. */')
	temp = copy(dev_info)
	temp["phoneid1"] = imei_hmac
	dg.getSignedKeyStoreNormalImei(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'sony_keystore_bound_to_hmac_imei_new_key', quiet)

	dg.appendNewLineToFile(f)
	domains = dg.getTotalNumberOfCerts(temp, platform, quiet)
	if 1 in domains:
		dg.appendIntToFileAsCUInt(f, domains[1], 'ks_bound_to_hmac_valid_n_normal_cert', quiet)
	else:
		dg.appendIntToFileAsCUInt(f, 0, 'ks_bound_to_hmac_valid_n_normal_cert', quiet)

	dg.appendUCListToFileAsCArray(f, hmac_key, 'hmac_key', quiet)
	dg.appendUCListToFileAsCArray(f, hmac_key_new, 'hmac_key_new', quiet)

	f.close()

	##############################################################
	# dut_wrong.c
	##############################################################

	f = open('dut_wrong.c', 'w')
	dg.appendHeaderToFile(f, platform, dev_info, quiet)

	dg.appendNewLineToFile(f)
	f.write('/*\n')
	f.write(' * HWConfig with the following wrong DevID:\n')
	f.write(' * 0x19, 0x83, 0x10, 0x08, 0x16, 0x10\n')
	f.write(' */')
	temp = copy(dev_info)
	temp["devid"] = '198310081610'
	dg.getSignedHWConfigNormal(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'hwconfig_wrong_devid', quiet)

	dg.appendNewLineToFile(f)
	f.write('/*\n')
	f.write(' * HWConfig with wrong payload.\n')
	f.write(' * Last byte has been increased by one.\n')
	f.write(' */')
	dg.getSignedHWConfigNormal(dev_info, platform, quiet)
	dg.modifyLastByte()
	dg.appendResultToFileAsCArray(f, 'hwconfig_wrong_payload', quiet)

	dg.appendNewLineToFile(f)
	f.write('/*\n')
	f.write(' * Keystore with the following wrong DevID:\n')
	f.write(' * 0x19, 0x83, 0x10, 0x08, 0x16, 0x10\n')
	f.write(' */')
	temp = copy(dev_info)
	temp["devid"] = '198310081610'
	dg.getSignedKeyStoreNormalDevId(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'keystore_wrong_devid', quiet)

	dg.appendNewLineToFile(f)
	f.write('/*\n')
	f.write(' * Keystore with the following wrong IMEI:\n')
	f.write(' * 00440245778550\n')
	f.write(' */')
	temp = copy(dev_info)
	temp["phoneid1"] = '00440245778550'
	dg.getSignedKeyStoreNormalImei(temp, platform, quiet)
	dg.appendResultToFileAsCArray(f, 'keystore_wrong_imei', quiet)

	dg.appendNewLineToFile(f)
	f.write('/*\n')
	f.write(' * Keystore with wrong payload. Some bytes have been\n')
	f.write(' * changed to 0xCAFEFACE.\n')
	f.write(' */')
	dg.getSignedKeyStoreNormalDevId(dev_info, platform, quiet)
	dg.modifyPayloadInKeystore()
	dg.appendResultToFileAsCArray(f, 'keystore_wrong_payload', quiet)

	dg.appendNewLineToFile(f)
	f.write('/*\n')
	f.write(' * HMAC key that do not match xcs_keystore_bound_to_hmac_devid\n')
	f.write(' * and xcs_keystore_bound_to_hmac_imei.\n')
	f.write(' * Last byte has been increased by one.\n')
	f.write(' */')
	dg.modifyLastByte(hmac_key)
	dg.appendUCListToFileAsCArray(f, hmac_key, 'wrong_hmac_key', quiet)

	f.close()

if __name__ == "__main__":
	try:
		sys.exit(main())
	finally:
		print "Done."

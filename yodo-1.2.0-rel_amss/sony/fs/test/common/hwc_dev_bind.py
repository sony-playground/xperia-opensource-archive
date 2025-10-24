#!/usr/bin/python

import sys
import binascii
import struct

def get_devid( text ):
	assert (text[:4] == 'OKAY'),"Unexpected response format!"
	return binascii.unhexlify(text[4:])

def get_payload( sin ):
	assert (binascii.hexlify(sin[0]) == '03'),"Unexpected SIN format!"
	assert (binascii.hexlify(sin[1]) == '53'),"Unexpected SIN format!"
	assert (binascii.hexlify(sin[2]) == '49'),"Unexpected SIN format!"
	assert (binascii.hexlify(sin[3]) == '4e'),"Unexpected SIN format!"
	start_payload = int(sin[6].encode('hex'), 16) *256
	start_payload += int(sin[7].encode('hex'), 16)
	return sin[start_payload:]

def get_devid_idxs( hwc ):
	assert (binascii.hexlify(hwc[0:2]) == '0007'),\
		"Unexpected HWConfig format!"
	# Skip Version, Flags, ProductID
	idx = 6
	# Skip Skip MiscDatas
	skip_length = int(hwc[idx].encode('hex'), 16) *256
	skip_length += int(hwc[idx+1].encode('hex'), 16)
	idx += 2
	idx += skip_length
	# Skip PhoneIDs
	skip_length = int(hwc[idx].encode('hex'), 16) *256
	skip_length += int(hwc[idx+1].encode('hex'), 16)
	idx += 2
	idx += skip_length
	# Skip Global Flags
	idx += 2
	# Skip Security Configs
	skip_length = int(hwc[idx].encode('hex'), 16) *256
	skip_length += int(hwc[idx+1].encode('hex'), 16)
	idx += 2
	idx += skip_length
	# DevIds section start Idx and Next section Idx
	skip_length = int(hwc[idx].encode('hex'), 16) *256
	skip_length += int(hwc[idx+1].encode('hex'), 16)
	return [idx, idx + 2 + skip_length]

assert (len(sys.argv) == 4),"Unexpected number of parameters!"

fdevid_in = open(sys.argv[1], "r")
strdevid = fdevid_in.read()
fdevid_in.close()

fhwc_in = open(sys.argv[2], "rb")
strhwc = fhwc_in.read()
fhwc_in.close()

devid = get_devid( strdevid )
hwc_payload = get_payload( strhwc )
devid_idxs = get_devid_idxs( hwc_payload )

fhwc_out = open(sys.argv[3], "wb")
fhwc_out.write(hwc_payload[:devid_idxs[0]])
fhwc_out.write(struct.pack(">H", len(devid) + 2))
fhwc_out.write(struct.pack(">H", len(devid)))
fhwc_out.write(devid)
fhwc_out.write(hwc_payload[devid_idxs[1]:])
fhwc_out.close()



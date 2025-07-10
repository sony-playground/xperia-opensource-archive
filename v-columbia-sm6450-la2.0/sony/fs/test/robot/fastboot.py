#!/usr/bin/env python
'''
Copyright (c) 2017, Sony Mobile Communications Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS")AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

'''

import sys
import os
import usb.core
import usb.util
import csv

__version__ = '0.1'

def usage():
	print("usage: fastboot [ <option> ] <command>")
	#print("  update <filename>                        Reflash device from update.zip.")
	#print("                                           Sets the flashed slot as active.")
	#print("  flashall                                 Flash boot, system, vendor, and --")
	#print("                                           if found -- recovery. If the device")
	#print("                                           supports slots, the slot that has")
	#print("                                           been flashed to is set as active.")
	#print("                                           Secondary images may be flashed to")
	#print("                                           an inactive slot.")
	print("  flash <partition> [ <filename> ]         Write a file to a flash partition.")
	#print("  flashing lock                            Locks the device. Prevents flashing.")
	#print("  flashing unlock                          Unlocks the device. Allows flashing")
	#print("                                           any partition except")
	#print("                                           bootloader-related partitions.")
	#print("  flashing lock_critical                   Prevents flashing bootloader-related")
	#print("                                           partitions.")
	#print("  flashing unlock_critical                 Enables flashing bootloader-related")
	#print("                                           partitions.")
	#print("  flashing get_unlock_ability              Queries bootloader to see if the")
	#print("                                           device is unlocked.")
	#print("  flashing get_unlock_bootloader_nonce     Queries the bootloader to get the")
	#print("                                           unlock nonce.")
	#print("  flashing unlock_bootloader <request>     Issue unlock bootloader using request.")
	#print("  flashing lock_bootloader                 Locks the bootloader to prevent")
	#print("                                           bootloader version rollback.")
	print("  erase <partition>                        Erase a flash partition.")
	#print("  format[:[<fs type>][:[<size>]] <partition>")
	#print("                                           Format a flash partition. Can")
	#print("                                           override the fs type and/or size")
	#print("                                           the bootloader reports.")
	print("  getvar <variable>                        Display a bootloader variable.")
	print("  set_active <slot>                        Sets the active slot. If slots are")
	print("                                           not supported, this does nothing.")
	#print("  boot <kernel> [ <ramdisk> [ <second> ] ] Download and boot kernel.")
	#print("  flash:raw boot <kernel> [ <ramdisk> [ <second> ] ]")
	#print("                                           Create bootimage and flash it.")
	#print("  devices [-l]                             List all connected devices [with")
	#print("                                           device paths].")
	print("  download <data file>                     Download data in <data file> to the device")
	print("                                           Could be used in combination with the")
	print("                                           signature command.")
	print("  signature [<signature file>]             Verify previously downloaded data.")
	print("                                           If a <signature file> is given it used")
	print("                                           for the verification. Required if the")
	print("                                           bootloader is 'secure' otherwise 'flash'")
	print("                                           and 'boot' will be ignored.")
	print("  continue                                 Continue with autoboot.")
	print("  reboot [bootloader]                      Reboot device [into bootloader].")
	print("  reboot-bootloader                        Reboot device into bootloader.")
	print("  powerdown                                Power off the device.")
	print("  help                                     Show this help message.")
	print("")
	print("SONY extension:")
	print("  Format-TA <partition>                    Formats the TA partition <partition>")
	print("                                           Valid partitions are between 0-9")
	print("  Read-TA <ta_partition> <unit> <ta_file>  Read data in unit <unit> in TA")
	print("                                           partition <ta_partition> to file")
	print("                                           <ta_file>. Valid partitions are between 0-9.")
	print("  Write-TA <ta_partition> <unit> <ta_file> Write data in <ta_file> to unit")
	print("                                           <unit> in TA partition <ta_partition>.")
	print("                                           Valid partitions are between 0-9.")
	print("  Getlog <log_file>                        Read loader log and save it to")
	print("                                           <log_file>.")
	print("  Getnvlog <log_file>                      Read non volatile log and save it to")
	print("                                           <log_file>.")
	print("  Get-security <file>                      Get security properties and save them")
	print("                                           in file <file>.")
	print("  Read-all-TA <ta_partition> <ta_file>     Read data in TA partition <partition>")
	print("                                           and save in file <ta_file>.")
	print("  Get-root-key-hash <file>                 Return a SHA256 of the platform")
	print("                                           root key in file <file>.")
	print("  Charge <percentage>                      Charge the device to the requested")
	print("                                           percentage.")
	print("  Authenticate:challenge [<level>] <challenge> Ask the client for a SAKE challenge")
	print("                                           message for level <level>. The challenge")
	print("                                           message is received in file <challenge>.")
	print("                                           <level> is either 0 for CS or 1 for")
	print("                                           PRODUCTION (default).")
	print("  Authenticate:response <response>         Send a SAKE response message to the")
	print("                                           client. The response message is")
	print("                                           provided in file <response>.")
	print("  Get-partition-list <file>                Gets all partitions on the device.")
	print("                                           The response is given as ascii strings")
	print("                                           separated by comma and put into file")
	print("                                           <file>.")
	print("  Read-partition <p> <file>                Read partition <p> into file <file>.")
	print("  Read-sector <l> <s> <e> <file>           Read flash from start sector <s>")
	print("                                           until end sector <e> on lun <l>")
	print("                                           into file <file>")
	print("  Repartition [<lun>]                      Repartition system. In the UFS case")
	print("                                           <lun> represent the desired LUN to")
	print("                                           repartition. The LUN value is a number")
	print("                                           starting from zero. If emmc is used,")
	print("                                           <lun> should be omitted.")
	print("  Sync                                     Synchronize cache and purge unmapped")
	print("                                           memory.")
	print("  Digest <p> <file>                        Calculate a digest of the entire")
	print("                                           partition <p>. The result is returned")
	print("                                           as a SHA256 hash in file <file>.")
	print("  Get-emmc-info <file>                     Gets info about the EMMC memory")
	print("                                           The response is put into file <file>.")
	print("  Get-ufs-info <file>                      Gets the UFS device descriptor")
	print("                                           followed by unit descriptors for each")
	print("                                           configured lun in one chunk of data.")
	print("                                           The response is put into file <file>.")
	print("  Get-gpt-info [<lun>] <file>              Get GPT info. In the UFS case, <lun>")
	print("                                           represents the desired LUN from which")
	print("                                           to get the info. The LUN value is a")
	print("                                           number starting from zero. If emmc is")
	print("                                           used the <lun> should be omitted.")
	print("                                           The data contains the MBR, GPT header")
	print("                                           and partition table and is put into")
	print("                                           file <file>.")
	print("  Reset-rollback-counter                   Reset rollback counters for Verified")
	print("                                           Boot to allow downgrade of software.")
	print("  Reset-frp                                Erase the frp partition.")
	print("  Secure-erase <partition>                 Do secure erase of given partition.")
	print("  Reboot-bootloader                        Reboot device into vendor fastboot.")
	print("  Set-ship-mode                            Enters 'Ship mode'.")
	print("  Enable-display                           Enables the display.")
	print("  Disable-display                          Disables the display.")

class FBProt:
	""" Fastboot protocol with Sony extensions.

	Detects, communicates and holds information about one device.
	"""

	##### Private functions #####

	def __init__(self, verbose=False):
		self.dev = None
		self.verbose = verbose

	def put_request(self, cmd):
		if self.verbose:
			print('--put_request: {}'.format(cmd))
		s = self.dev.write(0x01, cmd, 0)
		# assert s == len(cmd), 'ERROR: FBProt put_request, not all data was sent'

	def get_response(self):
		rs = bytearray(self.dev.read(0x81, 64, 0)).decode()
		if self.verbose:
			print('--get_response: {}'.format(rs))
		return rs[:4], rs[4:]

	def get_data(self, rd):
		datalen = int(rd, 16)
		if datalen > 0:
			max_read = 8*1024*1024
			if datalen > max_read:
				n_to_read = max_read
			else:
				n_to_read = datalen
			data = self.dev.read(0x81, n_to_read)
			#print('Got {} bytes. expected {}'.format(len(data), datalen))
			while len(data) < datalen:
				if datalen - len(data) > max_read:
					n_to_read = max_read
				else:
					n_to_read = datalen - len(data)
				more_data = self.dev.read(0x81, n_to_read)
				data += more_data
				#print('Got {} more bytes. remaining {}'.format(len(more_data), datalen - len(data)))
		else:
			data = None
		return data

	def put_data(self, data):
		s = self.dev.write(0x01, data, 0)
		# assert s == datalen, 'ERROR: FBProt not all data was sent {} != {}'.format(s, datalen)

	###### Public functions #####

	def connect(self, product=0xb00b):
		dev = None
		devs = usb.core.find(find_all=True, idVendor=0x0fce, idProduct=product)
		# find device which is not already busy
		for d in devs:
			try:
				usb.util.claim_interface(d, 0)
				dev = d
				break
			except usb.core.USBError as e:
				if e.errno == 5:	# input/output error
					pass
				elif e.errno == 16:	# resource busy
					pass
				elif e.errno == 19:	# no such device
					pass
				elif e.errno == 13:	# insufficient permissions
					pass
				else:
					print('device: {} WARNING: USB core problem: {}'.format('INIT', e))
					raise e
		msn = None
		if dev:
			self.dev = dev
			msn = self.getvar('serialno')
		return msn

	def authenticate_challenge(self, f, level):
		if level == None:
			self.put_request('SAKE-Authenticate:challenge')
		else:
			self.put_request('SAKE-Authenticate:challenge,{}'.format(level))
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def authenticate_response(self, data):
		rs, rd = self.download(data)
		if rs == 'OKAY':
			self.put_request('SAKE-Authenticate:response')
			r = self.get_response()
		return r

	def charge(self, percentage):
		self.put_request('Charge:{}'.format(percentage))
		r = self.get_response()
		return r

	def continue_cmd(self):
		self.put_request('continue')
		r = self.get_response()
		return r

	def digest(self, partition, f):
		self.put_request('Digest:{}'.format(partition))
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def disable_display(self):
		self.put_request('Disable-display')
		r = self.get_response()
		return r

	def download(self, data):
		datalen = len(data)
		if datalen > 0:
			self.put_request('download:{:08x}'.format(datalen))
			rs, rd = self.get_response()
			if rs == 'DATA':
				data_to_send = int(rd, 16)
				if data_to_send != datalen:
					rs = 'FAIL'
					rd = 'unable to send all data ({} of {}) in one chunk'.format(data_to_send, datalen)
					return rs, rd
				self.put_data(data)
				rs, rd = self.get_response()
		else:
			rs = 'OKAY'
			rd = ''
		return rs, rd

	def enable_display(self):
		self.put_request('Enable-display')
		r = self.get_response()
		return r

	def erase(self, partition):
		self.put_request('erase:{}'.format(partition))
		r  = self.get_response()
		return r

	def secure_erase(self, partition):
		self.put_request('Secure-erase:{}'.format(partition))
		r  = self.get_response()
		return r

	def flash_data(self, image_data, partition):
		rs, rd = self.download(image_data)
		if rs == 'OKAY':
			self.put_request('flash:{}'.format(partition))
			rs, rd = self.get_response()
		return rs, rd

	def flash_data_file(self, f, datalen, partition):
		self.put_request('download:{:08x}'.format(datalen))
		rs, rd = self.get_response()
		if rs == 'DATA':
			data_to_send = int(rd, 16)
			if data_to_send != datalen:
				rs = 'FAIL'
				rd = 'unable to send all data ({} of {}) in one chunk'.format(data_to_send, datalen)
				return rs, rd
			stot = 0
			for i in chunk_file(f, 0x200000, datalen):
				s = self.dev.write(0x01, i, 0)
				stot += s
			rs, rd = self.get_response()

		if rs == 'OKAY':
			self.put_request('flash:{}'.format(partition))
			rs, rd = self.get_response()
		return rs, rd

	def format_ta(self, partition):
		if partition == None or partition == '':
			self.put_request('Format-TA')
		else:
			self.put_request('Format-TA:{}'.format(partition))
		r = self.get_response()
		return r

	def getvar(self, var):
		self.put_request('getvar:{}'.format(var))
		rs,rd = self.get_response()
		while rs == 'INFO':
			print(rd)
			rs,rd = self.get_response()
		return rs,rd

	def get_emmc_info(self, f):
		self.put_request('Get-emmc-info')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def get_log(self, f):
		self.put_request('Getlog')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def get_nvlog(self, f):
		self.put_request('Getnvlog')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def get_partition_list(self, f):
		self.put_request('Get-partition-list')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def get_root_key_hash(self, f):
		self.put_request('Get-root-key-hash')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def get_security(self, f):
		self.put_request('Get-security')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def get_ufs_info(self, f):
		self.put_request('Get-ufs-info')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def get_gpt_info(self, f, lun):
		self.put_request('Get-gpt-info:{}'.format(lun))
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def powerdown(self):
		self.put_request('powerdown')
		rs, rd = self.get_response()
		return rs,rd

	def read_partition(self, partition, f):
		self.put_request('Read-partition:{}'.format(partition))
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def read_sector(self, lun, start, end, f):
		self.put_request('Read-sector:{}:{}:{}'.format(lun, start, end))
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def reboot(self, arg):
		if arg == None:
			self.put_request('reboot')
		else:
			self.put_request('reboot {}'.format(arg))
		r = self.get_response()
		return r

	def reboot_bootloader(self):
		self.put_request('reboot-bootloader')
		r = self.get_response()
		return r

	def reboot_bootloader_vendor(self):
		self.put_request('Reboot-bootloader')
		r = self.get_response()
		return r

	def repartition(self, lun):
		if lun == None:
			self.put_request('Repartition')
		else:
			self.put_request('Repartition:{}'.format(lun))
		r = self.get_response()
		return r

	def reset_frp(self):
		self.put_request('Reset-frp')
		r = self.get_response()
		return r

	def reset_rollback_counter(self):
		self.put_request('Reset-rollback-counter')
		r = self.get_response()
		return r

	def set_active(self, slot):
		self.put_request('set_active:{}'.format(slot))
		r = self.get_response()
		return r

	def set_ship_mode(self):
		self.put_request('Set-ship-mode')
		r = self.get_response()
		return r

	def signature(self, signature_data = None):
		rs = 'OKAY'
		if signature_data != None:
			rs, rd = self.download(signature_data)
		if rs == 'OKAY':
			self.put_request('signature')
			rs, rd = self.get_response()
		return rs, rd

	def sync(self):
		self.put_request('Sync')
		r = self.get_response()
		return r

	def ta_read(self, partition, unit, f):
		self.put_request('Read-TA:{}:{}'.format(partition, unit))
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs, rd

	def ta_read_all(self, partition, f):
		self.put_request('Read-all-TA:{}'.format(partition))
		rs, rd = self.get_response()
		if rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs, rd

	def ta_write(self, partition, unit, data):
		rs, rd = self.download(data)
		if rs == 'OKAY':
			self.put_request('Write-TA:{}:{}'.format(partition, unit))
			rs,rd = self.get_response()
		return rs,rd

# End of class FBProt

def chunk_image(image, chunksize):
	imagesize = len(image)
	for i in range(0, imagesize, chunksize):
		yield (image[i: i + chunksize], i + chunksize < imagesize)


def chunk_file(f, chunksize, filesize):
	cursize = 0
	while cursize < filesize:
		data = f.read(chunksize)
		cursize += len(data)
		yield data


#######################
# Interface functions #
#######################

def authenticate_challenge(arg1, arg2 = None):
	if arg2 == None:
		# level was not given, so set challenge to arg1
		challenge = arg1
		level = None
	else:
		level = arg1
		challenge = arg2
	f = open(challenge, "wb")
	r = fbp.authenticate_challenge(f, level)
	f.close()
	print("{}{}".format(r[0], r[1]))

def authenticate_response(response):
	f = open(response, "rb")
	data = f.read()
	f.close()
	r = fbp.authenticate_response(data)
	print("{}{}".format(r[0], r[1]))

def charge(percentage):
	r = fbp.charge(percentage)
	print("{}{}".format(r[0], r[1]))

def continue_cmd():
	r = fbp.continue_cmd()
	print("{}{}".format(r[0], r[1]))

def digest(partition, sha_file):
	f = open(sha_file, "wb")
	r = fbp.digest(partition, f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def disable_display():
	r = fbp.disable_display()
	print("{}{}".format(r[0], r[1]))

def download(filename):
	f = open(filename, "rb")
	data = f.read()
	f.close()
	r = fbp.download(data)
	print("{}{}".format(r[0], r[1]))

def enable_display():
	r = fbp.enable_display()
	print("{}{}".format(r[0], r[1]))

def erase(partition):
	r = fbp.erase(partition)
	print("{}{}".format(r[0], r[1]))

def secure_erase(partition):
	r = fbp.secure_erase(partition)
	print("{}{}".format(r[0], r[1]))

def flash(partition, image_file):
	f = open(image_file, "rb")
	size = os.path.getsize(image_file)
	r = fbp.flash_data_file(f, size, partition)
	f.close
	print("{}{}".format(r[0], r[1]))

def format_ta(partition = None):
	r = fbp.format_ta(partition)
	print("{}{}".format(r[0], r[1]))

def getvar(variable):
	r = fbp.getvar(variable)
	print("{}{}".format(r[0], r[1]))

def get_emmc_info(emmc_info_file):
	f = open(emmc_info_file, "wb")
	r = fbp.get_emmc_info(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def get_log(log_file):
	f = open(log_file, "wb")
	r = fbp.get_log(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def get_nvlog(log_file):
	f = open(log_file, "wb")
	r = fbp.get_nvlog(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def get_partition_list(partitions_file):
	f = open(partitions_file, "wb")
	r = fbp.get_partition_list(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def get_root_key_hash(hash_file):
	f = open(hash_file, "wb")
	r = fbp.get_root_key_hash(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def get_security(security_file):
	f = open(security_file, "wb")
	r = fbp.get_security(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def get_ufs_info(ufs_info_file):
	f = open(ufs_info_file, "wb")
	r = fbp.get_ufs_info(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def get_gpt_info(arg1, arg2 = None):
	if arg2 is None:
		lun = 0
		gpt_file = arg1
	else:
		lun = arg1
		gpt_file = arg2
	f = open(gpt_file, "wb")
	r = fbp.get_gpt_info(f, lun)
	f.close()
	print("{}{}".format(r[0], r[1]))

def powerdown():
	r = fbp.powerdown()
	print("{}{}".format(r[0], r[1]))

def read_partition(partition, image_file):
	f = open(image_file, "wb")
	r = fbp.read_partition(partition, f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def read_sector(lun, start, end, image_file):
	f = open(image_file, "wb")
	r = fbp.read_sector(lun, start, end, f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def read_all_ta(partition, ta_file):
	f = open(ta_file, "wb")
	r = fbp.ta_read_all(partition, f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def read_ta(partition, unit, ta_file):
	f = open(ta_file, "wb")
	r = fbp.ta_read(partition, unit, f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def reboot(bootloader = None):
	r = fbp.reboot(bootloader)
	print("{}{}".format(r[0], r[1]))

def reboot_bootloader():
	r = fbp.reboot_bootloader()
	print("{}{}".format(r[0], r[1]))

def reboot_bootloader_vendor():
	r = fbp.reboot_bootloader_vendor()
	print("{}{}".format(r[0], r[1]))

def repartition(lun = None):
	r = fbp.repartition(lun)
	print("{}{}".format(r[0], r[1]))

def reset_frp():
	r = fbp.reset_frp()
	print("{}{}".format(r[0], r[1]))

def reset_rollback_counter():
	r = fbp.reset_rollback_counter()
	print("{}{}".format(r[0], r[1]))

def set_active(slot):
	r = fbp.set_active(slot)
	print("{}{}".format(r[0], r[1]))

def set_ship_mode():
	r = fbp.set_ship_mode()
	print("{}{}".format(r[0], r[1]))

def signature(signature_file = None):
	if signature_file != '':
		f = open(signature_file, "rb")
		data = f.read()
		f.close()
	else:
		data = None
	r = fbp.signature(data)
	print("{}{}".format(r[0], r[1]))

def sync():
	r = fbp.sync()
	print("{}{}".format(r[0], r[1]))

def write_ta(partition, unit, ta_file):
	f = open(ta_file, "rb")
	data = f.read()
	f.close()
	r = fbp.ta_write(partition, unit, data)
	print("{}{}".format(r[0], r[1]))

if __name__ == '__main__':
	actions = {
		'Authenticate:challenge': authenticate_challenge,
		'Authenticate:response': authenticate_response,
		'Charge': charge,
		'continue': continue_cmd,
		'Digest': digest,
		'Disable-display' : disable_display,
		'download': download,
		'Enable-display' : enable_display,
		'erase': erase,
		'flash': flash,
		'Format-TA': format_ta,
		'getvar': getvar,
		'Getlog': get_log,
		'Getnvlog' : get_nvlog,
		'Get-emmc-info': get_emmc_info,
		'Get-gpt-info': get_gpt_info,
		'Get-partition-list': get_partition_list,
		'Get-root-key-hash':get_root_key_hash,
		'Get-security': get_security,
		'Get-ufs-info': get_ufs_info,
		'powerdown': powerdown,
		'Read-partition': read_partition,
		'Read-sector': read_sector,
		'Read-all-TA': read_all_ta,
		'Read-TA': read_ta,
		'reboot': reboot,
		'reboot-bootloader': reboot_bootloader,
		'Reboot-bootloader': reboot_bootloader_vendor,
		'Repartition': repartition,
		'Reset-frp': reset_frp,
		'Reset-rollback-counter': reset_rollback_counter,
		'Secure-erase': secure_erase,
		'set_active': set_active,
		'Set-ship-mode' : set_ship_mode,
		'signature': signature,
		'Sync': sync,
		'Write-TA': write_ta,
		'help': usage }
	try:
		action = sys.argv[1]
	except IndexError:
		action = 'help'
	args = sys.argv[2:]

	fbp = FBProt()
	msn = fbp.connect()
	if msn:
		actions[action](*args)
	else:
		print('No device found')

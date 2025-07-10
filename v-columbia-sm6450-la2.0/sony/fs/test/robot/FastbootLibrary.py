import os
import subprocess
import sys
import filecmp
import csv
import time
from RobotVariables import *

TIMEOUT = 600

class FastbootLibrary(object):
	def __init__(self):
		self._sut_path = os.path.join(os.path.dirname(__file__), 'fastboot.py')
		self._sut_path_bad = os.path.join(os.path.dirname(__file__), 'badfastboot.py')
		self._sut_path_vendor = os.path.join(os.path.dirname(__file__), 'vendorfastboot.py')
		self._status = ''
		self._data = None

	def adb_reboot_into_xfl(self):
		command = ['adb', 'reboot', 'oem-53']
		process = subprocess.Popen(command, universal_newlines=True, stdout=subprocess.PIPE,
								stderr=subprocess.STDOUT)
	def adb_wait_for_device(self):
		command = ['adb', 'get-state']
		response = ''
		t = 0
		while response != 'device' and t < TIMEOUT:
			time.sleep(3)
			t = t + 3
			process = subprocess.Popen(command, universal_newlines=True, stdout=subprocess.PIPE,
								stderr=subprocess.STDOUT)
			response = process.communicate()[0].strip()
		if t >= TIMEOUT:
			raise AssertionError("adb is not accessible, response = " + response)

	def wait_for_fastboot_device(self):
		command = ['fastboot', 'devices']
		response = ''
		t = 0
		while response != 'fastboot' and t < TIMEOUT:
			time.sleep(3)
			t = t + 3
			process = subprocess.Popen(command, universal_newlines=True, stdout=subprocess.PIPE,
								stderr=subprocess.STDOUT)
			response = process.communicate()[0].strip()
			# Extract 'fastboot' from expected '<serial> fastboot' response
			responseList = response.rsplit()
			if len(responseList) > 0:
				response = responseList[len(responseList)-1]
			print(response)
		if t >= TIMEOUT:
			raise AssertionError("Service mode not entered, fastboot devices returns " + response)

	def authenticate_challenge(self, challenge, level = None):
		if level == None:
			self._run_command("Authenticate:challenge", challenge)
		else:
			self._run_command("Authenticate:challenge", level, challenge)

	def bad_authenticate_challenge(self, challenge):
		self._run_bad_command("Authenticate:challenge", challenge)

	def authenticate_response(self, response):
		self._run_command("Authenticate:response", response)

	def bad_authenticate_response(self, response):
		self._run_bad_command("Authenticate:response", response)

	def charge(self, percentage):
		self._run_command('Charge', percentage)

	def continue_cmd(self):
		self._run_command('continue')

	def vendor_continue_cmd(self):
		self._run_vendor_command('continue')

	def digest(self, partition, sha_file):
		self._run_command('Digest', partition, sha_file)

	def download(self, data_file):
		self._run_command('download', data_file)

	def erase(self, partition):
		self._run_command('erase', partition)

	def flash(self, partition, image_file):
		self._run_command('flash', partition, image_file)

	def format_ta(self, partition = ''):
		self._run_command('Format-TA', partition)

	def getvar(self, variable, expected_response = 'OKAY'):
		if expected_response == 'OKAY':
			global gVarLists
			gVarLists.getvar_list.append(variable)
		self._run_command('getvar', variable)

	def getvar_all(self):
		# In this function we execute the command 'getvar all', which returns
		# a lot of variables and their values. Variables are separated from
		# values by a colon. We want to add all variables, but not their values,
		# to the list 'getvar_all_list'.
		# Normally the answers from 'getvar all' look like this: 'Device-id:EBC3F98D'
		# We need to remove the value so that only the variable remains. However,
		# often the answers look like this: 'has-slot:frp:no'
		# Here we see that the variable is 'has-slot:frp' and the value is 'no'.
		# Therefore we divide the string into two parts, 'has-slot:frp' and 'no',
		# and only add 'has-slot:frp' to the list. However, the variable 'Phone-id'
		# is an exception. The returned string from 'getvar all' may look like this:
		# 'Phone-id:0000:00440254199951'
		# Here the variable is 'Phone-id' and the value is '0000:00440254199951'.
		# Therefore we divide the string into two parts in such a way that only
		# 'Phone-id' will be added to the list.

		self._run_command('getvar', 'all')

		whole_string = gFastbootResponse.status + gFastbootResponse.value
		var_list = whole_string.split()
		for item in var_list:
			global gVarLists
			if item == 'OKAY':
				gVarLists.getvar_all_result = item
			elif item[:9] == 'Phone-id:':
				gVarLists.getvar_all_list.append(item.split(':', 1)[0])
			else:
				gVarLists.getvar_all_list.append(item.rsplit(':', 1)[0])

	def vendor_getvar(self, variable):
		self._run_vendor_command('getvar', variable)

	def get_log(self, log_file):
		self._run_command('Getlog', log_file)

	def get_partition_list(self, partitions_file):
		self._run_command('Get-partition-list', partitions_file)

	def get_root_key_hash(self, hash_file):
		self._run_command('Get-root-key-hash', hash_file)

	def get_security(self, security_file):
		self._run_command('Get-security', security_file)

	def get_ufs_info(self, ufs_info_file):
		self._run_command('Get-ufs-info', ufs_info_file)

	def get_emmc_info(self, emmc_info_file):
		self._run_command('Get-emmc-info', emmc_info_file)

	def read_all_ta(self, partition, ta_file):
		self._run_command('Read-all-TA', partition, ta_file)

	def read_partition(self, partition, image_file):
		self._run_command('Read-partition', partition, image_file)

	def reboot(self, bootloader = ''):
		self._run_command('reboot', bootloader)

	def reboot_bootloader(self):
		self._run_command('reboot-bootloader')

	def reboot_bootloader_vendor(self):
		self._run_command('Reboot-bootloader')

	def repartition(self, lun = ''):
		self._run_command('Repartition', lun)

	def read_ta(self, partition, unit, ta_file):
		self._run_command('Read-TA', partition, unit, ta_file)

	def reset_frp(self):
		self._run_command('Reset-frp')

	def reset_rollback_counter(self):
		self._run_command('Reset-rollback-counter')

	def set_active(self, slot):
		self._run_command('set_active', slot)

	def signature(self, signature_file = ''):
		self._run_command('signature', signature_file)

	def sync(self):
		self._run_command('Sync')

	def write_ta(self, partition, unit, ta_file):
		self._run_command('Write-TA', partition, unit, ta_file)

	def response_should_be(self, expected_status):
		global gFastbootResponse

		if expected_status != self._status[:4]:
			raise AssertionError("Expected status to be '%s' but was '%s'"
				% (expected_status, self._status))

	def data_should_be(self, expected_data_file, received_data_file):
		if not filecmp.cmp(expected_data_file, received_data_file):
			raise AssertionError("Expected data in file '%s' differs from received data in file '%s'"
				% (expected_data_file, received_data_file))

	def check_if_response_from_getvar_all_is_okay(self):
		if gVarLists.getvar_all_result != 'OKAY':
			raise AssertionError("Response from 'getvar all' was not 'OKAY'")

	def check_if_all_tested_vars_are_in_getvar_all(self):
		for item in gVarLists.getvar_list:
			if item not in gVarLists.getvar_all_list:
				raise AssertionError("Variable '%s' is not returned by 'getvar all'" % item)

	def check_if_all_vars_in_getvar_all_are_tested(self):
		for item in gVarLists.getvar_all_list:
			if item not in gVarLists.getvar_list:
				raise AssertionError("Variable '%s' has not been tested" % item)

	def send_challenge_to_secs(self, challenge, response):
		# export LD_LIBRARY_PATH='path to libsecs.so'
		os.putenv("LD_LIBRARY_PATH", ".")
		os.system("./secsauth {} {}".format(challenge, response))

	def create_list_from_csv(self, csv_file):
		plist = []
		with open(csv_file, 'rb') as csvfile:
			lst = csv.reader(csvfile, delimiter=',')
			for row in lst:
				for p in row:
					plist.append(p)
			csvfile.close
		return plist

	def create_random_ta_data (self, ta_file):
		with open(ta_file, 'wb') as taFile:
			taFile.write("RANDOM")
			taFile.close

	def _run_command(self, command, *args):
		global gFastbootResponse

		command = [sys.executable, self._sut_path, command] + list(args)
		process = subprocess.Popen(command, universal_newlines=True, stdout=subprocess.PIPE,
								stderr=subprocess.STDOUT)
		self._status = process.communicate()[0].strip()
		gFastbootResponse.status = self._status[:4]
		gFastbootResponse.value = self._status[4:]

	def _run_bad_command(self, command, *args):
		global gFastbootResponse

		command = [sys.executable, self._sut_path_bad, command] + list(args)
		process = subprocess.Popen(command, universal_newlines=True, stdout=subprocess.PIPE,
								stderr=subprocess.STDOUT)
		self._status = process.communicate()[0].strip()
		gFastbootResponse.status = self._status[:4]
		gFastbootResponse.value = self._status[4:]

	def _run_vendor_command(self, command, *args):
		global gFastbootResponse

		command = [sys.executable, self._sut_path_vendor, command] + list(args)
		process = subprocess.Popen(command, universal_newlines=True, stdout=subprocess.PIPE,
								stderr=subprocess.STDOUT)
		self._status = process.communicate()[0].strip()
		gFastbootResponse.status = self._status[:4]
		gFastbootResponse.value = self._status[4:]

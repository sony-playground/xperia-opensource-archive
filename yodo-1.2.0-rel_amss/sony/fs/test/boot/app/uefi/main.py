#!/usr/bin/python

import sys
import os
from serial import Serial
import time

hwstate_argidx_startup_flag = 0
hwstate_argidx_reset_detect = 2
hwstate_argidx_usb_otg_detect = 4
hwstate_argidx_pwr_but_pres_time = 5
hwstate_argidx_vldwn_but_pres_time = 6
hwstate_argidx_vlup_but_pres_time = 7
startup_flag_pon = 1
startup_flag_vbus = 4
startup_flag_hard_reset = 8

manual_wait_sec = 300

def extract_tcstate_params(strlog):
	param_begin = "PARAM TCSTATE <<<<<<\r\n"
	param_end = "\r\n>>>>>>> TCSTATE PARAM"
	str_extract_param = ""
	idx_cur = 0
	idx_found_begin = strlog.find(param_begin, idx_cur)
	idx_found_end = -1
	while (idx_found_begin > -1):
		idx_cur = idx_found_begin + len(param_begin)
		idx_found_end = strlog.find(param_end, idx_cur);
		if (idx_found_end > -1):
			idx_cur = idx_found_end + len(param_end)
			str_extract_param = strlog[idx_found_begin+len(param_begin):idx_found_end]
			idx_found_begin = strlog.find(param_begin, idx_cur)
		else:
			idx_found_begin = -1;
	return str_extract_param

match = ""

def extract_hwstate_params(strlog):
	param_begin = "PARAM HWSTATE <<<<<<\r\n"
	param_end = "\r\n>>>>>>> HWSTATE PARAM"
	str_extract_param = ""
	idx_cur = 0
	idx_found_begin = strlog.find(param_begin, idx_cur);
	while (idx_found_begin > -1):
		idx_cur = idx_found_begin + len(param_begin)
		idx_found_end = strlog.find(param_end, idx_cur)
		if (idx_found_end > -1):
			idx_cur = idx_found_end + len(param_end)
			str_extract_param = strlog[idx_found_begin+len(param_begin):idx_found_end]
			idx_found_begin = strlog.find(param_begin, idx_cur)
		else:
			idx_found_begin = -1
	return str_extract_param

def extract_test_logs(strlog):
	param_begin = "TEST <<<<<<\r\n"
	param_end = "\r\n>>>>>>> TEST"
	str_extract_log = ""
	idx_cur = 0
	idx_found_begin = strlog.find(param_begin, idx_cur);
	while (idx_found_begin > -1):
		idx_cur = idx_found_begin + len(param_begin)
		idx_found_end = strlog.find(param_end, idx_cur)
		if (idx_found_end > -1):
			idx_cur = idx_found_end + len(param_end)
			str_extract_log = str_extract_log + "\n" + strlog[idx_found_begin+len(param_begin):idx_found_end]
			idx_found_begin = strlog.find(param_begin, idx_cur)
		else:
			idx_found_begin = -1
	return str_extract_log

def extract_integration_logs(strlog):
	param_begin = "INTEGRATION <<<<<<\r\n"
	param_end = "\r\n>>>>>>> INTEGRATION"
	str_extract_log = ""
	idx_cur = 0
	idx_found_begin = strlog.find(param_begin, idx_cur);
	while (idx_found_begin > -1):
		idx_cur = idx_found_begin + len(param_begin)
		idx_found_end = strlog.find(param_end, idx_cur)
		if (idx_found_end > -1):
			idx_cur = idx_found_end + len(param_end)
			str_extract_log = str_extract_log + "\n" + strlog[idx_found_begin+len(param_begin):idx_found_end]
			idx_found_begin = strlog.find(param_begin, idx_cur)
		else:
			idx_found_begin = -1
	return str_extract_log

def append_fail_info(fail_list, strlog):
	pattern1 = "tests failed in module "
	pattern2 = "Failed to run tests in module "
	matchpattern = pattern1
	idx = strlog.find(matchpattern, 0)
	if idx == -1:
		matchpattern = pattern2
		idx = strlog.find(matchpattern, 0)
	if not idx == -1:
		idx_begin = idx + len(matchpattern)
		idx = strlog.find("\r", idx_begin)
		if idx == -1:
			idx = idx_begin
		idx = strlog.find("\n", idx)
		fail_list = fail_list +  strlog[idx_begin:idx] + "\r\n"
	return fail_list

#match = ""

def extract_params(strlog):
	tcstate_param = extract_tcstate_params(strlog)
	hwstate_param = extract_hwstate_params(strlog)
	return [tcstate_param, hwstate_param]

def extract_logs(strlog):
	int_logs = extract_integration_logs(strlog)
	test_logs = extract_test_logs(strlog)
	return [int_logs, test_logs]

def wait_pattern(port, logfile, wait_sec, match_str):
	strlog = ""
	match_index = 0;
	match_end = len(match_str)
	retries = wait_sec
	while (port.isOpen() and
		(match_index < match_end) and
		(retries > 0)):
		Char = '\0'
		Char = port.read(1)
		if (Char == '\0'):
			#sys.stdout.write('#')
			#sys.stdout.flush()
			if (retries > 2):
				retries = 2
			else:
				retries = retries - 1
		elif (not Char == ''):
			retries = wait_sec
			strlog = strlog + Char
			if not logfile.closed:
				logfile.write(Char)
				logfile.flush()
		else:
			retries = retries - 1

		if (match_str[match_index] == Char):
			match_index = match_index + 1
		else:
			match_index = 0
	if (match_index < match_end):
		return [False, strlog]
	else:
		return [True, strlog]

def wait_shutdown(port, logfile):
	Char = '\0'
	Char = port.read(1)
	while (port.isOpen() and
			not (Char == '\0')):
		Char = '\0'
		Char = port.read(1)
		if (not logfile.closed and
			(not Char == '\0') and
			(not Char == '')):
			logfile.write(Char)
			logfile.flush()

def fetch_list(port, logfile, wait_sec):
	print "--> Start device\n"

	res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
	print res[0]
	if not res[0] :
		return False

	port.write("list\n")

	res = wait_pattern(port, logfile, wait_sec, "print_modules:\r\n")
	if not res[0] :
		return False

	line = port.readline()
	print line,
	if not logfile.closed:
		logfile.write(line);
		logfile.flush()
	while (not line == "\r\n"):
		line = port.readline()
		print line,
		if not logfile.closed:
			logfile.write(line);
			logfile.flush()

# Returns AtPrompt
def get_prompt(port, logfile, wait_sec, prompt):
	if (not prompt):
		print "--> Manually [re]start device"

		res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
		return res[0]
	return prompt

# Returns [IsOK, AtPrompt, TCState, HWState, IntegrLog, TestLog]
def execute(port, logfile, wait_sec, prompt, match, arg):
	if (not prompt):
		res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
		if not res[0] :
			return [False, res[0], '', '']

	cmd = "execute"
	if (len(match) > 0):
		cmd = cmd + " " + match
	if (len(arg) > 0):
		cmd = cmd + " " + arg
	cmd = cmd + "\n"

	#print "Write to Serial:" + cmd
	port.write(cmd)

	res = wait_pattern(port, logfile, wait_sec, "XBootTest>")

	params = extract_params(res[1])
	logs = extract_logs(res[1])

	return [True, res[0], params[0], params[1], logs[0], logs[1]]

def check_usb(port, logfile, wait_sec):
	port.write("usb\n")
	res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
	if not res[0] :
		return
	usb_state = res[1].find("USB:Yes");
	if not (usb_state == -1):
		print "--> Remove USB Cable!"
		while not (usb_state == -1):
			time.sleep(1)
			port.write("usb\n")
			res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
			if not res[0] :
				return
			usb_state = res[1].find("USB:Yes");
		time.sleep(1)
	return

def check_pon(port, logfile, wait_sec):
	port.write("pon\n")
	res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
	if not res[0] :
		return
	pon_state = res[1].find("PON:Yes");
	if not (pon_state == -1):
		print "--> Release PON Button!"
		while not (pon_state == -1):
			time.sleep(1)
			port.write("pon\n")
			res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
			if not res[0] :
				return
			pon_state = res[1].find("PON:Yes");
		time.sleep(1)
	return

def is_coldboot(port, logfile, wait_sec):
	port.write("coldboot\n")
	res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
	if not res[0] :
		return False
	pon_state = res[1].find("CB:Yes");
	if not (pon_state == -1):
		return True
	return False

# Returns IsOK
def apply_hwstate(port, logfile, wait_sec, prompt, arg):
	if (not prompt):
		# Wait for prompt
		res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
		if not res[0] :
			return False
		prompt = res[0]

	# Release PON if pressed
	check_pon(port, logfile, wait_sec)
	# Remove USB if present
	check_usb(port, logfile, wait_sec)
	# Check if cold boot
	if not is_coldboot(port, logfile, wait_sec):
		print "To set up HWState correctly device must initially be cold booted",
		print "- Shutting Down"
		cmd = "shutdown\n"
		port.write(cmd)
		wait_shutdown(port, logfile)
		if not get_prompt(port, logfile, wait_sec, False):
			return False
	arg_split = arg.split()
	if not (len(arg_split) == 8):
		return False

	# Send Apply HWState to device
	# If force restart or shutdown do nothing to prepare hwstate
	if int(arg_split[hwstate_argidx_reset_detect]) == 0:
		cmd = "hwstate " + arg_split[0] + " " + arg_split[1] +"\n"

		port.write(cmd)

	# Information to test user
	if int(arg_split[hwstate_argidx_pwr_but_pres_time]) > 0:
		#Power Button Pressed
		print "--> Manually Press Power Button for",
		print arg_split[hwstate_argidx_pwr_but_pres_time],
		print "msec"

	if int(arg_split[hwstate_argidx_vldwn_but_pres_time]) > 0:
		#Volume Down Button Pressed
		print "--> Manually Press Volume Down Button for",
		print arg_split[hwstate_argidx_vldwn_but_pres_time],
		print "msec"

	if int(arg_split[hwstate_argidx_vlup_but_pres_time]) > 0:
		#Volume Up Button Pressed
		print "--> Manually Press Volume Up Button for",
		print arg_split[hwstate_argidx_vlup_but_pres_time],
		print "msec"

	if (int(arg_split[0]) & startup_flag_vbus) > 0:
		#USB inserted
		if  int(arg_split[hwstate_argidx_usb_otg_detect]) == 0:
			print "--> Manually Insert USB"
		else:
			print "--> Manually Insert USB OTG"

	# Handle response for Apply HWState
	# If force restart or shutdown no response is expected
	if (int(arg_split[hwstate_argidx_pwr_but_pres_time]) > 0 and
		int(arg_split[hwstate_argidx_vlup_but_pres_time]) > 0):
		print "Ready..."
		wait_shutdown(port, logfile)
		# Wait for prompt
		res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
		#res = [False, '']
	else:
		wait_shutdown(port, logfile)
		print "Ready..."
		# Wait for prompt
		res = wait_pattern(port, logfile, wait_sec, "XBootTest>")
		#res = [False, '']
	return res[0]

match = ""
fail_list = ""

assert (len(sys.argv) == 3 or len(sys.argv) == 4),"Unexpected number of parameters!"

print sys.argv[0]

#port = Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=1)
port = Serial(port=sys.argv[1], baudrate=115200, timeout=1)
port.flushInput()
port.flushOutput()
#logfile = open("dump.txt", "ab")
logfile = open(sys.argv[2], "ab")

if len(sys.argv) == 4:
	print sys.argv[3]
	match = sys.argv[3]
	if (match == "list"):
		fetch_list(port, logfile, manual_wait_sec)
		port.close()
		sys.exit(0)

print "--> Start device\n"
res = execute(port, logfile, manual_wait_sec, False, match, "")
isok = res[0]
prompt = res[1]
tcstate = res[2]
hwstate = res[3]
while (isok and len(tcstate) > 0):
	isok = get_prompt(port, logfile, manual_wait_sec, prompt);
	if (isok):
		if (len(hwstate) > 0):
			isok = apply_hwstate(port, logfile, manual_wait_sec, True, hwstate)
	if (isok):
		print "\n\nExecute..."
		res = execute(port, logfile, manual_wait_sec, True, match, tcstate)
		isok = res[0]
		prompt = res[1]
		tcstate = res[2]
		hwstate = res[3]

		fail_list = append_fail_info(fail_list, res[5])

		print "Integration:"
		print res[4]
		print "Test framework:"
		print res[5]

logfile.close()
port.close()

if (len(fail_list) > 0):
	print
	print "Failing modules:"
	print fail_list

if (isok):
	print "Done!"
else:
	print "Done with error!"



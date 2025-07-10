#!/usr/bin/python

import sys
import os

def extract_tcstate_params( strlog ):
	param_begin = "PARAM TCSTATE <<<<<<\n"
	param_end = "\n>>>>>>> TCSTATE PARAM"
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

def extract_params( strlog ):
	str_extract_param = extract_tcstate_params( strlog )
	if (len(str_extract_param) > 0):
		str_extract_param = " " + str_extract_param
	return str_extract_param

match = ""

def check_result( strlog ):
	success_string = "execute_module done! n_failed:0"
	idx_found_end = strlog.find(success_string, 0)
	if (idx_found_end > -1):
		return 0 # Test OK
	else:
		return 1 # Test fail


assert (len(sys.argv) == 1 or len(sys.argv) == 2),"Unexpected number of parameters!"

print sys.argv[0]

if len(sys.argv) == 2:
	print sys.argv[1]
	match = sys.argv[1]
	if (match == "list"):
		stream = os.popen("./device_test --list")
		strstdout = stream.read()
		stream.close()
		print strstdout
		sys.exit(0)

str_extract_params = ""
if (len(match) > 0):
	str_extract_params = str_extract_params + " --match=\"" + match + "\""
print "Execute: \"./device_test\"" + str_extract_params
stream = os.popen("./device_test" + str_extract_params)
strstdout = stream.read()
stream.close()
print strstdout
str_extract_params = extract_params( strstdout )
while (len(str_extract_params) > 0):
	if (len(match) > 0):
		str_extract_params = str_extract_params + " --match=\"" + match + "\""
	print "Execute: \"./device_test" + str_extract_params + "\""
	stream = os.popen("./device_test" + str_extract_params)
	strstdout = stream.read()
	stream.close()
	print strstdout
	str_extract_params = extract_params( strstdout )

res = check_result(strstdout)
if res == 0:
	print "Test OK!"
	sys.exit(0)
else:
	print "Test Failed!"
	sys.exit(1)



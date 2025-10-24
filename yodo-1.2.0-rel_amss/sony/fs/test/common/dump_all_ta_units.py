#!/usr/bin/python

import sys
import binascii
import struct

assert (len(sys.argv) == 4),"Unexpected number of parameters!"

read_all_ta_in = open(sys.argv[2], "rb")

header = read_all_ta_in.read(4)
assert (header == 'DATA'),"Wrong file format!"
header_count = read_all_ta_in.read(8)

count = 0;
while True:
	unit = read_all_ta_in.read(4)
	if unit == 'OKAY':
		break
	assert (unit != ''),"Wrong file format!"
	count += 4
	int_unit = struct.unpack(">I", unit)
	unit_len = read_all_ta_in.read(4)
	assert (unit_len != ''),"Wrong file format!"
	count += 4
	int_unit_len = struct.unpack(">I", unit_len)
	filename = sys.argv[3]+'/'+sys.argv[1]+str(int_unit[0])+'.bin'
	unit_data = read_all_ta_in.read(int_unit_len[0])
	assert (len(unit_data) == int_unit_len[0]),"Wrong file format!"
	ta_file_out = open(filename, "wb")
	ta_file_out.write(unit_data)
	ta_file_out.close()
	count += int_unit_len[0]

assert (count == int(header_count, 16)),"Wrong count!"

read_all_ta_in.close()



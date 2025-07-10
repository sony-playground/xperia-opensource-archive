#! /usr/bin/env python
# -*- coding: utf-8 -*-
from distutils.command.build import build
import sys, subprocess
import os
import json
import re
import struct
from datetime import datetime
import inspect


message = ""


# non ascii check start
def parse_illegal_character(current_file, code_file):
    global message
    accumulated_size = 0
    current_file_size = os.path.getsize(current_file)
    #check the character in one byte, 
    #if the value is not in 0~127, it's not the stanstard ascii code
    error_positions = ""
    code_file.seek(0)
    while(accumulated_size < current_file_size):
        read_value = struct.unpack("B", code_file.read(1))
        
        if (read_value[0] > 127):
            error_positions += ("\tError position: %d, value: %d (0x%02x)\n" % (accumulated_size, read_value[0], read_value[0]))
        accumulated_size += 1
    if error_positions:
        file = str(current_file)      
        current_file_name = file.split('/')[::-1][0].split(' ')[0].replace("'","")
        message+="\nFile %s contains non-ASCII characters:\n%s"%(current_file_name,error_positions)
    return message
 # non ascii check end   

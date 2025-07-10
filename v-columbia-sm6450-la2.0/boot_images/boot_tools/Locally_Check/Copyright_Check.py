#! /usr/bin/env python
# -*- coding: utf-8 -*-
from distutils.command.build import build
import sys, subprocess
import os
import json
import re
import struct
from datetime import datetime




#  Copyright script check starting point 
copyright_required_strings = ['Copyright','Qualcomm','Inc','Technologies','All rights reserved']
copyright_required_format = 'Copyright (c) YYYY[Add modified years by seperating with comma(,)] Qualcomm Technologies, Inc. All rights reserved.' 
confidential_required_strings = ['Confidential and Proprietary','Qualcomm Technologies', 'Inc']  
confidential_required_format = 'Confidential and Proprietary - Qualcomm Technologies, Inc'

def refactoring_confidential(line,index,error_line,empty_line):
    clean_line = re.sub(r'^\W+', '', line.strip()).replace(".","")
    confidential_found_strings = re.findall(r'\b(?:%s)\b' % '|'.join(confidential_required_strings), clean_line)
    confidential_missing_strings = list(set(confidential_required_strings) - set(confidential_found_strings))
    if len(confidential_missing_strings) == 0:
        pass
    else:
        if len(confidential_missing_strings) != 0 and len(clean_line) == 0:
            error_line +=f"line {index+1}: Missing Confidential format. Required format should be : {confidential_required_format}\n"
        elif len(confidential_missing_strings) != len(confidential_required_strings) and len(clean_line) != 0:
            error_line +=f"line {index+1}: Incorrect Confidential format found. Required format should be : {confidential_required_format}\n"
    return error_line
    
def refactoring_copyright(required_strings,line,index,error_line, next_line):
    clean_line = re.sub(r'^\W+', '', line.strip()).replace('All Rights Reserved', 'All rights reserved')
    clean_next_line = re.sub(r'^\W+', '', next_line.strip())
    # print('clean_next_line', clean_next_line)
    # Find all occurrences of the required strings in the clean line
    copyright_found_strings = re.findall(r'\b(?:%s)\b' % '|'.join(required_strings), clean_line)
    copyright_missing_strings = list(set(required_strings) - set(copyright_found_strings))
    confidential_found_strings = re.findall(r'\b(?:%s)\b' % '|'.join(confidential_required_strings), clean_next_line)
    confidential_missing_strings = list(set(confidential_required_strings) - set(confidential_found_strings))
    # print('confidential_found_strings', confidential_found_strings)
    if len(copyright_missing_strings) == 0:
        # print('yes')
        if len(confidential_missing_strings) == 3 and len(clean_next_line) == 0:
            # print('no')
            error_line +=f"line {index+2}: Missing Confidential format. Required format should be : {confidential_required_format}\n"
        elif len(confidential_missing_strings) != 3 and len(confidential_missing_strings) != 0 and len(clean_next_line) != 0:
            # print('yes1')
            error_line +=f"line {index+2}: Incorrect Confidential format found. Required format should be : {confidential_required_format}\n"

    elif len(copyright_missing_strings) !=0:
            error_line +=f"line {index+1}: Incorrect Copyright format found. Required format should be : {copyright_required_format}\n"
            if len(confidential_missing_strings) == 0:
                pass
            elif len(confidential_missing_strings) != 0 and len(clean_next_line)==0:
                error_line +=f"line {index+2}: Missing Confidential format. Required format should be : {confidential_required_format}\n"
            elif len(confidential_missing_strings) != len(confidential_required_strings) and len(confidential_missing_strings) != 0 and len(clean_next_line) != 0:
                error_line +=f"line {index+2}: Incorrect Confidential format found. Required format should be : {confidential_required_format}\n"
    return error_line

def new_function(line, index):
        error_line = ''
        clean_next_line = re.sub(r'^\W+', '', line.strip())
        confidential_found_strings = re.findall(r'\b(?:%s)\b' % '|'.join(confidential_required_strings), clean_next_line)
        confidential_missing_strings = list(set(confidential_required_strings) - set(confidential_found_strings))
        if len(confidential_missing_strings) == 3 and len(clean_next_line) == 0:
            # print('no')
            error_line +=f"line {index+3}: Missing Confidential format. Required format should be : {confidential_required_format}\n"
        elif len(confidential_missing_strings) != len(confidential_required_strings) and len(confidential_missing_strings) != 0 and len(clean_next_line) != 0:
            # print('yes1')
            error_line +=f"line {index+3}: Incorrect Confidential format found. Required format should be : {confidential_required_format}\n"
        return error_line
message = ""
def find_copy_right_error(file):
    global message
    error_line = '' 
    with open(file,'r',encoding="utf-8") as file:
        lines  = file.readlines()
        copyright_check=0
        for index,line in enumerate(lines):
            get_chars_line = re.sub(r'^\W+', '', line.strip()).split()
            empty_line = [i for i in get_chars_line if not i.isspace()]
            
            if copyright_check !=1 and (( "Copyright" in line.strip() and "Technologies" in line.strip() ) and  ( "Qualcomm" in line.strip() or "QUALCOMM" in line.strip() )):
                    copyright_check += 1
                    next_line = lines[index+1]
                    get_chars_line = ''.join(re.sub(r'^\W+', '', next_line.strip()))
                    if 'all rights reserved' in get_chars_line.lower():
                        if "All Rights Reserved" in get_chars_line or "All rights reserved" in get_chars_line:
                            next_line = lines[index+2]
                            error_line += new_function(next_line, index)
                        else:
                            error_line +=f'line {index+2}:Incorrect All rights reserved. Required format should be: All rights reserved\n'
                            next_line = lines[index+2]
                            error_line += new_function(next_line, index)
                    else:
                        error_line += refactoring_copyright(copyright_required_strings,line, index, error_line, next_line)
                    
   
            elif copyright_check !=1 and ('Qualcomm' in line.strip() and ('Confidential' in line.strip() or 'Confidential and Proprietary' in line.strip() )):
                get_chars_line = re.sub(r'^\W+', '', line.strip()).split()
                empty_line = [i for i in get_chars_line if not i.isspace()]
                error_line = refactoring_confidential(line, index, error_line, empty_line)
            elif not( len(empty_line) == 0 and "Copyright" in lines[index-1] )and ( "Qualcomm" in lines[index-1] or "QUALCOMM" in lines[index-1] ): 
               
                previous_line = lines[index-1]
                next_line = lines[index+1]
                if copyright_check !=1 and ( "Copyright" in previous_line.strip() and ( "Qualcomm" in previous_line.strip() or "QUALCOMM" in previous_line.strip())):
                    clean_line = re.sub(r'^\W+', '', next_line.strip())
                    found_strings = re.findall(r'\b(?:%s)\b' % '|'.join(confidential_required_strings), clean_line)
                    missing_strings = list(set(sorted(confidential_required_strings)) - set(sorted(found_strings)))
                    get_chars_line = re.sub(r'^\W+', '', next_line.strip()).replace(".", "")
                    next_line = lines[index+1]
                    clean_next_line = re.sub(r'^\W+', '', next_line.strip())
                    if len(clean_next_line) == 0 :
                        error_line +=f"line {index+2}: Missing Confidential format. Required format should be : {confidential_required_format}\n"
        copyright_check=0
    if error_line:
        file = str(file)
        current_file_name = file.split('/')[::-1][0].split(' ')[0].replace("'","")
        message+="\nFile %s contains invalid copyright format:\n%s"%(current_file_name,error_line)
    return message   
    
# Copyright script check end

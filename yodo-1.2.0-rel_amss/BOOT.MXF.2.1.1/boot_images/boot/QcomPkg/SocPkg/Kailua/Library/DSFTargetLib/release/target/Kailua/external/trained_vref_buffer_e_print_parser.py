#!/afs/localcell/cm/GV2/sysname/pkg.@sys/qct/software/python/3.6.4/bin/python3
"""/*******************************************************************************
  Qualcomm Proprietary Design Data
  Copyright (c) 2019, Qualcomm Technologies Incorporated.
  All rights reserved.
*******************************************************************************/
/*==============================================================================
$Header: //source/qcom/qct/core/boot/ddr/hw_sequence/DDRSS_SNS_V4/target/Kailua/mainline/release/target/Kailua/external/trained_vref_buffer_e_print_parser.py#14 $
$DateTime: 2022/02/18 14:21:17 $
$Author: aastley $
==============================================================================*/
"""
# This script converts TRN_PRINT and TRN_ISSUE console prints to CSV
import re

filter = "*.txt"

pattern = re.compile(r'.*?TRN_.*?,FREQ=(.*?),CHANNEL=(.*?),CHIPSELECT=(.*?),BYTE=(.*?),BIT=(.*?),LIMIT=0x(.*?),VALUE=(.*?)[\s\r\n]')

ps_value_multiplier = 4

trainings_dict = {}
names_dict = {}
names_to_units_dict = {}
names_to_size_dict = {}

trainings_dict[0] = "WRITE"
trainings_dict[1] = "READ"

names_dict[14] = "TRAINED_VREF"
names_to_units_dict[14] = "mV"
names_to_size_dict[14] = 9

def parse_file(input_file_name):
    output_file_name = input_file_name.split(".txt")[0] + ".csv"
    
    with open(output_file_name, "w") as outFile:
        outFile.write("TRAINING,NAME,VALUE,UNITS,FREQ,CHANNEL,RANK,BYTE,BIT\n")
        
        with open(input_file_name, "r") as inFile:
            for inLine in inFile:
                match = pattern.match(inLine)
                if match:
                    limit = int(match.group(6), 16)
                    
                    # TRAINING
                    training_idx = limit >> 8
                    if training_idx not in trainings_dict:
                        continue
                    
                    line = trainings_dict[training_idx]
                    line += ","
                    
                    # NAME
                    name_idx = limit & 0xFF
                    if name_idx not in names_dict:
                        continue
                    
                    line += names_dict[name_idx]
                    line += ","
                    
                    # VALUE & UNITS
                    value = int(match.group(7))
                    units = "na"
                    if name_idx in names_to_units_dict:
                        units = names_to_units_dict[name_idx]
                        if units == "ps" and  names_to_size_dict[name_idx] < 16:
                            value *= ps_value_multiplier
                    line += str(value)
                    line += ","
                    line += units
                    line += ","
                    
                    # FREQ
                    freq = match.group(1)
                    line += freq
                    line += ","
                    
                    # CHANNEL
                    channel = match.group(2)
                    line += channel
                    line += ","
                    
                    # CHIPSELECT
                    chipselect = match.group(3)
                    line += chipselect
                    line += ","
                    
                    # BYTE
                    byte = match.group(4)
                    line += byte
                    line += ","
                    
                    # BIT
                    bit = match.group(5)
                    line += bit
                    
                    line += "\n"
                    
                    outFile.write(line)

if __name__ == "__main__":
    import sys, os, fnmatch
    
    path = sys.argv[1]
    if os.path.isdir(path):
      for root, dirs, files in os.walk(path, topdown=True):
        print("Traversing: " + root)
        parent_root = os.path.dirname(root)
        buffer_e_files = fnmatch.filter(files, filter)
        for file in buffer_e_files:
            file_path = root + "/" + file
            print("   Parsing: " + file_path)
            parse_file(file_path)

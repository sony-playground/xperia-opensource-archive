#!/afs/localcell/cm/GV2/sysname/pkg.@sys/qct/software/python/3.6.4/bin/python3
"""/*******************************************************************************
  Qualcomm Proprietary Design Data
  Copyright (c) 2019, Qualcomm Technologies Incorporated.
  All rights reserved.
*******************************************************************************/
/*==============================================================================
$Header: //source/qcom/qct/core/boot/ddr/hw_sequence/DDRSS_SNS_V4/target/Kailua/mainline/release/target/Kailua/external/trained_vref_buffer_e_binary_parser.py#14 $
$DateTime: 2022/02/18 14:21:17 $
$Author: aastley $
==============================================================================*/
"""
# This script converts buffer_e binary to CSV

filter = "*buffer_e*.bin"

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

def parse_file(input_file_name, output_file, line_prefix):
    prev_byte = ~0
    curr_byte = ~0
    
    if os.stat(input_file_name).st_size == 0:
        return
    
    with open(input_file_name, "rb") as inFile:
        while not (prev_byte == 0 and curr_byte == 0):
            curr_byte = inFile.read(1)[0]
            prev_byte = curr_byte
            
            # Packet with 00b prefix
            if (curr_byte & 0xC0) == 0x00:
                packet = curr_byte << 8
                ch = curr_byte & 0xF
                cs = (curr_byte >> 4) & 0xF
                curr_byte = inFile.read(1)[0]
                packet |= curr_byte
                training = curr_byte & 0xF
                freq = (curr_byte >> 4) & 0xF
                #print("Packet 00b prefix: {:04X}".format(packet))
            # Packet with 01b prefix
            elif (curr_byte & 0xC0) == 0x40:
                byte = curr_byte & 0x3
                bit = (curr_byte >> 2) & 0xF
                #print("Packet 01b prefix: {:02X}".format(curr_byte))
            # Packet with 1Xb prefix
            elif (curr_byte & 0x80) == 0x80:
                name = curr_byte & 0x3F
                sign = (curr_byte >> 6) & 0x1
                #print("Packet 1Xb prefix: {:02X}".format(curr_byte))
                
                # Lower 8 bits of data
                curr_byte = inFile.read(1)[0]
                value = curr_byte
                
                # Upper 8 bits of data
                if name not in names_to_size_dict:
                    continue
                if names_to_size_dict[name] == 16:
                    curr_byte = inFile.read(1)[0]
                    value |= curr_byte << 8
                
                # 9 bit data
                if names_to_size_dict[name] == 9:
                    value |= sign << 8
                # Signed data
                else:
                    if sign == 1:
                        value *= -1
                
                # prefix
                line = line_prefix
                
                # training
                if training not in trainings_dict:
                    continue
                line += "{:s}".format(trainings_dict[training])
                
                # name
                line += ",{:s}".format(names_dict[name])
                
                # value
                if names_to_size_dict[name] < 16 and names_to_units_dict[name] == "ps":
                    value *= ps_value_multiplier
                line += ",{:d}".format(value)
                
                # units
                line += ",{:s}".format(names_to_units_dict[name])
                
                # freq
                if freq == 0xF:
                    line += ",DC"
                else:
                    line += ",{:d}".format(freq)
                
                # ch
                if ch == 0xF:
                    line += ",DC"
                else:
                    line += ",{:d}".format(ch)
                
                # cs
                if cs == 0x3:
                    line += ",DC"
                else:
                    line += ",{:d}".format(cs)
                
                # byte
                if byte == 0x3:
                    line += ",DC"
                else:
                    line += ",{:d}".format(byte)
                
                # bit
                if bit == 0xF:
                    line += ",DC"
                else:
                    line += ",{:d}".format(bit)
                
                line += "\n"
                
                output_file.write(line)
            # Error
            else:
                break

if __name__ == "__main__":
    import sys, os, fnmatch
    
    if (len(sys.argv) > 1 ):
        path = sys.argv[1]
    else:
        path = "."
        
    if os.path.isdir(path):
      for root, dirs, files in os.walk(path, topdown=True):
        print("Traversing: " + root)
        parent_root = os.path.dirname(root)
        buffer_e_files = fnmatch.filter(files, filter)
        for file in buffer_e_files:
            file_path = root + "/" + file
            print("   Parsing: " + file_path)
            output_file_name = file_path.split(".bin")[0] + ".csv"
            with open(output_file_name, "w") as output_file:
                output_file.write("TRAINING,NAME,VALUE,UNITS,FREQ,CHANNEL,RANK,BYTE,BIT\n")
                parse_file(file_path, output_file, "")

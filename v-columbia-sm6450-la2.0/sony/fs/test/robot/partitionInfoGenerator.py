import argparse
import os
import shutil
from xml.etree import ElementTree
from pprint import pformat
from PartitionTable import *

ap = argparse.ArgumentParser()
ap.add_argument("-p", "--path", required=True, help="provide the path for the test data directory")
ap.add_argument("-z", "--partitions", required=False, default=None, help="provide a zip file with partitions")
ap.add_argument("-b", "--block_size", required=False, default=4096, help="provide block size")
args = vars(ap.parse_args())

# parse fsconfig.xml
xml_file = 'fsconfig.xml'
file_path = os.path.join(args['path'], xml_file)
dom = ElementTree.parse(file_path)
partitions_from_xml = dom.findall('partitions/partition')

# make a dictionary of partition info from the xml
partition_info = {}

if args['block_size'] != '':
    block_size = int(args['block_size'])
else:
    block_size = 4096

for partition in partitions_from_xml:
    ptn_name = str(partition.attrib['name'])

    partition_size = int(partition.attrib['number_of_blocks'],16) * block_size
    size_str = "0x" + '{0:0x}'.format(partition_size)

    partition_info[ptn_name] = {'fs_type': partition.attrib['fs_type'],
                                'gpt_attributes': partition.attrib['gpt_attributes'],
                                'gpt_id': (partition.attrib['gpt_id']).lower(),
                                'gpt_type': (partition.attrib['gpt_type']).lower(),
                                'start_block': (partition.attrib['start_block']).lower(),
                                'number_of_blocks': (partition.attrib['number_of_blocks']).lower(),
                                'size': size_str}

# If provided, extract partition.zip fetched from debian pkg and generate ptn info
if args['partitions'] != None:
    zip_file = args['partitions']
    #ptn_zip_path = os.path.join(args['path'], zip_file)
    unpack_path = os.path.join(args['path'], 'temp')
    table = PartitionTableGenerator.create_from_zip(zip_file, unpack_path)

    # cleanup temp
    try:
        shutil.rmtree(unpack_path)
    except OSError as e:
        print("Error: %s - %s." % (e.filename, e.strerror))

    # check for inconsistancy against gpt from partition.zip
    # if there is one, update partition_info before saving to file
    for ptn in partition_info:
        partition_size = int(table.partition_table[ptn]['size'],16) * block_size
        size_str = "{0:#x}".format(partition_size)
        if partition_info[ptn]['size'] != size_str:
            partition_info[ptn]['size'] = size_str
        if partition_info[ptn]['gpt_type'] != table.partition_table[ptn]['type']:
            partition_info[ptn]['gpt_type'] = table.partition_table[ptn]['type']
        if partition_info[ptn]['gpt_id'] != table.partition_table[ptn]['unique']:
            partition_info[ptn]['gpt_id'] = table.partition_table[ptn]['unique']
        if partition_info[ptn]['start_block'] != '0x' + str(table.partition_table[ptn]['start_sector']):
            partition_info[ptn]['start_block'] = '0x' + str(table.partition_table[ptn]['start_sector'])

# save to file
with open('test_data/PartitionInfo.py', 'w') as file:
    file.write('# This file is generated from fsconfig.xml using partitionInfoGenerator.\n\n')
    file.write('class PartitionInfo:\n\t')
    file.write('partitions = ' + str(partition_info))
    file.close()

print('partition_info.py has been generated in test_data!!')

import xml.etree.ElementTree as ET
import struct
from cStringIO import StringIO
import sys

filepath=sys.argv[1]
ipcatpath=sys.argv[2]

try:
    ipcattree = ET.parse(ipcatpath)
    ipcatroot = ipcattree.getroot()
except:
    sys.exit(0)

dic = {}

for chip in ipcatroot.findall('chip'):
    for register in chip.findall('register'):
        value = int(register.get('value'),16)
        address = int(register.get('address'),16)
        dic[address] = value

f = open(filepath,"wb")

rpmh_start_addr = int("0xB200000",16)
rpmh_end_addr = int("0xBE00004",16)

string = ""

for i in range(rpmh_start_addr, rpmh_end_addr, 4):

    toWrite = 0

    if i in dic:
        toWrite = dic[i]

    toWrite = bin(toWrite)[2:].zfill(32)
    
    sio = StringIO(toWrite)

    # Grab the next 8 bits
    b1 = sio.read(8)
    b2 = sio.read(8)
    b3 = sio.read(8)
    b4 = sio.read(8)

    # Convert to int
    i1 = int(b1, 2)
    i2 = int(b2, 2)
    i3 = int(b3, 2)
    i4 = int(b4, 2)
    

    # Convert to char
    c1 = chr(i1)
    c2 = chr(i2)
    c3 = chr(i3)
    c4 = chr(i4)
    

    # Write
    f.write(c4)
    f.write(c3)
    f.write(c2)
    f.write(c1)
        
		
f.close()

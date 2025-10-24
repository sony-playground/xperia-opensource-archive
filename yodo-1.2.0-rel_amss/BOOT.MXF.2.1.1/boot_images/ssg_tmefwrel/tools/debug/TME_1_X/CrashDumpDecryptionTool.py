#=============================================================================
#* Copyright (c) 2021-2022 Qualcomm Technologies Incorporated.
#* All Rights Reserved.
#* Qualcomm Confidential and Proprietary
#=============================================================================

import binascii
import io
import struct
import os.path
import sys
import json
import argparse
from collections import OrderedDict
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Cipher import AES
from Crypto.PublicKey import ECC
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives import hashes

decodeHeaderDictionary = OrderedDict()
dumpInfoDictionary = OrderedDict()

magicNumber = "0x544d4521"
dumpTableAddres = 0x146AAC68
fourBytes = 0x4 # 4 bytes
aesTagLength = 0x10 #16 bytes
aesNonceLength = 0xC #12 bytes
aesKeySize = 0x100 #256 bytes

def fromHexToAscii(data):
    var = bytes.fromhex(data[2:]).decode('ASCII')
    return var

def padHex(string,fill):
    return "0x" + string[2:].zfill(fill)

def swap32(i):
    return struct.unpack("<L", struct.pack(">L", i))[0]

def unHexlify(data):
    var = binascii.unhexlify(data[2:])
    return var

def convertToHex(inputData):
    var = int(binascii.hexlify(inputData),16)
    return var

def convertHexToDec(inputData):
    var = int(inputData,16)
    return var

def convertStringToDec(inputData):
    var = int(inputData,10)
    return var

def cleanHex(inputVal):
    return hex(inputVal).rstrip('L')

def decode32BitData(inputData):
    var = swap32(convertToHex(inputData))
    return var

def updateTableHeaderDictionary(key, value):
    decodeHeaderDictionary[key] = value

def updateDumpInfoDictionary(fileName, offSet, fileSize):
    dumpInfoDictionary[fileName] = [fileSize, offSet]

def parseDumpInfoFile(dumpFolderLocation):
    with open(os.path.join(dumpFolderLocation,'dump_info.txt'),'rb') as dumpInfoFile:
        for line in dumpInfoFile:
            splitList = line.split()
            if '1' == splitList[0].decode('utf-8'): #Valid Line
                updateDumpInfoDictionary(splitList[-1].decode('utf-8'),splitList[1].decode('utf-8'),splitList[2].decode('utf-8'))
    dumpInfoFile.close()

def getFilenameAndOffset(inputAddress):
    fileName = None
    offSet = None
    for key,value in dumpInfoDictionary.items():
        fileStartAddress = convertHexToDec(value[1])
        fileSize = convertStringToDec(value[0])
        if  fileStartAddress <= inputAddress and inputAddress < (fileStartAddress + fileSize):
            fileName = key
            offSet = inputAddress - fileStartAddress
    if None == fileName or None == offSet:
        raise Exception("Error: Can not find the input address %s in dump_info.txt" % hex(inputAddress))
    return fileName, offSet

def returnDumpTableOffset(dumpFolderLocation):
    fileName, Offset = getFilenameAndOffset(dumpTableAddres)
    encDumpFile = open(os.path.join(dumpFolderLocation,fileName),'rb')
    encDumpFile.seek(Offset)
    dumpTableLocation = decode32BitData(encDumpFile.read(fourBytes))
    encDumpFile.close()
    return dumpTableLocation;

def decodeDumpHeader(dumpFolderLocation, offsetAddress):
    fileName, Offset = getFilenameAndOffset(offsetAddress)
    encDumpFile = open(os.path.join(dumpFolderLocation,fileName),'rb')
    encDumpFile.seek(Offset,1);
    updateTableHeaderDictionary("dumpTableVersion", decode32BitData(encDumpFile.read(fourBytes)))
    updateTableHeaderDictionary("dumpTableMagic", cleanHex(decode32BitData(encDumpFile.read(fourBytes))))
    updateTableHeaderDictionary("dumpTableNumberOfRecords", decode32BitData(encDumpFile.read(fourBytes)))

    dumpRecords = OrderedDict()
    for numRecord in range(decodeHeaderDictionary["dumpTableNumberOfRecords"]):
        tempDict = OrderedDict()
        tempDict["type"] =  decode32BitData(encDumpFile.read(fourBytes))
        tempDict["encrypted"] =  decode32BitData(encDumpFile.read(fourBytes))
        tempDict["imemAddr"] =  cleanHex(decode32BitData(encDumpFile.read(fourBytes)))
        tempDict["imemSize"] =  decode32BitData(encDumpFile.read(fourBytes))
        tempDict["ddrAddr"] =  cleanHex(decode32BitData(encDumpFile.read(fourBytes)))
        tempDict["ddrSize"] =  decode32BitData(encDumpFile.read(fourBytes))
        tempDict["tag"] = padHex(cleanHex(convertToHex(encDumpFile.read(aesTagLength))),aesTagLength*2)
        tempDict["nonce"] =  padHex(cleanHex(convertToHex(encDumpFile.read(aesNonceLength))),aesNonceLength*2)
        dumpRecords["RecordNumber_" + str(numRecord+1)] = tempDict

    updateTableHeaderDictionary("dumpRecords",dumpRecords)
    updateTableHeaderDictionary("wrappedKey",padHex(cleanHex(convertToHex(encDumpFile.read(aesKeySize))),aesKeySize*2))

    encDumpFile.close()

def ECDH_Key_exchange(my_priv_key_seed, wrapped_key_blob):
    if len(my_priv_key_seed) != 96:
        print("Key size Error !!! ECC Private key size must be 48 byte i.e 96 Nibbles")
        return False
    QBEC_magic = wrapped_key_blob.read(4)
    if QBEC_magic != b"QBEC":
        print("QBEC Magic Number in the wrapped AES key")
        return False
    wrapped_key_blob.seek(32)
    HKDF_context = wrapped_key_blob.read(64)
    TME_FW_pubkey = wrapped_key_blob.read(48)
    Number_of_wrapped_keys = wrapped_key_blob.read(4)
    Nonce = wrapped_key_blob.read(12)
    Tag = wrapped_key_blob.read(16)
    wrapped_key_size = swap32(int(binascii.hexlify(wrapped_key_blob.read(4)), 16))
    wrapped_key = wrapped_key_blob.read(wrapped_key_size)

    # Generate my private/public key-pair - should be randomly generated but for testing purpose using a seed to generate same key
    curve = ec.SECP384R1()
    print("oem private key :: " + str(my_priv_key_seed))
    my_priv_key = ec.derive_private_key(int(my_priv_key_seed, 16), curve)

    # ECDH(tool's private key + device's public key)
    shared_key = my_priv_key.exchange(ec.ECDH(), ec.EllipticCurvePublicKey.from_encoded_point(curve, binascii.unhexlify("02") + TME_FW_pubkey))
    # Note: SEC defines three types of public key format: 0x00 = point at infinity, 0x02 and 0x03 = compressed, 0x04 = uncompressed
    # 02 means even y-point, 03 means odd y-point

    # Reverse the key to follow what the Sequencer HW
    shared_key = shared_key[::-1]

    # HKDF
    # value that will be populated by hw on device
    bsve = binascii.unhexlify("20000000")

    # length of derived key is 256 bits (32 bytes)
    key_length = binascii.unhexlify("00010000")

    # sw_context
    context = HKDF_context + binascii.unhexlify(64 * "00")  # 128 bytes total i.e 64 byte from dump and next 64 byte pad with 0
    # salt
    salt = binascii.unhexlify(64 * "00")   # 64 bytes

    # HKDF output
    info=context+bsve+key_length

    hkdf = HKDF(algorithm=hashes.SHA512(), length=32, salt=salt, info=info, backend=default_backend())

    gcm_key = hkdf.derive(shared_key)

    aesgcm = AES.new(gcm_key, AES.MODE_GCM, Nonce)

    try:
        aesKey = aesgcm.decrypt(wrapped_key)
        aesgcm.verify(Tag)
        return aesKey
    except Exception as e:
        print("AES GCM Decryption fails for wrapped key with error: {}".format(e))
        return None

def decryptTheEcdhAesKey(priv_key_file, encryptedKey):
    priv_key = ECC.import_key(priv_key_file.read())

    # Private key is the D component of the ECC key. Get it in byte format
    priv_key_seed = binascii.hexlify(priv_key.d.to_bytes())

    # Use a virtual file
    wrapped_key = io.BytesIO(encryptedKey)

    return ECDH_Key_exchange(priv_key_seed, wrapped_key)

def decryptTheRsaAesKey(priv_key_file, encryptedKey):
    #Get the private key
    rsa_key = RSA.importKey(priv_key_file.read())
    #Generate cipher
    cipher = PKCS1_OAEP.new(rsa_key, hashAlgo=SHA256)
    decrypted = cipher.decrypt(encryptedKey)
    return decrypted

def decryptTheDDRBlock(inputStream, privateKey, nonce, tag, outFile):
    #Get the key
    cipher = AES.new(privateKey, AES.MODE_GCM, nonce)
    #Decrypt the block
    data = cipher.decrypt_and_verify(inputStream, tag)
    outFile.write(data)

def doDecode():
    privateAESKey = None
    if 0 != len(decodeHeaderDictionary):
        if fromHexToAscii(magicNumber) == fromHexToAscii(decodeHeaderDictionary["dumpTableMagic"]):
            for numRecord,value in decodeHeaderDictionary["dumpRecords"].items():
                print ("Processing : %s" % numRecord)

                if 0 == value["type"]:
                    print ("%s is invalidated!!" % numRecord)

                fileName, Offset = getFilenameAndOffset(convertHexToDec(value["ddrAddr"]))
                encDumpFile = open(os.path.join(args.dumpFolderLocation,fileName),'rb')
                encDumpFile.seek(Offset)
                dataToDecode = encDumpFile.read(value["ddrSize"])
                encDumpFile.close()

                outFile = open(os.path.join(args.dumpFolderLocation,'DDR_Record_Type_'+str(value["type"])+'.bin'),'wb')

                if 0 == value["encrypted"]: #The dump is not encrypted write to output directly
                    outFile.write(dataToDecode)
                    print ("################################ SUCCESS: data is not encrypted, output file name: %s ##################################" % outFile.name)
                else: #The dump is encrypted so decrypt it and write to output
                    #for first time, check if segment is encoded. If yes then decrypt the original key and store it globally
                    if None == privateAESKey:
                        priKeyFile = open(args.privateKeyFile,'rb')
                        wrappedKey = unHexlify(decodeHeaderDictionary["wrappedKey"])
                        if args.crypto == 'rsa':
                            privateAESKey = decryptTheRsaAesKey(priKeyFile, wrappedKey)
                        else:
                            privateAESKey = decryptTheEcdhAesKey(priKeyFile, wrappedKey)

                        priKeyFile.close()

                    nonce = unHexlify(value["nonce"])
                    tag = unHexlify(value["tag"])
                    decryptTheDDRBlock(dataToDecode, privateAESKey, nonce, tag, outFile)

                    print ("################################ SUCCESS: data decryption complete, output file name: %s ##################################" % outFile.name)
                outFile.close()
        else:
            raise Exception ("ERROR: DumpTable is corrupted!!")
    else:
        raise Exception ("ERROR: Decode the dump table first!!")

def decryptMiniDump(privateKeyFile, dumpFolderLocation):
    with open(privateKeyFile,'rb') as key, open(os.path.join(dumpFolderLocation,'md_TME_KEYS.BIN'),'rb') as keys:
        # Obtain the CEK from the QBEC blob
        privateAESKey = decryptTheEcdhAesKey(key, keys.read())

    # AES GCM nonce
    with open(os.path.join(dumpFolderLocation,'md_TME_AES_IV.BIN'),'rb') as f:
        md_TME_AES_IV = f.read()

    # AES GCM authentication tag
    with open(os.path.join(dumpFolderLocation,'md_TME_AES_TAG.BIN'),'rb') as f:
        md_TME_AES_TAG = f.read()

    # Encrypted minidump contents
    with open(os.path.join(dumpFolderLocation,'md_TME_DUMP.BIN'),'rb') as f:
        md_TME = f.read()

    # Decrypted minidump contents are sent to md_TME_RAW.BIN file
    with open(os.path.join(dumpFolderLocation,'md_TME_RAW.BIN'),'wb') as f:
        decryptTheDDRBlock(md_TME, privateAESKey, md_TME_AES_IV, md_TME_AES_TAG, f)

if __name__=='__main__':

    parser = argparse.ArgumentParser(
        description='Crash dump decryption tool.',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    parser.add_argument('-d',
                        '--dumpFolderLocation',
                        help='Path of the dump folder.',
                        type=str,
                        required=True)

    parser.add_argument('-p',
                        '--privateKeyFile',
                        help='Path to the private key file.',
                        type=str,
                        required=True)

    parser.add_argument('-c',
                        '--crypto',
                        choices=['rsa', 'ecc' ],
                        default='ecc',
                        help='Choice of asymmetric crypto.')

    parser.add_argument('-m',
                        '--minidump',
                        default=False,
                        action='store_true',
                        help='Decrypt minidump')

    args = parser.parse_args()

    if not os.path.isdir(args.dumpFolderLocation) :
        args.dumpFolderLocation = "."

    if args.minidump:
        if args.crypto == 'ecc': # Caller needs to decrypt the minidump
            decryptMiniDump(args.privateKeyFile, args.dumpFolderLocation)
    else:
        parseDumpInfoFile(args.dumpFolderLocation)

        outVal = returnDumpTableOffset(args.dumpFolderLocation)

        decodeDumpHeader(args.dumpFolderLocation, outVal)

        with open(os.path.join(args.dumpFolderLocation,'dumpTable.json'),'w') as outfile:
            json.dump(decodeHeaderDictionary, outfile, indent=4)

        outfile.close()

        doDecode()

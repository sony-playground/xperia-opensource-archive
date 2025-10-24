from __future__ import print_function
# ----------------------------------------------------------------------------
#  Copyright (c) 2021 - 2022 Qualcomm Technologies, Inc.
#  All rights reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
# ----------------------------------------------------------------------------
import os
import sys
import argparse
import binascii
import re
import logging
import struct
import subprocess

def install(name):
    subprocess.call(['pip', 'install', name])

try:
    import cbor2
except ImportError:
    
    install('cbor2')
    install('pycryptodome')
    print("Required Libraries are installed")
finally:
    import cbor2


progress_indicator_index = 0


def progress_indicate():
    global progress_indicator_index
    progress_indicator = ['-', '/', '|', '\\']
    sys.stdout.write(" %s   \r" % (progress_indicator[progress_indicator_index]))
    sys.stdout.flush()

    progress_indicator_index += 1
    if (progress_indicator_index % len(progress_indicator)) == 0:
        progress_indicator_index = 0


def setupAndGetLogger(output):
    # set up logging to file
    logger = logging.getLogger('logParser')

    if not len(logger.handlers):
        logHandler = logging.StreamHandler()
        logFormatter = logging.Formatter('%(message)s')
        logHandler.setFormatter(logFormatter)
        logger.addHandler(logHandler)
        logger.setLevel(logging.DEBUG)

    if not output is None:
        fileLogHandler = logging.FileHandler(output, mode='w')
        fileLogFormatter = logging.Formatter('%(message)s')
        fileLogHandler.setFormatter(fileLogFormatter)
        fileLogHandler.setLevel(logging.INFO)
        logger.addHandler(fileLogHandler)

    return logger


class DictItem(object):
    def __init__(self, raw):
        self.readyBody = None

        # Divide into id, component and body
        logItem = raw.split(':')
        # logItem[0]  = ID
        # logItem[1]  = Component Name
        # logItem[2:] = Raw body
        self.id = logItem[0]
        self.component = logItem[1]
        self.rawBody = ' '.join(logItem[2:])
        self.id = (hex(int(self.id, 16)).upper())

        DictItem.prepareLogBody(self, self.rawBody)

    def __str__(self):
        items = {
            "id": self.id,
            "component": self.component,
            "rawBody": self.rawBody,
            "readyBody": self.readyBody
        }
        return str(items)

    def getReadableLog(self, parameters, priority):
        result = None
        if parameters:
            if self.readyBody is not None:
                try:
                    result = self.readyBody.format(*parameters)
                except:
                    result = None

            # When formatting line is missing just show parameters in hex
            if result is None:
                paramsStr = [hex(x) for x in parameters]
                result = "{0} {1}".format(self.rawBody, paramsStr)
        else:
            result = self.rawBody

        return "{0}({1}) {2}".format(self.component, priority, result)

    @staticmethod
    def prepareLogBody(obj, rawBody):
        # find pattern of from % to x, d or u like C printf() formatters
        foundPatterns = re.findall(r'%[a-zA-Z0-9]+', rawBody)

        if foundPatterns:
             obj.readyBody = rawBody
             for index, pattern in enumerate(foundPatterns):
                 typePattern = ':X'
                 if pattern in [r'%d', r'%u']:
                     typePattern = ''
 
                 obj.readyBody = obj.readyBody.replace(pattern, '{' + str(index) + typePattern + '}', 1)

def prepare_dictionary(dict):
    
    dicts = {}
   
    with open(dict, "r") as dictFile:
        componentIDs = {}
        for line in dictFile:
            line = line.strip()
            if line.startswith("="):
                continue
            # 1. Check component IDs
            if line.startswith("COMPONENT"):
                tag, componentName, componentID = line.split(":")
                componentIDs[componentName] = hex(int(componentID, 16)).upper()
            # 2. Check Log Items
            else:
                dictItem = DictItem(line)
                logID = dictItem.id
                logComponent = dictItem.component
                dicts[(componentIDs[logComponent], logID)] = dictItem


    return dicts


class DecodedLogItems(object):
    def __init__(self):
        self.decodedLogItems = {}

    def add_load_item(self, decoded_log):
        # Preparing a map of log items, timestamp as key, log data as value
        self.decodedLogItems[decoded_log[2]] = decoded_log  # index 2 is timestamp

    def __len__(self):
        return len(self.decodedLogItems)

    def get_decoded_log_items(self):
        return self.decodedLogItems

if __name__ == '__main__':
    try:
        directory_path = os.getcwd()
        Errorfile = os.path.join(directory_path,'Error.txt')
        f = open(Errorfile,'w+')
        print("Error File Created")
       
        logger = setupAndGetLogger(None)
        logger.debug("><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><")
        global mapToDict
        mapToDict = False
        parser = argparse.ArgumentParser(
            description='TME LOG parser to logger.debug out as readable format.',
            formatter_class=argparse.ArgumentDefaultsHelpFormatter)
        parser.add_argument('--input',
                            help='Input RAW TME Log file.',
                            required=True)
        parser.add_argument('--output',
                            help='Output TXT file.  default is <input>.txt.')
        parser.add_argument('--dict',
                            help='Abs path of Log Dictionary TXT file.',
                            default="TMELogDictionary.txt")

        parser.add_argument('-e', '--elapsed_timestamp',
                            help='Print relative elapsed timestamps',
                            action='store_true')

        parser.add_argument('-r', '--real_timestamp',
                            help='Print real timestamps, instead of raw ticks',
                            action='store_true',
                            default=True)

        parser.add_argument('-t', '--raw_ticks',
                            dest='real_timestamp',
                            help='Print raw ticks, instead of real timestamps',
                            action='store_false')

        parser.add_argument('-c', '--timestamp_clockrate',
                            help='Timestamp clock rate in Hz',
                            default=19200000)

        args = parser.parse_args()

        inputFile = args.input
        outputFile = vars(args).get('output')
        dictFile = vars(args).get('dict')

        if outputFile is None:
            outputFile = inputFile + ".txt"
        

        current_dir = os.getcwd()
        inputFileAbsPath = os.path.join(current_dir, inputFile) 

        inputFileSize = os.path.getsize(inputFileAbsPath)

        outputFileAbsPath = os.path.join(current_dir, outputFile)
        dictFileAbsPath = os.path.join(current_dir, dictFile)

        if not os.path.isfile(dictFileAbsPath):
            logger.error("Log Dictionary file Abs path is not valid")
        else:
            mapToDict = True

        logger.debug("> Given Parameters")
        logger.debug(": Input, {0} {1} bytes \t Output, {2}".format(inputFile, inputFileSize, outputFile))
        logger.debug(": Working Dir {0}".format(current_dir))

        logger.debug("--------------------------------------------------------------------------------")
        if mapToDict:
            logger.debug("> Prepare Dictionary from {0}".format(dictFile))
            TMELogDict = prepare_dictionary(dictFileAbsPath)

        logger.debug("> Reading {0}".format(inputFile))
        tags = []
        LOG_OPEN_TAG = b'['
        LOG_CLOSE_TAG = b']'
        LOG_TAG_REGION_SIZE = 3

        with open(inputFileAbsPath, "rb") as rawLogFile:
            # Process byte by byte the given raw log file to locate log tags and log size
            for offset in range(0, inputFileSize):
                tag = []
                logData = None

                # If there is log size and close log tag can be read from the file
                if offset + (LOG_TAG_REGION_SIZE - 1) < inputFileSize:
                    rawLogFile.seek(offset)
                    logData = struct.unpack('ccc', rawLogFile.read(LOG_TAG_REGION_SIZE))
                # We can break out as there are no more bytes can be a log item
                else:
                    break

                # Prepare to check if there are log item
                openTag = logData[0]
                logSize = logData[1]
                closeTag = logData[2]

                # Check '[' as open tag and ']' as close tag, and store into tags
                if openTag is LOG_OPEN_TAG:
                    if closeTag is LOG_CLOSE_TAG:
                        tag.append(int(offset))
                        tag.append(ord(logSize))
                        tags.append(tag)

                progress_indicate()

        logger.debug(": {0} tags found.".format(len(tags)))
        f.write(": {0} tags found.".format(len(tags)))
        assert tags, "!No log tag found!"

        offset = 0
        decodedLogItems = DecodedLogItems()

        with open(inputFileAbsPath, "rb") as rawLogFile:
            for tag in tags:
                logItemOffset, logItemSize = tag
                rawLogFile.seek(logItemOffset + LOG_TAG_REGION_SIZE)
                cborData = rawLogFile.read(logItemSize)
                if cborData is None:
                    break
                try:
                    decoded = cbor2.decoder.loads(cborData)
                    isAddable = True
                    for item in decoded:
                        # If an item is CBOR break marker it is not valid log data
                        if isinstance(item, cbor2.types.BreakMarkerType):
                            isAddable = False
                            break;
                            
                        # If a sub-item is CBOR break marker it is not valid log data
                        # In this case put 0xDEADDEAD to try to save the other data.
                        if isinstance(item, list):
                            for index, subitem in enumerate(item):
                                if not isinstance(subitem, int):
                                    item[index] = 0xDEADDEAD

                    if isAddable:
                        decodedLogItems.add_load_item(decoded)
                except:
                # To catch CBOR2 decording exception, they are skipped
                    continue
                progress_indicate()

        logger.debug(": {0} log items found.".format(len(decodedLogItems)))

        assert decodedLogItems, "!Not able to decode any log items!"

        logger.debug("--------------------------------------------------------------------------------")
        logger.debug(" > Writing into {}".format(outputFile))
        
        logger = setupAndGetLogger(outputFile)
        lastTimestamp = 0

        #Choose the timestamp formatter
        timestampFormat = "{0:16} ticks"
        if args.real_timestamp:
            timestampFormat = "{0:16.6f} s"

        if args.elapsed_timestamp:
            timestampFormat = '+' + timestampFormat

        # Add the surrounding brackets
        timestampFormat = '[{}] '.format(timestampFormat)

        for timestamp, data in sorted(decodedLogItems.get_decoded_log_items().items()):
            try:
                parameters = []
                # Component ID at 0 index
                componentID = hex(data[0]).upper()
                # Priority at 1 index
                priority = hex(data[1]).upper()
                if isinstance(data[3], list):
                    eventID = hex(data[3][0]).upper()
                    parameters.extend(data[3][1:])
                else : 
                    eventID = 0
                    
                itemToWrite = "{0} {1} {2} {3}".format(componentID, priority, eventID, [hex(x) for x in parameters])

                # Try to map to dictionary
                if mapToDict is True:
                    dictItem = TMELogDict.get((componentID, eventID))
                    # A match found
                    if dictItem is not None:
                        itemToWrite = dictItem.getReadableLog(parameters, priority)

                if args.real_timestamp:
                    # Calculate the timestamp using the clock rate
                    try : 
                        timestamp = timestamp / float(args.timestamp_clockrate)
                    except ZeroDivisionError:
                        logger.debug("ZeroDivisionError Occurred and Handled")
                        
                if args.elapsed_timestamp:
                    tmpTimestamp = timestamp
                    timestamp = timestamp - lastTimestamp
                    lastTimestamp = tmpTimestamp
                # Timestamp , component,parameters, priority, result     
                itemToWrite = timestampFormat.format(timestamp) + itemToWrite

                logger.info(itemToWrite)
                progress_indicate()
            except:
                logger.exception(" > !Exception happend on timestamp:{}, data:{}".format(timestamp, data))
        logger.debug(" > Writing into {} Done.".format(outputFile))
        logger.debug("--------------------------------------------------------------------------------")
    except ImportError:
        logger.error("All the dependencies aren't installed") 
        f.write("All the dependencies aren't installed \n")
    except IOError: 
        logger.error("Input file is not given")
        f.write("Input file is not given \n")
    except :
        logger.error("Unexpected Error!!")
        f.write("Unexpected Error")
    finally:
        f.close()


if os.stat('Error.txt').st_size==0 :
    os.remove("Error.txt")
    print("Error File deleted as program ran successfully")
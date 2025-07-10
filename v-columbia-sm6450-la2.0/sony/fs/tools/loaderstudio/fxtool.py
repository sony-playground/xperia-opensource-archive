#!/bin/python
from ctypes import *
import struct
import os
import time
import sys


# typedef struct
# {
#   unsigned int TAUnitNumber;
#   unsigned int TAUnitSize;
#   char* TAUnitData;
# } T_TAUnit;

class TaUnit(Structure):
  _fields_ = [("unit", c_uint),
              ("size", c_uint),
              ("data", POINTER(c_ubyte))]

  def __init__(self, unit, mastersize=64000):
    self.mastersize = mastersize
    self.unit = unit
    self.size = self.mastersize
    self.data = (c_ubyte * self.mastersize)()

  def __str__(self):
    l = []
    l.append('unit: ' + hex(self.unit) + '\n')
    l.append('size: ' + str(self.size) + '\n')
    l.append('data: ')
    if (self.size):
      for n in range(0, self.size):
        l.append(' ' + hex(self.data[n]))
    else:
      l.append('None')
    l.append('\n')
    return ''.join(l)

  def list(self):
    l = []
    if (self.size):
      for n in range(0, self.size):
        l.append(self.data[n])
    return l

  def clear(self):
    if (self.size):
      for n in range(0, self.size):
        self.data[n] = 0
    self.size = self.mastersize

  def reset(self, unit):
    self.clear()
    self.unit = unit


# typedef struct
# {
#   unsigned int TAStartAddress;
#   unsigned int TABlockSize; //Erase block size
#   unsigned int TANumberOfBlocks; //Nbr of erase blocks allocated
# } T_TASetting;

class TaSetting(Structure):
  _fields_ = [("address", c_uint),
              ("blkSize", c_uint),
              ("blkNbr", c_uint)]

  def __str__(self):
    l = []
    l.append('address: ' + hex(self.address) + '\n')
    l.append('blkSize: ' + hex(self.blkSize) + '\n')
    l.append('blkNbr: ' + str(self.blkNbr) + '\n')
    return ''.join(l)


# typedef struct GDFSUnitData
# {
#   unsigned char GDFSBlockNumber; // Max 256
#   unsigned short GDFSUnitNumber; // Max 65 k unit numbers
#   unsigned int GDFSDataSize; // Max, yeah whatever...
#   char *GDFSData; // Pointer to the GDFS data that shall be written to id
# } T_GDFSUnitData;

class GdfsUnit(Structure):
  _fields_ = [("block", c_ubyte),
              ("unit", c_ushort),
              ("size", c_uint),
              ("data", POINTER(c_ubyte))]

  def __init__(self, unit, block, mastersize=64000):
    self.mastersize = mastersize
    self.unit = unit
    self.block = block
    self.size = self.mastersize
    self.data = (c_ubyte * self.mastersize)()


  def __str__(self):
    l = []
    l.append('unit: ' + hex(self.unit) + '\n')
    l.append('block: ' + hex(self.block) + '\n')
    l.append('size: ' + str(self.size) + '\n')
    l.append('data: ')
    if (self.size):
      for n in range(self.size):
        l.append(' ' + hex(self.data[n]))
    else:
      l.append('None')
    l.append('\n')
    return ''.join(l)

  def list(self):
    l = []
    if (self.size):
      for n in range(0, self.size):
        l.append(self.data[n])
    return l

  def clear(self):
    if (self.size):
      for n in range(0, self.size):
        self.data[n] = 0
    self.size = self.mastersize

  def reset(self, unit):
    self.clear()
    self.unit = unit



# typedef struct GDFSSetting
# {
#   unsigned int GDFSStartAddress;
#   unsigned int BlockSize;
#   unsigned char NumberOfBlocksUsed;
#   unsigned char NumberOfLogicalBlocks;
#   unsigned int NumberOfUnits;
#   unsigned char ApplicationCPU;
# } T_GDFSSetting;

class GdfsSetting(Structure):
  _fields_ = [("address", c_uint),
              ("blkSize", c_uint),
              ("blkUsed", c_ubyte),
              ("blkLogl", c_ubyte),
              ("blkNbr", c_uint)]

  def __str__(self):
    l = []
    l.append('address: ' + str(self.address) + '\n')
    l.append('blkSize: ' + str(self.blkSize) + '\n')
    l.append('blkUsed: ' + str(self.blkUsed) + '\n')
    l.append('blkLogical: ' + str(self.blkLogl) + '\n')
    l.append('blkNbr: ' + str(self.blkNbr) + '\n')
    return ''.join(l)

# typedef struct OTPData
# {
#   unsigned char Status;
#   unsigned char Locked;
#   unsigned short CID; // Max 65 k
#   unsigned char PAF;
#   unsigned char IMEI[14]; // IMEI 14 bytes ASCII string
#   unsigned char IMEIChangeable;
# } T_OTPData;

class OtpData(Structure):
  _fields_ = [("status", c_ubyte),
              ("locked", c_ubyte),
              ("cid", c_ushort),
              ("paf", c_ubyte),
              ("imei", c_char * 14),
              ("changeable", c_ubyte)]

  def __str__(self):
    l = []
    l.append('status: ' + str(self.status) + '\n')
    l.append('locked: ' + str(self.locked) + '\n')
    l.append('cid: ' + str(self.cid) + '\n')
    l.append('paf: ' + str(self.paf) + '\n')
    l.append('imei: ' + self.imei + '\n')
    l.append('chnble: ' + str(self.changeable) + '\n')
    return ''.join(l)

#typedef struct FXT_Sign_OTPData_DB3350_t
#{
#  unsigned char Status; // OTP read status, 0 = success, 1 = fail
#  unsigned char Locked; // boolean 0/1
#  unsigned short CID; // 2 bytes
#  unsigned char PAF; // boolean 0/1
#  char IMEI[14]; // IMEI 14 bytes binary array
#  unsigned char IMEIChangeable; // boolean 0/1
#  unsigned short RootKey; //1 byte
#  Unsigned short SecurityConfiguration; //1 byte
#  char CustomerOTP[21]; Customer OTP 21 bytes array
#} FXT_Sign_OTPData_DB3350_t;

class OtpDataDB3350(Structure):
  _fields_ = [("status", c_ubyte),
              ("locked", c_ubyte),
              ("cid", c_ushort),
              ("paf", c_ubyte),
              ("imei", c_ubyte* 14),
              ("changeable", c_ubyte),
              ("rootKey", c_ubyte),
              ("securityConfig", c_ubyte),
              ("customerOTP", c_ubyte*21)]

  def __str__(self):
    l = []
    l.append('status: ' + str(self.status) + '\n')
    l.append('locked: ' + str(self.locked) + '\n')
    l.append('cid: ' + str(self.cid) + '\n')
    l.append('paf: ' + str(self.paf) + '\n')
    l.append('imei: ' + str(self.imei) + '\n')
    l.append('chnble: ' + str(self.changeable) + '\n')
    l.append('rootKey: ' + str(self.rootKey) + '\n')
    l.append('securityConfig: ' + str(self.securityConfig) + '\n')
    l.append('customerOTP: ' + str(self.customerOTP) + '\n')
    return ''.join(l)

# typedef struct CertificateData
# {
#   T_CertificateType CertType;
#   unsigned int CertVersion;
#   unsigned int CID;
# } T_CertificateData;

class CertData(Structure):
  _fields_ = [("type", c_int),
              ("version", c_uint),
              ("cid", c_uint)]

  def __str__(self):
    l = []
    l.append('type: ' + str(self.type) + '\n')
    l.append('version: ' + str(self.version) + '\n')
    l.append('cid: ' + str(self.cid) + '\n')
    return ''.join(l)

# typedef struct FXT_Flash_ExtendedConfig
# {
#   unsigned char EFP;
#   unsigned char CheckErase;
#   unsigned char VerifyData;
#   unsigned char NoErase;
# } FXT_Flash_ExtendedConfig_t;

class FlashConfig(Structure):
  _fields_ = [("efp", c_ubyte),
              ("chkerase", c_ubyte),
              ("verify", c_ubyte),
              ("noerase", c_ubyte)]

  def __str__(self):
    l = []
    l.append('efp: ' + str(self.efp) + '\n')
    l.append('chk: ' + str(self.chkerase) + '\n')
    l.append('ver: ' + str(self.verify) + '\n')
    l.append('noe: ' + str(self.noerase) + '\n')
    return ''.join(l)

# typedef struct
# {
#   unsigned int Mode;
#   unsigned int NLink;
#   unsigned int Size;
#   unsigned int ATime;
#   unsigned int MTime;
#   unsigned int CTime;
# } T_EXStat;

class FsStat(Structure):
  _fields_ = [("mode", c_uint),
              ("nlink", c_uint),
              ("size", c_uint),
              ("atime", c_uint),
              ("mtime", c_uint),
              ("ctime", c_uint)]

  def __str__(self):
    l = []
    l.append('mode: ' + hex(self.mode) + '\n')
    l.append('nlink: ' + str(self.nlink) + '\n')
    l.append('size: ' + str(self.size) + '\n')
    l.append('atime: ' + str(self.atime) + '\n')
    l.append('mtime: ' + str(self.mtime) + '\n')
    l.append('ctime: ' + str(self.ctime) + '\n')
    return ''.join(l)


# typedef struct
# {
#   wchar_t *pName;
#   unsigned int NameSize;
#   unsigned int Mode;
#   unsigned int Size;
#   unsigned int Time;
# } FXT_FS_ListEntry_t;

class FsListEntry(Structure):
  _fields_ = [("name", POINTER(c_ushort)),
              ("namesize", c_uint),
              ("mode", c_uint),
              ("size", c_uint),
              ("time", c_uint)]

  def __init__(self):
    self.namesize = 256
    self.name = (c_ushort * self.namesize)()
    self.mode = 1
    self.size = 2
    self.time = 3

  def __str__(self):
    l = []
    l.append('a:' + oct(self.mode))
    l.append(' t:' + (time.strftime('%Y%m%d %H%M%S', time.localtime(self.time))))
    l.append(' s:' + str(self.size).rjust(6))
    l.append('  ' + self.nameStr())
    return ''.join(l)

  def nameStr(self):
    l = []
    for n in range(self.namesize):
      l.append(chr(self.name[n]))
      if self.name[n] == 0:
        break
    return ''.join(l)

class FsPartitionInfoV5(Structure):
  _fields_ = [("type_guid", c_ubyte*16),
              ("id_guid", c_ubyte*16),
              ("startBlock", c_ulong),
              ("endBlock", c_ulong),
              ("attribute", c_ulong),
              ("name", c_ubyte*72)]

  def __init__(self, buf):
    self.type_guid = (c_ubyte * 16)()
    for n in range(16):
      self.type_guid[n] = buf[n]
    self.id_guid = (c_ubyte * 16)()
    for n in range(16):
      self.id_guid[n] = buf[n+16]
    self.startBlock = 0
    for n in range(8):
      self.startBlock += buf[32+n] << 8*n
    self.endBlock = 0
    for n in range(8):
      self.endBlock += buf[40+n] << 8*n
    self.attribute = 0
    for n in range(8):
      self.attribute += buf[48+n] << 8*n
    self.name = (c_ubyte * 72)()
    for n in range(72):
      self.name[n] = buf[n+16+16+8+8+8]

  def __str__(self):
    l = []
    l.append('Type: ' + self.uniStr("type"))
    l.append(' Id: ' + self.uniStr("id"))
    l.append(' StartBlock: ' + hex(self.startBlock))
    l.append(' EndBlock: ' + hex(self.endBlock))
    l.append(' Attribute: ' + hex(self.attribute))
    l.append(' Name: ' + self.uniStr("name"))
    return ''.join(l)

  def uniStr(self, array):
    l = []

    if array == "id":
      for n in range(len(self.id_guid)):
        l.append(''.join("{:02x}".format(self.id_guid[n])))
    if array == "type":
      for n in range(len(self.type_guid)):
        l.append(''.join("{:02x}".format(self.type_guid[n])))
    if array == "name":
      for n in range(len(self.name)):
        l.append(chr(self.name[n]))

    return ''.join(l)

class FsPartitionInfoV6(Structure):
  _fields_ = [("name", c_ubyte*64),
              ("startBlock", c_ulong),
              ("endBlock", c_ulong),
              ("attribute", c_ulong)]

  def __init__(self, buf):
    self.name = (c_ubyte * 64)()
    for n in range(64):
      self.name[n] = buf[n]
    self.startBlock = 0
    for n in range(8):
      self.startBlock += buf[64+n] << 8*n
    self.endBlock = 0
    for n in range(8):
      self.endBlock += buf[72+n] << 8*n
    self.attribute = 0
    for n in range(8):
      self.attribute += buf[80+n] << 8*n

  def __str__(self):
    l = []
    l.append('Name: ' + self.nameStr())
    l.append(' StartBlock: ' + hex(self.startBlock))
    l.append(' EndBlock: ' + hex(self.endBlock))
    l.append(' Attribute: ' + hex(self.attribute))
    return ''.join(l)

  def nameStr(self):
    l = []
    for n in range(64):
      l.append(chr(self.name[n]))
      if self.name[n] == 0:
        break
    return ''.join(l)

class FsPartitionInfo(Structure):
  _fields_ = [("Id", c_uint),
              ("attribute", c_uint),
              ("startBlock", c_uint),
              ("nbrOfBlocks", c_uint)]

  def __init__(self):
    self.Id = 0
    self.attribute = 0
    self.startBlock = 0
    self.nbrOfBlocks = 0

  def __str__(self):
    l = []
    l.append('Id:' + str(self.Id))
    l.append('attribute:' + str(self.attribute))
    l.append('startBlock:' + str(self.startBlock))
    l.append('nbrOfBlocks:' + str(self.nbrOfBlocks))
    return ''.join(l)

  def pathStr(self):
    l = []
    for n in range(self.pathLength):
      l.append(self.mountPoint[n])
      if ord(self.mountPoint[n]) == 0:
        break
    return ''.join(l)

#typedef enum FXT_FS_PartitionType
#{
#  INTERNAL = 1,
#  DYNAMIC = 8,
#  EXTERNAL = 2
#}FXT_FS_PartitionType_t;

class FsPartitionType(Structure):
  _fields_ = [("Internal", c_int),
              ("Dynamic", c_int),
              ("External", c_int)]

  def __str__(self):
    l = []
    l.append('Internal: ' + str(self.Internal))
    l.append(', Dynamic: ' + str(self.Dynamic))
    l.append(', External: ' + str(self.External))
    return ''.join(l)

#typedef enum FXT_Flash_State
#{
#  NOT_STARTED  = 0x00,
#  ONGOING      = 0x01,
#  DONE         = 0x02,
#  FLASH_ERROR  = 0x03
#} FXT_Flash_State_t;

#// Progress / Total gives the percentage of the command executed.
#typedef struct FXT_Flash_Asynchronous_Status
#{
#  FXT_Flash_State_t State;
#  unsigned int Progress;
#  unsigned int Total;
#} FXT_Flash_Asynchronous_Status_t;

class AsynchFlashStatus(Structure):
  _fields_ = [("State", c_int),
              ("Progress", c_uint),
              ("Total", c_uint)]

  def __str__(self):
    l = []
    l.append('State: ' + str(self.State))
    l.append(', Progress: ' + str(self.Progress))
    l.append(', Total: ' + str(self.Total))
    return ''.join(l)

# typedef struct FlashStatistics
# {
#   unsigned int HandledBlocks;
#   unsigned int BadBlocks;
#   unsigned int NewBadBlocks;
# } T_FlashStatistics;

class FlashStat(Structure):
  _fields_ = [("handled", c_uint),
              ("bad", c_uint),
              ("new", c_uint)]

  def __str__(self):
    l = []
    l.append('handled: ' + str(self.handled))
    l.append(', bad: ' + str(self.bad))
    l.append(', new: ' + str(self.new))
    return ''.join(l)

class FlashExtendedStat(Structure):
  _fields_ = [("handled", c_uint),
              ("bad", c_uint),
              ("new", c_uint),
              ("singleErr", c_uint)]

  def __str__(self):
    l = []
    l.append('handled: ' + str(self.handled))
    l.append(', bad: ' + str(self.bad))
    l.append(', new: ' + str(self.new))
    l.append(', singleErr: ' + str(self.singleErr))
    return ''.join(l)
# ----------------------------------------------
# FxToolError
#

class FxToolNoError(Exception):
  def __init__(self, message):
    self.message = message
    print self

  def __str__(self):
    l = []
    l.append('\nFAILURE\n')
    l.append(' No error code set\n')
    l.append(' last error: ' + str(self.message) + '\n')
    return ''.join(l)

class FxToolError(Exception):
  def __init__(self, fxt, status=None):
    if isinstance(fxt, str): # check if fxt is actually message
      self.message = fxt
      self.status = status
    else:
      self.message = fxt.getLastError()
      if 'SECS' in self.message:
        secsError = fxt.getLastSecsError()
        if not secsError:
          secsError = 'None'
        self.message += ' (' + secsError + ')'
      self.status = None
      if not 'READ_SERIAL' in self.message:
        self.status = fxt.getResponseStatus()
    if '0x0000' in self.message:
      raise FxToolNoError(self.message)

  def __str__(self):
    l = []
    l.append('\nFAILURE\n')
    l.append(' last error: ' + str(self.message) + '\n')
    l.append(' response status: ' + str(self.status) + '\n')
    return ''.join(l)

# ----------------------------------------------
# FxTool
#

# FXTOOL_API unsigned int FXT_Main_GetHandle(const char *LogFileName, FXT_Loader_Type_t LoaderType);
# FXTOOL_API unsigned int FXT_Main_GetHandleEx(const char *LogFileName, FXT_Loader_Type_t LoaderType, FXT_Main_LogLevel_t LogLevel);
class FxTool():
  print 'Initializing FxTool dll.'
  print 'sys.platform:', sys.platform
  if sys.platform == 'win32':
    module = cdll.LoadLibrary('fxtool.dll')
    print 'Using fxtool dll in current directory'
  else:
    module = cdll.LoadLibrary('./libfxtool.so')
    print 'Using fxtool lib in current directory'

  def __init__(self, loadertype, level = 0, suffix = None, quiet = None):
    if not quiet:
      print 'FxTool, loader type:', loadertype
    self.loadertype = self.cleanLoaderType(loadertype)
    if not quiet:
      print 'log level:', level
    logfile = 0
    if level > 0:
      logfile = 'logs/fxtool_'
      if suffix:
        logfile += suffix
      else:
        logfile += time.strftime('%y%m%d-%H%M%S')
      logfile += '.log'
    self.handle = FxTool.module.FXT_Main_GetHandleEx(logfile, self.loadertype, level)
    if not quiet:
      print 'handle:', self.handle
    if self.handle == 0:
      raise FxToolError(self.getLastError(), 'No handle')
    self.partition = None
    self.first = True

  def cleanLoaderType(self, loadertype):
    if isinstance(loadertype, str):
      if 'no_loader' in loadertype.lower():
        loadertype = 0
      elif 'a2' in loadertype.lower():
        loadertype = 7
      elif 'zebra' in loadertype.lower():
        loadertype = 8
      elif 'lithium' in loadertype.lower():
        loadertype = 9
      elif 'pnx_4910' in loadertype.lower():
        loadertype = 17
      elif 's1' in loadertype.lower():
        loadertype = 10
      elif 'locosto' in loadertype.lower():
        loadertype = 11
      elif 'neptune' in loadertype.lower():
        loadertype = 12
      elif 'suzi' in loadertype.lower():
        loadertype = 13
      elif 'qualcomm_bootloader' in loadertype.lower():
        loadertype = 14
      elif 'qualcomm_7227' in loadertype.lower():
        loadertype = 15
      elif 'qualcomm_7x30' in loadertype.lower():
        loadertype = 18
      elif 'qualcomm_8x60' in loadertype.lower():
        loadertype = 19
      elif 'qualcomm_7225' in loadertype.lower():
        loadertype = 20
      elif 'qualcomm_8974' in loadertype.lower():
        loadertype = 21
      elif 'mediatek_boot' in loadertype.lower():
        loadertype = 22
      elif 'mediatek_debug' in loadertype.lower():
        loadertype = 23
      elif 'ste_8500' in loadertype.lower():
        loadertype = 16
      elif 'prod' in loadertype.lower():
        loadertype = 4
      elif 'reset' in loadertype.lower():
        loadertype = 4
      elif 'expl' in loadertype.lower():
        loadertype = 2
      elif 'flash' in loadertype.lower():
        loadertype = 1
      print ' loader type adjusted:', loadertype
    return loadertype

# FXTOOL_API int FXT_Main_ReleaseHandle(unsigned int Handle);
  def __del__(self, quiet = None):
    if self.handle:
      if not quiet:
        print 'Terminating FxTool, handle:', self.handle
      FxTool.module.FXT_Main_ReleaseHandle(self.handle)

# FXTOOL_API int FXT_Main_ReleaseHandle(unsigned int Handle);
  def releaseHandle(self, quiet = None):
    if self.handle:
      if not quiet:
        print 'Terminating FxTool, handle:', self.handle
      FxTool.module.FXT_Main_ReleaseHandle(self.handle)
# FXTOOL_API int FXT_Main_SetLogLevel(FXT_Main_LogLevel_t LogLevel, const char *LogFilename, unsigned int Handle)
  def setLogLevel(self, level, name = None):
    print 'Setting log, level:', level
    if not FxTool.module.FXT_Main_SetLogLevel(level, name, self.handle):
      raise FxToolError(self.getLastError(), 'Set log level failure')

# FXTOOL_API int FXT_Main_SetLoaderType(FXT_Loader_Type_t LoaderType, unsigned int Handle);
  def setLoaderType(self, loadertype):
    print 'Setting loadertype:', loadertype, '...'
    loadertype = self.cleanLoaderType(loadertype)
    if not FxTool.module.FXT_Main_SetLoaderType(loadertype, self.handle):
      raise FxToolError(self.getLastError())
    self.loadertype = loadertype
    print 'Loadertype set OK'

# FXTOOL_API int FXT_Comm_Open(const char *pPort, int WaitForMS, unsigned int Handle);
# FXTOOL_API int FXT_Comm_OpenWithTimeout(const char *pPort, int WaitForMS, unsigned int MillisecTimeout, unsigned int Handle);
  def connect(self, com, timeout = 10, quiet = None):
    if not quiet:
      print 'Connecting to device on', com
    if timeout > 0:
      if not quiet:
        print 'Please connect within', timeout, 'sec.'
    timeout *= 1000
    if 'USB' in com:
      com = '\\\\.\\EPI' + com[com.index('USB'):]
    if 'DFU' in com:
      com = '\\\\.\\' + com[com.index('PNXDFU'):]
    self.com = com
    if not quiet:
      print 'new log' , self.com
    if not FxTool.module.FXT_Comm_OpenWithTimeout(self.com, 1, timeout, self.handle):
      raise FxToolError(self)

  def connectWithSpeed(self, com, speed = 9600, timeout = 10, quiet = None):
    if not quiet:
      print 'Connecting to device on', com
    if timeout > 0:
      if not quiet:
        print 'Please connect within', timeout, 'sec.'
    timeout *= 1000
    if 'USB' in com:
      com = '\\\\.\\EPI' + com[com.index('USB'):]
    self.com = com
    if not FxTool.module.FXT_Comm_OpenWithTimeoutAndSpeed(self.com, 1, speed, timeout, self.handle):
      raise FxToolError(self)

# FXTOOL_API int FXT_Comm_Close(unsigned int Handle);
  def disconnect(self, quiet = None):
    if not quiet:
      print 'Closing communication ...'
    self.first = True
    if not FxTool.module.FXT_Comm_Close(self.handle):
      raise FxToolError(self.getLastError())
    if not quiet:
      print 'Closed OK'

  def reopen(self, com, timeout = 10, quiet = None):
    if not quiet:
      print 'Connecting to device on', com
    if timeout > 0:
      if not quiet:
        print 'Please connect within', timeout, 'sec.'
    timeout *= 1000
    #if 'USB' in com:
      #com = '\\\\.\\EPI' + com[com.index('USB'):]
    self.com = com
    if not FxTool.module.FXT_Comm_ReOpenWithTimeout(com, timeout, self.handle):
      raise FxToolError(self)
    if not quiet:
      print('Re-Open OK')

 #FXTOOL_API int FXT_Comm_SwitchToUsb(const char *pPort, unsigned int MillisecTimeout, unsigned int Handle);
  def switchToUsb(self, com, timeout = 0):
    print 'switching to USB'
    if not FxTool.module.FXT_Comm_SwitchToUsb(com, timeout, self.handle):
      raise FxToolError(self)
    print('switch to USB OK')

  def enableUsbHighspeed(self, com):
    print 'Enabling USB high speed'
    if not FxTool.module.FXT_Comm_EnableUSBHighSpeed(com, self.handle):
      raise FxToolError(self)
    print('Enable High Speed OK')

# FXTOOL_API int FXT_Comm_Abort(unsigned int Handle);
  def abort(self):
    print 'Aborting ...'
    if not FxTool.module.FXT_Comm_Abort(self.handle):
      raise FxToolError(self)
    print 'Aborted OK'

# FXTOOL_API int FXT_Comm_RebootMS(FXT_Loader_Type_t NextLoader, unsigned int Handle);
  def reboot(self, loadertype = 0):
    print 'Rebooting ...'
    if loadertype != 0:
      self.loadertype = loadertype
    self.first = True
    if not FxTool.module.FXT_Comm_RebootMS(self.loadertype, self.handle):
      raise FxToolError(self)
    print 'Rebooted OK'

# FXTOOL_API int FXT_Comm_ShutdownMS(unsigned int Handle);
  def shutdown(self, behaviour = None, quiet = None):
    if not quiet:
      print 'Shutting down ...'
    self.first = True
    if behaviour == None:
      if not FxTool.module.FXT_Comm_ShutdownMS(self.handle):
        raise FxToolError(self)
      if not quiet:
        print 'Shutdown OK'
    else:
      if not FxTool.module.FXT_Comm_ShutdownMSWithBehaviour(behaviour,self.handle):
        raise FxToolError(self)
      if not quiet:
        print 'Shutdown OK'

  def autoActivateLoaders(self, path, choice='production'):
    """ find all loaders lower in subtree pointed to by path.
        if loader not signed, or bin file is newer than ldr file, let's sign it
    """

    loaderTemplates = ('PRE_LOADER_ACC',
                       'PRE_LOADER_APP',
                       'PRODUCTION_LOADER_ACC',
                       'PRODUCTION_LOADER_APP',
                       'EXPLORER_LOADER_APP')

    if choice == 'reset':
      loaderTemplates = ('PRE_LOADER_ACC',
                         'PRE_LOADER_APP',
                         'RESET_LOADER_ACC',
                         'RESET_LOADER_APP')

    loaderBins = {}
    loaderLdrs = {}

    print 'Looking for loaders in:', path

    for root, dirs, files in os.walk(path):
      for f in files:
#        print 'file:', f, 'at:', root
        if f.endswith('.bin'):
          for t in loaderTemplates:
            if t in f:
              filepath = root + '/' + f
              if t not in loaderBins:
                loaderBins[t] = filepath
              else:
                print 'WARNING: More than 1 loader found for:', t
                print ' ', loaderBins[t]
                print ' ', filepath
        elif f.endswith('.ldr'):
          for t in loaderTemplates:
            if t in f:
              filepath = root + '/' + f
#              print 'found loader:', filepath
              if t not in loaderLdrs:
                loaderLdrs[t] = filepath
              else:
                print 'WARNING: More than 1 loader found for:', t
                print ' ', loaderLdrs[t]
                print ' ', filepath

    if len(loaderBins) > 4:
      print 'Too many loaders found ',
      # should we keep explorer loader or production loader
      if 'EXPL' in choice.upper():
        print 'using explorer loader'
        del loaderBins['PRODUCTION_LOADER_APP']
      else:
        print 'using production loader'
        del loaderBins['EXPLORER_LOADER_APP']
    elif len(loaderLdrs) > 4:
      print 'Too many loaders found ',
      # should we keep explorer loader or production loader
      if 'EXPL' in choice.upper():
        print 'using explorer loader'
        del loaderLdrs['PRODUCTION_LOADER_APP']
      else:
        print 'using production loader'
        del loaderLdrs['EXPLORER_LOADER_APP']

    loaders = []
    for t in loaderTemplates:
      if t in loaderBins:
        print ' ', t, ':', loaderBins[t]
        if t in loaderLdrs and os.path.getmtime(loaderLdrs[t]) >= os.path.getmtime(loaderBins[t]):
          loaders.append(loaderLdrs[t])
        else:
          print 'ERROR: No or old ldr file, please sign and try again.'
          return False
      elif len(loaderBins) == 0 and t in loaderLdrs:
        print ' ', t, ':', loaderLdrs[t]
        loaders.append(loaderLdrs[t])

    if (len(loaders) == 0):
      raise FxToolError('No loaders found.')
    return self.activateLoaders(loaders)

# FXTOOL_API int FXT_Loader_DownloadAndExecute(const unsigned char* pLoader, const char* pSpeed, char* pLoaderVersion, unsigned int VersionLength, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadAndExecuteWithType(const unsigned char* pLoader, FXT_Loader_Type_t LoaderType, const char* pSpeed, char* pLoaderVersion, unsigned int VersionLength, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadAndExecuteWithLength(const unsigned char* pLoader, unsigned int LoaderLength, const char* pSpeed, char* pLoaderVersion, unsigned int VersionLength, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadAndExecuteWithLengthAndType(const unsigned char* pLoader, unsigned int LoaderLength, FXT_Loader_Type_t LoaderType, const char* pSpeed, char* pLoaderVersion, unsigned int VersionLength, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadAndExecuteWithTypeFromFile(const char* pFilename, FXT_Loader_Type_t LoaderType, const char* pSpeed, char* pLoaderVersion, unsigned int VersionLength, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadAndExecuteWithTypeFromHandle(unsigned int LoaderHandle, FXT_Loader_Type_t LoaderType, const char* pSpeed, char* pLoaderVersion, unsigned int VersionLength, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadOnLoader(const unsigned char* pLoader, char* pLoaderVersion, unsigned int VersionLength, FXT_Loader_Type_t LoaderType, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadOnLoaderWithLengthAndType(const unsigned char* pLoader, unsigned int LoaderLength, char* pLoaderVersion, unsigned int VersionLength, FXT_Loader_Type_t LoaderType, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadOnLoaderFromFile(const char* pFilename, char* pLoaderVersion, unsigned int VersionLength, FXT_Loader_Type_t LoaderType, unsigned int Handle);
# FXTOOL_API int FXT_Loader_DownloadOnLoaderFromHandle(unsigned int LoaderHandle, char* pLoaderVersion, unsigned int VersionLength, FXT_Loader_Type_t LoaderType, unsigned int Handle);
  def activateLoaders(self, loaders, speed='921600', quiet = None):
    # do execute on first in list, then loaderonloader
    first = True
    if isinstance(loaders, str):
      l = []
      l.append(loaders)
      loaders = l
    for ln in loaders:
      if not ln:
        break
      if not quiet:
        print 'Loader:', ln
      f = open(ln, 'rb')
      l = f.read()
      f.close();
      # guess loadertype from loader filename
      loadertype = 0
      if 'DB31XX' in ln:
        loadertype = 7
      elif 'DB3200' in ln:
        loadertype = 7
      elif 'DB3210' in ln:
        loadertype = 7
      elif 'DB3350' in ln:
        loadertype = 7
      elif '.exe' in ln.lower():
        loadertype = 8 # zebra
      elif 'ramlite' in ln.lower():
        loadertype = 13 # suzi boot
      elif '.img' in ln.lower():
        loadertype = 13
      elif '.sin' in ln.lower():
        loadertype = 10 # S1
      elif 'neptune' in ln.lower():
        loadertype = 12
      elif '.bin' in ln.lower():
        loadertype = 9 # lithium
      elif 'flashloader' in ln.lower():
        loadertype = 1
      elif 'explorerloader' in ln.lower() or 'filesystemloader' in ln.lower():
        loadertype = 2
      elif 'recoveryloader' in ln.lower():
        loadertype = 3
      elif 'production' in ln.lower():
        loadertype = 4
      elif 'resetloader' in ln.lower():
        loadertype = 4
      elif 'csloader' in ln.lower():
        loadertype = 5
      elif 'idloader' in ln.lower():
        loadertype = 6
      elif '.ldr' in ln.lower():
        loadertype = 11 # locosto boot
      elif 'qual' in ln.lower():
        loadertype = 14
      elif '8500' in ln.lower():
        loadertype = 16
      else:
        print 'Can not guess loader type from filename:', ln

      if self.loadertype == 0 or loadertype != 0:
        self.loadertype = loadertype
      if not quiet:
        print 'Loader type:', self.loadertype, 'speed:', speed
      v = create_string_buffer(4096)
      if first:
        if self.loadertype == 8 or self.loadertype == 9 or self.loadertype == 10 or self.loadertype == 11 or self.loadertype == 12 or self.loadertype == 13 or self.loadertype == 14 or self.loadertype == 16 or self.loadertype == 18:
          r = FxTool.module.FXT_Loader_DownloadAndExecuteWithLengthAndType(l, len(l), self.loadertype, speed, byref(v), len(v), self.handle)
        else:
          r = FxTool.module.FXT_Loader_DownloadAndExecuteWithType(l, self.loadertype, speed, byref(v), len(v), self.handle)
        first = False
      else:
        if self.loadertype == 8 or self.loadertype == 13 or self.loadertype == 10:
          r = FxTool.module.FXT_Loader_DownloadOnLoaderWithLengthAndType(l, len(l), byref(v), len(v), loadertype, self.handle)
        else:
          r = FxTool.module.FXT_Loader_DownloadOnLoader(l, byref(v), len(v), loadertype, self.handle)
      if r:
        if not quiet:
          print ' Version:', v.value
      else:
        raise FxToolError(self)
      if not quiet:
        print ' Loader size:', self.getBytesFlashed()

  def activateLoader(self, loaderhandle, loadertype, speed='921600', quiet = None):
    if not quiet:
      print 'Activating loader from handle:', loaderhandle, 'type:', loadertype
    self.loadertype = self.cleanLoaderType(loadertype)
    v = create_string_buffer(16384)
    if self.first:
      r = FxTool.module.FXT_Loader_DownloadAndExecuteWithTypeFromHandle(loaderhandle, self.loadertype, speed, byref(v), len(v), self.handle)
      #self.first = False
    else:
      r = FxTool.module.FXT_Loader_DownloadOnLoaderFromHandle(loaderhandle, byref(v), len(v), self.loadertype, self.handle)
    if r:
      if not quiet:
        print ' Version:', v.value
    else:
      raise FxToolError(self)
    if not quiet:
      print ' Loader size:', self.getBytesFlashed()

  def activateLoaderOnLoader(self, loaderhandle, loadertype, quiet = None):
    if not quiet:
      print 'Activating loader on loader from handle:', loaderhandle, 'type:', loadertype
    self.loadertype = self.cleanLoaderType(loadertype)
    v = create_string_buffer(16384)
    r = FxTool.module.FXT_Loader_DownloadOnLoaderFromHandle(loaderhandle, byref(v), len(v), self.loadertype, self.handle)
    if r:
      if not quiet:
        print ' Version:', v.value
    else:
      raise FxToolError(self)
    if not quiet:
      print ' Loader size:', self.getBytesFlashed()

  def checkFile(self, filename):
    print 'Checking file:', filename, '...'
    f = open(filename, 'rb')
    f.close()
    print 'File checked OK'

# FXTOOL_API int FXT_Loader_GetSystemInfo(unsigned char *pSystemInfo, unsigned int SystemInfoLength, unsigned int Handle)
  def getSystemInfo(self, quiet = None):
    if not quiet:
      print 'System info ...'
    v = create_string_buffer(16384)
    if not FxTool.module.FXT_Loader_GetSystemInfo(byref(v), len(v), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'System info:', v.value
    return v.value

# FXTOOL_API int FXT_Loader_GetBootInfo(unsigned char *pBootInfo, unsigned int BootInfoLength, unsigned int Handle)
  def getBootInfo(self, quiet = None):
    if not quiet:
      print 'Boot info ...'
    v = create_string_buffer(512)
    if not FxTool.module.FXT_Loader_GetBootInfo(byref(v), len(v), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Boot info:', v.value
    return v.value

# FXTOOL_API int FXT_Loader_IntrinsicCommandSupport(unsigned int Handle);
  def getIntrinsicCommandSupport(self, quiet=None):
    if not quiet:
      print 'Intrinsic command support ...'
    r = FxTool.module.FXT_Loader_IntrinsicCommandSupport(self.handle)
    if r:
      print 'Instrinsic commands SUPPORTED'
    else:
      print 'Instrinsic commands NOT supported'
    return r
# depreciated, use getBootInfo

# FXTOOL_API unsigned int FXT_Flash_UploadImage(const unsigned char* pImage, unsigned int ImageSize);
# FXTOOL_API unsigned int FXT_Flash_UploadImageFromFile(const char* pFilename);
  def uploadFlashImage(self, filename, quiet=None):
    if not quiet:
      print 'Preparing image:', filename, '...'
    r = FxTool.module.FXT_Flash_UploadImageFromFile(filename)
    if not quiet:
       print 'Image uploaded, handle:', r
    if r == 0:
      raise FxToolError(self.getLastError('gen'))
    return r

  def uploadFlashImageV2(self, filename, quiet=None):
    if not quiet:
      print 'Preparing image:', filename, '...'
    r = FxTool.module.FXT_Flash_UploadImageFromFileV2(filename)
    if not quiet:
      print 'Image uploaded, handle:', r
    if r == 0:
      raise FxToolError(self.getLastError('gen'))
    return r

  def uploadFlashImageWV2(self, filename, quiet=None):
    if not quiet:
      print 'Preparing image:', filename, '...'
    r = FxTool.module.FXT_Flash_UploadImageFromFileWV2(filename)
    if not quiet:
      print 'Image uploaded, handle:', r
    if r == 0:
      raise FxToolError(self.getLastError('gen'))
    return r

#TEMP JUST TO TEST THE UPLOAD FROM FILE
  def uploadFlashImageFromFile(self, filename, loadertype, speed='921600', quiet=None):
    if not quiet:
      print 'Preparing image:', filename, '...'
    v = create_string_buffer(16384)
    r = FxTool.module.FXT_Loader_DownloadAndExecuteWithTypeFromFile(filename,self.loadertype, speed, byref(v), len(v), self.handle)
    if not quiet:
      print 'Image uploaded, handle:', r
    if r == 0:
      raise FxToolError(self.getLastError('gen'))
    return r

# Replacement for create_unicode_buffer, creates 16-bit unicode string
  def create_u16_buffer(self, ascstr, forceLen = -1):
    if (forceLen == -1):
      u16buf = (c_ushort * (len(ascstr) + 1))()
    else:
      u16buf = (c_ushort * forceLen)()
    k = 0
    for a in ascstr:
      u16buf[k] = ord(a)
      k = k + 1
    u16buf[k] = 0
    return u16buf

  def u16string(self, u16buf):
    s = ''
    for a in u16buf:
      s = s + chr(a)
    return s

#FXTOOL_API unsigned int FXT_Flash_UploadImageFromFileW(const wchar_t* pFilename);
  def uploadFlashImageFromUnicodePath(self, filename):
    print 'Preparing image:', filename, '...'
    unipath = create_unicode_buffer(filename);
    r = FxTool.module.FXT_Flash_UploadImageFromFileW(byref(unipath))
    print 'Image uploaded, handle:', r
    if r == 0:
      raise FxToolError(self.getLastError('gen'))
    return r

# FXTOOL_API int FXT_Flash_ReleaseImage(unsigned int ImageHandle);
  def releaseFlashImage(self, handle, quiet=None):
    if not quiet:
      print 'Releasing image:', handle, '...'
    if not FxTool.module.FXT_Flash_ReleaseImage(handle):
      raise FxToolError(self.getLastError('gen'))

# FXTOOL_API unsigned int FXT_Flash_GetImage(const unsigned char* pImage, unsigned int* pSize, unsigned int imageHandle)
  def getImage(self, handle, quiet=None):
    d = c_uint()
    s = c_uint()
    if not FxTool.module.FXT_Flash_GetImage(byref(d), byref(s), handle):
      raise FxToolError(self.getLastError('gen'))
    if not quiet:
      print 'Image size:', s.value
      print 'image address:', hex(d.value)
      #print 'image address:', d.value
    return s.value

# FXTOOL_API unsigned int FXT_Flash_GetImage(const unsigned char* pImage, unsigned int* pSize, unsigned int imageHandle)
  def getImageV2(self, handle, quiet=None):
    d = c_uint()
    s = c_uint()
    t = c_uint()
    if not FxTool.module.FXT_Flash_GetImageV2(byref(d), byref(s), byref(t),handle):
      raise FxToolError(self.getLastError('gen'))
    if not quiet:
      print 'actual Image size:', s.value
      print 'available size:', t.value
      print 'image address:', hex(d.value)
      #print 'image address:', d.value
    return s.value

# FXTOOL_API int FXT_GetVersion(const char* pVersion)
  def getVersion(self):
    d = (c_char*10)()
    FxTool.module.FXT_GetVersion(byref(d), 10)
    print 'Version:', d.value

# FXTOOL_API int FXT_Flash_CompressImage(unsigned int ImageHandle);
  def compressFlashImage(self, handle):
    print 'Compressing image ...'
    if not FxTool.module.FXT_Flash_CompressImage(handle):
      raise FxToolError(self.getLastError('gen'))
    print 'Compressed OK'

# FXTOOL_API int FXT_Flash_GetImageSize(unsigned int* pSize, unsigned int ImageHandle)
  def getImageSize(self, handle, quiet=None):
    s = c_uint()
    if not FxTool.module.FXT_Flash_GetImageSize(byref(s), handle):
      raise FxToolError(self.getLastError('gen'))
    if not quiet:
      print 'Image size:', s.value
    return s.value

# FXTOOL_API int FXT_Flash_LoadAndVerifyCompressedImageFromHandle(unsigned int ImageHandle, unsigned int Handle)
  def flashCompressedImageFromHandle(self, handle):
    print 'Flash sequence (compressed image) starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Flash_ProgramCompressedImageFromHandle(handle, self.handle):
      td = time.time() - t1
      s = 0
      l = self.getBytesFlashed()
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_SetECCMode(unsigned char Mode , unsigned int Handle);
  def flashSetECCMode(self, Mode):
    if not FxTool.module.FXT_Flash_SetECCMode(Mode,self.handle):
      raise FxToolError(self)
    print 'Set ECC mode OK'

#   FXTOOL_API int FXT_Flash_SetBlockStatus(unsigned int Start, unsigned int NbrOfBlocks, unsigned char Status, unsigned int Handle);
  def flashSetBlockStatus(self, start, nbrOfBlocks, status):
    if not FxTool.module.FXT_Flash_SetBlockStatus(start, nbrOfBlocks, status,self.handle):
      raise FxToolError(self)
    print 'Setting block status OK'

#   FXTOOL_API int FXT_Flash_SetBlockStatus(unsigned int Start, unsigned int NbrOfBlocks, unsigned char Status, unsigned int Handle);
  def flashSetBlockStatusWithMid(self, start, end, mid, status):
    if not FxTool.module.FXT_Flash_SetBlockStatusWithMID(start, end, mid, status,self.handle):
      raise FxToolError(self)
    print 'Setting block status OK'

# FXTOOL_API bool LoadAndVerifyFlashImage(void* FlashImagePointer, unsigned int size, unsigned int HandleIndex);
  def flashImage(self, filename):
    print 'Preparing flash image from file:', filename, '...'
    f = open(filename, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    print 'Flash sequence starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Flash_LoadAndVerifyBinaryImage(image, l, self.handle):
      td = time.time() - t1
      s = 0
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

  def loadAndVerifyImage(self, image, quiet=None):
    if not quiet:
      print 'Preparing flash image from image'
    l = len(image)
    if not quiet:
      print 'Flash sequence starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Flash_LoadAndVerifyBinaryImage(image, l, self.handle):
      td = time.time() - t1
      s = 0
      if td:
        s = l * 8 / td / 1024
      if not quiet:
        print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      if not quiet:
        print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_LoadAndVerifyBinaryImageFromHandle(unsigned int ImageHandle, unsigned int Handle)
  def loadAndVerifyImageFromHandle(self, imagehandle):
    print 'Preparing flash image from imagehandle:', imagehandle, '...'

    print 'Flash sequence starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Flash_LoadAndVerifyBinaryImageFromHandle(imagehandle, self.handle):
      td = time.time() - t1
      s = 0
      l = self.getBytesFlashed()
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)


  def flashTestImage(self, filename):
    print 'Preparing flash image from file:', filename, '...'
    f = open(filename, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    print 'Flash sequence starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Test_LoadImage(image, l, self.handle):
      td = time.time() - t1
      s = 0
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_ProgramImageFromFile(const char* pFilename, unsigned int Handle);
  def flashImageFromFile(self, filename):
    print 'Flash sequence starting ...'
    print 'WARNING: Flash time will include time for image preparation from file:', filename
    t1 = time.time()
    if FxTool.module.FXT_Flash_ProgramImageFromFile(filename, self.handle):
      td = time.time() - t1
      s = 0
      l = self.getBytesFlashed()
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_ProgramImageFromHandle(unsigned int ImageHandle, unsigned int Handle);
  def flashImageFromHandle(self, handle, quiet=None):
    if not quiet:
      print 'Flash sequence starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Flash_ProgramImageFromHandle(handle, self.handle):
      td = time.time() - t1
      s = 0
      l = self.getBytesFlashed()
      if td:
        s = l * 8 / td / 1024
      if not quiet:
        print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      if not quiet:
        print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_ProgramImageFromHandle(unsigned int ImageHandle, unsigned int Handle);
  def flashImageFromHandleAsynch(self, asynch, handle):
    print 'Flash sequence starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Flash_ProgramImageFromHandleAsynch(handle, asynch, self.handle):
      td = time.time() - t1
      s = 0
      l = self.getBytesFlashed()
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Transferred:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_ProgramImageInSession(const unsigned char* pImage, unsigned int ImageSize, unsigned int ImageType, int EraseDevice, unsigned int Handle)
  def flashImageInSession(self, filename, type, erase = 0):
    print 'Preparing flash image from file:', filename, '...'
    if isinstance(type, str):
      if 'miniboot' in type.lower():
        type = 0
      elif 'coreloader' in type.lower():
        type = 1
      elif 'erom' in type.lower():
        type = 2
      elif 'coreos' in type.lower():
        type = 3
      elif 'rofs1' in type.lower():
        if 'ext' in type.lower():
          type = 0x105
        else:
          type = 4
      elif 'rofs2' in type.lower():
        type = 6
      elif 'user' in type.lower():
        type = 8
      else:
        print 'Can not guess image type from:', type
    print 'Type:', hex(type)
    print 'Flash sequence starting ...'
    f = open(filename, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    t1 = time.time()
    if FxTool.module.FXT_Flash_ProgramImageInSession(image, l, type, erase, self.handle):
      td = time.time() - t1
      s = 0
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_ProgramImageInSessionFromHandle(unsigned int ImageHandle, unsigned int ImageType, int EraseDevice, unsigned int Handle)
  def flashImageInSessionFromHandle(self, handle, type, erase = 0):
    print 'Flash sequence starting ...'
    if isinstance(type, str):
      if 'miniboot' in type.lower():
        type = 0
      elif 'coreloader' in type.lower():
        type = 1
      elif 'erom' in type.lower():
        type = 2
      elif 'coreos' in type.lower():
        type = 3
      elif 'rofs1' in type.lower():
        if 'ext' in type.lower():
          type = 0x105
        else:
          type = 4
      elif 'rofs2' in type.lower():
        type = 6
      elif 'user' in type.lower():
        type = 8
      else:
        print 'Can not guess image type from:', type
    print 'Type:', hex(type)
    t1 = time.time()
    if FxTool.module.FXT_Flash_ProgramImageInSessionFromHandle(handle, type, erase, self.handle):
      td = time.time() - t1
      s = 0
      l = self.getBytesFlashed()
      if td:
        s = l * 8 / td / 1024
      print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Flash_ProgramImageEndSession(unsigned int Handle)
  def flashImageEndSession(self):
    print 'Ending flash session ...'
    if not FxTool.module.FXT_Flash_ProgramImageEndSession(self.handle):
      raise FxToolError(self)
    print 'Flash session end OK'

# FXTOOL_API bool ReadImageFromFlash(const char *Filename, unsigned int StartAddress, unsigned int EndAddress, unsigned int Handle)
  def readImage(self, filename, start, end, quiet=None):
    if not quiet:
      print 'Dumping image, range:', hex(start) + '--' + hex(end), 'to file:', filename
    end -= 1 # end is not inclusive here, but in fxtool it is
    t1 = time.time()
    if not FxTool.module.FXT_Flash_DumpFlashToFile(filename, start, end, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    l = self.getBytesFlashed()
    if td:
      s = l * 8 / td / 1024
    if not quiet:
      print 'Dumped', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'

# FXTOOL_API bool FXT_Flash_S1DumpFlashToFile(const char* Filename, unsigned int Start, unsigned int End, unsigned int MID, unsigned int Handle)
  def readImage_S1(self, filename, start, end, mid, quiet=None):
    if not quiet:
      print 'Dumping image, range:', hex(start) + '--' + hex(end), 'to file:', filename
    end -= 1 # end is not inclusive here, but in fxtool it is
    t1 = time.time()
    if not FxTool.module.FXT_Flash_S1DumpFlashToFile(filename, start, end, mid, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    l = self.getBytesFlashed()
    if td:
      s = l * 8 / td / 1024
    if not quiet:
      print 'Dumped', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'

# FXTOOL_API bool FXT_Flash_S1DumpFlashToFileWithFlag(const char* Filename, unsigned int Start, unsigned int End, unsigned int MID, unsigned int Flag, unsigned int Handle)
  def readImage_S1WithFlag(self, filename, start, end, mid, flag, quiet=None):
    if not quiet:
      print 'Dumping image, range:', hex(start) + '--' + hex(end), 'to file:', filename
    end -= 1 # end is not inclusive here, but in fxtool it is
    t1 = time.time()
    if not FxTool.module.FXT_Flash_S1DumpFlashToFileWithFlag(filename, start, end, mid, flag, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    l = self.getBytesFlashed()
    if td:
      s = l * 8 / td / 1024
    if not quiet:
      print 'Dumped', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'

# FXTOOL_API bool FXT_Flash_S1DumpFlashToFileWithBlock(const char* Filename, unsigned int Start, unsigned int End, unsigned int MID, unsigned int Flag, unsigned int BlockSize, unsigned int Handle)
  def readImage_S1WithBlock(self, filename, start, end, mid, flag, blocksize, quiet=None):
    if not quiet:
      print 'Dumping image, range:', hex(start) + '--' + hex(end), 'to file:', filename
    end -= 1 # end is not inclusive here, but in fxtool it is
    t1 = time.time()
    if not FxTool.module.FXT_Flash_S1DumpFlashToFileWithBlock(filename, start, end, mid, flag, blocksize, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    l = self.getBytesFlashed()
    if td:
      s = l * 8 / td / 1024
    if not quiet:
      print 'Dumped', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'

# FXTOOL_API int FXT_Flash_DumpFlashToBuffer(unsigned char* pBuf, unsigned int BufSize, unsigned int Start, unsigned int End, unsigned int Handle)
  def readImageToBuffer(self, start, end, length=0, quiet=None):
    if not quiet:
      print 'Dumping image, range:', hex(start) + '--' + hex(end), 'to buffer ...'
    end -= 1 # end is not inclusive here, but in fxtool it is
    if not length:
      length = end - start + 1
    d = (c_ubyte * length)()
    t1 = time.time()
    if not FxTool.module.FXT_Flash_DumpFlashToBuffer(byref(d), length, start, end, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    l = self.getBytesFlashed()
    if td:
      s = l * 8 / td / 1024
    if not quiet:
      print 'Dumped', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    l = []
    for n in range(0, length):
      l.append(d[n])
    return l

# FXTOOL_API int FXT_Flash_S1DumpFlashToBuffer(unsigned char* pBuf, unsigned int BufSize, unsigned int Start, unsigned int End, unsigned int MID, unsigned int Handle)
  def readImageToBuffer_S1(self, start, end, mid, length=0, quiet=None):
    if not quiet:
      print 'Dumping image, range:', hex(start) + '--' + hex(end), 'to buffer ...'
    end -= 1 # end is not inclusive here, but in fxtool it is
    if not length:
      length = end - start + 1
    d = (c_ubyte * length)()
    t1 = time.time()
    if not FxTool.module.FXT_Flash_S1DumpFlashToBuffer(byref(d), length, start, end, mid, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    l = self.getBytesFlashed()
    if td:
      s = l * 8 / td / 1024
    if not quiet:
      print 'Dumped', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    l = []
    for n in range(0, length):
      l.append(d[n])
    return l

# FXTOOL_API int FXT_Flash_S1DumpFlashToBufferWithFlag(unsigned char* pBuf, unsigned int BufSize, unsigned int Start, unsigned int End, unsigned int MID, unsigned int Handle)
  def readImageToBuffer_S1WithFlag(self, start, end, mid, length, flag, quiet=None):
    if not quiet:
      print 'Dumping image, range:', hex(start) + '--' + hex(end), 'to buffer ...'
    end -= 1 # end is not inclusive here, but in fxtool it is
    if not length:
      length = end - start + 1
    d = (c_ubyte * length)()
    t1 = time.time()
    if not FxTool.module.FXT_Flash_S1DumpFlashToBufferWithFlag(byref(d), length, start, end, mid, flag, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    l = self.getBytesFlashed()
    if td:
      s = l * 8 / td / 1024
    if not quiet:
      print 'Dumped', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    l = []
    for n in range(0, length):
      l.append(d[n])
    return l

#FXTOOL_API int FXT_Flash_EraseFlash(unsigned int Start, unsigned int End, unsigned char MID, unsigned int Handle)
  def eraseFlash(self, start, end, mid):
    print 'Erasing flash, address range:', hex(start) + '--' + hex(end)
    if not FxTool.module.FXT_Flash_EraseFlash(start, end, mid, self.handle):
      raise FxToolError(self)
    print 'Erasing flash OK'

#FXTOOL_API int FXT_Flash_EraseFlashWithFlag(unsigned int Start, unsigned int End, unsigned char MID, unsigned int Flag, unsigned int Handle)
  def eraseFlashWithFlag(self, start, end, mid, flag):
    print 'Erasing flash, address range:', hex(start) + '--' + hex(end)
    if not FxTool.module.FXT_Flash_EraseFlashWithFlag(start, end, mid, flag, self.handle):
      raise FxToolError(self)
    print 'Erasing flash OK'

#FXT_Flash_BadBlockScan(unsigned int Start, unsigned int End, unsigned int* BadBlock, unsigned int Count, unsigned int Handle)
  def scanBadBlock(self, start, end):
    print 'Scanning flash, address range:', hex(start) + '--' + hex(end)
    Count = c_uint(8192)
    badBlock = (c_uint * Count.value)()
    if not FxTool.module.FXT_Flash_BadBlockScan(start, end, byref(badBlock), byref(Count), self.handle):
      raise FxToolError(self)
    for i in range(Count.value):
      print 'Bad Block Addr:',  badBlock[a]
    print 'Scanning flash OK'

#FXT_Flash_BadBlockScanS1(unsigned int Start, unsigned int End, unsigned char MID, unsigned int* BadBlock, unsigned int Count, unsigned int Handle)
  def scanBadBlockWithMid(self, start, end, mid):
    print 'Scanning flash, address range:', hex(start) + '--' + hex(end)
    badList = []
    Count = c_uint(16384)
    badBlock = (c_ubyte * Count.value)()
    if not FxTool.module.FXT_Flash_BadBlockScanWithMID(start, end, mid, byref(badBlock), byref(Count), self.handle):
      raise FxToolError(self)

    print 'Found', Count.value, 'bad blocks.'
    for a in range(Count.value):
      badList.append(hex(badBlock[4 * a] | (badBlock[(4 * a) + 1] << 8) | (badBlock[(4 * a) + 2] << 16) | (badBlock[(4 * a) + 3] << 24)))
    for a in range(Count.value):
      print 'Bad Block Address:',  badList[a]
    print 'Scanning flash OK'

#FXTOOL_API int FXT_Flash_SetCompression(int compression, unsigned int Handle)
  def flashSetCompression(self, compression=1):
    print 'Setting compression:', compression, '...'
    if not FxTool.module.FXT_Flash_SetCompression(compression, self.handle):
      raise FxToolError(self)
    print 'Compression set OK'

# FXTOOL_API int FXT_Flash_SetProtocol(unsigned int Protocol, unsigned int Handle)
  def flashSetProtocol(self, protocol):
    print 'Setting flash protocol:', protocol, '...'
    if not FxTool.module.FXT_Flash_SetProtocol(protocol, self.handle):
      raise FxToolError(self)
    print 'Flash protocol set OK'

# FXTOOL_API int FXT_Flash_PatchAddress(unsigned int Address, unsigned int Length, const unsigned char *pData, unsigned int Handle)
  def flashPatch(self, address, data):
    print 'Patching address:', hex(address), 'with', len(data), 'bytes of data ...'
    length = 16#len(data)
    d = (c_ubyte * length)()
    for n in range(0, length):
      d[n] = data[n]
    if not FxTool.module.FXT_Flash_PatchAddress(address, length, d, self.handle):
      raise FxToolError(self)
    print 'Patched OK'

# FXTOOL_API unsigned int FXT_Flash_GetFlashId(unsigned int Handle)
  def getFlashId(self):
    print 'Reading flash ID ...'
    r = FxTool.module.FXT_Flash_GetFlashId(self.handle)
    print 'Flash ID:', hex(r)
    return r

# FXTOOL_API int FXT_Flash_SetExtendedConfig(const FXT_Flash_ExtendedConfig_t *pExtendedFlashConfig, unsigned int Handle)
  def flashSetExtConfig(self, efp, chkerase, verify, noerase):
    print 'Setting extended flash config:', efp, chkerase, verify, noerase, '...'
    config = FlashConfig()
    config.efp = efp
    config.chkerase = chkerase
    config.verify = verify
    config.noerase = noerase
    if not FxTool.module.FXT_Flash_SetExtendedConfig(byref(config), self.handle):
      raise FxToolError(self)
    print 'Extended flash config set OK'

  def getBytesFlashed(self):
    f = c_uint()
    if not FxTool.module.FXT_Stat_GetBytesFlashed(byref(f), self.handle):
      raise FxToolError(self)
    return f.value

  def getBytesFlashedV2(self):
    f = c_ulonglong()
    if not FxTool.module.FXT_Stat_GetBytesFlashedV2(byref(f), self.handle):
      raise FxToolError(self)
    return f.value

  def getFlashStatusAsynch(self):
    f = AsynchFlashStatus()
    if not FxTool.module.FXT_Flash_GetFlashStatus(byref(f), self.handle):
      raise FxToolError(self)
    #print 'flashing status:',f.State,'progress:',f.Progress,'Total:',f.Total
    return (f.State, f.Progress, f.Total)

  def getFlashProgressAsynch(self):
    f = AsynchFlashStatus()
    if not FxTool.module.FXT_Flash_GetFlashProgress(byref(f), self.handle):
      raise FxToolError(self)
    #print 'flashing status:',f.State,'progress:',f.Progress,'Total:',f.Total
    return (f.State, f.Progress, f.Total)

  def getFlashStatistics(self, quiet=None):
    if not quiet:
      print 'Getting flash statistics ...'
    stat = FlashStat()
    if not FxTool.module.FXT_Stat_GetFlashStatistics(byref(stat), self.handle):
      raise FxToolError(self)
    print 'Stat:', stat
    return stat

  def getExtendedFlashStatistics(self, quiet=None):
    if not quiet:
      print 'Getting flash statistics ...'
    stat = FlashExtendedStat()
    if not FxTool.module.FXT_Stat_GetExtendedFlashStatistics(byref(stat), self.handle):
      raise FxToolError(self)
    print 'Stat:', stat
    return stat

  def taGetVersion(self, partition, quiet=None):
    print 'Reading TA version, partition:', partition, '...'
    v = c_ubyte();
    if not FxTool.module.FXT_TA_GetVersion(partition, byref(v), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA version:', v.value
    return v.value

  def taVersionSupport(self, version, quiet=None):
    if not quiet:
      print 'Reading TA version support, version:', version, '...'
    s = c_int()
    if not FxTool.module.FXT_TA_VersionSupported(version, byref(s), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA version supported:', s.value
    return s.value

  def taGetConfig(self, quiet=None):
    if not quiet:
      print 'Getting TA config ...'
    setting = TaSetting()
    if not FxTool.module.FXT_TA_GetConfig(byref(setting), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA config:', setting
    return (setting.address, setting.blkSize, setting.blkNbr)

  def taSetConfig(self, address, blkSize, blkNbr, quiet=None):
    if not quiet:
      print 'Setting TA config ...'
    setting = TaSetting()
    setting.address = address
    setting.blkSize = blkSize
    setting.blkNbr = blkNbr
    if not FxTool.module.FXT_TA_SetConfig(byref(setting), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA config set OK'

  def taStoreConfig(self, quiet=None):
    if not quiet:
      print 'Storing TA config ...'
    if not FxTool.module.FXT_TA_StoreConfig(self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA config stored OK'

  def taOpen(self, partition, quiet=None):
    if not quiet:
      print 'Opening TA partition:', partition, '...'
    self.partition = partition
    if not FxTool.module.FXT_TA_Open(self.partition, self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA opened OK'

# FXTOOL_API int FXT_TA_ForceOpen(unsigned char Partition, const T_TASetting *pTASetting, unsigned int Handle)
  def taForceOpen(self, partition, address, blkSize, blkNbr, quiet=None):
    if not quiet:
      print 'Opening TA partition:', partition, 'at', hex(address), '...'
    self.partition = partition
    setting = TaSetting()
    setting.address = address
    setting.blkSize = blkSize
    setting.blkNbr = blkNbr
    if not FxTool.module.FXT_TA_ForceOpen(self.partition, byref(setting), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA Opened OK'

  def taRead(self, unit, quiet=None):
    if not quiet:
      print 'Reading TA unit:', unit, '...'
    taunit = TaUnit(unit)
    if FxTool.module.FXT_TA_ReadUnit(byref(taunit), self.handle):
      return taunit.list()
    return None

  def taReadWithMasterSize(self, unit,mastersize, quiet=None):
    if not quiet:
      print 'Reading Ta unit:', unit, '...'
    taunit = TaUnit(unit, mastersize)
    if not FxTool.module.FXT_TA_ReadUnit(byref(taunit), self.handle):
      raise FxToolError(self)
    return taunit.list()

  def taWrite(self, unit, data, quiet=None):
    if not quiet:
      print 'Writing TA unit:', unit, '...'
    taunit = TaUnit(unit)
    taunit.size = len(data)
    # copy data to taunit
    for n in range(0, taunit.size):
      if isinstance(data, str):
        taunit.data[n] = ord(data[n])
      else:
        taunit.data[n] = data[n]
    if not FxTool.module.FXT_TA_WriteUnit(byref(taunit), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA write OK'

  def taReadAll(self, filename, quiet=None):
    print 'Reading all TA units to file:', filename, '...'
    if not FxTool.module.FXT_TA_ReadAll(filename, self.handle):
      raise FxToolError(self)
    print 'Reading all TA units OK'

  def taWriteFromFile(self, filename, quiet=None):
    if not quiet:
      print 'Writing TA units from file:', filename, '...'
    f = open(filename, 'rb')
    data = f.read()
    f.close()
    if not FxTool.module.FXT_TA_FileProgram(data, len(data), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Writing all TA units from file OK'

  def taFormat(self, version=0, quiet=None):
    if not quiet:
      print 'Formatting TA, version:', version, '...'
    if not FxTool.module.FXT_TA_FormatWithVersion(version, self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA formatted OK'

  def taClose(self, quiet=None):
    if not quiet:
      print 'Closing TA (' + str(self.partition) + ') ...'
    self.partition = ''
    if not FxTool.module.FXT_TA_Close(self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'TA closed OK'


# FXTOOL_API bool FXT_GDFS_ForceStart(const T_GDFSSetting *pGDFSSetting, unsigned char Target, unsigned int Handle);
# FXTOOL_API bool FXT_GDFS_Start(unsigned char Target, unsigned int Handle);
# FXTOOL_API bool FXT_GDFS_Format(unsigned int Handle);
# FXTOOL_API bool FXT_GDFS_Read(T_GDFSUnitData *pGDFSUnit, unsigned int Handle);
# FXTOOL_API bool FXT_GDFS_Write(const T_GDFSUnitData *pGDFSUnit, unsigned int Handle);
# FXTOOL_API bool FXT_GDFS_ReadAll(const char *Filename, unsigned int Handle);
# FXTOOL_API bool FXT_GDFS_FileProgram(const unsigned char *pGDFData, unsigned int GDFDataSize, unsigned int Handle);

  def gdfsForceStart(self, address, blkSize, units, blkUsed, blkLogl, which = 0):
    print 'Force starting GDFS at', hex(address), 'with block size:', hex(blkSize), 'max units:', str(units), '(blk: ' + str(blkUsed) + ', log: ' + str(blkLogl) + ') ...'
    setting = GdfsSetting()
    setting.address = address
    setting.blkSize = blkSize
    setting.blkUsed = blkUsed
    setting.blkLogl = blkLogl
    setting.blkNbr = units

    if not FxTool.module.FXT_GDFS_ForceStart(which, byref(setting), self.handle):
      raise FxToolError(self)
    print 'GDFS force started OK'

  def gdfsStart(self, which = 0):
    print 'Starting GDFS (' + str(which) + ') ...'
    if not FxTool.module.FXT_GDFS_Start(which, self.handle):
      raise FxToolError(self)
    print 'GDFS started OK'

  def gdfsFormat(self):
    print 'Formatting GDFS ...'
    if not FxTool.module.FXT_GDFS_Format(self.handle):
      raise FxToolError(self)
    print 'GDFS formatted OK'

  def gdfsRead(self, unit, block, quiet=None):
    if not quiet:
      print 'Reading GDFS unit:', unit, block, '...'
    gdfsunit = GdfsUnit(unit, block)
    if not FxTool.module.FXT_GDFS_Read(byref(gdfsunit), self.handle):
      raise FxToolError(self)
    return gdfsunit.list()

  def gdfsReadWithMasterSize(self, unit, block, mastersize, quiet=None):
    if not quiet:
      print 'Reading GDFS unit:', unit, block, '...'
    gdfsunit = GdfsUnit(unit, block, mastersize)
    if not FxTool.module.FXT_GDFS_Read(byref(gdfsunit), self.handle):
      raise FxToolError(self)
    return gdfsunit.list()

  def gdfsWrite(self, unit, block, data, quiet=None):
    if not quiet:
      print 'Writing GDFS unit:', unit, block, '...'
    gdfsunit = GdfsUnit(unit, block)
    gdfsunit.size = len(data)
    # copy data to gdfsunit
    for n in range(0, gdfsunit.size):
      gdfsunit.data[n] = data[n]
    if not FxTool.module.FXT_GDFS_Write(byref(gdfsunit), self.handle):
      raise FxToolError(self)
    print 'GDFS write OK'

  def gdfsReadAll(self, filename):
    print 'Reading all GDFS units to file:', filename, '...'
    if not FxTool.module.FXT_GDFS_ReadAll(filename, self.handle):
      raise FxToolError(self)
    print 'Reading all GDFS units OK'

  def gdfsWriteFromFile(self, filename):
    print 'Writing GDFS from file:', filename, '...'
    f = open(filename, 'rb')
    data = f.read()
    f.close()
    if not FxTool.module.FXT_GDFS_FileProgram(data, len(data), self.handle):
      raise FxToolError(self)
    print 'Writing GDFS units from file OK'

  def hexlist(self, s, level = 'hex'):
    l = []
    if 'hex' in level.lower():
      l.append('hex (' + str(len(s)) + '):')
      for c in s:
        if c < 0:
          c += 256
        l.append(' %02x' % c)
    elif 'uni' in level.lower():
      try:
        us = ''
        zerocnt = 0
        for c in s:
          if c == 0:
            zerocnt += 1
          else:
            us += unichr(c)
            zerocnt = 0
          if zerocnt >= 2:
            break
        l.append('unicode (' + str(len(us)) + '): ')
        l.append(us)
      except (ValueError):
        l.append('WARNING: Not valid unicode.')
    return ''.join(l)


# FXTOOL_API int FXT_FS_StartupRequest(unsigned int Handle)
  def fsSystemStart(self):
    print 'Starting FS system ...'
    if not FxTool.module.FXT_FS_StartupRequest(self.handle):
      raise FxToolError(self)
    print 'FS system started OK'

# FXTOOL_API int FXT_FS_Start(unsigned int Handle);
# FXTOOL_API int FXT_FS_ForceStart(char *pConfigurationData, unsigned int ConfDataLength, unsigned int Handle);
  def fsStart(self):
    print 'Starting FS ...'
    if not FxTool.module.FXT_FS_Start(self.handle):
      raise FxToolError(self)
    print 'FS started OK'

  def fsForceStart(self, config):
    print 'Force starting FS ...'
    l = []
    length = 0
    cl = config.split(';')
    for c in cl:
      il = c.split('=')
      name = il[0]
      value = '='.join(il[1:])
      print 'name', name
      print 'value', value
      l.append(name)
      length += len(name) + 1
      l.append(value)
      length += len(value) + 1
    print 'tot len:', length
    cc = (c_ubyte * length)()
    i = 0
    for s in l:
      for c in s:
        cc[i] = ord(c)
        i += 1
      cc[i] = 0
      i += 1
    print 'i:', i
    if not FxTool.module.FXT_FS_ForceStart(byref(cc), length, self.handle):
      raise FxToolError(self)
    print 'FS force started OK'

# FXTOOL_API int FXT_FS_Pwd(wchar_t *pPath, unsigned int PathSize, unsigned int Handle);
  def fsPwd(self, quiet=None):
    print 'Reading pwd ...'
    p = self.create_u16_buffer('',256)
    if not FxTool.module.FXT_FS_Pwd(byref(p), len(p), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Pwd:', self.u16string(p)
    return self.u16string(p)

# FXTOOL_API int FXT_FS_CopyFile(const wchar_t *pSrcPath, const wchar_t *pDestPath, unsigned int Handle);
  def fsCopyFile(self, src, dest):
    print 'Copying file:', src, 'to:', dest, '...'
    unisrc = self.create_u16_buffer(src);
    unidest = self.create_u16_buffer(dest);
    t1 = time.time()
    if not FxTool.module.FXT_FS_CopyFile(byref(unisrc), byref(unidest), self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    print 'Flashed in', round(td, 2), 's'
    print 'Copy file OK'

# FXTOOL_API int FXT_FS_MoveFile(const wchar_t *pSrcPath, const wchar_t *pDestPath, unsigned int Handle);
  def fsMoveFile(self, src, dest):
    print 'Moving file:', src, 'to:', dest, '...'
    unisrc = self.create_u16_buffer(src);
    unidest = self.create_u16_buffer(dest);
    t1 = time.time()
    if not FxTool.module.FXT_FS_MoveFile(byref(unisrc), byref(unidest), self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    print 'Flashed in', round(td, 2), 's'
    print 'Move file OK'

# FXTOOL_API int FXT_FS_RenameFile(const wchar_t *pOldName, const wchar_t *pNewName, unsigned int Handle);
  def fsRenameFile(self, old, new):
    print 'Renaming file:', old, 'to:', new, '...'
    uniold = self.create_u16_buffer(old);
    uninew = self.create_u16_buffer(new);
    if not FxTool.module.FXT_FS_RenameFile(byref(uniold), byref(uninew), self.handle):
      raise FxToolError(self)
    print 'Renaming file OK'

# FXTOOL_API int FXT_FS_DeleteFile(const wchar_t *pPath, unsigned int Handle);
  def fsDeleteFile(self, path):
    print 'Deleting file:', path, '...'
    unipath = self.create_u16_buffer(path);
    t1 = time.time()
    if not FxTool.module.FXT_FS_DeleteFile(byref(unipath), self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    print 'Flashed in', round(td, 2), 's'
    print 'Deleting file OK'

# FXTOOL_API int FXT_FS_Chmod(const wchar_t *pPath, int Mode, unsigned int Handle);
  def fsChMod(self, path, mode):
    print 'Changing mode on:', path, 'to', oct(mode)
    unipath = self.create_u16_buffer(path);
    if not FxTool.module.FXT_FS_Chmod(byref(unipath), mode, self.handle):
      raise FxToolError(self)

# FXTOOL_API int FXT_FS_Stat(T_Stat *pStat, const wchar_t *pPath, unsigned int Handle);
  def fsGetFileSize(self, path, quiet=None):
    if not quiet:
      print 'Reading file size for:', path, '...'
    unipath = self.create_u16_buffer(path)
    stat = FsStat()
    if not FxTool.module.FXT_FS_Stat(byref(stat), byref(unipath), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'File size:', stat.size
    return stat.size

# FXTOOL_API int FXT_FS_MkDir(const wchar_t *pPath, int Mode, unsigned int Handle);
  def fsMkDir(self, path):
    print 'Making dir:', path
    unipath = self.create_u16_buffer(path);
    if not FxTool.module.FXT_FS_MkDir(byref(unipath), 0x1FF, self.handle):
      raise FxToolError(self)
      'Making dir OK'

# FXTOOL_API int FXT_FS_ChDir(const wchar_t *pPath, unsigned int Handle);
  def fsChDir(self, path):
    print 'Changing dir to:', path, '...'
    unipath = self.create_u16_buffer(path);
    if not FxTool.module.FXT_FS_ChDir(byref(unipath), self.handle):
      raise FxToolError(self)
    print 'Changed dir OK'

# FXTOOL_API int FXT_FS_RmDir(const wchar_t *pPath, unsigned int Handle);
  def fsRmDir(self, path):
    print 'Deleting dir:', path, '...'
    unipath = self.create_u16_buffer(path);
    if not FxTool.module.FXT_FS_RmDir(byref(unipath), self.handle):
      raise FxToolError(self)
    print 'Deleting dir OK'

# FXTOOL_API int FXT_FS_ListFiles(wchar_t **ppFileList, unsigned int Handle);
# FXTOOL_API int FXT_FS_GetFileList(FXT_FS_ListEntry_t *pFileList, unsigned int *pSize, unsigned int Handle)
  def fsGetFileList(self, quiet=None):
    if not quiet:
      print 'Reading file list ...'
    s = c_uint(128)
    l = (FsListEntry * s.value)()
    for i in l:
      i.__init__()

    if not FxTool.module.FXT_FS_GetFileList(byref(l), byref(s), self.handle):
      raise FxToolError(self)

    rl = []
    if not quiet:
      print 'File list, cnt:', s.value
    for i in range(s.value):
      if not quiet:
        print 'file:', l[i]
      rl.append(l[i].nameStr())
    return rl

#FXTOOL_API int FXT_FS_GetMemoryStickInfo(unsigned char* pMemoryStickInfo, unsigned int Handle)
  def GetMemoryStickInfo(self, quiet=None):
    if not quiet:
      print 'Reading the memoryStick ...'
    size = create_string_buffer(9)
    info = create_string_buffer(512)
    infoSize = c_uint(512)

    if not FxTool.module.FXT_FS_GetMemoryStickInfo(byref(size), byref(info), byref(infoSize), self.handle):
      raise FxToolError(self)

    if not quiet:
      print 'size:', size.value
      print 'info:', info.value
    return info.value

# FXTOOL_API int FXT_FS_ListSubdirs(wchar_t **ppDirList, unsigned int Handle);
# FXTOOL_API int FXT_FS_GetDirList(FXT_FS_ListEntry_t *pDirList, unsigned int *pSize, unsigned int Handle);
  def fsGetDirList(self, quiet=None):
    if not quiet:
      print 'Reading dir list ...'
    s = c_uint(128)
    l = (FsListEntry * s.value)()
    for i in l:
      i.__init__()

    if not FxTool.module.FXT_FS_GetDirList(byref(l), byref(s), self.handle):
      raise FxToolError(self)

    rl = []
    if not quiet:
      print 'Dir list, cnt:', s.value
    for i in range(s.value):
      if not quiet:
        print 'dir:', l[i]
      rl.append(l[i].nameStr())
    return rl


# FXTOOL_API int FXT_FS_ListVolumes(wchar_t **ppList, unsigned int Handle);
# FXTOOL_API int FXT_FS_GetVolumeList(FXT_FS_ListEntry_t *pVolumeList, unsigned int *pSize, unsigned int Handle);
  def fsGetVolumeList(self, quiet=None):
    if not quiet:
      print 'Reading volume list ...'
    s = c_uint(128)
    l = (FsListEntry * s.value)()
    for i in l:
      i.__init__()

    if not FxTool.module.FXT_FS_GetVolumeList(byref(l), byref(s), self.handle):
      raise FxToolError(self)

    rl = []
    if not quiet:
      print 'Volume list, cnt:', s.value
    for i in range(s.value):
      if not quiet:
        print 'vol:', l[i]
      rl.append(l[i].nameStr())
    return rl

#FXT_FS_GetPartitionInfo(FXT_FS_PartitionInfo_t *pPartitionInfo, unsigned int PartitionInfoLength, unsigned short *pPartitionInfoVersion, unsigned short *pnPartitions, unsigned char MID, unsigned int Handle)
  def fsGetPartitionsInfoData(self, mid, quiet=None):
    if not quiet:
      print 'Getting Partition Info ...'
    s = c_uint(256)
    #parInfoVer = c_uint(1)
    #nrPar = c_uint(1)
    l = (FsPartitionInfo * s.value)()
    for i in l:
      i.__init__()

    if not FxTool.module.FXT_FS_GetPartitionInfoData(byref(l), byref(s), mid, self.handle):
      raise FxToolError(self)

    #for a in range(nrPar.value):
    #  print 'partition:',  l[a]

    print 'Getting Partition Info :Done'

  def fsGetPartitionsInfo(self, mid, version, quiet=None):
    if not quiet:
      print 'Getting Partition Info ...'

    buf_size = c_int(0x4000)
    buf = (c_ubyte * buf_size.value)()
    if not FxTool.module.FXT_FS_GetPartitionInfoData(byref(buf), byref(buf_size), mid, self.handle):
      raise FxToolError(self)

    parInfoVer = (((((buf[3] << 8) + buf[2]) << 8) + buf[1]) << 8) + buf[0]
    nrPar = (((((buf[7] << 8) + buf[6]) << 8) + buf[5]) << 8) + buf[4]
    if not quiet:
      print 'Got version:', parInfoVer
      print 'Number of partitions:', nrPar

    if parInfoVer == 5:
      l = (FsPartitionInfoV5 * nrPar)()
    elif parInfoVer == 6:
      l = (FsPartitionInfoV6 * nrPar)()
    else:
      raise FxToolError(self)

    if version != parInfoVer:
      print 'Got partition data version', parInfoVer, 'but expected version', version
      raise FxToolError(self)

    offs = 8
    for i in l:
      i.__init__(buf[offs:])
      if parInfoVer == 5:
        offs = offs + 128
      elif parInfoVer == 6:
        offs = offs + 88
      else:
        raise FxToolError(self)

    parts = []

    for a in range(nrPar):
      parts.append(l[a])
      if not quiet:
        print 'partition:',  l[a]

    if not quiet:
      print 'Getting Partition Info :Done'

    return parts

  def fsGetPartitionsInfoV5(self, mid, quiet=None):
    if not quiet:
      print 'Getting Partition Info ...'
    s = c_uint(4096)
    parInfoVer = c_uint(1)
    nrPar = c_uint(1)
    l = (FsPartitionInfoV5 * s.value)()
    for i in l:
      i.__init__()

    if not FxTool.module.FXT_FS_GetPartitionInfoV3(byref(l), s, byref(parInfoVer), byref(nrPar), mid, self.handle):
      raise FxToolError(self)

    if not quiet:
      print 'Partition info version:',  parInfoVer.value

    if not quiet:
      for a in range(nrPar.value):
        print 'partition:',  l[a]

    if not quiet:
      print 'Getting Partition Info :Done'

    return parts

  def fsGetPartitionsInfoV6(self, mid, quiet=None):
    if not quiet:
      print 'Getting Partition Info ...'
    s = c_uint(4096)
    parInfoVer = c_uint(1)
    nrPar = c_uint(1)
    l = (FsPartitionInfoV6 * s.value)()
    for i in l:
      i.__init__()

    if not FxTool.module.FXT_FS_GetPartitionInfoV3(byref(l), s, byref(parInfoVer), byref(nrPar), mid, self.handle):
      raise FxToolError(self)

    if not quiet:
      print 'Partition info version:',  parInfoVer.value

    parts = []
    for a in range(nrPar.value):
      parts.append(l[a])
      if not quiet:
        print 'partition:',  l[a]

    if not quiet:
      print 'Getting Partition Info :Done'

    return parts

  def fsGetPartitionsInfoData(self, mid, quiet=None):
    if not quiet:
      print 'Getting Partition Info Data...'

    datasize = c_uint(256)
    l = (c_uint * datasize.value)()

    if not FxTool.module.FXT_FS_GetPartitionInfoData(byref(l), byref(datasize), mid, self.handle):
      raise FxToolError(self)

    print 'Getting Partition Info Data :Done'

#FXT_FS_MountVolume(char* pPath, unsigned int Handle)
  def fsMountVolume(self, path):
    print 'Mounting volume at:', path, '...'
    pathString = create_string_buffer(path)
    if not FxTool.module.FXT_FS_MountVolume(byref(pathString), self.handle):
      raise FxToolError(self)
    print 'Mount volume OK'

#FXT_FS_UnMountVolume(char* pPath, unsigned int Handle)
  def fsUnMountVolume(self, path):
    print 'UnMounting volume at:', path, '...'
    pathString = create_string_buffer(path)
    if not FxTool.module.FXT_FS_UnMountVolume(byref(pathString), self.handle):
      raise FxToolError(self)
    print 'UnMount volume OK'

# FXTOOL_API int FXT_FS_PutFile(const wchar_t *pPath, int Mode, const char *data, unsigned int size, unsigned int Handle);
  def fsPutFile(self, source, dest):
    print 'Putting file:', source, 'at:', dest, '...'
    f = open(source, 'rb')
    data = f.read()
    f.close()
    l = len(data)
    unipath = self.create_u16_buffer(dest)
    t1 = time.time()
    if not FxTool.module.FXT_FS_PutFile(byref(unipath), 0x1FF, data, l, self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    s = 0
    if td:
      s = l * 8 / td / 1024
    print 'Actual bytes flashed:', self.getBytesFlashed()
    print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    print 'File put OK'

  def fsPutZeroFile(self, name, dest):
    print 'Putting file of zero size:', name, 'at:', dest, '...'
    unipath = self.create_u16_buffer(dest)
    if not FxTool.module.FXT_FS_PutFile(byref(unipath), 0x1FF, None, 0, self.handle):
      raise FxToolError(self)
    print 'File put OK'

# FXTOOL_API int FXT_FS_GetFile(const wchar_t *pPath, char *data, unsigned int *size, unsigned int Handle);
  def fsGetFile(self, source, dest):
    print 'Getting file:', source, 'to:', dest, '...'
    unipath = self.create_u16_buffer(source)
    stat = FsStat()
    if not FxTool.module.FXT_FS_Stat(byref(stat), byref(unipath), self.handle):
      raise FxToolError(self)
    data = create_string_buffer(stat.size)
    length = c_uint(stat.size)
    t1 = time.time()
    if not FxTool.module.FXT_FS_GetFile(byref(unipath), byref(data), byref(length), self.handle):
      raise FxToolError(self)
    td = time.time() - t1
    print 'Flashed in', round(td, 2), 's'
    if length.value != stat.size:
      print ' stat.size:', stat.size
      print ' length:', length
      raise FxToolError('stat size not equal to file size')
    f = open(dest, 'wb')
    if stat.size > 0:
      f.write(data)
    f.close()
    print 'Get file OK'

# FXTOOL_API int FXT_FS_GetFile(const wchar_t *pPath, char *data, unsigned int *size, unsigned int Handle);
  def fsGetFileWithSize(self, source, dest,size):
    print 'Getting file:', source, 'to:', dest, '...'
    unipath = self.create_u16_buffer(source)
    data = create_string_buffer(size)
    length = c_uint(size)
    if not FxTool.module.FXT_FS_GetFile(byref(unipath), byref(data), byref(length), self.handle):
      raise FxToolError(self)
    f = open(dest, 'wb')
    f.write(data)
    f.close()
    print 'Get file OK'

# FXTOOL_API int FXT_FS_FormatVolume(const wchar_t *pPath, unsigned int Handle);
  def fsFormatVolume(self, path):
    print 'Formatting volume at:', path, '...'
    unipath = self.create_u16_buffer(path)
    if not FxTool.module.FXT_FS_FormatVolume(byref(unipath), self.handle):
      raise FxToolError(self)
    print 'Format volume OK'

# FXTOOL_API int FXT_FS_GetFreeSpace(const wchar_t *pPath, unsigned int *pFreeSpace, unsigned int Handle);
  def fsGetFreeSpace(self, path, quiet=None):
    if not quiet:
      print 'Reading free space for path:', path, '...'
    unipath = self.create_u16_buffer(path)
    f = c_uint()
    if not FxTool.module.FXT_FS_GetFreeSpace(byref(unipath), byref(f), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Free space:', f.value
    return f.value

  def fsGetBlockSize(self, path, quiet=None):
    if not quiet:
      print 'Reading block size for path:', path, '...'
    unipath = self.create_u16_buffer(path)
    f = c_uint()
    if not FxTool.module.FXT_FS_GetBlockSize(byref(unipath), byref(f), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Block size:', f.value
    return f.value

# FXTOOL_API int FXT_FS_LoadAndVerifySFAArchive(const unsigned char* pSFAArchive, unsigned int SFAArchiveSize, unsigned int Handle);
  def fsWriteSfa(self, filename):
    print 'Preparing SFA file ...'
    f = open(filename, 'rb')
    data = f.read()
    f.close()
    l = len(data)
    print 'Starting SFA flash sequence ...'
    if not FxTool.module.FXT_FS_LoadAndVerifySFAArchive(data, l, self.handle):
      raise FxToolError(self)
    print 'SFA flashed OK'

#
  def getLastError(self, gen = None):
    e = create_string_buffer(128)
    handle = self.handle
    if gen:
      handle = 0
    if FxTool.module.FXT_Stat_ReadErrorMessage(byref(e), len(e), handle):
      return e.value
    return None

#
  def getLastErrorCode(self, gen = None):
    e = c_int()
    handle = self.handle
    if gen:
      handle = 0
    FxTool.module.FXT_Stat_ReadErrorCode(byref(e), handle)
    return e.value

# FXTOOL_API int FXT_Stat_ReadResponseStatus(unsigned short* pStatus, unsigned int Handle)
  def getResponseStatusCode(self):
    i = c_ushort()
    FxTool.module.FXT_Stat_ReadResponseStatus(byref(i), self.handle)
    return i.value

# FXTOOL_API int FXT_Stat_ReadResponseStatusMessage(char *pMessage, int MessageSize, unsigned int Handle)
  def getResponseStatus(self):
    e = create_string_buffer(1024)
    if FxTool.module.FXT_Stat_ReadResponseStatusMessage(byref(e), len(e), self.handle):
      return e.value
    return None

# FXTOOL_API int FXT_Stat_ReadErrorMessageFromSECS(char *pMessage, int MessageSize, unsigned int Handle)
  def getLastSecsError(self):
    e = create_string_buffer(1024)
    if FxTool.module.FXT_Stat_ReadErrorMessageFromSECS(byref(e), len(e), self.handle):
      return e.value
    print e.value
    return None

  def getLastEvent(self):
    e = create_string_buffer(512)
    if FxTool.module.FXT_Stat_ReadLastEventMessage(byref(e), len(e), self.handle):
      return e.value
    return None

  def getImei(self, quiet = None):
    print 'Reading IMEI ...'
    otpdata = OtpData()
    if not FxTool.module.FXT_Sign_ReadFromOTP(byref(otpdata), self.handle):
      raise FxToolError(self) #('No IMEI')
    if not quiet:
      print 'IMEI:', otpdata.imei
    return otpdata.imei

  def getCid(self, quiet = None):
    print 'Reading CID ...'
    otpdata = OtpData()
    if not FxTool.module.FXT_Sign_ReadFromOTP(byref(otpdata), self.handle):
      raise FxToolError(self) #('No CID')
    if not quiet:
      print 'CID:', otpdata.cid
    return otpdata.cid

# FXTOOL_API int FXT_Sign_ReadDomain(FXT_Sign_ProductDomain_t* pDomain, unsigned int Handle);
  def getDomain(self, quiet = None):
    print 'Reading Domain ...'
    d = c_int()
    if not FxTool.module.FXT_Sign_ReadDomain(byref(d), self.handle):
      raise FxToolError(self) #('No Domain')
    if not quiet:
      print 'Domain:', hex(d.value)
    return d.value

# FXTOOL_API int FXT_Sign_WriteDomain(FXT_Sign_ProductDomain_t Domain, unsigned int Handle);
  def setDomain(self, domain):
    print 'Writing Domain', hex(domain), '...'
    if not FxTool.module.FXT_Sign_WriteDomain(domain, self.handle):
      raise FxToolError(self)
    print 'Domain written OK'

# FXTOOL_API int FXT_Sign_ReadHsdpaState(unsigned int *pState, unsigned int Handle);
  def getHsdpaState(self, quiet = None):
    print 'Reading HSDPA state ...'
    d = c_uint()
    if not FxTool.module.FXT_Sign_ReadHsdpaState(byref(d), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'HSDPA state:', hex(d.value)
    return d.value

# FXTOOL_API int FXT_Sign_WriteHsdpaState(unsigned int State, unsigned int Handle);
  def setHsdpaState(self, state):
    print 'Writing HSDPA state', hex(state)
    if not FxTool.module.FXT_Sign_WriteHsdpaState(state, self.handle):
      raise FxToolError(self)
    print 'HSDPA state written OK'

# FXTOOL_API int FXT_Sign_ReadWcdmaState(unsigned int *pState, unsigned int Handle);
  def getWcdmaState(self, quiet = None):
    print 'Reading WCDMA state ...'
    d = c_uint()
    if not FxTool.module.FXT_Sign_ReadWcdmaState(byref(d), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'WCDMA state:', hex(d.value)
    return d.value

# FXTOOL_API int FXT_Sign_WriteWcdmaState(unsigned int State, unsigned int Handle);
  def setWcdmaState(self, state):
    print 'Writing WCDMA state', hex(state)
    if not FxTool.module.FXT_Sign_WriteWcdmaState(state, self.handle):
      raise FxToolError(self)
    print 'WCDMA state written OK'

# FXTOOL_API int FXT_Sign_ReadFromOTP(T_OTPData* pOTPData, unsigned int Handle)
  def getOtp(self, quiet=None):
    if not quiet:
      print 'Reading OTP ...'
    otpdata = OtpData()
    otpdata.status = 0xccdd
    if not FxTool.module.FXT_Sign_ReadFromOTP(byref(otpdata), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'OTP:', otpdata
#   status locked cid paf imei chnble
    return (otpdata.status, otpdata.locked, otpdata.cid, otpdata.paf, otpdata.imei)
#typedef struct FXT_Sign_OTPData_DB3350_t
#{
#  unsigned char Status; // OTP read status, 0 = success, 1 = fail
#  unsigned char Locked; // boolean 0/1
#  unsigned short CID; // 2 bytes
#  unsigned char PAF; // boolean 0/1
#  char IMEI[14]; // IMEI 14 bytes binary array
#  unsigned char IMEIChangeable; // boolean 0/1
#  unsigned short RootKey; //1 byte
#  Unsigned short SecurityConfiguration; //1 byte
#  char CustomerOTP[21]; Customer OTP 21 bytes array
#} FXT_Sign_OTPData_DB3350_t;

#FXTOOL_API int FXT_Sign_ReadFrom_3350_OTP(FXT_Sign_OTPData_DB3350_t* pOTPData, unsigned int Handle)
  def getOtp3350(self, quiet=None):
    if not quiet:
      print 'Reading OTP ...'
    otpdata = OtpDataDB3350()
    otpdata.status = 0xccdd
    if not FxTool.module.FXT_Sign_ReadFrom_DB3350_OTP(byref(otpdata), self.handle):
      raise FxToolError(self)
    if not quiet:
      #print 'OTP:', otpdata
      print 'STATUS:', otpdata.status
      print 'LOCKED:', otpdata.locked
      print 'CID:', otpdata.cid
      print 'PAF:', otpdata.paf
      print 'IMEI:', self.hexlist(otpdata.imei, 'uni')
      print 'IMEI changeable:', otpdata.changeable
      print 'ROOTKEY:', otpdata.rootKey
      print 'SecurityConfiguration:', otpdata.securityConfig
      print 'Customer OTP:', self.hexlist(otpdata.customerOTP, 'uni')
#   status locked cid paf imei chnble
    return (otpdata.status, otpdata.locked, otpdata.cid, otpdata.paf, otpdata.imei)

# FXTOOL_API int FXT_Sign_WriteToOTP(const FXT_Sign_OTPData_t* pOTPData, unsigned int Handle)
  def writeOtp(self, quiet=None):
    if not quiet:
      print 'Writing OTP ...'
    raise FxToolError('not implemented in py')
    if not quiet:
      print 'Writing OTP OK'

#FXTOOL_API int FXT_Sign_WriteTo_3350_OTP(const FXT_Sign_OTPData_DB3350_t* pOTPData, unsigned int Handle)
  def write3350Otp(self,cid):
    otpdata = OtpDataDB3350()
    otpdata.status = 0xccdd
    otpdata.cid = cid
    otpdata.rootKey = 0x00
    otpdata.paf = 0x00
    otpdata.changeable = 0x00
    otpdata.securityConfig = 0x00

    otpdata.imei[0] = 0
    otpdata.imei[1] = 0
    otpdata.imei[2] = 4
    otpdata.imei[3] = 6
    otpdata.imei[4] = 0
    otpdata.imei[5] = 1
    otpdata.imei[6] = 0
    otpdata.imei[7] = 2
    otpdata.imei[8] = 2
    otpdata.imei[9] = 8
    otpdata.imei[10] = 7
    otpdata.imei[11] = 0
    otpdata.imei[12] = 5
    otpdata.imei[13] = 9

    otpdata.customerOTP[0] = 0
    otpdata.customerOTP[1] = 0
    otpdata.customerOTP[2] = 0
    otpdata.customerOTP[3] = 0
    otpdata.customerOTP[4] = 0
    otpdata.customerOTP[5] = 0
    otpdata.customerOTP[6] = 0
    otpdata.customerOTP[7] = 0
    otpdata.customerOTP[8] = 0
    otpdata.customerOTP[9] = 0
    otpdata.customerOTP[10] = 0
    otpdata.customerOTP[11] = 0
    otpdata.customerOTP[12] = 0
    otpdata.customerOTP[13] = 0
    otpdata.customerOTP[14] = 0
    otpdata.customerOTP[15] = 0
    otpdata.customerOTP[16] = 0
    otpdata.customerOTP[17] = 0
    otpdata.customerOTP[18] = 0
    otpdata.customerOTP[19] = 0
    otpdata.customerOTP[20] = 0

    if not FxTool.module.FXT_Sign_WriteTo_DB3350_OTP(byref(otpdata), self.handle):
      raise FxToolError(self)
    print 'Writing OTP OK'

# FXTOOL_API int FXT_Sign_DumpOTP(unsigned char* pData, unsigned int *pDataLength, unsigned int Handle)
  def getOtpDump(self):
    print 'Dump OTP ...'
    l = c_int(2048)
    d = (c_ubyte * l.value)()

    if not FxTool.module.FXT_Sign_DumpOTP(byref(d), byref(l), self.handle):
      raise FxToolError(self)

    rl = []
    if (l):
      for n in range(l.value):
        rl.append(d[n])

    print 'Result, length:', l.value
    print 'Result, data:', self.hexlist(rl, 'hex')
    print 'Dump OTP OK'
    return rl

#FXT_Sign_GetLithiumOTPRegistersBySECS(int ProdMode, unsigned char *pOutOtpData, unsigned int Handle)
  def getLithiumOtpRegister(self, mode):
    print 'Getting OTP register...'
    od = (c_ubyte*64)()
    if not FxTool.module.FXT_Sign_GetLithiumOTPRegistersBySECS(mode, byref(od), self.handle):
      raise FxToolError(self)

    l = []
    for n in range(64):
      l.append(od[n])
    print 'Reading OTP Register OK'
    return l

  def getLithiumOtpRegisterToFile(self, mode, chipid, otpFile):
    print 'Getting OTP register...'
    od = (c_ubyte*64)()
    c_lst = []
    for i in range(0, len(chipid), 2):
      c_lst.append(int('0x'+chipid[i:i+2], 16))
    assert len(c_lst) == 8

    c = (c_ubyte * 8)()
    for i in range(len(c_lst)):
      c[i] = c_lst[i]

    if not FxTool.module.FXT_Sign_GetLithiumOTPRegistersBySECS(mode, byref(c), 8, byref(od), self.handle):
      raise FxToolError(self)

    print 'Saving OTP data to file:', otpFile
    f = open(otpFile, 'wb')
    for n in range(0, 64):
      f.write(struct.pack('B', od[n]))
    f.close()
    print 'Reading OTP Register OK'


# FXTOOL_API int FXT_Loader_GetChipID(UINT64 *pChipID, unsigned int Handle)
  def getChipId(self, quiet = None):
    if not quiet:
      print 'Reading ChipID ...'
    i = c_ulonglong()
    if not FxTool.module.FXT_Loader_GetChipID(byref(i), self.handle):
      raise FxToolError(self) # 'No chip ID'
    if not quiet:
      print 'Chip ID:', hex(i.value)
    return i.value

# FXTOOL_API int FXT_Sign_GetFlashSignature(unsigned char *pSignatureData, unsigned int *pSignatureLength, unsigned int Handle)
  def getFlashSignature(self):
    print 'Reading flash signature ...'
    length = c_int(32)
    v = (c_ubyte * length.value)()
    if not FxTool.module.FXT_Sign_GetFlashSignature(byref(v), byref(length), self.handle):
      raise FxToolError(self)
    l = []
    if (length.value > 0):
      for n in range(length.value):
        l.append(v[n])
    print 'Reading flash signature OK'
    return l

# FXTOOL_API int FXT_Auth_SetSECSChipId(const unsigned char* pChipId, unsigned int ChipIdLength, unsigned int Handle);
  def setupSecs(self, url, chipid = None, quiet = None):
    if not quiet:
      print 'Setting up SECS:', url,
      if chipid:
        print '(chipId:', chipid + ')'
      else:
        print

    r = FxTool.module.FXT_Auth_SetSECSServerUrl(url, self.handle)
    if r and chipid:
      c_lst = []
      for i in range(0, len(chipid), 2):
        c_lst.append(int('0x'+chipid[i:i+2], 16))
      assert len(c_lst) == 8

      c = (c_ubyte * 8)()
      for i in range(len(c_lst)):
        c[i] = c_lst[i]

      r = FxTool.module.FXT_Auth_SetSECSChipId(byref(c), 8, self.handle)
    if not r:
      raise FxToolError(self)

  def setSecsServerProxy(self, proxy):
    print 'Setting up SECS proxy:', proxy,
    r = FxTool.module.FXT_Auth_SetSECSServerProxy(proxy, self.handle)
    if not r:
      raise FxToolError(self)

  def SetSECSServerUpgradeMode(self,UpgradeMode):
    print 'setting SECS server test mode', UpgradeMode,
    r = FxTool.module.FXT_Auth_SetSECSServerUpgradeMode(UpgradeMode, self.handle)
    if not r:
      raise FxToolError(self)

#FXTOOL_API int FXT_AUTH_GetAuthenticationMethods(unsigned char* pAuthMethod, unsigned int *pAuthMethodSize, unsigned int Handle);
  def getAuthenticationMethods(self):
    print 'Getting supported authentication methods...'
    v = create_string_buffer(1024)
    vLength = signature_length = c_int(1024)
    if not FxTool.module.FXT_AUTH_GetAuthenticationMethods(byref(v), byref(vLength), self.handle):
      raise FxToolError(self)
    print 'Supported methods:', v.value
    return v.value

# FXTOOL_API int FXT_Auth_Init(T_AuthenticationProtocol Protocol, unsigned int Handle)
  def authInit(self, protocol):
    prot = 0
    if 'p22' in protocol.lower():
      prot = 1
    elif 'p96' in protocol.lower():
      prot = 2
    return FxTool.module.FXT_Auth_Init(protocol, self.handle)

#FXT_Auth_AuthenticateWithResponseAndLevelBySECS(FXT_Auth_Protocol_t Protocol, FXT_Auth_Level_t Level, unsigned int Handle)
  def authInitWithLevel(self, protocol, level):
    prot = 0
    if 'p22' in protocol.lower():
      prot = 1
    elif 'p96' in protocol.lower():
      prot = 2
    return FxTool.module.FXT_Auth_Init(protocol, level, self.handle)

# FXTOOL_API int FXT_Auth_Authenticate(T_AuthenticationProtocol Protocol, const char* pKID, const char* pServerUrl, unsigned int Handle);
  def authenticate(self, protocol, quiet = None, kid = None, imei = None, server = None):
    if not quiet:
      print 'Authenticating ...'
    prot = 0
    if 'p22' in protocol.lower():
      prot = 1
    elif 'p96' in protocol.lower():
      prot = 2
    elif 'sake' in protocol.lower():
      prot = 3
    r = False
    if kid:
      r = FxTool.module.FXT_Auth_AuthenticateBySECS(prot, kid, imei, server, self.handle)
    else:
      r = FxTool.module.FXT_Auth_AuthenticateWithResponseBySECS(prot, self.handle)
    if not r:
      raise FxToolError(self)
    if not quiet:
      print 'Authentication OK'

# FXTOOL_API int FXT_Auth_Authenticate(T_AuthenticationProtocol Protocol, const char* pKID, const char* pServerUrl, unsigned int Handle);
  def authenticateWithLevel(self, protocol, level = None):
    print 'Authenticating ...'
    prot = 0
    if 'p22' in protocol.lower():
      prot = 1
    elif 'p96' in protocol.lower():
      prot = 2
    elif 'sake' in protocol.lower():
      prot = 3
    r = FxTool.module.FXT_Auth_AuthenticateWithResponseAndLevelBySECS(prot, level, self.handle)
    if not r:
      raise FxToolError(self)
    print 'Authentication OK'

# FXTOOL_API int FXT_Sign_ReadCertificateStatus(T_CertificateData* pCertData, unsigned int Handle);
  def getCertStatus(self, quiet=None):
    if not quiet:
      print 'Reading Cert status ...'
    certdata = CertData()
    if not FxTool.module.FXT_Sign_ReadCertificateStatus(byref(certdata), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Cert status:', certdata
    return (certdata.type, certdata.version, certdata.cid)

  def extractSimlockFile(self, src, dest):
    return FxTool.module.ExtractSimlockDataFromCustom(src, dest, None, None, self.handle)

# FXTOOL_API int FXT_Sign_ResetPhoneLock(unsigned int Handle)
  def resetPhoneLock(self):
    print 'Resetting phone lock ...'
    if not FxTool.module.FXT_Sign_ResetPhoneLock(self.handle):
      raise FxToolError(self)
    print 'Reset phone lock OK'

# FXTOOL_API int FXT_Sign_EraseSecurityData(unsigned int Handle)
  def eraseSecurityData(self):
    print 'Erasing security data ...'
    if not FxTool.module.FXT_Sign_EraseSecurityData(self.handle):
      raise FxToolError(self)
    print 'Erase security data OK'

# FXTOOL_API int FXT_Sign_WriteDefaultData(unsigned char* pGDFData, unsigned int GDFDataSize, unsigned int Handle)
  def writeDefaultData(self, filename):
    print 'Writing default data from file:', filename, '...'
    f = open(filename, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    if not FxTool.module.FXT_Sign_WriteDefaultData(image, l, self.handle):
      raise FxToolError(self)
    print 'Written default data OK'

# FXTOOL_API int FXT_Sign_WriteControlKeys(const FXT_Sign_ControlKey_t* pControlKeys, unsigned int Handle)
  def writeSimlockKeyCodes(self, value):
    print 'Writing SIM lock key codes, containing all:', value, '...'
    codes = (c_ubyte * (12 * 16))()
    for n in range(12*16):
      codes[n] = ord(value)
    if not FxTool.module.FXT_Sign_WriteControlKeys(byref(codes), self.handle):
      raise FxToolError(self)
    print 'Written SIM lock key codes OK'

# FXTOOL_API int FXT_Sign_WriteTestCID(unsigned short CID, unsigned int Handle)
  def writeTestCid(self, cid):
    print 'Writing test CID:', cid, '...'
    if not FxTool.module.FXT_Sign_WriteTestCID(cid, self.handle):
      raise FxToolError(self)
    print 'Test CID written OK'

# FXTOOL_API int FXT_Sign_WriteSimLockDummyData(unsigned int Handle)
  def writeSimlockDummyData(self):
    print 'Writing SIM lock dummy data ...'
    if not FxTool.module.FXT_Sign_WriteSimLockDummyData(self.handle):
      raise FxToolError(self)
    print 'Written SIM lock dummy data OK'

# FXTOOL_API int FXT_Sign_WriteTestSignature(unsigned int Handle)
  def writeTestSignature(self):
    print 'Writing test signature ...'
    if not FxTool.module.FXT_Sign_WriteTestSignature(self.handle):
      raise FxToolError(self)
    print 'Written test signature OK'

# FXTOOL_API int FXT_Calculate_Dynamic_Signature(unsigned int Handle)
  def calculateDynamicSignature(self):
    if not FxTool.module.FXT_Sign_CalculateDynamicSignature(self.handle):
      raise FxToolError(self)
    print 'Calculating dynamic signature OK'

# FXTOOL_API int FXT_Sign_WriteFullSignature(unsigned int Handle);
  def writeFullSignature(self):
    print 'Writing full signature ...'
    if not FxTool.module.FXT_Sign_WriteFullSignature(self.handle):
      raise FxToolError(self)
    print 'Written full signature OK'

# FXTOOL_API int FXT_Sign_UpdateCertificate(const unsigned char* pCertificateImage, unsigned int CertificateSize, unsigned int Handle)
  def writeCertificate(self, filename):
    print 'Writing new cert from file:', filename
    f = open(filename, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    if not FxTool.module.FXT_Sign_UpdateCertificate(image, l, self.handle):
      raise FxToolError(self)
    print 'New certificate written OK'

# FXTOOL_API int FXT_Sign_GetVersion(char *pVersion, unsigned int VersionBufferLength, unsigned int Handle)
  def getVersionsFromSecs(self, quiet = None):
    if not quiet:
      print 'System info ...'
    v = create_string_buffer(1024)
    if not FxTool.module.FXT_Sign_GetVersionsFromSECS(byref(v), len(v), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'System info:', v.value
    return v.value

  def getVersionsFromSecsClient(self, quiet = None):
    if not quiet:
      print 'System info ...'
    v = create_string_buffer(1024)
    if not FxTool.module.FXT_Sign_GetVersionsFromSECSClient(byref(v), len(v)):
      raise FxToolError(self)
    #if not quiet:
      #print 'System info:', v.value
    #return v.value

# FXTOOL_API int FXT_Sign_SetSecurityProperties(const unsigned char *pSecData, unsigned int SecDataLength, unsigned int Handle);
  def setSecurityProperties(self, filename, quiet = None):
    if not quiet:
      print 'Writing OTP from file:', filename
    f = open(filename, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    if not FxTool.module.FXT_Sign_SetSecurityProperties(image, l, self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Written OTP OK'

  def setSecurityPropertiesFromData(self, data):
    print 'Writing OTP from data'
    l = len(data)
    if not FxTool.module.FXT_Sign_SetSecurityProperties(data, l, self.handle):
      raise FxToolError(self)
    print 'Written OTP OK'

#FXTOOL_API int FXT_Sign_GetSignedLockResetBySECS(const char* pIMEIStr, const char* pCertName, unsigned char* pResBuf, unsigned int* pResLen, unsigned int Handle);
  def signedLockReset(self, imei, certname):
    print 'Getting Signed Lock Reset from SECS ...'
    res_len = c_int(4096)
    res = (c_ubyte * res_len.value)()
    if not FxTool.module.FXT_Sign_GetSignedLockResetBySECS(imei, certname, byref(res), byref(res_len), self.handle):
      raise FxToolError(self)
    print 'Lock Reset data:'
    for n in range(res_len.value):
      print('%02x' % res[n]),
    print ''


#FXTOOL_API int FXT_Sign_Locking(const char *parameters, const unsigned char* binDataIn, unsigned int binDataInLen, unsigned char* binDataOut, unsigned int *binDataOutLen, unsigned int Handle);
  def oemLock(self):
    params = 'TYPE="OEMLOCK";'
    if not FxTool.module.FXT_Sign_Locking(params, None, None, None, None, self.handle):
      raise FxToolError(self)
    print 'oemLock successful'

# FXTOOL_API int FXT_Sign_GetSimlockSignatureBySECS(const unsigned char* pDeviceId, const unsigned char* pIMEI, unsigned char* pInData, unsigned int inDataLength, int inDataType, unsigned char* pSignature, unsigned int* pSignatureSize, unsigned char* pMepd, unsigned int* pMepdSize, int keyCodeCount, unsigned char* pKeyCodes, unsigned int Handle)
  def simlockSignature(self, deviceId, imei, taFile, inDataType, signFile, mepdFile,keycode_len):
    print 'Getting SIM lock signature (from TA) from SECS ...'
    f = open(taFile, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    signature_length = c_int(4096)
    signature = (c_ubyte * signature_length.value)()
    mepd_length = c_int(4096)
    mepd = (c_ubyte * mepd_length.value)()
    #keycode_len = 5
    keycodes = (c_ubyte * (keycode_len * 16))()
    if not FxTool.module.FXT_Sign_GetSimlockSignatureBySECSv2(deviceId, imei, image, l, inDataType, byref(signature), byref(signature_length), byref(mepd), byref(mepd_length), keycode_len, byref(keycodes), self.handle):
      raise FxToolError(self)
    print 'Saving signature to file:', signFile
    f = open(signFile, 'wb')
    for n in range(0, signature_length.value):
      f.write(struct.pack('B', signature[n]))
    f.close()
    print 'Saving mepd data to file:', mepdFile
    f = open(mepdFile, 'wb')
    for n in range(0, mepd_length.value):
      f.write(struct.pack('B', mepd[n]))
    f.close()
    print 'Keycodes:'
    for n in range(keycode_len * 16):
      print keycodes[n],
      if n != 0 and (n + 1) % 16 == 0:
        print '' # newline
    print ''

  def simlockSignatureGdf(self, imei, gdfFile, signFile):
    print 'Getting SIM lock signature (from GDF) from SECS ...'
    f = open(gdfFile, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    signature_length = c_int(4096)
    signature = (c_ubyte * signature_length.value)()
    mepd_length = c_int(0)
    keycode_len = 12
    keycodes = (c_ubyte * (keycode_len * 20))() # FIX should be 16.
    if not FxTool.module.FXT_Sign_GetSimlockSignatureBySECS(None, imei, image, l, 0, byref(signature), byref(signature_length), None, byref(mepd_length), keycode_len, byref(keycodes), self.handle):
      raise FxToolError(self)
    print 'Saving signature to file:', signFile
    f = open(signFile, 'wb')
    for n in range(signature_length.value):
      f.write(struct.pack('B', signature[n]))
    f.close()
    print 'Keycodes:'
    for n in range(0, keycode_len * 16):
      print keycodes[n],
      if n != 0 and (n + 1) % 16 == 0:
        print '' # newline
    print ''

# FXTOOL_API int FXT_Sign_GetSimlockSignatureBySECS(const unsigned char* pDeviceId, const unsigned char* pIMEI, unsigned char* pInData, unsigned int inDataLength, int inDataType, unsigned char* pSignature, unsigned int* pSignatureSize, unsigned char* pMepd, unsigned int* pMepdSize, int keyCodeCount, unsigned char* pKeyCodes, unsigned int Handle)
  def simlockSignatureTest(self, deviceId, imei, taFile, inDataType, signFile, mepdFile, keycode_len):
    print 'Getting test SIM lock signature (from TA) from SECS ...'
    f = open(taFile, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    signature_length = c_int(4096)
    signature = (c_ubyte * signature_length.value)()
    mepd_length = c_int(4096)
    mepd = (c_ubyte * mepd_length.value)()
    #keycode_len = 5
    keycodes = (c_ubyte * (keycode_len * 16))()
    if not FxTool.module.FXT_Test_GetSimlockSignatureBySECSv2(deviceId, imei, image, l, inDataType, byref(signature), byref(signature_length), byref(mepd), byref(mepd_length), keycode_len, byref(keycodes), self.handle):
      raise FxToolError(self)
    print 'Saving signature to file:', signFile
    f = open(signFile, 'wb')
    for n in range(signature_length.value):
      f.write(struct.pack('B', signature[n]))
    f.close()
    print 'Saving mepd data to file:', mepdFile
    f = open(mepdFile, 'wb')
    for n in range(mepd_length.value):
      f.write(struct.pack('B', mepd[n]))
    f.close()
    print 'Keycodes:'
    for n in range(0, keycode_len * 16):
      print keycodes[n],
      if n != 0 and (n + 1) % 16 == 0:
        print '' # newline
    print ''

  def simlockSignatureTestGdf(self, imei, gdfFile, signFile):
    print 'Getting test SIM lock signature (from GDF) from SECS ...'
    f = open(gdfFile, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    signature_length = c_int(4096)
    signature = (c_ubyte * signature_length.value)()
    mepd_length = c_int(0)
    keycode_len = 12
    keycodes = (c_ubyte * (keycode_len * 20))() # FIX should be 16.
    if not FxTool.module.FXT_Test_GetSimlockSignatureBySECS(None, imei, image, l, 0, byref(signature), byref(signature_length), None, byref(mepd_length), keycode_len, byref(keycodes), self.handle):
      raise FxToolError(self)
    print 'Saving signature to file:', signFile
    f = open(signFile, 'wb')
    for n in range(signature_length.value):
      f.write(struct.pack('B', signature[n]))
    f.close()
    print 'Keycodes:'
    for n in range(0, keycode_len * 16):
      print keycodes[n],
      if n != 0 and (n + 1) % 16 == 0:
        print '' # newline
    print ''

#  FXTOOL_API int FXT_Sign_GetS1SimlockSignatureBySECS(int prodMode, const unsigned char* pIMEI, unsigned char* pInData, unsigned int inDataLength,
#                                                      unsigned char* pSignature, unsigned int* pSignatureSize, unsigned char* pMepd,
#                                                      unsigned int* pMepdSize, unsigned int* keyCodeCount, unsigned char* pKeyCodes, unsigned int* pKeyCodeSize, unsigned int Handle);

  def s1SimlockSignature(self, prodMode, imei, taFile, signFile, mepdFile):
    print 'Getting test SIM lock signature (from TA) from SECS ...'
    f = open(taFile, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    signature_length = c_int(4096)
    signature = (c_ubyte * signature_length.value)()
    mepd_length = c_int(4096)
    mepd = (c_ubyte * mepd_length.value)()
    #keycode_len = 4
    keycodes = (c_ubyte * (4 * 16))()
    keycode_len = c_int(128)
    keycode_count = c_int()
    if not FxTool.module.FXT_Sign_GetS1SimlockSignatureBySECS(prodMode, imei, image, l, byref(signature), byref(signature_length), byref(mepd), byref(mepd_length), byref(keycode_count), byref(keycodes), byref(keycode_len), self.handle):
      raise FxToolError(self)
    print 'Saving signature to file:', signFile
    f = open(signFile, 'wb')
    for n in range(signature_length.value):
      f.write(struct.pack('B', signature[n]))
    f.close()
    print 'Saving mepd data to file:', mepdFile
    f = open(mepdFile, 'wb')
    for n in range(mepd_length.value):
      f.write(struct.pack('B', mepd[n]))
    f.close()
    print 'Keycodes:'
    for n in range(0, 4 * 16):
      print keycodes[n],
      if n != 0 and (n + 1) % 16 == 0:
        print '' # newline
    print ''

#FXTOOL_API int FXT_Sign_GetS1SimlockSignatureSecureBySECS(int prodMode,const char* pIMEIStr, const unsigned char* unitDataFile,unsigned int unitDataFileLen,
#                                                             unsigned char* signature, unsigned int* pSignatureLen,char* keyCodeBlock,unsigned int* pKeyCodeBlockLen,unsigned char* modifiedUnitData,unsigned int* pModifiedUnitDataLen, unsigned int Handle)

  def s1SimlockSignatureSecure(self, prodMode, imei, taFile, signFile, mepdFile):
    print 'Getting test SIM lock signature (from TA) from SECS ...'
    f = open(taFile, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    signature_length = c_int(4096)
    signature = (c_ubyte * signature_length.value)()
    mepd_length = c_int(4096)
    mepd = (c_ubyte * mepd_length.value)()
    #keycode_len = 4
    keycodes = (c_ubyte * (4 * 16))()
    keycode_len = c_int(1280)
    if not FxTool.module.FXT_Sign_GetS1SimlockSignatureSecureBySECS(prodMode, imei, image, l, byref(signature), byref(signature_length), byref(keycodes), byref(keycode_len), byref(mepd), byref(mepd_length), self.handle):
      raise FxToolError(self)
    print 'Saving signature to file:', signFile
    f = open(signFile, 'wb')
    for n in range(signature_length.value):
      f.write(struct.pack('B', signature[n]))
    f.close()
    print 'Saving mepd data to file:', mepdFile
    f = open(mepdFile, 'wb')
    for n in range(mepd_length.value):
      f.write(struct.pack('B', mepd[n]))
    f.close()
    print 'Keycodes:'
    for n in range(0, 4 * 16):
      print keycodes[n],
      if n != 0 and (n + 1) % 16 == 0:
        print '' # newline
    print ''

# FXTOOL_API int FXT_Sign_GetDrmCertificateBySECS(const unsigned char* pIMEI, int drmGeneration, int certType, unsigned char* pCertificate, unsigned int* pCertificateSize, unsigned int Handle);
  def getDrmCertFromSecs(self, imei, gen, type, certFile):
    print 'Getting DRM cert from SECS ...'
    cert_length = c_uint(4096)
    cert = (c_ubyte * cert_length.value)()

    if not FxTool.module.FXT_Sign_GetDrmCertificateBySECS(imei, gen, type, byref(cert), byref(cert_length), self.handle):
      raise FxToolError(self)
    print 'Saving cert to file:', certFile
    f = open(certFile, 'wb')
    for n in range(cert_length.value):
      f.write(struct.pack('B', cert[n]))
    f.close()

#   FXTOOL_API int FXT_Sign_GetDrmCertificateAndIdWithSmkCombDKBySECS(int drmGeneration, int certType, const char* pIMEI, const char* pSmkName,
#                                                                                                                   unsigned char* pData, unsigned int *pDataSize, char* pCertificate ,
#                                                                                                                   unsigned int pCertificateSize, unsigned int Handle);

  def getDrmCertAndIdWithSmkCombDKFromSecs(self, imei, gen, smk, type, certFile):
    print 'Getting DRM cert from SECS ...'
    cert_length = c_uint(160000)
    cert = (c_ubyte * cert_length.value)()

    data_length = c_uint(160000)
    data = (c_byte*data_length.value)()

    if not FxTool.module.FXT_Sign_GetDrmCertificateAndIdWithSmkCombDKBySECS(gen, type, imei, smk, byref(data), byref(data_length),byref(cert), cert_length, self.handle):
      raise FxToolError(self)
    print 'Saving cert to file:', certFile
    f = open(certFile, 'wb')
    for n in range(cert_length.value):
      f.write(struct.pack('B', cert[n]))
    f.close()

# FXTOOL_API int FXT_Sign_GetDeviceKeyBySECS(const unsigned char* pIMEI, unsigned char* pDeviceKeyData, unsigned int* pDeviceKeySize, unsigned int Handle);
  def getDeviceKeyFromSecs(self, imei, devkeyFile=None):
    print 'Getting Device Key from SECS ...'
    devkey_length = c_uint(4096)
    devkey = (c_ubyte * devkey_length.value)()
    if not FxTool.module.FXT_Sign_GetDeviceKeyBySECS(imei, byref(devkey), byref(devkey_length), self.handle):
      raise FxToolError(self)
    if devkeyFile:
      print 'Saving Device Key to file:', devkeyFile
      f = open(devkeyFile, 'wb')
      for n in range(devkey_length.value):
        f.write(struct.pack('B', devkey[n]))
      f.close()
    print 'Device Key:'
    for n in range(devkey_length.value):
      print('%02x' % devkey[n]),
    print ''
    l = []
    for n in range(devkey_length.value):
      l.append(devkey[n])
    return l

#  FXTOOL_API int FXT_Sign_GetRootControlKeyBySECS(const char* pIMEI, const char* pSmkName, unsigned char* pRCKBuf, unsigned int* pRCKBufSize, unsigned int Handle);
  def getRootControlKeyBySECS(self, imei, smkname, devkeyFile=None):
    print 'Getting Device Key from SECS ...'
    devkey_length = c_uint(16)
    devkey = (c_ubyte * devkey_length.value)()
    if not FxTool.module.FXT_Sign_GetRootControlKeyBySECS(imei, smkname, byref(devkey), byref(devkey_length), self.handle):
      raise FxToolError(self)
    if devkeyFile:
      print 'Saving Device Key to file:', devkeyFile
      f = open(devkeyFile, 'wb')
      for n in range(devkey_length.value):
        f.write(struct.pack('B', devkey[n]))
      f.close()
    print 'Device Key:'
    for n in range(devkey_length.value):
      print('%02x' % devkey[n]),
    print ''
    l = []
    for n in range(devkey_length.value):
      l.append(devkey[n])
    return l

#  FXTOOL_API int FXT_Sign_CheckPreCommercialIMEI(const char *pIMEI, unsigned int *pResult, unsigned int Handle);
  def checkPreCommercialIMEI(self, imei):
    print 'checking pre-Commercial by SECS ...'
    res = c_uint()
    if not FxTool.module.FXT_Sign_CheckPreCommercialIMEI(imei, byref(res), self.handle):
      raise FxToolError(self)
    return res

# FXTOOL_API int FXT_Sign_GetHWConfigBySECS(const char *pHwConfRev, int nbrOfDeviceIds, const unsigned int *pDeviceIdLen, const char *pDeviceId,
#                    const char *pCertName, const char *pImeiNumberStr, unsigned int securityFlags, char *pResBuf,
#                    unsigned int *pResLen, unsigned int Handle);
  def getHwConfigBySecs(self, imei, rev, devidcnt, devidlens, devids, certname, securityflags, quiet=None):
    if not quiet:
      print 'Getting HwConfig from SECS for IMEI', imei, 'rev', rev, 'devidcnt', devidcnt, 'certname', certname, 'secflags', hex(securityflags), '...'
    assert devidcnt == 1, 'Support only for 1 devid for now'
    c_devidlen = (c_int * devidcnt)()
    c_devidlen[0] = devidlens
    c_devid = (c_ubyte * devidlens)()
    # convert binary string to true c binary
    for i, ch in enumerate(devids):
      c_devid[i] = ord(ch)

    reslen = c_uint(16*1024)
    resbuf = (c_ubyte * reslen.value)()
    if not FxTool.module.FXT_Sign_GetHWConfigBySECS(rev, devidcnt, byref(c_devidlen), c_devid, certname, imei, securityflags, byref(resbuf), byref(reslen), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'HwConfig from SECS ok'
    # make binary string out of resbuf
    l = [chr(resbuf[n]) for n in range(reslen.value)]
    return ''.join(l)

  #FXTOOL_API int FXT_Sign_GetSignedHwConfigWithIdList(const char *pHwConfRev,int nbrOfDeviceIds,const unsigned int *pDeviceIdLen,const char *pDeviceId,
  #                                                  const char *pCertName,int nbrOfPhoneIds,const unsigned int *pPhoneIdType,const char *pPhoneId,
  #                                                  const char *pSmkName,unsigned int securityFlags,char *pResBuf,unsigned int *pResLen,unsigned int Handle)
  def getSignedHWConfigWithIdList(self):
    print 'Getting signed HW configration with list from SECS ...'

    HwConfRev = "R1A"
    nbrOfDeviceIds = 2
    devidlen= (c_int * nbrOfDeviceIds)()
    devidlenlist = [16,18]

    urk = "1234567890123456123456789012345678"
    devID = []
    for x in range(len(urk)):
      devID.append(48 + int(urk[x]))

    totlen = 0
    for x in range(nbrOfDeviceIds):
      devidlen[x] = devidlenlist[x]
      totlen = totlen + devidlenlist[x]
    devid = (c_ubyte * totlen)()
    for x in range(totlen):
      devid[x] = devID[x]

    #certName = 'BROWNBLUE_CID110--80-53--49-0_DB3150'
    certName = 'S1_HWConf_Test_xxxx_0001'
    imei = "12345678901234"

    # 1, 0, imei is list length, type IMEI and IMEI string
    if isinstance(imei, str):
      phnidlen = 1
      phntype = c_int(0)
    else:
      phnidlen = len(imei)
      phntype = (c_int * phnidlen)(0)
      for i in range(phnidlen):
        phntype[i] = i
      imei = '\0'.join(imei)

    securityFlags = 1
    resLen = c_uint(4096)
    resBuf = (c_ubyte * resLen.value)()
    if not FxTool.module.FXT_Sign_GetSignedHwConfigWithIdList(HwConfRev, nbrOfDeviceIds, devidlen, devid, certName, phnidlen, byref(phntype), imei, None, securityFlags, byref(resBuf), byref(resLen), self.handle):
      raise FxToolError(self)
    return (resBuf, resLen)

   #FXT_Sign_SetSecurityInHWConfigBySECS Takes an existing HW config, sets
   # the security flag and resigns it with the cert that has the latest AID.
   # Supported platforms: S1.
   # Parameters
   #  pHwConf             (in): hwConf [in] Old Hw configuration data
   #  pHwConfLen          (in): Length of HW configuration data.
   #  securityFlags       (in): Zero means security will be enabled in the hw config, use one for security off.
   #  pResBuf             (out): A buffer where the result will be put
   #  pResLen             (in/out): Size of resBuf. This will be set to the size of the result before returning.
   #  Handle              (in): Handle index received from FXT_Main_GetHandle[Ex].
  #FXTOOL_API int FXT_Sign_SetSecurityInHWConfigBySECS(const char* pHwConf, unsigned int hwConfLen , unsigned int securityFlags, char *pResBuf, unsigned int *pResLen, unsigned int Handle);
  def SetSecurityInHWConfigBySECS(self, resBuf, resLen):
    print 'Setting HW configration from SECS ...'
    securityFlags = 1
    resLen1 = c_uint(4096)
    resBuf1 = (c_ubyte * resLen.value)()
    if not FxTool.module.FXT_Sign_SetSecurityInHWConfigBySECS(resBuf, resLen, securityFlags, byref(resBuf1), byref(resLen1), self.handle):
      raise FxToolError(self)

  def SetSwAidInHWConfigBySECS(self, resBuf, resLen):
    print 'Setting SwAid in HW configration from SECS ...'
    swAid = 1
    resLen1 = c_uint(4096)
    resBuf1 = (c_ubyte * resLen.value)()
    if not FxTool.module.FXT_Sign_SetSwAidInHwConfigBySECS(resBuf, resLen, swAid, byref(resBuf1), byref(resLen1), self.handle):
      raise FxToolError(self)

# FXTOOL_API int FXT_Sign_GetSecurityPropertiesBySECS(const unsigned char* pDeviceId, const unsigned char* pIMEI, unsigned char* pOTPData, unsigned int* pOTPDataSize, unsigned int* pOTPRevision, unsigned short OTPFormat, unsigned int Handle);
  def getOtpFromSecs(self, deviceid, imei, otpRev, otpFile):
    print 'Getting OTP from SECS, rev:', otpRev, '...'
    otp_length = c_int(4096)
    otp = (c_ubyte * otp_length.value)()
    otp_rev = c_uint(otpRev)
    if not FxTool.module.FXT_Sign_GetSecurityPropertiesBySECS(deviceid, imei, byref(otp), byref(otp_length), byref(otp_rev), 1, self.handle):
      raise FxToolError(self)
    print 'Saving OTP data to file:', otpFile
    f = open(otpFile, 'wb')
    for n in range(0, otp_length.value):
      f.write(struct.pack('B', otp[n]))
    f.close()
    print 'OTP size received:', otp_length.value
    print 'OTP revision received:', otp_rev.value

# FXTOOL_API int FXT_Sign_GetSecurityPropertiesWithRevisionBySECS(const unsigned char* pIMEI, unsigned char* pOTPData, unsigned int* pOTPDataSize, const unsigned char* pOTPRevision, unsigned int Handle);
  def getOtpWithRevFromSecs(self, imei, otpRev, otpFile):
    print 'Getting OTP from SECS, rev:', otpRev, '...'
    otp_length = c_int(4096)
    otp = (c_ubyte * otp_length.value)()
    if not FxTool.module.FXT_Sign_GetSecurityPropertiesWithRevisionBySECS(imei, byref(otp), byref(otp_length), otpRev, self.handle):
      raise FxToolError(self)
    print 'Saving OTP data to file:', otpFile
    f = open(otpFile, 'wb')
    for n in range(0, otp_length.value):
      f.write(struct.pack('B', otp[n]))
    f.close()
    print 'OTP size received:', otp_length.value

#FXT_Sign_GetSecurityPropertiesWithRevisionBySECS_v2(const char* pIMEI, unsigned char* pOTPData, unsigned int* pOTPDataSize, const char* pOTPRevision, unsigned int Handle)
  def getOtpWithRevFromSecsV2(self, imei, otpRev, otpFile):
    print 'Getting OTP from SECS, rev:', otpRev, '...'
    otp_length = c_int(4096)
    otp = (c_ubyte * otp_length.value)()
    if not FxTool.module.FXT_Sign_GetSecurityPropertiesWithRevisionBySECSv2(imei, byref(otp), byref(otp_length), otpRev, self.handle):
      raise FxToolError(self)
    print 'Saving OTP data to file:', otpFile
    f = open(otpFile, 'wb')
    for n in range(0, otp_length.value):
      f.write(struct.pack('B', otp[n]))
    f.close()
    print 'OTP size received:', otp_length.value

#FXTOOL_API int FXT_Sign_GetSecurityPropertiesWithRevisionAndProdModeBySECSv2(const char* pIMEI, int protMode, unsigned char* pOTPData, unsigned int* pOTPDataSize,
#                                                                     const char* pOTPRevision, const char* pSmkName, unsigned int Handle);

  def getOtpWithRevAndProdModeFromSecsV2(self, imei, prodMode, otpRev, otpFile, smk):
    print 'Getting OTP from SECS, rev:', otpRev, '...'
    otp_length = c_int(4096)
    otp = (c_ubyte * otp_length.value)()
    if not FxTool.module.FXT_Sign_GetSecurityPropertiesWithRevisionAndProdModeBySECSv2(imei, prodMode, byref(otp), byref(otp_length), otpRev, smk, self.handle):
      raise FxToolError(self)
    print 'Saving OTP data to file:', otpFile
    f = open(otpFile, 'wb')
    for n in range(0, otp_length.value):
      f.write(struct.pack('B', otp[n]))
    f.close()
    print 'OTP size received:', otp_length.value

# FXTOOL_API int FXT_Sign_BindToHw(const unsigned char *pInData, unsigned int inDataLength, unsigned char *pOutData, unsigned int *pOutDataLength, unsigned int Handle);
  def bind(self, indataFile, mepdFile):
    print 'Binding to hardware ...'
    f = open(indataFile, 'rb')
    image = f.read()
    f.close()
    l = len(image)
    mepd_length = c_int(4096)
    mepd = (c_ubyte * mepd_length.value)()
    if not FxTool.module.FXT_Sign_BindToHw(image, l, byref(mepd), byref(mepd_length), self.handle):
      raise FxToolError(self)
    print 'Saving bound mepd data to file:', mepdFile
    f = open(mepdFile, 'wb')
    for n in range(0, mepd_length.value):
      f.write(struct.pack('B', mepd[n]))
    f.close()

# FXTOOL_API int FXT_Flash_WriteData(uint64_t Bus, uint64_t Address, const unsigned char* pData, int64_t DataLength, void *AdditionalInfo, unsigned int Handle);
  def regWrite(self, bus,addr,data):
    print 'FXT_Flash_WriteData...'
    datalen = len(data)
    if data != None:
      d = (c_byte * datalen)()
      print 'In data len:', datalen
      for n in range(0, datalen):
        if isinstance(data, str):
          d[n] = ord(data[n])
        else:
          d[n] = data[n]
    if not FxTool.module.FXT_Flash_WriteData(bus, addr, byref(d), datalen, 0, self.handle):
        raise FxToolError(self)

  def setBootable(self, lun):
    print 'setbootablestoragedrive: ', lun
    setbootablelun = "LUN=\"%d\";" % lun
    if not FxTool.module.FXT_Flash_ProvisionDevice(1, setbootablelun, None, None, self.handle):
        raise FxToolError(self)
    else:
        print "setbootable.."

# FXTOOL_API int FXT_Test_GenericCommand(unsigned int Command, const unsigned char* pInData, unsigned int inDataSize, unsigned char* pOutData, unsigned int* pOutDataSize, unsigned int Handle)
  def genCommand(self, command, timeout = 0, data = None, outlength = 16384, quiet=None):
    if not quiet:
      print 'Executing Generic Command:', hex(command), 'with timeout:', timeout, '...'
    timeout *= 1000
    od_length = c_uint(outlength)
    od = (c_byte * od_length.value)()
    if data != None:
      l = len(data)
      d = (c_byte * l)()
      if not quiet:
        print 'In data len:', l
      for n in range(0, l):
        if isinstance(data, str):
          d[n] = ord(data[n])
        else:
          d[n] = data[n]
      if not FxTool.module.FXT_Test_GenericCommandWithTimeout(command, byref(d), l, byref(od), byref(od_length), timeout, self.handle):
        raise FxToolError(self)
    else:
      if not FxTool.module.FXT_Test_GenericCommandWithTimeout(command, None, 0, byref(od), byref(od_length), timeout, self.handle):
        raise FxToolError(self)

    rl = []
    if (od_length):
      for n in range(0, od_length.value):
        rl.append(od[n])

    if not quiet:
      print 'Result, length:', od_length.value
      print 'Result, data:', self.hexlist(rl, 'hex')
      print 'Generic Command OK'
    return rl

# FXTOOL_API int FXT_Test_InitiateCommunicationWithExistingLoader(unsigned int Command, const unsigned char* pInData,
#                                                                 unsigned int inDataLength, FXT_Loader_Type_t LoaderType,
#                                                                 const char *pPort, const char* pSpeed,
#                                                                 unsigned char* pOutData, unsigned int* pOutDataLength,
#                                                                 unsigned int timeout, unsigned int Handle)
  def testCommunicateWithExixtingLoader(self, loadertyp = 10, com = 'COM4', speed = '9600'):
    print 'Initiating communication On:',com,'...'
    if not FxTool.module.FXT_Test_InitiateCommunicationWithExistingLoader(loadertyp, com, speed, self.handle):
      raise FxToolError(self)
    print 'Communication Initiated: OK'


#FXT_Test_GenericFlag(const char* pFlag, unsigned int Handle);
  def setGenericSetting(self, info):
    if not FxTool.module.FXT_Setting_Set(info, self.handle):
      raise FxToolError(self)

# FXTOOL_API int FXT_Debug_GetRunningThreadId(unsigned long *pId, unsigned int Handle)
  def getRunningThreadId(self, quiet=None):
    if not quiet:
      print 'Getting running thread id ...'
    id = c_uint()
    if not FxTool.module.FXT_Debug_GetRunningThreadId(byref(id), self.handle):
      raise FxToolError(self)
    if not quiet:
      print 'Thread id:', hex(id.value)
    return id.value


#FXTOOL_API int FXT_Comm_ChangeLoaderTypeWithParameters(FXT_Loader_Type_t LoaderType, const char* Parameters, unsigned int Handle);
  def changeLoaderType(self, loadertype, paramString):
    FxTool.module.FXT_Comm_ChangeLoaderTypeWithParameters(loadertype, paramString, self.handle)

# FXTOOL_API int FXT_Flash_ProgramImageFromHandleWithParameters(unsigned int ImageHandle, const char* Parameters, unsigned int Handle);
  def flashImageFromHandleWithParameters(self, paramString, handle, quiet=None):
    if not quiet:
      print 'Flash sequence starting ...'
    t1 = time.time()
    if FxTool.module.FXT_Flash_ProgramImageFromHandleWithParameters(handle, paramString, self.handle):
      td = time.time() - t1
      s = 0
      l = self.getBytesFlashed()
      if td:
        s = l * 8 / td / 1024
      if not quiet:
        print 'Flashed', l, 'bytes in', round(td, 2), 's, speed', round(s, 2), 'kbit/s'
    else:
      if not quiet:
        print 'Flashed:', self.getBytesFlashed()
      raise FxToolError(self)

# FXTOOL_API int FXT_Loader_GetInfo(const char* Parameters, unsigned char* Buffer, UINT64 *BufferSize, unsigned int Handle);
  def getInfo(self, Logfile, Params):
    buf = create_string_buffer(4096)
    buflen = c_int(8)
    buflen.value = 4096
    if FxTool.module.FXT_Loader_GetInfo(Params, byref(buf), byref(buflen), self.handle):
      print Logfile, " length: ", buflen.value
      fp = open(Logfile, 'wb')
      fp.write(buf)
      fp.close()
    else:
      print 'Failed to get log'

# FXTOOL_API int FXT_Flash_DumpFlashToFileWithParameters(const char* Filename,const char* Parameters, unsigned int Handle);
  def dumpPartition(self, File, Params):
    if FxTool.module.FXT_Flash_DumpFlashToFileWithParameters(File, Params, self.handle):
      print "Failed to get partition"
    else:
      print "Dump to ", File

#FXTOOL_API int FXT_Test_FastbootGenericCommand(FXT_FastbootGenericFlow_t flowType, const char* command, unsigned char* buf, unsigned int *bufLen, int timeoutMS, unsigned int handle);
  def genCommand2(self, command_type, command, buf, buf_len, timeout):
    print "Fastboot Generic Command"
    buflen = c_int(8)
    buflen.value = buf_len
    if FxTool.module.FXT_Test_FastbootGenericCommand(command_type, command, buf, byref(buflen), timeout, self.handle):
      print "Yes", buflen.value
    else:
      print "No"

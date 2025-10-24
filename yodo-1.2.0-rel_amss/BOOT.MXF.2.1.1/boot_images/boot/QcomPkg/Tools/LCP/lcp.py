
#=============================================================================
# FILE:         lcp.py
#
# OVERVIEW:     LCP automation script
#
#               Copyright (c) 2018-2021 Qualcomm Technologies, Inc.
#               All Rights Reserved.
#               Qualcomm Technologies Proprietary and Confidential.
#=============================================================================
# ----------------------------------
# Portions
#
# 1.	Copyright Michael Foord 2004
# 2.	Released subject to the BSD License
# 3.	Please see http://www.voidspace.org.uk/python/license.shtml
# Copyright (c) 2003-2010, Michael Foord
# All rights reserved.
# E-mail : fuzzyman AT voidspace DOT org DOT uk
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following
# disclaimer in the documentation and/or other materials provided
# with the distribution.
#
# Neither the name of Michael Foord nor the name of Voidspace
# may be used to endorse or promote products derived from this
# software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ------------------------------

import argparse
import os
import json
import struct
import shutil
import tempfile
import subprocess
import sys
import re
import time
import glob
import fnmatch
import platform

import logging
import xml.etree.ElementTree as ET

# TODO: DEBUG
import pprint

if sys.version_info < (3, 8, 2):
      print("Must use Python 3.8.2 or greater")
      sys.exit(1)

DEBUG = False

def onerror(func, path, exc_info):
    """
    Error handler for ``shutil.rmtree``.

    If the error is due to an access error (read only file)
    it attempts to add write permission and then retries.

    If the error is for another reason it re-raises the error.

    Usage : ``shutil.rmtree(path, onerror=onerror)``
    """
    import stat
    if not os.access(path, os.W_OK):
        # Is the error an access error ?
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        raise Exception

def genremove(logger, rmpath):
    try:
        if os.path.isdir(rmpath):
            shutil.rmtree(rmpath, onerror=onerror)
        else:
            if os.path.isfile(rmpath):
                os.remove(rmpath)
            else:
                logger.debug(" %s is not present , skip delete", rmpath)
        time.sleep(1)
    except Exception as e:
        logger.debug(" could not remove path %s", rmpath)
        logger.debug(e)


def run_command(logger, cmd, errorkey=None, failonerror=True, Dly=0):
    errorcheck = False
    logger.info(" Running cmd: %s", cmd)
    logger.debug(cmd.split(" "))

    p = subprocess.Popen(cmd.split(" "), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    for c in iter(p.stdout.readline, b''):
        if errorkey is not None and errorkey in str(c):
            errorcheck = True
        logger.debug(c.decode('utf-8','ignore').rstrip('\r\n'))

    time.sleep(Dly)

    supressMsg = False
    subprocess.Popen("TASKLIST /FI \"PID eq {pid}\"".format(pid=p.pid), stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    for c in iter(p.stdout.readline, b''):
        if "No tasks" in str(c):
            supressMsg = True
        logger.debug(c.decode('utf-8','ignore').rstrip('\r\n'))

    if supressMsg:
        subprocess.Popen("TASKKILL /F /PID {pid} /T".format(pid=p.pid))

    if errorcheck:
        if failonerror:
            logger.error("[ERROR] found when running command, system_exit")
            sys.exit()
        logger.warning("[WARNING] Run command end with errorcheck=True")
        return False
    else:
        logger.debug(" Run command successfully")
        return True

#TODO: run-time auto-detect
LCPLibTargetSettings = {
    "SM8550" : {
        "ProfilePkg" : os.path.join("profiles","kailua","kailua_tme_security_profile.xml"),
        "OSPathDSFPkg" : os.path.join("SocPkg","kailua"),
    },
}

class LCPLib(object):
    # class globals
    BIN_NAMES = ["DDI_INPUT", "ECDT_POST_DEVICE_INIT", "ECDT_PRE_DEVICE_INIT", "LCP"]

    def __init__(self, output_dir, boot_build=None, sectool_path=None, target=None):
        self.logger = logging.getLogger("lcp.LCPLib")
        if target is None: #default
            target = "SA8540P"
            self.logger.debug("no target specified, use default")
        self.target = target
        self.logger.info("LCP Lib target config %s", self.target)

        if boot_build is None:
            boot_build = os.path.dirname(os.path.realpath(__file__)).split("boot_images")[-2]
        self.boot_build = boot_build


        self.output_dir = output_dir
        self.xblconfig_tools_loaded = False
        self.force_copy = False
        self.sectools = sectool_path

    def __get_xblconfig_tools(self):
        # TODO: import tools
        try:
            self.logger.debug("__get_xbl_config_tools, init")
            tools_path = os.path.join(self.boot_build, "boot_images", "boot_tools", "XBLConfig")
            dest_path =os.path.join(self.output_dir, "xblconfig")
            if(self.force_copy or (not os.path.exists(dest_path))):
                genremove(self.logger, dest_path)
                shutil.copytree(tools_path, dest_path)
                self.logger.info("XBLConfig tools copied to: %s", dest_path)
            else:
                self.logger.info("NOT COPY XBLConfig tools to: %s", dest_path)
                self.logger.info("reason: folder exist: " + str(os.path.exists(dest_path)) + ", force_copy: " + str(self.force_copy))
                
            tools_path = self.sectools
            dest_path =os.path.join(self.output_dir, "sectools")
            if(self.force_copy or (not os.path.exists(dest_path))):
                genremove(self.logger, dest_path)
                shutil.copytree(tools_path, dest_path)
                self.logger.info("sectools copied to: %s", dest_path)
            else:
                self.logger.info("NOT COPY sectools to: %s", dest_path)
                self.logger.info("reason: folder exist: " + str(os.path.exists(dest_path)) + ", force_copy: " + str(self.force_copy))
        except Exception as e:
            self.logger.debug(e)
            self.logger.debug("__get_xbl_config_tools, exception on copy tool.")
        
        try:        
            genremove(self.logger, os.path.join(self.output_dir, "decompose"))
            os.makedirs(os.path.join(self.output_dir, "decompose"))
            genremove(self.logger, os.path.join(self.output_dir, "compose"))
            os.makedirs(os.path.join(self.output_dir, "compose"))
            self.xblconfig_tools_loaded = True
            self.logger.debug("__get_xbl_config_tools, end")
        except Exception as e:
            self.logger.debug(e)
            self.logger.debug("__get_xbl_config_tools, exception on removing decompose or compose")
            return False

    def decompose_xblconfig(self, xbl_config):

        if not self.xblconfig_tools_loaded:
            self.__get_xblconfig_tools()
        
        os.chdir(os.path.join(self.output_dir, "xblconfig"))
        cmd = "python GenXBLConfig.py -d %s -f ELF -o %s" %(xbl_config, os.path.join(self.output_dir, "decompose"))
        self.logger.debug(cmd)
        run_command(self.logger, cmd)
        return os.path.join(self.output_dir, "decompose")

    def __compose_xblconfig(self, name_tag=None):
        xbl_name = "xbl_config"

        if not self.xblconfig_tools_loaded:
            self.__get_xblconfig_tools()

        os.chdir(os.path.join(self.output_dir, "xblconfig"))
        input_json = os.path.join(self.output_dir, "decompose", "create_xbl_config.json")
        bin_path = os.path.join(self.output_dir, "decompose")

        if(name_tag is not None):
            xbl_name = xbl_name+name_tag
        output = os.path.join(self.output_dir, "compose", xbl_name)
        sectools_path = os.path.join(self.output_dir, "sectools", platform.system())
        sec_prof = os.path.join(self.boot_build, "boot_images", "ssg_tmefwrel", LCPLibTargetSettings[self.target]["ProfilePkg"])
        if os.path.exists(sec_prof):
            cmd = "python GenXBLConfig.py -i %s -b %s -f ELF -o %s --sectools_directory %s --sectools_version v2 --sign_id XBL-CONFIG --security_profile %s --signing_mode %s" %(input_json, bin_path, output, sectools_path, sec_prof, "TEST")
            run_command(self.logger, cmd, Dly=25)

            xbl_name = xbl_name + ".elf"
        else:
            self.logger.debug("file %s doesn't exist, please make sure you are using a correct boot build!", sec_prof)
            sys.exit()

        return os.path.join(self.output_dir, "compose", xbl_name)

    @staticmethod
    def bytes_crc32(bytes):
        CRC_POLYNOMIAL = 0x04C11DB7
        CRC_INITVAL = 0xFFFFFFFF
        CRC_XOROUT = 0xFFFFFFFF

        result = CRC_INITVAL
        for octet in bytes:
            if type(octet) is str:
                octet = struct.unpack("B", octet)[0]
            for bit in range(0,8):
                if (octet >> 7) ^ (result >> 31):
                    result = ((result << 1) & 0xFFFFFFFF) ^ CRC_POLYNOMIAL
                else:
                    result = (result << 1) & 0xFFFFFFFF
                octet = (octet << 1) & 0xFF

        result = result ^ CRC_XOROUT
        return result

    def GenDcbBin(self, header_file, dcb_file, bin_files, output_path, output_file):
        binaries_ordered_by_header_index = []
        DCB_MAX_SIZE = 0

        if os.path.exists(header_file):
            define_re = re.compile(r'^#define[ \t]+([A-Z_]+)[ \t]+([\(\)\+\-\*\/0-9 xA-F]+)$')
            first = re.compile(r'^\s+DDI_INPUT_IDX.*?')
            reclaim = re.compile(r'^\s+RECLAIM_IDX.*?$')
            max = re.compile(r'^\s+DCB_IDX_MAX.*?$')
            cfg = re.compile(r'^\s+([A-Z0-9_]+)_CFG_IDX.*?$')
            idx = re.compile(r'^\s+([A-Z0-9_]+)_IDX.*?$')
            with open(header_file,"r") as dcb_header_fp:
                ignore = True
                for line in dcb_header_fp:
                    # Remove comments
                    line = line.split("//")[0]
                    # Check for a macro defined as a value or formula
                    m = define_re.match(line)
                    if m:
                        if m.group(1) == "DCB_MAX_SIZE":
                            DCB_MAX_SIZE = eval(m.group(2))
                        continue

                    # DDI_INPUT_IDX
                    match = first.match(line)
                    if match:
                        ignore = False
                
                    if ignore == False:
                        # RECLAIM_IDX
                        match = reclaim.match(line)
                        if match:
                            continue
                                
                        # DCB_IDX_MAX
                        match = max.match(line)
                        if match:
                            break
                            
                        # _CFG_IDX
                        match = cfg.match(line)
                        if match:
                            binaries_ordered_by_header_index.append(match.group(1))
                            continue
                            
                        # _IDX
                        match = idx.match(line)
                        if match:
                            if match.group(1) not in ["DCB_CRC", "DCB_SIZE", "DSF_MAINLINE_VERSION", "DSF_MAJOR_VERSION", "DSF_MINOR_VERSION"]:
                                binaries_ordered_by_header_index.append(match.group(1))
                            continue
        else:
            if self.target == 'SM8550':
                binaries_ordered_by_header_index = [#'DCB_CRC',
                                                    #'DCB_SIZE',
                                                    #'DSF_MAINLINE_VERSION',
                                                    #'DSF_MAJOR_VERSION',
                                                    #'DSF_MINOR_VERSION',
                                                    'DDI_INPUT',
                                                    'RUNTIME',
                                                    'LCP_INPUT_STRUCT',
                                                    'MC_PXI_PRE_TRAINING',
                                                    'MC_PXI_RD',
                                                    'MC_PXI_WR',
                                                    'MC_PXI_RCW',
                                                    'MC_PXI_WRLVL',
                                                    'MC_PXI_CBT',
                                                    'SAVE_RESTORE',
                                                    'TRAINING_PARAMS',
                                                    'LCP',
                                                    'MC_STATES',
                                                    'SHUB_STATES',
                                                    'SHRM_STATES',
                                                    'DEFAULT_ALC_POLICY',
                                                    'ALC_TIMINGS',
                                                    'ALC_POLICY_INDEX',
                                                    'PERF_MODE_ALC_POLICY',
                                                    'PMIC_SETTINGS',
                                                    'MIN_DDR_SHUB_RATIO',
                                                    'MIN_SHUB_CP',
                                                    'ECDT_PRE_DEVICE_INIT',
                                                    'ECDT_POST_DEVICE_INIT',
                                                    'DDRSS',
                                                    'NOC',
                                                    'SHRM',
                                                    'SHRM2',
                                                    'MCCC_MSTR',
                                                    'MCCC_SLV',
                                                    'DDRPHY',
                                                    'MC',
                                                    'LLCC',
                                                    'AHB2PHY',
                                                    'SHRM_DUMP']

                DCB_MAX_SIZE = ((1024*50)+4)

        self.logger.warning("DCB_MAX_SIZE: %d", DCB_MAX_SIZE)
        self.logger.warning("binaries_ordered_by_header_index: %s", binaries_ordered_by_header_index)

        import struct
        dcbBinDict = {}
        DCB_CRC = 0
        DCB_SIZE = 0
        DSF_MINOR_VERSION = 0
        DSF_MAJOR_VERSION = 0
        DSF_MAINLINE_VERSION = 0
        with open(dcb_file, "rb") as dcb_fp:
            DCB_CRC = struct.unpack("<I", dcb_fp.read(4))[0]
            DCB_SIZE = struct.unpack("<I", dcb_fp.read(4))[0]
            DSF_MAINLINE_VERSION = struct.unpack("<I", dcb_fp.read(4))[0]
            DSF_MAJOR_VERSION = struct.unpack("<I", dcb_fp.read(4))[0]
            DSF_MINOR_VERSION = struct.unpack("<I", dcb_fp.read(4))[0]
            header_offset = 20
            for bin in binaries_ordered_by_header_index:
                bin_off = struct.unpack("<H", dcb_fp.read(2))[0]
                bin_size = struct.unpack("<H", dcb_fp.read(2))[0]
                header_offset += 4
                
                self.logger.warning("bin_off: %d", bin_off)
                self.logger.warning("bin_size: %d", bin_size)
                self.logger.warning("header_offset: %d", header_offset)

                if bin in bin_files:
                    with open(bin_files[bin], "rb") as bin_f:
                        dcbBinDict[bin] = bin_f.read()
                else:
                    if bin_off != 0:
                        dcb_fp.seek(bin_off)
                        dcbBinDict[bin] = dcb_fp.read(bin_size)
                        dcb_fp.seek(header_offset)
        
        output = ""
        
        # Calculate header size
        # len(DSF.binaries_ordered_by_header_index) 
        # + 3 for DCB_CRC_IDX, DCB_SIZE_IDX, DSF_MAINLINE_VERSION_IDX, DSF_MAJOR_VERSION_IDX, & DSF_MINOR_VERSION_IDX
        # which are not part of DSF.binaries_ordered_by_header_index array
        header_max_size = (len(binaries_ordered_by_header_index) + 5) * 4

        # Make header a multiple of 8 bytes for proper pointer alignment
        remainder = header_max_size % 8
        if remainder != 0:
            header_max_size += (8 - remainder)

        # Header bytes object
        header = bytes()

        # Data bytes object
        data = bytes()

        # Data starts at end of header
        offset = header_max_size

        # Loop through each binary section of DCB
        for bin in binaries_ordered_by_header_index:
            # Check if DCB sub-block exists
            if bin in dcbBinDict:
                # Update header
                size = len(dcbBinDict[bin])
                header += struct.pack("<H", offset)
                header += struct.pack("<H", size)
                offset += size

                # Update data
                data += dcbBinDict[bin]
                
                # Align each section of DCB to 8 byte boundary
                remainder = offset % 8
                if remainder != 0:
                    remainder = 8 - remainder
                for _ in range(remainder):
                    data += struct.pack("<B", 0)
                offset += remainder
            else:
                header += struct.pack("<H", 0)
                header += struct.pack("<H", 0)
                self.logger.warning("[WARNING] {:s} DCB sub-block not populated".format(bin))

        # DSF Version
        header = struct.pack("<I", DSF_MINOR_VERSION) + header
        header = struct.pack("<I", DSF_MAJOR_VERSION) + header
        header = struct.pack("<I", DSF_MAINLINE_VERSION) + header
        # Size of DCB including header
        size = len(data) + header_max_size
        header = struct.pack("<I", size) + header

        # CRC set to zero as placeholder for CRC calculation
        header = struct.pack("<I",0) + header

        # Pad header with zeros
        header = header.ljust(header_max_size, b'\0')

        # Combine header and data
        binary = header + data

        # Pad binary with zeros
        binary = binary.ljust(DCB_MAX_SIZE, b'\0')

        # Calculate CRC on entire DCB binary
        crc = self.bytes_crc32(binary)

        # Replace placeholder CRC
        binary = struct.pack("<I", crc) + binary[4:]

        # Print information on which XL file is being processed and resulting binary
        # Print CRC and size information
        self.logger.info("[INFO] DCB {:s}, CRC 0x{:08X}, {:d}B free ({:d}/{:d} used)".format(
            os.path.basename(output_file),
            crc,
            DCB_MAX_SIZE - size,
            size,
            DCB_MAX_SIZE))

        # Write to file
        with open(os.path.join(output_path, output_file), "wb") as f:
            f.write(binary)

    def gen_xbl_config(self, dcb_input, lcp_input=None, name_tag=None):
        # create new dcb based on old dcb, lcp input
        header_file =os.path.join(self.boot_build, "boot_images", "boot", "QcomPkg", LCPLibTargetSettings[self.target]["OSPathDSFPkg"], "Library", "DSFTargetLib", "interface","header","api","ddr_shared_interface.h")
        binpaths = {}
        if lcp_input is not None:
            try:
                self.logger.debug("args.lcp_bin: %s", lcp_input)
                index = LCPLib.BIN_NAMES.index(os.path.basename(lcp_input).strip(".bin"))
                binpaths[LCPLib.BIN_NAMES[index]] = lcp_input
                self.logger.debug("Matched bin to LCPLib BIN_NAMES name:%s path:%s", LCPLib.BIN_NAMES[index], lcp_input)
            except ValueError:
                self.logger.debug("Could not match LCPLib BIN_NAMES with: "+lcp_input)
                sys.exit()

         
        for dcb_bin in glob.glob(dcb_input + '/*_dcb.bin'):
            # save off the input DCB for debug, new DCB will be generated in its place
            if (os.path.exists(dcb_input)):
                original_dcb = os.path.join(dcb_input, "orig_"+os.path.basename(dcb_bin))
                shutil.move(dcb_bin,original_dcb)
                self.GenDcbBin(header_file, original_dcb, binpaths, os.path.join(self.output_dir, "decompose"), dcb_bin)

        if(name_tag is not None):
            return self.__compose_xblconfig(name_tag)
        return self.__compose_xblconfig()

    def update_dcb_bin(self, dcb_path, lcp_input=None):
        # create new dcb based on old dcb, lcp input
        header_file =os.path.join(self.boot_build, "boot_images", "boot", "QcomPkg", LCPLibTargetSettings[self.target]["OSPathDSFPkg"], "Library", "DSFTargetLib", "interface","header","api","ddr_shared_interface.h")
        binpaths = {}
        if lcp_input is not None:
            try:
                self.logger.debug("args.lcp_bin: %s", lcp_input)
                index = LCPLib.BIN_NAMES.index(os.path.basename(lcp_input).strip(".bin"))
                binpaths[LCPLib.BIN_NAMES[index]] = lcp_input
                self.logger.debug("Matched bin to LCPLib BIN_NAMES name:%s path:%s", LCPLib.BIN_NAMES[index], lcp_input)
            except ValueError:
                self.logger.debug("Could not match LCPLib BIN_NAMES with: "+lcp_input)
                sys.exit()
                    
        for dcb_bin in glob.glob(dcb_path + '/*_dcb.bin'):
            # save off the input DCB for debug, new DCB will be generated in its place
            if (os.path.exists(dcb_path)):
                original_dcb = os.path.join(dcb_path, "orig_"+os.path.basename(dcb_bin))
                shutil.move(dcb_bin,original_dcb)
                self.GenDcbBin(header_file, original_dcb, binpaths, os.path.join(self.output_dir, "decompose"), dcb_bin)

def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter, description='LCP helper library\r\n' + 
    '1, example to update xbl_config.elf to include LCP bin:\r\n' +
    "   python <boot_build_path>boot_images\\boot\QcomPkg\Tools\LCP\lcp.py --target=SM8550 -v DEBUG -s <meta_build_path>\common\sectoolsv2\ext -o ./output in -l LCP.bin -x xbl_config.elf" + 
    '\r\n' +
    '2, example to update DCB bins to include LCP bin:\r\n' +
    "   python <boot_build_path>boot_images\\boot\QcomPkg\Tools\LCP\lcp.py --target=SM8550 -v DEBUG -s <meta_build_path>\common\sectoolsv2\ext -o ./output in -l LCP.bin -x <dcb_bin_path>")
    
    parser.add_argument("-b", "--boot_build", help="path to boot CRM build base")
    parser.add_argument("-o", "--output_dir", default=tempfile.mkdtemp(prefix="lcp_"), help="output location to store debug logs and output files. If not supplied, a OS temporary directory will be created")
    parser.add_argument("-r", "--run_id", default="run_output", help="run_id, timestamp of current run")    
    parser.add_argument("-v", "--verbose", default="INFO", choices=["DEBUG", "INFO", "WARNING" ,"ERROR"], help="logging verbosity to be send to the cmd window. By default, all debug logs will be sent to a file")
    parser.add_argument("-a", "--target", help="target device")
    parser.add_argument("-s", "--sec_tool", help="path to sec tools")

    subparsers = parser.add_subparsers(help="sub-command help")
    parser_input = subparsers.add_parser("in", help="Command to generate a new xbl_config.elf based on an original xbl_config.elf file or update original DCB bins to inlcude LCP.bin")
    parser_input.add_argument("-l", "--lcp_bin", required=True, help="list of lcp binary paths")
    parser_input.add_argument("-x", "--xbl_config", required=True, help="1)If providing an original xbl_config.elf file, will update it to include lcp.bin; 2) If providing DCB bin path, will update DCB bin to include lcp.bin.")
    parser_input.set_defaults(which="in")

    args = parser.parse_args()

    if not args.output_dir is None and not os.path.isdir(args.output_dir):
        os.makedirs(args.output_dir)
    
    run_output = os.path.join(args.output_dir, args.run_id)
    if not os.path.isdir(run_output):
        os.makedirs(run_output)
    init_time = int(time.time())
    lcp_log = "lcp_debug_log_"+str(init_time)+".txt"
    logging.basicConfig(filename=os.path.join(run_output, lcp_log), level=logging.getLevelName(args.verbose), filemode="w")
    rootlogger = logging.getLogger()
    ch = logging.StreamHandler()
    ch.setLevel(logging.getLevelName(args.verbose))
    rootlogger.addHandler(ch)
    logger = logging.getLogger("lcp")

    if args.which == "in":
        os.chdir(args.output_dir)
        logger.info("current working dir: %s:", os.getcwd())
        lcplib = LCPLib(args.output_dir, boot_build=args.boot_build, sectool_path= args.sec_tool, target=args.target)
        
        # Generate xbl_config.elf with new LCP
        if fnmatch.fnmatch(os.path.basename(args.xbl_config), "xbl_config.elf"):
            shutil.copy(args.xbl_config, os.path.join(args.output_dir, "ori_xbl_config.elf"))
            decompose_path = lcplib.decompose_xblconfig(args.xbl_config)    
            xbl_config = lcplib.gen_xbl_config(decompose_path, lcp_input=args.lcp_bin)
            logger.info("")
            if os.path.exists(xbl_config):
                logger.info("new xbl_config is generated at: %s !", xbl_config)
            else:
                logger.info("New xbl_config cannot be generated at: %s due to errors!", xbl_config)
                logger.info("Please check errors in the running log to get failure reason!")

        # Generate DCB binary
        elif os.path.isdir(args.xbl_config):
            lcplib.update_dcb_bin(args.xbl_config, lcp_input=args.lcp_bin)
            num_dcb_processed=0
            for dcb_bin in glob.glob(args.xbl_config + '/orig_*_dcb.bin'):
                if os.path.exists(os.path.dirname(dcb_bin)+ os.path.basename(dcb_bin).replace('orig_','/')):
                    num_dcb_processed = num_dcb_processed + 1
                    logger.info("DCB %s is processed", dcb_bin)
                else:
                    logger.info("DCB %s is not processed", dcb_bin)
            logger.info("%d DCB generated at: %s", num_dcb_processed, args.xbl_config)
        else:
            logger.info("")
            logger.info("Unrecognized input: %s", args.xbl_config)

    logger.info("")
    logger.info("----------  Finish LCP command")    

if __name__ == "__main__":
    main()

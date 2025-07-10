#! /usr/bin/env python
from __future__  import print_function
import os
import re
import zlib
import sys

import traceback

from voltage_plan_parser import *
from functools import reduce

__all__ = ['VersionedVoltagePlan', 'get_voltage_plan']


def error(msg):
    print(msg)
    sys.exit(1)

def railValueSet(value, rail):
    value1 = value.split('/')
    for i in range(len(value1)):
        value2 = value1[i].strip().split(':')
        if rail.lower() == value2[0].lower():
            return int(value2[1])
        else:
            value = 0
    return 0

class ParserDict(dict):
    def __init__(self, orig):
        dict.__init__(self, orig)

    def __getitem__(self, args):
        key = args
        rtnType = str

        if isinstance(args, tuple):
            key = args[0]
            rtnType = args[1]
            assert isinstance(rtnType, type)

        val = dict.__getitem__(self, key)
        if val is None or val.lower() in ['n/a', 'tbd']:
            return (None, 0)[rtnType in [int, float]]

        if rtnType is int:
            return int(float(val))
        else:
            return rtnType(val)

class CprRevCfg:
    def __init__(self, min=0, max=0):
        self.min = min
        self.max = max

    def __repr__(self):
        return str(self)

    def __str__(self):
        return str(self.__dict__)

    def setRevRange(self, min, max):
        self.min = min
        self.max = max
        
    def setVpIdRange(self, min, max):
        print ('setVpIdRange vpidmin:', min)
        print ('setVpIdRange vpidmax:', max)
        self.vpidmin = min
        self.vpidmax = max
        
        #self.vpidmin.append(min)
        #self.vpidmax.append(max)

def formatMode(rawMode):
    # CamelCase to underscores
    rawMode = rawMode.replace(' ', '_')
    mode    = re.sub('([a-z0-9])([A-Z])', r'\1_\2', rawMode).upper()
    return mode


class VersionedVoltagePlan:
    def __init__(self, rail, foundry, min, max):
        self.foundry = foundry
        self.rail = rail
        self.min = min
        self.max = max
        self.modes = []
        self.modeCprRevMax = None
        self.tempPoints = []
        self.kvs = []
     
    class QutoientParams(CprRevCfg):
        def __init__(self, ro=None, quot=None):
            self.ro = ro
            self.quot = quot
           
        def __hash__(self):
            h = 0
            for v in list(self.__dict__.values()):
                h = zlib.crc32(str(v).encode(), h)
            return h

        def __repr__(self):
            return str(self)

        def __str__(self):
            #return ' [{ro:2}, {quot:4}]'.format(**self.__dict__)
            return '\n            [%s]' % ','.join(['(%s: %10s)' % (key,str(val)) for key,val in self.__dict__.items()])

        def compare(self, q):
            if self.ro == q.ro and self.quot == q.quot:
                return True
            else:
                return False

    class KvParams:
        def __init__(self, ro=None, kv=None):
            self.ro = ro
            self.kv = kv

        def __hash__(self):
            h = 0
            for v in list(self.__dict__.values()):
                h = zlib.crc32(str(v).encode(), h)
            return h

        def __repr__(self):
            return str(self)

        def __str__(self):
            return '\n            [%s]' % ','.join(['(%s: %10s)' % (key,str(val)) for key,val in list(self.__dict__.items())])

    class ModeParams:
        def __init__(self):
            self.revMax = None
            self.virtualCorners = []
            self.enabled = []
            self.freq = []
            self.interplEnabled = []
            self.ceiling = []
            self.floor = []
            self.margins = []
            self.fuses = [None, None, None, None, None] #volt, quot, rosel, quotOffset, voltOffset
            self.fuseRef = 0
            self.quotients = []
            self.tempBands = []

        def __repr__(self):
            return str(self)

        def __str__(self):
            #qStr = (str(q) for q in self.quotients)
            return '\n        [%s]' % ', '.join(['(%s: %s)' % (key,str(val)) for key,val in list(self.__dict__.items())])
            #return 'e [{enabled:<5}] fq [{freq:<7}] c [{ceiling:<7}] f [{floor:<7}] m [{margins:<4}] fr [{fuseRef:<7}] ' + \
            #        '\n\t\t\t\tf {fuses:15}'.format(**self.__dict__) + \
            #        '\n\t\t\t\tro,q,kv ' + ''.join(qStr) + '\n'

        def __hash__(self):
            h = 0
            for v in list(self.__dict__.values()):
                if isinstance(v, list):
                    for x in v:
                        h = zlib.crc32(str(x).encode(), h)
                else:
                    h = zlib.crc32(str(v).encode(), h)
            return h

    def getModes(self, row, create=False, mode=''):
        rawMode = mode

        if not rawMode:
            rawMode = row['Mode']

        if rawMode.lower() == 'binning': return []

        mode = formatMode(rawMode)

        rtn = [m[1] for m in self.modes if m[0] == mode]

        if create and len(rtn) == 0:
            params = VersionedVoltagePlan.ModeParams()
            self.modes.append((mode, params))
            rtn = [params]

        if rawMode == '*':
            return [m[1] for m in self.modes]

        return rtn

    def __hash__(self):
        h = 0
        for v in list(self.__dict__.values()):
            h = zlib.crc32(str(v), h)
        return h

    def __repr__(self):
        return str(self)

    def __str__(self):
        return '\n\n=== {rail} {foundry} {min} {max} TempPoints:{tempPoints} ===\n\n'.format(**self.__dict__) +\
                '    ' + '\n\n    '.join(['{0:11} {1}'.format(m, str(v)) for m, v in self.modes])


def getrows(sheet):
    headers = [c.value for c in list(sheet.rows)[0] if c.value]
    for row in list(sheet.rows)[1:]:
        data = []
        for c in row:
            if c.value is not None:
                val = None
                try:
                    val = str(c.value)
                except:
                    val = None
                data.append(val)
            else:
                data.append(None)
        if reduce(lambda acc, x: acc and x == str(None), data, True):
            continue
        d = dict(list(zip(headers, data)))
        yield d

class Margin(CprRevCfg):
    def __init__(self, ol, cl, age, slt, f2c, rmax, rmin):
        self.ol   = ol
        self.cl   = cl
        self.age  = age
        self.slt  = slt
        self.fToC = f2c        
        self.vpidmin = 0
        self.vpidmax = 0
        self.max  = rmax
        self.min  = rmin

    def compare(self, m):
        if self.ol == m.ol and self.cl == m.cl and\
           self.age == m.age and self.slt == m.slt and\
           self.fToC == m.fToC and\
           self.min == m.min and self.max == m.max:
            return True
        else:
            return False


class FuseRef(CprRevCfg):
    def __init__(self, fref):
        self.fref = fref

    def compare(self, f):
        if self.fref == f.fref:
            return True
        else:
            return False


class VoltagePlanParser:

    def __init__(self, img, target):
        self.img = img.upper() # xbl, rpm, mpss
        self.target = target # 8998, 9x55, etc
        self.rails = []
        self.controller_rails = []
        self.results = { }
        self.hashval = ''

    def __parse_sensor_ids(self, sensor_ids):
        sensors = []
        if sensor_ids and sensor_ids.lower() not in ['na', 'n/a']:
            for sensor in sensor_ids.split(','):
                sensor = sensor.strip()
                if '-' in sensor:
                    start, end = sensor.split('-')
                    sensors.extend(list(range(int(start), int(end)+1)))
                elif '..' in sensor:
                    start, end = sensor.split('..')
                    sensors.extend(list(range(int(start), int(end)+1)))
                elif 'to' in sensor:
                    start, end = sensor.split('to')
                    sensors.extend(list(range(int(start), int(end)+1)))
                elif sensor:
                    sensors.append(int(sensor))
        return sensors

    def __parse_worksheet_enablement(self, wb):
        hdl = Enablement(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            raise Exception('"%s" worksheet does not exist' % hdl.SHEET_NAME)

        enablements = {}
        misc = None

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            hdl.parse(row)

            #
            # skip other images
            #
            if hdl.img != self.img:
                continue

            self.rails.append(hdl.rail)

            if hdl.rail not in enablements:
                enablements[hdl.rail] = []

            if hdl.foundry == '*':
                hdl.foundry = 'ANY'

            if hdl.version == '*':
                version_min = '0.0'
                version_max = '255.255'
            else:
                version_min = hdl.version.replace('x', '0')
                version_max = hdl.version.replace('x', '255')

            enab = {
                'foundry'            : hdl.foundry,
                'version_min'        : version_min,
                'version_max'        : version_max,
                'control_mode'       : 'CPR_INIT_' + hdl.control_mode,
                'step_size_uv'       : hdl.step_size_uv,
                'fuse_multiplier_uv' : hdl.fuse_multiplier_uv,
                'thermal_adjustments': hdl.thermal_adjustments,
                'interrupt'          : hdl.interrupt,
                'settle_modes'       : hdl.settle_modes,
                'rev_fuse_info'      : self.__parse_fuse_info(list(zip(hdl.rev_fuse_addr, hdl.rev_fuse_bits))),
                'enable'             : hdl.enable,
            }

            enablements[hdl.rail].append(enab)

            if misc is None:
                fuse_info = enab['rev_fuse_info'][0]
                misc = {
                    'cpr_rev_fuse' : {
                        'address': fuse_info.get('fuse_address'),
                        'offset' : fuse_info.get('fuse_offset'),
                        'mask'   : fuse_info.get('fuse_mask'),
                        },
                }

        self.results['enablements'] = enablements
        self.results['misc'] = misc

    def __parse_worksheet_controllers(self, wb):
        hdl = Controllers(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            raise Exception('"%s" worksheet does not exist' % hdl.SHEET_NAME)

        controllers = {}

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            hdl.parse(row)

            #
            # skip other images
            #
            if hdl.img != self.img:
                continue

            #
            # Store common controller settings
            #
            if hdl.controller_name not in controllers:
                controllers[hdl.controller_name] = {
                    'base'           : hdl.base,
                    'type'           : 'CPR_CONTROLLER_TYPE_' + hdl.type,
                    'ref_clk'        : hdl.ref_clk,
                    'ahb_clk'        : hdl.ahb_clk,
                    'num_sensors'    : hdl.num_sensors,
                    'mask_sensors'   : self.__parse_sensor_ids(hdl.mask_sensors),
                    'bypass_sensors' : self.__parse_sensor_ids(hdl.bypass_sensors),

                    'num_threads'    : hdl.num_threads,
                    'threads'        : {},
                }

            controllers[hdl.controller_name]['threads'][hdl.rail] = {
                    'thread'  : hdl.thread_id,
                    'sensors' : self.__parse_sensor_ids(hdl.thread_sensors),
                    'type'    : 'CPR_CONTROLLER_TYPE_' + hdl.type,
                }
            self.controller_rails.append(hdl.rail)

            #
            # Store controller and thread ID info in enablement config info to help
            # look up controller and thread ID by rail name easily later
            #
            for enab_rail, enabs in list(self.results['enablements'].items()):
                if enab_rail != hdl.rail:
                    continue
                for enab in enabs:
                    enab['controller_name'] = hdl.controller_name
                    enab['thread_id']       = hdl.thread_id

        self.results['controllers'] = controllers

    def __find_rails_for_row(self, row, create=False):
        COL_NAME_RAIL       = 'Voltage Rail'
        COL_NAME_CLK_DOMAIN = 'Clock Domain'
        COL_NAME_FOUNDRY    = 'Foundry'
        COL_NAME_CHIP_VER   = 'Chip Version'
        COL_NAME_CPR_REV    = 'CPR Rev'

        rail    = row[COL_NAME_RAIL]
        domain  = row.get(COL_NAME_CLK_DOMAIN, '*')
        foundry = row[COL_NAME_FOUNDRY]
        version = row[COL_NAME_CHIP_VER]
        rev     = row.get(COL_NAME_CPR_REV, '*')

        if domain not in [None, '*', 'GPU']:
            rail += '_' + domain

        if rev == 'n/a':
            rev = '*'

        if foundry == '*':
            foundry = 'ANY'

        if self.rails or not rail:
            if not rail or not reduce(lambda acc, x: acc or x.startswith(rail), self.rails, False):
                return []

        if not create and version == '*':
            rtn = []
            for key in self.results:
                if type(key) is not tuple:
                    continue
                r, f, min, max = key
                if r == rail and f == foundry:
                    rtn.append(self.results[key])
            return rtn
        else:
            min = version.replace('x', '0')
            max = version.replace('x', '255')

            if version == '*':
                min = '0.0'
                max = '255.255'

            key = (rail, foundry, str(float(min)), str(float(max)))
            if create:
                self.results[key] = self.results.get(key, VersionedVoltagePlan(*key))

            try:
                return [self.results[key]]
            except KeyError:
                return []

    def __parse_worksheet_voltage_settings(self, wb):
        import fuses

        hdl = VoltageSettings(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            for vvp in self.__find_rails_for_row(row, True):
                hdl.parse(row)

                # We only allow one voltage settings per chip and store the voltage settings for the latest CPR Rev
                if vvp.modeCprRevMax is None or hdl.revMax != vvp.modeCprRevMax:
                    vvp.modeCprRevMax = hdl.revMax
                    vvp.modes = []

                # We are assuming freqs are sorted low to high as we iterate, so fmax is always last...
                for mode in vvp.getModes(row, True):
                    mode.fuseRef = hdl.fuseRef

                    if hdl.virtualCorner not in mode.virtualCorners:
                        mode.virtualCorners.append(hdl.virtualCorner)
                        mode.enabled.append(hdl.enabled)
                        mode.freq.append(hdl.freq) # to kHz
                        mode.ceiling.append(hdl.ceiling) # to uV
                        mode.floor.append(hdl.floor)
                        mode.interplEnabled.append(hdl.interplEnabled)
                    else:
                        mode.enabled[-1] = hdl.enabled
                        mode.freq[-1]    = hdl.freq # to kHz
                        mode.ceiling[-1] = hdl.ceiling # to uV
                        mode.floor[-1]   = hdl.floor
                        mode.interplEnabled[-1] = hdl.interplEnabled

                    if hdl.fuseval and hdl.fuseval != 'TBD':
                        mode.fuses[0] = fuses.get_fuses(hdl.fuseval)[0]
                        if not mode.fuses[0]:
                            error('Could not find fuse registers for fuse value: ' + hdl.fuseval)

    def __parse_worksheet_cpr_fused_corner_adjustment(self, wb):
        
        sheet = wb['CPR Fused Corner Adjustment']        
        headers = [c.value for c in list(sheet.rows)[0] if c.value]
        vdelta = False
        vpid = False
        if 'VP ID' in headers:
            vpid = True

        import fuses

        hdl = FusedCornerAdjustment(self.target, vpid = vpid)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            for vvp in self.__find_rails_for_row(row):
                hdl.parse(row)

                for mode in vvp.getModes(row):
                    curr = Margin(hdl.ol, hdl.cl, hdl.age, hdl.slt, hdl.f2c, hdl.revMax, hdl.revMin)

                    if hdl.revMin == '*':
                        curr.setRevRange(0, 255)
                        curr.setVpIdRange(hdl.vpIdMin, hdl.vpIdMax)
                        mode.margins.append(curr)
                    else:
                        if len(mode.margins) == 0 or not mode.margins[-1].compare(curr):
                            curr.setRevRange(hdl.revMin, hdl.revMax)
                            curr.setVpIdRange(hdl.vpIdMin, hdl.vpIdMax)
                            mode.margins.append(curr)
                        else:
                            mode.margins[-1].max = hdl.revMax
                            mode.margins[-1].vpidmax = hdl.vpIdMax
                            
                    if hdl.fuseOffset and hdl.fuseOffset != 'TBD':
                        mode.fuses[4] = fuses.get_fuses(hdl.fuseOffset)[0]
                        if not mode.fuses[4]:
                            error('Could not find fuse registers for fuse value: ' + hdl.fuseOffset)

    def __parse_worksheet_global_target_quotient(self, wb):
        hdl = GlobalTargetQuotient(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            for vvp in self.__find_rails_for_row(row):
                hdl.parse(row)

                if hdl.quotient is None:
                    continue

                q = VersionedVoltagePlan.QutoientParams(hdl.ro, hdl.quotient)

                for mode in vvp.getModes(row):
                    if hdl.revMin == '*':
                        q.setRevRange(0, 255)
                        mode.quotients.append(q)
                    else:
                        if len(mode.quotients) == 0 or not mode.quotients[-1].compare(q):
                            q.setRevRange(hdl.revMin, hdl.revMax)
                            mode.quotients.append(q)
                        else:
                            mode.quotients[-1].max = hdl.revMax


    def __parse_worksheet_kv(self, wb):
        hdl = KV(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            for vvp in self.__find_rails_for_row(row):
                hdl.parse(row)

                hdl.mode = formatMode(hdl.mode)

                if hdl.mode != '*':
                    raise Exception("Core rails does not support different KV values for each mode")

                k = VersionedVoltagePlan.KvParams(hdl.ro, hdl.kv)
                vvp.kvs.append(k)

    def __parse_fuse_info(self, fuse_addrs_bits_pair):
        
        fuse_info = [] 
        fuse_address= 'FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (%s & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1))'
        #fuse region is moved to range4 except waipio and palima
        if   self.target.lower() in ['waipio','palima'] :
              fuse_address= 'QFPROM_CORR_REG_BASE | (%s & (QFPROM_CORR_REG_BASE_SIZE - 1))'

        for fuse_addr, fuse_bits in fuse_addrs_bits_pair:
            for bits in fuse_bits.split(','):
                bits = [int(n) if int(n) < 32 else int(n) - 32 for n in bits.split(':')]
                msb = bits[0]
                lsb = bits[len(bits)-1]
                offset = lsb
                mask = ' | '.join(['(1<<%d)' % n for n in range(msb, lsb-1, -1)])
                
                  
                fuse_info.append({
                     
                    'fuse_address' :  fuse_address % fuse_addr,# handle image virtual address
                    'fuse_offset'  : offset,
                    'fuse_mask'    : mask,
                })

        return fuse_info

    def __parse_worksheet_logic_aging(self, wb):
        hdl = LogicAging(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        aging_setting = {}
        rails = set([k[0] for k in list(self.results.keys()) if isinstance(k, tuple)])
        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):

            hdl.parse(row)

            if hdl.rail is None:
                continue

            #
            # de-aging can be enabled for closed loop rails
            #
            if hdl.rail not in self.controller_rails:
                continue

            if hdl.enab and (not rails or hdl.rail in rails):

                # These data must exist
                if hdl.fuse_addrs is None or hdl.fuse_bits is None:
                    continue

                aging_setting[hdl.rail] = {
                    'cpr_rev_min_to_run' : hdl.cpr_rev_min_to_run,
                    'mode'               : hdl.mode,
                    'sensor_id'          : hdl.sensor_id,
                    'kv_x100'            : hdl.kv_x100,
                    'scaling_factor_x10' : hdl.scaling_factor_x10,
                    'margin_limit'       : hdl.margin_limit,
                    'bypass_sensor_ids'  : self.__parse_sensor_ids(hdl.bypass_sensors),
                    'fuse_info'          : self.__parse_fuse_info(list(zip(hdl.fuse_addrs, hdl.fuse_bits))),
                    'fuse_packing_factor': hdl.packing_factor,
                }

        self.results['aging'] = aging_setting

    def __parse_worksheet_sw_settings(self, wb):
        hdl = SwSettings(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        sw_settings = {}
        rails = set([k[0] for k in list(self.results.keys()) if isinstance(k, tuple)])
        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            for rail in self.controller_rails:
                if not hdl.isSupported(rail, row):
                    continue

                hdl.parse(rail, row)

                if hdl.field is None:
                    break

                if hdl.field == 'CPR_STEP_QUOT_INIT.STEP_QUOT_INIT_MAX':
                    hdl.field = 'step_quot_max'
                    if hdl.comment is not None:
                        m = re.match(r'%s:\s*(\d+)' % rail, hdl.comment)
                        if m:
                            hdl.value = int(m.groups()[0])
                    else:
                        hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_STEP_QUOT_INIT.STEP_QUOT_INIT_MIN':
                    hdl.field = 'step_quot_min'
                    if hdl.comment is not None:
                        m = re.match(r'%s:\s*(\d+)' % rail, hdl.comment)
                        if m:
                            hdl.value = int(m.groups()[0])
                    else:
                        hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_TIMER_AUTO_CONT.AUTO_CONT_INTERVAL':
                    hdl.field = 'auto_cont_interval'
                    hdl.value = int(re.match(r'(\d+)',hdl.value).groups()[0])
                elif hdl.field == 'CPR_THRESHOLD_t.UP_THRESHOLD':
                    hdl.field = 'up_thresh'
                    hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_THRESHOLD_t.DN_THRESHOLD':
                    hdl.field = 'dn_thresh'
                    hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_THRESHOLD_t.CONSECUTIVE_UP':
                    hdl.field = 'consec_up'
                    hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_THRESHOLD_t.CONSECUTIVE_DN':
                    hdl.field = 'consec_dn'
                    hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_FSM_CTL.IDLE_CLOCKS':
                    hdl.field = 'idle_clocks'
                    hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_TIMER_CLAMP.CLAMP_TIMER_INTERVAL':
                    hdl.field = 'clamp_timer_interval'
                    if hdl.value and hdl.value.isdigit():
                        hdl.value = int(hdl.value)
                    else:
                        hdl.value = 0
                elif hdl.field == 'CPR_SENSOR_BYPASS_WRITEn.SENSOR_BYPASS':
                    # Using bypass sensors defined in CPR Enabalements
                    continue
                elif hdl.field == 'CPR_SENSOR_MASK_WRITEn.SENSOR_MASK':
                    # Using mask sensors defined in CPR Enabalements
                    continue
                elif hdl.field == 'CPR_FSM_CTL.COUNT_REPEAT':
                    hdl.field = 'count_repeat'
                    hdl.value = int(hdl.value)
                elif hdl.field == 'CPR_FSM_CTL.COUNT_MODE':
                    hdl.field = 'count_mode'
                    hdl.value = int(hdl.value)
                elif hdl.field.startswith('GCNT'):
                    # Same info as Global Target Quotient
                    # If Quotient is zero, GCNT=0 to disable RO
                    # If Quotient is non-zero, GCNT=19 to enable RO
                    continue
                elif hdl.field.startswith('TEMP_SENSOR_ID_START'):
                    if hdl.value is None:
                        hdl.value = 0
                    elif hdl.value.isdigit():
                        hdl.value = int(hdl.value)
                    else:
                        m = re.match(r'%s:\s*(\d+)' % rail.lower(), hdl.value.lower())
                        if m:
                            hdl.value = int(m.groups()[0])
                        else:
                            hdl.value = 0
                    hdl.field = 'temp_sensor_start_id'
                elif hdl.field.startswith('TEMP_SENSOR_ID_END'):
                    if hdl.value is None:
                        hdl.value = 0
                    elif hdl.value.isdigit():
                        hdl.value = int(hdl.value)
                    else:
                        m = re.match(r'%s:\s*(\d+)' % rail.lower(), hdl.value.lower())
                        if m:
                            hdl.value = int(m.groups()[0])
                        else:
                            hdl.value = 0
                    hdl.field = 'temp_sensor_end_id'
                else:
                    pass

                if rail not in sw_settings:
                    sw_settings[rail] = {}

                sw_settings[rail][hdl.field] = hdl.value

        self.results['sw_settings'] = sw_settings

    def __parse_worksheet_temperature_point(self, wb):
        hdl = TemperaturePoint(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            for vvp in self.__find_rails_for_row(row):
                hdl.parse(row)
                vvp.tempPoints.append((hdl.point, hdl.tempThresh))

    def __parse_worksheet_temperature_adjustment(self, wb):
        hdl = TemperatureAdjustment(self.target)

        if not hdl.SHEET_NAME in wb.sheetnames:
            print('Warning: "%s" worksheet does not exist' % hdl.SHEET_NAME)
            return

        for row in map(ParserDict, getrows(wb[hdl.SHEET_NAME])):
            for vvp in self.__find_rails_for_row(row):
                hdl.parse(row)

                for mode in vvp.getModes(row, mode=hdl.mode):
                    step_size        = self.results['enablements'][hdl.rail][0]['step_size_uv']
                    temp_margin_step = hdl.temp_margin_uv / step_size
                    mode.tempBands.append((hdl.temp_band, temp_margin_step))

    def __calculate_hash_value(self, wb):
        import hashlib

        #
        # We cannot simply calculate hash on excel file since data
        # can be different due to any styling/format change even though
        # all cell values are same.
        # Extract all cell values and calculate hash value.
        #
        md5 = hashlib.md5()
        for sheet in wb.worksheets:
            for row in sheet.rows:
                for c in row:
                    if isinstance(c.value, str):
                        md5.update(c.value.encode('utf-8'))
                    elif isinstance(c.value, int):
                        md5.update(c.value.to_bytes(4,'little', signed=True))

        self.hashval = md5.hexdigest().upper()

    def parse_voltage_plan(self, file):
        from openpyxl import load_workbook

        wb = load_workbook(filename=file, data_only=True)

        self.__calculate_hash_value(wb)

        #
        # First detect what rails are assigned to the image.
        #
        self.__parse_worksheet_enablement(wb)

        #
        # Then, collect Voltage Plan for the rails
        #
        self.__parse_worksheet_controllers(wb)
        self.__parse_worksheet_voltage_settings(wb)
        self.__parse_worksheet_cpr_fused_corner_adjustment(wb)
        self.__parse_worksheet_global_target_quotient(wb)
        self.__parse_worksheet_kv(wb)
        self.__parse_worksheet_logic_aging(wb)
        self.__parse_worksheet_sw_settings(wb)
        self.__parse_worksheet_temperature_point(wb)
        self.__parse_worksheet_temperature_adjustment(wb)

        return self.results, self.hashval



def get_voltage_plan(img, target, file):
    import warnings

    warnings.simplefilter('ignore', UserWarning)

    vvp = VoltagePlanParser(img, target)
    return vvp.parse_voltage_plan(file)


if __name__ == "__main__":
    img    = sys.argv[1] # 'XBL', 'RPM', 'MPSS'
    target = sys.argv[2] # 8998

    this_script_dir = os.path.dirname(os.path.abspath(__file__))

    fuse_dir = os.sep.join([this_script_dir,'..','target', target])
    pyx_dir  = os.sep.join([this_script_dir,'openpyxl-2.5.4-py2.7.egg'])

    # add scripts path
    sys.path.append(fuse_dir)
    sys.path.append(pyx_dir)

    file_path = os.sep.join([this_script_dir,'..','target',target,'Voltage_Plan_%s.xlsx' % target])

    vp, hashval = get_voltage_plan(img, target, file_path)

    for k in vp:
        print(k, vp[k])
        print()

    print()
    print('Hash Value:',hashval)


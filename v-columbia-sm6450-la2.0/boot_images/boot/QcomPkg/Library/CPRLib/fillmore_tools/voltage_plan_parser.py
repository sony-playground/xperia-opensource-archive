from __future__  import print_function
import re

def parseCprRev(val):
    if val is not None:
        val = val.strip()
    if val in [None, '*']:
        return '*','*'
    elif val.isdigit():
        return int(val),int(val)
    elif '-' in val: # range
        revMin, revMax = [int(v) for v in val.split('-')]
        return revMin, revMax
    elif '~' in val: # range
        revMin, revMax = [int(v) for v in val.split('~')]
        return revMin, revMax
    elif ',' in val: # range
        revs = sorted([int(v) for v in val.split(',')])
        return revs[0], revs[-1]
    elif re.match(r'>=\s*\d+', val):
        m = re.match(r'>=\s*(?P<rev_min>\d+)', val)
        revMin = m.group('rev_min')
        return revMin, 255
    elif re.match(r'>\s*\d+', val):
        m = re.match(r'>\s*(?P<rev_min>\d+)', val)
        revMin = m.group('rev_min') + 1
        return revMin, 255
    else:
        raise Exception('Unsupported format for CPR Rev: %s' % val)

def parseVpId(val):
    if val is not None:
        val = val.strip()
    if val in [None, '*']:
        return '*','*'
    elif val.isdigit():
        return int(val),int(val)
    elif '-' in val: # range
        vpIdMin, vpIdMax = [int(v) for v in val.split('-')]
        return vpIdMin, vpIdMax
    elif '~' in val: # range
        vpIdMin, vpIdMax = [int(v) for v in val.split('~')]
        return vpIdMin, vpIdMax
    elif ',' in val: # range
        ids = sorted([int(v) for v in val.split(',')])
        return ids[0], ids[-1]
    elif re.match(r'>=\s*\d+', val):
        m = re.match(r'>=\s*(?P<vpId_min>\d+)', val)
        vpIdMin = m.group('vpId_min')
        return vpIdMin, 255
    elif re.match(r'>\s*\d+', val):
        m = re.match(r'>\s*(?P<vpId_min>\d+)', val)
        vpIdMin = m.group('vpId_min') + 1
        return vpIdMin, 255
    else:
        raise Exception('Unsupported format for VP ID: %s' % val)

class VoltageSettings:
    COMMON_DEFS = {
        'SHEET_NAME'              : 'Voltage Settings',
        'COL_NAME_ENAB'           : 'Enable?',
        'COL_NAME_FREQ'           : 'Frequency (MHz)',
        'COL_NAME_CEILING'        : 'CPR Ceiling (Initial Voltage for Interpolation Disabled Case) (mV)  ',
        'COL_NAME_FLOOR'          : 'CPR Floor  (mV)',
        'COL_NAME_FUSE_REF'       : 'CPR Open Loop Efuse Reference Voltage (mV)',
        'COL_NAME_FUSE_REG'       : 'CPR Open-loop Voltage Fuse',
        'COL_NAME_VIRTUAL_CORNER' : 'Virtual Corner',
        'COL_NAME_INTRPL_ENAB'    : 'CPR Open-loop Voltage Interpolation Allowed?',
        'COL_NAME_CPR_REV'        : 'CPR Rev',
    }
    TARGET_DEFS = {
        '9x55' : {
            'COL_NAME_CEILING' : 'CPR Ceiling  (mV)',
        },
        '9x65' : {
            'COL_NAME_CEILING' : 'CPR Ceiling  (mV)',
        },
        '8998' : {
            'COL_NAME_CEILING' : 'CPR Ceiling (Initial Voltage for Interpolation Disabled Case) (mV)  ',
            'COL_NAME_FUSE_REG': 'CPR Open-loop Voltage Fuse',
        },
        '8997' : {
            'COL_NAME_CEILING' : 'CPR Ceiling  (mV)',
        },
        '660' : {
            'COL_NAME_CEILING' : 'CPR Ceiling (Initial Voltage for Interpolation Disabled Case) (mV)  ',
            'COL_NAME_FUSE_REG': 'CPR Open-loop Voltage Fuse',
        },
        '845' : {
            'COL_NAME_FUSE_REG': 'CPR Open-loop Voltage Fuse',
        },
        '855' : {
            'COL_NAME_FUSE_REG': 'CPR Open-loop Voltage Fuse',
        },
        '6150' : {
            'COL_NAME_FUSE_REG': 'CPR Open-loop Voltage Fuse',
        },
        '1000' : {
            'COL_NAME_FUSE_REG': 'CPR Open-loop Voltage Fuse',
        },
        '8250' : {
            'COL_NAME_FUSE_REG': 'CPR Open-loop Voltage Fuse',
        },
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.enabled = row[self.COL_NAME_ENAB].lower() == 'yes'
        self.freq    = int(row[self.COL_NAME_FREQ, float] * 1000)
        self.ceiling = int(row[self.COL_NAME_CEILING, float] * 1000)
        self.floor   = int(row[self.COL_NAME_FLOOR, float] * 1000)
        self.fuseRef = self.parseFuseRef(row)
        self.fuseval = row[self.COL_NAME_FUSE_REG]
        self.virtualCorner = row.get(self.COL_NAME_VIRTUAL_CORNER,'*')
        self.interplEnabled = self.parseInterpl(row)
        self.revMin,self.revMax = parseCprRev(row.get(self.COL_NAME_CPR_REV,'*'))

    def parseInterpl(self, row):
        orig = val = row[self.COL_NAME_INTRPL_ENAB].lower()
        if val == 'no':
            return 0
        if val == 'yes':
            print('-----------------------------------------------------------------------------')
            print('Voltage Plan Error: Interpolation if enabled, needs to have a Factor with it.')
            print('-----------------------------------------------------------------------------')
        val = re.findall(r'\(([^)]+)\)', row[self.COL_NAME_INTRPL_ENAB])[0].strip(' ')
        if val and val.isdigit():
            return val
        else:
            return 0

    def parseFuseRef(self, row):
        val = row[self.COL_NAME_FUSE_REF]
        if val and (val.isdigit() or re.match(r'\d+\.\d+',val)):
            return int(row[self.COL_NAME_FUSE_REF, float] * 1000)
        else:
            return 0

    def parseVirtualCorner(self, row):
        val = row.get(self.COL_NAME_VIRTUAL_CORNER, None)
        if val in [None, 'n/a', '*']:
            return '*'
        else:
            return int(val)


class FusedCornerAdjustment:
    COMMON_DEFS = {
        'SHEET_NAME'                : 'CPR Fused Corner Adjustment',
        'COL_NAME_CPR_REV'          : 'CPR Rev',
        'COL_NAME_OL_ADJ_WO_AGING'  : 'CPR Open Loop Voltage Adjustment without de-aging (mV)',
        'COL_NAME_CL_ADJ_WO_AGING'  : 'CPR Closed Loop Voltage Adjustment without de-aging (mV)',
        'COL_NAME_MAX_F2C_ADJ'      : 'Max Floor To Ceil Range Constant (mV)',
        'COL_NAME_FUSE_OFFSET'      : 'Fuse Offset',
    }
    TARGET_DEFS = {
        '9x55': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range (mV)',
        },
        '9x65': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range (mV)',
        },
        'waipio': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_AGING_OFFSET': 'Aging Offset (mV)',
            'COL_NAME_SLT_OFFSET'  : 'SLT Offset (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range Constant (mV)',
            'COL_NAME_FUSE_OFFSET' : 'Fuse Offset',
        },
	'palima': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_AGING_OFFSET': 'Aging Offset (mV)',
            'COL_NAME_SLT_OFFSET'  : 'SLT Offset (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range Constant (mV)',
            'COL_NAME_FUSE_OFFSET' : 'Fuse Offset',
        },
        'kailua': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_AGING_OFFSET': 'Aging Offset (mV)',
            'COL_NAME_SLT_OFFSET'  : 'SLT Offset (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range Constant (mV)',
            'COL_NAME_FUSE_OFFSET' : 'Fuse Offset',
        },
		'aurora': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_AGING_OFFSET': 'Aging Offset (mV)',
            'COL_NAME_SLT_OFFSET'  : 'SLT Offset (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range Constant (mV)',
            'COL_NAME_FUSE_OFFSET' : 'Fuse Offset',
        },
        'fillmore': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_AGING_OFFSET': 'Aging Offset (mV)',
            'COL_NAME_SLT_OFFSET'  : 'SLT Offset (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range Constant (mV)',
            'COL_NAME_FUSE_OFFSET' : 'Fuse Offset',
        },
		'netrani': {
            'COL_NAME_OL_ADJ'      : 'CPR Open Loop Voltage Adjustment (mV)',
            'COL_NAME_CL_ADJ'      : 'CPR Closed Loop Voltage Adjustment (mV)',
            'COL_NAME_AGING_OFFSET': 'Aging Offset (mV)',
            'COL_NAME_SLT_OFFSET'  : 'SLT Offset (mV)',
            'COL_NAME_MAX_F2C_ADJ' : 'Max Floor To Ceil Range Constant (mV)',
            'COL_NAME_FUSE_OFFSET' : 'Fuse Offset',
		},
    }

    def __init__(self, target,vpid=False):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))
        if vpid:
            self.__dict__.update( {'COL_NAME_VP_ID' : 'VP ID'})
        
    def parse(self, row):
        self.revMin,self.revMax = parseCprRev(row[self.COL_NAME_CPR_REV])

        if  hasattr(self, 'COL_NAME_VP_ID'):
            
            self.vpIdMin,self.vpIdMax = parseVpId(row[self.COL_NAME_VP_ID])
        else:
            self.vpIdMin = 0
            self.vpIdMax = 0 

        self.ol         = self.parseOpenLoopMargin(row)
        self.cl         = self.parseClosedLoopMargin(row)
        self.age        = self.parseAgingOffset(row) * 1000
        self.slt        = self.parseSltOffset(row) * 1000
        self.f2c        = 0 if row[self.COL_NAME_MAX_F2C_ADJ] in [None, 'n/a'] else int(row[self.COL_NAME_MAX_F2C_ADJ]) * 1000
        self.fuseOffset = None if row[self.COL_NAME_FUSE_OFFSET] in [None, 'n/a'] else row[self.COL_NAME_FUSE_OFFSET]

    def parseOpenLoopMargin(self, row):
        margin = 0

        if hasattr(self, 'COL_NAME_OL_ADJ'):
            margin = row[self.COL_NAME_OL_ADJ, int] * 1000
        elif hasattr(self, 'COL_NAME_OL_ADJ_WO_AGING'):
            if row[self.COL_NAME_OL_ADJ_W_AGING] not in [None, 'n/a']:
                margin = row[self.COL_NAME_OL_ADJ_W_AGING, int] * 1000
            else:
                margin = row[self.COL_NAME_OL_ADJ_WO_AGING, int] * 1000

        return margin

    def parseClosedLoopMargin(self, row):
        margin = 0

        if hasattr(self, 'COL_NAME_CL_ADJ'):
            margin = row[self.COL_NAME_CL_ADJ, int] * 1000
        elif hasattr(self, 'COL_NAME_CL_ADJ_W_AGING'):
            if row[self.COL_NAME_CL_ADJ_W_AGING] not in [None, 'n/a']:
                margin = row[self.COL_NAME_CL_ADJ_W_AGING, int] * 1000
            else:
                margin = row[self.COL_NAME_CL_ADJ_WO_AGING, int] * 1000

        return margin

    def parseAgingOffset(self, row):
        if hasattr(self, 'COL_NAME_AGING_OFFSET'):
            return 0 if row[self.COL_NAME_AGING_OFFSET] in [None, 'n/a'] else \
                    int(row[self.COL_NAME_AGING_OFFSET])
        return 0


    def parseSltOffset(self, row):

        if hasattr(self, 'COL_NAME_SLT_OFFSET'):
            return 0 if row[self.COL_NAME_SLT_OFFSET] in [None, 'n/a'] else \
                    int(row[self.COL_NAME_SLT_OFFSET])
        return 0


class GlobalTargetQuotient:
    COMMON_DEFS = {
        'SHEET_NAME'        : 'Global Target Quotient',
        'COL_NAME_RO'       : 'RO',
        'COL_NAME_QUOTIENT' : 'CPR Quotient',
        'COL_NAME_CPR_REV'  : 'CPR Rev',
    }
    TARGET_DEFS = {
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.ro       = None if row[self.COL_NAME_RO] is None else int(row[self.COL_NAME_RO])
        self.quotient = None if row[self.COL_NAME_QUOTIENT] is None else int(float(row[self.COL_NAME_QUOTIENT]))
        self.revMin,self.revMax = parseCprRev(row.get(self.COL_NAME_CPR_REV,'*'))

class KV:
    COMMON_DEFS = {
        'SHEET_NAME'    : 'KV',
        'COL_NAME_RO'   : 'RO',
        'COL_NAME_KV'   : 'KV',
        'COL_NAME_MODE' : 'Mode',
    }
    TARGET_DEFS = {
        '9x55': {
            'COL_NAME_KV' : 'CPR Quotient',
        },
        '9x65': {
            'COL_NAME_KV' : 'CPR Quotient',
        },
        '8998': {
            'COL_NAME_KV' : 'KV',
        },
        '8997': {
            'COL_NAME_KV' : 'CPR Quotient',
        },
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.ro   = row[self.COL_NAME_RO, int]
        self.kv   = int(row[self.COL_NAME_KV, float] * 100)
        self.mode = row[self.COL_NAME_MODE]



class LogicAging:
    COMMON_DEFS = {
        'SHEET_NAME'                : 'Logic Aging',
        'COL_NAME_RAIL'             : 'Voltage Rail',
        'COL_NAME_ENAB'             : 'CPR Aging Enabled',
        'COL_NAME_MODE'             : 'Mode to run aging',
        'COL_NAME_SENSOR_ID'        : 'Sensor ID for aging',
        'COL_NAME_BYPASS_SENSOR_ID' : 'Bypass Sensor ID',
        'COL_NAME_KV'               : 'AGE RO Kv',
        'COL_NAME_SCALING_FACTOR'   : 'Derate Scaling Factor (for all modes)',
        'COL_NAME_MARGIN_LIMIT'     : 'Max Age Compensation (mV)',
        'COL_NAME_FUSE_ADDR'        : 'Register Address',
        'COL_NAME_FUSE_BITS'        : 'Register Bits (MSB=sign bit)',
        'COL_NAME_PACKING_FACTOR'   : 'Packing Factor',
    }
    TARGET_DEFS = {
        '8998' : {
            'COL_NAME_MARGIN_LIMIT'       : 'Max Age Compensation [SW] (mV)',
            'COL_NAME_CPR_REV_MIN_TO_RUN' : 'CPR Rev to run aging',
        },
        '855' : {
            'COL_NAME_CPR_REV_MIN_TO_RUN' : 'CPR Rev to run aging',
        },
        '1000' : {
            'COL_NAME_CPR_REV_MIN_TO_RUN' : 'CPR Rev to run aging',
        },
        '8250' : {
            'COL_NAME_CPR_REV_MIN_TO_RUN' : 'CPR Rev to run aging',
        },
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.rail               = row[self.COL_NAME_RAIL]
        self.enab               = False if row[self.COL_NAME_ENAB] is None else row[self.COL_NAME_ENAB].lower() == 'yes'
        self.mode               = None if row[self.COL_NAME_MODE] is None else row[self.COL_NAME_MODE].strip().upper()
        self.sensor_id          = None if row[self.COL_NAME_SENSOR_ID] is None else int(row[self.COL_NAME_SENSOR_ID].strip('#'))
        self.kv_x100            = int(row[self.COL_NAME_KV, float] * 100)
        self.scaling_factor_x10 = self.parseScalingFactor(row)
        self.margin_limit       = self.parseMarginLimit(row)
        self.fuse_addrs         = self.parseFuseAddr(row)
        self.fuse_bits          = self.parseFuseBits(row)
        self.packing_factor     = 1 if row[self.COL_NAME_PACKING_FACTOR] is None else int(row[self.COL_NAME_PACKING_FACTOR].strip('x'))
        self.bypass_sensors     = row[self.COL_NAME_BYPASS_SENSOR_ID]
        if hasattr(self, 'COL_NAME_CPR_REV_MIN_TO_RUN'):
            if row[self.COL_NAME_CPR_REV_MIN_TO_RUN] is None:
                self.cpr_rev_min_to_run = 0
                self.enab = False
            else:
                self.cpr_rev_min_to_run = parseCprRev(row[self.COL_NAME_CPR_REV_MIN_TO_RUN])[0]
                if self.cpr_rev_min_to_run == '*':
                    self.cpr_rev_min_to_run = 0
        else:
            self.cpr_rev_min_to_run = 0

    def parseScalingFactor(self, row):
        if row[self.COL_NAME_SCALING_FACTOR] is None:
            return 1
        elif row[self.COL_NAME_SCALING_FACTOR].isdigit():
            return row[self.COL_NAME_SCALING_FACTOR, int] * 10
        else:
            return int(row[self.COL_NAME_SCALING_FACTOR, float] * 10)

    def parseMarginLimit(self, row):
        if row[self.COL_NAME_MARGIN_LIMIT] is None:
            return 0
        elif row[self.COL_NAME_MARGIN_LIMIT].isdigit():
            return row[self.COL_NAME_MARGIN_LIMIT, int] * 1000
        else:
            return int(row[self.COL_NAME_MARGIN_LIMIT, float] * 1000)

    def parseFuseAddr(self, row):
        return None if row[self.COL_NAME_FUSE_ADDR] is None else \
                [addr.strip(' ,') for addr in row[self.COL_NAME_FUSE_ADDR].split(',')]

    def parseFuseBits(self, row):
        return None if row[self.COL_NAME_FUSE_BITS] is None else \
                [bits.strip(' ,') for bits in row[self.COL_NAME_FUSE_BITS].split(',')]



class SwSettings:
    COMMON_DEFS = {
        'SHEET_NAME'      : 'SW Settings (non-KBSS)',
        'COL_NAME_FIELD'  : 'Field',
        'COL_NAME_VALUE'  : 'Value',
        'COL_NAME_COMMENT': 'Comment',
    }
    TARGET_DEFS = {
        '9x55': {
            'SHEET_NAME' : 'SW Settings (non-HMSS)',
        },
        '9x65': {
            'SHEET_NAME' : 'SW Settings (non-HMSS)',
        },
        '8998': {
            'SHEET_NAME' : 'SW Settings (non-KBSS)',
        },
        '8997': {
            'SHEET_NAME' : 'SW Settings (non-HMSS)',
        },
        '845': {
            'SHEET_NAME' : 'SW Settings (non-KBSS)',
        },
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, rail, row):
        self.field   = row[self.COL_NAME_FIELD]
        if self.COL_NAME_VALUE in row:
            self.value = row[self.COL_NAME_VALUE]
        else:
            self.value = row.get(rail, None)
        self.comment = row[self.COL_NAME_COMMENT]

    def isSupported(self, rail, row):
        if self.COL_NAME_VALUE in row:
            return True
        elif rail in row:
            return True
        else:
            return False


class TemperaturePoint:
    COMMON_DEFS = {
        'SHEET_NAME'           : 'CPR4-h Temperature Point',
        'COL_NAME_TEMP_POINT'  : 'Temperature Point',
        'COL_NAME_TEMP_THRESH' : 'Temperature Threshold ( C )',
    }
    TARGET_DEFS = {
        '845': {
            'SHEET_NAME' : 'CPRh Temperature Point',
        },
        '855': {
            'SHEET_NAME' : 'CPRh Temperature Point',
        },
        '6150': {
            'SHEET_NAME' : 'CPRh Temperature Point',
        },
        '1000': {
            'SHEET_NAME' : 'CPRh Temperature Point',
        },
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.point      = row[self.COL_NAME_TEMP_POINT, int]
        self.tempThresh = row[self.COL_NAME_TEMP_THRESH, int]



class TemperatureAdjustment:
    COMMON_DEFS = {
        'SHEET_NAME'         : 'CPR4-h Temperature Adjustment',
        'COL_NAME_RAIL'      : "Voltage Rail",
        'COL_NAME_MODE'      : 'Virtual Corner/Band  (Explicit Name)',
        'COL_NAME_TEMP_BAND' : 'Temperature Band',
        'COL_NAME_TEMP_ADJ'  : 'Temperature Adjustment (mV)',
    }
    TARGET_DEFS = {
        '845': {
            'SHEET_NAME' : 'CPRh Temperature Adjustment',
        },
        '855': {
            'SHEET_NAME' : 'CPRh Temperature Adjustment',
        },
        '6150': {
            'SHEET_NAME' : 'CPRh Temperature Adjustment',
        },
        '1000': {
            'SHEET_NAME' : 'CPRh Temperature Adjustment',
        },
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.rail           = row[self.COL_NAME_RAIL]
        self.temp_band      = row[self.COL_NAME_TEMP_BAND, int]
        self.temp_margin_uv = row[self.COL_NAME_TEMP_ADJ, int] * 1000 # will be divided by PMIC step size
        self.mode           = re.findall(r'\(([^)]+)\)', row[self.COL_NAME_MODE])[0]



class Enablement:
    COMMON_DEFS = {
        'SHEET_NAME'             : 'CPR Enablements',
        'COL_NAME_IMAGE'         : "Image",
        'COL_NAME_FOUNDRY'       : 'Foundry',
        'COL_NAME_CHIP_VER'      : "Chip Version",
        'COL_NAME_RAIL'          : "Voltage Rail",
        'COL_NAME_CONTROL_MODE'  : "Control Mode",
        'COL_NAME_PMIC_STEP'     : "PMIC Step Size (mV)",
        'COL_NAME_FUSE_MULT'     : "Fuse Multiplier (mV)",
        'COL_NAME_THERM_ADJ'     : "Thermal Adjustments (mV) (Normal, Cool, Cold, Critical Cold)",
        'COL_NAME_IRQ'           : "Interrupt",
        'COL_NAME_SETTLE_MODES'  : "Settle Modes",
        'COL_NAME_REV_FUSE_ADDR' : "CPR Rev Fuse Address",
        'COL_NAME_REV_FUSE_BITS' : "CPR Rev Fuse Bits",
        'COL_NAME_ENABLE'        : "Enable",
    }
    TARGET_DEFS = {
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.img                 = row[self.COL_NAME_IMAGE]
        self.rail                = row[self.COL_NAME_RAIL]
        self.foundry             = row[self.COL_NAME_FOUNDRY]
        self.version             = row[self.COL_NAME_CHIP_VER]
        self.interrupt           = self.parseInterrupt(row)
        self.settle_modes        = self.parseSettleModes(row)
        self.control_mode        = row[self.COL_NAME_CONTROL_MODE]
        self.step_size_uv        = 1000 * row[self.COL_NAME_PMIC_STEP, int]
        self.fuse_multiplier_uv  = 1000 * row[self.COL_NAME_FUSE_MULT, int]
        self.thermal_adjustments = self.parseThermalAdj(row)
        self.rev_fuse_addr       = self.parseFuseAddr(row)
        self.rev_fuse_bits       = self.parseFuseBits(row)
        self.enable              = row[self.COL_NAME_ENABLE].lower() == 'yes'

    def parseInterrupt(self, row):
        return None if row[self.COL_NAME_IRQ] in [None, 'n/a'] else row[self.COL_NAME_IRQ, int]

    def parseSettleModes(self, row):
        return [] if row[self.COL_NAME_SETTLE_MODES] in [None, 'n/a'] else \
                ['CPR_VOLTAGE_MODE_' + re.sub('([a-z0-9])([A-Z])', r'\1_\2', v.strip()).upper() for v in row[self.COL_NAME_SETTLE_MODES].split(',')]

    def parseThermalAdj(self, row):
        return [] if row[self.COL_NAME_THERM_ADJ] in [None, 'n/a'] else \
                [int(v)* 1000 for v in row[self.COL_NAME_THERM_ADJ].split(',')]

    def parseFuseAddr(self, row):
        return None if row[self.COL_NAME_REV_FUSE_ADDR] is None else \
                [addr.strip(' ,') for addr in row[self.COL_NAME_REV_FUSE_ADDR].split(',')]

    def parseFuseBits(self, row):
        return None if row[self.COL_NAME_REV_FUSE_BITS] is None else \
                [bits.strip(' ,') for bits in row[self.COL_NAME_REV_FUSE_BITS].split(',')]


class Controllers:
    COMMON_DEFS = {
        'SHEET_NAME'             : 'CPR Controllers',
        'COL_NAME_IMAGE'         : "Image",
        'COL_NAME_CPR_CONTROLLER': "CPR Controller",
        'COL_NAME_CPR_BASE_ADDR' : "CPR Controller Base Address",
        'COL_NAME_CPR_TYPE'      : "CPR Controller Type",
        'COL_NAME_TOTAL_THREADS' : "Threads on Controller",
        'COL_NAME_THREAD_ID'     : "Thread",
        'COL_NAME_RAIL'          : "Voltage Rail",
        'COL_NAME_TOTAL_SENSORS' : "Sensors on Controller",
        'COL_NAME_SENSORS'       : "Sensors on Thread",
        'COL_NAME_MASK_SENSORS'  : "Mask Sensors on Controller",
        'COL_NAME_BYPSS_SENSORS' : "Bypass Sensors on Controller",
        'COL_NAME_REF_CLK_NAME'  : "ref_clk Name",
        'COL_NAME_AHB_CLK_NAME'  : "ahb_clk Name",
    }
    TARGET_DEFS = {
    }

    def __init__(self, target):
        self.target = target
        self.__dict__.update(**self.COMMON_DEFS)
        self.__dict__.update(**self.TARGET_DEFS.get(target,{}))

    def parse(self, row):
        self.img             = row[self.COL_NAME_IMAGE]
        self.controller_name = row[self.COL_NAME_CPR_CONTROLLER].strip().lower()
        self.base            = hex(int(row[self.COL_NAME_CPR_BASE_ADDR], 16))
        self.type            = row[self.COL_NAME_CPR_TYPE]
        self.num_sensors     = row[self.COL_NAME_TOTAL_SENSORS, int]
        self.mask_sensors    = row[self.COL_NAME_MASK_SENSORS]
        self.bypass_sensors  = row[self.COL_NAME_BYPSS_SENSORS]
        self.num_threads     = row[self.COL_NAME_TOTAL_THREADS, int]
        self.thread_id       = row[self.COL_NAME_THREAD_ID, int]
        self.rail            = row[self.COL_NAME_RAIL]
        self.thread_sensors  = row[self.COL_NAME_SENSORS]
        self.ref_clk         = self.parseRefClk(row)
        self.ahb_clk         = self.parseAhbClk(row)

    def parseRefClk(self, row):
        return None if row[self.COL_NAME_REF_CLK_NAME] in [None, 'n/a'] else row[self.COL_NAME_REF_CLK_NAME]

    def parseAhbClk(self, row):
        return None if row[self.COL_NAME_AHB_CLK_NAME] in [None, 'n/a'] else row[self.COL_NAME_AHB_CLK_NAME]


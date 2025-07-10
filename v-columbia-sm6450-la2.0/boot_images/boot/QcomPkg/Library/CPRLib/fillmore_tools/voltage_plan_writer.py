#! /usr/bin/env python
from __future__  import print_function
import os
import sys
import datetime
import struct
from voltage_plan import *
from functools import reduce

__all__ = ['write_cpr_cfg', 'write_cpr_bin']

destFile = None
debug = False

def writefile(msg):
    if destFile:
      destFile.write(msg.encode())
      destFile.write('\n'.encode())

def filewriter(fHandle, msg, isBin):
    if fHandle:
        if debug and not isBin:
            print(msg)
        if isBin:
            fHandle.write(msg)
        else:
            fHandle.write(format(msg).encode())
            fHandle.write("\n".encode())

###############################################################################
# Margins
###############################################################################
writtenMargins = []
MARGIN_ADJUSTMENT_TEMPLATE = '''
static cpr_margin_cfg {name} = {{
    .count = {count},
    .data = {data}
}};
'''


MARGINS_TEMPLATE = '{{ .vpIdMin = {vpidmin}, .vpIdMax = {vpidmax},.cprRevMin = {min}, .cprRevMax = {max}, .openLoop = {ol:>7}, .closedLoop = {cl:>7}, .agingOffset = {age:>7}, .sltOffset = {slt:>7}, .maxFloorToCeil = {fToC:>6} }}'

written_margins = []
margin_uuids= []

def write_margins(margins):
    global writtenMargins
    marginsDecls = []
    uuid = 0
    margin_list = {}

    if len(margins) == 0:
        return 'NULL'

    for m in margins:
        uuid = abs(reduce(lambda acc,ix: acc + (ix[0]+1)*ix[1], enumerate(m.__dict__.values()), uuid))
        marginsDecls.append(MARGINS_TEMPLATE.format(**m.__dict__))
        for key,val in m.__dict__.items():
            margin_list[key] = val

    margin_found , uuid_exist = False, False

    for written_margin in written_margins:
        if (written_margin["min"] == margin_list["min"] and\
            written_margin["vpidmax"] == margin_list["vpidmax"] and\
            written_margin["max"] == margin_list["max"] and\
            written_margin["ol"] == margin_list["ol"] and\
            written_margin["cl"] == margin_list["cl"] and\
            written_margin["age"] == margin_list["age"] and\
            written_margin["slt"] == margin_list["slt"] and\
            written_margin["fToC"] == margin_list["fToC"] and\
            written_margin["vpidmin"] == margin_list["vpidmin"]
           ):
            margin_found = True
            uuid = written_margin["uuid"]
            break
        elif written_margin["uuid"] == uuid:
            uuid_exist = True

    if not margin_found:
       if uuid_exist:
           while uuid in margin_uuids:
               uuid += 1
       margin_list["uuid"] = uuid
       written_margins.append(margin_list)
       margin_uuids.append(uuid)

    name = 'margins_' + str(uuid)

    formatVals = {
        'name': name,
        'count': len(marginsDecls),
        'data': '(cpr_margin_data[]) { ' + ',\n                                  '.join(marginsDecls) + ' }',
    }

    if name not in writtenMargins:
        writtenMargins.append(name)
        writefile(MARGIN_ADJUSTMENT_TEMPLATE.format(**formatVals))

    return '&' + name

###############################################################################
# Fuses
###############################################################################
writtenFuses = []
FUSE_DATA_TEMPLATE = 'CPR_FUSE_MAPPING({0}, {1})'
INDIVIDUAL_FUSE_CFG_TEMPLATE = '''(cpr_fuse[]) {{ {{.count = {count}, .data = (struct raw_fuse_data[]) {{ {data} }} }} }}'''
FUSE_CFG_TEMPLATE = '''
static cpr_fuse_data  {0} =
{{
    .volt       = {1},
    .quot       = {2},
    .rosel      = {3},
    .quotOffset = {4},
    .voltOffset = {5},
}};
'''


def write_fuses(allFuses):
    global writtenFuses
    uuid = 0
    allfuseparams = []

    if len(allFuses) == 0:
        return 'NULL'

    for fuses in allFuses:
        fuseparams = []

        if not fuses:
            allfuseparams.append('NULL')
            continue

        for f in fuses:
            uuid += hash(f) & (1 << 32) - 1
            fuseparams.append(FUSE_DATA_TEMPLATE.format(*f))

        formatVals = {
            'data': ', '.join(fuseparams),
            'count': len(fuseparams),
        }
        allfuseparams.append(INDIVIDUAL_FUSE_CFG_TEMPLATE.format(**formatVals))

    if len(allfuseparams) > 0:
        name = 'fuses_' + str(uuid)

        if name not in writtenFuses:
            writtenFuses.append(name)
            writefile(FUSE_CFG_TEMPLATE.format(name, *allfuseparams))

        return '&' + name

    return 'NULL'

###############################################################################
# Quotients
###############################################################################
writtenQuots = []
QUOTIENT_DATA_TEMPLATE = '{{ .ro = {ro:2}, .quotient = {quot:4} }}'
INDIVIDUAL_QUOT_REV_CFG_TEMPLATE = '''\n\t{{ .count = {count}, .cprRevMin = {min}, .cprRevMax = {max},  .quots = ( cpr_quotient[]) {{\n \t\t\t\t\t\t\t\t\t  {quots} }}  }} '''
QUOTIENT_CFG_TEMPLATE = '''
static cpr_quotient_cfg_rev  {name} =
{{
    .count = {count},
    .data = ( struct cpr_quotient_cfg[]) {{ {data} }},
}};
'''


def write_quotients(quots):
    global writtenQuots
    uuid = 0
    quotparams_rev = [[[] for j in range(256)] for i in range(256)]
    quotparams = []

    if len(quots) == 0:
        return 'NULL'

    for q in quots:
        uuid += hash(q) & (1 << 32) - 1
        quotparams_rev[q.min][q.max].append(QUOTIENT_DATA_TEMPLATE.format(**q.__dict__))

    for a in range(256):
        for b in range(256):
            if (len(quotparams_rev[a][b]) != 0):
                formatVals = {
                    'min': a,
                    'max': b,
                    'quots': ',\n                                      '.join(quotparams_rev[a][b]),
                    'count': len(quotparams_rev[a][b]),
                }
                quotparams.append(INDIVIDUAL_QUOT_REV_CFG_TEMPLATE.format(**formatVals))


    name = 'quotients_' + str(uuid)

    formatVals = {
        'name': name,
        'data': ',\n                                      '.join(quotparams),
        'count': len(quotparams),
    }

    if name not in writtenQuots:
        writtenQuots.append(name)
        writefile(QUOTIENT_CFG_TEMPLATE.format(**formatVals))

    return '&' + name

###############################################################################
# KVs
###############################################################################
writtenKVs = []
KV_DATA_TEMPLATE = '{{ .ro = {ro:2}, .kv = {kv:4} }}'
KV_CFG_TEMPLATE = '''
static cpr_kv_cfg  {name} =
{{
    .count = {count},
    .kvs   = (cpr_kv[]) {{ {kvs} }},
}};
'''

def write_kv(kvs):
    global writtenKVs
    uuid = 0
    kvparams = []

    if len(kvs) == 0:
        return 'NULL'

    for k in kvs:
        uuid += hash(k) & (1 << 32) - 1
        kvparams.append(KV_DATA_TEMPLATE.format(**k.__dict__))

    name = 'kvs_' + str(uuid)

    formatVals = {
        'name': name,
        'kvs': ',\n                                '.join(kvparams),
        'count': len(kvs),
    }

    if name not in writtenKVs:
        writtenKVs.append(name)
        writefile(KV_CFG_TEMPLATE.format(**formatVals))

    return '&' + name

###############################################################################
# Temp Adj Control
###############################################################################
TEMP_ADJ_CONTROLS = '''
static cpr_temp_adj_cfg  {name} =
{{
    .tempSensorStartId = {temp_sensor_start_id},
    .tempSensorEndId   = {temp_sensor_end_id},
    .tempPoints        = {{ {temp_points} }}, // degree C
}};
'''

temp_adj_list = []
def write_temp_adj_ctrl(vp, sw_settings):
    global temp_adj_list
    if vp.tempPoints:
        name = 'temp_adj_cfg_%s_%d_%d_%s' % (
                vp.rail.lower().replace('cpr_rail_',''),
                sw_settings.get('temp_sensor_start_id',0),
                sw_settings.get('temp_sensor_end_id',0),
                '_'.join([str(val) for i,val in sorted(vp.tempPoints)])
                )

        formatVals = {
            'name'                 : name,
            'temp_points'          : ', '.join([str(val) for i,val in sorted(vp.tempPoints)]),
            'temp_sensor_start_id' : sw_settings.get('temp_sensor_start_id',0),
            'temp_sensor_end_id'   : sw_settings.get('temp_sensor_end_id',0),
        }

        if name not in temp_adj_list:
            temp_adj_list.append(name)

            writefile(TEMP_ADJ_CONTROLS.format(**formatVals))

        return '&' + name
    else:
        return 'NULL'

###############################################################################
# Voltage Plan
###############################################################################
writtenVPs = []
writtenSubModes = []

MODE_PARAMS_TEMPLATE = '''
/*
 * {rail} Voltage Plan
 */
static cpr_voltage_plan {name} =
{{
    .modesCount      = {supported_count},
    .tempAdjCfg      = {temp_adj_controls},
    .kvCfg           = {kvs_ptr},
    .supportedModes  = (cpr_voltage_mode[]) {{ {supported_modes} }},
    .modes           = (struct cpr_voltage_data[]) {{{data}}},
}};
'''

MODE_PARAMS_NO_TEMP_ADJ_TEMPLATE = '''
/*
 * {rail} Voltage Plan
 */
static cpr_voltage_plan {name} =
{{
    .modesCount      = {supported_count},
    .tempAdjCfg      = NULL,
    .kvCfg           = {kvs_ptr},
    .supportedModes  = (cpr_voltage_mode[]) {{ {supported_modes} }},
    .modes           = (struct cpr_voltage_data[]) {{{data}}},
}};
'''

VOLTAGE_DATA_TEMPLATE = '''
        // {mode}
        {{.fref = {fuseRef:>6}, .freqDelta = {f_delta:>7}, .fuses = {fuses_ptr}, .quotients = {quots_ptr}, .margins = {margin_list},
         .marginTempBands = {margin_temp_bands}, // PMIC step size
         .subModesCount   = {sub_modes_cnt},
         .subModes        = (cpr_freq_data[]){{ {sub_modes} }} }}'''

VOLTAGE_DATA_NO_TEMP_ADJ_TEMPLATE = '''
        // {mode}
        {{.fref = {fuseRef:>6}, .freqDelta = {f_delta:>7}, .fuses = {fuses_ptr}, .quotients = {quots_ptr}, .margins = {margin_list},
         .marginTempBands = {{0}},
         .subModesCount   = {sub_modes_cnt},
         .subModes        = (cpr_freq_data[]){{ {sub_modes} }} }}'''

VOLTAGE_SUB_MODE_DATA_TEMPLATE = '{{.ceiling = {1:7}, .floor = {2:7}, .freq = {0:7}, .interplEnabled = {3}}}'


def write_mode_params(vp, swSetting):
    global writtenVPs
    uuid = 0
    supportedModes = []
    modeDecls = []
    tempPoints = []
    foundLowestDisabledMode = False  # used for interpolation

    modes = vp.modes

    # Iterate over all modes

    modes = vp.modes

    # Iterate over all modes
    for i, (modeId, mode) in enumerate(modes):
        subModeDecls = []
        tempBandParams = []
        lowestDisabledMode = None
        marginModeSize = 0;

        #if modeId.lower() == 'retention':
        #   continue

        if not any(mode.enabled):
            continue

        # Iterate over all submodes
        for e, fq, c, fl, intrplEn in zip(mode.enabled, mode.freq, mode.ceiling, mode.floor, mode.interplEnabled):
            if e:
                subModeDecls.append(VOLTAGE_SUB_MODE_DATA_TEMPLATE.format(fq, c, fl, str(intrplEn).lower()))
            elif not foundLowestDisabledMode and not lowestDisabledMode:
                subModeDecls.append(VOLTAGE_SUB_MODE_DATA_TEMPLATE.format(fq, c, fl, str(intrplEn).lower()))
                lowestDisabledMode = True

        if len(subModeDecls) == 0:
            continue

        uuid += hash(mode) & (1 << 32) - 1

        if not lowestDisabledMode:
            supportedModes.append('CPR_VOLTAGE_MODE_' + modeId)

        fDelta = 0
        if i > 0 and mode.freq[-1] > 0:
            for id, m in modes[:i][::-1]:
                if m.freq[-1] > 0:
                    fDelta = mode.freq[-1] - m.freq[-1]
                    if m.enabled[-1]: break

        if mode.tempBands and swSetting is not None:
            formatVals = {
                'mode'              : modeId,
                'margin_list'       : write_margins(mode.margins),
                'f_delta'           : fDelta,
                'quots_ptr'         : write_quotients(mode.quotients),
                'fuses_ptr'         : write_fuses(mode.fuses),
                'margin_temp_bands' : '{ %s }' % ', '.join([str(v) for i,v in sorted(mode.tempBands)]),
                'sub_modes_cnt'     : len(subModeDecls),
                'sub_modes'         : ', '.join(subModeDecls)
            }
            formatVals.update(mode.__dict__)
            vdata = VOLTAGE_DATA_TEMPLATE.format(**formatVals)
        else:
            formatVals = {
                'mode'              : modeId,
                'margin_list'       : write_margins(mode.margins),
                'f_delta'           : fDelta,
                'quots_ptr'         : write_quotients(mode.quotients),
                'fuses_ptr'         : write_fuses(mode.fuses),
                'sub_modes_cnt'     : len(subModeDecls),
                'sub_modes'         : ', '.join(subModeDecls)
            }
            formatVals.update(mode.__dict__)
            vdata = VOLTAGE_DATA_NO_TEMP_ADJ_TEMPLATE.format(**formatVals)

        if not lowestDisabledMode:
            modeDecls.append(vdata)
        else:
            foundLowestDisabledMode = '(struct cpr_voltage_data[]) {{{0}}}'.format(vdata)

    name = 'voltage_plan_' + str(uuid)

    formatVals = {
        'rail'              : vp.rail.replace('CPR_RAIL_',''),
        'name'              : name,
        'supported_count'   : len(supportedModes),
        'temp_adj_controls' : None if swSetting is None else write_temp_adj_ctrl(vp, swSetting),
        'kvs_ptr'           : write_kv(vp.kvs),
        'supported_modes'   : ',\n                                                    '.join(supportedModes),
        'min_mode'          : foundLowestDisabledMode if foundLowestDisabledMode else 'NULL',
        'data'              : ',\n'.join(modeDecls),
    }

    if name not in writtenVPs:
        writtenVPs.append(name)
        if swSetting is None:
            writefile(MODE_PARAMS_NO_TEMP_ADJ_TEMPLATE.format(**formatVals))
        else:
            writefile(MODE_PARAMS_TEMPLATE.format(**formatVals))

    return '&' + name

###############################################################################
# Aging Config
###############################################################################
writtenAgingCfg = []
AGING_CONFIG_TEMPLATE = '''
static cpr_aging_cfg  {name} =
{{
    .cprRevMinToRun       = {cpr_rev_min_to_run},
    .modeToRun            = {mode},
    .sensorID             = {sensor_id},
    .kv                   = {kv_x100},
    .scalingFactor        = {scaling_factor_x10},
    .marginLimit          = {margin_limit},
    .bypassSensorIDs      = {bypass_sensor_ids},
    .bypassSensorIDsCount = {bypass_sensor_ids_count},
    .fusePackingFactor    = {fuse_packing_factor},
    .fuse                 = {aging_fuse}
}};
'''

def write_aging_config(rail, aging_cfg):
    global writtenAgingCfg
    uuid = 0

    if len(aging_cfg) == 0:
        return 'NULL'

    #for a in aging_cfg.items():
    #    uuid += hash(a) & (1 << 32) - 1

    #name = 'aging_' + str(uuid)
    name = 'aging_cfg_' + rail.lower()

    formatVals = {
        'name'                    : name,
        'cpr_rev_min_to_run'      : aging_cfg['cpr_rev_min_to_run'],
        'mode'                    : 'CPR_VOLTAGE_MODE_%s' % aging_cfg['mode'],
        'sensor_id'               : aging_cfg['sensor_id'],
        'kv_x100'                 : aging_cfg['kv_x100'],
        'scaling_factor_x10'      : aging_cfg['scaling_factor_x10'],
        'margin_limit'            : aging_cfg['margin_limit'],
        'bypass_sensor_ids'       : 'NULL' if not aging_cfg['bypass_sensor_ids'] else '(uint8[]) {%s}' % ', '.join([str(n) for n in aging_cfg['bypass_sensor_ids']]),
        'bypass_sensor_ids_count' : 0 if not aging_cfg['bypass_sensor_ids'] else len(aging_cfg['bypass_sensor_ids']),
        'fuse_packing_factor'     : aging_cfg['fuse_packing_factor'],
        'aging_fuse'              : '{.count = %d, .data = (struct raw_fuse_data[]) {\n%s } }' % (
                                        len(aging_cfg['fuse_info']),
                                        ',\n'.join([
                                            '                                 {%s, %s, %s}' % (
                                                info['fuse_address'],
                                                info['fuse_offset'],
                                                info['fuse_mask'])
                                            for info in aging_cfg['fuse_info']])
                                    ),
    }

    if name not in writtenAgingCfg:
        writtenAgingCfg.append(name)
        writefile(AGING_CONFIG_TEMPLATE.format(**formatVals))

    return '&' + name

###############################################################################
# Version
###############################################################################
writtenVersions = []
VERSION_TEMPLATE = '''
static cpr_version  {name} = {{ .foundry = CPR_FOUNDRY_{foundry}, .min = CPR_CHIPINFO_VERSION({min}), .max = CPR_CHIPINFO_VERSION({max}) }};
'''
def write_version(foundry, min, max):
    global writtenVersions
    name = 'ver_%s_%s_%s' % (foundry, min.replace('.','_'), max.replace('.','_'))
    if name not in writtenVersions:
        writtenVersions.append(name)
        formatVals = {
            'name'    : name,
            'foundry' : foundry,
            'min'     : min.replace('.', ','),
            'max'     : max.replace('.', ','),
        }
        writefile(VERSION_TEMPLATE.format(**formatVals))
    return '&' + name

###############################################################################
# Versioned Voltage Plan
###############################################################################
VERSIONED_VOLTAGE_PLAN_TEMPLATE = '''
static cpr_versioned_voltage_plan {name} = {{
    .rail     = {rail},
    .list     = (struct voltage_plan_list[]) {{{data}     }},
    .count    = {count},
    .agingCfg = {aging_cfg}
}};
'''
VOLTAGE_PLAN_TEMPLATE = '''
        {{ .version = {version}, .cfg = {cfg} }},
'''


###############################################################################
# Misc Cfg
###############################################################################
MISC_CFG_TEMPLATE = '''
static cpr_misc_cfg misc_cfg = {{
    .cprRev = {0}
}};
'''

def write_rev_fuse(rev_fuse_info):
    rev_fuse_data = '{.count = %d, .data = (struct raw_fuse_data[]) {\n%s } }' % (
        len(rev_fuse_info),
            ',\n'.join([
                '                   {%s, %s, %s}' % (
                info['fuse_address'],
                info['fuse_offset'],
                info['fuse_mask'])
                for info in rev_fuse_info])
            ),
    return rev_fuse_data[0]

def write_misc_cfg(vals):
    if not vals['cpr_rev_fuse'] or vals['cpr_rev_fuse'] == 'NULL':
        fuseDecl = '{.count = 0, .data = NULL }'
    else:
        fuseDecl = '{{.count = 1, .data = (struct raw_fuse_data[]) {{ {{{address}, {offset}, {mask}}} }} }}'.format(**vals['cpr_rev_fuse'])
    writefile(MISC_CFG_TEMPLATE.format(fuseDecl))


###############################################################################
# Controller Thread Cfg
###############################################################################
THREAD_CFG_TEMPLATE = '''
static cpr_hal_thread_cfg {name} = {{
    .upThresh     = {up_thresh},
    .dnThresh     = {dn_thresh},
    .consecUp     = {consec_up},
    .consecDn     = {consec_dn},
    .sensors      = {sensors},
    .sensorsCount = {sensors_count},
}};
'''

THREAD_INFO_TEMPLATE = '''
static cpr_hal_thread  {name} = {{
    .id   = {thread_id},
    .cfg  = {thread_cfg},
}};
'''

def write_controller_thread_cfg(name, cfg, sw_settings_vals):
    sensors = cfg.get('sensors', [])

    name = name.lower() + '_thread'

    formatVals = {
        'name'          : name+'_cfg',
        'up_thresh'     : 0,
        'dn_thresh'     : 0,
        'consec_up'     : 0,
        'consec_dn'     : 0,
        'sensors'       : ('(uint8[]){{ {0} }}'.format(','.join(str(s) for s in sensors)), 'NULL')[len(sensors) == 0],
        'sensors_count' : len(sensors),
    }
    formatVals.update(sw_settings_vals)

    writefile(THREAD_CFG_TEMPLATE.format(**formatVals))
    writefile(THREAD_INFO_TEMPLATE.format(**{
        'name'       : name,
        'thread_id'  : cfg['thread'],
        'thread_cfg' : '&'+name+'_cfg',
    }))

    return name

###############################################################################
# Controller Cfg
###############################################################################
CONTROLLER_CFG_TEMPLATE = '''
static cpr_hal_controller_cfg {name} = {{
    .stepQuotMin         = {step_quot_min},
    .stepQuotMax         = {step_quot_max},
    .sensorsTotal        = {num_sensors},
    .bypassSensors       = {bypassedSensors},
    .bypassSensorsCount  = {bypassCount},
    .disableSensors      = {disabledSensors},
    .disableSensorsCount = {disableCount},
    .refClk              = {ref_clk},
    .ahbClk              = {ahb_clk},
}};
'''

CONTROLLER_INFO_TEMPLATE = '''
static cpr_hal_controller  {name} = {{
    .base                = {base},
    .type                = {type},
    .cfg                 = {controller_cfg},
    .threads             = {threads},
    .threadsCount        = {num_threads},
}};
'''

def write_controller_cfg(name, cfg, sw_settings_vals, thread_names):
    bs = cfg.get('bypass_sensors', [])
    ds = cfg.get('mask_sensors', [])

    name = name.lower() + '_controller'

    formatVals = {
        'name'            : name+'_cfg',
        'ref_clk'         : 'NULL' if cfg['ref_clk'] is None else  '"%s"' % cfg['ref_clk'],
        'ahb_clk'         : 'NULL' if cfg['ahb_clk'] is None else  '"%s"' % cfg['ahb_clk'],
        'num_sensors'     : cfg['num_sensors'],
        'bypassedSensors' : ('(uint8[]){{ {0} }}'.format(','.join(str(v) for v in bs)), 'NULL')[len(bs) == 0],
        'disabledSensors' : ('(uint8[]){{ {0} }}'.format(','.join(str(v) for v in ds)), 'NULL')[len(ds) == 0],
        'bypassCount'     : len(bs),
        'disableCount'    : len(ds),
        'step_quot_max'   : sw_settings_vals['step_quot_max'],
        'step_quot_min'   : sw_settings_vals['step_quot_min'],
    }

    writefile(CONTROLLER_CFG_TEMPLATE.format(**formatVals))
    writefile(CONTROLLER_INFO_TEMPLATE.format(**{
        'name'           : name,
        'base'           : cfg['base'],
        'type'           : cfg['type'],
        'controller_cfg' : '&'+name+'_cfg',
        'num_threads'    : len(thread_names),
        'threads'        : '(cpr_hal_thread*[]){{ {0} }}'.format(', '.join('&%s' % name for name in thread_names)),
    }))

    return name


###############################################################################
# Enablements
###############################################################################
ENABLEMENT_TEMPLATE = '''
static cpr_enablement {name} =
{{
    .id                = {id},
    .version           = {version},
    .funcId            = {control_mode},
    .fuseMultiplier    = {fuse_multiplier_uv},
    .stepSize          = {step_size_uv},
    .thermalAdjustment = {thermal},
    .railCPRRevFuse    = {rev},
    .enable            = {en},
}};
'''
ENABLEMENT_TEMPLATE_NO_THERMAL = '''
static cpr_enablement {name} =
{{
    .id                = {id},
    .version           = {version},
    .funcId            = {control_mode},
    .fuseMultiplier    = {fuse_multiplier_uv},
    .stepSize          = {step_size_uv},
    .railCPRRevFuse    = {rev},
    .enable            = {en},
}};
'''


def write_enablement(id, vals):
    def x(val): return str(val).replace('.', ',')

    name = id.lower() + '_enablement_' + vals['version_min'].replace('.','_') + '_' + vals['version_max'].replace('.','_')

    formatVals = {
        'id'     : id,
        'name'   : name,
        'version': write_version(vals['foundry'], vals['version_min'], vals['version_max']),
        'thermal': '{ 0 }' if not vals['thermal_adjustments'] else \
                   '{{ {0} }}'.format(', '.join([str(v) for v in vals['thermal_adjustments']])),
        'rev'    : write_rev_fuse(vals['rev_fuse_info']),
        'en'     : 1 if vals['enable'] else 0
    }
    formatVals.update(vals)

    if vals['thermal_adjustments']:
        writefile(ENABLEMENT_TEMPLATE.format(**formatVals))
    else:
        writefile(ENABLEMENT_TEMPLATE_NO_THERMAL.format(**formatVals))

    return name


###############################################################################
# Rail Cfg
###############################################################################
RAIL_CFG_TEMPLATE = '''
static cpr_rail {name} = {{
    .id               = {id},
    .name             = "{debugName}",
    .hal              = {{ .controller = {controller}, .thread = {thread} }},
    .interruptId      = {interrupt},
    .settleModes      = {settleList},
    .settleModesCount = {settleCount},
}};
'''

def write_hal_rail_cfg(enumId, id, vals, sw_settings, controller_names, thread_names):
    name = enumId.lower() + '_cfg'

    formatVals = {
        'id'         : enumId,
        'name'       : name,
        'debugName'  : id,
        'controller' : 'NULL' if 'controller_name' not in vals else '&%s' % controller_names[vals['controller_name']],
        'thread'     : 'NULL' if 'controller_name' not in vals else '&%s' % thread_names[vals['controller_name']][vals['thread_id']],
        'settleList' : 'NULL' if not vals['settle_modes'] else \
                       '(cpr_voltage_mode[]) {{ {0} }}'.format(', '.join(vals['settle_modes'])),
        'settleCount': len(vals.get('settle_modes', [])),
        'interrupt'  : 0 if vals['interrupt'] is None else vals['interrupt'],
    }
    if sw_settings is not None:
        formatVals.update(sw_settings)
    writefile(RAIL_CFG_TEMPLATE.format(**formatVals))

    return name

###############################################################################
# Main output
###############################################################################


def write_cpr_cfg(img, target, sourcefile, destfile):
    global destFile
    destFile = open(destfile, 'wb')

    writefile(('\n'.join([
        '/*******************************************************************************',
        ' *',
        ' * Copyright (c) {0} Qualcomm Technologies, Inc.'.format(datetime.datetime.now().year),
        ' * All Rights Reserved.',
        ' * QUALCOMM Proprietary and Confidential.',
        ' *',
        ' * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR {0}.'.format(target),
        ' *',
        ' * DateTime: {0}'.format(datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S')),
        ' *',
        ' *******************************************************************************/'
        ])))

    ################################################################################
    # write Includes
    ################################################################################
    writefile('#include "cpr_data.h"')
    writefile('#include "cpr_image_target_init.h"')
    writefile('#include "cpr_target_hwio.h"')

    ################################################################################
    # parse voltage plan file
    ################################################################################
    allvps = { }
    vps, hashval = get_voltage_plan(img, target, sourcefile)

    ################################################################################
    # write hash value of voltage plan file
    ################################################################################
    writefile('\n\n//hash value of Voltage Plan file (extracted all cell values)')
    writefile('static char voltage_plan_hash_value[] = "%s";\n' % hashval)

    ################################################################################
    # write Voltage Plan data
    ################################################################################
    writefile('\n'.join([
        '',
        '/*******************************************************************************',
        '********************************************************************************',
        '**',
        '** Voltage Plan Data',
        '**',
        '********************************************************************************',
        '********************************************************************************/',
    ]))

    for k in vps:
        vp = vps[k]
        if isinstance(vp, dict):
            continue
        currentRail = vp.rail
        vp.rail = 'CPR_RAIL_' + vp.rail

        formatVals = {
            'cfg'     : write_mode_params(vp, vps['sw_settings'].get(currentRail, None)),
            'version' : write_version(vp.foundry, vp.min, vp.max)
        }
        #formatVals.update(vp.__dict__)
        allvps.setdefault(vp.rail, []).append(VOLTAGE_PLAN_TEMPLATE.format(**formatVals))

    def vvpName(k):
        return k.lower().replace('cpr_rail_','') + '_vvp'

    writefile('\n'.join([
        '',
        '/*',
        ' * Aging configs',
        ' */'
    ]))

    aging_cfg_list = {}
    for k in allvps:
        rail = k.split('CPR_RAIL_')[-1]
        if 'aging' in vps and rail in vps['aging']:
            aging_cfg_list[k] = write_aging_config(rail, vps['aging'][rail])


    writefile('\n'.join([
        '',
        '/*',
        ' * Versioned Voltage Plans',
        ' */'
    ]))

    for k in allvps:
        formatVals = {
            'name': vvpName(k),
            'rail': k,
            'data': ''.join(x for x in allvps[k]),
            'count': len(allvps[k]),
            'aging_cfg': 'NULL' if k not in aging_cfg_list else aging_cfg_list[k],
        }
        writefile(VERSIONED_VOLTAGE_PLAN_TEMPLATE.format(**formatVals))

    ################################################################################
    # write enablement config data
    ################################################################################
    writefile('\n'.join([
        '/*******************************************************************************',
        '********************************************************************************',
        '**',
        '** Enablement Config Data',
        '**',
        '********************************************************************************',
        '********************************************************************************/',
    ]))

    writefile('\n'.join([
        '',
        '/*',
        ' * CPR Controller Thread Config',
        ' */'
    ]))

    rail_controller_map = {}
    thread_names = {}
    for ctrl_name, controller in sorted(list(vps['controllers'].items()), key=lambda v: v[0]):
        for rail, thread in sorted(list(controller['threads'].items()), key=lambda v: v[1]['thread']):
            if ctrl_name not in thread_names:
                thread_names[ctrl_name] = []
            name = write_controller_thread_cfg(rail, thread, vps['sw_settings'].get(rail,{}))
            thread_names[ctrl_name].append(name)
            rail_controller_map[rail] = {'controller_name': ctrl_name, 'thread_id':thread['thread']}

    writefile('\n'.join([
        '',
        '/*',
        ' * CPR Controller Config',
        ' */'
    ]))

    controllernames = {}
    for ctrl_name, controller in sorted(list(vps['controllers'].items()), key=lambda v: v[0]):
        for rail in list(controller['threads'].keys()):
            if rail in vps['sw_settings']:
                name = write_controller_cfg(ctrl_name, vps['controllers'][ctrl_name], vps['sw_settings'][rail], thread_names.get(ctrl_name,[]))
                controllernames[ctrl_name] = name
                break

    writefile('\n'.join([
        '',
        '/*',
        ' * HAL Rail Config',
        ' */'
    ]))

    railnames = { }
    for rail, enabs in sorted(list(vps['enablements'].items()), key=lambda v: v[0]):
        enumId = 'CPR_RAIL_' + rail
        for enab in enabs:
            name = write_hal_rail_cfg(enumId, rail, enab, vps['sw_settings'].get(rail,None), controllernames, thread_names)
            railnames[enumId] = name
            break # no version control for HAL rail config

    writefile('\n'.join([
        '',
        '/*',
        ' * Rail Enablement Config',
        ' */'
    ]))

    enablementnames = []
    for rail, enabs in sorted(list(vps['enablements'].items()), key=lambda v: v[0]):
        id = 'CPR_RAIL_' + rail
        for enab in enabs:
            name = write_enablement(id, enab)
            enablementnames.append(name)

    write_misc_cfg(vps['misc'])

    sorted_railnames = sorted(railnames.keys())
    sorted_vvp = sorted(allvps, key=lambda k: k)

    writefile('\n'.join([
        '',
        'cpr_settings cpr_settings_{0} ='.format(target),
        '{',
        '    .hashValue        = voltage_plan_hash_value,',
        '',
        '    .railVVPs         = (cpr_versioned_voltage_plan*[]) {{ {0} }},'.format(', '.join('&' + vvpName(k) for k in sorted_vvp)),
        '    .rails            = (cpr_rail*[]) {{ {0} }},'.format(', '.join('&' + railnames[k] for k in sorted_railnames)),
        '    .railsCount       = %d,' % (len(sorted_vvp)),
        '',
        '    .controllers      = NULL,' if not controllernames else \
        '    .controllers      = (cpr_hal_controller*[]) {{ {0} }},'.format(', '.join('&' + v for v in sorted(controllernames.values()))),

        '    .controllersCount = %d,' % (len(controllernames)),
        '',
        '    .enablements      = (cpr_enablement*[]) {{ {0} }},'.format(', '.join('&' + r for r in enablementnames)),
        '    .enablementsCount = %d,' % (len(enablementnames)),
        '',
        '    .miscCfg          = &misc_cfg,',
        '};',
        '',
        ]))

    destFile.close()

    if len(sorted_vvp) != len(sorted_railnames):
        raise Exception('Fatal: the number of rail config does not match: (railVPs: %d) (rails: %d)' % \
                (len(sorted_vvp), len(sorted_railnames) ))

###############################################################################
# Bin File output
###############################################################################
def write_cpr_bin(img, target, source, binfile):
    binSize = 0

    if os.path.isfile(binfile):
        os.remove(binfile)
    binFile = open(binfile, 'wb')

    debugfile = binfile.split(".bin")[0]+".txt"
    if os.path.isfile(debugfile):
        os.remove(debugfile)

    if debug:
        debugFile = open(debugfile, 'wb')

    cpr_rail_map = {
        'CPR_RAIL_MX' : 0x100,
        'CPR_RAIL_CX' : 0x101,
        'CPR_RAIL_MSS' : 0x102,
        'CPR_RAIL_GFX' : 0x103,
        'CPR_RAIL_VDDA' : 0x104,
        'CPR_RAIL_WLAN' : 0x105,
        'CPR_RAIL_MM' : 0x106,
        'CPR_RAIL_MXC' : 0x107,
        'CPR_RAIL_SSC_MX' : 0x300,
        'CPR_RAIL_SSC_CX' : 0x301,
        'CPR_RAIL_LPI_MX' : 0x400,
        'CPR_RAIL_LPI_CX' : 0x401,
        'CPR_RAIL_MSS_LDO' : 0x500,
        'CPR_RAIL_TURING_LDO' : 0x501,
        'CPR_RAIL_NAV_LDO' : 0x502,
        'CPR_RAIL_WMSS_CX_1' : 0x600,
        'CPR_RAIL_WMSS_CX_2' : 0x601,
        'CPR_RAIL_WMSS_CX_3' : 0x602,
    }


    ################################################################################
    # parse voltage plan file
    ################################################################################
    vps, hashval = get_voltage_plan(img, target, source)

    for k in vps:
        vp = vps[k]
        if isinstance(vp, dict):
            continue

        #Get the chip version info.
        if (int(vp.max.split('.')[0])-int(vp.min.split('.')[0])):
            #If the major of the min, max differ,
            #then need to figure out how to handle it better.
            sys.exit(-1)
        else:
            chipver = int(vp.max.split('.')[0])

        modes = vp.modes
        vp.rail = 'CPR_RAIL_'+vp.rail

        # Iterate over all modes
        for i, (modeId, mode) in enumerate(modes):
            data = [];

            if not any(mode.enabled):
                continue
            if not mode.margins:
                continue

            for m in mode.margins:
                data = []
                data.append(cpr_rail_map[vp.rail])
                data.append(chipver)
                data.append(int(mode.virtualCorners[0]))
                data.append(int(m.__dict__.get('vpidmin')))
                data.append(int(m.__dict__.get('vpidmax'))) 
                data.append(int(m.__dict__.get('min')))
                data.append(int(m.__dict__.get('max')))
                data.append(int(m.__dict__.get('ol')))
                data.append(int(m.__dict__.get('cl')))
                data.append(int(m.__dict__.get('fToC')))
                encoded = struct.pack("<{}i".format(len(data)), *data)
                filewriter(binFile, encoded, True)
                if (debug):
                    filewriter(debugFile, data, False)
                binSize+=struct.calcsize("<{}I".format(len(data)))

    binFile.close()
    if (debug):
        filewriter(debugFile, binSize, False)
    if debug:
        debugFile.close()

###############################################################################
# Main
###############################################################################
if __name__ == '__main__':
    tgt = 'waipio'
    rails = None

    if len(sys.argv) >= 4:
        rails = sys.argv[3:]

    if len(sys.argv) >= 3:
        cfg = sys.argv[1]
        output = sys.argv[2]
    else:
        # debug = True
        # rails = ['CX', 'MX', 'VDDA', 'SSC_MX', 'SSC_CX']
        cfg = '../target/{0}/Voltage_Plan_{0}.xlsx'.format(tgt)
        output = '../build/out/gen/cpr_voltage_plan_{0}.c'.format(tgt)
        pass

    write_cpr_cfg(rails, cfg, output)

    output = '../build/out/gen/cpr_voltage_plan_{0}.bin'.format(tgt)
    write_cpr_bin(rails, cfg, output)

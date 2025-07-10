#! /usr/bin/env python
from __future__  import print_function
import os
import sys

__all__ = ['cpr_cfg']

def cpr_cfg(img, target, out_dir, target_dir=None, fuses_dir=None):
    if not os.path.exists(out_dir) or not os.path.exists(target_dir) or not os.path.exists(fuses_dir):
        print('Target folders do not exist')
        print('out_dir = {}\ntarget_dir = {}\nfuses_dir = {}\n'.\
              format(out_dir, target_dir, fuses_dir))
        return

    print('Generating CPR config files ...')

    tools_dir  = os.path.split(os.path.abspath(sys.argv[0]))[0]
    if target in 'fillmore':
        tools_dir = os.path.join(tools_dir, 'fillmore_tools')
    else:  
        tools_dir = os.path.join(tools_dir, 'tools')   
    pyx_dir    = os.path.join(tools_dir, 'openpyxl-2.5.4-py2.7.egg')
    etx_dir    = os.path.join(tools_dir, 'et_xmlfile-1.0.1-py2.7.egg')

    if target_dir is None:
        target_dir = os.path.join(tools_dir, os.sep.join(['..','target',target]))
    if fuses_dir is not None:
        sys.path.append(fuses_dir)

    sys.path.append(pyx_dir)
    sys.path.append(etx_dir)
    sys.path.append(target_dir)

    #
    #Write CPR config.
    #
    from voltage_plan_writer import write_cpr_cfg as writer
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    cfg = os.path.join(target_dir, 'Voltage_Plan_{0}.xlsx'.format(target))
    src = os.path.join(out_dir, 'cpr_voltage_plan_{0}.c'.format(target))

    if os.path.isfile(src):
        os.remove(src)

    print('  Parsing config file: %s ...' % cfg)
    writer(img, target, cfg, src)
    print('  Generated %s' % src)

    #
    #Write CPR bin.
    #
    from voltage_plan_writer import write_cpr_bin as bin_writer
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    cfg = os.path.join(target_dir, 'Voltage_Plan_{0}.xlsx'.format(target))
    default = os.path.join(out_dir, 'cpr_voltage_plan_{0}.bin'.format(target))
    custom = os.path.join(out_dir, 'cpr_voltage_plan_{0}_custom.bin'.format(target))

    print('  Parsing config file: %s ...' % cfg)
    bin_writer(img, target, cfg, default)
    print('  Generated %s' % default)
    print('  Generated %s' % custom)


###############################################################################
# Main
###############################################################################
if __name__ == '__main__':
    img    = 'xbl'
    target = '8350'
    out_dir = '../../../SocPkg/Lahaina/Settings/CPR'
    target_dir = '../../../SocPkg/Lahaina/Settings/CPR'
    fuses_dir = '../../../SocPkg/Lahaina/Library/CPRTargetLib/target/8350'

    if len(sys.argv) >= 4:
        img    = sys.argv[1] #mpss, rpm, xbl (images in enablement.cfg)
        target = sys.argv[2] #8996, 8998, 9x55 ...
        out_dir = sys.argv[3]
    # for XBL we need to specify target directory due to UEFI file structure.
    if len(sys.argv) >= 5:
        target_dir = sys.argv[4]
    # for XBL we need to specify fuses.py directory due to UEFI file structure.
    if len(sys.argv) >= 6:
        fuses_dir = sys.argv[5]

    if os.path.exists(out_dir) and os.path.exists(target_dir) and os.path.exists(fuses_dir):
        print('Target folders present')
        print('out_dir = {}\ntarget_dir = {}\nfuses_dir = {}\n'.\
              format(out_dir, target_dir, fuses_dir))
        cpr_cfg(img, target, out_dir, target_dir=target_dir, fuses_dir=fuses_dir)

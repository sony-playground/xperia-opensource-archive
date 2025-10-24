#! /usr/bin/env python
import os
import sys

def main(img, target, out_dir, target_dir=None, fuses_dir=None):
    tools_dir  = os.path.split(os.path.abspath(sys.argv[0]))[0]
    tools_dir = os.path.join(tools_dir, 'tools')
    cfg_path = os.path.join(tools_dir, 'cpr_cfg.py')

    f = open('parser.log', 'w+')
    f.write("img = {}\n".format(img))
    f.write("target = {}\n".format(target))
    f.write("out_dir = {}\n".format(out_dir))
    f.write("target_dir = {}\n".format(target_dir))
    f.write("fuses_dir = {}\n".format(fuses_dir))
    f.write("tools_dir = {}\n".format(tools_dir))
    f.write("cfg_path = {}\n".format(cfg_path))

    sys.path.append(tools_dir)
    if os.path.exists(cfg_path):
        f.write('{} found'.format(cfg_path))
        print('NOTE: {} found'.format(cfg_path))
        from cpr_cfg import cpr_cfg
        cpr_cfg(img, target, out_dir, target_dir, fuses_dir)
    else:
        f.write('{} not found\n'.format(cfg_path))
        print('WARNING: {} not found'.format(cfg_path))

    f.flush()
    f.close()

###############################################################################
# Main
###############################################################################
if __name__ == '__main__':
    img    = 'xbl'
    target = 'kailua'
    out_dir = '../../SocPkg/Kailua/Settings/CPR'
    target_dir = '../../SocPkg/Kailua/Settings/CPR'
    fuses_dir = '../../SocPkg/Kailua/Library/CPRTargetLib/target/kailua'

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

    print('img = {}'.format(img))
    print('target = {}'.format(target))
    print('out_dir = {}'.format(out_dir))
    print('target_dir = {}'.format(target_dir))
    print('fuses_dir = {}'.format(fuses_dir))

    main(img, target, out_dir, target_dir, fuses_dir)

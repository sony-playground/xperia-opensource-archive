#  ===========================================================================
#
#  Copyright (c) 2016-2019 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================

import glob, itertools, os, string, sys, subprocess, re, pickle, shutil, datetime, atexit, platform, stat
import xml.etree.ElementTree as xml


def write_setenv_files(static_variables, update_variables):
    if platform.system() == "Linux":
        setenv_cmd = open('setenv.sh', 'w')

        for var, val in static_variables.iteritems():
            setenv_cmd.write('export %s=%s\n' % (var, val))
        for var, val in update_variables.iteritems():
            val = string.replace(val, ";", ":")
            setenv_cmd.write('export %s=%s$%s\n' % (var, val, var))

        setenv_cmd.close()
    else:
        setenv_cmd = open('setenv.cmd', 'w')

        for var, val in static_variables.iteritems():
            setenv_cmd.write('set %s=%s\n' % (var, val))
        for var, val in update_variables.iteritems():
            setenv_cmd.write('set %s=%s%%%s%%\n' % (var, val, var))

        setenv_cmd.close()

def write_setenv_files_from_environment():
    if platform.system() == "Linux":
        setenv_cmd = open('setenv.sh', 'w')
    else:
        setenv_cmd = open('setenv.cmd', 'w')

    write_env_variable_to_setenv(     'ARMINC', setenv_cmd)
    write_env_variable_to_setenv(     'ARMLIB', setenv_cmd)
    write_env_variable_to_setenv(     'ARMBIN', setenv_cmd)
    write_env_variable_to_setenv(    'ARMPATH', setenv_cmd)
    write_env_variable_to_setenv( 'ARMINCLUDE', setenv_cmd)
    write_env_variable_to_setenv(   'ARMTOOLS', setenv_cmd)

    setenv_cmd.close()

def write_env_variable_to_setenv( env_var, setenv_cmd ):
    val = os.environ.get( env_var, 'none')
    if( val == 'none' ):
        print "ERROR: Environment variable " + env_var + " not defined."
        print "  Delete environment variable ARMPATH before running this build"
        print "  command to have it auto-detect the compiler settings"
        print "Exiting."
        setenv_cmd.close()
        sys.exit()
    else:
        if platform.system() == "Linux":
            setenv_cmd.write('export %s=%s\n' % (env_var, val))
        else:
            setenv_cmd.write('set %s=%s\n' % (env_var, val))

def get_clang_version(path):
    if not os.path.exists(path):
        return

    armcc = subprocess.Popen([path, '-v'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if 0 != armcc.wait():
        print 'Could not run clang from %s.' % path
        return
    output = armcc.stdout.read() + armcc.stderr.read()
    m = re.search(r'(Snapdragon LLVM ARM Compiler\s(?P<major>\d+).(?P<minor>\d+).(?P<build>\d+))', output)
    if not m:
        print 'Could not identify version of clang from %s.' % path
        return
    major = m.group('major')
    minor = m.group('minor')
    build = m.group('build')
    
    return {'major' : major, 'minor' : minor, 'build' : build, 'path' : path, 'pretty_name' : m.group(0)}

def select_clang_install(install_path):
    # pass the clang path
    if platform.system() == "Linux":
        clang_path = os.path.join(install_path, 'bin', 'clang')
    else:
        clang_path = os.path.join(install_path, 'bin', 'clang.exe')

    # check the clang version
    pending_clang = get_clang_version(clang_path)

    if not pending_clang:
      # raise a flag
      print 'Version Null'
      raise RuntimeError, 'get_clang_version'
      exit(1)

    # restore the "base" path for later use
    pending_clang['path'] = install_path

    return pending_clang

def setup_clang_install(install_info):
    incpath = os.path.join(install_info['path'], 'include')
    armpath = os.path.join(install_info['path'], 'bin')

    static_variables = {
        # Lie to the build scripts to tell them to treat this like RVCT 4.1 until they officially support ARMCC 5.
        'ARMTOOLS'   : 'Snapdragon LLVM',
        'ARMLIB'     : os.path.join(install_info['path'], 'lib'),
        'ARMINCLUDE' : incpath,
        'ARMINC'     : incpath,
        'ARMPATH'    : armpath,
        'ARMBIN'     : armpath,
    }

    update_variables = {
        'PATH'       : '.;' + os.path.join('..', 'tools', 'build', 'scons', 'SCons') + ';' + armpath + ';',
    }

    os.environ.update(static_variables)
    for var, val in update_variables.iteritems():
        current = os.environ.get(var)
        os.environ[var] = val + current

    write_setenv_files(static_variables, update_variables)
    
def GenerateXML(filename):
    root=xml.Element("ENVIRONMENT")
    root.text = "\n"
    c1=xml.Element("PYTHON ")
    root.append(c1)
    c1.text = "\n"
    
    type1=xml.SubElement(c1,"Version")
    type1.text= "\n" + sys.version + "\n"
   
   
    c2=xml.Element("COMPILER")
    root.append(c2)
    c2.text = "\n"
    
    type2=xml.SubElement(c2,"Name ")
    type2.text =  "\n" + os.environ.get('ARMTOOLS') + "\n" 
    type3=xml.SubElement(c2,"Version")
   
    type3.text =  "\n" + os.environ.get('LLVM_VERSION') + "\n"
    
    
    
    tree=xml.ElementTree(root)
    
    with open(filename,"wb") as files:
      tree.write(files)


compiler_types = [
    {
        'name'             : 'SD LLVM Compiler',
        'paths'            : ['/pkg/qct/software/llvm/release/arm/*',
                              'C:\\Apps\\LLVM\\*'
                              ],
        'install_selector' : select_clang_install,
        'setup'            : setup_clang_install,
    },
    {
        'name'             : 'SD LLVM Compiler',
        'paths'            : ['/pkg/qct/software/llvm/release/arm/*',
                              'C:\\Apps\\LLVM\\*'
                              ],
        'install_selector' : select_clang_install,
        'setup'            : setup_clang_install,
    },
]

def find_compiler():
    print '\n\n\nDetecting build environment...'
    selected_compiler = {}
    for compiler in compiler_types:
        # see if path can be pruned early
        env_LLVM_ROOT = os.environ.get('SD_LLVM_ROOT', 'none')
        if env_LLVM_ROOT  == ('none'):
          # raise a flag
          print 'SD_LLVM_ROOT is not defined in environment'
          raise RuntimeError, 'SD_LLVM_ROOT not defined'
          exit(2)
        else:
          env_LLVM_version_str = re.search(r'(?P<major>\d+)\.(?P<minor>\d+)\.(?P<build>\d+)(\\*|/)', env_LLVM_ROOT) 
          
          if not env_LLVM_version_str:
            print 'Could not identify version from SD_LLVM_ROOT'
            raise RuntimeError, 'Could not identify version from SD_LLVM_ROOT'
          
          print 'Environment points to', os.path.normpath(env_LLVM_ROOT)

          #abspath helps network latency?
          pending_compiler = compiler['install_selector'](os.path.abspath(env_LLVM_ROOT))

          #get a version check
          if pending_compiler['major'] == env_LLVM_version_str.group('major') and \
             pending_compiler['minor'] == env_LLVM_version_str.group('minor') and \
             pending_compiler['build'] == env_LLVM_version_str.group('build') : 
              selected_compiler = pending_compiler
              print 'Setting up to use:', selected_compiler['pretty_name']
              compiler['setup'](selected_compiler)
              #end def
              return True
          else:
              print 'Did not find any installs of', compiler['name']
              continue

    # should find a compiler
    if selected_compiler is None:
      print 'Failed to find a usable toolchain.'
      return False
  

def dump_env(log):
  log.write('---------------------------------------------\n')
  log.write(' PLATFORM : %s\n' % sys.platform)
  log.write('---------------------------------------------\n')

  log.write('---------------------------------------------\n')
  log.write(' ENVIRONMENT BEGIN\n')
  log.write('---------------------------------------------\n')

  padding = max([len(key) for key in os.environ.keys()])
  format = '%' + str(padding) + 's %s\n'
  for param in sorted(os.environ.keys()):
    log.write(format % (param, os.environ[param]))

  log.write('---------------------------------------------\n')
  log.write(' ENVIRONMENT END\n')
  log.write('---------------------------------------------\n')

def create_target_specific_build_artifacts():
  msm_id_map = {
    os.environ['MSM_ID']:os.environ['MSM_ID'],
  }
  know_build_variants = ['AAAAANAAO', 'AAAAANAZO', 'AAAAANADO']
  build_variant = os.environ['BUILD_ID']
  msm_id = msm_id_map[os.environ['MSM_ID']]
  dest_msm_id = os.environ['MSM_ID']
  chipset = os.environ['CHIPSET']
  if os.environ['MSM_ID'] in ['845'] and os.environ['CHIPSET_VERSION'] in ['v2']:
     chipset_version = os.environ['CHIPSET_VERSION']
     target_artifact_dir = '../core/bsp/aop/build/'+dest_msm_id+chipset_version+'/'
  elif os.environ['MSM_ID'] in ['670','waipio']:
     chipset_pmic = os.environ['CHIPSET_PMIC']
     target_artifact_dir = '../core/bsp/aop/build/'+chipset_pmic+'/'
  elif os.environ['MSM_ID'] in ['makenaau']:
     variant = os.environ['VARIANT']
     target_artifact_dir = '../core/bsp/aop/build/'+dest_msm_id+'/'+variant+'/'
  else:
     target_artifact_dir = '../core/bsp/aop/build/'+dest_msm_id+'/'
  target_artifact = target_artifact_dir + 'AOP_' + build_variant
  source_artifact_dir = '../core/bsp/aop/build/'
  source_artifact = source_artifact_dir + 'AOP_' + build_variant
  clocktestdict_target = '../core/power/aop/debug/scripts/ClockTestDict.py'
  clocktestdict_source = '../core/systemdrivers/hal/clk/hw/' + chipset + '/inc/ClockTestDict.py'

  artifacts = [ # Target Artifact                           # Source Artifact
                [target_artifact + '.mbn',                  source_artifact + '.mbn'],
                [target_artifact + '.elf',                  source_artifact + '.elf'],
				[target_artifact + '_devcfg.mbn',           source_artifact + '_devcfg.mbn'],
                [target_artifact + '_devcfg.elf',           source_artifact + '_devcfg.elf'],
                [target_artifact + '.htm',                  source_artifact + '.htm'],
                [target_artifact + '.map',                  source_artifact + '.map'],
                [target_artifact + '.scl',                  source_artifact + '.scl'],
                [target_artifact + '.sym',                  source_artifact + '.sym'],
				[target_artifact + '_devcfg.map',           source_artifact + '_devcfg.map'],
                [target_artifact + '_devcfg.scl',           source_artifact + '_devcfg.scl'],
                [target_artifact + '_devcfg.sym',           source_artifact + '_devcfg.sym'],
				[target_artifact + '_devcfg_scl.pp',        source_artifact + '_devcfg_scl.pp'],
                [target_artifact + '.hash',                 source_artifact + '.hash'],
                [target_artifact + '_hash.hd',              source_artifact + '_hash.hd'],
                [target_artifact + '_combined_hash.mbn',    source_artifact + '_combined_hash.mbn'],
                [target_artifact + '_phdr.pbn',             source_artifact + '_phdr.pbn'],
                [target_artifact + '_aop.elf',              source_artifact + '_aop.elf'],
                [target_artifact + '_scl.pp',               source_artifact + '_scl.pp'],
              ]
  artifacts_ext = [
                '.mbn',
                '.elf',
				'_devcfg.mbn',
				'_devcfg.elf',
                '.htm',
                '.map',
                '.scl',
                '.sym',
				'_devcfg.map',
				'_devcfg.scl',
				'_devcfg.sym',
				'_devcfg_scl.pp',
                '.hash',
                '_hash.hd',
                '_combined_hash.mbn',
                '_phdr.pbn',
                '_aop.elf',
                '_scl.pp',
              ]

  if 'LLVM' in os.environ['ARMTOOLS'] :
    artifacts.remove([target_artifact + '.htm', source_artifact + '.htm'])

  #import pdb; pdb.set_trace()
  # Internal Artifacts and Deliverable elf
  ms_bin_path = '../build/ms/bin/'+build_variant
  installed_mbn_path = '../build/aop/bf/build'
  
  if os.path.exists('../core/bsp/aop/build/'+'/AOP_'+build_variant+'.mbn') or \
     os.path.exists('../core/bsp/aop/build/'+'/AOP_'+build_variant+'_devcfg.mbn'):
    if os.environ['MSM_ID'] not in ['waipio']:
      print 'Cleaning up any old build artifacts'
      for variant in know_build_variants:                 # Remove other build variants' artifacts
        if variant != build_variant:
          if os.path.exists('../core/bsp/aop/build/AOP_'+variant):
            shutil.rmtree('../core/bsp/aop/build/AOP_'+variant)
          if os.path.exists('../build/ms/bin/'+variant):
            shutil.rmtree('../build/ms/bin/'+variant)
          if os.environ['MSM_ID'] not in ['makenaau']:                      #MAKENAU_TODO  
            if os.path.exists('../core/bsp/aop/build/'+dest_msm_id+'/'):
               shutil.rmtree('../core/bsp/aop/build/'+dest_msm_id+'/')
          for S_artifact_ext in artifacts_ext:
            if os.path.exists(source_artifact_dir + 'AOP_' + variant + S_artifact_ext):
                os.remove(source_artifact_dir + 'AOP_' + variant + S_artifact_ext)

    if ( not os.path.exists(clocktestdict_target) ) and os.path.exists(clocktestdict_source):
      shutil.copy(clocktestdict_source, clocktestdict_target)

    print 'Copying build artifacts to '+target_artifact_dir
    if not os.path.exists(target_artifact_dir):
      os.makedirs(target_artifact_dir)
    for [T_artifact,S_artifact] in artifacts:
      if(os.path.exists(S_artifact)):
        shutil.copy2(S_artifact, T_artifact)
    if os.path.exists('../build/aop/bf/build'):
      if os.path.exists(ms_bin_path):                   # shutil.copytree will fail if target directory exists... so remove it
        shutil.rmtree(ms_bin_path)
      shutil.copytree(installed_mbn_path, ms_bin_path)  # Replace with sectools generated mbn
  else: # clean build
    print 'Removing build artifacts'

    if os.path.exists(clocktestdict_target):
      # make sure the file is writable; otherwise, an IOError exception will be raised.
      os.chmod(clocktestdict_target, stat.S_IWRITE)
      os.remove(clocktestdict_target)

    if os.path.exists(target_artifact):
      for [T_artifact,S_artifact] in artifacts:
        os.remove(T_artifact)
      os.rmdir(target_artifact)

    if os.path.exists(target_artifact_dir):
      shutil.rmtree(target_artifact_dir)

    if os.path.exists('../core/bsp/aop/build/AOP_'+build_variant):
      shutil.rmtree('../core/bsp/aop/build/AOP_'+build_variant)
    if os.path.exists(installed_mbn_path):
      shutil.rmtree(installed_mbn_path)
    if os.path.exists(ms_bin_path):
      shutil.rmtree(ms_bin_path)


def start_build():
  # the list of build arguments we need to pass to scons--note that we're
  # not actually setting any of these here--they should be set externally

  # Default to generating a signed image.

  sec_policy = []

  for arg in sys.argv:
    if arg == 'GENSECIMAGE' or arg == 'NOGENSECIMAGE':
      print 'GENSECIMAGE/NOGENSECIMAGE is not supported, please use a SEC_POLICY instead'
      sys.exit(1)
    if arg == 'DISABLE_SEC_POLICY':
      if os.environ.has_key("SECPOLICY"):
        del os.environ["SECPOLICY"]
    if arg.find("USES_SEC_POLICY") == 0:
      sec_policy.append(arg)

  # Replace default sec policy with policy defined in arguments
  if len(sec_policy) > 0:
    os.environ["SECPOLICY"] = " ".join(sec_policy)
    print "Signing with custom sec policy"

  if os.environ.has_key("SECPOLICY"):
    print "Generating signed image"
  else:
    print "!! NOT GENERATING SIGNED IMAGE !!"

  if os.environ['MSM_ID'] in ['845']:
     build_args = [
      'BUILD_ID',
      'BUILD_VER',
      'MSM_ID',
      'HAL_PLATFORM',
      'TARGET_FAMILY',
      'BUILD_ASIC',
      'CHIPSET',
      'CHIPSET_VERSION',
    ]
  elif os.environ['MSM_ID'] in ['670','waipio']:
     build_args = [
      'BUILD_ID',
      'BUILD_VER',
      'MSM_ID',
      'HAL_PLATFORM',
      'TARGET_FAMILY',
      'BUILD_ASIC',
      'CHIPSET',
      'CHIPSET_PMIC',
    ]
  elif os.environ['MSM_ID'] in ['makenaau']:
     build_args = [
      'BUILD_ID',
      'BUILD_VER',
      'MSM_ID',
      'HAL_PLATFORM',
      'TARGET_FAMILY',
      'BUILD_ASIC',
      'CHIPSET',
      'VARIANT',
    ] 	
  else:
     build_args = [
      'BUILD_ID',
      'BUILD_VER',
      'MSM_ID',
      'HAL_PLATFORM',
      'TARGET_FAMILY',
      'BUILD_ASIC',
      'CHIPSET',
    ]


  std_args    = ' '.join(['%s=%s' % (key, os.environ[key]) for key in build_args])



  passed_args = []
  for arg in sys.argv[1:]:
    if arg != 'build_common.py' and arg != 'DISABLE_SEC_POLICY' and arg.find("USES_SEC_POLICY") != 0:
      passed_args.append(arg)

  # pass 'aop' as COMMAND_LINE_TARGETS if no args passed in order to not generate/delete HWIO files.
  # SCons is set to use 'all' as the default BUILD TARGETS, if COMMAND_LINE_TARGETS is not specified.
  if not any(target in passed_args for target in ['aop', 'hwio', 'all']):
      passed_args.append('aop')
  
  print "CWD: "+os.getcwd()+"\n"

  if platform.system() == "Linux":
    build_cmd   = '../tools/build/scons/SCons/scripts/scons -f ../tools/build/scons/build/start.scons %s %s' % (std_args, ' '.join(passed_args))
    #build_cmd   = '../tools/build/scons/SCons/scons.sh'
  else:
    build_cmd   = '..\\tools\\build\\scons\\SCons\\scripts\\scons.bat -f ..\\tools\\build\\scons\\build\\start.scons %s %s' % (std_args, ' '.join(passed_args))

    
  print 'Setting up build environment...'
  os.environ['SCONS_BUILD_ROOT'] = '..'
  os.environ['SCONS_TARGET_ROOT'] = '../..'
  os.environ['BUILD_ROOT'] = '..' # Adding until SCONS fixes there access issue to access SCONS_BUILD_ROOT and SCONS_TARGET_ROOT from SCONS ENV
  os.environ['TARGET_ROOT'] = '../..' # and not OS ENV CR 2939554
  os.environ['TOOLS_SCONS_ROOT'] = '../tools/build/scons'
  os.environ['PYTHONPATH'] = '../tools/build/scons/SCons/lib'


  if os.path.exists('build-log.txt'):
    print 'Renaming the previous build log...'
    index = 1
    while os.path.exists('build-log-%i.txt' % index):
      index += 1
    shutil.move('build-log.txt', 'build-log-%i.txt' % index)

  log = open('build-log.txt', 'w')
  dump_env(log)

  print 'Executing build command:\n\t' + build_cmd
  the_build = subprocess.Popen(build_cmd, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, shell=True)
  c = the_build.stdout.read(1)

  while c:
     log.write(c)
     sys.stdout.write(c)
     c = the_build.stdout.read(1)
  exit_code = the_build.wait()

  create_target_specific_build_artifacts()
  chipset = os.environ.get('CHIPSET')
  GenerateXML("build-cfg-%s.xml" %chipset)

  if exit_code == 0:
    generate_memsizes()
  sys.exit(exit_code)

def print_build_time(start):
  stop = datetime.datetime.now()
  print '\n\n'
  print 'Build started:', str(start)
  print 'Build ended:  ', str(stop)
  print 'Elapsed time: ', str(stop - start)

def generate_memsizes():
    print 'Calculating driver mem sizes...'
    try:
        os.system('python mapread_hfam_splitmem.py ')
    except:
        print("Couldn't parse map file.\n Error:", sys.exc_info()[0])


if __name__ == '__main__':
  atexit.register(print_build_time, datetime.datetime.now())


  DEFAULT_BUILD_ID = 'AAAAANAZO'

  os.environ['BUILD_ID']  = 'AAAAANAZO'
  os.environ['BUILD_VER'] = os.environ.get('BLD_ENV_VER_NUM_COMPRESSED', '0')

  # This is workaround for the below issue found on a customer's build server:
  #     When built on Linux 3.x with Python2.6, sys.platform returns "linux3" and causes the Sectool to use OpenSSL binary
  #     for Windows on Linux platform and Singed image was not generated correctly.
  # we can remove this workaround when Sectool is updated and has CR 803998
  if sys.platform.startswith('linux') and sys.platform != 'linux2':
      if not 'OPENSSL_DIR' in os.environ:
          os.environ['OPENSSL_DIR'] = '/usr/bin'

  # if ARMPATH is not defined then auto-detect the compiler.
  #   otherwise assume that all the env variables are already set.
  if( os.environ.get('ARMPATH', 'none') == 'none' ):
    if find_compiler():
      start_build()
  else:
    write_setenv_files_from_environment()
    start_build()



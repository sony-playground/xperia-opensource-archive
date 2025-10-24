#  DAL configuration Tools library Custom Makefile
#
#  Copyright (c) 2015-2022, Qualcomm Technologies, Inc.
#  All rights reserved.
#  Qualcomm Technologies, Inc. Confidential and Proprietary

#=======================================README===========================================
# Device Config user adding new xml or updating existing xml need to update
# modify the following variables:
# 1]  INC_DEPS
# 2]  XML_DEPS
#
# XML_DEPS need to be modified if a user adds a config xml in DALConfigLib
# folder of any of its subdirectories. The proper path of the xml file needs
# to be appended to the variable XML_DEPS
#
# INC_DEPS need to be modified if the added config xml file includes (#include directive)
# any header file(s). Proper paths of the header files need to be appended to
# the variable INC_DEPS
# Nothing else should be modified in the file.
#
# Any xxxx.dec Package entries meant to be added in DALConfigLoaderLib.inf have to be
# now added to the DALGenLibLoader.inf
#========================================================================================


MACRO_NAME         =  loader
DEVCFG_CONFIG = 8550_xml

#
# Following macro i.e. INC_DEPS lists all the header files that
# are included in the xml files. Any new header file added in the
# config xml files need to be appended to the following list
#
INC_DEPS = $(WORKSPACE)/QcomPkg/Include/api/dal/*.h \
           $(WORKSPACE)/QcomPkg/SocPkg/Kailua/Settings/DALConfig/*.h \
           $(WORKSPACE)/QcomPkg/SocPkg/Include/GPIODevCfg.h \

#
# Following macro i.e. XML_DEPS lists all the xml config files that
# It also enlists any xml files which are #included by other xml files.
# Any new xml file added will need to be appended to the following list.
#
XML_DEPS = $(WORKSPACE)/QcomPkg/SocPkg/Kailua/Settings/TLMM/loader/TLMMChipset.xml \
           $(WORKSPACE)/QcomPkg/Settings/PlatformInfo/PlatformInfo.xml \
           $(WORKSPACE)/QcomPkg/SocPkg/Settings/DALSystem/$(MACRO_NAME)/dalsystem_$(MACRO_NAME).xml \
           $(WORKSPACE)/QcomPkg/Settings/ChipInfo/DalChipInfo.xml \
           $(WORKSPACE)/QcomPkg/SocPkg/Kailua/Settings/ICB/loader/icbcfg_boot.xml \

#=====================USERS NEED NOT EDIT ANYTHING BEYOND THIS LINE========================
INC = @$(MODULE_BUILD_DIR)/../DALGenLibLoader_LA/OUTPUT/inc.lst

DEVCFG_LIB = $(OUTPUT_DIR)/DALConfigLoaderLib.lib
#DEVCFG_XBLCONFIG_LIB = $(OUTPUT_DIR)/devcfgLoaderLib_xblconfig.lib
IMAGE_CFG_XML = $(WORKSPACE)/QcomPkg/SocPkg/Kailua/Settings/DALConfig/image_cfg.xml
CALLING_MAKE_FILE = $(WORKSPACE)/QcomPkg/SocPkg/Kailua/Settings/DALConfig/DALConfigLoaderLib_LA.mk

# \
!include <$(WORKSPACE)/QcomPkg/SocPkg/Settings/devcfg/devcfg_rules.mk>
# \

# \
!IF 0
  include $(WORKSPACE)/QcomPkg/SocPkg/Settings/devcfg/devcfg_rules.mk # \
!ENDIF

# \
#!include <$(WORKSPACE)/QcomPkg/SocPkg/Settings/devcfg/devcfg_xblconfig_rules.mk>
# \

# \
#!IF 0
#  include $(WORKSPACE)/QcomPkg/SocPkg/Settings/devcfg/devcfg_xblconfig_rules.mk # \
#!ENDIF

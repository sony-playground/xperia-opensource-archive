#define SPMI_MAX_CHANNELS_SUPPORTED 768
#define SPMI_MAX_OWNER_IDS 10

#define INIT_SPMI_DEV_GENERICS { \
  .mNumChannels            = SPMI_MAX_CHANNELS_SUPPORTED, \
  .mNumPortPriorities      = 7, \
  .mNumPvcPorts            = 4, \
  .mNumPvcPortPPIDs        = 8, \
  .mNumMasters             = SPMI_MAX_OWNER_IDS, \
  .mNumProgRamRegs         = 256, \
  .mNumPicAccStatusRegs    = 24, \
  .mNumVrmIds              = 256, \
  .mNumMgpiPorts           = 8, \
}

// TEMPORARY IGNORE FATAL ERROR FLAG FOR PRE-SI
#define SPMI_IGNORE_FATAL_FLAG 1


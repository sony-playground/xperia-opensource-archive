#ifndef DRV_MAPPING_H
#define DRV_MAPPING_H

#include "comdef.h"

typedef enum {
    RSC_DRV_GLOBAL_TZ            = 0,
    RSC_DRV_GLOBAL_HYP           = 1,
    RSC_DRV_GLOBAL_HLOS          = 2,
    RSC_DRV_GLOBAL_L3            = 3,
    RSC_DRV_GLOBAL_SECPROC       = 4,
    RSC_DRV_GLOBAL_AUDIO         = 5,
    RSC_DRV_GLOBAL_SENSORS       = 6,
    RSC_DRV_GLOBAL_AOP           = 7,
    RSC_DRV_GLOBAL_DEBUG         = 8,
    RSC_DRV_GLOBAL_GPU           = 9,
    RSC_DRV_GLOBAL_DISPLAY       = 10,
    RSC_DRV_GLOBAL_COMPUTE_DSP   = 11,
    RSC_DRV_GLOBAL_TME_SW        = 12,
    RSC_DRV_GLOBAL_TME_HW        = 13,
    RSC_DRV_GLOBAL_MODEM_SW      = 14,
    RSC_DRV_GLOBAL_MODEM_HW      = 15,
    RSC_DRV_GLOBAL_WLAN_RF       = 16,
    RSC_DRV_GLOBAL_WLAN_BB       = 17,
    RSC_DRV_GLOBAL_DDR_AUX       = 18,   //DDR AUX (new)
    RSC_DRV_GLOBAL_ARC_CPRF      = 19,
    RSC_DRV_GLOBAL_ARC_DEP       = 20,   //ARC GP TCS (new)
    RSC_DRV_GLOBAL_BCM           = 30,
    RSC_DRV_GLOBAL_RESERVED      = 31,
    RSC_DRV_GLOBAL_MAX,
} RSCSW_DRV_GLOBAL_V1_MAPPING;

#endif // DRV_MAPPING_H


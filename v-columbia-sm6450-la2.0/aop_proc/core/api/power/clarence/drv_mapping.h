#ifndef DRV_MAPPING_H
#define DRV_MAPPING_H

#include "comdef.h"

typedef enum {
    RSC_DRV_GLOBAL_TZ            = 0,
    RSC_DRV_GLOBAL_L3            = 1,
    RSC_DRV_GLOBAL_HLOS          = 2,
    RSC_DRV_GLOBAL_HYP           = 3,
    RSC_DRV_GLOBAL_AUDIO         = 4,
    RSC_DRV_GLOBAL_AOP           = 5,
    RSC_DRV_GLOBAL_DEBUG         = 6,
    RSC_DRV_GLOBAL_GPU           = 7,
    RSC_DRV_GLOBAL_DISPLAY       = 8,
    RSC_DRV_GLOBAL_COMPUTE_DSP   = 9,
    RSC_DRV_GLOBAL_TME_HW        = 10,
    RSC_DRV_GLOBAL_TME_SW        = 11,
    RSC_DRV_GLOBAL_WPSS          = 12,   
    RSC_DRV_GLOBAL_MODEM_SW      = 13,
    RSC_DRV_GLOBAL_MODEM_HW      = 14,
    RSC_DRV_GLOBAL_WLAN_RF       = 15,
	RSC_DRV_GLOBAL_WLAN_BB       = 16,
    RSC_DRV_GLOBAL_DDR_AUX       = 17,   //DDR AUX (new)
    RSC_DRV_GLOBAL_ARC_CPRF      = 18,
//	RSC_DRV_GLOBAL_ARC_DEP       = 19,   //ARC GP TCS (new)
    RSC_DRV_GLOBAL_BCM           = 29,
    RSC_DRV_GLOBAL_RESERVED      = 31,   
    RSC_DRV_GLOBAL_MAX,
} RSCSW_DRV_GLOBAL_V1_MAPPING;

#endif // DRV_MAPPING_H


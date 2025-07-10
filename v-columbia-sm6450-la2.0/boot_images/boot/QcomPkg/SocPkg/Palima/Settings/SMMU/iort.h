/** SMMU IORT Macros

Copyright (c) 2019 - 2021 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

#define IORT_WORLD_ID_NON_SECURE 0x0
#define IORT_WORLD_ID_SECURE     0x1
#define IORT_WORLD_ID_SHIFT      31

#define IORT_DYNAMIC_MAPPING_NO          0x0
#define IORT_DYNAMIC_MAPPING_YES_DEFAULT 0x0
#define IORT_DYNAMIC_MAPPING_YES         0x1
#define IORT_DYNAMIC_MAPPING_SHIFT       30

#define IORT_TRANSLATION_TYPE_S2_ONLY      0x0
#define IORT_TRANSLATION_TYPE_S2CR_BYPASS  0x1
#define IORT_TRANSLATION_TYPE_SINGLE_STAGE 0x1
#define IORT_TRANSLATION_TYPE_NESTED       0x3
#define IORT_TRANSLATION_TYPE_SHIFT        24

#define IORT_VMID_SHIFT 16


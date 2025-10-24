#ifndef __HAL_IOMMU_QUEUE_H__
#define __HAL_IOMMU_QUEUE_H__

/*==============================================================================
@file HAL_IOMMULib.h

    This file contains the function declarations for the LIB interface that
    other drivers can use to interact with the HAL_IOMMUDxe driver.

        Copyright (c) 2008,2010,2014 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

==============================================================================*/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/19/17   amo     Created

=============================================================================*/

/*------------------------------------------------------------------------------
* Include Files
*-----------------------------------------------------------------------------*/
#include "HALIOMMUTypes.h"

/*------------------------------------------------------------------------------
* Commands Declarations
*-----------------------------------------------------------------------------*/
typedef enum HAL_IOMMUv3_Command_Id_t {
    CMD_PREFETCH_CONFIG     = 0x1,
    CMD_PREFETCH_ADDR       = 0x2,
    CMD_CFGI_STE            = 0x3,
    CMD_CFGI_STE_RANGE      = 0x4,
    CMD_CFGI_ALL            = 0x4,
    CMD_CFGI_CD             = 0x5,
    CMD_CFGI_CD_ALL         = 0x6,
    CMD_CFGI_VMS_PIDM       = 0x7,
    CMD_TLBI_NH_ALL         = 0x10,
    CMD_TLBI_NH_ASID        = 0x11,
    CMD_TLBI_NH_VA          = 0x12,
    CMD_TLBI_NH_VAA         = 0x13,
    CMD_TLBI_EL3_ALL        = 0x18,
    CMD_TLBI_EL3_VA         = 0x1A,
    CMD_TLBI_EL2_ALL        = 0x20,
    CMD_TLBI_EL2_ASID       = 0x21,
    CMD_TLBI_EL2_VA         = 0x22,
    CMD_TLBI_EL2_VAA        = 0x23,
    CMD_TLBI_S12_VMALL      = 0x28,
    CMD_TLBI_S2_IPA         = 0x2A,
    CMD_TLBI_NSNH_ALL       = 0x30,
    CMD_ATC_INV             = 0x40,
    CMD_PRI_RESP            = 0x41,
    CMD_RESUME              = 0x44,
    CMD_STALL_TERM          = 0x45,
    CMD_SYNC                = 0x46,
    CMD_TLBI_S_EL2_ALL      = 0x50,
    CMD_TLBI_S_EL2_ASID     = 0x51,
    CMD_TLBI_S_EL2_VA       = 0x52,
    CMD_TLBI_S_EL2_VAA      = 0x53,
    CMD_TLBI_S_S12_VMALL    = 0x58,
    CMD_TLBI_S_S2_IPA       = 0x5A,
    CMD_TLBI_SNH_ALL        = 0x60,
    CMD_MAX                 = 0x7FFFFFFF,
}HAL_IOMMUv3_Command_Id_t;

typedef uint32 HAL_IOMMUv3_CMD_t[4];

typedef enum HAL_IOMMUv3_Event_Id_t {
    EVENT_F_UUT              = 0x1,
    EVENT_C_BAD_STREAMID     = 0x2,
    EVENT_F_STE_FETCH        = 0x3,
    EVENT_C_BAD_STE          = 0x4,
    EVENT_F_BAD_ATS_TREQ     = 0x5,
    EVENT_F_STREAM_DISABLED  = 0x6,
    EVENT_F_TRANSL_FORBIDDEN = 0x7,
    EVENT_C_BAD_SUBSTREAMID  = 0x8,
    EVENT_F_CD_FETCH         = 0x9,
    EVENT_C_BAD_CD           = 0xA,
    EVENT_F_WALK_EABT        = 0xB,
    EVENT_F_TRANSLATION      = 0x10,
    EVENT_F_ADDR_SIZE        = 0x11,
    EVENT_F_ACCESS           = 0x12,
    EVENT_F_PERMISSION       = 0x13,
    EVENT_F_TLB_CONFLICT     = 0x20,
    EVENT_F_CFG_CONFLICT     = 0x21,
    EVENT_E_PAGE_REQUEST     = 0x24,
    EVENT_F_VMS_FETCH        = 0x25,
    EVENT_IMPDEF_EVENT0      = 0xE0,
    EVENT_IMPDEF_EVENT_MAX   = 0xEF,
    EVENT_MAX                = 0x7FFFFFFF,    
}HAL_IOMMUv3_Event_Id_t;

typedef uint32 HAL_IOMMUv3_EVT_t[8];

#define HALIOMMUv3_PROD_INVALID 0xFFFFFFFF
#define HALIOMMUv3_CONS_INVALID 0xFFFFFFFF

#define DEFAULT_CMDQ_SIZE       0x1000
#define DEFAULT_EVENTQ_SIZE     0x1000

/*------------------------------------------------------------------------------
* Function Declarations
*-----------------------------------------------------------------------------*/

HAL_IOMMUResult_t HAL_IOMMUv3_CMD_PREFETCH_CONFIG(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 ssid, boolean ssv);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_PREFETCH_ADDR(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 ssid, boolean ssv, uint64 addr, uint32 size, uint32 stride);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_STE(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_STE_RANGE(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 range);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_ALL(uint64 smmu_base, int ns, uint32 *prod_session, boolean ssec);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_CD(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 ssid, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_CD_ALL(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_VMS_PIDM(uint64 smmu_base, int ns, uint32 *prod_session, boolean ssec, uint32 vmid);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_ALL(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_ASID(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint32 asid);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_VA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint32 asid, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_VAA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL3_ALL(uint64 smmu_base, int ns, uint32 *prod_session);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL3_VA(uint64 smmu_base, int ns, uint32 *prod_session, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_ALL(uint64 smmu_base, int ns, uint32 *prod_session);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_ASID(uint64 smmu_base, int ns, uint32 *prod_session, uint32 asid);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_VA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 asid, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_VAA(uint64 smmu_base, int ns, uint32 *prod_session, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S12_VMALL(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S2_IPA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NSNH_ALL(uint64 smmu_base, int ns, uint32 *prod_session);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_ATC_INV(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, uint32 ssid, boolean ssv, boolean global, uint64 addr, uint32 size);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_PRI_RESP(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, uint32 ssid, boolean ssv, uint32 prgidx, uint32 rsp);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_RESUME(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 stag, boolean action, boolean abort);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_STALL_TERM(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_SYNC(uint64 smmu_base, int ns, uint32 *prod_session, uint32 compsig, uint64 msi_addr, uint32 msi_data, uint32 msi_attr);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_ALL(uint64 smmu_base, uint32 *prod_session);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_ASID(uint64 smmu_base, uint32 *prod_session, uint32 asid);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_VA(uint64 smmu_base, uint32 *prod_session, uint32 asid, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_VAA(uint64 smmu_base, uint32 *prod_session, uint64 addr, boolean leaf);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_S12_VMALL(uint64 smmu_base, uint32 *prod_session, uint32 vmid);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_S2_IPA(uint64 smmu_base, uint32 *prod_session, uint32 vmid, uint64 addr, boolean leaf, boolean ns);
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_SNH_ALL(uint64 smmu_base, uint32 *prod_session);

HAL_IOMMUResult_t HAL_IOMMUv3_Process_CMDs(uint64 smmu_base, int ns, uint32 *prod_session);
HAL_IOMMUResult_t HAL_IOMMUv3_Process_EVTs(uint64 smmu_base, int ns);

#endif /* __HAL_IOMMU_QUEUE_H__ */

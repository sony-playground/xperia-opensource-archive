/**---------------------------------------------------------------------------
 *   @file        usb4_operation.h
 *
 *   @brief   Header file for a full USB4 API
 *
 *   Copyright (c) 2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef __USB4_OPERATION_H__
#define __USB4_OPERATION_H__

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVHAL_usb4_comdef.h"
 
#pragma pack(push)
#pragma pack(1)

typedef struct
{
    UINT32 reserved_0   :  2;
    UINT32 NVMoffset    : 22;
    UINT32 len          :  4;
    UINT32 reserved_1   :  4;
} NVM_Metadata;

// AT/RT Command Data Symbols (table 4-12)
typedef struct
{
    UINT8 reg :8;
    UINT8 len :7;
    UINT8 wnr :1;
    UINT8 pData[64];
} USB4_AtRt_DataSym;

//table 8-56
typedef struct
{
    UINT32 port            :6;
    UINT32 adapter         :3;
    UINT32 pattern         :4;
    UINT32 preset          :4;
    UINT32 setModification :1;
    UINT32 modifications   :8;
    UINT32 Reserved        :6;
} USB4_setTxCompliance;

//table 8-57
typedef struct
{
    UINT32 port     :6;
    UINT32 adapter  :3;
    UINT32 reserved :23;
} USB4_setRxCompliance;

//table 8-58
typedef struct
{
    UINT32 port            :6;
    UINT32 adapter         :3;
    UINT32 pattern         :4;
    UINT32 reserved        :19;
} USB4_startBerTest;

//table 8-59
typedef struct
{
    UINT32 port            :6;
    UINT32 adapter         :3;
    UINT32 reserved        :23;
} USB4_endBerTest;

//table 8-60
typedef struct
{
// TODO: AC definition inconsistent with size    UINT32 countDWLow       ; 
    UINT32 countDWHigh     :16;
    UINT32 errCount        :16;
} USB4_endBerTestData;

//table 8-61
typedef struct
{
    UINT32 port            :6;
    UINT32 adapter         :3;
    UINT32 reserved        :23;
} USB4_endBurstTest;

//table 8-63
typedef struct
{
    UINT32 port            :6;
    UINT32 adapter         :3;
    UINT32 reserved        :23;
} USB4_readBurstTest;

//ENTER_EI_TEST Operation Metadata (table 8-65)
typedef struct
{
    UINT32 port     :6;
    UINT32 adapter  :3;
    UINT32 reserved :23;
} USB4_enterEiState;

//table 8-66
typedef struct
{
    UINT32 enterOfflineMode :1;
    UINT32 reserved         :31;
} USB4_routerOfflineMode;

//table 8-67
typedef struct
{
    UINT32 rcvLaneMargModes         :2;
    UINT32 twoLaneMarg              :1;
    UINT32 indepHighLowVoltMarg     :2;
    UINT32 timeMarg                 :1;
    UINT32 voltMargStepsMand        :7;
    UINT32 maxVoltOffsetMand        :6;
    UINT32 optVoltOffsetRange        :1;
    UINT32 voltMargStepsOpt         :7;
    UINT32 _res1                    :5;

    UINT32 maxVoltOffsetOpt         :8;
    UINT32 destrTimeMarg            :1;
    UINT32 indepLeftRightTimeMarg   :2;
    UINT32 timeMargStep             :5;
    UINT32 maxTimeOffset            :5;
    UINT32 minBERLevContSupport     :5;
    UINT32 maxBERLevContSupport     :5;
    UINT32 _res2                    :1;
} USB4_readLaneMargingCap;

//table 8_68 
typedef struct
{
    UINT32 laneSelect           :3;
    UINT32 timingMarginTest     :1;
    UINT32 enableMarginTests    :1; 
    UINT32 berLevelCounter      :5;
    UINT32 enableVoltageOffset  :1;
    UINT32 reseved              :21;
} USB4_runHwLaneMargining;

//table 8-71 
typedef struct
{
    UINT32  laneSelect              :3;
    UINT32  timingMargTest          :1;
    UINT32  enableMargTest          :1;
    UINT32  enableVoltageOffsetRange     :1;
    UINT32  voltageOffset           :7;
    UINT32  errorCounter            :2;
    UINT32  reserved                :17;
} USB4_runSwLaneMarg;

//table 8-67
typedef struct
{
    UINT32 errCountLane0    :4;
    UINT32 errCountLane1    :4;
    UINT32 _res             :24;
} USB4_readSwMargingErr;

#pragma pack(pop)

typedef enum
{
    USB4_PORT_OPERATION_SET_TX_COMP          = 0x4D435854,
    USB4_PORT_OPERATION_SET_RX_COMP          = 0x4D435852,
    USB4_PORT_OPERATION_START_BER_TEST       = 0x52454253,
    USB4_PORT_OPERATION_END_BER_TEST         = 0x52454245,
    USB4_PORT_OPERATION_END_BURST_TEST       = 0x52454242,
    USB4_PORT_OPERATION_READ_BRUST_TEST      = 0x52454252,
    USB4_PORT_OPERATION_ENTER_EI_TEST        = 0x54494545,
    USB4_PORT_OPERATION_ROUTER_OFFLINE_MODE  = 0x4e45534c,
    USB4_PORT_OPERATION_ENUMERATE_RETIMERS   = 0x4D554E45,
    USB4_PORT_OPERATION_READ_LANE_MARGIN_CAP = 0x50434452,
    USB4_PORT_OPERATION_RUN_HW_LANE_MARG     = 0x474D4852,
    USB4_PORT_OPERATION_RUN_SW_LANE_MARG     = 0x474D5352,
    USB4_PORT_OPERATION_READ_SW_MARG_ERR     = 0x57534452,
    /* operation completion indicated by OPCODE register acc. to 8.3.2 Port Operations */
    USB4_PORT_OPERATION_RC_SUCCESS           = 0,
    USB4_PORT_OPERATION_RC_NOT_SUPP          = 0x444D4321,   // '!CMD'
    USB4_PORT_OPERATION_RC_FAIL              = 0x20525245    // 'ERR '
} USB4_PORT_OPERATION;


/*table 4-15*/
typedef enum
{
    USB4_SB_REG_VENDOR_ID          = 0,
    USB4_SB_REG_PRODUCT_ID         = 1,
    USB4_SB_REG_TBT3_MODE          = 3,
    USB4_SB_REG_TBT3_TYPE          = 4,
    USB4_SB_REG_OPCODE             = 8,
    USB4_SB_REG_METADATA           = 9,
    USB4_SB_REG_LNK_CONFIG         = 12,
    USB4_SB_REG_TXFFE              = 13,
    USB4_SB_REG_SB_CHANNEL_VER     = 15,
    USB4_SB_REG_VENDOR_SPECIFIC_0  = 16, 
    USB4_SB_REG_VENDOR_SPECIFIC_1  = 17,
    USB4_SB_REG_DATA               = 18,
} USB4_sb_regs;

typedef enum
{
    USB4_SB_PORT_ACCESS     = 0,
    USB4_SB_AT_CMD          = 1,
    USB4_SB_RT_CMD          = 2,
    USB4_SB_NEAR_RT         = 6,
    USB4_SB_FAR_RT          = 7,
} USB4_sb_target;

typedef enum
{
    USB4_SB_WNR_READ = 0,
    USB4_SB_WNR_WRITE = 1,
} USB4_sb_wnr;

typedef struct
{
    USB4_PORT_OPERATION op_code;
    UINT8* metaData;
    UINT8* data;
    UINT8 metaDataDwNum;
    UINT8 dataDwNum;
    UINT8 ComplMetaDataDwNum;
    UINT8 ComplDataDwNum;
} USB4_port_operation;

#endif /* __USB4_OPERATION_H__ */


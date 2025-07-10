#ifndef __CLK_PEGGING_TOOL_H__
#define __CLK_PEGGING_TOOL_H__


/*
 * Macros
 */
#define CLK_DTB_LINE_BUF_SIZE 0x100
#define MAX_THRESHOLD 0x3FFF
#define RPMH_BCM_CD_TH_CD_ADDR 0x0BBE3800
#define TCS_CFG_VOTE_DATA_ADDR 0x0BBE5680
#define CD_Size 0x40 
#define CP_Size 0x4  
#define MAX_CPS 0x10 
#define CMD0_DATA_MASK 0xF
#define INVALID_CD_ID 0xFF
#define SND_LUT_ADDR 0x0bbe0500 
#define SW_CP_CD_ADDR 0x0bbf2600
#define MAX_SUPPORTED_CLK_PLAN 0x7

/*
 * VCD idx Macro
 */       
#define VCD_MC_ID        0
#define VCD_SHUB_ID      1
#define VCD_PKA_ID       2
#define VCD_SYS_NOC_ID   3
#define VCD_MMNOC_ID     4
#define VCD_CNOC_ID      5
#define VCD_CE_ID        6
#define VCD_IPA_ID       7
#define VCD_QUPV3_ID     8
#define VCD_CDSPNOC_ID   9
#define VCD_HWKM_ID      10

#define MIN_VOTE_VAL                   0x6002800A
#define BCM_VOTETABLE_DRVr_NDd(r,d)    (0x0BA00000 + (0x10000*r) + (0x4*d))

/* Note here we are using debug driver id to maintain the minimum votes to avoid collapse 
 * This driver id can be found at aop_proc\core\api\power\cedros\drv_mapping.h
 */

#define MC_VOTE_ADDR                    BCM_VOTETABLE_DRVr_NDd(6,0)   //bcm_phy_node_idx:-0
#define SHUB_VOTE_ADDR                  BCM_VOTETABLE_DRVr_NDd(6,1)   //bcm_phy_node_idx:-1
#define SYS_NOC_VOTE_ADDR               BCM_VOTETABLE_DRVr_NDd(6,3)   //bcm_phy_node_idx:-4
#define MMNOC_VOTE_ADDR                 BCM_VOTETABLE_DRVr_NDd(6,10)  //bcm_phy_node_idx:-12
#define CNOC_VOTE_ADDR                  BCM_VOTETABLE_DRVr_NDd(6,12)  //bcm_phy_node_idx:-14
#define CE_VOTE_ADDR                    BCM_VOTETABLE_DRVr_NDd(6,13)  //bcm_phy_node_idx:-15
#define IPA_VOTE_ADDR                   BCM_VOTETABLE_DRVr_NDd(6,14)  //bcm_phy_node_idx:-not supported
#define QUPV3_CORE_2X_VOTE_ADDR         BCM_VOTETABLE_DRVr_NDd(6,15)  //bcm_phy_node_idx:-17
#define CDSPNOC_VOTE_ADDR               BCM_VOTETABLE_DRVr_NDd(6,17)  //bcm_phy_node_idx:-20
#define HWKM_VOTE_ADDR               BCM_VOTETABLE_DRVr_NDd(6,x)  //bcm_phy_node_idx: not supported
#define PKA_VOTE_ADDR               BCM_VOTETABLE_DRVr_NDd(6,x)  //bcm_phy_node_idx: not supported

/*
 * Below structure are taken from 
 * 1. QcomPkg/SDM670Pkg/Library/ClockTargetLib/ClockAOP.c
 * 2. QcomPkg/Library/CoreUtilsLib/CoreMsgRam.c
 * Make sure these are in sync always to update MC and SHUB clock plans in the SMEM
 */
#define SMEM_TABLE_MAX_SIZE     0xA

typedef struct
{
  uint32 smem_id;
  uint32 addr;
} smem_addr_t;

typedef struct
{
  uint32      initialized;                //filled in by XBL once the table is initialized
  uint32      num_addrs;                   //size of the smem lookup table
  smem_addr_t table[SMEM_TABLE_MAX_SIZE];  //table of smem addresses
} aop_smem_table_t;

extern aop_smem_table_t *smem_table;

typedef struct{
  char *name;
  uint8 id;            //VCD index in the hardware
  uint8 minperflevel;
  uint8 maxperflevel;
  uint32 vote_addr;   // used to place minimum vote to avoid collapse
  uint32 nMax_hlvl;  //Maximum supported ICB map corner
}dfs_domains;

typedef enum{
  CDSPNOC_IDX,
  CE_IDX,
  CNOC_IDX,
  DDRMC_IDX,
  HWKM_IDX,
  IPA_IDX,
  MMNOC_IDX,
  PKA_IDX,
  QUPV3_IDX,
  SHUB_IDX,
  SNOC_IDX
}DFS_TABLE_IDX_ENUMS;

typedef struct {
  uint32_t  cx_corner[2];        /* [0] = VLVL, [1] = HLVL*/
  uint32_t  ddr_min_max_freq[2];
  uint32_t  shub_min_max_freq[2];
  uint32_t bUserCfgValid;
} ClkPeggingDataType;


//void boot_log_message(char * message);
int snprintf(char *restrict s, size_t n, const char *restrict fmt, ...);
boolean DDR_SetBIMCSpeed(uint32 nFreqKHz );

#endif
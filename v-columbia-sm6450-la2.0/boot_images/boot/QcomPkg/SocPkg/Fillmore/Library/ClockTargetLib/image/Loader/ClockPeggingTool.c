#include <stdlib.h>
#include <stdio.h>
#include "HALclkHWIO.h"
#include "HALClkBCMHWIO.h"
#include "smem_type.h"
#include "ddr_aop_params.h"
#include "ddr_drivers.h"
#include "boot_logger.h"
#include "DTBExtnLib.h"
#include "ClockPeggingTool.h"
#include "busywait.h"
#define CLK_PEGGING_NODE "/sw/clk_pegging_node"
#include "boot_crashdump.h"

static ddr_clock_plan MCPlan, SHUBPlan;
static FREQ_STATE *mc_states;     /* This variable is used to update the ddr clockplan data shared to aop by  boot ddr driver this data only used by ddr_manager in the aop image */
static FREQ_STATE *shub_states;   /* This variable is used to update the shub clockplan data shared to aop by boot ddr driver this data only used by ddr_manager in the aop image */

static uint8 nCpMin, nCpMax;
static uint8 gDDR_nCpMin, gDDR_nCpMax;
static uint8 gSHUB_nCpMin, gSHUB_nCpMax;

ClkPeggingDataType gClkPegData;
static char buffer[CLK_DTB_LINE_BUF_SIZE];

dfs_domains dfs_table[] = {
  [0]={
    .name = "cdspnoc",
    .id = VCD_CDSPNOC_ID,
    .vote_addr = CDSPNOC_VOTE_ADDR,
    .nMax_hlvl = 7,
      },
  [1]={
    .name = "ce",
    .id = VCD_CE_ID,
    .vote_addr = CE_VOTE_ADDR,
    .nMax_hlvl = 6,
      },
  [2]={
    .name = "cnoc",
    .id = VCD_CNOC_ID,
    .vote_addr = CNOC_VOTE_ADDR,
    .nMax_hlvl = 6,
      },
  [3]={
    .name = "ddrmc",
    .id = VCD_MC_ID,
    .vote_addr = MC_VOTE_ADDR,
    .nMax_hlvl = 7,
      },
  [4]={
    .name = "ipa",
    .id  = VCD_IPA_ID,
    .vote_addr = IPA_VOTE_ADDR,
    .nMax_hlvl = 6,
      },
  [5]={
    .name = "mmnoc",
    .id = VCD_MMNOC_ID,
    .vote_addr = MMNOC_VOTE_ADDR,
    .nMax_hlvl = 6,
      },
  [6]={
    .name = "qupv3_core_2x",
    .id = VCD_QUPV3_ID,
    .vote_addr = QUPV3_CORE_2X_VOTE_ADDR,
    .nMax_hlvl = 5,
      },
  [7]={
    .name = "shub",
    .id = VCD_SHUB_ID,
    .vote_addr = SHUB_VOTE_ADDR,
    .nMax_hlvl = 7,
      },
  [8]={
    .name = "sys_noc",
    .id = VCD_SYS_NOC_ID,
    .vote_addr = SYS_NOC_VOTE_ADDR,
    .nMax_hlvl = 6,
      },
};


/* =========================================================================
**  Function : Clock_InitPeggingToolData
** Reads the dts file to get user configs
** =========================================================================*/

void Clock_InitPeggingToolData(void)
{
  int32_t  nFdtResult;
  void    *fdt_handle = NULL;
  fdt_node_handle hNode;
  static boolean bInitCompleted = FALSE;

  if(bInitCompleted) return;
  bInitCompleted = TRUE;

  nFdtResult = fdt_get_blob_handle(&fdt_handle, DEFAULT_BLOB_ID);
  if (0 != nFdtResult)
    return;
  nFdtResult = fdt_get_node_handle(&hNode, fdt_handle, CLK_PEGGING_NODE);
  if (nFdtResult != 0) return;
  nFdtResult |= fdt_get_boolean_prop(&hNode, "test_mode", &(gClkPegData.bUserCfgValid));
  if (0 != nFdtResult || gClkPegData.bUserCfgValid == 0){
    snprintf(buffer, CLK_DTB_LINE_BUF_SIZE, "Pegging-tool : Result is %x and test_mode is %x\n",
        nFdtResult, gClkPegData.bUserCfgValid);
    boot_log_message(buffer);
    return;
  }
  nFdtResult |= fdt_get_uint32_prop_list(&hNode, "cx_corner", (uint32_t *)&(gClkPegData.cx_corner), sizeof(gClkPegData.cx_corner));
  nFdtResult |= fdt_get_uint32_prop_list(&hNode, "ddr_min_max_freq", (uint32_t *)&(gClkPegData.ddr_min_max_freq), sizeof(gClkPegData.ddr_min_max_freq));
  nFdtResult |= fdt_get_uint32_prop_list(&hNode, "shub_min_max_freq", (uint32_t *)&(gClkPegData.shub_min_max_freq), sizeof(gClkPegData.shub_min_max_freq));
  if (0 == nFdtResult) {
    snprintf(buffer, CLK_DTB_LINE_BUF_SIZE, "/sw/clk_pegging_node : cx_corner[%x]..ddr_min_max[%x]..shub_min_max[%x]\n",
        gClkPegData.cx_corner, gClkPegData.ddr_min_max_freq, gClkPegData.shub_min_max_freq);
    boot_log_message(buffer);
  } else {
    boot_log_message("Error in reading /sw/clk_pegging_node data");
  }
  return;
}

/* =========================================================================
**  Function : Clock_UpdateDDRMinMax
**  Updates MC VCD's Min and Max Perf-levels based on user inputs
** =========================================================================*/

static void Clock_UpdateDDRMinMax(void)
{

  MCPlan = ddr_clock_query(MC_CLOCK_PLAN);
  uint8 cp = 0;

  if(gClkPegData.cx_corner[0] != 0xFFFF && gClkPegData.ddr_min_max_freq[0] == 0xff && gClkPegData.ddr_min_max_freq[1] == 0xff)
  {
    for(int i=0; i<MCPlan.num_levels; i++)
    {
      if(MCPlan.state[i].freq_enable == FALSE)
      {
        continue;
      }
      if(MCPlan.state[i].vddcx <= gClkPegData.cx_corner[0]  &&  MCPlan.state[i].freq_enable == TRUE) 
      {
        nCpMin = i;
        nCpMax = i;
      }
      else if(MCPlan.state[i].vddcx > gClkPegData.cx_corner[0] )
      {
        break;
      }
    }
  }
  else
  {
    nCpMin = gClkPegData.ddr_min_max_freq[0];
    nCpMax = gClkPegData.ddr_min_max_freq[1];
  }
    cp = 0;
  while (cp < nCpMin && cp < MCPlan.num_levels)
  {
    mc_states[cp].freq_enable = FALSE;
    cp++;
  }
  cp = nCpMax+1;
  while (cp < MCPlan.num_levels)
  {
    mc_states[cp].freq_enable = FALSE;
    cp++;
  }
  /* Placing a minimum vote from unused driver, to avoid collapse*/
  if(nCpMin != 0)
  {
    out_dword((uint32)MC_VOTE_ADDR, (uint32)MIN_VOTE_VAL);
    while( 0 == HWIO_IN(STATUS_BCM) );
  }
  gDDR_nCpMin = nCpMin;
  gDDR_nCpMax = nCpMax;

  /* scaling the BIMC to settle the clock to updated table */
  DDR_SetBIMCSpeed(mc_states[nCpMin].freq_khz);
}

/* =========================================================================
**  Function : Clock_UpdateShubMinMax
**  Updates SHUB VCD's Min and Max Perf-levels based on user inputs
** =========================================================================*/

static void Clock_UpdateShubMinMax(void)
{
  
  SHUBPlan = ddr_clock_query(SHUB_CLOCK_PLAN);
  uint8 cp = 0;
  
  if(gClkPegData.cx_corner[0] != 0xFFFF)
  {
    for(int i=0; i<SHUBPlan.num_levels; i++)
    {
      if(SHUBPlan.state[i].freq_enable == FALSE)
      {
        continue;
      }
      if(SHUBPlan.state[i].vddcx <= gClkPegData.cx_corner[0]) 
      {
        nCpMin = i;
        nCpMax = i;
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    nCpMin = gClkPegData.shub_min_max_freq[0];
    nCpMax = gClkPegData.shub_min_max_freq[1];
  }

  cp = 0;
  while (cp < nCpMin && cp < SHUBPlan.num_levels )
  {
    shub_states[cp].freq_enable = FALSE;
    cp++;
  }
  cp = nCpMax+1;
  while( cp < SHUBPlan.num_levels )
  {
    shub_states[cp].freq_enable = FALSE;
    cp++;
  }
  /* Placing a minimum vote from unused driver, to avoid collapse, incase of  */
  if(nCpMin != 0)
  {
    out_dword((uint32)SHUB_VOTE_ADDR, (uint32)MIN_VOTE_VAL);
    while( 0 == HWIO_IN(STATUS_BCM) );
  }
  gSHUB_nCpMin = nCpMin;
  gSHUB_nCpMax = nCpMax;
}

/* =========================================================================
**  Function : Clock_InitMCShubhandles
** =========================================================================*/

int Clock_InitMCShubhandles()
{
  uint32 smem_index = 0;
  char *pSMEM = NULL;
  uint32 *smem_addr = NULL;
  smem_addr = (uint32 *)&pSMEM;
  ddr_smem_info *ddr_smem_info_ptr;
  for (smem_index = 0; smem_index < smem_table->num_addrs; smem_index++)
  {
    if(smem_table->table[smem_index].smem_id == (uint32)DDR_AOP_SMEM_ID)
    {
      *smem_addr = smem_table->table[smem_index].addr; /* Updating the pSMEM value to point to the DDR_AOP smem_table */
      ddr_smem_info_ptr = (ddr_smem_info *)pSMEM;
      if(ddr_smem_info_ptr)
      {
        *smem_addr = (*smem_addr)+ddr_smem_info_ptr->shared_table_header[MC_STATES].offset; /* Updating the pSMEM value to point to the DDR clockplan in the smem_table */
        mc_states = (FREQ_STATE *)pSMEM;
        /*re-assign the smem_addr to base to get shub addr with offset from base*/
        *smem_addr = smem_table->table[smem_index].addr; /* Updating the pSMEM value to point to the DDR_AOP smem_table */
        *smem_addr = (*smem_addr)+ddr_smem_info_ptr->shared_table_header[SHUB_STATES].offset; /* Updating the pSMEM value to point to the SHUB clockplan in the smem_table */
        shub_states= (FREQ_STATE *)pSMEM;
      }
    }
  }
  return pSMEM!=NULL?0:1;
}

/* =========================================================================
**  Function : Clock_UpdateMCShubMinMaxFreq
** =========================================================================*/

void Clock_UpdateMCShubMinMaxFreq()
{
  Clock_InitPeggingToolData();
  /*If its normal boot then return simply..*/
  if(gClkPegData.bUserCfgValid == 0x0)
  {
    return; 
  }
  /*DTB has valid request. so, update the DDR/SHUB tables.*/
  Clock_InitMCShubhandles();
  Clock_UpdateDDRMinMax();
  Clock_UpdateShubMinMax();
  return;
}

/* =========================================================================
**  Function : Clock_UpdateVCDMinMax
**  Updates VCD's Min and Max Perf-Levels based on user inputs
** =========================================================================*/

void  Clock_UpdateVCDMinMaxFreq
(
  dfs_domains  *dfs_domain
)
{
  uint32 nAddr = 0, v_addr = 0, hlvl = 0;
  uint32 s,c,n;
  uint8 cp = 0, cp_index = 0;

  /* return if the Clock Domain is Invalid */
#if 0
  if (dfs_domain->id == VCD_MC_ID || dfs_domain->id == VCD_SHUB_ID)
  {
    return ;
  }
#endif

  if(gClkPegData.cx_corner[0] != 0xFFFF)
  {
    cp_index = 0;
    v_addr = TCS_CFG_VOTE_DATA_ADDR + dfs_domain->id * CD_Size;
    hlvl = in_dword(v_addr) & CMD0_DATA_MASK; // extract the voltage vote data
    while ( hlvl < gClkPegData.cx_corner[1])
    {
      cp_index++;
      v_addr+=CP_Size;
      hlvl = in_dword(v_addr) & CMD0_DATA_MASK; // check the next cp hlvl data
      if((0x0 == hlvl) || (hlvl == dfs_domain->nMax_hlvl))  
      {
        break;    // if next-cp hlvl is 0x0 i.e no valid entry break the loop
      }
    }
    if(hlvl > gClkPegData.cx_corner[1]) cp_index--;

    //picking the fmax at given corner if multiple clk-plans exists
    if( hlvl ==gClkPegData.cx_corner[1] )
    {
      while(hlvl ==gClkPegData.cx_corner[1] && cp_index < MAX_SUPPORTED_CLK_PLAN)
      {
        v_addr+=CP_Size;
        hlvl = in_dword(v_addr) & CMD0_DATA_MASK; 
        cp_index++;
      }
    cp_index--;
    }
    nCpMin = cp_index;
    nCpMax = cp_index;
  }
  else
  {
    return;
  }

  /* Updating the Latency table for DDR VCD */
  if (dfs_domain->id == 0)
  {
    for(s = 0; s<2 ;s++ )
      for ( c=0 ; c < 3; c++)
        for ( n=0 ; n<10 ; n++)
        {
          v_addr = SND_LUT_ADDR + 0x100*s + 0x40*c + 0x4*n;
          out_dword(v_addr,0x3FFF);
        }
    v_addr =0;
  }

  nAddr = RPMH_BCM_CD_TH_CD_ADDR + dfs_domain->id*CD_Size;

  if(dfs_domain->id == VCD_MC_ID)
  {
    nCpMin = gDDR_nCpMin;
    nCpMax = gDDR_nCpMax;
  }
  if(dfs_domain->id == VCD_SHUB_ID)
  {
    nCpMin = gSHUB_nCpMin;
    nCpMax = gSHUB_nCpMax;
  }

  /* zero out the threshold entries below nCpMin */
  for(cp = 0; cp < nCpMin && cp < MAX_CPS; cp++)
  {
    if (in_dword(nAddr) == MAX_THRESHOLD) break;
    out_dword(nAddr,0x0);
    nAddr += CP_Size;
  }
  
  /* Don't change the Threshold data between nCpMin and nCpMax */
  for(cp = nCpMin; cp < nCpMax; cp++)
  {
    if (in_dword(nAddr) == MAX_THRESHOLD) break;
    nAddr += CP_Size;
  }

  /* Write 0x3FFF to the above nCpMax index */
  if(cp < 16)
  {
    out_dword(nAddr,MAX_THRESHOLD);
  }

  /* Placing a minimum vote from unused driver to avoid collapse*/
  if(nCpMin != 0)
  {
    out_dword(dfs_domain->vote_addr, (uint32)MIN_VOTE_VAL);
    while( 0 == HWIO_IN(STATUS_BCM) );
  }
  return;
}

/* =========================================================================
**  Function : Clock_UpdateVCDsMinMaxFreq
** =========================================================================*/

void Clock_UpdateVCDsMinMaxFreq(void)
{
  uint8 nIdx = 0;

  /*Incase of ramdump path, return*/
  if(boot_dload_is_dload_mode_set()) {
     return;
  }
  Clock_InitPeggingToolData();
  /*Return if its normal boot.*/
  if(gClkPegData.bUserCfgValid == 0x0)
  {
    return; 
  }
  /*Wait for AOP to initialize before updating the clock-rinit */
  while (in_dword(0xBBF2E00)>>31 ==0) busywait(5);
  //HWIO_OUTF(RPMH_BCM_STARC_CTRL,STARC_EN,0);
  out_dword(0xBBF2E00, 0x2BB);  /* Disabling the STARC */
  while(nIdx < sizeof(dfs_table)/sizeof(dfs_table[0]))
  {
    Clock_UpdateVCDMinMaxFreq(&dfs_table[nIdx]);
    nIdx++;
  }
  return;
}

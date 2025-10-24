/*===========================================================================
                              target_aop_services.c

DESCRIPTION:

Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "cpr_fuses_hwio.h"
#include "msmhwio.h"
#include "pwr_utils_lvl.h"
#include "cmd_db.h"
#include "cmd_db_aop.h"
#include "CoreVerify.h"
#include "drv_mapping.h"
#include "ChipInfo.h"
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------


#define SIZE_OF_ARRAY(arr) (sizeof(arr)/sizeof(arr[0]))
//pretty naming
#define _OFF        RAIL_VOLTAGE_LEVEL_OFF
#define _RET        RAIL_VOLTAGE_LEVEL_RET
#define _MIN_SVS    RAIL_VOLTAGE_LEVEL_MIN_SVS
#define _LOW_SVS    RAIL_VOLTAGE_LEVEL_LOW_SVS
#define _LSVS_L1    RAIL_VOLTAGE_LEVEL_LOW_SVS_L1
#define _LSVS_L2    RAIL_VOLTAGE_LEVEL_LOW_SVS_L2
#define _SVS        RAIL_VOLTAGE_LEVEL_SVS
#define _SVS_L0     RAIL_VOLTAGE_LEVEL_SVS_L0
#define _SVS_L1     RAIL_VOLTAGE_LEVEL_SVS_L1
#define _SVS_L2     RAIL_VOLTAGE_LEVEL_SVS_L2
#define _NOM        RAIL_VOLTAGE_LEVEL_NOM
#define _NOM_L1     RAIL_VOLTAGE_LEVEL_NOM_L1
#define _NOM_L2     RAIL_VOLTAGE_LEVEL_NOM_L2
#define _TUR        RAIL_VOLTAGE_LEVEL_TUR
#define _TUR_L1     RAIL_VOLTAGE_LEVEL_TUR_L1


typedef enum
{
  SW_MODES_BASE = 0xFF,
  SW_DIS_MSS_LVL,
}modes;

typedef struct tt
{
  modes  mode_values;                            
  uint32  rail_lvls[RAIL_VOLTAGE_LEVEL_NUM_LEVELS]; //1 : enable, 0: disable
}tt;

__attribute__((section("rinit_data_sec_pool2")))
static tt TRUTH_TABLE[] = //keep in sync with Enum of all SW corners in pwr_utils_lvl.h
{ // Keep this line static vlvl storage
  //CPR mode disable,
  {0xFF,               { 0x1,  _RET, _MIN_SVS, _LOW_SVS, _LSVS_L1, _LSVS_L2, _SVS, _SVS_L0, _SVS_L1, _SVS_L2, _NOM, _NOM_L1, _NOM_L2, _TUR, _TUR_L1,}},
  {1,                  {   1,     0,        0,        1,        1,        1,    1,       1,       1,       1,    1,       1,       1,    1,       1,}},
  {3,                  {   1,     0,        0,        0,        0,        0,    0,       0,       0,       0,    1,       1,       1,    1,       1,}},
  {7,                  {   1,     0,        0,        0,        0,        0,    0,       0,       0,       0,    1,       1,       1,    1,       1,}},
  {SW_DIS_MSS_LVL,     {   1,     0,        0,        0,        0,        0,    1,       1,       1,       0,    1,       1,       1,    1,       1,}},
};

uint16 aux_data_buffer[16]; //max this has to be RAIL_VOLTAGE_LEVELS
bool bypass_mode_disablement = FALSE;

__attribute__((section("rinit_code_sec_pool1")))
static uint32 find_and_replace_array(uint16* array, uint32 search_value, uint32 replace_value, uint32 size)
{
  uint32 i = -1;
  for(i = 1; i < size; i++)
  {
    if(array[i] == search_value)
    {
      array[i] = replace_value;
      break;
    }
  }
  return i;
}


/**
 * <!-- disable_rail_modes -->
 *
 * @brief disables certain modes for the resource. See
 *        Truth_table for more details on which modes will be
 *        disabled
 * 
 *  @param resource_name: eg: cx.lvl, mx.lvl (currently only arc
 *                      lvls are assumed)
 *  @param mode: mode to disable
 *  @return void: void
 */
__attribute__((section("rinit_code_sec_pool1")))
static void disable_rail_modes(const char* resource_name, uint32 mode)
{
  int i, j, index, replace_value = 0x0;

  // find len of aux data
  uint8 aux_len = (uint8) cmd_db_query_len(resource_name);

  CORE_VERIFY(aux_len != 0);

  // get the aux data in a buffer
  CORE_VERIFY(CMD_DB_SUCCESS == cmd_db_query_aux_data (resource_name, &aux_len, (uint8*)&aux_data_buffer));

  //find mode in the Truth table
  for(i=1; i < SIZE_OF_ARRAY(TRUTH_TABLE); i++)
  {
    if(mode == TRUTH_TABLE[i].mode_values)
    {
      //found the mode get the rail_lvls
      break;
    }
  }

  //check if we found something in truth table
  if(i == SIZE_OF_ARRAY(TRUTH_TABLE))
  {
    // found a mode we know nothing of
    return;
  }

  // i is the row
  for(j = 0; j < RAIL_VOLTAGE_LEVEL_NUM_LEVELS; j++)
  {
    if(TRUTH_TABLE[i].rail_lvls[j] == 1)
    {
      replace_value = TRUTH_TABLE[0].rail_lvls[j];
    }
    else
    {
                                     //arrary,        //find value                 //replace with  //data size
      index = find_and_replace_array(aux_data_buffer, TRUTH_TABLE[0].rail_lvls[j], replace_value,  aux_len/sizeof(uint16));
    }
  }
  
  CORE_VERIFY(CMD_DB_SUCCESS == cmd_db_modify_aux_data(resource_name, &aux_len, (uint8_t *)aux_data_buffer));
}

void disable_all_modes(void)
{
  disable_rail_modes("cx.lvl",0x3);
  disable_rail_modes("mx.lvl",0x3);
  disable_rail_modes("ebi.lvl",0x3);
  disable_rail_modes("lcx.lvl",0x3);
  disable_rail_modes("lmx.lvl",0x3);
  disable_rail_modes("gfx.lvl",0x3);
  disable_rail_modes("mss.lvl",0x3);
  disable_rail_modes("ddr.lvl",0x3);
  disable_rail_modes("mmcx.lvl",0x3);
  disable_rail_modes("mxc.lvl",0x3);
}


uint32 g_some_vlvls_disabled = 0x0;

/**
 * <!-- mode_disablement_init -->
 *
 * @brief reads QFPROM_CORR_CALIB_ROW10_MSB to read disabled
 *        modes and then disable them in cmddb
 * 
 *  @param void: void
 *
 *  @return void: void
 */
__attribute__((section("rinit_code_sec_pool1")))
void mode_disablement_init(void)
{
  //read value from QFPROM fuse
  uint32 fuses = HWIO_IN(CALIBRATION40);
  uint32 fuses2 = HWIO_IN(CALIBRATION41);
  uint32 fuses3 = HWIO_IN(CALIBRATION74);

  uint32 top_bin_fuse_blown = HWIO_INF(QFPROM_CORR_PTE_ROW0_MSB, BIN_V_IDENTIFIER);

  if ((fuses == 0 && fuses2 == 0 && fuses3 == 0 && top_bin_fuse_blown == 0) ||
          (bypass_mode_disablement))
  {
    return;
  }

  g_some_vlvls_disabled = 1;

  if (top_bin_fuse_blown)
  {
    disable_all_modes();
    return;
  }

  //find MXC mode
  uint32 mxc_mode_0 =
      (fuses & HWIO_CALIBRATION40_CPR_MXC_MODE_DISABLE_0_BMSK)
      >>(HWIO_CALIBRATION40_CPR_MXC_MODE_DISABLE_0_SHFT);
  uint32 mxc_mode_1_2 = (fuses2 & HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_2_1_BMSK)
      >>(HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_2_1_SHFT);
  uint32 mxc_mode = (mxc_mode_1_2<<1)|mxc_mode_0;
  if (mxc_mode)
  {
    //disable MXC modes
    disable_rail_modes("mxc.lvl",mxc_mode);
  }

  //find MX mode
  uint32 mx_mode =
      (fuses & HWIO_CALIBRATION40_CPR_MX_MODE_DISABLE_BMSK)
      >>(HWIO_CALIBRATION40_CPR_MX_MODE_DISABLE_SHFT) ;
  if (mx_mode)
  {
    //disable MX modes
    disable_rail_modes("mx.lvl",mx_mode);
  }

  //find GFX mode
  uint32 gfx_mode = (fuses & HWIO_CALIBRATION40_CPR_GFX_MODE_DISABLE_BMSK)
      >> (HWIO_CALIBRATION40_CPR_GFX_MODE_DISABLE_SHFT);
  if (gfx_mode) //if not zero, must disable some modes
  {
    //disable gfx modes
    disable_rail_modes("gfx.lvl",gfx_mode);
  }

  //find MSS mode
  uint32 mss_mode = (fuses & HWIO_CALIBRATION40_CPR_MSS_MODE_DISABLE_BMSK)
      >> (HWIO_CALIBRATION40_CPR_MSS_MODE_DISABLE_SHFT);
  if (mss_mode) //if not zero, must disable some modes
  {
    //disable mss modes
    disable_rail_modes("mss.lvl",mss_mode);
  }

  uint32 cx_mode = (fuses & HWIO_CALIBRATION40_CPR_CX_MODE_DISABLE_BMSK)
      >> (HWIO_CALIBRATION40_CPR_CX_MODE_DISABLE_SHFT);
  if (cx_mode) //if not zero, must disable some modes
  {
    //disable cx modes
    disable_rail_modes("cx.lvl",cx_mode);
  }

  //find MMCX mode
  uint32 mmcx_mode =
       (fuses2 & HWIO_CALIBRATION41_CPR_MMCX_MODE_DISABLE_BMSK)
      >>(HWIO_CALIBRATION41_CPR_MMCX_MODE_DISABLE_SHFT) ;
  if (mmcx_mode)
  {
    //disable mmcx modes
    disable_rail_modes("mmcx.lvl",mmcx_mode);
  }

  //find SSC_CX mode
  uint32 ssc_cx_mode =
      (fuses2 & HWIO_CALIBRATION41_CPR_SSCCX_MODE_DISABLE_BMSK)
      >>(HWIO_CALIBRATION41_CPR_SSCCX_MODE_DISABLE_SHFT) ;
  if (ssc_cx_mode)
  {
    //disable SSC_CX modes
    disable_rail_modes("lcx.lvl",ssc_cx_mode);
  }

  //find LPI_MX mode
  uint32 lpi_mx_mode =
      (fuses2 & HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_BMSK)
      >>(HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_SHFT);
  if (lpi_mx_mode)
  {
    //disable LPI_MX modes
    disable_rail_modes("lmx.lvl",lpi_mx_mode);
  }

  //find NSPCX mode
  uint32 nspcx_mode =
      (fuses3 & HWIO_CALIBRATION74_CPR_NSPCX_MODE_DISABLE_BMSK)
      >>(HWIO_CALIBRATION74_CPR_NSPCX_MODE_DISABLE_SHFT);
  if (nspcx_mode)
  {
    //disable NSPCX modes
    disable_rail_modes("nsp.lvl",nspcx_mode);
  }

//DDR Mode disablement fuses not allocated.
#if 0
  //find DDR mode
  uint32 ddr_mode = (fuses & HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_DDR_MODE_DISABLE_BMSK)
                         >> (HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_DDR_MODE_DISABLE_SHFT);
  if (ddr_mode) //if not zero, must disable some modes
  {
    //disable DDR phy rail modes
    disable_rail_modes("ebi.lvl",ddr_mode);
  }
#endif

}

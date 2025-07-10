/*
==============================================================================

FILE:         HALclkAPCS.c

DESCRIPTION:
  This file contains the clock HAL code to control the APCS clocks.


==============================================================================

                             Edit History


==============================================================================
   Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>
#include "HALclkInternal.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"
#include "Drivers/ClockDxe/ClockDriver.h"        // for DALCLOCK_LOCK
#include "HALclkAPCS.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  Function : HAL_clk_EPSS_READ_VCINDEX
**
** ======================================================================== */


boolean HAL_clk_EPSS_READ_VCINDEX
(
  HAL_clk_APCSCPUType  eCore,
  uint32              *nVcIndex
)
{ 
    volatile boolean    bDCVSInProgress;
    uint32              nCount = 200;

    do{
      switch(eCore)
      {
        case HAL_CLK_APCS_CPU_CLUSTER0:
          bDCVSInProgress = HWIO_INF(EPSSSLOW_CLKDOM1_DCVS_IN_PROGRESS, STATUS);
          break;

        case HAL_CLK_APCS_CPU_CLUSTER1: 
          bDCVSInProgress = HWIO_INF(EPSSSLOW_CLKDOM2_DCVS_IN_PROGRESS, STATUS);
          break;

        case HAL_CLK_APCS_CPU_L3:
          bDCVSInProgress = HWIO_INF(EPSSSLOW_CLKDOM0_DCVS_IN_PROGRESS, STATUS);
          break;

         default:
          return FALSE;
      }
    }while ((--nCount) && bDCVSInProgress);


    switch(eCore)
    {
      case HAL_CLK_APCS_CPU_CLUSTER0: 
		  *nVcIndex = HWIO_INF(EPSSSLOW_CLKDOM1_DOMAIN_STATE, VC_IDX);
        break;

      case HAL_CLK_APCS_CPU_CLUSTER1: 
		  *nVcIndex =HWIO_INF(EPSSSLOW_CLKDOM2_DOMAIN_STATE, VC_IDX);
        break;

      case HAL_CLK_APCS_CPU_L3: 
		  *nVcIndex = HWIO_INF(EPSSSLOW_CLKDOM0_DOMAIN_STATE, VC_IDX);
        break;

      default:
        return FALSE;
    }
    return TRUE;

} /* END HAL_clk_EPSS_READ_VCINDEX */


/* ===========================================================================
**  Function : HAL_clk_EPSS_LUT_READ_FREQUENCY
**
** ======================================================================== */

boolean HAL_clk_EPSS_LUT_READ_FREQUENCY
(
  HAL_clk_APCSCPUType  eCore,
  uint32               nRow,
  uint32              *nClkSource,
  uint32              *nLVal
)
{
  /* Sanity check */
  if (eCore      >= HAL_CLK_APCS_CPU_TOTAL ||
      nRow       >= EPSS_LUT_MAX_ROWS       ||
      nClkSource == NULL                   ||
      nLVal      == NULL                   )
  {
    return FALSE;
  }

  /* Read program from the hardware. */
  switch(eCore)
  {
    case HAL_CLK_APCS_CPU_CLUSTER0:
		*nClkSource = HWIO_INFI(EPSSSLOW_CLKDOM1_DCVS_LUT_r_FREQUENCY, nRow, CLKSRC);
		*nLVal		= HWIO_INFI(EPSSSLOW_CLKDOM1_DCVS_LUT_r_FREQUENCY, nRow, LVAL);
      break;

    case HAL_CLK_APCS_CPU_CLUSTER1:
		*nClkSource = HWIO_INFI(EPSSSLOW_CLKDOM2_DCVS_LUT_r_FREQUENCY, nRow, CLKSRC);
		*nLVal		= HWIO_INFI(EPSSSLOW_CLKDOM2_DCVS_LUT_r_FREQUENCY, nRow, LVAL);
      break;

    case HAL_CLK_APCS_CPU_L3:
		*nClkSource = HWIO_INFI(EPSSSLOW_CLKDOM0_DCVS_LUT_r_FREQUENCY, nRow, CLKSRC);
		*nLVal		= HWIO_INFI(EPSSSLOW_CLKDOM0_DCVS_LUT_r_FREQUENCY, nRow, LVAL);
      break;

    default:
      return FALSE;
  }

  return TRUE;

} /* END HAL_clk_EPSS_LUT_READ_FREQUENCY */

/* ===========================================================================
**  Function : HAL_clk_EPSS_LUT_READ_VOLTAGE
**
** ======================================================================== */

boolean HAL_clk_EPSS_LUT_READ_VOLTAGE
(
HAL_clk_APCSCPUType  eCore,
uint32               nRow,
uint32              *nOpenLoopVoltage
)
{
	/* Sanity check */
	if (eCore >= HAL_CLK_APCS_CPU_TOTAL ||
		nRow >= EPSS_LUT_MAX_ROWS ||
		nOpenLoopVoltage == NULL)
	{
		return FALSE;
	}

	/* Program the hardware. */
	switch (eCore)
	{
	case HAL_CLK_APCS_CPU_CLUSTER0:
		*nOpenLoopVoltage = HWIO_INFI(EPSSSLOW_CLKDOM1_DCVS_LUT_r_VOLTAGE, nRow, OLV);
		break;

	case HAL_CLK_APCS_CPU_CLUSTER1:
		*nOpenLoopVoltage = HWIO_INFI(EPSSSLOW_CLKDOM2_DCVS_LUT_r_VOLTAGE, nRow, OLV);
		break;

	case HAL_CLK_APCS_CPU_L3:
		*nOpenLoopVoltage = HWIO_INFI(EPSSSLOW_CLKDOM0_DCVS_LUT_r_VOLTAGE, nRow, OLV);
		break;

	default:
		return FALSE;
	}

	return TRUE;

} /* END HAL_clk_EPSS_LUT_READ_VOLTAGE */


/* ===========================================================================
**  Function : HAL_clk_EPSS_SET_L3_PERF_LEVEL

** ======================================================================== */

boolean HAL_clk_EPSS_SET_L3_PERF_LEVEL
(
  HAL_clk_APCSCoreType   eCore,
  uint32                 nVcIndex
)
{
  if (eCore    >= HAL_CLK_APCS_CPU_CORE_TOTAL ||
      nVcIndex >= EPSS_LUT_MAX_ROWS       )
  {
    return FALSE;
  }

  switch (eCore)
  {
    case HAL_CLK_APCS_CPU_CLUSTER0_C0:
      HWIO_OUTFI(EPSSSLOW_CLKDOM1_COREd_L3_VOTING, 0, VC, nVcIndex);
      break;

    case HAL_CLK_APCS_CPU_CLUSTER0_C1:
      HWIO_OUTFI(EPSSSLOW_CLKDOM1_COREd_L3_VOTING, 1, VC, nVcIndex);
      break;
  
    case HAL_CLK_APCS_CPU_CLUSTER0_C2:
	  HWIO_OUTFI(EPSSSLOW_CLKDOM1_COREd_L3_VOTING, 2, VC, nVcIndex);
      break;
      
    case HAL_CLK_APCS_CPU_CLUSTER0_C3:
	  HWIO_OUTFI(EPSSSLOW_CLKDOM1_COREd_L3_VOTING, 3, VC, nVcIndex);
      break;

    case HAL_CLK_APCS_CPU_CLUSTER1_C0:
      HWIO_OUTFI(EPSSSLOW_CLKDOM2_COREd_L3_VOTING, 0, VC, nVcIndex);
      break;

    case HAL_CLK_APCS_CPU_CLUSTER1_C1:
      HWIO_OUTFI(EPSSSLOW_CLKDOM2_COREd_L3_VOTING, 1, VC, nVcIndex);
      break;

    case HAL_CLK_APCS_CPU_CLUSTER1_C2:
      HWIO_OUTFI(EPSSSLOW_CLKDOM2_COREd_L3_VOTING, 2, VC, nVcIndex);
      break;

    case HAL_CLK_APCS_CPU_CLUSTER1_C3:
      HWIO_OUTFI(EPSSSLOW_CLKDOM2_COREd_L3_VOTING, 3, VC, nVcIndex);
      break;

    case HAL_CLK_APCS_CPU_CLUSTERL3:
      HWIO_OUTFI(EPSSSLOW_CLKDOM0_COREd_L3_VOTING, 0, VC, nVcIndex);
      break;

    default:
      return FALSE;
  }

  return TRUE;

} /* END HAL_clk_EPSS_SET_L3_PERF_LEVEL */

/* ===========================================================================
**  Function : HAL_clk_EPSS_SET_DESIRED_PERF_LEVEL
**
** ======================================================================== */

boolean HAL_clk_EPSS_SET_DESIRED_PERF_LEVEL
(
  HAL_clk_APCSCPUType eCore,
  uint32              nIndex
)
{
  uintnt  nAddress = 0; 
  uint32  nValue = 0;
  boolean bStatus = TRUE;
  ClockDrvCtxt      *pDrvCtxt = Clock_GetDrvCtxt();

  /* Sanity check */
  if (eCore  >= HAL_CLK_APCS_CPU_TOTAL ||
      nIndex >= EPSS_LUT_MAX_ROWS       )
  {
    return FALSE;
  }

  DALCLOCK_LOCK(pDrvCtxt);
  switch(eCore)
  {
    case HAL_CLK_APCS_CPU_CLUSTER0:
      /* Prepare the address and the data. */
      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, 0);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, 1);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, 2);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, 3);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM1_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      break;

    case HAL_CLK_APCS_CPU_CLUSTER1:
      /* Prepare the address and the data. */
      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, 0);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, 1);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, 2);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      /* Prepare the address and the data. */
      nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, 3);
      nValue   = HWIO_FVAL(EPSSSLOW_CLKDOM2_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      /* Program the hardware. */
      outpdw(nAddress, nValue);

      break;

    case HAL_CLK_APCS_CPU_L3:
      /* Prepare the address and the data. */
      //if (HWIO_INF(EPSSTOP_L3_VOTING_EN, L3_VOTING_ENABLE))
      //{
        HAL_clk_EPSS_SET_L3_PERF_LEVEL(HAL_CLK_APCS_CPU_CLUSTERL3, nIndex);
      //}
      //else
      //{
      //  nAddress = HWIO_ADDRI(EPSSSLOW_CLKDOM0_COREd_PERF_STATE_DESIRED, 0);
      //  nValue = HWIO_FVAL(EPSSSLOW_CLKDOM0_COREd_PERF_STATE_DESIRED, SW_INDEX, nIndex);
      //  outpdw(nAddress, nValue);
      //}
      break;

    default:
      bStatus = FALSE;
      break;
  }

  DALCLOCK_FREE(pDrvCtxt);
  return bStatus;

} /* END HAL_clk_EPSS_SET_DESIRED_PERF_LEVEL */


/* ===========================================================================
**  HAL_clk_InitMiscGfxRegisters
**
** ======================================================================== */

void HAL_clk_InitMiscRegisters
(
  void
)
{
  // INFO: Clearing out all votest on L3 from every Core, except L3 itself.
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER0_C0, 0);
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER0_C1, 0);
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER0_C2, 0);
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER0_C3, 0);
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER1_C0, 0);
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER1_C1, 0);
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER1_C2, 0);
  HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTER1_C3, 0);
  //HAL_clk_EPSS_SET_L3_PERF_LEVEL( HAL_CLK_APCS_CPU_CLUSTERL3, 0);

} /* HAL_clk_InitMiscRegisters */

/* ===========================================================================
**  HAL_clk_EnableDCDs
**
** ======================================================================== */

void HAL_clk_EnableDCDs
(
  void
)
{
  //HWIO_OUTF(CAM_CC_CAMNOC_AXI_DCD_DIV_DCDR, DCD_ENABLE, 0x1);
  HWIO_OUTF(VCODEC_VIDEO_CC_IRIS_DIV_DCDR, DCD_ENABLE, 0x1);
  //HWIO_OUTF(VCODEC_VIDEO_CC_MVS1C_DIV_DCDR, DCD_ENABLE, 0x1);
} /* HAL_clk_EnableDCDs */

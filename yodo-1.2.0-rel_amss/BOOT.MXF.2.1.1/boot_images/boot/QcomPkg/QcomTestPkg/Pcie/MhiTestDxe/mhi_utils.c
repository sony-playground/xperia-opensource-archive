/**
 *  @file mhi_utils.c
 *
 *  @brief This file contains the implementation of MHI utilities.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_utils.h"
#include "devcfg.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function rounds up to the nearest power of two.
 *
 * @param[in]  num  Number to round up
 *
 * @return num rouned up to the nearest power of two
 */
uint32 mhi_round_up_pow_of_2(uint32 num)
{
   uint32 i = num;
   uint32 shift = 0;
   uint32 val;

   if (i == 0)
   {
      return 1;
   }

   while (i >>= 1)
   {
      shift++;
   }

   val = 1 << shift;
   if (val != num)
   {
      val <<= 1;
   }

   return val;
}

/**
 * This function gets the state string name for a state enum value.
 *
 * @param[in]  state  MHI state
 *
 * @return Corresponding state string name
 */
const char *mhi_state_to_str(mhi_state_t state)
{
   switch (state)
   {
      case MHI_STATE_RESET:
         return "RESET";
      case MHI_STATE_READY:
         return "READY";
      case MHI_STATE_M0:
         return "M0";
      case MHI_STATE_M1:
         return "M1";
      case MHI_STATE_M2:
         return "M2";
      case MHI_STATE_M3:
         return "M3";
      case MHI_STATE_SYSERR:
         return "SYSERR";
      default:
         MHI_LOG_FATAL("Invalid state %d", state);
         return "INVALID";
   }
}

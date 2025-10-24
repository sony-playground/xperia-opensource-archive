/** @file SPIFWImageLibNull.c
  
  Stub functions for SPI FW Image Lib

  Copyright (c) 2020,2022 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/25/22   GKR     Added SPI stubs
 02/10/20   ck      Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "SpiApi.h"
#include "spi_config.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

void spi_fw_image_main(void)
{
}
spi_status spi_get_fw(uint8** base_ptr, uint32 version)
{

   return SPI_SUCCESS;
}


spi_status spi_fetch_common_clock(spi_plat_device_config *dcfg)
{

    return SPI_SUCCESS;

}

void spi_fetch_clk_cfg(spi_plat_device_config *dcfg)
{

}
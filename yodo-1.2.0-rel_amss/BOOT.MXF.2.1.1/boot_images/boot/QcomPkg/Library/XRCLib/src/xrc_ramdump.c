/*=============================================================================

                            XRC RAMDUMP

 RAM dump collection methods.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

#include "xrc_ram_dump.h"
#include "xrc_log.h"
#include "xrc_os.h"
#include "xrc_types.h"
#include "xrc_utils.h"
#include "xrc_gpio.h"
#include "busywait.h"
#include "slvcom.h"

extern xrc_gpio_type  *g_xrc_gpio_h2a_handle;

/*===========================================================================
  FUNCTION  xrc_ramdump_done
===========================================================================*/
/**
  Function to send ramdump done status to Helios and cleanup interfaces.
  @param[in] slvcom_handle_type: handle to the slvcom
   
  @return
  Returns true if cleanup done successfully.
*/
/*==========================================================================*/

boolean xrc_ramdump_done
(
	slvcom_handle_type *phandle
)
{
	  if(phandle == NULL)
	  {
	  	return FALSE;
	  }

	  /*TODO_HELIOS - Send RAMDUMP DONE command to Helios*/

	  return TRUE;
}

/*===========================================================================
  FUNCTION  xrc_ramdump_init
===========================================================================*/
/**
  Function to enable access to collect Helios Ram dump   
  @param[in] slvcom_handle_type: handle to the slvcom
   
  @return
  Returns true if enabling of helios ram dump is success
*/
/*==========================================================================*/

boolean xrc_ramdump_init
(
	slvcom_handle_type *phandle
)
{
    status_codes eReturn_val = FAILURE;
	
	  if (phandle == NULL)
	  {
	  	return FALSE;
	  }
	
    do
    {
		
        /* To trigger Helios restart, make A2H high */
        slvcom_secmode_enable(phandle);
        /* Bring down A2H line  */
        slvcom_secmode_disable(phandle);

		    /*Delay for Helios to enter crash path*/
        busywait(2000000);
		
        eReturn_val = xrc_gpio_h2a_register();
        BREAKIFFAIL(eReturn_val)
		
        eReturn_val = xrc_gpio_poll_high(H2A_INT_COMMAND_POLL_TIME, g_xrc_gpio_h2a_handle);
        XRC_LOG_ERR(0, "Wait for H2A_INT for crash command status, eReturn_val=%d",  eReturn_val);
        BREAKIFFAIL(eReturn_val)
		
		/*TODO_HELIOS - make changes for Helios crash flow.
		*/
		
    }while (0);

	  if (eReturn_val != SUCCESS)
	  {
	  	return FALSE;
	  }

	  return TRUE;
}

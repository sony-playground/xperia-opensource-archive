/** 
    @file  i2c_plat.c
    @brief platform implementation
 */
/*=============================================================================
            Copyright (c) 2017,2019, 2022 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

#include "i2c_plat.h"
#include "i2c_api.h"
#include "i2c_log.h"    // logging

// For Wait implementation
#include "DALSys.h"

// For GPIO enable/disable 
#include "DalDevice.h"
#include "DDITlmm.h"
#include "ClockBoot.h"
#include "Clock.h"

#include "HALtlmm.h"
#include "HALhwio.h"
#include "busywait.h"

#define INTLOCK()

static ClockHandle clock_handle = 0;

//HWIO Register Mapping
boolean plat_map_hardware (plat_device_config *config)
{
    return TRUE;
}

boolean plat_unmap_hardware (plat_device_config *config)
{
    return TRUE;
}

// clocks, noc etc.
boolean plat_clock_enable (plat_device_config *config)
{
    ClockResult res = CLOCK_SUCCESS ;
    boolean result = TRUE;
    ClockIdType common_clock_id;
    ClockIdType se_id;
    uint8       **clocks = NULL;

    if (config == NULL) { 
        result = FALSE;
        goto ON_EXIT; 
    }

    res = Clock_Init();
    if (res != CLOCK_SUCCESS)
    {
        result = FALSE;
        goto ON_EXIT;
    }

    /* Fails to attach to clocks, if they are not available */
    if (!clock_handle) { // Attach only for once
        res = Clock_Attach(&clock_handle, "I2CLib");
        if ( (CLOCK_SUCCESS != res) || (!clock_handle) ) {
            result = FALSE;
            goto ON_EXIT; 
        }
    }


    if (config->i2c_hub)   // Enable common clocks only for I2C hub Instances
    {
        clocks = config->common_clocks;

        while (*clocks != NULL)
        {
            res = Clock_GetId(clock_handle, (const char *) (*clocks), &common_clock_id);
            if (CLOCK_SUCCESS != res) { 
                result = FALSE;
                goto ON_EXIT; 
            }

            res = Clock_Enable(clock_handle, common_clock_id);
            if (CLOCK_SUCCESS != res) { 
                result = FALSE;
                goto ON_EXIT; 
            }
            I2C_LOG(LEVEL_INFO, "[I2C] clock_ON %s\n", (const char *) (*clocks));

            clocks++;
        };
    }


    res = Clock_GetId(clock_handle, (const char *) (*(config->se_clock)), &se_id);
    if (CLOCK_SUCCESS != res) { 
        result = FALSE;
        goto ON_EXIT; 
    }

    res = Clock_Enable(clock_handle, se_id);
    if (CLOCK_SUCCESS != res) { 
        result = FALSE;
        goto ON_EXIT; 
    }


ON_EXIT:
   return result;

}

boolean plat_clock_disable (plat_device_config *config)
{
    ClockResult res = TRUE ;
    boolean result = TRUE;
    ClockIdType se_id;
    ClockIdType common_clock_id;
    uint8       **clocks = NULL;

    if (config == NULL || (!clock_handle)) { 
        res = FALSE;
        goto ON_EXIT; 
    }

    res = Clock_GetId(clock_handle, (const char *) (*(config->se_clock)), &se_id);
    if (CLOCK_SUCCESS != res) { 
        result = FALSE;
        goto ON_EXIT; 
    }

    res = Clock_Disable(clock_handle, se_id);
    if (CLOCK_SUCCESS != res) { 
        result = FALSE;
        goto ON_EXIT; 
    }

    if (config->i2c_hub)
    {
        clocks = config->common_clocks;
        while (*clocks != NULL)
        {
            res = Clock_GetId(clock_handle, (const char *) (*clocks), &common_clock_id);
            if (CLOCK_SUCCESS != res) { 
                result = FALSE;
                goto ON_EXIT; 
            }

            res = Clock_Disable(clock_handle, common_clock_id);
            if (CLOCK_SUCCESS != res) { 
                result = FALSE;
                goto ON_EXIT; 
            }
            I2C_LOG(LEVEL_INFO, "[I2C] clock_OFF %s\n", (const char *) (*clocks));

            clocks++;
        };
    }

ON_EXIT:
   return result;

}

// gpio
boolean plat_gpio_enable (plat_device_config *config)
{
	DALResult dalRes = TRUE;
	
	if(!config) {
		dalRes = FALSE;
		goto ON_EXIT;
	}

   if(Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE,(DALGpioSignalType*)&config->sda_encoding, 1) != DAL_SUCCESS)
   {
       	dalRes = FALSE;
	    goto ON_EXIT;
   }       
   if(Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE,(DALGpioSignalType*)&config->scl_encoding, 1) != DAL_SUCCESS)
   {
        dalRes = FALSE;
	    goto ON_EXIT;
   }

ON_EXIT:	
	return dalRes;
}

boolean plat_gpio_disable (plat_device_config *config)
{
	DALResult dalRes = TRUE;

	if(!config) {
		dalRes = FALSE;
		goto ON_EXIT;
	}
    if(Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE,(DALGpioSignalType*)&config->sda_encoding, 0) != DAL_SUCCESS)
    {
       	dalRes = FALSE;
	    goto ON_EXIT;
    }       
    if(Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE,(DALGpioSignalType*)&config->scl_encoding, 0) != DAL_SUCCESS)
    {
        dalRes = FALSE;
	    goto ON_EXIT;
    }
ON_EXIT:	
	return dalRes;
}


void *plat_sys_mem_alloc (uint32 size)
{
	DALResult dalRes = I2C_SUCCESS;
	void *pTmpBuffer = NULL;

	dalRes = DALSYS_Malloc(size , &pTmpBuffer);
	if ( (DAL_SUCCESS != dalRes) || (NULL == pTmpBuffer) ) {
		dalRes = FALSE;
		goto ON_EXIT;
	}

ON_EXIT:	
	return pTmpBuffer;
}

void plat_sys_mem_dealloc (void* ptr)
{

  DALResult dalRes = I2C_SUCCESS;

  dalRes = DALSYS_Free(ptr);
  if ( (DAL_SUCCESS != dalRes) || (NULL == ptr) ) { 
     dalRes = FALSE; 
     goto ON_EXIT;   
  }
  
ON_EXIT:	
	return ;

}

void *plat_mem_alloc (uint8 core_index, uint32 size, mem_alloc_type ctxt)
{
    uint8 *mem = NULL;

    (void) core_index;

    if ((ctxt == TX_TRANSFER_ELEM_TYPE) ||
        (ctxt == RX_TRANSFER_ELEM_TYPE))
    {
        // enforce that size is multiple of 16 and also a power of 2
        if (((size & 0xF) != 0) ||
             (size & (size - 1)))
        {   
            I2C_LOG(LEVEL_INFO, "size is not multiple of 16 and also a power of 2");
            return NULL;
        }

    }

    mem = plat_sys_mem_alloc (size);
	
	if (mem != NULL)
	{
        memset(mem, 0, size);
	}

    return (void *) mem;
}

void plat_mem_free (void *ptr, uint32 size, mem_alloc_type ctxt)
{
    uint8 *sav = NULL;
	
	memset(ptr, 0, size);

	if ((ctxt == TX_TRANSFER_ELEM_TYPE) ||
		(ctxt == RX_TRANSFER_ELEM_TYPE))
	{
		sav = *((uint8 **) ((uint8 *) ptr - sizeof(uint8 *)));
	}

	plat_sys_mem_dealloc (sav);
}


void i2c_init (void)
{
	return;
}

// utils
void plat_delay_us (uint32 us)
{
	busywait(us);
}

// interrupt
// not supported in uefi/xbl core
boolean plat_interrupt_register (plat_device_config *config, void (*isr) (void *), void *handle)
{
    return TRUE;
}

// not supported in uefi/xbl core
boolean plat_interrupt_deregister (plat_device_config *config)
{
    return TRUE;
}

// tcsr
// not supported in uefi/xbl core
boolean plat_tcsr_init (plat_device_config *config)
{
    return TRUE;
}

// not supported in uefi/xbl core
boolean plat_tcsr_deinit (plat_device_config *config)
{
    return TRUE;
}

// not supported in uefi/xbl core
void *plat_virt_to_phys (void *ptr, mem_attr_type attr)
{
    return ptr;
}

// memory
// not supported in uefi/xbl core
boolean plat_mem_flush_cache (void *addr, uint32 size)
{
    return TRUE;
}

// not supported in uefi/xbl core
boolean plat_mem_invalidate_cache (void *addr, uint32 size)
{
    return TRUE;
}

// not supported in uefi/xbl core
void *plat_signal_alloc (uint8 core_index)
{
    return plat_mem_alloc (core_index, sizeof(uint8), SIGNAL_TYPE);
}

// not supported in uefi/xbl core
void plat_signal_free (void *signal)
{
    plat_mem_free (signal, sizeof(uint8), SIGNAL_TYPE);
}

// not supported in uefi/xbl core
void plat_signal_init(void **signal)
{
	return;
}

// not supported in uefi/xbl core
void plat_wait_for_event (void *signal)
{
	return;
}

// not supported in uefi/xbl core
void plat_signal_event (void *signal)
{
	return;
}

// critical section for specific instance
// not supported in uefi/xbl core
void *plat_mutex_instance_init (uint8 core_index)
{
    return (void *) 1;
}

// not supported in uefi/xbl core
void plat_mutex_instance_de_init (void *lock)
{
	return;
}

// not supported in uefi/xbl core
void plat_mutex_instance_lock (void *lock)
{
	return;
}

// not supported in uefi/xbl core
void plat_mutex_instance_unlock (void *lock)
{
	return;
}

// critical section for all cores instances
// not supported in uefi/xbl core
void plat_mutex_global_lock (void)
{
	return;
}

// not supported in uefi/xbl core
void plat_mutex_global_unlock (void)
{
	return;
}

// other
// not supported in uefi/xbl core
boolean plat_in_exception_context (void)
{
    return FALSE;
}


uint32 plat_raise_tpl (void)
{
    return 0;
}

void plat_restore_tpl (uint32 prev_tpl_level)
{
    prev_tpl_level = (uint32)prev_tpl_level;
    //do nothing
}

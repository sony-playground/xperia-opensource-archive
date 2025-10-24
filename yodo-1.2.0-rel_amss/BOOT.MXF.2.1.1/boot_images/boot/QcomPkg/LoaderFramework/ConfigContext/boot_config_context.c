/**
 * @file boot_config_context.c
 * @brief
 * XBL implementation for boot_config_context interfaces
 *
 * Copyright (C) 2019-2021 by Qualcomm Technologies, Inc. All Rights Reserved.
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ---------------------------------------------------------
01/22/21   rhy     Added CONFIG_CONTEXT_CRT_HANDLE in set_ptr and set_value
05/15/20   rhy     Additional check to set existing pointer
04/03/19   ep      Created the file
===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/
#include <string.h>
#include "boot_config_context.h"
#include "boot_memory_mgr_if.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/*
This is the ConfigContext ID.
Used to vbalidate if an object is a real ConfigContext object
*/
#define CONFIG_CONTEXT_ID	0x43464358

/*
Used to track how a particular parameter was set.
*/
typedef enum config_context_entry_set_type
{
  NOT_SET,
  SET_AS_VALUE,
  SET_AS_PTR
} config_context_entry_set_type;


/*
Info about a particular parameter value
*/
typedef struct config_context_entry_type
{
  union
  {
    struct
    {
      void *ptr;
      boot_boolean allocated;
    } ptr;
    uint32 value;
  };

  config_context_entry_set_type set;
} config_context_entry_type;


typedef struct config_context_type
{
  boot_handle_common_type handle_data;
  config_context_entry_type entries[CONFIG_CONTEXT_NO_PARAMS];
  boot_memory_mgr_if_type *mem_if;
} config_context_type;


static config_context_type *_crt_handle = NULL;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static bl_error_boot_type _free_ptr_allocated(config_context_type *config_context, boot_config_context_param_type param)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  if(config_context->entries[param].set == SET_AS_PTR)
  {
    if(config_context->entries[param].ptr.allocated)
    {
      return_status = config_context->mem_if->free(config_context->entries[param].ptr.ptr);
      if(return_status != BL_ERR_NONE)
      {
        return return_status;
      }
      config_context->entries[param].ptr.allocated = FALSE;
    }
  }

  return return_status;
}


static bl_error_boot_type _set_as_value(config_context_type *config_context, boot_config_context_param_type param, uint32 value)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  return_status = _free_ptr_allocated(config_context, param);
  if(return_status != BL_ERR_NONE)
  {
    return return_status;
  }

  config_context->entries[param].value = value;
  config_context->entries[param].set = SET_AS_VALUE;

  return return_status;
}


static bl_error_boot_type _set_as_ptr(config_context_type *config_context, boot_config_context_param_type param, void *ptr, boot_boolean allocated)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  /* Do not free and re-assign the pointer if it is already allocated */
  if((ptr == config_context->entries[param].ptr.ptr) && (config_context->entries[param].ptr.allocated == TRUE))
  {
      return return_status;
  }
  
  return_status = _free_ptr_allocated(config_context, param);
  if(return_status != BL_ERR_NONE)
  {
    return return_status;
  }

  config_context->entries[param].ptr.ptr = ptr;
  config_context->entries[param].ptr.allocated = allocated;
  config_context->entries[param].set = SET_AS_PTR;

  return return_status;
}


static bl_error_boot_type _get_ptr(config_context_type *config_context, boot_config_context_param_type param, void **dest)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if((param < 0) || (param >= CONFIG_CONTEXT_NO_PARAMS))
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    if(dest == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }


    if(config_context->entries[param].set != SET_AS_PTR)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    *dest = config_context->entries[param].ptr.ptr;

  }
  while(FALSE);

  return return_status;
}



static bl_error_boot_type _get_value(config_context_type *config_context, boot_config_context_param_type param, uint32 *dest)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if((param < 0) || (param >= CONFIG_CONTEXT_NO_PARAMS))
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    if(dest == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    if(config_context->entries[param].set != SET_AS_VALUE)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    *dest = config_context->entries[param].value;

  }
  while(FALSE);

  return return_status;
}




static bl_error_boot_type _init(config_context_type *config_context)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    memset((uint8 *)config_context, 0, sizeof(config_context_type));

    config_context->handle_data.id = CONFIG_CONTEXT_ID;
    config_context->handle_data.config_context_handle = NULL;

    for(int i = 0; i < CONFIG_CONTEXT_NO_PARAMS; i++)
    {
      config_context->entries[i].set = NOT_SET;
      config_context->entries[i].ptr.allocated = FALSE;
    }
  }
  while(FALSE);

  return return_status;
}


static bl_error_boot_type _check_object(config_context_type *config_context)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(config_context == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    if(config_context->handle_data.id != CONFIG_CONTEXT_ID)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
    }
  }
  while(FALSE);

  return return_status;
}


static bl_error_boot_type _reset_parameter(config_context_type *config_context, uint32 param)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  return_status = _free_ptr_allocated(config_context, param);
  if(return_status != BL_ERR_NONE)
  {
    return return_status;
  }

  config_context->entries[param].set = NOT_SET;

  return return_status;
}


static bl_error_boot_type _reset_parameters(config_context_type *config_context)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    for(int i = 0; i < CONFIG_CONTEXT_NO_PARAMS; i++)
    {
      return_status = _reset_parameter(config_context, i);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }
    }

  }
  while(FALSE);

  return return_status;
}

/*==========================================================================
                      FUNCTIONS IMPLEMENTATION
===========================================================================*/


/*===========================================================================
**  Function :  config_context_open
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_open(boot_handle *handle, boot_memory_mgr_if_type *mem_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  config_context_type *config_context = NULL;

  do
  {
    if((handle == NULL) || (mem_if == NULL))
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    return_status = mem_if->malloc(sizeof(config_context_type), (void *)&config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    if(config_context == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_MEMORY_ALLOC_FAIL);
      break;
    }

    return_status = _init(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    config_context->mem_if = mem_if;

    *handle = (boot_handle)config_context;

    if(_crt_handle == NULL)
    {
      _crt_handle = config_context;
    }

  }
  while(FALSE);

  return return_status;
}


/*===========================================================================
**  Function :  config_context_set_crt_handle
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_set_crt_handle(boot_handle handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(handle == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    _crt_handle=(config_context_type *)handle;

  }
  while(FALSE);

  return return_status;
}

/*===========================================================================
**  Function :  config_context_get_crt_handle
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_get_crt_handle(boot_handle *handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(handle == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    *handle = _crt_handle;

  }
  while(FALSE);

  return return_status;
}

/*===========================================================================
**  Function :  config_context_close
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_close(const boot_handle handle)
{
  config_context_type *config_context = (config_context_type *)handle;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if(_crt_handle == config_context)
    {
      _crt_handle = NULL;
    }

    return_status = _reset_parameters(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    config_context->handle_data.id = CLOSED_OBJECT_ID;

    return_status = config_context->mem_if->free(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}


/*===========================================================================
**  Function :  config_context_reset
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_reset_parameters(const boot_handle handle)
{
  config_context_type *config_context = (config_context_type *)handle;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = _reset_parameters(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}



/*===========================================================================
**  Function :  config_context_reset_parameter
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type config_context_reset_parameter(const boot_handle handle, boot_config_context_param_type param)
{
  config_context_type *config_context = (config_context_type *)handle;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if((param < 0) || (param >= CONFIG_CONTEXT_NO_PARAMS))
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    return_status = _reset_parameter(config_context, param);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}



/*===========================================================================
**  Function :  boot_config_context_init_ptr_params
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_init_ptr_params(const boot_handle handle, boot_config_context_ptr_data *init_params, int num_params)
{
  config_context_type *config_context = (config_context_type *)handle;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if(init_params == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    for(int i = 0; i < num_params; i++)
    {
      boot_config_context_param_type type = init_params[i].type;

      if((type < 0) && (type >= CONFIG_CONTEXT_NO_PARAMS))
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
        break;
      }
      return_status = _set_as_ptr(config_context, type, init_params[i].ptr, FALSE);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }
    }

    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}


/*===========================================================================
**  Function :  boot_config_context_init_value_params
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_init_value_params(const boot_handle handle, boot_config_context_value_data *init_params, int no_params)
{
  config_context_type *config_context = (config_context_type *)handle;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if(init_params == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    for(int i = 0; i < no_params; i++)
    {
      boot_config_context_param_type type = init_params[i].type;

      if((type < 0) && (type >= CONFIG_CONTEXT_NO_PARAMS))
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
        break;
      }
      return_status = _set_as_value(config_context, type, init_params[i].value);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }
    }

    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}



/*===========================================================================
**  Function :  config_context_get_ptr
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_get_ptr(const boot_handle handle, boot_config_context_param_type param, void **dest)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  config_context_type *config_context = NULL;


  do
  {
    if (handle == CONFIG_CONTEXT_CRT_HANDLE)
    {
      if(_crt_handle == NULL)
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INITIALIZATION_ERROR);
        break;
      }
      config_context = _crt_handle;
    }
    else
    {
      config_context = (config_context_type *)handle;
    }

    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = _get_ptr(config_context, param, dest);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}




/*===========================================================================
**  Function :  config_context_get_value
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_get_value(const boot_handle handle, boot_config_context_param_type param, uint32 *dest)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  config_context_type *config_context;

  do
  {
    if (handle == CONFIG_CONTEXT_CRT_HANDLE)
    {
      if(_crt_handle == NULL)
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INITIALIZATION_ERROR);
        break;
      }
      config_context = _crt_handle;
    }
    else
    {
      config_context = (config_context_type *)handle;
    }

    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }


    return_status = _get_value(config_context, param, dest);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}



/*===========================================================================
**  Function :  config_context_set_ptr
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_set_ptr(const boot_handle handle, boot_config_context_param_type param, void *source)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  config_context_type *config_context = (config_context_type *)handle;

  do
  {
    if(handle == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_NULL_PTR_PASSED);
      break;
    }
    
    if (handle == CONFIG_CONTEXT_CRT_HANDLE)
    {
      if(_crt_handle == NULL)
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INITIALIZATION_ERROR);
        break;
      }
      config_context = _crt_handle;
    }
    
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if((param < 0) || (param >= CONFIG_CONTEXT_NO_PARAMS))
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    return_status = _set_as_ptr(config_context, param, source, FALSE);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}




/*===========================================================================
**  Function :  config_context_set_value
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_config_context_set_value(const boot_handle handle, boot_config_context_param_type param, uint32 value)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  config_context_type *config_context = (config_context_type *)handle;

  do
  {
    if(handle == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_NULL_PTR_PASSED);
      break;
    }
    
    if (handle == CONFIG_CONTEXT_CRT_HANDLE)
    {
      if(_crt_handle == NULL)
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INITIALIZATION_ERROR);
        break;
      }
      config_context = _crt_handle;
    }
    
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if((param < 0) || (param >= CONFIG_CONTEXT_NO_PARAMS))
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    return_status = _set_as_value(config_context, param, value);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;
}



/*===========================================================================
**  Function :  boot_config_context_set_parameters
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_set_parameters(const boot_handle handle, boot_config_context_populate_table *parameters, uint32 no_params)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  config_context_type *config_context = (config_context_type *)handle;

  do
  {
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if(parameters == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    for(int i = 0; i < no_params; i++)
    {
      boot_config_context_populate_table *parameter = &(parameters[i]);

      if((parameter->parameter_id < 0) || (parameter->parameter_id >= CONFIG_CONTEXT_NO_PARAMS))
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
        break;
      }

      if(parameter->parameter_type == PARAMETER_TYPE_VALUE)
      {
        // Chech if get_value() function pointer is not NULL since this one has higher priority
        if(parameter->populate_value.get_value != NULL)
        {
          uint32 value;
          return_status = parameter->populate_value.get_value(&value);
          if(return_status != BL_ERR_NONE)
          {
            break;
          }
          return_status = _set_as_value(config_context, parameter->parameter_id, value);
          if(return_status != BL_ERR_NONE)
          {
            break;
          }
        }
        else
        {
          return_status = _set_as_value(config_context, parameter->parameter_id, parameter->populate_value.value);
          if(return_status != BL_ERR_NONE)
          {
            break;
          }
        }
      }
      else if(parameter->parameter_type == PARAMETER_TYPE_PTR)
      {
        // Chech if get_ptr() function pointer is not NULL since this one has higher priority
        if(parameter->populate_ptr.get_ptr != NULL)
        {
          void *ptr;

          return_status = config_context->mem_if->malloc(parameter->populate_ptr.size, (void *)&ptr);
          if(return_status != BL_ERR_NONE)
          {
            break;
          }

          return_status = parameter->populate_ptr.get_ptr(ptr);
          if(return_status != BL_ERR_NONE)
          {
            break;
          }

          return_status = _set_as_ptr(config_context, parameter->parameter_id, ptr, TRUE);
          if(return_status != BL_ERR_NONE)
          {
            break;
          }
        }
        else
        {
          return_status = _set_as_ptr(config_context, parameter->parameter_id, parameter->populate_ptr.ptr, FALSE);
          if(return_status != BL_ERR_NONE)
          {
            break;
          }
        }
      }
      else
      {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
        break;
      }
    }

    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  }
  while(FALSE);

  return return_status;

}



/*===========================================================================
**  Function :  boot_config_context_duplicate
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_duplicate(const boot_handle handle, boot_handle *new_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  config_context_type *config_context = (config_context_type *)handle;
  config_context_type *new_config_context = NULL;
  uint32 i;

  do
  {
    return_status = _check_object(config_context);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_open(new_handle, config_context->mem_if);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    new_config_context = (config_context_type *)*new_handle;

    for(i = 0; i < CONFIG_CONTEXT_NO_PARAMS; i++)
    {
      new_config_context->entries[i] = config_context->entries[i];
    }

  }
  while(FALSE);

  return return_status;
}


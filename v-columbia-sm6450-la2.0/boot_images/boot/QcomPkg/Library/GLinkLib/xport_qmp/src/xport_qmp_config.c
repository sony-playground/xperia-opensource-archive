/*===========================================================================

                GLINK QMP XPORT DEVICE CONFIGURATION

    This file provides the device configuration for Glink QMP xport

  ---------------------------------------------------------------------------
  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header:

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/04/17   mad      Valid value for mailbox_area_size_bytes member to enable 
                    checking against a reference value that cannot be compromised
                    by peer micro-core 
===========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include "xport_qmp_config.h"
#include "xport_qmp_settings.h"
#include "msmhwiobase.h"
#include <Protocol/EFIIPCC.h>

/*===========================================================================
                    CONSTANT / MACRO DECLARATIONS
===========================================================================*/
#define MAX_QMP_STR_LEN 20

/*===========================================================================
                      LOCAL DATA DEFINATION
===========================================================================*/

/*===========================================================================
                      GLOBAL DATA DEFINATION
===========================================================================*/

/** Processor information */
const xport_qmp_devcfg_proc_type xport_qmp_devcfg_proc =
{
  "apps",                /* Local host name */
  SMEM_APPS               /* Local host ID   */
};

/** Transports supported */
const xport_qmp_devcfg_remote_type xport_qmp_devcfg_remote_procs[] =
{
  /* APPS->AOP */
  {
    "aop_apps",           /* Logical Channel name    */
    "rpm",
    SMEM_INVALID_HOST,
    1*1024,               /* Total Mailbox region size including local and remote. */
    0,                    /* Local Mailbox size. Stub for slave side  */
    3,                    /* Max outstanding messages*/
    EFI_IPCC_C_AOP,           /* Interrupt      */
    QMP_IPCC_IRQ,      
    0,
    AOP_SS_MSG_RAM_START_ADDRESS_BASE
  },
  /* NULL */
  {
    NULL,                 /* Logical Channel name    */
    NULL,                 /* Remote proc name        */
    SMEM_INVALID_HOST,    /* Remote host ID          */
    0,                    /* Mailbox region size. Stub for slave side */
    0,                    /* Local Mailbox size. Stub for slave side  */
    0,                    /* Max outstanding messages*/
    QMP_NULL_CLIENT,
    QMP_NULL_SIGNAL,      /* Interrupt      */
    0,
    0,                /* Mailbox desc start address -- Virtual address */
  }
};

void xport_qmp_alloc_copy(char** dest, const char* src)
{
  size_t                xport_temp_len = 0;
  //Calculate the length of ch_name
  if(! *dest) 
  {
    xport_temp_len = strnlen(src, MAX_QMP_STR_LEN);
    
    //copy over ch_name from devcfg
    //dest = (char*)glink_os_malloc(temp_len+1);
    *dest = (char*)glink_os_calloc(xport_temp_len+1);
    if (*dest) {
        //memscpy((void*)dest,temp_len+1,(void*)src,temp_len+1);
        strlcpy(*dest, src, xport_temp_len+1);
        //memscpy((void*)dest,MAX_QMP_STR_LEN,(void*)src,MAX_QMP_STR_LEN);
    }
    else{
        ERR_FATAL("Cannot allocate qmp structure",0,0,0);
    }
  }
}

const uint32 xport_qmp_num_configs = ((sizeof(xport_qmp_devcfg_remote_procs)/sizeof(xport_qmp_devcfg_remote_procs[0])) - 1);

/*===========================================================================
FUNCTION      xport_qmp_get_config
===========================================================================*/
/**
  Return the configuration (remote subsystem) of given index.

  @param[in]  ind    Index.

  @return   Configuration.
*/
/*=========================================================================*/
const xport_qmp_config_type* xport_qmp_get_config(uint32 ind)
{
  if (ind >= xport_qmp_num_configs)
  {
    return NULL;
  }

  /* Last index is always secure processor */
  return (const xport_qmp_config_type*)&xport_qmp_devcfg_remote_procs[ind];
}

/*===========================================================================
FUNCTION      xport_qmp_alloc_mailbox
===========================================================================*/
/**
  Allocates the mailbox memory.

  @param[in]  ind    Index.
  @param[out] size   Size of the mailbox.

  @return   Mailbox memory.
*/
/*=========================================================================*/
void *xport_qmp_alloc_mailbox(uint32 ind, uint32* size)
{
  if (ind >= xport_qmp_num_configs)
  {
    return NULL;
  }
  *size = xport_qmp_devcfg_remote_procs[ind].mailbox_area_size_bytes;
  return (void*)xport_qmp_devcfg_remote_procs[ind].mailbox_desc_start;

}



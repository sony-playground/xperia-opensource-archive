#ifndef BOOT_DDR_TYPES_H
#define BOOT_DDR_TYPES_H

/*===========================================================================

                        Boot DDR Interface Header File

GENERAL DESCRIPTION
  This header file contains the definition of the public interface for DDR.

Copyright 2019 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/15/19   ep     Initial revision.

============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#ifndef _ARM_ASM_
#include "boot_comdef.h"
#endif /* _ARM_ASM_ */

#include "boot_ddr_if.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS
                      
===========================================================================*/
#ifndef _ARM_ASM_



/*---------------------------------------------------------------------------
  Structures to store the shared DDR information
---------------------------------------------------------------------------*/
typedef struct
{
  /* Chip Select Starting Address */
  uint64       cs_addr;
  /* DDR Size in Mega Bytes */  
  uint64       ramsize;    
} boot_ddr_info_type;


typedef struct
{
  /* Number of Partitions */
  uint32       num_partitions;

  /* highest address bit for bank address */
  uint32       highest_bank_bit;
  
  /* Chip Select 1st Partition Starting Address */
  uint64       sdram_addr;
} boot_extended_ddr_info_type;


typedef struct
{
  /* Number of total attached DDR */
  uint32       noofddr;    
  /* DDR's Information */
  boot_ddr_info_type  *ddr_info; 
  /* DDR's Extended Information */
  boot_extended_ddr_info_type *ddr_partition_info;
} boot_ddr_device_info_type;



#endif /* _ARM_ASM_ */

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/


#endif /* BOOT_DDR_TYPES_H */


/*===========================================================================
GENERAL DESCRIPTION
  This file is just to give an entry point to the pmic elf image

 &copy; Copyright 2013-2021 Qualcomm Technologies Inc, All Rights Reserved
 Qualcomm Confidential and Proprietary

============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/target/kailua/psi/pm_psi.c#1 $ 
$DateTime: 2022/08/18 10:15:46 $  $Author: pwbldsvc $


when         who     what, where, why
----------   ---     ----------------------------------------------------------
09/01/15     aab     Updated driver to support SBL Conditional configuration feature
06/23/15     aab     Added support for MSM8996 V2/V3. Removed support for V1
04/29/15     aab     Added support for PMK8001
06/06/14     akm     Created for psii elf image creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/ 

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "com_dtypes.h"
#include "pm_config_sbl.h"
#include "pm_sbl_boot_target.h"
#include "pm_config_target_size.h"
#include "pm_config_target_pbs_ram.h"
#include "pm_config_target_sbl_sequence.h"
#include "pm_config_target_sdam.h"
/*===========================================================================

                           DEFINITIONS

===========================================================================*/

struct pm_sbl_config_buffer {
	pm_sbl_config_info_type   pm_sbl_config_info;

	pm_sbl_seq_type           pm_sbl_seq[PM_SBL_SEQ_SIZE+10];
	pm_pbs_ram_data_type      pm_pbs_seq_a[PM_PBS_RAM_A_SIZE+1];
	pm_pbs_ram_data_type      pm_pbs_seq_b[PM_PBS_RAM_B_SIZE+1];
	pm_pbs_ram_data_type      pm_pbs_seq_c[PM_PBS_RAM_C_SIZE+1];
	pm_pbs_ram_data_type      pm_pbs_seq_d[PM_PBS_RAM_D_SIZE+1];

	pm_sbl_cond_seq_type      pm_sbl_cond_seq[PM_SBL_COND_SEQ_SIZE+1];
	uint8                     pm_sdam_seq[12][SDAM_DATA_SIZE_MAX];
};

struct pm_sbl_config_buffer pm_sbl_config_data = {
	.pm_sbl_config_info = SBL_CONFIG_INFO_DATA,

	.pm_sbl_seq = SBL_SEQ_DATA,
	.pm_pbs_seq_a = PM_PBS_RAM_A_DATA,
	.pm_pbs_seq_b = PM_PBS_RAM_B_DATA,
	.pm_pbs_seq_c = PM_PBS_RAM_C_DATA,
	.pm_pbs_seq_d = PM_PBS_RAM_D_DATA,

	.pm_sbl_cond_seq = SBL_COND_SEQ_DATA,
	.pm_sdam_seq = SBL_SDAM_DATA,
};

pm_pbs_ram_data_type*     pm_pbs_seq[] = { pm_sbl_config_data.pm_pbs_seq_a, pm_sbl_config_data.pm_pbs_seq_b, 
	                                        pm_sbl_config_data.pm_pbs_seq_c, pm_sbl_config_data.pm_pbs_seq_d};


pm_sbl_pdm_data_type    pm_psi_data_hdr   = {pm_sbl_config_data.pm_sbl_seq, NULL, pm_pbs_seq, pm_sbl_config_data.pm_sbl_cond_seq, (uint8 *)pm_sbl_config_data.pm_sdam_seq, 
	                                          sizeof(pm_sbl_seq_type) * PM_SBL_SEQ_SIZE, 0, 
															sizeof(pm_pbs_ram_data_type *) * PM_PBS_RAM_BUF_COUNT, 
															sizeof(pm_sbl_cond_seq_type) * PM_SBL_COND_SEQ_SIZE, 
															sizeof(uint8) * PM_SDAM_SEQ_SIZE};


pm_sbl_pdm_config_type pm_psi_header =
                                     { 
                                       &pm_sbl_config_data.pm_sbl_config_info,
                                       &pm_psi_data_hdr
                                     };


/*===========================================================================

                      FUNCTION PROTOTYPES

===========================================================================*/



 /*! \file  pm_config_target_size.h 
 *   
 *  \brief  File Contains the PMIC Set Mode Driver Implementation 
 *  \details Set Mode Driver implementation is responsible for setting and getting 
 *  all mode settings such as Register values, memory values, etc. 
 *   
 *    PMIC code generation Version: 1.0.0.0 
 *    Date: 10/17/2023 
 *    PMIC PSI Version: Clarence-SBL-b0x20_v0x31 - Approved 
 *    PBS RAM Version: Tokei_PBS2_RAM_b0x20_v0x20_p0x00 
 *    PBS RAM Version: Tokei_PBS1_RAM_b0x20_v0x14_p0x00 
 *    PBS RAM Version: Tokei_PBS3_RAM_b0x20_v0x03_p0x00 
 *    PBS RAM Version: Puhi_RAM_b0x00_v0x0D_p0x00 
 *    PBS RAM Version: Cortes_RAM_b0x00_v0x02_p0x00 
 *    PBS RAM Version: Tioman_RAM_b0x06_v0x24 
 *    PBS RAM Version: Nebula_RAM_b0x20_v0x02_p0x00 
 *    This file contains code for Target specific settings and modes. 
 *   
 *  Copyright (c) 2018,2023 Qualcomm Technologies, Inc. All rights reserved. 
 *  Confidential and Proprietary - Qualcomm Technologies, Inc. 
 */ 
 
# ifndef __PM_CONFIG_TARGET_SIZE_H__
# define __PM_CONFIG_TARGET_SIZE_H__

#define PM_PBS_RAM_A_ACTIVE_CODE_SIZE 	0x0C22
#define PM_PBS_RAM_B_ACTIVE_CODE_SIZE 	0x1FC2
#define PM_PBS_RAM_C_ACTIVE_CODE_SIZE 	0x0296
#define PM_PBS_RAM_D_ACTIVE_CODE_SIZE 	0x01F2
#define PM_PBS_RAM_E_ACTIVE_CODE_SIZE 	0x01F2
#define PM_PBS_RAM_F_ACTIVE_CODE_SIZE 	0x01F2
#define PM_PBS_RAM_G_ACTIVE_CODE_SIZE 	0x01CB

#define PM_PBS_RAM_A_SIZE 	0x1000
#define PM_PBS_RAM_B_SIZE 	0x2000
#define PM_PBS_RAM_C_SIZE 	0x1000
#define PM_PBS_RAM_D_SIZE 	0x200
#define PM_PBS_RAM_E_SIZE 	0x200
#define PM_PBS_RAM_F_SIZE 	0x200
#define PM_PBS_RAM_G_SIZE 	0x200
#define PM_PBS_RAM_SIZE_TOTAL 	0x11E5
#define PM_PBS_RAM_BUF_COUNT 	0x07		//No of PBS RAM 
#define PM_SBL_COND_SEQ_SIZE	0x30
#define PM_SBL_SEQ_SIZE			2480

#define PM_SDAM_SEQ_SIZE		(0* SDAM_DATA_SIZE_MAX) 

#endif /* PM_CONFIG_TARGET_SIZE_H */
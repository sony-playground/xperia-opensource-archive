 /*! \file  pm_config_target_size.h 
 *   
 *  \brief  File Contains the PMIC Set Mode Driver Implementation 
 *  \details Set Mode Driver implementation is responsible for setting and getting 
 *  all mode settings such as Register values, memory values, etc. 
 *   
 *    PMIC code generation Version: 1.0.0.0 
 *    Date: 9/5/2023 
 *    PMIC PSI Version: Netrani-SBL-b0x0F_v0x12 - Approved 
 *    PBS RAM Version: Tokei_PBS2_RAM_b0x0F_v0x07_p0x00 
 *    PBS RAM Version: Tokei_PBS1_RAM_b0x0F_v0x13_p0x00 
 *    PBS RAM Version: Tokei_PBS3_RAM_b0x0F_v0x02_p0x00 
 *    PBS RAM Version: MakuaC_RAM_b0x0F_v0x02_p0x00 
 *    PBS RAM Version: Puhi_RAM_b0x00_v0x0D_p0x00 
 *    PBS RAM Version: Cortes_RAM_b0x00_v0x02_p0x00 
 *    PBS RAM Version: Tioman_RAM_b0x0F_v0x24_p0x00 
 *    This file contains code for Target specific settings and modes. 
 *   
 *  Copyright (c) 2023, Qualcomm Technologies, Inc. All rights reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc. 
 */ 
 
# ifndef __PM_CONFIG_TARGET_SIZE_H__
# define __PM_CONFIG_TARGET_SIZE_H__

#define PM_PBS_RAM_A_ACTIVE_CODE_SIZE 	0x0C22
#define PM_PBS_RAM_B_ACTIVE_CODE_SIZE 	0x1FC2
#define PM_PBS_RAM_C_ACTIVE_CODE_SIZE 	0x0296
#define PM_PBS_RAM_D_ACTIVE_CODE_SIZE 	0x0023
#define PM_PBS_RAM_E_ACTIVE_CODE_SIZE 	0x01F2
#define PM_PBS_RAM_F_ACTIVE_CODE_SIZE 	0x01F2
#define PM_PBS_RAM_G_ACTIVE_CODE_SIZE 	0x01F2

#define PM_PBS_RAM_A_SIZE 	0x1000
#define PM_PBS_RAM_B_SIZE 	0x2000
#define PM_PBS_RAM_C_SIZE 	0x1000
#define PM_PBS_RAM_D_SIZE 	0x200
#define PM_PBS_RAM_E_SIZE 	0x200
#define PM_PBS_RAM_F_SIZE 	0x200
#define PM_PBS_RAM_G_SIZE 	0x200
#define PM_PBS_RAM_SIZE_TOTAL 	0x138D
#define PM_PBS_RAM_BUF_COUNT 	0x07		//No of PBS RAM 
#define PM_SBL_COND_SEQ_SIZE	0x31
#define PM_SBL_SEQ_SIZE			2521

#define PM_SDAM_SEQ_SIZE		(10* SDAM_DATA_SIZE_MAX) 

#endif /* PM_CONFIG_TARGET_SIZE_H */
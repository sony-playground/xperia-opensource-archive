 /*! \file  pm_config_target_size.h 
 *   
 *  \brief  File Contains the PMIC Set Mode Driver Implementation 
 *  \details Set Mode Driver implementation is responsible for setting and getting 
 *  all mode settings such as Register values, memory values, etc. 
 *   
 *    PMIC code generation Version: 1.0.0.0 
 *    Date: 11/24/2022 
 *    PMIC PSI Version: Kailua-SBL-b0x00_v0x83 - Approved 
 *    PBS RAM Version: Azura_PBS2_RAM_b0x00_v0x2A_p0x00 
 *    PBS RAM Version: Azura_PBS1_RAM_b0x00_v0x6B_p0x00 
 *    PBS RAM Version: Azura_PBS3_RAM_b0x00_v0x1A_p0x00 
 *    PBS RAM Version: Kohala_RAM_b0x00_v0x0C_p0x00 
 *    This file contains code for Target specific settings and modes. 
 *   
 *  &copy; Copyright 2022 Qualcomm Technologies Incorporated, All Rights Reserved 
 */ 
 
# ifndef __PM_CONFIG_TARGET_SIZE_H__
# define __PM_CONFIG_TARGET_SIZE_H__

#define PM_PBS_RAM_A_ACTIVE_CODE_SIZE 	0x04A2
#define PM_PBS_RAM_B_ACTIVE_CODE_SIZE 	0x1FC2
#define PM_PBS_RAM_C_ACTIVE_CODE_SIZE 	0x0296
#define PM_PBS_RAM_D_ACTIVE_CODE_SIZE 	0x0200

#define PM_PBS_RAM_A_SIZE 	0x1000
#define PM_PBS_RAM_B_SIZE 	0x2000
#define PM_PBS_RAM_C_SIZE 	0x1000
#define PM_PBS_RAM_D_SIZE 	0x200
#define PM_PBS_RAM_SIZE_TOTAL 	0x1906
#define PM_PBS_RAM_BUF_COUNT 	0x04		//No of PBS RAM 
#define PM_SBL_COND_SEQ_SIZE	0x45
#define PM_SBL_SEQ_SIZE			2528

#define PM_SDAM_SEQ_SIZE		(0* SDAM_DATA_SIZE_MAX) 

#endif /* PM_CONFIG_TARGET_SIZE_H */
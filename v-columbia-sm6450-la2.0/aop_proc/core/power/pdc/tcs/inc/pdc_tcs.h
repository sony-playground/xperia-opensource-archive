#ifndef _PDC_TCS_H_
#define _PDC_TCS_H_
/*===========================================================================
                                 pdc_tcs.h

DESCRIPTION:
  File containing typedefs and function prototypes for PDC TCS initialization

Copyright (c) 2019 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/

//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================


//===========================================================================
//                             Function Declarations
//===========================================================================

/**
 * <!-- pdc_tcs_init -->
 *
 * @brief Function to initialize TCSs for various PDC instances.
 *
 * It performs initialization in two separate steps - common instances and
 * target specific ones. Currently it is
 */
void pdc_tcs_init (void);

/**
 * <!-- get_white_list -->
 *
 * @brief This function returns whitelist and its size for this target
 * @param num_entries: num entries being returned 
 * @return string array 
 */
char** get_white_list(size_t* num_entries);

#endif   /* _PDC_TCS_H_ */

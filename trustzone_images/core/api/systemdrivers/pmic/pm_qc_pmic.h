#ifndef PM_QC_PMIC_H
#define PM_QC_PMIC_H
/*===========================================================================


                  P M    H E A D E R    F I L E

DESCRIPTION
  This file contains prototype definitions to support interaction
  with the QUALCOMM Power Management ICs.

Copyright (c) 2003 - 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.3.c1/api/systemdrivers/pmic/pm_qc_pmic.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/16/12   hs      Removed obsolete files.
02/10/11   hw      Uncomment pmapp_pmic_events.h header
02/08/11   hw      Merging changes from the PMIC Distributed Driver Arch branch
06/28/03   wra     Created as final PMIC library main include file. Named
                   so that it will not have naming collision with other
                   HLOS header files. Most of the contents in this file
                   were formerly in pm.h
===========================================================================*/

/*===========================================================================

                        PMIC INCLUDE FILES

===========================================================================*/
#include "comdef.h"

#include "pm_lib_api.h"
#include "rpm.h"


/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/
/**
 * @brief This function executes the PMIC device initialization in TZ.
 *
 * @details
 *  This function executes the pmic device initialization in TZ, such as
 *  initializing the SSBI module, etc.
 *
 * @param[in] void No input needed.
 *
 * @return pm_err_flag_type
 *         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
 *         version of the PMIC.
 *         PM_ERR_FLAG__SUCCESS           = SUCCESS.
 *
 *
 */ 
pm_err_flag_type pm_init(void);

/**
 * @brief This function enable SSC retention and pin control.
 *
 * @details The function sets LDO pin control when bring SPLI out of reset. 
 *             
 *
 * @param[in] boolean active
 *                   TRUE when bringing SLPI out of reset and FALSE when putting SLPI into reset.
 *                    
 *
 * @return pm_err_flag_type
 *         PM_ERR_FLAG__SPMI_OPT_ERR  on SPMI error. 
 *         PM_ERR_FLAG__SUCCESS           = SUCCESS.
 *
 *
 */ 
pm_err_flag_type pm_ssc_config(boolean active);  

/**
 * @brief Set a CX rail corner.
 *
 * @details This function sets CX rail corner value for a spcific corner value.
 * It does not perform HW Read/Write. It instead sends message requesting RPM
 * for voltage change.
 *
 *  @param conner_value [in]  A new corner value.
 *  @param rpm_set [in]  Can be RPM_ACTIVE_SET or RPM_SLEEP_SET.
 *
 * @return pm_err_flag_type
 *  PM_ERR_FLAG__SUCCESS -- on success otherwise PMIC error code. \n
 * @dependencies
 *  None.
 * @sa None.
 *
 */
pm_err_flag_type
pm_app_cx_corner_request(uint32 corner_value, rpm_set_type rpm_set);

#endif    /* PM_QC_PMIC_H */


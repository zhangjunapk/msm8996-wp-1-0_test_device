#ifndef PM_PON_CFG_H
#define PM_PON_CFG_H

/*! \ file pm_pon_cfg.h
*
 * \brief   <Brief Comment Block/>
 * \details <Detailed Comment Block/>
 * \n &copy; Copyright 2015 QUALCOMM Technolgoies Incorporated, All Rights Reserved
 */

/*===================================================================
                    EDIT HISTORY FOR MODULE
 This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.3.c1/systemdrivers/pmic/framework/inc/pm_pon_cfg.h#1 $
$Author: pwbldsvc $

when       who     what, where, why
--------    ---     ------------------------------------------------
10/07/15    vtw     Created.
====================================================================*/

#include "pm_pon.h"
#include "pm_lib_err.h"


/* ============================================================================
**    Function Prototype.
** ==========================================================================*/

/**
 * @brief Get PSHOLD configuration.
 *
 * @details This function gets PMIC PSHOLD configuration
 *
 *  @param pmic_index [in]  PMIC device index.
 *  @param reset_cfg [in]  Config type to query. .
 *  @param pshold_cfg [out]  Pointer to PSHOLD configuration.
 *
 * @return pm_err_flag_type
 *  PM_ERR_FLAG__SUCCESS -- on success otherwise PMIC error code. \n
 * @dependencies
 *  None.
 * @sa None.
 *
 */

pm_err_flag_type
pm_get_pshold_cfg
(
  uint32                      pmic_index,
  pm_app_pon_reset_cfg_type   reset_cfg,
  pm_app_pon_reset_cfg_type*  pshold_cfg
 );


#endif // PM_PON_CFG_H

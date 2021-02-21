/*! \file
*  \n
*  \brief  pm_oem_config.c
*  \n
*  \n This file contains pmic configuration data specific for OEM support. 
*  \n reset.
*  \n
*  \n &copy; Copyright 2015 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.3.c1/systemdrivers/pmic/config/msm8996_pm8994/src/pm_oem_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

12/14/15   vtw     Created.
========================================================================== */

/*=========================================================================
      Include Files
==========================================================================*/

#include "pm_pon_cfg.h"
#include "device_info.h"

/*===========================================================================
Data Declarations
===========================================================================*/

/*
 * PSHOLD config specific for LGE.
 */
const pm_app_pon_reset_cfg_type pm_oem_pshold_cfg[PM_APP_PON_CFG_MAX][PM_MAX_NUM_PMICS] =
{  //       PM8994                              PMI8994                       PM8004                             PMK8001
   {PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_NO_CONFIG_NEEDED,  PM_APP_PON_CFG_NO_CONFIG_NEEDED,  0,0,0}, //No config needed
   {PM_APP_PON_CFG_WARM_RESET,       PM_APP_PON_CFG_WARM_RESET,       PM_APP_PON_CFG_NO_CONFIG_NEEDED,  PM_APP_PON_CFG_WARM_RESET,        0,0,0}, //Warm Reset
   {PM_APP_PON_CFG_HARD_RESET,       PM_APP_PON_CFG_DVDD_HARD_RESET,  PM_APP_PON_CFG_NO_CONFIG_NEEDED,  PM_APP_PON_CFG_NORMAL_SHUTDOWN,   0,0,0}, //Hard Reset
   {PM_APP_PON_CFG_NORMAL_SHUTDOWN,  PM_APP_PON_CFG_NORMAL_SHUTDOWN,  PM_APP_PON_CFG_NO_CONFIG_NEEDED,  PM_APP_PON_CFG_NORMAL_SHUTDOWN,   0,0,0}, //Shutdown
   {PM_APP_PON_CFG_DVDD_HARD_RESET,  PM_APP_PON_CFG_DVDD_SHUTDOWN,    PM_APP_PON_CFG_NO_CONFIG_NEEDED,  PM_APP_PON_CFG_DVDD_SHUTDOWN,     0,0,0}, //Dvdd hard reset
   {PM_APP_PON_CFG_DVDD_SHUTDOWN,    PM_APP_PON_CFG_DVDD_SHUTDOWN,    PM_APP_PON_CFG_NO_CONFIG_NEEDED,  PM_APP_PON_CFG_DVDD_SHUTDOWN,     0,0,0} //DVDD Shutdown
};

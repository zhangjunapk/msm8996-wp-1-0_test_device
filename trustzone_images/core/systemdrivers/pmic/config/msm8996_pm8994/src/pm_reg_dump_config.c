/*! \file
*  \n
*  \brief  pm_reg_dump_config.c
*  \n
*  \n This file contains pmic configuration data specific for PMIC debug APIs.
*  \n
*  \n &copy; Copyright 2014-2015 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.3.c1/systemdrivers/pmic/config/msm8996_pm8994/src/pm_reg_dump_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

4/20/15   vtw     Updated for 8996 V2 support.
========================================================================== */

/*=========================================================================
      Include Files
==========================================================================*/

#include "pm_internal.h"

/*===========================================================================
Data Declarations
===========================================================================*/

/*
 * Array PMIC peripherals supply DDR rails.
 */
const pm_rail_reg_type pm_ddr_rai_reg[] =
{

  /* VDD_CX*/
  {0x1, 0x1400, PM_RAIL_TYPE_SMPS},    /* S1_CTRL */
  {0x1, 0x1600, PM_RAIL_TYPE_SMPS},    /* S1_FREQ */
  //{0x1, 0x2300, PM_RAIL_TYPE_SMPS},    /* S6_CTRL */ -- not mapped 
  //{0x1, 0x2500, PM_RAIL_TYPE_SMPS},    /* S6_FREQ */

  /* VDD_PX3*/
  {0x1, 0x1D00, PM_RAIL_TYPE_SMPS},    /* S4_CTRL */
  {0x1, 0x1F00, PM_RAIL_TYPE_SMPS},    /* S4_FREQ */

  /* VDD_PX11*/
  {0x1, 0x2000, PM_RAIL_TYPE_SMPS},    /* S5_CTRL */
  {0x1, 0x2200, PM_RAIL_TYPE_SMPS},    /* S5_FREQ */

  /* VDDA_EBI */
  {0x1, 0x4100, PM_RAIL_TYPE_LDO},    /* LDO2 */
  {0x1, 0x4200, PM_RAIL_TYPE_LDO},    /* LDO3 */
  {0x1, 0x5B00, PM_RAIL_TYPE_LDO},    /* LDO28 */

  /* End of array */
  {0xf, 0xffff, PM_RAIL_TYPE_INV},
};




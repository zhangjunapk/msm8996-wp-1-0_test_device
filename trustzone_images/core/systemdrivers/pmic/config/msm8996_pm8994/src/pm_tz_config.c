/*! \file
*  \n
*  \brief  pm_spmi_config.c
*  \n
*  \n This file contains pmic configuration data specific for SPMI Controller's
      Peripheral for MSM8996 device..
*  \n
*  \n &copy; Copyright 2015 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.3.c1/systemdrivers/pmic/config/msm8996_pm8994/src/pm_tz_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/26/15   vtw    Updated for V2 support.
03/02/15   vtw    Updated PVC port master numbers.
07/16/13   vtw    Created.
========================================================================== */

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/

#include "SpmiCfg.h"

/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/

/* Converts a PVC port index to an overall PMIC Arbiter port index */
#define PVC_PORT_TO_PMIC_ARB_PORT(p) (p+1)

/*   Port assignment in 8996   */
#define GPU_PORT           0   /* GPU */
#define HMSS_SAW2_PORT     1   /*  APPS_PORT */
#define MSS_SAW2_PORT      4   /* MSS Q6 SAW2   */
#define MSS_MVC_PORT       3   /* Modem MVC   */
#define MSS_MGPI_PORT      2   /* Modem MGPI   */

/*-------------------------------------------------------------------------
* Static Variable Definitions
* ----------------------------------------------------------------------*/

/*
 * pm_pvc_hmss_addr
 *
 * PVC port addr for HMSS block.
 */
static SpmiCfg_Ppid pm_pvc_hmss_addr[] =
{
  {0x1, 0x3241}, /* PMIC 8994, Periph S11_CTRL, S11_CTRL_VOLTAGE_CTL2 */
  {0x1, 0x3254}, /* PMIC 8994, Periph S11_CTRL, S11_CTRL_PHASE_CNT_MAX */
  {0x1, 0x3245}, /* PMIC 8994, Periph S11_CTRL, S11_CTRL_MODE_CTL */
  {0x1, 0x3246}, /* PMIC 8994, Periph S11_CTRL, S11_CTRL_EN_CTL */
};

/*
 * pm_pvc_mss_addr
 *
 * PVC port addr for MPSS.
 */
static SpmiCfg_Ppid pm_pvc_mss_addr[] =
{
  {0x1, 0x2641},    /* PM8994, Periph S7_CTRL, S7_CTRL_VOLTAGE_CTL2 */
  // {0x0, 0x7A42}, /* PM8994, PBS_CLIENT9_TRIG_CTL */
  {0x1, 0x2645},    /* PM8994, Periph S7_CTRL, S7_CTRL_MODE_CTL */
  {0x1, 0x2646},    /* PM8994, Periph S7_CTRL, S7_CTRL_EN_CTL */
};


/*
 * pm_pvc_mgpi_addr
 *
 * PVC port addr for MGPI block.
 */
static SpmiCfg_Ppid pm_pvc_mgpi_addr[] =
{
  {0x2, 0x094A}, /* PMI8994, MISC_TX_GTR_THRES_CTL */
};

/*
 * pm_arb_pvc_cfg
 *
 * PMIC Arbiter PVC ports config.
 */
const SpmiCfg_PvcPortCfg pm_arb_pvc_cfg[] =
{
  {
    /* .pvcPortId = */  HMSS_SAW2_PORT,
    /* .priority  = */ SPMI_ACCESS_PRIORITY_LOW,
    /* .ppids     = */ pm_pvc_hmss_addr,
    /* .numPpids  = */ sizeof(pm_pvc_hmss_addr)/sizeof(SpmiCfg_Ppid)
  },
  {
    /* .pvcPortId = */  MSS_SAW2_PORT,
    /* .priority  = */ SPMI_ACCESS_PRIORITY_LOW,
    /* .ppids     = */ pm_pvc_mss_addr,
    /* .numPpids  = */ sizeof(pm_pvc_mss_addr)/sizeof(SpmiCfg_Ppid)
  },
  {
    /* .pvcPortId = */  MSS_MGPI_PORT,
    /* .priority  = */ SPMI_ACCESS_PRIORITY_LOW,
    /* .ppids     = */ pm_pvc_mgpi_addr,
    /* .numPpids  = */ sizeof(pm_pvc_mgpi_addr)/sizeof(SpmiCfg_Ppid)
  }
};

/* Number of pvc ports. */
const uint32 pm_num_pvc_port = sizeof(pm_arb_pvc_cfg) / sizeof(SpmiCfg_PvcPortCfg);

const uint8 pm_arb_priorities[] =
{
    0,                                         /* SW port -- highest priority */
    PVC_PORT_TO_PMIC_ARB_PORT(HMSS_SAW2_PORT),
    PVC_PORT_TO_PMIC_ARB_PORT(MSS_SAW2_PORT),
    PVC_PORT_TO_PMIC_ARB_PORT(MSS_MGPI_PORT)

};

/* Number of port prioriries. */
const uint32 pm_num_prio = sizeof(pm_arb_priorities) / sizeof(uint8);

































































































































































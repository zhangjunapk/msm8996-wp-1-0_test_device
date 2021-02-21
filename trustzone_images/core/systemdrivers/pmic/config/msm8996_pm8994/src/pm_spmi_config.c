/*! \file
*  \n
*  \brief  pm_spmi_config.c
*  \n
*  \n This file contains pmic configuration data specific for SPMI Controller's
      Peripheral for MSM8996 device..
*  \n
*  \n &copy; Copyright 2014 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.3.c1/systemdrivers/pmic/config/msm8996_pm8994/src/pm_spmi_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/24/15   vtw    Added open all ownership.
06/23/15   vtw    Added VDD_EBI rail
03/26/15   vtw    Updated for V2 support.
03/02/15   vtw    Updated PVC port master numbers.
07/16/13   vtw    Created.
========================================================================== */

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/

#include "pm_spmi.h"

/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
* Static Variable Definitions
* ----------------------------------------------------------------------*/

/* PMIC MMU/SMMU configuration table. */

SpmiCfg_ChannelCfg pm_spmi_pheriph_cfg [] =
{
  /* PM8994 */
  {0, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* REVID */
  {0, 0x05, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* INT */
  {0, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* SPMI */
  {0, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER}, /* PON */
  {0, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER}, /* MISC */
  {0, 0x1C, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* BUA_EXT_CHARGER */
  {0, 0x24, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* TEMP_ALARM */
  {0, 0x28, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* COIN */
  {0, 0x31, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* VADC1_USR */
  {0, 0x32, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* VADC3_MDM */
  {0, 0x34, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* VADC2_BTM */
  {0, 0x50, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* XO */
  {0, 0x51, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* BB_CLK1 */
  {0, 0x52, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* BB_CLK2 */
  {0, 0x54, 0, PM_MSS_OWNER, PM_MSS_OWNER     }, /* RF_CLK1 */
  {0, 0x55, 0, PM_MSS_OWNER, PM_MSS_OWNER     }, /* RF_CLK2 */
  {0, 0x58, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LN_BB_CLK */
  {0, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* CLK_DIST */
  {0, 0x5A, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* SLEEP_CLK1 */
  {0, 0x5B, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* DIV_CLK1 */
  {0, 0x5C, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* DIV_CLK2 */
  {0, 0x5D, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* DIV_CLK3 */
  {0, 0x60, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* RTC_RW */
  {0, 0x61, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* RTC_ALARM */
  {0, 0x62, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* RTC_TIMER */
  {0, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CORE */
  {0, 0x72, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT1 */
  {0, 0x75, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT4 */
  {0, 0x76, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT5 */
  {0, 0x77, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* PBS_CLIENT6 */
  {0, 0x7A, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT9 */
  {0, 0x7B, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT10 */
  {0, 0x7C, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* PBS_CLIENT11 */
  {0, 0x7D, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT12 */
  {0, 0x7E, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT13 */
  {0, 0x7F, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT14 */
  {0, 0x80, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT15 */
  {0, 0xA0, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* MPP1 */
  {0, 0xA1, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP2 */
  {0, 0xA2, 0, PM_MSS_OWNER, SPMI_OPEN_OWNER          },   /* MPP3 */
  {0, 0xA3, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP4 */
  {0, 0xA4, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP5 */
  {0, 0xA5, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP6 */
  {0, 0xA6, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP7 */
  {0, 0xA7, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP8 */
  {0, 0xC0, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO1 */
  {0, 0xC1, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO2 */
  {0, 0xC2, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO3 */
  {0, 0xC3, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO4 */
  {0, 0xC4, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO5 */
  {0, 0xC5, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER }, /* GPIO6 */
  {0, 0xC6, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO7 */
  {0, 0xC7, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO8 */
  {0, 0xC8, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO9 */
  {0, 0xC9, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO10 */
  {0, 0xCA, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO11 */
  {0, 0xCB, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO12 */
  {0, 0xCC, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO13 */
  {0, 0xCD, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO14 */
  {0, 0xCE, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO15 */
  {0, 0xCF, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO16 */
  {0, 0xD0, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO17 */
  {0, 0xD1, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO18 */
  {0, 0xD2, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO19 */
  {0, 0xD3, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO20 */
  {0, 0xD4, 0, PM_MSS_OWNER, PM_MSS_OWNER             }, /* GPIO21 */
  {0, 0xD5, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO22 */

  {1, 0x10, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* BCLK_GEN_MAIN */
  {1, 0x14, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S1_CTRL */
  {1, 0x16, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S1_FREQ */
  {1, 0x17, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S2_CTRL */
  {1, 0x19, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S2_FREQ */
  {1, 0x1A, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S3_CTRL */
  {1, 0x1C, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S3_FREQ */
  {1, 0x1D, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S4_CTRL */
  {1, 0x1F, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S4_FREQ */
  {1, 0x20, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S5_CTRL */
  {1, 0x22, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S5_FREQ */
  {1, 0x26, 0, PM_MSS_OWNER, PM_MSS_OWNER            },   /* S7_CTRL */
  {1, 0x28, 0, PM_MSS_OWNER, PM_MSS_OWNER            },   /* S7_FREQ */
  {1, 0x29, 0, PM_RPM_OWNER,  PM_RPM_OWNER            },   /* S8_CTRL */
  {1, 0x2B, 0, PM_RPM_OWNER,  PM_RPM_OWNER            },   /* S8_FREQ */
  {1, 0x32, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* S11_CTRL */
  {1, 0x34, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* S11_FREQ */
  {1, 0x35, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S12_CTRL */
  {1, 0x37, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S12_FREQ */
  {1, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO1 */
  {1, 0x41, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO2 */
  {1, 0x42, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO3 */
  {1, 0x43, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO4 */
  {1, 0x45, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO6 */
  {1, 0x46, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO7 */
  {1, 0x47, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO8 */
  {1, 0x48, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* LDO9 */
  {1, 0x49, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* LDO10 */
  {1, 0x4A, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO11 */
  {1, 0x4B, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO12 */
  {1, 0x4C, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO13 */
  {1, 0x4D, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO14 */
  {1, 0x4E, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO15 */
  {1, 0x4F, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO16 */
  {1, 0x50, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO17 */
  {1, 0x51, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO18 */
  {1, 0x52, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO19 */
  {1, 0x53, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO20 */
  {1, 0x54, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO21 */
  {1, 0x55, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO22 */
  {1, 0x56, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO23 */
  {1, 0x57, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO24 */
  {1, 0x58, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO25 */
  {1, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO26 */
  {1, 0x5A, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO27 */
  {1, 0x5B, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO28 */
  {1, 0x5C, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO29 */
  {1, 0x5D, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO30 */
  {1, 0x5E, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO31 */
  {1, 0x5F, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO32 */
  {1, 0x80, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LVS1 */
  {1, 0x81, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LVS2 */
  {1, 0xB0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_LUT */
  {1, 0xB1, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN1 */
  {1, 0xB2, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN2 */
  {1, 0xB3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN3 */
  {1, 0xB4, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN4 */
  {1, 0xB5, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN5 */
  {1, 0xB6, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN6 */
  {1, 0xBC, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* PWM_3D */
  /* PMI8994 */
  {2, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* REVID */
  {2, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* PON */
  {2, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* MISC */
  {2, 0x10, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* SMBCHG_CHGR */
  {2, 0x11, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* SMBCHG_OTG */
  {2, 0x12, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* SMBCHG_BAT_IF */
  {2, 0x13, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* SMBCHG_USB_CHGPTH */
  {2, 0x14, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* SMBCHG_DC_CHGPTH */
  {2, 0x16, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* SMBCHG_MISC */
  {2, 0x1B, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* BSI */
  {2, 0x31, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* VADC1_USR */
  {2, 0x40, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* FG_SOC */
  {2, 0x41, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* FG_BATT */
  {2, 0x42, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* FG_ADC_USR */
  {2, 0x43, 0, PM_MSS_OWNER, PM_MSS_OWNER      }, /* FG_ADC_MDM */
  {2, 0x44, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* FG_MEMIF */
  {2, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* CLK_DIST */
  {2, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CORE */
  {2, 0x74, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT3 */
  {2, 0x75, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT4 */
  {2, 0x76, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT5 */
  {2, 0x77, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT6 */
  {2, 0x79, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT8 */
  {2, 0x7A, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT9 */
  {2, 0x7B, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT10 */
  {2, 0x7C, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT11 */
  {2, 0xA0, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP1 */
  {2, 0xA1, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP2 */
  {2, 0xA2, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* MPP3 */
  {2, 0xA3, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP4 */
  {2, 0xC0, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO1 */
  {2, 0xC1, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO2 */
  {2, 0xC2, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO3 */
  {2, 0xC3, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO4 */
  {2, 0xC4, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO5 */
  {2, 0xC5, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO6 */
  {2, 0xC6, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO7 */
  {2, 0xC7, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO8 */
  {2, 0xC8, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO9 */
  {2, 0xC9, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO10 */
  {3, 0x10, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* BCLK_GEN_MAIN */
  {3, 0x14, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S1_CTRL */
  {3, 0x16, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* S1_FREQ */
  {3, 0x17, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER            },   /* S2_CTRL */
  {3, 0x19, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER            },   /* S2_FREQ */
  {3, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* LDO1 */
  {3, 0xA0, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* BOOST */
  {3, 0xA1, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* BOOST_FREQ */
  {3, 0xA2, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* BOOST_BYP */
  {3, 0xB0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_LUT */
  {3, 0xB1, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN1 */
  {3, 0xB2, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN2 */
  {3, 0xB3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN3 */
  {3, 0xB4, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LPG_CHAN4 */
  {3, 0xC0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* HAPTICS */
  {3, 0xD0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* TRI_LED */
  {3, 0xD3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* FLASH1 */
  {3, 0xD8, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* WLED1_CTRL */
  {3, 0xD9, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* WLED1_SINK */
  {3, 0xDC, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* IBB */
  {3, 0xDE, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* LAB */
  /* PM8004*/
  {4, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* REVID */
  {4, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* PON */
  {4, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* MISC */
  {4, 0x24, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* TEMP_ALARM */
  {4, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* CLK_DIST */
  {4, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CORE */
  {4, 0x76, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT5 */
  {4, 0x77, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT6 */
  {4, 0x78, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* PBS_CLIENT7 */
  {4, 0xA0, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* MPP1 */
  {4, 0xA1, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP2 */
  {4, 0xA2, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP3 */
  {4, 0xA3, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* MPP4 */
  {5, 0x10, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* BCLK_GEN_MAIN */
  {5, 0x14, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* S1_CTRL */
  {5, 0x16, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* S1_FREQ */
  {5, 0x17, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER            },   /* S2_CTRL */
  {5, 0x19, 0, PM_APPS_HLOS_OWNER,  PM_APPS_HLOS_OWNER      }, /* S2_FREQ */
  {5, 0x20, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* S5_CTRL */
  {5, 0x22, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* S5_FREQ */
  {5, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER      }, /* LDO1 */
  /* PMK8001 */
  {6, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* REVID */
  {6, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* PON */
  {6, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* MISC */
  {6, 0x50, 0, PM_MSS_OWNER, PM_MSS_OWNER            },   /* XO */
  {6, 0x54, 0, PM_RPM_OWNER, PM_MSS_OWNER            },   /* RF_CLK1 */
  {6, 0x55, 0, PM_RPM_OWNER, PM_MSS_OWNER            },   /* RF_CLK2 */
  {6, 0x58, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* LN_BB_CLK */
  {6, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* CLK_DIST */
  {6, 0x5A, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* SLEEP_CLK1 */
  {6, 0x5B, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* DIV_CLK1 */
  {6, 0x5C, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* DIV_CLK2 */
  {6, 0x5D, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* DIV_CLK3 */
  {6, 0x5E, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* CALRC2 */
  {6, 0x60, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* RTC_RW */
  {6, 0x61, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* RTC_ALARM */
  {6, 0x62, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},   /* RTC_TIMER */
  {6, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* PBS_CORE */
  {6, 0x74, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* PBS_CLIENT3 */
  {6, 0x75, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* PBS_CLIENT4 */
  {6, 0xC0, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER         },   /* GPIO1 */
  {6, 0xC1, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER         },   /* GPIO2 */
  {6, 0xC2, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER         },   /* GPIO3 */
  {6, 0xC3, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER         },   /* GPIO4 */
  {7, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* REVID1 */
  {7, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* LDO_XO */
  {7, 0x41, 0, PM_RPM_OWNER, PM_RPM_OWNER            },   /* LDO_RF */

  /* Peripheral with slave ID for broadcast write access.*/
  {14, 0x05, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* INT */
  {14, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER     }, /* SPMI */
  {14, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER     }, /* PON */


};

/* Number of spmi channels config entries. . */
uint32 pm_spmi_pheriph_cfg_sz = sizeof(pm_spmi_pheriph_cfg) / sizeof(SpmiCfg_ChannelCfg);
































































































































































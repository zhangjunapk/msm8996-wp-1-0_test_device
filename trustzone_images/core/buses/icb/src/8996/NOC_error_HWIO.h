#ifndef __NOC_ERROR_HWIO_H__
#define __NOC_ERROR_HWIO_H__
/*
===========================================================================
*/
/**
  @file NOC_error_HWIO.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    CONFIG_NOC
    MMSS_NOC
    PERIPH_NOC
    SYSTEM_NOC

  'Include' filters applied: REG_BASE[SYSTEM_NOC] REG_BASE[CONFIG_NOC] REG_BASE[MMSS_NOC] REG_BASE[PERIPH_NOC] 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2014 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.tz/1.0.3.c1/buses/icb/src/8996/NOC_error_HWIO.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: SYSTEM_NOC
 *--------------------------------------------------------------------------*/

#define SYSTEM_NOC_REG_BASE                                 (SYSTEM_NOC_BASE      + 0x00000000)

#define HWIO_SNOC_OBS_ID_COREID_ADDR                        (SYSTEM_NOC_REG_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: PERIPH_NOC
 *--------------------------------------------------------------------------*/

#define PERIPH_NOC_REG_BASE                                 (PERIPH_NOC_BASE      + 0x00000000)

#define HWIO_PNOC_OBS_ID_COREID_ADDR                        (PERIPH_NOC_REG_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: MMSS_NOC
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_REG_BASE                                   (MMSS_NOC_BASE      + 0x00000000)

#define HWIO_MNOC_OBS_ID_COREID_ADDR                        (MMSS_NOC_REG_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CONFIG_NOC
 *--------------------------------------------------------------------------*/

#define CONFIG_NOC_REG_BASE                                 (CONFIG_NOC_BASE      + 0x00000000)

#define HWIO_CNOC_OBS_ID_COREID_ADDR                        (CONFIG_NOC_REG_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: A0_NOC_AGGRE0_NOC
 *--------------------------------------------------------------------------*/

#define A0_NOC_AGGRE0_NOC_REG_BASE                           (A0_NOC_AGGRE0_NOC_BASE      + 0x00000000)

#define HWIO_A0_NOC_AGGRE0NOC_OBS_ID_COREID_ADDR             (A0_NOC_AGGRE0_NOC_REG_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: A1_NOC_AGGRE1_NOC
 *--------------------------------------------------------------------------*/

#define A1_NOC_AGGRE1_NOC_REG_BASE                           (A1_NOC_AGGRE1_NOC_BASE      + 0x00000000)

#define HWIO_A1_NOC_AGGRE1NOC_OBS_ID_COREID_ADDR             (A1_NOC_AGGRE1_NOC_REG_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: A2_NOC_AGGRE2_NOC
 *--------------------------------------------------------------------------*/

#define A2_NOC_AGGRE2_NOC_REG_BASE                           (A2_NOC_AGGRE2_NOC_BASE      + 0x00000000)

#define HWIO_A2_NOC_AGGRE2NOC_OBS_ID_COREID_ADDR             (A2_NOC_AGGRE2_NOC_REG_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_GLOBAL1
 *--------------------------------------------------------------------------*/

#define BIMC_GLOBAL1_REG_BASE                                                   (BIMC_BASE      + 0x00001000)

#define HWIO_BIMC_BRIC_INTERRUPT_STATUS_0_ADDR                                  (BIMC_GLOBAL1_REG_BASE      + 0x00000100)

#define HWIO_BIMC_BRIC_INTERRUPT_STATUS_1_ADDR                                  (BIMC_GLOBAL1_REG_BASE      + 0x00000110)

#define HWIO_BIMC_BRIC_INTERRUPT_STATUS_2_ADDR                                  (BIMC_GLOBAL1_REG_BASE      + 0x00000120)

#define HWIO_BIMC_BRIC_INTERRUPT_STATUS_3_ADDR                                  (BIMC_GLOBAL1_REG_BASE      + 0x00000130)

#define HWIO_BIMC_BRIC_INTERRUPT_STATUS_4_ADDR                                  (BIMC_GLOBAL1_REG_BASE      + 0x00000140)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DDR0_SCMO
 *--------------------------------------------------------------------------*/

#define BIMC_S_DDR0_SCMO_REG_BASE                                                    (BIMC_BASE      + 0x00030000)

#define HWIO_BIMC_S_DDR0_SCMO_INTERRUPT_STATUS_ADDR                                  (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_ADDR_ADDR                                         (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000120)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_ADDR1_ADDR                                        (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000124)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_0_ADDR                                    (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000128)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_1_ADDR                                    (BIMC_S_DDR0_SCMO_REG_BASE      + 0x0000012c)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_2_ADDR                                    (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000130)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DDR1_SCMO
 *--------------------------------------------------------------------------*/

#define BIMC_S_DDR1_SCMO_REG_BASE                                                    (BIMC_BASE      + 0x0003c000)

#define HWIO_BIMC_S_DDR1_SCMO_INTERRUPT_STATUS_ADDR                                  (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_ADDR_ADDR                                         (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000120)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_ADDR1_ADDR                                        (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000124)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_0_ADDR                                    (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000128)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_1_ADDR                                    (BIMC_S_DDR1_SCMO_REG_BASE      + 0x0000012c)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_2_ADDR                                    (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000130)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DEFAULT_SWAY
 *--------------------------------------------------------------------------*/

#define BIMC_S_DEFAULT_SWAY_REG_BASE                                                   (BIMC_BASE      + 0x00060000)

#define HWIO_BIMC_S_DEFAULT_SWAY_INTERRUPT_STATUS_ADDR                                 (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_0_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000400)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_1_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000410)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_2_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000420)

/*----------------------------------------------------------------------------
 * MODULE: L3_QLL_HML3_CSR
 *--------------------------------------------------------------------------*/

#define L3_QLL_HML3_CSR_REG_BASE                                   (HMSS_QLL_BASE      + 0x00100000)

#define HWIO_L3_QLL_HML3_FIRA_ADDR                                 (L3_QLL_HML3_CSR_REG_BASE      + 0x00003000)

#define HWIO_L3_QLL_HML3_FIRAC_ADDR                                (L3_QLL_HML3_CSR_REG_BASE      + 0x00003008)

#define HWIO_L3_QLL_HML3_FIRAME_ADDR                               (L3_QLL_HML3_CSR_REG_BASE      + 0x00003030)

#define HWIO_L3_QLL_HML3_FIRAMI_ADDR                               (L3_QLL_HML3_CSR_REG_BASE      + 0x00003034)

#define HWIO_L3_QLL_HML3_FIRAS_ADDR                                (L3_QLL_HML3_CSR_REG_BASE      + 0x00003010)

#define HWIO_L3_QLL_HML3_FIRAT0_ADDR                               (L3_QLL_HML3_CSR_REG_BASE      + 0x00003018)

#define HWIO_L3_QLL_HML3_FIRAT0C_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x00003020)

#define HWIO_L3_QLL_HML3_FIRAT0S_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x00003028)

#define HWIO_L3_QLL_HML3_FIRAT1_ADDR                               (L3_QLL_HML3_CSR_REG_BASE      + 0x0000301c)

#define HWIO_L3_QLL_HML3_FIRAT1C_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x00003024)

#define HWIO_L3_QLL_HML3_FIRAT1S_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x0000302c)

#define HWIO_L3_QLL_HML3_FIRSYNA_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x00003100)

#define HWIO_L3_QLL_HML3_FIRSYNB_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x00003104)

#define HWIO_L3_QLL_HML3_FIRSYNC_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x00003108)

#define HWIO_L3_QLL_HML3_FIRSYND_ADDR                              (L3_QLL_HML3_CSR_REG_BASE      + 0x0000310c)

/*----------------------------------------------------------------------------
 * MODULE: APCS_CBF_CBF_M4M_REGS
 *--------------------------------------------------------------------------*/

#define APCS_CBF_CBF_M4M_REGS_REG_BASE                                              (HMSS_BASE      + 0x00240000)

#define HWIO_APCS_CBF_M4M_ERR_STATUS_ADDR                                           (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010000)

#define HWIO_APCS_CBF_M4M_ERR_CLR_ADDR                                              (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010008)

#define HWIO_APCS_CBF_M4M_INT_CTRL_ADDR                                             (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010010)

#define HWIO_APCS_CBF_M4M_ERR_CTRL_ADDR                                             (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010018)

#define HWIO_APCS_CBF_M4M_ERR_INJ_ADDR                                              (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010020)

#define HWIO_APCS_CBF_M4M_ERR_CAP_0_ADDR                                            (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010030)

#define HWIO_APCS_CBF_M4M_ERR_CAP_1_ADDR                                            (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010038)

#define HWIO_APCS_CBF_M4M_ERR_CAP_2_ADDR                                            (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010040)

#define HWIO_APCS_CBF_M4M_ERR_CAP_3_ADDR                                            (APCS_CBF_CBF_M4M_REGS_REG_BASE      + 0x00010048)

/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                 (CLK_CTL_BASE      + 0x00000000)

#define HWIO_GCC_SNOC_BUS_TIMEOUT_EXTREF_CTL_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x00049024)

#define HWIO_GCC_CNOC_BUS_TIMEOUT_EXTREF_CTL_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x00080014)



#endif /* __NOC_ERROR_HWIO_H__ */

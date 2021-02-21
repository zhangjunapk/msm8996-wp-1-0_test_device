#ifndef __BIMC_HWIO_H__
#define __BIMC_HWIO_H__
/*
===========================================================================
*/
/**
  @file BIMC_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8996 (Istari) v2 [istari_v2.1_p3q2r16.11]
 
  This file contains HWIO register definitions for the following modules:
    BIMC_S_DDR0_SCMO
    BIMC_S_DDR1_SCMO
    BIMC_S_DEFAULT_SWAY
    BIMC_GLOBAL2

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2015 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: //components/rel/core.tz/1.0.3.c1/buses/icb/src/8996/BIMC_error_HWIO.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DDR0_SCMO
 *--------------------------------------------------------------------------*/

#define BIMC_S_DDR0_SCMO_REG_BASE                                                         (BIMC_BASE      + 0x00030000)

#define HWIO_BIMC_S_DDR0_SCMO_INTERRUPT_STATUS_ADDR                                       (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DDR0_SCMO_INTERRUPT_CLEAR_ADDR                                        (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000108)

#define HWIO_BIMC_S_DDR0_SCMO_INTERRUPT_ENABLE_ADDR                                       (BIMC_S_DDR0_SCMO_REG_BASE      + 0x0000010c)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_ADDR_ADDR                                              (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000120)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_ADDR1_ADDR                                             (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000124)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_0_ADDR                                         (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000128)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_1_ADDR                                         (BIMC_S_DDR0_SCMO_REG_BASE      + 0x0000012c)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_2_ADDR                                         (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000130)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DDR1_SCMO
 *--------------------------------------------------------------------------*/

#define BIMC_S_DDR1_SCMO_REG_BASE                                                         (BIMC_BASE      + 0x0003c000)

#define HWIO_BIMC_S_DDR1_SCMO_INTERRUPT_STATUS_ADDR                                       (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DDR1_SCMO_INTERRUPT_CLEAR_ADDR                                        (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000108)

#define HWIO_BIMC_S_DDR1_SCMO_INTERRUPT_ENABLE_ADDR                                       (BIMC_S_DDR1_SCMO_REG_BASE      + 0x0000010c)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_ADDR_ADDR                                              (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000120)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_ADDR1_ADDR                                             (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000124)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_0_ADDR                                         (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000128)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_1_ADDR                                         (BIMC_S_DDR1_SCMO_REG_BASE      + 0x0000012c)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_2_ADDR                                         (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000130)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DEFAULT_SWAY
 *--------------------------------------------------------------------------*/

#define BIMC_S_DEFAULT_SWAY_REG_BASE                                                   (BIMC_BASE      + 0x00060000)

#define HWIO_BIMC_S_DEFAULT_SWAY_INTERRUPT_STATUS_ADDR                                 (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DEFAULT_SWAY_INTERRUPT_CLEAR_ADDR                                  (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000108)

#define HWIO_BIMC_S_DEFAULT_SWAY_INTERRUPT_ENABLE_ADDR                                 (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x0000010c)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_0_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000400)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_1_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000410)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_2_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000420)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_GLOBAL2
 *--------------------------------------------------------------------------*/

#define BIMC_GLOBAL2_REG_BASE                                                      (BIMC_BASE      + 0x00002000)

#define HWIO_BIMC_BRIC_INTERRUPT_1_STATUS_1_ADDR                                   (BIMC_GLOBAL2_REG_BASE      + 0x00000110)

#define HWIO_BIMC_BRIC_INTERRUPT_1_CLEAR_1_ADDR                                    (BIMC_GLOBAL2_REG_BASE      + 0x00000118)

#define HWIO_BIMC_BRIC_INTERRUPT_1_ENABLE_1_ADDR                                   (BIMC_GLOBAL2_REG_BASE      + 0x0000011c)

#define HWIO_BIMC_BRIC_INTERRUPT_1_STATUS_2_ADDR                                   (BIMC_GLOBAL2_REG_BASE      + 0x00000120)

#define HWIO_BIMC_BRIC_INTERRUPT_1_CLEAR_2_ADDR                                    (BIMC_GLOBAL2_REG_BASE      + 0x00000128)

#define HWIO_BIMC_BRIC_INTERRUPT_1_ENABLE_2_ADDR                                   (BIMC_GLOBAL2_REG_BASE      + 0x0000012c)

#define HWIO_BIMC_BRIC_INTERRUPT_1_STATUS_3_ADDR                                   (BIMC_GLOBAL2_REG_BASE      + 0x00000130)

#define HWIO_BIMC_BRIC_INTERRUPT_1_CLEAR_3_ADDR                                    (BIMC_GLOBAL2_REG_BASE      + 0x00000138)

#define HWIO_BIMC_BRIC_INTERRUPT_1_ENABLE_3_ADDR                                   (BIMC_GLOBAL2_REG_BASE      + 0x0000013c)


#endif /* __BIMC_HWIO_H__ */

#ifndef __MSMHWIOBASE_H__
#define __MSMHWIOBASE_H__
/*
===========================================================================
*/
/**
  @file msmhwiobase.h
  @brief Auto-generated HWIO base include file.
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

  $Header: //components/rel/core.tz/1.0.3.c1/api/systemdrivers/hwio/msm8996/phys/msmhwiobase.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

  ===========================================================================
*/


/*
 * Renamed bases.
 */
#define QDSS_QDSS_APB_BASE                                          QDSS_QDSS_ISTARI_BASE
#define QDSS_QDSS_APB_BASE_SIZE                                     QDSS_QDSS_ISTARI_BASE_SIZE
#define QDSS_QDSS_APB_BASE_PHYS                                     QDSS_QDSS_ISTARI_BASE_PHYS


/*----------------------------------------------------------------------------
 * BASE: DCC_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define DCC_RAM_SIZE_BASE                                           0x00002000
#define DCC_RAM_SIZE_BASE_SIZE                                      0x00000000
#define DCC_RAM_SIZE_BASE_PHYS                                      0x00002000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_RAM_SIZE_BASE                                           0x00004000
#define SSC_RAM_SIZE_BASE_SIZE                                      0x00000000
#define SSC_RAM_SIZE_BASE_PHYS                                      0x00004000

/*----------------------------------------------------------------------------
 * BASE: RPM_SS_MSG_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define RPM_SS_MSG_RAM_SIZE_BASE                                    0x00006000
#define RPM_SS_MSG_RAM_SIZE_BASE_SIZE                               0x00000000
#define RPM_SS_MSG_RAM_SIZE_BASE_PHYS                               0x00006000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_LPM_SIZE_BASE                                         0x00010000
#define LPASS_LPM_SIZE_BASE_SIZE                                    0x00000000
#define LPASS_LPM_SIZE_BASE_PHYS                                    0x00010000

/*----------------------------------------------------------------------------
 * BASE: RPM_DATA_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define RPM_DATA_RAM_SIZE_BASE                                      0x00014000
#define RPM_DATA_RAM_SIZE_BASE_SIZE                                 0x00000000
#define RPM_DATA_RAM_SIZE_BASE_PHYS                                 0x00014000

/*----------------------------------------------------------------------------
 * BASE: CNOC_0_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_0_BUS_TIMEOUT_BASE                                     0x00020000
#define CNOC_0_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_0_BUS_TIMEOUT_BASE_PHYS                                0x00020000

/*----------------------------------------------------------------------------
 * BASE: CNOC_1_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_1_BUS_TIMEOUT_BASE                                     0x00021000
#define CNOC_1_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_1_BUS_TIMEOUT_BASE_PHYS                                0x00021000

/*----------------------------------------------------------------------------
 * BASE: CNOC_2_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_2_BUS_TIMEOUT_BASE                                     0x00022000
#define CNOC_2_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_2_BUS_TIMEOUT_BASE_PHYS                                0x00022000

/*----------------------------------------------------------------------------
 * BASE: CNOC_3_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_3_BUS_TIMEOUT_BASE                                     0x00023000
#define CNOC_3_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_3_BUS_TIMEOUT_BASE_PHYS                                0x00023000

/*----------------------------------------------------------------------------
 * BASE: CNOC_4_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_4_BUS_TIMEOUT_BASE                                     0x00024000
#define CNOC_4_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_4_BUS_TIMEOUT_BASE_PHYS                                0x00024000

/*----------------------------------------------------------------------------
 * BASE: CNOC_5_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_5_BUS_TIMEOUT_BASE                                     0x00025000
#define CNOC_5_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_5_BUS_TIMEOUT_BASE_PHYS                                0x00025000

/*----------------------------------------------------------------------------
 * BASE: CNOC_6_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_6_BUS_TIMEOUT_BASE                                     0x00026000
#define CNOC_6_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_6_BUS_TIMEOUT_BASE_PHYS                                0x00026000

/*----------------------------------------------------------------------------
 * BASE: CNOC_7_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_7_BUS_TIMEOUT_BASE                                     0x00027000
#define CNOC_7_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_7_BUS_TIMEOUT_BASE_PHYS                                0x00027000

/*----------------------------------------------------------------------------
 * BASE: RPM_CODE_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define RPM_CODE_RAM_SIZE_BASE                                      0x00028000
#define RPM_CODE_RAM_SIZE_BASE_SIZE                                 0x00000000
#define RPM_CODE_RAM_SIZE_BASE_PHYS                                 0x00028000

/*----------------------------------------------------------------------------
 * BASE: CNOC_8_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_8_BUS_TIMEOUT_BASE                                     0x00028000
#define CNOC_8_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_8_BUS_TIMEOUT_BASE_PHYS                                0x00028000

/*----------------------------------------------------------------------------
 * BASE: CNOC_9_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_9_BUS_TIMEOUT_BASE                                     0x00029000
#define CNOC_9_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define CNOC_9_BUS_TIMEOUT_BASE_PHYS                                0x00029000

/*----------------------------------------------------------------------------
 * BASE: XPU_CFG_CPR_APU1132_2
 *--------------------------------------------------------------------------*/

#define XPU_CFG_CPR_APU1132_2_BASE                                  0x0002c000
#define XPU_CFG_CPR_APU1132_2_BASE_SIZE                             0x00000300
#define XPU_CFG_CPR_APU1132_2_BASE_PHYS                             0x0002c000

/*----------------------------------------------------------------------------
 * BASE: XPU_CFG_SNOC_CFG_MPU1032_4_M16L12_AHB
 *--------------------------------------------------------------------------*/

#define XPU_CFG_SNOC_CFG_MPU1032_4_M16L12_AHB_BASE                  0x0002d000
#define XPU_CFG_SNOC_CFG_MPU1032_4_M16L12_AHB_BASE_SIZE             0x00000400
#define XPU_CFG_SNOC_CFG_MPU1032_4_M16L12_AHB_BASE_PHYS             0x0002d000

/*----------------------------------------------------------------------------
 * BASE: XPU_CFG_ANOC0_CFG_MPU1032_4_M16L12_AHB
 *--------------------------------------------------------------------------*/

#define XPU_CFG_ANOC0_CFG_MPU1032_4_M16L12_AHB_BASE                 0x0002e000
#define XPU_CFG_ANOC0_CFG_MPU1032_4_M16L12_AHB_BASE_SIZE            0x00000400
#define XPU_CFG_ANOC0_CFG_MPU1032_4_M16L12_AHB_BASE_PHYS            0x0002e000

/*----------------------------------------------------------------------------
 * BASE: XPU_CFG_ANOC1_CFG_MPU1032_4_M16L12_AHB
 *--------------------------------------------------------------------------*/

#define XPU_CFG_ANOC1_CFG_MPU1032_4_M16L12_AHB_BASE                 0x0002f000
#define XPU_CFG_ANOC1_CFG_MPU1032_4_M16L12_AHB_BASE_SIZE            0x00000400
#define XPU_CFG_ANOC1_CFG_MPU1032_4_M16L12_AHB_BASE_PHYS            0x0002f000

/*----------------------------------------------------------------------------
 * BASE: XPU_CFG_ANOC2_CFG_MPU1032_4_M16L12_AHB
 *--------------------------------------------------------------------------*/

#define XPU_CFG_ANOC2_CFG_MPU1032_4_M16L12_AHB_BASE                 0x00030000
#define XPU_CFG_ANOC2_CFG_MPU1032_4_M16L12_AHB_BASE_SIZE            0x00000400
#define XPU_CFG_ANOC2_CFG_MPU1032_4_M16L12_AHB_BASE_PHYS            0x00030000

/*----------------------------------------------------------------------------
 * BASE: XPU_CFG_QDSS_MPU1132_3_M23L12_AHB
 *--------------------------------------------------------------------------*/

#define XPU_CFG_QDSS_MPU1132_3_M23L12_AHB_BASE                      0x00031000
#define XPU_CFG_QDSS_MPU1132_3_M23L12_AHB_BASE_SIZE                 0x00000380
#define XPU_CFG_QDSS_MPU1132_3_M23L12_AHB_BASE_PHYS                 0x00031000

/*----------------------------------------------------------------------------
 * BASE: XPU_CFG_SSC_MPU1032_10_M22L11_AHB
 *--------------------------------------------------------------------------*/

#define XPU_CFG_SSC_MPU1032_10_M22L11_AHB_BASE                      0x00032000
#define XPU_CFG_SSC_MPU1032_10_M22L11_AHB_BASE_SIZE                 0x00000700
#define XPU_CFG_SSC_MPU1032_10_M22L11_AHB_BASE_PHYS                 0x00032000

/*----------------------------------------------------------------------------
 * BASE: PCIE20_AHB2PHY
 *--------------------------------------------------------------------------*/

#define PCIE20_AHB2PHY_BASE                                         0x00034000
#define PCIE20_AHB2PHY_BASE_SIZE                                    0x00004000
#define PCIE20_AHB2PHY_BASE_PHYS                                    0x00034000

/*----------------------------------------------------------------------------
 * BASE: RAMBLUR_PIMEM
 *--------------------------------------------------------------------------*/

#define RAMBLUR_PIMEM_BASE                                          0x00038000
#define RAMBLUR_PIMEM_BASE_SIZE                                     0x00008000
#define RAMBLUR_PIMEM_BASE_PHYS                                     0x00038000

/*----------------------------------------------------------------------------
 * BASE: BOOT_ROM_SIZE
 *--------------------------------------------------------------------------*/

#define BOOT_ROM_SIZE_BASE                                          0x0003c000
#define BOOT_ROM_SIZE_BASE_SIZE                                     0x00000000
#define BOOT_ROM_SIZE_BASE_PHYS                                     0x0003c000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM_SIZE
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_SIZE_BASE                                       0x00040000
#define SYSTEM_IMEM_SIZE_BASE_SIZE                                  0x00000000
#define SYSTEM_IMEM_SIZE_BASE_PHYS                                  0x00040000

/*----------------------------------------------------------------------------
 * BASE: OCIMEM_WRAPPER_CSR
 *--------------------------------------------------------------------------*/

#define OCIMEM_WRAPPER_CSR_BASE                                     0x00040000
#define OCIMEM_WRAPPER_CSR_BASE_SIZE                                0x00004000
#define OCIMEM_WRAPPER_CSR_BASE_PHYS                                0x00040000

/*----------------------------------------------------------------------------
 * BASE: SPDM_WRAPPER_TOP
 *--------------------------------------------------------------------------*/

#define SPDM_WRAPPER_TOP_BASE                                       0x00048000
#define SPDM_WRAPPER_TOP_BASE_SIZE                                  0x00008000
#define SPDM_WRAPPER_TOP_BASE_PHYS                                  0x00048000

/*----------------------------------------------------------------------------
 * BASE: CPR3
 *--------------------------------------------------------------------------*/

#define CPR3_BASE                                                   0x00050000
#define CPR3_BASE_SIZE                                              0x00004000
#define CPR3_BASE_PHYS                                              0x00050000

/*----------------------------------------------------------------------------
 * BASE: MX_CPR3
 *--------------------------------------------------------------------------*/

#define MX_CPR3_BASE                                                0x00054000
#define MX_CPR3_BASE_SIZE                                           0x00004000
#define MX_CPR3_BASE_PHYS                                           0x00054000

/*----------------------------------------------------------------------------
 * BASE: ISTARI_SKL_WRAPPER
 *--------------------------------------------------------------------------*/

#define ISTARI_SKL_WRAPPER_BASE                                     0x00058000
#define ISTARI_SKL_WRAPPER_BASE_SIZE                                0x00004000
#define ISTARI_SKL_WRAPPER_BASE_PHYS                                0x00058000

/*----------------------------------------------------------------------------
 * BASE: MSS_MPU_MPU1032A_16_M35L12_AXI_36
 *--------------------------------------------------------------------------*/

#define MSS_MPU_MPU1032A_16_M35L12_AXI_36_BASE                      0x0005c000
#define MSS_MPU_MPU1032A_16_M35L12_AXI_36_BASE_SIZE                 0x00000a00
#define MSS_MPU_MPU1032A_16_M35L12_AXI_36_BASE_PHYS                 0x0005c000

/*----------------------------------------------------------------------------
 * BASE: MSS_Q6_MPU_MPU1032A_16_M35L12_AXI_36
 *--------------------------------------------------------------------------*/

#define MSS_Q6_MPU_MPU1032A_16_M35L12_AXI_36_BASE                   0x0005d000
#define MSS_Q6_MPU_MPU1032A_16_M35L12_AXI_36_BASE_SIZE              0x00000a00
#define MSS_Q6_MPU_MPU1032A_16_M35L12_AXI_36_BASE_PHYS              0x0005d000

/*----------------------------------------------------------------------------
 * BASE: ANOC1_MPU_MPU1032A_16_M35L12_AXI_36
 *--------------------------------------------------------------------------*/

#define ANOC1_MPU_MPU1032A_16_M35L12_AXI_36_BASE                    0x0005e000
#define ANOC1_MPU_MPU1032A_16_M35L12_AXI_36_BASE_SIZE               0x00000a00
#define ANOC1_MPU_MPU1032A_16_M35L12_AXI_36_BASE_PHYS               0x0005e000

/*----------------------------------------------------------------------------
 * BASE: ANOC2_MPU_MPU1032A_16_M35L12_AXI_36
 *--------------------------------------------------------------------------*/

#define ANOC2_MPU_MPU1032A_16_M35L12_AXI_36_BASE                    0x0005f000
#define ANOC2_MPU_MPU1032A_16_M35L12_AXI_36_BASE_SIZE               0x00000a00
#define ANOC2_MPU_MPU1032A_16_M35L12_AXI_36_BASE_PHYS               0x0005f000

/*----------------------------------------------------------------------------
 * BASE: RPM_SS_MSG_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_SS_MSG_RAM_START_ADDRESS_BASE                           0x00068000
#define RPM_SS_MSG_RAM_START_ADDRESS_BASE_SIZE                      0x00000000
#define RPM_SS_MSG_RAM_START_ADDRESS_BASE_PHYS                      0x00068000

/*----------------------------------------------------------------------------
 * BASE: RPM_MSG_RAM
 *--------------------------------------------------------------------------*/

#define RPM_MSG_RAM_BASE                                            0x00068000
#define RPM_MSG_RAM_BASE_SIZE                                       0x00006000
#define RPM_MSG_RAM_BASE_PHYS                                       0x00068000

/*----------------------------------------------------------------------------
 * BASE: RPM_SS_MSG_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_SS_MSG_RAM_END_ADDRESS_BASE                             0x0006dfff
#define RPM_SS_MSG_RAM_END_ADDRESS_BASE_SIZE                        0x00000000
#define RPM_SS_MSG_RAM_END_ADDRESS_BASE_PHYS                        0x0006dfff

/*----------------------------------------------------------------------------
 * BASE: SECURITY_CONTROL
 *--------------------------------------------------------------------------*/

#define SECURITY_CONTROL_BASE                                       0x00070000
#define SECURITY_CONTROL_BASE_SIZE                                  0x00010000
#define SECURITY_CONTROL_BASE_PHYS                                  0x00070000

/*----------------------------------------------------------------------------
 * BASE: PRNG_CFG_PRNG_TOP
 *--------------------------------------------------------------------------*/

#define PRNG_CFG_PRNG_TOP_BASE                                      0x00080000
#define PRNG_CFG_PRNG_TOP_BASE_SIZE                                 0x00010000
#define PRNG_CFG_PRNG_TOP_BASE_PHYS                                 0x00080000

/*----------------------------------------------------------------------------
 * BASE: MMSS_VMEM_SIZE
 *--------------------------------------------------------------------------*/

#define MMSS_VMEM_SIZE_BASE                                         0x00100000
#define MMSS_VMEM_SIZE_BASE_SIZE                                    0x00000000
#define MMSS_VMEM_SIZE_BASE_PHYS                                    0x00100000

/*----------------------------------------------------------------------------
 * BASE: BOOT_ROM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define BOOT_ROM_START_ADDRESS_BASE                                 0x00100000
#define BOOT_ROM_START_ADDRESS_BASE_SIZE                            0x00000000
#define BOOT_ROM_START_ADDRESS_BASE_PHYS                            0x00100000

/*----------------------------------------------------------------------------
 * BASE: L3_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define L3_TCM_SIZE_BASE                                            0x00100000
#define L3_TCM_SIZE_BASE_SIZE                                       0x00000000
#define L3_TCM_SIZE_BASE_PHYS                                       0x00100000

/*----------------------------------------------------------------------------
 * BASE: BOOT_ROM
 *--------------------------------------------------------------------------*/

#define BOOT_ROM_BASE                                               0x00100000
#define BOOT_ROM_BASE_SIZE                                          0x00100000
#define BOOT_ROM_BASE_PHYS                                          0x00100000

/*----------------------------------------------------------------------------
 * BASE: BOOT_ROM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define BOOT_ROM_END_ADDRESS_BASE                                   0x0013bfff
#define BOOT_ROM_END_ADDRESS_BASE_SIZE                              0x00000000
#define BOOT_ROM_END_ADDRESS_BASE_PHYS                              0x0013bfff

/*----------------------------------------------------------------------------
 * BASE: RPM_CODE_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_CODE_RAM_START_ADDRESS_BASE                             0x00200000
#define RPM_CODE_RAM_START_ADDRESS_BASE_SIZE                        0x00000000
#define RPM_CODE_RAM_START_ADDRESS_BASE_PHYS                        0x00200000

/*----------------------------------------------------------------------------
 * BASE: RPM
 *--------------------------------------------------------------------------*/

#define RPM_BASE                                                    0x00200000
#define RPM_BASE_SIZE                                               0x00100000
#define RPM_BASE_PHYS                                               0x00200000

/*----------------------------------------------------------------------------
 * BASE: RPM_CODE_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_CODE_RAM_END_ADDRESS_BASE                               0x00227fff
#define RPM_CODE_RAM_END_ADDRESS_BASE_SIZE                          0x00000000
#define RPM_CODE_RAM_END_ADDRESS_BASE_PHYS                          0x00227fff

/*----------------------------------------------------------------------------
 * BASE: RPM_DATA_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_DATA_RAM_START_ADDRESS_BASE                             0x00290000
#define RPM_DATA_RAM_START_ADDRESS_BASE_SIZE                        0x00000000
#define RPM_DATA_RAM_START_ADDRESS_BASE_PHYS                        0x00290000

/*----------------------------------------------------------------------------
 * BASE: RPM_DATA_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_DATA_RAM_END_ADDRESS_BASE                               0x002a3fff
#define RPM_DATA_RAM_END_ADDRESS_BASE_SIZE                          0x00000000
#define RPM_DATA_RAM_END_ADDRESS_BASE_PHYS                          0x002a3fff

/*----------------------------------------------------------------------------
 * BASE: CLK_CTL
 *--------------------------------------------------------------------------*/

#define CLK_CTL_BASE                                                0x00300000
#define CLK_CTL_BASE_SIZE                                           0x000a0000
#define CLK_CTL_BASE_PHYS                                           0x00300000

/*----------------------------------------------------------------------------
 * BASE: QDSP6SS_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define QDSP6SS_TCM_SIZE_BASE                                       0x00400000
#define QDSP6SS_TCM_SIZE_BASE_SIZE                                  0x00000000
#define QDSP6SS_TCM_SIZE_BASE_PHYS                                  0x00400000

/*----------------------------------------------------------------------------
 * BASE: BIMC
 *--------------------------------------------------------------------------*/

#define BIMC_BASE                                                   0x00400000
#define BIMC_BASE_SIZE                                              0x00080000
#define BIMC_BASE_PHYS                                              0x00400000

/*----------------------------------------------------------------------------
 * BASE: DDR_SS
 *--------------------------------------------------------------------------*/

#define DDR_SS_BASE                                                 0x00480000
#define DDR_SS_BASE_SIZE                                            0x00020000
#define DDR_SS_BASE_PHYS                                            0x00480000

/*----------------------------------------------------------------------------
 * BASE: MPM2_MPM
 *--------------------------------------------------------------------------*/

#define MPM2_MPM_BASE                                               0x004a0000
#define MPM2_MPM_BASE_SIZE                                          0x00010000
#define MPM2_MPM_BASE_PHYS                                          0x004a0000

/*----------------------------------------------------------------------------
 * BASE: DCC_WRAPPER
 *--------------------------------------------------------------------------*/

#define DCC_WRAPPER_BASE                                            0x004b0000
#define DCC_WRAPPER_BASE_SIZE                                       0x00004000
#define DCC_WRAPPER_BASE_PHYS                                       0x004b0000

/*----------------------------------------------------------------------------
 * BASE: DCC_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define DCC_RAM_START_ADDRESS_BASE                                  0x004b4000
#define DCC_RAM_START_ADDRESS_BASE_SIZE                             0x00000000
#define DCC_RAM_START_ADDRESS_BASE_PHYS                             0x004b4000

/*----------------------------------------------------------------------------
 * BASE: DCC_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define DCC_RAM_END_ADDRESS_BASE                                    0x004b5fff
#define DCC_RAM_END_ADDRESS_BASE_SIZE                               0x00000000
#define DCC_RAM_END_ADDRESS_BASE_PHYS                               0x004b5fff

/*----------------------------------------------------------------------------
 * BASE: CONFIG_NOC
 *--------------------------------------------------------------------------*/

#define CONFIG_NOC_BASE                                             0x00500000
#define CONFIG_NOC_BASE_SIZE                                        0x00000080
#define CONFIG_NOC_BASE_PHYS                                        0x00500000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_NOC
 *--------------------------------------------------------------------------*/

#define SYSTEM_NOC_BASE                                             0x00520000
#define SYSTEM_NOC_BASE_SIZE                                        0x0000a100
#define SYSTEM_NOC_BASE_PHYS                                        0x00520000

/*----------------------------------------------------------------------------
 * BASE: A0_NOC_AGGRE0_NOC
 *--------------------------------------------------------------------------*/

#define A0_NOC_AGGRE0_NOC_BASE                                      0x00540000
#define A0_NOC_AGGRE0_NOC_BASE_SIZE                                 0x00005100
#define A0_NOC_AGGRE0_NOC_BASE_PHYS                                 0x00540000

/*----------------------------------------------------------------------------
 * BASE: A1_NOC_AGGRE1_NOC
 *--------------------------------------------------------------------------*/

#define A1_NOC_AGGRE1_NOC_BASE                                      0x00560000
#define A1_NOC_AGGRE1_NOC_BASE_SIZE                                 0x00003100
#define A1_NOC_AGGRE1_NOC_BASE_PHYS                                 0x00560000

/*----------------------------------------------------------------------------
 * BASE: A2_NOC_AGGRE2_NOC
 *--------------------------------------------------------------------------*/

#define A2_NOC_AGGRE2_NOC_BASE                                      0x00580000
#define A2_NOC_AGGRE2_NOC_BASE_SIZE                                 0x00008100
#define A2_NOC_AGGRE2_NOC_BASE_PHYS                                 0x00580000

/*----------------------------------------------------------------------------
 * BASE: MMSS_NOC
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_BASE                                               0x005a0000
#define MMSS_NOC_BASE_SIZE                                          0x0000b080
#define MMSS_NOC_BASE_PHYS                                          0x005a0000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_NOC
 *--------------------------------------------------------------------------*/

#define PERIPH_NOC_BASE                                             0x005c0000
#define PERIPH_NOC_BASE_SIZE                                        0x00002480
#define PERIPH_NOC_BASE_PHYS                                        0x005c0000

/*----------------------------------------------------------------------------
 * BASE: PCIE_0_PCIE20_WRAPPER_AHB
 *--------------------------------------------------------------------------*/

#define PCIE_0_PCIE20_WRAPPER_AHB_BASE                              0x00600000
#define PCIE_0_PCIE20_WRAPPER_AHB_BASE_SIZE                         0x00008000
#define PCIE_0_PCIE20_WRAPPER_AHB_BASE_PHYS                         0x00600000

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_PCIE20_WRAPPER_AHB
 *--------------------------------------------------------------------------*/

#define PCIE_1_PCIE20_WRAPPER_AHB_BASE                              0x00608000
#define PCIE_1_PCIE20_WRAPPER_AHB_BASE_SIZE                         0x00008000
#define PCIE_1_PCIE20_WRAPPER_AHB_BASE_PHYS                         0x00608000

/*----------------------------------------------------------------------------
 * BASE: PCIE_2_PCIE20_WRAPPER_AHB
 *--------------------------------------------------------------------------*/

#define PCIE_2_PCIE20_WRAPPER_AHB_BASE                              0x00610000
#define PCIE_2_PCIE20_WRAPPER_AHB_BASE_SIZE                         0x00008000
#define PCIE_2_PCIE20_WRAPPER_AHB_BASE_PHYS                         0x00610000

/*----------------------------------------------------------------------------
 * BASE: UFS_UFS_REGS
 *--------------------------------------------------------------------------*/

#define UFS_UFS_REGS_BASE                                           0x00620000
#define UFS_UFS_REGS_BASE_SIZE                                      0x00020000
#define UFS_UFS_REGS_BASE_PHYS                                      0x00620000

/*----------------------------------------------------------------------------
 * BASE: CRYPTO0_CRYPTO_TOP
 *--------------------------------------------------------------------------*/

#define CRYPTO0_CRYPTO_TOP_BASE                                     0x00640000
#define CRYPTO0_CRYPTO_TOP_BASE_SIZE                                0x00040000
#define CRYPTO0_CRYPTO_TOP_BASE_PHYS                                0x00640000

/*----------------------------------------------------------------------------
 * BASE: IPA_0_IPA_WRAPPER
 *--------------------------------------------------------------------------*/

#define IPA_0_IPA_WRAPPER_BASE                                      0x00680000
#define IPA_0_IPA_WRAPPER_BASE_SIZE                                 0x00080000
#define IPA_0_IPA_WRAPPER_BASE_PHYS                                 0x00680000

/*----------------------------------------------------------------------------
 * BASE: CORE_TOP_CSR
 *--------------------------------------------------------------------------*/

#define CORE_TOP_CSR_BASE                                           0x00700000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00100000
#define CORE_TOP_CSR_BASE_PHYS                                      0x00700000

/*----------------------------------------------------------------------------
 * BASE: MMSS
 *--------------------------------------------------------------------------*/

#define MMSS_BASE                                                   0x00800000
#define MMSS_BASE_SIZE                                              0x00800000
#define MMSS_BASE_PHYS                                              0x00800000

/*----------------------------------------------------------------------------
 * BASE: PIMEM_SIZE
 *--------------------------------------------------------------------------*/

#define PIMEM_SIZE_BASE                                             0x01000000
#define PIMEM_SIZE_BASE_SIZE                                        0x00000000
#define PIMEM_SIZE_BASE_PHYS                                        0x01000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM_SIZE
 *--------------------------------------------------------------------------*/

#define QDSS_STM_SIZE_BASE                                          0x01000000
#define QDSS_STM_SIZE_BASE_SIZE                                     0x00000000
#define QDSS_STM_SIZE_BASE_PHYS                                     0x01000000

/*----------------------------------------------------------------------------
 * BASE: TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                                                   0x01000000
#define TLMM_BASE_SIZE                                              0x00310000
#define TLMM_BASE_PHYS                                              0x01000000

/*----------------------------------------------------------------------------
 * BASE: LPASS_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_ISTARI
 *--------------------------------------------------------------------------*/

#define LPASS_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_ISTARI_BASE             0x01600000
#define LPASS_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_ISTARI_BASE_SIZE        0x00020000
#define LPASS_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_ISTARI_BASE_PHYS        0x01600000

/*----------------------------------------------------------------------------
 * BASE: LPASS_CORE_SMMU_QSMMUV2_WRAP_LPASS_CORE_ISTARI
 *--------------------------------------------------------------------------*/

#define LPASS_CORE_SMMU_QSMMUV2_WRAP_LPASS_CORE_ISTARI_BASE         0x01620000
#define LPASS_CORE_SMMU_QSMMUV2_WRAP_LPASS_CORE_ISTARI_BASE_SIZE    0x00020000
#define LPASS_CORE_SMMU_QSMMUV2_WRAP_LPASS_CORE_ISTARI_BASE_PHYS    0x01620000

/*----------------------------------------------------------------------------
 * BASE: ANOC0_SMMU_QSMMUV2_WRAP_PCIE_ISTARI
 *--------------------------------------------------------------------------*/

#define ANOC0_SMMU_QSMMUV2_WRAP_PCIE_ISTARI_BASE                    0x01640000
#define ANOC0_SMMU_QSMMUV2_WRAP_PCIE_ISTARI_BASE_SIZE               0x00020000
#define ANOC0_SMMU_QSMMUV2_WRAP_PCIE_ISTARI_BASE_PHYS               0x01640000

/*----------------------------------------------------------------------------
 * BASE: ANOC1_SMMU_QSMMUV2_WRAP_ANOC1_ISTARI
 *--------------------------------------------------------------------------*/

#define ANOC1_SMMU_QSMMUV2_WRAP_ANOC1_ISTARI_BASE                   0x01660000
#define ANOC1_SMMU_QSMMUV2_WRAP_ANOC1_ISTARI_BASE_SIZE              0x00020000
#define ANOC1_SMMU_QSMMUV2_WRAP_ANOC1_ISTARI_BASE_PHYS              0x01660000

/*----------------------------------------------------------------------------
 * BASE: ANOC2_SMMU_QSMMUV2_WRAP_ANOC2_ISTARI
 *--------------------------------------------------------------------------*/

#define ANOC2_SMMU_QSMMUV2_WRAP_ANOC2_ISTARI_BASE                   0x01680000
#define ANOC2_SMMU_QSMMUV2_WRAP_ANOC2_ISTARI_BASE_SIZE              0x00020000
#define ANOC2_SMMU_QSMMUV2_WRAP_ANOC2_ISTARI_BASE_PHYS              0x01680000

/*----------------------------------------------------------------------------
 * BASE: MDM_Q6_SMMU_QSMMUV2_WRAP_MDM_Q6_ISTARI
 *--------------------------------------------------------------------------*/

#define MDM_Q6_SMMU_QSMMUV2_WRAP_MDM_Q6_ISTARI_BASE                 0x016a0000
#define MDM_Q6_SMMU_QSMMUV2_WRAP_MDM_Q6_ISTARI_BASE_SIZE            0x00020000
#define MDM_Q6_SMMU_QSMMUV2_WRAP_MDM_Q6_ISTARI_BASE_PHYS            0x016a0000

/*----------------------------------------------------------------------------
 * BASE: SSC
 *--------------------------------------------------------------------------*/

#define SSC_BASE                                                    0x01800000
#define SSC_BASE_SIZE                                               0x00800000
#define SSC_BASE_PHYS                                               0x01800000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_START_ADDRESS_BASE                                  0x01ec0000
#define SSC_RAM_START_ADDRESS_BASE_SIZE                             0x00000000
#define SSC_RAM_START_ADDRESS_BASE_PHYS                             0x01ec0000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_END_ADDRESS_BASE                                    0x01ec3fff
#define SSC_RAM_END_ADDRESS_BASE_SIZE                               0x00000000
#define SSC_RAM_END_ADDRESS_BASE_PHYS                               0x01ec3fff

/*----------------------------------------------------------------------------
 * BASE: MODEM_TOP
 *--------------------------------------------------------------------------*/

#define MODEM_TOP_BASE                                              0x02000000
#define MODEM_TOP_BASE_SIZE                                         0x01000000
#define MODEM_TOP_BASE_PHYS                                         0x02000000

/*----------------------------------------------------------------------------
 * BASE: QDSP6SS_TCM
 *--------------------------------------------------------------------------*/

#define QDSP6SS_TCM_BASE                                            0x02400000
#define QDSP6SS_TCM_BASE_SIZE                                       0x00000000
#define QDSP6SS_TCM_BASE_PHYS                                       0x02400000

/*----------------------------------------------------------------------------
 * BASE: QDSP6SS_TCM_END
 *--------------------------------------------------------------------------*/

#define QDSP6SS_TCM_END_BASE                                        0x027fffff
#define QDSP6SS_TCM_END_BASE_SIZE                                   0x00000000
#define QDSP6SS_TCM_END_BASE_PHYS                                   0x027fffff

/*----------------------------------------------------------------------------
 * BASE: QDSS_QDSS_ISTARI
 *--------------------------------------------------------------------------*/

#define QDSS_QDSS_ISTARI_BASE                                       0x03000000
#define QDSS_QDSS_ISTARI_BASE_SIZE                                  0x00800000
#define QDSS_QDSS_ISTARI_BASE_PHYS                                  0x03000000

/*----------------------------------------------------------------------------
 * BASE: HMSS_DBG_HMSS_DEBUG
 *--------------------------------------------------------------------------*/

#define HMSS_DBG_HMSS_DEBUG_BASE                                    0x03800000
#define HMSS_DBG_HMSS_DEBUG_BASE_SIZE                               0x00400000
#define HMSS_DBG_HMSS_DEBUG_BASE_PHYS                               0x03800000

/*----------------------------------------------------------------------------
 * BASE: PMIC_ARB
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_BASE                                               0x04000000
#define PMIC_ARB_BASE_SIZE                                          0x01c00000
#define PMIC_ARB_BASE_PHYS                                          0x04000000

/*----------------------------------------------------------------------------
 * BASE: L3_TCM
 *--------------------------------------------------------------------------*/

#define L3_TCM_BASE                                                 0x06000000
#define L3_TCM_BASE_SIZE                                            0x00000000
#define L3_TCM_BASE_PHYS                                            0x06000000

/*----------------------------------------------------------------------------
 * BASE: L3_TCM_END
 *--------------------------------------------------------------------------*/

#define L3_TCM_END_BASE                                             0x060fffff
#define L3_TCM_END_BASE_SIZE                                        0x00000000
#define L3_TCM_END_BASE_PHYS                                        0x060fffff

/*----------------------------------------------------------------------------
 * BASE: HMSS_QLL
 *--------------------------------------------------------------------------*/

#define HMSS_QLL_BASE                                               0x06400000
#define HMSS_QLL_BASE_SIZE                                          0x00200000
#define HMSS_QLL_BASE_PHYS                                          0x06400000

/*----------------------------------------------------------------------------
 * BASE: SNOC_1_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define SNOC_1_BUS_TIMEOUT_BASE                                     0x06601000
#define SNOC_1_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define SNOC_1_BUS_TIMEOUT_BASE_PHYS                                0x06601000

/*----------------------------------------------------------------------------
 * BASE: SNOC_2_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define SNOC_2_BUS_TIMEOUT_BASE                                     0x06602000
#define SNOC_2_BUS_TIMEOUT_BASE_SIZE                                0x00001000
#define SNOC_2_BUS_TIMEOUT_BASE_PHYS                                0x06602000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_BASE                                            0x06680000
#define SYSTEM_IMEM_BASE_SIZE                                       0x00000000
#define SYSTEM_IMEM_BASE_PHYS                                       0x06680000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM_END
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_END_BASE                                        0x066bffff
#define SYSTEM_IMEM_END_BASE_SIZE                                   0x00000000
#define SYSTEM_IMEM_END_BASE_PHYS                                   0x066bffff

/*----------------------------------------------------------------------------
 * BASE: MMSS_VMEM
 *--------------------------------------------------------------------------*/

#define MMSS_VMEM_BASE                                              0x06800000
#define MMSS_VMEM_BASE_SIZE                                         0x00000000
#define MMSS_VMEM_BASE_PHYS                                         0x06800000

/*----------------------------------------------------------------------------
 * BASE: MMSS_VMEM_END
 *--------------------------------------------------------------------------*/

#define MMSS_VMEM_END_BASE                                          0x068fffff
#define MMSS_VMEM_END_BASE_SIZE                                     0x00000000
#define MMSS_VMEM_END_BASE_PHYS                                     0x068fffff

/*----------------------------------------------------------------------------
 * BASE: USB30_PRIM
 *--------------------------------------------------------------------------*/

#define USB30_PRIM_BASE                                             0x06a00000
#define USB30_PRIM_BASE_SIZE                                        0x00200000
#define USB30_PRIM_BASE_PHYS                                        0x06a00000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_BASE                                              0x07400000
#define PERIPH_SS_BASE_SIZE                                         0x00400000
#define PERIPH_SS_BASE_PHYS                                         0x07400000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM
 *--------------------------------------------------------------------------*/

#define QDSS_STM_BASE                                               0x08000000
#define QDSS_STM_BASE_SIZE                                          0x00000000
#define QDSS_STM_BASE_PHYS                                          0x08000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM_END
 *--------------------------------------------------------------------------*/

#define QDSS_STM_END_BASE                                           0x08ffffff
#define QDSS_STM_END_BASE_SIZE                                      0x00000000
#define QDSS_STM_END_BASE_PHYS                                      0x08ffffff

/*----------------------------------------------------------------------------
 * BASE: LPASS
 *--------------------------------------------------------------------------*/

#define LPASS_BASE                                                  0x09000000
#define LPASS_BASE_SIZE                                             0x00800000
#define LPASS_BASE_PHYS                                             0x09000000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_LPM_BASE                                              0x09120000
#define LPASS_LPM_BASE_SIZE                                         0x00000000
#define LPASS_LPM_BASE_PHYS                                         0x09120000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_LPM_END_BASE                                          0x0912ffff
#define LPASS_LPM_END_BASE_SIZE                                     0x00000000
#define LPASS_LPM_END_BASE_PHYS                                     0x0912ffff

/*----------------------------------------------------------------------------
 * BASE: HMSS
 *--------------------------------------------------------------------------*/

#define HMSS_BASE                                                   0x09800000
#define HMSS_BASE_SIZE                                              0x00800000
#define HMSS_BASE_PHYS                                              0x09800000

/*----------------------------------------------------------------------------
 * BASE: PIMEM
 *--------------------------------------------------------------------------*/

#define PIMEM_BASE                                                  0x0b000000
#define PIMEM_BASE_SIZE                                             0x00000000
#define PIMEM_BASE_PHYS                                             0x0b000000

/*----------------------------------------------------------------------------
 * BASE: PIMEM_END
 *--------------------------------------------------------------------------*/

#define PIMEM_END_BASE                                              0x0bffffff
#define PIMEM_END_BASE_SIZE                                         0x00000000
#define PIMEM_END_BASE_PHYS                                         0x0bffffff

/*----------------------------------------------------------------------------
 * BASE: PCIE_0_PCIE20_WRAPPER_AXI
 *--------------------------------------------------------------------------*/

#define PCIE_0_PCIE20_WRAPPER_AXI_BASE                              0x0c000000
#define PCIE_0_PCIE20_WRAPPER_AXI_BASE_SIZE                         0x01000000
#define PCIE_0_PCIE20_WRAPPER_AXI_BASE_PHYS                         0x0c000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_PCIE20_WRAPPER_AXI
 *--------------------------------------------------------------------------*/

#define PCIE_1_PCIE20_WRAPPER_AXI_BASE                              0x0d000000
#define PCIE_1_PCIE20_WRAPPER_AXI_BASE_SIZE                         0x01000000
#define PCIE_1_PCIE20_WRAPPER_AXI_BASE_PHYS                         0x0d000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_2_PCIE20_WRAPPER_AXI
 *--------------------------------------------------------------------------*/

#define PCIE_2_PCIE20_WRAPPER_AXI_BASE                              0x0e000000
#define PCIE_2_PCIE20_WRAPPER_AXI_BASE_SIZE                         0x02000000
#define PCIE_2_PCIE20_WRAPPER_AXI_BASE_PHYS                         0x0e000000

/*----------------------------------------------------------------------------
 * BASE: MODEM
 *--------------------------------------------------------------------------*/

#define MODEM_BASE                                                  0x10000000
#define MODEM_BASE_SIZE                                             0x02000000
#define MODEM_BASE_PHYS                                             0x10000000

/*----------------------------------------------------------------------------
 * BASE: DDR_MEM
 *--------------------------------------------------------------------------*/

#define DDR_MEM_BASE                                                0x80000000
#define DDR_MEM_BASE_SIZE                                           0x100000000
#define DDR_MEM_BASE_PHYS                                           0x80000000

/*----------------------------------------------------------------------------
 * BASE: DDR_MEM_SIZE
 *--------------------------------------------------------------------------*/

#define DDR_MEM_SIZE_BASE                                           0x180000000uLL
#define DDR_MEM_SIZE_BASE_SIZE                                      0x00000000
#define DDR_MEM_SIZE_BASE_PHYS                                      0x180000000uLL

/*----------------------------------------------------------------------------
 * BASE: DDR_MEM_END
 *--------------------------------------------------------------------------*/

#define DDR_MEM_END_BASE                                            0x1ffffffffuLL
#define DDR_MEM_END_BASE_SIZE                                       0x00000000
#define DDR_MEM_END_BASE_PHYS                                       0x1ffffffffuLL


#endif /* __MSMHWIOBASE_H__ */

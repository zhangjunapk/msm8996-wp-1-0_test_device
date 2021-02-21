#==============================================================================
# Target Build ID Config Script.
#
# Copyright (c) 2010 Qualcomm Technologies Inc.  All Rights Reserved
#==============================================================================

def exists(env):
   return env.Detect('tcfg_IADAANAAA_data')

def generate(env):
   # Save the tcfg_bid_data in the env
   env['TCFG_BID_IMAGE'] = 'APPS_PROC'

   env.AddUsesFlags('USES_NO_STRIP_NO_ODM', from_builds_file = True)
   env.AddUsesFlags('USES_PICT_BRIDGE', from_builds_file = True)
   env.AddUsesFlags('USES_SURF', from_builds_file = True)
   env.AddUsesFlags('USES_SMEM_SW_SPINLOCK', from_builds_file = True)
   env.AddUsesFlags('USES_NO_BOOT_LOADER', from_builds_file = True)
   env.AddUsesFlags('USES_DIAG_SMD_SUPPORT', from_builds_file = True)
   env.AddUsesFlags('USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN', from_builds_file = True)
   env.AddUsesFlags('USES_NAND16_4K_CFG_DATA', from_builds_file = True)
   env.AddUsesFlags('USES_ERR_SERVICES', from_builds_file = True)
   env.AddUsesFlags('USES_DEM', from_builds_file = True)
   env.AddUsesFlags('USES_HS_USB_CHG_REMOTE_API', from_builds_file = True)
   env.AddUsesFlags('USES_SMD_PORT_MGR', from_builds_file = True)
   env.AddUsesFlags('USES_BUS_PERF', from_builds_file = True)
   env.AddUsesFlags('USES_PHLP_XCVR', from_builds_file = True)
   env.AddUsesFlags('USES_DCACHE_IN_BOOT', from_builds_file = True)
   env.AddUsesFlags('USES_HIGH_POWER_CLK_FREQUENCY_PLAN', from_builds_file = True)
   env.AddUsesFlags('USES_PLAYREADY', from_builds_file = True)
   env.AddUsesFlags('USES_DDR36_CFG_DATA', from_builds_file = True)
   env.AddUsesFlags('USES_BOOT_LOGGER_RAM', from_builds_file = True)
   env.AddUsesFlags('USES_DDR_ONLY', from_builds_file = True)
   env.AddUsesFlags('USES_MBNTOOLS', from_builds_file = True)
   env.AddUsesFlags('USES_BOOT_LOGGER_TIMER', from_builds_file = True)
   env.AddUsesFlags('USES_FTM_HWTC', from_builds_file = True)
   env.AddUsesFlags('USES_LPDDR2', from_builds_file = True)
   env.AddUsesFlags('USES_AUTH', from_builds_file = True)
   env.AddUsesFlags('USES_BUS_MON_AXI_BUS_HANG_FIXED', from_builds_file = True)
   env.AddUsesFlags('USES_BOOT_LOGGER_JTAG', from_builds_file = True)
   env.AddUsesFlags('USES_HSU', from_builds_file = True)
   env.AddUsesFlags('USES_I2C_ON_APPS', from_builds_file = True)
   env.AddUsesFlags('USES_SEC_CLNT', from_builds_file = True)
   env.AddUsesFlags('USES_HW7500', from_builds_file = True)
   env.AddUsesFlags('USES_BUILD_NATIVELINUX_APPS', from_builds_file = True)
   env.AddUsesFlags('USES_LINUX_BT', from_builds_file = True)
   env.AddUsesFlags('USES_HSU_CHG_BOOT', from_builds_file = True)
   env.AddUsesFlags('USES_ARM_ASM_SPINLOCK', from_builds_file = True)
   env.AddUsesFlags('USES_HAL', from_builds_file = True)
   env.AddUsesFlags('USES_HSU_ECM', from_builds_file = True)
   env.AddUsesFlags('USES_SMD', from_builds_file = True)
   env.AddUsesFlags('USES_HSU_MS_FD_BOOT', from_builds_file = True)
   env.AddUsesFlags('USES_SFS', from_builds_file = True)
   env.AddUsesFlags('USES_BT_FTM_MODEM', from_builds_file = True)
   env.AddUsesFlags('USES_AKA', from_builds_file = True)
   env.AddUsesFlags('USES_PMIC_ON_APPS', from_builds_file = True)
   env.AddUsesFlags('USES_SEC_SVC', from_builds_file = True)
   env.AddUsesFlags('USES_SEC', from_builds_file = True)
   env.AddUsesFlags('USES_EFS2', from_builds_file = True)
   env.AddUsesFlags('USES_MBCBASBA', from_builds_file = True)
   env.AddUsesFlags('USES_QOS', from_builds_file = True)
   env.AddUsesFlags('USES_HSU_MS_FD', from_builds_file = True)
   env.AddUsesFlags('USES_SMEM', from_builds_file = True)
   env.AddUsesFlags('USES_EXPORT_7K_APIS', from_builds_file = True)
   env.AddUsesFlags('USES_SMEM_LOG', from_builds_file = True)
   env.AddUsesFlags('USES_SMD_BRIDGE', from_builds_file = True)
   env.AddUsesFlags('USES_PMEM_REMOTE', from_builds_file = True)
   env.AddUsesFlags('USES_I2C_ON_APPS', from_builds_file = True)
   env.AddUsesFlags('USES_SPLIT_CODE_DATA', from_builds_file = True)
   env.AddUsesFlags('USES_HSU_OTG', from_builds_file = True)
   env.AddUsesFlags('USES_DMOV', from_builds_file = True)
   env.AddUsesFlags('USES_APQ', from_builds_file = True)
   env.AddUsesFlags('USES_SDCC', from_builds_file = True)

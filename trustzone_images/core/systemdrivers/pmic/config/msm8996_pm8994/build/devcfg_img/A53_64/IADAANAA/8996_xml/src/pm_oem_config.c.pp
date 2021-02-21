# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/config/msm8996_pm8994/src/pm_oem_config.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/config/msm8996_pm8994/src/pm_oem_config.c" 2
# 27 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/config/msm8996_pm8994/src/pm_oem_config.c"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/framework/inc/pm_pon_cfg.h" 1
# 24 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/framework/inc/pm_pon_cfg.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h" 1
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_err.h" 1
# 42 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_err.h"
typedef enum
{



    PM_ERR_FLAG__SUCCESS,




    PM_ERR_FLAG__SBI_OPT_ERR,
    PM_ERR_FLAG__SBI_OPT2_ERR,
    PM_ERR_FLAG__SBI_OPT3_ERR,
    PM_ERR_FLAG__SBI_OPT4_ERR,

    PM_ERR_FLAG__I2C_OPT_ERR,
    PM_ERR_FLAG__I2C_OPT2_ERR,
    PM_ERR_FLAG__I2C_OPT3_ERR,
    PM_ERR_FLAG__I2C_OPT4_ERR,

    PM_ERR_FLAG__SPMI_OPT_ERR,
    PM_ERR_FLAG__SPMI_OPT2_ERR,
    PM_ERR_FLAG__SPMI_OPT3_ERR,
    PM_ERR_FLAG__SPMI_OPT4_ERR,

    PM_ERR_FLAG__SPMI_TRANSCOMM_ERR,





    PM_ERR_FLAG__PAR1_OUT_OF_RANGE,



    PM_ERR_FLAG__PAR2_OUT_OF_RANGE,



    PM_ERR_FLAG__PAR3_OUT_OF_RANGE,



    PM_ERR_FLAG__PAR4_OUT_OF_RANGE,



    PM_ERR_FLAG__PAR5_OUT_OF_RANGE,



    PM_ERR_FLAG__PAR6_OUT_OF_RANGE,
    PM_ERR_FLAG__VLEVEL_OUT_OF_RANGE,
    PM_ERR_FLAG__VREG_ID_OUT_OF_RANGE,



    PM_ERR_FLAG__FEATURE_NOT_SUPPORTED,
    PM_ERR_FLAG__INVALID_PMIC_MODEL,
    PM_ERR_FLAG__SECURITY_ERR,
    PM_ERR_FLAG__IRQ_LIST_ERR,
    PM_ERR_FLAG__DEV_MISMATCH,
    PM_ERR_FLAG__ADC_INVALID_RES,
    PM_ERR_FLAG__ADC_NOT_READY,
    PM_ERR_FLAG__ADC_SIG_NOT_SUPPORTED,



    PM_ERR_FLAG__RTC_BAD_DIS_MODE,



    PM_ERR_FLAG__RTC_READ_FAILED,



    PM_ERR_FLAG__RTC_WRITE_FAILED,



    PM_ERR_FLAG__RTC_HALTED,



    PM_ERR_FLAG__DBUS_IS_BUSY_MODE,



    PM_ERR_FLAG__ABUS_IS_BUSY_MODE,




    PM_ERR_FLAG__MACRO_NOT_RECOGNIZED,




    PM_ERR_FLAG__DATA_VERIFY_FAILURE,




    PM_ERR_FLAG__SETTING_TYPE_NOT_RECOGNIZED,




    PM_ERR_FLAG__MODE_NOT_DEFINED_FOR_MODE_GROUP,




    PM_ERR_FLAG__MODE_GROUP_NOT_DEFINED,



    PM_ERR_FLAG__PRESTUB_FAILURE,




    PM_ERR_FLAG__POSTSTUB_FAILURE,




    PM_ERR_FLAG__MODE_NOT_RECORDED_CORRECTLY,




    PM_ERR_FLAG__MODE_GROUP_STATE_NOT_FOUND,




    PM_ERR_FLAG__SUPERSTUB_FAILURE,

   PM_ERR_FLAG__TARGET_PROCESSOR_CAN_NOT_ACCESS_RESOURCE,



   PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED,




    PM_ERR_FLAG__VBATT_CLIENT_TABLE_FULL,

    PM_ERR_FLAG__VBATT_REG_PARAMS_WRONG,

    PM_ERR_FLAG__VBATT_DEREGISTRATION_FAILED,

    PM_ERR_FLAG__VBATT_MODIFICATION_FAILED,

    PM_ERR_FLAG__VBATT_INTERROGATION_FAILED,

    PM_ERR_FLAG__VBATT_SET_FILTER_FAILED,



    PM_ERR_FLAG__VBATT_LAST_ERROR,
    PM_ERR_FLAG__PMIC_NOT_SUPPORTED,


    PM_ERR_FLAG__INVALID_VIBRATOR_INDEXED ,


    PM_ERR_FLAG__INVALID_PWM_GENERATOR_INDEXED ,


    PM_ERR_FLAG__INVALID_CHG_INDEXED ,

    PM_ERR_FLAG__INVALID_CLK_INDEXED,

    PM_ERR_FLAG__INVALID_XO_INDEXED,

    PM_ERR_FLAG__INVALID_XOADC_INDEXED,

    PM_ERR_FLAG__INVALID_TCXO_INDEXED,

    PM_ERR_FLAG__INVALID_RTC_INDEXED,

    PM_ERR_FLAG__INVALID_SMBC_INDEXED,

    PM_ERR_FLAG__INVALID_BMS_INDEXED,

    PM_ERR_FLAG__API_NOT_IMPLEMENTED,

    PM_ERR_FLAG__INVALID_PAONCNTRL_INDEXED,


    PM_ERR_FLAG__INVALID_COINCELL_INDEXED ,


    PM_ERR_FLAG__INVALID_FLASH_INDEXED ,


    PM_ERR_FLAG__INVALID_OVP_INDEXED ,


    PM_ERR_FLAG__INVALID_KEYPAD_INDEXED ,


    PM_ERR_FLAG__INVALID_LVS_INDEXED ,


    PM_ERR_FLAG__INVALID_HSED_INDEXED ,


    PM_ERR_FLAG__INVALID_TALM_INDEXED ,


    PM_ERR_FLAG__INVALID_NCP_INDEXED ,


    PM_ERR_FLAG__INVALID_NFC_INDEXED ,


    PM_ERR_FLAG__INVALID_MVS_INDEXED,


    PM_ERR_FLAG__INVALID_HDMI_INDEXED,


    PM_ERR_FLAG__INVALID_VS_INDEXED,


    PM_ERR_FLAG__INVALID_UVLO_INDEXED,


    PM_ERR_FLAG__INVALID_AMUX_INDEXED,

    PM_ERR_FLAG__INVALID_KEYPAD_EVENT_COUNTER,


    PM_ERR_FLAG__INVALID_MPP_INDEXED,

    PM_ERR_FLAG__INVALID_BATTERY_CELL_NUMBER,

    PM_ERR_FLAG__INVALID_PWRON_INDEXED,

    PM_ERR_FLAG__INVALID_VBATT_INDEXED,

    PM_ERR_FLAG__INVALID_HSDKYPD_APP_INDEXED,

    PM_ERR_FLAG__INVALID_PWRKEY_APP_INDEXED,

    PM_ERR_FLAG__INVALID_EVENT_CALLBACK,

    PM_ERR_FLAG__SHADOW_REGISTER_INIT_FAILED ,


    PM_ERR_FLAG__PSDTE_ENV_FAILURE,

    PM_ERR_FLAG__PSDTE_PMIC_POWERUP_FAILED,

    PM_ERR_FLAG__PSDTE_PMIC_POWERDOWN_FAILED,

    PM_ERR_FLAG__FTS_CALCULATION_ERROR ,

    PM_ERR_FLAG__API_DEPRICATED_ERROR,

    PM_ERR_FLAG__RPC_PROCESSOR_NOT_RECOGNIZED_ERROR,


    PM_ERR_FLAG__VREG_VOTE_DEREGISTER_ERROR,

    PM_ERR_FLAG__VREG_VOTE_REGISTER_ERROR,


    PM_ERR_FLAG__INVALID_VS_STATUS,

    PM_ERR_FLAG__DAL_SERVICE_REGISTRATION_FAILED,

    PM_ERR_FLAG__DAL_SERVICE_FAILED,

    PM_ERR__MUTEX_CREATION_FAILED ,

    PM_ERR__MUTEX_RELEASE_FAILED ,

    PM_ERR__MUTEX_DELETION_FAILED ,

    PM_ERR__MUTEX_UNAVAILBLE ,

    PM_ERR_FLAG__COMM_TYPE_NOT_RECOGNIZED,

    PM_ERR_FLAG__IRQ_GPIO_SET_FAILED,

    PM_ERR_FLAG__PMAPP_EVENT_CLIENT_TABLE_FULL,

    PM_ERR_FLAG__PMAPP_EVENT_DEREGISTRATION_FAILED,

    PM_ERR_FLAG__PMAPP_EVENT_CLIENT_INDEX_FAILURE,

    PM_ERR_FLAG__INVALID_MISC_INDEXED,

    PM_ERR_FLAG__INVALID_MISC_TBD,

    PM_ERR_FLAG__INVALID_VREG_INDEXED,

    PM_ERR_FLAG__INVALID_POINTER,

    PM_ERR_FLAG__FUNCTION_NOT_SUPPORTED_AT_THIS_LEVEL,

    PM_ERR_FLAG__INVALID_LPG_INDEXED,

    PM_ERR_FLAG__INVALID_DISPBACKLIGHT_APP_INDEXED,
    PM_ERR_FLAG_CFG_INIT_FAILED,

    PM_ERR_FLAG__INVALID

} pm_err_flag_type;
# 35 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/com_dtypes.h" 1
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/stdint.h" 1
# 20 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/stdint.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/bits/alltypes.h" 1
# 90 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/bits/alltypes.h"
typedef unsigned long uintptr_t;
# 105 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/bits/alltypes.h"
typedef long intptr_t;
# 121 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/bits/alltypes.h"
typedef signed char int8_t;




typedef short int16_t;




typedef int int32_t;




typedef long int64_t;




typedef long intmax_t;




typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef unsigned int uint32_t;




typedef unsigned long uint64_t;
# 171 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/bits/alltypes.h"
typedef unsigned long uintmax_t;
# 21 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/stdint.h" 2

typedef int8_t int_fast8_t;
typedef int64_t int_fast64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

typedef uint8_t uint_fast8_t;
typedef uint64_t uint_fast64_t;

typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
# 95 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/stdint.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/bits/stdint.h" 1
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 96 "/pkg/qct/software/llvm/release/arm/3.5.2.4/tools/lib64/include/stdint.h" 2
# 35 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/com_dtypes.h" 2
# 88 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
typedef unsigned char boolean;







typedef uint32_t bool32;
# 116 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
typedef uint32_t uint32;




typedef uint16_t uint16;




typedef uint8_t uint8;




typedef int32_t int32;




typedef int16_t int16;




typedef int8_t int8;




typedef unsigned long uintnt;
# 155 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
typedef uint8_t byte;



typedef unsigned short word;
typedef unsigned int dword;

typedef unsigned char uint1;
typedef unsigned short uint2;
typedef unsigned int uint4;

typedef signed char int1;
typedef signed short int2;
typedef long int int4;

typedef signed int sint31;
typedef signed short sint15;
typedef signed char sint7;

typedef uint16 UWord16 ;
typedef uint32 UWord32 ;
typedef int32 Word32 ;
typedef int16 Word16 ;
typedef uint8 UWord8 ;
typedef int8 Word8 ;
typedef int32 Vect32 ;
# 196 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
      typedef long long int64;



      typedef unsigned long long uint64;
# 36 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_resources_and_types.h" 1
# 42 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_resources_and_types.h"
enum
{

  PM_LDO_1,
  PM_LDO_2,
  PM_LDO_3,
  PM_LDO_4,
  PM_LDO_5,
  PM_LDO_6,
  PM_LDO_7,
  PM_LDO_8,
  PM_LDO_9,
  PM_LDO_10,
  PM_LDO_11,
  PM_LDO_12,
  PM_LDO_13,
  PM_LDO_14,
  PM_LDO_15,
  PM_LDO_16,
  PM_LDO_17,
  PM_LDO_18,
  PM_LDO_19,
  PM_LDO_20,
  PM_LDO_21,
  PM_LDO_22,
  PM_LDO_23,
  PM_LDO_24,
  PM_LDO_25,
  PM_LDO_26,
  PM_LDO_27,
  PM_LDO_28,
  PM_LDO_29,
  PM_LDO_30,
  PM_LDO_31,
  PM_LDO_32,
  PM_LDO_33,

  PM_SMPS_1,
  PM_SMPS_2,
  PM_SMPS_3,
  PM_SMPS_4,
  PM_SMPS_5,
  PM_SMPS_6,
  PM_SMPS_7,
  PM_SMPS_8,
  PM_SMPS_9,
  PM_SMPS_10,

  PM_VS_LVS_1,
  PM_VS_LVS_2,
  PM_VS_LVS_3,
  PM_VS_LVS_4,
  PM_VS_LVS_5,
  PM_VS_LVS_6,
  PM_VS_LVS_7,
  PM_VS_LVS_8,
  PM_VS_LVS_9,
  PM_VS_LVS_10,
  PM_VS_LVS_11,
  PM_VS_LVS_12,
  PM_VS_MVS_1,
  PM_VS_OTG_1,
  PM_VS_HDMI_1,
  PM_VREG_INVALID
};




enum
{
  PM_CHG_1,
  PM_CHG_INVALID
};




enum
{
  PM_LEDH_1,
  PM_LEDH_2,
  PM_LEDH_3,
  PM_LEDH_INVALID
};




enum
{
  PM_LEDL_1,
  PM_LEDL_2,
  PM_LEDL_3,
  PM_LEDL_INVALID
};




enum
{
  PM_PWM_1,
  PM_PWM_2,
  PM_PWM_3,
  PM_PWM_INVALID
};




enum
{
  PM_HSED_1,
  PM_HSED_2,
  PM_HSED_3,
  PM_HSED_INVALID
};




enum
{
  PM_CHG_EXT_1,
  PM_CHG_EXT_INVALID
};




enum
{
  PM_SMBC_1,
  PM_SMBC_INVALID
};




enum
{
  PM_BMS_1,
  PM_BMS_INVALID
};




enum
{
  PM_BTM_1,
  PM_BTM_INVALID
};






enum
{
    PM_ARB_ADC_1,
    PM_ARB_ADC_2,
    PM_ARB_ADC_3,
    PM_ARB_ADC_INVALID
};




enum
{
    PM_LPG_1,
    PM_LPG_2,
    PM_LPG_3,
    PM_LPG_4,
    PM_LPG_5,
    PM_LPG_6,
    PM_LPG_7,
    PM_LPG_8,
    PM_LPG_INVALID
};




enum
{
    PM_INTERRUPT_1,
    PM_INTERRUPT_2,
    PM_INTERRUPT_3,
    PM_INTERRUPT_INVALID
};




enum
{
    PM_OVP_1,
    PM_OVP_2,
    PM_OVP_INVALID
};




enum
{
    PM_MEGA_XO_1,
    PM_MEGA_XO_2,
    PM_MEGA_XO_3,
    PM_MEGA_XO_4,
    PM_MEGA_XO_5,
    PM_MEGA_XO_6,
    PM_MEGA_XO_7,
    PM_MEGA_XO_8,
    PM_MEGA_XO_9,
    PM_MEGA_XO_INVALID,
};




enum
{
  PM_UICC_1,
  PM_UICC_2,
  PM_UICC_INVALID
};




enum
{
    PM_CLK_1,
    PM_CLK_2,
    PM_CLK_INVALID
};

typedef enum
{
   PM_OFF,
   PM_ON,
   PM_INVALID
}pm_on_off_type;




typedef enum
{
  PM_IRQ_TRIGGER_ACTIVE_LOW,
  PM_IRQ_TRIGGER_ACTIVE_HIGH,
  PM_IRQ_TRIGGER_RISING_EDGE,
  PM_IRQ_TRIGGER_FALLING_EDGE,
  PM_IRQ_TRIGGER_DUAL_EDGE,
  PM_IRQ_TRIGGER_INVALID
} pm_irq_trigger_type;




typedef enum
{
  PM_IRQ_STATUS_RT,
  PM_IRQ_STATUS_LATCHED,
  PM_IRQ_STATUS_PENDING,
  PM_IRQ_STATUS_ENABLE,
  PM_IRQ_STATUS_INVALID
} pm_irq_status_type;
# 37 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h" 2
# 46 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h"
typedef enum
{
  PM_PON_RESET_CFG_WARM_RESET,
  PM_PON_RESET_CFG_NORMAL_SHUTDOWN,

  PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN,

  PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,

  PM_PON_RESET_CFG_HARD_RESET,

  PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_D_VDD_COIN_CELL_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,

  PM_PON_RESET_CFG_WARM_RESET_AND_D_VDD_BATT_REMOVE_SHUTDOWN,
  PM_PON_RESET_CFG_WARM_RESET_AND_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,
  PM_PON_RESET_CFG_WARM_RESET_AND_SHUTDOWN,

  PM_PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET,
  PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_INVALID
}pm_pon_reset_cfg_type;




typedef enum
{
  PM_APP_PON_CFG_NO_CONFIG_NEEDED,
  PM_APP_PON_CFG_WARM_RESET,
  PM_APP_PON_CFG_HARD_RESET,
  PM_APP_PON_CFG_NORMAL_SHUTDOWN,
  PM_APP_PON_CFG_DVDD_HARD_RESET,
  PM_APP_PON_CFG_DVDD_SHUTDOWN,
  PM_APP_PON_CFG_MAX
}pm_app_pon_reset_cfg_type;


typedef enum
{
  PM_APP_PON_RESET_SOURCE_KPDPWR,
  PM_APP_PON_RESET_SOURCE_RESIN,
  PM_APP_PON_RESET_SOURCE_RESIN_AND_KPDPWR,
  PM_APP_PON_RESET_SOURCE_RESIN_OR_KPDPWR,
  PM_APP_PON_RESET_SOURCE_MAX
}pm_app_pon_reset_source_type;
# 120 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h"
pm_err_flag_type
pm_pon_ps_hold_cfg(uint32 pmic_device_index, pm_pon_reset_cfg_type ps_hold_cfg);
# 140 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pon.h"
pm_err_flag_type
pm_app_ps_hold_cfg(pm_app_pon_reset_cfg_type ps_hold_cfg);
# 25 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/framework/inc/pm_pon_cfg.h" 2
# 49 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/framework/inc/pm_pon_cfg.h"
pm_err_flag_type
pm_get_pshold_cfg
(
  uint32 pmic_index,
  pm_app_pon_reset_cfg_type reset_cfg,
  pm_app_pon_reset_cfg_type* pshold_cfg
 );
# 28 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/config/msm8996_pm8994/src/pm_oem_config.c" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/pmic_devices/common/src/device_info.h" 1
# 28 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/pmic_devices/common/src/device_info.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h" 1
# 40 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h" 1
# 152 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/target.h" 1
# 77 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/target.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/customer.h" 1
# 80 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/customer.h"
# 1 "./custiadaanaaa.h" 1
# 10 "./custiadaanaaa.h"
# 1 "./targiadaanaaa.h" 1
# 11 "./custiadaanaaa.h" 2
# 144 "./custiadaanaaa.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custremoteapis.h" 1
# 145 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custtarget.h" 1
# 146 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsdcc.h" 1
# 147 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsurf.h" 1
# 148 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custdiag.h" 1
# 149 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custefs.h" 1
# 150 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custpmic.h" 1
# 151 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsio_8660.h" 1
# 152 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsec.h" 1
# 121 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsec.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsfs.h" 1
# 122 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsec.h" 2
# 153 "./custiadaanaaa.h" 2
# 81 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/customer.h" 2
# 78 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/target.h" 2
# 153 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/armasm.h" 1
# 154 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h" 2
# 255 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h"
        typedef struct __attribute__((packed))
        { uint16 x; }
        unaligned_uint16;
        typedef struct __attribute__((packed))
        { uint32 x; }
        unaligned_uint32;
        typedef struct __attribute__((packed))
        { uint64 x; }
        unaligned_uint64;
        typedef struct __attribute__((packed))
        { int16 x; }
        unaligned_int16;
        typedef struct __attribute__((packed))
        { int32 x; }
        unaligned_int32;
        typedef struct __attribute__((packed))
        { int64 x; }
        unaligned_int64;
# 789 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h"
  extern dword rex_int_lock(void);
  extern dword rex_int_free(void);
# 1031 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h"
    extern dword rex_fiq_lock(void);
    extern void rex_fiq_free(void);
# 1078 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/services/comdef.h"
   extern void rex_task_lock( void);
   extern void rex_task_free( void);
# 41 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h" 2

# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 1
# 46 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_cmd.h" 1
# 31 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_cmd.h"
typedef enum
{



   PM_OFF_CMD,



   PM_ON_CMD,



   PM_INVALID_CMD
}pm_switch_cmd_type;
# 47 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2

# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h" 1
# 44 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h" 1
# 45 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h" 2
# 58 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h"
typedef enum
{
   PMIC_IS_UNKNOWN = 0,
   PMIC_IS_PM8941 = 1,
   PMIC_IS_PM8841 = 2,
   PMIC_IS_PM8019 = 3,
   PMIC_IS_PM8026 = 4,
   PMIC_IS_PM8110 = 5,
   PMIC_IS_PMA8084 = 6,
   PMIC_IS_PMI8962 = 7,
   PMIC_IS_PMD9635 = 8,
   PMIC_IS_PM8994 = 9,
   PMIC_IS_PMI8994 = 10,
   PMIC_IS_PM8916 = 11,
   PMIC_IS_PM8004 = 12,
   PMIC_IS_PM8909 = 13,
   PMIC_IS_PM2433 = 14,
   PMIC_IS_PM8950 = 16,
   PMIC_IS_PMI8950 = 17,
   PMIC_IS_PMI8937 = 17,
   PMIC_IS_PMK8001 = 18,
   PMIC_IS_PMI8996 = 19,
   PMIC_IS_PM8998 = 20,
   PMIC_IS_PM8953 = 22,
   PMIC_IS_PM8005 = 24,
   PMIC_IS_PM8937 = 25,
   PMIC_IS_INVALID = 0x7FFFFFFF,
} pm_model_type;
# 97 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h"
typedef struct
{
  pm_model_type ePmicModel;
  uint32 nPmicAllLayerRevision;
  uint32 nPmicMetalRevision;
} pm_device_info_type;
# 126 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h"
pm_model_type pm_get_pmic_model(uint8 pmic_device_index);
# 144 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h"
uint8 pm_get_pmic_revision(uint8 pmic_device_index);
# 174 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_version.h"
pm_err_flag_type pm_get_pmic_info(uint8 pmic_index, pm_device_info_type* pmic_device_info_ptr);
# 49 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h" 1
# 92 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
typedef int pm_mpp_which_type;


enum
{
  PM_MPP_1,
  PM_MPP_2,
  PM_MPP_3,
  PM_MPP_4,
  PM_MPP_5,
  PM_MPP_6,
  PM_MPP_7,
  PM_MPP_8,
  PM_MPP_9,
  PM_MPP_10,
  PM_MPP_11,
  PM_MPP_12,
  PM_MPP_13,
  PM_MPP_14,
  PM_MPP_15,
  PM_MPP_16,
  PM_MPP_INVALID,
};






typedef enum
{
  PM_MPP__DLOGIC__LVL_VIO_0 = 0,
  PM_MPP__DLOGIC__LVL_VIO_1,
  PM_MPP__DLOGIC__LVL_VIO_2,
  PM_MPP__DLOGIC__LVL_VIO_3,
  PM_MPP__DLOGIC__LVL_VIO_4,
  PM_MPP__DLOGIC__LVL_VIO_5,
  PM_MPP__DLOGIC__LVL_VIO_6,
  PM_MPP__DLOGIC__LVL_VIO_7,
  PM_MPP__DLOGIC__LVL_INVALID = 8,

} pm_mpp_dlogic_lvl_type;


typedef enum
{
  PM_MPP__DLOGIC_IN__DBUS1,
  PM_MPP__DLOGIC_IN__DBUS2,
  PM_MPP__DLOGIC_IN__DBUS3,
  PM_MPP__DLOGIC_IN__DBUS4,
  PM_MPP__DLOGIC_IN__DBUS_INVALID
}pm_mpp_dlogic_in_dbus_type;



typedef enum
{
  PM_MPP__DLOGIC_OUT__CTRL_LOW,
  PM_MPP__DLOGIC_OUT__CTRL_HIGH,
  PM_MPP__DLOGIC_OUT__CTRL_MPP,

  PM_MPP__DLOGIC_OUT__CTRL_NOT_MPP,

  PM_MPP__DLOGIC_OUT__CTRL_INVALID
}pm_mpp_dlogic_out_ctrl_type;


typedef enum
{
  PM_MPP__DLOGIC_INOUT__PUP_1K,
  PM_MPP__DLOGIC_INOUT__PUP_10K,
  PM_MPP__DLOGIC_INOUT__PUP_30K,
  PM_MPP__DLOGIC_INOUT__PUP_OPEN,
  PM_MPP__DLOGIC_INOUT__PUP_INVALID
}pm_mpp_dlogic_inout_pup_type;


typedef enum
{
  PM_MPP__DLOGIC_OUT__DBUS1,
  PM_MPP__DLOGIC_OUT__DBUS2,
  PM_MPP__DLOGIC_OUT__DBUS3,
  PM_MPP__DLOGIC_OUT__DBUS4,
  PM_MPP__DLOGIC_OUT__DBUS_INVALID
}pm_mpp_dlogic_out_dbus_type;





typedef enum
{
  PM_MPP__AIN__CH_AMUX5,
  PM_MPP__AIN__CH_AMUX6,
  PM_MPP__AIN__CH_AMUX7,
  PM_MPP__AIN__CH_AMUX8,
  PM_MPP__AIN__CH_ABUS1,
  PM_MPP__AIN__CH_ABUS2,
  PM_MPP__AIN__CH_ABUS3,
  PM_MPP__AIN__CH_ABUS4,
  PM_MPP__AIN__CH_INVALID
}pm_mpp_ain_ch_type;





typedef enum
{
  PM_MPP__AOUT__LEVEL_VREF_1p25_Volts,
  PM_MPP__AOUT__LEVEL_VREF_0p625_Volts,
  PM_MPP__AOUT__LEVEL_VREF_0p3125_Volts,
  PM_MPP__AOUT__LEVEL_INVALID
}pm_mpp_aout_level_type;

typedef enum
{
  PM_MPP__AOUT__SWITCH_OFF,
  PM_MPP__AOUT__SWITCH_ON,
  PM_MPP__AOUT__SWITCH_ON_IF_MPP_HIGH,
  PM_MPP__AOUT__SWITCH_ON_IF_MPP_LOW,
  PM_MPP__AOUT__SWITCH_INVALID
}pm_mpp_aout_switch_type;





typedef enum
{
  PM_MPP__I_SINK__LEVEL_5mA,
  PM_MPP__I_SINK__LEVEL_10mA,
  PM_MPP__I_SINK__LEVEL_15mA,
  PM_MPP__I_SINK__LEVEL_20mA,
  PM_MPP__I_SINK__LEVEL_25mA,
  PM_MPP__I_SINK__LEVEL_30mA,
  PM_MPP__I_SINK__LEVEL_35mA,
  PM_MPP__I_SINK__LEVEL_40mA,
  PM_MPP__I_SINK__LEVEL_INVALID
}pm_mpp_i_sink_level_type;

typedef enum
{
  PM_MPP__I_SINK__SWITCH_DIS,
  PM_MPP__I_SINK__SWITCH_ENA,
  PM_MPP__I_SINK__SWITCH_ENA_IF_MPP_HIGH,
  PM_MPP__I_SINK__SWITCH_ENA_IF_MPP_LOW,
  PM_MPP__I_SINK__SWITCH_INVALID
}pm_mpp_i_sink_switch_type;



typedef enum
{
  PM_MPP__CH_ATEST1,
  PM_MPP__CH_ATEST2,
  PM_MPP__CH_ATEST3,
  PM_MPP__CH_ATEST4,
  PM_MPP__CH_ATEST_INVALID
}pm_mpp_ch_atest_type;




typedef struct
{
    pm_mpp_dlogic_lvl_type mpp_dlogic_lvl;
    pm_mpp_dlogic_in_dbus_type mpp_dlogic_in_dbus;
} pm_mpp_digital_input_status_type;




typedef struct
{
    pm_mpp_dlogic_lvl_type mpp_dlogic_lvl;
    pm_mpp_dlogic_out_ctrl_type mpp_dlogic_out_ctrl;
} pm_mpp_digital_output_status_type;




typedef struct
{
    pm_mpp_dlogic_lvl_type mpp_dlogic_lvl;
    pm_mpp_dlogic_inout_pup_type mpp_dlogic_inout_pup;
} pm_mpp_bidirectional_status_type;




typedef struct
{
    pm_mpp_ain_ch_type mpp_ain_ch;
} pm_mpp_analog_input_status_type;




typedef struct
{
    pm_mpp_aout_level_type mpp_aout_level;
    pm_mpp_aout_switch_type mpp_aout_switch;
} pm_mpp_analog_output_status_type;




typedef struct
{
    pm_mpp_i_sink_level_type mpp_i_sink_level;
    pm_mpp_i_sink_switch_type mpp_i_sink_switch;
} pm_mpp_current_sink_status_type;




typedef struct
{
    pm_mpp_dlogic_lvl_type mpp_dlogic_lvl;
    pm_mpp_dlogic_out_dbus_type mpp_dlogic_out_dbus;
} pm_mpp_dtest_output_status_type;




typedef enum
{
    PM_MPP_CFG_DIGITAL_IN,
    PM_MPP_CFG_DIGITAL_OUT,
    PM_MPP_CFG_BIDIRECTIONAL,
    PM_MPP_CFG_ANALOG_IN,
    PM_MPP_CFG_ANALOG_OUT,
    PM_MPP_CFG_ISINK,
    PM_MPP_CFG_DTEST_OUT
} pm_mpp_config_type;




typedef struct s_pm_mpp_status_type
{



    pm_mpp_config_type mpp_config;





    union
    {
        pm_mpp_digital_input_status_type mpp_digital_input_status;
        pm_mpp_digital_output_status_type mpp_digital_output_status;
        pm_mpp_bidirectional_status_type mpp_bidirectional_status;
        pm_mpp_analog_input_status_type mpp_analog_input_status;
        pm_mpp_analog_output_status_type mpp_analog_output_status;
        pm_mpp_current_sink_status_type mpp_current_sink_status;
        pm_mpp_dtest_output_status_type mpp_dtest_output_status;
    } mpp_config_settings;
} pm_mpp_status_type;
# 364 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
pm_err_flag_type pm_dev_mpp_status_get(unsigned pmic_device_index, pm_mpp_which_type mpp, pm_mpp_status_type *mpp_status);

pm_err_flag_type pm_mpp_status_get(pm_mpp_which_type mpp, pm_mpp_status_type *mpp_status);
# 472 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
extern pm_err_flag_type pm_dev_mpp_config_digital_input(
                                          unsigned pmic_device_index,
                                          pm_mpp_which_type mpp,
                                          pm_mpp_dlogic_lvl_type level,
                                          pm_mpp_dlogic_in_dbus_type dbus);

extern pm_err_flag_type pm_mpp_config_digital_input(
    pm_mpp_which_type mpp,
    pm_mpp_dlogic_lvl_type level,
    pm_mpp_dlogic_in_dbus_type dbus);
# 584 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
extern pm_err_flag_type pm_dev_mpp_config_digital_output(
                                    unsigned pmic_device_index,
                                    pm_mpp_which_type mpp,
                                    pm_mpp_dlogic_lvl_type level,
                                    pm_mpp_dlogic_out_ctrl_type output_ctrl);

extern pm_err_flag_type pm_mpp_config_digital_output(
    pm_mpp_which_type mpp,
    pm_mpp_dlogic_lvl_type level,
    pm_mpp_dlogic_out_ctrl_type output_ctrl);
# 698 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
extern pm_err_flag_type pm_dev_mpp_config_digital_inout(
                                    unsigned pmic_device_index,
                                    pm_mpp_which_type mpp,
                                    pm_mpp_dlogic_lvl_type level,
                                    pm_mpp_dlogic_inout_pup_type pull_up);

extern pm_err_flag_type pm_mpp_config_digital_inout(
    pm_mpp_which_type mpp,
    pm_mpp_dlogic_lvl_type level,
    pm_mpp_dlogic_inout_pup_type pull_up);
# 790 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
pm_err_flag_type pm_dev_mpp_config_dtest_output(
                                             unsigned pmic_device_index,
                                             pm_mpp_which_type mpp,
                                             pm_mpp_dlogic_lvl_type level,
                                             pm_mpp_dlogic_out_dbus_type dbus);

pm_err_flag_type pm_mpp_config_dtest_output(
    pm_mpp_which_type mpp,
    pm_mpp_dlogic_lvl_type level,
    pm_mpp_dlogic_out_dbus_type dbus);
# 877 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
extern pm_err_flag_type pm_dev_mpp_config_analog_input(
                                    unsigned pmic_device_index,
                                    pm_mpp_which_type mpp,
                                    pm_mpp_ain_ch_type ch_select);

extern pm_err_flag_type pm_mpp_config_analog_input(
    pm_mpp_which_type mpp,
    pm_mpp_ain_ch_type ch_select);
# 967 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
extern pm_err_flag_type pm_dev_mpp_config_analog_output(
                                    unsigned pmic_device_index,
                                    pm_mpp_which_type mpp,
                                    pm_mpp_aout_level_type level,
                                    pm_mpp_aout_switch_type OnOff);

extern pm_err_flag_type pm_mpp_config_analog_output(
    pm_mpp_which_type mpp,
    pm_mpp_aout_level_type level,
    pm_mpp_aout_switch_type OnOff);
# 1067 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
extern pm_err_flag_type pm_dev_mpp_config_i_sink(
                                    unsigned pmic_device_index,
                                    pm_mpp_which_type mpp,
                                    pm_mpp_i_sink_level_type level,
                                    pm_mpp_i_sink_switch_type OnOff);

extern pm_err_flag_type pm_mpp_config_i_sink(
    pm_mpp_which_type mpp,
    pm_mpp_i_sink_level_type level,
    pm_mpp_i_sink_switch_type OnOff);
# 1142 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
extern pm_err_flag_type pm_dev_mpp_config_atest(
                                    unsigned pmic_device_index,
                                    pm_mpp_which_type mpp,
                                    pm_mpp_ch_atest_type atest_select);

extern pm_err_flag_type pm_mpp_config_atest(
    pm_mpp_which_type mpp,
    pm_mpp_ch_atest_type atest_select);
# 1215 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
pm_err_flag_type pm_dev_mpp_set_list_mpp_with_shunt_cap(unsigned pmic_device_index, pm_mpp_which_type mpp);

pm_err_flag_type pm_mpp_set_list_mpp_with_shunt_cap(pm_mpp_which_type mpp);
# 1250 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_mpps.h"
pm_err_flag_type pm_dev_get_mpp_with_shunt_cap_list_status_for_device(unsigned pmic_device_index, pm_mpp_which_type mpp, uint32* shuntList);

pm_err_flag_type pm_get_mpp_with_shunt_cap_list_status_for_device(pm_mpp_which_type mpp, uint32* shuntList);
# 50 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h" 1
# 51 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
typedef struct
{
   uint32 sec;
} pm_hal_rtc_time_type;


typedef enum
{
   PM_HAL_RTC_ALARM_1,
   PM_HAL_RTC_ALARM_INVALID
} pm_hal_rtc_alarm;


typedef struct
{
   boolean alarm_1_triggered;
} pm_hal_rtc_alarm_status_type;
# 110 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_start(
   unsigned pmic_device_index,
   const pm_hal_rtc_time_type *start_time_ptr
);

extern pm_err_flag_type pm_hal_rtc_start(const pm_hal_rtc_time_type *start_time_ptr);
# 144 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_stop(unsigned pmic_device_index);

extern pm_err_flag_type pm_hal_rtc_stop(void);
# 186 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_get_time(
    unsigned pmic_device_index,
    pm_hal_rtc_time_type *time_ptr
);

extern pm_err_flag_type pm_hal_rtc_get_time(pm_hal_rtc_time_type *time_ptr);
# 238 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_enable_alarm(
    unsigned pmic_device_index,
    pm_hal_rtc_alarm what_alarm,
    const pm_hal_rtc_time_type *trigger_time_ptr
);

extern pm_err_flag_type pm_hal_rtc_enable_alarm(
    pm_hal_rtc_alarm what_alarm,
    const pm_hal_rtc_time_type *trigger_time_ptr
    );
# 285 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_disable_alarm(
    unsigned pmic_device_index,
    pm_hal_rtc_alarm what_alarm
);

extern pm_err_flag_type pm_hal_rtc_disable_alarm(pm_hal_rtc_alarm what_alarm);
# 334 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_get_alarm_time(
   unsigned pmic_device_index,
   pm_hal_rtc_alarm what_alarm,
   pm_hal_rtc_time_type *alarm_time_ptr
);

extern pm_err_flag_type pm_hal_rtc_get_alarm_time(
    pm_hal_rtc_alarm what_alarm,
    pm_hal_rtc_time_type *alarm_time_ptr
    );
# 386 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_get_alarm_status(unsigned pmic_device_index, uint8 *status_ptr);

extern pm_err_flag_type pm_hal_rtc_get_alarm_status(uint8 *status_ptr);
# 428 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_set_time_adjust(
    unsigned pmic_device_index,
    uint8 time_adjust
);

extern pm_err_flag_type pm_hal_rtc_set_time_adjust(uint8 time_adjust);
# 474 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_get_time_adjust(
    unsigned pmic_device_index,
    uint8 *time_adjust_ptr
);

extern pm_err_flag_type pm_hal_rtc_get_time_adjust(uint8 *time_adjust_ptr);
# 488 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hal_rtc_prescaler_reset(unsigned pmic_device_index);

extern pm_err_flag_type pm_hal_rtc_prescaler_reset(void);
# 501 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_rtc.h"
extern pm_err_flag_type pm_dev_hard_reset(unsigned pmic_device_index);
# 51 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h" 1
# 50 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_external_resources.h" 1
# 51 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h" 2
# 60 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
typedef int pm_vreg_id_type;




typedef unsigned pm_vreg_level_type_microvolts ;

typedef uint64 pm_vreg_mask_type;
typedef uint64 pm_vreg_masked_type;




typedef enum
{
    PM_PWR_SW_MODE_PFM = 0,
    PM_PWR_SW_MODE_BYPASS = 1,
    PM_PWR_SW_MODE_AUTO = 2,
    PM_PWR_SW_MODE_NPM = 4,
    PM_PWR_SW_MODE_INVALID
}pm_pwr_sw_mode_type;







typedef struct
{
   uint8 sawtooth_set;
   uint8 gm_set;
   uint8 resistor_set;
}pm_vreg_buck_cfg_cp_type;

typedef enum
{
  PM_INDUCTOR_ILIM__300MA,

  PM_INDUCTOR_ILIM__700MA,

  PM_INDUCTOR_ILIM__1100MA,

  PM_INDUCTOR_ILIM__1500MA,

  PM_INDUCTOR_ILIM__1900MA,

  PM_INDUCTOR_ILIM__2300MA,

  PM_INDUCTOR_ILIM__2700MA,

  PM_INDUCTOR_ILIM__3100MA,

  PM_INDUCTOR_ILIM__INVALID
} pm_pwr_buck_inductor_ilim_type ;



typedef enum
{
   PM_CLK_TCXO,
   PM_CLK_RC,
   PM_CLK_SOURCE_INVALID
}pm_pwr_buck_clk_source_type;






typedef enum
{
    PM_CLK_19p2_MHz = 0,
    PM_CLK_9p6_MHz = 1,
    PM_CLK_6p4_MHz = 2,
    PM_CLK_4p8_MHz = 3,
    PM_CLK_3p84_MHz = 4,
    PM_CLK_3p2_MHz = 5,
    PM_CLK_2p74_MHz = 6,
    PM_CLK_2p4_MHz = 7,
    PM_CLK_2p13_MHz = 8,
    PM_CLK_1p92_MHz = 9,
    PM_CLK_1p75_MHz = 10,
    PM_CLK_1p6_MHz = 11,
    PM_CLK_1p48_MHz = 12,
    PM_CLK_1p37_MHz = 13,
    PM_CLK_1p28_MHz = 14,
    PM_CLK_1p2_MHz = 15,
    PM_CLK_1p13_MHz = 16,
    PM_CLK_1p07_MHz = 17,
    PM_CLK_1p01_MHz = 18,
    PM_CLK_960_KHz = 19,
    PM_CLK_914_KHz = 20,
    PM_CLK_873_KHz = 21,
    PM_CLK_835_KHz = 22,
    PM_CLK_800_KHz = 23,
    PM_CLK_768_KHz = 24,
    PM_CLK_738_KHz = 25,
    PM_CLK_711_KHz = 26,
    PM_CLK_686_KHz = 27,
    PM_CLK_662_KHz = 28,
    PM_CLK_640_KHz = 29,
    PM_CLK_619_KHz = 30,
    PM_CLK_600_KHz = 31,
    PM_SWITCHING_FREQ_INVALID,
 PM_SWITCHING_FREQ_FREQ_NONE
}pm_pwr_buck_switching_freq_type;




typedef float pm_vreg_smps_stepper_delay_type;



typedef float pm_vreg_smps_step_size_type;
# 185 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_vreg_set_level
(
 pm_vreg_id_type vreg,
 pm_vreg_level_type_microvolts voltage
 );
pm_err_flag_type pm_dev_pwr_volt_level
(
    unsigned pmic_device_index,
    unsigned resourceIndex,
    pm_vreg_level_type_microvolts voltLevel
);



pm_err_flag_type pm_vreg_get_level
(
 pm_vreg_id_type vreg,
 pm_vreg_level_type_microvolts *vreg_level
 );
pm_err_flag_type pm_dev_pwr_volt_level_status
(
    unsigned pmic_device_index,
    unsigned resourceIndex,
    pm_vreg_level_type_microvolts *voltLevel
);
# 220 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_pwr_buck_clk_source
(
    unsigned pmic_device_index,
 uint8 externalResourceIndex,
 pm_pwr_buck_clk_source_type clkSource
);

pm_err_flag_type pm_pwr_buck_clk_source
(
    uint8 externalResourceIndex,
    pm_pwr_buck_clk_source_type clkSource
);
# 258 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_pwr_buck_switching_freq
(
    unsigned pmic_device_index,
 uint8 externalResourceIndex,
 pm_pwr_buck_switching_freq_type switchingFreq
    );

pm_err_flag_type pm_pwr_buck_switching_freq
(
    uint8 externalResourceIndex,
    pm_pwr_buck_switching_freq_type switchingFreq
 );
# 344 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_vreg_buck_config_comp(
                            unsigned pmic_device_index,
                            pm_vreg_id_type vreg_id,
                            const pm_vreg_buck_cfg_cp_type *cfg);

pm_err_flag_type pm_vreg_buck_config_comp(pm_vreg_id_type vreg_id,
                                          const pm_vreg_buck_cfg_cp_type *cfg);
# 360 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_pwr_pull_down
(
    unsigned pmic_device_index,
 uint8 externalResourceIndex,
 pm_switch_cmd_type enableDisableCmd
    );

pm_err_flag_type pm_pwr_pull_down
(
 uint8 externalResourceIndex,
 pm_switch_cmd_type enableDisableCmd
 );
# 392 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_vreg_mask_type pm_dev_vreg_status_get(unsigned pmic_device_index);

pm_vreg_mask_type pm_vreg_status_get(void);
# 416 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_vreg_smps_pulse_skipping_enable
(
    unsigned pmic_device_index,
    pm_vreg_id_type vreg_id,
    boolean enable
    );

pm_err_flag_type pm_vreg_smps_pulse_skipping_enable
(
    pm_vreg_id_type vreg_id,
    boolean enable
);
# 441 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_pwr_mode_status(unsigned pmic_device_index, uint8 resourceIndex, pm_pwr_sw_mode_type* mode);

pm_err_flag_type pm_vreg_mode_status
(
    pm_vreg_id_type vreg ,
    pm_pwr_sw_mode_type* mode_status
);
# 459 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_vreg_smps_inductor_ilim
(
    unsigned pmic_device_index,
    pm_pwr_buck_inductor_ilim_type ilim_level,
    pm_vreg_id_type externalResourceIndex
);

pm_err_flag_type pm_vreg_smps_inductor_ilim
(
    pm_pwr_buck_inductor_ilim_type ilim_level,
    pm_vreg_id_type externalResourceIndex
);
# 482 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vreg.h"
pm_err_flag_type pm_dev_vreg_smps_inductor_ilim_status
(
  unsigned pmic_device_index,
  pm_pwr_buck_inductor_ilim_type* ilim_level,
  pm_vreg_id_type externalResourceIndex
  ) ;

pm_err_flag_type pm_vreg_smps_inductor_ilim_status
(
 pm_pwr_buck_inductor_ilim_type* ilim_level,
 pm_vreg_id_type externalResourceIndex
 );
# 52 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h" 1
# 25 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_external_resources.h" 1
# 26 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h" 2








typedef enum
{

  PM_VS_NORMAL_MODE,

  PM_VS_LPM_MODE,

  PM_VS_LPM_MODE_VIA_SLEEPB,

  PM_VS_AUTO_SLEEP_MODE,

  PM_VS_SWITCH_MODE_ID__INVALID,

}pm_vs_switch_mode_type;

typedef enum
{

  PM_VS_SSPGM_4uA_CURRENT,

  PM_VS_SSPGM_12uA_CURRENT,

  PM_VS_SSPGM_20uA_CURRENT,

  PM_VS_SSPGM_28uA_CURRENT,

  PM_VS_SSPGM_CURRENT_ID__INVALID,
}
pm_vs_sspgm_current_type;



typedef enum
{



  PM_VS_PIN_CTRL_ID__SLEEP_B,



  PM_VS_PIN_CTRL_ID__TCXO_EN0,



  PM_VS_PIN_CTRL_ID__TCXO_EN1,



  PM_VS_PIN_CTRL_ID__TCXO_EN2,



  PM_VS_PIN_CTRL_ID__TCXO_EN3,



  PM_VS_PIN_CTRL_ID__INVALID,
}pm_vs_pin_ctrl_id_type;




typedef enum
{

  PM_VS_SLEEP_B_PIN_FOLLOW_SLEEP_B,

  PM_VS_SLEEP_B_PIN_IGNORE,
} pm_vs_sleep_b_pin_type;




typedef enum
{

  PM_VS_FORCE_SLEEP_PIN_CONTROLLED,

  PM_VS_FORCE_SLEEP_ENTER_SLEEP_MODE,
} pm_vs_force_sleep_type;
# 130 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_switch_mode_switch(int externalResourceIndex,
                                          pm_vs_switch_mode_type mode);
# 146 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_set_sspgm(int externalResourceIndex,
                                 pm_vs_sspgm_current_type current);
# 164 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_get_over_current_indicator(int externalResourceIndex,
                                                   boolean *status);
# 181 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_get_output_voltage_status(int externalResourceIndex,
                                                 boolean *status);
# 196 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_soft_start_override(int externalResourceIndex,
                                           boolean ss_override );
# 213 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_over_current_protection_override(int externalResourceIndex,
                                                        boolean over_current_protection);
# 232 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_force_sleep_mode(int externalResourceIndex,
                                        pm_vs_force_sleep_type mode);
# 250 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_vs.h"
pm_err_flag_type pm_vs_sleep_b_pin_control(int externalResourceIndex,
                                           pm_vs_sleep_b_pin_type control);
# 53 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_ncp.h" 1
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_ncp.h"
typedef enum
{
    PM_NCP_FREQ_9_6MHZ,
    PM_NCP_FREQ_4_8MHZ,
    PM_NCP_FREQ_3_2MHZ,
    PM_NCP_FREQ_2_4MHZ,
    PM_NCP_FREQ_1_92MHZ,
    PM_NCP_FREQ_1_6MHZ,
    PM_NCP_FREQ_1_37MHZ,
    PM_NCP_FREQ_1_2MHZ,
    PM_NCP_FREQ_OUT_OF_RANGE
}pm_ncp_switching_freq_type;
# 100 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_ncp.h"
pm_err_flag_type pm_vreg_ncp_sample_comp_mode_enable(
                                             pm_switch_cmd_type OnOff,
                                             pm_ncp_switching_freq_type freq);
# 114 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_ncp.h"
pm_err_flag_type pm_ncp_control(pm_switch_cmd_type on_off);
# 54 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h" 1
# 50 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
typedef int pm_gpio_which_type;




enum
{
    PM_GPIO_1,
    PM_GPIO_2,
    PM_GPIO_3,
    PM_GPIO_4,
    PM_GPIO_5,
    PM_GPIO_6,
    PM_GPIO_7,
    PM_GPIO_8,
    PM_GPIO_9,
    PM_GPIO_10,
    PM_GPIO_11,
    PM_GPIO_12,
    PM_GPIO_13,
    PM_GPIO_14,
    PM_GPIO_15,
    PM_GPIO_16,
    PM_GPIO_17,
    PM_GPIO_18,
    PM_GPIO_19,
    PM_GPIO_20,
    PM_GPIO_21,
    PM_GPIO_22,
    PM_GPIO_23,
    PM_GPIO_24,
    PM_GPIO_25,
    PM_GPIO_26,
    PM_GPIO_27,
    PM_GPIO_28,
    PM_GPIO_29,
    PM_GPIO_30,
    PM_GPIO_31,
    PM_GPIO_32,
    PM_GPIO_33,
    PM_GPIO_34,
    PM_GPIO_35,
    PM_GPIO_36,
    PM_GPIO_37,
    PM_GPIO_38,
    PM_GPIO_39,
    PM_GPIO_40,
    PM_GPIO_41,
    PM_GPIO_42,
    PM_GPIO_43,
    PM_GPIO_44
};




typedef enum
{
    PM_GPIO_VIN0,
    PM_GPIO_VIN1,
    PM_GPIO_VIN2,
    PM_GPIO_VIN3,
    PM_GPIO_VIN4,
    PM_GPIO_VIN5,
    PM_GPIO_VIN6,
    PM_GPIO_VIN7,
    PM_GPIO_VOLTAGE_SOURCE_TYPE__INVALID
}pm_gpio_voltage_source_type;
# 133 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
typedef enum
{
    PM_GPIO_OUT_BUFFER_CONFIG_CMOS,
    PM_GPIO_OUT_BUFFER_CONFIG_OPEN_DRAIN_NMOS,
    PM_GPIO_OUT_BUFFER_CONFIG_OPEN_DRAIN_PMOS,
    PM_GPIO_OUT_BUFFER_CONFIG_INVALID
}pm_gpio_out_buffer_config_type;




typedef enum
{
    PM_GPIO_OUT_BUFFER_RESERVED,
    PM_GPIO_OUT_BUFFER_LOW,
    PM_GPIO_OUT_BUFFER_MEDIUM,
    PM_GPIO_OUT_BUFFER_HIGH,
    PM_GPIO_OUT_BUFFER_DRIVE_STRENGTH__INVALID
}pm_gpio_out_buffer_drive_strength_type;





typedef enum
{
    PM_GPIO_I_SOURCE_PULL_UP_30uA,
    PM_GPIO_I_SOURCE_PULL_UP_1_5uA,
    PM_GPIO_I_SOURCE_PULL_UP_31_5uA,
    PM_GPIO_I_SOURCE_PULL_UP_1_5uA_PLUS_30uA_BOOST,
    PM_GPIO_I_SOURCE_PULL_DOWN_10uA,
    PM_GPIO_I_SOURCE_PULL_NO_PULL,
    PM_GPIO_CURRENT_SOURCE_PULLS_TYPE__INVALID
}pm_gpio_current_source_pulls_type;




typedef enum
{
    PM_GPIO_SOURCE_GND,
    PM_GPIO_SOURCE_PAIRED_GPIO,
    PM_GPIO_SOURCE_SPECIAL_FUNCTION1,
    PM_GPIO_SOURCE_SPECIAL_FUNCTION2,
    PM_GPIO_SOURCE_DTEST1,
    PM_GPIO_SOURCE_DTEST2,
    PM_GPIO_SOURCE_DTEST3,
    PM_GPIO_SOURCE_DTEST4,
    PM_GPIO_SOURCE_CONFIG_TYPE__INVALID
}pm_gpio_source_config_type;




typedef enum
{
    PM_GPIO_DTEST_DISABLE,
    PM_GPIO_DTEST_ENABLE,
    PM_GPIO_DTEST_BUFFER_ONOFF_TYPE__INVALID
}pm_gpio_dtest_buffer_OnOff_type;




typedef enum
{

    PM_GPIO_EXT_PIN_DISABLE,
    PM_GPIO_EXT_PIN_ENABLE,
    PM_GPIO_EXT_PIN_CONFIG_TYPE__INVALID
}pm_gpio_ext_pin_config_type;




typedef enum
{
    PM_UART_MUX_NO,
    PM_UART_MUX_1,
    PM_UART_MUX_2,
    PM_UART_MUX_3,
    PM_UART_MUX_INVALID
}pm_gpio_uart_path_type;
# 245 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
typedef struct
{

    pm_gpio_voltage_source_type gpio_voltage_source;

    pm_gpio_out_buffer_config_type gpio_out_buffer_config;
    pm_gpio_out_buffer_drive_strength_type gpio_out_buffer_drive_strength;
    pm_gpio_current_source_pulls_type gpio_current_source_pulls;
    pm_gpio_source_config_type gpio_source_config;
    pm_gpio_dtest_buffer_OnOff_type gpio_dtest_buffer_OnOff;
    pm_gpio_ext_pin_config_type gpio_ext_pin_config;
} pm_gpio_status_type;





typedef struct
{
    pm_gpio_which_type gpio;
    boolean config_gpio;
    pm_gpio_voltage_source_type gpio_voltage_source;


    pm_gpio_out_buffer_config_type gpio_out_buffer_config;
    boolean invert_ext_pin;
    pm_gpio_current_source_pulls_type gpio_current_source_pulls;
    pm_gpio_out_buffer_drive_strength_type gpio_out_buffer_drive_strength;
    pm_gpio_dtest_buffer_OnOff_type gpio_dtest_buffer_OnOff;
    pm_gpio_ext_pin_config_type gpio_ext_pin_config;
    pm_gpio_source_config_type gpio_source_config;
    boolean interrup_polarity;
} pm_gpio_config_type;
# 289 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
pm_err_flag_type pm_dev_gpio_status_get(unsigned pmic_device_index, pm_gpio_which_type gpio , pm_gpio_status_type *gpio_status);

pm_err_flag_type pm_gpio_status_get(pm_gpio_which_type gpio , pm_gpio_status_type *gpio_status);
# 329 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_config_bias_voltage
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_voltage_source_type voltage_source
 );

extern pm_err_flag_type pm_gpio_config_bias_voltage
(
 pm_gpio_which_type gpio,
 pm_gpio_voltage_source_type voltage_source
 );
# 395 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_config_digital_input
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_current_source_pulls_type i_source_pulls,
 pm_gpio_voltage_source_type voltage_source,
 pm_gpio_out_buffer_drive_strength_type out_buffer_strength,
 pm_gpio_source_config_type source

 );

extern pm_err_flag_type pm_gpio_config_digital_input
(
 pm_gpio_which_type gpio,
 pm_gpio_current_source_pulls_type i_source_pulls,
 pm_gpio_voltage_source_type voltage_source,
 pm_gpio_out_buffer_drive_strength_type out_buffer_strength,
 pm_gpio_source_config_type source
 );
# 468 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_config_digital_output
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_out_buffer_config_type out_buffer_config,
 pm_gpio_voltage_source_type voltage_source,
 pm_gpio_source_config_type source,
 pm_gpio_out_buffer_drive_strength_type out_buffer_strength,
 boolean out_inversion
 );

extern pm_err_flag_type pm_gpio_config_digital_output
(
 pm_gpio_which_type gpio,
 pm_gpio_out_buffer_config_type out_buffer_config,
 pm_gpio_voltage_source_type voltage_source,
 pm_gpio_source_config_type source,
 pm_gpio_out_buffer_drive_strength_type out_buffer_strength,
 boolean out_inversion
 );
# 519 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_voltage_source
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_voltage_source_type voltage_source
 );
extern pm_err_flag_type pm_gpio_set_voltage_source
(
 pm_gpio_which_type gpio,
 pm_gpio_voltage_source_type voltage_source
 );
# 561 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_output_buffer_configuration
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_out_buffer_config_type out_buffer_config
 );

extern pm_err_flag_type pm_gpio_set_output_buffer_configuration
(
 pm_gpio_which_type gpio,
 pm_gpio_out_buffer_config_type out_buffer_config
 );
# 602 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_inversion_configuration
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 boolean inversion
 );

extern pm_err_flag_type pm_gpio_set_inversion_configuration
(
 pm_gpio_which_type gpio,
 boolean inversion
 );
# 645 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_current_source_pulls
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_current_source_pulls_type i_source_pulls
 );

extern pm_err_flag_type pm_gpio_set_current_source_pulls
(
 pm_gpio_which_type gpio,
 pm_gpio_current_source_pulls_type i_source_pulls
 );
# 686 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_ext_pin_config
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_ext_pin_config_type ext_pin_config
 );

extern pm_err_flag_type pm_gpio_set_ext_pin_config
(
 pm_gpio_which_type gpio,
 pm_gpio_ext_pin_config_type ext_pin_config
 );
# 729 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_output_buffer_drive_strength
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_out_buffer_drive_strength_type out_buffer_strength
 );

extern pm_err_flag_type pm_gpio_set_output_buffer_drive_strength
(
 pm_gpio_which_type gpio,
 pm_gpio_out_buffer_drive_strength_type out_buffer_strength
 );
# 771 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_source_configuration
(
 unsigned pmic_device_index,
 pm_gpio_which_type gpio,
 pm_gpio_source_config_type source
 );

extern pm_err_flag_type pm_gpio_set_source_configuration
(
 pm_gpio_which_type gpio,
 pm_gpio_source_config_type source
 );
# 804 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_gpio.h"
extern pm_err_flag_type pm_dev_gpio_set_mux_ctrl(unsigned pmic_device_index,
                                                 pm_gpio_uart_path_type uart_path);

extern pm_err_flag_type pm_gpio_set_mux_ctrl(pm_gpio_uart_path_type uart_path);
# 55 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_coinchg.h" 1
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_coinchg.h"
typedef enum
{



    PM_COIN_CELL_VSET_3p0V,



    PM_COIN_CELL_VSET_3p1V,



    PM_COIN_CELL_VSET_3p2V,



    PM_COIN_CELL_VSET_2p5V,



    PM_COIN_CELL_VSET_INVALID
}pm_coin_cell_vset_type;




typedef enum
{



    PM_COIN_CELL_RSET_2100_OHMS,



    PM_COIN_CELL_RSET_1700_OHMS,



    PM_COIN_CELL_RSET_1200_OHMS,



    PM_COIN_CELL_RSET_800_OHMS,



    PM_COIN_CELL_RSET_INVALID
}pm_coin_cell_rset_type;
# 119 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_coinchg.h"
extern pm_err_flag_type pm_dev_coin_cell_chg_switch(unsigned pmic_device_index, pm_switch_cmd_type cmd);

extern pm_err_flag_type pm_coin_cell_chg_switch(pm_switch_cmd_type cmd);
# 162 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_coinchg.h"
extern pm_err_flag_type pm_dev_coin_cell_chg_config(unsigned pmic_device_index,
                                                    pm_coin_cell_vset_type vset,
                                                    pm_coin_cell_rset_type rset);

extern pm_err_flag_type pm_coin_cell_chg_config(pm_coin_cell_vset_type vset,
                                                pm_coin_cell_rset_type rset);
# 56 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_itemp.h" 1
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_itemp.h"
typedef enum
{
    PM_ITEMP_STAGE0,
    PM_ITEMP_STAGE1,
    PM_ITEMP_STAGE2,
    PM_ITEMP_STAGE3
}pm_item_stage_type;





typedef enum
{
    PM_ITEMP_ORIDE_STAGE2,
    PM_ITEMP_ORIDE_OUT_OF_RANGE
}pm_item_oride_type;





typedef enum
{
    PM_TEMP_THRESH_CTRL0,
    PM_TEMP_THRESH_CTRL1,
    PM_TEMP_THRESH_CTRL2,
    PM_TEMP_THRESH_CTRL3,
    PM_INVALID_INPUT
} pm_itemp_threshold_type;
# 114 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_itemp.h"
pm_err_flag_type pm_dev_itemp_get_stage(unsigned pmic_device_index, pm_item_stage_type *itemp_stage );

pm_err_flag_type pm_itemp_get_stage( pm_item_stage_type *itemp_stage );
# 149 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_itemp.h"
pm_err_flag_type pm_dev_itemp_stage_override(unsigned pmic_device_index, pm_switch_cmd_type oride_cmd,
                                         pm_item_oride_type oride_stage);

pm_err_flag_type pm_itemp_stage_override( pm_switch_cmd_type oride_cmd,
                                         pm_item_oride_type oride_stage);
# 187 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_itemp.h"
pm_err_flag_type pm_dev_itemp_thresh_cntrl(unsigned pmic_device_index, pm_itemp_threshold_type thresh_value );

pm_err_flag_type pm_itemp_thresh_cntrl( pm_itemp_threshold_type thresh_value );
# 57 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h" 1
# 54 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
typedef enum{
    PM_POWER_RESET_SIGNAL__INVALID
}pm_power_reset_signal;

typedef enum
{
    PM_PWR_ON_RST_ACTION_TYPE__COMPLETE_FULL_SHUTDOWN,
    PM_PWR_ON_RST_ACTION_TYPE__FULL_SHUTDOWN,
    PM_PWR_ON_RST_ACTION_TYPE__HARD_RESET,
    PM_PWR_ON_RST_ACTION_TYPE__POWER_OFF_NORMAL,
    PM_PWR_ON_RST_ACTION_TYPE__SOFT_RESET,
    PM_PWR_ON_RST_ACTION_TYPE__WARM_RESET,
    PM_PWR_ON_RST_ACTION_TYPE__INVALID
}pm_power_reset_action_type;



typedef enum
{
  PM_PWR_KEY_DELAY_EQ_0_msecs,
  PM_PWR_KEY_DELAY_EQ_0p97_msecs,
  PM_PWR_KEY_DELAY_EQ_1p95_msecs,
  PM_PWR_KEY_DELAY_EQ_3p90_msecs,
  PM_PWR_KEY_DELAY_EQ_7p81_msecs,
  PM_PWR_KEY_DELAY_EQ_15p62_msecs,
  PM_PWR_KEY_DELAY_EQ_31p25_msecs,
  PM_PWR_KEY_DELAY_EQ_62p50_msecs,
  PM_NUM_OF_PWR_KEY_DELAY

}pm_pwr_key_delay_type;
# 95 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
typedef enum
{
  PM_CBL_PWR_ON__ENABLE,
  PM_CBL_PWR_ON__DISABLE,
  PM_CBL_PWR_ON__DIS_PERMANENTLY,
  PM_CBL_PWR_ON__INVALID
}pm_cbl_pwr_on_switch_type;

typedef enum
{
  PM_CBL_PWR_ON_PIN__0,
  PM_CBL_PWR_ON_PIN__1,
  PM_CBL_PWR_ON_PIN__INVALID
}pm_cbl_pwr_on_pin_type;
# 129 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_start_up_abort_timer_switch(unsigned pmic_device_index, pm_switch_cmd_type OnOff);
# 147 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_pwr_key_delay_set(unsigned pmic_device_index, uint32 microseconds);

pm_err_flag_type pm_pwr_key_delay_set(uint32 microseconds);
# 165 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_pwr_key_pullup_set(unsigned pmic_device_index, pm_switch_cmd_type pull_up_en);

pm_err_flag_type pm_pwr_key_pullup_set(pm_switch_cmd_type pull_up_en);
# 182 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_wdog_status_get(unsigned pmic_device_index, boolean *dog_status);

pm_err_flag_type pm_wdog_status_get(boolean *dog_status);
# 230 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_get_power_on_reason(unsigned pmic_device_index, uint64* pwr_on_reason);
# 278 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_get_power_on_status(unsigned pmic_device_index, uint32* pwr_on_status);

pm_err_flag_type pm_get_power_on_status(uint32* pwr_on_status);
# 313 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_clear_power_on_status(unsigned pmic_device_index);

pm_err_flag_type pm_clear_power_on_status(void);
# 361 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_watchdog_reset_detect_switch(unsigned pmic_device_index, pm_switch_cmd_type OnOff);

pm_err_flag_type pm_watchdog_reset_detect_switch(pm_switch_cmd_type OnOff);
# 427 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_cbl_pwr_on_switch(unsigned pmic_device_index, pm_cbl_pwr_on_switch_type cmd);

pm_err_flag_type pm_cbl_pwr_on_switch(pm_cbl_pwr_on_switch_type cmd);
# 499 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_cbl_pwr_on_pull_up_switch(
                                  unsigned pmic_device_index,
                                  pm_switch_cmd_type OnOff,
                                  pm_cbl_pwr_on_pin_type cable);

pm_err_flag_type pm_cbl_pwr_on_pull_up_switch(
    pm_switch_cmd_type OnOff,
    pm_cbl_pwr_on_pin_type cable);
# 523 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_pwron_soft_reset(unsigned pmic_device_index);

pm_err_flag_type pm_pwron_soft_reset(void);
# 543 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_pwron_hard_reset_enable(unsigned pmic_device_index, boolean enable);

pm_err_flag_type pm_pwron_hard_reset_enable(boolean enable);
# 570 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_pwron_hard_reset_delay_timer_set(unsigned pmic_device_index, int delay_timer_ms);

pm_err_flag_type pm_pwron_hard_reset_delay_timer_set(int delay_timer_ms);
# 601 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_pwron_hard_reset_debounce_timer_set(unsigned pmic_device_index, int debounce_timer_ms);

pm_err_flag_type pm_pwron_hard_reset_debounce_timer_set(int debounce_timer_ms);
# 618 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_pwron.h"
pm_err_flag_type pm_dev_pwron_stay_on_enable(unsigned pmic_device_index, boolean enable);

pm_err_flag_type pm_pwron_stay_on_enable(boolean enable);
# 58 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_misc.h" 1
# 30 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_misc.h"
typedef enum
{
  PM_MISC_LEGACY_MODE__DESSERT = 0,

  PM_MISC_LEGACY_MODE__ASSERT,

  PM_MISC_LEGACY_MODE__INVALID
}pm_misc_legacy_mode_type;

typedef enum {
  PM_MISC_RES_STATE__FOLLOW_BOOT = 0,

  PM_MISC_RES_STATE__OFF = 1,

  PM_MISC_RES_STATE__LPM = 2,

  PM_MISC_RES_STATE__HPM = 3,

  PM_MISC_RES_STATE__INVALID
}pm_misc_res_state_type;


typedef enum
{
  PM_MISC_MODE_ACT__DESSERT = 0,

  PM_MISC_MODE_ACT__ASSERT,

  PM_MISC_MODE_ACT__INVALID
}pm_misc_mode_act_type;

typedef enum
{
  PM_MISC_MODE_CTRL_MASK__FOLLOW_MODE_ACT = 0,

  PM_MISC_MODE_CTRL_MASK__MODE_ACT_DONTCARE,

  PM_MISC_MODE_CTRL_MASK__INVALID
}pm_misc_mode_ctrl_mask_type;


typedef enum
{
  PM_MISC_SEL_CTRL_PIN0 = 0x01,

  PM_MISC_SEL_CTRL_PIN1 = 0x02,

  PM_MISC_SEL_CTRL_PIN2 = 0x04,

  PM_MISC_SEL_CTRL_MODE = 0x08,

  PM_MISC_SEL_CTRL_PIN__INVALID
}pm_misc_sel_ctrl_pin_type;

typedef enum
{
  PM_MISC_CTRL_PIN_MASK__ALLOW_PIN_CTRL = 0,

  PM_MISC_CTRL_PIN_MASK__DISALLOW_PIN_CTRL,

  PM_MISC_CTRL_PIN_MASK__INVALID
}pm_misc_ctrl_pin_mask_type;

typedef enum
{
  PM_MISC_TERM__FORCE_OFF = 0x00,

  PM_MISC_TERM__FORCE_PULLUP = 0x01,

  PM_MISC_TERM__FORCE_PULLDOWN = 0x10,

  PM_MISC_TERM__FOLLOW_MODE_CTRL = 0x11,

  PM_MISC_TERM__INVALID
}pm_misc_term_type;

typedef enum
{
  PM_MISC_DTEST__NORMAL = 0,

  PM_MISC_DTEST__MODE_CTRL_TO_DTEST3,

  PM_MISC_DTEST__INVALID
}pm_misc_dtest_type;

typedef enum
{


  PM_MISC_POLARITY__ACTIVE_H = 0,

  PM_MISC_POLARITY__ACTIVE_L,

  PM_MISC_POLARITY__INVALID
}pm_misc_polarity_type;
# 59 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot.h" 1
# 36 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot.h"
pm_err_flag_type pm_device_init( void );
# 53 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot.h"
pm_err_flag_type pm_tz_device_init( void );
# 69 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot.h"
pm_err_flag_type pm_enable_qfuse_power_rail(void);
# 85 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot.h"
pm_err_flag_type pm_disable_qfuse_power_rail(void);
# 60 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h" 1
# 35 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
typedef enum
{

   PM_BOOT_CHG_LED_SRC__GROUND,

   PM_BOOT_CHG_LED_SRC__VPH_PWR,

   PM_BOOT_CHG_LED_SRC__BOOST,

   PM_BOOT_CHG_LED_SRC__INTERNAL
}pm_boot_chg_led_source_type;




typedef enum
{

   PM_BOOT_CHG_ATTACHED_CHGR__NONE,

   PM_BOOT_CHG_ATTACHED_CHGR__USB,

   PM_BOOT_CHG_ATTACHED_CHGR__DCIN,

   PM_BOOT_CHG_ATTACHED_CHGR__BOTH
}pm_boot_chg_attached_chgr_type;



typedef enum
{

   PM_BOOT_CHG_MODE__CHARGE_OFF,

   PM_BOOT_CHG_MODE__CHARGE_ON,

   PM_BOOT_CHG_MODE__ATC_OFF,

   PM_BOOT_CHG_MODE__ATC_ON
}pm_boot_chg_mode_type;
# 103 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_set_battery_thresholds(uint32 dead_battery_threshold,
                                                    uint32 weak_battery_threshold);
# 116 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_get_weak_battery_status(boolean *weak);
# 131 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_get_battery_present(boolean *present);
# 147 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_get_attached_charger(pm_boot_chg_attached_chgr_type *type);
# 167 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_set_iusb_max(uint32 value_ma);
# 186 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_set_ibat_max(uint32 value_ma);
# 205 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_set_itrkl(uint32 value_ma);
# 228 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_set_mode(pm_boot_chg_mode_type mode);
# 247 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_boot_chg.h"
pm_err_flag_type pm_boot_chg_enable_led (boolean enable, pm_boot_chg_led_source_type source);
# 61 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h" 1
# 42 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
typedef enum
{

   PM_SMBC_CMD__DISABLE,

   PM_SMBC_CMD__ENABLE
}pm_smbc_cmd_type;



typedef enum
{

   PM_SMBC_VDD_DEFAULT__LOW,

   PM_SMBC_VDD_DEFAULT__STANDARD
}pm_smbc_vdd_default_type;




typedef enum
{

   PM_SMBC_BATT_TEMP_REF_GND__PACK,

   PM_SMBC_BATT_TEMP_REF_GND__GND
}pm_smbc_batt_temp_ref_gnd_type;




typedef enum
{

   PM_SMBC_BATT_TEMP_COLD_THR__LOW,

   PM_SMBC_BATT_TEMP_COLD_THR__HIGH
}pm_smbc_batt_temp_cold_thr_type;




typedef enum
{

   PM_SMBC_BATT_TEMP_HOT_THR__LOW,

   PM_SMBC_BATT_TEMP_HOT_THR__HIGH
}pm_smbc_batt_temp_hot_thr_type;




typedef enum
{

   PM_SMBC_MODE__BOOT_FAIL,

   PM_SMBC_MODE__BOOT_DONE,

   PM_SMBC_MODE__BATT_TEMP_SENSING_OFF,

   PM_SMBC_MODE__BATT_TEMP_SENSING_ON,

   PM_SMBC_MODE__IMON_GAIN_LOW,

   PM_SMBC_MODE__IMON_GAIN_HIGH,

   PM_SMBC_MODE__CHARGE_OFF,

   PM_SMBC_MODE__CHARGE_ON,

   PM_SMBC_MODE__CHARGE_PAUSE,

   PM_SMBC_MODE__CHARGE_RESUME,

   PM_SMBC_MODE__FORCE_ATC_OFF,

   PM_SMBC_MODE__FORCE_ATC_ON,

   PM_SMBC_MODE__ATC_FAILED_CLEAR_ON,

   PM_SMBC_MODE__CHG_FAILED_CLEAR_ON,

   PM_SMBC_MODE__USB_SUSPENDED_OFF,

   PM_SMBC_MODE__USB_SUSPENDED_ON
}pm_smbc_mode_type;




typedef enum
{

   PM_SMBC_LED_SRC__GROUND,

   PM_SMBC_LED_SRC__VPH_PWR,

   PM_SMBC_LED_SRC__BOOST,

   PM_SMBC_LED_SRC__INTERNAL
}pm_smbc_led_source_type;




typedef enum
{

   PM_SMBC_ATTACHED_CHGR__NONE,

   PM_SMBC_ATTACHED_CHGR__USB,

   PM_SMBC_ATTACHED_CHGR__DCIN,

   PM_SMBC_ATTACHED_CHGR__BOTH
}pm_smbc_attached_chgr_type;




typedef enum
{

   PM_SMBC_CHGR_PATH__USB,

   PM_SMBC_CHGR_PATH__DCIN
}pm_smbc_chg_path_type;




typedef enum
{

   PM_SMBC_FSM_ST__OFF,

   PM_SMBC_FSM_ST__PWR_ON_CHGR,

   PM_SMBC_FSM_ST__ATC_LOW_I,

   PM_SMBC_FSM_ST__PWR_ON_BATT,

   PM_SMBC_FSM_ST__ATC_FAIL = 4,

   PM_SMBC_FSM_ST__PWR_ON_CHGR_AND_BATT = 6,

   PM_SMBC_FSM_ST__FAST_CHG,

   PM_SMBC_FSM_ST__TRICKLE_CHG,

   PM_SMBC_FSM_ST__CHG_FAIL,

   PM_SMBC_FSM_ST__EOC = 10,

   PM_SMBC_FSM_ST__ATC_PAUSE = 13,

   PM_SMBC_FSM_ST__FAST_CHG_PAUSE,

   PM_SMBC_FSM_ST__TRICKLE_CHG_PAUSE = 15,

   PM_SMBC_FSM_ST__ATC_HIGH_I = 18,

   PM_SMBC_FSM_ST__FLCB = 22
}pm_smbc_fsm_state_name_type;
# 286 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_mode(int externalResourceIndex,
                                  pm_smbc_mode_type mode);
# 327 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_pwron_trig(int externalResourceIndex,
                                        pm_smbc_cmd_type enable,
                                        pm_smbc_chg_path_type path);
# 353 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_batfet_present(int externalResourceIndex,
                                            boolean *present);
# 382 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_default_vdd(int externalResourceIndex,
                                         pm_smbc_vdd_default_type vdd);
# 414 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_batt_temp_config(int externalResourceIndex,
                                      pm_smbc_batt_temp_ref_gnd_type ref_gnd,
                                      pm_smbc_batt_temp_cold_thr_type cold_thr,
                                      pm_smbc_batt_temp_hot_thr_type hot_thr);
# 447 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_batt_therm_gnd(int externalResourceIndex,
                                     pm_smbc_batt_temp_ref_gnd_type* ref_gnd);
# 479 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_led_source(int externalResourceIndex,
                                        pm_smbc_led_source_type source);
# 509 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_battery_weak(int externalResourceIndex,
                                          boolean *weak);
# 538 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_attached_charger(int externalResourceIndex,
                                              pm_smbc_attached_chgr_type *type);
# 566 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_battery_present(int externalResourceIndex,
                                             boolean *present);
# 600 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_iusb_max(int externalResourceIndex,
                                      uint32 value_ma);
# 633 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_vdd_max(int externalResourceIndex,
                                     uint32 value_mv);
# 669 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_vbatdet(int externalResourceIndex,
                                     uint32 value_mv);
# 702 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_ibat_max(int externalResourceIndex,
                                      uint32 value_ma);
# 735 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_vin_min(int externalResourceIndex,
                                     uint32 value_mv);
# 763 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_batt_sense_r(int externalResourceIndex,
                                          uint32* value_mOhm);
# 797 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_weak_vbatt_threshold(int externalResourceIndex,
                                                  uint32 value_mv);
# 831 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_low_vbatt_threshold(int externalResourceIndex,
                                                 uint32 value_mv);
# 864 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_itrkl(int externalResourceIndex,
                                   uint32 value_ma);
# 898 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_iterm(int externalResourceIndex, uint32 value_ma);
# 933 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_ttrkl(int externalResourceIndex,
                                   uint32 value_minutes);
# 968 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_tchg(int externalResourceIndex,
                                  uint32 value_minutes);
# 1019 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_twdog(int externalResourceIndex,
                                   uint32 delay_seconds,
                                   uint32 timeout_seconds);
# 1061 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_temp_threshold(int externalResourceIndex,
                                            uint32 stop_deg_c,
                                            uint32 resume_deg_c);
# 1092 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_charge_path(int externalResourceIndex,
                                         pm_smbc_chg_path_type path);
# 1121 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_charge_path(int externalResourceIndex,
                                         pm_smbc_chg_path_type *path);
# 1147 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_set_charge_state(int externalResourceIndex,
                                          pm_smbc_fsm_state_name_type state);
# 1173 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_smbc.h"
pm_err_flag_type pm_smbc_get_charge_state(int externalResourceIndex,
                                          pm_smbc_fsm_state_name_type *state);
# 62 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h" 1
# 35 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
typedef enum
{

   PM_BTM_MODE__MODULE_OFF,

   PM_BTM_MODE__MODULE_ON
}pm_btm_mode_type;




typedef enum
{

   PM_BTM_CONV_REQ_CMD__OFF,

   PM_BTM_CONV_REQ_CMD__ON
}pm_btm_conv_req_cmd_type;




typedef enum
{

    PM_BTM_XOADC_CONVERSION_STATUS__COMPLETE,

    PM_BTM_XOADC_CONVERSION_STATUS__PENDING
} pm_btm_xoadc_conversion_status_type;




typedef enum
{
   PM_BTM_MEAS_MODE_SINGLE = 0,
   PM_BTM_MEAS_MODE_CONTINUOUS
}pm_btm_meas_mode_type;




typedef enum
{
   PM_BTM_AMUX_MAIN,
   PM_BTM_PREMUX_TO_CH6,
   PM_BTM_PREMUX_TO_CH7,
   PM_BTM_RSV_DISABLED
} pm_btm_mux_type;




typedef enum
{
   PM_BTM_XOADC_INPUT_XO_IN_XOADC_GND,
   PM_BTM_XOADC_INPUT_PMIC_IN_XOADC_GND,
   PM_BTM_XOADC_INPUT_PMIC_IN_BMS_CSP,
   PM_BTM_XOADC_INPUT_RESERVED,
   PM_BTM_XOADC_INPUT_XOADC_GND_XOADC_GND,
   PM_BTM_XOADC_INPUT_XOADC_VDD_XOADC_GND,
   PM_BTM_XOADC_INPUT_VREFN_VREFN,
   PM_BTM_XOADC_INPUT_VREFP_VREFN
} pm_btm_xoadc_input_select_type;




typedef enum
{
  PM_BTM_XOADC_DECIMATION_RATIO_512,
  PM_BTM_XOADC_DECIMATION_RATIO_1K,
  PM_BTM_XOADC_DECIMATION_RATIO_2K,
  PM_BTM_XOADC_DECIMATION_RATIO_4K,
} pm_btm_xoadc_decimation_ratio_type;




typedef enum
{
  PM_BTM_XOADC_CONVERSION_RATE_TCXO_DIV_8,
  PM_BTM_XOADC_CONVERSION_RATE_TCXO_DIV_4,
  PM_BTM_XOADC_CONVERSION_RATE_TCXO_DIV_2,
  PM_BTM_XOADC_CONVERSION_RATE_TCXO
} pm_btm_xoadc_conversion_rate_type;
# 156 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_mode(int externalResourceIndex,
                                 pm_btm_mode_type mode);
# 188 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_conversion_request(int externalResourceIndex,
                                               pm_btm_conv_req_cmd_type cmd);
# 220 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_get_conversion_status(int externalResourceIndex,
                            pm_btm_xoadc_conversion_status_type *status);
# 253 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_measurement_mode(int externalResourceIndex,
                                             pm_btm_meas_mode_type mode);
# 286 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_measurement_interval(int externalResourceIndex,
                                                 uint32 second);
# 317 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_amux(int externalResourceIndex,
                                 uint8 channel,
                                 pm_btm_mux_type mux);
# 350 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_get_prescalar(int externalResourceIndex,
                                      uint8 channel,
                                      uint8 *numerator,
                                      uint8 *denominator);
# 383 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_xoadc_input(int externalResourceIndex,
                                        pm_btm_xoadc_input_select_type input);
# 415 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_xoadc_decimation_ratio(int externalResourceIndex,
                                    pm_btm_xoadc_decimation_ratio_type ratio);
# 447 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_xoadc_conversion_rate(int externalResourceIndex,
                                    pm_btm_xoadc_conversion_rate_type rate);
# 475 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_get_xoadc_data(int externalResourceIndex,
                                       uint32* data);
# 503 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_batt_warm_threshold(int externalResourceIndex,
                                                uint32 warm_temp_thresh);
# 531 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_btm.h"
pm_err_flag_type pm_btm_set_batt_cool_threshold(int externalResourceIndex,
                                                uint32 cool_temp_thresh);
# 63 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h" 1
# 35 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
typedef enum
{

   PM_ADC_MODE__MODULE_OFF,

   PM_ADC_MODE__MODULE_ON
}pm_adc_mode_type;




typedef enum
{

   PM_ADC_CONVERSION_REQ_CMD__OFF,

   PM_ADC_CONVERSION_REQ_CMD__ON
}pm_adc_conv_req_cmd_type;




typedef enum
{

   PM_ADC_CMD__DISABLE,

   PM_ADC_CMD__ENABLE
}pm_adc_cmd_type;




typedef enum
{

    PM_ADC_CONVERSION_STATUS__COMPLETE,

    PM_ADC_CONVERSION_STATUS__PENDING
} pm_adc_conversion_status_type;





typedef enum
{

   PM_ADC_CONV_TRIG__FE,

   PM_ADC_CONV_TRIG__RE
}pm_adc_conv_trig_type;




typedef enum
{
   PM_ADC_AMUX_MAIN,
   PM_ADC_PREMUX_TO_CH6,
   PM_ADC_PREMUX_TO_CH7,
   PM_ADC_RSV_DISABLED
} pm_adc_mux_type;




typedef enum
{
   PM_ADC_XOADC_INPUT_XO_IN_XOADC_GND,
   PM_ADC_XOADC_INPUT_PMIC_IN_XOADC_GND,
   PM_ADC_XOADC_INPUT_PMIC_IN_BMS_CSP,
   PM_ADC_XOADC_INPUT_RESERVED,
   PM_ADC_XOADC_INPUT_XOADC_GND_XOADC_GND,
   PM_ADC_XOADC_INPUT_XOADC_VDD_XOADC_GND,
   PM_ADC_XOADC_INPUT_VREFN_VREFN,
   PM_ADC_XOADC_INPUT_VREFP_VREFN
} pm_adc_xoadc_input_select_type;




typedef enum
{
  PM_ADC_XOADC_DECIMATION_RATIO_512,
  PM_ADC_XOADC_DECIMATION_RATIO_1K,
  PM_ADC_XOADC_DECIMATION_RATIO_2K,
  PM_ADC_XOADC_DECIMATION_RATIO_4K,
} pm_adc_xoadc_decimation_ratio_type;




typedef enum
{
  PM_ADC_XOADC_CONVERSION_RATE_TCXO_DIV_8,
  PM_ADC_XOADC_CONVERSION_RATE_TCXO_DIV_4,
  PM_ADC_XOADC_CONVERSION_RATE_TCXO_DIV_2,
  PM_ADC_XOADC_CONVERSION_RATE_TCXO
} pm_adc_xoadc_conversion_rate_type;





typedef struct
{

   boolean timeout;

   boolean fifo_not_empty;
}pm_adc_conv_seq_status_type;
# 181 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_mode(int externalResourceIndex,
                                 pm_adc_mode_type mode);
# 211 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_conversion_request(int externalResourceIndex,
                                               pm_adc_conv_req_cmd_type cmd);
# 242 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_get_conversion_status(int externalResourceIndex,
                                  pm_adc_conversion_status_type *status);
# 274 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_conv_sequencer(int externalResourceIndex,
                                           pm_adc_cmd_type cmd);
# 306 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_conv_trig_condition(int externalResourceIndex,
                                                pm_adc_conv_trig_type trig);
# 340 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_holdoff_time(int externalResourceIndex,
                                         uint32 time_us);
# 374 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_timeout_time(int externalResourceIndex,
                                         uint32 time_ms);
# 408 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_get_conv_sequencer_status(int externalResourceIndex,
                                        pm_adc_conv_seq_status_type *status);
# 439 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_amux(int externalResourceIndex,
                                 uint8 channel,
                                 pm_adc_mux_type mux);
# 473 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_get_resource_prescalar(int externalResourceIndex,
                                               uint8 channel,
                                               uint8 *numerator,
                                               uint8 *denominator);
# 506 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_xoadc_input(int externalResourceIndex,
                                        pm_adc_xoadc_input_select_type input);
# 538 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_xoadc_decimation_ratio(int externalResourceIndex,
                                    pm_adc_xoadc_decimation_ratio_type ratio);
# 570 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_set_xoadc_conversion_rate(int externalResourceIndex,
                                    pm_adc_xoadc_conversion_rate_type rate);
# 597 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_arbiter_xoadc.h"
pm_err_flag_type pm_adc_get_xoadc_data(int externalResourceIndex,
                                       uint32* data);
# 64 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_uicc.h" 1
# 37 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_uicc.h"
typedef enum
{
  PM_UICC_POLARITY_ACTIVE_LOW,
  PM_UICC_POLARITY_ACTIVE_HIGH,
  PM_UICC_POLARITY_INVALID,
} pm_uicc_polarity_type;
# 64 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_uicc.h"
pm_err_flag_type pm_uicc_cntrl_enable(int externalResourceIndex, boolean enable);
# 76 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_uicc.h"
pm_err_flag_type pm_uicc_set_polarity(int externalResourceIndex, pm_uicc_polarity_type polarity);
# 65 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_xo_core.h" 1
# 32 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_xo_core.h"
typedef enum
{



    PM_XO_CORE_PWR_MODE__VLPM,



    PM_XO_CORE_PWR_MODE__LPM,



    PM_XO_CORE_PWR_MODE__NPM,



    PM_XO_CORE_PWR_MODE__HPM
} pm_xo_core_power_mode_type;
# 90 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_xo_core.h"
pm_err_flag_type pm_dev_xo_core_set_power_mode(unsigned pmic_device_index,
                                           int externalResourceIndex,
                                           pm_xo_core_power_mode_type mode);

pm_err_flag_type pm_xo_core_set_power_mode(int externalResourceIndex,
                                           pm_xo_core_power_mode_type mode);
# 123 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_xo_core.h"
pm_err_flag_type pm_dev_mega_xo_set_xo_trim(unsigned pmic_device_index, int externalResourceIndex, uint8 trim_value);

pm_err_flag_type pm_mega_xo_set_xo_trim(int externalResourceIndex, uint8 trim_value);
# 150 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_xo_core.h"
pm_err_flag_type pm_dev_mega_xo_get_xo_trim(unsigned pmic_device_index, int externalResourceIndex, uint8* trim_value);

pm_err_flag_type pm_xo_core_get_xo_trim(int externalResourceIndex, uint8* trim_value);
# 162 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_xo_core.h"
pm_err_flag_type pm_dev_mega_xo_set_xo_core_force_on(unsigned pmic_device_index, int externalResourceIndex, boolean xo_core_enable);

pm_err_flag_type pm_xo_core_set_xo_core_force_on(int externalResourceIndex, boolean xo_core_enable);
# 66 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_clk_buffer.h" 1
# 32 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_clk_buffer.h"
typedef enum
{



    PM_CLK_BUFF_OUT_DRV__1X,



    PM_CLK_BUFF_OUT_DRV__2X,



    PM_CLK_BUFF_OUT_DRV__3X,



    PM_CLK_BUFF_OUT_DRV__4X,
} pm_clk_buff_output_drive_strength_type;
# 91 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_clk_buffer.h"
pm_err_flag_type pm_dev_clk_buff_set_output_drive_strength(unsigned pmic_device_index,
                                                           int resourceIndex,
                                                           pm_clk_buff_output_drive_strength_type drive_strength);

pm_err_flag_type pm_clk_buff_set_output_drive_strength(int resourceIndex,
                                                       pm_clk_buff_output_drive_strength_type drive_strength);
# 109 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_clk_buffer.h"
pm_err_flag_type pm_dev_clk_buff_enable(unsigned pmic_device_index, int resourceIndex, boolean enable);

pm_err_flag_type pm_clk_buff_enable(int resourceIndex, boolean enable);
# 124 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_clk_buffer.h"
pm_err_flag_type pm_dev_clk_buff_pin_control_enable(unsigned pmic_device_index, int resourceIndex, boolean pin_control_enable);

pm_err_flag_type pm_clk_buff_pin_control_enable(int resourceIndex, boolean enable);
# 140 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_clk_buffer.h"
pm_err_flag_type pm_dev_clk_buff_pin_control_polarity(unsigned pmic_device_index, int resourceIndex, boolean is_low_enabled);
# 67 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_lib_api.h" 2
# 43 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/power/rpm.h" 1
# 14 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/power/rpm.h"
typedef enum
{
    RPM_ACTIVE_SET = 0,
    RPM_SLEEP_SET = 1,



    RPM_NUM_SETS
} rpm_set_type;

typedef enum
{
    RPM_TEST_REQ = 0x74736574,

    RPM_CLOCK_0_REQ = 0x306b6c63,
    RPM_CLOCK_1_REQ = 0x316b6c63,
    RPM_CLOCK_2_REQ = 0x326b6c63,

    RPM_BUS_SLAVE_REQ = 0x766c7362,
    RPM_BUS_MASTER_REQ = 0x73616d62,
    RPM_BUS_SPDM_CLK_REQ = 0x63707362,

    RPM_SMPS_A_REQ = 0x61706D73,
    RPM_LDO_A_REQ = 0x616F646C,
    RPM_NCP_A_REQ = 0x6170636E,
    RPM_VS_A_REQ = 0x617376,
    RPM_CLK_BUFFER_A_REQ = 0x616B6C63,

    RPM_SMPS_B_REQ = 0x62706D73,
    RPM_LDO_B_REQ = 0x626F646C,
    RPM_NCP_B_REQ = 0x6270636E,
    RPM_VS_B_REQ = 0x627376,
    RPM_CLK_BUFFER_B_REQ = 0x626B6C63,

 RPM_OCMEM_POWER_REQ = 0x706d636f,
} rpm_resource_type;

typedef enum
{
    RPM_REQUEST_SERVICE = 0x00716572,
    RPM_SYSTEMDB_SERVICE = 0x00626473,
} rpm_service_type;

boolean rpm_is_up(void);

void ubsp_rpm_send (uint32 resource_type, uint32 id, uint32 set, uint8 *kvps, uint32 len);
# 44 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h" 2
# 67 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h"
pm_err_flag_type pm_init(void);
# 85 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h"
pm_err_flag_type pm_ssc_config(boolean active);
# 104 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/systemdrivers/pmic/pm_qc_pmic.h"
pm_err_flag_type
pm_app_cx_corner_request(uint32 corner_value, rpm_set_type rpm_set);
# 29 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/pmic_devices/common/src/device_info.h" 2
# 70 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/pmic_devices/common/src/device_info.h"
pm_err_flag_type pm_version_detect(void);
# 94 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/pmic_devices/common/src/device_info.h"
pm_err_flag_type pm_get_slave_id(uint8 pmic_index, uint8 slave_id_index, uint32* slave_id_ptr);
# 107 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/pmic_devices/common/src/device_info.h"
uint8 pm_get_num_slaves_per_pmic(void);
# 29 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/config/msm8996_pm8994/src/pm_oem_config.c" 2








const pm_app_pon_reset_cfg_type pm_oem_pshold_cfg[PM_APP_PON_CFG_MAX][7] =
{
   {PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_NO_CONFIG_NEEDED, 0,0,0},
   {PM_APP_PON_CFG_WARM_RESET, PM_APP_PON_CFG_WARM_RESET, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_WARM_RESET, 0,0,0},
   {PM_APP_PON_CFG_HARD_RESET, PM_APP_PON_CFG_DVDD_HARD_RESET, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_NORMAL_SHUTDOWN, 0,0,0},
   {PM_APP_PON_CFG_NORMAL_SHUTDOWN, PM_APP_PON_CFG_NORMAL_SHUTDOWN, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_NORMAL_SHUTDOWN, 0,0,0},
   {PM_APP_PON_CFG_DVDD_HARD_RESET, PM_APP_PON_CFG_DVDD_SHUTDOWN, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_DVDD_SHUTDOWN, 0,0,0},
   {PM_APP_PON_CFG_DVDD_SHUTDOWN, PM_APP_PON_CFG_DVDD_SHUTDOWN, PM_APP_PON_CFG_NO_CONFIG_NEEDED, PM_APP_PON_CFG_DVDD_SHUTDOWN, 0,0,0}
};

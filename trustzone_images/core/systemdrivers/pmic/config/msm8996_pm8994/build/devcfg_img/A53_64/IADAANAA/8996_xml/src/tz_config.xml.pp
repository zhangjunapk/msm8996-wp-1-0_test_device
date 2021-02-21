# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/config/msm8996_pm8994/src/tz_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/pmic/config/msm8996_pm8994/src/tz_config.xml" 2
<driver name="NULL">
<device id="/tz/pmic">
<props name="QFPROM_rail_id" type=DALPROP_ATTR_TYPE_UINT32>
15
</props>
<props name="QFPROM_rail_type" type=DALPROP_ATTR_TYPE_UINT32>
0x616F646C
</props>
<props name="pam_qfprom_rail" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
pm_pam_qfprom_rail
</props>
<props name="ddr_rail_reg" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
 pm_ddr_rai_reg
</props>
<!--
    Uncomment below for dVdd hard reset configuration for PMI
-->
<!--
<props name="oem_pshold_config" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
 pm_oem_pshold_cfg
</props>
-->
</device>
</driver>

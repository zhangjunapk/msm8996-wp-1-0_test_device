# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/biometrics/ontario/config/src/ontario_config_8996.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/biometrics/ontario/config/src/ontario_config_8996.xml" 2
# 22 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/biometrics/ontario/config/src/ontario_config_8996.xml"
<driver name="NULL">
  <global_def>
      <var_seq name = "gcc_blsp_ahb_clk" type=DALPROP_DATA_TYPE_STRING>gcc_blsp1_ahb_clk</var_seq>
      <var_seq name = "gcc_blsp_qup_spi_apps_clk" type=DALPROP_DATA_TYPE_STRING>gcc_blsp1_qup5_spi_apps_clk</var_seq>
  </global_def>
  <device id="/dev/ont">
      <props name="spi_device_id" type=DALPROP_ATTR_TYPE_UINT32>13</props>
      <props name="gcc_blsp_ahb_clk" type=DALPROP_ATTR_TYPE_STRING_PTR>gcc_blsp_ahb_clk</props>
      <props name="gcc_blsp_qup_spi_apps_clk" type=DALPROP_ATTR_TYPE_STRING_PTR>gcc_blsp_qup_spi_apps_clk</props>
      <props name="clock-frequency" type=DALPROP_ATTR_TYPE_UINT32>15000000</props>
  </device>
</driver>

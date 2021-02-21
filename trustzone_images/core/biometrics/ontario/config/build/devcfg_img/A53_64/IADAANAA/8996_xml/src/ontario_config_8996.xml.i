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

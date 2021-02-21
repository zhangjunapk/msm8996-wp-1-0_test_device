<driver name="NULL">
    <!--
 "global_def" section contains strings used by the "device" section below.
 Each string should be referenced using the unique "name" property from the "device" section.
  -->
  <global_def>
    <var_seq name="system_path_00" type=DALPROP_DATA_TYPE_STRING>
      "/system/build.prop"
    </var_seq>
    <var_seq name="system_path_01" type=DALPROP_DATA_TYPE_STRING>
      "/system/default.prop"
    </var_seq>
    <var_seq name="system_path_02" type=DALPROP_DATA_TYPE_STRING>
      "/system/app"
    </var_seq>
    <var_seq name="system_path_03" type=DALPROP_DATA_TYPE_STRING>
      "/system/bin"
    </var_seq>
    <var_seq name="system_path_04" type=DALPROP_DATA_TYPE_STRING>
      "/system/etc"
    </var_seq>
    <var_seq name="system_path_05" type=DALPROP_DATA_TYPE_STRING>
      "/system/framework"
    </var_seq>
    <var_seq name="system_path_06" type=DALPROP_DATA_TYPE_STRING>
      "/system/lib"
    </var_seq>
    <var_seq name="system_path_07" type=DALPROP_DATA_TYPE_STRING>
      "/system/priv-app"
    </var_seq>
    <var_seq name="system_path_08" type=DALPROP_DATA_TYPE_STRING>
      "/system/vendor"
    </var_seq>
    <var_seq name="system_path_09" type=DALPROP_DATA_TYPE_STRING>
      "/system/xbin"
    </var_seq>
  </global_def>
  <!-- "device" section contains configuration properties read by MDTP -->
  <device id="mdtp">
    <!-- "mdtp_system_min_verify_ratio" property specifies minimal verify ratio for the system partition.
    The property value unit are percent and the valid numeric range is 1 to 100.
    For example: value of 10 will result in 10% minimal verification ratio.
    -->
    <props name="mdtp_system_min_verify_ratio" type=DALPROP_ATTR_TYPE_UINT32>
      10
    </props>
    <!-- "mdtp_system_path_##" properties specifies file/directory path to protect by MDTP
    - Each property "name" attribute should end with two decimal digits.
      Allowed range is 00-99 (mdtp_system_path_00 ... mdtp_system_path_99)
    - The properties definition should come in a strict incremental order
      E.g: mdtp_system_path_00, mdtp_system_path_01, mdtp_system_path_02 ,...
    - The property value is a name reference to a string defined in a "global_def" section above
    - At least one system path property should be present in this concfiguration file. Otherwise the
      whole configuraiton will be discarded.
    - Properties are processed in order. If an invalid property is encounterd or property
      is missing the rest of configration will discarded.
    -->
    <props name="mdtp_system_path_00" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_00
    </props>
    <props name="mdtp_system_path_01" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_01
    </props>
    <props name="mdtp_system_path_02" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_02
    </props>
    <props name="mdtp_system_path_03" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_03
    </props>
    <props name="mdtp_system_path_04" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_04
    </props>
    <props name="mdtp_system_path_05" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_05
    </props>
    <props name="mdtp_system_path_06" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_06
    </props>
    <props name="mdtp_system_path_07" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_07
    </props>
    <props name="mdtp_system_path_08" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_08
    </props>
    <props name="mdtp_system_path_09" type=DALPROP_ATTR_TYPE_STRING_PTR>
      system_path_09
    </props>
  </device>
</driver>

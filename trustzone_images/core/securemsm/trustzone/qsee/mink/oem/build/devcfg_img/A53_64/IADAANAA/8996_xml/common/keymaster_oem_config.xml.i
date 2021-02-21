<driver name="NULL">
  <global_def>
    <var_seq name="fpta_name_str" type=DALPROP_DATA_TYPE_STRING>
      fingerprint
    </var_seq>
    <var_seq name="fp_sensor_name_str" type=DALPROP_DATA_TYPE_STRING>
      Stargate
    </var_seq>
  </global_def>
  <device id="keymaster">
    <props name="fpta_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      fpta_name_str
    </props>
<!--
    OEM specific requirement for GK Retry Timeout, default is 0.
-->
    <props name="gk_timeout_config" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="fp_sensor_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      fp_sensor_name_str
    </props>
    <props name="fp_sensor_version" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>
    <props name="enable_finger_id" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="enable_soter" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
  </device>
</driver>

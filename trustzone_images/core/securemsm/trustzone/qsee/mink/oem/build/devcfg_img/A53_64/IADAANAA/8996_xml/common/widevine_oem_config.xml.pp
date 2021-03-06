# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/widevine_oem_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/widevine_oem_config.xml" 2
<driver name="NULL">

  <global_def>

    <var_seq name="drm_data_store_path" type=DALPROP_DATA_TYPE_STRING>
      "/data/misc/qsee/"
    </var_seq>

  </global_def>

  <device id="widevine">

<!--
    Not applicable to Widevine
-->
    <props name="license_data_store_path" type=DALPROP_ATTR_TYPE_STRING_PTR>
      drm_data_store_path
    </props>

<!--
    Not applicable to Widevine
-->
    <props name="disable_security_stream_check" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

<!--
    Not applicable to Widevine
-->
    <props name="get_IV_constraint" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

<!--
    Not applicable to Widevine
-->
    <props name="use_legacy_hdmi_hdcp_check" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

<!--
    customers need to config "provision_constraint_flag" to have single time provisioning
    feature with drm_prov_finalize().
    if "provision_constraint_flag" = 1, key provisioning can be done only once after calling drm_prov_finalize().
    if "provision_constraint_flag" = 0, there is no such constraint
-->
    <props name="provision_constraint_flag" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

<!--
   The maximum HDCP 2.x version that OEM can support
   we define
   1 is NOT supported.
   2 is HDCP2.0;
   3 is HDCP2.1;
   4 is HDCP2.2;
-->
    <props name="maximum_hdcp_2x_capability" type=DALPROP_ATTR_TYPE_UINT32>
      4
    </props>

<!--
   This feature for Widevine debug only
   if g_widevine_kcb_logging_flag is set (=1), every OEMCrypto_SelectKey will log
   key control block info: including magic, duration, nonce, control bits (4 bytes).
   Note, this feature should be only turned on for a debugging purpose. Turning on
   this feature adds more loggings and downgrades performance.
   0: Disable
   1: Enable
-->
    <props name="enable_kcb_logging_flag" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

  </device>
</driver>

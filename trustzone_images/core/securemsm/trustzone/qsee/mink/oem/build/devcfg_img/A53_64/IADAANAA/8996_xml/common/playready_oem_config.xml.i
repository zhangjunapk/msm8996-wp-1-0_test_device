<driver name="NULL">
  <global_def>
    <var_seq name="drm_data_store_path" type=DALPROP_DATA_TYPE_STRING>
      "/data/misc/qsee/"
    </var_seq>
  </global_def>
  <device id="playread">
    <props name="license_data_store_path" type=DALPROP_ATTR_TYPE_STRING_PTR>
      drm_data_store_path
    </props>
<!--
    customers need to config "proprietary_play_enabler_video_protect"
    if "proprietary_play_enabler_video_protect" = 1, g_bUse_proprietary_play_enabler_default_subsample = 1
                audio stream must match customer specific requirements and default behaviour is "CHECK_SUBSAMPLE"
                This is the case where server side development is completely up and running.
    if "proprietary_play_enabler_video_protect" = 1, g_bUse_proprietary_play_enabler_default_subsample = 0
                audio stream must match customer specific requirements and default behaviour "CHECK_NONE"
                This is the case where server side development is in intermediate stage where there can be a GUID in license
    if "proprietary_play_enabler_video_protect" = 0, g_bUse_proprietary_play_enabler_default_subsample = 1
                server side development is not ready (no GUIDs in license) and default behaviour "CHECK_SUBSAMPLE"
    if "proprietary_play_enabler_video_protect" = 0, g_bUse_proprietary_play_enabler_default_subsample = 0
                server side development is not ready (no GUIDs in license) and default behaviour "CHECK_NONE"
   NOTE: "IV_constraint" and below flags SHOULD NOT be used together.
-->
    <props name="proprietary_play_enabler_video_protect" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="proprietary_play_enabler_default_behaviour" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
<!--
    customers need to configure "get_IV_constraint"
    if "IV_constraint" = 1, audio IV must begin with 0b01
                                 video IV must begin with 0b00
    if "IV_constraint" = 0, there is no such a constraint
-->
    <props name="IV_constraint" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
<!--
    This is the robustness version value used by porting kit while generating
    device certificates. This value should be incremented by OEMs as part of
    reprovisioning the device whenever there is a revocation. If there is a
    mismatch between this value and the robustness version used in model
    certificates, then initialize will fail. Hence, this value should always be
    same as that of the value used in model certificates.
-->
    <props name="robustness_version" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
<!--
   OEMs need to set this flag to zero to avoid check for existence of
   play enabler object in license.
   set "proprietary_play_enabler_profile" = 1, to check for existence of
   play enabler object in license.
   Note: Blocking or unblocking HDCP display is based on how this flag is
         used with "proprietary_opl_profile_0". Valid combinations
         are explained in the comment section for "proprietary_opl_profile_0".
   set "proprietary_play_enabler_profile" = 0, to ignore check for
   existence of play enabler object in license.
-->
    <props name="proprietary_play_enabler_profile" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
<!--
   OEMs need to define this flag to enable check for OPL >= 270.
   Please note that if this flag has to be enabled then "proprietary_play_enabler_profile"
   should also be enabled. Below are the valid/invalid combinations.
   (1) "proprietary_play_enabler_profile" = 0, "proprietary_opl_profile_0" = 0 (valid)
       HDCP display is controlled with regular OPL>=301 check
   (2) "proprietary_play_enabler_profile" = 1, "proprietary_opl_profile_0" = 0 (valid)
       HDCP display is blocked if play enabler object is not found in license.
   (3) "proprietary_play_enabler_profile" = 0, "proprietary_opl_profile_0" = 1 (Invalid)
       Invalid combination. Result is same as case (1)
   (4) "proprietary_play_enabler_profile" = 1, "proprietary_opl_profile_0" = 1 (valid)
       HDCP display is blocked if OPL>=270.
   set "proprietary_opl_profile_0" = 1, to check for OPL >= 270 in license.
   Note: If this flag is enabled (set to one) then OPL >=270 check will act as fallback
         check in case play enabler object for HDCP display is not found in license.
         i.e., HDCP WFD gets blocked if play enabler object is not found and OPL >= 270.
   set "proprietary_opl_profile_0" = 0, to ignore OPL 270 check
   Note: If this flag is disabled (set to zero) then HDCP display gets blocked if play
         enabler object for HDCP display is not found in license.
-->
    <props name="proprietary_opl_profile_0" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="disable_security_stream_check" type=DALPROP_ATTR_TYPE_UINT32>
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
    <props name="use_legacy_hdmi_hdcp_check" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
  </device>
</driver>

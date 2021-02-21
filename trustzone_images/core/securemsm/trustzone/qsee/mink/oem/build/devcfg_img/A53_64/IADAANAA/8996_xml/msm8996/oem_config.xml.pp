# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/msm8996/oem_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/msm8996/oem_config.xml" 2
<driver name="NULL">
  <global_def>

  </global_def>
  <device id="/tz/oem">
    <props name="OEM_keystore_enable_rpmb" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>
    <props name="OEM_counter_enable_rpmb" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>
    <props name="OEM_allow_rpmb_key_provision" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="OEM_disable_rpmb_autoprovisioning" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="OEM_sec_wdog_bark_time" type="0x00000002">
      6000
    </props>
    <props name="OEM_sec_wdog_bite_time" type=DALPROP_ATTR_TYPE_UINT32>
      32000
    </props>
    <props name="OEM_reset_reason_list" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
      oem_rst_reason_list
    </props>
    <props name="OEM_l2_wa_enable" type="0x00000002">
    1
    </props>

    <!-- RoT transfer: enable feature and provide pk_hash1/encryption key1 fuse data -->
    <props name="OEM_rot_enable_transfer_APPS" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="OEM_rot_enable_transfer_MODEM" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="OEM_rot_pk_hash1_fuse_values" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
      0x00, end
    </props>
    <!-- RoT transfer: END-->

    <!-- PIL load region information -->
    <props name="OEM_pil_secure_app_load_region_size" type=DALPROP_ATTR_TYPE_UINT32>
      0x02200000
    </props>
    <props name="OEM_pil_subsys_load_region_start" type=DALPROP_ATTR_TYPE_UINT32>
      0x88800000
    </props>
    <props name="OEM_pil_subsys_load_region_size" type=DALPROP_ATTR_TYPE_UINT32>
      0x8D00000
    </props>

    <!--
    <props name="OEM_pil_enable_clear_pil_region" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    -->

    <!-- PIMEM disable flag, default is PIMEM, to disable set value to 1-->
 <props name="OEM_disable_secure_app_pimem" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

  </device>
</driver>

# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/cmnlib_oem_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/cmnlib_oem_config.xml" 2
<driver name="NULL">

  <global_def>

    <var_seq name="gppo_root_path" type=DALPROP_DATA_TYPE_STRING>
      "/persist/data/"
    </var_seq>

  </global_def>

  <device id="commonlib">

    <props name="cmnlib_gppo_rpmb_enablement" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>

    <props name="cmnlib_gppo_root_path" type=DALPROP_ATTR_TYPE_STRING_PTR>
      gppo_root_path
    </props>

  </device>
</driver>

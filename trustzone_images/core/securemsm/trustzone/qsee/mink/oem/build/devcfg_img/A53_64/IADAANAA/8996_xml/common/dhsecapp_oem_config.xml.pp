# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/dhsecapp_oem_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/dhsecapp_oem_config.xml" 2
<driver name="NULL">
  <global_def>
    <var_seq name="kernel_version_str" type=DALPROP_DATA_TYPE_STRING>
        "Linux version 3.14.26-g43b1178-00038-g96ef344 (lnxbuild@abait242-sd-lnx) (gcc version 4.9.x-google 20140827 (prerelease) (GCC) ) #1 SMP PREEMPT Fri Jun 5 15:15:57 PDT 2015"
    </var_seq>
  </global_def>
  <device id="dhsecapp">
    <props name="kernel_version" type=DALPROP_ATTR_TYPE_STRING_PTR>
        kernel_version_str
    </props>
    <props name="kernel_version_str_length" type=DALPROP_ATTR_TYPE_UINT32>
        171
    </props>
    <props name="challenges" type="byte" array="true">
 {
  0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,
  0x00,0x54,0x08,0x00,0xC0,0xFF,0xFF,0xFF,
  0xF0,0xDE,0xBC,0x9A,0x78,0x56,0x34,0x12,
  0x5F,0xCF,0x13,0x25,0x41,0x64,0x6B,0xB8,
  0x1B,0xAA,0x16,0x58,0x0A,0xA0,0x30,0xC6,
  0xFD,0xC4,0x27,0xC4,0xA6,0x7C,0x14,0x63,
  0xA5,0x8E,0x51,0xCB,0x60,0xD2,0x0F,0x87,
  0xB2,0xD5,0x1A,0x6D,0x53,0xFA,0x37,0x26,0x80,0xDE,
  0x7C,0xE0,0x74,0xA0,0x0C,0x6E,0xD7,0xA2,0xE1,0x49
 }
    </props>
    <props name="challenges_array_length" type=DALPROP_ATTR_TYPE_UINT32>
        76
    </props>
  </device>
</driver>

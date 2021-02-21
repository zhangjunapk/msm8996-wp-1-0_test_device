# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/bsp/devcfg/build/IADAANAA/devconfig_data_dynamic.ld"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 175 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/bsp/devcfg/build/IADAANAA/devconfig_data_dynamic.ld" 2








# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/customer.h" 1
# 80 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/customer.h"
# 1 "./custiadaanaaa.h" 1
# 10 "./custiadaanaaa.h"
# 1 "./targiadaanaaa.h" 1
# 11 "./custiadaanaaa.h" 2
# 144 "./custiadaanaaa.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custremoteapis.h" 1
# 145 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custtarget.h" 1
# 146 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsdcc.h" 1
# 147 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsurf.h" 1
# 148 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custdiag.h" 1
# 149 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custefs.h" 1
# 150 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custpmic.h" 1
# 151 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsio_8660.h" 1
# 152 "./custiadaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsec.h" 1
# 121 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsec.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsfs.h" 1
# 122 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/custsec.h" 2
# 153 "./custiadaanaaa.h" 2
# 81 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/build/cust/customer.h" 2
# 10 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/bsp/devcfg/build/IADAANAA/devconfig_data_dynamic.ld" 2

PHDRS {
  DEVCFG_DATA_SEG_TZ PT_LOAD;
  DEVCFG_DATA_SEG_HYP PT_LOAD;
}
SECTIONS {

   DEVCFG_DATA_TZ ((0x80000000 + 0x062C0000 + 0x14000)):
   {
      KEEP(*\DevCfgSegInfo_tz_oem.o (.rodata* .data* .sdata*))
      KEEP(*\8996_data_tz_oem.o (.rodata* .data* .sdata*))
      KEEP(*\DALConfig_8996_tz_oem.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_BIMC_error_OEM_data.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_ABT_OEM_data.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_NOC_error_OEM_data.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_oem_data.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_pm_oem_config.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_pm_spmi_config.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_pm_ac_config.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_pm_tz_config.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_pm_config.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_pm_reg_dump_config.o (.rodata* .data* .sdata*))
      ASSERT(SIZEOF(DEVCFG_DATA_TZ) <= 0xA000, "Oversize");
   }:DEVCFG_DATA_SEG_TZ

   DEVCFG_DATA_HYP (0x85DFD000):
   {
      KEEP(*\DevCfgSegInfo_hyp_oem.o (.rodata* .data* .sdata))
      KEEP(*\8996_data_hyp_oem.o (.rodata* .data* .sdata*))
      KEEP(*\DALConfig_8996_hyp_oem.o (.rodata* .data* .sdata*))
      KEEP(*\8996_devcfg_pm_hyp_config.o (.rodata* .data* .sdata*))
      ASSERT(SIZEOF(DEVCFG_DATA_HYP) <= 0x3000, "Oversize");
     }:DEVCFG_DATA_SEG_HYP

  .got : { * (.got) }
  .got.plt : { * (.got.plt) }
  .debug 0 : { *(.debug) }
  .line 0 : { *(.line) }

  .debug_srcinfo 0 : { *(.debug_srcinfo) }
  .debug_sfnames 0 : { *(.debug_sfnames) }

  .debug_aranges 0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }

  .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_line 0 : { *(.debug_line) }
  .debug_frame 0 : { *(.debug_frame) }
  .debug_str 0 : { *(.debug_str) }
  .debug_loc 0 : { *(.debug_loc) }
  .debug_macinfo 0 : { *(.debug_macinfo) }

  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames 0 : { *(.debug_varnames) }

  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges 0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.ARM.exidx*) *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.init) *(.fini)}
}

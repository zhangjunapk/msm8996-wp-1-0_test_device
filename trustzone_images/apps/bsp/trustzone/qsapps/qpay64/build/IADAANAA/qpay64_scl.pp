# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/apps/securemsm/trustzone/qsapps/qpay64/build/qpay64.ld"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 178 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/apps/securemsm/trustzone/qsapps/qpay64/build/qpay64.ld" 2
PHDRS {
  CODE_RO PT_LOAD;
  DATA PT_LOAD;
  GOT PT_LOAD;
  REL_H PT_LOAD;
  REL_D PT_LOAD;
}

SECTIONS {
  .text : {
    KEEP(*\tzapp_entry.o (TZAPPENTRYCODE))
    * (.text .text.* kthread_shared)
    KEEP(*(tzapp_syscall_asm))
    * (.rodata)
    * (EXCLUDE_FILE(*\metadata.o) .rodata.*)
    *metadata.o (.rodata.str1.1)
  } : CODE_RO

  .sentinel : {
    * (.rodata.sentinel)
    ASSERT_FATAL(SIZEOF(.sentinel) != 0, "No sentinel section defined.");
  } : CODE_RO

  .metadata_check : {
    *metadata.o (.rodata.*)
    ASSERT_FATAL(SIZEOF(.metadata_check) == 0, "New metadata not accounted for here");
  } : CODE_RO

  .data ALIGN(4096): {
    * (.data TZAPPENTRYSTACK .bss COMMON)
  } : DATA

  .rel.text : {
    *(.rel.text)
  } : DATA
  .rel.rodata : {
    *(.rel.rodata)
  } : DATA
  .data.rel.ro.local : {
    *(.data.rel.ro.local)
  } : DATA
  .data.rel.ro : {
    *(.data.rel.ro)
  } : DATA
  .rel.data : {
    *(.rel.data)
  } : DATA
  .rel.plt : {
    *(.rel.plt)
  } : DATA
  .data.rel : {
    *(.data.rel)
  } : DATA
  .data.rel.local : {
    *(.data.rel.local)
  } : DATA

  TZ_APP_STACK : {
    Image$$TZ_APP_STACK$$ZI$$Base = .;
    . = . + 0x2000;
    Image$$TZ_APP_STACK$$ZI$$Limit = .;
  } : DATA
  TZ_APP_HEAP : {
    Image$$TZ_APP_HEAP$$ZI$$Base = .;
    . = . + 0x2800;
    Image$$TZ_APP_HEAP$$ZI$$Limit = .;
  } : DATA

  .got : ALIGN(4096) { *(.got.plt) *(.igot.plt) *(.got) *(.igot) } : GOT

  .dynamic : ALIGN(4096) { *(.dynamic) }: REL_H

  .rela.dyn : ALIGN(4096) {*(.rela.dyn)} : REL_D

  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.hash) *(.dynsym) *(.dynstr) *(.ARM.exidx*) *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.init) *(.fini) }
}

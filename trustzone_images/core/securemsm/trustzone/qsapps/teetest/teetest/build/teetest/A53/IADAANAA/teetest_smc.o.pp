# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsapps/teetest/teetest/src/teetest_smc.s"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 173 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/securemsm/trustzone/qsapps/teetest/teetest/src/teetest_smc.s" 2
;*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
; Copyright (c) 2015 by Qualcomm Technologies, Incorporated.All Rights Reserved.
;*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
  .global tee_ipc_return_from_inbound_asm
  .global tee_ipc_outbound_asm

;============================================================================
;
; MODULE CODE
;
;============================================================================
  .section TEE_SMC, "ax", %progbits
  .p2align 5
  .code 32

;======================================================
;tee_smc_xx(smc)
;======================================================
.type tee_ipc_return_from_inbound_asm, %function
.type tee_ipc_outbound_asm, %function
tee_ipc_return_from_inbound_asm:
tee_ipc_outbound_asm:
  push {r4-r5, r8}
  mov r8, r0
  ldr r0, [r8, #0x0]
  ldr r1, [r8, #0x4]
  ldr r2, [r8, #0x8]
  ldr r3, [r8, #0xc]
  ldr r4, [r8, #0x10]
  ldr r5, [r8, #0x14]
  smc #0
  str r0, [r8, #0x0]
  str r1, [r8, #0x4]
  str r2, [r8, #0x8]
  str r3, [r8, #0xc]
  str r4, [r8, #0x10]
  str r5, [r8, #0x14]
  mov r0, r8
  pop {r4-r5, r8}
  bx lr

  .end

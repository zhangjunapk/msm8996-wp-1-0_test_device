#line 1 "/local/mnt/workspace/CRMBuilds/BTFM.RM.2.2-00163-QCABTFMSWPZ-1_20161115_235757/b/btfm_proc/bt/build/ms/6174_rampatch.scl"

; The maxim size of the patch iamge in load view. 
; The RW/ZI section is right after this offset.
; We can increase this value if the real patch load size exceed this value. 


; 0x00019b08 and 0x00019b08 are set 
; by the target.scons script. They are PATCH_AREA 
; base addresses generated in the ROM building procedure.

RAMPATCH 0x00019b08 0x0000E000   
{
    EXEC_ENTRY  0x00019b08
    {
        ; patch_entry() function is the entry point of the patch space,
        ; so it should be placed exactly at the start of the patch area.
        ; ENTRY_POINT is set where patch_entry function is defined.
        rampatch_main.o (ENTRY_POINT, +FIRST)    ; Patch Entry point
    }

    EXEC_ENTITY  +0
    {
        *.o (+RO)           ; Patch Entity
    }
    
    ; SSRAM contains statically-allocated RAM
    PATCH_SSRAM (0x00019b08 + 0x0000E000) ALIGN 8
    {
        * (+RW, +ZI)        ; RW, ZI Section
    }
}

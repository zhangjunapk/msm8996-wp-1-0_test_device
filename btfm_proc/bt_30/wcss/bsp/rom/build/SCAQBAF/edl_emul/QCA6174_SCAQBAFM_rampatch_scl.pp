#line 1 "/local/mnt/workspace/CRMBuilds/BTFM.RM.2.2-00163-QCABTFMSWPZ-1_20161115_235757/b/btfm_proc/bt_30/build/ms/6174_rampatch.scl"
; Total Maximum Patch Size available for ROME 3.1
; All the +RO, +RW,sections of Patch needs to be under this value, 0x100 is signature length 0x04 for CRC calculation


; +RW, +ZI sections of Patch needs to be under this value. 


; The maxim size of the patch image in load view. 
; The RW/ZI section is right after this offset.
; We can increase this value if the real patch load size exceed this value. 



; 0x0001feb0 and 0x0001feb0 are set 
; by the target.scons script. They are PATCH_AREA 
; base addresses generated in the ROM building procedure.

RAMPATCH 0x0001feb0 (0x0010150 - 0x104)   
{
    EXEC_ENTRY  0x0001feb0
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
    ; Here, we put the RW, ZI section out of the patch region here, 
    ; reduce the upper heap size accordingly
    PATCH_SSRAM (0x0001feb0 - 0x2000) ALIGN 8
    {
        * (+RW, +ZI)        ; RW, ZI Section
    }
}

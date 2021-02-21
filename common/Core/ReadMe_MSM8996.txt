//====================================================================================================//
//================================ Meta-Scripts ReadMe.txt ===========================================//
//====================================================================================================//
//
//  Name:                                                                     
//    ReadMe_MSM8996.txt 
//
//  Description:                                                              
//    Basic script intro ReadMe.txt
//                                                                            
// Copyright (c) 2012 - 2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.        
//
//
//
//
//                      EDIT HISTORY FOR FILE
//  This section contains comments describing changes made to the module.
//  Notice that changes are listed in reverse chronological order.
//
// when       who             what, where, why
// --------   ---             ---------------------------------------------------------
// 01/18/2016 JBILLING        Update for load.cmm ramdump feature added.
// 10/22/2015 JBILLING        Added notes for CS release, and for change in peripheral debug due to Android M update
// 07/24/2015 JBILLING        Added notes for FC release, automation testing.
// 06/19/2015 JBILLING        Added notes for: plusvm and island_debug modes. TPIU re-enabled and peripheral CTI enabled with limitations.
// 05/20/2015 JBILLING        Created for 8996v2 


This document describes the following:
    - Release notes, limitations, fixes, Lauterbach T32 approved versions.
    - Basic instructions for using features available for JTag on Qualcomm MSM chipsets.
    
Release Notes
    Date: 01/18/2016
    Update for MSM8996
        Changes: Updates made to ramdump loader scripts to accept load.cmm as an option when ramdump files are
        unrecognized. Previously, filenames were hardcoded and ramdump loading would fail if those filenames weren't
        present. Now, if those filenames aren't present but load.cmm is present in ramdump folder, T32 will run load.cmm,
        and then try and restore context. This was mainly introduced for WP/Dexter tool.
    Date: 10/22/2015 
    Commercial Software for MSM8996
        Changes: Android M requires change in procedure when debugging peripheral processors (MPSS, ADSP, SLPI, MBA)
        Std_loadsim_apps has been updated to accomodate basic simulator loading as a basic alternative to HLOS ramdump parser.
    Date: 7/24/2015
    Feature Complete for MSM8996
        Changes: SSR dumps and Alternateelf enabled in std_loadsim. Automation testing support. Apps all-resume functionality enabled
        path to load_coredump.cmm fixed in t32 simulator (loadsim) routines (7/17/2015)
    Date: 5/29/2015
    Engineering sample 1 for MSM8996v2

    
    
Existing limitations
    std_debug
        - Computer OS is assumed to be windows at this time. 
        - IMPORTANT - Due to changes in Android M, the debug persist property, invoked by "adb wait-for-devices shell setprop persist.sys.ssr.enable_debug 1" 
          is no longer functional. Instead, VMLINUX ELF file must now be loaded on T32 Apps0 window in order to debug peripheral processors (MPSS,ADSP,SLPI,MBA)
          An additional prompt will appear asking for a VMLINUX file. Select the VMLINUX file which matches the boot.img file loaded onto the target. 
          If VMLINUX file and boot.img file mismatch, then Apps0 will not be able to halt at the appropriate breakpoint and set peripheral debug properties, hindering debug.
          ->  An alternative method has been given. If user does not know what boot.img is loaded or doesn't have access to VMLINUX file, deselect the 'Use Apps Symbols' Option
              on the debug menu, and CTI_Enable will be automatically added. This will allow debug at the entry breakpoint of the peripheral, and a basic system resume is 
              available, but due to Apps timeouts, the peripheral processor will likely be shut down after resume. It is recommended to use Apps Symbols at this time.
        - std_savelogs not available for any subsystems in this release
        - Peripheral processor CTI halt feature within std_debug is now functional *but* apps processors can not be resumed after the initial halt.
        - Hot-Attach buttons for SLPI have limited functionality. SSC subsystem must be online to get SSC Q6 awake. Enabling a listener should do this.
        - Hot-Attach Wake-And-Break button for MPSS has unstable functionality. Recommended to use hotattach "GO" and  then stop.
        - Some images require an ELF which is not available in external releases (XBL, TZ). Therefore std_debug won't work for those images.

    std_loadsim
        <-Changed with this release->: Updates made to ramdump loader scripts to accept load.cmm as an option when ramdump files are unrecognized. 
            Previously, filenames were hardcoded and ramdump loading would fail if those filenames weren't present. 
            Now, if those filenames aren't present but load.cmm is present in ramdump folder, T32 will run load.cmm,
            and then try and restore context. This was mainly introduced for WP/Dexter tool.
        - For command line functionality, user must do one of the following
            1. (Recommended) User must specify option 'alternateelf=<path\to\elf\file.elf'. For multi-elf subsystems (such as TZ,ADSP,SLPI), both elfs must be in the same directory.
            2. GLOBAL PRACTICE macros must be defined which gives path from buildroot to ELF file (such as &ADSP_ELF="adsp_proc\build\ms\M8996AAAAAAAL.ELF"
                and &ADSP_PD2_ELF="adsp_proc\build\ms\M8996AAAAAAAL_AUDIO.ELF". Each subsystem has its own expected macro. See corresponding
                std_loadsym_<subsystem> for further information.
        - QuRT has changed its pagetable structure. A recent version of T32 will be needed in order to parse it properly.
            - This change applies to ADSP in this ES release, and SLPI as well in the next
            - T32 version April 28th 2015, or Build number 62625 is the minimum version required for QURTV2 pagetable structure
            - Context loading will fail if the wrong T32 version is used.



Release 01/18/2016
Lauterbach Trace32 builds verified:
    ***Jan 19, 2015 (build 59765.)*** - No longer valid with ADSP simulator. See note in 'std_loadsim' section.
    May 19, 2015 (build 63096) - This is still the recommended build version and is the version used for all validation at this time

This document assumes the following:
    An up to date Lauterbach Trace32 license and (for live debugging) working JTag pod.
    Python 2.6 or later is installed and  available to system path
    MSM target is properly powered. In the case of using std_Debug scripts
        target has software and successfully boots to subsystem of choice.
    Trace32 is installed and computer is successfully connected to Trace32 pod
    Using Windows for computer OS.
    See chipset help pdf for further details
        
A note on T32 path
    All the scripts described are embedded into t32 path, so they do not require absolute accessing.
    I.E. a simple "do std_debug" will invoke the std_debug script. 
    It is not necessary to call it directly (i.e. "do common\std_debug.cmm" is not necessary)
        
Help menus
    Many of the scripts have help menus to describe functionality and usage. 
    These can be accessed in the following way
        do std_debug help
        do std_cti help
        do std_loadsim help
        do std_loadsyms_adsp help 
        do std_loadsyms_mpss help 
        do std_loadsyms_slpi help 
        do std_loadsyms_rpm help 
        
        
std_loadbuild
    This is primarily a GUI which allows loading the a build via JTag to the target.
    It has some other features such as individually swapping out images (such as tz or xbl based images)
    You can also set T32's paths for the different image builds here. Pressing the 'map' button
    will intercom to other open T32 windows to change their paths as well.
    Deviceprogrammer is for internal use only.
        
std_debug
    std_debug is a suite of scripts intended to facilitate JTag attach to the core of choice.
    There are two primary features within std_debug:
        std_debug boot up debug
            This is designed to get the user attached to desired subsystem with specified breakpoints and options.
            If 'main' is specified as breakpoint, the subsystem will halt at entry. Otherwise the subsystem
            will go immediately from main(), setting all error breakpoints, which preserves system sync
            This is offered through the primary GUI (obtained by typing 'do std_debug' in the APPS0 T32 window) or
            by command line (type 'do std_debug help' in the APPS0 T32 window for command line instructions)
            
            There is an option to enable JTag to be attached when SLPI is in island mode. This will keep on
            certain clocks (such as ddr, qdss) by voting for them from SLPI core software. If std_debug command line
            is invoked with extraoption=island_debug, then this variable will be set at main function of SLPI, resulting
            in island debug feature being enabled. Note that this is only available from command line at this time.
            e.g.: do std_debug Img=slpi Bkpts=some_brkpt extraoption=island_debug,silent
            
        hotattach menus
            These menus are present on most T32 windows and they offer live debug without needing to restart the system.
            Q6 based processors (ADSP,MPSS,SLPI) have functionality to wakeup, attach, set breakpoints, and start ETM tracing 
                without halting the processor
            APPS processors menus provide basic features to facilitate multicore debug. Entering commands in
                command area will apply desired command to all open Apps t32 windows (note that this GUI text box
                is simply an invocation of 'do std_apps <your_command>', which does the same thing). Using ELF load
                buttons from this menu will likewise load desired elf to all apps windows.
                Note that Cluster apps view is also useful for multicore apps debug, as it is Lauterbach's own implementation
                to debug all apps at once. Please note that not all features (such as some std_debug subsystems) work properly
                when using Apps cluster T32.
                
        Plusvm option has been added to all symbol loading scripts. This is invoked only via command line at this time, via the 'extraoption' option.
            Plusvm is intended for faster ETM trace processig (After a trace is captured, JTag searches DDR to correlate traces with actual memory.
            With Plusvm, ELF gets loaded onto JTag pod and so this second time consuming and invasive step doesn't have to be performed. 
            However, the ELF will take up room on the jtag pod and so tracing room can be limited.
            e.g.: do std_loadsyms_adsp NULL NULL NULL loadsecondelf NULL extraoption=plusvm,silent
                
        - Additional note: For Android targets, make sure to set the 'persist' bit via adb commands: "adb wait-for-devices shell setprop persist.sys.ssr.enable_debug 1"
          This will keep apps' Peripheral Image Loader (PIL) from timing out on peripheral subsystem when it's booting up. This is only needed if user 
          desires to break processor during its initialization. If this is not set, and user has set a breakpoint that occurs prior to when peripheral 
          processor sends ACK back to apps' PIL, you'll see peripheral processor get reset (T32 will show 'RES/PWR DWN' soon after halt).

std_loadsim
    std_loadsim is the suite of scripts designed to open a post-mortem T32 simulator session from a crash dump.
    GUI - the GUI will open automatically when opening a session. If you want to open another GUI, simply type 'do std_loadsim'
    Command line - command line options are available. For more information, type 'do std_loadsim help'
    
        
        
        
        
        
        
        
        
        
        
        

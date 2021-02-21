#===============================================================================
#
# Image Top-Level Build Script
#
# GENERAL DESCRIPTION
#    build script
#
# Copyright (c) 2009-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/scons.tz/1.0/build/scons/build/build.py#1 $
#  $DateTime: 2015/06/19 12:11:44 $
#  $Change: 8409094 $
#
#===============================================================================

#================================
# Import Python Libraries
#================================
import sys
import os
import time
from xml.etree import ElementTree as et

def delta_time (start, end):
   '''Calculate the delta between two times'''
   delta = end - start
   minutes = delta / 60
   seconds = delta % 60
   delta_str = "%d minutes, %d seconds" % (minutes, seconds)
   return delta_str

def build (*args):
   '''Parent script for QC-SCons Build System'''

   #================================
   # Get our bearings
   #================================

   on_linux          = sys.platform != 'win32'
   build_root        = os.path.realpath(os.path.join(os.path.dirname(__file__), "../../../.."))
   targ_root         = os.path.realpath(os.path.join(os.path.dirname(__file__), "../../../../.."))
   tools_root        = os.path.join(build_root, "tools")
   logger_root       = os.path.join(tools_root, "libs/logger")
   qcscons_root      = os.path.join(tools_root, "build/scons")
   qcscons_build_dir = os.path.join(qcscons_root, "build")
   qcscons_cmd       = os.path.realpath(os.path.join(qcscons_root, "SCons/scons"))
   if not on_linux:
      qcscons_cmd += '.bat'
   qcscons_script    = os.path.realpath(os.path.join(qcscons_root, "build/start.scons"))

   lg = None
   try:
      #================================
      # Initialize logging
      #================================

      sys.path.append(logger_root)
      import logger
      lg = logger.Logger('build')
   
      lg.log("#-------------------------------------------------------------------------------")
      lg.log("# BUILD START")
      lg.log("#-------------------------------------------------------------------------------")
      start_time = time.time()
      lg.log("Start Time: " + time.ctime(start_time))
      lg.log("Running $Header: //components/rel/scons.tz/1.0/build/scons/build/build.py#1 $")
   
      #================================
      # Import Image-Specific Configuration Information
      #================================
      #==========================================
      # Retrieve image values for build parameters
      # (This will be pulled from a config file later)
      #==========================================
   
      # Read data from config file:
      XmlImageCfg = et.ElementTree(file = "image_cfg.xml").getroot()
   
      # Read build flags
      lg.log("Reading Image Config")
      lg.log("  Build Flags:")
      build_flags = dict()
      for child in XmlImageCfg.find('build_flags').getchildren():
         bf_name = child.tag.upper()
         bf_val  = child.text
         lg.log("    " + bf_name + " = " + bf_val)
         if bf_val:
            bf_val = bf_val.strip()
         if bf_name == 'BUILD_ID':
            build_id_list = bf_val.split(',')
         elif bf_name == 'COMPILER_ID':
            compiler_id = bf_val
         else:
            build_flags[bf_name] = bf_val
   
      # Read environment variable settings
      lg.log("  Environment Variables:")
      for child in XmlImageCfg.find('env_vars').getchildren():
         var_name  = child.find('var_name').text
         if var_name:
            var_name = var_name.strip()
         var_value = child.find('var_value').text
         if var_value:
            var_value = var_value.strip()
         lg.log("    " + var_name + " = " + var_value)
         os.environ[var_name] = var_value
   
      #================================
      # Setup environment variables that SCons needs
      #================================
   
      os.environ["BUILD_ROOT"]  = build_root
      os.environ["TARGET_ROOT"] = targ_root
   
      #================================
      # Hacks for backward-compatibility
      #================================
      # At least one tool accesses MSM_ID from os.environ, rather than the SCons
      # environment, so we need to add this there:
      os.environ['MSM_ID'] = build_flags['MSM_ID']
   
      #================================
      # Load OEM top-level build script, if available
      #================================
      if 'SCONS_BUILD_SCRIPTS_OEM_ROOT' in os.environ:
         oem_root = os.environ['SCONS_BUILD_SCRIPTS_OEM_ROOT']
         if os.path.exists(os.path.join(oem_root, 'build_oem.py')):
            sys.path.append(oem_root)
            import build_oem
   
      #================================
      # Import local build environment settings, if available
      #================================
      if on_linux:
         setenv = os.path.join(qcscons_build_dir, 'setenv.sh')
      else:
         setenv = os.path.realpath(os.path.join(qcscons_build_dir, 'setenv.cmd'))
      if os.path.exists(setenv):
         lg.log("Running setenv")
         new_env = lg.log_exec([setenv, compiler_id], capture_output=True)[1]
         new_env = [x.strip() for x in new_env.split('\n')]
         setenv_dict = {}
         for setting in new_env:
            if '=' in setting:
               var, value = setting.split('=', 1)
               setenv_dict[var] = value
      else:
         setenv_dict = os.environ
      
      #================================
      # Log the environment settings
      #================================
      lg.log("#-------------------------------------------------------------------------------")
      lg.log("# ENVIRONMENT BEGIN")
      lg.log("#-------------------------------------------------------------------------------")
      env_vars = setenv_dict.keys()
      env_vars.sort()
      for var in env_vars:
         lg.log(var + " = " + setenv_dict[var])
      lg.log("#-------------------------------------------------------------------------------")
      lg.log("# ENVIRONMENT END")
      lg.log("#-------------------------------------------------------------------------------")
   
      #================================
      # Parse Build IDs from command line parameters
      # Multiple Build IDs can be specified with the syntax:
      #      BUILD_ID=bid1,bid2,...
      #================================
      cleaned_args  = []
      for arg in args:
         if arg.startswith("BUILD_ID="):
            # Let command line override list from image_cfg.xml
            build_id_list = arg[9:].split(',')
         else:
            # All other args are passed through to QC-SCons
            cleaned_args.append(arg)
   
      #================================
      # Call QC-SCons
      #================================
      
      ret = 1  # Fail if no build_ids specified
      build_time_log = dict()
      for bid in build_id_list:
         build_cmd_line = [qcscons_cmd, "-f", qcscons_script, "BUILD_ID=" + bid]
         build_cmd_line += [key + "=" + build_flags[key] for key in sorted(build_flags.keys())]
         build_cmd_line += cleaned_args
         lg.log("#-------------------------------------------------------------------------------")
         lg.log("# BUILD BEGIN: " + bid)
         lg.log("#-------------------------------------------------------------------------------")
         build_time_log[bid] = [time.time()]  # Remember the start time.
         ret = lg.log_exec(build_cmd_line, env=setenv_dict)
         build_time_log[bid].append(time.time())  # Remember the end time.
         lg.log("#-------------------------------------------------------------------------------")
         lg.log("# BUILD END: " + bid)
         lg.log("#-------------------------------------------------------------------------------")
         if ret != 0:
            break
   
      end_time = time.time()
   
      # Report build times
      for bid in build_id_list:
         build_start_time = build_time_log[bid][0]
         build_end_time   = build_time_log[bid][1]
         lg.log("Build " + bid + ": Start Time: " + time.ctime(build_start_time) + ",  End Time: " + time.ctime(build_end_time))
         lg.log("Build " + bid + ": Delta Time: " + delta_time(build_start_time, build_end_time))
         lg.log("#-------------------------------------------------------------------------------")
      lg.log("Overall Start Time: " + time.ctime(start_time) + ",  Overall End Time: " + time.ctime(end_time))
      lg.log("Overall Delta Time: " + delta_time(start_time, end_time))
      lg.log("#-------------------------------------------------------------------------------")
      return ret
   except:
      # Log any crashes to the log file
      if lg:
         lg.log_crash()
      raise
   finally:
      if lg:
         del lg


# Allow this script to be called from the OS command shell,
# or from another Python script.
if __name__ == "__main__":
   ret = build(*tuple(sys.argv[1:]))
   sys.exit(ret)

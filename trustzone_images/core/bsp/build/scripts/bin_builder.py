#===============================================================================
#
# BIN file builder
#
# GENERAL DESCRIPTION
#    build rules script
#
# Copyright (c) 2009-2009 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/core.tz/1.0.3.c1/bsp/build/scripts/bin_builder.py#1 $
#  $DateTime: 2016/12/02 01:46:26 $
#  $Author: pwbldsvc $
#  $Change: 11896995 $
#                      EDIT HISTORY FOR FILE
#                      
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#  
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
#
#===============================================================================
import os
import subprocess
import string
import re
import shutil


#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('bin_builder')

def generate(env):
   bin_generate(env)

#===============================================================================
# PBN build rules
#===============================================================================
def bin_generate(env):
   #-------------------------------------------------------------------------------
   # def builder for PBN
   #
   bin_act = env.GetBuilderAction(bin_builder)
   bin_bld = env.Builder(action = bin_act,
                         suffix = '.bin')

   env.Append(BUILDERS = {'BinBuilder' : bin_bld})

#-------------------------------------------------------------------------------
# Emitter builder to add clean actions
#
def bin_emitter(target, source, env):
   # here one can also add dependencies for say aexe.exe (if it needs to be build)
   # env.Depends(target, propgen_tool)
   return (target, source)

#-------------------------------------------------------------------------------
# def builder for qcoreapp_booting.pbn
#
def bin_builder(target, source, env):
   # init and fix variebles
   source_str = os.path.abspath(str(source[0]))
   target_str = os.path.abspath(str(target[0]))
   target_tmp = target_str+'.tmp'

   cmds = ["$BINTOOL ${ARMBIN_BIN_CMD}"  + " " + source_str + " " + "${ARMBIN_OUTPUT_CMD} " + target_tmp ]

   data, err, rv = env.RunCmds(target, source, cmds)
   
  
   # chcek to see if bintool generated a folder if so, then extra steps are needed
   if os.path.isdir(target_tmp):
      shutil.copy (target_tmp + '/CODE', target_str)
      #for file in os.listdir(target_tmp):
      #   file_path = os.path.join(target_tmp, file)
      #   if os.path.isfile(file_path):
      #      os.unlink(file_path)
               
      #os.rmdir(target_tmp)
   else:
      os.rename(target_tmp, target_str) 
   
   return None
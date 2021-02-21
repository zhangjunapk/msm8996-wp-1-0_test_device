#============================================================================
#
# CBSP Builders build rules
#
# GENERAL DESCRIPTION
#    Contains builder(s) to build a Secure App 
#
# Copyright 2015 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#  $Header: //components/rel/core.tz/1.0.3.c1/bsp/build/scripts/get_dependency_builder.py#1 $
#  $DateTime: 2016/12/02 01:46:26 $
#  $Author: pwbldsvc $
#  $Change: 11896995 $
#
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who       what, where, why
# --------   ---       ------------------------------------------------------
# 
#============================================================================
import os

#----------------------------------------------------------------------------
# Global values
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Hooks for Scons
#----------------------------------------------------------------------------
def exists(env):
  return env.Detect('get_dependency_builder')

def generate(env):
  get_dependency(env)

#============================================================================
# Add the Dependency Builder
#============================================================================
def get_dependency(env):
  env.AddMethod(get_dependency_builder, "GetDependency")

def get_dependency_builder(env):

  env = env.Clone()
  for path in env['CPPPATH']:
    if 'apps' in path:
      env['CPPPATH'].remove(path)
  for flag in env['CPPDEFINES']:
    if '_DEBUG' in flag:
      env['CPPDEFINES'].remove(flag)
  libs = list()
  objs = list()

  clibs, cobjs = env.LoadAUSoftwareUnits('core')
  libs.extend(clibs)
  objs.extend(cobjs)

  alibs, aobjs = env.LoadAUSoftwareUnits('apps')
  libs.extend(alibs)  
  objs.extend(aobjs)

  return (libs, objs)

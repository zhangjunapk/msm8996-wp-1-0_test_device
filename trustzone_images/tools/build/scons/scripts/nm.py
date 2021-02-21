#===============================================================================
#
# CoreBSP Symbol Extract
#
# GENERAL DESCRIPTION
#    extract and formot symbols like the followign Linux command:
#              awk  \'/ [DBT] /{print $3,"=","0x"$1,";";}
#
# Copyright (c) 2009-2010 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/scons.tz/1.0/build/scons/scripts/nm.py#2 $
#  $DateTime: 2015/08/07 19:32:02 $
#  $Author: pwbldsvc $
#  $Change: 8770880 $
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 05/01/10   weimingz      Create
#
#===============================================================================
import os
import re
import sys
from optparse import OptionParser

#------------------------------------------------------------------------------
# Parse command line arguments
#------------------------------------------------------------------------------
def parse_args():
   usage = "usage: %prog [options]"
   version = "%prog 1.0"

   parser = OptionParser(usage=usage, version=version)
   parser.add_option("-f", "--ppfile", dest="pp_filename",
                  help="Read input symbol from FILE", metavar="FILE")
   parser.add_option("-o", "--outfile", dest="output_filename",
                  help="Write output to FILE", metavar="FILE")

   (options, args) = parser.parse_args()

   if options.pp_filename is None:
      parser.error("-f option must be defined")
      sys.exit(2)


   return (options, args)

#------------------------------------------------------------------------------
# main
#------------------------------------------------------------------------------
def main():
   # get args from cmd line
   (options, args) = parse_args()
   file = open(options.pp_filename, 'r')
   data = file.readlines()
   file.close()

   if options.output_filename is None:
      file = sys.stdout
   else:
      file = open(options.output_filename, 'w')

   for line in data:
         fields = line.split()
         if len(fields) == 3 and (fields[1] == 'D' or fields[1] == 'B' or fields[1] == 'T') :
           if fields[2] == "memcpy" or fields[2] == "memset":
             continue
           str = fields[2] + ' = ' + '0x' + fields[0] + ' ;\n'
           file.write(str)

   file.close()

main()

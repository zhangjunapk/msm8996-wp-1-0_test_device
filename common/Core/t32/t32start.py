#===============================================================================
#
# t32start.py
#
# GENERAL DESCRIPTION
#    T32 startup script for windows
#
# Copyright (c) 2011-2012 by QUALCOMM Technologies Incorporated.
# All Rights Reserved.
#
# QUALCOMM Proprietary
#
#-------------------------------------------------------------------------------
#
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who         what, where, why
# --------   ---         ---------------------------------------------------------
# 08/03/2015 JBILLING     Update for linux, path fixes
# 08/10/2014 AJCheriyan   Created v1.0 for Elessar
#==============================================================================

import glob, itertools, os, string, sys, subprocess, re, platform, shutil, fnmatch, time, tempfile
from optparse import OptionParser

# Function to terminate program with a message
def debug(msg, force=False):
    debug_enable = False
    if debug_enable or force:
        print msg

def kill(msg):
    if msg:
        print msg
    sys.exit(1)

def IsWindows64():
    command = 'WMIC OS GET OSARCHITECTURE /Format:list'
    getosarch = subprocess.Popen(command, stderr = subprocess.PIPE, stdout = subprocess.PIPE)
    (cmdout, cmderr) = getosarch.communicate()
    #print 'Detecting Windows arch : ' + cmdout.strip()

    if cmdout.strip().endswith('64-bit'):
        debug('Detected 64 bit Windows')
        return True

def IsLinux64():
  return True

# Function to parse input options
def parseoptions():
    global options
    argparser = OptionParser(version='%prog 1.0')

    argparser.add_option('-t', '--target', dest='targetname', help='Name of the target: e.g. msm8994', metavar='NAME', default=None)
    argparser.add_option('-s', '--session', dest='session', help='Trace32 window to be opened e.g. RPM', metavar='SESS', default=None)

    (options, args) = argparser.parse_args()

    # Ask for input if not provided
    configs = glob.glob('./*.ts2')
    if (len(configs) > 1):
        options.targetname = raw_input("Enter Target Name: ")
    else:
        (options.targetname, ext) = os.path.splitext(os.path.basename(configs[0]))


    #if not options.session:
    #    options.session = raw_input("Enter Session Name: ")

    # Convert our  sessions to a list
    options.session = options.session.split(',') if options.session else options.session
    debug("Selected target: " + str(options.targetname), True)
    debug("Selected session: " + str(options.session), True)

def start32():
    if platform.system() != 'Linux':
        # File which needs to be created
        cmmfilename = 'gen_buildinfo.cmm'
        tmpfile = tempfile.gettempdir() + os.sep + cmmfilename
        cmd = ' '.join(['python', os.path.join('..','..', 'build', 'app', 'gen_cmm_data3.py ', os.path.join('..', '..', '..')), tmpfile, ' -paths_only'])

        debug('Temp filename: ' + tmpfile)
        debug('Current Working Dir: ' + os.getcwd())
        debug('Generate MetaBuild Information: ' + cmd)

        # Make the call to generate the cmm script
        genfilecall = subprocess.Popen(cmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        (stdout, stderr) = genfilecall.communicate()

        # Set the additional environment variables
        # Set T32 start directory
        t32dir = ''
        if os.path.isdir('C:\T32'):
            t32dir = 'C:\T32'
        else:
            t32dir = raw_input('Enter the location of the T32 installation: ')



        # Set the location of the T32 installation
        os.environ['T32SYS'] = t32dir
        os.environ['SCRIPTSDIR'] = os.path.join(os.getcwd(), '..', 'tools', 'cmm')


        # Now start T32
        windows_ver = 'windows'
        if IsWindows64():
            windows_ver = 'windows64'

        # Find the version of the exe to execute
        t32exe = os.path.join(t32dir,'bin', windows_ver, 't32start.exe')
        if not os.path.isfile(t32exe):
            kill('T32start executable not found at : ' + t32exe)

        # Put together the command
        t32startcmd = ' '.join([ t32exe, '-runcfgfile', options.targetname + '.ts2'])

        # Adjust now
        if (options.session) and ('all' not in options.session ):
            for session in options.session:
                t32finalcmd = t32startcmd + ' -runitem \"//Root/DAP/Podbus Device Chain/Power Trace Ethernet/' + session + '\" -QUIT'
                debug("Trace32 start command is : " + t32finalcmd, True)
                subprocess.Popen(t32finalcmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE).communicate()
                time.sleep(5)
        else:
            subprocess.Popen(t32startcmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE)


    else:
        print "Detected running on Linux."
        # File which needs to be created
        cmmfilename = 'gen_buildinfo.cmm'
        tmpfile = tempfile.gettempdir() + os.sep + cmmfilename

        print(os.getcwd())

        cmd = ' '.join(['python', os.path.join('..', '..', 'build', 'app', 'gen_cmm_data3.py ', os.path.join('..', '..', '..')), tmpfile, ' -paths_only'])

        print "cmd :" 
        print cmd

        debug('Temp filename: ' + tmpfile)
        debug('Current Working Dir: ' + os.getcwd())
        debug('Generate MetaBuild Information: ' + cmd)

        # Make the call to generate the cmm script
        #genfilecall = subprocess.Popen(cmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        #(stdout, stderr) = genfilecall.communicate()

        #call cmd
        # Set the additional environment variables
        # Set T32 start directory
        t32dir = ''
        t32dir = os.environ['T32SYS']

        if os.path.isdir(t32dir):
            t32dir = t32dir
        else:
            t32dir = raw_input('Enter the location of the T32 installation: ')

        # Set the location of the T32 installation
        os.environ['SCRIPTSDIR'] = os.path.join(os.getcwd(), '..', 'tools', 'cmm')

        # Now start T32
        linux_ver = 'pc_linux'
        if IsLinux64():
            linux_ver = 'pc_linux64'

        # Find the version of the exe to execute
        t32exe = os.path.join(t32dir,'bin', linux_ver, 't32marm64-qt')
        if not os.path.isfile(t32exe):
            kill('T32start executable not found at : ' + t32exe)

        print "Detected running on Linux, ready to start t32."
        
        #Get absolute path of startup.cmm
        current_dir = os.path.dirname(os.path.realpath(__file__))
        start_up = os.path.join('..', 'tools', 'cmm', 'config', 'startup.cmm')
        start_up = os.path.join(current_dir, start_up)

        os.chdir(os.path.join('..', 'tools', 'cmm'))

        subprocess.call([t32exe, "-c", tempfile.gettempdir()+os.sep+options.targetname.upper()+"_APPS0.t32, ", start_up, "DAP", options.targetname.upper() , "APPS 0 SWD"])


# @Description
#
#   Main meat of the program
#

if __name__ == '__main__':

    parseoptions()

    start32()






#============================================================================
#
# CBSP Builders build rules
#
# GENERAL DESCRIPTION
#    Contains builder(s) to build a Secure App 
#
# Copyright 2015,2016 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#  $Header: //components/rel/core.tz/1.0.3.c1/bsp/build/scripts/secure_app_builder.py#1 $
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
  
  return env.Detect('secure_app_builder')

def generate(env):
  secure_app_generate(env)

#============================================================================
# Add the Secure App Builder to the environment. Also Load other builders
# that are needed for secure app compilation via LoadToolScript helper. 
#============================================================================
def secure_app_generate(env):
  env.AddMethod(secure_app_builder, "SecureAppBuilder")
  env.AddMethod(get_object_file_name, "GetObjectFileName")
  env.AddMethod(secure_app_lib_builder, "SecureAppLibBuilder")
  tools = [
    # load the llvm builder
    '${BUILD_ROOT}/tools/build/scons/scripts/llvm.py',
    # load the builder to add cust_h and other ASM_DFLAGS and CC_DFLAGS
    '${BUILD_ROOT}/tools/build/scons/scripts/apps_defs.py',
    # the builder to help sign the secure app image
    '${BUILD_ROOT}/tools/build/scons/sectools/sectools_builder.py',
    # the builder to generate mbn image
    '${BUILD_ROOT}/core/bsp/build/scripts/mbn_builder.py',
    # the builder to get the objects and libraries the app depends on
    '${BUILD_ROOT}/core/bsp/build/scripts/get_dependency_builder.py',
    # the builder that generate the scatter loader file to generate an image map to be used by linker
    '${BUILD_ROOT}/core/bsp/build/scripts/scl_builder.py',
    # the builder that creates multiple files from the image file 
    '${BUILD_ROOT}/core/bsp/build/scripts/pil_splitter_builder.py',
    # the builder that generates the metadata.c file and add privileges as defined in metadata dictionary
    '${BUILD_ROOT}/core/bsp/build/scripts/secure_apps.py',
    # the builder that affects formatting and also has buildspec rules for klocwork
    '${BUILD_ROOT}/tools/build/scons/scripts/buildspec_builder.py'
  ]
# The tools get loaded as part of init_build_config. Loading them here could cause 
# a race condition where these tools get loaded prior to init_build_config and may thus
# miss some of the env variables populated like the USES_* variables. MBN builder does 
# reference USES_MBN* variables that get populated in init_build_config
  env.Replace(IMAGE_TOOLS = tools)

#============================================================================
# secure_app_builder:
# this builder takes in the list of source files, include file paths,
# the metadata dictionary and the desired image name to build the 
# secure application. The builder takes key word arguments as optional
# parameters. The key word arguments currently processed are: 
# stack_size, heap_size, sec_xml_config, user_libs 
# The Node object of the final builder is returned
# back so that the caller can add it as a dependency if needed.
#============================================================================
def secure_app_builder(env, sources, includes, metadata, image, **kwargs):
  env = env.Clone()

  if 'stack_size' in kwargs and kwargs['stack_size']:
    env['APP_STACK_SIZE'] = kwargs['stack_size']

  if 'heap_size' in kwargs and kwargs['heap_size']:
    env['APP_HEAP_SIZE'] = kwargs['heap_size']

  if 'sec_xml_config' in kwargs and kwargs['sec_xml_config']:
    env['SECIMAGE_XML_CONFIG'] = kwargs['sec_xml_config']

  env.Append(CPPPATH = includes)
  env.Append(CPPPATH = ['#../../core/api/services/',
                        '#../../core/securemsm/trustzone/qsee/mink/include/',
                        '#../../core/securemsm/secrsa/shared/inc',
                        '#../../core/api/securemsm/trustzone/qsee/',
                        '#../../core/securemsm/accesscontrol/api/',
                        '#../../core/securemsm/trustzone/qsee/include/',
                        '#../../core/securemsm/trustzone/qsapps/libs/applib/common_applib/inc',]
            )

  env.Replace(APP_IMAGE_NAME = image)
  env.Append(CFLAGS = '-fPIC')
  env.Append(CFLAGS = '-Werror')
  env.Append(LINKFLAGS = "-shared -Bsymbolic")

  #The app scons environment is expected to define the OUT_DIR path
  buildPath = env.subst('${OUT_DIR}/' + '${SHORT_BUILDPATH}/' + image)

  #Generate the metadata.c file 
  metadataObject = env.AddSecureAppMetadata(metadata)

  #compile sources to objects first, so we can control where the .o files end up at
  sobjects = compile_sources(env, buildPath, sources)

  #Get Dependencies
  libs, objs = env.GetDependency()
  sobjects.extend(objs)

  gp_app_list = ['gptest', 'gptest2', 'gpsample', 'ttaari1', 'ttacapi1', 'ttacapi2', 'ttacapi3', 'ttacapi4', 'ttacapi5',
                 'ttacrp1', 'ttads1', 'ttatcf1', 'ttatcf2', 'ttatcf3', 'ttatcf4', 'ttatcf5', 'ttatime1' ]
  #Add SCL file
  if image in gp_app_list:
    scl =  env.SclBuilder(buildPath,
                         '${BUILD_ROOT}/core/bsp/build/scripts/gpapp.ld')
  elif image == 'tbase':
    scl = env.SclBuilder(buildPath,
                         '${BUILD_ROOT}/core/securemsm/trustzone/qsapps/tbase/tbase310a/tbase/build/tbase.ld')
  elif image == 'teetest':
    scl = env.SclBuilder(buildPath, 
                         '${BUILD_ROOT}/core/securemsm/trustzone/qsapps/teetest/teetest/build/teetest.ld')
  else:
    if env['PROC'] == 'scorpion':
      scl = env.SclBuilder(buildPath,
                           '${BUILD_ROOT}/core/bsp/build/scripts/secureapp.ld')
    else:
      scl = env.SclBuilder(buildPath,
                           '${BUILD_ROOT}/core/bsp/build/scripts/secureapp64.ld')

  # get the libs for 32 bit or 64 bit based on PROC. scorpion => 32 bit
  if env['PROC'] == 'scorpion':
    libca = env.SubstRealPath('${MUSL32PATH}/lib/libc.a')
  else:
    libca= env.SubstRealPath('${MUSLPATH}/lib/libc.a')
  # only libc.a has a different lib for 32 bit vs 64 bit. The libclang_rt.builtins-arm.a
  # is common for both architectures.
  arm_libs = [
    env.File(libca),
    env.File(env.SubstRealPath('${LLVMLIB}/libclang_rt.builtins-arm.a')),
  ]

  libs.extend(arm_libs)
  if 'user_libs' in kwargs and kwargs['user_libs']:
    libs.extend(kwargs['user_libs']) 

  libs_path = env['INSTALL_LIBPATH']
  # ELF
  elf = env.Program( buildPath,
                     source=[sobjects, metadataObject],
                     LIBS=[libs], LIBPATH=libs_path
                   )
  env.Depends(elf, scl)

  image_map = env.subst(buildPath + '.map')
  image_sym = env.subst(buildPath + '.sym')

  env.Clean(elf, image_map)
  env.Clean(elf, image_sym)
  env.Clean(elf, metadataObject)
  
  pbn = env.InstallAs(buildPath + ".pbn", elf)
  env.Depends(pbn,elf)

  install_root = env.subst('${MBN_ROOT}')
  install_unsigned_root = env.SectoolGetUnsignedInstallPath(install_base_dir = install_root)
  env.Replace(MBN_FILE = os.path.join(install_unsigned_root, image))

  mbn = env.MbnBuilder( buildPath,
                        pbn, IMAGE_TYPE=image, MBN_TYPE="elf",
                        IMAGE_ID=4, FLASH_TYPE="sdcc")

  env.Depends(mbn, pbn)
  #----------------------------------------------------------------------------
  # Sectools signing
  #----------------------------------------------------------------------------
  default_config = env.subst('${BUILD_ROOT}/apps/bsp/trustzone/qsapps/build/secimage.xml')
  secimage_xml_config = env.get('SECIMAGE_XML_CONFIG', default_config)
  
  pil_base_dir = '${BUILD_ROOT}/build/ms/bin/PIL_IMAGES/SPLITBINS_${QC_SHORT_BUILDPATH}'
  sectools_signed_mbn = env.SectoolBuilder(
                            target_base_dir = '${OUT_DIR}/' + '${SHORT_BUILDPATH}',
                            source= mbn,
                            sign_id=image,
                            msmid = env.subst('${MSM_ID}'),
                            sectools_install_base_dir = install_root,
                            install_file_name = image + ".mbn",
                            config=secimage_xml_config,
                            pilsplitter_target_base_dir=pil_base_dir
                        )

  env.Depends(sectools_signed_mbn, mbn)
  #-------------------------------------------------------------------------
  # Build files for PIL driver
  #-------------------------------------------------------------------------
  unsigned_pil_dir = env.SectoolGetUnsignedInstallPath(install_base_dir = pil_base_dir)
  pil = env.PilSplitterBuilder(os.path.join(unsigned_pil_dir, image + '.mdt'), mbn)

  env.Depends(pil, sectools_signed_mbn)
  return pil

def get_object_file_name(env, spath):
  #source files can be of the form a.c, ../x/a.c, b/a.c.
  #in each of above cases, we want objects to be stored as
  #a.o, x/a.o, b/a.o
  if isinstance(spath, str):
    sstr = spath
  elif isinstance(spath, list):
    print 'Error: get_object_file_name does not process list!! %s' % (str(spath))
    exit(1)
  else:
    spath_str = spath.path
    sstr = spath_str.split(env.subst('${SRC_SCONS_ROOT}'))[-1]
    if sstr == spath_str :
      # scons root is not in the path, so try to split at image
      # name if it is there in the path to get relative paths
      if 'APP_IMAGE_NAME' in env and \
           env['APP_IMAGE_NAME'] and \
           env.subst('${APP_IMAGE_NAME}') in spath_str:
        sstr = spath_str.split(env.subst('${APP_IMAGE_NAME}'))[-1]
      else:
        # no easy way to split the path to get relative source paths
        # break down at the BUILD_ROOT, so objects are stored with relative
        # paths from root under the objects directory in output
        sstr = spath_str.split(env.subst('${BUILD_ROOT}'))[-1]
  name, extension = os.path.splitext(sstr)
  #print 'Returning name and extension = %s %s from get_object_file_name' % (name, extension)
  return (sstr.split('../')[-1].split('.')[0], extension)


def secure_app_lib_builder(env, includes, sources, libname):
  env.Replace(LIBNAME = libname.upper())
  env.Append(CFLAGS = '-fPIC')
  env.Append(CPPPATH = includes)

  install_dir = env.subst('${LIB_OUT_DIR}')
  objlist = compile_sources(env, install_dir, sources)
  lib = env.Library(install_dir + '/' + libname, objlist)
  return lib

def flatten_list (origlist, newlist):
  for i in origlist:
    if isinstance(i, str):
      newlist.append(i)
    else:
      flatten_list(i, newlist)
    
def compile_sources(env, dest_dir, sources):
  sobjects = []
  for s in sources:
   if isinstance(s, list):
     sflatten = []
     flatten_list(s, sflatten)
     for p in sflatten:
       objname, extension = get_object_file_name(env,p)
       if extension.lower() == '.o':
         sobjects.append(p)
       else:
         o = env.Object(dest_dir + '/objects/' + objname, p)
         sobjects.append(o)
   else:
     objname, extension = get_object_file_name(env, s)
     if extension.lower() == '.o':
       sobjects.append(s)
     else:
       o = env.Object(dest_dir + '/objects/' + objname , s)
       sobjects.append(o)

  return sobjects

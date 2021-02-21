#==============================================================================
# SCONS Tool for Target-Specific Build Parameters.
#
# Copyright (c) 2012-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#==============================================================================
#==============================================================================
#
#                        EDIT HISTORY FOR MODULE
#
# $Header: //components/rel/core.tz/1.0.3.c1/bsp/build/tbc_core_devcfg.py#1 $
#
# when       who    what, where, why
# -------    ---    -------------------------------------------
# 08/14/12   aa   Initial Revision
#==============================================================================
import xml.dom.minidom
import unicodedata

def get_devcfg_xml_tags(env, xml_file):
   '''
   Get the devcfg tags that the clients need to use to pass in the xml information
   for different configurations by reading it from build\ms\image_cfg.xml
   '''
   xml_file = env.RealPath(xml_file)
   # parse the xml file
   image_cfg_tag = xml.dom.minidom.parse(xml_file)
   # Get the devcfg_info elements
   devcfginfotags = image_cfg_tag.getElementsByTagName("devcfg_info")
   # Get devcfg_xml_tag's elements, which has the xml tags in it that is required here
   rootenv = env.get('IMAGE_ENV')
   if rootenv.GetUsesFlag('USES_DEVCFG_MULTIPLE_CONFIG') is True:
     devcfgxmlelems = devcfginfotags[0].getElementsByTagName("devcfg_xml_tag_multiple_configs")
   else:
     devcfgxmlelems = devcfginfotags[0].getElementsByTagName("devcfg_xml_tag_single_configs")
   # This will have only one child of devcfg_xml_tag type. It returns a unicode type data
   udata = devcfgxmlelems[0].firstChild.data
   # Convert it to string
   devcfg_xml_tags = unicodedata.normalize('NFKD', udata).encode('ascii','ignore')
   # Remove any \t, \n in the string and split it with demiliter ',' to give a list of the tags
   devcfg_xml_tag_list = (devcfg_xml_tags.replace('\t', '').replace('\n', '')).split(',')
   # Remove any spaces in the list elements
   devcfg_xml_tag_list = [word.strip() for word in devcfg_xml_tag_list]
   
   #import pdb;pdb.set_trace()
   # Get chipinfo(family number, device number) for all exposed tags, the values are defined in ipcat
   # description for TCSR_SOC_HW_VERSION register for all supported chipset in a family
   devcfgchipelems = devcfginfotags[0].getElementsByTagName("soc_hw_version")
   soc_data = devcfgchipelems[0].firstChild.data
   devcfg_soc_tags = unicodedata.normalize('NFKD', soc_data).encode('ascii','ignore')
   devcfg_soc_tag_list = (devcfg_soc_tags.replace('\t', '').replace('\n', '')).split(',')
   devcfg_soc_tag_list = [word.strip() for word in devcfg_soc_tag_list]
   devcfg_soc_tag_dict = {}
   for element in devcfg_soc_tag_list :
      val = element.split(':')
      devcfg_soc_tag_dict.setdefault(val[0].strip(),[]).append(val[1].strip())
   
   #Get the TCSR_SOC_HW_VERSION ADDRESS, the value is defined in ipcat and is fixed for a family
   tcsr_hw_version_addr_node = devcfginfotags[0].getElementsByTagName("tcsr_soc_hw_version_addr")
   tcsr_hw_version_addr = tcsr_hw_version_addr_node[0].firstChild.data
   tcsr_hw_version_addr = unicodedata.normalize('NFKD', tcsr_hw_version_addr).encode('ascii','ignore')
   tcsr_hw_version_addr = tcsr_hw_version_addr.strip()
   return devcfg_xml_tag_list, devcfg_soc_tag_dict, tcsr_hw_version_addr

def generate(env):
   #---------------------------------------------------------------------------
   # Add Device Configuration specific defines
   #---------------------------------------------------------------------------
   # Reason for doing this is because python does 
   # not like the 'x' in targets like '9x15'
   if env['MSM_ID'] in ['8937']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8937')
      multi_config_xml = "${BUILD_ROOT}/core/bsp/build/chipset/msm8937/image_cfg.xml"
   if env['MSM_ID'] in ['8996']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8996')
      multi_config_xml = "${BUILD_ROOT}/core/bsp/build/chipset/msm8996/image_cfg.xml"
   if env['MSM_ID'] in ['8998']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8998')
      multi_config_xml = "${BUILD_ROOT}/core/bsp/build/chipset/msm8998/image_cfg.xml"
   if env['MSM_ID'] in ['8953']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8953')
      multi_config_xml = "${BUILD_ROOT}/core/bsp/build/chipset/msm8953/image_cfg.xml"
   if env['MSM_ID'] in ['8952']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8952')
      multi_config_xml = "${BUILD_ROOT}/core/bsp/build/chipset/msm8952/image_cfg.xml"
   if env['MSM_ID'] in ['8956']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8956')
      multi_config_xml = "${BUILD_ROOT}/core/bsp/build/chipset/msm8956/image_cfg.xml"

   devcfg_xml_tag_list, devcfg_soc_tag_dict, tcsr_hw_version_addr = get_devcfg_xml_tags(env, multi_config_xml)
   env.Replace(DEVCFG_XML_TAGS = devcfg_xml_tag_list)
   env.Replace(DEVCFG_SOC_DICT = devcfg_soc_tag_dict)
   env.Replace(DEVCFG_TCSR_SOC_HW_ADDR = tcsr_hw_version_addr)
   #devcfg_used_tag_list = []
   #env.Replace(DEVCFG_ENV_USED_XML_TAGS = devcfg_used_tag_list)
   
   env.Append(CPPDEFINES = [
      "DAL_CONFIG_TARGET_ID=${DAL_CONFIG_TARGET_ID}"
   ])

def exists(env):
    return env.Detect('tbc_core_devcfg')

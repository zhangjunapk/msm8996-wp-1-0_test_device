/*==============================================================================

FILE:      ABT_OEM_data.c

DESCRIPTION: This file contains target/platform specific configuration data.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.tz/1.0.3.c1/buses/icb/src/8996/ABT_OEM_data.c#1 $ 
$DateTime: 2016/12/02 01:46:26 $
$Author: pwbldsvc $
$Change: 11896995 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------  
2014/12/09  tb     Created
 
        Copyright (c) 2014 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "ABTimeout.h"
#include "ABTimeout_HWIO.h"

/*============================================================================
                      TARGET AND PLATFORM SPECIFIC DATA
============================================================================*/

/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/* OEM ABT Configuration Data*/
const ABT_slave_info_type_oem ABT_cfgdata_oem[] = 
{ 
//ABT_SLAVE_INFO_OEM(name,     sl_en,  int_en, to_val)
  ABT_SLAVE_INFO_OEM(CNOC_0,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_1,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_2,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_3,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_4,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_5,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_6,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_7,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_8,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_9,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(SNOC_2,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(SNOC_1,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(PNOC_0,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(PNOC_1,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(PNOC_2,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(PNOC_3,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(PNOC_4,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(MMSS_0,   TRUE,   TRUE,   0xFF), 
  ABT_SLAVE_INFO_OEM(MMSS_1,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(MMSS_2,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(MMSS_3,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(MMSS_4,   TRUE,   TRUE,   0xFF),
  ABT_SLAVE_INFO_OEM(SSC_CFG,  TRUE,   TRUE,   0xFF),
};

/* OEM ABT Configuration Property Data*/
const ABT_propdata_type_oem ABT_propdata_oem =  
{
    /* Length of the OEM config data array */
    sizeof(ABT_cfgdata_oem)/sizeof(ABT_slave_info_type_oem), 
    /* Pointer to OEM config data array */ 
    ABT_cfgdata_oem                                 
};


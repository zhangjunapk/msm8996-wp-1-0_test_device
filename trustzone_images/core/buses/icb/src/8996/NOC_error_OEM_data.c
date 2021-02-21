/*==============================================================================

FILE:      NOC_error_OEM_data.c

DESCRIPTION: This file contains target/platform specific configuration data.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.tz/1.0.3.c1/buses/icb/src/8996/NOC_error_OEM_data.c#1 $ 
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
#include "NOC_error.h"
#include "NOC_error_HWIO.h"

/*============================================================================
                           TARGET SPECIFIC DATA
============================================================================*/

/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/* OEM NOC Configuration Data*/
const NOCERR_info_type_oem NOCERR_cfgdata_oem[] = 
{ 
//NOCERR_INFO_OEM(name,               intr_en, intr_fatal)
  NOCERR_INFO_OEM(CNOC,               TRUE,    TRUE),  /* Config NOC */
  NOCERR_INFO_OEM(SNOC,               TRUE,    TRUE),  /* System NOC */
  NOCERR_INFO_OEM(PNOC,               TRUE,    TRUE),  /* Peripheral NOC */
  NOCERR_INFO_OEM(MNOC,               TRUE,    TRUE),  /* Multimedia NOC */
  NOCERR_INFO_OEM(A0_NOC_AGGRE0_NOC,  TRUE,    TRUE),  /* AGGRE0 NOC */
  NOCERR_INFO_OEM(A1_NOC_AGGRE1_NOC,  TRUE,    TRUE),  /* AGGRE1 NOC */
  NOCERR_INFO_OEM(A2_NOC_AGGRE2_NOC,  TRUE,    TRUE),  /* AGGRE2 NOC */
};

const NOCERR_propdata_type_oem NOCERR_propdata_oem =
{
    /* Length of the config data array */
    sizeof(NOCERR_cfgdata_oem)/sizeof(NOCERR_info_type_oem), 
    /* Pointer to OEM config data array */ 
    NOCERR_cfgdata_oem,
};

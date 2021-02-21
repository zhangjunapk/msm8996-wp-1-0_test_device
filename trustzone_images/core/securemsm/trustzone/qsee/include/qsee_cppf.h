#ifndef QSEE_CPPF_H
#define QSEE_CPPF_H

/*============================================================================
Copyright (c) 2015 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
=========================================================================== */

/*=========================================================================
                              Edit History

  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsee/include/qsee_cppf.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     ---------------------------------------------------------------
06/19/15   shl     Initial Revision

================================================================================== */
#include <stdint.h>

/* this definition is from SWI document, inclusifn namin. */
typedef enum
{
  NONE = 0,
  V_1_4,
//	V_2_0,
//	V_2_1,
  V_2_2,
  BLOCK,
  MAX_MIN_ENC_LEVEL
} MinEnLevelType;


typedef enum
{
  CPPF_SUCCESS             =  0,       /* Operation successful */
  CPPF_INVALID_ARG ,                   /* parameters passed in is invalid */
  CPPF_HDMI_HW_NOT_AVAILABLE ,         /* No HDMI HW available  */
  CPPF_CLOCK_NOT_ON,                   /* HDMI related clocks not on */
  CPPF_OUT_OF_MAX_NUM_OF_APPS,         /* Too many apps try to set min_enc_level  */
  CPPF_NOT_SUPPORTED,                  

  CPPF_RESERVED           = 0x7FFFFFFF
}CPPFErrNoType;

/*
   Handle the request of setting the minimum encryption level

   Parameters:
       min_enc_level      - (in) min_enc_level to set

   Return: 
       CPPFErrNoType;

*/
CPPFErrNoType qsee_set_hdcp_min_enc_level( uint8_t min_enc_level );

/*
   Handle request of getting minimum encryption level

   Parameters:
        min_enc_level_type    - (in/out) minimum enc-level

   Return: CPPFErrNoType;

*/
CPPFErrNoType qsee_get_hdcp_min_enc_level(uint8_t *min_enc_level);

#endif /*QSEE_CPPF_H*/


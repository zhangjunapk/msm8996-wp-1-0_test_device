#ifndef GD_COLOR_H
#define GD_COLOR_H

/*===========================================================================
   Copyright (c) 2013 Qualcomm Technologies, Inc.       
   All Rights Reserved.
   Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/sse/qsee/SecureDisplay/libgd/include/gd_color.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

when       who      what, where, why
--------   ---      ------------------------------------
07/02/13   ts       Initial version.

===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

	int gdColorMatch(gdImagePtr im, int col1, int col2, float threshold);

#ifdef __cplusplus
}
#endif

#endif

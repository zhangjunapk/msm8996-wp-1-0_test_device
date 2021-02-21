#ifndef QSEE_ONTARIO_H
#define QSEE_ONTARIO_H

/*============================================================================
  Copyright (c) 2011-2013 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Technologies Confidential and Proprietary
=========================================================================== */

/*=========================================================================
                              Edit History

  $Header: //components/rel/core.tz/1.0.3.c1/api/securemsm/trustzone/qsee/qsee_ontario.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     --------------------------------------------------------
7/28	   kbuska  Ontario driver QSEE interface
=========================================================================== */

void Ontario_Driver_Ioctl
(
   uint32_t       *command,
   void           *args,
   uint32_t       *result
);

#endif /*QSEE_ONTARIO_H*/


/*
@file app_main.c
@brief App main entry point.

*/
/*===========================================================================
   Copyright (c) 2011-2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

#include <comdef.h>
#include <string.h>
#include "qsee_log.h"
#include "qsee_heap.h"
#include "object.h"
#include "COEMUnwrapKeys.h"
#include "COEMUnwrapKeys_open.h"

int32_t tz_module_open(uint32_t uid, Object cred, Object *objOut)
{
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Sample Server tz_module_open() uid: %d", uid);

  if (uid == COEMUnwrapKeys_UID) {
    return COEMUnwrapKeys_open(cred, objOut);
  }

  *objOut = (Object){ NULL, NULL };
  return Object_ERROR_INVALID;
}

void tz_app_init(void)
{
  /*  App specific initialization code*/  
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Sample Server init.");
}

void tz_app_cmd_handler(void* cmd, uint32 cmdlen, 
                        void* rsp, uint32 rsplen)
{
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Sample Server received command.");
  return;
}

void tz_app_shutdown(void)
{
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Sample Server shutdown.");
  return;
}

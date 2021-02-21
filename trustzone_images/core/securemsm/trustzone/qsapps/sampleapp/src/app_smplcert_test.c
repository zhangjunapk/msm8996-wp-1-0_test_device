/*===========================================================================
   Copyright (c) 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE
  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsapps/sampleapp/src/app_smplcert_test.c#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

# when       who     what, where, why
# --------   ---     ---------------------------------------------------------

===========================================================================*/
#include "CCertValidate.h"
#include "IValidate.h"
#include "qsee_env.h"
#include "qsee_log.h"


static char bufInValid[8] = {0x30, 0x82, 0x04, 0xC8};
static char bufInInvalid[8] = "abcdef";

int run_smplcert_test()
{
  Object o;
  int32_t err;

  qsee_open(CCertValidate_UID, &o);
  if (Object_isNull(o)){
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplcert_test() qsee_open() failed");
    goto bail;
  }
    
  err = IValidate_validate(o, bufInValid, sizeof(bufInValid));
  if (!Object_isOK(err)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplcert_test() validate() #1 failed");
    goto bail;
  }

  err = IValidate_validate(o, bufInInvalid, sizeof(bufInInvalid));
  if (Object_isOK(err)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplcert_test() validate() #2 failed");
    goto bail;
  }

  return 0;

  bail:
    return -1;
}



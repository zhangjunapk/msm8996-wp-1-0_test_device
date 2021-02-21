/*===========================================================================
   Copyright (c) 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE
  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsapps/sampleapp/src/app_smplserv_test.c#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

# when       who     what, where, why
# --------   ---     ---------------------------------------------------------

===========================================================================*/
#include "COEMUnwrapKeys.h"
#include "IUnwrapKeys.h"
#include "qsee_env.h"
#include "qsee_log.h"


static char bufIn[] = "abcdefg";

int run_smplserv_test()
{
  Object o;
  int32_t err;
  char bufOut[32] = {0};
  size_t lenOut;

  err = qsee_open(COEMUnwrapKeys_UID, &o);
  if (!Object_isOK(err) || Object_isNull(o)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplserv_test() qsee_open() failed");
    return -1;
  }

  err = IUnwrapKeys_unwrap(o, bufIn, sizeof(bufIn), bufOut, sizeof(bufOut), &lenOut);
  if (!Object_isOK(err)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplserv_test() unwrap() failed");
    goto bail;
  }

  if (lenOut != sizeof(bufIn)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplserv_test() lenOut check failed");
    goto bail;
  }

  if (memcmp(bufIn, bufOut, sizeof(bufIn))) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplserv_test() strnicmp() failed");
    goto bail;
  }

  return 0;

  bail:
    if (!Object_isNull(o)){
      IUnwrapKeys_release(o);
    }
    return -1;
}

int run_smplserv_crash_test()
{
  Object o;
  int32_t err;
  char bufOut[32] = {0};
  size_t lenOut;

  static char bufCrash[] = "__crash__";

  err = qsee_open(COEMUnwrapKeys_UID, &o);
  if (!Object_isOK(err) || Object_isNull(o)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplserv_crash_test() qsee_open() failed, err = %d", err);
    return -1;
  }

  err = IUnwrapKeys_unwrap(o, bufCrash, sizeof(bufCrash), bufOut, sizeof(bufOut), &lenOut);
  if (!Object_isOK(err)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplserv_crash_test() PASSED, expected error is Object_ERROR_DEFUNCT,  err=%d", err);
  }

  // Call open on the same object again - should fail again the same way
  err = qsee_open(COEMUnwrapKeys_UID, &o);
  if (!Object_isOK(err) || Object_isNull(o)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_smplserv_crash_test() PASSED - qsee_open() expected to fail after app crash, err = %d", err);
  }

  return 0;

  bail:
    if (!Object_isNull(o)){
      IUnwrapKeys_release(o);
    }
    return -1;
}



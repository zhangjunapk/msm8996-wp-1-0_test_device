/*
 * Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */
#include "sselog.h"
#include "SecureTouchError.h"
#include "drTsController.h"
#include "TouchApi.h"

#include "atmel_mxt_ts.h"
#include "synaptics_ts.h"

uint32_t g_drTs_sid = DR_SID_INVALID;
struct drTsFunc g_ts_dr_func = {
  .drTsOpen = NULL,
  .drTsClose = NULL,
  .drTsProcessEvents = NULL
};

uint32_t touchOpen(uint32_t *sid, const uint32_t width, const uint32_t height) {
  uint32_t rv = SSE_OK;
  ENTER;
  do {
    if (g_drTs_sid != DR_SID_INVALID) {
      LOG_E("Secure touch already in use");
      rv = E_ST_BUSY;
      break;
    }

    if (width < 2000) { // fluid
      LOG_D("Detected Fluid, using Synaptics driver");
      g_ts_dr_func.drTsOpen          = synaptics_drTsOpen;
      g_ts_dr_func.drTsClose         = synaptics_drTsClose;
      g_ts_dr_func.drTsProcessEvents = synaptics_drTsProcessEvents;
    } else {
      LOG_D("Detected Liquid, using Atmel driver");
      g_ts_dr_func.drTsOpen          = atmel_drTsOpen;
      g_ts_dr_func.drTsClose         = atmel_drTsClose;
      g_ts_dr_func.drTsProcessEvents = atmel_drTsProcessEvents;
    }

    if (0 != g_ts_dr_func.drTsOpen(width,height)) {
      LOG_E("Failed to open Touch interface");
      rv = E_ST_DRIVER_ERROR; // the TZBSP I2C interface doesn't return much info on failures...
      break;
    }
    g_drTs_sid = 0; // poor man random...
    *sid = g_drTs_sid;
  } while(0);
  EXITRV;
}

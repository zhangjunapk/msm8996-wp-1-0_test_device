/*
 * Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */
#pragma once

#include "qsee_i2c.h"
#include "qsee_blsp.h"

#define BLSP_MODIFY_OWNERSHIP_SUPPORT
#define I2C_ADDRESS 0x20

#define I2C_DEVICE         QSEE_I2CPD_DEVICE_12 
#define I2C_DEVICE_ID_SUB  11 /*Refer BLSP2 QUP5 at \trustzone_images\core\buses\qup_accesscontrol\honeybadger\inc\QupACCommonIds.h */

#define QSEE_TZ_ID_SUB     1 /* Refer at \trustzone_images\core\buses\qup_accesscontrol\honeybadger\inc\QupACCommonIds.h for APPS_ID and TZ_ID*/
#define QSEE_APPS_ID_SUB   3




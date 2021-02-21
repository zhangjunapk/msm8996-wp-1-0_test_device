#ifndef __II2C_H
#define __II2C_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

/** @file II2C.idl  */

/*
  Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential. */

/**
 * @addtogroup core
 * @{
 */

/** Bus configuration settings. */

typedef struct {
  uint32_t fsBusFreqInKhz;
  uint32_t hsBusFreqInKhz;
  int32_t i2cInterface;
  int32_t maxBusAcquireWaitTimeMsec;
} II2C_BusConfig;

typedef struct {
  uint32_t slaveAddress;
  int32_t slaveAddressOption;
  int32_t slaveDeviceType;
  int32_t readOption;
  int32_t byteTransferWaitTimeUsec;
} II2C_SlaveDeviceConfig;

typedef struct {
  int32_t useDefaultBusConfig;
  II2C_BusConfig busConfig;
  II2C_SlaveDeviceConfig slaveConfig;
} II2C_Config;

#define II2C_DEFAULT_WAIT_TIME INT32_C(-1)
#define II2C_INVALID_DEVICE INT32_C(-1)
#define II2C_INVALID_INTERFACE INT32_C(-1)
#define II2C_STANDARD_INTERFACE INT32_C(0)
#define II2C_AUXILIARY_INTERFACE INT32_C(1)
#define II2C_INTERFACE_COUNT INT32_C(2)
#define II2C_INVALID_SLAVE_ADDRESS INT32_C(-1)
#define II2C_SEVEN_BIT_SLAVE_ADDRESS INT32_C(0)
#define II2C_TEN_BIT_SLAVE_ADDRESS INT32_C(1)
#define II2C_SLAVE_ADDR_OPTIONS_COUNT INT32_C(2)
#define II2C_INVALID_ADDRESS_DEVICE INT32_C(-1)
#define II2C_DEFAULT_ADDRESS_DEVICE INT32_C(0)
#define II2C_MEMORY_ADDRESS_DEVICE INT32_C(1)
#define II2C_REGISTER_ADDRESS_DEVICE INT32_C(2)
#define II2C_SLAVE_DEVICE_COUNT INT32_C(3)
#define II2C_INVALID_READ_OPTION INT32_C(-1)
#define II2C_READ_OPTION_DEFAULT INT32_C(0)
#define II2C_GEN_START_BEFORE_READ INT32_C(1)
#define II2C_GEN_STOP_START_BEFORE_READ INT32_C(2)
#define II2C_READ_OPTIONS_COUNT INT32_C(3)

#define II2C_OP_close 0
#define II2C_OP_open 1
#define II2C_OP_read 2
#define II2C_OP_write 3
#define II2C_OP_acquireExclusiveAccess 4
#define II2C_OP_releaseExclusiveAccess 5

static inline int32_t
II2C_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
II2C_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

static inline int32_t
II2C_close(Object self, int32_t deviceId_val)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { &deviceId_val, sizeof(int32_t) };

  return Object_invoke(self, II2C_OP_close, a, ObjectCounts_pack(1, 0, 0, 0));
}

static inline int32_t
II2C_open(Object self, int32_t deviceId_val)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { &deviceId_val, sizeof(int32_t) };

  return Object_invoke(self, II2C_OP_open, a, ObjectCounts_pack(1, 0, 0, 0));
}

static inline int32_t
II2C_read(Object self, int32_t deviceId_val, const II2C_Config *config_ptr, uint32_t startAddr_val, void *payload_ptr, size_t payload_len, size_t *payload_lenout)
{
  ObjectArg a[3];
  struct {
    int32_t m_deviceId;
    uint32_t m_startAddr;
  } i;
  a[0].b = (ObjectBuf) { &i, 8 };
  i.m_deviceId = deviceId_val;
  a[1].bi = (ObjectBufIn) { config_ptr, sizeof(II2C_Config) };
  i.m_startAddr = startAddr_val;
  a[2].b = (ObjectBuf) { payload_ptr, payload_len * 1 };

  int32_t result = Object_invoke(self, II2C_OP_read, a, ObjectCounts_pack(2, 1, 0, 0));

  *payload_lenout = a[2].b.size / 1;

  return result;
}

static inline int32_t
II2C_write(Object self, int32_t deviceId_val, const II2C_Config *config_ptr, uint32_t startAddr_val, const void *payload_ptr, size_t payload_len, uint64_t *bytesWritten_ptr)
{
  ObjectArg a[4];
  struct {
    int32_t m_deviceId;
    uint32_t m_startAddr;
  } i;
  a[0].b = (ObjectBuf) { &i, 8 };
  i.m_deviceId = deviceId_val;
  a[1].bi = (ObjectBufIn) { config_ptr, sizeof(II2C_Config) };
  i.m_startAddr = startAddr_val;
  a[2].bi = (ObjectBufIn) { payload_ptr, payload_len * 1 };
  a[3].b = (ObjectBuf) { bytesWritten_ptr, sizeof(uint64_t) };

  return Object_invoke(self, II2C_OP_write, a, ObjectCounts_pack(3, 1, 0, 0));
}

static inline int32_t
II2C_acquireExclusiveAccess(Object self, int32_t deviceId_val)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { &deviceId_val, sizeof(int32_t) };

  return Object_invoke(self, II2C_OP_acquireExclusiveAccess, a, ObjectCounts_pack(1, 0, 0, 0));
}

static inline int32_t
II2C_releaseExclusiveAccess(Object self, int32_t deviceId_val)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { &deviceId_val, sizeof(int32_t) };

  return Object_invoke(self, II2C_OP_releaseExclusiveAccess, a, ObjectCounts_pack(1, 0, 0, 0));
}


#endif /* __II2C_H */
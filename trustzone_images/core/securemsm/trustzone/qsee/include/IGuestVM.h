#ifndef __IGUESTVM_H
#define __IGUESTVM_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

// Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.

// Qualcomm Technologies Proprietary and Confidential.

#define IGuestVM_OP_handleCommand 0
#define IGuestVM_OP_handleInterrupt 1

static inline int32_t
IGuestVM_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
IGuestVM_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

static inline int32_t
IGuestVM_handleCommand(Object self, const void *req_ptr, size_t req_len, void *resp_ptr, size_t resp_len, size_t *resp_lenout)
{
  ObjectArg a[2];
  a[0].bi = (ObjectBufIn) { req_ptr, req_len * 1 };
  a[1].b = (ObjectBuf) { resp_ptr, resp_len * 1 };

  int32_t result = Object_invoke(self, IGuestVM_OP_handleCommand, a, ObjectCounts_pack(1, 1, 0, 0));

  *resp_lenout = a[1].b.size / 1;

  return result;
}

static inline int32_t
IGuestVM_handleInterrupt(Object self, uint32_t registeredMask_val)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { &registeredMask_val, sizeof(uint32_t) };

  return Object_invoke(self, IGuestVM_OP_handleInterrupt, a, ObjectCounts_pack(1, 0, 0, 0));
}


#endif /* __IGUESTVM_H */

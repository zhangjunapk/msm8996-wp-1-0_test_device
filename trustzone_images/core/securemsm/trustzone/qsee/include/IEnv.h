#ifndef __IENV_H
#define __IENV_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"
#include "IOpener.h"

// Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.

// Qualcomm Technologies Proprietary and Confidential.

//! @file

#define IEnv_ERROR_NOT_FOUND INT32_C(10)
#define IEnv_ERROR_PRIVILEGE INT32_C(11)

#define IEnv_OP_log 1
#define IEnv_OP_exit 2

static inline int32_t
IEnv_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
IEnv_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

static inline int32_t
IEnv_open(Object self, uint32_t id_val, Object *obj_ptr)
{
  ObjectArg a[2];
  a[0].b = (ObjectBuf) { &id_val, sizeof(uint32_t) };

  int32_t result = Object_invoke(self, IOpener_OP_open, a, ObjectCounts_pack(1, 0, 0, 1));

  *obj_ptr = a[1].o;

  return result;
}

static inline int32_t
IEnv_log(Object self, const void *text_ptr, size_t text_len)
{
  ObjectArg a[1];
  a[0].bi = (ObjectBufIn) { text_ptr, text_len * 1 };

  return Object_invoke(self, IEnv_OP_log, a, ObjectCounts_pack(1, 0, 0, 0));
}

static inline int32_t
IEnv_exit(Object self, int32_t code_val)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { &code_val, sizeof(int32_t) };

  return Object_invoke(self, IEnv_OP_exit, a, ObjectCounts_pack(1, 0, 0, 0));
}


#endif /* __IENV_H */

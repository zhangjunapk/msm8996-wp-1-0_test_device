#ifndef __IUNWRAPKEYS_H
#define __IUNWRAPKEYS_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

// Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.

// Qualcomm Technologies Proprietary and Confidential.

#define IUnwrapKeys_OP_unwrap 0

static inline int32_t
IUnwrapKeys_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
IUnwrapKeys_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

static inline int32_t
IUnwrapKeys_unwrap(Object self, const void *wrapped_ptr, size_t wrapped_len, void *unwrapped_ptr, size_t unwrapped_len, size_t *unwrapped_lenout)
{
  ObjectArg a[2];
  a[0].bi = (ObjectBufIn) { wrapped_ptr, wrapped_len * 1 };
  a[1].b = (ObjectBuf) { unwrapped_ptr, unwrapped_len * 1 };

  int32_t result = Object_invoke(self, IUnwrapKeys_OP_unwrap, a, ObjectCounts_pack(1, 1, 0, 0));

  *unwrapped_lenout = a[1].b.size / 1;

  return result;
}


#endif /* __IUNWRAPKEYS_H */
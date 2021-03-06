#ifndef __ISOURCE_H
#define __ISOURCE_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

// Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.

// Qualcomm Technologies Proprietary and Confidential.

#define ISource_OP_read 0

static inline int32_t
ISource_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
ISource_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

static inline int32_t
ISource_read(Object self, void *data_ptr, size_t data_len, size_t *data_lenout)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { data_ptr, data_len * 1 };

  int32_t result = Object_invoke(self, ISource_OP_read, a, ObjectCounts_pack(0, 1, 0, 0));

  *data_lenout = a[0].b.size / 1;

  return result;
}


#endif /* __ISOURCE_H */

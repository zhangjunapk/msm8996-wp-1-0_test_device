#ifndef __IINTMASK_H
#define __IINTMASK_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

// Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights

// Reserved.  Qualcomm Technologies Proprietary and Confidential.

#define IIntMask_FIQ UINT32_C(0x1)
#define IIntMask_IRQ UINT32_C(0x2)
#define IIntMask_SError UINT32_C(0x4)
#define IIntMask_DebugException UINT32_C(0x8)

#define IIntMask_ERROR_UNSUPPORTED_INTERRUPT_BIT INT32_C(10)
#define IIntMask_ERROR_MAY_NOT_UNMASK_IRQ INT32_C(11)

#define IIntMask_OP_disableAllInterrupts 0
#define IIntMask_OP_setIntMask 1
#define IIntMask_OP_getIntMask 2

static inline int32_t
IIntMask_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
IIntMask_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

static inline int32_t
IIntMask_disableAllInterrupts(Object self, uint32_t *restoreMask_ptr)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { restoreMask_ptr, sizeof(uint32_t) };

  return Object_invoke(self, IIntMask_OP_disableAllInterrupts, a, ObjectCounts_pack(0, 1, 0, 0));
}

static inline int32_t
IIntMask_setIntMask(Object self, uint32_t intMask_val)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { &intMask_val, sizeof(uint32_t) };

  return Object_invoke(self, IIntMask_OP_setIntMask, a, ObjectCounts_pack(1, 0, 0, 0));
}

static inline int32_t
IIntMask_getIntMask(Object self, uint32_t *intMask_ptr)
{
  ObjectArg a[1];
  a[0].b = (ObjectBuf) { intMask_ptr, sizeof(uint32_t) };

  return Object_invoke(self, IIntMask_OP_getIntMask, a, ObjectCounts_pack(0, 1, 0, 0));
}


#endif /* __IINTMASK_H */

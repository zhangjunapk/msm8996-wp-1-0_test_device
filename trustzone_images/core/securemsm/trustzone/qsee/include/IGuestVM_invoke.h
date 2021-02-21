#ifndef __IGUESTVM_INVOKE_H
#define __IGUESTVM_INVOKE_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

#include "IGuestVM.h"

#define IGuestVM_DEFINE_INVOKE(func, prefix, type) \
  int32_t func(ObjectCxt h, ObjectOp op, ObjectArg *a, ObjectCounts k) \
  { \
    type me = (type) h; \
    switch (ObjectOp_methodID(op)) { \
      case Object_OP_release: { \
        return prefix##release(me); \
      } \
      case Object_OP_retain: { \
        return prefix##retain(me); \
      } \
      case IGuestVM_OP_handleCommand: { \
        if (k != ObjectCounts_pack(1, 1, 0, 0)) { \
          break; \
        } \
        const void *req_ptr = (const void*) a[0].b.ptr; \
        size_t req_len = a[0].b.size / 1; \
        void *resp_ptr = (void*) a[1].b.ptr; \
        size_t resp_len = a[1].b.size / 1; \
        int32_t r = prefix##handleCommand(me, req_ptr, req_len, resp_ptr, resp_len, &resp_len); \
        a[1].b.size = resp_len * 1; \
        return r; \
      } \
      case IGuestVM_OP_handleInterrupt: { \
        if (k != ObjectCounts_pack(1, 0, 0, 0) || \
          a[0].b.size != 4) { \
          break; \
        } \
        const uint32_t *registeredMask_ptr = (const uint32_t*) a[0].b.ptr; \
        return prefix##handleInterrupt(me, *registeredMask_ptr); \
      } \
    } \
    return Object_ERROR_INVALID; \
  }

#endif /* __IGUESTVM_INVOKE_H */

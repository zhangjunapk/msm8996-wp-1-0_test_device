#ifndef GPTIME_H
#define GPTIME_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "gpTypes.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#ifdef __cplusplus
  extern "C"
  {
#endif

TEE_Result
TEE_GetTAPersistentTime(
  TEE_Time* time);

TEE_Result
TEE_SetTAPersistentTime(
  TEE_Time* time);

void
TEE_GetSystemTime (
  TEE_Time* time);

void TEE_GetREETime(
  TEE_Time* time);

TEE_Result
TEE_Wait(
  uint32_t timeout);

#ifdef __cplusplus
  }
#endif

#endif /* GPTIME_H */

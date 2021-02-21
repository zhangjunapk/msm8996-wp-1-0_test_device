#ifndef GPTAINTERFACEAPIS_H
#define GPTAINTERFACEAPIS_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "gpTypes.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
TEE_Result
TA_CreateEntryPoint(
  void);

void
TA_DestroyEntryPoint(
  void);

TEE_Result
TA_OpenSessionEntryPoint(
  uint32_t,
  TEE_Param params[MAX_GP_PARAMS],
  void**);

void
TA_CloseSessionEntryPoint(
  void*);

TEE_Result
TA_InvokeCommandEntryPoint(
  void*,
  uint32_t,
  uint32_t,
  TEE_Param params[MAX_GP_PARAMS]);

#endif /* GPTAINTERFACEAPIS_H */

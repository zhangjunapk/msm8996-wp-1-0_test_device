#ifndef GPINTERNALCLIENTAPIS_H
#define GPINTERNALCLIENTAPIS_H

/* ------------------------------------------------------------------------
 * Include files
 * ------------------------------------------------------------------------ */
#include "gpTypes.h"

/*----------------------------------------------------------------------------
 * Function Declarations
 * -------------------------------------------------------------------------*/
TEE_Result
TEE_OpenTASession(
  TEE_UUID* destination,
  uint32_t cancellationRequestTimeout,
  uint32_t paramTypes,
  TEE_Param params[MAX_GP_PARAMS],
  TEE_TASessionHandle* session,
  uint32_t* returnOrigin);

void
TEE_CloseTASession(
  TEE_TASessionHandle session);

TEE_Result
TEE_InvokeTACommand(
  TEE_TASessionHandle session,
  uint32_t cancellationRequestTimeout,
  uint32_t commandID,
  uint32_t paramTypes,
  TEE_Param params[MAX_GP_PARAMS],
  uint32_t* returnOrigin);

#endif /* GPINTERNALCLIENTAPIS_H */

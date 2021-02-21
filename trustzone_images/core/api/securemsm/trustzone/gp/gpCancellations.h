#ifndef GPCANCELLATIONS_H_
#define GPCANCELLATIONS_H_

/*----------------------------------------------------------------------------
 * Include files
 * -------------------------------------------------------------------------*/
#include <stdbool.h>

bool
TEE_GetCancellationFlag(
  void);

bool
TEE_UnmaskCancellation(
  void);

bool
TEE_MaskCancellation(
  void);

#endif /* GPCANCELLATIONS_H_ */

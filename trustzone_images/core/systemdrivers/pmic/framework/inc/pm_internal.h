#ifndef PM_INTERNAL_H
#define PM_INTERNAL_H

/*! \file
 *  \n
 *  \brief  pm_internal.h
 *  \n
 *  \n This header file contains local definitions for PMIC SW.
 *  \n
 *  \n &copy; Copyright 2014 Qualcomm Technologies Incorporated, All Rights Reserved
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.tz/1.0.3.c1/systemdrivers/pmic/framework/inc/pm_internal.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

06/25/14   vtw     Created.
=============================================================================*/

#include "comdef.h"

typedef enum
{
  PM_RAIL_TYPE_LDO,
  PM_RAIL_TYPE_SMPS,
  PM_RAIL_TYPE_INV,
} pm_rail_type;

/**
  * PMIC Peripheral Register Info.
  */
typedef struct
{
  uint32 slave_id;  /* Slave ID */
  uint32 base_addr; /* Base Address */
  pm_rail_type rail_t;
} pm_rail_reg_type;


#endif /* PM_INTERNAL_H */

#ifndef __DALTLMMPROPDEF_H__
#define __DALTLMMPROPDEF_H__
/*
============================================================================

                 D A L T L M M   S T A T E   S T R U C T U R E
                             H E A D E R   F I L E

FILE:         DALTLMMDefines.h

DESCRIPTION:  
              This file contains definitions for use solely with the
              DALTLMM Properties XML file.  It's use is not recommended by
              any drivers and must not be used in any DALTLMM APIs.

============================================================================

                             Edit History

$Header: //components/rel/core.tz/1.0.3.c1/systemdrivers/tlmm/config/TlmmPropDef.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------
07/30/14   dcf     Created the initial revision. 
 
============================================================================
             Copyright (c) 2014 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
============================================================================
*/

#include "DALStdDef.h"

/*==========================================================================

                     DEFINITIONS FOR THIS MODULE

==========================================================================*/

/*
 * TLMMGpioIdType
 *
 * GPIO Identifier for configuring a GPIO based on device config data for
 * a particular platform.
 *
 *  nGpioNumber:     GPIO Pin Number.
 *  nFunctionSelect: The function select associated with this GPIO.
 */


typedef struct {  
   uint32 nGpioNumber;
   uint32 nFunctionSelect;
}TLMMGpioIdType;
 
#endif /* __DALTLMMPROPDEF_H__ */


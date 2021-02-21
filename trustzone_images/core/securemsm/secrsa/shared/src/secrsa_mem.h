#ifndef CE_RSA_MEM_H
#define CE_RSA_MEM_H

/*===========================================================================
   Copyright (c) 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
  
   This file contains a secure memset implementation.
  ===========================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE
  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/secrsa/shared/src/secrsa_mem.h#1 $
  $DateTime: 2016/12/02 01:46:26 $ 
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  04/11/11   qxu     initial version
=============================================================================*/

#undef memset

#define memset secrsa_memset

void * secrsa_memset(void *buf, int i, uint32 size);



#endif /* CE_RSA_MEM_H */

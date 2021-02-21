#ifndef _QSEE_COUNTER_H
#define _QSEE_COUNTER_H

/**
@file qsee_counter.h  
@brief This is wrapper of counter service in tzbsp
*/



/*=============================================================================
        Copyright (c) 2012-2014, Qualcomm Technologies, Inc.
                       All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential.

=============================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.3.c1/api/securemsm/trustzone/qsee/qsee_counter.h#1 $ 
  $DateTime: 2016/12/02 01:46:26 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/25/13   yh      initial version

===========================================================================*/

#include <stdint.h>
#include "IxErrno.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#define QSEE_COUNTER_LENGTH  32
 /**
 * @brief Create a pair of value [identifier, initial_value] and ask TZ to save
 *        the pair value in SFS, only the caller application can query the value back
 *
 * @param[in] identifier  32 bytes long array as the input identifier
 * @param[in] initial_value  A initial value binded with identifier
 *
 * @return 0 on success, 
 *  return E_INVALID_ARG if identifier points to NULL
 *  return E_ALREADY_DONE if identifier already created.
 */
int qsee_create_counter(uint8_t *identifier, uint64_t initial_value);

/**
 * @brief Query the counter value associated with an identifier
 *
 * @param[in] identifier  32 bytes long array as the input identifier
 * @param[out] current_value  A initial value binded with identifier
 *
 * @return 0 on success, 
 *  return E_INVALID_ARG if identifier or current_value points
 *  to NULL
 *  return E_NOT_AVAILABLE if TZ has no counter record for
 *  identifier
 *
 */
int qsee_query_counter(uint8_t *identifier, uint64_t *current_value);

/**
 * @brief Increase the counter value of the identifier
 *
 * @param[in] identifier  32 bytes long array as the input identifier
 *
 * @return 0 on success
 *  return E_INVALID_ARG if identifier points to NULL
 *  return E_NOT_AVAILABLE if TZ has no counter record for
 *  identifier
 *
 */
int qsee_increment_counter(uint8_t *identifier);

/**
 * @brief delete [identifier, counter] record from TZ SFS
 *
 * @param[in] identifier  32 bytes long array as the input identifier
 *
 * @return 0 on success
 *  return E_INVALID_ARG if identifier points to NULL
 *  return E_NOT_AVAILABLE if TZ has no counter record for
 *  identifier
 *
 */
int qsee_delete_counter(uint8_t *identifier);

#endif /* _QSEE_COUNTER_H */

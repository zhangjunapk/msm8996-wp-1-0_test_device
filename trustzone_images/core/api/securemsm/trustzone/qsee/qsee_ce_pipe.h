#ifndef QSEE_CE_PIPE_H
#define QSEE_CE_PIPE_H

/**
@file qsee_ce_pipe.h
@brief Provide ce pipe defines
*/

/*===========================================================================
   Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.3.c1/api/securemsm/trustzone/qsee/qsee_ce_pipe.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

when       who      what, where, why
--------   ---      ------------------------------------
5/20/14    sk       Added ICE support
4/11/14    amen     Initial version.

===========================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include <stdint.h>
#include "qsee_ks.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
typedef enum
{
  QSEE_PIPE_ENC            = 0,
  QSEE_PIPE_ENC_XTS        = 1,
  QSEE_PIPE_AUTH           = 2,
  QSEE_PIPE_NUM_PIPE_DESCS = 3,
  QSEE_PIPE_ENUM_FILL      = 0x7FFFFFFF
} qsee_pipe_desc_t;

typedef enum
{
  QSEE_PIPE_NONE_MSK      = 0,
  QSEE_PIPE_ENC_MSK       = 1 << QSEE_PIPE_ENC,
  QSEE_PIPE_ENC_XTS_MSK   = 1 << QSEE_PIPE_ENC_XTS,
  QSEE_PIPE_AUTH_MSK      = 1 << QSEE_PIPE_AUTH,
  QSEE_PIPE_MSK_ENUM_FILL = 0x7FFFFFFF
} qsee_pipe_desc_msk_t;

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

typedef struct
{
  ks_ent_id_t usr_key;
  ks_ent_pwd_t usr_pwd;
} qsee_pipe_key_param_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/**
   Sets the key in pipe of ce

   @param ce             Crypto engine number
   @param pipe           pipe of ce
   @param pipe_desc_msk  mask described by type qsee_pipe_desc_msk_t
   @param flags          for future use
   @param key_info_ptr   usr_key defined as per usecase and usr_pwd
                         to access the key
 
   @retval E_SUCCESS                         on success
           QSEE_RESULT_FAIL_LOAD_KS          if the keystore could not be loaded
                                             from EMMC or if the version could
                                             not be verified from RPMB
           QSEE_RESULT_FAIL_KEY_ID_DNE       if the key did not exist in the
                                             keystore
           QSEE_RESULT_FAIL_CE_PIPE_INVALID  ce and pipe combination invalid
           QSEE_RESULT_FAIL_KS_OP            Operation failed
           -E_FAILURE                        Operation failed
           QSEE_RESULT_FAIL_SAVE_KS          if the keystore update isn't saved
*/
int qsee_ce_pipe_key_select(uint32_t ce, uint32_t pipe,
                            qsee_pipe_desc_msk_t pipe_desc_msk,
                            uint32_t flags, qsee_pipe_key_param_t* key_info_ptr);

#endif /*QSEE_CE_PIPE_H*/


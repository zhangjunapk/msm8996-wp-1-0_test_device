#ifndef QSEE_KS_H
#define QSEE_KS_H

/**
@file qsee_ks.h
@brief This file is the API for the keystore.
The keystore is used to store keys on the non-volatile storage
(i.e. eMMC) on dedicated partitions. Normally, the partition is
encrypted and stored via fastbot during manifacturing.
*/

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                      TrustZone Keystore

General Description
  Implement generic keystore functionality.

Copyright (c) 2013 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                           Edit History

  $Header: //components/rel/core.tz/1.0.3.c1/api/securemsm/trustzone/qsee/qsee_ks.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

when         who     what, where, why
--------     ---     -------------------------------------------------------
04/05/13     pre     Initial Revision
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <stdint.h>

/*===========================================================================

                 DEFINITIONS AND TYPE DECLARATIONS

===========================================================================*/

/*===========================================================================

                 DEFINITIONS AND TYPE DECLARATIONS

===========================================================================*/
typedef enum
{
  KS_DIR_MD           = 0,

  KS_FREE_MD_VAL      = 1,

  KS_MD_MAX_USAGE     = 0x7FFFFFFF
} ks_ent_md_t;

typedef struct
{
  uint8_t auth_tag[32];
} ks_auth_tag_t;

typedef struct
{
  uint8_t key_id[32];
} ks_ent_id_t;

typedef struct
{
  uint8_t usr_pwd[32];
} ks_ent_pwd_t;

typedef struct
{
  uint8_t* ks_ptr;
  uint32_t ks_len;
  uint32_t max_ks_len;
  const char* ks_name;
} ks_obj_t;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
/**
   Retrieves a key from the keystore given the key's ID and metadata.
   Alternatively, this function may be called with NULL output
   parameters to query whether a key exists in the keystore.

   @param[out] key      The key, if found
   @param[out] key_len  The length of the key

   @return  E_SUCCESS    On success
           -E_FAILURE    Key with given ID and MD does not exist
                         in keystore

   @pre The keystore passed to this function must be a valid keystore.
   @pre id parameter must point to a valid-length key id
 */
int qsee_ks_get_key(uint8_t* keystore,
		    uint32_t keystore_len,
		    const ks_ent_id_t* id,
		    const ks_ent_md_t* md,
		    const uint8_t**      key,
		    uint32_t*            key_len);

/**
   Decryption and authentication of the keys.

   @return  E_SUCCESS      On success
           -E_NO_DATA      If the keystore has no keys
           -E_OUT_OF_RANGE If there is a key whose length is out of the
                           given keystore length or causes an overflow
           -E_FAILURE      All other failures

   @pre Fixed TrustZone keystore area in DDR must be XPU protected
        before calling into this function

   @pre keystore_len must be at least the size of the keystore header

   @pre keystore input pointer and length do not fall into any secure
        memory area, is less than the QSEE storage region size in DDR
        and will not cause an overflow
 */
int qsee_ks_decrypt(uint8_t* keystore, uint32_t keystore_len);


/**
   Removes a key from QSEE storage

   @param flags        TBD
   @param key_id_ptr   Key ID data used to access the generated 
                       key in the future. Associate with a
                       specific usecase
   @param user_pwd_ptr User password to associate with the use 
                       case

   @retval E_SUCCESS                   on success
           QSEE_RESULT_FAIL_KS_OP      operation failed
           QSEE_RESULT_FAIL_LOAD_KS    if the keystore could not be loaded
                                       from EMMC or if the version could
                                       not be verified from RPMB
           QSEE_RESULT_FAIL_KEY_ID_DNE  if the key did not exist
                                        in the keystore
           QSEE_RESULT_FAIL_SAVE_KS     if the keystore update
                                        isn't saved
           QSEE_RESULT_FAIL_MAX_ATTEMPT max wrong password
                                        entries made
            
           
*/
int qsee_ks_delete_key(uint32_t flags,
                       ks_ent_id_t* key_id_ptr, 
                       ks_ent_pwd_t* user_pwd_ptr);

#endif /* #ifndef QSEE_KS_H */

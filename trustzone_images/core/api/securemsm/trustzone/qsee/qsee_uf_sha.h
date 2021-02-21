#ifndef QSEE_UF_SHA_H
#define QSEE_UF_SHA_H

/**
@file qsee_uf_sha.h
@brief Provide Software crypto Hash and Hmac API wrappers
*/

/*===========================================================================
   Copyright (c) 2012 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header:
  $DateTime:
  $Author:

when       who      what, where, why
--------   ---      ------------------------------------
03/05/13   amen      Initial version.

===========================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <stdint.h>

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/**
 * SHA DIGEST and Block sizes
  */
#define SW_SHA_BLOCK_SIZE               64
#define SW_SHA1_BLOCK_SIZE              SW_SHA_BLOCK_SIZE
#define SW_SHA1_DIGEST_SIZE             (160 / 8)

#define SW_SHA256_BLOCK_SIZE            SW_SHA1_BLOCK_SIZE
#define SW_SHA256_DIGEST_SIZE           (256 / 8)

#define SW_SHA224_BLOCK_SIZE            SW_SHA256_BLOCK_SIZE
#define SW_SHA224_DIGEST_SIZE           (224 / 8)

#define SW_SHA512_BLOCK_SIZE            128
#define SW_SHA512_DIGEST_SIZE           (512 / 8)

#define SW_SHA384_BLOCK_SIZE            SW_SHA512_BLOCK_SIZE
#define SW_SHA384_DIGEST_SIZE           (384 / 8)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/**
 * Enum for Hash algorithm type
 */
typedef enum
{
  SW_AUTH_ALG_NULL               = 0x1,
  SW_AUTH_ALG_SHA1               = 0x2,
  SW_AUTH_ALG_SHA256,
  SW_AUTH_ALG_SHA224,
  SW_AUTH_ALG_SHA384,
  SW_AUTH_ALG_SHA512,
  SW_AUTH_ALG_INVALID            = 0x7FFFFFFF
} SW_Auth_Alg_Type;

#ifndef SW_CRYPTO_TYPEDEF
#define SW_CRYPTO_TYPEDEF
typedef uint32_t sw_crypto_errno_enum_type;

typedef struct
{
  void                              *pvBase;
  uint32_t                            dwLen;
} __attribute__((__packed__)) IovecType;

typedef struct
{
  IovecType                     *iov;
  uint32_t                        size;
} __attribute__((__packed__)) IovecListType;


typedef void CryptoCntxHandle;
#endif

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/**
 * @brief Main function for sha1/sha256 and hmac
 *
 * @param handle       [in] Pointer of pointer to hash context
 * @param auth_alg     [in] see SW_Auth_Alg_Type
 *
 * @return errno_enum_type
 *
 * @see
 *
 */
sw_crypto_errno_enum_type qsee_SW_Hash_Init(CryptoCntxHandle **handle, SW_Auth_Alg_Type auth_alg);


/**
 * @brief Reset a hash context
 *
 * @param handle       [in] Pointer of pointer to cipher context
 *
 * @return errno_enum_type
 *
 * @see
 *
 */
sw_crypto_errno_enum_type qsee_SW_Hash_Reset(CryptoCntxHandle *handle);

/**
 * @brief Update function for sha1/sha256 for intermediate data
 *        blocks hash
 *
 * @param handle       [in] Pointer of pointer to hash context
 * @param ioVecIn      [in] Input to cipher
 *
 * @return errno_enum_type
 *
 * @see
 *
 */
sw_crypto_errno_enum_type qsee_SW_Hash_Update(CryptoCntxHandle *handle,IovecListType ioVecIn);

/**
 * @brief Sha1/Sha256 last block hash update
 *
 * @param handle       [in] Pointer of pointer to hash context
 * @param ioVecOut     [in] Output from cipher
 *
 * @return errno_enum_type
 *
 * @see
 *
 */
sw_crypto_errno_enum_type qsee_SW_Hash_Final (CryptoCntxHandle *handle,IovecListType *ioVecOut);

/**
 * @brief Main function for sha1/sha256 hmac
 *
 * @param key_ptr      [in] Pointer of Key for HMAC
 * @param keylen       [in] key length (16bytes for SHA1 /
 *                          32bytes for SHA256)
 * @param ioVecIn      [in] Input to cipher
 * @param ioVecOut     [in] Output from cipher
 * @param pAlgo        [in] See enum SW_Auth_Alg_Type
 *
 * @return errno_enum_type
 *
 * @see
 *
 */
sw_crypto_errno_enum_type qsee_SW_Hmac (uint8_t * key_ptr, uint32_t keylen, IovecListType ioVecIn,
                              IovecListType * ioVecOut, SW_Auth_Alg_Type  pAlgo);

#endif /* QSEE_UF_SHA_H */

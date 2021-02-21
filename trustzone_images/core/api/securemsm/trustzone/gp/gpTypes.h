#ifndef GPTYPES_H
#define GPTYPES_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 * Table of Contents
 * -------------------------------------------------------------------------*/
/*
 * 1. Basic type definitions
 *    a) Basic types
 * 2. TEE type definitions
 *    a) TEE Data types
 *        -TEE Core Framework data types (UUID, params, sessions, etc..)
 *        -TEE Trusted Storage types
 *        -TEE Crypto types
 *        -TEE Time types
 *        -TEE Arithmetical types
 * 3. TEE Constants
 *    a) TEE Core Framework constants
 *        -TEE Error codes
 *        -TEE Param types
 *        -TEE Login types
 *        -TEE Origin codes
 *        -TEE Property Set pseudo-handles
 *        -TEE Memory Access rights
 *        -TEE Handle values
 *    b) TEE Trusted Storage constants
 *        -TEE Object Storage constants
 *        -TEE Data Flag constants
 *        -TEE Usage constants
 *        -TEE Handle Flag constants
 *        -TEE Operation constants
 *        -TEE Miscellaneous constants
 *    c) TEE Crypto constants
 *        -TEE Crypto algorithms
 *        -TEE Transient Object types
 *        -TEE Object/Operation attributes
 *        -TEE attribute ID flags
 *
 */

/*----------------------------------------------------------------------------
 * Basic GP types
 * -------------------------------------------------------------------------*/
//typedef unsigned  char  uint8_t;
//typedef signed    char  int8_t;
//typedef uint16  uint16_t;
//typedef int16   int16_t;
//typedef uint32  uint32_t;
//typedef int32   int32_t;
//typedef uint64  uint64_t;
//typedef int64   int64_t;

//#define uint16_t uint16
//#define int16_t int16
//#define uint32_t uint32
//#define int32_t int32
//typedef unsigned short uint16_t;
//typedef signed short int16_t;
//typedef unsigned int uint32_t;
//typedef signed int int32_t;

/* For future revision to 64-bit cpu */
//typedef unsigned long uint64_t;
//typedef signed long int64_t;
//typedef unsigned long size_t;

/*----------------------------------------------------------------------------
 * TEE data types
 * -------------------------------------------------------------------------*/

/* Return type */
typedef uint32_t TEE_Result;
typedef TEE_Result TEEC_Result;

/* TEE Arithmetical types */
typedef uint32_t TEE_BigInt; /* placeholder for large multi-precision int */
typedef uint32_t TEE_BigIntFMMContext; /* placeholder for context */
typedef uint32_t TEE_BigIntFMM; /* placeholder for mem structure of Fast modular mult */
#define TEE_BigIntSizeInU32(n) ((((n)+31)/32)+2)

#ifndef NULL
#define NULL 0
#endif

typedef struct TEE_Buffer
{
  void*     buffer;
  uint32_t  size;
} TEE_Buffer;

typedef struct TEE_Value
{
  uint32_t a;
  uint32_t b;
} TEE_Value;

typedef union TEE_Param
{
  TEE_Buffer  memref;
  TEE_Value   value;
} TEE_Param;

/*---------------------------------------------------------
    Common type definition
    ---------------------------------------------------------*/
typedef struct TEE_UUID
{
  uint32_t timeLow;
  uint16_t timeMid;
  uint16_t timeHiAndVersion;
  uint8_t  clockSeqAndNode[8];
} TEE_UUID;

/*---------------------------------------------------------
    Type definition for Trusted Core Framework API
    ---------------------------------------------------------*/
typedef struct TEE_Identity
{
  uint32_t login;
  TEE_UUID uuid;
} TEE_Identity;

// Sessions
typedef struct __TEE_TASessionHandle* TEE_TASessionHandle; /* Opaque handle */

#define TA_EXPORT //__declspec(dllexport)

// Property Set
struct __TEE_PropSetHandle;
typedef struct __TEE_PropSetHandle* TEE_PropSetHandle; /* Opaque handle */

/*---------------------------------------------------------
    Type definition for Time API
    ---------------------------------------------------------*/
typedef struct
{
  uint32_t seconds;
  uint32_t millis;
} TEE_Time;

/*---------------------------------------------------------
    Type definition for Data Storage
    ---------------------------------------------------------*/
typedef struct
{
  uint32_t attributeID;
  union
  {
    struct
    {
      void* buffer; /* [inbuf] */
      size_t length;
    } ref;
    struct
    {
      uint32_t a, b;
    } value;
  } content;
} TEE_Attribute;

typedef struct
{
  uint32_t objectType;
  uint32_t objectSize;
  uint32_t maxObjectSize;
  uint32_t objectUsage;
  uint32_t dataSize;
  uint32_t dataPosition;
  uint32_t handleFlags;
  uint32_t mode;
} TEE_ObjectInfo;

typedef enum
{
  TEE_DATA_SEEK_SET = 0,
  TEE_DATA_SEEK_CUR,
  TEE_DATA_SEEK_END
} TEE_Whence;

// Obj
struct __TEE_ObjectHandle;
typedef struct __TEE_ObjectHandle* TEE_ObjectHandle; /* Opaque handle */

// Obj enum
struct __TEE_ObjectEnumHandle;
typedef struct __TEE_ObjectEnumHandle* TEE_ObjectEnumHandle; /* Opaque handle */

/* TEE Crypto types */

// Operation mode
typedef enum {
  TEE_MODE_ENCRYPT  = 0,
  TEE_MODE_DECRYPT  = 1,
  TEE_MODE_SIGN     = 2,
  TEE_MODE_VERIFY   = 3,
  TEE_MODE_MAC      = 4,
  TEE_MODE_DIGEST   = 5,
  TEE_MODE_DERIVE   = 6
} TEE_OperationMode;

// Operation info
typedef struct
{
  uint32_t algorithm;
  uint32_t operationClass;
  uint32_t mode;
  uint32_t digestLength;
  uint32_t maxKeySize;
  uint32_t keySize;
  uint32_t requiredKeyUsage;
  uint32_t handleState;
} TEE_OperationInfo;

typedef struct
{
  uint32_t keySize;
  uint32_t requiredKeyUsage;
} TEE_OperationInfoKey;

typedef struct
{
  uint32_t algorithm;
  uint32_t operationClass;
  uint32_t mode;
  uint32_t digestLength;
  uint32_t maxKeySize;
  uint32_t keySize;
  uint32_t requiredKeyUsage;
  uint32_t handleState;
  uint32_t operationState;
  uint32_t numberOfKeys;
  TEE_OperationInfoKey keyInformation[];
} TEE_OperationInfoMultiple;

// Operation Handle
struct __TEE_OperationHandle;
typedef struct __TEE_OperationHandle* TEE_OperationHandle; /* Opaque handle */

/*----------------------------------------------------------------------------
 * TEE Core framework constants
 * -------------------------------------------------------------------------*/

/* TEE Error codes */

#define TEE_SUCCESS                           0x00000000    /* Operation success */
#define TEE_ERROR_CORRUPT_OBJECT              0xF0100001
#define TEE_ERROR_CORRUPT_OBJECT_2            0xF0100002
#define TEE_ERROR_STORAGE_NOT_AVAILABLE       0xF0100003
#define TEE_ERROR_STORAGE_NOT_AVAILABLE_2     0xF0100004
#define TEE_ERROR_GENERIC                     0xFFFF0000    /* Non-specific error */
#define TEE_ERROR_ACCESS_DENIED               0xFFFF0001    /* Access priveleges are not sufficient */
#define TEE_ERROR_CANCEL                      0xFFFF0002    /* Operation was cancelled */
#define TEE_ERROR_ACCESS_CONFLICT             0xFFFF0003    /* Concurrent accesses caused conflict */
#define TEE_ERROR_EXCESS_DATA                 0xFFFF0004    /* Too much data for the requested operation was provided */
#define TEE_ERROR_BAD_FORMAT                  0xFFFF0005    /* The input data was of invalid format */
#define TEE_ERROR_BAD_PARAMETERS              0xFFFF0006    /* The input parameters were invalid */
#define TEE_ERROR_BAD_STATE                   0xFFFF0007    /* The operation is not valid in current state */
#define TEE_ERROR_ITEM_NOT_FOUND              0xFFFF0008    /* The requested data could not be found */
#define TEE_ERROR_NOT_IMPLEMENTED             0xFFFF0009    /* The operation should be implemented, but does not currently exist */
#define TEE_ERROR_NOT_SUPPORTED               0xFFFF000A    /* The operation is valid, but not supported */
#define TEE_ERROR_NO_DATA                     0xFFFF000B    /* Expected data was missing */
#define TEE_ERROR_OUT_OF_MEMORY               0xFFFF000C    /* System ran out of resources */
#define TEE_ERROR_BUSY                        0xFFFF000D    /* System is busy with something else */
#define TEE_ERROR_COMMUNICATION               0xFFFF000E    /* Communication with a remote party failed */
#define TEE_ERROR_SECURITY                    0xFFFF000F    /* A security fault was detected */
#define TEE_ERROR_SHORT_BUFFER                0xFFFF0010    /* The buffer is NULL or is too small */
#define TEE_PENDING                           0xFFFF2000    /* The operation is pending action */
#define TEE_ERROR_TIMEOUT                     0xFFFF3001    /* The operation has timed out and could not complete */
#define TEE_ERROR_OVERFLOW                    0xFFFF300F    /* An integer overflow has occurred */
#define TEE_ERROR_TARGET_DEAD                 0xFFFF3024    /* TA has shut down */
#define TEE_ERROR_STORAGE_NO_SPACE            0xFFFF3041    /* Insufficient space available to create persistent object */
#define TEE_ERROR_MAC_INVALID                 0xFFFF3071    /* The computed MAC does not correspond with passed-in param */
#define TEE_ERROR_SIGNATURE_INVALID           0xFFFF3072    /* The signature is invalid */
#define TEE_ERROR_TIME_NOT_SET                0xFFFF5000    /* Persistent object is not currently set */
#define TEE_ERROR_TIME_NEEDS_RESET            0xFFFF5001    /* Persistent object is set, but may be corrupted and can no longer be trusted */
#define TEEC_SUCCESS                          TEE_SUCCESS
#define TEEC_ERROR_GENERIC                    TEE_ERROR_GENERIC
#define TEEC_ERROR_ACCESS_DENIED              TEE_ERROR_ACCESS_DENIED
#define TEEC_ERROR_CANCEL                     TEE_ERROR_CANCEL
#define TEEC_ERROR_ACCESS_CONFLICT            TEE_ERROR_ACCESS_CONFLICT
#define TEEC_ERROR_EXCESS_DATA                TEE_ERROR_EXCESS_DATA
#define TEEC_ERROR_BAD_FORMAT                 TEE_ERROR_BAD_FORMAT
#define TEEC_ERROR_BAD_PARAMETERS             TEE_ERROR_BAD_PARAMETERS
#define TEEC_ERROR_BAD_STATE                  TEE_ERROR_BAD_STATE
#define TEEC_ERROR_ITEM_NOT_FOUND             TEE_ERROR_ITEM_NOT_FOUND
#define TEEC_ERROR_NOT_IMPLEMENTED            TEE_ERROR_NOT_IMPLEMENTED
#define TEEC_ERROR_NOT_SUPPORTED              TEE_ERROR_NOT_SUPPORTED
#define TEEC_ERROR_NO_DATA                    TEE_ERROR_NO_DATA
#define TEEC_ERROR_OUT_OF_MEMORY              TEE_ERROR_OUT_OF_MEMORY
#define TEEC_ERROR_BUSY                       TEE_ERROR_BUSY
#define TEEC_ERROR_COMMUNICATION              TEE_ERROR_COMMUNICATION
#define TEEC_ERROR_SECURITY                   TEE_ERROR_SECURITY
#define TEEC_ERROR_SHORT_BUFFER               TEE_ERROR_SHORT_BUFFER
#define TEEC_ERROR_TARGET_DEAD                TEE_ERROR_TARGET_DEAD

/* TEE Login types */
#define TEE_LOGIN_PUBLIC                      0x00000000
#define TEE_LOGIN_USER                        0x00000001
#define TEE_LOGIN_GROUP                       0x00000002
#define TEE_LOGIN_APPLICATION                 0x00000004
#define TEE_LOGIN_APPLICATION_USER            0x00000005
#define TEE_LOGIN_APPLICATION_GROUP           0x00000006
#define TEE_LOGIN_TRUSTED_APP                 0xF0000000

/* TEE Param types */
#define TEE_PARAM_TYPE_NONE                   0x0
#define TEE_PARAM_TYPE_VALUE_INPUT            0x1
#define TEE_PARAM_TYPE_VALUE_OUTPUT           0x2
#define TEE_PARAM_TYPE_VALUE_INOUT            0x3
#define TEE_PARAM_TYPE_MEMREF_INPUT           0x5
#define TEE_PARAM_TYPE_MEMREF_OUTPUT          0x6
#define TEE_PARAM_TYPE_MEMREF_INOUT           0x7

/* TEE Memory Access rights */
#define TEE_MEMORY_ACCESS_READ                0x1
#define TEE_MEMORY_ACCESS_WRITE               0x2
#define TEE_MEMORY_ACCESS_ANY_OWNER           0x4

//Macros to retrieve Param Types
#define TEE_PARAM_TYPES(t0,t1,t2,t3)          ((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))
#define TEE_PARAM_TYPE_GET(t, i)              (((t) >> (i*4)) & 0xF)

/* TEE Origin codes */
#define TEE_ORIGIN_API                        0x1
#define TEE_ORIGIN_COMMS                      0x2
#define TEE_ORIGIN_TEE                        0x3
#define TEE_ORIGIN_TRUSTED_APP                0x4

#define TEE_TIMEOUT_INFINITE                  0xFFFFFFFF

/* TEE Property Set pseudo-handles */
#define TEE_PROPSET_CURRENT_TA                (TEE_PropSetHandle)0xFFFFFFFF
#define TEE_PROPSET_CURRENT_CLIENT            (TEE_PropSetHandle)0xFFFFFFFE
#define TEE_PROPSET_TEE_IMPLEMENTATION        (TEE_PropSetHandle)0xFFFFFFFD

/*----------------------------------------------------------------------------
 * TEE Trusted storage constants
 * -------------------------------------------------------------------------*/
/* Object storage constants */
#define TEE_HANDLE_NULL                       (NULL)
#define TEE_OBJECT_STORAGE_PRIVATE            0x00000001

/* Data Flag constants */

#define TEE_DATA_FLAG_ACCESS_READ             0x00000001
#define TEE_DATA_FLAG_ACCESS_WRITE            0x00000002
#define TEE_DATA_FLAG_ACCESS_WRITE_META       0x00000004
#define TEE_DATA_FLAG_SHARE_READ              0x00000010
#define TEE_DATA_FLAG_SHARE_WRITE             0x00000020
#define TEE_DATA_FLAG_CREATE                  0x00000200
#define TEE_DATA_FLAG_EXCLUSIVE               0x00000400

/* Usage constants */

#define TEE_USAGE_EXTRACTABLE                 0x00000001
#define TEE_USAGE_ENCRYPT                     0x00000002
#define TEE_USAGE_DECRYPT                     0x00000004
#define TEE_USAGE_MAC                         0x00000008
#define TEE_USAGE_SIGN                        0x00000010
#define TEE_USAGE_VERIFY                      0x00000020
#define TEE_USAGE_DERIVE                      0x00000040

/* Handle Flag constants */

#define TEE_HANDLE_FLAG_UNINITIALIZED         0x00000000
#define TEE_HANDLE_FLAG_PERSISTENT            0x00010000
#define TEE_HANDLE_FLAG_INITIALIZED           0x00020000
#define TEE_HANDLE_FLAG_KEY_SET               0x00040000
#define TEE_HANDLE_FLAG_EXPECT_TWO_KEYS       0x00080000

/* Operation constants */

#define TEE_OPERATION_CIPHER                  1
#define TEE_OPERATION_MAC                     3
#define TEE_OPERATION_AE                      4
#define TEE_OPERATION_DIGEST                  5
#define TEE_OPERATION_ASYMMETRIC_CIPHER       6
#define TEE_OPERATION_ASYMMETRIC_SIGNATURE    7
#define TEE_OPERATION_KEY_DERIVATION          8

/* Operation States */
#define TEE_OPERATION_STATE_INITIAL           0x00000000
#define TEE_OPERATION_STATE_ACTIVE            0x00000001
/* Reserved for future use                    0x00000002-0x7FFFFFFF */
/* Implementation defined                     0x80000000-0xFFFFFFFF */

/* Miscellaneous constants */
#define TEE_DATA_MAX_POSITION                 0xFFFFFFFF
#define TEE_OBJECT_ID_MAX_LEN                 64
#define TEE_STORAGE_PRIVATE                   1
#define TEE_ITEM_NOT_FOUND                    0xFFFF6001          //Not defined in GP Spec continue after the last error code

/*----------------------------------------------------------------------------
 * TEE Crypto constants
 * -------------------------------------------------------------------------*/

/* TEE Crypto algorithms */

#define TEE_ALG_AES_ECB_NOPAD                 0x10000010
#define TEE_ALG_AES_CBC_NOPAD                 0x10000110
#define TEE_ALG_AES_CTR                       0x10000210
#define TEE_ALG_AES_CTS                       0x10000310
#define TEE_ALG_AES_XTS                       0x10000410
#define TEE_ALG_AES_CBC_MAC_NOPAD             0x30000110
#define TEE_ALG_AES_CBC_MAC_PKCS5             0x30000510
#define TEE_ALG_AES_CMAC                      0x30000610
#define TEE_ALG_AES_CCM                       0x40000710
#define TEE_ALG_AES_GCM                       0x40000810
#define TEE_ALG_AES_GCM_SW                    0x40000910
#define TEE_ALG_AES_CCM_SW                    0x40000A10
#define TEE_ALG_DES_ECB_NOPAD                 0x10000011
#define TEE_ALG_DES_CBC_NOPAD                 0x10000111
#define TEE_ALG_DES_CBC_MAC_NOPAD             0x30000111
#define TEE_ALG_DES_CBC_MAC_PKCS5             0x30000511
#define TEE_ALG_DES3_ECB_NOPAD                0x10000013
#define TEE_ALG_DES3_CBC_NOPAD                0x10000113
#define TEE_ALG_DES3_CBC_MAC_NOPAD            0x30000113
#define TEE_ALG_DES3_CBC_MAC_PKCS5            0x30000513
#define TEE_ALG_RSASSA_PKCS1_V1_5_MD5         0x70001830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA1        0x70002830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA224      0x70003830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA256      0x70004830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA384      0x70005830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA512      0x70006830
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1    0x70212930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA224  0x70313930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA256  0x70414930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA384  0x70515930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA512  0x70616930
#define TEE_ALG_RSAES_PKCS1_V1_5              0x60000130
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1    0x60210230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA224  0x60310230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA256  0x60410230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA384  0x60510230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA512  0x60610230
#define TEE_ALG_RSA_NOPAD                     0x60000030
#define TEE_ALG_DSA_SHA1                      0x70002131
#define TEE_ALG_DH_DERIVE_SHARED_SECRET       0x80000032
#define TEE_ALG_MD5                           0x50000001
#define TEE_ALG_SHA1                          0x50000002
#define TEE_ALG_SHA224                        0x50000003
#define TEE_ALG_SHA256                        0x50000004
#define TEE_ALG_SHA384                        0x50000005
#define TEE_ALG_SHA512                        0x50000006
#define TEE_ALG_HMAC_MD5                      0x30000001
#define TEE_ALG_HMAC_SHA1                     0x30000002
#define TEE_ALG_HMAC_SHA224                   0x30000003
#define TEE_ALG_HMAC_SHA256                   0x30000004
#define TEE_ALG_HMAC_SHA384                   0x30000005
#define TEE_ALG_HMAC_SHA512                   0x30000006

/* TEE Transient Object types */

#define TEE_TYPE_AES                          0xA0000010  /* 128, 192, or 256 bits */
#define TEE_TYPE_DES                          0xA0000011  /* Always 56 bits */
#define TEE_TYPE_DES3                         0xA0000013  /* 112 or 168 bits */
#define TEE_TYPE_HMAC_MD5                     0xA0000001  /* Between 64 and 512 bits, multiple of 8 bits */
#define TEE_TYPE_HMAC_SHA1                    0xA0000002  /* Between 80 and 512 bits, multiple of 8 bits */
#define TEE_TYPE_HMAC_SHA224                  0xA0000003  /* Between 112 and 512 bits, multiple of 8 bits */
#define TEE_TYPE_HMAC_SHA256                  0xA0000004  /* Between 192 and 1024 bits, multiple of 8 bits */
#define TEE_TYPE_HMAC_SHA384                  0xA0000005  /* Between 256 and 1024 bits, multiple of 8 bits */
#define TEE_TYPE_HMAC_SHA512                  0xA0000006  /* Between 192 and 1024 bits, multiple of 8 bits */
#define TEE_TYPE_RSA_PUBLIC_KEY               0xA0000030  /* Object size is the number of bits in the modulus. Min key size 256 bits, must support up to 2048 bit key sizes */
#define TEE_TYPE_RSA_KEYPAIR                  0xA1000030  /* Same as RSA public key size */
#define TEE_TYPE_DSA_PUBLIC_KEY               0xA0000031  /* Between 512 and 1024 bits, multiple of 64 bits */
#define TEE_TYPE_DSA_KEYPAIR                  0xA1000031  /* Same as DSA public key size */
#define TEE_TYPE_DH_KEYPAIR                   0xA1000032  /* From 256 to 2048 bits */
#define TEE_TYPE_GENERIC_SECRET               0xA0000000  /* Multiple of 8 bits, up to 4096 bits */

/* TEE Object/Operation attributes */

#define TEE_ATTR_SECRET_VALUE                 0xC0000000
#define TEE_ATTR_LABEL                        0xC0000100
#define TEE_ATTR_CONTEXT                      0xC0000200
#define TEE_ATTR_INPUT_KEY                    0xC0000300
#define TEE_ATTR_RSA_MODULUS                  0xD0000130
#define TEE_ATTR_RSA_PUBLIC_EXPONENT          0xD0000230
#define TEE_ATTR_RSA_PRIVATE_EXPONENT         0xC0000330
#define TEE_ATTR_RSA_PRIME1                   0xC0000430
#define TEE_ATTR_RSA_PRIME2                   0xC0000530
#define TEE_ATTR_RSA_EXPONENT1                0xC0000630
#define TEE_ATTR_RSA_EXPONENT2                0xC0000730
#define TEE_ATTR_RSA_COEFFICIENT              0xC0000830
#define TEE_ATTR_DSA_PRIME                    0xD0001031
#define TEE_ATTR_DSA_SUBPRIME                 0xD0001131
#define TEE_ATTR_DSA_BASE                     0xD0001231
#define TEE_ATTR_DSA_PUBLIC_VALUE             0xD0000131
#define TEE_ATTR_DSA_PRIVATE_VALUE            0xC0000231
#define TEE_ATTR_DH_PRIME                     0xD0001032
#define TEE_ATTR_DH_SUBPRIME                  0xD0001132
#define TEE_ATTR_DH_BASE                      0xD0001232
#define TEE_ATTR_DH_X_BITS                    0xF0001332
#define TEE_ATTR_DH_PUBLIC_VALUE              0xD0000132
#define TEE_ATTR_DH_PRIVATE_VALUE             0xC0000232
#define TEE_ATTR_RSA_OAEP_LABEL               0xD0000930
#define TEE_ATTR_RSA_PSS_SALT_LENGTH          0xF0000A30
#define TEE_ATTR_RSA_KEY_CRT_DECRYPT          0xF0000B30

/* TEE attribute ID flags */

#define TEE_ATTR_FLAG_VALUE                   0x20000000
#define TEE_ATTR_FLAG_PUBLIC                  0x10000000

/* TEE crypto GP macros */

//size in bytes
#define TEE_ALG_MD5_DIGEST_LENGTH             (128 / 8)
#define TEE_ALG_SHA1_DIGEST_LENGTH            (160 / 8)
#define TEE_ALG_SHA256_DIGEST_LENGTH          (256 / 8)
#define TEE_ALG_SHA224_DIGEST_LENGTH          (224 / 8)
#define TEE_ALG_SHA512_DIGEST_LENGTH          (512 / 8)
#define TEE_ALG_SHA384_DIGEST_LENGTH          (384 / 8)

//size in bytes
#define TEE_ALG_AES_BLK_SIZE                  16
//size in bits
#define TEE_ALG_AES128_LENGTH                 (16*8)
#define TEE_ALG_AES192_LENGTH                 (24*8)
#define TEE_ALG_AES256_LENGTH                 (32*8)

//size in bits
#define TEE_ALG_DES_LENGTH                    64
#define TEE_ALG_DES3_LENGTH_128               128
#define TEE_ALG_DES3_LENGTH_192               192

//size in bits
#define TEE_ALG_HMAC_MD5_KEY_MIN              64
#define TEE_ALG_HMAC_MD5_KEY_MAX              512

#define TEE_ALG_HMAC_SHA1_KEY_MIN             80
#define TEE_ALG_HMAC_SHA1_KEY_MAX             512

#define TEE_ALG_HMAC_SHA256_KEY_MIN           192
#define TEE_ALG_HMAC_SHA256_KEY_MAX           1024

#define TEE_ALG_HMAC_SHA224_KEY_MIN           112
#define TEE_ALG_HMAC_SHA224_KEY_MAX           512

#define TEE_ALG_HMAC_SHA512_KEY_MIN           256
#define TEE_ALG_HMAC_SHA512_KEY_MAX           1024

#define TEE_ALG_HMAC_SHA384_KEY_MIN           256
#define TEE_ALG_HMAC_SHA384_KEY_MAX           1024

#define TEE_ALG_RSA_MIN_KEY_SIZE              256
#define TEE_ALG_RSA_MAX_KEY_SIZE              QSEE_MAX_KEY_SIZE

#define TEE_ALG_GENERIC_SECRET_MAX_KEY_SIZE   4096
#define TEE_DH_MIN_KEY_SIZE					  256
#define TEE_DH_MAX_KEY_SIZE					  2048

/*----------------------------------------------------------------------------
 * Implementation specific errors
 * -------------------------------------------------------------------------*/
#define TEE_ERROR_UNUSED                            0x80000000
#define TEE_ERROR_GENERATE_RANDOM_FAILED            0x80000001
#define TEE_ERROR_CURRENT_SESSION_NOT_SET           0x80000002
#define TEE_ERROR_INVALID_SESSION_ID                0x80000003
#define TEE_ERROR_APP_INIT_FAILED                   0x80000004
#define TEE_ERROR_QSEECOM_REQUEST_INCORRECT_SIZE    0x80000005
#define TEE_ERROR_QSEECOM_RESPONSE_INCORRECT_SIZE   0x80000006
#define TEE_ERROR_QSEECOM_INVALID_GP_COMMAND        0x80000007
#define TEE_ERROR_INVALID_LOGIN_METHOD              0x80000008
#define TEE_ERROR_NON_MONOTONIC_TIME                0x80000009
#define TEE_ERROR_MINK_IPC_ERROR                    0x80000010

/*----------------------------------------------------------------------------
 * Generic GP Constants
 * -------------------------------------------------------------------------*/
#define MAX_GP_PARAMS                               4

/*----------------------------------------------------------------------------
 * Include Files for various GP APIs
 * -------------------------------------------------------------------------*/
#include "gpArithmetic.h"
#include "gpCancellations.h"
#include "gpCrypto.h"
#include "gpGenericObjects.h"
#include "gpInternalClientAPIs.h"
#include "gpMemoryMgmt.h"
#include "gpPanics.h"
#include "gpPersistentObjects.h"
#include "gpPropertyAccess.h"
#include "gpTAInterfaceAPIs.h"
#include "gpTime.h"
#include "gpTransientObjects.h"

#include "gpAppLibMain.h"
#include "gpUtils.h"
#include "qsee_log.h"

#ifdef _SIMULATOR_ENV
#include "SimulatorEnv.h"
#endif

/*------------------------------------------------------------------------------
               --- WARNING --- WARNING --- WARNING ---
               The following definitions are not part of the TEE Internal API
               ------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
      Trace Functions
      ------------------------------------------------------------------------------*/
//void _SLogTrace(
//               const char *message,
//               ... /* arguments */);
//void _SLogWarning(
//               const char *message,
//               ... /* arguments */);
//void _SLogError(
//               const char *message,
//               ... /* arguments */);

#ifndef TEE_NO_TRACE

//#define SLogTrace    _SLogTrace
//#define SLogWarning  _SLogWarning
//#define SLogError    _SLogError

#define SLogTrace(xx_fmt, ...)    QSEE_LOG(QSEE_LOG_MSG_DEBUG, #xx_fmt, ##__VA_ARGS__)
#define SLogWarning(xx_fmt, ...)  QSEE_LOG(QSEE_LOG_MSG_ERROR, #xx_fmt, ##__VA_ARGS__)
#define SLogError(xx_fmt, ...)    QSEE_LOG(QSEE_LOG_MSG_FATAL, #xx_fmt, ##__VA_ARGS__)

#else /* defined(TEE_NO_TRACE) */

/* Note that the following code depends on the compiler's supporting variadic macros */
#define SLogTrace(...)   do {} while(false)
#define SLogWarning(...) do {} while(false)
#define SLogError(...)   do {} while(false)

#endif /* !defined(TEE_NO_TRACE) */

#define GPLOG_ERROR(x) \
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "%s:%d retvalue=[0x%x]", __FUNCTION__, __LINE__, x)

#define GPLOG_ERROR2(s, x) \
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "%s:%d %s retvalue=[0x%x]", __FUNCTION__, __LINE__, s, x)

#define GPLOG_FATAL(x) \
  QSEE_LOG(QSEE_LOG_MSG_FATAL, "%s:%d retvalue=[0x%x]", __FUNCTION__, __LINE__, x)

#define GPLOG_FATAL2(s, x) \
  QSEE_LOG(QSEE_LOG_MSG_FATAL, "%s:%d %s retvalue=[0x%x]", __FUNCTION__, __LINE__, s, x)

#define S_VAR_NOT_USED(variable) do{(void)(variable);}while(0);

#endif /* GPTYPES_H */

#ifndef GPCRYPTO_H
#define GPCRYPTO_H

/* ------------------------------------------------------------------------
** Includes
** ------------------------------------------------------------------------ */

#include "gpTypes.h"


#ifdef __cplusplus
extern "C"
  {
#endif


/*==============================================================

                  General API's

===============================================================*/

/**
 * @brief allocates a handle for a new cryptographic operation and sets the mode and algorithm type
 *
 * The TEE_AllocateOperation function allocates a handle for a new cryptographic operation and sets the mode and algorithm type.
 * If this function does not return with TEE_SUCCESS then there is no valid handle value.
 *     Supported algorithm                   Supported mode                         Supported maxKeySize
 *     TEE_ALG_AES_ECB_NOPAD                 TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     128, 256bits
 *     TEE_ALG_AES_CBC_NOPAD                 TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     128, 256bits
 *     TEE_ALG_AES_CTR                       TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     128, 256bits
 *     TEE_ALG_AES_CTS                       TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     128, 256bits
 *     TEE_ALG_AES_XTS                       TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     128, 256bits
 *     TEE_ALG_AES_CCM_SW                    TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     128, 256bits
 *     TEE_ALG_AES_GCM_SW                    TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     128, 256bits
 *     TEE_ALG_RSASSA_PKCS1_V1_5_SHA1        TEE_MODE_SIGN, TEE_MODE_VERIFY         upto 4096bits
 *     TEE_ALG_RSASSA_PKCS1_V1_5_SHA256      TEE_MODE_SIGN, TEE_MODE_VERIFY         upto 4096bits
 *     TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1    TEE_MODE_SIGN, TEE_MODE_VERIFY         upto 4096bits
 *     TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA256  TEE_MODE_SIGN, TEE_MODE_VERIFY         upto 4096bits
 *     TEE_ALG_RSAES_PKCS1_V1_5              TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     upto 4096bits
 *     TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1    TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     upto 4096bits
 *     TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA256  TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     upto 4096bits
 *     TEE_ALG_RSA_NOPAD                     TEE_MODE_ENCRYPT, TEE_MODE_DECRYPT     upto 4096bits
 *     TEE_ALG_SHA1                          TEE_MODE_DIGEST
 *     TEE_ALG_SHA256                        TEE_MODE_DIGEST
 *     TEE_ALG_HMAC_SHA1                     TEE_MODE_MAC
 *     TEE_ALG_HMAC_SHA256                   TEE_MODE_MAC
 *     TEE_ALG_AES_CMAC                      TEE_MODE_MAC
 *
 * @param[out]  operation   A pointer to a TEE_OperationHandle
 * @param[in]   algorithm   One of the cipher algorithms enumerated above
 * @param[in]   mode        The operation mode
 * @param[in]   maxKeySize  Maximum key size in bits for the operation
 *
 * @return   TEE_SUCCESS                Handle is allocated
 *           TEE_ERROR_OUT_OF_MEMORY    No free memory
 *           TEE_ERROR_GENERIC          Hardware failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input parameters
 */
TEE_Result TEE_AllocateOperation( TEE_OperationHandle *operation,
                                  uint32_t algorithm,
                                  uint32_t mode,
                                  uint32_t maxKeySize
                                );

/**
 * @brief The TEE_Free Operation function deallocates all
 *        resources associated with an operation handle. After
 *        this function is called, the operation handle is no
 *        longer valid.
 *
 * @param[in]   operation   handle allocated during
 *       TEE_AllocateOperation
 *
 * @return      none
 *
 */
void TEE_FreeOperation( TEE_OperationHandle operation);


/**
 * @brief returns information about an operation handle
 *
 * It fills the following fields in the structure operationInfo
 *
 *  • algorithm, mode, maxKeySize: The parameters passed to the
 *                        function TEE_AllocateOperation
 *  • algorithmClass: One of the following constants, describing
 *                   the kind of operation:
 *              o TEE_OPERATION_CIPHER
 *              o TEE_OPERATION_MAC
 *              o TEE_OPERATION_AE
 *              o TEE_OPERATION_DIGEST
 *              o TEE_OPERATION_ASYMMETRIC_CIPHER
 *              o TEE_OPERATION_ASYMMETRIC_SIGNATURE
 * • keySize: If a key is programmed in the operation, the
 *            actual size of this key
 * • requiredKeyUsage: A bit vector that describes the necessary
 *                  bits in the object usage for
 *                  TEE_SetOperationKey or TEE_SetOperationKey2
 *                  to succeed without panicking. Set to 0 for a
 *                  digest operation.
 * • digestLength: For a MAC, AE, or Digest , describes
 *                 the number of bytes in the digest or tag
 *  • handleState: A bit vector describing the current state of
 *                 the operation. Contains one or more of the
 *                 following flags:
 *            o TEE_HANDLE_FLAG_EXPECT_TWO_KEYS: Set if the
 *            algorithm expects two keys to be set, using
 *            TEE_SetOperationKey2. This happens only if
 *            algorithm is set to TEE_ALG_AES_XTS.
 *            o TEE_HANDLE_FLAG_KEY_SET: Set if the operation
 *            key has been set. Always set for digest operations
 *            o TEE_HANDLE_FLAG_INITIALIZED: For multi-stage
 *            operations
 *
 * @param[in]  operation     A pointer to a TEE_OperationHandle
 *                            allocated by TEE_AllocateOperation
 * @param[out] operationInfo Fills above operation info at
 *                            this pointer location
 *
 * @return   TEE_SUCCESS                OperationInfo filled
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 */
TEE_Result TEE_GetOperationInfo( TEE_OperationHandle operation,
                                 TEE_OperationInfo* operationInfo);

/**
 * @brief Resets the operation
 *
 * For a multi-stage operation, the TEE_ResetOperation function
 * resets the operation state before initialization, but after
 * the key has been set.
 * Only for the multi-stage operations, i.e., symmetric ciphers,
 * MACs, AEs, and digests. When such a multi-stage operation is
 * active, i.e., when it has been initialized but not yet
 * successfully finalized, then the operation is reset to its
 * pre-initialization state. The operation key(s) are not
 * cleared.
 *
 *  Valid only for
 *      TEE_OPERATION_CIPHER
 *      TEE_OPERATION_DIGEST
 *      TEE_OPERATION_MAC
 *      TEE_OPERATION_AE
 *
 * @param[in]  operation     A pointer to a TEE_OperationHandle
 *                            allocated by TEE_AllocateOperation
 *
 * @return   TEE_SUCCESS                operation reset
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not implemented
 */
TEE_Result TEE_ResetOperation( TEE_OperationHandle operation);


/*==============================================================

                  Key API's

===============================================================*/


/**
 * @brief generates a random key or a key-pair and
 *        populates a transient key object with the
 *        generated key material.
 *
 * The size of the desired key is passed in the keySize
 * parameter and must be less than the maximum size
 * of the transient object.
 *
 * Object Type              Details
 * TEE_TYPE_AES              TEE_ATTR_INPUT_KEY, TEE_ATTR_CONTEXT,
 * TEE_TYPE_HMAC_SHA1        and TEE_ATTR_LABEL are the input parameters.
 * TEE_TYPE_HMAC_SHA256      To use Hardware key
 * TEE_TYPE_GENERIC_SECRET   TEE_ATTR_INPUT_KEY can be NULL
 *
 * TEE_TYPE_RSA_KEYPAIR      TEE_ATTR_RSA_PUBLIC_EXPONENT is the input
 *                           parameter to be passed.
 *                           params TEE_ATTR_RSA_PUBLIC_EXPONENT needs to be given
 *
 * @param[in]  object        Handle on an uninitialized transient key to
 *                           populate with the generated key
 * @param[in]  keySize       Requested key size in bits. Must be less than or equal
 *                           to the maximum size of the object container
 * @param[in]  params        Array of attribute parameters for key generation
 * @param[in]  paramCount    Number of params
 *
 * @return   TEE_SUCCESS                Key generated
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not implemented
 */

TEE_Result TEE_GenerateKey( TEE_ObjectHandle object,
                            uint32_t keySize,
                            TEE_Attribute* params,
                            uint32_t paramCount);


/**
 * @brief associates an operation with a key
 *
 * The key material is copied from the key object handle into
 * the operation. After the key has been set, there is no longer
 * any link between the operation and the key object. The object
 * handle can be closed or reset and this will not affect the
 * operation.
 *
 * The key object type and size must be compatible with the type
 * and size of the operation. The operation mode must be
 * compatible with key usage:
 * • In general, the operation mode must be allowed in the
 * object usage.
 * • For the TEE_ALG_RSA_NOPAD algorithm:
 *        o The only supported modes are TEE_MODE_ENCRYPT and
 *        TEE_MODE_DECRYPT.
 *        o For TEE_MODE_ENCRYPT, the object usage must contain
 *        both the TEE_USAGE_ENCRYPT and TEE_USAGE_VERIFY flags.
 *        o For TEE_MODE_DECRYPT, the object usage must contain
 *        both the TEE_USAGE_DECRYPT and TEE_USAGE_SIGN flags.
 * • For a public key object, the operation mode can only be
 * TEE_MODE_ENCRYPT or TEE_MODE_VERIFY but cannot be
 * TEE_MODE_DECRYPT or TEE_MODE_SIGN as these kinds of
 * operations require the private parts of a key-pair.
 * • If the object is a key-pair then the key parts used in the
 * operation depend on the mode:
 *        o For a TEE_MODE_ENCRYPT or TEE_MODE_VERIFY operation,
 *        the public parts of the key-pair are used.
 *        o For a TEE_MODE_DECRYPT or TEE_MODE_SIGN, the private
 *        parts of the key-pair are used.
 *
 * @param[in]  operation     A pointer to a TEE_OperationHandle
 *                            allocated by TEE_AllocateOperation
 * @param[in]  key           Initialized key
 *
 * @return   TEE_SUCCESS                Key associated with
 *                                      operation
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not implemented
 */
TEE_Result TEE_SetOperationKey( TEE_OperationHandle operation,
                                TEE_ObjectHandle key);


/**
 * @brief initializes an existing operation with two keys
 *
 * This is used only for the algorithm TEE_ALG_AES_XTS.
 * The key material is copied from the key object handle into
 * the operation.
 * This function works like TEE_SetOperationKey except that two
 * keys are set instead of a single key.
 *
 * @param[in]  operation     A pointer to a TEE_OperationHandle
 *                            allocated by TEE_AllocateOperation
 * @param[in]  key1           Initialized key 1
 * @param[in]  key2           Initialized key 2
 *
 * @return   TEE_SUCCESS                Key associated to
 *                                      operation
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not implemented
 */
TEE_Result TEE_SetOperationKey2( TEE_OperationHandle operation,
                                 TEE_ObjectHandle key1,
                                 TEE_ObjectHandle key2);


/*==============================================================

                  HASH/MAC API's

===============================================================*/

/**
 * @brief accumulates message data for hashing
 *
 * The message does not have to be block aligned.
 * Subsequent calls to this function are possible.
 *
 * @param[in]  operation     Handle of a running Message Digest operation
 * @param[in]  chunk         Chunk of data to be hashed
 * @param[in]  chunkSize     size of chunk in bytes
 *
 * @return   TEE_SUCCESS                Hash update done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 */

TEE_Result TEE_DigestUpdate( TEE_OperationHandle operation,
                             void* chunk, size_t chunkSize);

/**
 * @brief finalizes the message digest operation
 *
 * produces the message hash. the Message Digest
 * operation can be reset and reused.
 *
 * @param[in]  operation     Handle of a running Message Digest operation
 * @param[in]  chunk         Chunk of data to be hashed
 * @param[in]  chunkSize     size of chunk in bytes
 * @param[out] hash          Output buffer filled with the
 *                           message hash
 * @param[in/out]hashLen     Length of hash buffer passed in
 *                           bytes, updated with length of hash
 *                           result.
 *
 * @return   TEE_SUCCESS                Hash final op done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 */

TEE_Result TEE_DigestDoFinal( TEE_OperationHandle operation,
                              void* chunk, size_t chunkLen,
                              void* hash, size_t *hashLen);


/**
 * @brief initializes a MAC operation
 *
 * The operation is started and associated with a key. If this
 * function does not return with TEE_SUCCESS, the operation is
 * not initialized.
 * If the MAC algorithm does not require an IV, the parameters
 * IV, IVLen are ignored. IV must still be a valid input buffer,
 * so, for example, if IV is NULL, then IVLen must be set to 0.
 *
 * @param[in]  operation     Operation handle
 * @param[in]  IV            Input buffer containing the
 *                           operation IV, if applicable
 * @param[in]  IVLen         Length of IV in bytes
 *
 * @return   TEE_SUCCESS                Mac initialized
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_SUPPORTED    Not supported for the
 *                                      operation
 */

TEE_Result TEE_MACInit( TEE_OperationHandle operation,
                        void* IV, size_t IVLen);


/**
 * @brief accumulates data for a MAC calculation
 *
 * Input data does not have to be a multiple of the block size.
 * Subsequent calls to this function are possible.
 * TEE_MACComputeFinal or TEE_MACCompareFinal are called to
 * complete the MAC operation.
 *
 * @param[in]  operation     Handle of a MAC operation
 * @param[in]  chunk         Chunk of the message to be MACed
 * @param[in]  chunkSize     Size of chunk in bytes
 *
 * @note This operation not supported for :
 *          TEE_ALG_AES_CMAC
 *
 * @return   TEE_SUCCESS                Mac initialized
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_SUPPORTED    Not supported for the
 *                                      operation
 */

TEE_Result TEE_MACUpdate( TEE_OperationHandle operation,
                          void* chunk, size_t chunkSize);

/**
 * @brief finalizes the MAC operation with a last chunk of
 *        message, and computes the MAC
 *
 * finalizes the MAC operation with a last chunk of message, and
 * computes the MAC.
 *
 * @param[in]  operation     Handle of a MAC operation
 * @param[in]  message       Chunk of the message to be MACed
 * @param[in]  messageLen    Size of chunk in bytes
 * @param[out] mac           Output buffer filled with the
 *                           computed MAC
 * @param[in/out]  macLen    Length of buffer passed, updated
 *                           with correct length after function
 *                           returns, size in bytes
 *
 *
 * @return   TEE_SUCCESS                Mac final done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_SUPPORTED    Not supported for the
 *                                      operation
 */

TEE_Result TEE_MACComputeFinal( TEE_OperationHandle operation,
                                void* message, size_t messageLen,
                                void* mac, size_t *macLen);

/**
 * @brief finalizes the MAC operation and compares the MAC with
 *        the buffer passed to the function
 *
 * finalizes the MAC operation and compares the MAC with the
 * buffer passed to the function.
 *
 * @param[in]  operation     Handle of a MAC operation
 * @param[in]  message       Input buffer containing the last
 *                           message chunk to MAC
 * @param[in]  messageLen    Size of message in bytes
 * @param[in]  mac           Input buffer containing the MAC to check
 * @param[in]  macLen        Length of buffer passed, size in
 *                           bytes
 *
 * @return   TEE_SUCCESS                Mac initialized
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_SUPPORTED    Not supported for the
 *                                      operation
 *           TEE_ERROR_MAC_INVALID      computed MAC does not
 *                                      correspond to the value
 *                                      passed in the parameter
 *                                      mac
 */

TEE_Result TEE_MACCompareFinal( TEE_OperationHandle operation,
                                void* message, size_t messageLen,
                                void* mac, size_t *macLen);


/*==============================================================

                  CIPHER API's

===============================================================*/


/**
 * @brief Initialiaze the XTS du size for XTS operation
 *
 * The operation must have been associated with a key.
 *
 * @param[in]  operation     A handle on an opened cipher
 *                           operation setup with a key
 * @param[in]  XTS_DUsize    XTS DU size in bytes
 *
 * @note (1) XTS_DUsize should be less than equal to 32K-64
 *       (2) total data size should be multiple of XTS_DUsize
 *       (3) (32K-64)%XTS_DUsize = 0
 *
 * @return   TEE_SUCCESS                DU size set
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 */

TEE_Result TEE_CipherXTS_DUsize( TEE_OperationHandle operation,
                                 size_t XTS_DUsize);


/**
 * @brief starts the symmetric cipher operation
 *
 * The operation must have been associated with a key.
 *
 * @param[in]  operation     A handle on an opened cipher
 *                           operation setup with a key
 * @param[in]  IV            Buffer containing the operation
 *                           Initialization Vector
 * @param[in]  IVLen         Size of IV in bytes
 *
 * @return   TEE_SUCCESS                Cipher initialized
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 */

TEE_Result TEE_CipherInit( TEE_OperationHandle operation,
                           void* IV, size_t IVLen);

/**
 * @brief function encrypts or decrypts input data
 *
 * Subsequent calls to this function are possible. The cipher
 * operation is finalized with a call to TEE_CipherDoFinal.
 *
 * @param[in]  operation     Handle of a running Cipher operation
 * @param[in]  srcData       Input data buffer to be encrypted
 *                           or decrypted operation
 * @param[in]  srcLen        length of srcData in bytes
 * @param[out] destData      Output buffer
 * @param[in/out]  destLen   length of destData in bytes
 *
 * @return   TEE_SUCCESS                Cipher update done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *
 * @note  TEE_ALG_AES_CTS and TEE_ALG_AES_CTR needs the
 *        srcLen to be multiple of TEE_ALG_AES_BLK_SIZE(16bytes)
 */

TEE_Result TEE_CipherUpdate( TEE_OperationHandle operation,
                             void* srcData, size_t srcLen,
                             void* destData, size_t *destLen);


/**
 * @brief finalizes the cipher operation
 *
 * Input data does not have to be a multiple of block size for
 * TEE_ALG_AES_CTS and TEE_ALG_AES_CTR. The cipher operation is
 * finalized with this call.
 *
 * @param[in]  operation     Handle of a running Cipher operation
 * @param[in]  srcData       Input data buffer to be encrypted
 *                           or decrypted operation
 * @param[in]  srcLen        length of srcData in bytes
 * @param[out] destData      Output buffer
 * @param[in/out]  destLen   length of destData in bytes
 *
 * @return   TEE_SUCCESS                Cipher final done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *
 */

TEE_Result TEE_CipherDoFinal( TEE_OperationHandle operation,
                              void* srcData, size_t srcLen,
                              void* destData, size_t *destLen);


/*==============================================================

                 AUTHENTICATED ENCRYPTION API's

===============================================================*/

/**
 * @brief initializes an Authentication Encryption operation
 *
 * @param[in]  operation     A handle on the operation
 * @param[in]  nonce         The operation nonce or IV
 * @param[in]  nonceLen      operation nonce or IV in bytes
 * @param[in]  tagLen        Size in bits of the tag length
 * @param[in]  AADLen        Length in bytes of the AAD
 *                             o Used only for AES-CCM. Ignored for AES-GCM
 * @param[in]  payloadLen    Used only for AES-CCM. Ignored for AES-GCM.bits
 *
 * @return   TEE_SUCCESS                AE intialize done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not Implemented mode
 *
 */

TEE_Result TEE_AEInit(TEE_OperationHandle operation,
                      void* nonce, size_t nonceLen,
                      uint32_t tagLen, uint32_t AADLen,
                      uint32_t payloadLen);

/**
 * @brief Feeds AAD chunk to the AE operation
 *
 * @param[in]  operation     Handle on the AE operation
 * @param[in]  AADdata       Input buffer containing the chunk
 *                           of AAD
 * @param[in]  AADdataLen    Length in bytes of the AAD
 *
 * @return   TEE_SUCCESS                AAD associated to
 *                                      operation
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not Implemented mode
 *
 */

TEE_Result TEE_AEUpdateAAD(TEE_OperationHandle operation,
                           void* AADdata, size_t AADdataLen);

/**
 * ****       NOT SUPPORTED *****
 * @brief accumulates data for an Authentication Encryption
 *        operation
 *
 * Subsequent calls to this function are possible.
 *
 * @param[in]  operation     Handle of a running AE operation
 * @param[in]  srcData       Input data buffer to be encrypted
 *                           or decrypted
 * @param[in]  srcLen        length of srcData in bytes
 * @param[out] destData      Output buffer
 * @param[in/out]  destLen   length of destData in bytes
 *
 * @return   TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_SUPPORTED    Update on AE operations
 *                                      not supported
 *
 */

TEE_Result TEE_AEUpdate(TEE_OperationHandle operation,
                        void* srcData, size_t srcLen,
                        void* destData, size_t *destLen);

/**
 * @brief completes the AE operation and computes the tag
 *
 * @param[in]  operation     Handle of a running AE operation
 * @param[in]  srcData       Reference to final chunk of input
 *                           data to be encrypted
 * @param[in]  srcLen        Length in bytes of the srcData
 * @param[out]  destData      Output buffer. Can be omitted if
 *                           the output is to be discarded,
 *                           e.g., because it is known to be
 *                           empty.
 * @param[in]  destLen       Length in bytes of the destData
 * @param[out]  tag          Output buffer filled with the computed tag
 * @param[in]  tagLen        Length in bytes of the tag
 *
 * @return   TEE_SUCCESS                AE final done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not Implemented mode
 *
 */

TEE_Result TEE_AEEncryptFinal(TEE_OperationHandle operation,
                              void* srcData, size_t srcLen,
                              void* destData, size_t* destLen,
                              void* tag, size_t* tagLen);

/**
 * @brief completes the AE operation and verifies the tag
 *
 * @param[in]  operation     Handle of a running AE operation
 * @param[in]  srcData       Reference to final chunk of input
 *                           data to be encrypted
 * @param[in]  srcLen        Length in bytes of the srcData
 * @param[out]  destData      Output buffer. Can be omitted if
 *                           the output is to be discarded,
 *                           e.g., because it is known to be
 *                           empty.
 * @param[in]  destLen       Length in bytes of the destData
 * @param[out]  tag          Input buffer filled with the
 *                           computed tag
 * @param[in]  tagLen        Length in bytes of the tag
 *
 * @return   TEE_SUCCESS                AE final done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_NOT_IMPLEMENTED  Not Implemented mode
 *
 */

TEE_Result TEE_AEDecryptFinal(TEE_OperationHandle operation,
                              void* srcData, size_t srcLen,
                              void* destData, size_t *destLen,
                              void* tag, size_t tagLen);

/*==============================================================

                  ASYMMETRIC CIPHER API's

===============================================================*/

/**
 * @brief encrypts a message within an asymmetric operation
 *
 * These functions can be called only with an operation of the following algorithms:
 * • TEE_ALG_RSAES_PKCS1_V1_5
 * • TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1
 * • TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA256
 * • TEE_ALG_RSA_NOPAD (expects input buffer and output buffer of same size)
 *
 * The parameters params, paramCount contain the operation parameters
 *
 * Algorithm                               Possible operation parameters
 * TEE_ALG_RSAES_PKCS1_OAEP_MGF1_XXX       TEE_ATTR_RSA_OAEP_LABEL: This parameter is optional.
 *                                         If not present, an empty label is assumed.
 *
 *
 * @param[in]  operation     Handle on the operation, which must have been suitably
 *                           set up with an operation key
 * @param[in]  params        Optional operation parameters
 * @param[in]  paramCount    Optional operation parameters count
 * @param[in]  srcData       Reference to final chunk of input
 *                           data to be encrypted
 * @param[in]  srcLen        Length in bytes of the srcData
 * @param[out]  destData     Output buffer.
 * @param[in]  destLen       Length in bytes of the destData
 *
 * @return   TEE_SUCCESS                Asym  encryption done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_SHORT_BUFFER     If the output buffer is
 *                                      not large enough to hold the result
 *
 */

TEE_Result TEE_AsymmetricEncrypt( TEE_OperationHandle operation,
                                  TEE_Attribute* params, uint32_t paramCount,
                                  void* srcData, size_t srcLen,
                                  void* destData, size_t *destLen);

/**
 * @brief decrypts a message within an asymmetric operation
 *
 * These functions can be called only with an operation of the following algorithms:
 * • TEE_ALG_RSAES_PKCS1_V1_5
 * • TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1
 * • TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA256
 * • TEE_ALG_RSA_NOPAD (expects input buffer and output buffer of same size)
 *
 * The parameters params, paramCount contain the operation parameters
 *
 * Algorithm                               Possible operation parameters
 * TEE_ALG_RSAES_PKCS1_OAEP_MGF1_XXX       TEE_ATTR_RSA_OAEP_LABEL: This parameter is optional.
 *                                         If not present, an empty label is assumed.
 *
 *  All supported algo by this api         TEE_ATTR_RSA_KEY_CRT_DECRYPT:This parameter is optional.
 *                                         If not present, a
 *                                         regular asymmetric
 *                                         decryption is done
 *                                         else CRT decryption
 *                                         is done.
 *
 * @param[in]  operation     Handle on the operation, which must have been suitably
 *                           set up with an operation key
 *
 * @param[in]  params        Optional operation parameters
 * @param[in]  paramCount    Optional operation parameters count
 * @param[in]  srcData       Reference to final chunk of input
 *                           data to be encrypted
 * @param[in]  srcLen        Length in bytes of the srcData
 * @param[out] destData      Output buffer. Can be omitted if
 *                           the output is to be discarded,
 *                           e.g., because it is known to be
 *                           empty.
 * @param[in]  destLen       Length in bytes of the destData
 *
 * @return   TEE_SUCCESS                Asym  decryption done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_SHORT_BUFFER     If the output buffer is
 *                                      not large enough to hold the result
 *
 */

TEE_Result TEE_AsymmetricDecrypt( TEE_OperationHandle operation,
                                  TEE_Attribute* params, uint32_t paramCount,
                                  void* srcData, size_t srcLen,
                                  void* destData, size_t *destLen);

/**
 * @brief signs a message digest within an asymmetric operation
 *
 * Note that only an already hashed message can be signed.
 * This function can be called only with an operation of the
 * following algorithms:
 * • TEE_ALG_RSASSA_PKCS1_V1_5_SHA1
 * • TEE_ALG_RSASSA_PKCS1_V1_5_SHA256
 * • TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1
 * • TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA256
 *
 * The parameters params, paramCount contain the operation
 * parameters
 *
 * Algorithm                      Possible operation parameters
 * TEE_ALG_RSASSA_PKCS1_PSS_MGF1_XX
 *                                      TEE_ATTR_RSA_PSS_SALT_LENGTH: Number of bytes in the salt.
 *                                      This parameter is
 *                                      optional. If not
 *                                      present, the salt length
 *                                      is equal to the hash
 *                                      length.
 *
 * @param[in]  operation     Handle on the operation, which must have been suitably
 *                           set up with an operation key
 * @param[in]  params        Optional operation parameters
 * @param[in]  paramCount    Optional operation parameters count
 * @param[in]  digest        Input buffer containing the input message digest
 * @param[in]  digestLen     length of message digest in bytes
 * @param[out] signature     Output buffer written with the signature of the digest
 * @param[in]  signatureLen  Length in bytes of the signature
 *                           buffer
 *
 * @return   TEE_SUCCESS                Signing done
 *           TEE_ERROR_GENERIC          Hardware/Software
 *                                      failure
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *           TEE_ERROR_SHORT_BUFFER     If the output buffer is
 *                                      not large enough to hold the result
 *
 */

TEE_Result TEE_AsymmetricSignDigest(TEE_OperationHandle operation,
                                    TEE_Attribute* params, uint32_t paramCount,
                                    void* digest, size_t digestLen,
                                    void* signature, size_t *signatureLen);


/**
 * @brief verifies a message digest signature within an
 *        asymmetric operation
 *
 * Note that only an already hashed message can be signed.
 * This function can be called only with an operation of the
 * following algorithms:
 * • TEE_ALG_RSASSA_PKCS1_V1_5_SHA1
 * • TEE_ALG_RSASSA_PKCS1_V1_5_SHA256
 * • TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1
 * • TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA256
 *
 * The parameters params, paramCount contain the operation
 * parameters
 *
 * Algorithm                      Possible operation parameters
 * TEE_ALG_RSASSA_PKCS1_PSS_MGF1_XXX
 *                                      TEE_ATTR_RSA_OAEP_LABEL:
 *                                         TEE_ATTR_RSA_PSS_SALT_LENGTH: Number of bytes in the salt.
 *                                         This parameter is
 *                                         optional. If not
 *                                         present, the salt
 *                                         length is equal to
 *                                         the hash length.
 *
 * @param[in]  operation     Handle on the operation, which must have been suitably
 *                           set up with an operation key
 * @param[in]  params        Optional operation parameters
 * @param[in]  paramCount    Optional operation parameters count
 * @param[in]  digest        Input buffer containing the input message digest
 * @param[in]  digestLen     length of message digest in bytes
 * @param[in]  signature     signature of the digest to be
 *                           verified
 * @param[in]  signatureLen  Length in bytes of the signature
 *                           buffer
 *
 * @return   TEE_SUCCESS                Signature verified
 *           TEE_ERROR_GENERIC          Operation
 *                                      failure/Verification failed
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *
 */

TEE_Result TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation,
                                      TEE_Attribute* params, uint32_t paramCount,
                                      void* digest, size_t digestLen,
                                      void* signature, size_t signatureLen);

/*==============================================================

                  RANDOM NUMBER GENERATOR API

===============================================================*/


/**
 * @brief generates random data
 *
 * @param[out] randomBuffer     Reference to generated random data
 * @param[in]  randomBufferLen  Byte length of requested random data
 *
 * @return   TEE_SUCCESS                Random data is generated
 *           TEE_ERROR_GENERIC          Hardware failure/Improper parameters
 */

TEE_Result TEE_GenerateRandom(void* randomBuffer,
                              size_t randomBufferLen);


void TEE_CopyOperation(
TEE_OperationHandle dstOperation,
TEE_OperationHandle srcOperation
);

void TEE_DeriveKey(
TEE_OperationHandle operation,
TEE_Attribute* params, uint32_t paramCount,
TEE_ObjectHandle derivedKey
);

/**
 * @brief signes a message and generates signature within an
 *        DSA asymmetric operation
 *
 * Note that only an already hashed message can be signed.
 *
 * @param[in]  operation     Handle on the operation, which must have been suitably
 *                           set up with an operation key
 * @param[in]  digest        Input buffer containing the input message digest
 * @param[in]  digestLen     length of message digest in bytes
 * @param[in]  signature     signature of the digest to be
 *                           signed
 * @param[in]  signatureLen  Length in bytes of the signature
 *                           buffer
 *
 * @return   TEE_SUCCESS                Signature successfully generated
 *           TEE_ERROR_GENERIC          Operation
 *                                      failure/Verification failed
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *
 */

TEE_Result TEE_DsaSignDigest(TEE_OperationHandle operation,
                             void* digest, size_t digestLen,
                             void* signature, size_t *signatureLen);

/**
 * @brief signes a message and generates signature within an
 *        DSA asymmetric operation
 *
 * Note that only an already hashed message can be signed.
 *
 * @param[in]  operation     Handle on the operation, which must have been suitably
 *                           set up with an operation key
 * @param[in]  digest        Input buffer containing the input message digest
 * @param[in]  digestLen     length of message digest in bytes
 * @param[in]  signature     signature of the digest to be
 *                           verified
 * @param[in]  signatureLen  Length in bytes of the signature
 *                           buffer
 *
 * @return   TEE_SUCCESS                Signature verified
 *           TEE_ERROR_GENERIC          Operation
 *                                      failure/Verification failed
 *           TEE_ERROR_BAD_PARAMETERS   Incorrect input
 *                                      parameters
 *
 */

TEE_Result  TEE_DsaVerifyDigest(TEE_OperationHandle operation,
                                void* digest, size_t digestLen,
                                void* signature, size_t signatureLen);

#ifdef __cplusplus
  }
#endif

#endif /* GPCRYPTO_H */

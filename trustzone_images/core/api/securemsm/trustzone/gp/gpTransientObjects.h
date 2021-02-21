#ifndef GPTRANSIENTOBJECTS_H
#define GPTRANSIENTOBJECTS_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "gpTypes.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#ifdef __cplusplus
  extern "C"
  {
#endif

/**
 * @brief allocates an uninitialized transient object, i.e., a
 *        container for attributes
 *
 * Transient objects are used to hold a cryptographic object
 * (key or key-pair). The object type and the maximum object
 * characteristic size must be specified so that all the
 * container resources can be pre-allocated
 *
 *  The returned handle is used to refer to the newly-created
 *  container in all subsequent functions that require an object
 *  container: key management and operation functions. The
 *  handle remains valid until the container is deallocated
 *  using the function TEE_FreeTransientObject.
 *
 *  the object type determines the possible object size:
 *
 *  Object Type                   Possible Object Sizes
 *  TEE_TYPE_AES                   128 or 256 bits
 *  TEE_TYPE_HMAC_SHA1             multiple of 8 bits
 *  TEE_TYPE_HMAC_SHA256           multiple of 8 bits
 *  TEE_TYPE_RSA_PUBLIC_KEY        Object size is the number of
 *                                 bits in the modulus. Upto
 *                                 4096 bits
 *  TEE_TYPE_RSA_KEYPAIR           Same as for RSA public key
 *  size.
 *
 * @param[in]  objectType     Type of uninitialized object container to be created
 * @param[in]  maxObjectSize  Size of the object as described
 *                            above
 * @param[out]  object        Filled with a handle on the newly created key container
 *
 * @return   TEE_SUCCESS                handle created
 *           TEE_ERROR_OUT_OF_MEMORY   not enough resources
 *                                     are available to allocate
 *                                     the object handle
 *           TEE_ERROR_BAD_PARAMETERS  Incorrect input
 *                                     parameters
 *           TEE_ERROR_NOT_SUPPORTED   Not supported Object type
 */
TEE_Result
TEE_AllocateTransientObject(
    uint32_t objectType,
    uint32_t maxObjectSize,
    TEE_ObjectHandle* object /*[out]*/
);

/**
 * @brief deallocates a transient object previously allocated with TEE_AllocateTransientObject
 *
 * After this function has been called, the object handle is no
 *  longer valid and all resources associated with the transient
 *  object must have been reclaimed
 *
 *
 * @param[in]  object        Handle on the object to free
 *
 * @return
 *
 */

void
TEE_FreeTransientObject(
    TEE_ObjectHandle object
);

/**
 * @brief resets a transient object to its initial state after allocation
 *
 * If the object is currently initialized, the function clears
 *  the object of all its material. The object is then
 *  uninitialized again.
 *
 * @param[out]  object        handle on transient object to
 *                            reset
 *
 * @return
 *
 */
void
TEE_ResetTransientObject(
    TEE_ObjectHandle object
);

/**
 * @brief populates an uninitialized object container with object attributes passed by the TA in the attrs parameter.
 *
 *
 *  the object type determines the possible attributes:
 *
 *  Object Type                   Possible attrs
 *  TEE_TYPE_AES                    For all secret key objects,
 *                                  the TEE_ATTR_SECRET_VALUE must be provided.
 *  TEE_TYPE_HMAC_SHA1             same as TEE_TYPE_AES
 *  TEE_TYPE_HMAC_SHA256           same as TEE_TYPE_AES
 *  TEE_TYPE_RSA_PUBLIC_KEY        TEE_ATTR_RSA_MODULUS
 *                                 TEE_ATTR_RSA_PUBLIC_EXPONENT
 *  TEE_TYPE_RSA_KEYPAIR           TEE_ATTR_RSA_MODULUS
 *                                 TEE_ATTR_RSA_PUBLIC_EXPONENT
 *                                 TEE_ATTR_RSA_PRIVATE_EXPONENT
 *                                 The CRT parameters are
 *                                 optional. If any of these
 *                                 parts is provided, then all
 *                                 of them must be provided:
 *                                 TEE_ATTR_RSA_PRIME1 (p)
 *                                 TEE_ATTR_RSA_PRIME2 (q)
 *                                 TEE_ATTR_RSA_EXPONENT1 (dP)
 *                                 TEE_ATTR_RSA_EXPONENT2 (dQ)
 *                                 TEE_ATTR_RSA_COEFFICIENT (pQ)
 *
 *
 * @param[in]  object        Handle on an already created
 *                           transient and uninitialized object
 * @param[in]  attrs         Array of object attributes
 * @param[in]  attrCount     number of elements in attrs array
 *
 * @return   TEE_SUCCESS               object populated
 *           TEE_ERROR_OUT_OF_MEMORY   not enough resources
 *                                     are available to allocate
 *                                     the object handle
 *           TEE_ERROR_BAD_PARAMETERS  Incorrect input
 *                                     parameters
 *           TEE_ERROR_GENERIC         HW/SW failure
 */
TEE_Result
TEE_PopulateTransientObject(
    TEE_ObjectHandle object,
    TEE_Attribute* attrs, /*[in]*/
    uint32_t attrCount
);

/**
 * @brief populate a single attribute with a reference to
 *        a buffer
 *
 * @param[out]  attr          handle on transient object to
 *                            reset
 * @param[in]   attributeID   attribute Type
 * @param[in]   buffer        buffer holding data
 * @param[in]   length        size of buffer in bytes
 *
 * @return
 *
 */
void
TEE_InitRefAttribute(
    TEE_Attribute* attr, /*[out]*/
    uint32_t attributeID,
    void* buffer, /*[inbuf]*/
    size_t length
);

/**
 * @brief populate a single attribute with integer values
 *
 * @param[out]  attr          handle on transient object to
 *                            reset
 * @param[in]   attributeID   attribute Type
 * @param[in]   a             data
 * @param[in]   b             data
 *
 * @return
 *
 */
void
TEE_InitValueAttribute(
    TEE_Attribute* attr, /*[out]*/
    uint32_t attributeID,
    uint32_t a,
    uint32_t b
);

/**
 * @brief populates an uninitialized object handle with the
 *        attributes of another object handle
 *
 * populates the attributes of destObject with the attributes of
 * srcObject. It is most useful in the following situations
 * • To extract the public key attributes from a key-pair object
 * • To copy the attributes from a persistent object into a
 * transient object
 * The source and destination objects must have compatible types
 * and sizes in the following sense:
 *  • The type of destObject must be a subtype of srcObject,
 *  i.e., one of the following must be true:
 *        o The type of destObject is equal to the type of
 *        srcObject.
 *        o The type of destObject is TEE_TYPE_RSA_PUBLIC_KEY
 *        and the type of srcObject is TEE_TYPE_RSA_KEYPAIR.
 *   • The size of srcObject must be less than or equal to the
 *   maximum size of destObject.
 *
 * @param[in]  destObject    Handle on an uninitialized
 *                           transient object
 * @param[in]  srcObject     Handle on an initialized object
 *
 * @return   TEE_SUCCESS               destObject populated
 *           TEE_ERROR_OUT_OF_MEMORY   not enough resources
 *                                     are available to allocate
 *                                     the object handle
 *           TEE_ERROR_BAD_PARAMETERS  Incorrect input
 *                                     parameters
 */

void
TEE_CopyObjectAttributes(
    TEE_ObjectHandle destObject,
    TEE_ObjectHandle srcObject
);

TEE_Result
TEE_CopyObjectAttributes1(
    TEE_ObjectHandle destObject,
    TEE_ObjectHandle srcObject
);

#ifdef __cplusplus
  }
#endif

#endif /* GPTRANSIENTOBJECTS_H */

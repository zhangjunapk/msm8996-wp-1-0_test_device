#ifndef GPGENERICOBJECTS_H
#define GPGENERICOBJECTS_H

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
 * This function replaces the TEE_GetObjectInfo function, whose use is deprecated.
 *
 * @brief Gets info about transient or persistent object.
 *
 * The TEE_GetObjectInfo1 function returns the characteristics of an object.
 * It fills in the following fields in the structure TEE_ObjectInfo (section 5.3.2):
 *   • objectType: The parameter objectType passed when the object was created
 *   • keySize: The current size in bits of the object as determined by its attributes.
 *     This will always be less than or equal to maxKeySize. Set to 0 for uninitialized
 *     and data only objects.
 *   • maxKeySize: The maximum keySize which this object can represent.
 *     o For a persistent object, set to keySize
 *     o For a transient object, set to the parameter maxKeySize passed to
 *       TEE_AllocateTransientObject
 *   • objectUsage: A bit vector of the TEE_USAGE_XXX bits defined in Table 5-4.
 *   • dataSize
 *     o For a persistent object, set to the current size of the data associated with the object
 *     o For a transient object, always set to 0
 *   • dataPosition
 *     o For a persistent object, set to the current position in the data for this handle.
 *       Data positions for different handles on the same object may differ.
 *     o For a transient object, set to 0
 *   • handleFlags: A bit vector containing one or more of the following flags:
 *     o TEE_HANDLE_FLAG_PERSISTENT: Set for a persistent object
 *     o TEE_HANDLE_FLAG_INITIALIZED
 *   • For a persistent object, always set
 *   • For a transient object, initially cleared, then set when the object becomes initialized
 *     o TEE_DATA_FLAG_XXX: Only for persistent objects, the flags used to open or create the object
 *
 * @param[in]   object      Handle on an object
 * @param[out]  objectInfo  A pointer to a TEE_ObjectInfo struct who's data members we'll be populated by the function
 *
 * @return   TEE_SUCCESS                Object info was copied form object.
 *           TEE_ERROR_BAD_PARAMETERS   Parameters were invalid to complete the operation
 *           TEE_ERROR_CORRUPT_OBJECT   If the persistent object is corrupt. The object handle is closed.
 *           TEE_ERROR_STORAGE_NOT_AVAILABLE   If the persistent object is stored in a storage area which is
 *                                             currently inaccessible.
 */
TEE_Result
TEE_GetObjectInfo1(
    TEE_ObjectHandle object,
    TEE_ObjectInfo* objectInfo /*[out]*/
);

/**
 * Use of this function is DEPRECATED – new code SHOULD use the TEE_GetObjectInfo1 function instead.
 *
 * @brief Gets info about transient or persistent object.
 *
 * The TEE_GetObjectInfo function returns the characteristics of an object.
 * It fills in the following fields in the structure TEE_ObjectInfo:
 *  • objectType: The parameter objectType passed when the object was created
 *  • objectSize: Set to 0 for an uninitialized object
 *  • maxObjectSize
 *    o For a persistent object, set to objectSize
 *    o For a transient object, set to the parameter maxObjectSize passed to TEE_AllocateTransientObject
 *  • objectUsage: A bit vector of the TEE_USAGE_XXX bits defined in Table 5-3. Initially set to 0xFFFFFFFF.
 *    Can be narrowed by calling TEE_SetRestrictUsage.
 *  • dataSize
 *    o For a persistent object, set to the current size of the data associated with the object
 *    o For a transient object, always set to 0
 *  • dataPosition
 *    o For a persistent object, set to the current position in the data for this handle.
 *      Data positions for different handles on the same object may differ.
 *    o For a transient object, set to 0
 *  • handleFlags: A bit vector containing one or more of the following flags:
 *    o TEE_HANDLE_FLAG_PERSISTENT: Set for a persistent object
 *    o TEE_HANDLE_FLAG_INITIALIZED
 *  • For a persistent object, always set
 *  • For a transient object, initially cleared, then set when the object becomes initialized
 *    o TEE_DATA_FLAG_XXX: Only for persistent objects, the flags used to open or create the object
 *
 * @param[in]   object      Handle on an object
 * @param[out]  objectInfo  A pointer to a TEE_ObjectInfo struct who's data members we'll be populated by the function
 *
 * @return   TEE_SUCCESS                Object info was copied form object.
 *           TEE_ERROR_BAD_PARAMETERS   Parameters were invalid to complete the operation
 */
void
TEE_GetObjectInfo(
    TEE_ObjectHandle object,
    TEE_ObjectInfo* objectInfo /*[out]*/
);

/**
 * @brief Restricts the usage permissions of a transient or persistent object.
 *
 * The TEE_RestrictObjectUsage function restricts the object usage flags of an object handle
 * to contain at most the flags passed in the objectUsage parameter.
 * For each bit in the parameter objectUsage:
 *  • If the bit is set to 1, the corresponding usage flag in the object is left unchanged.
 *  • If the bit is set to 0, the corresponding usage flag in the object is cleared.
 * For example, if the usage flags of the object are set to TEE_USAGE_ENCRYPT | TEE_USAGE_DECRYPT and
 * if objectUsage is set to TEE_USAGE_ENCRYPT | TEE_USAGE_EXTRACTABLE, then the only remaining usage
 * flag in the object after calling the function TEE_RestrictObjectUsage is TEE_USAGE_ENCRYPT.
 * Note that an object usage flag can only be cleared. Once it is cleared, it cannot be set to 1 again
 * until the whole object is reset using the function TEE_ResetObject. For a transient object, resetting
 * the object also clears all the key material stored in the container. For a persistent object,
 * setting the object usage MUST be an atomic operation.
 *
 * @param[in] object        Handle on an object
 * @param[in] objectUsage   New object usage, an OR combination of one or more of the TEE_USAGE_XXX
 *                          constants defined in Table 5-3 in GP spec
 *
 * @return   TEE_SUCCESS                Object info was copied form object.
 *           TEE_ERROR_BAD_PARAMETERS   Parameters were invalid to complete the operation
 */
void
TEE_RestrictObjectUsage(
    TEE_ObjectHandle object,
    uint32_t objectUsage
);

TEE_Result
TEE_RestrictObjectUsage1(
    TEE_ObjectHandle object,
    uint32_t objectUsage
);

/**
 * @brief Extracts an attribute containing a buffer from a transient or persistent object.
 *
 * The TEE_GetObjectBufferAttribute function extracts one buffer attribute from an object.
 * The attribute is identified by the argument attributeID. The precise meaning of this parameter
 * depends on the container type and size and is defined in section 6.11.
 * Bit [29] of the attribute identifier must be set to 0, i.e., it must denote a buffer attribute.
 * They are two kinds of object attributes:
 *  • Public object attributes can always be extracted whatever the status of the container.
 *  • Secret attributes can be extracted only if the object’s key usage contains the TEE_USAGE_EXTRACTABLE flag.
 * See section 6.11 for a definition of all available object attributes and their level of protection.
 *
 * @param[in]   object        Handle on an object
 * @param[in]   attributeID   Identifier of the attribute to retrieve
 * @param[out]  buffer        Output buffer to get the content of the attribute
 * @param[out]  size          Size of the output buffer
 *
 * @return
 * TEE_SUCCESS: In case of success
 * TEE_ERROR_ITEM_NOT_FOUND: If the attribute is not found on this object or if the object is a transient uninitialized object
 * TEE_ERROR_SHORT_BUFFER: If buffer is NULL or too small to contain the key part
 */

TEE_Result
TEE_GetObjectBufferAttribute(
    TEE_ObjectHandle object,
    uint32_t attributeID,
    void* buffer, /*[outbuf]*/
    size_t* size
);

/**
 * @brief Extracts an attribute containing two values from a transient or persistent object.
 *
 * The TEE_GetObjectValueAttribute function extracts a value attribute from an object.
 * The attribute is identified by the argument attributeID. The precise meaning of this parameter depends
 * on the container type and size and is defined in section 6.11.
 * Bit [29] of the attribute identifier must be set to 1, i.e., it must denote a value attribute.
 * They are two kinds of object attributes:
 *  • Public object attributes can always be extracted whatever the status of the container.
 *  • Secret attributes can be extracted only if the object’s key usage contains the TEE_USAGE_EXTRACTABLE flag.
 * See section 6.11 for a definition of all available object attributes and their level of protection.
 *
 * @param[in]   object        Handle on an object
 * @param[in]   attributeID   Identifier of the attribute to retrieve
 * @param[out]  a             Pointer on the placeholder filled with the attribute field a. Can be NULL
 *                            if the corresponding field is not of interest to the caller.
 * @param[out]  b             Pointer on the placeholder filled with the attribute field b. Can be NULL
 *                            if the corresponding field is not of interest to the caller.
 *
 * @return
 * TEE_SUCCESS: In case of success
 * TEE_ERROR_ITEM_NOT_FOUND: If the attribute is not found on this object or if the object is a transient uninitialized object
 * TEE_ERROR_ACCESS_DENIED: For an attempt to extract a secret part of a non-extractable container
 */

TEE_Result
TEE_GetObjectValueAttribute(
    TEE_ObjectHandle object,
    uint32_t attributeID,
    uint32_t* a, /*[outopt]*/
    uint32_t* b  /*[outopt]*/
);

/**
 * @brief Closes an opened object handle.
 *
 * The TEE_CloseObject function closes an opened object handle. The object can be persistent or transient.
 *
 * @param[in]  object    Handle on an object
 */

void
TEE_CloseObject(
    TEE_ObjectHandle object
);

#ifdef __cplusplus
  }
#endif

#endif /* GPGENERICOBJECTS_H */

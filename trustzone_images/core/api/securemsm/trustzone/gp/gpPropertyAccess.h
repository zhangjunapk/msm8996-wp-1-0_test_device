#ifndef GPPROPERTYACCESS_H
#define GPPROPERTYACCESS_H

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
 * @brief Get property as string.
 *
 *    The TEE_GetPropertyAsString function performs a lookup in a property set to retrieve an individual property
 * and convert its value into a printable string. When the lookup succeeds, the implementation MUST convert
 * the property into a printable string and copy the result into the buffer described by valueBuffer and valueBufferLen.
 *
 * @param[in]     propsetOrEnumerator     One of the TEE_PROPSET_XXX pseudo-handles or a handle on a property enumerator
 * @param[in]     name                    A pointer to the zero-terminated string containing the name of the property to
 *                                        retrieve. Its content is case-sensitive and it must be encoded in UTF-8.
 *                                          o If hPropSet is a property enumerator handle, name is ignored and can be NULL.
 *                                          o Otherwise, name cannot be NULL
 * @param[out]    valueBuffer             Output buffer for the property value.
 * @param[inout]  valueBufferLen          Length of the output buffer.
 *
 * @return        TEE_SUCCESS: In case of success
 *                TEE_ERROR_ITEM_NOT_FOUND: If the property is not found or if name is not a valid UTF-8 encoding
 *                TEE_ERROR_SHORT_BUFFER: If the value buffer is not large enough to hold the whole property value
 */
TEE_Result
TEE_GetPropertyAsString(
    TEE_PropSetHandle  propsetOrEnumerator,
    char*              name,        /* [instringopt] */
    char*              valueBuffer, /* [outstring] */
    size_t*            valueBufferLen
);

/**
 * @brief Get property as bool.
 *
 *    The TEE_GetPropertyAsBool function retrieves a single property in a property set and converts its value to a Boolean.
 * If a property cannot be viewed as a Boolean, this function MUST return TEE_ERROR_BAD_FORMAT. Otherwise, if this
 * function succeeds, then calling the function TEE_GetPropertyAsString on the same name and with a sufficiently large
 * output buffer MUST also succeed and return a string equal to “true” or “false” case-insensitive, depending on the value
 * of the Boolean.
 *
 * @param[in]     propsetOrEnumerator     One of the TEE_PROPSET_XXX pseudo-handles or a handle on a property enumerator
 * @param[in]     name                    A pointer to the zero-terminated string containing the name of the property to
 *                                        retrieve. Its content is case-sensitive and it must be encoded in UTF-8.
 *                                          o If hPropSet is a property enumerator handle, name is ignored and can be NULL.
 *                                          o Otherwise, name cannot be NULL
 * @param[out]    value                   A pointer to the variable that will contain the value of the property on success or
 *                                        false on error.
 *
 * @return        TEE_SUCCESS: In case of success
 *                TEE_ERROR_ITEM_NOT_FOUND: If the property is not found or if name is not a valid UTF-8 encoding
 *                TEE_ERROR_BAD_FORMAT: If the property value cannot be converted to a Boolean
 */
TEE_Result
TEE_GetPropertyAsBool(
    TEE_PropSetHandle  propsetOrEnumerator,
    char*              name, /* [instringopt] */
    bool*              value /* [out] */
);

/**
 * @brief Get property as uint32_t.
 *
 *    The TEE_GetPropertyAsU32 function retrieves a single property in a property set and converts its value to a 32-bit
 * unsigned integer. If a property cannot be viewed as a 32-bit unsigned integer, this function MUST return
 * TEE_ERROR_BAD_FORMAT.
 *
 * @param[in]     propsetOrEnumerator     One of the TEE_PROPSET_XXX pseudo-handles or a handle on a property enumerator
 * @param[in]     name                    A pointer to the zero-terminated string containing the name of the property to
 *                                        retrieve. Its content is case-sensitive and it must be encoded in UTF-8.
 *                                          o If hPropSet is a property enumerator handle, name is ignored and can be NULL.
 *                                          o Otherwise, name cannot be NULL
 * @param[out]    value                   A pointer to the variable that will contain the value of the property on success or
 *                                        zero on error.
 *
 * @return        TEE_SUCCESS: In case of success
 *                TEE_ERROR_ITEM_NOT_FOUND: If the property is not found or if name is not a valid UTF-8 encoding
 *                TEE_ERROR_BAD_FORMAT: If the property value cannot be converted to a 32-bit integer.
 */
TEE_Result
TEE_GetPropertyAsU32 (
    TEE_PropSetHandle propsetOrEnumerator,
    char*             name, /* [intstringopt] */
    uint32_t*         value /* [out] */
);

/**
 * @brief Get property as base64 encoded binary block.
 *
 *    The function TEE_GetPropertyAsBinaryBlock retrieves an individual property and converts its value into a binary block.
 * If a property cannot be viewed as a binary block, this function MUST return TEE_ERROR_BAD_FORMAT. Otherwise, if this function
 * succeeds, then calling the function TEE_GetPropertyAsString on the same name and with a sufficiently large output buffer
 * MUST also succeed and return a string that is consistent with a Base64 encoding of the binary block as defined in RFC 2045 [6],
 * section 6.8 but with the following tolerance:
 *  • An Implementation is allowed not to encode the final padding ‘=’ characters.
 *  • An Implementation is allowed to insert characters that are not in the Base64 character set.
 *
 * @param[in]     propsetOrEnumerator     One of the TEE_PROPSET_XXX pseudo-handles or a handle on a property enumerator
 * @param[in]     name                    A pointer to the zero-terminated string containing the name of the property to
 *                                        retrieve. Its content is case-sensitive and it must be encoded in UTF-8.
 *                                          o If hPropSet is a property enumerator handle, name is ignored and can be NULL.
 *                                          o Otherwise, name cannot be NULL
 * @param[out]    valueBuffer             Output buffer for the property value.
 * @param[inout]  valueBufferLen          Length of the output buffer.
 *
 * @return        TEE_SUCCESS: In case of success
 *                TEE_ERROR_ITEM_NOT_FOUND: If the property is not found or if name is not a valid UTF-8 encoding
 *                TEE_ERROR_BAD_FORMAT: If the property cannot be retrieved as a binary block
 *                TEE_ERROR_SHORT_BUFFER: If the value buffer is not large enough to hold the whole property value
 */
TEE_Result
TEE_GetPropertyAsBinaryBlock(
    TEE_PropSetHandle  propsetOrEnumerator,
    char*              name,        /* [instringopt] */
    char*              valueBuffer, /* [outstring] */
    size_t*            valueBufferLen
);

/**
 * @brief Get property as TEE_UUID.
 *
 *    The function TEE_GetPropertyAsUUID retrieves an individual property and converts its value into a UUID.
 * If a property cannot be viewed as a UUID, this function MUST return TEE_ERROR_BAD_FORMAT. Otherwise,
 * if this function succeeds, then calling the function TEE_GetPropertyAsString on the same name and with
 * a sufficiently large output buffer MUST also succeed and return a string that is consistent with the
 * concrete syntax of UUIDs defined in RFC 4122. Note that this string may mix character cases.
 *
 * @param[in]     propsetOrEnumerator     One of the TEE_PROPSET_XXX pseudo-handles or a handle on a property enumerator
 * @param[in]     name                    A pointer to the zero-terminated string containing the name of the property to
 *                                        retrieve. Its content is case-sensitive and it must be encoded in UTF-8.
 *                                          o If hPropSet is a property enumerator handle, name is ignored and can be NULL.
 *                                          o Otherwise, name cannot be NULL
 * @param[out]    value                   A pointer filled with the UUID. Must not be NULL.
 *
 * @return        TEE_SUCCESS: In case of success
 *                TEE_ERROR_ITEM_NOT_FOUND: If the property is not found or if name is not a valid UTF-8 encoding
 *                TEE_ERROR_BAD_FORMAT: If the property cannot be converted into a UUID
 */
TEE_Result
TEE_GetPropertyAsUUID(
    TEE_PropSetHandle  propsetOrEnumerator,
    char*              name, /* [instringopt] */
    TEE_UUID*          value /* [out] */
);

/**
 * @brief Get property as TEE_Identity.
 *
 * The function TEE_GetPropertyAsIdentity retrieves an individual property and converts its value into a TEE_Identity.
 *
 * @param[in]     propsetOrEnumerator     One of the TEE_PROPSET_XXX pseudo-handles or a handle on a property enumerator
 * @param[in]     name                    A pointer to the zero-terminated string containing the name of the property to
 *                                        retrieve. Its content is case-sensitive and it must be encoded in UTF-8.
 *                                          o If hPropSet is a property enumerator handle, name is ignored and can be NULL.
 *                                          o Otherwise, name cannot be NULL
 * @param[out]    value                   A pointer filled with the identity. Must not be NULL.
 *
 * @return        TEE_SUCCESS: In case of success
 *                TEE_ERROR_ITEM_NOT_FOUND: If the property is not found or if name is not a valid UTF-8 encoding
 *                TEE_ERROR_BAD_FORMAT: If the property cannot be converted into an Identity
 */
TEE_Result
TEE_GetPropertyAsIdentity(
    TEE_PropSetHandle  propsetOrEnumerator,
    char*              name, /* [instringopt] */
    TEE_Identity*      value /* [out] */
);

/**
 * @brief Allocate a Property Set enumerator.
 *
 *    The function TEE_AllocatePropertyEnumerator allocates a property enumerator object. Once a handle on a property enumerator
 * has been allocated, it can be used to enumerate properties in a property set using the function TEE_StartPropertyEnumerator.
 *
 * @param[in]     enumerator    A pointer filled with an opaque handle on the property enumerator on success and with TEE_HANDLE_NULL on error
 *
 * @return        TEE_SUCCESS: In case of success
 *                TEE_ERROR_OUT_OF_MEMORY: If there are not enough resources to allocate the property enumerator
 */
TEE_Result
TEE_AllocatePropertyEnumerator(
    TEE_PropSetHandle* enumerator
);

/**
 * @brief Free a Property Set enumerator.
 *
 * The function TEE_FreePropertyEnumerator deallocates a property enumerator object.
 *
 * @param[in]       enumerator    A handle on the enumerator to free
 */
void
TEE_FreePropertyEnumerator(
    TEE_PropSetHandle enumerator
);

/**
 * @brief Assign a Property Set to the Enumerator.
 *
 *    The function TEE_StartPropertyEnumerator starts to enumerate the properties in an enumerator.
 * Once an enumerator is attached to a property set:
 *  • Properties can be retrieved using one of the TEE_GetPropertyAsXXX functions, passing the enumerator handle as the property set and NULL as the name.
 *  • The function TEE_GetPropertyName can be used to retrieve the name of the current property in the enumerator.
 *  • The function TEE_GetNextProperty can be used to advance the enumeration to the next property in the property set.
 *
 *  @param[in]      enumerator    A handle on the enumerator
 *  @param[in]      propSet       A pseudo-handle on the property set to enumerate. Must be one of the TEE_PROPSET_XXX pseudo-handles.
 */
void
TEE_StartPropertyEnumerator(
    TEE_PropSetHandle enumerator,
    TEE_PropSetHandle propSet
);

/**
 * @brief Reset Property Set enumerator to the un-assigned state.
 *
 * The function TEE_ResetPropertyEnumerator resets a property enumerate to its state immediately after allocation.
 * If an enumeration is currently started, it is abandoned.
 *
 * @param[in]       enumerator    A handle on the enumerator to reset
 */
void
TEE_ResetPropertyEnumerator(
    TEE_PropSetHandle enumerator
);

/**
 * @brief Get the name of the current property from the enumerator as a (char *).
 *
 * The function TEE_GetPropertyName gets the name of the current property in an enumerator.
 * The property name MUST be the valid UTF-8 encoding of a Unicode string containing no U+0000 code points.
 *
 * @param[in]       enumerator    A handle on the enumerator
 * @param[out]      nameBuffer    The buffer filled with the name
 * @param[inout]    nameBufferLen The buffer length that is updated to reflect the size property name.
 *
 * @return          TEE_SUCCESS: In case of success
 *                  TEE_ERROR_ITEM_NOT_FOUND: If there is no current property either because the enumerator
 *                  has not started or because it has reached the end of the property set
 *                  TEE_ERROR_SHORT_BUFFER: If the name buffer is not large enough to contain the property name
 */
TEE_Result
TEE_GetPropertyName(
    TEE_PropSetHandle enumerator,
    void*             nameBuffer,   /* [outstring] */
    size_t*           nameBufferLen
);

/**
 * @brief Iterate to the next property in the enumerator.
 *
 * The function TEE_GetNextProperty advances the enumerator to the next property.
 *
 * @param[in]       enumerator      A handle on the enumerator
 *
 * @return          TEE_SUCCESS: In case of success
 *                  TEE_ERROR_ITEM_NOT_FOUND: If the enumerator has reached the end of the property set or if it has not started
 */
TEE_Result
TEE_GetNextProperty(
    TEE_PropSetHandle enumerator
);

#ifdef __cplusplus
  }
#endif

#endif /* GPPROPERTYACCESS_H */

#ifndef GPHEAP_H
#define GPHEAP_H

/* ------------------------------------------------------------------------
 * Include files
 * ------------------------------------------------------------------------ */
#include "gpTypes.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
  {
#endif

/**
 * @brief Checks memory access rights on buffer address.
 *
 * The TEE_CheckMemoryAccessRights function causes the Implementation to examine a buffer of memory
 * specified in the parameters buffer and size and to determine whether the current Trusted Application
 * instance has the access rights requested in the parameter accessFlags. If the characteristics of the buffer
 * are compatible with accessFlags, then the function returns TEE_SUCCESS. Otherwise, it returns
 * TEE_ERROR_ACCESS_DENIED. Note that the buffer SHOULD NOT be accessed by the function, but the
 * Implementation SHOULD check the access rights based on the address of the buffer and internal memory
 * management information.
 *
 * @return  Upon successful completion, TEE_SUCCESS, otherwise TEE_ERROR_ACCESS_DENIED
 *
*/

TEE_Result
TEE_CheckMemoryAccessRights( uint32_t accessFlags,
                             void* buffer,
                             size_t size );


/**
 * @brief Set an application global variable.
 *
 * The TEE_SetInstanceData and TEE_GetInstanceData functions provide an alternative to writable global data
 * (writable variables with global scope and writable static variables with global or function scope). While
 * an Implementation MUST support C global variables, using these functions may be sometimes more efficient,
 * especially if only a single instance data variable is required.
 * These two functions can be used to register and access an instance variable. Typically this instance
 * variable can be used to hold a pointer to a Trusted Application-defined memory block containing any
 * writable data that needs instance global scope, or writable static data that needs instance function scope.
 * An equivalent session context variable for managing session global and static data exists for sessions
 * (see TA_OpenSessionEntryPoint, TA_InvokeCommandEntryPoint, and TA_CloseSessionEntryPoint in section 4.3).
 * This function sets the Trusted Application instance data pointer. The data pointer can then be retrieved
 * by the Trusted Application instance by calling the TEE_GetInstanceData function.
 *
 * @param[in] instanceData    A pointer to the global Trusted Application instance data. This pointer may be NULL.
 */
void
TEE_SetInstanceData(
    void* instanceData
);

/**
 * @brief Get the application global variable.
 *
 * The TEE_GetInstanceData function retrieves the instance data pointer set by the Trusted Application
 * using the TEE_GetInstanceData function.
 *
 * @return The value returned is the previously set pointer to the Trusted Application instance data, or NULL if
 * no instance data pointer has yet been set.
 */
void*
TEE_GetInstanceData( void );

/**
 * @brief Allocate dynamic memory.
 *
 * The parameter hint is a hint to the allocator. In this version of the specification, only one hint
 * is defined. This parameter is nonetheless included so that the Trusted Applications may refer to
 * various pools of memory or request special characteristics for the allocated memory by using an
 * implementation-defined hint. Future versions of this specification may introduce additional standard hints.
 * If the space cannot be allocated, a NULL pointer is returned.
 *
 * Calls qsee_malloc().
 *
 * @param[in] size    The size of the buffer to be allocated.
 * @param[in] hint    A hint to the allocator. Currently defined values are as follows:
 *                      o The default value, 0, guarantees that the returned block of memory is filled with zeros.
 *                      o Values in the range [0x00000001, 0x7FFFFFFF] are reserved for future version of this specification.
 *                      o Values in the range [0x80000000, 0xFFFFFFFF] can be used for implementation-defined hints.
 *
 * @return  Upon successful completion, with size not equal to zero, the function returns a pointer to the allocated space.
 *          If the space cannot be allocated, a NULL pointer is returned.
 */
void*
TEE_Malloc(
    size_t size,
    uint32_t hint
);

void*
TEE_Realloc( void* buffer,
             uint32_t newSize );

/**
 * @brief Free dynamically allocated memory.
 *
 * The TEE_Free function causes the space pointed to by buffer to be deallocated; that is, made available for further allocation.
 * If buffer is a NULL pointer, TEE_Free does nothing.
 *
 * @param[in] buffer    Upon successful completion, with size not equal to zero, the function returns a pointer
 *                      to the allocated space. If the space cannot be allocated, a NULL pointer is returned.
 */
void
TEE_Free(
    void* buffer
);

/**
 * @brief Copy bytes from source to destination.
 *
 * The TEE_MemMove function copies size bytes from the object pointed to by src into the object pointed to by dest.
 * Copying takes place as if the size bytes from the object pointed to by src are first copied into a temporary
 * array of size bytes that does not overlap the objects pointed to by dest and src, and then the size bytes
 * from the temporary array are copied into the object pointed to by dest.
 *
 * @param[in] dest    A pointer to the destination buffer
 * @param[in] src     A pointer to the source buffer
 * @param[in] size    The number of bytes to be copied
 */
void
TEE_MemMove(
    void* dest,
    void* src,
    uint32_t size
);

/**
 * @brief Compare two blocks of memory.
 *
 * The TEE_MemCompare function compares the first size bytes of the object pointed to by buffer1 to the first size
 * bytes of the object pointed to by buffer2.
 *
 * @param[in] buffer1     A pointer to the first buffer
 * @param[in] buffer2     A pointer to the second buffer
 * @param[in] size        The number of bytes to be compared
 *
 * @return The sign of a non-zero return value is determined by the sign of the difference between the values of
 *         the first pair of bytes (both interpreted as type uint8_t) that differ in the objects being compared.
 *          • If the first byte that differs is higher in buffer1, then return an integer greater than zero.
 *          • If the first size bytes of the two buffers are identical, then return zero.
 *          • If the first byte that differs is higher in buffer2, then return an integer lower than zero.
 */
int32_t
TEE_MemCompare(
    void* buffer1,
    void* buffer2,
    uint32_t size
);

/**
 * @brief Fill memory with byte x.
 *
 * The TEE_MemFill function writes the byte x (converted to a uint8_t) into the first size bytes of the
 * object pointed to by buffer.
 *
 * @param[in] buffer    A pointer to the destination buffer
 * @param[in] x         The value to be set
 * @param[in] size      The number of bytes to be set
 */
void
TEE_MemFill(
    void* buffer,
    uint32_t x,
    uint32_t size
);

#ifdef __cplusplus
  }
#endif

#endif /* GPHEAP_H */

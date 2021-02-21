#ifndef _GP_PERSISTENT_OBJECTS_
#define _GP_PERSISTENT_OBJECTS_

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
   @addtogroupqsee_sfs_apis
   @{
*/

/**
The TEE_OpenPersistentObject function opens a handle on an existing persistent object.
It returns a handle that can be used to access the object’s attributes and data stream.
The storageID parameter indicates which Trusted Storage Space to access.
The flags parameter is a set of flags that controls the access rights and sharing
permissions with which the object handle is opened. The value of the flags parameter
is constructed by a bitwise-inclusive OR of flags from the following list:

  Access control flags:
    - TEE_DATA_FLAG_ACCESS_READ:
      The object is opened with the read access right. This allows the Trusted Application
      to call the function TEE_ReadObjectData.
    - TEE_DATA_FLAG_ACCESS_WRITE:
      The object is opened with the write access right. This allows the Trusted Application
      to call the functions TEE_WriteObjectData and TEE_TruncateObjectData.
    - TEE_DATA_FLAG_ACCESS_WRITE_META:
      The object is opened with the write-meta access right. This allows the Trusted
      Application to call the functions TEE_CloseAndDeletePersistentObject and
      TEE_RenamePersistentObject.

  Sharing permission control flags:
    - TEE_DATA_FLAG_SHARE_READ:
      The caller allows another handle on the object to be created with read access.
    - TEE_DATA_FLAG_SHARE_WRITE:
      The caller allows another handle on the object to be created with write access.
    - TEE_DATA_FLAG_OVERWRITE:
      If this flag is present and the object exists, then the object is deleted and
      re-created as an atomic operation: that is the TA sees either the old object or
      the new one. If the flag is absent and the object exists, then the function SHALL
      return TEE_ERROR_ACCESS_CONFLICT.

  Other flags are reserved for future use and SHALL be set to 0.

Multiple handles may be opened on the same object simultaneously, but sharing MUST be
explicitly allowed.
The initial data position in the data stream is set to 0.
Every Trusted Storage implementation is expected to return TEE_ERROR_CORRUPT_OBJECT if
a Trusted Application attempts to open an object and the TEE determines that its contents
(or those of the storage itself) have been tampered with or rolled back.

@param[in]  storageID    The storage to use. It must be TEE_STORAGE_PRIVATE.
@param[in]  objectID     The object identifier. Note that this cannot reside in shared
                         memory.
@param[in]  objectIDLen  Length of objectID
@param[in]  flags        The flags which determine the settings under which the object
                         is opened.
@param[out] object       A pointer to the handle, which contains the opened handle upon
                         successful completion. If this function fails for any reason,
                         the value pointed to by object is set to TEE_HANDLE_NULL. When
                         the object handle is no longer required, it MUST be closed using
                         a call to the TEE_CloseObject function.

@return
TEE_SUCCESS:                     In case of success
TEE_ERROR_ITEM_NOT_FOUND:        If the storage denoted by storageID does not exist or if
                                 the object identifier cannot be found in the storage
TEE_ERROR_ACCESS_CONFLICT:       If an access right conflict was detected while opening the
                                 object
TEE_ERROR_OUT_OF_MEMORY:         If there is not enough memory to complete the operation
TEE_ERROR_CORRUPT_OBJECT:        If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE: If the persistent object is stored in a storage area which
                                 is currently inaccessible.

*/
TEE_Result TEE_OpenPersistentObject
(
  uint32_t storageID,
  void* objectID,
  size_t objectIDLen,
  uint32_t flags,
  TEE_ObjectHandle* object
);

/**
The TEE_CreatePersistentObject function creates a persistent object with initial attributes
and an initial data stream content, and optionally returns either a handle on the created
object, or TEE_HANDLE_NULL upon failure.
The storageID parameter indicates which Trusted Storage Space to access
The flags parameter is a set of flags that controls the access rights, sharing permissions,
and object creation mechanism with which the object handle is opened. The value of the flags
parameter is constructed by a bitwise-inclusive OR of flags from the following list:

  Access control flags:
    - TEE_DATA_FLAG_ACCESS_READ:
      The object is opened with the read access right. This allows the Trusted Application
      to call the function TEE_ReadObjectData.
    - TEE_DATA_FLAG_ACCESS_WRITE:
      The object is opened with the write access right. This allows the Trusted Application
      to call the functions TEE_WriteObjectData and TEE_TruncateObjectData.
    - TEE_DATA_FLAG_ACCESS_WRITE_META:
      The object is opened with the write-meta access right. This allows the Trusted
      Application to call the functions TEE_CloseAndDeletePersistentObject and
      TEE_RenamePersistentObject.

  Sharing permission control flags:
    - TEE_DATA_FLAG_SHARE_READ:
      The caller allows another handle on the object to be created with read access.
    - TEE_DATA_FLAG_SHARE_WRITE:
      The caller allows another handle on the object to be created with write access.
    - TEE_DATA_FLAG_OVERWRITE:
      If this flag is present and the object exists, then the object is deleted and
      re-created as an atomic operation: that is the TA sees either the old object or
      the new one. If the flag is absent and the object exists, then the function SHALL
      return TEE_ERROR_ACCESS_CONFLICT.

  Other flags are reserved for future use and SHALL be set to 0.

The attributes of the newly created persistent object are taken from attributes, which can
be another persistent object or an initialized transient object. The attributes argument
can also be NULL for a pure data object. The object type, size, and usage are copied from
attributes. If attributes is NULL, the object type SHALL be set to TEE_TYPE_DATA to create
a pure data object.
Multiple handles may be opened on the same object simultaneously, but sharing MUST be
explicitly allowed.
The initial data position in the data stream is set to 0.

@param[in] storageID      The storage to use. It must be TEE_STORAGE_PRIVATE.
@param[in] objectID       The object identifier. Note that this cannot reside in shared
                          memory.
@param[in] objectIDLen    Length of objectID
@param[in] flags          The flags which determine the settings under which the object
                          is opened
@param[in] attributes     A handle on a persistent object or an initialized transient
                          object from which to take the persistent object attributes.
                          Can be TEE_HANDLE_NULL if the persistent object contains no
                          attribute; for example, if it is a pure data object.
@param[in]initialData     The initial data content of the persistent object
@param[in]initialDataLen  Length of initialData
@param[out]object         A pointer to the handle, which contains the opened handle upon
                          successful completion. If this function fails for any reason,
                          the value pointed to by object is set to TEE_HANDLE_NULL. When
                          the object handle is no longer required, it MUST be closed using
                          a call to the TEE_CloseObject function.

@return
TEE_SUCCESS:                      In case of success
TEE_ERROR_ITEM_NOT_FOUND:         If the storage denoted by storageID does not exist or if
                                  the object identifier cannot be found in the storage
TEE_ERROR_ACCESS_CONFLICT:        If an access right conflict was detected while opening the
                                  object
TEE_ERROR_OUT_OF_MEMORY:          If there is not enough memory to complete the operation
TEE_ERROR_STORAGE_NO_SPACE:       If insufficient space is available to create the persistent
                                  object
TEE_ERROR_CORRUPT_OBJECT:         If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE:  If the persistent object is stored in a storage area which
                                  is currently inaccessible.

*/
TEE_Result TEE_CreatePersistentObject
(
  uint32_t storageID,
  void* objectID, size_t objectIDLen,
  uint32_t flags,
  TEE_ObjectHandle attributes,
  void* initialData, size_t initialDataLen,
  TEE_ObjectHandle* object
);

/**
The TEE_CloseAndDeletePersistentObject1 function marks an object for deletion and closes
the object handle.
The object handle MUST have been opened with the write-meta access right, which means
access to the object is exclusive.
Deleting an object is atomic; once this function returns, the object is definitely deleted
and no more open handles for the object exist. This SHALL be the case even if the object or
the storage containing it have become corrupted.
The only reason this routine can fail is if the storage area containing the object becomes
inaccessible (e.g. the user removes the media holding the object). In this case
TEE_ERROR_STORAGE_NOT_AVAILABLE SHALL be returned.
If object is TEE_HANDLE_NULL, the function does nothing.

@param[in] object   The object handle

@return

*/
TEE_Result TEE_CloseAndDeletePersistentObject1( TEE_ObjectHandle object );

/**
Use of this function is DEPRECATED – new code SHOULD use the
TEE_CloseAndDeletePersistentObject1 function instead.

The TEE_CloseAndDeletePersistentObject function marks an object for deletion and closes
the object handle.
The object handle MUST have been opened with the write-meta access right, which means
access to the object is exclusive.
Deleting an object is atomic; once this function returns, the object is definitely deleted
and no more open handles for the object exist. This SHALL be the case even if the object or
the storage containing it have become corrupted.
If the storage containing the object is unavailable then this routine SHALL panic.
If object is TEE_HANDLE_NULL, the function does nothing.

@param[in] object   The object handle

@return

*/
void TEE_CloseAndDeletePersistentObject(TEE_ObjectHandle object);


/**
The function TEE_RenamePersistentObject changes the identifier of an object. The object
handle MUST have been opened with the write-meta access right, which means access to the
object is exclusive.
Renaming an object is an atomic operation; either the object is renamed or nothing happens.

@param[in] object         The object handle
@param[in] newObjectID    A buffer containing the new object identifier. The identifier
                          contains arbitrary bytes, including the zero byte. The buffer
                          containing the new object identifier cannot reside in shared
                          memory.
@param[in] newObjectIDLen The identifier length MUST be less than or equal to
                          TEE_OBJECT_ID_MAX_LEN and can be zero.

@return
TEE_SUCCESS:                      In case of success
TEE_ERROR_ACCESS_CONFLICT:        If an object with the same identifier already exists
TEE_ERROR_CORRUPT_OBJECT:         If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE:  If the persistent object is stored in a storage area which
                                  is currently inaccessible.

*/
TEE_Result TEE_RenamePersistentObject
(
  TEE_ObjectHandle object,
  void* newObjectID,
  uint32_t newObjectIDLen
);

/**
The TEE_ReadObjectData function attempts to read size bytes from the data stream associated
with the object object into the buffer pointed to by buffer.
The object handle MUST have been opened with the read access right.
The bytes are read starting at the position in the data stream currently stored in the
object handle. The handle’s position is incremented by the number of bytes actually read.
On completion TEE_ReadObjectData sets the number of bytes actually read in the uint32_t
pointed to by count. The value written to *count may be less than size if the number of
bytes until the end-ofstream is less than size. It is set to 0 if the position at the start
of the read operation is at or beyond the end-of-stream. These are the only cases where
*count may be less than size.
No data transfer can occur past the current end of stream. If an attempt is made to read
past the end-ofstream, the TEE_ReadObjectData function stops reading data at the
end-of-stream and returns the data read up to that point. This is still a success. The
position indicator is then set at the end-of-stream. If the position is at, or past, the end
of the data when this function is called, then no bytes are copied to *buffer and *count is
set to 0.

@param[in]  object   The object handle
@param[out] buffer   A pointer to the memory which, upon successful completion, contains
                     the bytes read
@param[in]  size     The number of bytes to read
@param[out] count    A pointer to the variable which upon successful completion contains
                     the number of bytes read

@return
TEE_SUCCESS                       In case of success
TEE_ERROR_CORRUPT_OBJECT:         If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE:  If the persistent object is stored in a storage area which
                                  is currently inaccessible.
*/
TEE_Result TEE_ReadObjectData
(
  TEE_ObjectHandle object,
  void* buffer,
  size_t size,
  uint32_t* count
);

/**
The TEE_WriteObjectData function writes size bytes from the buffer pointed to by buffer to
the data stream associated with the open object handle object.
The object handle MUST have been opened with the write access permission.
If the current data position points before the end-of-stream, then size bytes are written
to the data stream, overwriting bytes starting at the current data position. If the current
data position points beyond the stream’s end, then the data stream is first extended with
zero bytes until the length indicated by the data position indicator is reached, and then
size bytes are written to the stream. Thus, the size of the data stream can be increased as
a result of this operation.
If the operation would move the data position indicator to beyond its maximum possible value,
then TEE_ERROR_OVERFLOW is returned and the operation fails.
The data position indicator is advanced by size. The data position indicators of other
object handles opened on the same object are not changed.
Writing in a data stream is atomic; either the entire operation completes successfully or
no write is done.

@param[in] object   The object handle
@param[in] buffer   The buffer containing the data to be written
@param[in] size     The number of bytes to write

@return
TEE_SUCCESS:                      In case of success
TEE_ERROR_STORAGE_NO_SPACE:       If insufficient storage space is available
TEE_ERROR_OVERFLOW:               If the value of the data position indicator resulting
                                  from this operation would be greater than
                                  TEE_DATA_MAX_POSITION
TEE_ERROR_CORRUPT_OBJECT:         If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE:  If the persistent object is stored in a storage area which
                                  is currently inaccessible.

*/
TEE_Result TEE_WriteObjectData
(
  TEE_ObjectHandle object,
  void* buffer,
  size_t size
);

/**
The function TEE_TruncateObjectData changes the size of a data stream. If size is less
than the current size of the data stream then all bytes beyond size are removed. If size
is greater than the current size of the data stream then the data stream is extended by
adding zero bytes at the end of the stream.
The object handle MUST have been opened with the write access permission.
This operation does not change the data position of any handle opened on the object.
Note that if the current data position of such a handle is beyond size, the data position
will point beyond the object data’s end after truncation.
Truncating a data stream is atomic: Either the data stream is successfully truncated or
nothing happens.

@param[in] object   The object handle
@param[in] size     The new size of the data stream

@return
TEE_SUCCESS:                      In case of success
TEE_ERROR_STORAGE_NO_SPACE:       If insufficient storage space is available
TEE_ERROR_CORRUPT_OBJECT:         If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE:  If the persistent object is stored in a storage area which
                                  is currently inaccessible.

*/
TEE_Result TEE_TruncateObjectData
(
  TEE_ObjectHandle object,
  uint32_t size
);

/**
The TEE_SeekObjectData function sets the data position indicator associated with the
object handle.
The parameter whence controls the meaning of offset:

    - If whence is TEE_DATA_SEEK_SET,
      the data position is set to offset bytes from the beginning of the data stream.
    - If whence is TEE_DATA_SEEK_CUR, the data position is set to its current position
      plus offset.
    - If whence is TEE_DATA_SEEK_END, the data position is set to the size of the object
      data plus offset.

The TEE_SeekObjectData function may be used to set the data position beyond the end of
stream; this does not constitute an error. However, the data position indicator does have
a maximum value which is TEE_DATA_MAX_POSITION. If the value of the data position indicator
resulting from this operation would be greater than TEE_DATA_MAX_POSITION, the error
TEE_ERROR_OVERFLOW is returned.
If an attempt is made to move the data position before the beginning of the data stream,
the data position is set at the beginning of the stream. This does not constitute an error.

@param[in] object   The object handle
@param[in] offset   The number of bytes to move the data position.
                    A positive value moves the data position forward; a negative value
                    moves the data position backward.
@param[in] whence   The position in the data stream from which to calculate the new
                    position

@return
TEE_SUCCESS:                      In case of success
TEE_ERROR_OVERFLOW:               If the value of the data position indicator resulting
                                  from this operation would be greater than
                                  TEE_DATA_MAX_POSITION
TEE_ERROR_CORRUPT_OBJECT:         If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE:  If the persistent object is stored in a storage area
                                  which is currently inaccessible.
*/
TEE_Result TEE_SeekObjectData
(
  TEE_ObjectHandle object,
  int32_t offset,
  TEE_Whence whence
);


/**
The TEE_AllocatePersistentObjectEnumerator function allocates a handle on an object
enumerator. Once an object enumerator handle has been allocated, it can be reused for
multiple enumerations.

@param[out] objectEnumerator   A pointer filled with the newly-allocated object
                               enumerator handle on success. Set to TEE_HANDLE_NULL
                               in case of error.

@return
TEE_SUCCESS:              In case of success
TEE_ERROR_OUT_OF_MEMORY:  If there is not enough memory to allocate the enumerator
                          handle
*/
TEE_Result TEE_AllocatePersistentObjectEnumerator
(
  TEE_ObjectEnumHandle* objectEnumerator
);

/**
The TEE_FreePersistentObjectEnumerator function deallocates all resources associated
with an object enumerator handle. After this function is called, the handle is no longer
valid.

@param[in] objectEnumerator  The handle to close. If objectEnumerator is TEE_HANDLE_NULL,
                             then this function does nothing.

*/
void TEE_FreePersistentObjectEnumerator
(
  TEE_ObjectEnumHandle objectEnumerator
);

/**
The TEE_ResetPersistentObjectEnumerator function resets an object enumerator handle to
its initial state after allocation. If an enumeration has been started, it is stopped.
This function does nothing if objectEnumerator is TEE_HANDLE_NULL.

@param[in] objectEnumerator  The handle to reset.

*/
void TEE_ResetPersistentObjectEnumerator
(
  TEE_ObjectEnumHandle objectEnumerator
);

/**
The TEE_StartPersistentObjectEnumerator function starts the enumeration of all the
persistent objects in a given Trusted Storage. The object information can be retrieved
by calling the function TEE_GetNextPersistentObject repeatedly.
The enumeration does not necessarily reflect a given consistent state of the storage:
During the enumeration, other TAs or other instances of the TA may create, delete, or
rename objects. It is not guaranteed that all objects will be returned if objects are
created or destroyed while the enumeration is in progress.
To stop an enumeration, the TA can call the function TEE_ResetPersistentObjectEnumerator,
which detaches the enumerator from the Trusted Storage. The TA can call the function
TEE_FreePersistentObjectEnumerator to completely deallocate the object enumerator.
If this function is called on an enumerator that has already been started, the enumeration
is first reset then started.

@param[in] objectEnumerator   A valid handle on an object enumerator
@param[in] storageID          The identifier of the storage in which the objects MUST be
                              enumerated.

@return
TEE_SUCCESS:                     In case of success
TEE_ERROR_ITEM_NOT_FOUND:        If the storage does not exist or if there is no object
                                 in the specified storage
TEE_ERROR_CORRUPT_OBJECT:        If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE: If the persistent object is stored in a storage area
                                 which is currently inaccessible.
*/
TEE_Result TEE_StartPersistentObjectEnumerator
(
  TEE_ObjectEnumHandle objectEnumerator,
  uint32_t storageID
);

/**
The TEE_GetNextPersistentObject function gets the next object in an enumeration and
returns information about the object: type, size, identifier, etc.
If there are no more objects in the enumeration or if there is no enumeration started,
then the function returns TEE_ERROR_ITEM_NOT_FOUND.
If while enumerating objects a corrupt object is detected, then its object ID SHALL
be returned in objectID, objectInfo shall be zeroed, and the function SHALL return
TEE_ERROR_CORRUPT_OBJECT.

@param[in]  objectEnumerator  A handle on the object enumeration
@param[out] objectInfo        A pointer to a TEE_ObjectInfo filled with the object
                              information as specified in the function TEE_GetObjectInfo1
                              in section 5.5.1. It may be NULL.
@param[out] objectID          Pointer to an array able to hold at least TEE_OBJECT_ID_MAX_LEN
                              bytes. On exit the object identifier is written to this location.
@param[out] objectIDLen       Filled with the size of the object identifier (from 0 to
                              TEE_OBJECT_ID_MAX_LEN)

@return
TEE_SUCCESS:                     In case of success
TEE_ERROR_ITEM_NOT_FOUND:        If there are no more elements in the object enumeration
                                 or if no enumeration is started on this handle
TEE_ERROR_CORRUPT_OBJECT:        If the storage or returned object is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE: If the persistent object is stored in a storage area
                                   which is currently inaccessible.
*/
TEE_Result TEE_GetNextPersistentObject(
  TEE_ObjectEnumHandle objectEnumerator,
  TEE_ObjectInfo* objectInfo,
  void* objectID,
  uint32_t* objectIDLen
);

/** @} */   /* end_addtogroup qsee_sfs_apis */
#ifdef __cplusplus
}
#endif

#endif //_GP_PERSISTENT_OBJECTS_

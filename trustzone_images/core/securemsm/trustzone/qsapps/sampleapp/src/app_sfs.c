/*
@file app_crypto.c
@brief This file is a sample code that show how QSEE crypto API's can be used.

*/
/*===========================================================================
   Copyright (c) 2011 - 2015 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE
  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsapps/sampleapp/src/app_sfs.c#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
  09/29/15    aw      Fixed CR900655 - Remove link API as it is no longer supported
  05/19/15    cz     Changed fs and sfs test pathes to /data/misc/qsee/sampleapp
  03/06/15    cz     Fixed tz_app_fs test clean up issue
===========================================================================*/
#include "qsee_log.h"
#include "qsee_heap.h"
#include "qsee_sfs.h"
#include "qsee_counter.h"
#include "qsee_timer.h"
#include "gpPersistObjData.h"
#include "IxErrno.h"

#ifdef APP_SFS_L2_TEST
#include "tzcommon_entry.h"
#include "qsee_fs.h"
#include <string.h>
#else
#include "tzbsp_fs.h"
#endif

#define FILE_NAME_TOO_LONG "/persist/data/mytest/this/is/just/much/too/long/of/a/name/to/use/myfile.txt"
#define FILE_NAME "/persist/data/mytest/myfile.txt"
#define FILE_SIZE (6 * 1024)

int smplap_sfs_unit_open(void)
{
  int i = 0, ret = 0, fd = 0;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_open TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);

  /* Negative Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_open Negative Tests ----------------------");

  /* Open File with No O_CREAT Flag Set */
  if (0 != (fd = qsee_sfs_open(FILE_NAME, O_RDONLY)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  /* Create File with Too Large of File Name */
  if (0 != (fd = qsee_sfs_open(FILE_NAME_TOO_LONG, O_CREAT)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_open Negative PASSED----------------------");

  /* Positive Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_open Positive Tests ----------------------");

  /* Create a File with O_CREAT */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDONLY)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Open a File with O_WRONLY */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_WRONLY)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Open a File with O_RDONLY */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_RDONLY)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Open a File with O_RDWR */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_RDWR)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Open a File with O_TRUNC */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_RDWR | O_TRUNC)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Open a File with O_APPEND */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_RDWR | O_APPEND)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Clean Up File */
  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_open Positive PASSED----------------------");

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_open PASSED ---------------------------------");

Exit:

  if (0 != fd)
    qsee_sfs_close(fd);

  qsee_sfs_rm(FILE_NAME);

  return ret;
}

#define BASE_WRITE_SIZE 691

int smplap_sfs_unit_read_write(void)
{
  int i = 0, j = 0, ret = 0, fd = 0, total = 0;
  void* data = NULL;
  char buffer[10] = { 0 };

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_read_write TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);

  /* Negative Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_read_write Negative Tests ----------------------");

  /* Create the File to Operate On */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  /* Null Buffer Inputs */
  if (0 <= (ret = qsee_sfs_write(fd, NULL, 10)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }
  if (0 <= (ret = qsee_sfs_read(fd, NULL, 10)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Negative Value Number of Bytes */
  if (0 <= (ret = qsee_sfs_write(fd, buffer, -10)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }
  if (0 <= (ret = qsee_sfs_read(fd, buffer, -10)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Clean Up File */
  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_read_write Negative PASSED----------------------");

  /* Positive Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_read_write Positive Tests ----------------------");

  for (i = 1; i < 10; i++)
  {
    int len = i * BASE_WRITE_SIZE;
    if (NULL == (data = qsee_malloc(len)))
    {
      GPLOG_ERROR(len);
      ret = -1;
      goto Exit;
    }

    memset(data, 0x66, len);

    total = 0;

    /* Create the File to Operate On */
    if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }

    /* Write to FILE_SIZE in Chunks */
    while (total < FILE_SIZE)
    {
      int writeSize = (len < FILE_SIZE - total) ? len : FILE_SIZE - total;
      if (writeSize != (ret = qsee_sfs_write(fd, data, writeSize)))
      {
        GPLOG_ERROR(ret);
        ret = -1;
        goto Exit;
      }
      total += writeSize;
    }

    /* Seek Back to Beginning of File */
    if (0 != (ret = qsee_sfs_seek(fd, 0, SEEK_SET)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    total = 0;

    /* Read bytes in File to Verify Writes */
    while (total < FILE_SIZE)
    {
      int readSize = (len < FILE_SIZE - total) ? len : FILE_SIZE - total;
      if (readSize != (ret = qsee_sfs_read(fd, data, readSize)))
      {
        GPLOG_ERROR(ret);
        ret = -1;
        goto Exit;
      }
      for (j = 0; j < readSize; j++)
      {
        if (((uint8*)data)[j] != 0x66)
        {
          GPLOG_ERROR(((uint8*)data)[j]);
          ret = -1;
          goto Exit;
        }
      }
      total += readSize;
    }

    qsee_sfs_close(fd);
    fd = 0;

    /* Clean Up File */
    if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    qsee_free(data);
    data = NULL;

  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_read_write Positive PASSED----------------------");

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_read_write PASSED ---------------------------------");

Exit:
  if (NULL != data)
    qsee_free(data);

  if (0 != fd)
    qsee_sfs_close(fd);

  qsee_sfs_rm(FILE_NAME);

  return ret;
}

#define GET_SIZE_WRITE_SIZE 512

int smplap_sfs_unit_get_size(void)
{
  int i = 0, ret = 0, fd = 0, total = 0;
  uint32_t size = 0;
  void* data = NULL;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_get_size TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);

  /* Create the File to Operate On */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  /* Negative Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_get_size Negative Tests ----------------------");

  if (E_SUCCESS == (ret = qsee_sfs_getSize(0, &size)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (E_SUCCESS == (ret = qsee_sfs_getSize(fd, NULL)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_get_size Negative PASSED----------------------");

  /* Positive Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_get_size Positive Tests ----------------------");

  if (NULL == (data = qsee_malloc(GET_SIZE_WRITE_SIZE)))
  {
    GPLOG_ERROR(GET_SIZE_WRITE_SIZE);
    ret = -1;
    goto Exit;
  }

  for (i = GET_SIZE_WRITE_SIZE; i < FILE_SIZE; i += GET_SIZE_WRITE_SIZE)
  {

    if (E_SUCCESS != (ret = qsee_sfs_getSize(fd, &size)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    if (total != size)
    {
      GPLOG_ERROR(total);
      GPLOG_ERROR(size);
      ret = -1;
      goto Exit;
    }

    if (GET_SIZE_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, GET_SIZE_WRITE_SIZE)))
    {
      GPLOG_ERROR(GET_SIZE_WRITE_SIZE);
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    total += GET_SIZE_WRITE_SIZE;

  }

  ret = 0;

  qsee_free(data);
  data = NULL;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_get_size Positive PASSED----------------------");

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_get_size PASSED ---------------------------------");

Exit:
  if (NULL != data)
    qsee_free(data);

  if (0 != fd)
    qsee_sfs_close(fd);

  qsee_sfs_rm(FILE_NAME);

  return ret;
}

#define SEEK_WRITE_SIZE 64
#define SEEK_FILE_CHUNKS 4
#define SEEK_SEGMENT_SIZE (4*1024)
#define SEEK_FILE_SIZE    (SEEK_SEGMENT_SIZE*2)

int smplap_sfs_unit_seek(void)
{
  int i = 0, ret = 0, fd = 0;
  void* data = NULL;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_seek TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);

  if (NULL == (data = qsee_malloc(SEEK_SEGMENT_SIZE)))
  {
    GPLOG_ERROR(data);
    ret = -1;
    goto Exit;
  }

  memset(data, 0x99, SEEK_SEGMENT_SIZE);

  /* Create the File to Operate On */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  /* Do SEEK_FILE_CHUNKS Writes to Creat 4k Segments */
  for (i = 0; i < SEEK_FILE_SIZE / SEEK_SEGMENT_SIZE; i++)
  {
    if (SEEK_SEGMENT_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_SEGMENT_SIZE)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
  }

  /* Negative Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_seek Negative Tests ----------------------");

  /* Invalid Whence */
  if (-1 != (ret = qsee_sfs_seek(fd, 0, 0x666)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }
  if (-1 != (ret = qsee_sfs_seek(fd, 0, SEEK_SET | SEEK_CUR | SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_seek Negative PASSED----------------------");

  /* Positive Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_seek Positive Tests ----------------------");

  memset(data, 0x77, SEEK_SEGMENT_SIZE);

  /* TESTS WITH SEEK_SET */

  /* Write at Beginning */
  if (0 != (ret = qsee_sfs_seek(fd, 0, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (0 != (ret = qsee_sfs_seek(fd, 0, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* Write at Middle of Segments */
  if (SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, SEEK_SEGMENT_SIZE / 2, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, SEEK_SEGMENT_SIZE / 2, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  if (3 * SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, 3 * SEEK_SEGMENT_SIZE / 2, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (3 * SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, 3 * SEEK_SEGMENT_SIZE / 2, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* Write at End */
  if (SEEK_FILE_SIZE - SEEK_WRITE_SIZE != (ret = qsee_sfs_seek(fd, SEEK_FILE_SIZE - SEEK_WRITE_SIZE, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (SEEK_FILE_SIZE - SEEK_WRITE_SIZE != (ret = qsee_sfs_seek(fd, SEEK_FILE_SIZE - SEEK_WRITE_SIZE, SEEK_SET)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* TESTS WITH SEEK_CUR */

  /* Write at Beginning */
  if (0 != (ret = qsee_sfs_seek(fd, -1 * SEEK_FILE_SIZE, SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (0 != (ret = qsee_sfs_seek(fd, -1 * SEEK_WRITE_SIZE, SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* Write at Middle of Segments */
  if (SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, SEEK_SEGMENT_SIZE / 2 - SEEK_WRITE_SIZE, SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, -1 * SEEK_WRITE_SIZE, SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  if (3 * SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, SEEK_SEGMENT_SIZE - SEEK_WRITE_SIZE, SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (3 * SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, -1 * SEEK_WRITE_SIZE, SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* Write at End */
  if (SEEK_FILE_SIZE - SEEK_WRITE_SIZE != (ret = qsee_sfs_seek(fd, SEEK_SEGMENT_SIZE / 2 - (2 * SEEK_WRITE_SIZE), SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (SEEK_FILE_SIZE - SEEK_WRITE_SIZE != (ret = qsee_sfs_seek(fd, -1 * SEEK_WRITE_SIZE, SEEK_CUR)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* TESTS WITH SEEK_END */

  /* Write at Beginning */
  if (0 != (ret = qsee_sfs_seek(fd, -1 * SEEK_FILE_SIZE, SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (0 != (ret = qsee_sfs_seek(fd, -1 * SEEK_FILE_SIZE, SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* Write at Middle of Segments */
  if (SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, -1 * (3 * SEEK_SEGMENT_SIZE / 2), SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, -1 * (3 * SEEK_SEGMENT_SIZE / 2), SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  if (3 * SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, -1 * (SEEK_SEGMENT_SIZE / 2), SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (3 * SEEK_SEGMENT_SIZE / 2 != (ret = qsee_sfs_seek(fd, -1 * (SEEK_SEGMENT_SIZE / 2), SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  /* Write at End */
  if (SEEK_FILE_SIZE - SEEK_WRITE_SIZE != (ret = qsee_sfs_seek(fd, -1 * SEEK_WRITE_SIZE, SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_write(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Verify */
  if (SEEK_FILE_SIZE - SEEK_WRITE_SIZE != (ret = qsee_sfs_seek(fd, -1 * SEEK_WRITE_SIZE, SEEK_END)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (SEEK_WRITE_SIZE != (ret = qsee_sfs_read(fd, data, SEEK_WRITE_SIZE)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < SEEK_WRITE_SIZE; i++)
  {
    if (((uint8*)data)[i] != 0x77)
    {
      GPLOG_ERROR(((uint8*)data)[i]);
      ret = -1;
      goto Exit;
    }
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Clean Up File */
  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_seek Positive PASSED----------------------");

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_seek PASSED ---------------------------------");

Exit:
  if (NULL != data)
    qsee_free(data);

  if (0 != fd)
    qsee_sfs_close(fd);

  qsee_sfs_rm(FILE_NAME);

  return ret;
}

int smplap_sfs_unit_rm(void)
{
  int i = 0, ret = 0, fd = 0;
  void* data = NULL;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_rm TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);

  /* Negative Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_rm Negative Tests ----------------------");

  /* Remove a File Which is Not Present */
  if (E_SUCCESS == (ret = qsee_sfs_rm("/persist/data/im/not/there")))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_rm Negative PASSED----------------------");

  /* Positive Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_rm Positive Tests ----------------------");

  /* Create the File to Operate On */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_close(fd);
  fd = 0;

  /* Clean Up File */
  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_rm Positive PASSED----------------------");

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_rm PASSED ---------------------------------");

Exit:
  if (NULL != data)
    qsee_free(data);

  qsee_sfs_rm(FILE_NAME);

  return ret;
}

int smplap_sfs_unit_file_list(void)
{
  int i = 0, j = 0, ret = 0, fd = 0;
  void* data = NULL;
  uint32_t size = 0;
  sfs_file_entry* list = NULL;
  char fileNames[5][6] = { { 'f', 'i', 'l', 'e', '1', '\0' }, 
                           { 'f', 'i', 'l', 'e', '2', '\0' },
                           { 'f', 'i', 'l', 'e', '3', '\0' },
                           { 'f', 'i', 'l', 'e', '4', '\0' },
                           { 'f', 'i', 'l', 'e', '5', '\0' } };

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_file_list TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);
  for (i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
    qsee_sfs_rm(fileNames[i]);

  /* Negative Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_file_list Negative Tests ----------------------");

  /* Null Inputs */
  if (E_SUCCESS == (ret = qsee_sfs_get_file_list(NULL, &size)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }
  if (E_SUCCESS == (ret = qsee_sfs_get_file_list(&list, NULL)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  qsee_sfs_clean_file_list(NULL);

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_file_list Negative PASSED----------------------");

  /* Positive Test Cases */
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_file_list Positive Tests ----------------------");

  if (E_SUCCESS != (ret = qsee_sfs_get_file_list(&list, &size)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (0 != size)
  {
    GPLOG_ERROR(size);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
  {
    /* Create a New File to Check in the List */
    if (0 == (fd = qsee_sfs_open(fileNames[i], O_CREAT | O_RDWR)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }

    qsee_sfs_close(fd);
    fd = 0;

    /* Get and Verify List */
    if (E_SUCCESS != (ret = qsee_sfs_get_file_list(&list, &size)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    if (i + 1 != size)
    {
      GPLOG_ERROR(size);
      ret = -1;
      goto Exit;
    }

    for (j = 0; j < i + 1; j++)
    {
      if (0 != strncmp(fileNames[j], list[j].file_name, sizeof(fileNames[i])))
      {
        GPLOG_ERROR(0);
        ret = -1;
        goto Exit;
      }
      if (0 != list[j].file_size)
      {
        GPLOG_ERROR(list[j].file_size);
        ret = -1;
        goto Exit;
      }
    }

    qsee_sfs_clean_file_list(list);

  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_file_list Positive PASSED----------------------");

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_unit_file_list PASSED ---------------------------------");

Exit:
  if (NULL != data)
    qsee_free(data);

  for (i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
    qsee_sfs_rm(fileNames[i]);

  return ret;
}

#define TEST_OBJ_SIZE (2*1024)

#pragma pack(push, 1)
typedef struct
{
  uint8_t data[TEST_OBJ_SIZE];
  uint8_t iv[GPCRYPTO_IV_SIZE];
  uint8_t hmac[GPCRYPTO_HMAC_SIZE];
} /*__attribute__((packed))*/ dataObj;
#pragma pack(pop)

#define BASIC_NUM_OF_WRITES 4

int smplap_sfs_basic_use_cases(void)
{
  int i = 0, j = 0, k = 0, ret = 0, fd = 0;
  void* data = NULL;
  dataObj* obj1 = NULL;
  dataObj* obj2 = NULL;
  uint32_t size = 0, fileSize = 0;
  sfs_file_entry* list = NULL;
  char fileNames[5][6] = { { 'f', 'i', 'l', 'e', '1', '\0' },
                           { 'f', 'i', 'l', 'e', '2', '\0' },
                           { 'f', 'i', 'l', 'e', '3', '\0' },
                           { 'f', 'i', 'l', 'e', '4', '\0' },
                           { 'f', 'i', 'l', 'e', '5', '\0' } };

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_basic_use_cases TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);
  for (i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
    qsee_sfs_rm(fileNames[i]);

  if (NULL == (obj1 = qsee_malloc(sizeof(dataObj))))
  {
    GPLOG_ERROR(obj1);
    ret = -1;
    goto Exit;
  }
  if (NULL == (obj2 = qsee_malloc(sizeof(dataObj))))
  {
    GPLOG_ERROR(obj2);
    ret = -1;
    goto Exit;
  }

  memset(obj1->data, 0x01, sizeof(obj1->data));
  memset(obj1->iv,   0x02, sizeof(obj1->iv));
  memset(obj1->hmac, 0x03, sizeof(obj1->hmac));

  memset(obj2, 0, sizeof(dataObj));

  /* USE CASE 1 (Marshall and Unmarshall Structs) */

  /* Create and Write the File */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  if (sizeof(dataObj) != (ret = qsee_sfs_write(fd, (char*)obj1, sizeof(dataObj))))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (E_SUCCESS != (ret = qsee_sfs_close(fd)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  /* Now Reopen and Read in Data */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_RDONLY)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  if (sizeof(dataObj) != (ret = qsee_sfs_read(fd, (char*)obj2, sizeof(dataObj))))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (E_SUCCESS != (ret = qsee_sfs_close(fd)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (0 != memcmp(obj1, obj2, sizeof(dataObj)))
  {
    GPLOG_ERROR(0);
    ret = -1;
    goto Exit;
  }

  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  qsee_free(obj1);
  obj1 = NULL;
  qsee_free(obj2);
  obj2 = NULL;

  /* USE CASE 2 (Append to File) */

  if (NULL == (data = qsee_malloc(FILE_SIZE / BASIC_NUM_OF_WRITES)))
  {
    GPLOG_ERROR(obj1);
    ret = -1;
    goto Exit;
  }

  memset(data, 0x99, FILE_SIZE / BASIC_NUM_OF_WRITES);

  for (i = 0; i < BASIC_NUM_OF_WRITES; i++)
  {
    /* Append to the File */
    if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR | O_APPEND)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }

    if (FILE_SIZE / BASIC_NUM_OF_WRITES != (ret = qsee_sfs_write(fd, data, FILE_SIZE / BASIC_NUM_OF_WRITES)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    if (E_SUCCESS != (ret = qsee_sfs_close(fd)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
  }

  /* Read and Verify */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_RDONLY)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < BASIC_NUM_OF_WRITES; i++)
  {
    if (FILE_SIZE / BASIC_NUM_OF_WRITES != (ret = qsee_sfs_read(fd, data, FILE_SIZE / BASIC_NUM_OF_WRITES)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
    for (j = 0; j < FILE_SIZE / BASIC_NUM_OF_WRITES; j++)
    {
      if (0x99 != ((uint8*)data)[j])
      {
        GPLOG_ERROR(((uint8*)data)[j]);
        ret = -1;
        goto Exit;
      }
    }
  }

  qsee_sfs_close(fd);
  fd = 0;

  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }


  /* USE CASE 3 (Create Several File and Use Enumeration and GetSize to Access Them) */

  memset(data, 0x22, FILE_SIZE / BASIC_NUM_OF_WRITES);

  for (i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
  {
    /* Create a New File to Check in the List */
    if (0 == (fd = qsee_sfs_open(fileNames[i], O_CREAT | O_RDWR)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }

    for (j = 0; j < i + 1; j++)
    {
      if (FILE_SIZE / BASIC_NUM_OF_WRITES != (ret = qsee_sfs_write(fd, data, FILE_SIZE / BASIC_NUM_OF_WRITES)))
      {
        GPLOG_ERROR(ret);
        ret = -1;
        goto Exit;
      }
    }

    qsee_sfs_close(fd);
    fd = 0;
  }

  /* Get and Verify List */
  if (E_SUCCESS != (ret = qsee_sfs_get_file_list(&list, &size)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (sizeof(fileNames) / sizeof(fileNames[0]) != size)
  {
    GPLOG_ERROR(size);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < size; i++)
  {
    if (0 != strncmp(fileNames[i], list[i].file_name, sizeof(fileNames[i])))
    {
      GPLOG_ERROR(0);
      ret = -1;
      goto Exit;
    }

    if (0 == (fd = qsee_sfs_open(list[i].file_name, O_RDONLY)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }

    if (E_SUCCESS != (ret = qsee_sfs_getSize(fd, &fileSize)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    if (fileSize != list[i].file_size)
    {
      GPLOG_ERROR(fileSize);
      GPLOG_ERROR(list[i].file_size);
      ret = -1;
      goto Exit;
    }

    for (j = 0; j < fileSize / (FILE_SIZE / BASIC_NUM_OF_WRITES); j++)
    {
      if (FILE_SIZE / BASIC_NUM_OF_WRITES != (ret = qsee_sfs_read(fd, data, FILE_SIZE / BASIC_NUM_OF_WRITES)))
      {
        GPLOG_ERROR(ret);
        ret = -1;
        goto Exit;
      }

      for (k = 0; k < FILE_SIZE / BASIC_NUM_OF_WRITES; k++)
      {
        if (0x22 != ((uint8*)data)[k])
        {
          GPLOG_ERROR(((uint8*)data)[k]);
          ret = -1;
          goto Exit;
        }
      }
    }

    qsee_sfs_close(fd);
    fd = 0;
  }

  qsee_sfs_clean_file_list(list);

  ret = 0;

  qsee_free(data);
  data = NULL;

  /* USE CASE 4 (Create a File by Dictating call flow via qsee_sfs_error Return Value) */

  if (NULL == (obj1 = qsee_malloc(sizeof(dataObj))))
  {
    GPLOG_ERROR(obj1);
    ret = -1;
    goto Exit;
  }

  memset(obj1->data, 0x01, sizeof(obj1->data));
  memset(obj1->iv, 0x02, sizeof(obj1->iv));
  memset(obj1->hmac, 0x03, sizeof(obj1->hmac));

  /* Try to Open the File */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_RDWR)))
  {
    if (SFS_NO_FILE == (ret = qsee_sfs_error(fd)))
    {
      /* Create the File */
      if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
      {
        GPLOG_ERROR(fd);
        ret = -1;
        goto Exit;
      }
    }
    else
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }
  }

  if (sizeof(dataObj) != (ret = qsee_sfs_write(fd, (char*)obj1, sizeof(dataObj))))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (E_SUCCESS != (ret = qsee_sfs_close(fd)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  qsee_free(obj1);
  obj1 = NULL;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_basic_use_cases PASSED ---------------------------------");

Exit:

  if (NULL != obj1)
    qsee_free(obj1);
  if (NULL != obj2)
    qsee_free(obj2);
  if (NULL != data)
    qsee_free(data);

  if (0 != fd)
    qsee_sfs_close(fd);

  qsee_sfs_rm(FILE_NAME);
  for (i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
    qsee_sfs_rm(fileNames[i]);

  return ret;
}

#define ITERS 10
#define PERF_FILE_SIZE (12 * 1024)

int smplap_sfs_perf_test(void)
{
  unsigned long long start = 0;
  unsigned long long stop = 0;
  unsigned long long total = 0;

  int i = 0, j = 0, ret = 0, fd = 0;
  uint32_t size = 0;
  void* data = NULL;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_perf_test TESTS ---------------------------------");

  /* Make sure to remove any persistent file prior to tests */
  qsee_sfs_rm(FILE_NAME);

  if (NULL == (data = qsee_malloc(PERF_FILE_SIZE)))
  {
    GPLOG_ERROR(data);
    ret = -1;
    goto Exit;
  }

  /* Create the File to Operate On */
  if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
  {
    GPLOG_ERROR(fd);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < ITERS; i++)
  {
    start = qsee_get_uptime();
    if (PERF_FILE_SIZE != (ret = qsee_sfs_write(fd, data, PERF_FILE_SIZE)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
    stop = qsee_get_uptime();
    total += stop - start;

    if (0 != qsee_sfs_seek(fd, 0, SEEK_SET))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  --> Write: avg=%llu ms", total / ITERS);
  total = 0;

  for (i = 0; i < ITERS; i++)
  {
    start = qsee_get_uptime();
    if (PERF_FILE_SIZE != (ret = qsee_sfs_read(fd, data, PERF_FILE_SIZE)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
    stop = qsee_get_uptime();
    total += stop - start;

    if (0 != qsee_sfs_seek(fd, 0, SEEK_SET))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  --> Read: avg=%llu ms", total / ITERS);
  total = 0;

  for (i = 0; i < ITERS; i++)
  {
    if (PERF_FILE_SIZE != (ret = qsee_sfs_read(fd, data, PERF_FILE_SIZE)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }

    start = qsee_get_uptime();
    if (0 != qsee_sfs_seek(fd, 0, SEEK_SET))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
    stop = qsee_get_uptime();
    total += stop - start;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  --> Seek: avg=%llu ms", total / ITERS);
  total = 0;

  for (i = 0; i < ITERS; i++)
  {
    start = qsee_get_uptime();
    if (E_SUCCESS != qsee_sfs_getSize(fd, &size))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
    stop = qsee_get_uptime();
    total += stop - start;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  --> GetSize: avg=%llu ms", total / ITERS);
  total = 0;

  qsee_sfs_close(fd);
  fd = 0;

  for (i = 0; i < ITERS; i++)
  {
    start = qsee_get_uptime();
    if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }
    stop = qsee_get_uptime();
    total += stop - start;

    qsee_sfs_close(fd);
    fd = 0;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  --> Open: avg=%llu ms", total / ITERS);
  total = 0;

  if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
  {
    GPLOG_ERROR(ret);
    ret = -1;
    goto Exit;
  }

  for (i = 0; i < ITERS; i++)
  {
    start = qsee_get_uptime();
    if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }
    stop = qsee_get_uptime();
    total += stop - start;

    qsee_sfs_close(fd);
    fd = 0;

    if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  --> Create: avg=%llu ms", total / ITERS);
  total = 0;

  for (i = 0; i < ITERS; i++)
  {
    if (0 == (fd = qsee_sfs_open(FILE_NAME, O_CREAT | O_RDWR)))
    {
      GPLOG_ERROR(fd);
      ret = -1;
      goto Exit;
    }

    qsee_sfs_close(fd);
    fd = 0;

    start = qsee_get_uptime();
    if (E_SUCCESS != (ret = qsee_sfs_rm(FILE_NAME)))
    {
      GPLOG_ERROR(ret);
      ret = -1;
      goto Exit;
    }
    stop = qsee_get_uptime();
    total += stop - start;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  --> Remove: avg=%llu ms", total / ITERS);
  total = 0;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- smplap_sfs_perf_test PASSED ---------------------------------");

Exit:

  if (NULL != data)
    qsee_free(data);

  if (0 != fd)
    qsee_sfs_close(fd);

  qsee_sfs_rm(FILE_NAME);

  return E_SUCCESS;
}

int smplap_sfs_unit_test_suite(void)
{
  if (E_SUCCESS != smplap_sfs_unit_open())
  {
    return E_FAILURE;
  }
  if (E_SUCCESS != smplap_sfs_unit_rm())
  {
    return E_FAILURE;
  }
  if (E_SUCCESS != smplap_sfs_unit_read_write())
  {
    return E_FAILURE;
  }
  if (E_SUCCESS != smplap_sfs_unit_get_size())
  {
    return E_FAILURE;
  }
  if (E_SUCCESS != smplap_sfs_unit_seek())
  {
    return E_FAILURE;
  }
  if (E_SUCCESS != smplap_sfs_unit_file_list())
  {
    return E_FAILURE;
  }
  if (E_SUCCESS != smplap_sfs_basic_use_cases())
  {
    return E_FAILURE;
  }
  if (E_SUCCESS != smplap_sfs_perf_test())
  {
    return E_FAILURE;
  }

  return E_SUCCESS;
}

#define ETEST_DATA "dummy data for sfs test suite"
#define ETEST_DATA2 ". kdfjg sodj sdk gasdoi"

#define TZ_CM_MAX_NAME_LEN          256

int tz_app_sfs(void)
{
  int ret = 0;
  int fd = -1;
  uint8 * buf = NULL;
  uint32 len = 0;
  uint32 num_bytes = 0;
  char etest_sfs_dir[] = "/data/misc/qsee/sampleapp/sfs";
  char etest_sfs_file[] = "/data/misc/qsee/sampleapp/sfs/file.dat";
  char etest_sfs_file2[] = "/data/misc/qsee/sampleapp/sfs/file2.dat";
  unsigned long long time_1;
  unsigned long long time_2;
  sfs_file_entry* file_list = NULL;
  uint32 file_size = 0;
  bool rollback = false;

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "-- SFS UNIT TESTS ---------------------------------");
  
  qsee_sfs_rm(etest_sfs_file);
  qsee_sfs_rm(etest_sfs_file2);

  do
  {
    len = (strlen(ETEST_DATA) + strlen(ETEST_DATA2) + 1);
    buf = (uint8*)qsee_malloc(sizeof(int8)*  len);
    if (buf == NULL)
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Failed to create buffer! qsee_malloc() failed!");
      ret = -1;
      break;
    }
    buf[len - 1] = '\0';

    ret = qsee_sfs_is_anti_rollback_enabled(&rollback);
    if (ret != E_SUCCESS)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_is_anti_rollback_enabled() FAILED! errno = %d", ret);
      break;
    }
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "Is Anti-Rollback Enabled = %d", rollback);

    /* do not check return value becuase qsee_sfs_mkdir is deprecated */
    ret = qsee_sfs_mkdir(etest_sfs_dir);

    time_1 = qsee_get_uptime();
    fd = qsee_sfs_open(etest_sfs_file, O_RDWR | O_CREAT | O_TRUNC);
    if (fd == 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_open( O_RDWR | O_CREAT | O_TRUNC ) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_open time used %ld ", time_2 - time_1);

    ret = qsee_sfs_write(fd, ETEST_DATA, strlen(ETEST_DATA));
    if (ret != strlen(ETEST_DATA))
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_write() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_write(%s) PASSED", ETEST_DATA);
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_write time used %ld ", time_1 - time_2);

    ret = qsee_sfs_read(fd, (char *)(uintnt)buf, 1);
    if (ret != 0)
    {
      //ret = qsee_sfs_error(fd);
      //if (ret == SFS_EOF)
      //  QSEE_LOG(QSEE_LOG_MSG_ERROR, "SFS_EOF test PASSED errno = %d", ret);
      //else
      //{
      //  QSEE_LOG(QSEE_LOG_MSG_ERROR, "SFS_EOF test FAILED errno = %d", ret);
      //  break;
      //}
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_read time used %ld ", time_2 - time_1);

    ret = qsee_sfs_close(fd);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_close() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_close() PASSED");
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_close time used %ld ", time_1 - time_2);

    ret = qsee_sfs_get_file_list(&file_list, &file_size);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_get_file_list() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      /* Verify info in list */
      if (file_size != 1)
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_get_file_list() FAILED! %d != 1 errno = %d", file_size, ret);
        ret = 1;
        break;
      }
      if (strcmp(file_list->file_name, etest_sfs_file))
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_get_file_list() FAILED! %s != %s errno = %d",
          file_list->file_name, etest_sfs_file, ret);
        ret = 1;
        break;
      }
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_get_file_list() PASSED");
    }
    qsee_sfs_clean_file_list(file_list);

    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_get_file_list used %ld ", time_2 - time_1);

    fd = qsee_sfs_open(etest_sfs_file, O_RDWR | O_CREAT | O_APPEND);
    if (fd == 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_open( O_RDWR | O_CREAT | O_APPEND ) PASSED");
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_open time used %ld ", time_1 - time_2);

    ret = qsee_sfs_write(fd, ETEST_DATA2, strlen(ETEST_DATA2));
    if (ret != strlen(ETEST_DATA2))
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_write() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_write(%s) PASSED", ETEST_DATA2);
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_write time used %ld ", time_2 - time_1);

    ret = qsee_sfs_close(fd);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_close() FAILED! errno = %d ", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_close() PASSED");
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_close time used %ld ", time_1 - time_2);

    fd = qsee_sfs_open(etest_sfs_file, O_RDONLY);
    if (fd == 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open( O_RDONLY ) FAILED! errno = %d ", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_open() PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_open time used %ld ", time_2 - time_1);

    ret = qsee_sfs_getSize(fd, &num_bytes);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_getSize() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      if (num_bytes != len - 1)
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_getSize %ld != write %ld", num_bytes, len - 1);
      }
      else
      {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_getSize PASSED");
      }
    }

    ret = qsee_sfs_read(fd, (char*)(uintnt)buf, len - 1);
    if (ret != len - 1)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_read() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_read(%s) PASSED", buf);
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_read time used %ld ", time_1 - time_2);

    ret = qsee_sfs_close(fd);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_close() FAILED! errno = %d ", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_close() PASSED");
    }

    fd = 0;

    time_1 = qsee_get_uptime();
    ret = qsee_sfs_rm(etest_sfs_file);
    if (ret != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_rm(etest_sfs_file) FAILED! returned = %ld", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_rm(etest_sfs_file) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_rm time used %ld ", time_2 - time_1);

    fd = qsee_sfs_open(etest_sfs_file2, O_RDONLY);
    if (fd == 0)
    {
      //ret = qsee_sfs_error(fd);
      //if (ret == SFS_NO_FILE)
      //{
      //  QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open(%s,O_RDONLY) PASSED errno = %d", etest_sfs_file2, ret);
      //}
      //else
      //{
      //  QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open(%s,O_RDONLY) FAILED! errno = %d", etest_sfs_file2, ret);
      //  break;
      //}
    }


    fd = qsee_sfs_open(etest_sfs_file2, O_RDWR | O_CREAT | O_TRUNC);
    if (fd == 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open() FAILED! errno = ret", fd);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_open( O_RDWR | O_CREAT | O_TRUNC ) PASSED");
    }

    ret = qsee_sfs_getSize(fd, &num_bytes);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_getSize() FAILED! errno = %d ", ret);
    }
    else
    {
      if (num_bytes != 0)
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_getSize %ld != 0", num_bytes);
      }
      else
      {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_getSize PASSED");
      }
    }

    ret = qsee_sfs_write(fd, ETEST_DATA, strlen(ETEST_DATA));
    if (ret != strlen(ETEST_DATA))
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_write() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_write(%s) PASSED", ETEST_DATA);
    }

    ret = qsee_sfs_getSize(fd, &num_bytes);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_getSize() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      if (num_bytes != strlen(ETEST_DATA))
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_getSize %ld != %ld", num_bytes, strlen(ETEST_DATA));
      }
      else
      {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_getSize PASSED");
      }
    }

    ret = qsee_sfs_seek(fd, 0, SEEK_SET);
    if (ret == -1)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_seek SEEK_SET error = %d", ret);
      break;
    }

    memset((void *)(uintnt)buf, 0, len);
    ret = qsee_sfs_read(fd, (char *)(uintnt)buf, 1);
    if (ret != 1)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_read error errno = %d", ret);
      break;
    }

    //Compare seek results 
    ret = memcmp(buf, ETEST_DATA, 1);
    if (ret)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_seek read error %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_seek read PASSED");
    }

    time_1 = qsee_get_uptime();
    ret = qsee_sfs_seek(fd, 0, SEEK_END);
    if (ret == -1)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_seek SEEK_END errno = %d", ret);
      break;
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_seek time used %ld ", time_2 - time_1);

    ret = qsee_sfs_seek(fd, 0, SEEK_CUR);
    if (ret == -1)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_seek SEEK_CUR errno = %d", ret);
      break;
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_seek time used %ld ", time_1 - time_2);

    if (ret != strlen(ETEST_DATA))
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_seek Tell overall file size compare error %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_seek Tell overall file size passed");
    }


    ret = qsee_sfs_close(fd);
    if (ret != 0)
    {
      ret = qsee_sfs_error(fd);
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_close() FAILED! errno = %d", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_close() PASSED");
    }

    fd = 0;

    time_1 = qsee_get_uptime();
    ret = qsee_sfs_rm(etest_sfs_file2);
    if (ret != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_rm(etest_sfs_file2) FAILED! returned = %ld", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_rm(etest_sfs_file2) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_rm time used %ld ", time_2 - time_1);

    /* do not check return value becuase qsee_sfs_mkdir is deprecated */
    ret = qsee_sfs_rmdir(etest_sfs_dir);

  } while (0);

  /* Clean up */
  if (ret != 0 && fd != 0)
  {
    if (qsee_sfs_close(fd))
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "Clean Up FAILED: Heap Memory Leaked", ret);
    }
  }
  if (buf != NULL)
  {
    qsee_free(buf);
    buf = NULL;
  }

  return ret;
}


int tz_app_counter(void)
{
  uint8 id_1[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, \
    17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
  uint8 id_2[32]={16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16, \
    17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
  uint8 id_3[32]={3,3,3,3,16,16,16,16,16,16,16,16,16,16,16,16, \
    17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
  int stat;
  uint64_t value;
  unsigned long long time_1;
  unsigned long long time_2;

  do
  {
    time_1 = qsee_get_uptime();
    stat = qsee_create_counter(id_1, 0);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_create_counter(id_1, 0) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_create_counter(id_1, 0) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_create_counter time used %ld ",  time_2-time_1);

    value = 0;
    stat = qsee_query_counter(id_1, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_1) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_1, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1) );
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_query_counter time used %ld ",  time_1-time_2);

    stat = qsee_increment_counter(id_1);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_increment_counter(id_1) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_increment_counter(id_1) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_increment_counter time used %ld ",  time_2-time_1);

    value = 0;
    stat = qsee_query_counter(id_1, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_1) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_1, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1));
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_query_counter time used %ld ",  time_1-time_2);

    stat = qsee_create_counter(id_2, 0xFFFFFFFF);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_create_counter(id_2, 0xFFFFFFFF) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_create_counter(id_2, 0xFFFFFFFF) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_create_counter time used %ld ",  time_2-time_1);

    value = 0;
    stat = qsee_query_counter(id_2, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_2, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1));
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_query_counter time used %ld ",  time_1-time_2);

    stat = qsee_increment_counter(id_2);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_increment_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_increment_counter(id_2) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_increment_counter time used %ld ",  time_2-time_1);

    stat = qsee_increment_counter(id_2);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_increment_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_increment_counter(id_2) PASSED");
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_increment_counter time used %ld ",  time_1-time_2);

    value = 0;
    stat = qsee_query_counter(id_2, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_2, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1));
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_query_counter time used %ld ",  time_2-time_1);

    stat = qsee_create_counter(id_2, 1);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_create_counter(id_2) PASSED negative returned = %ld", stat);
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_create_counter(id_2) FAILED negative create");
      break;
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_create_counter time used %ld ",  time_1-time_2);

    value = 0;
    stat = qsee_query_counter(id_2, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_2, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1));
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_query_counter time used %ld ",  time_2-time_1);

    stat = qsee_increment_counter(id_2);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_increment_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_increment_counter(id_2) PASSED");
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_increment_counter time used %ld ",  time_1-time_2);

    value = 0;
    stat = qsee_query_counter(id_2, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_2, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1));
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_query_counter time used %ld ",  time_2-time_1);

    memset(&value, 0xFF, sizeof(uint64_t));
    stat = qsee_create_counter(id_3, value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_create_counter(id_3, 0xFFFFFFFFFFFFFFFF) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_create_counter(id_3, 0xFFFFFFFFFFFFFFFF) PASSED");
    }

    value = 0;
    stat = qsee_query_counter(id_3, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_3) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_3, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1));
    }

    stat = qsee_increment_counter(id_3);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_increment_counter(id_3) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_increment_counter(id_3) PASSED");
    }

    value = 0;
    stat = qsee_query_counter(id_3, &value);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_query_counter(id_3) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_query_counter(id_3, value[0]=0x%x, value[1]=0x%x)", *((uint32 *)(uintnt)(&value)), *((uint32 *)(uintnt)(&value)+1));
    }

    stat = qsee_delete_counter(id_1);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_delete_counter(id_1) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_delete_counter(id_1) PASSED");
    }
    time_1 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_delete_counter time used %ld ",  time_1-time_2);

    stat = qsee_delete_counter(id_2);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_delete_counter(id_2) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_delete_counter(id_2) PASSED");
    }
    time_2 = qsee_get_uptime();
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_delete_counter time used %ld ",  time_2-time_1);

    stat = qsee_delete_counter(id_3);
    if( stat != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_delete_counter(id_3) FAILED! returned = %ld", stat);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, " qsee_delete_counter(id_3) PASSED");
    }

  }while(0);

  return stat;
}

/**
 *  Test cases for fs deamon
 */
int tz_app_fs(void) {
	int ret = 0;
	int fd = -1;
	int nfd = -1;
	uint8 * buf = NULL;
	uint32 len = 0;
	char etest_fs_dir[] = "/data/misc/qsee/sampleapp/fs";
	char etest_fs_file[] = "/data/misc/qsee/sampleapp/fs/file.dat";
	char etest_fs_file_link[] = "/data/misc/qsee/sampleapp/fs/fileLink.dat";
	char etest_fs_file_linkat[] = "/data/misc/qsee/sampleapp/fs/fileLinkat.dat";
	char etest_fs_file2[] = "/data/misc/qsee/sampleapp/fs/file2Create.dat";
	//char etest_fs_fileopenat[] = "/data/misc/qsee/sampleapp/fs/fileOpenat.dat";
	 unsigned long long time_1;
	 unsigned long long time_2;

	do {
		len = (strlen(ETEST_DATA) + strlen(ETEST_DATA2) + 1);
		buf = (uint8*) qsee_malloc(sizeof(int8) * len);
		if (buf == NULL) {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG,
					"Failed to create buffer! qsee_malloc() failed!");
			ret = -1;
			break;
		}
		buf[len - 1] = '\0';

		ret = testdir(etest_fs_dir);
		if (ret == 0) {
//remove
			ret = remove(etest_fs_dir);
			if (ret == 0) {
				QSEE_LOG(QSEE_LOG_MSG_DEBUG,
						"file system remove( O_RDWR | O_CREAT | O_TRUNC ) PASSED");
			} else {
				QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system remove() falied");
				break;
			}
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system testdir() passed");
			QSEE_LOG(QSEE_LOG_MSG_DEBUG,
					"directory does not exists create one");
		}
		time_1 = qsee_get_uptime();
//create  a new directory
		ret = mkdir(etest_fs_dir, 0755);
		if (ret != 0) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system mkdir() FAILED! errno = %d", ret);
		} else {
			QSEE_LOG(QSEE_LOG_MSG_ERROR, "file system mkdir() PASSED");
		}
//open a new file
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_mkdir time used %ld ",  time_2-time_1);
		fd = open(etest_fs_file, O_RDWR | O_CREAT | O_TRUNC);
		if (fd == -1) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system open() FAILED! errno = %d", fd);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG,
					"file system open( O_RDWR | O_CREAT | O_TRUNC ) PASSED");
		}
		time_1 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_open time used %ld ",  time_1-time_2);
//write a file
		ret = write(fd, ETEST_DATA, strlen(ETEST_DATA));

		if (ret != strlen(ETEST_DATA)) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system write() FAILED! errno = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system write(%s) PASSED",
					ETEST_DATA);
		}
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_ write used %ld ",  time_2-time_1);
//close
		ret = close(fd);
		if (ret != 0) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"   file system close FAILED! returned = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "   fs_close() PASSED");
			fd = -1;
		}
		time_1 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_close used %ld ",  time_1-time_2);
//open
		fd = open(etest_fs_file, O_RDONLY);
		if (fd == -1) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system open() FAILED! errno = %d", fd);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG,
					"file system open( O_RDONLY ) PASSED");
		}
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_open readonly   used %ld ",  time_2-time_1);
//read
		ret = read(fd, (void *) buf, strlen(ETEST_DATA));
		if (ret < 0) {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system read FAILED  %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_ERROR, "file system read PASSED");

		}
		time_1 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_mkdir close used %ld ",  time_1-time_2);
//seek file
		ret = lseek(fd, strlen(ETEST_DATA), SEEK_SET);
		if (ret > 0) {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system seek PASSED  ");
		} else {
			QSEE_LOG(QSEE_LOG_MSG_ERROR, "file system seek FAILED errno = %d",
					ret);
			break;
		}
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_lseek  used %ld ",  time_2-time_1);
//unlink
		ret = unlink(etest_fs_file);
		if (ret != 0) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system unlink FAILED! errno = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system unlink PASSED");
		}
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_unlink  used %ld ",  time_2-time_1);
//open a file for unlinkat
    fd = open(etest_fs_file_linkat, O_RDONLY);
    if (fd == -1) {
      QSEE_LOG(QSEE_LOG_MSG_ERROR,
          "file system open() FAILED! errno = %d", fd);
			break;
		}
		time_1 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file open  used %ld ",  time_1-time_2);
//unlinkat
		ret = unlinkat(fd, etest_fs_file_linkat, 0);
		if (ret != 0) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system unlink FAILED! errno = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system unlinkat PASSED");
		}
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_unlinkat  used %ld ",  time_2-time_1);
//creat
		nfd = creat(etest_fs_file2, O_RDWR | O_CREAT | O_TRUNC);
		if (nfd == -1) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system creat() FAILED! errno = %d", nfd);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG,
					"file system creat(etest_fs_file2, O_RDWR | O_CREAT | O_TRUNC) PASSED");
		}
		time_1 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_create  used %ld ",  time_1-time_2);
//write a file
		ret = write(nfd, ETEST_DATA, strlen(ETEST_DATA));

		if (ret != strlen(ETEST_DATA)) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system write() FAILED! errno = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system write(%s) PASSED",
					ETEST_DATA);
		}
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_write  used %ld ",  time_2-time_1);
//fsync
		ret = fsync(nfd);
		if (ret != 0) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system fsync() FAILED! errno = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system fsync PASSED");
		}
		time_1= qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_fsync  used %ld ",  time_1-time_2);
//fctnl
		ret = fcntl(nfd, F_GETFL, 0);
		if (ret == -1) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system fcntl() FAILED! errno = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system fctnl PASSED");
		}
		time_2 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_fcntl  used %ld ",  time_2-time_1);
//remdir
		ret = rmdir(etest_fs_dir);
		if (ret != 0) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR,
					"file system rmdir() FAILED! errno = %d", ret);
			break;
		} else {
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "file system rmdir PASSED");
		}
		time_1 = qsee_get_uptime();
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_fs_rmdir  used %ld ",  time_1-time_2);

	} while (0);

	/* Clean up */
	if (fd != -1) {
		if (close(fd)) {
			QSEE_LOG(QSEE_LOG_MSG_ERROR, "Clean Up FAILED: Heap Memory Leaked",
					ret);
		}
	}
	if (buf != NULL) {
		qsee_free(buf);
		buf = NULL;
	}

	return ret;
}


#ifdef APP_SFS_L2_TEST
const char config_path[]="/persist/sfs.config";
const char anti_rollback_file[]="anti_rollback_sfs_file";
/* Note sfs.config format, a char must immediately follow data: */
/* write data:b  -> You want to write 100 bytes 'b' to anti_rollback_sfs_file */
/* read data:b  -> You expect to read 100 bytes 'b' out from anti_rollback_sfs_file */


int tz_app_sfs_anti_rollback(void)
{
  int ret = 0;
  int fd = -1;
  fs_stat  stat_info;
  char  *sfs_config_buf = NULL;
  bool   write_file = true;
  char  *data;
  char  *test_buffer = NULL;
  int    len = 100;
  int    fd_sfs = -1;

  /* open, read, close test config file form HLOS file system */
  do
  {
    fd = open(config_path, O_RDONLY);
    if(fd >0)
    {
      /* get the status of the file */
      ret = lstat(config_path, &stat_info);
      if(!ret && stat_info.st_size <250)
      {
        sfs_config_buf = (char *)qsee_malloc(stat_info.st_size);
        if (!sfs_config_buf) 
        {
          QSEE_LOG(QSEE_LOG_MSG_DEBUG,"sfs_config_buf malloc failed");
          break;
        }
        (void)read(fd, (void *)(uintnt)sfs_config_buf, stat_info.st_size);
      }
      else
      {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "/persist/sfs.config size=%d too big, ret=%d",stat_info.st_size,ret);
        break;
      }
      (void)close(fd);
      if(strstr((const char *)(uintnt)sfs_config_buf, "read"))
      {
        write_file = false;
      }
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG,"No tz_app_sfs_anti_rollback test");
      break;
    }


    /* parse write, data, len*/
    data = strstr((const char *)(uintnt)sfs_config_buf, "data:");
    if (!data) 
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG,"data: is not set in /persist/sfs.config");
      break;
    }
    data+=5;
    test_buffer = (char *)qsee_malloc(len);
    if (!test_buffer) 
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG,"test_buffer malloc failed");
      break;
    }


    /* write result */
    if (write_file) 
    {
      memset((void *)(uintnt)test_buffer, *data, len);
      fd_sfs = qsee_sfs_open(anti_rollback_file, O_RDWR | O_CREAT | O_TRUNC );
      if( fd_sfs == 0 )
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open() %s for write FAILED! ",anti_rollback_file );
        break;
      }
      ret = qsee_sfs_write(fd_sfs, test_buffer, len);
      if(ret != len)
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_write() %s FAILED! ",anti_rollback_file );
        break;
      }
      else
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "%d bytes %c is written to %s for sfs anti-rollback test ",len, *data, anti_rollback_file );
        break;
      }
    }
    else    /* read result */
    {
      fd_sfs = qsee_sfs_open(anti_rollback_file, O_RDONLY );
      if( fd_sfs == 0 )
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_open() %s for read FAILED! ",anti_rollback_file );
        break;
      }
      ret = qsee_sfs_read(fd_sfs, test_buffer, len);
      if(ret != len)
      {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_sfs_write() %s FAILED! ",anti_rollback_file );
        break;
      }
      else
      {
        int i;
        char *read_data = test_buffer;
        for(i = 0; i<len; i++)
        {
          if(*read_data != *data)
          {
             QSEE_LOG(QSEE_LOG_MSG_ERROR, "read data %c != %c from %s for sfs anti-rollback test ", *test_buffer, *data,  anti_rollback_file );
             break;
          }
          read_data++;
        }
        if(i == len)
          QSEE_LOG(QSEE_LOG_MSG_ERROR, "%d bytes %c is read from %s for sfs anti-rollback test ",len, *test_buffer, anti_rollback_file );
      }
    }


  }while(0);

  if(fd != -1)
    close(fd);
  if(fd_sfs != -1)
    qsee_sfs_close(fd_sfs);
  if(sfs_config_buf)
    qsee_free(sfs_config_buf);
  if(test_buffer)
    qsee_free(test_buffer);

  return 0;
}

#endif


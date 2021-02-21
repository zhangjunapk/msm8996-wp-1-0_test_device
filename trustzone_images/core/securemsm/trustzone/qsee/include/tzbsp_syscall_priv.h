#ifndef TZBSP_SYSCALL_PRIV_H
#define TZBSP_SYSCALL_PRIV_H

/**
   @file tzbsp_syscall_priv.h
   @brief Provide the private SYSCALL API infrastructure
*/

/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.

      The xxx_mainpage.dox file contains all descriptions that are displayed
      in the output PDF generated using Doxygen and LaTeX. To edit or update
      any of the file/group text in the PDF, edit the xxx_mainpage.dox
      file or contact Tech Pubs.
===========================================================================*/

/*===========================================================================
   Copyright (c) 2010-2012 by Qualcomm Technologies, Incorporated.
   All rights reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsee/include/tzbsp_syscall_priv.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

when       who      what, where, why
--------   ---      ------------------------------------
03/21/12   pre      Initial version.
04/25/14   dp       Removed CPU DCVS and updated GFX DCVS

===========================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "tz_syscall_pub.h"

/** DCVS service. */
#define TZ_SVC_DCVS               13


/*----------------------------------------------------------------------------
                Deprecated Command IDs: Do not reuse
 * -------------------------------------------------------------------------*/
#define TZBSP_GFX_DCVS_RESET_OLD_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_IO_ACCESS, 0x03)

#define TZBSP_GFX_DCVS_UPDATE_OLD_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_IO_ACCESS, 0x04)

#define TZBSP_DCVS_CREATE_GROUP_DEPRECATED_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x1)

#define TZBSP_DCVS_REGISTER_CORE_DEPRECATED_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x2)

#define TZBSP_DCVS_SET_ALG_PARAMS_DEPRECATED_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x3)

#define TZBSP_DCVS_SYSTEM_EVENT_DEPRECATED_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x4)

#define TZBSP_DCVS_INIT_DEPRECATED_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x5)

#define TZBSP_GFX_DCVS_INIT_OLD_ID \
        TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x6)

/**
   @ingroup gfx_dcvs_reset

   API for the graphics team to control the proprietary dynamic clock
   and voltage scaling routine.

   @note1hang Implementation takes place as a TZ kernel service

   @owner_id
     0x00000002

   @command_id
     0x00000D03

   @param_id
     0x00000000

   @return
     \c 0                Always successful.
*/
#define TZBSP_GFX_DCVS_RESET_ID                           \
  TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x07)

#define TZBSP_GFX_DCVS_RESET_ID_PARAM_ID \
  TZ_SYSCALL_CREATE_PARAM_ID_0

/**
   @ingroup gfx_dcvs_update

   API for the graphics team to control the proprietary dynamic clock
   and voltage scaling routine.

   @owner_id
     0x00000002

   @command_id
     0x00000D04

   @param_id
     0x00000001

   @param[in] data: tzbsp_gfx_dcvs_update_data_t structure containing
                    power level, total value, and busy value.
   @param[out] decision_buf: Pointer to an int.
     \c  0               Continue in last performance level.
     \c  1               Increase the performance level.
     \c -1               Decrease the performance level.
   @param[in] decision_buf_size: Size of result buffer.

   @note1hang Implementation takes place as a TZ kernel service

   @return
     \c  E_SUCCESS       If successful.
     \c -E_BAD_ADDRESS   If structure pointer/memory is invalid.
     \c -E_OUT_OF_RANGE  If power levels are out of range
                         or buffer size is too small.
     \c -E_FAILURE       If number of power levels is zero.


*/
#define TZBSP_GFX_DCVS_UPDATE_ID                          \
  TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x08)

#define TZBSP_GFX_DCVS_UPDATE_ID_PARAM_ID \
  TZ_SYSCALL_CREATE_PARAM_ID_1( TZ_SYSCALL_PARAM_TYPE_BUF_RW )

/**
   @ingroup gfx_dcvs_init

   Used to initialize the Graphics DCVS.

   @param[in] data: tzbsp_gfx_dcvs_init_data_t struct containing number
                    of power levels and array of frequency values.
   @param[out] version_buf: A buffer of size unsigned int containing
                    versioning of GFX DCVS TZ implementation.
   @param[in] version_buf_size: Size of version buffer.

   @note1hang Implementation takes place as a TZ kernel service

   @return
     \c 0                If successful.
     \c -E_BAD_ADDRESS   If structure pointer/memory is invalid, or if
                         buffer is not in NS memory.
     \c -E_OUT_OF_RANGE  If power levels are out of range, or if
                         buffer size is too small.
     \c -E_FAILURE       If number of power levels is zero.

   @command_id
     0x00003406

   @com_datatypes
     tz_syscall_req_s \n
     tz_syscall_rsp_s
 */
#define TZBSP_GFX_DCVS_INIT_ID                      \
  TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x09)

#define TZBSP_GFX_DCVS_INIT_ID_PARAM_ID \
  TZ_SYSCALL_CREATE_PARAM_ID_1( TZ_SYSCALL_PARAM_TYPE_BUF_RW )

/**
   @ingroup gfx_dcvs_update

   API for the graphics team to control the proprietary dynamic clock
   and voltage scaling routine.

   @owner_id
     0x00000002

   @command_id
     0x00000D04

   @param_id
     0x00000001

   @param[in] data: tzbsp_gfx_dcvs_update_data_t structure containing
                    power level, total value, and busy value.
   @param[out] decision_buf: Pointer to an int.
     \c  0               Continue in last performance level.
     \c  1               Increase the performance level.
     \c -1               Decrease the performance level.
   @param[in] decision_buf_size: Size of result buffer.

   @note1hang Implementation takes place as a TZ kernel service

   @return
     \c  E_SUCCESS       If successful.
     \c -E_BAD_ADDRESS   If structure pointer/memory is invalid.
     \c -E_OUT_OF_RANGE  If power levels are out of range
                         or buffer size is too small.
     \c -E_FAILURE       If number of power levels is zero.


*/
#define TZBSP_GFX_DCVS_UPDATE_FLATTENED_ID                          \
  TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x0A)

#define TZBSP_GFX_DCVS_UPDATE_FLATTENED_ID_PARAM_ID \
  TZ_SYSCALL_CREATE_PARAM_ID_3( TZ_SYSCALL_PARAM_TYPE_VAL, \
      TZ_SYSCALL_PARAM_TYPE_VAL, TZ_SYSCALL_PARAM_TYPE_VAL )

/**
   @ingroup gfx_dcvs_init

   Used to initialize the Graphics DCVS.

   @param[in] data: tzbsp_gfx_dcvs_init_data_t struct containing number
                    of power levels and array of frequency values.
   @param[out] version_buf: A buffer of size unsigned int containing
                    versioning of GFX DCVS TZ implementation.
   @param[in] version_buf_size: Size of version buffer.

   @note1hang Implementation takes place as a TZ kernel service

   @return
     \c 0                If successful.
     \c -E_BAD_ADDRESS   If structure pointer/memory is invalid, or if
                         buffer is not in NS memory.
     \c -E_OUT_OF_RANGE  If power levels are out of range, or if
                         buffer size is too small.
     \c -E_FAILURE       If number of power levels is zero.

   @command_id
     0x00003406

   @com_datatypes
     tz_syscall_req_s \n
     tz_syscall_rsp_s
 */
#define TZBSP_GFX_DCVS_INIT_WITH_SIZE_ID                      \
  TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_DCVS, 0x0B)

#define TZBSP_GFX_DCVS_INIT_WITH_SIZE_ID_PARAM_ID \
  TZ_SYSCALL_CREATE_PARAM_ID_2( \
      TZ_SYSCALL_PARAM_TYPE_BUF_RW, TZ_SYSCALL_PARAM_TYPE_VAL )

/**
   @ingroup get_ablfv_entry_point

   Get the entry point of the Apps Boot Loader Firmware Volume
   (ABL.FV) image for UEFI. Can only be called once per cold boot.

   @smc_id
     0x02000113

   @param_id
     0x00000000

   @sys_call_params{tz_get_image_entry_point_rsp_s}
     @table{weak__tz__get__image__entry__point__rsp__s}

   @return
     E_SUCCESS on success; an error code otherwise.
*/
#define TZ_GET_IMAGE_ENTRY_POINT_ID                      \
  TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_BOOT, 0x13)

#define TZ_GET_IMAGE_ENTRY_POINT_PARAM_ID \
  TZ_SYSCALL_CREATE_PARAM_ID_0

/*----------------------------------------------------------------------------
 * Graphics DCVS structures
 * -------------------------------------------------------------------------*/

#define TZBSP_GPU_DCVS_NUMPWRLEVELS                 10

/**
   @ingroup gfx_dcvs_update

   Request message structure corresponding to the message ID
   TZBSP_GFX_DCVS_UPDATE_ID.
*/
typedef struct tzbsp_gfx_dcvs_update_data_s
{
  uint32 active_pwrlevel;               /**< Power level index */
  uint32 total;                         /**< Total vector index */
  uint32 inBusy;                        /**< Busy vector index */
} __attribute__ ((packed)) tzbsp_gfx_dcvs_update_data_t;

typedef struct tzbsp_gfx_dcvs_update_req_s
{
  tzbsp_gfx_dcvs_update_data_t* data;     /**< Data structure for update */
} __attribute__ ((packed)) tzbsp_gfx_dcvs_update_req_t;

typedef struct tzbsp_gfx_dcvs_update_rsp_s
{
  int32 decision;                       /**< Result of power level either
                                             increased, decreased, or stayed
                                             the same */
} __attribute__ ((packed)) tzbsp_gfx_dcvs_update_rsp_t;

typedef struct tzbsp_gfx_dcvs_init_data_s
{
  uint32 nlevels;                       /**< Number of levels provided in
                                             freq array */
  uint32 freq[TZBSP_GPU_DCVS_NUMPWRLEVELS]; /**< Array of GPU frequencies */
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_data_t;

typedef struct tzbsp_gfx_dcvs_init_rsp_s
{
  uint32 version;                       /**< Version of TZ GFX DCVS implementation */
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_rsp_t;

/**
   @ingroup gfx_dcvs_init

   Request message structure corresponding to the message ID
   TZBSP_GFX_DCVS_INIT_ID.
*/
typedef struct tzbsp_gfx_dcvs_init_req_s
{
  tzbsp_gfx_dcvs_init_data_t* data;     /**< Data structure for init */
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_req_t;

/**
   @weakgroup weak_tz_get_ablfv_entry_point_rsp_s
@{
*/

typedef struct tz_get_ablfv_entry_point_rsp_s
{
  uint64 e_entry;  /**< Image entry point. */

} __attribute__ ((packed)) tz_get_ablfv_entry_point_rsp_t;

/** @} */ /* end_weakgroup */

#endif /* TZBSP_SYSCALL_PRIV_H */

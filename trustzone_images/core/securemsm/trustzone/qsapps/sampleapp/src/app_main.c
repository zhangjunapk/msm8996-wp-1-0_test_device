/*
@file app_main.c
@brief App main entry point.

*/
/*===========================================================================
Copyright (c) 2011-2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE
  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsapps/sampleapp/src/app_main.c#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 12/23/15   dpk     Added support to pass args to SPI and BLSP modify ownership tests
# 10/28/15   dpk     Added BLSP Modify Ownership test
# 05/06/15   cz      Fixed a KW error
# 01/29/15   kr      Fixed CP COPY API bugs
# 12/19/13   wt      Added commands and logic for Content_Protection_Copy API
===========================================================================*/
#include <comdef.h>
//#include <rt_misc.h>
#include <string.h>
#include <stdint.h>
#include "qsee_log.h"
#include "qsee_services.h"
#include "qsee_timer.h"
#include "qsee_heap.h"
#include "qsee_fuse.h"
#include "qsee_sync.h"
#include "app_content_protection.h"
#include "SecureUILib.h"
#include "SecureUI.h"
#include "qsee_trans_ns_addr.h"
#include "qsee_fs.h"

/* commands supported from sample client */
#define CLIENT_CMD0_GET_VERSION                               0
#define CLIENT_CMD1_BASIC_DATA                                1
#define CLIENT_CMD2_REGISTER_SB_PTR                           2
#define CLIENT_CMD3_RUN_CRYTPO_TEST                           3
#define CLIENT_CMD4_RUN_CRYTPO_PERF                           4
#define CLIENT_CMD5_RUN_SFS_TEST                              5
#define CLIENT_CMD6_RUN_FS_TEST                               6
#define CLIENT_CMD7_RUN_RSA_TEST                              7
#define CLIENT_CMD8_RUN_RSA_PERF_TEST                         8
#define CLIENT_CMD9_RUN_CMNLIB_TEST                           9
#define CLIENT_CMD10_RUN_CORE_TEST                            10
#define CLIENT_CMD11_RUN_SECURECHANNEL_TEST                   11
#define CLIENT_CMD12_RUN_MESSAGE_PASSING                      12
#define CLIENT_CMD13_RUN_MISC_TEST                            13
// 14 and 15 are used for RPMB operations in the sample client.
#define RESERVED_FOR_RPMB_OPS_0                               14
#define RESERVED_FOR_RPMB_OPS_1                               15
#define CLIENT_CMD16_RUN_BUSES_TEST                           16
#define CLIENT_CMD17_RUN_STOR_TEST                            17
#define CLIENT_CMD18_RUN_FUSE_TEST                            18
#define CLIENT_CMD19_RUN_BUSES_SPI_TEST                       19
#define CLIENT_CMD21_RUN_CRYPTO_COPY                          21
#define CLIENT_CMD22_RUN_SECURE_UI_DISPLAY_TEST               22
#define CLIENT_CMD23_RUN_SECURE_UI_TOUCH_TEST                 23
#define CLIENT_CMD25_RUN_SAFE_TEST                            25
#define CLIENT_CMD26_RUN_ABORT_TEST                           26
#define CLIENT_CMD27_RUN_SMPLSERV_TEST                        27
#define CLIENT_CMD29_RUN_BIO_LIB_TEST                         29
#define CLIENT_CMD30_RUN_BULLETIN_BOARD_TEST                  30
#define CLIENT_CMD31_RUN_TLMM_TEST                            31
#define CLIENT_CMD32_RUN_ABORT_TEST                           32
#define CLIENT_CMD33_RUN_SMPLCERT_TEST                        33
#define CLIENT_CMD34_RUN_TRANS_TEST                           34
#define CLIENT_CMD35_RUN_OEM_BUF_TEST                         35
#define CLIENT_CMD36_RUN_INTLOCK_TEST                         36
#define CLIENT_CMD37_REG_SHARED_BUFS                          37
#define CLIENT_CMD38_ACCESS_REGION                            38

#define CLIENT_CMD50_RUN_LISTENER_FRAMEWORK_TEST              50
#define CLIENT_CMD51_RUN_VFP_TEST                             51
#define CLIENT_CMD52_SPIN_TEST                                52
#define CLIENT_CMD53_RUN_LOG_BITMASK_TEST                     53

#define CLIENT_CMD99_RUN_SFS_PERF_TEST                        99
#define CLIENT_CMD100_RUN_CACHE_TEST                         100
#define CLIENT_CMD101_RUN_SHAREDBUFFER_TEST                  101
#define CLIENT_CMD999_RUN_SMPLSERV_CRASH_TEST                999
#define CLIENT_CMD1000_RUN_BLSP_MODIFY_OWNERSHIP_TEST       1000

#define __2MB__ 0x200000
#define __1MB__ 0x100000
#define __64KB__ 0x10000
#define __32KB__ 0x8000
#define __16KB__ 0x4000
#define __8KB__ 0x2000
#define __4KB__ 0x1000
#define __2KB__ 0x800
#define __1KB__ 0x400

/* Error code: status sent as response to command from sample client*/

#define SUCCESS                                0
#define FAILED                                -1
#define FAIL_REGISTER_SB                      -2
#define FAIL_DEREGISTER_SB                    -3
#define FAIL_PREP_SB_NON_SECURE_READ          -4
#define FAIL_PREP_SB_SECURE_READ              -5
#define FAIL_CMD_BUF_TOO_SMALL_FOR_CMD_ID     -6
#define FAIL_CMD_RSP_BUFS_TOO_SMALL           -7
#define FAIL_SHARED_BUFF_TOO_SMALL            -8
#define FAIL_UNDEFINED_COMMAND                -9

#define SAMPLE_APP_VERSION_MAJOR 0x1
#define SAMPLE_APP_VERSION_MINOR 0x3

#define SHARED_BUF_PATTERN_LEN 16

#define ALIGNED_BUF_MAX_NUM 3

extern int tz_app_crypto_test(uint32 src, uint32 dst, uint32 length);
extern int tz_app_crypto_func_test(void);
extern int tz_app_crypto_perf_test(void);
extern int smplap_sfs_unit_test_suite(void);
extern int smplap_sfs_perf_test(void);
extern int tz_app_sfs(void);
extern int tz_app_fs(void);
extern int tz_app_crypto_rsa_test(void);
extern int run_core_test(void* cmd, uint32 cmdlen, void* rsp, uint32 rsplen, void* data, uint32 len);
extern int run_misc_test(void);
extern int run_securechannel_test(void);
extern int tz_app_cmnlib_test(void);
extern int run_message_passing_test(void);
extern int run_buses_test(void);
extern int run_fuse_test(void);
extern int run_sw_fuse_test(void);
extern int run_stor_test(void);
extern int run_buses_spi_test(uint32 spiDeviceId);
extern int tz_app_counter(void);
extern int security_state_test(void);
extern int run_display_test(void);
extern int run_touch_test(void);
extern int run_smplserv_test(void);
extern int run_smplcert_test(void);
extern int run_bio_lib_tests(void);
extern int run_bulletin_board_tests(void);
extern int run_tlmm_tests(void);
extern int run_abort_test(void);
extern int run_cache_test(void);
extern int run_sharedbuffer_test(void* data, uint32 len);
extern int run_smplserv_crash_test(void);
extern int run_spin_test(void);
extern int run_trans_test(qsee_transm_t tt, uintptr_t va, uintptr_t exp_pa);
extern int run_oem_buf_test(void);
extern int run_intlock_tests(void);
extern int run_blsp_modify_ownership_test(uint32 peripheralId, uint32 subsystemId);
extern int run_log_bitmask_test(void);
/**
* Sample app name
* Modify the app name to your specific app name
*/
/**
@brief
Add any app specific initialization code here
QSEE will call this function after secure app is loaded and
authenticated
*/
void tz_app_init(void)
{
  /*  App specific initialization code*/
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "SAMPLEApp Init ");
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Version: %x.%x", SAMPLE_APP_VERSION_MAJOR, SAMPLE_APP_VERSION_MINOR);

}

/**
@brief
Data structure

@param[in]   cmd_id      Requested command
@param[in]   data        information (could be data or a pointer to the memory that holds the data
@param[in]   len         if data is ptr to some buffer, len indicates length of the buffer
@param[in]   test_buf_size  When running crypto test, this indicates the test packet size
*/

typedef struct send_cmd{
  uint32 cmd_id;
  uintnt data;
  uintnt data2;
  uint32 len;
  uint32 start_pkt;
  uint32 end_pkt;
  uint32 test_buf_size;
} send_cmd_t;

typedef struct send_cmd_rsp{
  uint32 data;
  int32 status;
} send_cmd_rsp_t;

unsigned long long b4 = 0;
unsigned long long after = 0;
unsigned long long time_diff = 0;
unsigned long long average_time_diff = 0;
// This is a floating-point unit test for Trustzone.  This utility
// performs a series of floating-point operations and verifies the
// results of the computations.  It is expected that this unit test
// will run in the context of a larger utility that will verify
// that the TrustZone kernel will save and restore FP register
// context after this unit test runs.

// This utility has been tested using the Android 'qseecom_sample_client'
// utility.  It can be stared by copying the built vfptest app files
// to the appropriate Android directory and then:
// /system/bin/qseecom_sample_client 1 vfptest 1 1


// Returns 0 on success, 1 on failure

static int float_test()
{
  float res = 1.5;
  int final = 0;

  // 32-bit integer pointer to single-precision floating point variable
  uint32 *fp =  (uint32 *)&res;
  int i;

  // These are hex representations of the IEEE single-precision FP
  // values of the expected results of the computation loop.
  // Check to see if the proper floating-point values are computed
  // in the loop
  uint32 expected[] =
  {
    0x3fc00000,     // 1.5f
    0x402dc28f,
    0x408c2546,
    0x40d51e96,
    0x411c8bfe,
    0x41610778,
    0x419f6ccc,
    0x41dfb136,
    0x421bde82
  };

  long long loop;
  uint32 tempExpected = 0;

  for(loop = 0; loop < 1000000 /*500000000*/; loop++)
  {
    res = 1.5;
    for(i = 0; i < 8; i++)
    {
      if (*fp != expected[i])
      {
        final = 1;
        tempExpected = expected[i];
        break;                       // break out the very first time !
      }
      else
        res = res * 1.37 + 0.66;
    }
    if (final > 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Incorrect operation. Val: %08x  Exp: %08x Loop: #%d", *fp, tempExpected, loop);
      break;
    }
  }
  return final;
}

static int double_test(void)
{
  char etest_fs_dir[] = "/data/misc/qsee/sampleapp/fs";
  int ret = 0;
  volatile double val = (double)1000;
  unsigned int loop, pass=0, fail=0;

  for(loop = 0; loop < 10000 ; loop++)
  {
    val /= (double)2;

    /* Check whether /data/misc/qsee/sampleapp/fs exist */
    if (testdir(etest_fs_dir)) {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "directory does not exists create one");
    }

    if (val == (double)1000/(double)2)
    {
      pass++;
      val *= (double)2;
    }
    else
    {
      ret = -1;
      fail++;
      val = (double)1000;
    }
  }

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "loop(%d): pass = %d, fail = %d", loop, pass, fail);
  return ret;
}

void tz_app_cmd_handler(void* cmd, uint32 cmdlen,
void* rsp, uint32 rsplen)
{
  /* Request-response buffers are allocated by non-secure side*/
  /* Add code to process requests and set response (if any)*/
  int retval;
  int  j;
  uint32 i = 0;
  uint32 cmd_id;
  uint32 expected_cmdlen;
  uint32 expected_rpslen;
  unsigned char *ptr;
  struct send_cmd *cmd_ptr = (struct send_cmd *)cmd;
  struct send_cmd_rsp *rsp_ptr = (struct send_cmd_rsp *)rsp;
  uint32 list_test_req = 0;
  uint32 list_test_rsp = 0;


  /*First we check if the response pointer is large enough to support a pass/fail response*/
  if(rsplen < sizeof(send_cmd_rsp_t))
  {
    QSEE_LOG(QSEE_LOG_MSG_FATAL, "Response buffer len insufficient, ERROR OUT");
    return;
  }

  /* sanity check */
  if ((!cmd_ptr) || (!rsp_ptr))
  {
    QSEE_LOG(QSEE_LOG_MSG_FATAL, "Command pointer equals NULL!");
    return;
  }
  /*Determine the command id*/
  /*We check if the command buffer is large enough to support the uint32 read for cmd_id*/
  /*It is assumed that the first member of the command buffer is the cmd_id*/
  if(cmdlen < sizeof(uint32))
  {
    QSEE_LOG(QSEE_LOG_MSG_FATAL, "Command buffer len insufficient for reading cmd_id, ERROR OUT");
      rsp_ptr->status = FAIL_CMD_BUF_TOO_SMALL_FOR_CMD_ID;
    return;
  }
  cmd_id = cmd_ptr->cmd_id;
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "TZ App cmd handler, cmd_id = %d", cmd_id);

  /*Identify which command and response buffers we are using based on command ID*/
  if(cmd_id == CLIENT_CMD21_RUN_CRYPTO_COPY)
  {
    expected_cmdlen = sizeof(tz_sc_copy_req_t);
    expected_rpslen = sizeof(tz_sc_copy_rsp_t);
  }
  else
  {
    expected_cmdlen = sizeof(send_cmd_t);
    expected_rpslen = sizeof(send_cmd_rsp_t);
  }

  /*Validate the command buffer and response buffer are the correct size.
  If not, the the MPU protection and ns_range checks done by QSEE kernel might be insufficient*/
  if(cmdlen < expected_cmdlen || rsplen < expected_rpslen)
  {
    QSEE_LOG(QSEE_LOG_MSG_FATAL, "Cmd/rsp buffer lens insufficient - %x, %x, ERROR OUT", cmdlen, rsplen);
    rsp_ptr->status = FAIL_CMD_RSP_BUFS_TOO_SMALL;
    return;
  }

  if (secUiProcessCmd(cmd,cmdlen,rsp,rsplen)){
    return;
  }

  switch (cmd_id) {

    case CLIENT_CMD0_GET_VERSION :
      /* Return major version of the sample test app*/
      rsp_ptr->data = SAMPLE_APP_VERSION_MAJOR;
      rsp_ptr->status = SUCCESS;
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : get version test");
    break;

    case CLIENT_CMD51_RUN_VFP_TEST :
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Doing VFPTest");
      retval = float_test();
      if (retval){
        rsp_ptr->status=FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : float test");
      }
      else{
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : float test");
      }

      retval = double_test();
      if (retval){
        rsp_ptr->status=FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : double test");
      }
      else{
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : double test");
      }
    break;

    case CLIENT_CMD1_BASIC_DATA :
      /*Modify response by 10 */
      rsp_ptr->data = ((uint32)cmd_ptr->data) * 10;
      QSEE_LOG(QSEE_LOG_MSG_FATAL, "cmd_ptr->data%u", cmd_ptr->data);
      rsp_ptr->status = SUCCESS;
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Basic data test");
    break;

    case CLIENT_CMD2_REGISTER_SB_PTR :
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Begin Register Shared Buffer Test (CMD_ID 2) ****");
      if(cmd_ptr->len < SHARED_BUF_PATTERN_LEN)
      {
        rsp_ptr->status = FAIL_SHARED_BUFF_TOO_SMALL;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED because shared buffer len too small.");
        return;
      }
      ptr = (unsigned char *)(uintnt)(cmd_ptr->data);
      retval = qsee_register_shared_buffer(ptr, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_REGISTER_SB;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at qsee_register_shared_buffer()");
        return;
      }
      retval = qsee_prepare_shared_buf_for_secure_read(ptr, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_PREP_SB_SECURE_READ;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at qsee_prepare_shared_buf_for_secure_read()");
        retval = qsee_deregister_shared_buffer((void *)(uintnt)cmd_ptr->data);
        return;
      }
      /*Check for the pattern and update that in shared buffer*/
      for (j = 0; j < SHARED_BUF_PATTERN_LEN; j++) {
        i = *ptr;
        i = i + 10;
        *ptr = i;
        ptr++;
      }
      retval = qsee_prepare_shared_buf_for_nosecure_read((void *)(uintnt)cmd_ptr->data, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_PREP_SB_NON_SECURE_READ;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at qsee_prepare_shared_buf_for_nosecure_read()");
        return;
      }
      retval = qsee_deregister_shared_buffer((void *)(uintnt)cmd_ptr->data);
      if (retval) {
        rsp_ptr->status = FAIL_DEREGISTER_SB;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at qsee_deregister_shared_buffer()");
        return;
      }
      /* proceed to test limitations to the qsee_register_shared_buffer command
         specifically
         - no more than 3 unaligned (to 2MB) buffers are to be allowed
         - after that, it's still possible to map memory, aligned, up to 3 buffers (we will test 1)
       */
      {
        size_t split_len = cmd_ptr->len / (ALIGNED_BUF_MAX_NUM+1);
        uint32_t split_mapped[ALIGNED_BUF_MAX_NUM+1] = {0};
        uint8_t * aligned_buf = NULL;
        size_t aligned_len = __2MB__;
        do {
          QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer - testing limits on number of mappable buffers");
          ptr = (unsigned char *)(uintnt)(cmd_ptr->data);
          for (j = 0; j < ALIGNED_BUF_MAX_NUM; j++) {
            //QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Mapping [%u]: 0x%p %u", j, ptr+split_len*j, split_len);
            retval = qsee_register_shared_buffer(ptr+split_len*j, split_len);
            if (retval) {
              rsp_ptr->status = FAIL_REGISTER_SB;
              QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at qsee_register_shared_buffer() (Allocating buffer n. %u)", j);
              break;
            }
            split_mapped[j] = 1;
          }
          //QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Mapping [%u]: 0x%p %u", j, ptr+split_len*j, split_len);
          /* Mapping the 4th buffer, this has to fail */
          retval = qsee_register_shared_buffer(ptr+split_len*j, split_len);
          if (retval == 0) {
            split_mapped[j] = true;
            rsp_ptr->status = FAIL_REGISTER_SB;
            QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at qsee_register_shared_buffer(). This call was supposed to FAIL but it SUCCEEDED");
            break;
          }

          /* Obtain the multimedia buffer, which is 2MB aligned. This function will also map it. */
          retval = sec_ui_alloc_app_buffer(aligned_len, &aligned_buf);
          if ((retval != 0) && (retval != SEC_UI_QSEE_SECURE_BUFFER_ERROR)) {
            QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test PASSED at sec_ui_alloc_app_buffer(), N/A error. Skipping the remaining part of the test");
            rsp_ptr->status = SUCCESS;
            break;
          }
          if (retval) {
            QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at sec_ui_alloc_app_buffer(). Failed to map 2MB aligned buffer");
            rsp_ptr->status = FAIL_REGISTER_SB;
            break;
          }

          // free it
          retval = sec_ui_free_app_buffer();
          if (retval) {
            rsp_ptr->status = FAIL_DEREGISTER_SB;
            QSEE_LOG(QSEE_LOG_MSG_ERROR, "****Shared Buffer test FAILED at sec_ui_free_app_buffer. Returned: %d", retval);
            break;
          }
          rsp_ptr->status = SUCCESS;
          QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test PASSED  (CMD_ID 2)");
        } while (0);

        // cleanup of mapped buffers
        for (j = 0; j < ALIGNED_BUF_MAX_NUM; j++) {
          if (split_mapped[j]) {
            retval = qsee_deregister_shared_buffer(ptr+split_len*j);
            if (retval) {
              rsp_ptr->status = FAIL_DEREGISTER_SB;
              QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****Shared Buffer test FAILED at qsee_deregister_shared_buffer(), cleanup [%u]", j);
              // ignore and continue
            }
          }
        }
      }
    break;

    case CLIENT_CMD3_RUN_CRYTPO_TEST:
      ptr = (unsigned char *)(uintnt)(cmd_ptr->data);
      retval = qsee_register_shared_buffer(ptr, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_REGISTER_SB;
        break;
      }

      retval = qsee_prepare_shared_buf_for_secure_read(ptr, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_PREP_SB_SECURE_READ;
        break;
      }

      //Run crypto functional tests
      retval = tz_app_crypto_func_test();
      if(retval)
      {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Crypto Functional Test");
      }
      else
      {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Crypto Functional Test");
        rsp_ptr->status = SUCCESS;
      }

      retval = qsee_prepare_shared_buf_for_nosecure_read((void *)(uintnt)cmd_ptr->data, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_PREP_SB_NON_SECURE_READ;
      }
      retval = qsee_deregister_shared_buffer((void *)(uintnt)cmd_ptr->data);
      if (retval) {
        rsp_ptr->status = FAIL_DEREGISTER_SB;
      }
    break;

    case CLIENT_CMD4_RUN_CRYTPO_PERF:
      ptr = (unsigned char *)(uintnt)(cmd_ptr->data);
      retval = qsee_register_shared_buffer(ptr, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_REGISTER_SB;
        break;
      }
      retval = qsee_prepare_shared_buf_for_secure_read(ptr, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_PREP_SB_SECURE_READ;
        break;
      }

      //Run crypto performance tests
      retval = tz_app_crypto_perf_test();
      if(retval)
      {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Crypto performance Test");
        rsp_ptr->status = FAILED;
      }
      else
      {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Crypto performance Test");
        rsp_ptr->status = SUCCESS;
      }

      if(retval)
      {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "    crypto test failed for pkt_size = %d", i);
          rsp_ptr->data= average_time_diff;
      } else
      {
        rsp_ptr->status = SUCCESS;
        rsp_ptr->data= average_time_diff;
      }
      retval = qsee_prepare_shared_buf_for_nosecure_read((void *)(uintnt)cmd_ptr->data, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAIL_PREP_SB_NON_SECURE_READ;
        return;
      }
      retval = qsee_deregister_shared_buffer((void *)(uintnt)cmd_ptr->data);
      if (retval) {
        rsp_ptr->status = FAIL_DEREGISTER_SB;
      }
    break;

    case CLIENT_CMD5_RUN_SFS_TEST :
      retval = smplap_sfs_unit_test_suite();
      if (retval) {
        rsp_ptr->status = FAILED;
      }
      else {
        rsp_ptr->status = SUCCESS;
      }

      if (retval) {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : SFS unit Test");
        break;
      }

      retval = tz_app_sfs();
      if (retval) {
        rsp_ptr->status = FAILED;
      } else {
        rsp_ptr->status = SUCCESS;
      }

      if (retval) {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : SFS unit Test");
        break;
      }

      /* This test must be last for setup reasons */
      //retval = tz_app_counter();
      //if (retval) {
      //  rsp_ptr->status = FAILED;
      //} else {
      //  rsp_ptr->status = SUCCESS;
      //}

      if (retval) {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : SFS unit Test");
      } else {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : SFS unit Test");
      }
    break;

    case CLIENT_CMD6_RUN_FS_TEST :
      retval = tz_app_fs();
      if (retval) {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : FS counter Test");
        rsp_ptr->status = FAILED;
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : FS counter Test");
      }
    break;

    case CLIENT_CMD7_RUN_RSA_TEST :
      retval = tz_app_crypto_rsa_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Crypto RSA Test");

      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Crypto RSA Test");
      }
    break;

    /*
    case CLIENT_CMD8_RUN_RSA_PERF_TEST :
    retval = SUCCESS;
    if (retval) {
    rsp_ptr->status = FAILED;
    } else {
    rsp_ptr->status = SUCCESS;
    }
    break;
    */

    case CLIENT_CMD9_RUN_CMNLIB_TEST:
      retval = tz_app_cmnlib_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Common lib Test");

      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Common lib Test");
      }
    break;

    case CLIENT_CMD10_RUN_CORE_TEST :
      retval = run_core_test(cmd, cmdlen, rsp, rsplen, (void*)(uintnt)cmd_ptr->data, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : COre Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Core Test");
      }
    break;

    /*
    case CLIENT_CMD11_RUN_SECURECHANNEL_TEST :
    retval = run_securechannel_test();
    if (retval) {
    rsp_ptr->status = FAILED;
    } else {
    rsp_ptr->status = SUCCESS;
    }
    break;
    */

    case CLIENT_CMD12_RUN_MESSAGE_PASSING:
      retval = run_message_passing_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Message passing Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Message passing Test");
      }
    break;


    case CLIENT_CMD13_RUN_MISC_TEST :
      retval = run_misc_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Misc Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Misc Test");
      }
    break;

    /* If this test runs concurrently with a touch or power event, an xPU violation
    will be triggered.
    */
    #if 0
      case CLIENT_CMD16_RUN_BUSES_TEST:
    retval = run_buses_test();
    if (retval) {
      rsp_ptr->status = FAILED;
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : buses Test");

    } else {
      rsp_ptr->status = SUCCESS;
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : buses Test");
    }
    break;
    #endif

    case CLIENT_CMD17_RUN_STOR_TEST :
      retval = run_stor_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Store Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Store Test");
      }
    break;

    case CLIENT_CMD18_RUN_FUSE_TEST:
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "----- BEGIN HARD FUSE TESTS -------");
      retval = run_fuse_test();
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "----- END HARD FUSE TESTS -------");

      QSEE_LOG(QSEE_LOG_MSG_ERROR, "--- BEGIN SW-FUSE TESTS -------");
      retval |= run_sw_fuse_test();
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "--- END SW-FUSE TESTS -------");

      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : FUSE Tests");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : FUSE Tests");
      }
    break;

    case CLIENT_CMD19_RUN_BUSES_SPI_TEST:
      retval = run_buses_spi_test((uint32)cmd_ptr->data);
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : SPI bus Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : SPI bus Test");
      }
    break;


    case CLIENT_CMD21_RUN_CRYPTO_COPY:
      // copyDir = 1 means Secure to Non-secure
      if((uint32)(((tz_sc_copy_req_t*)cmd)->copyDir))
      {
        #ifdef USES_NO_CP
        retval = Content_Protection_Copy_SecureToNonsecure((uint8*)(uintnt)(((tz_sc_copy_req_t*)cmd)->nonSecBuffer),
        (uint32)(((tz_sc_copy_req_t*)cmd)->nonSecBufferLength),
        (tz_mem_array_s_t*)(&(((tz_sc_copy_req_t*)cmd)->secBufferHandle)),
        (uint32)(((tz_sc_copy_req_t*)cmd)->secBufferOffset),
        (uint32*)&((tz_sc_copy_rsp_t*)rsp)->secBufferLength);
        #else
          retval = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "This feature is not supported on external builds...");
        #endif
        ((tz_sc_copy_rsp_t *)rsp)->ret = retval;
      }
      // copyDir = 0 means Non-secure to secure
      else
      {
        retval = Content_Protection_Copy_NonsecureToSecure((uint8*)(uintnt)(((tz_sc_copy_req_t*)cmd)->nonSecBuffer),
        (uint32)(((tz_sc_copy_req_t*)cmd)->nonSecBufferLength),
        (tz_mem_array_s_t*)(&(((tz_sc_copy_req_t*)cmd)->secBufferHandle)),
        (uint32)(((tz_sc_copy_req_t*)cmd)->secBufferOffset),
        (uint32*)(&((tz_sc_copy_rsp_t*)rsp)->secBufferLength));
        ((tz_sc_copy_rsp_t*)rsp)->ret = retval;
      }
    break;

    case CLIENT_CMD22_RUN_SECURE_UI_DISPLAY_TEST:
      rsp_ptr->status = run_display_test( );
    break;

    case CLIENT_CMD23_RUN_SECURE_UI_TOUCH_TEST:
      rsp_ptr->status = run_touch_test( );
    break;

    case CLIENT_CMD25_RUN_SAFE_TEST:
      #if 0 //TODO
        retval = security_state_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : SAFE  Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : SAFE Test");
      }
      break
      #endif
    break;

    case CLIENT_CMD27_RUN_SMPLSERV_TEST:
      retval = run_smplserv_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Smplserv Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Smplserv Test");
      }
    break;

    case CLIENT_CMD29_RUN_BIO_LIB_TEST:
      retval = run_bio_lib_tests();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : BIO Lib Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : BIO Lib Test");
      }
    break;

    case CLIENT_CMD30_RUN_BULLETIN_BOARD_TEST:
      retval = run_bulletin_board_tests();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Bulletin Board Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Bulletin Board Test");
      }
    break;

    case CLIENT_CMD31_RUN_TLMM_TEST:
      retval = run_tlmm_tests();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : TLMM Test");

      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : TLMM Test");
      }
    break;

    case CLIENT_CMD50_RUN_LISTENER_FRAMEWORK_TEST:
      /*Modify response by 10 */
      if ((!cmd_ptr) || (!rsp_ptr) || (cmdlen < sizeof(struct send_cmd))) {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "Invalid input for %u cmd", CLIENT_CMD50_RUN_LISTENER_FRAMEWORK_TEST);
          rsp_ptr->status = -1;
        break;
      }
      list_test_req = ((uint32)cmd_ptr->data) * 100;
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "cmd_ptr->data: %u,  list_test_req:%u", cmd_ptr->data, list_test_req);
      retval = qsee_request_service(0x100, &list_test_req, sizeof(uint32), &list_test_rsp, sizeof(uint32));
      if (retval) {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Error in qsee req service");
        rsp_ptr->data = 0;
        rsp_ptr->status = -2;
        break;
      }
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "list_test_rsp:%u", list_test_rsp);
      if (list_test_rsp == (list_test_req * 100)) {
        rsp_ptr->data = ((uint32)cmd_ptr->data) * 10;
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Security Sate Test");
      } else {
        rsp_ptr->data = 0;
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Security Sate Test");
      }
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "rsp_ptr->data:%u, rsp_ptr->status: %d", rsp_ptr->data, rsp_ptr->status);
      for (i = 0; i < 24; i++) {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "Test Print: i: %u", i);
      }
    break;

    case CLIENT_CMD99_RUN_SFS_PERF_TEST:
      retval = smplap_sfs_perf_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : SFS unit Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : SFS unit Test");
      }
    break;

    case CLIENT_CMD32_RUN_ABORT_TEST:
      run_abort_test();
    break;

    case CLIENT_CMD33_RUN_SMPLCERT_TEST:
      retval = run_smplcert_test();
      if (retval) {
        rsp_ptr->status = FAILED;
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Smplcert Test");
      } else {
        rsp_ptr->status = SUCCESS;
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Smplcert Test");
      }
    break;

    case CLIENT_CMD34_RUN_TRANS_TEST:
    {
      rsp_ptr->status = run_trans_test((qsee_transm_t) cmd_ptr->len,
                                       cmd_ptr->data,
                                       cmd_ptr->data2);
      break;
    }

    case CLIENT_CMD35_RUN_OEM_BUF_TEST:
    {
      rsp_ptr->status = run_oem_buf_test();

      if (rsp_ptr->status == SUCCESS) {
          QSEE_LOG(QSEE_LOG_MSG_DEBUG,
                   "****PASSED : OEM Buffer Tests");
      } else {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG,
                 "****FAILED : OEM Buffer Tests");
      }

      break;
    }

    case CLIENT_CMD36_RUN_INTLOCK_TEST:
    {
      run_intlock_tests();
      rsp_ptr->status = SUCCESS;
      break;
    }

    case CLIENT_CMD37_REG_SHARED_BUFS:
    {
      qsee_register_shared_buffer((void*) ((uintptr_t) cmd_ptr->data), 0x1000);
      qsee_register_shared_buffer((void*) ((uintptr_t) cmd_ptr->data2), 0x1000);
      qsee_register_shared_buffer((void*) ((uintptr_t) cmd_ptr->len), 0x1000);
      rsp_ptr->status = SUCCESS;
      break;
    }

    case CLIENT_CMD38_ACCESS_REGION:
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Reading memory that should cause an abort");
      uint32_t status = *((uint32_t*) cmd_ptr->data);
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Abort did not happen!");
      rsp_ptr->status = status;
      break;
    }

    case CLIENT_CMD100_RUN_CACHE_TEST:
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "..... Starting Cache Test");
      retval =  run_cache_test();
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Cache Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Cache Test");
      }
    break;

    case CLIENT_CMD101_RUN_SHAREDBUFFER_TEST:
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "..... Starting SharedBuffer Test");
      retval =  run_sharedbuffer_test((void*)(uintnt)cmd_ptr->data, cmd_ptr->len);
      if (retval) {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : SharedBuffer Test");
      } else {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : SharedBuffer Test");
      }
    break;

    case CLIENT_CMD999_RUN_SMPLSERV_CRASH_TEST:   // smplserv crash test
      retval = run_smplserv_crash_test();
      if (retval)
      {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : Smplserv Crash Test, retval = %d", retval);
      }
      else
      {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : Smplserv Crash Test, retval = %d", retval );
      }
    break;

    case CLIENT_CMD52_SPIN_TEST:
      retval = run_spin_test();
      if (retval)
      {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : spin test, retval = %d", retval);
      }
      else
      {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : spin test, retval = %d", retval );
      }
      break;
    case CLIENT_CMD53_RUN_LOG_BITMASK_TEST:
      retval = run_log_bitmask_test();
      if (retval)
      {
        rsp_ptr->status = FAILED;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : run log bitmask test, retval = %d", retval);
      }
      else
      {
        rsp_ptr->status = SUCCESS;
        QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : run log bitmask test, retval = %d", retval );
      }
      break;
    case CLIENT_CMD1000_RUN_BLSP_MODIFY_OWNERSHIP_TEST:
        retval = run_blsp_modify_ownership_test((uint32)cmd_ptr->data, (uint32)cmd_ptr->data2);
        if (retval) {
           rsp_ptr->status = FAILED;
           QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****FAILED : BLSP Test");		   
        } else {
           rsp_ptr->status = SUCCESS;
		   QSEE_LOG(QSEE_LOG_MSG_DEBUG, "****PASSED : BLSP Test");
        }
        break;

    default :
      rsp_ptr->status = SUCCESS;
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Unsupported command: %d.  Test not yet implemented or commnented out.", cmd_ptr->cmd_id);
    break;
  }
}


/**
@brief
App specific shutdown
App will be given a chance to shutdown gracefully
*/
void tz_app_shutdown(void)
{
  /* app specific shutdown code*/
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "SAMPLE App shutdown");
  return;
}

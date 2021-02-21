/*
@file qsee_api_tests.c
@brief Contains test code for most of the QSEE APIs.

*/
/*===========================================================================
   Copyright (c) 2011-2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE
  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsapps/sampleapp/src/qsee_api_tests.c#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 12/23/15   dpk     Added support to pass args to SPI and BLSP modify ownership tests
# 10/28/15   dpk     Added BLSP Modify Ownership test
===========================================================================*/
#include "com_dtypes.h"
#include "qsee_log.h"
#include "qsee_heap.h"
#include "qsee_sfs.h"
#include "qsee_fs.h"
#include "qsee_i2c.h"
#include "qsee_comstr.h"
#include "qsee_spi.h"
#include "qsee_tlmm.h"
#include "qsee_comstr.h"
#include "qsee_prng.h"
#include "qsee_core.h"
#include "qsee_dcache.h"
#include "qsee_services.h"
#include "qsee_sync.h"
#include "qsee_trans_ns_addr.h"
#include "qsee_oem_buffer.h"
#include "qsee_intmask.h"
#include "qsee_blsp.h"

#define TOUCH_I2C_ADDRESS 0x4a                /* Address of the touch controller on the I2C bus */
#define TOUCH_I2C_DEVICE  QSEE_I2CPD_DEVICE_1 /* Bus the touch controller is on, BLSP 1 */

#define SPI_WRITE_BUF_SIZE 256
#define SPI_READ_BUF_SIZE  256


/* Registers in the Atmel mXT Memory Map, Figure 2-1 of Protocol Guide */
#define REG_FAMILY_ID		  0x00

#define QSEE_SUCCESS 0
#define TZBSP_OEM_IMEM_SIZE 0x1000
#define ut_assert_eqi(xx, yy) if ((xx) != (yy)) {return -1;}
#define TEST_ASSERT(xx, yy, str_fmt, ...)                               \
  if ((xx) != (yy))                                                     \
  {qsee_log(QSEE_LOG_MSG_ERROR, "Failed! (0x%x != 0x%x) "               \
            #str_fmt, (xx), (yy), ##__VA_ARGS__); return -1; } else {   \
    qsee_log(QSEE_LOG_MSG_ERROR, "Success! (0x%x == 0x%x) "             \
            #str_fmt, (xx), (yy), ##__VA_ARGS__);}

static int run_security_state_test(void);

int run_core_test(void* cmd, uint32 cmdlen, void* rsp, uint32 rsplen, void* data, uint32 len)
{
  uint32 retval = 0;
  uint32 output_buffer = 0;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- CORE UNIT TESTS ---------------------------------");

  retval = qsee_prng_getdata((uint8 *)(uintnt)(&output_buffer), sizeof(uint32));
  if(retval != sizeof(uint32))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_prng_getdata() FAILED, returned wrong number of bytes written.");
    return -1;
  }
  else
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_prng_getdata() PASSED, output: %x", output_buffer);
  }

  if( !qsee_is_ns_range(cmd, cmdlen)  && qsee_is_ns_range(data, len))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_is_ns_range PASSED");
  }
  else
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_is_ns_range FAILED");
    return -1;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_read_jtag_id() output: %x",qsee_read_jtag_id());
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_read_serial_num() output: %x",qsee_read_serial_num());

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_get_secure_stat() tests DONE (pass==1): %x",(0==run_security_state_test()));

  return 0;
}

int run_securechannel_test()
{
 QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- SECURE CHANNEL UNIT TESTS ---------------------------------");

	/*add tests here*/

 QSEE_LOG(QSEE_LOG_MSG_ERROR, "   Secure channel tests are not yet implemented.");
 return 0;
}


int run_misc_test()
{
  WCHAR* w_a = (WCHAR*)qsee_malloc(128);
  char * a = (char*)qsee_malloc(64);
  char * b = (char*)qsee_malloc(64);

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- COMSTR TESTS begin---------------------------------");

  if(!a || !b || !w_a)
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_malloc() failed");
    return -1;
  }

  if(!qsee_strlcpy(a, "Test string", 32))  //Returns the number of bytes copied, if succssful.  Should be non-zero.
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_strlcpy() failed");
    return -1;
  }

  if(!qsee_strlcpy(b, "Test string", 32))  //Returns the number of bytes copied, if succssful.  Should be non-zero.
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_strlcpy() failed");
    return -1;
  }

  if(!qsee_strlcat(a, "-ending-", 32)) // (a's string length is now 19 chars, and then a NULL char at the end.)
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_strlcat() failed");
    return -1;
  }

  if(0 != qsee_strnicmp(a, b, 4)) //Compare only first 4 bytes.  Return should be 0.
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_strnicmp() failed");
    return -1;
  }

  if(0 == qsee_strnicmp(a, b, 32)) //Compare all 32 bytes.  Return should NOT be 0.
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_strnicmp() failed");
    return -1;
  }

  qsee_strtowstr(a, w_a, 64);

  if(19 != qsee_wstrlen(w_a))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_strtowstr() or qsee_wstrlen() failed");
    return -1;
  }

  if(0 != qsee_wstrcmp(w_a, w_a))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_wstrcmp() failed");
    return -1;
  }
  #if 0
  if(NULL != qsee_wstrcmp(NULL, NULL))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_wstrcmp() failed, NULL was acceptes as a ptr to a string");
    return -1;
  }
  #endif

  if(0 == qsee_wstrtostr(w_a, b, 32))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_wstrtostr() failed");
    return -1;
  }

  if(0 != qsee_strnicmp(a, b, 32))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_strnicmp() failed");
    return -1;
  }

  if(0 == qsee_wstrlcat(w_a, w_a, 64))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_wstrlcat() failed");
    return -1;
  }

  if(w_a != qsee_wstrchr(w_a, 'T'))
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_wstrchr() failed");
    return -1;
  }
  #if 0
  if(NULL != qsee_wstrchr(NULL, 'T'))
  {
	QSEE_LOG(QSEE_LOG_MSG_ERROR, "-------------- qsee_wstrchr() failed, NULL was accepted as a ptr to a string");
	return -1;
  }
  #endif

  qsee_free(a);
  qsee_free(b);
  qsee_free(w_a);

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- COMSTR TESTS passed---------------------------------");
  return 0;
}

int run_tlmm_tests()
{
  uint32 gpio_key;
  qsee_tlmm_config_t my_config;
  qsee_gpio_value_t myval = 0;
  int index = 0;

  my_config.drive = QSEE_GPIO_6MA;
  my_config.pull = QSEE_GPIO_PULL_UP;
  my_config.direction = QSEE_GPIO_OUTPUT;

  for (index = 0; index < 2; index++)
  {
    if (qsee_tlmm_get_gpio_id("tlmm_gpio_test_pin", &gpio_key) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_get_gpio_id: Failed");
      return -1;
    }
    if (qsee_tlmm_config_gpio_id(gpio_key, &my_config) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_config_gpio_id: Failed");
      return -1;
    }
    if (qsee_tlmm_select_gpio_id_mode(gpio_key, QSEE_GPIO_MODE_GENERAL) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_select_gpio_id_mode to generic IO: Failed");
      return -1;
    }
    if (qsee_tlmm_select_gpio_id_mode(gpio_key, QSEE_GPIO_MODE_PRIMARY) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_select_gpio_id_mode to primary: Failed");
      return -1;
    }

    my_config.pull = QSEE_GPIO_NO_PULL;

    if (qsee_tlmm_select_gpio_id_mode(gpio_key, QSEE_GPIO_MODE_GENERAL) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_select_gpio_id_mode to generic (2nd time): Failed");
      return -1;
    }
    if (qsee_tlmm_gpio_id_out(gpio_key, QSEE_GPIO_HIGH) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_gpio_id_out output-HIGH: Failed");
      return -1;
    }
    if (qsee_tlmm_gpio_id_out(gpio_key, QSEE_GPIO_LOW) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_gpio_id_out output-LOW: Failed");
      return -1;
    }

    my_config.direction = QSEE_GPIO_INPUT;

    if (qsee_tlmm_config_gpio_id(gpio_key, &my_config) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_config_gpio_id: Failed");
      return -1;
    }
    if (qsee_tlmm_gpio_id_in(gpio_key, &myval) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_gpio_id_in signal read: Failed");
      return -1;
    }
    if (qsee_tlmm_release_gpio_id(gpio_key) != 0)
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_tlmm_release_gpio_id: Failed");
      return -1;
    }
  }
  return 0;

}

/**
 * @brief     QSEE SPI test 
 *               QSEE Sample Client Command ::
 *                    qseecom_sample_client v sampleap 19 1
 *
 * @spiDeviceId    SPI device Id 0 to 11
 *                       
 */
int run_buses_spi_test(uint32 spiDeviceId)
{
	int retval = 0;

	qsee_spi_config_t spi_config;
	qsee_spi_transaction_info_t write_info;
	static uint8 write_data[SPI_WRITE_BUF_SIZE] __attribute__((aligned(64)));
	qsee_spi_transaction_info_t read_info;
	static uint8 read_data[SPI_READ_BUF_SIZE] __attribute__((aligned(64)));
	int i;

    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_buses_spi_test: spiDeviceId = %d\n", spiDeviceId);
	//START SPI TEST CODE
	spi_config.spi_bits_per_word = 8;
	spi_config.spi_clk_always_on = QSEE_SPI_CLK_NORMAL;
	spi_config.spi_clk_polarity = QSEE_SPI_CLK_IDLE_HIGH;
	spi_config.spi_cs_mode = QSEE_SPI_CS_KEEP_ASSERTED;
	spi_config.spi_cs_polarity = QSEE_SPI_CS_ACTIVE_HIGH;
	spi_config.spi_shift_mode = QSEE_SPI_OUTPUT_FIRST_MODE;
	spi_config.max_freq = 19200000; //19.2 MHz
	spi_config.hs_mode = 0;
	spi_config.loopback = 1;
    spi_config.spi_slave_index = 0;
    spi_config.deassertion_time_ns = 0;
	

	for (i = 0; i < SPI_WRITE_BUF_SIZE; i++) {
		write_data[i] = i;
	}
	write_info.buf_addr = write_data;
	write_info.buf_len = SPI_WRITE_BUF_SIZE*sizeof(uint8);


	if (0 != (retval = qsee_spi_open(spiDeviceId))) {
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_open1: retval = %d\n", retval);
	}

	do{
		for (i = 0; i < SPI_READ_BUF_SIZE; i++) {
			read_data[i] = 0XFF;
		}
		read_info.buf_addr = read_data;
		read_info.buf_len = SPI_READ_BUF_SIZE*sizeof(uint8);
		//PERFORM WRITE
		if (0 != (retval = qsee_spi_write(spiDeviceId,&spi_config, &write_info))){
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_write: retval = %d\n", retval);
			break;
		}

		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_write: retval = %d\n", retval);

		//PEFORM READ

		if (0 != (retval = qsee_spi_read(spiDeviceId,&spi_config, &read_info))){
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_read: retval = %d\n", retval);
			break;
		}


		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_read: retval = %d\n", retval);

		if (0 != (retval = qsee_spi_full_duplex(spiDeviceId,&spi_config,
						&write_info, &read_info))){
			QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_full_duplex: retval = %d\n",
					retval);
			break;
		}

		if (retval == -1) {
			break;
		}


		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_full_duplex: retval = %d\n",
				retval);
	}while(0);


	if (0 != (retval = qsee_spi_close(spiDeviceId))) {
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_spi_close1: retval = %d\n", retval);
	}

	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "BUSES SPI TEST COMPLETE, retval = %d\n", retval);
	return retval;

}

int run_buses_test()
{
  int ret = 0;
  int retClose = 0;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- BUSES UNIT TESTS ---------------------------------");

  /* Open the bus. This will lock the bus to TZ */
  ret = qsee_i2c_open(TOUCH_I2C_DEVICE);
  if( ret != 0 )
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "   qsee_i2c_open() FAILED! returned = %ld", ret);
    return ret;
  }
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "   qsee_i2c_open() PASSED");

  /* This call requires the QUP clocks to be on, or will cause an L2 error */
#if 0
  do {
    uint8 familyId;
    qsee_i2c_config_t i2c_config;
    qsee_i2c_transaction_info_t  readInfo;
    qsee_i2c_bus_config_t busConfig;
    qsee_i2c_slave_device_config_t deviceConfig;

    i2c_config.p_bus_config = &busConfig;
    i2c_config.p_slave_config = &deviceConfig;

    /* swap HIGH and LOW bytes for address , as requested by the Atmel mXT specs */
    readInfo.start_addr = ((REG_FAMILY_ID >> 8) & 0x00FF) | ((REG_FAMILY_ID & 0x00FF) << 8);
    readInfo.p_buf = &familyId;
    readInfo.buf_len = sizeof(familyId);
    readInfo.total_bytes = 0;

    ret = qsee_i2c_read(TOUCH_I2C_DEVICE, &i2c_config, &readInfo);
    if( ret != 0 )
    {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "   qsee_i2c_read() FAILED! returned = %ld", ret);
      break;
    }
    else
    {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "   qsee_i2c_read() PASSED");
    }
  } while (0);
#endif
  retClose = qsee_i2c_close(TOUCH_I2C_DEVICE);
  if( retClose != 0 )
  {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "   qsee_i2c_close() FAILED! returned = %ld", ret);
  }
  else
  {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "   qsee_i2c_close() PASSED");
  }

  if (ret)
    return ret;

  return retClose;
}


int security_state_test()
{
  int ret = 0;
  qsee_secctrl_secure_status_t status;
  memset(&status, 0, sizeof(status));

  ret = qsee_get_secure_state(&status);
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_get_secure_state() pass test: %x %x, ret %d",
               status.value[0], status.value[1], ret);
  if (0 != ret) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "qsee_get_secure_state() call fail and returns %d\n", ret);
    return 1;
  }
  if (0 == (status.value[0] & 0x1f)) {
     QSEE_LOG(QSEE_LOG_MSG_DEBUG, "secure boot is setup");
     ret = 0x0;
  } else {
     QSEE_LOG(QSEE_LOG_MSG_DEBUG, "secure boot is NOT setup");
     ret = 0x02;
  }

  if (0 == (status.value[0] & 0x20)) {
     QSEE_LOG(QSEE_LOG_MSG_DEBUG, "RPMB is provisioned");
  } else {
     QSEE_LOG(QSEE_LOG_MSG_DEBUG, "RPMB boot is NOT provisioned");
     ret |= 0x4;
  }

  return ret;
}




static int run_security_state_test()
{
  int ret = 0;
  qsee_secctrl_secure_status_t status;
  memset(&status, 0, sizeof(status));

  ret = qsee_get_secure_state(&status);
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_get_secure_state() pass(=1): %d, val: %x %x",
               (ret == 0), status.value[0], status.value[1]);

  ret = qsee_get_secure_state(NULL);
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "  qsee_get_secure_state() negative, NULL buffer, pass(=1): %d", (ret != 0));

  return 0;
}


int run_abort_test(void)
{
  volatile uint32* my_bad_ptr = NULL;
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Sampleapp about to abort");
  *my_bad_ptr = 5;
  return *my_bad_ptr;
}


static char mybuff[1024];

int run_cache_test()
{

  int testLength = 5;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, " Test qsee_dcache_clean_region() : addr = %x , length = %d", mybuff, testLength);
  qsee_dcache_clean_region( mybuff, testLength);

  testLength = 6;
  QSEE_LOG(QSEE_LOG_MSG_ERROR, " Test qsee_dcache_flush_region() : addr = %x , length = %d", mybuff, testLength);
  qsee_dcache_flush_region( mybuff, testLength);

  testLength = 1024;
  QSEE_LOG(QSEE_LOG_MSG_ERROR, " Test qsee_dcache_inval_region() : addr = %x , length = %d", mybuff, testLength);
  qsee_dcache_inval_region( mybuff, testLength);

  for (int i =0; i<testLength; i++ ){
	  mybuff [i] = i%256;
  }

  return 0;
}


int run_sharedbuffer_test(void* data, uint32 len)
{

  int ret;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, " Test qsee_register_shared_buffer() : addr = %x , length = %d", data, len);
  ret = qsee_register_shared_buffer(data, len);

  if (ret)
  {
	  QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_register_shared_buffer() test failed");
	  return ret;
  }

  QSEE_LOG(QSEE_LOG_MSG_ERROR, " Test  qsee_deregister_shared_buffer: addr = %x , length = %d", data, len);
  ret = qsee_deregister_shared_buffer(data);

  if (ret)
  {
	  QSEE_LOG(QSEE_LOG_MSG_ERROR, " qsee_deregister_shared_buffer() test failed");
	  return ret;
  }

  return 0;
}


int run_spin_test()
{
  int rc = qsee_spin(10);
  return rc;
}

int run_trans_test(qsee_transm_t tt, uintptr_t va, uintptr_t exp_pa)
{
  uintptr_t pa = 0;

  int retval = qsee_trans_ns_addr(tt, va, &pa);

  if (retval || (exp_pa & 0xFFFFF000) != pa) {
    /* Bit one indicates an expected translation fault. */
    if (QSEE_TRANS_NS_ADDR_ERROR_TRANSLATION_FAULT == retval && (exp_pa & 1)) {
      if (QSEE_EL1_READ == tt) {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG,
                 "****PASSED : NS Address Translation Test - Read 0x%08x Fault Result", va);
      } else {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG,
                 "****PASSED : NS Address Translation Test - Write 0x%08x Fault Result", va);
      }
      return 0;
    } else {
      if (QSEE_EL1_READ == tt) {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG,
                 "****FAILED : NS Address Translation Test - Read 0x%08x Expected 0x%08x Result 0x%08x Return %d", va , exp_pa, pa, retval);
      } else {
        QSEE_LOG(QSEE_LOG_MSG_DEBUG,
                 "****FAILED : NS Address Translation Test - Write 0x%08x Expected 0x%08x Result 0x%08x Return %d", va, exp_pa, pa, retval);
      }
      return -1;
    }
  } else {
    if (QSEE_EL1_READ == tt) {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG,
               "****PASSED : NS Address Translation Test - Read 0x%08x", va);
    } else {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG,
               "****PASSED : NS Address Translation Test - Write 0x%08x", va);
    }
    return 0;
  }
}


static int test_write_and_read_no_offset(void)
{
  char buf[TZBSP_OEM_IMEM_SIZE];
  char cmpbuf[TZBSP_OEM_IMEM_SIZE];
  qsee_strlcpy(buf, "test write and read", sizeof(buf));
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0, buf, strlen(buf)));
  ut_assert_eqi(QSEE_SUCCESS, qsee_read_oem_buffer(0, cmpbuf, strlen(buf)));
  ut_assert_eqi(0, memcmp(buf, cmpbuf, strlen(buf)));

  memset(buf, 0, sizeof(buf));
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0, buf, sizeof(buf)));
  ut_assert_eqi(QSEE_SUCCESS, qsee_read_oem_buffer(0, cmpbuf, sizeof(buf)));
  ut_assert_eqi(0, memcmp(buf, cmpbuf, sizeof(buf)));

  qsee_strlcpy(buf, "test", sizeof(buf));
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0, buf, strlen(buf)));
  qsee_strlcpy(buf, "test overwrite", sizeof(buf));
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0, buf, strlen(buf)));
  ut_assert_eqi(QSEE_SUCCESS, qsee_read_oem_buffer(0, cmpbuf, strlen(buf)));
  ut_assert_eqi(0, memcmp(buf, cmpbuf, strlen(buf)));

  return QSEE_SUCCESS;
}

static int test_write_and_read_with_offset(void)
{
  char buf[TZBSP_OEM_IMEM_SIZE];
  char cmpbuf[TZBSP_OEM_IMEM_SIZE];
  qsee_strlcpy(buf, "test offset write and read", sizeof(buf));
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0x50,
                                                    buf,
                                                    strlen(buf)));
  ut_assert_eqi(QSEE_SUCCESS, qsee_read_oem_buffer(0x50,
                                                   cmpbuf,
                                                   strlen(buf)));
  ut_assert_eqi(0, memcmp(buf, cmpbuf, strlen(buf)));

  ut_assert_eqi(QSEE_SUCCESS, qsee_read_oem_buffer(0x50,
                                                   cmpbuf,
                                                   strlen("test")));
  ut_assert_eqi(0, memcmp(buf, cmpbuf, strlen("test")));

  ut_assert_eqi(QSEE_SUCCESS, qsee_read_oem_buffer(0x50 + strlen("test "),
                                                   cmpbuf,
                                                   strlen("offset")));
  ut_assert_eqi(0,
                memcmp(buf + strlen("test "), cmpbuf, strlen("offset")));

  memset(buf, 0, sizeof(buf));
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0, buf, sizeof(buf)));
  ut_assert_eqi(QSEE_SUCCESS, qsee_read_oem_buffer(0, cmpbuf, sizeof(buf)));
  ut_assert_eqi(0, memcmp(buf, cmpbuf, sizeof(buf)));

  return QSEE_SUCCESS;
}

static int test_read_size_greater_than_buf(void)
{
  char buf[TZBSP_OEM_IMEM_SIZE];
  char cmpbuf[TZBSP_OEM_IMEM_SIZE * 2];

  /* Start with known OEM buffer of all zeros */
  memset(buf, 0, sizeof(buf));
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0, buf, sizeof(buf)));

  /* Initialize local buffers */
  qsee_strlcpy(buf, "test large read buffer", sizeof(buf));
  memset(cmpbuf, 0xFF, sizeof(cmpbuf));

  /* Write string into OEM buffer. */
  ut_assert_eqi(QSEE_SUCCESS, qsee_write_oem_buffer(0, buf, strlen(buf)));
  ut_assert_eqi(QSEE_SUCCESS,
                qsee_read_oem_buffer(0, cmpbuf, strlen(cmpbuf)));

  /* Check entire buffer copied correctly */
  ut_assert_eqi(0, memcmp(buf, cmpbuf, sizeof(buf)));

  /* Check remaining part of input buffer was unchanged. */
  memset(buf, 0xFF, sizeof(buf));
  ut_assert_eqi(0, memcmp(cmpbuf + sizeof(buf),
                          buf,
                          sizeof(cmpbuf) - sizeof(buf)));

  return QSEE_SUCCESS;
}

static int test_overflow_failures(void)
{
  /* AA32 cannot overflow.  Cannot test overflow for AA64 on target
     from EL0 due to MINK IPC validating buffer arguments as coming
     from the address space of the application. */
  return QSEE_SUCCESS;
}

static int test_bad_offset_failures(void)
{
  char buf[TZBSP_OEM_IMEM_SIZE];
  qsee_strlcpy(buf, "test bad offsets", sizeof(buf));

  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_OFFSET_OUT_OF_BOUNDS,
                qsee_write_oem_buffer(TZBSP_OEM_IMEM_SIZE, buf, 0));
  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_OFFSET_OUT_OF_BOUNDS,
                qsee_write_oem_buffer(TZBSP_OEM_IMEM_SIZE * 2,
                                      buf, sizeof(buf)));

  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_OFFSET_OUT_OF_BOUNDS,
                qsee_read_oem_buffer(TZBSP_OEM_IMEM_SIZE, buf, 0));
  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_OFFSET_OUT_OF_BOUNDS,
                qsee_read_oem_buffer(TZBSP_OEM_IMEM_SIZE * 5,
                                     buf, sizeof(buf)));

  return QSEE_SUCCESS;
}

static int test_bad_source_buffer_failures(void)
{
  char buf[TZBSP_OEM_IMEM_SIZE * 2];
  qsee_strlcpy(buf, "test bad source buffers", sizeof(buf));

  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_SOURCE_BUFFER_TOO_LARGE,
                qsee_write_oem_buffer(0, buf, sizeof(buf)));
  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_SOURCE_BUFFER_TOO_LARGE,
                qsee_write_oem_buffer(TZBSP_OEM_IMEM_SIZE - 1, buf, 2));
  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_SOURCE_BUFFER_TOO_LARGE,
                qsee_write_oem_buffer(0, buf, TZBSP_OEM_IMEM_SIZE + 1));
  ut_assert_eqi(QSEE_OEM_BUFFER_ERROR_SOURCE_BUFFER_TOO_LARGE,
                qsee_write_oem_buffer(0, buf, sizeof(buf)));

  return QSEE_SUCCESS;
}

int run_oem_buf_test(void)
{
  ut_assert_eqi(TZBSP_OEM_IMEM_SIZE, qsee_get_oem_buffer_length());
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_get_oem_buffer_length() PASSED");

  ut_assert_eqi(QSEE_SUCCESS, test_write_and_read_no_offset());
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "test_write_and_read_no_offset() PASSED");
  ut_assert_eqi(QSEE_SUCCESS, test_write_and_read_with_offset());
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "test_write_and_read_with_offset() PASSED");
  ut_assert_eqi(QSEE_SUCCESS, test_read_size_greater_than_buf());
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "test_read_size_greater_than_buf() PASSED");

  ut_assert_eqi(QSEE_SUCCESS, test_overflow_failures());
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "test_overflow_failures() PASSED");
  ut_assert_eqi(QSEE_SUCCESS, test_bad_offset_failures());
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "test_bad_offset_failures() PASSED");
  ut_assert_eqi(QSEE_SUCCESS, test_bad_source_buffer_failures());
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "test_bad_source_buffer_failures() PASSED");

  return QSEE_SUCCESS;
}

extern int run_smplserv_test(void);

int run_intlock_tests(void)
{
  qsee_intsrc_t ori_mask;
  qsee_intsrc_t restore_mask;
  qsee_intsrc_t cur_mask;

  qsee_get_intmask(&cur_mask);
  ori_mask = cur_mask;

  qsee_get_oem_buffer_length();
  qsee_get_intmask(&cur_mask);
  TEST_ASSERT(cur_mask, ori_mask, "Check intmask after syscall");

  qsee_disable_all_interrupts(&restore_mask);
  qsee_get_intmask(&cur_mask);
  TEST_ASSERT(restore_mask, ori_mask,
              "Check restore_mask from qsee_disable_all_interrupts()");
  if (sizeof(uint64_t) == sizeof(uintptr_t)) {
    TEST_ASSERT(cur_mask, QSEE_FIQ | QSEE_IRQ | QSEE_SERROR | QSEE_DEBUG,
                "Check interrupt mask after qsee_disable_all_interrupts()");
  }
  else {
    TEST_ASSERT(cur_mask, QSEE_FIQ | QSEE_IRQ | QSEE_SERROR,
                "Check interrupt mask after qsee_disable_all_interrupts()");
  }

  qsee_get_oem_buffer_length();
  qsee_get_intmask(&cur_mask);
  if (sizeof(uint64_t) == sizeof(uintptr_t)) {
    TEST_ASSERT(cur_mask, QSEE_FIQ | QSEE_IRQ | QSEE_SERROR | QSEE_DEBUG,
                "Check all interrupts stay disabled after syscall");

  }
  else {
    TEST_ASSERT(cur_mask, QSEE_FIQ | QSEE_IRQ | QSEE_SERROR,
                "Check all interrupts stay disabled after syscall");
  }

  qsee_set_intmask(restore_mask);
  qsee_get_intmask(&cur_mask);
  TEST_ASSERT(cur_mask, ori_mask,
              "Check qsee_set_intmask() to restore value");

  qsee_set_intmask(cur_mask | QSEE_IRQ);
  qsee_get_intmask(&cur_mask);
  TEST_ASSERT(cur_mask, ori_mask | QSEE_IRQ,
              "Check qsee_set_intmask() masking one interrupt source");

  run_smplserv_test();
  qsee_get_intmask(&cur_mask);
  TEST_ASSERT(cur_mask, ori_mask | QSEE_IRQ,
             "Check intmask after making call to another secure application");

  qsee_set_intmask(ori_mask);

  /* If aa64, we can set DAIF directly! */
  if (sizeof(uint64_t) == sizeof(uintptr_t)) {
    __asm volatile ("mrs %0, DAIF" : "=r" (cur_mask) :);
    TEST_ASSERT(cur_mask >> 6, ori_mask,
                "Check mrs read of interrupt mask shows expected value");

    qsee_set_intmask(ori_mask | QSEE_IRQ);
    __asm volatile ("mrs %0, DAIF" : "=r" (cur_mask) :);
    TEST_ASSERT(cur_mask >> 6, ori_mask | QSEE_IRQ,
               "Check mrs read of interrupt mask shows expected value");

    uint64_t daif = 0x80;
    __asm volatile ("msr DAIF, %x0" : : "r" (daif));
    __asm volatile ("mrs %0, DAIF" : "=r" (cur_mask) :);
    TEST_ASSERT(cur_mask, daif, "Check msr write then mrs read");

    qsee_get_intmask(&cur_mask);
    TEST_ASSERT(cur_mask, daif >> 6,
                "Check msr write then qsee_get_intmask() read");
  }

  return 0;
}

/**
 * @brief     QSEE test to modify ownership of a BLSP instance, using sample client command from adb shell.
 *               QSEE Sample Client Command ::
 *                    qseecom_sample_client v sampleap 1000 1
 *
 * @peripheralId    QUP ID 1 to 12, UART ID 13 to 24
 *
 * @subsystemId    Subsystem ID
 *                         0 -> NONE
 *                         1 -> TRUSTZONE
 *                         3 -> HLOS
 *                         6 -> ADSP/LPASS
 *                       
 */

int run_blsp_modify_ownership_test(uint32 peripheralId, uint32 subsystemId)
{
   int res = 0;

   QSEE_LOG(QSEE_LOG_MSG_DEBUG, "run_blsp_modify_ownership_test: peripheralId = %d, subsystemId = %d\n", peripheralId, subsystemId);   
   
   if (0 != (res = qsee_blsp_modify_ownership((qsee_qup_device_id_t)peripheralId, (qsee_subsystem_id_t)subsystemId))) {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_blsp_modify_ownership() Failed for QUP %d & Subsystem ID %d : retval = %d\n", peripheralId, subsystemId, res);
   }
   else
   {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_blsp_modify_ownership() Success for QUP %d & Subsystem ID %d...\n", peripheralId, subsystemId);
   }

   return res;
}

int run_log_bitmask_test()
{
  uint8_t pri = 0;
  uint8_t expected = QSEE_LOG_MSG_LOW | QSEE_LOG_MSG_HIGH;
  uint8_t current = qsee_log_get_mask();

  qsee_log_set_mask(QSEE_LOG_MSG_LOW);
  QSEE_LOG(QSEE_LOG_MSG_LOW, "-- LOG BIT MASK TEST LOW ---------------------------------");

  qsee_log_set_mask(QSEE_LOG_MSG_MED);
  QSEE_LOG(QSEE_LOG_MSG_LOW, "-- ALERT: Should Not see this - run_log_bitmask_test----");
  QSEE_LOG(QSEE_LOG_MSG_MED, "-- LOG BIT MASK TEST LOW MED---------------------------------");

  qsee_log_set_mask(QSEE_LOG_MSG_HIGH);
  QSEE_LOG(QSEE_LOG_MSG_LOW, "-- ALERT: Should Not see this - run_log_bitmask_test----");
  QSEE_LOG(QSEE_LOG_MSG_MED, "-- ALERT: Should Not see this - run_log_bitmask_test----");
  QSEE_LOG(QSEE_LOG_MSG_HIGH,"-- LOG BIT MASK TEST HIGH---------------------------------");
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "-- ALERT: Should Not see this - run_log_bitmask_test----");

  pri = qsee_log_get_mask();

  QSEE_LOG(QSEE_LOG_MSG_HIGH, "Mask Value set = %0x", pri);

  qsee_log_set_mask(QSEE_LOG_MSG_LOW | QSEE_LOG_MSG_HIGH);
  pri = qsee_log_get_mask();
  
  TEST_ASSERT(pri, expected, "Priority should be value of %d", expected);
  QSEE_LOG(QSEE_LOG_MSG_HIGH, "Mask Value set = %0x", pri);
  qsee_log_set_mask(current); 
  return 0;
}

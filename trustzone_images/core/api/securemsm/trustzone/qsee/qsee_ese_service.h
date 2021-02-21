#ifndef QSEE_ESE_SERVICE_H
#define QSEE_ESE_SERVICE_H

/**
*
*  @file qsee_ese_service.h
*
*  @brief Provide Embedded Secure Element (eSE) Services API wrappers. The eSE QSEE service
*         resides in the QSEE kernel.
*         The has the following responsibilities:
*         - Management of multiple sessions and open channels.
*         - Sending Command Application Protocol Data Units (C-APDUs) to the eSE driver
*         - Receiving Response Application Protocol Data Units (R-APDUs) from the eSE driver.
*
*/

/*===========================================================================
  Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header:
  $DateTime:
  $Author:

when            who         what, where, why
--------        ---         -----------------------------------
15-Dec-2015     dc          Add support for SPI Chip Select slave identifier
20-Apr-2015     dc          Initial Version

===========================================================================*/

#include "IxErrno.h"
#include "qsee_spi.h"

#define QSEE_ESE_SERVICE_SPI_APDU_SIZE 258

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/**
 * @brief QCOM return codes for QSEE eSE Service. These need to be mapped to
 *        appropriate codes for GPTEE SE API interface. The can be done from
 *        within the TA app or TEE library
 */
typedef enum
{
  QSEE_ESE_SERVICE_STATUS_SUCCESS,               /**< Operation has been successful */
  QSEE_ESE_SERVICE_STATUS_PENDING_IRQ,           /**< QCOM: C-APDU send and waiting for R-APDU */
  QSEE_ESE_SERVICE_STATUS_PENDING_CHANNEL,       /**< QCOM: Blocked by another session to complete send C-APDU and receiving R-APDU */
  QSEE_ESE_SERVICE_STATUS_ERROR_BAD_STATE,       /**< QCOM: Tried to resume a blocked API when it was not in a pending state */
  QSEE_ESE_SERVICE_STATUS_ERROR_GENERIC,         /**< Generic error code for some unknown failure */
  QSEE_ESE_SERVICE_STATUS_ERROR_BAD_PARAMETERS,  /**< Bad arguments supplied to the API call */
  QSEE_ESE_SERVICE_STATUS_ERROR_ITEM_NOT_FOUND,  /**< Handle supplied cannot be found */
  QSEE_ESE_SERVICE_STATUS_ERROR_OUT_OF_MEMORY,   /**< Out of memory when creating new handles */
  QSEE_ESE_SERVICE_STATUS_ERROR_COMMUNICATION,   /**< Problems with SPI communication */
  QSEE_ESE_SERVICE_STATUS_ERROR_SHORT_BUFFER,    /**< Read buffer supplied not big enough for message received */
} qsee_ese_service_status_t;

/**
 * Type of timeout variable
 */
typedef uint32_t qsee_ese_service_timeout_t;

/**
 * Handle used by the TZ service to manage the status of the current connection
 * A value of zero(0) is invalid
 */
typedef uint32_t qsee_ese_service_handle_t;

/**
 * @brief C-APDU
 */
typedef struct
{
  uint32_t  size_write;                               /**< number of bytes to write */
  uint8_t   buff[QSEE_ESE_SERVICE_SPI_APDU_SIZE];     /**< address for write data */
} qsee_ese_service_capdu_t;

/**
 * @brief R-APDU
 */
typedef struct
{
  uint32_t size_read;                                 /**< number of bytes read which is initialised to zero  */
  uint8_t   buff[QSEE_ESE_SERVICE_SPI_APDU_SIZE];      /**< address for read data */
} qsee_ese_service_rapdu_t;

/**
 * Starts the eSE TZBSP Service, and perform some intialization \n
 *
 * @return 0 on success, otherwise failure
 *
 * @see qsee_ese_service_stop
 *
 */
int qsee_ese_service_start(void);

/**
 * Stops the eSE TZBSP Service, and perform some resouce clearing if necessary \n
 *
 * @return QSEE_ESE_SERVICE_STATUS_SUCCESS on success, otherwise failure
 *
 * @see qsee_ese_service_start
 *
 */
int qsee_ese_service_stop(void);

/**
 * Open the SPI device and setups the eSE Service for communication with slave \n
 *
 * @param [in] device_id The SPI device ID to attach to
 * @param [in] slave_id  The Chip Select slave identifier
 *
 * @return QSEE_ESE_SERVICE_STATUS_SUCCESS on success, otherwise failure
 *
 * @see qsee_ese_service_spi_close
 *
 */
int qsee_ese_service_spi_open(qsee_spi_device_id_t device_id, uint8_t slave_id);

/**
 * Closes SPI device used for eSE Service communication with the slave
 *
 * @param [in] device_id The SPI device ID to attach to
 *
 * @return QSEE_ESE_SERVICE_STATUS_SUCCESS on success, otherwise failure
 *
 * @see qsee_ese_service_spi_open
 *
 */
int qsee_ese_service_spi_close(qsee_spi_device_id_t device_id);

/**
 * Open a logical connection using the handle to communicate over SPI.
 *
 * @param [in] handle The unique handle for the connection
 *
 * @return QSEE_ESE_SERVICE_STATUS_SUCCESS on success, otherwise failure
 *
 * @see qsee_ese_service_close
 *
 */
int qsee_ese_service_handle_open(qsee_ese_service_handle_t handle);

/**
 * Close a logical connection using the handle.
 *
 * @param [in] handle The unique handle for the connection
 *
 * @return QSEE_ESE_SERVICE_STATUS_SUCCESS on success, otherwise failure
 *
 * @see qsee_ese_service_open
 *
 */

int qsee_ese_service_handle_close(qsee_ese_service_handle_t handle);

/**
 * Writes to slave data on the logical connection handle.
 *
 * @param [in]      handle        The handle to communicate on
 * @param [in]      c_apdu        Write buffer information.
 * @param [in,out]  r_apdu        Write buffer information.
 * @param [in]      microseconds  Timeout in microseconds to wait for a response from the eSE.
 *                                A non-zero value for the timeout makes this call block
 *                                A zero value makes this call return if there is no response
 *                                right away
 *
 * @return
 *       QSEE_ESE_SERVICE_STATUS_PENDING_IRQ successful write of C-APDU \n
 *       QSEE_ESE_SERVICE_STATUS_PENDING_CHANNEL Did not write since waiting for R-APDU \n
 *       Any other eason code as per TEE SE API interface \n
 *
 * @see qsee_ese_service_write
 * @see qsee_ese_service_read
 *
 * @pre qsee_ese_service_open
 *
 */

int qsee_ese_service_transceive(qsee_ese_service_handle_t  handle,
                                qsee_ese_service_capdu_t  *c_apdu,
                                qsee_ese_service_rapdu_t  *r_apdu,
                                qsee_ese_service_timeout_t microseconds);

/**
 * Writes to slave data on the logical connection handle.
 *
 * @param [in]  handle   The handle to communicate on
 * @param [in]  c_apdu   Write buffer information.
 *
 * @return
 *       QSEE_ESE_SERVICE_STATUS_PENDING_IRQ successful write of C-APDU \n
 *       QSEE_ESE_SERVICE_STATUS_PENDING_CHANNEL Did not write since waiting for R-APDU \n
 *       Any other eason code as per TEE SE API interface \n
 *
 * @see qsee_ese_service_transceive
 *
 * @pre qsee_ese_service_open
 *
 */
int qsee_ese_service_write(qsee_ese_service_handle_t  handle,
                           qsee_ese_service_capdu_t  *c_apdu);

/**
 * Reads from slave data on the logical connection handle.
 *
 * @param [in]      handle        The handle to communicate on
 * @param [in,out]  r_apdu        Write buffer information.
 * @param [in]      status        Status returned from previous Write
 * @param [in]      microseconds  Timeout in microseconds to wait for a response from the eSE.
 *                                A non-zero value for the timeout makes this call block
 *                                A zero value makes this call return if there is no response
 *                                right away
 *
 * @return
 *       QSEE_ESE_SERVICE_STATUS_SUCCESS If successfully read the data \n
 *       Any other eason code as per TEE SE API interface \n
 *
 * @see qsee_ese_service_transceive
 *
 * @pre qsee_ese_service_open
 *
 */
int qsee_ese_service_read(qsee_ese_service_handle_t  handle,
                          qsee_ese_service_rapdu_t  *r_apdu,
                          qsee_ese_service_status_t  status,
                          qsee_ese_service_timeout_t microseconds);

#endif  // QSEE_ESE_SERVICE_H


/**
   @file app_main.c
   @brief Sample trusted application to demonstrate use of GP TEE SE lib in
   @ conjunction with smart card service/HLOS daemon.
*/
/*=========================================================================
  Global Platform TEE SE  API Source File
  Description
  This file contains GP TEE SE API Implementation.

  # Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
  # Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/
/*===========================================================================
  Edit History
  when        who   what
  --------    ---   ----------------------------------------------------------
  26/11/2015  dc    Add Support for TEE Secure Channel.
  07/09/2015  pm    Bug fixes.
  18/03/2015  pm    Initial Implementation of GP TEE SE API

  ===========================================================================*/


/*==========================================================================*
 *                             INCLUDE FILES                                *
 *==========================================================================*/
#include "qsee_log.h"
#include "qsee_message.h"
#include "qsee_timer.h"
#include <stringl.h>
#include "qsee_ese_service.h"
#include "qsee_heap.h"
#include "tee_internal_se_api.h"

#define QPAY_LOG_INF(xx_fmt, ...)         QSEE_LOG(QSEE_LOG_MSG_DEBUG, "TA: %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)
#define QPAY_LOG_ERR(xx_fmt, ...)         QSEE_LOG(QSEE_LOG_MSG_ERROR, "TA: %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)

#define QPAY_ENTER(xx_fmt, ...)           QSEE_LOG(QSEE_LOG_MSG_DEBUG, "TA: Entering %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)
#define QPAY_EXIT(xx_fmt, ...)            QSEE_LOG(QSEE_LOG_MSG_DEBUG, "TA: Exiting %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)

#ifndef TEE_SE_API_1_1
#define QC_TEE_SE_ARRAY_SIZE(a)                     ((sizeof(a)) / (sizeof((a)[0])))
#endif // TEE_SE_API_1_1

/*HLOS Controlling Daemon Commands Defnitions*/

/*App service open and close*/
#define QPAY_OPEN_CONNECTION                      1
#define QPAY_CLOSE_CONNECTION                     3

/*Service Class*/
#define TEE_SE_SERVICE_OPEN                      41
#define TEE_SE_SERVICE_CLOSE                     42
#define TEE_SE_SERVICE_GET_READERS               43

/*Reader Class*/
#define TEE_SE_READER_GET_PROPERTIES             51
#define TEE_SE_READER_GET_NAME                   52
#define TEE_SE_READER_OPEN_SESSION               53
#define TEE_SE_READER_CLOSE_SESSIONS             54

/*Session class*/
#define TEE_SE_SESSION_ClOSE                     63
#define TEE_SE_SESSION_CLOSE_CHANNELS            64
#define TEE_SE_SESSION_OPEN_BASIC_CHANNEL        65
#define TEE_SE_SESSION_OPEN_LOGICAL_CHANNEL      66

/*Channel Class*/
#define TEE_SE_CHANNEL_CLOSE                     71
#define TEE_SE_CHANNEL_SELECT_NEXT               72
#define TEE_SE_CHANNEL_GET_SELECT_RESPONSE       73
#define TEE_SE_CHANNEL_TRANSMIT                  74
#define TEE_SE_CHANNEL_GET_RESPONSE_LENGTH       75
#define TEE_SE_SECURE_CHANNEL_OPEN               76
#define TEE_SE_SECURE_CHANNEL_CLOSE              77
#define TEE_SE_SECURE_CHANNEL_GET_SECURITY_LEVEL 78

#define TEE_SE_HLOS_APDU_SIZE                    2200

#define TEE_SE_STATUS_BYTE_LEN                    1
#define TEE_SE_OFFSET_STATUS_BYTE                 0
#define TEE_SE_OFFSET_CHANNEL_BYTE                1
#define TEE_SE_OFFSET_AID                         1
#define TEE_SE_OFFSET_RSP                         2
#define TEE_SE_OFFSET_PDU                         1
#define TEE_SE_MAX_CHANNEL_SUPPORTED              3
#define TEE_SE_NUMBER_OF_SESSIONS                 5
#define TEE_SE_NUMBER_OF_READERS                  2
#define TEE_SE_MASK_CHANNEL_BYTE                  0x03

/*Handles to TA.Will be filled by GP TEE SE LIB*/
static TEE_SEServiceHandle seServiceHandle                               = NULL;
static TEE_SEReaderHandle  seReaderHandleList[TEE_SE_NUMBER_OF_READERS]  = { NULL, NULL };
static TEE_SESessionHandle seSessionHandle[TEE_SE_NUMBER_OF_SESSIONS]    = { NULL, NULL, NULL, NULL, NULL };
static TEE_SEChannelHandle seChannelHandle[TEE_SE_MAX_CHANNEL_SUPPORTED] = { NULL, NULL, NULL };

static uint8_t  sessionHandleCount = 0;
static uint8_t  channelHandleCount = 0;
static uint32_t channelHandleIndex = 0;


/* Input command data struct(TO TA from HLOS)*/
typedef struct
{
  uint32_t sessionHandle;
  uint32_t channelNumber;
  uint32_t cmd_id;
  uint32_t cmd_len;
  uint8_t  tApdu[TEE_SE_HLOS_APDU_SIZE];
} __attribute__((packed)) tz_app_send_cmd_t;

/* output command data struct(TO HLOS from TA)*/
typedef struct
{
  uint32_t sessionHandle;
  uint32_t channelNumber;
  uint32_t rsp_len;
  uint8_t  rApdu[TEE_SE_HLOS_APDU_SIZE];
} __attribute__((packed)) tz_app_send_rsp_t;

/* Local AID buffer to extract and copt AID information from HLOS daemon*/
static TEE_SEAID seAID = { NULL, 0 };

/*buffer where manage channel response will be copied if it fails
  (other than 0x9000 status bytes)*/
extern uint8_t manageChannelRsp[QC_TEE_MANAGE_CHANNEL_RSP_SIZE];

/**
 *
 * invoked when trusted application is loaded.
 *
 * @param   void.
 *
 * @return  None.
 **/
void tz_app_init(void)
{
  QPAY_ENTER();

  QPAY_EXIT();
}

/**
 *
 * Validates a channel index
 *
 * @param [in] index : channel index to validate.
 *
 * @return  true if index is valid. false otherwise.
 **/
static bool tz_app_is_channel_handle_index_valid(uint32_t index)
{
  return (index != QC_TEE_SE_FAILED) && (index < TEE_SE_MAX_CHANNEL_SUPPORTED);
}

/**
 *
 * Validates a session handle
 *
 * @param [in] handle : session handle to validate.
 *
 * @return  true if handle is valid. false otherwise.
 **/
static bool tz_app_is_session_handle_valid(uint32_t handle)
{
  return (handle > 0) && (handle <= TEE_SE_NUMBER_OF_SESSIONS);
}

/**
 *
 * Checks if the channel status is pending
 *
 * @param [in] status : Channel status to valid.
 *
 * @return  true if channel is pending sending another C-APDU or waiting for R-APDU. false otherwise.
 **/
static bool tz_app_is_channel_status_pending(uint32_t status)
{
  return (status == QC_TEE_SE_PENDING_IRQ) || (status == QC_TEE_SE_PENDING_CHANNEL);
}

/**
 *
 * Fills response APDU , status and other needed information by HLOS daemon in
 * response struct and returns that back to HLOS for further processing.
 *
 * @param   [out] rsp_ptr : response poiter buffer where R-APDU , status and other
 *                         information will be filled.
 *          [out] status : Status whether passed or failed or pending(channel/IRQ).
 *          [in]  cmd    : Last command recieved from HLOS daemon as based on this
 *                         based on this cmd , needed response will be filled.
 *
 * @return  None.
 **/
static void tz_app_get_rapdu(tz_app_send_rsp_t *rsp_ptr, TEE_Result status, uint32_t cmd)
{
  QPAY_ENTER("rsp_ptr->rsp_len=%d, status=%d, cmd=%d", rsp_ptr->rsp_len, status, cmd);

  rsp_ptr->rApdu[TEE_SE_OFFSET_STATUS_BYTE] = (uint8_t)status;

  switch (status)
  {
    case TEE_SUCCESS:

      if ((cmd == TEE_SE_SESSION_OPEN_BASIC_CHANNEL) ||
          (cmd == TEE_SE_SESSION_OPEN_LOGICAL_CHANNEL))
      {
        TEE_SEChannelHandle channelHandle = seChannelHandle[channelHandleIndex];

        QPAY_LOG_INF("seAID.bufferLen=%d, seChannelHandle[channelHandleIndex]->channelNumber=%d",
                     seAID.bufferLen,
                     channelHandle->channelNumber);

        QPAY_LOG_INF("channelHandle->selectRsp.buffLen=%d", channelHandle->selectRsp.buffLen);

        rsp_ptr->rApdu[TEE_SE_OFFSET_CHANNEL_BYTE] = channelHandle->channelNumber;

        if (seAID.bufferLen != 0)
        {
          rsp_ptr->rsp_len = QSEE_ESE_SERVICE_SPI_APDU_SIZE;

          TEE_SEChannelGetSelectResponse(channelHandle,
                                         rsp_ptr->rApdu + TEE_SE_OFFSET_RSP,
                                         &rsp_ptr->rsp_len);

          rsp_ptr->rsp_len += QC_TEE_STATUS_WORD_LENGTH;
        }
        else
        {
          // when no AID present then only return manage channel response in read.
          memscpy(rsp_ptr->rApdu + TEE_SE_OFFSET_RSP,
                  sizeof(rsp_ptr->rApdu) - TEE_SE_OFFSET_RSP,
                  manageChannelRsp, QC_TEE_STATUS_WORD_LENGTH);

          rsp_ptr->rsp_len = sizeof(manageChannelRsp);
        }
      }
      else if ((cmd == TEE_SE_CHANNEL_TRANSMIT) ||
               (cmd == TEE_SE_CHANNEL_GET_SELECT_RESPONSE) ||
               (cmd == TEE_SE_CHANNEL_SELECT_NEXT))
      {
        // data already copied in buffer
        rsp_ptr->rsp_len += TEE_SE_STATUS_BYTE_LEN;
      }
      else
      {
        rsp_ptr->rsp_len = TEE_SE_STATUS_BYTE_LEN;     /*Only status for rest of commands*/
      }

      break;

    case QC_TEE_SE_PENDING_IRQ:

      /*QC_TEE_SE_PENDING_IRQ*/
      if ((cmd == TEE_SE_CHANNEL_TRANSMIT) && (rsp_ptr->rApdu[TEE_SE_OFFSET_PDU] == QC_TEE_T1_S_BLOCK_WTX))
      {
        // data already copied in buffer
        rsp_ptr->rsp_len += TEE_SE_STATUS_BYTE_LEN;
      }
      else
      {
        rsp_ptr->rsp_len = TEE_SE_STATUS_BYTE_LEN;
      }

      break;

    case QC_TEE_SE_PENDING_CHANNEL:
      rsp_ptr->rsp_len = TEE_SE_STATUS_BYTE_LEN;
      break;

    default:

      rsp_ptr->rsp_len = TEE_SE_STATUS_BYTE_LEN;
      rsp_ptr->rApdu[TEE_SE_OFFSET_STATUS_BYTE] = (uint8_t)QC_TEE_SE_FAILED;

      if (cmd == TEE_SE_SESSION_OPEN_LOGICAL_CHANNEL)
      {
        memscpy(rsp_ptr->rApdu + TEE_SE_STATUS_BYTE_LEN,
                sizeof(rsp_ptr->rApdu) - TEE_SE_STATUS_BYTE_LEN,
                manageChannelRsp, QC_TEE_STATUS_WORD_LENGTH);

        rsp_ptr->rsp_len += QC_TEE_STATUS_WORD_LENGTH;
      }

      break;
  }

  debugPrint(rsp_ptr->rApdu, rsp_ptr->rsp_len, "TA -> HLOS =");

  QPAY_EXIT("rsp_ptr->rsp_len=%d", rsp_ptr->rsp_len);
}

/**
 *
 * Finds a free channel handle index in local list so that the new open channel handle
 * can be assigned to this index.
 *
 * @param   void.
 *
 * @return  free available index.
 **/
static TEE_Result tz_app_find_free_channel_handle_index(void)
{
  size_t          j = 0;
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER();

  for (j = 0; j < TEE_SE_MAX_CHANNEL_SUPPORTED; j++)
  {
    if (seChannelHandle[j] == NULL)
    {
      retval = j;

      break;
    }
  }

  QPAY_EXIT("Free Channel handle index =%X", retval);

  return retval;
}
/**
 *
 * Clears local records(maintained in trusted application) of channels associated with the
 * provided session handle as these channels will be cleared and closed by library internally.
 * so trusted application needs to remove these records also from its list.
 *
 * @param   [in] seSessionHandle : Session handle whose channels are to be cleared.
 *
 * @return  None.
 **/
static void tz_app_clear_channels_from_session(TEE_SESessionHandle *seSessionHandle)
{
  size_t j = 0;
  size_t i = 0;

  QPAY_ENTER("seSessionHandle=%X, (*seSessionHandle)->numofChannels=%X",
             seSessionHandle,
             (*seSessionHandle)->numofChannels);

  for (j = 0; j < QC_TEE_SE_ARRAY_SIZE((*seSessionHandle)->channel); j++)
  {
    for (i = 0; i < QC_TEE_SE_ARRAY_SIZE(seChannelHandle); i++)
    {
      if ((*seSessionHandle)->channel[j] != NULL)
      {
        if ((*seSessionHandle)->channel[j] == seChannelHandle[i])
        {
          seChannelHandle[i] = NULL;
          channelHandleCount--;
          QPAY_LOG_INF("Cleared one channel from index %d", i);
          QPAY_LOG_INF("Total Channel still open %d", channelHandleCount);
        }
      }
    }
  }

  QPAY_EXIT("Cleared one channel from indices[%d,%d], Total Channel still open %d", j, i, channelHandleCount);
}

/**
 *
 * Finds the channel handle index in local list(maintained in trusted application) based
 * on channel number recieved from HLOS daemon.
 *
 * @param   [in] channelNumber : Channel number to be searched.
 *
 * @return  Index of this channel number in local list.
 **/
static TEE_Result tz_app_find_channel_handle_index(int channelNumber)
{
  size_t          i = 0;
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER("Channel to find is %X and total channels are %X", channelNumber, channelHandleCount);

  for (i = 0; i < TEE_SE_MAX_CHANNEL_SUPPORTED; i++)
  {
    if (seChannelHandle[i] != NULL)
    {
      if (channelNumber == seChannelHandle[i]->channelNumber)
      {
        QPAY_LOG_INF("Channel handle is %X at index %d", seChannelHandle[i], i);

        retval = i;

        break;
      }
    }
  }

  QPAY_EXIT("Free Channel handle index is retval=%X", retval);

  return retval;
}

/**
 *
 * Checks the returned value from GP TEE SE API and if its some error case
 * then it returns QC_TEE_SE_FAILED(error indication) to HLOS daemon.
 *
 * @param   [in] retval : Incoming returned value from library.
 *
 * @return  None.
 **/
static TEE_Result tz_app_check_error(TEE_Result retval)
{
  QPAY_ENTER("retval=%X", retval);

  if ((retval != QC_TEE_SE_PENDING_IRQ) &&
      (retval != QC_TEE_SE_PENDING_CHANNEL) &&
      (retval != TEE_SUCCESS))
  {
    QPAY_LOG_INF("Error Returned from API %x", retval);

    /* Error Case*/
    retval = QC_TEE_SE_FAILED;
  }

  QPAY_EXIT("retval=%X", retval);

  return retval;
}
/**
 *
 * Opens a channel(Basic or Logical depending on the Cmd from HLOS) with the specified AID
 * (given by HLOS wallet app).
 *
 * @param   [in] cmd_ptr : Pointer to the command struct coming from HLOS.
 *
 * @return  QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
 * @return  QC_TEE_SE_PENDING_IRQ     : if CAPDU has been sent by eSE service and response is pending.
 * @return  QC_TEE_SE_FAILED          : If failed due to any error.
 * @return  TEE_SUCCESS               : If operation succeeds.
 **/
static TEE_Result tz_app_open_channel(tz_app_send_cmd_t *cmd_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER();

  /* remove status byte which is first*/
  seAID.bufferLen = cmd_ptr->cmd_len - TEE_SE_STATUS_BYTE_LEN;

  QPAY_LOG_INF("seAID.bufferLen=%d", seAID.bufferLen);

  if (seAID.bufferLen != 0)
  {
    seAID.buffer = (uint8_t *)QC_TEE_SE_MALLOC(seAID.bufferLen);

    if (seAID.buffer == NULL)
    {
      retval = TEE_ERROR_OUT_OF_MEMORY;
    }
    else
    {
      memscpy(seAID.buffer, seAID.bufferLen, cmd_ptr->tApdu + TEE_SE_STATUS_BYTE_LEN, seAID.bufferLen);
    }
  }

  if ((seAID.bufferLen == 0) || (seAID.buffer != NULL))
  {
    /* find free channel index to allocate handle to this request */
    channelHandleIndex = tz_app_find_free_channel_handle_index();

    if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
    {
      if (tz_app_is_session_handle_valid(cmd_ptr->sessionHandle))
      {
        uint8_t sessionHandleIndex = cmd_ptr->sessionHandle - 1;

        switch (cmd_ptr->cmd_id)
        {
          case TEE_SE_SESSION_OPEN_BASIC_CHANNEL:

            if (tz_app_is_channel_status_pending(cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]))
            {
              retval = TEE_SESessionOpenBasicChannel_cc(seSessionHandle[sessionHandleIndex],
                                                        &seAID,
                                                        &seChannelHandle[channelHandleIndex],
                                                        cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]);
              if (retval == TEE_SUCCESS)
              {
                channelHandleCount++;
              }
            }
            else
            {
              retval = TEE_SESessionOpenBasicChannel(seSessionHandle[sessionHandleIndex],
                                                     &seAID,
                                                     &seChannelHandle[channelHandleIndex]);
            }
            break;

          case TEE_SE_SESSION_OPEN_LOGICAL_CHANNEL:

            if (sessionHandleCount == 1)
            {
              sessionHandleIndex = 0;
            }

            if (tz_app_is_channel_status_pending(cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]))
            {
              retval = TEE_SESessionOpenLogicalChannel_cc(seSessionHandle[sessionHandleIndex],
                                                          &seAID,
                                                          &seChannelHandle[channelHandleIndex],
                                                          cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]);
              if (retval == TEE_SUCCESS)
              {
                channelHandleCount++;
              }
            }
            else
            {
              retval = TEE_SESessionOpenLogicalChannel(seSessionHandle[sessionHandleIndex],
                                                       &seAID,
                                                       &seChannelHandle[channelHandleIndex]);
            }
            break;
        }
      }
    }
  }

  if ((seAID.buffer != NULL) && (seAID.bufferLen != 0))
  {
    QC_TEE_SE_FREE(seAID.buffer);
  }

  retval = tz_app_check_error(retval);

  if (retval == TEE_SUCCESS)
  {
    QPAY_LOG_INF("================================================================");
    QPAY_LOG_INF("Total channels opened %d", channelHandleCount);
    QPAY_LOG_INF("================================================================");
  }

  QPAY_EXIT("retval=%X", retval);

  /*Check if any Error*/
  return retval;
}

/**
 *
 * Transmits incoming C-APDU from HLOS to eSE over the channel which is attached in
 * CLA byte of the C-APDU and transmits back R-APDU recieved from eSE to HLOS daemon.
 *
 * @param   [in] cmd_ptr : Pointer to the command struct coming from HLOS.
 * @param   [in] rsp_ptr : Pointer to the response struct which will be returned
 *                         back to HLOS after response is filled.
 *
 * @return  QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
 * @return  QC_TEE_SE_PENDING_IRQ     : if CAPDU has been sent by eSE service and response is pending.
 * @return  QC_TEE_SE_FAILED          : If failed due to any error.
 * @return  TEE_SUCCESS               : If operation succeeds.
 * @
 **/
static TEE_Result tz_app_channel_transmit(tz_app_send_cmd_t *cmd_ptr, tz_app_send_rsp_t *rsp_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER();

  /*cmd_ptr->tApdu[TEE_SE_OFFSET_CHANNEL_BYTE](CLA byte of to be transmitted message) will have channel number.*/
  channelHandleIndex = tz_app_find_channel_handle_index((cmd_ptr->tApdu[TEE_SE_OFFSET_CHANNEL_BYTE] & TEE_SE_MASK_CHANNEL_BYTE));

  if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
  {
    rsp_ptr->rsp_len  = QSEE_ESE_SERVICE_SPI_APDU_SIZE;

    // Clear the response
    secure_memset(rsp_ptr->rApdu, 0, sizeof(rsp_ptr->rApdu));

    if (tz_app_is_channel_status_pending(cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]))
    {
      retval = TEE_SEChannelTransmit_cc(seChannelHandle[channelHandleIndex],
                                        cmd_ptr->tApdu + TEE_SE_STATUS_BYTE_LEN,
                                        cmd_ptr->cmd_len,
                                        rsp_ptr->rApdu + TEE_SE_STATUS_BYTE_LEN,
                                        &rsp_ptr->rsp_len,
                                        cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]);
    }
    else
    {
      retval = TEE_SEChannelTransmit(seChannelHandle[channelHandleIndex],
                                     cmd_ptr->tApdu + TEE_SE_STATUS_BYTE_LEN,
                                     cmd_ptr->cmd_len - TEE_SE_STATUS_BYTE_LEN,
                                     rsp_ptr->rApdu + TEE_SE_STATUS_BYTE_LEN,
                                     &rsp_ptr->rsp_len);
    }
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

/**
 *
 * Closes channel requested by HLOS daemon.Channel number is recieved in command struct
 * and attached channel handle (with this channel number) is found to pass it further to
 * library so that only correct channel handle is freed by library.
 *
 * @param   [in] cmd_ptr : Pointer to the command struct coming from HLOS.
 *
 * @return  QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
 * @return  QC_TEE_SE_PENDING_IRQ     : if CAPDU has been sent by eSE service and response is pending.
 * @return  QC_TEE_SE_FAILED          : If failed due to any error.
 * @return  TEE_SUCCESS               : If operation succeeds.
 **/
static TEE_Result tz_app_channel_close(tz_app_send_cmd_t *cmd_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER();

  /* cmd_ptr->tApdu[TEE_SE_OFFSET_CHANNEL_BYTE] will have channel number.*/
  channelHandleIndex = tz_app_find_channel_handle_index(cmd_ptr->tApdu[TEE_SE_OFFSET_CHANNEL_BYTE]);

  if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
  {
    if (tz_app_is_channel_status_pending(cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]))
    {
      retval = TEE_SEChannelClose_cc(seChannelHandle[channelHandleIndex], cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]);
    }
    else
    {
      retval = TEE_SEChannelClose(seChannelHandle[channelHandleIndex]);
    }
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  if (retval == TEE_SUCCESS)
  {
    seChannelHandle[channelHandleIndex] = NULL;
    channelHandleCount--;
    QPAY_LOG_INF("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    QPAY_LOG_INF("Channels still open %d and Closed index is %d", channelHandleCount, channelHandleIndex);
    QPAY_LOG_INF("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  }

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

/**
 *
 * Selects next applet on this channel.Channel number is recieved from HLOS(in command
 * struct) and corresponding channel handle is passed to library.
 *
 * @param   [in] cmd_ptr : Pointer to the command struct coming from HLOS.
 * @param   [in] rsp_ptr : Pointer to the response struct which will be returned
 *                         back to HLOS after response is filled.
 *
 * @return  QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
 * @return  QC_TEE_SE_PENDING_IRQ     : if CAPDU has been sent by eSE service and response is pending.
 * @return  QC_TEE_SE_FAILED          : If failed due to any error.
 * @return  TEE_SUCCESS               : If operation succeeds.
 **/
static TEE_Result tz_app_channel_select_next(tz_app_send_cmd_t *cmd_ptr, tz_app_send_rsp_t *rsp_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER();

  /* cmd_ptr->tApdu[TEE_SE_OFFSET_CHANNEL_BYTE] will have channel number.*/
  channelHandleIndex = tz_app_find_channel_handle_index(cmd_ptr->channelNumber);

  if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
  {
    if (tz_app_is_channel_status_pending(cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]))
    {
      // TEE_SEChannelSelectNext_cc updates rsp_ptr->rsp_len but needs to know the size of the buffer
      rsp_ptr->rsp_len = sizeof(cmd_ptr->tApdu) - TEE_SE_STATUS_BYTE_LEN;

      retval = TEE_SEChannelSelectNext_cc(seChannelHandle[channelHandleIndex],
                                          rsp_ptr->rApdu + TEE_SE_STATUS_BYTE_LEN,
                                          &rsp_ptr->rsp_len,
                                          cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]);
    }
    else
    {
      retval = TEE_SEChannelSelectNext(seChannelHandle[channelHandleIndex]);
    }
  }

  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}
/**
 *
 * Closes requested session .Session handle to be closed is recieved from HLOS daemon.
 * Channel records of this session(available in trusted application)are cleared and
 * internally library closes and clears all channel attached to this session.
 *
 * @param   [in] cmd_ptr : Pointer to the command struct coming from HLOS.
 *
 * @return  None.
 **/
static TEE_Result tz_app_session_close(tz_app_send_cmd_t *cmd_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER();

  if (tz_app_is_session_handle_valid(cmd_ptr->sessionHandle))
  {
    const uint8_t sessionHandleIndex = cmd_ptr->sessionHandle - 1;

    /*Clear Trusted App record of channels associated to this session as TEE_SESessionClose
      API will clear attached channels so it should be cleared from trusted application records
      also*/
    tz_app_clear_channels_from_session(&seSessionHandle[sessionHandleIndex]);

    /*Now close intended session*/
    TEE_SESessionClose(seSessionHandle[sessionHandleIndex]);

    /*Clear recorded session handle*/
    seSessionHandle[sessionHandleIndex] = NULL;
    sessionHandleCount--;

    retval = TEE_SUCCESS;
  }
  else
  {
    QPAY_LOG_INF("Invalid Session handle");
  }

  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

/**
 *
 * Gets SELECT command response for the channel number requested by HLOS
 * daemon.
 *
 * @param   [in] cmd_ptr : Pointer to the command struct coming from HLOS.
 * @param   [in] rsp_ptr : Pointer to the response struct which will be returned
 *                         back to HLOS after response is filled.
 *
 * @return  QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
 * @return  QC_TEE_SE_PENDING_IRQ     : if CAPDU has been sent by eSE service and response is pending.
 * @return  QC_TEE_SE_FAILED          : If failed due to any error.
 * @return  TEE_SUCCESS               : If operation succeeds.
 **/
static TEE_Result tz_app_channel_get_select_rsp(tz_app_send_cmd_t *cmd_ptr, tz_app_send_rsp_t *rsp_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER("cmd_ptr->channelNumber=%d", cmd_ptr ? cmd_ptr->channelNumber : TEE_SE_MAX_CHANNEL_SUPPORTED);

  if (cmd_ptr)
  {
    channelHandleIndex = tz_app_find_channel_handle_index(cmd_ptr->channelNumber);

    if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
    {
      rsp_ptr->rsp_len = QSEE_ESE_SERVICE_SPI_APDU_SIZE;

      retval = TEE_SEChannelGetSelectResponse(seChannelHandle[channelHandleIndex],
                                              rsp_ptr->rApdu + TEE_SE_STATUS_BYTE_LEN,
                                              &rsp_ptr->rsp_len);
    }
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

/**
 *
 * Opens a session being requested by HLOS daemon and returns a unique handle for
 * this session to HLOS so that HLOS daemon can direct all channel open requests
 * on corrsponding sessions.
 *
 * @param   [in] rsp_ptr : Pointer to the response struct which will be returned
 *                         back to HLOS with a unique session handle.
 *
 * @return  QC_TEE_SE_FAILED   : If failed due to any error.
 * @return  TEE_SUCCESS        : If operation succeeds.
 **/
static TEE_Result tz_app_open_session(tz_app_send_rsp_t *rsp_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER();

  retval = TEE_SEReaderOpenSession(seReaderHandleList[0],
                                   &seSessionHandle[sessionHandleCount]);
  if (retval == TEE_SUCCESS)
  {
    sessionHandleCount++;
    rsp_ptr->sessionHandle = sessionHandleCount;
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

/**
 *
 * Gets readers (eSE) information from library e.g. how many readers are available
 * and provides a unique handle to each reader. This reader handle is used further
 * to communicate with corresponding reader. In currrent implementation , it is always
 * single eSE so always one reader and corresponding sinlge reader handle. This reader
 * handle is cleared when servie close is invoked either during the trusted app unload
 * by HLOS or trusted aplication is closing down the opened service.
 *
 * @param   void.
 *
 * @return  QC_TEE_SE_FAILED    : If failed due to any error.
 * @return  TEE_SUCCESS         : If operation succeeds.
 **/
static TEE_Result tz_app_get_readers(void)
{
  TEE_Result retval = TEE_SUCCESS;

  uint32_t seReaderHandleListLen = 2;

  QPAY_ENTER();

  if (seReaderHandleList[0] == NULL)
  {
    retval = TEE_SEServiceGetReaders(seServiceHandle, seReaderHandleList,
                                     &seReaderHandleListLen);

    if (retval == TEE_SUCCESS)
    {
      // Open session for access control mechanism of Smart card service.
      QPAY_LOG_INF("Open a session for access control. sessionHandleCount=%d", sessionHandleCount);

      retval = TEE_SEReaderOpenSession(seReaderHandleList[0],
                                       &seSessionHandle[sessionHandleCount]);
    }

    sessionHandleCount++;
  }
  else
  {
    QPAY_LOG_INF("Readers are allocated");
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

#ifdef TEE_SE_API_1_1

static TEE_Result tz_app_channel_get_response_length(tz_app_send_cmd_t *cmd_ptr, tz_app_send_rsp_t *rsp_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER("cmd_ptr->channelNumber=%d", cmd_ptr ? cmd_ptr->channelNumber : TEE_SE_MAX_CHANNEL_SUPPORTED);

  if (cmd_ptr)
  {
    channelHandleIndex = tz_app_find_channel_handle_index(cmd_ptr->channelNumber);

    if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
    {
      retval = TEE_SEChannelGetResponseLength(seChannelHandle[channelHandleIndex], &rsp_ptr->rsp_len);
    }
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result tz_app_secure_get_secure_channel_parameters(TEE_SC_Params *scParams)
{
  TEE_Result retval = TEE_ERROR_BAD_PARAMETERS;

  QPAY_ENTER("scParams=%X", scParams);

  if (scParams)
  {
    // Fill in scParams according to the secure channel required.
    // @see GlobalPlatform Device Technology TEE Secure Element API Version 1.1
    retval = TEE_ERROR_NOT_IMPLEMENTED;
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result tz_app_secure_channel_open(tz_app_send_cmd_t *cmd_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER("cmd_ptr=%X", cmd_ptr);

  if (cmd_ptr)
  {
    channelHandleIndex = tz_app_find_channel_handle_index(cmd_ptr->channelNumber);

    QPAY_LOG_INF("cmd_ptr->channelNumber=%d, channelHandleIndex=%d", cmd_ptr->channelNumber, channelHandleIndex);

    if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
    {
      const TEE_SEChannelHandle channelHandle = seChannelHandle[channelHandleIndex];

      if (TEE_SESecureChannelGetSecurityLevel(channelHandle) == TEE_SC_NO_SECURE_MESSAGING)
      {
        TEE_SC_Params scParams = { 0 };

        retval = tz_app_secure_get_secure_channel_parameters(&scParams);

        if (retval == TEE_SUCCESS)
        {
          if (tz_app_is_channel_status_pending(cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]))
          {
            retval = TEE_SESecureChannelOpen_cc(channelHandle, &scParams, cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]);
          }
          else
          {
            retval = TEE_SESecureChannelOpen(channelHandle, &scParams);;
          }
        }
      }
    }
  }

  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result tz_app_secure_channel_close(tz_app_send_cmd_t *cmd_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER("cmd_ptr=%X", cmd_ptr);

  if (cmd_ptr)
  {
    channelHandleIndex = tz_app_find_channel_handle_index(cmd_ptr->channelNumber);

    QPAY_LOG_INF("cmd_ptr->channelNumber=%d, channelHandleIndex=%d", cmd_ptr->channelNumber, channelHandleIndex);

    if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
    {
      if (tz_app_is_channel_status_pending(cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]))
      {
        retval = TEE_SESecureChannelClose_cc(seChannelHandle[channelHandleIndex], cmd_ptr->tApdu[TEE_SE_OFFSET_STATUS_BYTE]);
      }
      else
      {
        retval = TEE_SESecureChannelClose(seChannelHandle[channelHandleIndex]);
      }
    }
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result tz_app_secure_channel_get_security_level(tz_app_send_cmd_t *cmd_ptr, tz_app_send_rsp_t *rsp_ptr)
{
  TEE_Result retval = QC_TEE_SE_FAILED;

  QPAY_ENTER("cmd_ptr=%X, rsp_ptr=%X", cmd_ptr, rsp_ptr);

  if (cmd_ptr && rsp_ptr)
  {
    channelHandleIndex = tz_app_find_channel_handle_index(cmd_ptr->channelNumber);

    QPAY_LOG_INF("cmd_ptr->channelNumber=%d, channelHandleIndex=%d", cmd_ptr->channelNumber, channelHandleIndex);

    if (tz_app_is_channel_handle_index_valid(channelHandleIndex))
    {
      const int32_t security_level = TEE_SESecureChannelGetSecurityLevel(seChannelHandle[channelHandleIndex]);

      if (memscpy(rsp_ptr->rApdu + TEE_SE_OFFSET_RSP,
                  sizeof(rsp_ptr->rApdu) - TEE_SE_OFFSET_RSP,
                  &security_level,
                  sizeof(security_level)) == sizeof(security_level))
      {
        retval = TEE_SUCCESS;
      }
    }
  }

  /*Check if any Error*/
  retval = tz_app_check_error(retval);

  QPAY_EXIT("retval=%X", retval);

  return retval;
}

#endif //  TEE_SE_API_1_1

/**
 *
 * Handles commands coming from HLOS daemon and invokes corresponding method in
 * trusted application which internally invokes GP TEE APIs.

 * @param   [in] cmd     : Pointer to the command struct coming from HLOS.
 * @param   [in] cmdlen  : Length of comamnd from HLOS.Not being used by trusted application.
 * @param   [in] rsp_ptr : Pointer to the response struct which will be returned
 *                         back to HLOS after response is filled by GP TEE SE APIs.
 * @param   [in] rsplen  : Length of response from TZ.Not being used by trusted application.
 *
 * @return  None.
 **/
void tz_app_cmd_handler(void *cmd, uint32_t cmdlen, void *rsp, uint32_t rsplen)
{
  TEE_Result retval = TEE_SUCCESS;

  tz_app_send_cmd_t *cmd_ptr = (tz_app_send_cmd_t *)cmd;
  tz_app_send_rsp_t *rsp_ptr = (tz_app_send_rsp_t *)rsp;

  QPAY_ENTER("cmd=%X, cmdlen=%d, rsp=%X, rsplen=%d", cmd, cmdlen, rsp, rsplen);

  if (cmd_ptr && rsp_ptr &&
      (cmdlen >= sizeof(tz_app_send_cmd_t)) &&      // HLOS buffers 64 byte aligned so check command buffer is big enough
      (rsplen >= sizeof(tz_app_send_rsp_t)) &&      // HLOS buffers 64 byte aligned so check response buffer is big enough
      (cmd_ptr->cmd_len <= sizeof(cmd_ptr->tApdu))) // Validate the command size fits into our command buffer
  {
    QPAY_LOG_INF("HLOS cmd_id=0x%02X, cmd_len=%d, rsp_len=%d, sessionHandle=0x%08X",
                 cmd_ptr->cmd_id, cmd_ptr->cmd_len, rsp_ptr->rsp_len, cmd_ptr->sessionHandle);

    /*Assign status byte length*/
    rsp_ptr->rsp_len = TEE_SE_STATUS_BYTE_LEN;

    switch (cmd_ptr->cmd_id)
    {
      case QPAY_OPEN_CONNECTION:
        //Initialize SE Service here and return available readers.
#ifdef TEE_SE_API_1_1
        retval = TEE_SEServiceOpen_cc(&seServiceHandle,
                                      QSEE_SPI_DEVICE_1 /* ESE defaults to BLSP1 QUP 1 */,
                                      1                 /* ESE defaults to Chip Select slave identifier of 1*/);
#else // TEE_SE_API_1_1
        retval = TEE_SEServiceOpen(&seServiceHandle);
#endif // TEE_SE_API_1_1

        break;

      case TEE_SE_SERVICE_GET_READERS:
        retval = tz_app_get_readers();
        break;

      case TEE_SE_READER_OPEN_SESSION:
        retval = tz_app_open_session(rsp_ptr);
        break;

      case TEE_SE_SESSION_OPEN_BASIC_CHANNEL:
      case TEE_SE_SESSION_OPEN_LOGICAL_CHANNEL:
        retval = tz_app_open_channel(cmd_ptr);
        break;

      case TEE_SE_CHANNEL_GET_SELECT_RESPONSE:
        retval = tz_app_channel_get_select_rsp(cmd_ptr, rsp_ptr);
        break;

      case TEE_SE_CHANNEL_TRANSMIT:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = tz_app_channel_transmit(cmd_ptr, rsp_ptr);
        }
        break;

      case TEE_SE_SESSION_ClOSE:
        retval = tz_app_session_close(cmd_ptr);
        break;

      case TEE_SE_CHANNEL_CLOSE:

        if (cmd_ptr->cmd_len != 0)
        {
          retval = tz_app_channel_close(cmd_ptr);
        }
        break;

      case TEE_SE_CHANNEL_SELECT_NEXT:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = tz_app_channel_select_next(cmd_ptr, rsp_ptr);
        }
        break;

      case QPAY_CLOSE_CONNECTION:
        TEE_SEServiceClose(seServiceHandle);
        break;

#ifdef TEE_SE_API_1_1

      case TEE_SE_CHANNEL_GET_RESPONSE_LENGTH:
        retval = tz_app_channel_get_response_length(cmd_ptr, rsp_ptr);
        break;

      case TEE_SE_SECURE_CHANNEL_OPEN:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = tz_app_secure_channel_open(cmd_ptr);
        }
        break;

      case TEE_SE_SECURE_CHANNEL_CLOSE:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = tz_app_secure_channel_close(cmd_ptr);
        }
        break;

      case TEE_SE_SECURE_CHANNEL_GET_SECURITY_LEVEL:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = tz_app_secure_channel_get_security_level(cmd_ptr, rsp_ptr);
        }
        break;
#endif // TEE_SE_API_1_1

      default:
        retval = QC_TEE_SE_FAILED;
        QPAY_LOG_INF("Unsupported command");
        break;
    }

    tz_app_get_rapdu(rsp_ptr, retval, cmd_ptr->cmd_id);
  }

  QPAY_EXIT("API Returned retval=%X, rsp_ptr->rsp_len=%d", retval, rsp_ptr ? rsp_ptr->rsp_len : 0);
}

/**
 *
 * Trusted application shut down invoked from HLOS.
 *
 * @param   void.
 *
 * @return  None.
 **/
void tz_app_shutdown(void)
{
  QPAY_ENTER();

  QPAY_EXIT();
}

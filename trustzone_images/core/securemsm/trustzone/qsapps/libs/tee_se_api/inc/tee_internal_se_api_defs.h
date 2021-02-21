#ifndef TEE_INTERNAL_SE_API_DEF_H_
#define TEE_INTERNAL_SE_API_DEF_H_
/**
   @file tee_internal_se_api_defs.h
   @brief Global defnitions used in GP TEE SE LIB.
*/

/*==========================================================================

  GP TEE SE API Defnitions header file

  Description : header file contains defnitions related to APIs.

  Copyright (c) 2015 - 2016 by Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

  ===========================================================================*/

/*===========================================================================

  Edit History


  when        who              what,                      where,     why
  --------   ---   ----------------------------------------------------------
  12/04/2016  dc   Add support for retransmission
  23/03/2016  dc   Rework session handling
  15/12/2015  dc   Add support for Secure Channel Protocol(SCP)
  18/03/2015  pm   Initial Implementation of GP TEE SE API
  07/09/2015  pm   Bug fixes.
  ===========================================================================*/
#include <stdio.h>
#include <stdbool.h>
#include <stringl.h>
#include "qsee_heap.h"
#include "qsee_log.h"
#include "qsee_ese_service.h"

/******************************** Definitions*******************************************/

#define QC_TEE_SELECT_CMD_HEADER                    5
#define QC_TEE_SPI_BUFF_MAX_SIZE                    QSEE_ESE_SERVICE_SPI_APDU_SIZE // Leave this for backward compatibility until the qpay app is updated
#define QC_TEE_STATUS_WORD_LENGTH                   2
#define QC_TEE_SELECT_NEXT_CMD_HEADER_LEN           5
#define QC_TEE_MAX_NUM_OF_SESSIONS                  10
#define QC_TEE_MAX_NUMBER_OF_CHANNELS               20
#define QC_TEE_T1_LRC_LEN                           1
#define QC_TEE_T1_HEADER_SIZE                       3
#define QC_TEE_T1_STATUS_SW1_REVERSE_OFFSET         0x03
#define QC_TEE_T1_STATUS_SW2_REVERSE_OFFSET         0x02
#define QC_TEE_T1_STATUS_SW1_MORE_DATA              0x61
#define QC_TEE_T1_STATUS_SW1_WRONG_LE_FIELD         0x6C
#define QC_TEE_T1_STATUS_SW1_SUCCESS                0x90
#define QC_TEE_T1_STATUS_SW2_SUCCESS                0x00
#define QC_TEE_T1_FRAMING_OVERHEAD                  (QC_TEE_T1_HEADER_SIZE + QC_TEE_T1_LRC_LEN)
#define QC_TEE_T1_BLOCK_MASK                        0xC0 /* Mask for the bits identifying the block type */
#define QC_TEE_T1_I_BLOCK                           0x00 /* Identifies an I-Block */
#define QC_TEE_T1_R_BLOCK                           0x80 /* Identifies an R-Block */
#define QC_TEE_T1_S_BLOCK                           0xC0 /* Identifies an S-Block */
#define QC_TEE_T1_S_BLOCK_WTX                       0xC3
#define QC_TEE_T1_CHAINING                          0x20
#define QC_TEE_T1_SINGLE_FRAME                      0x00
#define QC_TEE_T1_SINGLE_FRAME_MAX_LEN              (QSEE_ESE_SERVICE_SPI_APDU_SIZE - QC_TEE_T1_HEADER_SIZE - QC_TEE_T1_LRC_LEN)
#define QC_TEE_BASIC_CHANNEL_NUMBER                 0
#define QC_TEE_DEFAULT_BWT_MICROSECONDS             5000
#define QC_TEE_MAX_BWT_MICROSECONDS                 1624000
#define QC_TEE_MAX_APDU_SIZE                        0x10000
#define QC_TEE_READ_TRIAL_COUNT_MAX                 (QC_TEE_MAX_BWT_MICROSECONDS / QC_TEE_DEFAULT_BWT_MICROSECONDS)
#define QC_TEE_MANAGE_CHANNEL_RSP_SIZE              4
#define QC_TEE_ATR_MAX_SIZE                         20
#define QC_TEE_TRANSMIT_SEQ_0                       0
#define QC_TEE_TRANSMIT_SEQ_1                       1
#define QC_TEE_AID_MIN_LEN                          5
#define QC_TEE_AID_MAX_LEN                          16
#define QC_TEE_MIN_RSP_LEN_WITH_STATUS_BYTES        6
#define QC_TEE_MIN_CAPDU_LEN                        4
#define QC_TEE_WTX_RSP_LEN                          5

#define QC_TEE_SE_MALLOC                            qsee_zalloc
#define QC_TEE_SE_REALLOC                           qsee_realloc
#define QC_TEE_SE_FREE(ptr)                         QSEE_FREE_PTR(ptr)
#define QC_TEE_SE_ARRAY_SIZE(a)                     ((sizeof(a)) / (sizeof((a)[0])))

/*Sevcie , reader , session and cannel handles*/
typedef uint32_t   TEE_Result;
typedef struct __TEE_SEServiceHandle  *TEE_SEServiceHandle;
typedef struct __TEE_SEReaderHandle   *TEE_SEReaderHandle;
typedef struct __TEE_SESessionHandle  *TEE_SESessionHandle;
typedef struct __TEE_SEChannelHandle  *TEE_SEChannelHandle;
typedef struct __TEE_ObjectHandle     *TEE_ObjectHandle;

//Error Cases.
#define QC_TEE_SE_PANIC                     0xFFFFFFFF
#define QC_TEE_SE_PENDING_IRQ               0x00000006
#define QC_TEE_SE_PENDING_CHANNEL           0x00000007
#define QC_TEE_SE_BAD_STATE                 0x00000008
#define QC_TEE_SE_FAILED                    0x000000FF

#define TEE_SUCCESS                         0x00000000
#define TEE_ERROR_CORRUPT_OBJECT            0xF0100001
#define TEE_ERROR_CORRUPT_OBJECT_2          0xF0100002
#define TEE_ERROR_STORAGE_NOT_AVAILABLE     0xF0100003
#define TEE_ERROR_STORAGE_NOT_AVAILABLE_2   0xF0100004
#define TEE_SE_SESSION_OPEN                 0xF0240000
#define TEE_ERROR_61_SHORT_BUFFER           0xF0240001
#define TEE_ERROR_6C_SHORT_BUFFER           0xF0240002
#define TEE_ERROR_GENERIC                   0xFFFF0000
#define TEE_ERROR_ACCESS_DENIED             0xFFFF0001
#define TEE_ERROR_CANCEL                    0xFFFF0002
#define TEE_ERROR_ACCESS_CONFLICT           0xFFFF0003
#define TEE_ERROR_EXCESS_DATA               0xFFFF0004
#define TEE_ERROR_BAD_FORMAT                0xFFFF0005
#define TEE_ERROR_BAD_PARAMETERS            0xFFFF0006
#define TEE_ERROR_BAD_STATE                 0xFFFF0007
#define TEE_ERROR_ITEM_NOT_FOUND            0xFFFF0008
#define TEE_ERROR_NOT_IMPLEMENTED           0xFFFF0009
#define TEE_ERROR_NOT_SUPPORTED             0xFFFF000A
#define TEE_ERROR_NO_DATA                   0xFFFF000B
#define TEE_ERROR_OUT_OF_MEMORY             0xFFFF000C
#define TEE_ERROR_BUSY                      0xFFFF000D
#define TEE_ERROR_COMMUNICATION             0xFFFF000E
#define TEE_ERROR_SECURITY                  0xFFFF000F
#define TEE_ERROR_SHORT_BUFFER              0xFFFF0010
#define TEE_ERROR_EXTERNAL_CANCEL           0xFFFF0011
#define TEE_ERROR_OVERFLOW                  0xFFFF300F
#define TEE_ERROR_TARGET_DEAD               0xFFFF3024
#define TEE_ERROR_STORAGE_NO_SPACE          0xFFFF3041
#define TEE_ERROR_MAC_INVALID               0xFFFF3071
#define TEE_ERROR_SIGNATURE_INVALID         0xFFFF3072
#define TEE_ERROR_TIME_NOT_SET              0xFFFF5000
#define TEE_ERROR_TIME_NEEDS_RESET          0xFFFF5001

#define TEE_SE_LOG_INF(xx_fmt, ...)         QSEE_LOG(QSEE_LOG_MSG_DEBUG, "SE: %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)
#define TEE_SE_LOG_ERR(xx_fmt, ...)         QSEE_LOG(QSEE_LOG_MSG_ERROR, "SE: %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)

#define TEE_SE_ENTER(xx_fmt, ...)           QSEE_LOG(QSEE_LOG_MSG_DEBUG, "SE: Entering %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)
#define TEE_SE_EXIT(xx_fmt, ...)            QSEE_LOG(QSEE_LOG_MSG_DEBUG, "SE: Exiting %s" xx_fmt, __FUNCTION__, ##__VA_ARGS__)

/*====================================================================================================================*
 *                             Declarations                                                                           *
 *====================================================================================================================*/

// Channelselect Cmd structure buffer.
typedef struct
{
  uint8_t *buff;
  uint32_t buffLen;
} TEE_ChannelSelect;

//Reader Properties.
typedef struct
{
  bool sePresent;                             // true if an SE is present in the reader
  bool teeOnly;                               // true if this reader is only accessible via the TEE
  bool selectResponseEnable;                  // true if the response to a SELECT is available in the TEE
} TEE_SEReaderProperties;

// AID structure.
typedef struct
{
  uint8_t *buffer;                              // the value of the applet's AID
  uint32_t bufferLen;                           // length of the applet's AID
} TEE_SEAID;

//SE Service handle
struct __TEE_SEServiceHandle
{
  uint8_t              numOfReaders;
  bool                 is_connected;
  qsee_spi_device_id_t spi_device_id;
  uint8_t              spi_slave_id;
  TEE_SEReaderHandle   reader_handle;
};

//Reader handle
struct __TEE_SEReaderHandle
{
  char *reader_name; // maximum length 64 characters
  uint8_t numOfSessions;
  // SE Service handle
  TEE_SEServiceHandle service_handle;
  //session handle.
  TEE_SESessionHandle session[QC_TEE_MAX_NUM_OF_SESSIONS];
};

//Session handle
struct __TEE_SESessionHandle
{
  bool    is_closed;
  bool    isBasicChannelOpened;
  uint8_t numofChannels;
  //Reader handle
  TEE_SEChannelHandle channel[QC_TEE_MAX_NUMBER_OF_CHANNELS];
};

//Forward declaration to avoid circular header file dependencies
struct _SCPInfo_t;

//channel handle
struct __TEE_SEChannelHandle
{
  bool    is_closed;
  uint8_t channelNumber;
  TEE_SEAID AppletID;
  TEE_ChannelSelect selectRsp;
  //session handle.
  TEE_SESessionHandle sessionOfThisChannel;
  //SE service handle
  TEE_SEServiceHandle service_handle;
  //SCP Information
  struct _SCPInfo_t *scpInfo;
};

/**
 * Values for the scpType member of the TEE_SC_Params structure passed to
 * TEE_SESecureChannelOpen(), denoting the SCP type to run on the secured channel.
 */
#define TEE_SC_TYPE_SCP02                   0x00
#define TEE_SC_TYPE_SCP03                   0x01
#define TEE_SC_TYPE_SCP11a                  0x02
#define TEE_SC_TYPE_SCP11b                  0x03

/**
 * An alternbative way to define the SCP type is using an OID
 */
#define TEE_OID_SCP02                       { 0x06, 0x08, 0x2A, 0x86, 0x48, 0x86, 0xFC, 0x6B, 0x04, 0x02 }
#define TEE_OID_SCP03                       { 0x06, 0x08, 0x2A, 0x86, 0x48, 0x86, 0xFC, 0x6B, 0x04, 0x03 }
#define TEE_OID_SCP11a                      { 0x06, 0x08, 0x2A, 0x86, 0x48, 0x86, 0xFC, 0x6B, 0x04, 0x0B, 0x01 }
#define TEE_OID_SCP11b                      { 0x06, 0x08, 0x2A, 0x86, 0x48, 0x86, 0xFC, 0x6B, 0x04, 0x0B, 0x02 }

/**
 * This enumeration lists the Security Levels which can be applied for a secure channel
 *
 * @note  TEE_SC_AUTHENTICATE shall be applied if only authentication between TEE and SE
 *        is expected. The Command and Response APDUs transferred after this authentication
 *        are not secured.
 *
 * @note  A Security Level with response encryption cannot be applied on SCP '02'. If this
 *        is attempted, TEE_SESecureChannelOpen will respond with the error TEE_ERROR_BAD_PARAMETERS
 *
 * @note  SCP '11' only allows the security levels TEE_SC_CR_MAC and TEE_SC_CR_ENC_MAC. All
 *        other options will result in an error.
 */
typedef enum
{
  TEE_SC_NO_SECURE_MESSAGING = 0x00, //Nothing will be applied
  TEE_SC_AUTHENTICATE        = 0x80, //Command, Response APDU not be secured
  TEE_SC_C_MAC               = 0x01, //Command APDU shall be MAC protected
  TEE_SC_R_MAC               = 0x10, //Response APDU shall be MAC protected
  TEE_SC_CR_MAC              = 0x11, //Command, Response APDU shall be MAC protected
  TEE_SC_C_ENC_MAC           = 0x03, //Command APDU shall be encrypted and MAC protected
  TEE_SC_R_ENC_MAC           = 0x30, //Response APDU encrypted, MAC protected
  TEE_SC_CR_ENC_MAC          = 0x33  //Command, Response APDU encrypted, MAC protected
} TEE_SC_SecurityLevel;

/**
 * This enumeration lists the options for key types.
 */
typedef enum
{
  TEE_SC_BASE_KEY = 0,  // A base key acc. to SCP02
  TEE_SC_KEY_SET  = 1   // A key set (key-ENC, key-MAC) acc. to SCP02, SCP03
} TEE_SC_KeyType;

/**
 * This type defines the type of protocol which shall be used for the secure channel
 */
typedef struct __TEE_SC_OID
{
  uint8_t *buffer;    // the value of the OID
  uint32_t bufferLen; // length of the SC OID
} TEE_SC_OID;


/**
 * This type defines the reference to the card keys which shall be used for the secure channel
 */
typedef struct __TEE_SC_CardKeyRef
{
  uint8_t scKeyID;      // key identifier of the SC card key
  uint8_t scKeyVersion; // key version of the SC card key
} TEE_SC_CardKeyRef;

/**
 * This type can be used to define a key set with Key-MAC and Key-ENC according to SCP '02' and SCP '03'.
 */
typedef struct __TEE_SC_KeySetRef
{
  TEE_ObjectHandle scKeyEncHandle; // the Key-ENC (static encryption key)
  TEE_ObjectHandle scKeyMacHandle; // the Key-MAC (static MAC key)
} TEE_SC_KeySetRef;

/**
 * This type defines the reference to the device keys which shall be used for the secure channel.
 *
 * The TA has to define object handles which refer to the secure channel keys stored in the TEE.
 * The TA can obtain these object handles from its private Trusted Storage or from a certain
 * Security Domain. How a TA obtains a key object handle is defined in [TEE Core API] and in
 * TEE Administration Framework [TEE Admin].
 *
 * @note  Secure channel keys can be transient objects. The usage of transient objects is
 *        described in [TEE Core API].
 *
 * @note  The specified Key-ENC and Key-MAC must have the same type and length. Otherwise the
 *        function TEE_SESecureChannelOpen will respond with the error TEE_ERROR_BAD_PARAMETERS.
 *
 * @note  SCP '02' requires a double length DES key with 16 bytes as key value. SCP '03' requires
 *        an AES key which may have a length of 16, 24, or 32 bytes as key value. If the length of
 *        the specified key value is inconsistent with the chosen protocol or the key cannot be
 *        applied on the cryptographic algorithm, the function TEE_SESecureChannelOpen will respond
 *        with the error TEE_ERROR_BAD_PARAMETERS.
 *
 */
typedef struct __TEE_SC_DeviceKeyRef
{
  TEE_SC_KeyType      scKeyType;        // type of SC keys

  union
  {
    TEE_ObjectHandle  scBaseKeyHandle; // SC base key (acc. to SCP02)
    TEE_SC_KeySetRef  scKeySetRef;     // Key-ENC, Key-MAC (acc. to SCP02, SCP03)
  } scKeyInfo;
} TEE_SC_DeviceKeyRef;

/**
 * This type defines the parameters which are needed to set up a secure channel.
 *
 * The Secure Channel type can be specified either by defining an OID or by a constant.
 * The constant scType will apply only if scOID.buffer is set to NULL and scOID.bufferLen
 * is set to 0.
 */
typedef struct __TEE_SC_Params
{
  uint8_t               scType;           // the SC type
  TEE_SC_OID            scOID;            // the SC type defined by OID
  TEE_SC_SecurityLevel  scSecurityLevel;  // the SC security level
  TEE_SC_CardKeyRef     scCardKeyRef;     // reference to SC card keys
  TEE_SC_DeviceKeyRef   scDeviceKeyRef;   // reference to SC device keys
} TEE_SC_Params;

/**
 *
 * Prints the C-APDU and R-APDU in single byte string for debugging purpose.
 *
 * @param    [in] pBuffer: Buffer whose contents are to be printed.
 * @param    [in] length : Length of the buffer.
 * @param    [in] pMode  : Debug level string to identify logs further
 *                         e.g. TX or RX or DBG or TA(to print trusted app logs).
 *
 * @return   None.
 **/
void debugPrint(uint8_t *pBuffer, size_t length, char *pMode);

#endif /* TEE_INTERNAL_SE_API_DEF_H_ */

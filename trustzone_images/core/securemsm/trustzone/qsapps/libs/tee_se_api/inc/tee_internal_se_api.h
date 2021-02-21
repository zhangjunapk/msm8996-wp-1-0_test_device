#ifndef TEE_INTERNAL_SE_API_H_
#define TEE_INTERNAL_SE_API_H_

/**
@file tee_internal_se_api.h
@brief Global Platform specified TEE SE interface API header.
*/

/*==========================================================================

                     GP TEE SE API header file

Description
   header file for the TEE SE API

 Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

===========================================================================*/

/*===========================================================================

Edit History
  when        who   what,                  where,        why
  --------    ---   ----------------------------------------------------------
  08/12/2015  dc    Add support for Secure Channel Protocol(SCP)
  18/03/2015  pm    Header file for TEE SE API.
===========================================================================*/

#include "tee_internal_se_api_defs.h"

// Required by "GlobalPlatform Device Technology TEE Secure Element API Version 1.1"
#define TEE_SE_API_1_1

/**
 *
 * Allocates a handle for a new connection that can be used to connect to all the Secure
 * Elements available to the TEE.
 *
 * @param    [out] seServiceHandle     : Allocated handle of the service.
 *
 * @return   TEE_SUCCESS               : if valid handle has been returned.
 * @return   TEE_ERROR_ACCESS_CONFLICT : if allocated to TA already.
 * @return   TEE_ERROR_OUT_MEMORY      : if no enough resources.
**/
TEE_Result TEE_SEServiceOpen(TEE_SEServiceHandle *seServiceHandle);

/**
 *
 * Extension to TEE_SEServiceOpen to allow specification of SPI Intance and Slave ID to use
 *
 * @param [out] seServiceHandle : Allocated handle of the service.
 * @param [in]  spi_device_id   : The SPI device ID to attach to
 * @param [in]  spi_slave_id    : The Chip Select slave identifier
 *
 * @return   TEE_SUCCESS               : if valid handle has been returned.
 * @return   TEE_ERROR_ACCESS_CONFLICT : if allocated to TA already.
 * @return   TEE_ERROR_OUT_MEMORY      : if no enough resources.
 *
 * @see  TEE_SEServiceOpen
**/
TEE_Result TEE_SEServiceOpen_cc(TEE_SEServiceHandle *seServiceHandle,
                                qsee_spi_device_id_t device_id,
                                uint8_t slave_id);

/**
 *
* Releases all Secure Elements resources allocated by this seService
* handle. Should be called in TA termination method.
*
* @param    [in] seServiceHandle - Service handle to be closed.
*
* @return  Void
**/
void TEE_SEServiceClose(TEE_SEServiceHandle seServiceHandle);

/**
*
* Returns the list of available secure element reader handles.
*
* @param    [in] Reference to seService handle.
* @param    [out] Reference to seReader handle list.
* @param    [out] Length of the seReader handle list.
*
* @return   TEE_SUCCESS              : In case of success.
* @return   TEE_ERROR_ITEM_NOT_FOUND : If no reader is found.
* @return   TEE_ERROR_OUT_OF_MEMORY  : If not enough resources are available to perform the operation.
* @return   TEE_ERROR_SHORT_BUFFER   : If *SEReaderHandleListLen is too small to count all readers.
**/
TEE_Result TEE_SEServiceGetReaders(TEE_SEServiceHandle seServiceHandle,
                                   TEE_SEReaderHandle *seReaderHandleList,
                                   uint32_t *seReaderHandleListLen);

/**
*
* Returns the reader properties e.g.if an SE is present in the reader, if SE is
* connected directly to the TEE, and whether the response to a SELECT is available
* in the TEE.
*
* @param    [in]  seReaderHandle   : Reference to seReader handle
* @param    [out] readerProperties : Reference to the reader properties
*
* @return   None
**/
void TEE_SEReaderGetProperties(TEE_SEReaderHandle seReaderHandle,
                               TEE_SEReaderProperties *readerProperties);

/**
*
* Returns user-friendly name of this reader.
*
* @param    [in] seReaderHandle   : Reference to seReader handle.
* @param    [out] readerName      : buffer to return reader name.
* @param    [inout] readerNameLen : Buffer length to store reader name.
*
* @return   TEE_SUCCESS            : if operation successful.
* @return   TEE_ERROR_SHORT_BUFFER : if buffer is smaller than actual reader length.
**/
TEE_Result TEE_SEReaderGetName(TEE_SEReaderHandle seReaderHandle,
                               char *readerName,
                               uint32_t *readerNameLen);

/**
*
* Opens a session with eSE that connects to a Secure Element through TEE.Session is the link between
* TA and eSE.
*
* @param    [in] seReaderHandle   : Reference to seReader handle
* @param    [out] seSessionHandle : Reference to seSession handle
*
* @return   TEE_SUCCESS             : In case operation is successful.
* @return   TEE_ERROR_COMMUNICATION : If seReader is not able to open a session with the SE because
                                      the SE could not be powered up.(Power up is initialization).
* @return   TEE_ERROR_OUT_OF_MEMORY : If not enough resources are available to perform the operation
**/
TEE_Result TEE_SEReaderOpenSession(TEE_SEReaderHandle seReaderHandle,
                                   TEE_SESessionHandle *seSessionHandle);

/**
*
* Closes all the sessions opened on this reader. All the channels opened by all these
* sessions will be closed.
*
* @param    [in] seReaderHandle : Reference to seReader handle
*
* @return   None
**/
void TEE_SEReaderCloseSessions(TEE_SEReaderHandle seReaderHandle);

/**
*
* Description    returns the ATR of this Secure Element.
*
* @param     [in] seSessionHandle : Reference to seSession handle
* @param     [out] atr            : Output buffer containing the ATR info
* @param     [inout] atrLen       : atr buffer lentgh
*
* @return    TEE_SUCCESS              : In case of success
* @return    TEE_ERROR_COMMUNICATION  : If the ATR is not available or if there is an I/O error
* @return    TEE_ERROR_SHORT_BUFFER   : If atr buffer is too small to hold the whole session ATR
**/
TEE_Result TEE_SESessionGetATR(TEE_SESessionHandle seSessionHandle,
                               void *atr,
                               uint32_t *atrLen);

/**
*
* Returns information of session i.e. if it is open or has been closed.
*
* @param    [in] seSessionHandle : Reference to seSession handle.
*
* @return   TEE_SUCCESS             : In case of success
* @return   TEE_ERROR_COMMUNICATION : If the SE is not present or if there is an I/O error
**/
TEE_Result TEE_SESessionIsClosed(TEE_SESessionHandle seSessionHandle);

/**
*
* Closes this session opened by trusted application(TA).
*
* @param     [in] seSessionHandle : Reference to seSession handle
*
* @return   TEE_SUCCESS             : In case of success
* @return   TEE_ERROR_COMMUNICATION : If the SE is not present or if there is an I/O error
**/
void TEE_SESessionClose(TEE_SESessionHandle seSessionHandle);

/**
*
* Open basic channel(channel number 0) requested by trusted application(TA).
*
* @param     [in] seSessionHandle  : Reference to seSession handle
* @param     [in] seAID            : Reference to AID which is to be selected after
*                                    channel is opened.
* @param     [out] seChannelHandle : Reference to seChannel handle.
*
* @return    QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE service and
                                         response is pending.
* @return    TEE_ERROR_NOT_SUPPORTED   : If CAPDU sending failed or channel is already opened.
* @return    TEE_ERROR_BAD_STATE       : If the seSession is closed
* @return    TEE_ERROR_BAD_PARAMETERS  : If the seAID->bufferLen is not within 5 to 16 (inclusive) or 0
* @return    TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
**/
TEE_Result TEE_SESessionOpenBasicChannel(TEE_SESessionHandle seSessionHandle,
                                         TEE_SEAID *seAID,
                                         TEE_SEChannelHandle *seChannelHandle);

/**
*
* This API is QCOM extension to support thread yield case. So in previous
* TEE_SESessionOpenBasicChannel call either C-APDU was sent successfully
* so response is pending and TA wants to read the response back or in previous
* call channel was not free so now TA wants to send CAPDU again on same channel
* and will read response back using this API.
*
* @param     [in]  seSessionHandle  : Reference to seSession handle
* @param     [in]  seAID            : Reference to the AID with which the channel
*                                    is to be opened
* @param     [out] seChannelHandle  : Reference to seChannel handle
* @param     [in]  state            : State which was returned in previous API call.
*
* @return     QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return     QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE
*                                         service and response is pending.
* @return     TEE_ERROR_NOT_SUPPORTED   : If CAPDU sending failed or channel is already
*                                         opened.
* @return     TEE_ERROR_BAD_STATE       : If the seSession is closed.
* @return     TEE_ERROR_BAD_PARAMETERS  : If the seAID->bufferLen is not within 5 to
*                                         16 (inclusive) or 0.
* @return     TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an
*                                         I/O error.
* @return     TEE_SUCCESS               : If operation is successful and proper response
*                                         is recieved.
**/
TEE_Result TEE_SESessionOpenBasicChannel_cc(TEE_SESessionHandle seSessionHandle,
                                            TEE_SEAID *seAID,
                                            TEE_SEChannelHandle *seChannelHandle,
                                            TEE_Result state);

/**
*
* Function opens a logical channel with the Secure Element, selecting the application
* represented by the given AID.If the seAID->bufferLen is 0, which means no application is
* to be selected on this channel, the default application is used. The Secure Element
* chooses which logical channel will be used.
*
* @param    [in] seSessionHandle  : Reference to seSession handle
* @param    [in] seAID            : Reference to the AID with which the channel
*                                   is to be opened
* @param    [out] seChannelHandle : Reference to seChannel handle
*
* @return   QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return   QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE service and
                                              response is pending.
* @return   TEE_ERROR_NOT_SUPPORTED   : If CAPDU sending failed or channel is already opened.
* @return   TEE_ERROR_BAD_STATE       : If the seSession is closed
* @return   TEE_ERROR_BAD_PARAMETERS  : If the seAID->bufferLen is not within 5 to 16 (inclusive)
                                        or 0
* @return   TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error.
**/
TEE_Result TEE_SESessionOpenLogicalChannel(TEE_SESessionHandle seSessionHandle,
                                           TEE_SEAID *seAID,
                                           TEE_SEChannelHandle *seChannelHandle);

/**
*
* This API is QCOM extension to support thread yield case. So in previous
* TEE_SESessionOpenLogicalChannel either C-APDU was sent successfully
* so response is pending and TA wants to read the response back or in previous
* call channel was not free so now TA wants to send CAPDU again on same channel
* and will read response back using this API.
*
* @param   [in] seSessionHandle: Reference to seSession handle
* @param   [in] seAID: Reference to the AID with which the channel is to be opened
* @param   [out] seChannelHandle: Reference to seChannel handle
* @param   [in] state : State which was returned in previous API call.
*
* @return  QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return  QC_TEE_SE_PENDING_IRQ     : if CAPDU has been sent by eSE service and
                                              response is pending.
* @return  TEE_ERROR_NOT_SUPPORTED   : If CAPDU sending failed or channel is already opened.
* @return  TEE_ERROR_BAD_STATE       : If the seSession is closed
* @return  TEE_ERROR_BAD_PARAMETERS  : If the seAID->bufferLen is not within 5 to 16
*                                      (inclusive) or 0
* @return  TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
* @return  TEE_SUCCESS               : If operation is successful and proper response is
*                                      recieved.
**/
TEE_Result TEE_SESessionOpenLogicalChannel_cc(TEE_SESessionHandle seSessionHandle,
                                              TEE_SEAID *seAID,
                                              TEE_SEChannelHandle *seChannelHandle,
                                              TEE_Result state);

/**
*
* Performs selection of the next Applet on this channel. This method can be used
* by a device application in  order to iterate through all Applets matching to the
* same partial AID
*
* @param    [in] seChannelHandle : Reference to seChannel handle
*
* @return   QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return   QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE service and
                                        response is pending.
* @return   TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
* @return   TEE_ERROR_BAD_STATE       : If the seSession is closed
**/
TEE_Result TEE_SEChannelSelectNext(TEE_SEChannelHandle seChannelHandle);

/**
*
* This API is QCOM extension to support thread yield case. So in previous
* TEE_SEChannelSelectNext_cc either the command was sent successfully so
* response is pending and TA wants to read the response back or in previous
* call channel was not free so now TA wants to send CAPDU again on same channel
* and will read response back using this API again.
*
* @param     [in]     seChannelHandle : Reference to seChannel handle
* @param     [in,out] rsp             : Outbuf buffer which will contain response select next APDU.
* @param     [in,out] rsplen          : Response buffer length for the select next next response buffer.
* @param     [in]     state           : State which was returned in previous API call.
*
* @return     QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return     QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE
*                                         service and
* @return     TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an
*                                         I/O error
* @return     TEE_SUCCESS               : In case of success
**/
TEE_Result TEE_SEChannelSelectNext_cc(TEE_SEChannelHandle seChannelHandle,
                                      uint8_t *rsp,
                                      uint32_t *rsplen,
                                      TEE_Result state);

/*
*
* Returns response data (with status word) resulting from the SELECT response.
*
* @param   [in] seChannelHandle  : Reference to seChannel handle
* @param   [out] response        : Response buffer pointer to return SELECT response.
* @param   [inout] responseLen   : Select response buffer length
*
* @return  TEE_SUCCESS             : In case of success.
* @return  TEE_ERROR_COMMUNICATION : If the SE is not present or if there is an I/O error
* @return  TEE_ERROR_BAD_STATE     : If the seSession is closed
* @return  TEE_ERROR_NO_DATA       : If no data is available (see above)
**/
TEE_Result TEE_SEChannelGetSelectResponse(TEE_SEChannelHandle seChannelHandle,
                                          void *response,
                                          uint32_t *responseLen);

/**
*
* Function transmits an APDU command (as per [ISO 7816-4]) to the Secure Element. The underlying
* layers generate as many TPDUs as necessary to transport this entire APDU. The transport part is
* invisible from the trusted application.
*
* @param     [in] seChannelHandle : Reference to seChannel handle
* @param     [in] command         : Input buffer containing the command to be sent .
* @param     [in] commandLen      : Input command buffer length.
* @param     [out] response       : Outbuf buffer which will contain response APDU.
* @param     [inout] responseLen  : Response buffer length.
*
* @return    QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE service and
                                         response is pending.
* @return    TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
* @return    TEE_ERROR_BAD_STATE       : If the seSession is closed
* @return    TEE_ERROR_BAD_PARAMETERS  : If CAPDU is not orrectly framed.
**/
TEE_Result TEE_SEChannelTransmit(TEE_SEChannelHandle seChannelHandle,
                                 void *command,
                                 uint32_t commandLen,
                                 void *response,
                                 uint32_t *responseLen);

/**
*
* This API is QCOM extension to support thread yield case for original API. So in previous
* TEE_SEChannelTransmit call either the command was sent successfully so response is pending
* and TA wants to read the response back or in previous call channel was not free so now TA
* wants to send C-APDU again on same channel and will read response back using this API again.
*
* @param     [in] seChannelHandle : Reference to seChannel handle
* @param     [in] command         : Input buffer containing the command to send .
* @param     [in] commandLen      : Input command buffer length.
* @param     [out] response       : Outbuf buffer which will contain response APDU.
* @param     [inout] responseLen  : Response buffer length.
* @param     [in] state           : State which was returned in previous API call.
*
* @return    QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE service and
* @return    TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
* @return    TEE_ERROR_BAD_STATE       : If the seSession is closed
* @return    TEE_ERROR_BAD_PARAMETERS  : If CAPDU is not orrectly framed.
* @return    TEE_SUCCESS               : In case of success
**/
TEE_Result TEE_SEChannelTransmit_cc(TEE_SEChannelHandle seChannelHandle,
                                    void *command,
                                    uint32_t commandLen,
                                    void *response,
                                    uint32_t *responseLen,
                                    TEE_Result state);

/**
 * The TEE_SEChannelGetResponseLength function returns the actual length of response
 * data as indicated by the SE with status word '61XX' or '6CXX' resulting from a
 * transmit operation performed with TEE_SEChannelTransmit.
 *
 * This function does provide the length value gained from the status word '61XX' or '6CXX'
 * (see [ISO 7816-4]) which is received during a transmit operation with TEE_SEChannelTransmit.
 * This length value is available only if the response buffer, defined as a parameter on
 * TEE_SEChannelTransmit, was too small to perform a response handling. In such a case the
 * application has to implement the response handling by itself. Depending on the status word
 * '61XX' or '6CXX' a GET RESPONSE command has to be used to fetch the response or the command
 * has to be re-issued with the correct LE byte.
 *
 * @param   [in]     seChannelHandle : Reference to seChannel handle
 * @param   [in,out] responseLen     : Select response buffer length
 *
 * @return  TEE_SUCCESS         : In case of success
 * @return  TEE_ERROR_BAD_STATE : If the seChannel is closed
 * @return  TEE_ERROR_NO_DATA   : If no data is available (see above)
 *
 * @note  In some cases the status word information ('61XX' or '6CXX') is not available (depending
 *        on the underlying drivers and controllers) and this routine returns TEE_ERROR_NO_DATA. In
 *        such cases it is recommended to try the transaction again, increasing the response buffer
 *        to an estimated size.
 */
TEE_Result TEE_SEChannelGetResponseLength(TEE_SEChannelHandle seChannelHandle, uint32_t *responseLen);

/**
*
* Closes any channels opened on this session.The session itself is not closed.
*
* @param   [in] seSessionHandle: Reference to seSession handle
*
* @return   None
**/
void TEE_SESessionCloseChannels(TEE_SESessionHandle seSessionHandle);

/**
*
* This API is QCOM extension to support thread yield case. So in previous
* TEE_SEChannelClose either C-APDU was sent successfully so response is pending
* and TA wants to read the response back or in previous call channel was not free
* so now TA wants to send CAPDU again on same channel and will read response back
* using this API.
*
* @param   [in] seChannelHandle : Reference to seChannel handle
* @param   [in] state           : last close API status (from HLOS daemon).
*
* @return  QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other APDU.
* @return  QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE
*                                      service and response is pending.
* @return  TEE_ERROR_COMMUNICATION   : If CAPDU failed or SE is not present.
* @return  TEE_SUCCESS               : if channel is closed successfully.
**/
TEE_Result TEE_SEChannelClose_cc(TEE_SEChannelHandle seChannelHandle, TEE_Result state);

/**
*
* Function closes provided channel to the Secure Element.
*
* @param     [in]seServiceHandle : Reference to seChannel handle.
*
* @return    QC_TEE_SE_PENDING_CHANNEL : if channel is pending to process other
*                                            APDU.
* @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by
*                                            eSE service and response is pending.
* @return    TEE_ERROR_COMMUNICATION   : If CAPDU failed or SE is not present.
**/
TEE_Result TEE_SEChannelClose(TEE_SEChannelHandle seChannelHandle);

/**
 * This API establishes a secure channel to the Secure Element. This secure channel is established
 * on the communication channel which is specified by the parameter TEE_SEChannelHandle.
 *
 * Once this function is called the API starts to set up the secure channel based on the specified
 * protocol parameters. If this function returns with success the secure channel is established
 * for the defined TEE_SEChannelHandle and subsequently all APDUs transmitted based on this handle
 * with TEE_SEChannelTransmit are automatically secured (encrypted and/or MAC protected), depending
 * on the secure channel parameter options defined on TEE_SESecureChannelOpen. The secure channel
 * can be terminated with TEE_SESecureChannelClose.
 *
 * @param   [in] seChannelHandle : Reference to seChannel handle
 * @param   [in] scParams        : Reference to parameters for the Secure Channel Protocol
 *
 * @return    TEE_SUCCESS               : In case of success
 * @return    TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
 * @return    TEE_ERROR_BAD_STATE       : If the seChannel is closed
 * @return    TEE_ERROR_BAD_PARAMETERS  : If scParams includes wrongly encoded data
 * @return    TEE_ERROR_NOT_SUPPORTED   : If the scParams is not supported
 * @return    TEE_ERROR_SECURITY        : If the authentication failed or a higher Security Level is expected
 * @return    TEE_ERROR_CANCEL          : If the command has been cancelled
 * @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE
 *                                        service and response is pending.
 *
 * @note  Once a secure channel is established with TEE_SESecureChannelOpen, the command and response
 *        buffers defined by TEE_SEChannelTransmit require additional space for performing secure messaging.
 *        According to SCP '02' and SCP '03' the encryption of an APDU requires a padding of up to 16 bytes.
 *        The MAC code which is added to each message has a length of 8 bytes. Thus, an additional buffer size
 *        of up 24 bytes is required.
 *
 * @see TEE_SESecureChannelOpen_cc
 *
 */
TEE_Result TEE_SESecureChannelOpen(TEE_SEChannelHandle seChannelHandle, TEE_SC_Params *scParams);

/**
 * This API is QCOM extension to support thread yield case for the TEE_SESecureChannelOpen.
 *
 * @param   [in] seChannelHandle : Reference to seChannel handle
 * @param   [in] scParams        : Reference to parameters for the Secure Channel Protocol
 * @param   [in] state           : last close API status (from HLOS daemon).
 *
 * @return    TEE_SUCCESS               : In case of success
 * @return    TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
 * @return    TEE_ERROR_BAD_STATE       : If the seChannel is closed
 * @return    TEE_ERROR_BAD_PARAMETERS  : If scParams includes wrongly encoded data
 * @return    TEE_ERROR_NOT_SUPPORTED   : If the scParams is not supported
 * @return    TEE_ERROR_SECURITY        : If the authentication failed or a higher Security Level is expected
 * @return    TEE_ERROR_CANCEL          : If the command has been cancelled
 * @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE
 *                                        service and response is pending.
 * @see TEE_SESecureChannelOpen
 */
TEE_Result TEE_SESecureChannelOpen_cc(TEE_SEChannelHandle seChannelHandle, TEE_SC_Params *scParams, TEE_Result state);

/**
 * This API returns the Security Level which is currently established with the Secure Element on
 * the defined seChannelHandle. If the function is called when no Secure Channel is currently
 * established, the function returns NO_SECURITY_LEVEL
 *
 * @param   [in] seChannelHandle : Reference to seChannel handle
 *
 * @return  TEE_SC_SecurityLevel
 *
 * @see TEE_SC_SecurityLevel
 */
int32_t TEE_SESecureChannelGetSecurityLevel(TEE_SEChannelHandle seChannelHandle);

/**
 * This API terminates the secure channel which is currently established to the Secure Element.
 * The channel itself is not closed and can be used for further unsecured communication.
 * If the function is called with an established unsecured channel, the function call will be
 * ignored. After executing this function, all APDUs transmitted with TEE_SEChannelTransmit on
 * seChannelHandle are not secured.
 *
 * @param   [in] seChannelHandle : Reference to seChannel handle
 *
 * @return    TEE_SUCCESS               : In case of success
 * @return    TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
 * @return    TEE_ERROR_BAD_STATE       : If the seChannel is closed
 * @return    TEE_ERROR_BAD_PARAMETERS  : If scParams includes wrongly encoded data
 * @return    TEE_ERROR_NOT_SUPPORTED   : If the scParams is not supported
 * @return    TEE_ERROR_SECURITY        : If the authentication failed or a higher Security Level is expected
 * @return    TEE_ERROR_CANCEL          : If the command has been cancelled
 * @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE
 *                                        service and response is pending.
 * @see TEE_SESecureChannelClose_cc
 */
TEE_Result TEE_SESecureChannelClose(TEE_SEChannelHandle seChannelHandle);

/**
 * This API is QCOM extension to support thread yield case for the TEE_SESecureChannelClose.
 *
 * @param   [in] seChannelHandle : Reference to seChannel handle
 * @param   [in] state           : last close API status (from HLOS daemon).
 *
 * @return    TEE_SUCCESS               : In case of success
 * @return    TEE_ERROR_COMMUNICATION   : If the SE is not present or if there is an I/O error
 * @return    TEE_ERROR_BAD_STATE       : If the seChannel is closed
 * @return    TEE_ERROR_BAD_PARAMETERS  : If scParams includes wrongly encoded data
 * @return    TEE_ERROR_NOT_SUPPORTED   : If the scParams is not supported
 * @return    TEE_ERROR_SECURITY        : If the authentication failed or a higher Security Level is expected
 * @return    TEE_ERROR_CANCEL          : If the command has been cancelled
 * @return    QC_TEE_SE_PENDING_IRQ     : if basic channel CAPDU has been sent by eSE
 *                                        service and response is pending.
 *
 * @see TEE_SESecureChannelClose
 */
TEE_Result TEE_SESecureChannelClose_cc(TEE_SEChannelHandle seChannelHandle, TEE_Result state);

#endif /* TEE_INTERNAL_SE_API_H_ */

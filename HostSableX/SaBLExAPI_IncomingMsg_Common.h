/*******************************************************************************
	Filename:       SaBLExAPI_IncomingMsg_Common
	Revised:        05.07.2017 18:44:07
	Revision:       1.0

	Description:    This file contains the SaBLE-x API message definitions and prototypes

	Copyright 2017 LS Research, LLC (LSR). All rights reserved.

	IMPORTANT: Your use of this Software is limited to those specific rights
	granted under the terms of a software license agreement between the user
	who downloaded the software, his/her employer (which must be your employer)
	and LSR (the "License").  You may not use this
	Software unless you agree to abide by the terms of the License. The License
	limits your use, and you acknowledge, that the Software may not be modified,
	copied or distributed unless embedded on a Texas Instruments microcontroller
	or used solely and exclusively in conjunction with a LSR radio
	frequency transceiver, which is integrated into your product.  Other than for
	the foregoing purpose, you may not use, reproduce, copy, prepare derivative
	works of, modify, distribute, perform, display or sell this Software and/or
	its documentation for any purpose.

	YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
	PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
	INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
	NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
	TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
	NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
	LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
	INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
	OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
	OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
	(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

	Should you have any questions regarding your right to use this Software,
	contact LSR at www.lsr.com.
*******************************************************************************/

#ifndef SABLEXAPI_INCOMINGMSG_COMMON_H
#define SABLEXAPI_INCOMINGMSG_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
* INCLUDES
*/
#include "SaBLExAPITypes.h"
#include "json.h"
#include "SaBLExAPI_Shared.h"


/*********************************************************************
* EXTERNAL VARIABLES
*/
extern void (*const pProcessIncomingMsgCommon[31])(JsonNode* pMsg);


/*********************************************************************
* CONSTANTS
*/


/*********************************************************************
* TYPEDEFS
*/

typedef struct params_DebugMessageIn
{
	char*	Message;
} params_DebugMessageIn_t;

typedef struct params_ResetAlertIn
{
	uint8_t	Source;
} params_ResetAlertIn_t;

typedef struct params_LinkStatusIn
{
	uint8_t	Status;
} params_LinkStatusIn_t;

typedef struct params_RFAckIn
{
	uint8_t	Status;
} params_RFAckIn_t;

typedef struct params_ReceiveOtaDataIn
{
	char*	DataAscii;
	char*	DataHex;
	int8_t	RSSI;
} params_ReceiveOtaDataIn_t;

typedef struct results_ErrorIn
{
	int32_t	code;
	char*	message;
} results_ErrorIn_t;

typedef struct results_ModuleGoToLpmIn
{
	uint8_t	Status;
} results_ModuleGoToLpmIn_t;

typedef struct results_QueryConnectionParamsIn
{
	uint16_t	MinConnectionInterval;
	uint16_t	MaxConnectionInterval;
	uint16_t	SlaveLatency;
	uint16_t	SupervisionTimeout;
} results_QueryConnectionParamsIn_t;

typedef struct results_QueryDevBoardSensorsEnableIn
{
	bool	Enable;
} results_QueryDevBoardSensorsEnableIn_t;

typedef struct results_QueryDevBoardSensorsIn
{
	bool	S1;
	bool	S2;
	int32_t	TempSensor;
	uint8_t	AccelerometerTilt;
	uint32_t	LightSensor;
} results_QueryDevBoardSensorsIn_t;

typedef struct results_QueryFirmwareVersionIn
{
	uint8_t	Major;
	uint8_t	Minor;
	uint8_t	Month;
	uint8_t	Day;
	uint8_t	Year;
	char*	Desc;
	char*	Partnumber;
} results_QueryFirmwareVersionIn_t;

typedef struct results_QueryLpmParamsIn
{
	uint16_t	SleepTime;
	bool	WakeHost;
} results_QueryLpmParamsIn_t;

typedef struct results_QueryMacAddressIn
{
	char*	MacAddress;
} results_QueryMacAddressIn_t;

typedef struct results_QueryModuleSensorsIn
{
	int32_t	Temperature;
	uint16_t	Voltage;
} results_QueryModuleSensorsIn_t;

typedef struct results_QueryRfParamsIn
{
	uint8_t	TxPower;
} results_QueryRfParamsIn_t;

typedef struct results_QueryUartErrorEnableIn
{
	bool	Enable;
} results_QueryUartErrorEnableIn_t;

typedef struct results_ResetToFactoryDefaultsIn
{
	uint8_t	Status;
} results_ResetToFactoryDefaultsIn_t;

typedef struct results_SendOtaDataIn
{
	uint8_t	Status;
} results_SendOtaDataIn_t;

typedef struct results_SetBaudRateIn
{
	uint8_t	Status;
} results_SetBaudRateIn_t;

typedef struct results_SetConnectionParamsIn
{
	uint8_t	Status;
} results_SetConnectionParamsIn_t;

typedef struct results_SetDevBoardSensorsEnableIn
{
	uint8_t	Status;
} results_SetDevBoardSensorsEnableIn_t;

typedef struct results_SetLpmParamsIn
{
	uint8_t	Status;
} results_SetLpmParamsIn_t;

typedef struct results_SetMacAddressIn
{
	uint8_t	Status;
} results_SetMacAddressIn_t;

typedef struct results_SetRfParamsIn
{
	uint8_t	Status;
} results_SetRfParamsIn_t;

typedef struct results_SetUartErrorEnableIn
{
	uint8_t	Status;
} results_SetUartErrorEnableIn_t;

typedef struct results_SoftResetIn
{
	uint8_t	Status;
} results_SoftResetIn_t;

typedef struct results_TerminateBleConnectionIn
{
	uint8_t	Status;
} results_TerminateBleConnectionIn_t;


/*********************************************************************
* MACROS
*/


/*********************************************************************
* API FUNCTIONS
*/

/*********************************************************************
 @fn	DebugMessageIn
 *
 @brief	This message can be used for debugging during software development.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void DebugMessageIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ModuleBaudRateChangedIn
 *
 @brief	This notification is sent to the host after the baud rate has been changed on the module.  This indicates to the host that the module is ready to accept host data at the updated baud rate.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void ModuleBaudRateChangedIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ResetAlertIn
 *
 @brief	The message is sent any time the module resets so the host can identify the souce of the reset.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void ResetAlertIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	LinkStatusIn
 *
 @brief	Notification sent to the host to indicate the status of the link (connected or disconnected).
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void LinkStatusIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	RFAckIn
 *
 @brief	This notification is sent to the host to indicate whether a transmitted message was received.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void RFAckIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ModuleAwakeIn
 *
 @brief	This notification is sent to the host to indicate the module is awake and ready to receive commands.  The host should wait until this notification is received to send any other data.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void ModuleAwakeIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	WakeupHostIn
 *
 @brief	This notification should be sent to the host when it is sleeping in order to wake it up so it can receive further commands.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void WakeupHostIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ReceiveOtaDataIn
 *
 @brief	Request to send received OTA data from the module to the host.

If DataAscii is NOT null and DataHex is null (0 length), the data is in ASCII format.
If DataHex is NOT null and DataAscii is null (0 length), the data is in HEX format.
Leading zeros will be sent with hex data, thus the number of hex bytes in the string will always be even.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void ReceiveOtaDataIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ErrorIn
 *
 @brief	Error message sent if there is an issue with a message that was sent to the module:
-32601: Method not found
-32700: Parse error; This will occur if there is trouble parsing a properly framed message.
-32000: UART overrun error
-32001: UART break error
-32002: UART framing error
-32003: CRC error; This will occur if the calculated CRC does not match the CRC in the message.
-32004: Invalid param value
-32006: Invalid param length
-32007: Invalid JSON-RPC header; This will occur if the is a problem with the start of the API message.
-32008: Invalid JSON-RPC trailer; This will occur if the is a problem with the end of the API message.
-32009: Invalid operation; Check command sequence.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void ErrorIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ModuleGoToLpmIn
 *
 @brief	Response to module go to LPM request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void ModuleGoToLpmIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryConnectionParamsIn
 *
 @brief	Response to query connection params request.
Please see the CC2640 TI software developers guide for more inforamtion about the parameters in this message.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryConnectionParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryDevBoardSensorsEnableIn
 *
 @brief	Response to query dev board sensors enable request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryDevBoardSensorsEnableIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryDevBoardSensorsIn
 *
 @brief	Response to query dev board sensors request.
For more information on the sensors please see the specific sensor datasheet.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryDevBoardSensorsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryFirmwareVersionIn
 *
 @brief	Response to query firmware version request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryFirmwareVersionIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryLpmParamsIn
 *
 @brief	Response to query LPM params request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryLpmParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryMacAddressIn
 *
 @brief	Response to query MAC address request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryMacAddressIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryModuleSensorsIn
 *
 @brief	Response to query module sensors request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryModuleSensorsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryRfParamsIn
 *
 @brief	Response to query RF params request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryRfParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryUartErrorEnableIn
 *
 @brief	Response to query the enable setting of UART error messages.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryUartErrorEnableIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ResetToFactoryDefaultsIn
 *
 @brief	Response to reset to factory defaults request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void ResetToFactoryDefaultsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SendOtaDataIn
 *
 @brief	Response to send OTA data request.  The RF Ack Notification will indicate if the message was received over the air.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SendOtaDataIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetBaudRateIn
 *
 @brief	Response to the set baud rate request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetBaudRateIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetConnectionParamsIn
 *
 @brief	Response to set connection params request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetConnectionParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetDevBoardSensorsEnableIn
 *
 @brief	Response to request to enable or disable sensors on the LSR development board.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetDevBoardSensorsEnableIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetLpmParamsIn
 *
 @brief	Response to set LPM params request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetLpmParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetMacAddressIn
 *
 @brief	Response to set MAC address request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetMacAddressIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetRfParamsIn
 *
 @brief	Response to set RF params request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetRfParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetUartErrorEnableIn
 *
 @brief	Response to request enable or disable UART errror messages.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetUartErrorEnableIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SoftResetIn
 *
 @brief	Response to the soft reset request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SoftResetIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	TerminateBleConnectionIn
 *
 @brief	Response to terminate BLE connection request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void TerminateBleConnectionIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ProcessInvalidMessageCommon
 *
 @brief	This function will handle a invalid message.
 *
 @param	none
 *
 */
void ProcessInvalidMessageCommon (JsonNode* pMsg);


#ifdef __cplusplus
}
#endif

#endif /*SABLEXAPI_INCOMINGMSG_COMMON_H*/

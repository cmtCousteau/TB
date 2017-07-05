/*******************************************************************************
	Filename:       SaBLExAPI_IncomingMsg_Common
	Revised:        05.07.2017 18:44:07
	Revision:       1.0

	Description:    This file contains functions used to process API messages being received by the SaBLE-x Module.

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


/*********************************************************************
* INCLUDES
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "json.h"
#include "SaBLExAPITypes.h"
#include "SaBLExAPI_Shared.h"
#include "SaBLExAPI_IncomingMsg_Common.h"
#include "SaBLExAPI_OutgoingMsg_Common.h"
#include "SaBLExAPI_OutgoingMsg_Common.h"


/*********************************************************************
* GLOBAL VARIABLES
*/


void (*const pProcessIncomingMsgCommon[31])(JsonNode* pMsg) = {
	ProcessInvalidMessageCommon,
	DebugMessageIn,
	ModuleBaudRateChangedIn,
	ResetAlertIn,
	LinkStatusIn,
	RFAckIn,
	ModuleAwakeIn,
	WakeupHostIn,
	ReceiveOtaDataIn,
	ErrorIn,
	ModuleGoToLpmIn,
	QueryConnectionParamsIn,
	QueryDevBoardSensorsEnableIn,
	QueryDevBoardSensorsIn,
	QueryFirmwareVersionIn,
	QueryLpmParamsIn,
	QueryMacAddressIn,
	QueryModuleSensorsIn,
	QueryRfParamsIn,
	QueryUartErrorEnableIn,
	ResetToFactoryDefaultsIn,
	SendOtaDataIn,
	SetBaudRateIn,
	SetConnectionParamsIn,
	SetDevBoardSensorsEnableIn,
	SetLpmParamsIn,
	SetMacAddressIn,
	SetRfParamsIn,
	SetUartErrorEnableIn,
	SoftResetIn,
	TerminateBleConnectionIn
};

/*********************************************************************
* EXTERNAL VARIABLES
*/


/*********************************************************************
* EXTERNAL FUNCTIONS
*/


/*********************************************************************
* LOCAL FUNCTIONS
*/


/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*********************************************************************
 @fn	ProcessInvalidMessageCommon
 *
 @brief	This function will handle a invalid message.
 *
 @param	none
 *
 */
void ProcessInvalidMessageCommon (JsonNode* pMsg)
{

}


/*********************************************************************
 @fn	DebugMessageIn
 *
 @brief	This message can be used for debugging during software development.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void DebugMessageIn (JsonNode* pMsg)
{
	/* Get paramaters */
	params_DebugMessageIn_t DebugMessageParameters;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pParamater = json_find_member (pMsg, JSON_PARAMS_ID);
	JsonNode *pMessage = json_find_member (pParamater, "Message");
	DebugMessageParameters.Message = pMessage->string_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMessage);
	json_delete(pParamater);
	json_delete(pId);
}
/*********************************************************************
 @fn	ModuleBaudRateChangedIn
 *
 @brief	This notification is sent to the host after the baud rate has been changed on the module.  This indicates to the host that the module is ready to accept host data at the updated baud rate.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void ModuleBaudRateChangedIn (JsonNode* pMsg)
{

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pId);
}
/*********************************************************************
 @fn	ResetAlertIn
 *
 @brief	The message is sent any time the module resets so the host can identify the souce of the reset.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void ResetAlertIn (JsonNode* pMsg)
{
	params_ResetAlertIn_t ResetAlertParameters;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pParamater = json_find_member (pMsg, JSON_PARAMS_ID);
	JsonNode *pSource = json_find_member (pParamater, "Source");
	ResetAlertParameters.Source = pSource->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pSource);
	json_delete(pParamater);
	json_delete(pId);
}
/*********************************************************************
 @fn	LinkStatusIn
 *
 @brief	Notification sent to the host to indicate the status of the link (connected or disconnected).
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void LinkStatusIn (JsonNode* pMsg)
{
	params_LinkStatusIn_t LinkStatusParameters;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pParamater = json_find_member (pMsg, JSON_PARAMS_ID);
	JsonNode *pStatus = json_find_member (pParamater, "Status");
	LinkStatusParameters.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pParamater);
	json_delete(pId);
}
/*********************************************************************
 @fn	RFAckIn
 *
 @brief	This notification is sent to the host to indicate whether a transmitted message was received.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void RFAckIn (JsonNode* pMsg)
{
	params_RFAckIn_t RFAckParameters;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pParamater = json_find_member (pMsg, JSON_PARAMS_ID);
	JsonNode *pStatus = json_find_member (pParamater, "Status");
	RFAckParameters.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pParamater);
	json_delete(pId);
}
/*********************************************************************
 @fn	ModuleAwakeIn
 *
 @brief	This notification is sent to the host to indicate the module is awake and ready to receive commands.  The host should wait until this notification is received to send any other data.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void ModuleAwakeIn (JsonNode* pMsg)
{

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pId);
}
/*********************************************************************
 @fn	WakeupHostIn
 *
 @brief	This notification should be sent to the host when it is sleeping in order to wake it up so it can receive further commands.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void WakeupHostIn (JsonNode* pMsg)
{

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pId);
}
/*********************************************************************
 @fn	ReceiveOtaDataIn
 *
 @brief	Request to send received OTA data from the module to the host.

If DataAscii is NOT null and DataHex is null (0 length), the data is in ASCII format.
If DataHex is NOT null and DataAscii is null (0 length), the data is in HEX format.
Leading zeros will be sent with hex data, thus the number of hex bytes in the string will always be even.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void ReceiveOtaDataIn (JsonNode* pMsg)
{
	params_ReceiveOtaDataIn_t ReceiveOtaDataParameters;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pParamater = json_find_member (pMsg, JSON_PARAMS_ID);
	JsonNode *pDataAscii = json_find_member (pParamater, "DataAscii");
	ReceiveOtaDataParameters.DataAscii = pDataAscii->string_;
	JsonNode *pDataHex = json_find_member (pParamater, "DataHex");
	ReceiveOtaDataParameters.DataHex = pDataHex->string_;
	JsonNode *pRSSI = json_find_member (pParamater, "RSSI");
	ReceiveOtaDataParameters.RSSI = pRSSI->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pRSSI);
	json_delete(pDataHex);
	json_delete(pDataAscii);
	json_delete(pParamater);
	json_delete(pId);
}
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
 @param	pMsg - Pointer to Incoming Message
 *
 */
void ErrorIn (JsonNode* pMsg)
{
	results_ErrorIn_t ErrorResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pcode = json_find_member (pResult, "code");
	ErrorResults.code = pcode->number_;
	JsonNode *pmessage = json_find_member (pResult, "message");
	ErrorResults.message = pmessage->string_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pmessage);
	json_delete(pcode);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	ModuleGoToLpmIn
 *
 @brief	Response to module go to LPM request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void ModuleGoToLpmIn (JsonNode* pMsg)
{
	results_ModuleGoToLpmIn_t ModuleGoToLpmResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	ModuleGoToLpmResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryConnectionParamsIn
 *
 @brief	Response to query connection params request.
Please see the CC2640 TI software developers guide for more inforamtion about the parameters in this message.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryConnectionParamsIn (JsonNode* pMsg)
{
	results_QueryConnectionParamsIn_t QueryConnectionParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pMinConnectionInterval = json_find_member (pResult, "MinConnectionInterval");
	QueryConnectionParamsResults.MinConnectionInterval = pMinConnectionInterval->number_;
	JsonNode *pMaxConnectionInterval = json_find_member (pResult, "MaxConnectionInterval");
	QueryConnectionParamsResults.MaxConnectionInterval = pMaxConnectionInterval->number_;
	JsonNode *pSlaveLatency = json_find_member (pResult, "SlaveLatency");
	QueryConnectionParamsResults.SlaveLatency = pSlaveLatency->number_;
	JsonNode *pSupervisionTimeout = json_find_member (pResult, "SupervisionTimeout");
	QueryConnectionParamsResults.SupervisionTimeout = pSupervisionTimeout->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pSupervisionTimeout);
	json_delete(pSlaveLatency);
	json_delete(pMaxConnectionInterval);
	json_delete(pMinConnectionInterval);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryDevBoardSensorsEnableIn
 *
 @brief	Response to query dev board sensors enable request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryDevBoardSensorsEnableIn (JsonNode* pMsg)
{
	results_QueryDevBoardSensorsEnableIn_t QueryDevBoardSensorsEnableResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pEnable = json_find_member (pResult, "Enable");
	QueryDevBoardSensorsEnableResults.Enable = pEnable->bool_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pEnable);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryDevBoardSensorsIn
 *
 @brief	Response to query dev board sensors request.
For more information on the sensors please see the specific sensor datasheet.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryDevBoardSensorsIn (JsonNode* pMsg)
{
	results_QueryDevBoardSensorsIn_t QueryDevBoardSensorsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pS1 = json_find_member (pResult, "S1");
	QueryDevBoardSensorsResults.S1 = pS1->bool_;
	JsonNode *pS2 = json_find_member (pResult, "S2");
	QueryDevBoardSensorsResults.S2 = pS2->bool_;
	JsonNode *pTempSensor = json_find_member (pResult, "TempSensor");
	QueryDevBoardSensorsResults.TempSensor = pTempSensor->number_;
	JsonNode *pAccelerometerTilt = json_find_member (pResult, "AccelerometerTilt");
	QueryDevBoardSensorsResults.AccelerometerTilt = pAccelerometerTilt->number_;
	JsonNode *pLightSensor = json_find_member (pResult, "LightSensor");
	QueryDevBoardSensorsResults.LightSensor = pLightSensor->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pLightSensor);
	json_delete(pAccelerometerTilt);
	json_delete(pTempSensor);
	json_delete(pS2);
	json_delete(pS1);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryFirmwareVersionIn
 *
 @brief	Response to query firmware version request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryFirmwareVersionIn (JsonNode* pMsg)
{
	results_QueryFirmwareVersionIn_t QueryFirmwareVersionResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pMajor = json_find_member (pResult, "Major");
	QueryFirmwareVersionResults.Major = pMajor->number_;
	JsonNode *pMinor = json_find_member (pResult, "Minor");
	QueryFirmwareVersionResults.Minor = pMinor->number_;
	JsonNode *pMonth = json_find_member (pResult, "Month");
	QueryFirmwareVersionResults.Month = pMonth->number_;
	JsonNode *pDay = json_find_member (pResult, "Day");
	QueryFirmwareVersionResults.Day = pDay->number_;
	JsonNode *pYear = json_find_member (pResult, "Year");
	QueryFirmwareVersionResults.Year = pYear->number_;
	JsonNode *pDesc = json_find_member (pResult, "Desc");
	QueryFirmwareVersionResults.Desc = pDesc->string_;
	JsonNode *pPartnumber = json_find_member (pResult, "Partnumber");
	QueryFirmwareVersionResults.Partnumber = pPartnumber->string_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pPartnumber);
	json_delete(pDesc);
	json_delete(pYear);
	json_delete(pDay);
	json_delete(pMonth);
	json_delete(pMinor);
	json_delete(pMajor);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryLpmParamsIn
 *
 @brief	Response to query LPM params request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryLpmParamsIn (JsonNode* pMsg)
{
	results_QueryLpmParamsIn_t QueryLpmParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pSleepTime = json_find_member (pResult, "SleepTime");
	QueryLpmParamsResults.SleepTime = pSleepTime->number_;
	JsonNode *pWakeHost = json_find_member (pResult, "WakeHost");
	QueryLpmParamsResults.WakeHost = pWakeHost->bool_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pWakeHost);
	json_delete(pSleepTime);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryMacAddressIn
 *
 @brief	Response to query MAC address request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryMacAddressIn (JsonNode* pMsg)
{
	results_QueryMacAddressIn_t QueryMacAddressResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pMacAddress = json_find_member (pResult, "MacAddress");
	QueryMacAddressResults.MacAddress = pMacAddress->string_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMacAddress);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryModuleSensorsIn
 *
 @brief	Response to query module sensors request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryModuleSensorsIn (JsonNode* pMsg)
{
	results_QueryModuleSensorsIn_t QueryModuleSensorsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pTemperature = json_find_member (pResult, "Temperature");
	QueryModuleSensorsResults.Temperature = pTemperature->number_;
	JsonNode *pVoltage = json_find_member (pResult, "Voltage");
	QueryModuleSensorsResults.Voltage = pVoltage->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pVoltage);
	json_delete(pTemperature);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryRfParamsIn
 *
 @brief	Response to query RF params request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryRfParamsIn (JsonNode* pMsg)
{
	results_QueryRfParamsIn_t QueryRfParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pTxPower = json_find_member (pResult, "TxPower");
	QueryRfParamsResults.TxPower = pTxPower->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pTxPower);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryUartErrorEnableIn
 *
 @brief	Response to query the enable setting of UART error messages.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryUartErrorEnableIn (JsonNode* pMsg)
{
	results_QueryUartErrorEnableIn_t QueryUartErrorEnableResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pEnable = json_find_member (pResult, "Enable");
	QueryUartErrorEnableResults.Enable = pEnable->bool_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pEnable);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	ResetToFactoryDefaultsIn
 *
 @brief	Response to reset to factory defaults request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void ResetToFactoryDefaultsIn (JsonNode* pMsg)
{
	results_ResetToFactoryDefaultsIn_t ResetToFactoryDefaultsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	ResetToFactoryDefaultsResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SendOtaDataIn
 *
 @brief	Response to send OTA data request.  The RF Ack Notification will indicate if the message was received over the air.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SendOtaDataIn (JsonNode* pMsg)
{
	results_SendOtaDataIn_t SendOtaDataResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SendOtaDataResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetBaudRateIn
 *
 @brief	Response to the set baud rate request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetBaudRateIn (JsonNode* pMsg)
{
	results_SetBaudRateIn_t SetBaudRateResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetBaudRateResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetConnectionParamsIn
 *
 @brief	Response to set connection params request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetConnectionParamsIn (JsonNode* pMsg)
{
	results_SetConnectionParamsIn_t SetConnectionParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetConnectionParamsResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetDevBoardSensorsEnableIn
 *
 @brief	Response to request to enable or disable sensors on the LSR development board.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetDevBoardSensorsEnableIn (JsonNode* pMsg)
{
	results_SetDevBoardSensorsEnableIn_t SetDevBoardSensorsEnableResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetDevBoardSensorsEnableResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetLpmParamsIn
 *
 @brief	Response to set LPM params request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetLpmParamsIn (JsonNode* pMsg)
{
	results_SetLpmParamsIn_t SetLpmParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetLpmParamsResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetMacAddressIn
 *
 @brief	Response to set MAC address request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetMacAddressIn (JsonNode* pMsg)
{
	results_SetMacAddressIn_t SetMacAddressResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetMacAddressResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetRfParamsIn
 *
 @brief	Response to set RF params request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetRfParamsIn (JsonNode* pMsg)
{
	results_SetRfParamsIn_t SetRfParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetRfParamsResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetUartErrorEnableIn
 *
 @brief	Response to request enable or disable UART errror messages.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetUartErrorEnableIn (JsonNode* pMsg)
{
	results_SetUartErrorEnableIn_t SetUartErrorEnableResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetUartErrorEnableResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SoftResetIn
 *
 @brief	Response to the soft reset request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SoftResetIn (JsonNode* pMsg)
{
	results_SoftResetIn_t SoftResetResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SoftResetResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	TerminateBleConnectionIn
 *
 @brief	Response to terminate BLE connection request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void TerminateBleConnectionIn (JsonNode* pMsg)
{
	results_TerminateBleConnectionIn_t TerminateBleConnectionResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	TerminateBleConnectionResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}


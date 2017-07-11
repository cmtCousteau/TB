/*******************************************************************************
	Filename:       SaBLExAPI_OutgoingMsg_Common
	Revised:        05.07.2017 18:44:07
	Revision:       1.0

	Description:    This file contains functions used to generate API messages being transmitted by the SaBLE-x Module.

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
#include "SaBLExAPI_Shared.h"
#include "SaBLExAPI_OutgoingMsg_Common.h"
#include "rs232.h"


/*********************************************************************
* GLOBAL VARIABLES
*/


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
 @fn	QueryDevBoardSensorsEnableOut
 *
 @brief	Request to query the enable setting of sensors on the LSR development board.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryDevBoardSensorsEnableOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryDevBoardSensorsEnable"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryDevBoardSensorsOut
 *
 @brief	Request to query all of the dev board sensor values.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryDevBoardSensorsOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryDevBoardSensors"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryFirmwareVersionOut
 *
 @brief	Request to query the module firmware version.

 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryFirmwareVersionOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryFirmwareVersion"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryMacAddressOut
 *
 @brief	Request to query the BLE MAC address.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryMacAddressOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryMacAddress"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryModuleSensorsOut
 *
 @brief	Request to query the internal sensors on the SaBLE-x module.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryModuleSensorsOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryModuleSensors"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryRfParamsOut
 *
 @brief	Request to query RF parameters.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryRfParamsOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryRfParams"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryUartErrorEnableOut
 *
 @brief	Request to query the enable setting of UART error messages.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryUartErrorEnableOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryUartErrorEnable"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	ResetToFactoryDefaultsOut
 *
 @brief	Resets the following messages to factory defaults: 
-Peripheral LED Behavior
-RF Params
-Advertising Enable
-Advertising Params
-Connection Params
-LPM Params
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void ResetToFactoryDefaultsOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("ResetToFactoryDefaults"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SetBaudRateOut
 *
 @brief	Request to set the UART baudrate of the module.  This is automatically saved to NV memory.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetBaudRateOut - Point to structure that represent the message.
 *
 */
void SetBaudRateOut (uint8_t u8MsgId, params_SetBaudRateOut_t* params_SetBaudRateOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "Baudrate", json_mknumber(params_SetBaudRateOut->Baudrate));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetBaudRate"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SetDevBoardSensorsEnableOut
 *
 @brief	Request to enable or disable sensors on the LSR development board.  Enabling initializes the I2C peripheral and all the dev board sensors.  Disabling shuts of the I2C peripheral and sets the pins as inputs with internal pull up resistors.

I2C peripheral uses DIO2 (SaBLE-x pin 17) and DIO3 (SaBLE-x pin 16).
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetDevBoardSensorsEnableOut - Point to structure that represent the message.
 *
 */
void SetDevBoardSensorsEnableOut (uint8_t u8MsgId, params_SetDevBoardSensorsEnableOut_t* params_SetDevBoardSensorsEnableOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "Enable", json_mkbool(params_SetDevBoardSensorsEnableOut->Enable));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetDevBoardSensorsEnableOut->SaveToNv));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetDevBoardSensorsEnable"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SetMacAddressOut
 *
 @brief	Request to set the BLE MAC address.  This is automatically save to NV memory.
Setting the MAC address to ff:ff:ff:ff:ff:ff will restore the modules fused MAC address.
This command will cause the device to reset.

 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetMacAddressOut - Point to structure that represent the message.
 *
 */
void SetMacAddressOut (uint8_t u8MsgId, params_SetMacAddressOut_t* params_SetMacAddressOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "MacAddress", json_mkstring(params_SetMacAddressOut->MacAddress));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetMacAddress"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SetRfParamsOut
 *
 @brief	Request to set the module RF parameters.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetRfParamsOut - Point to structure that represent the message.
 *
 */
void SetRfParamsOut (uint8_t u8MsgId, params_SetRfParamsOut_t* params_SetRfParamsOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "TxPower", json_mknumber(params_SetRfParamsOut->TxPower));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetRfParamsOut->SaveToNv));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetRfParams"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SetUartErrorEnableOut
 *
 @brief	Request to enable or disable UART error messages.  This includes UART hardware and parsing errors.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetUartErrorEnableOut - Point to structure that represent the message.
 *
 */
void SetUartErrorEnableOut (uint8_t u8MsgId, params_SetUartErrorEnableOut_t* params_SetUartErrorEnableOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "Enable", json_mkbool(params_SetUartErrorEnableOut->Enable));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetUartErrorEnableOut->SaveToNv));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetUartErrorEnable"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SoftResetOut
 *
 @brief	Request to reset the SaBLE-x by writing the SYSRESET bit in RESETCTL register. 
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void SoftResetOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SoftReset"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryConnectionParamsOut
 *
 @brief	Request to query the connection parameters for the BLE link.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryConnectionParamsOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryConnectionParams"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SetConnectionParamsOut
 *
 @brief	Request to set the connection parameters for the BLE link.
Please see the CC2640 TI software developers guide for more information about the parameters in this message.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetConnectionParamsOut - Point to structure that represent the message.
 *
 */
void SetConnectionParamsOut (uint8_t u8MsgId, params_SetConnectionParamsOut_t* params_SetConnectionParamsOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "MinConnectionInterval", json_mknumber(params_SetConnectionParamsOut->MinConnectionInterval));
	json_append_member(pParam, "MaxConnectionInterval", json_mknumber(params_SetConnectionParamsOut->MaxConnectionInterval));
	json_append_member(pParam, "SlaveLatency", json_mknumber(params_SetConnectionParamsOut->SlaveLatency));
	json_append_member(pParam, "SupervisionTimeout", json_mknumber(params_SetConnectionParamsOut->SupervisionTimeout));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetConnectionParamsOut->SaveToNv));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetConnectionParams"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	TerminateBleConnectionOut
 *
 @brief	Request to terminate (disconnect) the established BLE connection.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void TerminateBleConnectionOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("TerminateBleConnection"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SendOtaDataOut
 *
 @brief	Request to send OTA data via the LSR Serial Profile.

The following rules apply:
If both parameters below are null (0 length), the module will return an error.
If both parameters below are NOT null (length > 0), the module will return an error.
If DataAscii is NOT null and DataHex is null (0 length), the DataAscii message will be sent.
If DataHex is NOT null and DataAscii is null (0 length), the DataHex message will be sent.
Leading zeros are required for hex data.  Hex data must be an even number of bytes.

A characteristic will be set in the BLE Profile to indicate what format is being used so the receiving side knows how to interpret the data.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SendOtaDataOut - Point to structure that represent the message.
 *
 */
void SendOtaDataOut (uint8_t u8MsgId, params_SendOtaDataOut_t* params_SendOtaDataOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "DataAscii", json_mkstring(params_SendOtaDataOut->DataAscii));
	json_append_member(pParam, "DataHex", json_mkstring(params_SendOtaDataOut->DataHex));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SendOtaData"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */
        UartProcessor_WriteTxMessage(pTemp);
	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	ModuleGoToLpmOut
 *
 @brief	Request to send the module into low power mode.
Standby consumes about 1uA and retains RAM, therefore after wakeup the module is ready to operate.
Shutdown consumes about 0.1uA, but does not retain RAM, and therefore takes longer to wakeup.

When the timeout occurs the module shuts off the UART and makes the UART receive pin a input with interrupt so the module can be woken up with a 'Wakeup Module Notification'.

The heartbeat LED will continue to flash, if enabled.

On wakeup the module will send a 'Module Awake Notification' if standby mode is selected. 
On wakeup the module will send a 'Reset Alert Notification' if shutdown mode is selected. 
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_ModuleGoToLpmOut - Point to structure that represent the message.
 *
 */
void ModuleGoToLpmOut (uint8_t u8MsgId, params_ModuleGoToLpmOut_t* params_ModuleGoToLpmOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "Mode", json_mknumber(params_ModuleGoToLpmOut->Mode));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("ModuleGoToLpm"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	QueryLpmParamsOut
 *
 @brief	Request to query the LPM params.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryLpmParamsOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryLpmParams"));
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	SetLpmParamsOut
 *
 @brief	Request to set the low power mode parameters.

When the timeout occurs the module shuts off the UART and makes the UART receive pin a input with interrupt so the module can be woken up with a 'Wakeup Module Notification'.

The heartbeat LED will continue to flash, if enabled.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetLpmParamsOut - Point to structure that represent the message.
 *
 */
void SetLpmParamsOut (uint8_t u8MsgId, params_SetLpmParamsOut_t* params_SetLpmParamsOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "SleepTime", json_mknumber(params_SetLpmParamsOut->SleepTime));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetLpmParamsOut->SaveToNv));
	json_append_member(pParam, "WakeHost", json_mkbool(params_SetLpmParamsOut->WakeHost));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetLpmParams"));
	json_append_member (pMsg, JSON_PARAMS_ID, pParam);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

        UartProcessor_WriteTxMessage(pTemp);
        
	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pParam);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	ErrorOut
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
 @param	u8MsgId - Id of the Received Message
 @param	msgIdNull - Set to true if the MsgId will be sent as null
 @param	params_ErrorOut - Point to structure that represent the message.
 *
 */
void ErrorOut (uint8_t u8MsgId, bool msgIdNull, params_ErrorOut_t* params_ErrorOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pResult = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pResult, "code", json_mknumber(params_ErrorOut->code));
	json_append_member(pResult, "message", json_mkstring(params_ErrorOut->message));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_ERROR_ID, pResult);
	if (msgIdNull == true)
	{
		json_append_member (pMsg, JSON_ID, json_mknull());
	}
	else
	{
		json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	}
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pResult);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	ReceiveOtaDataOut
 *
 @brief	Response to receive OTA data request.
 *
 @param	u8MsgId - Id of the Received Message
 @param	results_ReceiveOtaDataOut - Point to structure that represent the message.
 *
 */
void ReceiveOtaDataOut (uint8_t u8MsgId, results_ReceiveOtaDataOut_t* results_ReceiveOtaDataOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pResult = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pResult, "Status", json_mknumber(results_ReceiveOtaDataOut->Status));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_RESULT_ID, pResult);
	json_append_member (pMsg, JSON_ID, json_mknumber(u8MsgId));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pResult);
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	HostAwake
 *
 @brief	This notification is sent to the module to indicate the host is awake and ready to receive commands.  The module should wait until this notification is received to send any other data.
 *
 @param	none
 *
 */
void HostAwakeOut ()
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("HostAwake"));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

        UartProcessor_WriteTxMessage(pTemp);
        
	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}


/*********************************************************************
 @fn	WakeupModule
 *
 @brief	This notification should be sent to the module when it is sleeping in order to wake it up so it can receive further commands.
 *
 @param	none
 *
 */
void WakeupModuleOut ()
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("WakeupModule"));
	char* pTemp = json_stringify (pMsg, NULL);

	/* # App Code Start # */
	/* Send pTemp out UART */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pMsg);
	free(pTemp);
}




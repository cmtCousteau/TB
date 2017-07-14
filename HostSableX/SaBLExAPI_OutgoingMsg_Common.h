/*******************************************************************************
	Filename:       SaBLExAPI_OutgoingMsg_Common
	Revised:        05.07.2017 18:44:07
	Revision:       1.0

	Description:    This file contains the SaBLE-x API outgoing message definitions and prototypes

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

#ifndef SABLEXAPI_OUTGOINGMSG_COMMON_H
#define SABLEXAPI_OUTGOINGMSG_COMMON_H

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


/*********************************************************************
* CONSTANTS
*/


/*********************************************************************
* TYPEDEFS
*/

typedef struct params_SetBaudRateOut
{
	uint32_t	Baudrate;
} params_SetBaudRateOut_t;

typedef struct params_SetDevBoardSensorsEnableOut
{
	bool	Enable;
	bool	SaveToNv;
} params_SetDevBoardSensorsEnableOut_t;

typedef struct params_SetMacAddressOut
{
	char*	MacAddress;
} params_SetMacAddressOut_t;

typedef struct params_SetRfParamsOut
{
	uint8_t	TxPower;
	bool	SaveToNv;
} params_SetRfParamsOut_t;

typedef struct params_SetUartErrorEnableOut
{
	bool	Enable;
	bool	SaveToNv;
} params_SetUartErrorEnableOut_t;

typedef struct params_SetConnectionParamsOut
{
	uint16_t	MinConnectionInterval;
	uint16_t	MaxConnectionInterval;
	uint16_t	SlaveLatency;
	uint16_t	SupervisionTimeout;
	bool	SaveToNv;
} params_SetConnectionParamsOut_t;

typedef struct params_SendOtaDataOut
{
	char*	DataAscii;
	char*	DataHex;
} params_SendOtaDataOut_t;

typedef struct params_ModuleGoToLpmOut
{
	uint8_t	Mode;
} params_ModuleGoToLpmOut_t;

typedef struct params_SetLpmParamsOut
{
	uint16_t	SleepTime;
	bool	SaveToNv;
	bool	WakeHost;
} params_SetLpmParamsOut_t;

typedef struct params_ErrorOut
{
	int32_t	code;
	char*	message;
} params_ErrorOut_t;

typedef struct results_ReceiveOtaDataOut
{
	uint8_t	Status;
} results_ReceiveOtaDataOut_t;


/*********************************************************************
* MACROS
*/


/*********************************************************************
* API FUNCTIONS
*/

/*********************************************************************
 @fn	QueryDevBoardSensorsEnableOut
 *
 @brief	Request to query the enable setting of sensors on the LSR development board.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryDevBoardSensorsEnableOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	QueryDevBoardSensorsOut
 *
 @brief	Request to query all of the dev board sensor values.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryDevBoardSensorsOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	QueryFirmwareVersionOut
 *
 @brief	Request to query the module firmware version.

 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryFirmwareVersionOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	QueryMacAddressOut
 *
 @brief	Request to query the BLE MAC address.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryMacAddressOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	QueryModuleSensorsOut
 *
 @brief	Request to query the internal sensors on the SaBLE-x module.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryModuleSensorsOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	QueryRfParamsOut
 *
 @brief	Request to query RF parameters.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryRfParamsOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	QueryUartErrorEnableOut
 *
 @brief	Request to query the enable setting of UART error messages.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryUartErrorEnableOut ( uint8_t u8MsgId);
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
 @param	uint8_t u8MsgId - Message Id
 *
 */
void ResetToFactoryDefaultsOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	SetBaudRateOut
 *
 @brief	Request to set the UART baudrate of the module.  This is automatically saved to NV memory.
 *
 @param	uint8_t u8MsgId - Message Id
 @param	params_SetBaudRateOut - Point to structure that represent the message.
 *
 */
void SetBaudRateOut ( uint8_t u8MsgId, params_SetBaudRateOut_t* params_SetBaudRateOut);
/*********************************************************************
 @fn	SetDevBoardSensorsEnableOut
 *
 @brief	Request to enable or disable sensors on the LSR development board.  Enabling initializes the I2C peripheral and all the dev board sensors.  Disabling shuts of the I2C peripheral and sets the pins as inputs with internal pull up resistors.

I2C peripheral uses DIO2 (SaBLE-x pin 17) and DIO3 (SaBLE-x pin 16).
 *
 @param	uint8_t u8MsgId - Message Id
 @param	params_SetDevBoardSensorsEnableOut - Point to structure that represent the message.
 *
 */
void SetDevBoardSensorsEnableOut ( uint8_t u8MsgId, params_SetDevBoardSensorsEnableOut_t* params_SetDevBoardSensorsEnableOut);
/*********************************************************************
 @fn	SetMacAddressOut
 *
 @brief	Request to set the BLE MAC address.  This is automatically save to NV memory.
Setting the MAC address to ff:ff:ff:ff:ff:ff will restore the modules fused MAC address.
This command will cause the device to reset.

 *
 @param	uint8_t u8MsgId - Message Id
 @param	params_SetMacAddressOut - Point to structure that represent the message.
 *
 */
void SetMacAddressOut ( uint8_t u8MsgId, params_SetMacAddressOut_t* params_SetMacAddressOut);
/*********************************************************************
 @fn	SetRfParamsOut
 *
 @brief	Request to set the module RF parameters.
 *
 @param	uint8_t u8MsgId - Message Id
 @param	params_SetRfParamsOut - Point to structure that represent the message.
 *
 */
void SetRfParamsOut ( uint8_t u8MsgId, params_SetRfParamsOut_t* params_SetRfParamsOut);
/*********************************************************************
 @fn	SetUartErrorEnableOut
 *
 @brief	Request to enable or disable UART error messages.  This includes UART hardware and parsing errors.
 *
 @param	uint8_t u8MsgId - Message Id
 @param	params_SetUartErrorEnableOut - Point to structure that represent the message.
 *
 */
void SetUartErrorEnableOut ( uint8_t u8MsgId, params_SetUartErrorEnableOut_t* params_SetUartErrorEnableOut);
/*********************************************************************
 @fn	SoftResetOut
 *
 @brief	Request to reset the SaBLE-x by writing the SYSRESET bit in RESETCTL register. 
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void SoftResetOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	QueryConnectionParamsOut
 *
 @brief	Request to query the connection parameters for the BLE link.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryConnectionParamsOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	SetConnectionParamsOut
 *
 @brief	Request to set the connection parameters for the BLE link.
Please see the CC2640 TI software developers guide for more information about the parameters in this message.
 *
 @param	uint8_t u8MsgId - Message Id
 @param	params_SetConnectionParamsOut - Point to structure that represent the message.
 *
 */
void SetConnectionParamsOut ( uint8_t u8MsgId, params_SetConnectionParamsOut_t* params_SetConnectionParamsOut);
/*********************************************************************
 @fn	TerminateBleConnectionOut
 *
 @brief	Request to terminate (disconnect) the established BLE connection.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void TerminateBleConnectionOut ( uint8_t u8MsgId);
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
 @param	uint8_t u8MsgId - Message Id
 @param	params_SendOtaDataOut - Point to structure that represent the message.
 *
 */
void SendOtaDataOut ( uint8_t u8MsgId, params_SendOtaDataOut_t* params_SendOtaDataOut);
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
 @param	uint8_t u8MsgId - Message Id
 @param	params_ModuleGoToLpmOut - Point to structure that represent the message.
 *
 */
void ModuleGoToLpmOut ( uint8_t u8MsgId, params_ModuleGoToLpmOut_t* params_ModuleGoToLpmOut);
/*********************************************************************
 @fn	QueryLpmParamsOut
 *
 @brief	Request to query the LPM params.
 *
 @param	uint8_t u8MsgId - Message Id
 *
 */
void QueryLpmParamsOut ( uint8_t u8MsgId);
/*********************************************************************
 @fn	SetLpmParamsOut
 *
 @brief	Request to set the low power mode parameters.

When the timeout occurs the module shuts off the UART and makes the UART receive pin a input with interrupt so the module can be woken up with a 'Wakeup Module Notification'.

The heartbeat LED will continue to flash, if enabled.
 *
 @param	uint8_t u8MsgId - Message Id
 @param	params_SetLpmParamsOut - Point to structure that represent the message.
 *
 */
void SetLpmParamsOut ( uint8_t u8MsgId, params_SetLpmParamsOut_t* params_SetLpmParamsOut);
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
 @param	uint8_t u8MsgId - Message Id
 @param	msgIdNull - Set to true if the MsgId will be sent as null
 @param	params_ErrorOut - Point to structure that represent the message.
 *
 */
void ErrorOut ( uint8_t u8MsgId, bool msgIdNull, params_ErrorOut_t* params_ErrorOut);
/*********************************************************************
 @fn	ReceiveOtaDataOut
 *
 @brief	Response to receive OTA data request.
 *
 @param	uint8_t u8MsgId - Message Id
 @param	results_ReceiveOtaDataOut - Point to structure that represent the message.
 *
 */
void ReceiveOtaDataOut ( uint8_t u8MsgId, results_ReceiveOtaDataOut_t* results_ReceiveOtaDataOut);
/*********************************************************************
 @fn	HostAwakeOut
 *
 @brief	This notification is sent to the module to indicate the host is awake and ready to receive commands.  The module should wait until this notification is received to send any other data.
 *
 @param	none
 *
 */
void HostAwakeOut ();
/*********************************************************************
 @fn	WakeupModuleOut
 *
 @brief	This notification should be sent to the module when it is sleeping in order to wake it up so it can receive further commands.
 *
 @param	none
 *
 */
void WakeupModuleOut ();

#ifdef __cplusplus
}
#endif

#endif /*SABLEXAPI_OUTGOINGMSG_COMMON_H*/

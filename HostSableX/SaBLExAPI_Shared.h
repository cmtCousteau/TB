/*******************************************************************************
	Filename:       SaBLExAPI_Shared
	Revised:        05.07.2017 18:44:06
	Revision:       1.0

	Description:    This file contains shared functions for the SaBLE-x API

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

#ifndef SABLEXAPI_SHARED_H
#define SABLEXAPI_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
* CONSTANTS
*/
#define JSON_HEADER_STRING "jsonrpc"
#define JSON_HEADER_VALUE "2.0"
#define JSON_ID "id"
#define JSON_RESULT_ID "result"
#define JSON_PARAMS_ID "params"
#define JSON_METHOD_ID "method"
#define JSON_ERROR_ID "error"
#define JSON_CODE_ID "code"
#define JSON_MESSAGE_ID "message"
#define INVALID_PARAM_VAL "Invalid Parameter Val"
#define INVALID_PARAM_LENGTH "Invalid Parameter Len"
#define PARSE_ERROR -32700
#define CRC_ERROR -32003
#define OVERRUN_ERROR -32000
#define BREAK_ERROR -32001
#define FRAMING_ERROR -32002
#define METHOD_NOT_FOUND -32601
#define PARAM_VAL -32004
#define PARAM_LEN -32006
#define INVALID_HEADER -32007
#define INVALID_TRAILER -32008
#define INVALID_OPERATION -32009


/*********************************************************************
* TYPEDEFS
*/

typedef enum Peripheral_UARTIncomingMsgIndex
{
	Peripheral_invalidMsg_Index = 0,
	QueryAdvertisingEnableIn_Index,
	QueryAdvertisingParamsIn_Index,
	QueryPeripheralLedBehaviorIn_Index,
	SetAdvertisingEnableIn_Index,
	SetAdvertisingParamsIn_Index,
	SetPeripheralLedBehaviorIn_Index
} Peripheral_UARTIncomingMsgIndex_t;

typedef enum Common_UARTIncomingMsgIndex
{
	Common_invalidMsg_Index = 0,
	DebugMessageIn_Index,
	ModuleBaudRateChangedIn_Index,
	ResetAlertIn_Index,
	LinkStatusIn_Index,
	RFAckIn_Index,
	ModuleAwakeIn_Index,
	WakeupHostIn_Index,
	ReceiveOtaDataIn_Index,
	ErrorIn_Index,
	ModuleGoToLpmIn_Index,
	QueryConnectionParamsIn_Index,
	QueryDevBoardSensorsEnableIn_Index,
	QueryDevBoardSensorsIn_Index,
	QueryFirmwareVersionIn_Index,
	QueryLpmParamsIn_Index,
	QueryMacAddressIn_Index,
	QueryModuleSensorsIn_Index,
	QueryRfParamsIn_Index,
	QueryUartErrorEnableIn_Index,
	ResetToFactoryDefaultsIn_Index,
	SendOtaDataIn_Index,
	SetBaudRateIn_Index,
	SetConnectionParamsIn_Index,
	SetDevBoardSensorsEnableIn_Index,
	SetLpmParamsIn_Index,
	SetMacAddressIn_Index,
	SetRfParamsIn_Index,
	SetUartErrorEnableIn_Index,
	SoftResetIn_Index,
	TerminateBleConnectionIn_Index
} Common_UARTIncomingMsgIndex_t;

typedef enum Central_UARTIncomingMsgIndex
{
	Central_invalidMsg_Index = 0,
	AdvertisingDataReceivedIn_Index,
	ScanCompleteIn_Index,
	ScanResponseDataReceivedIn_Index,
	ConnectToDeviceIn_Index,
	QueryCentralLedBehaviorIn_Index,
	QueryScanParamsIn_Index,
	ScanIn_Index,
	SetCentralLedBehaviorIn_Index,
	SetScanParamsIn_Index
} Central_UARTIncomingMsgIndex_t;

typedef enum MessageNamespace
{
	Peripheral = 0,
	Common,
	Central
} MessageNamespace_t;


/*********************************************************************
* PUBLIC FUNCTIONS
*/
void SendJsonErrorMessage(int err);


/*********************************************************************
 @fn	GetIncomingMsgIndex
 *
 @brief	This function will get the appropriate message index from the function pointer table.
 *
 @param	char* - pointer to JSON message name.
 @param	MessageNamespace_t* - pointer to JSON message namespace.
 *
 */
uint8_t GetIncomingMsgIndex ( char*,  MessageNamespace_t*);

#ifdef __cplusplus
}
#endif

#endif /*SABLEXAPI_SHARED_H*/

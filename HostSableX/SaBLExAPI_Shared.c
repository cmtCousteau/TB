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


/*********************************************************************
* INCLUDES
*/
#include <string.h>
#include <stdint.h>
#include "SaBLExAPI_Shared.h"


/*********************************************************************
 @fn	GetIncomingMsgIndex
 *
 @brief	This function will get the appropriate message index from the function pointer table.
 *
 @param	char* - Pointer to JSON message name
 *
 */
uint8_t GetIncomingMsgIndex (char* pMethodName, MessageNamespace_t* messageNamespace)
{
	Peripheral_UARTIncomingMsgIndex_t PeripheralMsgIndex;
	Common_UARTIncomingMsgIndex_t CommonMsgIndex;
	Central_UARTIncomingMsgIndex_t CentralMsgIndex;

	if (0 == strcmp("QueryAdvertisingEnable", pMethodName))
	{
		*messageNamespace = Peripheral;
		PeripheralMsgIndex = QueryAdvertisingEnableIn_Index;
	}
	else if (0 == strcmp("QueryAdvertisingParams", pMethodName))
	{
		*messageNamespace = Peripheral;
		PeripheralMsgIndex = QueryAdvertisingParamsIn_Index;
	}
	else if (0 == strcmp("QueryPeripheralLedBehavior", pMethodName))
	{
		*messageNamespace = Peripheral;
		PeripheralMsgIndex = QueryPeripheralLedBehaviorIn_Index;
	}
	else if (0 == strcmp("SetAdvertisingEnable", pMethodName))
	{
		*messageNamespace = Peripheral;
		PeripheralMsgIndex = SetAdvertisingEnableIn_Index;
	}
	else if (0 == strcmp("SetAdvertisingParams", pMethodName))
	{
		*messageNamespace = Peripheral;
		PeripheralMsgIndex = SetAdvertisingParamsIn_Index;
	}
	else if (0 == strcmp("SetPeripheralLedBehavior", pMethodName))
	{
		*messageNamespace = Peripheral;
		PeripheralMsgIndex = SetPeripheralLedBehaviorIn_Index;
	}
	else if (0 == strcmp("DebugMessage", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = DebugMessageIn_Index;
	}
	else if (0 == strcmp("ModuleBaudRateChanged", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = ModuleBaudRateChangedIn_Index;
	}
	else if (0 == strcmp("ResetAlert", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = ResetAlertIn_Index;
	}
	else if (0 == strcmp("LinkStatus", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = LinkStatusIn_Index;
	}
	else if (0 == strcmp("RFAck", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = RFAckIn_Index;
	}
	else if (0 == strcmp("ModuleAwake", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = ModuleAwakeIn_Index;
	}
	else if (0 == strcmp("WakeupHost", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = WakeupHostIn_Index;
	}
	else if (0 == strcmp("ReceiveOtaData", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = ReceiveOtaDataIn_Index;
	}
	else if (0 == strcmp("Error", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = ErrorIn_Index;
	}
	else if (0 == strcmp("ModuleGoToLpm", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = ModuleGoToLpmIn_Index;
	}
	else if (0 == strcmp("QueryConnectionParams", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryConnectionParamsIn_Index;
	}
	else if (0 == strcmp("QueryDevBoardSensorsEnable", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryDevBoardSensorsEnableIn_Index;
	}
	else if (0 == strcmp("QueryDevBoardSensors", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryDevBoardSensorsIn_Index;
	}
	else if (0 == strcmp("QueryFirmwareVersion", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryFirmwareVersionIn_Index;
	}
	else if (0 == strcmp("QueryLpmParams", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryLpmParamsIn_Index;
	}
	else if (0 == strcmp("QueryMacAddress", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryMacAddressIn_Index;
	}
	else if (0 == strcmp("QueryModuleSensors", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryModuleSensorsIn_Index;
	}
	else if (0 == strcmp("QueryRfParams", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryRfParamsIn_Index;
	}
	else if (0 == strcmp("QueryUartErrorEnable", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = QueryUartErrorEnableIn_Index;
	}
	else if (0 == strcmp("ResetToFactoryDefaults", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = ResetToFactoryDefaultsIn_Index;
	}
	else if (0 == strcmp("SendOtaData", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SendOtaDataIn_Index;
	}
	else if (0 == strcmp("SetBaudRate", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SetBaudRateIn_Index;
	}
	else if (0 == strcmp("SetConnectionParams", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SetConnectionParamsIn_Index;
	}
	else if (0 == strcmp("SetDevBoardSensorsEnable", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SetDevBoardSensorsEnableIn_Index;
	}
	else if (0 == strcmp("SetLpmParams", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SetLpmParamsIn_Index;
	}
	else if (0 == strcmp("SetMacAddress", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SetMacAddressIn_Index;
	}
	else if (0 == strcmp("SetRfParams", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SetRfParamsIn_Index;
	}
	else if (0 == strcmp("SetUartErrorEnable", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SetUartErrorEnableIn_Index;
	}
	else if (0 == strcmp("SoftReset", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = SoftResetIn_Index;
	}
	else if (0 == strcmp("TerminateBleConnection", pMethodName))
	{
		*messageNamespace = Common;
		CommonMsgIndex = TerminateBleConnectionIn_Index;
	}
	else if (0 == strcmp("AdvertisingDataReceived", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = AdvertisingDataReceivedIn_Index;
	}
	else if (0 == strcmp("ScanComplete", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = ScanCompleteIn_Index;
	}
	else if (0 == strcmp("ScanResponseDataReceived", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = ScanResponseDataReceivedIn_Index;
	}
	else if (0 == strcmp("ConnectToDevice", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = ConnectToDeviceIn_Index;
	}
	else if (0 == strcmp("QueryCentralLedBehavior", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = QueryCentralLedBehaviorIn_Index;
	}
	else if (0 == strcmp("QueryScanParams", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = QueryScanParamsIn_Index;
	}
	else if (0 == strcmp("Scan", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = ScanIn_Index;
	}
	else if (0 == strcmp("SetCentralLedBehavior", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = SetCentralLedBehaviorIn_Index;
	}
	else if (0 == strcmp("SetScanParams", pMethodName))
	{
		*messageNamespace = Central;
		CentralMsgIndex = SetScanParamsIn_Index;
	}

	if (*messageNamespace == Peripheral)
	{
		return PeripheralMsgIndex;
	}
	else if (*messageNamespace == Common)
	{
		return CommonMsgIndex;
	}
	else if (*messageNamespace == Central)
	{
		return CentralMsgIndex;
	}
	else
	{
		return 0;
	}
}


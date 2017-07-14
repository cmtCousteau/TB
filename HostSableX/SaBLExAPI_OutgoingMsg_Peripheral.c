/*******************************************************************************
	Filename:       SaBLExAPI_OutgoingMsg_Peripheral
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
#include "SaBLExAPI_OutgoingMsg_Peripheral.h"

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
 @fn	QueryPeripheralLedBehaviorOut
 *
 @brief	Request to query the LED behavior for the peripheral.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryPeripheralLedBehaviorOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryPeripheralLedBehavior"));
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
 @fn	SetPeripheralLedBehaviorOut
 *
 @brief	Request to set the LED behavior for the peripheral.
All period values are in ms.
The LED on time is 5ms.  As an example, if the LED period is set to 250ms, the LED will be on for 5mS and off for 245ms.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetPeripheralLedBehaviorOut - Point to structure that represent the message.
 *
 */
void SetPeripheralLedBehaviorOut (uint8_t u8MsgId, params_SetPeripheralLedBehaviorOut_t* params_SetPeripheralLedBehaviorOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "HeartbeatPeriod", json_mknumber(params_SetPeripheralLedBehaviorOut->HeartbeatPeriod));
	json_append_member(pParam, "UartActivity", json_mkbool(params_SetPeripheralLedBehaviorOut->UartActivity));
	json_append_member(pParam, "AdvertisingPeriod", json_mknumber(params_SetPeripheralLedBehaviorOut->AdvertisingPeriod));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetPeripheralLedBehaviorOut->SaveToNv));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetPeripheralLedBehavior"));
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
 @fn	QueryAdvertisingEnableOut
 *
 @brief	Request to query advertising enable.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryAdvertisingEnableOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryAdvertisingEnable"));
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
 @fn	QueryAdvertisingParamsOut
 *
 @brief	Request to query the advertising params.
 *
 @param	u8MsgId - Id of the Received Message
 *
 */
void QueryAdvertisingParamsOut (uint8_t u8MsgId)
{
	JsonNode *pMsg = json_mkobject();

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("QueryAdvertisingParams"));
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
 @fn	SetAdvertisingEnableOut
 *
 @brief	Request to enable or disable advertising.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetAdvertisingEnableOut - Point to structure that represent the message.
 *
 */
void SetAdvertisingEnableOut (uint8_t u8MsgId, params_SetAdvertisingEnableOut_t* params_SetAdvertisingEnableOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "AdvertisingEnable", json_mkbool(params_SetAdvertisingEnableOut->AdvertisingEnable));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetAdvertisingEnableOut->SaveToNv));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetAdvertisingEnable"));
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
 @fn	SetAdvertisingParamsOut
 *
 @brief	Request to set the advertising parameters.  

In BLE there is advertising data and scan response data.  Scan response data is not required, some applications may choose to use it if they would like to provide additional information in an active scan response.

Adversing data has a maximum payload of 31 bytes OTA.  The first five bytes are reserved, leaving 26 bytes available to the user.  If advertising data is set to null (or "" in the Json Message) only the first three bytes mentioned below will be used in the advertising data.
The three reserved bytes are as follows:
byte 1 = Length of Data
byte 2 = Advertisement Type Flag (Hard-coded to 0x01 in Serial-to-BLE App)
byte 3 = Advertisement Type Data (Contains information on Discoverable Mode which can be set using the Serial-to-BLE API)
byte 4 = Reserved per Bluetooth spec.
byte 5 = Reserved per Bluetooth spec.

Note:  5361424C452D78 in the Example/Default values below translates to "SaBLE-x" in ASCII.

Scan response data has a maximum payload of 29 bytes OTA, all of it available to the user.  If scan response data is set to null (or "" in the Json Message) only byte 1 mentioned below will be used in the scan response data.
byte 1 = Length of Data
byte 2 = Local Name Complete (Hard-coded to 0x09)

Note:  5361424C452D782053657269616C2D746F2D424C45 in the Example/Default values below translates to "SaBLE-x Serial-to-BLE" in ASCII.
 *
 @param	u8MsgId - Id of the Received Message
 @param	params_SetAdvertisingParamsOut - Point to structure that represent the message.
 *
 */
void SetAdvertisingParamsOut (uint8_t u8MsgId, params_SetAdvertisingParamsOut_t* params_SetAdvertisingParamsOut)
{
	JsonNode *pMsg = json_mkobject();

	JsonNode *pParam = json_mkobject();

	/* Fill in message parameters */
	json_append_member(pParam, "AdvertisingChannels", json_mknumber(params_SetAdvertisingParamsOut->AdvertisingChannels));
	json_append_member(pParam, "AdvertisingData", json_mkstring(params_SetAdvertisingParamsOut->AdvertisingData));
	json_append_member(pParam, "AdvertisingInterval", json_mknumber(params_SetAdvertisingParamsOut->AdvertisingInterval));
	json_append_member(pParam, "DiscoverableMode", json_mknumber(params_SetAdvertisingParamsOut->DiscoverableMode));
	json_append_member(pParam, "SaveToNv", json_mkbool(params_SetAdvertisingParamsOut->SaveToNv));
	json_append_member(pParam, "ScanResponseData", json_mkstring(params_SetAdvertisingParamsOut->ScanResponseData));
	/* Fill in message parameters end*/

	/* Create message */
	json_append_member (pMsg, JSON_HEADER_STRING, json_mkstring(JSON_HEADER_VALUE));
	json_append_member (pMsg, JSON_METHOD_ID, json_mkstring("SetAdvertisingParams"));
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




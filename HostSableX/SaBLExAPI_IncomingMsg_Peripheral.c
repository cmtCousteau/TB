/*******************************************************************************
	Filename:       SaBLExAPI_IncomingMsg_Peripheral
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
#include "SaBLExAPI_IncomingMsg_Peripheral.h"

/*********************************************************************
* GLOBAL VARIABLES
*/


void (*const pProcessIncomingMsgPeripheral[7])(JsonNode* pMsg) = {
	ProcessInvalidMessagePeripheral,
	QueryAdvertisingEnableIn,
	QueryAdvertisingParamsIn,
	QueryPeripheralLedBehaviorIn,
	SetAdvertisingEnableIn,
	SetAdvertisingParamsIn,
	SetPeripheralLedBehaviorIn
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
 @fn	ProcessInvalidMessagePeripheral
 *
 @brief	This function will handle a invalid message.
 *
 @param	none
 *
 */
void ProcessInvalidMessagePeripheral (JsonNode* pMsg)
{

}


/*********************************************************************
 @fn	QueryAdvertisingEnableIn
 *
 @brief	Response to query advertising enable request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryAdvertisingEnableIn (JsonNode* pMsg)
{
	/* Get paramaters */
	results_QueryAdvertisingEnableIn_t QueryAdvertisingEnableResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pAdvertisingEnable = json_find_member (pResult, "AdvertisingEnable");
	QueryAdvertisingEnableResults.AdvertisingEnable = pAdvertisingEnable->bool_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pAdvertisingEnable);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryAdvertisingParamsIn
 *
 @brief	Response to query advertising params request.  Please see the "SetAdvertisingParams" Request as well as the CC2640 TI software developers guide for more information about the parameters in this message.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryAdvertisingParamsIn (JsonNode* pMsg)
{
	results_QueryAdvertisingParamsIn_t QueryAdvertisingParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pAdvertisingChannels = json_find_member (pResult, "AdvertisingChannels");
	QueryAdvertisingParamsResults.AdvertisingChannels = pAdvertisingChannels->number_;
	JsonNode *pAdvertisingData = json_find_member (pResult, "AdvertisingData");
	QueryAdvertisingParamsResults.AdvertisingData = pAdvertisingData->string_;
	JsonNode *pAdvertisingInterval = json_find_member (pResult, "AdvertisingInterval");
	QueryAdvertisingParamsResults.AdvertisingInterval = pAdvertisingInterval->number_;
	JsonNode *pDiscoverableMode = json_find_member (pResult, "DiscoverableMode");
	QueryAdvertisingParamsResults.DiscoverableMode = pDiscoverableMode->number_;
	JsonNode *pScanResponseData = json_find_member (pResult, "ScanResponseData");
	QueryAdvertisingParamsResults.ScanResponseData = pScanResponseData->string_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pScanResponseData);
	json_delete(pDiscoverableMode);
	json_delete(pAdvertisingInterval);
	json_delete(pAdvertisingData);
	json_delete(pAdvertisingChannels);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	QueryPeripheralLedBehaviorIn
 *
 @brief	Response to query peripheral LED behavior request.
All period values are in ms.
The LED on time is 5ms.  As an example, if the LED period is set to 250ms, the LED will be on for 5mS and off for 245ms.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void QueryPeripheralLedBehaviorIn (JsonNode* pMsg)
{
	results_QueryPeripheralLedBehaviorIn_t QueryPeripheralLedBehaviorResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pHeartbeatPeriod = json_find_member (pResult, "HeartbeatPeriod");
	QueryPeripheralLedBehaviorResults.HeartbeatPeriod = pHeartbeatPeriod->number_;
	JsonNode *pUartActivity = json_find_member (pResult, "UartActivity");
	QueryPeripheralLedBehaviorResults.UartActivity = pUartActivity->bool_;
	JsonNode *pAdvertisingPeriod = json_find_member (pResult, "AdvertisingPeriod");
	QueryPeripheralLedBehaviorResults.AdvertisingPeriod = pAdvertisingPeriod->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pAdvertisingPeriod);
	json_delete(pUartActivity);
	json_delete(pHeartbeatPeriod);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetAdvertisingEnableIn
 *
 @brief	Response to set advertising enable request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetAdvertisingEnableIn (JsonNode* pMsg)
{
	results_SetAdvertisingEnableIn_t SetAdvertisingEnableResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetAdvertisingEnableResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetAdvertisingParamsIn
 *
 @brief	Response to set advertising params request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetAdvertisingParamsIn (JsonNode* pMsg)
{
	results_SetAdvertisingParamsIn_t SetAdvertisingParamsResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetAdvertisingParamsResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}
/*********************************************************************
 @fn	SetPeripheralLedBehaviorIn
 *
 @brief	Response to set peripheral LED behavior request.
 *
 @param	pMsg - Pointer to Incoming Message
 *
 */
void SetPeripheralLedBehaviorIn (JsonNode* pMsg)
{
	results_SetPeripheralLedBehaviorIn_t SetPeripheralLedBehaviorResults;

	/* Get the Id of the message */
	JsonNode *pId = json_find_member (pMsg, JSON_ID);
	uint8_t u8MsgId = pId->number_;

	JsonNode *pResult = json_find_member (pMsg, JSON_RESULT_ID);
	JsonNode *pStatus = json_find_member (pResult, "Status");
	SetPeripheralLedBehaviorResults.Status = pStatus->number_;
	/* # App Code Start # */

	/* # App Code End # */

	/* Clean Up Memory */
	json_delete(pStatus);
	json_delete(pResult);
	json_delete(pId);
}


/*******************************************************************************
	Filename:       SaBLExAPI_IncomingMsg_Peripheral
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

#ifndef SABLEXAPI_INCOMINGMSG_PERIPHERAL_H
#define SABLEXAPI_INCOMINGMSG_PERIPHERAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
* INCLUDES
*/
#include "json.h"
#include "SaBLExAPITypes.h"
#include "SaBLExAPI_Shared.h"


/*********************************************************************
* EXTERNAL VARIABLES
*/
extern void (*const pProcessIncomingMsgPeripheral[7])(JsonNode* pMsg);


/*********************************************************************
* CONSTANTS
*/


/*********************************************************************
* TYPEDEFS
*/

typedef struct results_QueryAdvertisingEnableIn
{
	bool	AdvertisingEnable;
} results_QueryAdvertisingEnableIn_t;

typedef struct results_QueryAdvertisingParamsIn
{
	uint8_t	AdvertisingChannels;
	char*	AdvertisingData;
	uint16_t	AdvertisingInterval;
	uint8_t	DiscoverableMode;
	char*	ScanResponseData;
} results_QueryAdvertisingParamsIn_t;

typedef struct results_QueryPeripheralLedBehaviorIn
{
	uint16_t	HeartbeatPeriod;
	bool	UartActivity;
	uint16_t	AdvertisingPeriod;
} results_QueryPeripheralLedBehaviorIn_t;

typedef struct results_SetAdvertisingEnableIn
{
	uint8_t	Status;
} results_SetAdvertisingEnableIn_t;

typedef struct results_SetAdvertisingParamsIn
{
	uint8_t	Status;
} results_SetAdvertisingParamsIn_t;

typedef struct results_SetPeripheralLedBehaviorIn
{
	uint8_t	Status;
} results_SetPeripheralLedBehaviorIn_t;


/*********************************************************************
* MACROS
*/


/*********************************************************************
* API FUNCTIONS
*/

/*********************************************************************
 @fn	QueryAdvertisingEnableIn
 *
 @brief	Response to query advertising enable request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryAdvertisingEnableIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryAdvertisingParamsIn
 *
 @brief	Response to query advertising params request.  Please see the "SetAdvertisingParams" Request as well as the CC2640 TI software developers guide for more information about the parameters in this message.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryAdvertisingParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	QueryPeripheralLedBehaviorIn
 *
 @brief	Response to query peripheral LED behavior request.
All period values are in ms.
The LED on time is 5ms.  As an example, if the LED period is set to 250ms, the LED will be on for 5mS and off for 245ms.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void QueryPeripheralLedBehaviorIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetAdvertisingEnableIn
 *
 @brief	Response to set advertising enable request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetAdvertisingEnableIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetAdvertisingParamsIn
 *
 @brief	Response to set advertising params request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetAdvertisingParamsIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	SetPeripheralLedBehaviorIn
 *
 @brief	Response to set peripheral LED behavior request.
 *
 @param	JsonNode* pMsg - Pointer to Incoming Message
 *
 */
void SetPeripheralLedBehaviorIn ( JsonNode* pMsg);
/*********************************************************************
 @fn	ProcessInvalidMessagePeripheral
 *
 @brief	This function will handle a invalid message.
 *
 @param	none
 *
 */
void ProcessInvalidMessagePeripheral (JsonNode* pMsg);


#ifdef __cplusplus
}
#endif

#endif /*SABLEXAPI_INCOMINGMSG_PERIPHERAL_H*/

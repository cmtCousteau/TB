/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   command.h
 * Author: marco
 *
 * Created on 11. juillet 2017, 13:37
 */

#ifndef COMMAND_H
#define COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "rs232.h"
#include "json.h"
#include "SaBLExAPI_OutgoingMsg_Peripheral.h"
#include "SaBLExAPI_OutgoingMsg_Common.h"



    bool sendSetPeripheralLedBehaviorOut(uint8_t u8MsgId, uint16_t AdvertisingPeriod, uint16_t HeartbeatPeriod, bool UartActivity, bool SaveToNv);
    bool sendSendOtaDataOut (uint8_t u8MsgId, char* data);
    bool sendSetAdvertisingParamsOut ( uint8_t u8MsgId, uint8_t advertisingChannels, char* advertisingData, uint16_t advertisingInterval,
    uint8_t discoverableMode, bool saveToNv, char* scanResponseData);
    bool sendSetAdvertisingEnableOut(uint8_t u8MsgId, bool advertisingEnable, bool saveToNv);
    bool sendHostAwakeOut();
    bool sendSetLpmParamsOut(uint8_t, bool, uint16_t, bool);
    void sendSoftResetOut (uint8_t);
    void sendSetConnectionParamsOut (uint8_t, uint16_t, uint16_t, bool, uint16_t, uint16_t);
    uint16_t waitForCommand();
    
    void startReadThread();
    
#define GET_RESOURCES 1
    
    


#ifdef __cplusplus
}
#endif

#endif /* COMMAND_H */


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

#include <stdio.h>
#include <stdlib.h>

#include "rs232.h"
#include "json.h"
#include "SaBLExAPI_OutgoingMsg_Peripheral.h"
#include "SaBLExAPI_OutgoingMsg_Common.h"

#ifdef __cplusplus
extern "C" {
#endif

    bool sendSetPeripheralLedBehaviorOut(uint8_t u8MsgId, int AdvertisingPeriod, int HeartbeatPeriod, bool UartActivity, bool SaveToNv);
    bool sendSendOtaDataOut (uint8_t u8MsgId, char* data);
    bool sendSetAdvertisingParamsOut ( uint8_t u8MsgId, uint8_t advertisingChannels,
        char* advertisingData, uint16_t advertisingInterval,
        uint8_t discoverableMode, bool saveToNv, char* scanResponseData);
    bool sendSetAdvertisingEnableOut(uint8_t u8MsgId, bool advertisingEnable, bool saveToNv);
    bool sendHostAwakeOut();
    bool sendSetLpmParamsOut(uint8_t, bool, uint16_t, bool);
    
    void readData();
    
    void startReadThread();
    
    DWORD WINAPI thread_1(void *);
    
    


#ifdef __cplusplus
}
#endif

#endif /* COMMAND_H */


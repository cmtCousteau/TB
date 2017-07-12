#include "command.h"


bool sendSetPeripheralLedBehaviorOut(uint8_t u8MsgId, int AdvertisingPeriod, int HeartbeatPeriod, bool UartActivity, bool SaveToNv){

    params_SetPeripheralLedBehaviorOut_t paramLed;
    JsonNode pMsg;
    
    paramLed.AdvertisingPeriod = AdvertisingPeriod;
    paramLed.HeartbeatPeriod = HeartbeatPeriod;
    paramLed.UartActivity = UartActivity;
    paramLed.SaveToNv = SaveToNv;
    
    SetPeripheralLedBehaviorOut(u8MsgId, &paramLed);
    
   // &pMsg = json_mkstring(te);
    
   // SetPeripheralLedBehaviorIn (pMsg);
    
}

bool sendSendOtaDataOut (uint8_t u8MsgId, char* data){
    
    params_SendOtaDataOut_t params_SendOtaDataOut;
    params_SendOtaDataOut.DataAscii = data;
    params_SendOtaDataOut.DataHex = "";
    
    SendOtaDataOut(u8MsgId, &params_SendOtaDataOut);
    
    char te[200];
    UartProcessor_ReadTxMessage(te, 200);
    UartProcessor_ReadTxMessage(te, 200);
}

bool sendSetAdvertisingParamsOut ( uint8_t u8MsgId, uint8_t advertisingChannels,
        char* advertisingData, uint16_t advertisingInterval,
        uint8_t discoverableMode, bool saveToNv, char* scanResponseData){
    
    params_SetAdvertisingParamsOut_t params_SetAdvertisingParamsOut;
    params_SetAdvertisingParamsOut.AdvertisingChannels = advertisingChannels;
    params_SetAdvertisingParamsOut.AdvertisingData = advertisingData;
    params_SetAdvertisingParamsOut.AdvertisingInterval = advertisingInterval;
    params_SetAdvertisingParamsOut.DiscoverableMode = discoverableMode;
    params_SetAdvertisingParamsOut.SaveToNv = saveToNv;
    params_SetAdvertisingParamsOut.ScanResponseData = scanResponseData;
    
    
    SetAdvertisingParamsOut (u8MsgId, &params_SetAdvertisingParamsOut);
}

bool sendSetAdvertisingEnableOut(uint8_t u8MsgId, bool advertisingEnable, bool saveToNv){
     
    params_SetAdvertisingEnableOut_t params_SetAdvertisingEnableOut;
    params_SetAdvertisingEnableOut.AdvertisingEnable = advertisingEnable;
    params_SetAdvertisingEnableOut.SaveToNv = saveToNv;      

    SetAdvertisingEnableOut (u8MsgId, &params_SetAdvertisingEnableOut);
    char te[200];
    UartProcessor_ReadTxMessage(te, 200);
}

bool sendHostAwakeOut(){
    HostAwakeOut();
    char te[200];
    UartProcessor_ReadTxMessage(te, 200);
}

bool sendSetLpmParamsOut(uint8_t u8MsgId, bool wakeHost, uint16_t sleepTime, bool saveToNv){
    params_SetLpmParamsOut_t params_SetLpmParamsOut;
    params_SetLpmParamsOut.WakeHost = wakeHost;
    params_SetLpmParamsOut.SleepTime = sleepTime;
    params_SetLpmParamsOut.SaveToNv = saveToNv;
     
    SetLpmParamsOut(u8MsgId, &params_SetLpmParamsOut);
    char te[200];
    UartProcessor_ReadTxMessage(te, 200);
     
}

void readData(){
    char te[200];
    UartProcessor_ReadTxMessage(te, 200);
    UartProcessor_ReadTxMessage(te, 200);
    UartProcessor_ReadTxMessage(te, 200);
}

DWORD WINAPI thread_1(void *arg)
{
    int bufferLenght = 200;
    char pcMessage[200];
    
    while(1){
        printf("thread\n");
        char te[200];
        UartProcessor_ReadTxMessage(te, 200);
    }
}



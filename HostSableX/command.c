#include "command.h"



bool sendSetPeripheralLedBehaviorOut(uint8_t u8MsgId, int AdvertisingPeriod, int HeartbeatPeriod, bool UartActivity, bool SaveToNv){

    params_SetPeripheralLedBehaviorOut_t paramLed;
    JsonNode pMsg;
    
    paramLed.AdvertisingPeriod = AdvertisingPeriod;
    paramLed.HeartbeatPeriod = HeartbeatPeriod;
    paramLed.UartActivity = UartActivity;
    paramLed.SaveToNv = SaveToNv;
    
    SetPeripheralLedBehaviorOut(u8MsgId, &paramLed);
    
    char te[100];
    UartProcessor_ReadTxMessage(te);
    
   // &pMsg = json_mkstring(te);
    
   // SetPeripheralLedBehaviorIn (pMsg);
    
}

bool sendSendOtaDataOut (uint8_t u8MsgId, char* data){
    
    params_SendOtaDataOut_t params_SendOtaDataOut;
    params_SendOtaDataOut.DataAscii = data;
    params_SendOtaDataOut.DataHex = "";
    
    SendOtaDataOut(u8MsgId, &params_SendOtaDataOut);
    char te[100];
    UartProcessor_ReadTxMessage(te);
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
    
    char te[100];
    UartProcessor_ReadTxMessage(te);
}

bool sendSetAdvertisingEnableOut(uint8_t u8MsgId, bool advertisingEnable, bool saveToNv){
     
    params_SetAdvertisingEnableOut_t params_SetAdvertisingEnableOut;
    params_SetAdvertisingEnableOut.AdvertisingEnable = advertisingEnable;
    params_SetAdvertisingEnableOut.SaveToNv = saveToNv;      

    SetAdvertisingEnableOut (u8MsgId, &params_SetAdvertisingEnableOut);
            
    char te[100];
    UartProcessor_ReadTxMessage(te);
}

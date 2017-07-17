#include "command.h"


bool sendSetPeripheralLedBehaviorOut(uint8_t u8MsgId, uint16_t AdvertisingPeriod, uint16_t HeartbeatPeriod, bool UartActivity, bool SaveToNv){

    params_SetPeripheralLedBehaviorOut_t paramLed;
    JsonNode pMsg;
    
    paramLed.AdvertisingPeriod = AdvertisingPeriod;
    paramLed.HeartbeatPeriod = HeartbeatPeriod;
    paramLed.UartActivity = UartActivity;
    paramLed.SaveToNv = SaveToNv;
    
    SetPeripheralLedBehaviorOut(u8MsgId, &paramLed);
    
    char msg[200];
    JsonNode *jsonMsg = UartProcessor_ReadTxMessage(msg, 200);
    
}

bool sendSendOtaDataOut (uint8_t u8MsgId, char* data){
    
    params_SendOtaDataOut_t params_SendOtaDataOut;
    params_SendOtaDataOut.DataAscii = data;
    params_SendOtaDataOut.DataHex = "";
    
    SendOtaDataOut(u8MsgId, &params_SendOtaDataOut);
    
    char msgStatus[200];
    char msgACK[200];
    
    UartProcessor_ReadTxMessage(msgStatus, 200);
    if(getBLEConnectionStatus())
        UartProcessor_ReadTxMessage(msgACK, 200);
    
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
    char msg[200];
    JsonNode *jsonMsg = UartProcessor_ReadTxMessage(msg, 200);
}

bool sendSetAdvertisingEnableOut(uint8_t u8MsgId, bool advertisingEnable, bool saveToNv){
     
    params_SetAdvertisingEnableOut_t params_SetAdvertisingEnableOut;
    params_SetAdvertisingEnableOut.AdvertisingEnable = advertisingEnable;
    params_SetAdvertisingEnableOut.SaveToNv = saveToNv;      

    SetAdvertisingEnableOut (u8MsgId, &params_SetAdvertisingEnableOut);
    char msg[200];
    JsonNode *jsonMsg = UartProcessor_ReadTxMessage(msg, 200);
    
    JsonNode *jsonResult = json_find_member (jsonMsg, "result");
    JsonNode *jsonStatus = json_find_member (jsonResult, "Status");
    free(jsonMsg);
    free(jsonResult);
    
    if(jsonStatus->number_ == 0){
        free(jsonStatus);
        printf("OK\n");
        return true;
    }else{
        free(jsonStatus);
        printf("KO\n");
        return false;
    }
    
  //  printf("%s\n", msg);
//    SetAdvertisingEnableIn(pMsg);
        
    
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

void sendSoftResetOut (uint8_t u8MsgId){
    
    SoftResetOut(u8MsgId);
    char te[200];
    UartProcessor_ReadTxMessage(te, 200);
    UartProcessor_ReadTxMessage(te, 200);
}

void sendSetConnectionParamsOut (uint8_t u8MsgId, uint16_t maxConInterval, uint16_t minConInterval, bool saveToNv, uint16_t slaveLatency, uint16_t supervisionTimeout){

    params_SetConnectionParamsOut_t params_SetConnectionParamsOut;
    
    params_SetConnectionParamsOut.MaxConnectionInterval = maxConInterval;
    params_SetConnectionParamsOut.MinConnectionInterval = minConInterval;
    params_SetConnectionParamsOut.SaveToNv = saveToNv;
    params_SetConnectionParamsOut.SlaveLatency = slaveLatency;
    params_SetConnectionParamsOut.SupervisionTimeout = supervisionTimeout;
    
    SetConnectionParamsOut(u8MsgId, &params_SetConnectionParamsOut);
    
    char te[200];
    UartProcessor_ReadTxMessage(te, 200);
}

void readData(){
    char te[200];
    
    
    UartProcessor_ReadTxMessage(te, 200);
    UartProcessor_ReadTxMessage(te, 200);
    
    JsonNode *jsonMsg = UartProcessor_ReadTxMessage(te, 200);
    
    JsonNode *jsonParam = json_find_member (jsonMsg, "params");
    JsonNode *jsonDataAscii = json_find_member (jsonParam, "DataAscii");
      
    printf("Data : %s", jsonDataAscii->number_);
    
   // uint8_t u8MsgId = 10;
   // sendSendOtaDataOut( u8MsgId, "Blu");
    
}




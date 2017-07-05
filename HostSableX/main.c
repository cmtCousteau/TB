/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: marco
 *
 * Created on 5. juillet 2017, 18:36
 * 
 * 
 * https://www.lsr.com/embedded-wireless-modules/bluetooth-module/sable-x-ble-module/sable-x-development#host-porting-guide
 * 
 * https://www.lsr.com/embedded-wireless-modules/bluetooth-module/sable-x-ble-module/sable-x-development#host-code-documentation
 */

#include <stdio.h>
#include <stdlib.h>
#include "rs232.h"
#include "SaBLExAPI_OutgoingMsg_Peripheral.h"
#include "SaBLExAPI_OutgoingMsg_Common.h"



int main(int argc, char** argv) {
    
    int portCOMId;
    
    params_SetLpmParamsOut_t lpmParam;
    lpmParam.SaveToNv = true;
    lpmParam.SleepTime = 65535;
    lpmParam.SaveToNv = false;
    
    params_SetAdvertisingEnableOut_t paramAdvertisingEnable;
    paramAdvertisingEnable.AdvertisingEnable = false;
    paramAdvertisingEnable.SaveToNv = true;

    uint8_t u8MsgId = 1;
    
    printf("List des ports COM disponibles : \n");
    printf("--------------------------------\n");
    
    for(int i = 0; i < 10; i++){
        if(OpenCOM(i) == true){
            printf("Port COM : %d\n", i);
            CloseCOM();
        }
    }
    
    do{
        printf("Choisissez un port COM auquel se connecter : ");
        scanf("%d", &portCOMId);
        
    }while(OpenCOM(portCOMId) == false);
    
    HostAwakeOut ();
    SetLpmParamsOut(u8MsgId, &lpmParam);
    SetAdvertisingEnableOut(++u8MsgId, &paramAdvertisingEnable);
    
    CloseCOM();
            

    return (EXIT_SUCCESS);
}


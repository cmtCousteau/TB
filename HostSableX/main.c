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
#include "SaBLExAPI_OutgoingMsg_Peripheral.h"
#include "SaBLExAPI_OutgoingMsg_Common.h"
#include "command.h"
#include <inttypes.h>


void cleanBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int main(int argc, char** argv) {
    
    char menuChoice = '\0';
    int portCOMId;
    int choixDecimal = 0;
    uint8_t u8MsgId = 0;   
    
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("| List des ports COM disponibles  |\n");

    for(int i = 0; i < 10; i++){
        if(fastOpenCOM(i) == true){
            printf("| port COM : %d                    |\n", i);
        }
    }
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    do{
        printf("Choisissez un port COM auquel se connecter : ");
        scanf("%d", &portCOMId);
    }while(fastOpenCOM(portCOMId) == false);
    
    openCOM(portCOMId);
    sendSoftResetOut(++u8MsgId);
    
    // sendHostAwakeOut();
    // sendSetLpmParamsOut(u8MsgId, false, 65535, true);
    // sendSetAdvertisingParamsOut(++u8MsgId, 7, "5361424C452D78", 160, 1, true, "5361424C452D782053657269616C2D746F2D424C45");

    do{
        printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("| Configuration des advertising (G)  |\n");
        printf("| Activation des advertising (A)     |\n");
        printf("| Desactivation des advertising (D)  |\n");
        printf("| Choix du heartbeat (B)             |\n");
        printf("| Configuration des intervals (P)    |\n");
        printf("| Attends commande (R)               |\n");
        printf("| Quitter (Q)                        |\n");
        printf("| Choix : ");
        
        cleanBuffer();
        scanf("%c", &menuChoice);
        printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        
        if(menuChoice == 'G' || menuChoice == 'g'){
        
            printf("Choix de l'interval d'avertising : ");
            scanf("%d", &choixDecimal);            
            sendSetAdvertisingParamsOut(++u8MsgId, 7, "5361424C452D78", choixDecimal, 1, true, "5361424C452D782053657269616C2D746F2D424C45");
        }
        
        if(menuChoice == 'A' || menuChoice == 'a'){
            sendSetAdvertisingEnableOut(++u8MsgId,true,true);
        }
            
        if(menuChoice == 'D' || menuChoice == 'd')
            sendSetAdvertisingEnableOut(++u8MsgId,false,true);
        if(menuChoice == 'B' || menuChoice == 'b'){
            uint16_t periodeValue;
            printf("Valeur du hearbeat ms [0-65535]: ");
            scanf("%" SCNu16, &periodeValue);
            
            sendSetPeripheralLedBehaviorOut(++u8MsgId, periodeValue, periodeValue, true, false);
        }
        
        if(menuChoice == 'P' || menuChoice == 'p'){
            
            uint16_t maxConInterval = 0;
            uint16_t minConInterval = 0;
           
            do{
                printf("Maximum interval ms [6-3200] : ");
                cleanBuffer();
                scanf("%" SCNu16, &maxConInterval);
            }while(maxConInterval < 6 || maxConInterval > 3200);
            
            do{
                printf("Minimum interval ms [6-3200] : ");
                cleanBuffer();
                scanf("%" SCNu16, &minConInterval);
            }while(minConInterval < 6 || minConInterval > 3200);
            
            sendSetConnectionParamsOut(++u8MsgId, maxConInterval, minConInterval, true, 0,1000);
        }
        if(menuChoice == 'R' || menuChoice == 'r'){
            uint16_t command = waitForCommand();
            if(command == GET_RESOURCES){
                sendSendOtaDataOut(++u8MsgId, "Voltage 230 v");
                sendSendOtaDataOut(++u8MsgId, "Courant 5 A");
                sendSendOtaDataOut(++u8MsgId, "Cosphi 12");
                sendSendOtaDataOut(++u8MsgId, "Frequence 200 Hz");
                sendSendOtaDataOut(++u8MsgId, "Paggr 300 kWh");
            }
        }
     
    }while(menuChoice != 'Q' && menuChoice != 'q');

    CloseCOM();
    return (EXIT_SUCCESS);
}


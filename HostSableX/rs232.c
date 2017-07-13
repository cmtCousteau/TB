#include "rs232.h"

/*=============================================================================
  Variables globales.
=============================================================================*/

/* Handle du port COM ouvert */
HANDLE g_hCOM = NULL;

int DEBUG = 0;

/* Délais d'attente sur le port COM */
COMMTIMEOUTS g_cto =
{
    MAX_WAIT_READ,  /* ReadIntervalTimeOut          */
    0,              /* ReadTotalTimeOutMultiplier   */
    MAX_WAIT_READ,  /* ReadTotalTimeOutConstant     */
    0,              /* WriteTotalTimeOutMultiplier  */
    0               /* WriteTotalTimeOutConstant    */
};

static const uint16_t crcTable[256]  =
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

const uint8_t hextable[256] = {
  //[0 ... 255] = -1, // bit aligned access into this table is considerably
  ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, // faster for most modern processors,
  ['A'] = 10, 11, 12, 13, 14, 15,       // for the space conscious, reduce to
  ['a'] = 10, 11, 12, 13, 14, 15        // signed char.
};

/******************************************************************************
  OpenCOM : ouverture et configuration du port COM.
  entrée : nId : Id du port COM à ouvrir.
  retour : vrai si l'opération a réussi, faux sinon.

*/

bool fastOpenCOM(int nId){
    char szCOM[16];
    
    sprintf(szCOM, "COM%d", nId);
    
    HANDLE tmp_COM = CreateFile( szCOM,
                      GENERIC_READ | GENERIC_WRITE,
                      0,      //  must be opened with exclusive-access
                      NULL,   //  default security attributes
                      OPEN_EXISTING, //  must use OPEN_EXISTING
                      0,      //  not overlapped I/O
                      NULL );
    
    if(tmp_COM == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    
    CloseHandle(tmp_COM);
    return TRUE;
}


bool openCOM(int nId){
    
    /* variables locales */
    DWORD dwStoredFlags = EV_BREAK | EV_CTS   | EV_DSR | EV_ERR | EV_RING |\
                EV_RLSD | EV_RXCHAR | EV_RXFLAG | EV_TXEMPTY ;
    DWORD dwCommEvent;
    char szCOM[16];
    DCB dcb;

    /* construction du nom du port, tentative d'ouverture */
    sprintf(szCOM, "COM%d", nId);
  
    g_hCOM = CreateFile( szCOM,
                      GENERIC_READ | GENERIC_WRITE,
                      0,      //  must be opened with exclusive-access
                      NULL,   //  default security attributes
                      OPEN_EXISTING, //  must use OPEN_EXISTING
                      0,      //  not overlapped I/O
                      NULL ); //  hTemplate must be NULL for comm devices
    //  Initialize the DCB structure.
  // SecureZeroMemory(&dcb, sizeof(DCB));
  // dcb.DCBlength = sizeof(DCB);
   
   GetCommState(g_hCOM, &dcb);
   
   SetCommState(g_hCOM, &dcb);
   
   if (!SetCommMask(g_hCOM, EV_RXCHAR)){
    // error setting communications mask
   }
   
   
   
      return true;
    
    
    
}

bool CloseCOM()
{
    /* fermeture du port COM */
    CloseHandle(g_hCOM);
    return TRUE;
}

bool ReadCOM(char* buffer, int nBytesToRead, long unsigned int* pBytesRead)
{
    return ReadFile(g_hCOM, buffer, nBytesToRead, pBytesRead, NULL);
}

bool WriteCOM(void* buffer, int nBytesToWrite,long unsigned int* pBytesWritten)
{
    /* écriture sur le port */
    return WriteFile(g_hCOM, buffer, nBytesToWrite, pBytesWritten, NULL);
}

JsonNode * UartProcessor_ReadTxMessage(char* receivedMsg, uint16_t bufferLenght){
    
    DEBUG++;
    
    DWORD dwCommEvent = 0;
    COMSTAT lpStat = {0};
    DWORD error;
    BOOL completMsg = false;
    uint16_t receivedMsgCRC;
    char* method;
    char* receivedMsgWithoutCRC;
    int i = 0;
    
    unsigned long int numberOfCharRead;
    unsigned long int sizeOfMsg = 0;

    while(!completMsg){
    
        // On attend de recevoir un event qui indiquera du changement sur le port COM.
        WaitCommEvent(g_hCOM, &dwCommEvent, NULL);  
        printf("Event : %d\n", i++);

        // S'il y a des charactère présent sur le port COM on commence à lire.
        if(dwCommEvent == EV_RXCHAR){
            // Lecture du port COM.
            ReadCOM(&receivedMsg[sizeOfMsg], bufferLenght, &numberOfCharRead);
             // Augmentation de la taille total du message.
            sizeOfMsg += numberOfCharRead;
            // Si les 2 derniers charactères sont }} le message est terminé.
            if(receivedMsg[sizeOfMsg-1] == '}' && receivedMsg[sizeOfMsg-2] == '}'){

                // Le message est complet vu qu'il se termine par }}. 
                completMsg = true;
                
                // On récupère le CRC contenu dans le message reçu.
                receivedMsgCRC = hextable[receivedMsg[sizeOfMsg-3]];
                receivedMsgCRC |= (hextable[receivedMsg[sizeOfMsg-4]]) << 4;
                receivedMsgCRC |= (hextable[receivedMsg[sizeOfMsg-5]]) << 8;
                receivedMsgCRC |= (hextable[receivedMsg[sizeOfMsg-6]]) << 12;
                
                // Allocation de mémoire pour stocker le message mais sans le CRC.
                uint16_t sizeOfMessageWithoutCRC = sizeOfMsg - 12;
                receivedMsgWithoutCRC = malloc(sizeOfMessageWithoutCRC+1);
                // Creation du nouveau message sans le CRC, +1 pour eviter de prendre la première accolade.
                memcpy(receivedMsgWithoutCRC, receivedMsg + 1, sizeOfMessageWithoutCRC);
                // Ajout du du \0 à la fin de la chaîne.
                receivedMsgWithoutCRC[sizeOfMessageWithoutCRC]  = '\0';
                
                printf("%s\n", receivedMsgWithoutCRC);
                printf("avant json\n");
                if(DEBUG == 2){
                    printf("Plantage\n");
                }
 
                JsonNode *JsonMessage = json_decode(receivedMsgWithoutCRC);
                printf("apres json\n");
              
                // On calcul le CRC du message qu'on à reçu.
                uint16_t receivedMsgCalculatedCRC = UartProcessor_calculateCrc(receivedMsgWithoutCRC);
                
                printf("%d = %d\n",receivedMsgCalculatedCRC,receivedMsgCRC);
                
                /*JsonNode *pResult = json_find_member (message, "result");
                JsonNode *pStatus = json_find_member (pResult, "Status");*/                
                JsonNode *pMethod = json_find_member (JsonMessage, "method");
                if(pMethod != NULL){
                    method = pMethod->number_;
                    
                    if(strcmp(method, "LinkStatus")== 0){
                        printf("method : %s\n", method);
                        completMsg = false;
                        sizeOfMsg = 0;
                    }
                    else{
                        printf("Reception : "); 
                        printf("brut      : %s\n", receivedMsg);
                        printf("Reception : ");
                        printf("traite    : %s\n", receivedMsgWithoutCRC);
                        
                        printf("If method return\n");
                        
                        return JsonMessage;
                    }
                }                                       
                else{
                    printf("Reception : "); 
                    printf("brut      : %s\n", receivedMsg);
                    printf("Reception : ");
                    printf("traiter   : %s\n", receivedMsgWithoutCRC);
                    printf("else method return\n");
                    return JsonMessage;
                }
             }// Fin du if complet.
        }
    }// Fin du while.
    
    
    
    
    
    
    
    /*WaitCommEvent(g_hCOM, &dwCommEvent, NULL);  
    printf("Event : %d\n", dwCommEvent);

    if(dwCommEvent == EV_RXCHAR){

        ClearCommError(g_hCOM, &error ,&lpStat); 
        ReadCOM(pcMessage, bufferLenght, &numberOfCharRead);
       
        while(lpStat.cbInQue > 0){
            
            ReadCOM(pcMessage, bufferLenght, &numberOfCharRead);
            WaitCommEvent(g_hCOM, &dwCommEvent, NULL);
            
            ReadCOM(&pcMessage[sizeOfMessage], bufferLenght, &numberOfCharRead);
            sizeOfMessage += numberOfCharRead;
            ClearCommError(g_hCOM, &error ,&lpStat);
        }
        printf("%s\n", pcMessage);
    }*/
}

void UartProcessor_WriteTxMessage(char* pcMessage){
    

    uint16_t u16crc = UartProcessor_calculateCrc(pcMessage);
    bool test;
    unsigned long int written;

    int status = -1;
    
    char res[4];
    res[0] = TO_HEX(((u16crc & 0xF000) >> 12));   
    res[1] = TO_HEX(((u16crc & 0x0F00) >> 8));
    res[2] = TO_HEX(((u16crc & 0x00F0) >> 4));
    res[3] = TO_HEX((u16crc & 0x000F));

    
    uint16_t u16MsgSize = strlen(pcMessage) + 13;
    char* pcMsg = malloc(u16MsgSize);
    //copy pcBuffer into pcMsg prior to bracketizing
    memcpy(pcMsg+1, pcMessage, strlen(pcMessage));
    
    //bracketize and add crc
    pcMsg[0] = '{';
    pcMsg[u16MsgSize-2] = '}';
    pcMsg[u16MsgSize-3] = '}';
    pcMsg[u16MsgSize-4] = res[3];
    pcMsg[u16MsgSize-5] = res[2];
    pcMsg[u16MsgSize-6] = res[1];
    pcMsg[u16MsgSize-7] = res[0];
    pcMsg[u16MsgSize-8] = ':';
    pcMsg[u16MsgSize-9] = 'C';
    pcMsg[u16MsgSize-10] = 'R';
    pcMsg[u16MsgSize-11] = 'C';
    pcMsg[u16MsgSize-12] = '{';
    pcMsg[u16MsgSize-1] = '\0';

    printf("Envoi : %s\n",pcMsg); 
    WriteCOM(pcMsg, u16MsgSize, &written);
    free(pcMsg);  
}

uint16_t UartProcessor_crcByte(uint16_t u16fcs, uint8_t u8c)
{
    uint8_t index = (uint8_t)((u16fcs >> 8 ^ u8c) & 0xff);
    
    u16fcs = (uint16_t)(crcTable[index] ^ (u16fcs << 8));
    return u16fcs;
}

uint16_t UartProcessor_calculateCrc(char* pcMessage)
{
    int len = strlen(pcMessage);
    uint16_t fcs = 0xffff;
    
    for(int i =0; i<len; i++)
    {
        fcs = UartProcessor_crcByte(fcs, pcMessage[i]);
    }
    
    return fcs;
}

unsigned short crc16(const unsigned char* data_p, unsigned char length){
    unsigned char x;
    unsigned short crc = 0xFFFF;
    
   // printf("\n\n %s\n", data_p);

    while (length--){
        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }
    return crc;
}






/* 
 * File:   rs232.h
 * Author: marco
 *
 * Created on 5. juillet 2017, 10:49
 * Source : http://codes-sources.commentcamarche.net/source/22441-base-communication-serie-rs232-win32
 */

#ifndef RS232_H


#include <windows.h>
#include <stdio.h>
#include "SaBLExAPITypes.h"
#include "json.h"

#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' -10 + i)

bool openCOM(int);
bool fastOpenCOM(int);
bool CloseCOM();
bool ReadCOM(char*, int, long unsigned int*);
bool WriteCOM(void*, int,long unsigned int*);

bool getBLEConnectionStatus();

void UartProcessor_WriteTxMessage(char*);
JsonNode * UartProcessor_ReadTxMessage(char*, uint16_t);

unsigned short UartProcessor_crcByte(uint16_t u16fcs, uint8_t u8c);
unsigned short UartProcessor_calculateCrc(char* pcMessage);

/*=============================================================================
  Définition de constantes
=============================================================================*/


#define	RS232_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RS232_H */


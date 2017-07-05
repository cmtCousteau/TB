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
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include "SaBLExAPITypes.h"

#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' -10 + i) 

bool OpenCOM(int nId);
bool CloseCOM();
bool ReadCOM(void* buffer, int nBytesToRead, long unsigned int* pBytesRead);
bool WriteCOM(void* buffer, int nBytesToWrite,long unsigned int* pBytesWritten);

unsigned short UartProcessor_crcByte(uint16_t u16fcs, uint8_t u8c);
unsigned short UartProcessor_calculateCrc(char* pcMessage);

/*=============================================================================
  Définition de constantes
=============================================================================*/
#define RX_SIZE         4096    /* taille tampon d'entrée  */
#define TX_SIZE         4096    /* taille tampon de sortie */
#define MAX_WAIT_READ   5000    /* temps max d'attente pour lecture (en ms) */


#define	RS232_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RS232_H */


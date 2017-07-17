/**-----------------------------------------------------------------------------
 * This function gonna receive each character from the UART and put it in the
 * reception buffer to treat the messagermations.
 */
int32_t nxsNCAPIUARTParser( uint8_t c, nxsDHAL02Peripheral_t * crcPeripheral ) {
    
    int32_t code = NXS_CODE_ERROR;
    nxsBuffer_t * parserBuffer = NULL;
    nxsNCAPIUARTMessage_t * message = NULL;
    #if NXS_NOVACOM_API_MONITORING == 1 
    uint32_t bufferSize = 0;
    #endif

    /* Function Entry Checks  - - - - - - - - - - - - - - - - - - - - - - - - */  
    if( crcPeripheral == NULL ) return NXS_CODE_MISSING_PARAMETER;

    /* Function Processing  - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* CRC Building */
    parserCRCValue += ( c  << ( 8 * ( parserCRCCount ) ) );
    parserCRCCount++;

    /* Add character to crc32 value  */
    if( ( crcPerGlobal != NULL ) && \
        ( parserCRCCount %= sizeof( parserCRCValue ) ) == 0 ) { 
        
        crcPeripheral->data.crc32->crc32PutValue( parserCRCValue );
        parserCRCValue = 0;
        
    }

    /* UART protocol state machine */
    switch( parserStatus ) {
      
        case NXS_API_UART_SOH:
          
            /* Check if we receive a start of heading character */
            if( c == NXS_API_UART_START_OF_HEADING ) {

                /* Reset */
                parserLength = 0;
                parserOpcode = 0;
                parserSequenceID = 0;
                parserToken = 0;
                parserCrc = 0;
                parserPayload_i = 0;

                /* crcResource */
                parserCRCCount = 0;
                parserCRCValue = 0;
                
                /* Reset and set the global crc resource used by the timeout 
                   and CRC Building */
                crcPeripheral->data.crc32->crc32Reset();
                crcPerGlobal = crcPeripheral;

                /* Take hand on CRC semaphore */
                code = nxsMutexTake( &crcPeripheral->mutex, 
                                     NXS_SYSTEM_MAX_DELAY ); 
                if( code != NXS_CODE_NO_ERROR ) {
                   
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to take mutex." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    return NXS_CODE_ERROR;
                    
                }
                
                #if defined( NXS_NOVACOM_API_UART_USE_TIMER ) && \
                    NXS_NOVACOM_API_UART_USE_TIMER == 1    
                /* Start/Reset the parser timer on each byte received */
                code = nxsTimerReset( &parserTimer, NULL );
                if( code != NXS_CODE_NO_ERROR ){
                    
                    /* Release CRC resource */
                    if( crcPerGlobal != NULL ) {
                      
                        nxsMutexGive( &crcPeripheral->mutex );
                        crcPerGlobal = NULL;
                        
                    }
                    
                    parserStatus = NXS_API_UART_SOH;
                    
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to start/reset timer." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    return NXS_CODE_ERROR;   
                    
                }
                #endif /* NXS_NOVACOM_API_UART_USE_TIMER == 1 */
                
                /* Update the status byte */
                parserStatus = NXS_API_UART_OPCODE_MSB;
                
            }
            
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_OPCODE_MSB:
                        
            /* Receive the opcode (msb) of the frame to process */
            parserOpcode = c << 8;

            /* Update the status byte */
            parserStatus = NXS_API_UART_OPCODE_LSB;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_OPCODE_LSB:
  
            /* Receive the opcode (lsb) of the frame to process */
            parserOpcode += c;
            
            /* Update the status byte */
            parserStatus = NXS_API_UART_SEQ_ID_MSB;
             
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_SEQ_ID_MSB:
                        
            /* Receive the parserSequenceID (msb) of the frame to process */
            parserSequenceID = c << 8;

            /* Update the status byte */
            parserStatus = NXS_API_UART_SEQ_ID_LSB;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_SEQ_ID_LSB:
  
            /* Receive the parserSequenceID (lsb) of the frame to process */
            parserSequenceID += c;
            
            /* Update the status byte */
            parserStatus = NXS_API_UART_TOKEN_0;
             
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_TOKEN_0:
                        
            /* Receive the parserToken of the frame to process */
            parserToken = ( c << 24 );

            /* Update the status byte */
            parserStatus = NXS_API_UART_TOKEN_1;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_TOKEN_1:
                        
            /* Receive the parserToken of the frame to process */
            parserToken += ( c << 16 );

            /* Update the status byte */
            parserStatus = NXS_API_UART_TOKEN_2;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_TOKEN_2:
                        
            /* Receive the parserToken of the frame to process */
            parserToken += ( c << 8 );

            /* Update the status byte */
            parserStatus = NXS_API_UART_TOKEN_3;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_TOKEN_3:
  
            /* Receive the parserToken of the frame to process */
            parserToken += c;
            
            /* Update the status byte */
            parserStatus = NXS_API_UART_LENGTH_MSB;
             
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_LENGTH_MSB:
                        
            /* Receive the parserLength (msb) of the frame to process */
            parserLength = c << 8;

            /* Update the status byte */
            parserStatus = NXS_API_UART_LENGTH_LSB;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_LENGTH_LSB:
  
            /* Receive the parserLength (lsb) of the frame to process */
            parserLength += c;

            /* We add a maximum */
            if( parserLength > NXS_API_UART_PAYLOAD_LENGTH_MAX ){
                
                nxsMutexGive( &crcPeripheral->mutex );
                parserStatus = NXS_API_UART_SOH;
                crcPerGlobal = NULL;

                #if defined( NXS_NOVACOM_API_UART_USE_TIMER ) && \
                    NXS_NOVACOM_API_UART_USE_TIMER == 1                
                /* Stop the timer */
                code = nxsTimerStop( &parserTimer, NULL );
                if( code != NXS_CODE_NO_ERROR ) {
                  
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to stop the timer." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    
                }
                #endif /* NXS_NOVACOM_API_UART_USE_TIMER == 1 */
                
                #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                    NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                NXS_WARNING( "Length too big." );
                #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */

                return NXS_CODE_ERROR;  
                
            }
            
            /* Update the status byte */
            parserStatus = NXS_API_UART_STX;
             
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_STX:
      
            /* Check if the byte that we get is the start of text, else
               we have a transmission error */
            if( c == NXS_API_UART_START_OF_TEXT ) {
              
                /* Update the status byte */
                parserStatus = NXS_API_UART_ETX;
        
            /* We didn't receive the start of text */
            } else {
              
                nxsMutexGive( &crcPeripheral->mutex );
                parserStatus = NXS_API_UART_SOH;
                crcPerGlobal = NULL;
                
                #if defined( NXS_NOVACOM_API_UART_USE_TIMER ) && \
                    NXS_NOVACOM_API_UART_USE_TIMER == 1                
                /* Stop the timer */
                code = nxsTimerStop( &parserTimer, NULL );
                if( code != NXS_CODE_NO_ERROR ) {
                  
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to stop the timer." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    
                }
                #endif /* NXS_NOVACOM_API_UART_USE_TIMER == 1 */

                #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                    NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                NXS_WARNING( "STX not found." );
                #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */

                return NXS_CODE_ERROR;   
                
            }
            
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_ETX:
          
            /* Check if we are at the end of the frame */
            if( parserLength == parserPayload_i ) {
              
                /* We expected and EOT character */
                if( c == NXS_API_UART_END_OF_TEXT ) {            

                    /* Complete by empty byte(s) */    
                    if( parserCRCCount != 0 ) 
                        crcPeripheral->data.crc32->crc32PutValue( parserCRCValue );

                    /* get crc 32 */
                    crcPeripheral->data.crc32->crc32Get( &parserCRCBuild );
                    
                    /* Release the resource and the mutex */
                    nxsMutexGive( &crcPeripheral->mutex );
                    crcPerGlobal = NULL;

                    /* Change the status to wait for the end of transmission */
                    parserStatus = NXS_API_UART_CRC_0;

                    break;

                /* If we don't receive the end of text character, we
                   have an error */
                } else {

                    /* Release the resource and the mutex */
                    nxsMutexGive( &crcPeripheral->mutex );
                    parserStatus = NXS_API_UART_SOH;
                    crcPerGlobal = NULL;
                    
                    #if defined( NXS_NOVACOM_API_UART_USE_TIMER ) && \
                        NXS_NOVACOM_API_UART_USE_TIMER == 1                
                    /* Stop the timer */
                    code = nxsTimerStop( &parserTimer, NULL );
                    if( code != NXS_CODE_NO_ERROR ) {
                      
                        #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                            NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                        NXS_WARNING( "Unable to stop the timer." );
                        #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                        
                    }
                    #endif /* NXS_NOVACOM_API_UART_USE_TIMER == 1 */
                    
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "EOF not found." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    
                    return NXS_CODE_ERROR;    
                    
                } 
                
            } else if( parserLength < parserPayload_i ) {

                /* Release the resource and the mutex */
                nxsMutexGive( &crcPeripheral->mutex );
                parserStatus = NXS_API_UART_SOH;
                crcPerGlobal = NULL;
                
                #if defined( NXS_NOVACOM_API_UART_USE_TIMER ) && \
                    NXS_NOVACOM_API_UART_USE_TIMER == 1                
                /* Stop the timer */
                code = nxsTimerStop( &parserTimer, NULL );
                if( code != NXS_CODE_NO_ERROR ) {
                  
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to stop the timer." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    
                }
                #endif /* NXS_NOVACOM_API_UART_USE_TIMER == 1 */

                #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                    NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                NXS_WARNING( "Payload length unexpected." );
                #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                return NXS_CODE_ERROR;                      
                
            }
          
            /* Append the received char to our reception buffer */
            parserPayload[parserPayload_i++] = c;
            
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_CRC_0:
                        
            /* Receive the crcResource of the frame to process */
            parserCrc = ( c << 24 );

            /* Update the status byte */
            parserStatus = NXS_API_UART_CRC_1;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_CRC_1:
                        
            /* Receive the crcResource of the frame to process */
            parserCrc += ( c << 16 );

            /* Update the status byte */
            parserStatus = NXS_API_UART_CRC_2;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_CRC_2:
                        
            /* Receive the crcResource of the frame to process */
            parserCrc += ( c << 8 );

            /* Update the status byte */
            parserStatus = NXS_API_UART_CRC_3;

            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_CRC_3:
  
            /* Receive the crcResource of the frame to process */
            parserCrc += c;
            
            /* Update the status byte */
            parserStatus = NXS_API_UART_EOT;
             
            break;
            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        case NXS_API_UART_EOT:

            /* If we don't receive the end of transmission character, we
               have an error */
            if( c != NXS_API_UART_END_OF_TRANSMISSION ) {
                
                /* Reset the uart status */
                parserStatus = NXS_API_UART_SOH;
                
                #if defined( NXS_NOVACOM_API_UART_USE_TIMER ) && \
                    NXS_NOVACOM_API_UART_USE_TIMER == 1                
                /* Stop the timer */
                code = nxsTimerStop( &parserTimer, NULL );
                if( code != NXS_CODE_NO_ERROR ) {
                  
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to stop the timer." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    
                }
                #endif /* NXS_NOVACOM_API_UART_USE_TIMER == 1 */
                
                #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                    NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                NXS_WARNING( "EOT not found." );
                #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
            
                return NXS_CODE_ERROR;
            
            } else {     
              
                /* Send to the dispatcher ( N/ACK + Dispatch ) */
                /* Stop the timer */
                #if defined( NXS_NOVACOM_API_UART_USE_TIMER ) && \
                    NXS_NOVACOM_API_UART_USE_TIMER == 1                
                code = nxsTimerStop( &parserTimer, NULL );
                if( code != NXS_CODE_NO_ERROR ) {

                    parserStatus = NXS_API_UART_SOH;
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to stop the timer." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    return NXS_CODE_ERROR;
                    
                }
                #endif /* NXS_NOVACOM_API_UART_USE_TIMER == 1 */


                /* Send generic frame */
                code = nxsBufferSync( parserPayload, parserLength, 
                                      parserLength, &parserBuffer );
                if( code != NXS_CODE_NO_ERROR ) {
                    
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to allocate field (Buffer)." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    return NXS_CODE_ERROR;
                    
                }
                
                #if defined( NXS_NOVACOM_API_MONITORING ) && \
                    NXS_NOVACOM_API_MONITORING == 1 
                bufferSize = sizeof( nxsBuffer_t )+ parserLength;
                nxsNCAPIDebugMonitorInc( bufferSize );
                #endif /* NXS_NOVACOM_API_MONITORING == 1 */

                /* Init API interface message */
                code = nxsNCAPIUARTMessageInit( NXS_API_UART_MESSAGE_NB_RETRIES_MAX, 
                                                parserCrc == parserCRCBuild, 
                                                parserSequenceID, parserOpcode, 
                                                parserToken, parserBuffer, 
                                                parserCrc, &message );
                if( code != NXS_CODE_NO_ERROR ) {

                    parserStatus = NXS_API_UART_SOH;

                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to initialize message (UART-API)." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */

                    nxsBufferFree(parserBuffer);

                    #if defined( NXS_NOVACOM_API_MONITORING ) && \
                        NXS_NOVACOM_API_MONITORING == 1 
                    nxsNCAPIDebugMonitorInc( bufferSize );
                    #endif /* NXS_NOVACOM_API_MONITORING == 1 */
                    return NXS_CODE_ERROR;
                    
                }

                /* Send API Interface message parsed to UART RX Controller */
                code = nxsNCAPIUARTCtrlRx( message );
                if( code != NXS_CODE_NO_ERROR ) {

                    parserStatus = NXS_API_UART_SOH;   
                    #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                        NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                    NXS_WARNING( "Unable to transmit message to UART CTRL." );
                    #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                    nxsNCAPIUARTMessageFree( message );
                    return NXS_CODE_ERROR;
                    
                }
                
                #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                    NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                NXS_INFO( "Message parsed - success." );
                if( parserCrc == parserCRCBuild ) NXS_INFO( "CRC32 -> OK" );
                else NXS_INFO( "CRC32 -> NOK" );
                #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */

                /* Reset the uart status */
                parserStatus = NXS_API_UART_SOH;   

                return NXS_CODE_NO_ERROR;   
                
            }           
            break;

            
        /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        default:
          
            /* Reset the uart status */
            parserStatus = NXS_API_UART_SOH;
            
            /* Stop the timer */
            #if NXS_NOVACOM_API_UART_USE_TIMER == 1                
            code = nxsTimerStop( &parserTimer, NULL );
            if( code != NXS_CODE_NO_ERROR ){

                parserStatus = NXS_API_UART_SOH;

                #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                    NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
                NXS_WARNING( "Unable to stop the timer." );
                #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */
                return NXS_CODE_ERROR;
                
            }
            #endif

            #if defined( NXS_NOVACOM_API_INTERFACE_UART_DEBUG ) && \
                NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1
            NXS_WARNING( "State unknown." );
            #endif /* NXS_NOVACOM_API_INTERFACE_UART_DEBUG == 1 */

            return NXS_CODE_ERROR;                      

    } 
    
    return NXS_CODE_NO_ERROR;
    
}
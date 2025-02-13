#ifndef __NRF24_H__
#define __NRF24_H__

#include "Arduino.h"
#include "RF24.h"
#include "define.h"

void Setup_NRF24( void );
void NRF24_SendMessage( uint8_t p_PushedID );

#endif /* NRF24_H */
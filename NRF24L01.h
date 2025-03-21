#ifndef __NRF24_H__
#define __NRF24_H__

#include "RF24.h"
#include "define.h"
#include <Arduino.h>

typedef struct
{
    uint8_t PlayStatus;
    uint8_t TruckNo;
    uint8_t PlayFolder;
} MSG;

typedef struct
{
    PinStatus Status;
    uint8_t   Stat = false;
    uint32_t  Time = 0U;
} VALID_PUSH;

void Setup_NRF24( void );
void NRF24_SendMessage( void );
bool NRF24_ReceiveMessage( MSG *p_Message );

#endif /* NRF24_H */
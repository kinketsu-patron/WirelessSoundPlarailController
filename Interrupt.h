#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "NRF24L01.h"
#include "define.h"
#include <Arduino.h>

void    Setup_Interrupt( void );
uint8_t Get_PushedID( void );

#endif
#include "Interrupt.h"

static void prev_pushed( void );
static void play_pushed( void );
static void next_pushed( void );
static void mode_pushed( void );

static volatile uint8_t m_PushedID = NONE;

void Setup_Interrupt( void )
{
    attachInterrupt( digitalPinToInterrupt( PREV_SW ), prev_pushed, FALLING );
    attachInterrupt( digitalPinToInterrupt( PLAY_SW ), play_pushed, FALLING );
    attachInterrupt( digitalPinToInterrupt( NEXT_SW ), next_pushed, FALLING );
    attachInterrupt( digitalPinToInterrupt( MODE_SW ), mode_pushed, FALLING );
}

static void prev_pushed( void )
{
    m_PushedID = PREV_ID;
}

static void play_pushed( void )
{
    m_PushedID = PLAY_ID;
}

static void next_pushed( void )
{
    m_PushedID = NEXT_ID;
}

static void mode_pushed( void )
{
    m_PushedID = MODE_ID;
}

uint8_t Intr_GetPushedID( void )
{
    uint8_t w_PushedID;

    w_PushedID = m_PushedID;
    m_PushedID = NONE;
    return w_PushedID;
}
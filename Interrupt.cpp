#include "Interrupt.h"

static void prev_pushed( void );
static void play_pushed( void );
static void next_pushed( void );
static void mode_pushed( void );
static bool allow_intrrput( uint32_t p_WaitTime, uint32_t *p_PrevTime );

void Setup_Interrupt( void )
{
    pinMode( PREV_PIN_NO, INPUT_PULLUP );
    pinMode( PLAY_PIN_NO, INPUT_PULLUP );
    pinMode( NEXT_PIN_NO, INPUT_PULLUP );
    pinMode( MODE_PIN_NO, INPUT_PULLUP );

    attachInterrupt( digitalPinToInterrupt( PREV_PIN_NO ), prev_pushed, FALLING );
    attachInterrupt( digitalPinToInterrupt( PLAY_PIN_NO ), play_pushed, FALLING );
    attachInterrupt( digitalPinToInterrupt( NEXT_PIN_NO ), next_pushed, FALLING );
    attachInterrupt( digitalPinToInterrupt( MODE_PIN_NO ), mode_pushed, FALLING );
}

static void prev_pushed( void )
{
    static uint32_t l_Prevtime = 0U;  // 前回時間を初期化する

    if ( allow_intrrput( CHATTER_WAIT, &l_Prevtime ) == true )  // 前回の割り込みから所定時間経っていれば
    {
        NRF24_SendMessage( PREV_ID );
        USB_Serial.println( "Prev" );
    }
}

static void play_pushed( void )
{
    static uint32_t l_Prevtime = 0U;  // 前回時間を初期化する

    if ( allow_intrrput( CHATTER_WAIT, &l_Prevtime ) == true )  // 前回の割り込みから所定時間経っていれば
    {
        NRF24_SendMessage( PLAY_ID );
        USB_Serial.println( "Play" );
    }
}

static void next_pushed( void )
{
    static uint32_t l_Prevtime = 0U;  // 前回時間を初期化する

    if ( allow_intrrput( CHATTER_WAIT, &l_Prevtime ) == true )  // 前回の割り込みから所定時間経っていれば
    {
        NRF24_SendMessage( NEXT_ID );
        USB_Serial.println( "Next" );
    }
}

static void mode_pushed( void )
{
    static uint32_t l_Prevtime = 0U;  // 前回時間を初期化する

    if ( allow_intrrput( CHATTER_WAIT, &l_Prevtime ) == true )  // 前回の割り込みから所定時間経っていれば
    {
        NRF24_SendMessage( MODE_ID );
        USB_Serial.println( "ModeChange" );
    }
}

/**
 * =======================================================
 * @fn          allow_intrrput
 * @brief       前回の割り込みからの所定時間経過判定
 * @date        2025-02-13
 * =======================================================
 */
static bool allow_intrrput( uint32_t p_WaitTime, uint32_t *p_PrevTime )
{
    ulong32 l_Interval;
    bool    l_Allow;

    l_Interval = millis( ) - *p_PrevTime;  // 前回の割込みからの経過時間を計算する

    if ( l_Interval >= p_WaitTime )  // 割込み待ち時間が所定時間を超えていたら
    {
        l_Allow     = true;
        *p_PrevTime = millis( );  // 前回時間を更新しておく
    }
    else
    {
        l_Allow = false;
    }

    return l_Allow;
}
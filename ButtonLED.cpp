#include "ButtonLED.h"

void BTN_PrevON( void )
{
    digitalWrite( PREV_LED, HIGH );
}

void BTN_PlayON( void )
{
    digitalWrite( PLAY_LED, HIGH );
}

void BTN_PlayBlink( void )
{
    static uint32_t w_PrevTime = 0U;
    static bool     w_Output   = LOW;
    uint32_t        w_Interval;

    w_Interval = millis( ) - w_PrevTime;  // 前回の割込みからの経過時間を計算する
    if ( w_Interval >= 1000 )             // 1000ミリ秒以上経過したら
    {
        digitalWrite( PLAY_LED, w_Output );
        w_Output   = !w_Output;
        w_PrevTime = millis( );  // 前回時間を更新しておく
    }
}

void BTN_NextON( void )
{
    digitalWrite( NEXT_LED, HIGH );
}

void BTN_AllOff( void )
{
    digitalWrite( PREV_LED, LOW );
    digitalWrite( PLAY_LED, LOW );
    digitalWrite( NEXT_LED, LOW );
}
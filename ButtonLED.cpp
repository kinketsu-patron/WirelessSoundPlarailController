#include "ButtonLED.h"

void BTN_PrevON( void )
{
    digitalWrite( PREV_LED, HIGH );
    digitalWrite( PLAY_LED, LOW );
    digitalWrite( NEXT_LED, LOW );
}

void BTN_PlayON( void )
{
    digitalWrite( PREV_LED, LOW );
    digitalWrite( PLAY_LED, HIGH );
    digitalWrite( NEXT_LED, LOW );
}

void BTN_NextON( void )
{
    digitalWrite( PREV_LED, LOW );
    digitalWrite( PLAY_LED, LOW );
    digitalWrite( NEXT_LED, HIGH );
}

void BTN_AllOff( void )
{
    digitalWrite( PREV_LED, LOW );
    digitalWrite( PLAY_LED, LOW );
    digitalWrite( NEXT_LED, LOW );
}
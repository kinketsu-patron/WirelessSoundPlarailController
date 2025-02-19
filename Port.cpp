#include "Port.h"

void Setup_Port( void )
{
    pinMode( PREV_LED, OUTPUT );
    pinMode( PLAY_LED, OUTPUT );
    pinMode( NEXT_LED, OUTPUT );
    pinMode( MODE_LED, OUTPUT );
    pinMode( POWER_LED, OUTPUT );
    pinMode( PREV_SW, INPUT_PULLUP );
    pinMode( PLAY_SW, INPUT_PULLUP );
    pinMode( NEXT_SW, INPUT_PULLUP );
    pinMode( MODE_SW, INPUT_PULLUP );
    pinMode( SDA_I2C, INPUT );  // 内部プルアップを無効化
    pinMode( SCL_I2C, INPUT );  // 内部プルアップを無効化
}
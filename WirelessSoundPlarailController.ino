/**
 * =============================================================
 * @file        WirelessSoundPlarailController.ino
 * @author      kinketsu patron (https://kinketsu-patron.com)
 * @brief       メインファイル
 * @version     1.0
 * @date        2025-02-10
 * =============================================================
 */

// =======================================================
// ヘッダインクルード
// =======================================================
#include "Arduino.h"
#include "RF24.h"
#include <SPI.h>

// =======================================================
// DEFINE定義
// =======================================================
#define USB_Serial Serial
#define PREV_PIN   D0
#define PLAY_PIN   D1
#define NEXT_PIN   D2
#define MODE_PIN   D3
#define CE_PIN     D7
#define CSN_PIN    D8

// =======================================================
// オブジェクト
// =======================================================
static RF24 m_NRFRadio( CE_PIN, CSN_PIN );

// =======================================================
// メンバ変数
// =======================================================
static const byte m_Address[ 6 ] = "NODE1";

/**
 * =======================================================
 * @fn         setup
 * @brief      初期化を行う
 * @date        2025-02-11
 * =======================================================
 */
void setup( void )
{
    pinMode( PREV_PIN, INPUT_PULLUP );
    pinMode( PLAY_PIN, INPUT_PULLUP );
    pinMode( NEXT_PIN, INPUT_PULLUP );
    pinMode( MODE_PIN, INPUT_PULLUP );

    USB_Serial.begin( 115200 );  // USBデータ通信の通信速度

    if ( m_NRFRadio.begin( ) == 0 )
    {
        Serial.println( F( "radio hardware is not responding!!" ) );
        while ( true )
        {
            delay( 0 );
        }
    }

    m_NRFRadio.setPALevel( RF24_PA_MIN );
    m_NRFRadio.openWritingPipe( m_Address );
    m_NRFRadio.stopListening( );
}

/**
 * =======================================================
 * @fn         loop
 * @brief      繰り返し処理を行う
 * @date        2025-02-11
 * =======================================================
 */
void loop( void )
{
    static bool w_HasPushed[ 4 ];

    if ( digitalRead( PLAY_PIN ) == LOW )
    {
        w_HasPushed[ 0 ] = false;
        w_HasPushed[ 1 ] = true;
        w_HasPushed[ 2 ] = false;
        w_HasPushed[ 3 ] = false;
    }
    else if ( digitalRead( PREV_PIN ) == LOW )
    {
        w_HasPushed[ 0 ] = true;
        w_HasPushed[ 1 ] = false;
        w_HasPushed[ 2 ] = false;
        w_HasPushed[ 3 ] = false;
    }
    else if ( digitalRead( NEXT_PIN ) == LOW )
    {
        w_HasPushed[ 0 ] = false;
        w_HasPushed[ 1 ] = false;
        w_HasPushed[ 2 ] = true;
        w_HasPushed[ 3 ] = false;
    }
    else if ( digitalRead( MODE_PIN ) == LOW )
    {
        w_HasPushed[ 0 ] = false;
        w_HasPushed[ 1 ] = false;
        w_HasPushed[ 2 ] = false;
        w_HasPushed[ 3 ] = true;
    }
    else
    {
        w_HasPushed[ 0 ] = false;
        w_HasPushed[ 1 ] = false;
        w_HasPushed[ 2 ] = false;
        w_HasPushed[ 3 ] = false;
    }

    m_NRFRadio.write( &w_HasPushed, sizeof( w_HasPushed ) );
    delay( 50 );
}
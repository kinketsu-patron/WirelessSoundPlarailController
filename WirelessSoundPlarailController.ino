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
#include "ButtonLED.h"
#include "Interrupt.h"
#include "NRF24L01.h"
#include "OLED.h"
#include "Port.h"
#include "define.h"

/**
 * =======================================================
 * @fn         setup
 * @brief      初期化を行う
 * @date        2025-02-11
 * =======================================================
 */
void setup( void )
{
    USB_Serial.begin( 115200 );       // USBデータ通信の通信速度
    Setup_Port( );                    // ポートの初期設定
    digitalWrite( POWER_LED, HIGH );  // 電源LEDを点ける
    Setup_OLED( );                    // ディスプレイの初期設定
    SplashMovie_Start( );             // スプラッシュ画面開始
    Setup_Interrupt( );               // 割り込み初期設定
    Setup_NRF24( );                   // 無線通信設定
    delay( 2000 );                    // 3秒待つ
    SplashMovie_Stop( );              // スプラッシュ画面を消す
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
    // u8g2.clearBuffer( );
    // u8g2.drawXBMP( 0, 0, 72, 24, Tsugiha );
    // u8g2.drawXBMP( 32, 32, 96, 32, Kakogawa );
    // u8g2.sendBuffer( );
    // digitalWrite( MODE_LED, HIGH );

    // delay( 500 );

    // u8g2.clearBuffer( );
    // u8g2.drawXBMP( 0, 0, 72, 24, Tsugiha );
    // u8g2.sendBuffer( );
    // digitalWrite( MODE_LED, LOW );

    // delay( 500 );
    MSG     w_Message;
    uint8_t w_PushedID;

    w_Message = NRF24_ReceiveMessage( );
    switch ( w_Message.PlayStatus )
    {
        case IN_PREV:
            BTN_PrevON( );
            break;
        case IN_PLAY:
            BTN_PlayON( );
            break;
        case IN_PAUSE:
            BTN_PlayBlink( );
            break;
        case IN_NEXT:
            BTN_NextON( );
            break;
        default:
            BTN_AllOff( );
            break;
    }
    delay( 50 );

    w_PushedID = Get_PushedID( );
    if ( w_PushedID != NONE )
    {
        NRF24_SendMessage( w_PushedID );
        USB_Serial.println( "SendPushedID" );
    }
    delay( 50 );
}
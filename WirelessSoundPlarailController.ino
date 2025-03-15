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
    MSG w_Message;

    w_Message = NRF24_ReceiveMessage( );
    switch ( w_Message.PlayStatus )
    {
        case IN_PREV:
            BTN_PrevON( );
            //ShowDisplay( w_Message.TruckNo, w_Message.PlayFolder );
            break;
        case IN_PLAY:
            BTN_PlayON( );
            //ShowDisplay( w_Message.TruckNo, w_Message.PlayFolder );
            break;
        case IN_NEXT:
            BTN_NextON( );
            //ShowDisplay( w_Message.TruckNo, w_Message.PlayFolder );
            break;
        default:
            BTN_AllOff( );
            //TurnOffDisplay( );
            break;
    }
    delay( 50 );
}
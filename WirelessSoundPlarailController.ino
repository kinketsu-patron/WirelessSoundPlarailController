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
    USB_Serial.begin( 115200 );  // USBデータ通信の通信速度
    Setup_Port( );               // ポートの初期設定
    Setup_NRF24( );              // 無線通信設定
    Setup_OLED( );               // ディスプレイの初期設定
    Setup_Interrupt( );
    SplashMovie_Start( );  // スプラッシュ画面開始

    delay( 1500 );  // 1.5秒待つ

    digitalWrite( POWER_LED, HIGH );  // 電源LEDを点ける
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
    static uint8_t   w_Wait = 0U;
    MSG              w_Message;
    volatile uint8_t w_PushedID;
    bool             w_IsReceived;

    delay( 100 );

    noInterrupts( );
    w_PushedID = Intr_GetPushedID( );
    interrupts( );

    if ( w_PushedID == MODE_ID )
    {
        NRF24_SendMessage( w_PushedID );
        w_Wait = 20U;
    }

    if ( w_Wait > 0U )
    {
        w_PushedID = NONE;
        w_Wait--;
    }
    NRF24_SendMessage( w_PushedID );

    delay( 100 );
    w_IsReceived = NRF24_ReceiveMessage( &w_Message );
    if ( w_IsReceived == true )
    {
        switch ( w_Message.PlayStatus )
        {
            case IN_PREV:
                BTN_PrevON( );
                ShowDisplay( w_Message.TruckNo, w_Message.PlayFolder );
                break;
            case IN_PLAY:
                BTN_PlayON( );
                ShowDisplay( w_Message.TruckNo, w_Message.PlayFolder );
                break;
            case IN_NEXT:
                BTN_NextON( );
                ShowDisplay( w_Message.TruckNo, w_Message.PlayFolder );
                break;
            default:
                if ( w_Wait > 0U && w_Wait < 18U )
                {
                    ShowModeChange( w_Message.PlayFolder );
                    BTN_ModeON( );
                }
                else
                {
                    ShowStandby( );
                    BTN_AllOff( );
                }
                break;
        }
        USB_Serial.print( "PlayStatus = " );
        USB_Serial.print( w_Message.PlayStatus );
        USB_Serial.print( ", TruckNo = " );
        USB_Serial.print( w_Message.TruckNo );
        USB_Serial.print( ", PlayFolder = " );
        USB_Serial.println( w_Message.PlayFolder );
    }
}
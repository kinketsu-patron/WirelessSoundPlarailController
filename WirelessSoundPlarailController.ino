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
#include "Interrupt.h"
#include "Port.h"
#include "RF24.h"
#include "define.h"
#include <SPI.h>

/**
 * =======================================================
 * @fn         setup
 * @brief      初期化を行う
 * @date        2025-02-11
 * =======================================================
 */
void setup( void )
{
    Setup_Port( );
    Setup_Interrupt( );
    Setup_NRF24( );
    USB_Serial.begin( 115200 );       // USBデータ通信の通信速度
    digitalWrite( POWER_LED, HIGH );  // 電源LEDを点ける
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
    /* Nothing */
}
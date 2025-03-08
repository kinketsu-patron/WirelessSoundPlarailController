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
#include "StationName.h"
#include "define.h"
#include <SPI.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2( U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE );

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
    Setup_Port( );
    Setup_Interrupt( );
    Setup_NRF24( );
    digitalWrite( POWER_LED, HIGH );  // 電源LEDを点ける

    u8g2.begin( );
    u8g2.enableUTF8Print( );
    u8g2.setBitmapMode( false /* solid */ );
    //u8g2.setFont( u8g2_font_b10_b_t_japanese1 );
    u8g2.setFontDirection( 0 );
    u8g2.setContrast( 255 );
    u8g2.setFlipMode( 0 );
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
    u8g2.clearBuffer( );
    u8g2.drawXBMP( 0, 0, 72, 24, Tsugiha );
    u8g2.drawXBMP( 32, 32, 96, 32, Kakogawa );
    u8g2.sendBuffer( );

    delay( 500 );

    u8g2.clearBuffer( );
    u8g2.drawXBMP( 0, 0, 72, 24, Tsugiha );
    u8g2.sendBuffer( );

    delay( 500 );
}
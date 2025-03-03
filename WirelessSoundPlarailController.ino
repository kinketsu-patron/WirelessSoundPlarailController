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
#include <Adafruit_GFX.h>      //Adarfuitの画像描写ライブラリーを読み込む
#include <Adafruit_SSD1306.h>  //AdarfuitのSSD1306用ライブラリーを読み込む
#include <SPI.h>

const int SCREEN_WIDTH   = 128;   //ディスプレイのサイズ指定
const int SCREEN_HEIGHT  = 64;    //ディスプレイのサイズ指定
const int SCREEN_ADDRESS = 0x3C;  //I2Cのアドレス指定

Adafruit_SSD1306 display( SCREEN_WIDTH, SCREEN_HEIGHT,
                          &Wire );  //ディスプレイ制御用のインスタンスを作成。この時にデイスプレのサイズを渡す。

int count = 1;  //countを整数型の変数として定義

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

    display.begin( SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS );  //ディスプレイを初期化。この時にI2Cアドレスを渡す。
    display.clearDisplay( );                                //画面描写エリアを削除。
    display.display( );  //画面描写エリアをディスプレイに転送。ここで全画面を削除。
    delay( 1000 );       //1秒待機
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
    digitalWrite( PREV_LED, HIGH );
    delay( 200 );
    digitalWrite( PREV_LED, LOW );
    digitalWrite( PLAY_LED, HIGH );
    delay( 200 );
    digitalWrite( PLAY_LED, LOW );
    digitalWrite( NEXT_LED, HIGH );
    delay( 200 );
    digitalWrite( NEXT_LED, LOW );
    digitalWrite( MODE_LED, HIGH );
    delay( 200 );
    digitalWrite( MODE_LED, LOW );

    display.clearDisplay( );
    display.setTextSize( 2 );                              //フォントサイズ指定。
    display.setTextColor( SSD1306_BLACK, SSD1306_WHITE );  //display.setTextColor( 文字本体の色, 背景の色)
    display.setCursor( 15, 10 );                           //描写開始座標（X.Y）
    display.print( " HIBIKI " );                           //("")内を表示する。
    display.setCursor( 0, 30 );
    display.setTextColor( SSD1306_WHITE, SSD1306_BLACK );
    display.setTextSize( 1 );
    display.println( " MicroMouse " );  //printの後ろにlnが付くことで表示した後に改行する。
    display.print( " Enjoy! " );
    display.setCursor( 10, 55 );
    display.print( "Count:" );
    display.print( count );  //変数の中身を表示する。
    display.display( );      //上記で設定したprint()をディスプレイに転送し表示する。
    delay( 1000 );
    count = count + 1;  //ループを１回通るごとに１づつたされる。
}
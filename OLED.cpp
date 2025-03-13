#include "OLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2( U8G2_R0, /* reset=*/U8X8_PIN_NONE );

void Setup_OLED( void )
{
    /* 初期設定 */
    u8g2.begin( );
    u8g2.enableUTF8Print( );
    u8g2.setBitmapMode( false /* solid */ );
    u8g2.setFont( u8g2_font_ncenB08_tr );
    u8g2.setFontDirection( 0 );
    u8g2.setContrast( 255 );
    u8g2.setFlipMode( 0 );
}

void SplashMovie_Start( void )
{
    u8g2.clearBuffer( );
    u8g2.drawXBMP( 0, 0, 128, 64, OpeningMovie );
    u8g2.sendBuffer( );
}

void SplashMovie_Stop( void )
{
    u8g2.clearBuffer( );
    u8g2.sendBuffer( );
}

void ShowDisplay( void )
{
    u8g2.clearBuffer( );
    u8g2.drawXBMP( 0, 0, 72, 24, Tsugiha );
    u8g2.drawXBMP( 32, 32, 96, 32, Kakogawa );
    u8g2.sendBuffer( );
}
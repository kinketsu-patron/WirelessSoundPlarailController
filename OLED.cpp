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

void ShowDisplay( uint8_t p_TruckNo, uint8_t p_PlayFolder )
{
    static ARROW    w_ArrowStatus = MIN;
    static uint8_t *w_Arrow;

    u8g2.clearBuffer( );
    u8g2.drawXBMP( 0, 0, 72, 24, Station_DispData[ p_PlayFolder - 1 ][ p_TruckNo - 1 ].Prefix );
    switch ( w_ArrowStatus )
    {
        case MIN:
            w_Arrow       = Arrow_Min;
            w_ArrowStatus = MID;
            break;
        case MID:
            w_Arrow       = Arrow_Mid;
            w_ArrowStatus = MAX;
            break;
        case MAX:
            w_Arrow       = Arrow_Max;
            w_ArrowStatus = MIN;
            break;
        default:
            break;
    }
    u8g2.drawXBMP( 0, 40, 32, 24, w_Arrow );
    u8g2.drawXBMP( 32, 32, 96, 32, Station_DispData[ p_PlayFolder - 1 ][ p_TruckNo - 1 ].Name );
    u8g2.sendBuffer( );
}

void TurnOffDisplay( void )
{
    u8g2.clearBuffer( );
    u8g2.sendBuffer( );
}
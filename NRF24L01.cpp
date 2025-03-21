#include "NRF24L01.h"

// =======================================================
// オブジェクト
// =======================================================
static RF24 m_NRFRadio( CE_NO, CSN_NO );

static const byte m_Address_ToTrain[ 6 ]      = "TOTRN";
static const byte m_Address_ToController[ 6 ] = "TOCTL";

/**
 * =======================================================
 * @fn          Setup_NRF24
 * @brief       初期化
 * @date        2025-02-13
 * =======================================================
 */
void Setup_NRF24( void )
{
    if ( m_NRFRadio.begin( ) == 0 )
    {
        USB_Serial.println( F( "radio hardware is not responding!!" ) );
        while ( true )
        {
            delay( 0 );
        }
    }

    m_NRFRadio.setPALevel( RF24_PA_MIN );
    m_NRFRadio.openWritingPipe( m_Address_ToTrain );
    m_NRFRadio.openReadingPipe( 1, m_Address_ToController );
}

void NRF24_SendMessage( uint8_t p_PushedID )
{
    if ( p_PushedID == PREV_ID )
    {
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "Prev" );
    }
    else if ( p_PushedID == PLAY_ID )
    {
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "Play" );
    }
    else if ( p_PushedID == NEXT_ID )
    {
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "Next" );
    }
    else if ( p_PushedID == MODE_ID )
    {
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "ModeChange" );
    }
    else
    {
        /* 何もしない */
    }
}

bool NRF24_ReceiveMessage( MSG *p_Message )
{
    bool w_Result = false;

    m_NRFRadio.startListening( );      // 受信を開始
    while ( m_NRFRadio.available( ) )  // 読み取り可能なバイトがあれば
    {
        m_NRFRadio.read( p_Message, sizeof( *p_Message ) );
        w_Result = true;
    }
    return w_Result;
}
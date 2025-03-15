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
    m_NRFRadio.openReadingPipe( 0, m_Address_ToController );
}

void NRF24_SendMessage( uint8_t p_PushedID )
{
    m_NRFRadio.stopListening( );                            // 受信を停止
    m_NRFRadio.write( &p_PushedID, sizeof( p_PushedID ) );  // PushedIDを送信
}

MSG NRF24_ReceiveMessage( void )
{
    MSG w_Message;

    noInterrupts( );
    m_NRFRadio.startListening( );      // 受信を開始
    while ( m_NRFRadio.available( ) )  // 読み取り可能なバイトがあれば
    {
        m_NRFRadio.read( &w_Message, sizeof( w_Message ) );  //
    }
    interrupts( );
    return w_Message;
}
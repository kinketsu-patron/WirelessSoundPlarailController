#include "NRF24L01.h"

// =======================================================
// オブジェクト
// =======================================================
static RF24 m_NRFRadio( CE_NO, CSN_NO );

// =======================================================
// メンバ変数
// =======================================================
static const byte m_Address[ 6 ] = "NODE1";

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
        Serial.println( F( "radio hardware is not responding!!" ) );
        while ( true )
        {
            delay( 0 );
        }
    }

    m_NRFRadio.setPALevel( RF24_PA_MIN );
    m_NRFRadio.openWritingPipe( m_Address );
    m_NRFRadio.stopListening( );
}

void NRF24_SendMessage( uint8_t p_PushedID )
{
    m_NRFRadio.write( &p_PushedID, sizeof( p_PushedID ) );
}
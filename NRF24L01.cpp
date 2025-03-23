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

    m_NRFRadio.setPALevel( RF24_PA_LOW );
    //m_NRFRadio.setPayloadSize( sizeof( uint8_t ) );
    m_NRFRadio.openWritingPipe( m_Address_ToTrain );
    m_NRFRadio.openReadingPipe( 1, m_Address_ToController );
}

void NRF24_SendMessage( uint8_t p_PushedID )
{
    uint32_t w_StartTimer, w_EndTimer;
    bool     w_Report = false;

    w_StartTimer = micros( );
    if ( p_PushedID == PREV_ID )
    {
        m_NRFRadio.stopListening( );                                      // 受信を停止
        w_Report   = m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        w_EndTimer = micros( );
    }
    if ( p_PushedID == PLAY_ID )
    {
        m_NRFRadio.stopListening( );                                      // 受信を停止
        w_Report   = m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        w_EndTimer = micros( );
    }
    if ( p_PushedID == NEXT_ID )
    {
        m_NRFRadio.stopListening( );                                      // 受信を停止
        w_Report   = m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        w_EndTimer = micros( );
    }
    if ( p_PushedID == MODE_ID )
    {
        m_NRFRadio.stopListening( );                                      // 受信を停止
        w_Report   = m_NRFRadio.write( &p_PushedID, sizeof( uint8_t ) );  // IDを送信
        w_EndTimer = micros( );
    }

    if ( w_Report )
    {
        USB_Serial.print( F( "Transmission successful! " ) );  // payload was delivered
        USB_Serial.print( F( "Time to transmit = " ) );
        USB_Serial.print( w_EndTimer - w_StartTimer );  // print the timer result
        USB_Serial.print( F( " us. Sent: " ) );
        if ( p_PushedID == 1U )
        {
            USB_Serial.println( "PREV" );
        }
        if ( p_PushedID == 2U )
        {
            USB_Serial.println( "PLAY" );
        }
        if ( p_PushedID == 3U )
        {
            USB_Serial.println( "NEXT" );
        }
        if ( p_PushedID == 4U )
        {
            USB_Serial.println( "MODE" );
        }
    }
}

bool NRF24_ReceiveMessage( MSG *p_Message )
{
    uint8_t w_Pipe;
    uint8_t w_Bytes;
    bool    w_Result = false;

    m_NRFRadio.startListening( );           // 受信を開始
    if ( m_NRFRadio.available( &w_Pipe ) )  // 読み取り可能なバイトがあれば
    {
        w_Bytes = m_NRFRadio.getPayloadSize( );  // get the size of the payload
        m_NRFRadio.read( p_Message, sizeof( *p_Message ) );
        USB_Serial.print( F( "Received " ) );
        USB_Serial.print( w_Bytes );  // print the size of the payload
        USB_Serial.print( F( " bytes on pipe " ) );
        USB_Serial.println( w_Pipe );  // print the pipe number
        // USB_Serial.print( F( ": " ) );
        // USB_Serial.println( payload );  // print the payload's value
        w_Result = true;
    }
    return w_Result;
}
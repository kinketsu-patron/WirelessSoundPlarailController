#include "NRF24L01.h"

// =======================================================
// オブジェクト
// =======================================================
static RF24 m_NRFRadio( CE_NO, CSN_NO );
static bool IsPushed( VALID_PUSH *p_ValidPush );

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

void NRF24_SendMessage( void )
{
    uint8_t           w_PushedID = NONE;
    static VALID_PUSH w_PrevValid, w_PlayValid, w_NextValid, w_ModeValid;

    w_PrevValid.Status = digitalRead( PREV_SW );
    if ( IsPushed( &w_PrevValid ) )
    {
        w_PushedID = PREV_ID;
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &w_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "Prev" );
    }

    w_PlayValid.Status = digitalRead( PLAY_SW );
    if ( IsPushed( &w_PlayValid ) )
    {
        w_PushedID = PLAY_ID;
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &w_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "Play" );
    }

    w_NextValid.Status = digitalRead( NEXT_SW );
    if ( IsPushed( &w_NextValid ) )
    {
        w_PushedID = NEXT_ID;
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &w_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "Next" );
    }

    w_ModeValid.Status = digitalRead( MODE_SW );
    if ( IsPushed( &w_ModeValid ) )
    {
        w_PushedID = MODE_ID;
        m_NRFRadio.stopListening( );                         // 受信を停止
        m_NRFRadio.write( &w_PushedID, sizeof( uint8_t ) );  // IDを送信
        USB_Serial.println( "ModeChange" );
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

static bool IsPushed( VALID_PUSH *p_ValidPush )
{
    bool w_Result = false;

    if ( p_ValidPush->Status == HIGH )
    {
        if ( p_ValidPush->Stat == false )
            p_ValidPush->Time = millis( );

        p_ValidPush->Stat = true;
    }
    else
    {
        if ( p_ValidPush->Stat == true && millis( ) - p_ValidPush->Time >= CHATTER_WAIT )
        {
            w_Result = true;
        }
        p_ValidPush->Stat = false;
    }

    return w_Result;
}
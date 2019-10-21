#include <xc.h>
#include "SERIAL.h"

//unsigned char * ptrSerialIn;
//unsigned char * ptrSerialOut;
//unsigned char   lenSerialIO;

// ************************** HAL
volatile SERIALIObits_t SERIALIO __at(SERIALIO_ADDRS);

void initSerialIO(void)
{
//    ptrSerialIn = ptrIn;
//    ptrSerialOut = ptrOut;
//    lenSerialIO = length;
// ************************** Serial IO Shift/Load
    PORTEbits.RE0 = 0;
    ANSELbits.ANS5 = 0;
    TRISEbits.TRISE0 = 0;

// ************************** Serial IO Clock
    PORTEbits.RE1 = 0;
    ANSELbits.ANS6 = 0;
    TRISEbits.TRISE1 = 0;

// ************************** Serial IO Output
    PORTEbits.RE2 = 0;
    ANSELbits.ANS7 = 0;
    TRISEbits.TRISE2 = 0;

// ************************** Serial IO Input
    PORTAbits.RA0;
    TRISAbits.TRISA0 = 1;
    ANSELbits.ANS0 = 0;
    
    
    SERIALIO.CLK = 0;
    SERIALIO.OUT = 0;
    SERIALIO.SHLD = 1;
    
}


void serialOut( unsigned char d )
{
    unsigned char i = 0x80;

    SERIALIO.SHLD = 1;
    while( i )
    {
        SERIALIO.CLK = 0;
        if(d & i)
            SERIALIO.OUT = 1;
        else
            SERIALIO.OUT = 0;
        SERIALIO.CLK = 1;
        i >>= 1;
    }
    SERIALIO.SHLD = 0;
    SERIALIO.CLK = 0;
    SERIALIO.SHLD = 1;
}


unsigned char serialIn( void )
{
    unsigned char i;
    unsigned char dado = 0;
    
    SERIALIO.SHLD = 0;
    i = 0x80;
     SERIALIO.SHLD = 1;
    while( i )
    {
        SERIALIO.CLK = 0;
        if( PORTAbits.RA0 )
            dado |= i;
        i >>= 1;
        SERIALIO.CLK = 1;
        
        
    }
   
    return( dado );
}


//void serialIOload( void )
//{
//    SERIALIO.SHLD = 0;
//    SERIALIO.SHLD = 1;
//}
//unsigned char serialIObyteShift( unsigned char dataIn )
//{
//    unsigned char dataBit;
//    unsigned char dataOut;
//
//    dataBit = 0x80;
//    dataOut = 0;
//
//    while( dataBit )
//    {
//        SERIALIO.CLK = 0;
//        if( dataIn & dataBit )
//            SERIALIO.OUT = 1;
//        else
//            SERIALIO.OUT = 0;
//
//        if( SERIALIO.IN )
//            dataOut |= dataBit;
//        SERIALIO.CLK = 1;
//        dataBit >>= 1;
//    }
//    SERIALIO.CLK = 0;
//    return( dataOut );
//}

// ************************** Interface Serial IO
//void serialIO( void )
//{
//    unsigned char i,j;
//    j = lenSerialIO - 1;
//    serialIOload();
//    for( i=0; i<lenSerialIO; i++ )
//    {
//        ptrSerialIn[i] = serialIObyteShift( ptrSerialOut[j-i]);
//    }
//    serialIOload();
//}
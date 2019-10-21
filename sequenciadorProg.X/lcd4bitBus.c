/*
 * File:   lcd.c
 * Author: sn1011701
 *
 * Created on 23 de Abril de 2019, 15:47
 */

#include <xc.h>
#include "config.h"
#include "lcd4bitBus.h"

volatile LCDbits_t LCD4b __at(LCD4b_ADDRS);

void LCD4b_cmd( unsigned char cmd )
{
    volatile REGnibble_t nibble;
    
    
    nibble.HILO = cmd;
    LCD4b.RS = 0;
    LCD4b.BUS = nibble.HI;

    LCD4b.EN = 0;
    if( cmd == LCD_CLEAR || cmd == LCD_HOME )
        __delay_ms( 2 );
    else
        __delay_us( 40 );
    LCD4b.EN = 1;
    

    if( cmd != (LCD_DATA_BITS_4) )
    {
        LCD4b.RS = 0;
        LCD4b.BUS = nibble.LO;
        LCD4b.EN = 0;
        if( cmd == LCD_CLEAR || cmd == LCD_HOME )
            __delay_ms( 2 );
        else
            __delay_us( 40 );
        LCD4b.EN = 1;
    }
}

void LCD4b_put( unsigned char c )
{
    volatile REGnibble_t nibble;
    
    nibble.HILO = c;

    LCD4b.RS = 1;
    LCD4b.BUS = nibble.HI;
    LCD4b.EN = 0;
    __delay_us( 40 );
    LCD4b.EN = 1;

    LCD4b.RS = 1;
    LCD4b.BUS = nibble.LO;
    LCD4b.EN = 0;
    __delay_us( 40 );
    LCD4b.EN = 1;
}

void gotoxy( unsigned char x, unsigned char y )
{
    LCD4b_cmd((LCD_GOTOL0 | LCD_GOTOL1*y) + (x & 0x3F) );
}

void writeLCD4b( unsigned char x, unsigned char y, const char * ptr )
{
    gotoxy(x,y);
    while( *ptr )
      LCD4b_put( *ptr++ );
}

void initLCD4b( void )
{
    LCD4b.BUS = 0;
    LCD4b.RS = 0;
    LCD4b.EN = 1;
    TRISD = 0xC0;
    
    LCD4b_cmd(LCD_DATA_BITS_4);
    LCD4b_cmd(LCD_LINE2);
    LCD4b_cmd(LCD_ON);
    LCD4b_cmd(LCD_CLEAR);
    LCD4b_cmd(LCD_HOME);
 
}


char lcdb0( void )
{
    return( LCD4b.B0 );
}


char lcdb1( void )
{
    return( LCD4b.B1 );
}



void intTOstr( int ui16, char * str )
{
    for(int div=10000; div>=1; div/=10 )
    {
        *str = (ui16 / div) + '0';
        ui16 = ui16 % div;
        ++str;
    }
    *str = 0;
}

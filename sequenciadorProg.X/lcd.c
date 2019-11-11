/* 
 * File:   lcd.c
 * Author: 18175242
 *
 * Created on 22 de Agosto de 2019, 16:03
 */

#include <xc.h>
#include "config.h"
#include "lcd.h"


volatile  LCDbits_t LCD __at(0x008);  

void initLCD( void )
    {
        LCD.B0  = 0;
        LCD.B1  = 0;
        LCD.RS  = 0;
        LCD.BUS = 0x3;
        LCD.EN  = 1;
        TRISD = 0xC0;
        
        __delay_ms(100);
        
        cmdLCD(LCD_DATA_BITS_4);
        cmdLCD(LCD_LINE2);
        cmdLCD(LCD_ON);
        cmdLCD(LCD_CLEAR);
        cmdLCD(LCD_HOME);
        
        __delay_ms(100);
    }

void cmdLCD( unsigned char cmd )
{
        volatile REGnibble_t nibble;
   
        nibble.HILO = cmd;
        LCD.RS = 0;
        LCD.BUS = nibble.HI ;
         LCD.EN = 0;
        if( cmd == LCD_CLEAR || cmd == LCD_HOME )   
        __delay_ms(2);
        else 
        __delay_us(40);    
        LCD.EN = 1;
   
        if( cmd != (LCD_DATA_BITS_4) )
    {
       LCD.RS = 0;
       LCD.BUS = nibble.LO;
       LCD.EN = 0;
       if( cmd == LCD_CLEAR || cmd == LCD_HOME )
            __delay_ms(2);
       else
            __delay_us(40);    
       LCD.EN = 1;
    }
}
void putLCD( unsigned char c )
 {
        volatile REGnibble_t nibble;
   
        nibble.HILO = c;
        LCD.RS = 1;
        LCD.BUS= nibble.HI;
        LCD.EN = 0;
        __delay_ms(2);
        LCD.EN = 1;

        LCD.RS = 1;
        LCD.BUS = nibble.LO;
        LCD.EN = 0;
        __delay_ms(2);
        LCD.EN = 1;
}
void gotoxy( unsigned char x, unsigned char y )
{
        cmdLCD((LCD_GOTOL0 | LCD_GOTOL1 * y) + (x & 0X3F));    
}
void writeLCD( unsigned char x, unsigned char y, const char * ptr )
{
        gotoxy(x,y);
        while( *ptr )
        putLCD( *ptr++ );    
}

char lcdb0(void)
{
    return(LCD.B0);
}
char lcdb1(void)
{
    return(LCD.B1);
}

void clearLCD( void )
{
    cmdLCD(0x01);
}

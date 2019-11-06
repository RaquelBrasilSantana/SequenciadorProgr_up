/* 
 * File:    lcd4bitBus.h
 * Author:  Curta Eletrônica
 *
 * Created on 27 de Setembro de 2019, 20:33
 */

#ifndef LCD4BITBUS_H
#define	LCD4BITBUS_H

typedef union
{
    struct
    {
        unsigned char P0 :1;
        unsigned char P1 :1;
        unsigned char P2 :1;
        unsigned char P3 :1;
        unsigned char P4 :1;
        unsigned char P5 :1;
        unsigned char P6 :1;
        unsigned char P7 :1;
        unsigned char P8 :1;
        unsigned char P9 :1;
        unsigned char P10 :1;
        unsigned char P11 :1;
        unsigned char P12 :1;
        unsigned char P13 :1;
        unsigned char P14 :1;
        unsigned char P15 :1;
    };
    
} forLcd_t;
/*
 * **************** Procedimentos de acesso ao LCD
 */
void initLCD( void );
void intTOstr( int ui16, char * str );
void lcd( unsigned char x, unsigned char y, const char * ptr );
void lcdxy( unsigned char x, unsigned char y );
void lcddat( unsigned char dat );
void lcdcmd( unsigned char cmd );
void clearLCD( void );
void screen_car (void);
void screen_menu (void);
void screen_monitor (void);
/*
 * **************** Funções de acesso aos botões da placa do display LCD
 */
char lcdb0( void );
char lcdb1( void );


#endif	/* LCD_H */

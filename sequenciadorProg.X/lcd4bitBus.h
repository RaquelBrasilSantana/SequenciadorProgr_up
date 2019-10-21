/* 
 * File:   lcd.h
 * Author: sn1011701
 *
 * Created on 29 de Abril de 2019, 15:25
 */

#ifndef LCD4BITBUS_H
#define	LCD4BITBUS_H

#define LCD4b_ADDRS     0x008

typedef union 
{
    struct 
    {
        unsigned char BUS :4;
        unsigned char RS  :1;
        unsigned char EN  :1;
        unsigned char B0  :1;
        unsigned char B1  :1;
    };
} LCDbits_t;



//
/****************** CMD LCD: Definicao de Comandos ao LCD ********************/
//
#define LCD_CLEAR       0x01    // Limpa display

#define LCD_HOME        0x02    // Retorna cursor a origem

#define LCD_ON          0x0C    // Ligar Display
#define LCD_CURSOR      0x0A    // Ligar Cursor
#define LCD_BLINK       0x09    // Piscar

#define LCD_CURSOR_L    0x10    // Deslocar cursor  a Esquerda (L)
#define LCD_CURSOR_R    0x14    // Deslocar cursor  a Direita  (R)
#define LCD_DISPLAY_L   0x18    // Deslocar display a Esquerda (L)
#define LCD_DISPLAY_R   0x1C    // Deslocar display a Direita  (R)

#define LCD_GOTOL0      0x80    // Seta o cursor para a primeira linha
#define LCD_GOTOL1      0xC0    // Seta o cursor na segunda linha

//
/****************** CMD LCD: Definicao de Configuracao ***********************/
//
#define LCD_DATA_BITS_4 0x20    // Habilita barramento de 4 vias de dados
#define LCD_DATA_BITS_8 0x30    // Habilita barramento de 8 vias de dados
#define LCD_LINE2       0x28    // Habilita 2a linha do display



//
/****************** Funcoes de acesso ao LCD *********************************/
//
void LCD4b_cmd( unsigned char cmd );
void LCD4b_put( unsigned char c );
void gotoxy( unsigned char x, unsigned char y );
void writeLCD4b( unsigned char x, unsigned char y, const char * ptr );
void initLCD4b( void );
char lcdb0( void );
char lcdb1( void );
void intTOstr( int ui16, char * str );


#endif	/* LCD_H */

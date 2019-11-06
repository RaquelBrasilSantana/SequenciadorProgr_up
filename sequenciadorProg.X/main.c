/*
 * File:   main.c
 * Author: curtaeletronica
 *
 * Created on 03 de Outubro de 2019, 08:27
 * 
 * IDE:         MPLAB X IDE v3.15
 * Compiler:    XC8 v1.45
 * OS:          Deepin 15.11 X86_64
 * Kernel:      4.15.0-30deepin-generic
 * 
 * Objetivo: 
 *      Testar as rotinas do teclado matricial 4x4 apresentando o valor 
 *      das teclas no display.
 * 
 * Pinos    |nº     |Conexão
 *  VDD     |11,32  | Alimentação (Vcc/+5V)
 *  VSS     |12,31  | Alimentação (GND/0V)
 *  RB0     |33     | L1 : 123A
 *  RB1     |34     | L2 : 456B
 *  RB2     |35     | L3 : 789C
 *  RB3     |36     | L4 : *0#D
 *  RB4     |37     | C1 : 147*
 *  RB5     |38     | C2 : 2580
 *  RB6     |39     | C3 : 369#
 *  RB7     |40     | C4 : ABCD
 *  RD0     |19     | LCD_D4 (LCD_Data 4)
 *  RD1     |20     | LCD_D5
 *  RD2     |21     | LCD_D6
 *  RD3     |22     | LCD_D7
 *  RD4     |27     | LCD_RS
 *  RD5     |28     | LCD_EN
 *  RD6     |29     | LCD_B0
 *  RD7     |30     | LCD_B1
 * 
*/

//***************** Bibliotecas
#include <xc.h>
#include "config.h"
#include "lcd4bitBus.h"
#include "keyboard.h"
#include "fifo.h"
#include "serialIO.h"
#include "atuadores.h"

//***************** Programa Principal
void main(void)
{
    unsigned char tecla = 0;
    unsigned char a,b,c,d = 0;
    unsigned char rest = 0;
    SENSORESbits_t sensor;
    ATUADORESbits_t atuador;
    int estado = 0;
    forLcd_t screenDisp[16];
  
    initLCD();
    screen_car();
    initKeyboard();
    initSerialIO(  &sensor, &atuador, 1 );
    
    while( 1 )                      // Laço de repetição infinita.
    {
        
        keyboardScan();
        screen_menu();

        switch( estado )
        {
            case 0:
                    estado = 10;
                    break;
            case 10:
                    rest = getFIFO();
                    if( rest == 'A' )
                        estado = 100;
                    else if( rest == 'B' )
                        estado = 110;
                    else if( rest == 'C' )
                        estado = 120;
                    else if( rest == 'D' )
                        estado = 130;
                    else if( rest == '1' )
                        estado = 140;
                    else if( rest == '2' )
                        estado = 150;
                    else if( rest == '3' )
                        estado = 160;
                    else if( rest == '4' )
                        estado = 170;
                    else if( rest == '5' )
                        estado = 180;
                    else if( rest == '6' )
                        estado = 190;
                    else if( rest == '7' )
                        estado = 200;
                    else if( rest == '8' )
                        estado = 210;
                    else if( rest == '9' )
                        estado = 220;
                    else if( rest == 'a' )
                        estado = 230;
                    else if( rest == 'b' )
                        estado = 240;
                    else if( rest == 'c' )
                        estado = 250;
                    else if( rest == 'd' )
                        estado = 260;
                    break;
            case 100: // A+
                    atuador.A = 1;
                    estado = 101;
                    break;
            case 101:
                    if( sensor.A1 == 1)
                        estado = 10;
                    break;
            case 110: // B+
                    atuador.B = 1;
                    estado = 111;
                    break;
            case 111:
                    if( sensor.B1 == 1)
                        estado = 10;
                    break;
            case 120: // C+
                    atuador.C = 1;
                    estado = 121;
                    break;
            case 121:
                    if( sensor.C1 == 1)
                        estado = 10;
                    break;
            case 130: // D+
                    atuador.D = 1;
                    estado = 131;
                    break;
            case 131:
                    if( sensor.D1 == 1)
                        estado = 10;
                    break;
            case 140:
                    __delay_ms(1000);
                    estado = 141;
                    break;
            case 141:
                    estado = 10;
                    break;
            case 150:
                    __delay_ms(2000);
                    estado = 151;
                    break;
            case 151:
                    estado = 10;
                    break;
            case 160:
                    __delay_ms(3000);
                    estado = 161;
                    break;
            case 161:
                    estado = 10;
                    break;
            case 170:
                    __delay_ms(4000);
                    estado = 171;
                    break;
            case 171:
                    estado = 10;
                    break;
            case 180:
                    __delay_ms(5000);
                    estado = 181;
                    break;
            case 181:
                    estado = 10;
                    break;
            case 190:
                    __delay_ms(6000);
                    estado = 191;
                    break;
            case 191:
                    estado = 10;
                    break;
            case 200:
                    __delay_ms(7000);
                    estado = 201;
                    break;
            case 201:
                    estado = 10;
                    break;
            case 210:
                    __delay_ms(8000);
                    estado = 211;
                    break;
            case 211:
                    estado = 10;
                    break;
            case 220:
                    __delay_ms(9000);
                    estado = 221;
                    break;
            case 221:
                    estado = 10;
                    break;
                    
            case 230: // A-
                    atuador.A = 0;
                    estado = 231;
                    break;
            case 231:
                    if( sensor.A0 == 1)
                        estado = 10;
                    break;        
            case 240: // B-
                    atuador.B = 0;
                    estado = 241;
                    break;
            case 241:
                    if( sensor.B0 == 1)
                        estado = 10;
                    break;        
            case 250: // C-
                    atuador.C = 0;
                    estado = 251;
                    break;
            case 251:
                    if( sensor.C0 == 1)
                        estado = 10;
                    break;        
            case 260: // D-
                    atuador.D = 0;
                    estado = 261;
                    break;
            case 261:
                    if( sensor.D0 == 1)
                        estado = 10;
                    break;        
            
        }
        if( currentKey() && !previousKey() )
        {
            tecla = currentKey();
            switch(tecla)
            {
                case 'A':
                        ++a;
                        if( a % 2 )
                            putFIFO( tecla );   
                        else
                            putFIFO( tecla | 0x20 );
                        break;
                case 'B':
                        ++b;
                        if( b % 2 )
                            putFIFO( tecla );
                        else
                            putFIFO( tecla | 0x20 );
                        break;
                case 'C':
                        ++c;
                        if( c % 2 )
                            putFIFO( tecla );
                        else
                            putFIFO( tecla | 0x20 );
                        break;
                case 'D':
                        ++d;
                        if( d % 2 )
                            putFIFO( tecla );
                        else
                            putFIFO( tecla | 0x20 );
                        break;  
                case '0':
                        delFIFO(16);
                        clearLCD();
                        a = b = c = d = 0;
                        break;  
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                        putFIFO(tecla);
                        break;  
                case '*':
                        switch( delFIFO(1) )
                        {
                            case 'A':   a = 0;  break;
                            case 'a':   a = 1;  break;
                            case 'B':   b = 0;  break;
                            case 'b':   b = 1;  break;
                            case 'C':   c = 0;  break;
                            case 'c':   c = 1;  break;
                            case 'D':   d = 0;  break;
                            case 'd':   d = 1;  break;
                        }
                        clearLCD();
                        break;
                case '#':
                        estado = 0;
                        break;
            }
            lcd(0,1, displayFIFO() );
            
        }
        serialIOscan();
    }
}
    
//***************** Fim do Programa Principal

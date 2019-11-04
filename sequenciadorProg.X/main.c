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
    char estado = 0;
  
    initLCD();
    initKeyboard();
    initSerialIO(  &sensor, &atuador, 1 );
    
    while( 1 )                      // Laço de repetição infinita.
    {
        
        keyboardScan();

        switch( estado )
        {
            case 0:
                    
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
                    break;
            case 100: // A+
                    atuador.A = 1;
                    estado = 101;
                    break;
            case 101:
                    if( sensor.A1 == 1)
                        estado = 10;
                    break;
            case 110:
                    atuador.B = 1;
                    estado = 111;
                    break;
            case 111:
                    if( sensor.B1 == 1)
                        estado = 10;
                    break;
            case 120:
                    atuador.C = 1;
                    estado = 121;
                    break;
            case 121:
                    if( sensor.C1 == 1)
                        estado = 10;
                    break;
            case 130:
                    atuador.D = 1;
                    estado = 131;
                    break;
            case 131:
                    if( sensor.D1 == 1)
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
                        estado = 10;
                        break;
            }
            lcd(0,0, displayFIFO() );
            
        }
        serialIOscan();
    }
}
    
//***************** Fim do Programa Principal

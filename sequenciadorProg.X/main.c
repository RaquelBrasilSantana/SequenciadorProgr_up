#include <xc.h>
#include "SERIAL.h"
#include "config.h"
#include "lcd.h"
#include "delay.h"
#include "teclado4x4_v08.h"


//void __interrupt() irq(void)
//{
//    if( INTCONbits.T0IE && INTCONbits.T0IF )
//    {
//        INTCONbits.T0IF = 0;
//        intt0_1ms();
//    }
//}

void main(void) 
{   
    initSerialIO(); 
    tecladoIniciar();
    initLCD();
    
    int Vetprog [12]; 
    
    char estado = 0;
    
            
  
    while(1)
    {        
        switch(estado)
        {
            case 0:
                estado = 1;
                break;
            case 1:
                menu0();
                estado = 2;
                break;
            case 2:
                delay(100);
                estado = 3;
                break;
            case 3:
                cmdLCD(LCD_CLEAR);
                estado = 4;
                break;
            case 4:
                delay(100);
                estado = 5;
                break;
            case 5:
                menu1();
                delay(1000);
                cmdLCD(LCD_CLEAR);
                estado = 10;
                break;
            case 10:
                menu2();       
                estado = 11;
                break;
            case 11:
                if(tecladoLer() == 'E')
                {    
                    cmdLCD(LCD_CLEAR);
                    estado = 12; 
                }    
                if(tecladoLer() == 'A')
                {    
                    cmdLCD(LCD_CLEAR);
                    estado = 20; 
                }    
                if(tecladoLer() == 'B')
                {    
                    cmdLCD(LCD_CLEAR);
                    estado = 40;
                }    
                break;
            case 12:
                menu3();
                estado = 14;
                break;
             case 14:
                if(tecladoLer() == 'F')
                {    
                    cmdLCD(LCD_CLEAR);
                    estado = 10;
                }    
                if(tecladoLer() == 'C')
                {    
                    cmdLCD(LCD_CLEAR);
                    estado = 60; 
                }    
                if(tecladoLer() == 'D')
                {    
                    cmdLCD(LCD_CLEAR);
                    estado = 80; 
                }    
                break; 

            case 20:
                SUBmenu0();
                estado = 21;
                break;
            case 21:
                if(tecladoLer() == 'A')
                   estado = 22;  
                if(tecladoLer() == 'B')
                   estado = 25;  
                if(tecladoLer() == 'C')
                   estado = 28;  
                if(tecladoLer() == 'D')
                   estado = 31;

                if(tecladoLer() == 'F')
                   estado = 10;  
                break;
                    
            case 22:
                if(tecladoLer() == 'A')
                {
                    writeLCD(0,1,"A+");
                    estado = 23;
                }    
                break;
            case 23:
                if(tecladoLer() == 'E')
                {
                    serialOut(0b00000001);
                    estado = 24;
                }    
                break;
            case 24:
                if(tecladoLer() == 'F')
                {
                    writeLCD(0,1,"A-");
                    serialOut(0b00000000);
                    estado = 20;
                }    
                break;
            
            case 25:
                if(tecladoLer() == 'B')
                {
                    writeLCD(0,1,"B+");
                    estado = 26;
                }
                break;
            case 26:
                if(tecladoLer() == 'E')
                {
                    serialOut(0b00000010);
                    estado = 27;
                }
                break;
            case 27:
                if(tecladoLer() == 'F')
                {
                    writeLCD(0,1,"B-");
                    serialOut(0b00000000);
                    estado = 20;
                }
                break;
                    
             case 28:
                if(tecladoLer() == 'C')
                {
                    writeLCD(0,1,"C+");
                    estado = 29;
                }
                break;
            case 29:
                if(tecladoLer() == 'E')
                {
                    serialOut(0b00000100);
                    estado = 30;
                }
                break;
            case 30:
                if(tecladoLer() == 'F')
                {
                    writeLCD(0,1,"C-");
                    serialOut(0b00000000);
                    estado = 20;
                }
                break;
                    
            case 31:
                if(tecladoLer() == 'D')
                {
                    writeLCD(0,1,"D+");
                    estado = 32;
                }
                break;
            case 32:
                if(tecladoLer() == 'E')
                {
                    serialOut(0b00001000);
                    estado = 33;
                }
                break;
            case 33:
                if(tecladoLer() == 'F')
                {
                    writeLCD(0,1,"D-");
                    serialOut(0b00000000);
                    estado = 20;
                }
                break;
                
            case 40:        
                SUBmenu1();
                estado = 41;
                break;
            case 41:
                
                break;
                
            case 60:
                SUBmenu2();
                estado = 61;
                break;
            case 61:
                if(serialIn() == 0x01)
                {    
                    writeLCD(3,0,"A+" );
                    writeLCD(13,0,"B-" );
                    writeLCD(3,1,"C-" );
                    writeLCD(13,1,"D-" );
                }    
                else if(serialIn() == 0x02)
                    writeLCD(3,0,"A-");

                else if(serialIn() == 0b00000100)
                {    
                    writeLCD(3,0,"A-" );
                    writeLCD(13,0,"B+" );
                    writeLCD(3,1,"C-" );
                    writeLCD(13,1,"D-" );
                }   
                else if(serialIn() == 0b00001000)
                    writeLCD(13,0,"B-");

                else if(serialIn() == 0b00010000)
                {    
                    writeLCD(3,0,"A-" );
                    writeLCD(13,0,"B-" );
                    writeLCD(3,1,"C+" );
                    writeLCD(13,1,"D-" );
                }
                else if(serialIn() == 0b00100000)
                    writeLCD(3,1,"C-");

                else if(serialIn() == 0b01000000)
                {    
                    writeLCD(3,0,"A-" );
                    writeLCD(13,0,"B-" );
                    writeLCD(3,1,"C-" );
                    writeLCD(13,1,"D+" );
                }
                else if(serialIn() == 0b10000000)
                    writeLCD(13,1,"D-");

                else if(tecladoLer() == 'F')
                    estado = 12;
                break;
            case 80:
                SUBmenu3();
                estado = 81;
                break;    
            case 81:
                if(tecladoLer() == 'A')
                {    
                    serialOut(0b00001111);
                    estado = 82;
                }
                if(tecladoLer() == 'F')
                    estado = 12;
                break;    
            case 82:
                if(tecladoLer() == 'B')
                {    
                    serialOut(0b00000000);
                    estado = 80;
                }    
                break;    
         
        }          
    }      
}                 

/* 
 * File:   delay.c
 * Author: 18175242
 *
 * Created on 22 de Agosto de 2019, 16:05
 */

#include <xc.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"



void delay (unsigned int t) 
{
    while(t)
    {    
     __delay_ms (1);
        --t;
    }
       
}



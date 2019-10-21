/* 
 * File:   SERIAL.h
 * Author: 18175218
 *
 * Created on 10 de Setembro de 2019, 14:28
 */

#ifndef SERIAL_H
#define	SERIAL_H

#define SERIALIO_ADDRS 0x009

typedef union
{
    struct
    {
        unsigned char SHLD:1;
        unsigned char CLK :1;
        unsigned char OUT :1;
        unsigned char IN  :1;
    };
} SERIALIObits_t;

void initSerialIO(void);
void serialOut( unsigned char d );
unsigned char serialIn( void );
void serialIO( void );

#endif	/* SERIAL_H */


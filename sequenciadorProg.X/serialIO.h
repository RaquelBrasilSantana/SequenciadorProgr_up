/* 
 * File:   serialIO.h
 * Author: sn1011701
 *
 * Created on 19 de Julho de 2019, 10:40
 */

#ifndef SERIALIO_H
#define	SERIALIO_H

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

void initSerialIO( unsigned char * ptrIn, unsigned char * ptrOut, unsigned char length );
void serialOut( unsigned char d );
unsigned char serialIn( void );
void serialIO( void );

#endif	/* SERIALIO_H */

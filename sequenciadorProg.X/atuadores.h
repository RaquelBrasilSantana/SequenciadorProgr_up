/* 
 * File:   atuadores.h
 * Author: 18175218
 *
 * Created on 28 de Outubro de 2019, 13:25
 */

#ifndef ATUADORES_H
#define	ATUADORES_H

typedef union
{
    struct
    {
        unsigned char A :1;
        unsigned char B :1;
        unsigned char C :1;
        unsigned char D :1;
    };
    unsigned char ABCD;
} ATUADORESbits_t;

typedef union
{
    struct
    {
        unsigned char A0 :1;
        unsigned char B0 :1;
        unsigned char C0 :1;
        unsigned char D0 :1;
        unsigned char A1 :1;
        unsigned char B1 :1;
        unsigned char C1 :1;
        unsigned char D1 :1;
    };
    struct
    {
        unsigned char ABCD0:4;
        unsigned char ABCD1:4;
    };
} SENSORESbits_t;




#endif	/* ATUADORES_H */


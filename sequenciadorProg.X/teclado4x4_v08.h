#ifndef __TECLADO4X4_V08_H
#define __TECLADO4X4_V08_H

#define tec01C1 PORTBbits.RB4							// Pino da Coluna 1
#define tec01C2 PORTBbits.RB5							// Pino da Coluna 2
#define tec01C3 PORTBbits.RB6							// Pino da Coluna 3
#define tec01C4 PORTBbits.RB7							// Pino da Coluna 4
#define tec01L1 PORTBbits.RB0							// Pino da Linha 1
#define tec01L2 PORTBbits.RB1							// Pino da Linha 2
#define tec01L3 PORTBbits.RB2							// Pino da Linha 3
#define tec01L4 PORTBbits.RB3							// Pino da Linha 4
#define cfgSaidaTEC TRISB							// Configuração das entradas(1) e saídas(0).

#ifndef _PIC18									// Se for para 16F...
#define Saida PORTB								// ...define o termo correto para a saída.
#elif   _PIC18									// Se for para 18F...
#define Saida LATB								// ...define o termo correto para a saída.
#endif

unsigned char tec01TeclaAnte;							// Variável local, armazena valor antigo.
unsigned char tec01Tecla;							// Variável local, armazena valor novo.
//				 11  21  31  41
//				{'7','4','1','F','8','5','2','0','9','6','3','E','A','B','C','D'}; //{'9','8','7','A','6','5','4','B','3','2','1','C','F','0','E','D'};
const unsigned char tabTeclas[]={'1','4','7','F','2','5','8','0','3','6','9','E','A','B','C','D'}; // {'1','4','7','F','2','5','8','0','3','6','9','E','A','B','C','D'};

void tecladoIniciar(void)
{
#ifndef _PIC18									// Se for para 16F...
	OPTION_REGbits.nRBPU=0;							// Ativa os resistores de Pull-Up no PORTB
	ANSELH=0x00;								// Desliga entrada analógica
#elif   _PIC18									// Se for para 18F...
	INTCON2bits.RBPU=0;							// Ativa os resistores de Pull-Up no PORTB
	ADCON1 |= 0x0E;								// Desliga entrada analógica
#endif
	cfgSaidaTEC=0B00001111;							// RB7-RB4: Output (Saída=0)  RB3-RB0: Input(Entrada=1)
	Saida=0x00;								// Limpa o PORTB.
	tec01TeclaAnte=0x00;							// Limpa a variável local.
	tec01Tecla=0x00;							// Limpa a variável local.
}

unsigned char tecladoLer(void)							// Loop infinito. Inicio...
{
    tec01C4=1,tec01C3=1,tec01C2=1,tec01C1=0;					// Ativa somente a 1ª coluna.
    NOP();NOP();								// NOP=Sem operação. Perde tempo para estabilizar.
    if(!tec01L1)	tec01Tecla = tabTeclas[0];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tec01L2)	tec01Tecla = tabTeclas[1];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tec01L3)	tec01Tecla = tabTeclas[2];				// Se a terceira linha for ativada, guardar este caracter.
    else if(!tec01L4)	tec01Tecla = tabTeclas[3];				// Se a quarta linha for ativada, guardar este caracter.

    tec01C4=1,tec01C3=1,tec01C2=0,tec01C1=1;					// Ativa somente a 2ª coluna.
    NOP();NOP();								// NOP=Sem operação. Perde tempo para estabilizar.
    if(!tec01L1)	tec01Tecla = tabTeclas[4];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tec01L2)	tec01Tecla = tabTeclas[5];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tec01L3)	tec01Tecla = tabTeclas[6];				// Se a terceira linha for ativada, guardar este caracter
    else if(!tec01L4)	tec01Tecla = tabTeclas[7];				// Se a quarta linha for ativada, guardar este caracter.
    
    tec01C4=1,tec01C3=0,tec01C2=1,tec01C1=1;					// Ativa somente a 3ª coluna.
    NOP();NOP();								// NOP=Sem operação. Perde tempo para estabilizar.
    if(!tec01L1)	tec01Tecla = tabTeclas[8];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tec01L2)	tec01Tecla = tabTeclas[9];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tec01L3)	tec01Tecla = tabTeclas[10];				// Se a terceira linha for ativada, guardar este caracter
    else if(!tec01L4)	tec01Tecla = tabTeclas[11];				// Se a quarta linha for ativada, guardar este caracter.
    
    tec01C4=0,tec01C3=1,tec01C2=1,tec01C1=1;					// Ativa somente a 4ª coluna.
    NOP();NOP();								// NOP=Sem operação. Perde tempo para estabilizar.
    if(!tec01L1)	tec01Tecla = tabTeclas[12];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tec01L2)	tec01Tecla = tabTeclas[13];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tec01L3)	tec01Tecla = tabTeclas[14];				// Se a terceira linha for ativada, guardar este caracter
    else if(!tec01L4)	tec01Tecla = tabTeclas[15];				// Se a quarta linha for ativada, guardar este caracter.

    // Código anti-repetição
    if(tec01Tecla!=tec01TeclaAnte)						// Verifica se a tecla atual é diferente da anterior...
    {
        tec01TeclaAnte=tec01Tecla;						// ...se for salva atual e ... 
        return tec01Tecla;							// ...retorna com o novo valor...
    }
    else									// ...se não...
    {
	tec01Tecla=0x00;							// Salva como não acionada ou não liberada.
        return tec01Tecla;							// ...retorna com o valor.
    }
}

#endif
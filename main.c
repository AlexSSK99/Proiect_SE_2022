/*
Print 'n1:'
Print 'n2:'

Print 'operation:' (default +)
Read operation

Print result
*/

#include <MKL25Z4.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdout_UART.h"

#define Enter 13
#define Plus '+'
#define Minus '-'
#define Multiply '*'
#define Divide '/'

static void config_sys_clock(void);
static void LongToStr(long l, unsigned char* buffer);
void br();

/*
	In cadrul programului s-au folosit:
	5 mesaje de tipul unsigned char,
	variabile tip long pentru termenii operatiei de efectuat: Op1, Op2
	Key pentru a stoca rezultatul conversiei caracterului receptionat pe UART spre numar
	Calc unde se stocheaza rezultatul operatiei
	
	un buffer de tip unsigned char in care se va pastra rezultatul operaetiei dupa conversia de la char la intreg (long)
	pointer de tip unsigned char care poate fi folosit pentru trimming-ul spatiilor albe din buffer-ul de afisare (neimplementat)
	i si j pentru folosirea lor in cadrul unor bucle for
	
	Intregul cod ruleaza intr-o bucla infinita unde secvential se petrec urmatoarele actiuni:
		*Se afiseaza un mesaj de introducere
		*Se cere introducerea primului numar:
			- Se face intr-o bucla (caracter cu caracter) ce se va opri atunci cand se detecteaza apasarea tastei Enter
			- La fiecare iteratie se converteste din caracter in numar
		*Se cere introducerea celui de-al doilea numar
			- Se repeta aceeasi secventa ca si in cazul primului numar
		*Se cere introducerea operatiei dorite (+, -, *, /)
			- In cazul default (introducerea altui caracter decat cele precizate) se va efectua suma
			- Se stocheaza rezultatul operatiei
		*Se realizeaza conversia rezultatului
		*Se afiseaza rezultatul operatiei
		
	Aditional, se folosesc functiile deja prezentate in laboratoare pentru configurarea UART-ului, clock.. etc
	
	Singurele aditii sunt:
		- stdout_getchar(unsigned char echo):
			echo = 0 sau 1; pentru 1 se va trimite inapoi caracterul receptionat, altfel nu
		- LongToStr(long l, unsigned char* buffer):
			realizeaza conversia parametrului l in codul ASCII si stocarea acestuia in buffer in vederea afisarii ulterioare
		- void br()
			trimite newline si carriage return
	
*/
 
int main(void) {
	unsigned char MyKey, i, j, kbd[20];
	unsigned char *op;
	unsigned long Calc, Op1, Op2, Key;
	unsigned char msg1[] = "CALCULATOR PROGRAM";
	unsigned char msg2[] = " Enter n1: ";
	unsigned char msg3[] = " Enter n2: ";
	unsigned char msg4[] = " Enter operation: ";
	unsigned char msg5[] = " Result = ";
	
	config_sys_clock();
	
	stdout_init();
	
	while(1)
	{
		MyKey = 0;
		Op1 = 0;
		Op2 = 0;
		
		br();
		br();
		stdout_putstr(msg1, 19);
		br();
		br();
		
		stdout_putstr(msg2, 11);
		do
		{
			MyKey = stdout_getchar(1);
			if(MyKey == Enter) break;
			Key = MyKey - '0';
			Op1 = 10*Op1 + Key;
		}while(1);
		
		br();
		
		stdout_putstr(msg3, 11);
		do
		{
			MyKey = stdout_getchar(1);
			if(MyKey == Enter) break;
			Key = MyKey - '0';
			Op2 = 10*Op2 + Key;
		}while(1);
		
		br();
		
		stdout_putstr(msg4, 19);
		do
		{
			MyKey = stdout_getchar(1);
			if(MyKey == Enter) break;
			Key = MyKey;
		}while(1);
		
		br();
		switch(Key)
		{
			case Minus:
				Calc = Op1 - Op2;
				break;
			case Multiply:
				Calc = Op1 * Op2;
				break;
			case Divide:
				Calc = Op1 / Op2;
				break;
			default:
				Calc = Op1 + Op2;
				break;
		}

		LongToStr(Calc, kbd);

		stdout_putstr(msg5, 10);
		stdout_putstr(kbd, 20);
		
	}
}

static void LongToStr(long l, unsigned char* buffer)
{
	int idx = strlen((char*)buffer);
	int i;

	do
	{
		buffer[idx] = l % 10 + '0';
		l /= 10;
		idx--;
	}	while(l);
	
	for(i = 0; i <= idx; i++)
	{
		buffer[idx] = ' ';
	}
}

static void config_sys_clock(void)
{
    // MCG_C1: CLKS (bit 7-6) = 00
    MCG->C1 |= MCG_C1_CLKS(0);  // Select PLL/FLL as clock source
     
    // MCG_C1: IREFS (bit 2)  = 1
    MCG->C1 |= MCG_C1_IREFS(1); // Select Inernal Reference clock
                                // source for FLL
     
    // MCG_C4: DRST_DRS (bit 6-5) = 01
    MCG->C4 |= MCG_C4_DRST_DRS(1); // Select DCO range as Mid range
                                   // DCO generates the FLL Clock
     
    // MCG_C4: DMX32 (bit 7) = 1
    MCG->C4 |= MCG_C4_DMX32(1);    // Select DCO frequency as 48Mhz
}

void br()
{
	stdout_putchar(0x0D);
	stdout_putchar(0x0A);
}

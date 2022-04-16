#include "stdout_UART.h"


#define BUS_CLOCK (48000000)

uint32_t baud = 9600;

void stdout_init(void) {
	//https://learningmicro.wordpress.com/serial-communication-interface-using-uart/
	uint32_t divisor = baud;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
 
	PORTA_PCR1 |=  PORT_PCR_MUX(2); /* PTA1 as ALT2 (UART0) */
	PORTA_PCR2 |=  PORT_PCR_MUX(2); /* PTA2 as ALT2 (UART0) */
	
	// Select MCGFLLCLK as UART0 clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
 
	// Enable UART0 Clock
	SIM->SCGC4 |= SIM_SCGC4_UART0(1);
	
	// Configure Baud Rate
	divisor = BUS_CLOCK /(divisor *16);
	UART0->BDH = UART_BDH_SBR(divisor>>8);
	UART0->BDL = UART_BDL_SBR(divisor);
		
	// Configure Serial Port as 8-N-1
	// (8 data bits, No parity and 1 stop bit)
	UART0->C1  = 0x00;
	
	// Configure Tx/Rx Interrupts
	UART0->C2  |= UART_C2_TIE(0);  // Tx Interrupt disabled
	UART0->C2  |= UART_C2_TCIE(0); // Tx Complete Interrupt disabled
	UART0->C2  |= UART_C2_RIE(1);    // Rx Interrupt enabled
 
	// Configure Transmitter/Receiever
	UART0->C2  |= UART_C2_TE(1);     // Tx Enabled
	UART0->C2  |= UART_C2_RE(1);     // Rx Enabled
}
 
void stdout_putchar (unsigned char ch) {
	//Wait until transmit buffer is empty
	while(!(UART0->S1 & UART_S1_TDRE_MASK));
	//write to tx buffer
	UART0->D = ch;
}

void stdout_putstr(unsigned char* str, char max) {
	int i;
	for(i = 0; i < max; i++) {
		stdout_putchar(str[i]);
	}
}

unsigned char stdout_getchar(unsigned char echo)
{
	unsigned char my_ch;
	//check receive buffer not full
	while (!(UART0->S1 & UART_S1_RDRF_MASK));
	//write rx buffer to my_ch
	my_ch = UART0->D;
	
	if(echo)
		stdout_putchar(my_ch);
	
	//return to calling function
	return my_ch;
}

unsigned char *stdout_getstr(unsigned char echo)
{
	unsigned char buff[5];
	int i;
	for(i = 0; i < 5; i++)
	{
		if(stdout_getchar(0) == 0)
			return 0;
		buff[i] = stdout_getchar(echo) - '0';
	}
	return buff;
}

int str_int(unsigned char *string)
{
	int i, aux = 0;
	for(i=0; i<5; i++)
		{
			if(*(string+i) == 0) break;
			aux += *(string+i) ^ (4-i);
		}
	return aux;
}

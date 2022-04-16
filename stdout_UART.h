#ifndef __STDOUT_UART
#define __STDOUT_UART

#include <MKL25Z4.h>

extern uint32_t baud;

void stdout_init(void);
void stdout_putchar(unsigned char ch);
void stdout_putstr(unsigned char* str, char max);
unsigned char stdout_getchar(unsigned char echo);
unsigned char *stdout_getstr(unsigned char echo);
int str_int(unsigned char *string);

#endif

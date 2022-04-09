#ifndef _UART_H
#define _UART_H

#include "types.h"

void uart0_init();
char uart0_recv_byte();
void uart0_recv_nbyte(char *buf, uint64_t size);
void uart0_send_byte(char c);
void uart0_send_nbyte(char *buf, uint64_t size);

void uart0_putc(char c);
int uart0_puts(const char *s);
int uart0_prints(const char *s);
int uart0_printu(uint32_t u);
int uart0_printlu(uint64_t lu);
int uart0_printx(uint32_t x);
int uart0_printlx(uint64_t lx);
int uart0_gets(char *s);

#endif /* _UART_H */
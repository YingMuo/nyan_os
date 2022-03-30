#ifndef _UART_H
#define _UART_H

#include <stdint.h>

void uart0_init();
char uart0_recv_byte();
void uart0_recv_nbyte(char *buf, uint64_t size);
void uart0_send_byte(char c);
void uart0_send_nbyte(char *buf, uint64_t size);

#endif /* _UART_H */
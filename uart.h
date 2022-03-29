#ifndef _UART_H
#define _UART_H

void uart0_init();
char uart0_recv_byte();
void uart0_send_byte(char c);

#endif /* _UART_H */
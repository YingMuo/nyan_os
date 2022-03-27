#ifndef _UART_H
#define _UART_H

void mini_uart_init();
char uart_read_byte();
void uart_write_byte(char c);

#endif /* _UART_H */
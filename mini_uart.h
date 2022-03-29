#ifndef _MINI_UART_H
#define _MINI_UART_H

void mini_uart_init();
char mini_uart_read_byte();
void mini_uart_write_byte(char c);

#endif /* _MINI_UART_H */
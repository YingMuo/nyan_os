#include "uart.h"

void main()
{
    uart_write_byte('h');
    uart_write_byte('e');
    uart_write_byte('l');
    uart_write_byte('l');
    uart_write_byte('o');
    while (1);
}
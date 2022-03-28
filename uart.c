#include "reg.h"

#define LSR_DATA_READY (1 << 0)
#define LSR_TRANSMITTER_EMPTY (1 << 5)

void mini_uart_init()
{
    int r;

    *GPFSEL1 &= ~((0b111 << 12) | (0b111 << 15));
    *GPFSEL1 |= ((0b111 << 12) | (0b111 << 15));

    *GPPUD = 0;
    r = 150; while(r--);
    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    r = 150; while(r--);
    *GPPUDCLK0 = 0;

    *AUX_ENABLES = 1;
    *AUX_MU_CNTL_REG = 0;
    *AUX_MU_IER_REG = 0;
    *AUX_MU_LCR_REG = 3;
    *AUX_MU_MCR_REG = 0;
    *AUX_MU_BAUD_REG = 270;
    *AUX_MU_IIR_REG = 6;
    *AUX_MU_CNTL_REG = 3;
}

char uart_read_byte()
{
    while (!(*AUX_MU_LSR_REG & LSR_DATA_READY));
    return *AUX_MU_IO_REG & 0xff;
}

void uart_write_byte(char c)
{
    while (!(*AUX_MU_LSR_REG & LSR_TRANSMITTER_EMPTY));
    *(char *)AUX_MU_IO_REG = c;
}
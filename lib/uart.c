#include "reg.h"
#include "mbox.h"

#include <stdint.h>

void uart0_init()
{
    uint32_t r;

    *UART0_CR = 0;

    mbox[0] = 9 * 4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_TAG_SETCLKRATE;
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2; // UART ID
    mbox[6] = 400000;
    mbox[7] = 0;
    mbox[8] = MBOX_TAG_LAST;
    mbox_call(MBOX_CH_PROP);

    *GPFSEL1 &= ~((0b111 << 12) | (0b111 << 15));
    *GPFSEL1 |= ((0b111 << 12) | (0b111 << 15));
    *GPPUD = 0;
    r = 150; while(r--);
    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    r = 150; while(r--);
    *GPPUDCLK0 = 0;

    *UART0_ICR = 0x7ff; // interrupt cancel register
    *UART0_IBRD = 2; // set buad rate =  230400 / 2
    *UART0_FBRD = 0; // set fraction of baud rate
    *UART0_LCRH = 0b111 << 4; // set 8 bits and enable FIFO
    *UART0_CR = 0x301; // enable r/t and enable uart
}

char uart0_recv_byte()
{
    while (*UART0_FR & 0x10); // receive FIFO empty
    return *UART0_DR & 0xff; // r/t data
}

void uart0_recv_nbyte(char *buf, uint64_t size)
{
    for (uint64_t i = 0; i < size; ++i)
        buf[i] = uart0_recv_byte();
}

void uart0_send_byte(char c)
{
    while (*UART0_FR & 0x20); // transmit FIFO full
    *UART0_DR = c;
}

void uart0_send_nbyte(char *buf, uint64_t size)
{
    for (uint64_t i = 0; i < size; ++i)
        uart0_send_byte(buf[i]);
}
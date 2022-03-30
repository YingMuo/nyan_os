#include "uart.h"
#include <stdint.h>

void putc(char c)
{
    uart0_send_byte(c);
}

int puts(const char *s)
{
    int i = 0;
    for (; s[i] != '\0'; ++i)
        uart0_send_byte(s[i]);
    uart0_send_byte('\n');
    return i;
}

int prints(const char *s)
{
    int i = 0;
    for (; s[i] != '\0'; ++i)
        uart0_send_byte(s[i]);
    return i;
}

int printu(uint32_t u)
{
    char buf[0x100];
    if (!u)
    {
        uart0_send_byte('0');
        return 1;
    }
    int i = 0xfe;
    for (; u; --i, u /= 10)
        buf[i] = u % 10 + '0';
    int ret = 0xfe - i;
    for (; i < 0xff; ++i)
        uart0_send_byte(buf[i]);
    return ret;
}

int printlu(uint64_t lu)
{
    char buf[0x100];
    if (!lu)
    {
        uart0_send_byte('0');
        return 1;
    }
    int i = 0xfe;
    for (; lu; --i, lu /= 10)
        buf[i] = lu % 10 + '0';
    int ret = 0xfe - i;
    for (; i < 0xff; ++i)
        uart0_send_byte(buf[i]);
    return ret;
}

int printx(uint32_t x)
{
    char buf[0x100];
    if (!x)
    {
        uart0_send_byte('0');
        return 1;
    }
    int i = 0xfe;
    char c;
    for (; x; --i, x /= 0x10)
    {
        c = x & 0xf;
        if (c < 10)
            buf[i] = c + '0';
        else
            buf[i] = c - 0xa + 'a';
    }
    int ret = 0xfe - i;
    uart0_send_byte('0');
    uart0_send_byte('x');
    for (; i < 0xff; ++i)
        uart0_send_byte(buf[i]);
    return ret;
}

int gets(char *s)
{
    char c = '\0';
    int i = 0;
    for (;c != '\r'; ++i)
    {
        c = uart0_recv_byte();
        uart0_send_byte(c);
        s[i] = c;
    }
    uart0_send_byte('\n');
    s[i - 1] = '\0';
    return i;
}

int strcmp(const char *s1, const char *s2)
{
    for (int i = 0; s1[i] != '\0'; ++i)
    {
        if (s1[i] < s2[i])
            return -1;
        if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}
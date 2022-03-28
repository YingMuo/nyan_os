#include "uart.h"
#include "util.h"
#include "reset.h"
#include <stdint.h>

char buf[0x100];
const char hello[] = "Hello World!";
const char * const cmd[] = {
    "help",
    "hello",
    "timestamp",
    "reboot"
};

enum CMD
{
    HELP = 0,
    HELLO,
    TIMESTAMP,
    REBOOT
};

void putc(char c)
{
    uart_write_byte(c);
}

int puts(const char *s)
{
    int i = 0;
    for (; s[i] != '\0'; ++i)
        uart_write_byte(s[i]);
    uart_write_byte('\n');
    return i;
}

int prints(const char *s)
{
    int i = 0;
    for (; s[i] != '\0'; ++i)
        uart_write_byte(s[i]);
    return i;
}

int printu(uint32_t u)
{
    if (!u)
    {
        uart_write_byte('0');
        return 1;
    }
    int i = 0xfe;
    for (; u; --i, u /= 10)
        buf[i] = u % 10 + '0';
    int ret = 0xfe - i;
    for (; i < 0xff; ++i)
        uart_write_byte(buf[i]);
    return ret;
}

int gets(char *s)
{
    char c = '\0';
    int i = 0;
    for (;c != '\r'; ++i)
    {
        c = uart_read_byte();
        uart_write_byte(c);
        s[i] = c;
    }
    uart_write_byte('\n');
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

void print_time()
{
    putc('[');
    uint64_t tc = get_tc();
    uint32_t tf = get_tf();
    uint32_t tp = tc / tf;
    uint32_t ts = tc % tf;
    printu(tp);
    putc('.');
    printu(ts);
    putc(']');
    putc('\n');
}

void shell()
{
    for (;;)
    {
        prints("# ");
        gets(buf);
        int i = 0;
        for (;i < 4 && strcmp(buf, cmd[i]); ++i);
        switch (i)
        {
        case HELP:
            puts("help : print usage");
            puts("hello : print Hello World!");
            break;
        case HELLO:
            puts(hello);
            break;
        case TIMESTAMP:
            print_time();
            break;
        case REBOOT:
            reset(10);
            puts("reboot...");
            break;
        default:
            puts("Wrong cmd! Please type <help> to get usage.");
        }
    }
}

void main()
{
    shell();
}
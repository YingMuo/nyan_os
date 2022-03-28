#include "uart.h"

char buf[0x100];
const char hello[] = "Hello World!";
const char * const cmd[] = {
    "help",
    "hello"
};

enum CMD
{
    HELP = 0,
    HELLO
};

int puts(const char *s)
{
    int i = 0;
    for (; s[i] != '\0'; ++i)
        uart_write_byte(s[i]);
    uart_write_byte('\n');
    return i;
}

int print(const char *s)
{
    int i = 0;
    for (; s[i] != '\0'; ++i)
        uart_write_byte(s[i]);
    return i;
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

void shell()
{
    for (;;)
    {
        print("# ");
        gets(buf);
        int i = 0;
        for (;i < 2 && strcmp(buf, cmd[i]); ++i);
        switch (i)
        {
        case HELP:
            puts("help : print usage");
            puts("hello : print Hello World!");
            break;
        case HELLO:
            puts(hello);
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
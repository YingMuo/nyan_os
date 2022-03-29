#include "mini_uart.h"
#include "uart.h"
#include "mbox.h"
#include "util.h"
#include "reset.h"
#include <stdint.h>
#include "string.h"
#include "fb.h"

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

#define GET_BOARD_REVISION  0x00010002
#define REQUEST_CODE        0x00000000
#define REQUEST_SUCCEED     0x80000000
#define REQUEST_FAILED      0x80000001
#define TAG_REQUEST_CODE    0x00000000
#define END_TAG             0x00000000

void get_board_revision()
{
    mbox[0] = 7 * 4; // buffer size in bytes
    mbox[1] = REQUEST_CODE;
    // tags begin
    mbox[2] = GET_BOARD_REVISION; // tag identifier
    mbox[3] = 4; // maximum of request and response value buffer's length.
    mbox[4] = TAG_REQUEST_CODE;
    mbox[5] = 0; // value buffer
    // tags end
    mbox[6] = END_TAG;

    mbox_call(MBOX_CH_PROP); // message passing procedure call, you should implement it following the 6 steps provided above.

    printx(mbox[5]); // it should be 0xa020d3 for rpi3 b+
}

void main()
{
    fb_init();
    fb_show();
    uart0_init();
    get_board_revision();
    shell();
}
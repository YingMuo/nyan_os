#include "peripheral/mini_uart.h"
#include "peripheral/uart.h"
#include "peripheral/mbox.h"
#include "peripheral/fb.h"
#include "animation.h"
#include "reset.h"
#include "string.h"
#include "sysreg.h"
#include "timer.h"
#include "types.h"

const char hello[] = "Hello World!";
const char * const cmd[] = {
    "help",
    "hello",
    "timestamp",
    "reboot",
    "exc"
};

enum CMD
{
    HELP = 0,
    HELLO,
    TIMESTAMP,
    REBOOT,
    EXC
};

void print_time()
{
    uart0_putc('[');
    uint64_t tc = sysreg_read(cntpct_el0);
    uint32_t tf = sysreg_read(cntfrq_el0);
    uint32_t tp = tc / tf;
    uint32_t ts = tc % tf;
    uart0_printu(tp);
    uart0_putc('.');
    uart0_printu(ts);
    uart0_putc(']');
    uart0_putc('\n');
}

void shell()
{
    char buf[0x100];
    for (;;)
    {
        uart0_prints("# ");
        uart0_gets(buf);
        int i = 0;
        for (;i < sizeof(cmd) / 0x8 && strcmp(buf, cmd[i]); ++i);
        switch (i)
        {
        case HELP:
            uart0_puts("help : print usage");
            uart0_puts("hello : print Hello World!");
            break;
        case HELLO:
            uart0_puts(hello);
            break;
        case TIMESTAMP:
            print_time();
            break;
        case REBOOT:
            reset(10);
            uart0_puts("reboot...");
            break;
        case EXC:
            asm ("svc #1");
            break;
        default:
            uart0_puts("Wrong cmd! Please type <help> to get usage.");
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

    uart0_printx(mbox[5]); // it should be 0xa020d3 for rpi3 b+
    uart0_putc('\n');
}

void main()
{
    fb_init(512, 512, 16);
    animation_init_16();
    uart0_init();
    core_timer_enable();
    shell();
}
#include "peripheral/fb.h"
#include "peripheral/reg.h"
#include "sysreg.h"
#include "timer.h"
#include "types.h"

uint64_t jeffies;

void draw()
{
    for (int y = 0; y < 480; ++y)
    {
        for (int x = 0; x < 640; ++x)
        {
            if ((x + y + jeffies*4) / 16 % 2)
                fb_draw_pixel(x, y, 0xff, 0xff, 0xff);
            else
                fb_draw_pixel(x, y, 0x00, 0x00, 0x00);
        }
    }
}

void core_timer_hdlr()
{
    jeffies++;
    sysreg_write(cntp_tval_el0, 0xfffff);
    if (jeffies % 3 == 0)
    {
        fb_flip();
        draw();
    }
}

void core_timer_enable()
{
    sysreg_write(cntp_ctl_el0, 1);
    uint64_t tval = (sysreg_read(cntfrq_el0) & 0xffffffff) / TIMER_HZ;
    sysreg_write(cntp_tval_el0, tval);

    *CORE0_TIMER_IRQ_CTRL = 2;

    jeffies = 0;
}
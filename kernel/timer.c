#include "peripheral/reg.h"
#include "sysreg.h"
#include "timer.h"
#include "sched.h"
#include "types.h"

uint64_t jeffies;

uint64_t get_jeffies()
{
    return jeffies;
}

void inc_jeffies()
{
    ++jeffies;
}

void core_timer_hdlr()
{
    inc_jeffies();
    sysreg_write(cntp_tval_el0, 0xfffff);

    sched();
}

void core_timer_enable()
{
    sysreg_write(cntp_ctl_el0, 1);
    uint64_t tval = (sysreg_read(cntfrq_el0) & 0xffffffff) / TIMER_HZ;
    sysreg_write(cntp_tval_el0, tval);

    *CORE0_TIMER_IRQ_CTRL = 2;

    jeffies = 0;
}
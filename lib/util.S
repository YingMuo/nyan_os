.section ".text"

.global get_tc
get_tc:
    mrs x0, cntpct_el0
    ret

.global get_tf
get_tf:
    mrs x0, cntfrq_el0
    ret

.global svc1
svc1:
    svc #1
    ret

.global brk1
brk1:
    brk #1
    ret

#define CORE0_TIMER_IRQ_CTRL 0x40000040

.global core_timer_enable
core_timer_enable:
    mov x0, 1
    msr cntp_ctl_el0, x0 // enable timer
    mov x0, 0xfffffff
    msr cntp_tval_el0, x0 // set expired time
    mov x0, 2
    ldr x1, =CORE0_TIMER_IRQ_CTRL
    str x0, [x1] // enable timer interrupt
    ret
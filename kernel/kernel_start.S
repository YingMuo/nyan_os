.section ".text.kernel"

// let core with cpuid != 0 enter busy loop
_start:
    mrs x0, mpidr_el1
    and x0, x0, 3
    cbz x0, el2_start
busy_loop:
    wfe
    b busy_loop

el2_start:
    // set elf2 stack
    ldr x0, = _stack_top
    mov sp, x0

    // set elf1 stack same addr
    msr sp_el1, x0

    // clear elf1/2 bss
    ldr x1, = _sbss
    ldr w2, = bss_size
loop1:
    cbz w2, loop1_end
    str xzr, [x1], #8
    sub w2, w2, #1
    cbnz w2, loop1

loop1_end:
    // load exception table to VBAR_EL1
    ldr x0, =exc_tbl
    msr VBAR_EL1, x0

    // set hcr_el2.RW to 1 for aarch64
    mov x0, (1 << 31)
    msr hcr_el2, x0

    // set elf1 PSTATE D, A, F mask to 1 and set sp to elf1 and PSTATE.SP to 1 (interrupt is not mask)
    mov x0, 0b1101000101
    msr spsr_el2, x0

    ldr x0, =el1_start
    msr elr_el2, x0
    eret

el1_start:
    bl main
    b busy_loop
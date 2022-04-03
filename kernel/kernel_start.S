.section ".text.kernel"

// let core with cpuid != 0 enter busy loop
_start:
    mrs x0, mpidr_el1
    and x0, x0, 3
    cbz x0, 2f
1:
    wfe
    b 1b
// set stack pointer and branch to main function.
2:
    ldr x0, = _stack_top
    mov sp, x0

    ldr x1, = _sbss
    ldr w2, = bss_size
3:
    cbz w2, 4f
    str xzr, [x1], #8
    sub w2, w2, #1
    cbnz w2, 3b

4:
    // load exception table to VBAR_EL2
    ldr x0, =exc_tbl
    msr VBAR_EL2, x0

    bl main
    b 1b
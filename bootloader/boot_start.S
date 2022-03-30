.global _start
.section ".text.boot"

// let core with cpuid != 0 enter busy loop
_start:
    adr x20, .
    ldr x21, =_stext
    ldr w22, =code_size

loop0:
    cbz w22, loop0_end
    ldr x23, [x20], #8
    str x23, [x21], #8
    sub w22, w22, #1
    cbnz w22, loop0

loop0_end:
    ldr x20, =_start_bl
    br x20

.section .text
_start_bl:
// set stack pointer and branch to main function.
    ldr x20, = _estack
    mov sp, x20

    ldr x21, = _sbss
    ldr w22, = bss_size
loop1:
    cbz w22, loop1_end
    str xzr, [x21], #8
    sub w21, w21, #1
    cbnz w2, loop1

loop1_end:
    bl main

loop:
    b loop
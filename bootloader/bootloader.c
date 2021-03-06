#include "uart.h"
#include "string.h"

extern char _kernel[];
const char info[] = "Trying to load kernel.img from UART...";

void load_kernel() {
    unsigned int size;
    puts(info);
    uart0_recv_nbyte((char *)&size, 4);
    uart0_send_nbyte("Kernel base: ", 13);
    printlu((unsigned long)_kernel);
    uart0_send_nbyte("\n\r", 2);
    uart0_send_nbyte("Kernel size: ", 13);
    printu(size);
    uart0_send_nbyte("\n\r", 2);
    uart0_recv_nbyte(_kernel, size);
    uart0_send_nbyte("Start kernel", 13);

    ((void (*)(void))_kernel)();
}

int main() {
    uart0_init();
    load_kernel();
    return 0;
}
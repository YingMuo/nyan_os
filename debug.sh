#!/bin/sh

gdb-multiarch \
    -ex "set arch aarch64" \
    -ex "file ./build/bootloader.elf" \
    -ex "target remote :1234" \
    -ex "context"

#!/bin/sh

gdb-multiarch \
    -ex "set arch aarch64" \
    -ex "file ./kernel8.elf" \
    -ex "target remote :1234" \
    -ex "context"

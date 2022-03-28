SRCS := $(wildcard *.c)
ASMS := $(wildcard *.S)
OBJS := $(SRCS:%.c=%.o) $(ASMS:%.S=%.o)
CFLAGS = -mcpu=cortex-a53 \
	-fno-common -ffreestanding -O0 \
	-Wall -Werror \
	-Wl,-Tlinker.ld -nostartfiles
CROSS := aarch64-linux-gnu-
CC := gcc

all: kernel8.img

%.o: %.S
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

kernel8.img: $(OBJS)
	$(CROSS)ld -nostdlib -nostartfiles $(OBJS) -T linker.ld -o kernel8.elf
	$(CROSS)objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio

debug:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio -s -S
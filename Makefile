KERNEL_DIR := kernel
BOOT_DIR := bootloader
LIB_DIR := lib
BUILD_DIR := build

KERNEL_SRCS := $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_ASMS := $(wildcard $(KERNEL_DIR)/*.S)
KERNEL_OBJS := $(KERNEL_SRCS:$(KERNEL_DIR)/%.c=$(BUILD_DIR)/%.o) $(KERNEL_ASMS:$(KERNEL_DIR)/%.S=$(BUILD_DIR)/%.o)
KERNEL_DEPS := $(KERNEL_OBJS:.o=.d)

BOOT_SRCS := $(wildcard $(BOOT_DIR)/*.c)
BOOT_ASMS := $(wildcard $(BOOT_DIR)/*.S)
BOOT_OBJS := $(BOOT_SRCS:$(BOOT_DIR)/%.c=$(BUILD_DIR)/%.o) $(BOOT_ASMS:$(BOOT_DIR)/%.S=$(BUILD_DIR)/%.o)
BOOT_DEPS := $(BOOT_OBJS:.o=.d)

LIB_SRCS := $(wildcard $(LIB_DIR)/*.c)
LIB_ASMS := $(wildcard $(LIB_DIR)/*.S)
LIB_OBJS := $(LIB_SRCS:$(LIB_DIR)/%.c=$(BUILD_DIR)/%.o) $(LIB_ASMS:$(LIB_DIR)/%.S=$(BUILD_DIR)/%.o)
LIB_DEPS := $(LIB_OBJS:.o=.d)

CFLAGS = -mcpu=cortex-a53 \
	-fno-common -ffreestanding -O0 \
	-Wall -Werror \
	-Iinclude -MMD -MP \
	-Wl,-Tlinker.ld -nostartfiles
CROSS := aarch64-linux-gnu-
CC := gcc

all: bootloader.img kernel8.img

kernel8.img: $(KERNEL_OBJS) $(LIB_OBJS)
	$(CROSS)ld -nostdlib -nostartfiles $^ -T $(KERNEL_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf
	$(CROSS)objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

bootloader.img: $(BOOT_OBJS) $(LIB_OBJS)
	$(CROSS)ld -nostdlib -nostartfiles $^ -T $(BOOT_DIR)/linker.ld -o $(BUILD_DIR)/bootloader.elf
	$(CROSS)objcopy -O binary $(BUILD_DIR)/bootloader.elf bootloader.img

$(BUILD_DIR)/%.o: $(KERNEL_DIR)/%.S
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BOOT_DIR)/%.S
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BOOT_DIR)/%.c
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.S
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(BUILD_DIR)/kernel8.elf kernel8.img $(BUILD_DIR)/bootloader.elf bootloader.img $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio -s

debug:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio -s -S

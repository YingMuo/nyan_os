SRC_DIR := src
BUILD_DIR := build

SRCS := $(wildcard $(SRC_DIR)/*.c)
ASMS := $(wildcard $(SRC_DIR)/*.S)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(ASMS:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
CFLAGS = -mcpu=cortex-a53 \
	-fno-common -ffreestanding -O0 \
	-Wall -Werror \
	-Iinclude -MMD -MP \
	-Wl,-Tlinker.ld -nostartfiles
CROSS := aarch64-linux-gnu-
CC := gcc

all: kernel8.img

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

kernel8.img: $(OBJS)
	$(CROSS)ld -nostdlib -nostartfiles $^ -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf
	$(CROSS)objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

clean:
	rm $(BUILD_DIR)/kernel8.elf kernel8.img $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio

debug:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio -s -S

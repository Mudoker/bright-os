#--------------------------------------Makefile-------------------------------------

# Compiler
CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
OBJCOPY = aarch64-none-elf-objcopy
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib

# Directories
CLI_DIR = ./src/cli
UART_DIR = ./src/uart
GLOBAL_DIR = ./src/global
HELPER_DIR = ./src/helper
BUILD_DIR = ./build

# C files
CFILES = $(wildcard $(CLI_DIR)/*.c)
CFILES += $(wildcard $(UART_DIR)/*.c)
CFILES += $(wildcard $(GLOBAL_DIR)/*.c)
CFILES += $(wildcard $(HELPER_DIR)/styler/*.c)
CFILES += $(wildcard $(HELPER_DIR)/utils/*.c)

#S files
SFILES = $(wildcard $(CLI_DIR)/*.S)

# Object files
OFILES := $(patsubst $(CLI_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(CLI_DIR)/*.c))
OFILES += $(patsubst $(UART_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(UART_DIR)/*.c))
OFILES += $(patsubst $(GLOBAL_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(GLOBAL_DIR)/*.c))
OFILES += $(patsubst $(HELPER_DIR)/styler/%.c,${BUILD_DIR}/%.o,$(wildcard $(HELPER_DIR)/styler/*.c))
OFILES += $(patsubst $(HELPER_DIR)/utils/%.c,${BUILD_DIR}/%.o,$(wildcard $(HELPER_DIR)/utils/*.c))
OFILES += $(patsubst $(CLI_DIR)/%.S,${BUILD_DIR}/%.o,$(wildcard $(CLI_DIR)/*.S))

# Compiler
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib

# Targets
.PHONY: all clean run

all: clean kernel_brightos.img run

$(BUILD_DIR)/%.o: $(CLI_DIR)/%.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(CLI_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(UART_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(GLOBAL_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(HELPER_DIR)/styler/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(HELPER_DIR)/utils/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $^ -o $@

kernel_brightos.img: $(OFILES)
	@echo BUILDING PROJECTS... $(CFILES)
	$(LD) $(LDFLAGS) $^ -T $(CLI_DIR)/link.ld -o $(BUILD_DIR)/kernel_brightos.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel_brightos.elf $@

clean:
	del *.img .\build\*.elf .\build\*.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel_brightos.img -serial stdio

#--------------------------------------Makefile-------------------------------------

# Compiler
CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
OBJCOPY = aarch64-none-elf-objcopy
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

# Directories
CLI_DIR = ./src/cli
UART_DIR = ./src/uart
GLOBAL_DIR = ./src/global
HELPER_DIR = ./src/helper
BUILD_DIR = ./build
COMMANDS_DIR = ./src/commands
MBOX_DIR = ./src/mbox

# Object files
OFILES := $(patsubst $(CLI_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(CLI_DIR)/*.c))
OFILES += $(patsubst $(UART_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(UART_DIR)/*.c))
OFILES += $(patsubst $(GLOBAL_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(GLOBAL_DIR)/*.c))
OFILES += $(patsubst $(HELPER_DIR)/styler/%.c,${BUILD_DIR}/%.o,$(wildcard $(HELPER_DIR)/styler/*.c))
OFILES += $(patsubst $(HELPER_DIR)/utils/%.c,${BUILD_DIR}/%.o,$(wildcard $(HELPER_DIR)/utils/*.c))
OFILES += $(patsubst $(CLI_DIR)/%.S,${BUILD_DIR}/%.o,$(wildcard $(CLI_DIR)/*.S))
OFILES += $(patsubst $(COMMANDS_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(COMMANDS_DIR)/*.c))
OFILES += $(patsubst $(MBOX_DIR)/%.c,${BUILD_DIR}/%.o,$(wildcard $(MBOX_DIR)/*.c))

# Compiler
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib

# Targets
.PHONY: all clean run

all: clean kernel8.img run

$(BUILD_DIR)/%.o: $(CLI_DIR)/%.S
	$(CC) $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(CLI_DIR)/%.c
	$(CC) $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(UART_DIR)/%.c
	$(CC) $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(GLOBAL_DIR)/%.c
	$(CC) $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(HELPER_DIR)/styler/%.c
	$(CC) $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(HELPER_DIR)/utils/%.c
	$(CC) $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(COMMANDS_DIR)/%.c
	$(CC) $(GCCFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(MBOX_DIR)/%.c
	$(CC) $(GCCFLAGS) -c $^ -o $@

kernel8.img: $(OFILES)
	@echo BUILDING PROJECTS...
	$(LD) -nostdlib $^ -T $(CLI_DIR)/link.ld -o $(BUILD_DIR)/kernel8.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel8.elf $@

clean:
	del *.img .\build\*.elf .\build\*.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio

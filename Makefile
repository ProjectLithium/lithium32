include config.mk

BUILD_DIR=build
SRC_DIR=src

.PHONY: all always clean run

all: always
	@$(MAKE) -C $(SRC_DIR) BUILD_DIR=$(abspath $(BUILD_DIR))

always:
	@mkdir -p $(BUILD_DIR)/c
	@mkdir -p $(BUILD_DIR)/asm

run: all
	@qemu-system-i386 -kernel $(BUILD_DIR)/image.elf

clean:
	@rm -rf $(BUILD_DIR)/*
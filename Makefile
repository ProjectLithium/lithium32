include config.mk

BUILD_DIR=build
SRC_DIR=src

.PHONY: all always clean run

all: always
	@$(MAKE) -C $(SRC_DIR) BUILD_DIR=$(abspath $(BUILD_DIR))
	@echo "Making ISO"
	@mkdir -p $(BUILD_DIR)/iso/boot/grub
	@cp $(BUILD_DIR)/image.elf $(BUILD_DIR)/iso/boot/image.elf
	@cp $(SRC_DIR)/grub.cfg $(BUILD_DIR)/iso/boot/grub/grub.cfg
	@grub-mkrescue $(BUILD_DIR)/iso -o lithium.iso 2> /dev/null
	@echo "Build done!"

always:
	@mkdir -p $(BUILD_DIR)/c
	@mkdir -p $(BUILD_DIR)/asm

run: all
	@qemu-system-x86_64 -cdrom lithium.iso -m 4M --enable-kvm

clean:
	@rm -rf $(BUILD_DIR)/*
	@rm -rf lithium.iso
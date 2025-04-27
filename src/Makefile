TARGET_ASMFLAGS += -f elf
TARGET_CFLAGS += -nostdlib -ffreestanding -m32 -I.
TARGET_LIBS += -lgcc
TARGET_LINKFLAGS += -T link.ld -nostdlib

BUILD_DIR?=build/

HEADERS_C=$(shell find . -type f -name "*.h")

SOURCES_C=$(shell find . -type f -name "*.c")

HEADERS_ASM=$(shell find . -type f -name "*.inc")

SOURCES_ASM=$(shell find . -type f -name "*.asm")

OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/c/%.o, $(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/asm/%.o, $(SOURCES_ASM))

.PHONY: all

all: $(BUILD_DIR)/image.elf

$(BUILD_DIR)/image.elf: $(OBJECTS_ASM) $(OBJECTS_C)
	@echo "Linking image.elf"
	@$(TARGET_LD) $(TARGET_LINKFLAGS) -Wl,-Map=$(BUILD_DIR)/image.map -o $@ $^ $(TARGET_LIBS)

$(BUILD_DIR)/c/%.o: %.c $(HEADERS_C)
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<

$(BUILD_DIR)/asm/%.o: %.asm $(HEADERS_ASM)
	@echo "Assembling $<"
	@mkdir -p $(@D)
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) -o $@ $<
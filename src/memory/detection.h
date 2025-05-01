#pragma once
#include <stdint.h>
#include <boot/multiboot.h>

void init_memory_detector(multiboot_info_t* info);
uint32_t memory_get_ram_size();
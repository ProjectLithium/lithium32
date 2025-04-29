#pragma once
#include <stdint.h>

void x86_outb(uint16_t port, uint8_t value);
uint8_t x86_inb(uint16_t port);
void x86_enable_interrupts();
void x86_disable_interrupts();

void x86_iowait();
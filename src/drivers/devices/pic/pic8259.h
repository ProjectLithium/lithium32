#pragma once
#include <stdint.h>

void pic8259_remap(int offset1, int offset2);
void pic8259_eoi(uint8_t irq);
void pic8259_disable(void);
void pic8259_mask(int irq);
void pic8259_unmask(int irq);
uint16_t pic8259_get_irq_request_register();
uint16_t pic8259_get_in_service_register();
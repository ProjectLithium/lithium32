#include "idt.h"
#include <util/binary.h>

typedef struct {
	uint16_t base_low;
    uint16_t segment;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry;

typedef struct
{
    uint16_t limit;
    idt_entry* entry_ptr;
} __attribute__((packed)) idt_descriptor;

idt_entry idt[256];

idt_descriptor descriptor_idt = {sizeof(idt) - 1, idt};

extern void __attribute__((cdecl)) x86_load_idt(idt_descriptor* descriptor_ptr);

void idt_set_gate(int interrupt, void* base, uint16_t segmentDescriptor, uint8_t flags)
{
    idt[interrupt].base_low = ((uint32_t)base) & 0xFFFF;
    idt[interrupt].segment = segmentDescriptor;
    idt[interrupt].reserved = 0;
    idt[interrupt].flags = flags;
    idt[interrupt].base_high = ((uint32_t)base >> 16) & 0xFFFF;
}

void idt_enable_gate(int interrupt)
{
    SET_FLAG(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void idt_disable_gate(int interrupt)
{
    UNSET_FLAG(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void idt_install()
{
    x86_load_idt(&descriptor_idt);
}
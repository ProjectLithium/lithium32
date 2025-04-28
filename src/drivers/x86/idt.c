#include "idt.h"
#include <util/binary.h>

typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry;

typedef struct
{
    uint16_t limit;
    idt_entry* entry_ptr;
} __attribute__((packed)) idt_descriptor;



idt_entry idt[256];

idt_descriptor descriptor_idt = {sizeof(idt) - 1, &idt};

extern void __attribute__((cdecl)) x86_load_idt(idt_descriptor* descriptor_ptr);

void idt_set_gate(int interrupt, void* base, uint16_t segmentDescriptor, uint8_t flags)
{
    idt[interrupt].isr_low = (uint32_t)base & 0xFFFF;
    idt[interrupt].kernel_cs = segmentDescriptor;
    idt[interrupt].attributes = flags;
    idt[interrupt].reserved = 0;
    idt[interrupt].isr_high = (uint32_t)base >> 16;
}

void idt_enable_gate(int interrupt)
{
    SET_FLAG(idt[interrupt].attributes, IDT_FLAG_PRESENT);
}

void idt_disable_gate(int interrupt)
{
    UNSET_FLAG(idt[interrupt].attributes, IDT_FLAG_PRESENT);
}

void idt_install()
{
    x86_load_idt(&descriptor_idt);
}
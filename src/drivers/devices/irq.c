#include "irq.h"
#include "pic/pic8259.h"
#include <drivers/io/io.h>
#include <drivers/x86/isr.h>
#include <stddef.h>
#include <std/stdio.h>

#define PIC_REMAP_OFFSET        0x20

irq_handler irq_handlers[16];

void irq_default_handler(regdump* regs)
{
    int irq = regs->interrupt - PIC_REMAP_OFFSET;
    
    uint8_t pic_isr = pic8259_get_in_service_register();
    uint8_t pic_irr = pic8259_get_irq_request_register();

    if (irq_handlers[irq] != NULL)
    {
        // handle IRQ
        irq_handlers[irq](regs);
    }
    else
    {
        printf("Unhandled IRQ %d  ISR=%x  IRR=%x...\n", irq, pic_isr, pic_irr);
    }

    // send EOI
    pic8259_eoi(irq);
}

void irq_install()
{
    pic8259_remap(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);

    // register ISR handlers for each of the 16 irq lines
    for (int i = 0; i < 16; i++) {
        isr_register_handler(PIC_REMAP_OFFSET + i, irq_default_handler);
    }

    // enable interrupts
    x86_enable_interrupts();
}


void irq_register_handler(int irq, irq_handler handler)
{
    irq_handlers[irq] = handler;
}
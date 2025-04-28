#include "isr.h"
#include "idt.h"
#include <std/stdio.h>
#include <stddef.h>
#include <core/panic.h>

static const char* exceptions[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception ",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    ""
};

isr_handler handlers[256];

void __attribute__((cdecl)) x86_isr_handler(regdump* regs)
{
    int interrupt = regs->interrupt;
    if (handlers[interrupt] != NULL)
        handlers[interrupt](regs);
    else if (interrupt >= 32)
        printf("Unhandled interrupt %d!\n", interrupt);
    else {
        printf("Unhandled exception occured in kernel!\n%d %s\n", interrupt, exceptions[interrupt]);
        printf("  eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x\n",
                regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi);

        printf("  esp=%x  ebp=%x  eip=%x  eflags=%x  cs=%x  ds=%x  ss=%x\n",
                regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss);

        printf("  interrupt=%x  errorcode=%x\n", regs->interrupt, regs->error);

        printf("Kernel panic! System halted!\n");
        kernel_panic();
    }
}

void isr_install()
{
    x86_isr_init_gates();
    for (int i = 0; i < 256; i++)
    {
        idt_enable_gate(i);
    }
}
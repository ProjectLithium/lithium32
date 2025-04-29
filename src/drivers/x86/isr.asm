[bits 32]

extern x86_isr_handler

%macro ISR_NOERR 1
global x86_isr%1
x86_isr%1:
    push 0
    push %1
    jmp isr_common
%endmacro

%macro ISR_ERR 1
global x86_isr%1
x86_isr%1:
    push %1
    jmp isr_common
%endmacro

%include "drivers/x86/isrs.inc"

isr_common:
    pusha               ; pushes in order: eax, ecx, edx, ebx, esp, ebp, esi, edi

    xor eax, eax        ; push ds
    mov ax, ds
    push eax

    mov ax, 0x10        ; use kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    push esp            ; pass pointer to stack to C, so we can access all the pushed information
    call x86_isr_handler
    add esp, 4

    pop eax             ; restore old segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                ; pop what we pushed with pusha
    add esp, 8          ; remove error code and interrupt number
    iret                ; will pop: cs, eip, eflags, ss, esp
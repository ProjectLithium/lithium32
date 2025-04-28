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
    pusha

    xor eax, eax
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call x86_isr_handler
    add esp, 4

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    iret
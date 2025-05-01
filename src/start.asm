; Multiboot Header Section
section .multiboot
align 4                      ; Ensure the section is aligned to 4 bytes
dd 0x1BADB002                ; Magic number for Multiboot
dd 0x0                       ; Flags (usually zero)
dd -0x1BADB002               ; Checksum (negative of the magic number)

; Code Section
section .text
global _start                ; Declare _start as the entry point
extern main

_start:
    mov esp, stack_top
    
    ; Push Multiboot info pointer (EBX) then magic number (EAX)
    push ebx
    push eax

    call main                    ; Call the main function

hang:
    cli                          ; Clear interrupts (disable interrupts)
    hlt                          ; Halt the CPU
    jmp hang                     ; Infinite loop to keep the program halted

section .bss
align 16
stack_bottom:
    resb 16384          ; 16KB stack
stack_top:
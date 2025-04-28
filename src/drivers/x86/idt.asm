[bits 32]

; void __attribute__((cdecl)) x86_load_idt(idt_descriptor* descriptor_ptr);
; load IDT
global x86_load_idt
x86_load_idt:
    push ebp
    mov ebp, esp

    ; load IDT
    mov eax, [ebp + 8]
    lidt [eax]

    mov esp, ebp
    pop ebp
    ret
[bits 32]

; void __attribute__((cdecl)) x86_load_gdt(gdt_descriptor* descriptor_ptr, uint16_t codeSeg, uint16_t dataSeg);
; load GDT and reload segments
global x86_load_gdt
x86_load_gdt:
    push ebp
    mov ebp, esp

    ; load GDT
    mov eax, [ebp + 8]
    lgdt [eax]

    ; reload segments

    ;reload code segment
    mov eax, [ebp + 12]
    push eax
    push .reload_cs
    retf
.reload_cs:
    
    ;reload data segment
    mov ax, [ebp + 16]
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, ebp
    pop ebp
    ret
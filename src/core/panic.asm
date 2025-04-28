[bits 32]

global kernel_panic
kernel_panic:
    cli
    hlt
    jmp kernel_panic
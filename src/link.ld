OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
    . = 1M; /* 1 мегабайт */

    .text : {
        *(.multiboot)
        *(.text*)
    }

    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(.bss*) }
}

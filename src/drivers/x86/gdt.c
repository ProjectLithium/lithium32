#include "gdt.h"

typedef struct
{
    uint16_t limit_low;     // Lower 16 bits of segment limit
    uint16_t base_low;      // Lower 16 bits of base address
    uint8_t  base_middle;   // Next 8 bits of base address
    uint8_t  access;        // Access flags
    uint8_t  granularity;   // Granularity + upper 4 bits of limit
    uint8_t  base_high;     // Last 8 bits of base address
} __attribute__((packed)) gdt_entry;

typedef struct
{
    uint16_t limit;
    gdt_entry* entry_ptr;
} __attribute__((packed)) gdt_descriptor;

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)

 
#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR
 
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

extern uint32_t tss; // TSS структура где-то объявлена

gdt_entry gdt[] = {
    // NULL descriptor
    {0, 0, 0, 0, 0, 0},

    // Kernel Code Segment
    {
        .limit_low    = 0xFFFF,
        .base_low     = 0x0000,
        .base_middle  = 0x00,
        .access       = 0x9A,
        .granularity  = 0xCF, // limit high nibble | G=1, D=1
        .base_high    = 0x00,
    },

    // Kernel Data Segment
    {
        .limit_low    = 0xFFFF,
        .base_low     = 0x0000,
        .base_middle  = 0x00,
        .access       = 0x92,
        .granularity  = 0xCF,
        .base_high    = 0x00,
    }
};
     
gdt_descriptor descriptor = {sizeof(gdt) - 1, &gdt};

void __attribute__((cdecl)) x86_load_gdt(gdt_descriptor* descriptor_ptr, uint16_t codeSeg, uint16_t dataSeg);

void gdt_install()
{
    x86_load_gdt(&descriptor, x86_GDT_CODE_SEGMENT, x86_GDT_DATA_SEGMENT);
}
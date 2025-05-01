#include "detection.h"

multiboot_info_t* mbf;

void init_memory_detector(multiboot_info_t* info)
{
    mbf = info;
}

uint32_t memory_get_ram_size()
{
    uint32_t size = 0;
    uint32_t mmap_end = mbf->mmap_addr + mbf->mmap_length;
    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbf->mmap_addr;

    while ((uint32_t)mmap < mmap_end) {
        if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
            size += mmap->len; // Use len, not size!
        }

        mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }

    return size;
}
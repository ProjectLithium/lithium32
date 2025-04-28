#include "init.h"
#include <drivers/x86/gdt.h>

void init_drivers()
{
    gdt_install();
    return;
}